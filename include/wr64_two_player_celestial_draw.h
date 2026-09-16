#pragma once
#include "recomp.h"
#ifdef __cplusplus
extern "C" {
#endif
uint32_t wr64_two_player_celestial_draw(uint8_t*, recomp_context*, uint32_t);
uint32_t wr64_two_player_sun_overlay(uint8_t*, recomp_context*, uint32_t);
uint32_t wr64_two_player_sun_skip_shared_wash(uint8_t*);
#ifdef __cplusplus
}
#endif
