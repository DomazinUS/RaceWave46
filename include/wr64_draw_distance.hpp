#pragma once
#include "wr64_draw_distance.h"

namespace wr64::draw_distance {
// 0: Original; 1: 1.5x; 2: 2x. Invalid persisted values use Original.
void set_mode(uint32_t mode);
uint32_t mode();
}
