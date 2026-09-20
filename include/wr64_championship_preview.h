#pragma once
#include "recomp.h"

#ifdef __cplusplus
extern "C" {
#endif
void wr64_championship_preview_prepare(uint8_t* rdram, uint32_t cursor);
uint32_t wr64_championship_preview_finish(uint8_t* rdram, uint32_t cursor);
#ifdef __cplusplus
}
#endif
