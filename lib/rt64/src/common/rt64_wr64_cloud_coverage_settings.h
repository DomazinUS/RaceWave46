#pragma once

#include <atomic>
#include <cstdint>

namespace RT64 {
    inline constexpr uint32_t wr64CloudCoverageMode(uint32_t mode) {
        return mode == 1U ? 1U : 0U;
    }

    inline std::atomic<uint32_t> wr64CloudCoverageSetting{0U};

    inline void setWr64CloudCoverageMode(uint32_t mode) {
        wr64CloudCoverageSetting.store(wr64CloudCoverageMode(mode), std::memory_order_relaxed);
    }

    inline uint32_t getWr64CloudCoverageMode() {
        return wr64CloudCoverageSetting.load(std::memory_order_relaxed);
    }

    // State samples this once before preparing a native workload. Presentation
    // keeps that workload's owned geometry when the UI changes the next mode.
    inline bool wr64CloudCoverageEnabled() {
        return getWr64CloudCoverageMode() == 1U;
    }
}
