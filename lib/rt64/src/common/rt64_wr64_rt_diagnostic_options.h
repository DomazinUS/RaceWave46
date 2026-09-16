#pragma once

#include <cstdlib>

namespace RT64 {
    inline bool wr64D3D12DiagnosticNoSkyRequested(bool dxil, const char *diagnostics, const char *noSky) {
        return dxil && diagnostics && diagnostics[0] == '1' && diagnostics[1] == '\0' &&
            noSky && noSky[0] == '1' && noSky[1] == '\0';
    }

    inline bool wr64D3D12DiagnosticSkyDisabled(bool dxil) {
        // Read once for this process. This isolation never modifies saved options,
        // and neither Vulkan nor a normal launch can activate it with one flag.
        static const bool requested = wr64D3D12DiagnosticNoSkyRequested(true,
            std::getenv("WR64_D3D12_DIAGNOSTICS"),
            std::getenv("WR64_D3D12_DIAGNOSTIC_NO_SKY"));
        return dxil && requested;
    }
}
