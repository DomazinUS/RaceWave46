#pragma once

#include <cmath>
#include <cstdint>

#include "rt64_wr64_vertical_split.h"

namespace RT64 {
    // Source coordinates, before horizontal/vertical presentation mapping.
    // Populate from the actual perspective projection and its draw's scissor,
    // never from a framebuffer's aggregate scissor or the output rectangle.
    struct WR64RTViewDomain {
        bool perspective = false;
        bool menuModelPreview = false;
        bool menuWaterPreview = false;
        float scale[3] = {};
        float translate[3] = {};
        int32_t scissor[4] = {};
    };

    // Return 1/2 for the native race view, or zero for another domain. The
    // caller also supplies the active two-player race/course feature gate.
    // make_world_glist uses A8D0/A8E0 for backdrop, cloud and water alike;
    // the full-height viewport is cropped by each exact half-scissor. Signal,
    // indicator, menu, HUD and one-player viewports must not select a scene.
    inline uint32_t wr64RTNativeRaceView(const WR64RTViewDomain &domain) {
        if (!domain.perspective || domain.menuModelPreview || domain.menuWaterPreview)
            return 0;
        for (uint32_t i = 0; i < 3; ++i) {
            if (!std::isfinite(domain.scale[i]) || !std::isfinite(domain.translate[i]))
                return 0;
        }
        int viewportHalf = 0;
        if (wr64VerticalViewport(domain.scale[0], domain.scale[1],
            domain.translate[0], domain.translate[1], viewportHalf) !=
                Wr64VerticalViewport::World) return 0;
        const int scissorHalf = wr64VerticalHalfScissor(domain.scissor[0],
            domain.scissor[1], domain.scissor[2], domain.scissor[3]);
        return scissorHalf == viewportHalf ? uint32_t(viewportHalf) : 0;
    }

    // Ending's main perspective world may contain no water in podium shots.
    // Validate the native viewport and either authored or borderless scissor
    // before admitting its opaque scene as a shadow-camera source. Callers
    // additionally require depth-writing world material and matching matrices.
    inline bool wr64RTEndingWorldView(bool endingScope, const WR64RTViewDomain &domain) {
        if (!endingScope || !domain.perspective || domain.menuModelPreview || domain.menuWaterPreview)
            return false;
        for (uint32_t i = 0; i < 3; ++i)
            if (!std::isfinite(domain.scale[i]) || !std::isfinite(domain.translate[i])) return false;
        const bool full = domain.scissor[0] == 0 && domain.scissor[1] == 0 &&
            domain.scissor[2] == 1696 && domain.scissor[3] == 960;
        // make_world_glist 8008FF28..3C: ED020050 0067C36C.
        const bool authored = domain.scissor[0] == 32 && domain.scissor[1] == 80 &&
            domain.scissor[2] == 1660 && domain.scissor[3] == 876;
        return std::abs(domain.scale[0] - 212.0f) < 0.01f &&
            std::abs(std::abs(domain.scale[1]) - 120.0f) < 0.01f &&
            std::abs(domain.translate[0] - 212.0f) < 0.01f &&
            std::abs(domain.translate[1] - 120.0f) < 0.01f &&
            (full || authored);
    }

    // Ownership is necessary but not sufficient: keep the existing camera
    // matrix comparison at the call site (full view for geometry, orientation
    // for sky). Projection indices may differ within the same camera domain.
    inline bool wr64RTSameRaceView(const WR64RTViewDomain &candidate,
        const WR64RTViewDomain &water) {
        const uint32_t owner = wr64RTNativeRaceView(water);
        return owner != 0 && wr64RTNativeRaceView(candidate) == owner;
    }
}
