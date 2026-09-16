#pragma once
#include <cstdint>
#include "rt64_wr64_raster_sky_scope.h"

namespace RT64 {
    // Share the established one-player course-world eligibility, including
    // introductions and Dolphin Park's opening/title, plus all eight native
    // two-player race courses with their Enhanced assets already loaded.
    inline constexpr bool wr64RasterShadowScope(bool selected, uint32_t course,
        uint32_t players, uint32_t phase, uint32_t mode, bool loadedEnhanced = false) {
        return wr64RTReflectionScope(selected, course, players, phase, mode) ||
            wr64RasterTwoPlayerScope(selected, course, players, phase, mode, loadedEnhanced);
    }
}
