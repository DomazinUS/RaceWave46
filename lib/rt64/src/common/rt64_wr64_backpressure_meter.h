// WR64 workload-thread back-pressure diagnostics.
// WR64_BACKPRESSURE_METER optionally names a CSV with one row per native frame:
// batch wait time, blocked-wait count, counter-set flips, and previous presented,
// available, and total counts. A previously drained counter set explains why a
// batch's waits can complete immediately; correlate with presentation records
// before attributing a visible stall to producer timing.
// Run timing calls outside interpolatedMutex and keep this recorder off the
// presentation thread. Flush rows during the run, independently of shutdown.

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <mutex>

namespace RT64 {
    inline const char *wr64BackpressureMeterPath() {
        static const char *path = std::getenv("WR64_BACKPRESSURE_METER");
        return path;
    }

    inline bool wr64BackpressureMeterArmed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool armed = [] {
            const char *p = wr64BackpressureMeterPath();
            const bool on = (p != nullptr) && (p[0] != '\0') && (p[0] != '0');
            if (on) {
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[backpressure] armed -> %s\n", p); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            }
            return on;
        }();
        return armed;
    }

    struct Wr64BackpressureMeterState {
        std::FILE *file = nullptr;
        bool opened = false;
        size_t written = 0;

        // Accumulated across one native frame's batch.
        uint64_t frame = 0;
        uint32_t displayFrames = 0;
        uint32_t flipped = 0;
        uint32_t prevPresented = 0;
        uint32_t prevAvailable = 0;
        uint32_t prevCount = 0;
        int64_t counterWaitUs = 0;
        int64_t waitTotalUs = 0;
        uint32_t waitsBlocked = 0;
        uint32_t waits = 0;
        bool open = false;

        // A learned baseline for the total wait, so "the back-pressure collapsed"
        // is measured against this run rather than an assumed 50 ms frame. The
        // cadence meter and the VI meter BOTH shipped a hardcoded threshold once;
        // this is the third instrument and the rule is settled.
        int64_t waitBaselineUs = 0;
        size_t waitSamples = 0;
        size_t collapses = 0;
    };

    // Batches needed before the baseline is trusted. Loads and menus come first
    // and would poison an unwarmed average.
    static constexpr size_t Wr64BackpressureWarmupFrames = 40;

    // A batch whose waits total less than this fraction of the learned baseline
    // has lost its back-pressure. The event under investigation cut a 50 ms cycle
    // to 18.8 ms, so its waits collapsed by far more than half; ordinary jitter in
    // the measured runs stays within about 10%.
    static constexpr double Wr64BackpressureCollapseFraction = 0.5;

    inline std::mutex &wr64BackpressureMeterMutex() {
        static std::mutex *m = new std::mutex();
        return *m;
    }

    // Leaked on purpose, as every recorder here is: anything that might be touched
    // during teardown must outlive teardown.
    inline Wr64BackpressureMeterState &wr64BackpressureMeterState() {
        static Wr64BackpressureMeterState *s = new Wr64BackpressureMeterState();
        return *s;
    }

    static constexpr size_t Wr64BackpressureMeterMaxRows = 500000;

    // Called once per native frame, after the counter set for this frame has been
    // chosen and before the interpolated-frame loop starts.
    inline void wr64BackpressureBegin(uint64_t submissionFrame, uint32_t displayFrames,
        bool flipped, uint32_t prevPresented, uint32_t prevAvailable, uint32_t prevCount,
        int64_t counterWaitUs)
    {
        if (!wr64BackpressureMeterArmed()) {
            return;
        }

        std::lock_guard<std::mutex> lock(wr64BackpressureMeterMutex());
        Wr64BackpressureMeterState &s = wr64BackpressureMeterState();
        s.frame = submissionFrame;
        s.displayFrames = displayFrames;
        s.flipped = flipped ? 1u : 0u;
        s.prevPresented = prevPresented;
        s.prevAvailable = prevAvailable;
        s.prevCount = prevCount;
        s.counterWaitUs = counterWaitUs;
        s.waitTotalUs = 0;
        s.waitsBlocked = 0;
        s.waits = 0;
        s.open = true;
    }

    // Called once per interpolated frame that reaches the back-pressure wait, with
    // how long that wait actually blocked.
    inline void wr64BackpressureWait(int64_t waitUs) {
        if (!wr64BackpressureMeterArmed()) {
            return;
        }

        std::lock_guard<std::mutex> lock(wr64BackpressureMeterMutex());
        Wr64BackpressureMeterState &s = wr64BackpressureMeterState();
        if (!s.open) {
            return;
        }

        s.waits++;
        s.waitTotalUs += waitUs;
        // 100 us is well above the cost of taking an uncontended lock and finding
        // the predicate already true, and well below any real wait.
        if (waitUs > 100) {
            s.waitsBlocked++;
        }
    }

    // Called once per native frame, after the loop.
    inline void wr64BackpressureEnd() {
        if (!wr64BackpressureMeterArmed()) {
            return;
        }

        std::lock_guard<std::mutex> lock(wr64BackpressureMeterMutex());
        Wr64BackpressureMeterState &s = wr64BackpressureMeterState();
        if (!s.open) {
            return;
        }
        s.open = false;

        if (!s.opened) {
            s.opened = true;
            s.file = std::fopen(wr64BackpressureMeterPath(), "wb");
            if (s.file != nullptr) {
                std::fprintf(s.file,
                    "submission_frame,display_frames,flipped,prev_presented,prev_available,"
                    "prev_count,counter_wait_us,wait_total_us,waits,waits_blocked,collapsed\n");
                std::fflush(s.file);
            }
            else {
                std::fprintf(stderr, "[backpressure] could not open %s for writing\n",
                    wr64BackpressureMeterPath());
                std::fflush(stderr);
            }
        }

        // The baseline is updated only from batches that did NOT collapse, so one
        // event cannot drag the reference down and hide the next.
        const bool warm = (s.waitSamples >= Wr64BackpressureWarmupFrames);
        const bool collapsed = warm && (s.waits > 0) &&
            (double(s.waitTotalUs) < (double(s.waitBaselineUs) * Wr64BackpressureCollapseFraction));
        if (collapsed) {
            s.collapses++;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[backpressure] frame %llu: THE WAITS COLLAPSED - %.1f ms total across %u"
                " frames (usual %.1f), %u of them blocked. Counter set %s, previous set had"
                " presented %u of %u.\n",
                static_cast<unsigned long long>(s.frame),
                double(s.waitTotalUs) / 1000.0, s.waits,
                double(s.waitBaselineUs) / 1000.0, s.waitsBlocked,
                s.flipped ? "FLIPPED" : "reused",
                s.prevPresented, s.prevCount); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }
        else if (s.waits > 0) {
            s.waitBaselineUs = (s.waitSamples == 0)
                ? s.waitTotalUs
                : ((s.waitBaselineUs * 15) + s.waitTotalUs) / 16;
            s.waitSamples++;
        }

        if ((s.file == nullptr) || (s.written >= Wr64BackpressureMeterMaxRows)) {
            return;
        }

        std::fprintf(s.file, "%llu,%u,%u,%u,%u,%u,%lld,%lld,%u,%u,%u\n",
            static_cast<unsigned long long>(s.frame),
            s.displayFrames, s.flipped,
            s.prevPresented, s.prevAvailable, s.prevCount,
            static_cast<long long>(s.counterWaitUs),
            static_cast<long long>(s.waitTotalUs),
            s.waits, s.waitsBlocked,
            collapsed ? 1u : 0u);
        std::fflush(s.file);
        s.written++;
    }
};
