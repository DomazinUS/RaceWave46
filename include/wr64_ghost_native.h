#pragma once
#include "recomp.h"
#ifdef __cplusplus
extern "C" {
#endif
void wr64_ghost_after_init_hover(uint8_t* rdram, recomp_context* ctx);
void wr64_ghost_after_hover_glist(uint8_t* rdram, recomp_context* ctx);
void wr64_ghost_draw_dolphin(uint8_t* rdram, recomp_context* ctx);
void wr64_ghost_begin_dolphin_draw(uint8_t* rdram, recomp_context* ctx, int actor_index);
void wr64_ghost_end_dolphin_draw(uint8_t* rdram, recomp_context* ctx);
// Thread-safe readiness published only after native execution has begun, which
// follows runtime init_saving. Does not read the cross-thread save-path object.
int wr64_ghost_native_storage_ready(void);
// Safe after the runtime has destroyed its guest arena; touches host state only.
void wr64_ghost_native_forget(void);
// Call after native execution and renderer activity have stopped, while RDRAM
// and the recomp heap are still valid. Frees only this module's allocation.
void wr64_ghost_native_reset(void);
#ifdef __cplusplus
}
#endif
