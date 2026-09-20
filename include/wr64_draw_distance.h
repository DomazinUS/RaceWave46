#pragma once
#include <stdint.h>
#include "recomp.h"

#ifdef __cplusplus
extern "C" {
#endif
// Scope the distance change to DrawBuoy's local visibility calculation.
void wr64_draw_distance_begin(uint8_t* rdram, recomp_context* ctx);
void wr64_draw_distance_finish(uint8_t* rdram, recomp_context* ctx);
void wr64_draw_distance_capacity(uint8_t* rdram, recomp_context* ctx);
// Restore native visibility before Twilight lights and later overlays consume it.
void wr64_draw_distance_end(uint8_t* rdram, recomp_context* ctx);
// The boundary buoys have their own roster, visibility table and matrix bank.
void wr64_area_draw_distance_begin(uint8_t* rdram, recomp_context* ctx);
void wr64_area_draw_distance_finish(uint8_t* rdram, recomp_context* ctx);
void wr64_area_draw_distance_capacity(uint8_t* rdram, recomp_context* ctx);
void wr64_area_draw_distance_end(uint8_t* rdram, recomp_context* ctx);
#ifdef __cplusplus
}
#endif
