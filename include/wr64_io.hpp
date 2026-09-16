#pragma once

#include <cstddef>
#include <cstdint>

#include "ultramodern/input.hpp"

namespace wr64::audio {

void queue_samples(int16_t* samples, size_t sample_count);
size_t get_frames_remaining();
void set_frequency(uint32_t frequency);

} // namespace wr64::audio

namespace wr64::input {

void poll();
bool get(int controller, uint16_t* buttons, float* x, float* y);
void set_rumble(int controller, bool enabled);
ultramodern::input::connected_device_info_t get_connected_device_info(
    int controller);

} // namespace wr64::input
