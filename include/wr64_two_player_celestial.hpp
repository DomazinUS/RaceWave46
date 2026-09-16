#pragma once
#include <stdint.h>
#include "recomp.h"
extern "C" uint32_t wr64_two_player_celestial_begin(uint8_t*, recomp_context*);
extern "C" void wr64_two_player_celestial_end(uint8_t*);
extern "C" uint32_t wr64_two_player_celestial_view(void);
extern "C" uint32_t wr64_two_player_celestial_camera_address(uint8_t*, uint32_t);
