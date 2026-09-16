#pragma once

#include <stdint.h>
#ifndef __cplusplus
#include <stdbool.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Game thread: call once after USA Rev1 move_hover (800665B0) completes.
// Reads the USA state only; never writes the emulated game or save memory.
void wr64_game_rumble_sample(uint8_t* rdram);

// Host event thread, immediately before wr64::input::update_rumble().
// Advances the native 60 Hz binary motor duty state using steady-clock time.
void wr64_game_rumble_update(void);

// Safe from either thread. Output is applied by the next host update.
void wr64_game_rumble_reset(void);
void wr64_game_rumble_set_enabled(bool enabled);

#ifdef __cplusplus
}

#include <array>
#include <cstddef>

namespace wr64::rumble {
constexpr std::size_t player_count = 2;

struct BoatSample {
    bool active = false;
    int racer = -1;
    uint16_t pressed = 0;
    int animation = 0;
    int sea_contacts = 0;
    float speed = 0.0f;
    std::array<float, 3> acceleration{};
    std::array<float, 3> collision{};
};
using Samples = std::array<BoatSample, player_count>;

// N64ModernRuntime's RDRAM uses native words with byte/halfword lane swaps.
// This adapter is specific to the verified USA Rev1 layout.
Samples read_usa_samples(const uint8_t* rdram);

// Host-owned gameplay state. Shindou's verified event/intensity contract is
// adapted to USA samples; no original game instructions or assets are embedded.
class MotorState {
public:
    void submit(const BoatSample& sample);
    void tick();
    void reset();
    bool on() const { return on_; }
    unsigned intensity() const { return intensity_; }
    unsigned decay() const { return decay_; }

private:
    int racer_ = -1;
    bool active_ = false;
    bool collision_ = false;
    bool on_ = false;
    unsigned phase_ = 0;
    unsigned intensity_ = 0;
    unsigned decay_ = 1;
};

// Integer timebase avoids render-rate dependence and fractional-frame drift.
// Catch-up is bounded to 100 ms; longer stalls do not replay their full history.
class DutyClock {
public:
    unsigned advance(uint64_t now_ns);
    void reset();
private:
    bool started_ = false;
    uint64_t last_ns_ = 0;
    uint64_t remainder_ = 0;
};
}
#endif
