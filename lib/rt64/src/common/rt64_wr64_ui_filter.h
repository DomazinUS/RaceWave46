#pragma once

#include <atomic>
#include <cstdint>

namespace RT64 {
    enum class Wr64UiFilter : uint32_t {
        Original = 0,
        Light = 1,
        Enhanced = 2
    };

    // Written by the settings UI, read once when preparing each game workload.
    // The native game state and the final framebuffer filter are independent.
    inline std::atomic<uint32_t> wr64UiFilterSetting{0};

    inline void setWr64UiFilter(uint32_t mode) {
        wr64UiFilterSetting.store(mode <= uint32_t(Wr64UiFilter::Enhanced) ? mode : 0,
            std::memory_order_relaxed);
    }

    inline uint32_t getWr64UiFilter() {
        return wr64UiFilterSetting.load(std::memory_order_relaxed);
    }
}
