#pragma once

#include <cstdint>

namespace recompinput {
    // The rumble envelope advances on every host update (about 1 kHz), so it
    // produces a new strength almost every call. Each change becomes a driver
    // command and a USB/radio packet, which some controller firmware cannot
    // sustain and latches its motor on. Quantize the output and cap the rate
    // of changes. A stop is never delayed.
    class RumbleLimiter {
    public:
        static constexpr uint32_t levels = 32;
        static constexpr uint64_t min_change_interval_ms = 25;

        // Levels are relative to full_scale, the output at full envelope for the
        // player's strength setting, so every non-zero setting keeps all levels.
        static constexpr uint16_t quantize(uint16_t strength, uint16_t full_scale) {
            if (full_scale == 0) return 0;
            const uint32_t clamped = strength < full_scale ? strength : full_scale;
            const uint32_t level = (clamped * levels + full_scale / 2) / full_scale;
            return uint16_t(level * full_scale / levels);
        }

        // Returns the strength to hand to SDL. SDL only issues a driver command
        // when this differs from the previous call.
        uint16_t next(uint16_t requested, uint16_t full_scale, uint64_t now_ms) {
            const uint16_t target = quantize(requested, full_scale);
            if (target == held_) return held_;
            if (target == 0 || !changed_ || now_ms < last_change_ms_ ||
                now_ms - last_change_ms_ >= min_change_interval_ms) {
                held_ = target;
                last_change_ms_ = now_ms;
                changed_ = true;
            }
            return held_;
        }

        void reset() { *this = RumbleLimiter{}; }
        uint16_t held() const { return held_; }

    private:
        uint16_t held_ = 0;
        uint64_t last_change_ms_ = 0;
        bool changed_ = false;
    };
}
