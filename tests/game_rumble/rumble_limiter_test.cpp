#include "recompinput/rumble_limiter.h"

#include <cstdint>
#include <cstdlib>
#include <iostream>

namespace {
using recompinput::RumbleLimiter;

void require(bool condition, const char* message) {
    if (!condition) { std::cerr << message << '\n'; std::exit(1); }
}

void quantization_contract() {
    require(RumbleLimiter::quantize(0) == 0, "Zero must stay zero");
    require(RumbleLimiter::quantize(0x03FF) == 0, "Values below half a level must stop");
    require(RumbleLimiter::quantize(0x0400) == 0x0800, "Half a level rounds up");
    require(RumbleLimiter::quantize(0xFFFF) == 0xFFFF, "Full strength must stay full");
    require(RumbleLimiter::quantize(0xFC00) == 0xFFFF, "The top level must clamp to full strength");
}

void timing_contract() {
    RumbleLimiter limiter;
    require(limiter.next(0x8000, 1000) == 0x8000, "The first change must pass immediately");
    require(limiter.next(0x9000, 1001) == 0x8000, "A fast change must hold the previous level");
    require(limiter.next(0x9000, 1024) == 0x8000, "The hold must last the full interval");
    require(limiter.next(0x9000, 1025) == 0x9000, "The change must pass after the interval");
    require(limiter.next(0, 1026) == 0, "A stop must never be delayed");
    require(limiter.next(0x4000, 1027) == 0, "A restart right after a stop must wait");
    require(limiter.next(0x4000, 1051) == 0x4000, "The restart must pass after the interval");
    limiter.reset();
    require(limiter.held() == 0 && limiter.next(0x2000, 1052) == 0x2000,
        "Reset must forget the held level and allow the next change");
}

// Replay the host envelope from input_state.cpp at its ~1 ms cadence with the
// game's 60 Hz duty cycle and count the commands that would reach the driver.
void game_pattern_rate() {
    for (const unsigned intensity : {40u, 60u, 128u, 200u, 255u}) {
        RumbleLimiter limiter;
        float cur = 0.0f;
        unsigned phase = 0;
        bool on = false;
        uint16_t last_sent = 0;
        unsigned driver_calls = 0;
        unsigned active_ms = 0;
        uint64_t next_tick_us = 0;
        constexpr uint64_t seconds = 10;
        for (uint64_t ms = 0; ms < seconds * 1000; ++ms) {
            while (ms * 1000 >= next_tick_us) {
                phase += intensity;
                on = phase >= 256;
                if (on) phase -= 256;
                next_tick_us += 1'000'000 / 60;
            }
            if (on) { cur += 0.17f; if (cur > 1.0f) cur = 1.0f; }
            else { cur = cur * 0.92f - 0.01f; if (cur < 0.0f) cur = 0.0f; }
            const float smooth = cur * cur * (3.0f - 2.0f * cur);
            const uint16_t sent = limiter.next(uint16_t(smooth * 0xFFFF), ms);
            if (sent != last_sent) ++driver_calls;
            active_ms += sent != 0;
            last_sent = sent;
        }
        const unsigned per_second = unsigned(driver_calls / seconds);
        std::cout << "intensity " << intensity << ": " << per_second << " driver commands/s, "
                  << active_ms / seconds << " ms/s active\n";
        require(per_second <= 80, "The limiter must keep the driver command rate low");
        require(active_ms > 0, "A sustained request must still rumble");
    }
}
}

int main() {
    quantization_contract();
    timing_contract();
    game_pattern_rate();
    std::cout << "Rumble output limiter contracts passed\n";
}
