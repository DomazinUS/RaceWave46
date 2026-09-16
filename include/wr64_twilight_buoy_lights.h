#pragma once
#include <stdint.h>
#include "recomp.h"

#ifdef __cplusplus
extern "C" {
#endif
// Restore Twilight's native checkpoint light bases and translucent columns
// at DrawBuoy's local player-count branch, for each Enhanced two-player view.
void wr64_twilight_buoy_lights(uint8_t* rdram, recomp_context* ctx);
// Reuse the preceding base pass's identical matrices for its light columns.
void wr64_twilight_buoy_lights_reuse(uint8_t* rdram);
#ifdef __cplusplus
}
#endif
