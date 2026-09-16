#pragma once
#include "recomp.h"

#ifdef __cplusplus
extern "C" {
#endif
void wr64_watercraft_preview_prepare(uint8_t* rdram, uint32_t cursor);
void wr64_change_name_preview_prepare(uint8_t* rdram, uint32_t cursor);
void wr64_two_player_preview_viewport(uint8_t* rdram, recomp_context* ctx, uint32_t player);
void wr64_two_player_preview_scissor(uint8_t* rdram, recomp_context* ctx, uint32_t player);
void wr64_two_player_preview_coverage(uint8_t* rdram, recomp_context* ctx, uint32_t player);
void wr64_watercraft_preview_viewport(uint8_t* rdram, recomp_context* ctx);
uint32_t wr64_watercraft_preview_scissor(uint32_t original);
void wr64_watercraft_preview_name(uint8_t* rdram, recomp_context* ctx);
void wr64_change_name_preview_name(uint8_t* rdram, recomp_context* ctx);
uint32_t wr64_watercraft_preview_coverage(uint8_t* rdram, uint32_t cursor);
void wr64_watercraft_preview_finish(uint8_t* rdram, uint32_t cursor);
#ifdef __cplusplus
}
#endif
