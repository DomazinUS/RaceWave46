#include "wr64_diagnostic_policy.h"
#include "wr64_io.hpp"
#include "wr64_audio_resampler.h"
#include "wr64_composer_window.hpp"
#include "wr64_audio_volume.hpp"
#ifdef WR64_ENABLE_FRONTEND
#include "recompui/config.h"
#endif

#ifdef WR64_ENABLE_RT64

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>

#include <SDL.h>

namespace {

constexpr uint16_t kButtonA = 0x8000;
constexpr uint16_t kButtonB = 0x4000;
constexpr uint16_t kButtonZ = 0x2000;
constexpr uint16_t kButtonStart = 0x1000;
constexpr uint16_t kDpadUp = 0x0800;
constexpr uint16_t kDpadDown = 0x0400;
constexpr uint16_t kDpadLeft = 0x0200;
constexpr uint16_t kDpadRight = 0x0100;
constexpr uint16_t kButtonL = 0x0020;
constexpr uint16_t kButtonR = 0x0010;
constexpr uint16_t kCUp = 0x0008;
constexpr uint16_t kCDown = 0x0004;
constexpr uint16_t kCLeft = 0x0002;
constexpr uint16_t kCRight = 0x0001;

bool key_down(int key) {
    return (GetAsyncKeyState(key) & 0x8000) != 0;
}

float normalize_stick(SHORT value, SHORT deadzone) {
    const float magnitude = static_cast<float>(value);
    if (std::abs(magnitude) <= deadzone) {
        return 0.0F;
    }
    const float direction = magnitude < 0.0F ? -1.0F : 1.0F;
    const float scaled = (std::abs(magnitude) - deadzone) /
        (32767.0F - static_cast<float>(deadzone));
    return direction * std::clamp(scaled, 0.0F, 1.0F);
}

struct InputState {
    std::mutex mutex;
    std::array<XINPUT_STATE, XUSER_MAX_COUNT> controllers{};
    std::array<bool, XUSER_MAX_COUNT> connected{};
} input_state;

// Audio delivery uses a stateful resampler and a lock-free producer/consumer ring.
// Preserve resampler history across blocks and repeated same-rate requests; drain
// the old rate's tail before changing rates. Drop incoming samples on overflow
// instead of clearing audio already queued for playback.
//
// A 40 ms cushion keeps scheduler jitter from starving the device. Prime that
// cushion with silence and subtract it from the scheduler's remaining-frame count.
// WR64_AUDIO_TRACE records timing and queue metadata; WR64_AUDIO_DUMP records
// native and converted PCM. Both require explicit diagnostic configuration.
static constexpr uint32_t Wr64AudioCushionMs = 40;

// The device callback drains a lock-free SPSC ring; queue_samples resamples and
// fills it. The scheduler reads ring counters without taking SDL's device lock.
// The 1024-frame device buffer gives the callback more scheduling headroom.
// Diagnostics track callback cadence, silence padding, and the largest callback
// gap to distinguish producer starvation from late device requests.
static constexpr uint32_t Wr64AudioRingSeconds = 2;

struct AudioState {
    std::mutex mutex;
    SDL_AudioDeviceID device = 0;
    wr64::audio_resampler::Resampler resampler;
    bool resampler_live = false;
    uint32_t input_frequency = 48000;
    uint32_t output_frequency = 48000;
    std::vector<int16_t> swap_buffer;
    std::vector<uint8_t> pull_buffer;
    uint64_t blocks_queued = 0;
    uint64_t blocks_dropped = 0;
    bool drop_announced = false;

    // The SPSC ring between the producer (queue_samples, mutex held) and the
    // SDL audio callback (no locks ever). Counters are MONOTONIC sample
    // counts; the fill level is write - read. Sized at open.
    std::vector<int16_t> ring;
    std::atomic<uint64_t> ring_write{0};
    std::atomic<uint64_t> ring_read{0};

    // Rates and openness, readable without the mutex.
    std::atomic<uint32_t> atomic_input_hz{48000};
    std::atomic<uint32_t> atomic_output_hz{48000};
    std::atomic<uint32_t> atomic_device_open{0};
    std::atomic<uint64_t> remaining_polls{0};

    // Callback forensics, written by the callback, read at trace time.
    std::atomic<uint64_t> cb_count{0};
    std::atomic<uint64_t> cb_underrun_samples{0};
    std::atomic<uint64_t> cb_last_ms{0};
    std::atomic<uint64_t> cb_max_gap_ms{0};

    ~AudioState() {
        if (device != 0) {
            SDL_CloseAudioDevice(device);
        }
    }
} audio_state;

uint64_t audio_now_ms() {
    static const auto start = std::chrono::steady_clock::now();
    return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - start).count());
}

std::FILE *audio_trace_file() {
    static std::FILE *file = []() -> std::FILE * {
        const char *path = WR64_DIAGNOSTIC_ENV(std::getenv("WR64_AUDIO_TRACE"));
        if ((path == nullptr) || (path[0] == '\0')) {
            return nullptr;
        }
        std::FILE *f = std::fopen(path, "wb");
        if (f != nullptr) {
            std::fprintf(f, "t_ms,event,input_hz,output_hz,samples,ring_before,ring_after,stream_avail,drops,polls,cb_count,cb_underrun_samples,cb_max_gap_ms\n");
            std::fflush(f);
            WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[audio] trace armed -> %s\n", path));
        }
        return f;
    }();
    return file;
}

// Flush each diagnostic row so abnormal process exit does not discard it.
void audio_trace(const char *event, uint32_t samples,
                 uint32_t queued_before, uint32_t queued_after, int stream_avail) {
    std::FILE *f = audio_trace_file();
    if (f == nullptr) {
        return;
    }
    std::fprintf(f, "%llu,%s,%u,%u,%u,%u,%u,%d,%llu,%llu,%llu,%llu,%llu\n",
        static_cast<unsigned long long>(audio_now_ms()), event,
        audio_state.input_frequency, audio_state.output_frequency,
        samples, queued_before, queued_after, stream_avail,
        static_cast<unsigned long long>(audio_state.blocks_dropped),
        static_cast<unsigned long long>(
            audio_state.remaining_polls.load(std::memory_order_relaxed)),
        static_cast<unsigned long long>(
            audio_state.cb_count.load(std::memory_order_relaxed)),
        static_cast<unsigned long long>(
            audio_state.cb_underrun_samples.load(std::memory_order_relaxed)),
        static_cast<unsigned long long>(
            audio_state.cb_max_gap_ms.load(std::memory_order_relaxed)));
    std::fflush(f);
}

std::FILE *audio_dump_file(const char *suffix, std::FILE *&slot, bool &tried) {
    if (!tried) {
        tried = true;
        const char *base = WR64_DIAGNOSTIC_ENV(std::getenv("WR64_AUDIO_DUMP"));
        if ((base != nullptr) && (base[0] != '\0')) {
            char path[1024];
            std::snprintf(path, sizeof(path), "%s%s", base, suffix);
            slot = std::fopen(path, "wb");
            if (slot != nullptr) {
                WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[audio] dump armed -> %s\n", path));
            }
        }
    }
    return slot;
}

std::FILE *audio_dump_in() {
    static std::FILE *slot = nullptr;
    static bool tried = false;
    return audio_dump_file(".in.s16", slot, tried);
}

std::FILE *audio_dump_out() {
    static std::FILE *slot = nullptr;
    static bool tried = false;
    return audio_dump_file(".out.s16", slot, tried);
}

// Runs on SDL's audio thread. NO locks, NO allocation, NO stdio - anything
// blocking here CAUSES the glitch this exists to measure. Serves from the
// ring; pads with silence and counts when the ring runs short; timestamps
// itself so a late ask (a driver-side stall) is a recorded gap.
void SDLCALL audio_device_callback(void *, Uint8 *out, int len) {
#if WR64_DIAGNOSTIC_ENABLED
    const uint64_t now = audio_now_ms();
    const uint64_t prev = audio_state.cb_last_ms.exchange(now, std::memory_order_relaxed);
    if (prev != 0) {
        const uint64_t gap = (now > prev) ? (now - prev) : 0;
        uint64_t seen = audio_state.cb_max_gap_ms.load(std::memory_order_relaxed);
        while ((gap > seen) && !audio_state.cb_max_gap_ms.compare_exchange_weak(
                   seen, gap, std::memory_order_relaxed)) {
        }
    }
    audio_state.cb_count.fetch_add(1, std::memory_order_relaxed);
#endif

    int16_t *dst = reinterpret_cast<int16_t *>(out);
    const size_t want = static_cast<size_t>(len) / sizeof(int16_t);
    const size_t capacity = audio_state.ring.size();
    const uint64_t write = audio_state.ring_write.load(std::memory_order_acquire);
    const uint64_t read = audio_state.ring_read.load(std::memory_order_relaxed);
    const size_t fill = static_cast<size_t>(write - read);
    const size_t serve = (fill < want) ? fill : want;

    for (size_t i = 0; i < serve; i++) {
        dst[i] = audio_state.ring[static_cast<size_t>((read + i) % capacity)];
    }
    if (serve < want) {
        std::memset(dst + serve, 0, (want - serve) * sizeof(int16_t));
        WR64_DIAGNOSTIC_LOG(audio_state.cb_underrun_samples.fetch_add(want - serve, std::memory_order_relaxed));
    }
#ifdef WR64_ENABLE_FRONTEND
    // Gain belongs at final delivery, so it also affects already queued audio
    // immediately and cannot be applied twice through resampler rate changes.
    wr64::audio::apply_main_volume(dst, want, recompui::config::sound::get_main_volume());
#endif
    audio_state.ring_read.store(read + serve, std::memory_order_release);
}

bool open_audio_device() {
    if (audio_state.device != 0) {
        return true;
    }
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
        std::fprintf(stderr, "[audio] SDL initialization failed: %s\n", SDL_GetError());
        return false;
    }

    SDL_AudioSpec desired{};
    desired.freq = static_cast<int>(audio_state.output_frequency);
    desired.format = AUDIO_S16SYS;
    desired.channels = 2;
    // 1024 frames: a 21.3 ms callback deadline. Kept from R3.
    desired.samples = 0x400;
    desired.callback = audio_device_callback;

    SDL_AudioSpec obtained{};
    audio_state.device = SDL_OpenAudioDevice(
        nullptr, 0, &desired, &obtained, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
    if (audio_state.device == 0) {
        std::fprintf(stderr, "[audio] unable to open device: %s\n", SDL_GetError());
        return false;
    }
    audio_state.output_frequency = static_cast<uint32_t>(obtained.freq);
    // The ring outlives every rate change (it is in OUTPUT samples) and is
    // sized once. PAUSED until the first prime, so the callback's underrun
    // counter never charges the silence before audio exists.
    audio_state.ring.assign(
        static_cast<size_t>(audio_state.output_frequency) * 2 * Wr64AudioRingSeconds, 0);
    WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[audio] output device: %d Hz, %u channels, ring callback\n",
        obtained.freq, static_cast<unsigned>(obtained.channels)));
    return true;
}

// Producer-side ring write. Called with the mutex held. Returns false when
// the ring lacks space (the caller drops the block - same latency-bound
// semantics as before, never touching what is already scheduled).
bool ring_write_samples(const int16_t *samples, size_t count) {
    const size_t capacity = audio_state.ring.size();
    const uint64_t write = audio_state.ring_write.load(std::memory_order_relaxed);
    const uint64_t read = audio_state.ring_read.load(std::memory_order_acquire);
    const size_t fill = static_cast<size_t>(write - read);
    if (fill + count > capacity) {
        return false;
    }
    for (size_t i = 0; i < count; i++) {
        audio_state.ring[static_cast<size_t>((write + i) % capacity)] = samples[i];
    }
    audio_state.ring_write.store(write + count, std::memory_order_release);
    return true;
}

uint32_t ring_fill_bytes() {
    const uint64_t write = audio_state.ring_write.load(std::memory_order_relaxed);
    const uint64_t read = audio_state.ring_read.load(std::memory_order_relaxed);
    return static_cast<uint32_t>((write - read) * sizeof(int16_t));
}

// Move everything the resampler has finished converting into the ring.
// Called with the mutex held.
void drain_audio_stream() {
    std::vector<int16_t> &ready = audio_state.resampler.ready();
    if (ready.empty()) {
        return;
    }
    if (std::FILE *out = audio_dump_out()) {
        std::fwrite(ready.data(), sizeof(int16_t), ready.size(), out);
        std::fflush(out);
    }
    ring_write_samples(ready.data(), ready.size());
    ready.clear();
}

// The resampler's converted-but-unmoved backlog, for the trace column that
// used to report the SDL stream's. Zero in steady state - drained every put.
int resampler_ready_bytes() {
    return static_cast<int>(audio_state.resampler.ready().size() * sizeof(int16_t));
}

// Publish the rates and openness for the lock-free readers. Called with the
// mutex held after anything that changed them. The ring counters themselves
// need no mirror - they ARE atomics.
void refresh_remaining_mirror() {
    audio_state.atomic_input_hz.store(audio_state.input_frequency, std::memory_order_relaxed);
    audio_state.atomic_output_hz.store(audio_state.output_frequency, std::memory_order_relaxed);
    audio_state.atomic_device_open.store((audio_state.device != 0) ? 1u : 0u, std::memory_order_relaxed);
}

// Configure the sinc resampler for the current rate pair. Called with the
// mutex held, after the device is open. A rate CHANGE flushes the old
// kernel window's tail first so the old rate's last milliseconds play
// rather than vanish - a dropped tail is a pop at every music transition.
void rebuild_audio_stream() {
    if (audio_state.resampler_live) {
        audio_state.resampler.flush();
        drain_audio_stream();
    }
    audio_state.resampler.configure(
        audio_state.input_frequency, audio_state.output_frequency);
    audio_state.resampler_live = true;
    WR64_DIAGNOSTIC_LOG(std::fprintf(stderr,
        "[audio] sinc resampler: %u -> %u Hz (32 taps, 1024 phases, ear-validated design)\n",
        audio_state.input_frequency, audio_state.output_frequency));

    // Prime the ring with silence UP TO the cushion, so the headroom exists
    // from the first audible block. A TOP-UP, not a blind add: on a mid-play
    // rate change the ring already holds close to the cushion and this adds
    // little or nothing, so rate changes do not stack latency. The device
    // unpauses only after the first prime - the callback never counts the
    // silence before audio existed.
    const uint32_t cushion_bytes = audio_state.output_frequency * 2 *
        static_cast<uint32_t>(sizeof(int16_t)) * Wr64AudioCushionMs / 1000;
    const uint32_t already_queued = ring_fill_bytes();
    if (already_queued < cushion_bytes) {
        const size_t zeros = static_cast<size_t>(cushion_bytes - already_queued) / sizeof(int16_t);
        audio_state.pull_buffer.assign(zeros * sizeof(int16_t), 0);
        ring_write_samples(reinterpret_cast<const int16_t *>(audio_state.pull_buffer.data()), zeros);
        audio_trace("prime-cushion", 0, already_queued, ring_fill_bytes(),
            resampler_ready_bytes());
    }
    refresh_remaining_mirror();
    SDL_PauseAudioDevice(audio_state.device, 0);
}

} // namespace

namespace wr64::audio {

void queue_samples(int16_t* samples, size_t sample_count) {
    std::lock_guard lock{audio_state.mutex};
    if (audio_state.device == 0 || !audio_state.resampler_live || sample_count == 0) {
        return;
    }

    const size_t input_bytes = sample_count * sizeof(int16_t);
    audio_state.swap_buffer.resize(sample_count);

    // N64 recomp memory layout presents stereo pairs in host-swapped order.
    for (size_t i = 0; i + 1 < sample_count; i += 2) {
        audio_state.swap_buffer[i] = samples[i + 1];
        audio_state.swap_buffer[i + 1] = samples[i];
    }

    const uint32_t queued_before = ring_fill_bytes();

    // Bound latency if execution runs ahead of the audio device - by dropping
    // the INCOMING block, never by touching what is already scheduled. 400 ms
    // of headroom, a counter, and one announcement; the trace records every
    // drop. If drops ever fire in normal play the defect is the game-side
    // pacing, and THAT is what gets fixed next - not this bound.
    const uint32_t maximum_queue = audio_state.output_frequency * 2 * sizeof(int16_t) * 2 / 5;
    if (queued_before > maximum_queue) {
        audio_state.blocks_dropped++;
        if (!audio_state.drop_announced) {
            audio_state.drop_announced = true;
            WR64_DIAGNOSTIC_LOG(std::fprintf(stderr,
                "[audio] latency bound: dropping an incoming block rather than "
                "clearing the playing queue\n"));
        }
        audio_trace("drop", static_cast<uint32_t>(sample_count), queued_before, queued_before,
            resampler_ready_bytes());
        return;
    }

    if (std::FILE *in = audio_dump_in()) {
        std::fwrite(audio_state.swap_buffer.data(), 1, input_bytes, in);
        std::fflush(in);
    }

    audio_state.resampler.put(audio_state.swap_buffer.data(), sample_count);
    drain_audio_stream();
    audio_state.blocks_queued++;
    refresh_remaining_mirror();

    if (audio_trace_file() != nullptr) {
        audio_trace("queue", static_cast<uint32_t>(sample_count), queued_before,
            ring_fill_bytes(),
            resampler_ready_bytes());
    }
}

size_t get_frames_remaining() {
    // LOCK-FREE ON PURPOSE - no mutex, no SDL call. The game's scheduler
    // polls this. With R4's ring the report is EXACT: the ring counters are
    // the source of truth and they are atomics; R3's wall-clock drain
    // estimate is gone.
    WR64_DIAGNOSTIC_LOG(audio_state.remaining_polls.fetch_add(1, std::memory_order_relaxed));
    if (audio_state.atomic_device_open.load(std::memory_order_relaxed) == 0) {
        return 0;
    }
    const uint32_t input_hz = audio_state.atomic_input_hz.load(std::memory_order_relaxed);
    const uint32_t output_hz = audio_state.atomic_output_hz.load(std::memory_order_relaxed);
    if ((input_hz == 0) || (output_hz == 0)) {
        return 0;
    }
    const uint64_t output_frames = ring_fill_bytes() / (2 * sizeof(int16_t));
    const uint64_t input_frames = output_frames * input_hz / output_hz;

    // UNDER-REPORT by the cushion - the derivation is with Wr64AudioCushionMs.
    const uint64_t cushion_frames =
        static_cast<uint64_t>(input_hz) * Wr64AudioCushionMs / 1000;
    if (input_frames <= cushion_frames) {
        return 0;
    }
    return static_cast<size_t>(input_frames - cushion_frames);
}

void set_frequency(uint32_t frequency) {
    std::lock_guard lock{audio_state.mutex};
    WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[audio] game frequency: %u Hz\n", frequency));
    if (!open_audio_device()) {
        audio_state.input_frequency = frequency;
        return;
    }
    // Same rate re-set: KEEP the stream and its resampler state. The game
    // re-announces its frequency without changing it; rebuilding here would
    // discard filter history and put a seam in the middle of clean audio.
    if (audio_state.resampler_live && (audio_state.input_frequency == frequency)) {
        refresh_remaining_mirror();
        audio_trace("setfreq-same", 0, ring_fill_bytes(), ring_fill_bytes(),
            resampler_ready_bytes());
        return;
    }
    audio_state.input_frequency = frequency;
    rebuild_audio_stream();
    refresh_remaining_mirror();
    audio_trace("setfreq", 0, ring_fill_bytes(), ring_fill_bytes(),
        resampler_ready_bytes());
}

} // namespace wr64::audio

// recompinput replaces this entire layer when the frontend is built, and the
// two cannot coexist: both define wr64::input and the linker would reject the
// duplicate symbols. src/wr64_input.cpp is the other implementation.
//
// This one is XInput-only, which is why the 8BitDo N64 Modkit over Bluetooth
// was invisible to it no matter how many controllers were connected.
#ifndef WR64_ENABLE_FRONTEND

namespace wr64::input {

void poll() {
    std::lock_guard lock{input_state.mutex};
    for (DWORD index = 0; index < XUSER_MAX_COUNT; index++) {
        ZeroMemory(&input_state.controllers[index], sizeof(XINPUT_STATE));
        input_state.connected[index] =
            XInputGetState(index, &input_state.controllers[index]) == ERROR_SUCCESS;
    }
}

bool get(int controller, uint16_t* buttons, float* x, float* y) {
    if (controller < 0 || controller >= XUSER_MAX_COUNT) {
        return false;
    }

    std::lock_guard lock{input_state.mutex};
    uint16_t result = 0;
    float stick_x = 0.0F;
    float stick_y = 0.0F;

    if ((controller == 0) && !wr64::composer::keyboard_captured()) {
        result |= key_down('Z') ? kButtonA : 0;
        result |= key_down('X') ? kButtonB : 0;
        result |= key_down('C') ? kButtonZ : 0;
        result |= key_down(VK_RETURN) ? kButtonStart : 0;
        result |= key_down('Q') ? kButtonL : 0;
        result |= key_down('E') ? kButtonR : 0;
        result |= key_down('W') ? kDpadUp : 0;
        result |= key_down('S') ? kDpadDown : 0;
        result |= key_down('A') ? kDpadLeft : 0;
        result |= key_down('D') ? kDpadRight : 0;
        result |= key_down('I') ? kCUp : 0;
        result |= key_down('K') ? kCDown : 0;
        result |= key_down('J') ? kCLeft : 0;
        result |= key_down('L') ? kCRight : 0;
        stick_x = (key_down(VK_RIGHT) ? 1.0F : 0.0F) -
            (key_down(VK_LEFT) ? 1.0F : 0.0F);
        stick_y = (key_down(VK_UP) ? 1.0F : 0.0F) -
            (key_down(VK_DOWN) ? 1.0F : 0.0F);
    }

    if (input_state.connected[controller]) {
        const auto& pad = input_state.controllers[controller].Gamepad;
        result |= (pad.wButtons & XINPUT_GAMEPAD_A) ? kButtonA : 0;
        result |= (pad.wButtons & XINPUT_GAMEPAD_X) ? kButtonB : 0;
        result |= (pad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) ? kButtonZ : 0;
        result |= (pad.wButtons & XINPUT_GAMEPAD_START) ? kButtonStart : 0;
        result |= (pad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) ? kButtonL : 0;
        result |= (pad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) ? kButtonR : 0;
        result |= (pad.wButtons & XINPUT_GAMEPAD_DPAD_UP) ? kDpadUp : 0;
        result |= (pad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) ? kDpadDown : 0;
        result |= (pad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) ? kDpadLeft : 0;
        result |= (pad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) ? kDpadRight : 0;
        result |= (pad.wButtons & XINPUT_GAMEPAD_Y) ? kCUp : 0;
        result |= (pad.wButtons & XINPUT_GAMEPAD_B) ? kCRight : 0;

        const float controller_x = normalize_stick(
            pad.sThumbLX, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
        const float controller_y = normalize_stick(
            pad.sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
        if (std::abs(controller_x) > std::abs(stick_x)) {
            stick_x = controller_x;
        }
        if (std::abs(controller_y) > std::abs(stick_y)) {
            stick_y = controller_y;
        }

        const float c_x = normalize_stick(pad.sThumbRX, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
        const float c_y = normalize_stick(pad.sThumbRY, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
        result |= c_x < -0.5F ? kCLeft : 0;
        result |= c_x > 0.5F ? kCRight : 0;
        result |= c_y < -0.5F ? kCDown : 0;
        result |= c_y > 0.5F ? kCUp : 0;
    }

    *buttons = result;
    *x = std::clamp(stick_x, -1.0F, 1.0F);
    *y = std::clamp(stick_y, -1.0F, 1.0F);
    return controller == 0 || input_state.connected[controller];
}

void set_rumble(int controller, bool enabled) {
    if (controller < 0 || controller >= XUSER_MAX_COUNT) {
        return;
    }
    XINPUT_VIBRATION vibration{};
    if (enabled) {
        vibration.wLeftMotorSpeed = 0xA000;
        vibration.wRightMotorSpeed = 0x6000;
    }
    XInputSetState(static_cast<DWORD>(controller), &vibration);
}

ultramodern::input::connected_device_info_t get_connected_device_info(
    int controller) {
    if (controller == 0) {
        return {ultramodern::input::Device::Controller,
                ultramodern::input::Pak::RumblePak};
    }
    std::lock_guard lock{input_state.mutex};
    if (controller > 0 && controller < XUSER_MAX_COUNT &&
        input_state.connected[controller]) {
        return {ultramodern::input::Device::Controller,
                ultramodern::input::Pak::RumblePak};
    }
    return {ultramodern::input::Device::None, ultramodern::input::Pak::None};
}

} // namespace wr64::input

#endif // !WR64_ENABLE_FRONTEND

#endif
