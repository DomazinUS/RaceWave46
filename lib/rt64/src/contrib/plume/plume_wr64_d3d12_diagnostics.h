#pragma once

#include "../../../../../include/wr64_diagnostic_policy.h"

// Opt-in failure capture only. No debug layer or normal rendering policy changes.
#ifdef PLUME_D3D12_AGILITY_SDK_ENABLED
#include <directx/d3d12.h>
#else
#include <d3d12.h>
#endif
#include <cstdio>
#include <cstdlib>
#include <mutex>

namespace plume {
    inline bool wr64D3D12DiagnosticsEnabled() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool enabled = [] {
            const char *value = std::getenv("WR64_D3D12_DIAGNOSTICS");
            return value && value[0] == '1' && value[1] == '\0';
        }();
        return enabled;
    }

    inline void wr64D3D12EnableDiagnostics() {
        if (!wr64D3D12DiagnosticsEnabled()) return;
        // DRED settings must be configured before the first D3D12CreateDevice.
        ID3D12DeviceRemovedExtendedDataSettings *settings = nullptr;
        const HRESULT result = D3D12GetDebugInterface(IID_PPV_ARGS(&settings));
        if (SUCCEEDED(result) && settings) {
            settings->SetAutoBreadcrumbsEnablement(D3D12_DRED_ENABLEMENT_FORCED_ON);
            settings->SetPageFaultEnablement(D3D12_DRED_ENABLEMENT_FORCED_ON);
            settings->Release();
        }
        std::fprintf(stderr, "[d3d12-diagnostic] enabled=1 dred_settings=0x%08lX breadcrumbs=%u page_faults=%u debug_layer_requested=0\n",
            static_cast<unsigned long>(result), unsigned(SUCCEEDED(result)), unsigned(SUCCEEDED(result)));
        std::fflush(stderr);
    }

    inline const char *wr64D3D12DiagnosticName(const char *nameA, const wchar_t *nameW, char (&text)[192]) {
        if (nameA) {
            unsigned i = 0;
            for (; i < sizeof(text) - 1 && nameA[i]; ++i) text[i] = nameA[i];
            text[i] = '\0';
        }
        else if (nameW) {
            int length = 0;
            while (length < 60 && nameW[length]) ++length;
            const int bytes = WideCharToMultiByte(CP_UTF8, 0, nameW, length, text, sizeof(text) - 1, nullptr, nullptr);
            text[bytes > 0 ? bytes : 0] = '\0';
        }
        else return "(unnamed)";
        for (unsigned i = 0; text[i]; ++i)
            if (text[i] == '\r' || text[i] == '\n' || text[i] == '\t') text[i] = ' ';
        return text;
    }

    inline const char *wr64D3D12BreadcrumbOperation(D3D12_AUTO_BREADCRUMB_OP operation) {
        switch (operation) {
        case D3D12_AUTO_BREADCRUMB_OP_DRAWINSTANCED: return "DrawInstanced";
        case D3D12_AUTO_BREADCRUMB_OP_DRAWINDEXEDINSTANCED: return "DrawIndexedInstanced";
        case D3D12_AUTO_BREADCRUMB_OP_DISPATCH: return "Dispatch";
        case D3D12_AUTO_BREADCRUMB_OP_EXECUTEINDIRECT: return "ExecuteIndirect";
        case D3D12_AUTO_BREADCRUMB_OP_COPYBUFFERREGION: return "CopyBufferRegion";
        case D3D12_AUTO_BREADCRUMB_OP_COPYTEXTUREREGION: return "CopyTextureRegion";
        case D3D12_AUTO_BREADCRUMB_OP_COPYRESOURCE: return "CopyResource";
        case D3D12_AUTO_BREADCRUMB_OP_RESOLVESUBRESOURCE: return "ResolveSubresource";
        case D3D12_AUTO_BREADCRUMB_OP_RESOLVESUBRESOURCEREGION: return "ResolveSubresourceRegion";
        case D3D12_AUTO_BREADCRUMB_OP_RESOURCEBARRIER: return "ResourceBarrier";
        case D3D12_AUTO_BREADCRUMB_OP_BUILDRAYTRACINGACCELERATIONSTRUCTURE: return "BuildRaytracingAccelerationStructure";
        case D3D12_AUTO_BREADCRUMB_OP_DISPATCHRAYS: return "DispatchRays";
        default: return "other";
        }
    }

    inline void wr64D3D12DumpAllocations(const char *kind, const D3D12_DRED_ALLOCATION_NODE1 *node) {
        unsigned count = 0;
        for (; node && count < 32; node = node->pNext, ++count) {
            char name[192];
            std::fprintf(stderr, "[d3d12-diagnostic] allocation=%s index=%u type=%u object=%p name=%s\n",
                kind, count, unsigned(node->AllocationType), node->pObject,
                wr64D3D12DiagnosticName(node->ObjectNameA, node->ObjectNameW, name));
        }
        std::fprintf(stderr, "[d3d12-diagnostic] allocation_summary=%s count=%u truncated=%u\n", kind, count, unsigned(node != nullptr));
    }

    inline void wr64D3D12Failure(ID3D12Device *device, const char *operation, HRESULT result) {
        if (SUCCEEDED(result) || !wr64D3D12DiagnosticsEnabled()) return;
        // Other failing threads wait here until the first report has been flushed.
        // Do not let a second thread exit the process halfway through its report.
        static std::mutex reportMutex;
        const std::lock_guard<std::mutex> lock(reportMutex);
        const HRESULT removedReason = device ? device->GetDeviceRemovedReason() : E_POINTER;
        std::fprintf(stderr, "[d3d12-diagnostic] failure operation=%s hresult=0x%08lX device_removed_reason=0x%08lX thread=%lu\n",
            operation, static_cast<unsigned long>(result), static_cast<unsigned long>(removedReason), GetCurrentThreadId());
        std::fflush(stderr);
        ID3D12DeviceRemovedExtendedData1 *dred = nullptr;
        const HRESULT queryResult = device ? device->QueryInterface(IID_PPV_ARGS(&dred)) : E_POINTER;
        std::fprintf(stderr, "[d3d12-diagnostic] dred_interface=0x%08lX\n", static_cast<unsigned long>(queryResult));
        if (SUCCEEDED(queryResult) && dred) {
            D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT1 breadcrumbs{};
            const HRESULT breadcrumbResult = dred->GetAutoBreadcrumbsOutput1(&breadcrumbs);
            std::fprintf(stderr, "[d3d12-diagnostic] breadcrumbs_result=0x%08lX\n", static_cast<unsigned long>(breadcrumbResult));
            const auto *node = SUCCEEDED(breadcrumbResult) ? breadcrumbs.pHeadAutoBreadcrumbNode : nullptr;
            unsigned nodes = 0;
            for (; node && nodes < 64; node = node->pNext, ++nodes) {
                const UINT completed = node->pLastBreadcrumbValue ? *node->pLastBreadcrumbValue : 0;
                char listName[192], queueName[192];
                std::fprintf(stderr, "[d3d12-diagnostic] breadcrumb_node=%u command_list=%p list_name=%s queue=%p queue_name=%s completed=%u count=%u last_value_present=%u\n",
                    nodes, node->pCommandList,
                    wr64D3D12DiagnosticName(node->pCommandListDebugNameA, node->pCommandListDebugNameW, listName),
                    node->pCommandQueue,
                    wr64D3D12DiagnosticName(node->pCommandQueueDebugNameA, node->pCommandQueueDebugNameW, queueName),
                    completed, node->BreadcrumbCount, unsigned(node->pLastBreadcrumbValue != nullptr));
                // History is a 65,536-entry ring, even when the logical count is larger.
                const UINT stop = completed < node->BreadcrumbCount ? completed : node->BreadcrumbCount;
                const UINT retainedStart = node->BreadcrumbCount > 65536 ? node->BreadcrumbCount - 65536 : 0;
                UINT begin = stop > 8 ? stop - 8 : 0;
                if (begin < retainedStart) begin = retainedStart;
                const UINT remaining = node->BreadcrumbCount - stop;
                const UINT end = stop + (remaining < 8 ? remaining : 8);
                if (node->pCommandHistory) for (UINT index = begin; index < end; ++index) {
                    const auto op = node->pCommandHistory[index % 65536];
                    std::fprintf(stderr, "[d3d12-diagnostic] breadcrumb_node=%u index=%u completed=%u operation=%s opcode=%u\n",
                        nodes, index, unsigned(index < completed), wr64D3D12BreadcrumbOperation(op), unsigned(op));
                }
            }
            std::fprintf(stderr, "[d3d12-diagnostic] breadcrumb_nodes=%u truncated=%u\n", nodes, unsigned(node != nullptr));
            D3D12_DRED_PAGE_FAULT_OUTPUT1 pageFault{};
            const HRESULT pageFaultResult = dred->GetPageFaultAllocationOutput1(&pageFault);
            std::fprintf(stderr, "[d3d12-diagnostic] page_fault_result=0x%08lX address=0x%016llX\n",
                static_cast<unsigned long>(pageFaultResult), static_cast<unsigned long long>(pageFault.PageFaultVA));
            if (SUCCEEDED(pageFaultResult)) {
                wr64D3D12DumpAllocations("existing", pageFault.pHeadExistingAllocationNode);
                wr64D3D12DumpAllocations("recently_freed", pageFault.pHeadRecentFreedAllocationNode);
            }
            dred->Release();
        }
        std::fprintf(stderr, "[d3d12-diagnostic] report_complete=1 terminating=1\n");
        std::fflush(stderr);
        std::fflush(stdout);
        std::_Exit(1);
    }
}
