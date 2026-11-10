#include "recompinput/rumble_limiter.h"

#include <cstdint>
#include <cstdlib>
#include <iostream>

namespace {
using recompinput::RumbleLimiter;

void require(bool condition, const char* message) {
    if (!condition) { std::cerr << message << '\n'; std::exit(1); }
}

constexpr uint16_t full = 0xFFFF;

constexpr uint16_t q(uint16_t strength) { return RumbleLimiter::quantize(strength, full); }

void quantization_contract() {
    require(q(0) == 0, "Zero must stay zero");
    require(q(0x03FF) == 0, "Values below half a level must stop");
    require(q(0x0400) == full / RumbleLimiter::levels, "Half a level rounds up");
    require(q(0xFFFF) == full, "Full strength must stay full");
    require(q(0xFC00) == full, "The top level must round to full strength");
    require(RumbleLimiter::quantize(1, 0) == 0, "A zero strength setting must stay off");
}

// Levels are relative to the strength setting, so low settings keep the same
// shape as full strength instead of rounding away or being amplified.
void strength_setting_contract() {
    for (const unsigned percent : {1u, 2u, 5u, 25u, 50u, 100u}) {
        const uint16_t scale = uint16_t(percent * 0xFFFF / 100);
        require(RumbleLimiter::quantize(scale, scale) == scale,
            "Full envelope must reach the configured strength");
        uint16_t previous = 0;
        unsigned distinct = 0;
        for (uint32_t s = 0; s <= scale; ++s) {
            const uint16_t value = RumbleLimiter::quantize(uint16_t(s), scale);
            require(value <= scale, "Output must never exceed the configured strength");
            require(value >= previous, "Quantization must be monotonic");
            distinct += value != previous;
            previous = value;
        }
        require(distinct == RumbleLimiter::levels, "Every non-zero setting must keep all levels");
    }
}

void timing_contract() {
    RumbleLimiter limiter;
    require(limiter.next(0x8000, full, 1000) == q(0x8000), "The first change must pass immediately");
    require(limiter.next(0x9000, full, 1001) == q(0x8000), "A fast change must hold the previous level");
    require(limiter.next(0x9000, full, 1024) == q(0x8000), "The hold must last the full interval");
    require(limiter.next(0x9000, full, 1025) == q(0x9000), "The change must pass after the interval");
    require(limiter.next(0, full, 1026) == 0, "A stop must never be delayed");
    require(limiter.next(0x4000, full, 1027) == 0, "A restart right after a stop must wait");
    require(limiter.next(0x4000, full, 1051) == q(0x4000), "The restart must pass after the interval");
    limiter.reset();
    require(limiter.held() == 0 && limiter.next(0x2000, full, 1052) == q(0x2000),
        "Reset must forget the held level and allow the next change");
}

struct PatternResult {
    unsigned driver_calls_per_second;
    unsigned active_ms;
};

constexpr uint64_t pattern_seconds = 10;

// Replay the host envelope from input_state.cpp at its ~1 ms cadence with the
// game's 60 Hz duty cycle and count the commands that would reach the driver.
PatternResult replay_game_pattern(unsigned intensity, unsigned percent) {
    const uint16_t scale = uint16_t(percent * 0xFFFF / 100);
    RumbleLimiter limiter;
    float cur = 0.0f;
    unsigned phase = 0;
    bool on = false;
    uint16_t last_sent = 0;
    unsigned driver_calls = 0;
    unsigned active_ms = 0;
    uint64_t next_tick_us = 0;
    for (uint64_t ms = 0; ms < pattern_seconds * 1000; ++ms) {
        while (ms * 1000 >= next_tick_us) {
            phase += intensity;
            on = phase >= 256;
            if (on) phase -= 256;
            next_tick_us += 1'000'000 / 60;
        }
        if (on) { cur += 0.17f; if (cur > 1.0f) cur = 1.0f; }
        else { cur = cur * 0.92f - 0.01f; if (cur < 0.0f) cur = 0.0f; }
        const float smooth = cur * cur * (3.0f - 2.0f * cur);
        const uint16_t sent = limiter.next(uint16_t(smooth * scale), scale, ms);
        if (sent != last_sent) ++driver_calls;
        active_ms += sent != 0;
        last_sent = sent;
    }
    return { unsigned(driver_calls / pattern_seconds), active_ms };
}

void game_pattern_rate() {
    for (const unsigned intensity : {40u, 60u, 128u, 200u, 255u}) {
        const unsigned full_strength_active_ms = replay_game_pattern(intensity, 100).active_ms;
        for (const unsigned percent : {100u, 25u, 1u}) {
            const PatternResult result = replay_game_pattern(intensity, percent);
            std::cout << "intensity " << intensity << " at " << percent << "%: "
                      << result.driver_calls_per_second << " driver commands/s, "
                      << result.active_ms / pattern_seconds << " ms/s active\n";
            require(result.driver_calls_per_second <= 80,
                "The limiter must keep the driver command rate low");
            require(result.active_ms > 0, "A sustained request must still rumble");
            require(result.active_ms * 100 >= full_strength_active_ms * 95,
                "A low strength setting must rumble as long as full strength");
        }
    }
}
}

int main() {
    quantization_contract();
    strength_setting_contract();
    timing_contract();
    game_pattern_rate();
    std::cout << "Rumble output limiter contracts passed\n";
}
