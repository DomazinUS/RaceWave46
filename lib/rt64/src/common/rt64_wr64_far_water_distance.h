#pragma once

#include <atomic>
#include <cstdint>

namespace RT64 {
    // Only the neutral outer coverage changes. The first ring remains the
    // accepted wave-to-flat transition at every setting.
    inline constexpr uint32_t wr64FarWaterDistanceMode(uint32_t mode) {
        return mode <= 5U ? mode : 0U;
    }

    inline std::atomic<uint32_t> wr64FarWaterDistanceSetting{0U};

    inline void setWr64FarWaterDistanceMode(uint32_t mode) {
        wr64FarWaterDistanceSetting.store(wr64FarWaterDistanceMode(mode),
            std::memory_order_relaxed);
    }

    inline uint32_t getWr64FarWaterDistanceMode() {
        return wr64FarWaterDistanceSetting.load(std::memory_order_relaxed);
    }

    // Native world scenes only. A caller captures each selected camera before
    // publishing the workload; the geometry checks still identify the sheet.
    inline constexpr bool wr64FarWaterDistanceScope(uint32_t course,
        uint32_t players, uint32_t phase, uint32_t raceMode, uint32_t view,
        uint32_t cameraIndex, uint32_t cameraType, uint32_t cameraOwner,
        bool loadedEnhanced = false) {
        const bool race = phase == 1U && raceMode >= 40U && raceMode <= 45U;
        const bool world = players == 1U ? course <= 8U &&
            (phase == 1U || (phase == 8U && (raceMode == 30U || raceMode == 31U)) ||
                (course == 0U && phase == 0U && raceMode >= 2U && raceMode <= 4U)) :
            players == 2U && course <= 8U && (course != 0U || loadedEnhanced) && race;
        return world && view < players && cameraIndex <= 1U &&
            (cameraType == 3U || cameraType == 4U || cameraType == 5U) && cameraOwner == cameraIndex;
    }

    inline constexpr double wr64FarWaterRingScale(uint32_t mode, uint32_t layer) {
        // Exact binary fractions preserve Original bit-for-bit and keep the
        // four rings ordered across every current/previous mode transition.
        constexpr double scales[6][4] = {
            {1.125, 1.75, 2.375, 3.0},
            {1.125, 2.25, 3.375, 4.5},
            {1.125, 2.75, 4.375, 6.0},
            {1.125, 3.75, 6.375, 9.0},
            {1.125, 4.75, 8.375, 12.0},
            {1.125, 5.75, 10.375, 15.0}
        };
        return layer >= 1U && layer <= 4U
            ? scales[wr64FarWaterDistanceMode(mode)][layer - 1U] : 1.0;
    }
}
