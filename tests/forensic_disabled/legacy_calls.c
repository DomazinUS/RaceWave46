#include "wr64_forensic.h"

// Parentheses bypass function-like clean-build macros and exercise the actual
// external C symbols used by older runtime and generated direct declarations.
int wr64_forensic_c_linkage_probe(void) {
    (wr64_forensic_initialize)();
    (wr64_forensic_set_rdram)((uint8_t *)1, SIZE_MAX);
    (wr64_forensic_set_native_frame)(UINT64_MAX);
    (wr64_forensic_set_task)(UINT64_MAX);
    (wr64_forensic_set_submission)(UINT64_MAX);
    (wr64_forensic_set_workload)(UINT64_MAX);
    (wr64_forensic_set_present)(UINT64_MAX);
    (wr64_forensic_set_output)(UINT64_MAX);
    (wr64_forensic_record)(WR64_FORENSIC_RSP_COMMAND, 1, 2, 3, 4, 5, 6, 7, 8);
    (wr64_forensic_record_blob)(WR64_FORENSIC_SKY_MEMORY, UINT64_MAX, (const void *)1, SIZE_MAX);
    (wr64_forensic_capture_sky)((uint8_t *)1, 0, UINT32_MAX, UINT32_MAX);
    (wr64_forensic_capture_rt64_sky)(1, UINT64_MAX, UINT32_MAX, UINT32_MAX,
        (const float *)1, (const float *)1, (const float *)1, (const float *)1,
        UINT32_MAX, (const float *)1, (const float *)1);
    (wr64_forensic_freeze_pause_export)();
    (wr64_forensic_wait_if_paused)();
    if ((wr64_forensic_enabled)() || (wr64_forensic_is_paused)() ||
        (wr64_forensic_is_frozen)() || (wr64_forensic_export_in_progress)()) return 1;
    (wr64_forensic_resume_reset)();
    (wr64_forensic_force_resume)();
    (wr64_forensic_shutdown)();
    return 0;
}

int wr64_forensic_c_argument_probe(void) {
    int evaluated = 0;
    wr64_forensic_set_rdram((uint8_t *)(uintptr_t)(++evaluated), ++evaluated);
    wr64_forensic_record(++evaluated, ++evaluated, ++evaluated, ++evaluated,
        ++evaluated, ++evaluated, ++evaluated, ++evaluated, ++evaluated);
    wr64_forensic_capture_sky((uint8_t *)(uintptr_t)(++evaluated), ++evaluated, ++evaluated, ++evaluated);
    return evaluated;
}
