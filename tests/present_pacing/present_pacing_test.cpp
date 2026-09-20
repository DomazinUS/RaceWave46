#include <cstdint>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <initializer_list>
#include <limits>
#include <windows.h>
#include <dxgi1_5.h>

#include "common/rt64_wr64_present_pacing.h"

namespace plume {
struct RenderCommandSemaphore {};
struct FakeNativeSwapChain {
    UINT interval = UINT_MAX;
    UINT flags = UINT_MAX;
    uint32_t calls = 0;
    HRESULT result = S_OK;
    HRESULT Present(UINT syncInterval, UINT presentFlags) {
        interval = syncInterval;
        flags = presentFlags;
        ++calls;
        return result;
    }
};
struct D3D12SwapChain {
    struct { bool enablePresentWait = false; } desc;
    bool vsyncEnabled = true;
    UINT swapChainFlags = 0;
    FakeNativeSwapChain *d3d = nullptr;
    bool present(uint32_t textureIndex, RenderCommandSemaphore **waitSemaphores,
        uint32_t waitSemaphoreCount);
};
#include "present_implementation.inc"
} // namespace plume

namespace RT64 {
struct UserConfiguration {
    enum class GraphicsAPI { D3D12, Vulkan, Metal, Automatic };
};
using Timestamp = int;
struct FakePresentSwapChain {
    bool vsync = true;
    bool isVsyncEnabled() const { return vsync; }
};
struct FakePresentExternal {
    UserConfiguration::GraphicsAPI createdGraphicsAPI;
    FakePresentSwapChain *swapChain;
};
bool productionSleeps(FakePresentExternal ext, bool presentWaitEnabled,
    uint32_t targetRate, uint32_t swapChainRate, uint32_t viOriginalRate,
    Timestamp presentTimestamp) {
#include "pacing_implementation.inc"
}
} // namespace RT64

static uint32_t checks = 0;
static void check(bool condition, const char *message) {
    ++checks;
    if (!condition) {
        std::fprintf(stderr, "FAIL: %s (check %u)\n", message, checks);
        std::exit(1);
    }
}

int main() {
    // Exercise the real backend call, including its HRESULT propagation. No
    // swap chain or HWND is created: only the native Present endpoint is inert.
    for (bool vsync : { false, true }) {
        for (bool waitable : { false, true }) {
            for (bool tearing : { false, true }) {
                for (HRESULT result : { S_OK, DXGI_STATUS_OCCLUDED, DXGI_ERROR_DEVICE_REMOVED }) {
                    plume::FakeNativeSwapChain native;
                    native.result = result;
                    plume::D3D12SwapChain chain;
                    chain.d3d = &native;
                    chain.vsyncEnabled = vsync;
                    chain.desc.enablePresentWait = waitable;
                    chain.swapChainFlags = tearing ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0;
                    const bool valid = chain.present(2, nullptr, 0);
                    check(native.calls == 1, "one native Present per output frame");
                    check(native.interval == (vsync ? 1u : 0u),
                        "waitable queue cannot disable requested VSync");
                    check(native.flags == ((!vsync && tearing) ? DXGI_PRESENT_ALLOW_TEARING : 0u),
                        "tearing requires both permission and VSync disabled");
                    check(valid == SUCCEEDED(result), "native result propagated");
                }
            }
        }
    }

    using API = RT64::UserConfiguration::GraphicsAPI;
    constexpr uint32_t rates[] = { 0, 20, 30, 59, 60, 61, 120, 144, 179, 180, 181, 240,
        std::numeric_limits<uint32_t>::max() };
    for (API api : { API::D3D12, API::Vulkan, API::Metal, API::Automatic }) {
        for (bool vsync : { false, true }) {
            for (bool waitable : { false, true }) {
                for (uint32_t target : rates) {
                    for (uint32_t display : rates) {
                        for (uint32_t native : { 0u, 20u, 30u, 60u }) {
                            for (int previous : { 0, 1 }) {
                                RT64::FakePresentSwapChain chain{vsync};
                                const bool actual = RT64::productionSleeps({api, &chain},
                                    waitable, target, display, native, previous);
                                const bool originalLimiter = previous && target > 0 && target > native;
                                bool expected = originalLimiter;
                                if (api == API::D3D12 && vsync && waitable && display && target >= display) {
                                    expected = false;
                                }
                                check(actual == expected,
                                    "production sleep preserves native/manual/other-backend boundaries");
                            }
                        }
                    }
                }
            }
        }
    }
    std::printf("PASS: %u checks; native DXGI call and production pacing decision, no windows or game\n", checks);
}
