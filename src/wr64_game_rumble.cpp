#include "wr64_diagnostic_policy.h"
#include "wr64_game_rumble.hpp"

#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mutex>

#include "wr64_input.hpp"

namespace wr64::rumble {
namespace {
template<class T>
T read_word(const uint8_t* rdram, uint32_t address) {
    static_assert(sizeof(T) == 4);
    static_assert(std::endian::native == std::endian::little);
    T result;
    std::memcpy(&result, rdram + (address & 0x7FFFFF), sizeof(result));
    return result;
}

int16_t read_half(const uint8_t* rdram, uint32_t address) {
    int16_t result;
    std::memcpy(&result, rdram + ((address & 0x7FFFFF) ^ 2), sizeof(result));
    return result;
}

bool finite(const BoatSample& sample) {
    if (!std::isfinite(sample.speed)) return false;
    for (const float value : sample.acceleration) if (!std::isfinite(value)) return false;
    for (const float value : sample.collision) if (!std::isfinite(value)) return false;
    return true;
}
}

Samples read_usa_samples(const uint8_t* rdram) {
    Samples result{};
    if (rdram == nullptr) return result;

    // USA move_hover's manual-controller selection, plus the game's pause gate.
    const int mode = read_word<int32_t>(rdram, 0x801CE648);
    if (read_word<int32_t>(rdram, 0x801CE638) != 1 || mode == 0 || mode == 2 ||
        read_half(rdram, 0x801CE624) != -1 || read_half(rdram, 0x800D4964) != 0) {
        return result;
    }
    const int players = read_word<int32_t>(rdram, 0x800DAB28);
    if (players != 1 && players != 2) return result;
    const int pads = std::clamp(read_word<int32_t>(rdram, 0x80154344), 0, 4);
    const int boats = std::clamp(read_word<int32_t>(rdram, 0x801982F0), 0, 4);
    for (int logical = 0; logical < players && logical < pads; ++logical) {
        const int port = read_word<int32_t>(rdram, 0x80154330 + logical * 4);
        const int racer = read_word<int32_t>(rdram, 0x800D48DC + logical * 4);
        if (port < 0 || port >= int(player_count) || racer < 0 || racer >= boats || result[port].active) continue;
        const uint32_t boat = 0x80192690 + uint32_t(racer) * 0x1718;
        // The native manual-controller routine falls back to AI for this state.
        if (read_half(rdram, boat + 0x1446) < 0) continue;
        auto& sample = result[port];
        sample.active = true;
        sample.racer = racer;
        sample.pressed = uint16_t(read_half(rdram, boat + 0xB58));
        sample.animation = read_word<int32_t>(rdram, boat + 0xC54);
        sample.sea_contacts = read_word<int32_t>(rdram, boat + 0xC78);
        sample.speed = read_word<float>(rdram, boat + 0xB90);
        for (unsigned axis = 0; axis < 3; ++axis) {
            sample.acceleration[axis] = read_word<float>(rdram, boat + 0xB84 + axis * 4);
            sample.collision[axis] = read_word<float>(rdram, boat + 0x15B4 + axis * 4);
        }
    }
    return result;
}

void MotorState::reset() {
    *this = MotorState{};
}

void MotorState::submit(const BoatSample& sample) {
    if (!sample.active || !finite(sample)) {
        reset();
        return;
    }
    if (racer_ != sample.racer) reset();
    racer_ = sample.racer;
    active_ = true;

    // Verified Shindou cal_vibration (80065CC0): impact has priority, then an
    // A/Z press at low speed, then contact acceleration. Its third acceleration
    // coefficient is zero. Keep that behavior rather than inventing a Z effect.
    const bool hit = std::any_of(sample.collision.begin(), sample.collision.end(),
        [](float value) { return value != 0.0f; });
    unsigned strength = 0;
    unsigned duration_divisor = 1;
    if (hit) {
        if (!collision_) {
            strength = 255;
            duration_divisor = 30;
        }
    }
    else if ((sample.pressed & 0xA000) != 0 && sample.speed <= 5.0f && sample.animation != 7) {
        strength = 200;
        duration_divisor = 40;
    }
    else if (sample.sea_contacts != 0) {
        const float sideways = sample.acceleration[0] * 25.0f;
        const float vertical = sample.acceleration[1] * 2.75f;
        const float vertical_squared = vertical * vertical;
        const float amount = std::abs(sideways) + vertical_squared;
        strength = amount >= 255.0f ? 255 : static_cast<unsigned>(amount);
        duration_divisor = 20;
    }
    collision_ = hit;

    // The native message consumer accepts only a stronger request; a weaker
    // event cannot truncate an impact already decaying in the motor channel.
    if (strength > intensity_) {
        intensity_ = strength;
        decay_ = strength / duration_divisor + 1;
    }
}

void MotorState::tick() {
    if (!active_) return;
    phase_ += intensity_;
    intensity_ = intensity_ > decay_ ? intensity_ - decay_ : 0;
    on_ = phase_ >= 256;
    if (on_) phase_ -= 256;
}

unsigned DutyClock::advance(uint64_t now_ns) {
    if (!started_ || now_ns < last_ns_) {
        started_ = true;
        last_ns_ = now_ns;
        remainder_ = 0;
        return 0;
    }
    const uint64_t elapsed = std::min<uint64_t>(now_ns - last_ns_, 100'000'000);
    last_ns_ = now_ns;
    const uint64_t scaled = elapsed * 60 + remainder_;
    remainder_ = scaled % 1'000'000'000;
    return static_cast<unsigned>(scaled / 1'000'000'000);
}

void DutyClock::reset() {
    *this = DutyClock{};
}
}

namespace {
uint64_t clock_ns() {
    using namespace std::chrono;
    return uint64_t(duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count());
}

std::mutex state_mutex;
std::array<wr64::rumble::MotorState, wr64::rumble::player_count> motors;
wr64::rumble::DutyClock duty_clock;
uint64_t last_sample_ns = 0;
bool enabled = true;
wr64::rumble::Samples last_samples{};
uint64_t sample_count = 0;
uint64_t duty_tick_count = 0;
uint64_t active_sample_count = 0;
uint64_t on_tick_count = 0;
unsigned peak_intensity = 0;

bool tracing() {
    static const bool value = [] {
        const char* env = WR64_DIAGNOSTIC_ENV(std::getenv("WR64_GAME_RUMBLE_TRACE"));
        return env != nullptr && std::strcmp(env, "1") == 0;
    }();
    return value;
}

void clear_locked() {
    for (auto& motor : motors) motor.reset();
    duty_clock.reset();
    last_sample_ns = 0;
    last_samples = {};
}
}

extern "C" void wr64_game_rumble_sample(uint8_t* rdram) {
    // RDRAM is sampled only on its game thread. The host receives value copies.
    const auto samples = wr64::rumble::read_usa_samples(rdram);
    const std::lock_guard lock(state_mutex);
    ++sample_count;
    if (!enabled) return;
    last_samples = samples;
    for (std::size_t port = 0; port < motors.size(); ++port) {
        motors[port].submit(samples[port]);
        active_sample_count += samples[port].active;
        peak_intensity = std::max(peak_intensity, motors[port].intensity());
    }
    last_sample_ns = clock_ns();
}

extern "C" void wr64_game_rumble_reset() {
    const std::lock_guard lock(state_mutex);
    clear_locked();
}

extern "C" void wr64_game_rumble_set_enabled(bool value) {
    const std::lock_guard lock(state_mutex);
    enabled = value;
    if (!enabled) clear_locked();
}

extern "C" void wr64_game_rumble_update() {
    const uint64_t now = clock_ns();
    std::array<bool, wr64::rumble::player_count> output{};
    {
        const std::lock_guard lock(state_mutex);
        // A missing game tick must not leave an old motor-on state latched
        // through a loader, stopped task or modal interface.
        if (!enabled || !wr64::input::ready() || last_sample_ns == 0 ||
            now < last_sample_ns || now - last_sample_ns > 150'000'000) {
            clear_locked();
        }
        else {
            const unsigned ticks = duty_clock.advance(now);
            duty_tick_count += ticks;
            for (unsigned tick = 0; tick < ticks; ++tick) {
                for (auto& motor : motors) {
                    motor.tick();
                    on_tick_count += motor.on();
                }
            }
            for (std::size_t port = 0; port < motors.size(); ++port) output[port] = motors[port].on();
        }
        if (tracing()) {
            static uint64_t next_trace_ns = 0;
            if (now >= next_trace_ns) {
                next_trace_ns = now + 1'000'000'000;
                WR64_DIAGNOSTIC_LOG(std::fprintf(stderr,
                    "[game-rumble] enabled=%d samples=%llu active=%llu duty_ticks=%llu on_ticks=%llu peak=%u "
                    "p1=%d/%d/%u/%d p2=%d/%d/%u/%d\n", int(enabled),
                    static_cast<unsigned long long>(sample_count),
                    static_cast<unsigned long long>(active_sample_count),
                    static_cast<unsigned long long>(duty_tick_count),
                    static_cast<unsigned long long>(on_tick_count), peak_intensity,
                    int(last_samples[0].active), last_samples[0].racer, motors[0].intensity(), int(output[0]),
                    int(last_samples[1].active), last_samples[1].racer, motors[1].intensity(), int(output[1])));
                peak_intensity = 0;
            }
        }
    }
    // Reuse the Shindou host output path. Device assignment, strength settings,
    // SDL support and the physical attack/decay envelope stay in RecompFrontend.
    // Both this call and update_rumble() run on the same host thread.
    for (std::size_t port = 0; port < output.size(); ++port) {
        wr64::input::set_rumble(int(port), output[port]);
    }
}
