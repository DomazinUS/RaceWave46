//
// WR64 frame-time probe.
//
// MEASUREMENT ONLY, and deliberately cheap enough to leave on while judging
// fluidity: one atomic increment and one store into a preallocated array per
// presented frame. No lock, no allocation, no I/O on the hot path. The buffer is
// written out once, at process exit.
//
// That last part matters. The lerp-gate trace takes a mutex on every transform
// evaluation and flushes to disk on every gate row, inside the function RT64's
// own comment describes as "the thread every interpolated frame waits behind" -
// so that instrument cannot be used to judge smoothness. This one can.
//
// Why it exists
// -------------
// The repaired AUTO interpolation test changes which objects interpolate, and
// the question is whether it costs fluidity. The honest way to answer that is
// A/B on the SAME binary: WR64_LERPGATE_FIX=0 restores the original test and
// WR64_CAMCUT_SUPPRESS=0 the original cut behaviour, so both runs differ only in
// the thing being tested.
//
// Read the result with care. If both configurations come back with the same
// present interval distribution, then frame delivery is identical and any felt
// difference is not frame timing - it is either the changed look of objects that
// used to snap and now glide, or it is nothing. Presentation was already
// measured metronomic on the stable build: median 5.551 ms, largest gap in 21 s
// 1.12x median. A real regression would have to show up against that.
//
//   WR64_FRAMETIME_PROBE   output CSV path; dormant unless set
//

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <atomic>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

namespace RT64 {
    // 4M samples is over six hours at 180 Hz; the array is 32 MB and is only
    // allocated when the probe is armed.
    static constexpr size_t Wr64FrameTimeCapacity = 4u * 1024u * 1024u;

    inline const char *wr64FrameTimePath() {
        static const char *path = std::getenv("WR64_FRAMETIME_PROBE");
        return path;
    }

    inline bool wr64FrameTimeArmed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool armed = [] {
            const char *p = wr64FrameTimePath();
            return (p != nullptr) && (p[0] != '\0') && (p[0] != '0');
        }();
        return armed;
    }

    inline uint64_t *wr64FrameTimeBuffer() {
        static uint64_t *buffer = wr64FrameTimeArmed()
            ? static_cast<uint64_t *>(std::calloc(Wr64FrameTimeCapacity, sizeof(uint64_t)))
            : nullptr;
        return buffer;
    }

    inline std::atomic<size_t> &wr64FrameTimeCount() {
        static std::atomic<size_t> count{0};
        return count;
    }

    inline void wr64FrameTimeDump() {
        if (!wr64FrameTimeArmed()) {
            return;
        }

        uint64_t *buffer = wr64FrameTimeBuffer();
        const size_t count = std::min(wr64FrameTimeCount().load(std::memory_order_acquire), Wr64FrameTimeCapacity);
        if ((buffer == nullptr) || (count == 0)) {
            return;
        }

        std::FILE *f = std::fopen(wr64FrameTimePath(), "wb");
        if (f == nullptr) {
            return;
        }

        std::fprintf(f, "index,timestamp_ns,interval_ms\n");
        for (size_t i = 0; i < count; i++) {
            const double interval = (i > 0) ? double(buffer[i] - buffer[i - 1]) / 1e6 : 0.0;
            std::fprintf(f, "%zu,%llu,%.6f\n", i, static_cast<unsigned long long>(buffer[i]), interval);
        }

        std::fclose(f);
        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[frametime] %zu presented frames -> %s\n", count, wr64FrameTimePath()); }
        { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
    }

    struct Wr64FrameTimeDumper {
        ~Wr64FrameTimeDumper() { wr64FrameTimeDump(); }
    };

    inline void wr64FrameTimeMark() {
        if (!wr64FrameTimeArmed()) {
            return;
        }

        // Registers the exit dump the first time a frame is marked.
        static Wr64FrameTimeDumper dumper;
        (void)dumper;

        uint64_t *buffer = wr64FrameTimeBuffer();
        if (buffer == nullptr) {
            return;
        }

        const size_t index = wr64FrameTimeCount().fetch_add(1, std::memory_order_acq_rel);
        if (index < Wr64FrameTimeCapacity) {
            buffer[index] = uint64_t(std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::steady_clock::now().time_since_epoch()).count());
        }
    }
};
