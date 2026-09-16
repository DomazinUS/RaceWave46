#pragma once

#include <array>
#include <atomic>
#include <cstdint>

namespace RT64 {
    // Native course loading publishes only after the validated full roots and full
    // water textures are resident. Each course slot atomically owns one RAM
    // identity, so a reader cannot combine a course with another publication's
    // pointer. Loading clears every slot before publishing exactly one owner.
    // GPU work uses the workload snapshot rather than these producer markers.
    inline std::array<std::atomic<const uint8_t *>, 9> wr64RTTwoPlayerAssetsRam{};

    inline void wr64RTPublishTwoPlayerAssets(const uint8_t *ram, uint32_t course) {
        for (auto &owner : wr64RTTwoPlayerAssetsRam) {
            owner.store(nullptr, std::memory_order_release);
        }
        if (ram && course <= 8) {
            wr64RTTwoPlayerAssetsRam[course].store(ram, std::memory_order_release);
        }
    }

    inline bool wr64RTTwoPlayerAssetsReady(const uint8_t *ram, uint32_t course) {
        return ram && course <= 8 &&
            wr64RTTwoPlayerAssetsRam[course].load(std::memory_order_acquire) == ram;
    }
}
