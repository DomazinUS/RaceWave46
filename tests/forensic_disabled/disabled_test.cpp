#include "wr64_forensic.h"
#include <cstdio>
#include <cstdlib>
#include <new>
#include <io.h>
#include <windows.h>

static_assert(WR64_ENABLE_DIAGNOSTICS == 0, "This test must never initialize the real recorder");
static size_t allocations = 0;
void *operator new(size_t size) {
    ++allocations;
    if (void *memory = std::malloc(size ? size : 1)) return memory;
    throw std::bad_alloc();
}
void *operator new[](size_t size) { return ::operator new(size); }
void operator delete(void *memory) noexcept { std::free(memory); }
void operator delete[](void *memory) noexcept { std::free(memory); }
void operator delete(void *memory, size_t) noexcept { std::free(memory); }
void operator delete[](void *memory, size_t) noexcept { std::free(memory); }
extern "C" int wr64_forensic_c_linkage_probe(void);
extern "C" int wr64_forensic_c_argument_probe(void);

int main() {
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
    _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
    if (_access("unexpected-capture", 0) == 0 || _access(".forensics", 0) == 0) return 2;
    const size_t allocationsBefore = allocations;
    int evaluated = 0;
    wr64_forensic_initialize();
    wr64_forensic_set_rdram(reinterpret_cast<uint8_t *>(++evaluated), ++evaluated);
    wr64_forensic_set_native_frame(++evaluated);
    wr64_forensic_set_task(++evaluated);
    wr64_forensic_set_submission(++evaluated);
    wr64_forensic_set_workload(++evaluated);
    wr64_forensic_set_present(++evaluated);
    wr64_forensic_set_output(++evaluated);
    wr64_forensic_record(++evaluated, ++evaluated, ++evaluated, ++evaluated,
        ++evaluated, ++evaluated, ++evaluated, ++evaluated, ++evaluated);
    wr64_forensic_record_blob(++evaluated, ++evaluated, reinterpret_cast<void *>(++evaluated), ++evaluated);
    wr64_forensic_capture_sky(reinterpret_cast<uint8_t *>(++evaluated), ++evaluated, ++evaluated, ++evaluated);
    wr64_forensic_capture_rt64_sky(++evaluated, ++evaluated, ++evaluated, ++evaluated,
        reinterpret_cast<float *>(++evaluated), reinterpret_cast<float *>(++evaluated),
        reinterpret_cast<float *>(++evaluated), reinterpret_cast<float *>(++evaluated),
        ++evaluated, reinterpret_cast<float *>(++evaluated), reinterpret_cast<float *>(++evaluated));
    wr64_forensic_freeze_pause_export();
    wr64_forensic_wait_if_paused();
    wr64_forensic_resume_reset();
    wr64_forensic_force_resume();
    wr64_forensic_shutdown();
    if (wr64_forensic_enabled() || wr64_forensic_is_paused() ||
        wr64_forensic_is_frozen() || wr64_forensic_export_in_progress()) return 3;
    if (evaluated || wr64_forensic_c_argument_probe()) return 4;
    for (unsigned i = 0; i < 64; ++i) if (wr64_forensic_c_linkage_probe()) return 5;
    if (allocations != allocationsBefore) return 6;
    if (_access("unexpected-capture", 0) == 0 || _access(".forensics", 0) == 0) return 7;
    std::puts("PASS: clean C/C++ calls skip argument evaluation; 21 external C entry points preserve ABI; zero allocations, pause state, or export files");
    return 0;
}
