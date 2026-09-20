#pragma once
#include <stdint.h>
#include "recomp.h"

#ifdef __cplusplus
extern "C" {
#endif
// Run the native animal renderer once, then reuse its world-space geometry
// in the second viewport without advancing animation or rewriting matrices.
uint32_t wr64_sunny_animals_replay(uint8_t* rdram, recomp_context* ctx);
void wr64_sunny_animals_capture_begin(uint8_t* rdram, recomp_context* ctx);
void wr64_sunny_animals_capture_end(uint8_t* rdram, recomp_context* ctx);
#ifdef __cplusplus
}
#endif
