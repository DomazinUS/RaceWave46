//
// Wave Race 64 stall attribution probe.
//
// Header-only so it can be dropped into any translation unit without a new build
// system entry. It exists to answer one question: when the presented frame rate
// dips for a moment, which blocking operation ate the time?
//
// Inert unless WR64_STALL_PROBE is set. The disabled path is a single load of a
// latched bool and an early return: no clock read, no allocation, no lock, no I/O.
// That standard is deliberate, since diagnostics that cost something when switched
// off are exactly what this probe is meant to hunt down.
//
// WR64_STALL_PROBE=1             enable
// WR64_STALL_PROBE_MS=5.0        report a blocking operation immediately at or above this many ms
// WR64_STALL_PROBE_INTERVAL_MS   present-to-present gap that counts as a hitch, default 11.0
// WR64_STALL_PROBE_HOT_MS=0.5    floor for sites that run at draw rate or frame rate
// WR64_STALL_PROBE_GATE_SCALE=1  multiplier on the per site floors written into the source
// WR64_STALL_PROBE_CONTEXT=96    how many preceding samples to dump when a hitch fires
// WR64_STALL_PROBE_WINDOW_MS=250 how far back that dump is allowed to reach
// WR64_STALL_PROBE_LOG           log path, default wr64-stall-probe.log
//
// The interval threshold is separate on purpose. A locked 180 Hz present loop
// runs a 5.556 ms gap every frame, so it would trip the operation threshold
// continuously and drown the log. 11.0 ms is just over two display frames at
// 180 Hz: silent when the cadence holds, loud the moment a frame is missed.
//
// Why the ring buffer.
//
// The first version of this probe only wrote a line when a single operation
// exceeded the threshold. That answers "which one call was slow" and nothing
// else, and it is blind to the two failure shapes that are just as likely here:
//
//   many small costs         thirty operations of 1.2 ms in the same window add
//                            up to a dropped frame while no single one of them
//                            ever crosses a 4 ms bar
//
//   uninstrumented cost      the frame is late and none of the named probes
//                            fired, so the time went somewhere this file does
//                            not yet watch
//
// So every probe now records into a fixed ring regardless of how long it took,
// and a hitch dumps the recent history of that ring. The two shapes above become
// directly readable: the first as a dense run of small samples before the hitch
// line, the second as a hitch line with an empty window behind it.
//
// The ring is a fixed array of PODs with an atomic publication counter. There is
// no allocation on the recording path and no lock, so a probe cannot serialise
// the very threads it is measuring. A sample that is overwritten while the dump
// is reading it is detected and skipped rather than printed torn.
//

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <atomic>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

namespace RT64 {
    inline bool wr64StallProbeEnabled() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool enabled = []() {
            const char *value = std::getenv("WR64_STALL_PROBE");
            return (value != nullptr) && (value[0] != '\0') && (value[0] != '0');
        }();
        return enabled;
    }

    inline double wr64StallProbeEnvDouble(const char *name, double fallback) {
        const char *value = std::getenv(name);
        if ((value == nullptr) || (value[0] == '\0')) {
            return fallback;
        }

        const double parsed = std::atof(value);
        return (parsed > 0.0) ? parsed : fallback;
    }

    inline double wr64StallProbeThresholdMs() {
        static const double threshold = wr64StallProbeEnvDouble("WR64_STALL_PROBE_MS", 5.0);
        return threshold;
    }

    inline double wr64StallProbeIntervalThresholdMs() {
        static const double threshold = wr64StallProbeEnvDouble("WR64_STALL_PROBE_INTERVAL_MS", 11.0);
        return threshold;
    }

    // Floor for sites that run at draw call or present rate. Those fire thousands
    // of times a second, and if every one of them landed in the ring the ring would
    // recycle in well under the context window, which would leave a hitch dump
    // showing nothing but the last few milliseconds of noise. A hot site only
    // records when it actually blocked for this long. Anything under it cannot on
    // its own explain a lost frame, and if a crowd of them adds up, the batch level
    // probes that enclose them will show the total.
    inline double wr64StallProbeHotThresholdMs() {
        static const double threshold = wr64StallProbeEnvDouble("WR64_STALL_PROBE_HOT_MS", 0.5);
        return threshold;
    }

    // Multiplier applied to every per site floor (see WR64StallProbeGate below).
    // Those floors are written into the source at each call site because each one
    // knows its own normal cost, but a second pass sometimes needs to hear the
    // quieter sites too. Set this to 0.3 and a 7 ms floor becomes 2.1 ms, without
    // rebuilding and without editing four numbers by hand. One is the default and
    // leaves every site exactly as the source declares it. The floor is never
    // allowed below a twentieth of a millisecond, because a floor of zero would
    // record every single call and flood the ring, which is the failure the floors
    // exist to prevent in the first place.
    inline double wr64StallProbeGateScale() {
        static const double scale = wr64StallProbeEnvDouble("WR64_STALL_PROBE_GATE_SCALE", 1.0);
        return (scale > 0.0) ? scale : 1.0;
    }

    inline uint32_t wr64StallProbeContextCount() {
        static const uint32_t count = static_cast<uint32_t>(wr64StallProbeEnvDouble("WR64_STALL_PROBE_CONTEXT", 96.0));
        return count;
    }

    inline double wr64StallProbeContextWindowMs() {
        static const double window = wr64StallProbeEnvDouble("WR64_STALL_PROBE_WINDOW_MS", 250.0);
        return window;
    }

    // One clock origin shared by every site, so the timestamps in a context dump
    // and the timestamps on the immediate reports are on the same timeline and can
    // be read against each other.
    inline double wr64StallProbeNowMs() {
        if (!WR64_DIAGNOSTIC_ENABLED) return 0.0;
        static const std::chrono::steady_clock::time_point origin = std::chrono::steady_clock::now();
        const std::chrono::duration<double, std::milli> since = std::chrono::steady_clock::now() - origin;
        return since.count();
    }

    // Threads are identified by a small dense integer rather than the platform id,
    // because the point is to read a dump at a glance and see that six samples came
    // off three different threads. The name is optional and is only a label; a
    // thread that never sets one still gets an id.
    inline uint32_t wr64StallProbeThreadId() {
        static std::atomic<uint32_t> nextId(1);
        static thread_local const uint32_t id = nextId.fetch_add(1, std::memory_order_relaxed);
        return id;
    }

    inline const char *&wr64StallProbeThreadNameSlot() {
        static thread_local const char *name = "unnamed";
        return name;
    }

    // Call once at the top of a thread loop. Only string literals, since the
    // pointer is stored in the ring and read later.
    inline void wr64StallProbeNameThread(const char *name) {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        if (!wr64StallProbeEnabled()) {
            return;
        }

        wr64StallProbeThreadNameSlot() = name;
        wr64StallProbeThreadId();
    }

    struct WR64StallProbeSample {
        // Zero while the payload is being written, then index + 1 once it is
        // complete. A reader that sees any other value knows this slot was
        // recycled underneath it.
        std::atomic<uint64_t> published;
        double startMs;
        double durationMs;
        uint64_t detail;
        const char *label;
        const char *threadName;
        uint32_t threadId;
    };

    static constexpr uint64_t WR64StallProbeRingCapacity = 512;

    struct WR64StallProbeRing {
        WR64StallProbeSample samples[WR64StallProbeRingCapacity];
        std::atomic<uint64_t> cursor;

        WR64StallProbeRing() : cursor(0) {
            for (uint64_t i = 0; i < WR64StallProbeRingCapacity; i++) {
                samples[i].published.store(0, std::memory_order_relaxed);
                samples[i].startMs = 0.0;
                samples[i].durationMs = 0.0;
                samples[i].detail = 0;
                samples[i].label = nullptr;
                samples[i].threadName = nullptr;
                samples[i].threadId = 0;
            }
        }
    };

    inline WR64StallProbeRing &wr64StallProbeRing() {
        static WR64StallProbeRing ring;
        return ring;
    }

    inline std::FILE *wr64StallProbeLogFile() {
        // Opened once on the first write. A file rather than stderr only, because a
        // windowed process does not reliably have a console attached and a probe whose
        // output can silently go nowhere is worse than no probe. Path defaults next to
        // the executable; override with WR64_STALL_PROBE_LOG.
        static std::FILE *logFile = []() -> std::FILE * {
            const char *path = std::getenv("WR64_STALL_PROBE_LOG");
            if ((path == nullptr) || (path[0] == '\0')) {
                path = "wr64-stall-probe.log";
            }

            std::FILE *file = std::fopen(path, "w");
            if (file != nullptr) {
                std::fprintf(file, "# wr64 stall probe\n");
                std::fprintf(file, "# operation threshold %.3f ms, hitch threshold %.3f ms\n",
                    wr64StallProbeThresholdMs(), wr64StallProbeIntervalThresholdMs());
                std::fprintf(file, "# context %u samples within %.1f ms\n",
                    wr64StallProbeContextCount(), wr64StallProbeContextWindowMs());
                std::fprintf(file, "# columns: index  at_ms  thread  label  duration_ms  detail\n");
                std::fflush(file);
            }

            return file;
        }();
        return logFile;
    }

    // Writes one sample into the ring. Every probe calls this, however short it
    // was, so the ring is a complete recent history rather than a list of
    // exceptions. Cost is one relaxed fetch_add, six stores and one release store.
    inline void wr64StallProbeRecord(const char *label, double startMs, double durationMs, uint64_t detail) {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        WR64StallProbeRing &ring = wr64StallProbeRing();
        const uint64_t index = ring.cursor.fetch_add(1, std::memory_order_relaxed);
        WR64StallProbeSample &sample = ring.samples[index % WR64StallProbeRingCapacity];
        sample.published.store(0, std::memory_order_release);
        sample.startMs = startMs;
        sample.durationMs = durationMs;
        sample.detail = detail;
        sample.label = label;
        sample.threadName = wr64StallProbeThreadNameSlot();
        sample.threadId = wr64StallProbeThreadId();
        sample.published.store(index + 1, std::memory_order_release);
    }

    inline void wr64StallProbeReport(const char *label, double elapsedMs, uint64_t detail) {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        std::FILE *logFile = wr64StallProbeLogFile();

        static std::atomic<uint64_t> reportCounter(0);
        const uint64_t reportIndex = reportCounter.fetch_add(1, std::memory_order_relaxed);
        const double atMs = wr64StallProbeNowMs();
        const uint32_t threadId = wr64StallProbeThreadId();
        const char *threadName = wr64StallProbeThreadNameSlot();

        // fprintf on a FILE * locks internally, so concurrent reports from the present,
        // workload and render worker threads interleave by line rather than by character.
        if (logFile != nullptr) {
            std::fprintf(logFile, "#%-6llu %10.1f  t%-2u %-14s %-30s %8.3f ms  detail=%llu\n",
                static_cast<unsigned long long>(reportIndex), atMs, threadId, threadName, label,
                elapsedMs, static_cast<unsigned long long>(detail));
            std::fflush(logFile);
        }

        std::fprintf(stderr, "[wr64-stall] #%llu t%u %-30s %8.3f ms  detail=%llu\n",
            static_cast<unsigned long long>(reportIndex), threadId, label, elapsedMs,
            static_cast<unsigned long long>(detail));
        std::fflush(stderr);
    }

    // Prints the recent contents of the ring. Called after a hitch has already been
    // reported, so it is never on a hot path and does not need to be fast.
    inline void wr64StallProbeDumpContext(double hitchAtMs) {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        std::FILE *logFile = wr64StallProbeLogFile();
        if (logFile == nullptr) {
            return;
        }

        WR64StallProbeRing &ring = wr64StallProbeRing();
        const uint64_t end = ring.cursor.load(std::memory_order_acquire);
        const uint64_t requested = wr64StallProbeContextCount();
        const uint64_t span = (requested < WR64StallProbeRingCapacity) ? requested : WR64StallProbeRingCapacity;
        const uint64_t begin = (end > span) ? (end - span) : 0;
        const double earliest = hitchAtMs - wr64StallProbeContextWindowMs();

        std::fprintf(logFile, "   ---- context, the %llu samples before this hitch ----\n",
            static_cast<unsigned long long>(end - begin));

        uint64_t printed = 0;
        double busyMs = 0.0;
        for (uint64_t i = begin; i < end; i++) {
            const WR64StallProbeSample &sample = ring.samples[i % WR64StallProbeRingCapacity];
            if (sample.published.load(std::memory_order_acquire) != (i + 1)) {
                continue;
            }

            const double startMs = sample.startMs;
            const double durationMs = sample.durationMs;
            const uint64_t detail = sample.detail;
            const char *label = sample.label;
            const char *threadName = sample.threadName;
            const uint32_t threadId = sample.threadId;

            // Re-check after copying the payload out. If the slot was recycled while
            // this loop was reading it, the values above are a mix of two samples and
            // must not be printed.
            if (sample.published.load(std::memory_order_acquire) != (i + 1)) {
                continue;
            }

            if (startMs < earliest) {
                continue;
            }

            std::fprintf(logFile, "     %10.1f  -%6.1f ms  t%-2u %-14s %-30s %8.3f ms  detail=%llu\n",
                startMs, hitchAtMs - startMs, threadId, (threadName != nullptr) ? threadName : "unnamed",
                (label != nullptr) ? label : "unknown", durationMs,
                static_cast<unsigned long long>(detail));
            printed++;
            busyMs += durationMs;
        }

        if (printed == 0) {
            std::fprintf(logFile, "     nothing instrumented ran in the %.1f ms before this hitch.\n",
                wr64StallProbeContextWindowMs());
            std::fprintf(logFile, "     the cost is in code this probe does not watch yet.\n");
        }
        else {
            std::fprintf(logFile, "     %llu samples, %.3f ms of instrumented work in that window.\n",
                static_cast<unsigned long long>(printed), busyMs);
        }

        std::fprintf(logFile, "   ------------------------------------------------------\n");
        std::fflush(logFile);
    }

    // Times the enclosing scope. The detail value is free-form per site; it is
    // there to carry the count that explains the cost, such as how many textures a
    // batch actually uploaded. Every scope lands in the ring; only the slow ones
    // are also reported immediately.
    struct WR64StallProbe {
        const char *label = nullptr;
        uint64_t detail = 0;
        double startMs = 0.0;
        std::chrono::steady_clock::time_point start;
        bool active = false;

        explicit WR64StallProbe(const char *probeLabel, uint64_t probeDetail = 0) {
            active = wr64StallProbeEnabled();
            if (!active) {
                return;
            }

            label = probeLabel;
            detail = probeDetail;
            startMs = wr64StallProbeNowMs();
            start = std::chrono::steady_clock::now();
        }

        ~WR64StallProbe() {
            if (!active) {
                return;
            }

            const std::chrono::duration<double, std::milli> elapsed =
                std::chrono::steady_clock::now() - start;
            wr64StallProbeRecord(label, startMs, elapsed.count(), detail);
            if (elapsed.count() < wr64StallProbeThresholdMs()) {
                return;
            }

            wr64StallProbeReport(label, elapsed.count(), detail);
        }

        void setDetail(uint64_t value) {
            detail = value;
        }

        WR64StallProbe(const WR64StallProbe &) = delete;
        WR64StallProbe &operator=(const WR64StallProbe &) = delete;
    };

    // Same contract as WR64StallProbe, for sites on the draw call or present path.
    // It skips the ring entirely when the scope was quick, so a site that runs ten
    // thousand times a second costs one clock read and one compare and leaves no
    // trace, while the rare call that blocks on a contended mutex still lands in the
    // dump with its real duration.
    struct WR64StallProbeHot {
        const char *label = nullptr;
        uint64_t detail = 0;
        double startMs = 0.0;
        std::chrono::steady_clock::time_point start;
        bool active = false;

        explicit WR64StallProbeHot(const char *probeLabel, uint64_t probeDetail = 0) {
            active = wr64StallProbeEnabled();
            if (!active) {
                return;
            }

            label = probeLabel;
            detail = probeDetail;
            startMs = wr64StallProbeNowMs();
            start = std::chrono::steady_clock::now();
        }

        ~WR64StallProbeHot() {
            if (!active) {
                return;
            }

            const std::chrono::duration<double, std::milli> elapsed =
                std::chrono::steady_clock::now() - start;
            if (elapsed.count() < wr64StallProbeHotThresholdMs()) {
                return;
            }

            wr64StallProbeRecord(label, startMs, elapsed.count(), detail);
            if (elapsed.count() < wr64StallProbeThresholdMs()) {
                return;
            }

            wr64StallProbeReport(label, elapsed.count(), detail);
        }

        void setDetail(uint64_t value) {
            detail = value;
        }

        WR64StallProbeHot(const WR64StallProbeHot &) = delete;
        WR64StallProbeHot &operator=(const WR64StallProbeHot &) = delete;
    };

    // Same contract again, but the floor is given per site instead of coming from
    // the global hot threshold. Needed for the handful of places that are supposed
    // to block every single frame as part of normal operation: a vsync wait and a
    // pacing sleep both sit there for most of a frame period by design, so at the
    // 0.5 ms hot floor they would land in the ring 180 times a second and recycle
    // the whole 512 slot history in under three seconds, erasing exactly the
    // context a hitch dump exists to show. Give those sites a floor above their
    // normal cost and they stay silent until they misbehave.
    struct WR64StallProbeGate {
        const char *label = nullptr;
        uint64_t detail = 0;
        double floorMs = 0.0;
        double startMs = 0.0;
        std::chrono::steady_clock::time_point start;
        bool active = false;

        WR64StallProbeGate(const char *probeLabel, double probeFloorMs, uint64_t probeDetail = 0) {
            active = wr64StallProbeEnabled();
            if (!active) {
                return;
            }

            label = probeLabel;
            detail = probeDetail;

            // The floor the call site asked for, scaled by the run time knob so a
            // second pass can turn these sites up without a rebuild, and clamped so
            // it can never reach zero and start recording every call.
            const double scaled = probeFloorMs * wr64StallProbeGateScale();
            floorMs = (scaled > 0.05) ? scaled : 0.05;
            startMs = wr64StallProbeNowMs();
            start = std::chrono::steady_clock::now();
        }

        ~WR64StallProbeGate() {
            if (!active) {
                return;
            }

            const std::chrono::duration<double, std::milli> elapsed =
                std::chrono::steady_clock::now() - start;
            if (elapsed.count() < floorMs) {
                return;
            }

            wr64StallProbeRecord(label, startMs, elapsed.count(), detail);
            if (elapsed.count() < wr64StallProbeThresholdMs()) {
                return;
            }

            wr64StallProbeReport(label, elapsed.count(), detail);
        }

        void setDetail(uint64_t value) {
            detail = value;
        }

        WR64StallProbeGate(const WR64StallProbeGate &) = delete;
        WR64StallProbeGate &operator=(const WR64StallProbeGate &) = delete;
    };

    // Records something that happened without timing a scope: a cohort size, a
    // cache miss, a mode switch. Never reported on its own, but it shows up in the
    // context dump, which is where the cheap facts turn out to matter.
    inline void wr64StallProbeMarkEvent(const char *label, uint64_t detail) {
        if (!wr64StallProbeEnabled()) {
            return;
        }

        wr64StallProbeRecord(label, wr64StallProbeNowMs(), 0.0, detail);
    }

    // Reports the interval between successive calls when it runs long. Ground truth
    // for "a hitch happened at all": this is the frame the player actually lost. A
    // violation drags the recent ring out with it, so the line is never alone.
    inline void wr64StallProbeMarkInterval(const char *label) {
        if (!wr64StallProbeEnabled()) {
            return;
        }

        // Only ever called from the present thread, so a plain function local is
        // sufficient and avoids putting an atomic on the presentation path.
        static std::chrono::steady_clock::time_point last;
        static bool hasLast = false;
        static uint64_t intervalIndex = 0;

        const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        if (hasLast) {
            const std::chrono::duration<double, std::milli> elapsed = now - last;
            if (elapsed.count() >= wr64StallProbeIntervalThresholdMs()) {
                const double atMs = wr64StallProbeNowMs();
                wr64StallProbeReport(label, elapsed.count(), intervalIndex);
                wr64StallProbeDumpContext(atMs);
            }
        }

        last = now;
        hasLast = true;
        intervalIndex++;
    }
}
