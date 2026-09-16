#include "wr64_diagnostic_policy.h"
#include "wr64_io.hpp"

#ifndef WR64_ENABLE_RT64

#include <cinttypes>
#include <cstdio>

namespace wr64::audio {

void queue_samples(int16_t*, size_t) {}
size_t get_frames_remaining() { return 0; }
void set_frequency(uint32_t frequency) {
    WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[audio] frequency: %" PRIu32 " Hz\n", frequency));
}

} // namespace wr64::audio

namespace wr64::input {

void poll() {}

bool get(int controller, uint16_t* buttons, float* x, float* y) {
    if (controller != 0) {
        return false;
    }
    *buttons = 0;
    *x = 0.0F;
    *y = 0.0F;
    return true;
}

void set_rumble(int, bool) {}

ultramodern::input::connected_device_info_t get_connected_device_info(
    int controller) {
    if (controller == 0) {
        return {ultramodern::input::Device::Controller, ultramodern::input::Pak::None};
    }
    return {ultramodern::input::Device::None, ultramodern::input::Pak::None};
}

} // namespace wr64::input

#endif
