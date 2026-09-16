#pragma once
#include <cstdint>

namespace wr64::split_screen {
// Horizontal is the persisted default. This is sampled when a native display
// list is built, so queued/interpolated frames retain their own layout.
void set_mode(uint32_t mode);
uint32_t mode();
bool separate_windows();
void set_vertical(bool enabled);
bool vertical();
}

extern "C" uint32_t wr64_split_screen_frame(uint8_t* rdram, uint32_t cursor);
extern "C" uint32_t wr64_split_screen_pause(uint8_t* rdram, uint32_t cursor, int begin);
// owner1/2 begins that player's complete large lap announcement; zero ends it.
extern "C" uint32_t wr64_split_screen_lap(uint8_t* rdram, uint32_t cursor, int owner);
