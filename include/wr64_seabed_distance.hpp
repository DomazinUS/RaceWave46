#pragma once
#include "wr64_seabed_distance.h"

namespace wr64::seabed_distance {
// 0: Original; 1: 1.5x; 2: 2x; 3: 3x; 4: 4x; 5: 5x.
// Invalid persisted values use Original.
void set_mode(uint32_t mode);
uint32_t mode();
}
