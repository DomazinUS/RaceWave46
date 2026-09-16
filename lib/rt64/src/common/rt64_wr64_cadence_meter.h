// WR64 native-frame cadence diagnostics, enabled by WR64_CADENCE_METER.
// Record rational batch size and reset state alongside wall-clock submission and
// workload-pickup intervals. Fixed integer cadence does not prove steady delivery:
// the producer and presenter can change phase without changing batch size.
//
// Compare submission and pickup intervals to distinguish game timing from queue
// processing. Queue depth counts work beyond the current workload, so zero alone
// cannot distinguish early submission from early pickup. Reset the learned timing
// baseline when the reported native rate changes, avoiding false 20-to-30 Hz alerts.
// Write one row per native frame through a persistent stream and flush during the
// run rather than depending on shutdown handlers.

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <cstdint>
#include <cstdio>
#include <chrono>
#include <cstdlib>
#include <mutex>

namespace RT64 {
    inline const char *wr64CadenceMeterPath() {
        static const char *path = std::getenv("WR64_CADENCE_METER");
        return path;
    }

    inline bool wr64CadenceMeterArmed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool armed = [] {
            const char *p = wr64CadenceMeterPath();
            const bool on = (p != nullptr) && (p[0] != '\0') && (p[0] != '0');
            if (on) {
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[cadencemeter] armed -> %s\n", p); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            }
            return on;
        }();
        return armed;
    }

    struct Wr64CadenceMeterState {
        std::FILE *file = nullptr;
        bool opened = false;
        size_t written = 0;
        uint32_t lastDisplayFrames = 0;
        bool haveLast = false;
        size_t irregular = 0;
        size_t resets = 0;
        // R2. Wall-clock, which is the thing R1 turned out not to be measuring.
        std::chrono::steady_clock::time_point lastTime{};
        bool haveTime = false;
        size_t late = 0;
        int64_t worstIntervalUs = 0;
        // R3. A LEARNED baseline for the SHORT test, never an assumed period.
        // The VI meter had this bug in its first draft - a hardcoded threshold
        // that silently assumed 20 Hz - and its own self-test flagged every
        // single flip. Same rule here.
        int64_t baselineUs = 0;
        size_t baselineSamples = 0;
        size_t shortFrames = 0;
        // R4. The rate the baseline was learned at. A baseline learned at 20 Hz
        // means nothing at 30 Hz, and an exponential average walks between them
        // far too slowly - which is why 104 menu frames were flagged.
        uint32_t baselineRate = 0;
        // R4. The GAME's rhythm, stamped at State::fullSync on the game thread,
        // as opposed to the workload thread's pickup rhythm measured below.
        std::chrono::steady_clock::time_point lastSubmit{};
        bool haveSubmit = false;
        int64_t lastSubmitIntervalUs = 0;
    };

    // Frames needed before the baseline is trusted. Below this nothing is called
    // short, because an unwarmed average would flag the opening loads.
    static constexpr size_t Wr64CadenceMeterWarmupFrames = 24;

    // A native frame shorter than this fraction of the learned baseline is the
    // event. Measured jitter reaches 0.9 (45 ms against a 50 ms baseline) and the
    // recorded events came in at 0.41 to 0.44, so 0.8 sits in open space.
    static constexpr double Wr64CadenceMeterShortFraction = 0.8;

    inline std::mutex &wr64CadenceMeterMutex() {
        static std::mutex *m = new std::mutex();
        return *m;
    }

    // Leaked on purpose, same reason as every other recorder here: anything that
    // might be touched during teardown must outlive teardown.
    inline Wr64CadenceMeterState &wr64CadenceMeterState() {
        static Wr64CadenceMeterState *s = new Wr64CadenceMeterState();
        return *s;
    }

    static constexpr size_t Wr64CadenceMeterMaxRows = 500000;

    // Called from State::fullSync on the GAME thread, immediately before the
    // workload is advanced. This is when the game says it has finished the frame;
    // everything else in this file is measured on the workload thread afterwards.
    inline void wr64CadenceMeterSubmit() {
        if (!wr64CadenceMeterArmed()) {
            return;
        }

        std::lock_guard<std::mutex> lock(wr64CadenceMeterMutex());
        Wr64CadenceMeterState &s = wr64CadenceMeterState();
        const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        if (s.haveSubmit) {
            s.lastSubmitIntervalUs =
                std::chrono::duration_cast<std::chrono::microseconds>(now - s.lastSubmit).count();
        }
        s.lastSubmit = now;
        s.haveSubmit = true;
    }

    inline void wr64CadenceMeterRecord(uint64_t submissionFrame, uint64_t workloadId,
        uint64_t presentId, uint32_t viOriginalRate, uint32_t targetRate,
        uint32_t displayFrames, int64_t tickGap, bool resetTicks,
        bool generateInterpolatedFrames, bool paused, uint32_t queueDepth)
    {
        if (!wr64CadenceMeterArmed()) {
            return;
        }

        std::lock_guard<std::mutex> lock(wr64CadenceMeterMutex());
        Wr64CadenceMeterState &s = wr64CadenceMeterState();

        if (!s.opened) {
            s.opened = true;
            s.file = std::fopen(wr64CadenceMeterPath(), "wb");
            if (s.file != nullptr) {
                std::fprintf(s.file,
                    "submission_frame,workload_id,present_id,vi_original_rate,target_rate,"
                    "display_frames,tick_gap,reset_ticks,generate_interpolated,paused,"
                    "changed_from_previous,interval_us,expected_us,late,"
                    "queue_depth,short_frame,submit_interval_us\n");
                std::fflush(s.file);
            }
            else {
                std::fprintf(stderr, "[cadencemeter] could not open %s for writing\n",
                    wr64CadenceMeterPath());
                std::fflush(stderr);
            }
        }

        // "Changed" is the column the whole file exists for. A steady cadence
        // writes zero in it forever; the frames worth looking at are the ones
        // that write one.
        // ---- R2. The native frame period, measured rather than derived.
        //
        // steady_clock, not system_clock: this is a duration between two points in
        // one process and must not move when the wall clock is adjusted.
        //
        // "Expected" comes from the game's OWN reported video rate, so the test
        // does not assume 20 Hz. A frame is called late at one and a half times
        // its own period, which at 20 Hz is 75 ms against a 50 ms budget - well
        // clear of ordinary jitter and well under the 100 ms a wholly missed
        // period would cost.
        const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        int64_t intervalUs = 0;
        if (s.haveTime) {
            intervalUs = std::chrono::duration_cast<std::chrono::microseconds>(now - s.lastTime).count();
        }
        s.lastTime = now;
        s.haveTime = true;

        const int64_t expectedUs = (viOriginalRate > 0) ? (1000000 / int64_t(viOriginalRate)) : 0;
        const bool late = (expectedUs > 0) && (intervalUs > ((expectedUs * 3) / 2));
        if (late) {
            s.late++;
            if (intervalUs > s.worstIntervalUs) {
                s.worstIntervalUs = intervalUs;
            }
        }

        // ---- R4. A baseline learned at one video rate is meaningless at
        // another, and an exponential average crosses between them far too
        // slowly - 104 menu frames were flagged for exactly this reason. Reset on
        // the change rather than trying to follow it.
        if (viOriginalRate != s.baselineRate) {
            s.baselineRate = viOriginalRate;
            s.baselineUs = 0;
            s.baselineSamples = 0;
        }

        // ---- R3. THE SHORT FRAME, against a baseline learned from this run.
        //
        // The baseline is updated only from frames that are NOT short, so one
        // event cannot drag the reference down and hide the next one.
        const bool warm = (s.baselineSamples >= Wr64CadenceMeterWarmupFrames);
        const bool shortFrame = warm && (intervalUs > 0) && generateInterpolatedFrames &&
            (double(intervalUs) < (double(s.baselineUs) * Wr64CadenceMeterShortFraction));
        if (shortFrame) {
            s.shortFrames++;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[cadencemeter] frame %llu: NATIVE FRAME ARRIVED %.1f ms EARLY"
                " (%.1f ms, usual %.1f) - the game submitted %.1f ms apart, so %s\n",
                static_cast<unsigned long long>(submissionFrame),
                double(s.baselineUs - intervalUs) / 1000.0,
                double(intervalUs) / 1000.0, double(s.baselineUs) / 1000.0,
                double(s.lastSubmitIntervalUs) / 1000.0,
                (s.lastSubmitIntervalUs > 0) && (s.lastSubmitIntervalUs < ((s.baselineUs * 4) / 5))
                    ? "THE GAME SUBMITTED EARLY"
                    : "THE WORKLOAD THREAD RAN AHEAD"); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }
        else if ((intervalUs > 0) && generateInterpolatedFrames && !late) {
            s.baselineUs = (s.baselineSamples == 0)
                ? intervalUs
                : ((s.baselineUs * 15) + intervalUs) / 16;
            s.baselineSamples++;
        }

        const uint32_t previousDisplayFrames = s.lastDisplayFrames;
        const bool changed = s.haveLast && (displayFrames != previousDisplayFrames);
        s.lastDisplayFrames = displayFrames;
        s.haveLast = true;
        if (changed) {
            s.irregular++;
        }
        if (resetTicks) {
            s.resets++;
        }

        // Announce cadence changes only while interpolating; scene-change resets are
        // expected. Capture the previous batch size before overwriting it so the
        // diagnostic reports both values correctly.
        if (changed && generateInterpolatedFrames) {
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[cadencemeter] frame %llu: batch %u -> %u interpolated frames%s\n",
                static_cast<unsigned long long>(submissionFrame),
                previousDisplayFrames, displayFrames,
                resetTicks ? "  (the cadence was reset)" : ""); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        // R2. THE LINE THIS BUILD EXISTS FOR. Said out loud the moment it happens,
        // so a long native frame and a felt stutter can be matched up live instead
        // of afterwards. Only while interpolating - a long frame during a load is
        // a load, and saying so would train the reader to ignore the line.
        if (late && generateInterpolatedFrames) {
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[cadencemeter] frame %llu: NATIVE FRAME TOOK %.1f ms (expected %.1f) -"
                " the presenter had nothing new for %.1f ms\n",
                static_cast<unsigned long long>(submissionFrame),
                double(intervalUs) / 1000.0, double(expectedUs) / 1000.0,
                double(intervalUs - expectedUs) / 1000.0); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        if ((s.file == nullptr) || (s.written >= Wr64CadenceMeterMaxRows)) {
            return;
        }

        std::fprintf(s.file, "%llu,%llu,%llu,%u,%u,%u,%lld,%u,%u,%u,%u,%lld,%lld,%u,%u,%u,%lld\n",
            static_cast<unsigned long long>(submissionFrame),
            static_cast<unsigned long long>(workloadId),
            static_cast<unsigned long long>(presentId),
            viOriginalRate, targetRate, displayFrames,
            static_cast<long long>(tickGap),
            resetTicks ? 1u : 0u,
            generateInterpolatedFrames ? 1u : 0u,
            paused ? 1u : 0u,
            changed ? 1u : 0u,
            static_cast<long long>(intervalUs),
            static_cast<long long>(expectedUs),
            late ? 1u : 0u,
            queueDepth,
            shortFrame ? 1u : 0u,
            static_cast<long long>(s.lastSubmitIntervalUs));
        std::fflush(s.file);
        s.written++;
    }
};
