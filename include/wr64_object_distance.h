#pragma once
#include <stdint.h>
#include "recomp.h"

#ifdef __cplusplus
extern "C" {
#endif
// Temporarily admit verified static ramps only during their native body draw.
void wr64_object_distance_begin(uint8_t* rdram, recomp_context* ctx);
void wr64_object_distance_end(uint8_t* rdram, recomp_context* ctx);
#ifdef __cplusplus
}
#endif
