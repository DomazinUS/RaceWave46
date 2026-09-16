#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <array>
#include <atomic>
#include <cstdint>

namespace RT64 {
    using Wr64UiFilterDiagnosticSink = void (*)(const char *stage, const char *details);
    inline std::atomic<Wr64UiFilterDiagnosticSink> wr64UiFilterDiagnosticSink{nullptr};

    inline void setWr64UiFilterDiagnosticSink(Wr64UiFilterDiagnosticSink sink) {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        wr64UiFilterDiagnosticSink.store(sink, std::memory_order_release);
    }

    inline bool wr64UiFilterDiagnosticEnabled() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        return wr64UiFilterDiagnosticSink.load(std::memory_order_acquire) != nullptr;
    }

    inline void wr64UiFilterDiagnostic(const char *stage, const char *details) {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        if (auto sink = wr64UiFilterDiagnosticSink.load(std::memory_order_acquire))
            sink(stage, details);
    }

    // Keep one thread-local budget per stage. The budget itself uses no shared
    // collection, allocation, file access or GPU synchronization. Accepted
    // records synchronously call the frontend's bounded diagnostic sink.
    // Candidate and applied-draw stages use separate budgets so boot/menu
    // artwork cannot consume the evidence budget before the first race HUD.
    struct Wr64UiFilterDiagnosticBudget {
        uint32_t selectedMode = UINT32_MAX;
        uint64_t lastWorkload = UINT64_MAX, workloadCount = 0;
        uint64_t summarizedParts = 0;
        std::array<uint64_t, 64> hashes{};
        uint32_t hashCount = 0;

        bool observe(uint64_t workload, uint32_t mode, uint32_t part = 0) {
            if (mode != selectedMode) {
                selectedMode = mode;
                lastWorkload = UINT64_MAX;
                workloadCount = 0;
                hashCount = 0;
                summarizedParts = 0;
            }
            if (lastWorkload != workload) {
                lastWorkload = workload;
                ++workloadCount;
                summarizedParts = 0;
            }
            // An interpolated presentation can revisit the same game frame
            // many times. Report each sampled framebuffer part once, so these
            // repeats cannot exhaust the log before later menus are visited.
            if ((workloadCount != 1 && (workloadCount % 120) != 0) || part >= 64) return false;
            const uint64_t bit = uint64_t(1) << part;
            if (summarizedParts & bit) return false;
            summarizedParts |= bit;
            return true;
        }

        bool firstHash(uint64_t hash) {
            for (uint32_t i = 0; i < hashCount; ++i)
                if (hashes[i] == hash) return false;
            if (hashCount == hashes.size()) return false;
            hashes[hashCount++] = hash;
            return true;
        }
    };
}
