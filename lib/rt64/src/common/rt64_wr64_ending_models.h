#pragma once

#include "rt64_wr64_hud_motion.h"

namespace RT64 {
// The ending's TOTAL POINT RANKING is a single native panel (content 10).
// Its rectangles already carry an authenticated producer and an output-frame
// translation. The four perspective previews must use that same translation:
// their RSP viewports otherwise remain at the current 20 Hz source position.
struct Wr64EndingModelPanel {
    Wr64HudMotion motion{};
    int32_t deltaQuarterY = 0;
    bool found = false;
    bool rejected = false;

    template <typename Rect>
    void include(const Wr64HudMotion &candidate, const Rect &native, const Rect &presented) {
        if (!candidate.generation || candidate.kind != 3 || candidate.content != 10 ||
            (candidate.context & 0x00ffffffu) != 0x00150107u ||
            (candidate.context >> 24 != 102 && candidate.context >> 24 != 103) ||
            candidate.slot >= 10 || candidate.x < -1024 || candidate.x > 1024 ||
            candidate.y < -1024 || candidate.y > 1024) return;

        const int64_t dy = int64_t(presented.uly) - native.uly;
        // Native panel motion is stationary or two pixels upward per tick.
        // Fail closed if a future effect changes its shape or horizontal path.
        if (presented.ulx != native.ulx || presented.lrx != native.lrx ||
            int64_t(presented.lry) - native.lry != dy || dy < 0 || dy > 8) {
            rejected = true;
            return;
        }
        if (found && (candidate.generation != motion.generation || candidate.slot != motion.slot ||
            candidate.context != motion.context || candidate.x != motion.x || candidate.y != motion.y ||
            deltaQuarterY != dy)) {
            rejected = true;
            return;
        }
        motion = candidate;
        deltaQuarterY = int32_t(dy);
        found = true;
    }

    float offsetY(bool nativePreview, float centerX, float centerY) const {
        if (!nativePreview || !found || rejected || centerX != float(motion.x + 58)) return 0.0f;
        // func_i15_802C5800, 802C5C60..802C5C9C: all four viewports
        // are centered at panel + (58, 67 + rank * 32). Other menus use
        // the same viewport allocation, so allocation identity alone is unsafe.
        for (int rank = 0; rank < 4; ++rank) {
            if (centerY == float(motion.y + 67 + rank * 32)) return deltaQuarterY * 0.25f;
        }
        return 0.0f;
    }
};
}
