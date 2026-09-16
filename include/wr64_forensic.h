#pragma once

#include "wr64_diagnostic_policy.h"

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum Wr64ForensicEventType {
    WR64_FORENSIC_BOOT = 1,
    WR64_FORENSIC_CONTROL = 2,
    WR64_FORENSIC_VI = 10,
    WR64_FORENSIC_GFX_TASK = 20,
    WR64_FORENSIC_RSP_COMMAND = 21,
    WR64_FORENSIC_RDP_COMMAND = 22,
    WR64_FORENSIC_DRAW_CALL = 23,
    WR64_FORENSIC_SKY_PRODUCER_BEGIN = 30,
    WR64_FORENSIC_SKY_PRODUCER_END = 31,
    WR64_FORENSIC_SKY_MEMORY = 32,
    WR64_FORENSIC_RT64_SKY = 40,
    WR64_FORENSIC_EXACT_SKY_CUT = 41,
    WR64_FORENSIC_WORKLOAD = 50,
    WR64_FORENSIC_PRESENT = 60,
    WR64_FORENSIC_NOTE = 100
};

void wr64_forensic_initialize(void);
void wr64_forensic_shutdown(void);
int wr64_forensic_enabled(void);
int wr64_forensic_is_paused(void);
int wr64_forensic_is_frozen(void);
int wr64_forensic_export_in_progress(void);

void wr64_forensic_set_rdram(uint8_t *rdram, size_t size);
void wr64_forensic_set_native_frame(uint64_t native_frame);
void wr64_forensic_set_task(uint64_t task_sequence);
void wr64_forensic_set_submission(uint64_t submission_frame);
void wr64_forensic_set_workload(uint64_t workload_id);
void wr64_forensic_set_present(uint64_t present_id);
void wr64_forensic_set_output(uint64_t output_id);

void wr64_forensic_record(
    uint32_t type,
    uint64_t a0,
    uint64_t a1,
    uint64_t a2,
    uint64_t a3,
    uint64_t a4,
    uint64_t a5,
    uint64_t a6,
    uint64_t a7);

void wr64_forensic_record_blob(
    uint32_t type,
    uint64_t tag,
    const void *data,
    size_t size);

void wr64_forensic_capture_sky(
    uint8_t *rdram,
    uint32_t phase,
    uint32_t a0,
    uint32_t output_address);

void wr64_forensic_capture_rt64_sky(
    uint32_t stage,
    uint64_t submission_frame,
    uint32_t transform_index,
    uint32_t previous_transform_index,
    const float *positions,
    const float *position_velocities,
    const float *texcoords,
    const float *texcoord_velocities,
    uint32_t vertex_count,
    const float *view_matrix,
    const float *projection_matrix);

void wr64_forensic_freeze_pause_export(void);
void wr64_forensic_resume_reset(void);
void wr64_forensic_force_resume(void);
void wr64_forensic_wait_if_paused(void);

#ifdef __cplusplus
}
#endif

// Clean builds discard recorder arguments too: command decoding must not pay
// for diagnostic pointer lookups, timestamps, or capture preparation. Keep the
// declarations above so function pointers and older direct-extern callers can
// still link to the no-op C entry points in wr64_forensic.cpp.
#if !WR64_ENABLE_DIAGNOSTICS && !defined(WR64_FORENSIC_IMPLEMENTATION)
#define wr64_forensic_initialize(...) ((void)0)
#define wr64_forensic_shutdown(...) ((void)0)
#define wr64_forensic_enabled(...) (0)
#define wr64_forensic_is_paused(...) (0)
#define wr64_forensic_is_frozen(...) (0)
#define wr64_forensic_export_in_progress(...) (0)
#define wr64_forensic_set_rdram(...) ((void)0)
#define wr64_forensic_set_native_frame(...) ((void)0)
#define wr64_forensic_set_task(...) ((void)0)
#define wr64_forensic_set_submission(...) ((void)0)
#define wr64_forensic_set_workload(...) ((void)0)
#define wr64_forensic_set_present(...) ((void)0)
#define wr64_forensic_set_output(...) ((void)0)
#define wr64_forensic_record(...) ((void)0)
#define wr64_forensic_record_blob(...) ((void)0)
#define wr64_forensic_capture_sky(...) ((void)0)
#define wr64_forensic_capture_rt64_sky(...) ((void)0)
#define wr64_forensic_freeze_pause_export(...) ((void)0)
#define wr64_forensic_resume_reset(...) ((void)0)
#define wr64_forensic_force_resume(...) ((void)0)
#define wr64_forensic_wait_if_paused(...) ((void)0)
#endif
