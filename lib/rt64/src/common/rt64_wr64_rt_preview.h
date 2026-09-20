#pragma once

#include <cmath>
#include <cstdint>

namespace RT64 {
    // Shared live-water viewport loaded by USA 8008FB74. This is distinct
    // from both the four craft thumbnails and the results/ranking previews.
    inline constexpr bool wr64RTMenuWaterViewport(uint32_t address) {
        return address == 0x800DA8F0U;
    }

    struct WR64RTPreviewDomain {
        bool nativeWaterViewport = false;
        float scale[3] = {};
        float translate[3] = {};
        int32_t scissor[4] = {};
    };

    // Compare source viewport and native clipping as well as camera (checked
    // separately). Two draws can share a camera while belonging to different
    // menu panes. Do not demand viewport coverage: the widened preview keeps
    // its original scale while extending the scissor to the left.
    inline bool wr64RTSamePreviewDomain(const WR64RTPreviewDomain &candidate,
        const WR64RTPreviewDomain &water) {
        if (!candidate.nativeWaterViewport || !water.nativeWaterViewport) return false;
        for (uint32_t i = 0; i < 3; ++i) {
            if (!std::isfinite(candidate.scale[i]) || !std::isfinite(water.scale[i]) ||
                !std::isfinite(candidate.translate[i]) || !std::isfinite(water.translate[i]) ||
                std::abs(candidate.scale[i] - water.scale[i]) > 1e-4f ||
                std::abs(candidate.translate[i] - water.translate[i]) > 1e-4f) return false;
        }
        if (water.scale[0] <= 0.0f || water.scale[1] <= 0.0f ||
            candidate.scale[0] <= 0.0f || candidate.scale[1] <= 0.0f) return false;
        if (candidate.scissor[2] <= candidate.scissor[0] || candidate.scissor[3] <= candidate.scissor[1] ||
            water.scissor[2] <= water.scissor[0] || water.scissor[3] <= water.scissor[1]) return false;
        for (uint32_t i = 0; i < 4; ++i) {
            const int64_t delta = int64_t(candidate.scissor[i]) - int64_t(water.scissor[i]);
            if (delta < -8 || delta > 8) return false;
        }
        return true;
    }
}
