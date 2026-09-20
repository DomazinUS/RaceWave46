#pragma once
#include <stdint.h>
#include "recomp.h"

#ifdef __cplusplus
extern "C" {
#endif
// Enable the existing L/R label and pontoon pass for an Enhanced two-player
// course at DrawBuoy's local gate. The native material is shared by all courses.
// Changes only its temporary player-count register; native globals stay intact.
void wr64_sunny_buoy_details(uint8_t* rdram, recomp_context* ctx);
#ifdef __cplusplus
}
#endif
