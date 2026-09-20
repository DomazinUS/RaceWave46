#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>

namespace RT64 {
    enum class Wr64DolphinSunEdgeScope : uint8_t { None = 0, Opening = 2 };

    // Producer-thread scene snapshot. The opening's old 20-pixel letterbox
    // concealed a full disk too; that disk is not the shortened gameplay park.
    inline Wr64DolphinSunEdgeScope wr64DolphinSunEdgeScope(
        uint32_t course, uint32_t players, uint32_t phase, uint32_t mode) {
        if (course != 0 || players != 1) return Wr64DolphinSunEdgeScope::None;
        if (phase == 0 && mode == 2) return Wr64DolphinSunEdgeScope::Opening;
        return Wr64DolphinSunEdgeScope::None;
    }

    // Opening-only edge treatment: retain its 20-pixel inset and 12-pixel transition.
    // Gameplay keeps the visible disk until its geometry leaves the screen.
    inline float wr64DolphinSunEdgeOpacity(Wr64DolphinSunEdgeScope scope,
        uint64_t textureHash, bool rectangle, float chosenTopQuarterPx) {
        if (scope != Wr64DolphinSunEdgeScope::Opening ||
            textureHash != 0x79185A8F164D1366ULL || !rectangle ||
            !std::isfinite(chosenTopQuarterPx)) return 1.0f;
        const float t = std::clamp((chosenTopQuarterPx - 80.0f) / 48.0f, 0.0f, 1.0f);
        return t * t * (3.0f - 2.0f * t);
    }
}
