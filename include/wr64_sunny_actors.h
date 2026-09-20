#pragma once
#include <stdint.h>
#include "recomp.h"

#ifdef __cplusplus
extern "C" {
#endif
// Returns nonzero when an Enhanced two-player course's shadow pass replaced
// the native early return. Drake Lake retains its native shadow exclusion.
// In that case v0 contains the appended display-list pointer.
uint32_t wr64_sunny_actor_shadows(uint8_t* rdram, recomp_context* ctx);
#ifdef __cplusplus
}
#endif
