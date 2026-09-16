// WR64 presentation diagnostics, enabled by WR64_PRESENT_METER.
// Record one row per present event and join workload_id to the cadence meter.
// The rescued, dropped, and flat verdicts come from queue/interpolation state;
// starvation uses measured time waiting for the first producer frame.
//
// A skipped event advances presented to count, allowing the following producer
// batch to run ahead. Correlation is therefore needed before treating a short
// producer interval as the cause of a presentation stall. Report backlog edges
// without printing every event, while retaining each event in the CSV.
//
// The presentation thread must not block for instrumentation. Durations arrive
// from call sites; this recorder does not read the clock or run inside the
// interpolated-frame loop. Flush rows during the run independently of shutdown.

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <mutex>

namespace RT64 {
    inline const char *wr64PresentMeterPath() {
        static const char *path = std::getenv("WR64_PRESENT_METER");
        return path;
    }

    inline bool wr64PresentMeterArmed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool armed = [] {
            const char *p = wr64PresentMeterPath();
            const bool on = (p != nullptr) && (p[0] != '\0') && (p[0] != '0');
            if (on) {
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[presentmeter] armed -> %s\n", p); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            }
            return on;
        }();
        return armed;
    }

    struct Wr64PresentMeterState {
        std::FILE *file = nullptr;
        bool opened = false;
        size_t written = 0;

        // Accumulated across one present event.
        uint64_t presentId = 0;
        uint64_t workloadId = 0;
        int64_t eventWaitUs = 0;
        int64_t workloadWaitUs = 0;
        int64_t cycleUs = 0;
        int64_t frameWaitUs = 0;
        int64_t firstFrameWaitUs = 0;
        uint32_t frameWaits = 0;
        uint32_t frameWaitsBlocked = 0;
        uint32_t framesToPresent = 0;
        uint32_t framesSubmitted = 0;
        uint32_t counterCount = 0;
        uint32_t counterAvailable = 0;
        uint32_t counterPresented = 0;
        uint32_t interpolationEnabled = 0;
        uint32_t viVisible = 0;
        uint32_t scanFired = 0;
        uint32_t scanWalked = 0;
        uint32_t scanSize = 0;
        uint32_t viAddress = 0;
        uint32_t presentAddress = 0;
        uint32_t skipped = 0;
        uint32_t queueDepth = 0;
        bool open = false;

        // A LEARNED BASELINE FOR THE PRESENTER'S OWN PERIOD, not an assumed one.
        // The cadence meter and the VI meter each shipped a hardcoded threshold
        // and each flagged every single frame on its own scaled self-test. This
        // is the fourth instrument and the rule is settled: measure the run
        // against the run. Note that only the TIMED verdict needs this at all -
        // the two exact verdicts below compare integers and need no baseline,
        // which is why they are the primary ones.
        int64_t cycleBaselineUs = 0;
        size_t cycleSamples = 0;
        uint32_t baselineCount = 0;
        size_t flats = 0;
        size_t drops = 0;
        size_t rescues = 0;

        // A BACKLOG IS A STRETCH, NOT AN EVENT. The first build of this announced
        // every rescued frame, expecting three a run. It got 1,883 and buried the
        // console, which made the one thing the run existed to measure - how the
        // game FEELS - impossible to judge. Announce the edges.
        bool inBacklog = false;
        uint64_t backlogFirstPresent = 0;
        size_t backlogEvents = 0;
        uint32_t backlogMaxDepth = 0;
        int64_t backlogUs = 0;
        size_t backlogDropped = 0;
        size_t backlogStretches = 0;
        size_t starves = 0;
    };

    // Present events needed before the TIMED verdict is trusted. Loads and menus
    // come first and would poison an unwarmed average. The exact verdicts do not
    // wait for this - an integer needs no warmup.
    static constexpr size_t Wr64PresentMeterWarmupEvents = 40;

    // The presenter has STARVED when it spent more than this fraction of a whole
    // native period waiting for the producer to publish frame 0 of the batch.
    //
    // Healthy is essentially zero: the producer is a full batch ahead, so that id
    // was advanced long before the present event arrived. A presenter that ran
    // out would sit here for most of a period. A quarter is far above the healthy
    // value and far below that, and because it is a fraction OF THE LEARNED
    // PERIOD rather than a millisecond count it stays correct at 20 Hz, at 30 Hz,
    // and on a scaled self-test clock.
    static constexpr double Wr64PresentMeterStarveFraction = 0.25;

    inline std::mutex &wr64PresentMeterMutex() {
        static std::mutex *m = new std::mutex();
        return *m;
    }

    // Leaked on purpose, as every recorder here is: anything that might be
    // touched during teardown must outlive teardown.
    inline Wr64PresentMeterState &wr64PresentMeterState() {
        static Wr64PresentMeterState *s = new Wr64PresentMeterState();
        return *s;
    }

    static constexpr size_t Wr64PresentMeterMaxRows = 500000;

    // Called once per present event, in threadLoop, after both of that
    // function's waits have returned and before the event is presented.
    //
    // Every duration is passed in. This file reads no clock - see the note at the
    // top about why that is a rule here and not a preference.
    inline void wr64PresentMeterBegin(uint64_t presentId, uint64_t workloadId,
        int64_t eventWaitUs, int64_t workloadWaitUs, int64_t cycleUs, bool skipped,
        uint32_t queueDepth)
    {
        if (!wr64PresentMeterArmed()) {
            return;
        }

        std::lock_guard<std::mutex> lock(wr64PresentMeterMutex());
        Wr64PresentMeterState &s = wr64PresentMeterState();
        s.presentId = presentId;
        s.workloadId = workloadId;
        s.eventWaitUs = eventWaitUs;
        s.workloadWaitUs = workloadWaitUs;
        s.cycleUs = cycleUs;
        s.skipped = skipped ? 1u : 0u;
        s.queueDepth = queueDepth;
        s.frameWaitUs = 0;
        s.firstFrameWaitUs = 0;
        s.frameWaits = 0;
        s.frameWaitsBlocked = 0;
        s.framesToPresent = 0;
        s.framesSubmitted = 0;
        s.counterCount = 0;
        s.counterAvailable = 0;
        s.counterPresented = 0;
        s.interpolationEnabled = 0;
        s.viVisible = 0;
        s.scanFired = 0;
        s.scanWalked = 0;
        s.scanSize = 0;
        s.viAddress = 0;
        s.presentAddress = 0;
        s.open = true;
    }

    // Called once at the end of threadPresent, with totals the loop accumulated
    // into plain locals and the framebuffer scan's own counters. Nothing in this
    // file is called from inside that loop.
    //
    // interpolationEnabled and the three scan fields are what say WHY a present
    // event went flat, rather than only that it did.
    inline void wr64PresentMeterFrames(uint32_t framesToPresent, uint32_t framesSubmitted,
        int64_t frameWaitUs, int64_t firstFrameWaitUs, uint32_t frameWaits,
        uint32_t frameWaitsBlocked, uint32_t counterCount, uint32_t counterAvailable,
        uint32_t counterPresented, bool interpolationEnabled, bool viVisible,
        uint32_t scanFired, uint32_t scanWalked, uint32_t scanSize, uint32_t viAddress,
        uint32_t presentAddress)
    {
        if (!wr64PresentMeterArmed()) {
            return;
        }

        std::lock_guard<std::mutex> lock(wr64PresentMeterMutex());
        Wr64PresentMeterState &s = wr64PresentMeterState();
        if (!s.open) {
            return;
        }

        s.framesToPresent = framesToPresent;
        s.framesSubmitted = framesSubmitted;
        s.frameWaitUs = frameWaitUs;
        s.firstFrameWaitUs = firstFrameWaitUs;
        s.frameWaits = frameWaits;
        s.frameWaitsBlocked = frameWaitsBlocked;
        s.counterCount = counterCount;
        s.counterAvailable = counterAvailable;
        s.counterPresented = counterPresented;
        s.interpolationEnabled = interpolationEnabled ? 1u : 0u;
        s.viVisible = viVisible ? 1u : 0u;
        s.scanFired = scanFired;
        s.scanWalked = scanWalked;
        s.scanSize = scanSize;
        s.viAddress = viAddress;
        s.presentAddress = presentAddress;
    }

    // Called once per present event, in threadLoop, after the event has been
    // presented or skipped. Writes the row.
    inline void wr64PresentMeterEnd() {
        if (!wr64PresentMeterArmed()) {
            return;
        }

        std::lock_guard<std::mutex> lock(wr64PresentMeterMutex());
        Wr64PresentMeterState &s = wr64PresentMeterState();
        if (!s.open) {
            return;
        }
        s.open = false;

        if (!s.opened) {
            s.opened = true;
            s.file = std::fopen(wr64PresentMeterPath(), "wb");
            if (s.file != nullptr) {
                std::fprintf(s.file,
                    "present_id,workload_id,cycle_us,event_wait_us,workload_wait_us,"
                    "frame_wait_us,first_frame_wait_us,frame_waits,frame_waits_blocked,"
                    "work_us,frames_to_present,frames_submitted,counter_count,"
                    "counter_available,counter_presented,interp_enabled,vi_visible,fb_scan_fired,"
                    "fb_scan_walked,fb_scan_size,vi_address,present_address,"
                    "skipped,flat,dropped,starved,queue_depth,rescued\n");
                std::fflush(s.file);
            }
            else {
                std::fprintf(stderr, "[presentmeter] could not open %s for writing\n",
                    wr64PresentMeterPath());
                std::fflush(stderr);
            }
        }

        // What the presenter did with its period, after the three waits are
        // taken out of it. Clamped at zero because the cycle and the waits are
        // measured by different call sites and rounding may cross.
        int64_t workUs = s.cycleUs - s.eventWaitUs - s.workloadWaitUs - s.frameWaitUs;
        if (workUs < 0) {
            workUs = 0;
        }

        // Detect a produced multi-frame batch presented as one image from the actual
        // integer counts, not a learned baseline. Require visible VI output so screen-
        // off transitions and one-frame load batches do not produce false alerts.
        const bool dropped = (s.skipped != 0u);
        const bool flat = !dropped && (s.viVisible != 0u) &&
            (s.counterCount > 1u) && (s.framesToPresent == 1u);

        // Count events retained despite a backlog. The earlier any-backlog rule discarded
        // a complete native tick to correct a sub-millisecond phase difference.
        const bool rescued = !dropped && (s.queueDepth > 0u);

        // ---- THE TIMED VERDICT, which is the competing story: that the
        // presenter ran out and sat waiting rather than showing one frame.
        const bool warm = (s.cycleSamples >= Wr64PresentMeterWarmupEvents);
        const bool starved = warm && (s.cycleBaselineUs > 0) &&
            (double(s.workloadWaitUs) > (double(s.cycleBaselineUs) * Wr64PresentMeterStarveFraction));

        if (rescued) {
            s.rescues++;
        }

        // THE EDGES OF A BACKLOG STRETCH, and nothing in between. Every event
        // inside one still gets its row and its rescued flag; the console gets
        // two lines for the whole stretch.
        const bool inBacklogNow = (s.queueDepth > 0u);
        if (inBacklogNow && !s.inBacklog) {
            s.inBacklog = true;
            s.backlogStretches++;
            s.backlogFirstPresent = s.presentId;
            s.backlogEvents = 0;
            s.backlogMaxDepth = 0;
            s.backlogUs = 0;
            s.backlogDropped = 0;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[presentmeter] present %llu:"
                " KEEPING FRAMES THAT USED TO BE THROWN AWAY"
                " - one event is now queued behind each one. Before this build every"
                " one of these was a discarded game tick. Quiet from here until it"
                " ends or deepens.\n",
                static_cast<unsigned long long>(s.presentId)); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        if (inBacklogNow) {
            s.backlogEvents++;
            s.backlogUs += s.cycleUs;
            if (dropped) {
                s.backlogDropped++;
            }
            if (s.queueDepth > s.backlogMaxDepth) {
                // A stretch that DEEPENS is worth a line: two or more is a real
                // backlog and the event is being dropped again.
                if (s.backlogMaxDepth > 0u) {
                    { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                        "[presentmeter] present %llu: THE BACKLOG DEEPENED to %u."
                        " %s\n",
                        static_cast<unsigned long long>(s.presentId), s.queueDepth,
                        (s.queueDepth >= 3u)
                            ? "The ring is full and the game is about to block, so this is a tick lost."
                            : "Still kept - the ring holds four. Watch whether it STAYS here."); }
                    { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
                }
                s.backlogMaxDepth = s.queueDepth;
            }
        }
        else if (s.inBacklog) {
            s.inBacklog = false;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[presentmeter] present %llu: BACK TO ZERO after %zu event(s),"
                " %.1f s, deepest %u. %zu kept, %zu lost.\n",
                static_cast<unsigned long long>(s.presentId),
                s.backlogEvents, double(s.backlogUs) / 1000000.0, s.backlogMaxDepth,
                s.backlogEvents - s.backlogDropped, s.backlogDropped); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        if (flat) {
            s.flats++;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[presentmeter] present %llu (workload %llu):"
                " ONE IMAGE FOR A WHOLE PERIOD"
                " - the producer built %u frames and this event showed 1."
                " Interpolation was %s and the framebuffer scan %s (%u of %u entries"
                " walked, VI %08X, showing %08X).\n",
                static_cast<unsigned long long>(s.presentId),
                static_cast<unsigned long long>(s.workloadId),
                s.counterCount,
                s.interpolationEnabled ? "ON" : "OFF",
                s.scanFired ? "found the framebuffer" : "NEVER MATCHED",
                s.scanWalked, s.scanSize, s.viAddress, s.presentAddress); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }
        else if (dropped) {
            s.drops++;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[presentmeter] present %llu (workload %llu): THE EVENT WAS DROPPED -"
                " %u events were already queued behind it, which is a real backlog"
                " rather than phase noise, so nothing was shown for this period.\n",
                static_cast<unsigned long long>(s.presentId),
                static_cast<unsigned long long>(s.workloadId),
                s.queueDepth); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }
        else if (starved) {
            s.starves++;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[presentmeter] present %llu (workload %llu): THE PRESENTER RAN DRY -"
                " it waited %.1f ms for the producer to publish this batch, out of a"
                " %.1f ms period. The previous batch left it %u of %u presented.\n",
                static_cast<unsigned long long>(s.presentId),
                static_cast<unsigned long long>(s.workloadId),
                double(s.workloadWaitUs) / 1000.0,
                double(s.cycleBaselineUs) / 1000.0,
                s.counterPresented, s.counterCount); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        // A CHANGE OF BATCH SIZE RESETS THE PERIOD BASELINE. An exponential
        // average cannot follow a rate change: the cadence meter's average was
        // still chasing the 20 Hz period all the way through a 30 Hz menu block
        // and flagged all 104 of its frames. Menus, loads and the attract mode
        // all move this, and none of them is the event being hunted.
        if (s.counterCount != s.baselineCount) {
            s.baselineCount = s.counterCount;
            s.cycleBaselineUs = 0;
            s.cycleSamples = 0;
        }
        else if ((s.cycleUs > 0) && !flat && !dropped && !starved) {
            // The baseline learns only from ordinary events, so one bad period
            // cannot drag the reference and hide the next.
            s.cycleBaselineUs = (s.cycleSamples == 0)
                ? s.cycleUs
                : ((s.cycleBaselineUs * 15) + s.cycleUs) / 16;
            s.cycleSamples++;
        }

        if ((s.file == nullptr) || (s.written >= Wr64PresentMeterMaxRows)) {
            return;
        }

        std::fprintf(s.file,
            "%llu,%llu,%lld,%lld,%lld,%lld,%lld,%u,%u,%lld,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%08X,%08X,%u,%u,%u,%u,%u,%u\n",
            static_cast<unsigned long long>(s.presentId),
            static_cast<unsigned long long>(s.workloadId),
            static_cast<long long>(s.cycleUs),
            static_cast<long long>(s.eventWaitUs),
            static_cast<long long>(s.workloadWaitUs),
            static_cast<long long>(s.frameWaitUs),
            static_cast<long long>(s.firstFrameWaitUs),
            s.frameWaits, s.frameWaitsBlocked,
            static_cast<long long>(workUs),
            s.framesToPresent, s.framesSubmitted,
            s.counterCount, s.counterAvailable, s.counterPresented,
            s.interpolationEnabled, s.viVisible, s.scanFired, s.scanWalked, s.scanSize,
            s.viAddress, s.presentAddress,
            s.skipped,
            flat ? 1u : 0u,
            dropped ? 1u : 0u,
            starved ? 1u : 0u,
            s.queueDepth,
            rescued ? 1u : 0u);
        std::fflush(s.file);
        s.written++;
    }
};
