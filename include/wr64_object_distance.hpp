#pragma once
#include "wr64_object_distance.h"

namespace wr64::object_distance {
// 0: Original; 1: 1.5x; 2: 2x; 3: 3x. Invalid persisted values use Original.
void set_mode(uint32_t mode);
uint32_t mode();
}
