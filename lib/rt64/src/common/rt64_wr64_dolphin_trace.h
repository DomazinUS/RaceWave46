// WR64 dolphin identity and continuity diagnostics.
// WR64_DOLPHIN_TRACE optionally records every stamper exit path, keyed by frame
// and matrix address, with position, record age, and the resulting identity state.
//
// The runtime capture wr64-dolphin-decisions-sunset-bay-20260731_144200.csv separates
// normal steps below 100 units from relocations above 200. The 150-unit guard
// detects the relocation; retaining the ID while skipping interpolation prevents
// the following frame from falling back to heuristic pairing. Expected successful
// verdicts are stamped or stamped_interp_skipped.
// Flush each row so a single-frame event survives an abnormal process exit.

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <mutex>

namespace RT64 {
    inline const char *wr64DolphinTracePath() {
        static const char *path = std::getenv("WR64_DOLPHIN_TRACE");
        return path;
    }

    inline bool wr64DolphinTraceArmed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool armed = [] {
            const char *p = wr64DolphinTracePath();
            const bool on = (p != nullptr) && (p[0] != '\0') && (p[0] != '0');
            if (on) {
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[dolphintrace] armed -> %s\n", p); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            }
            return on;
        }();
        return armed;
    }

    // The verdicts, one per exit path in the stamper. Keep these in the same
    // order as the branches so a reader can follow the function from the log.
    enum Wr64DolphinVerdict : uint32_t {
        Wr64DolphinVerdictStamped = 0,        // named by address, interpolation forced on
        Wr64DolphinVerdictNoId = 1,           // address outside segment 6
        Wr64DolphinVerdictCollision = 2,      // another transform already took this id
        // Slot 3 was R2's Wr64DolphinVerdictMoved: "failed the continuity test,
        // identity withdrawn, transform handed back to the heuristic matcher".
        // R4 does not withdraw identities - see the R4 block in the stamper - so
        // the branch survives with the opposite outcome: the transform IS named,
        // and the INTERPOLATION is what gets dropped. Same slot, new meaning, and
        // the CSV says which because the string changed with it.
        Wr64DolphinVerdictStampedSkip = 3,    // named, position/rotation interpolation suppressed
        Wr64DolphinVerdictBadGroup = 4,       // transform group index out of range
    };

    inline const char *wr64DolphinVerdictName(uint32_t v) {
        switch (v) {
            case Wr64DolphinVerdictStamped:     return "stamped";
            case Wr64DolphinVerdictNoId:        return "no_id_outside_segment6";
            case Wr64DolphinVerdictCollision:   return "id_collision";
            case Wr64DolphinVerdictStampedSkip: return "stamped_interp_skipped";
            case Wr64DolphinVerdictBadGroup:    return "bad_group_index";
        }
        return "unknown";
    }

    struct Wr64DolphinTraceRow {
        uint64_t frame;
        uint64_t prevFrame;      // 0 when this address had no record
        uint32_t transform;
        uint32_t segAddress;
        uint32_t matrixId;
        uint32_t verdict;
        uint32_t hadRecord;      // 0 = first sighting of this address
        uint32_t ageFrames;      // frame - prevFrame, 0 when no record
        uint32_t withinWindow;   // did the age qualify the step for comparison
        float step;              // distance from the recorded position
        float x, y, z;
        uint32_t stampCallSeq;   // how many times the stamper has run, ever
    };

    inline std::mutex &wr64DolphinTraceMutex() {
        static std::mutex *m = new std::mutex();
        return *m;
    }

    struct Wr64DolphinTraceState {
        std::FILE *file = nullptr;
        bool opened = false;
        size_t written = 0;
    };

    // Leaked on purpose, same reason as the matrix slot recorder: anything that
    // might be touched during teardown must outlive teardown.
    inline Wr64DolphinTraceState &wr64DolphinTraceState() {
        static Wr64DolphinTraceState *s = new Wr64DolphinTraceState();
        return *s;
    }

    static constexpr size_t Wr64DolphinTraceMaxRows = 2000000;

    inline void wr64DolphinTraceRecord(uint64_t frame, uint32_t transform,
        uint32_t segAddress, uint32_t matrixId, uint32_t verdict,
        bool hadRecord, uint64_t prevFrame, uint32_t ageFrames, bool withinWindow,
        float step, float x, float y, float z, uint32_t stampCallSeq)
    {
        if (!wr64DolphinTraceArmed()) {
            return;
        }

        std::lock_guard<std::mutex> lock(wr64DolphinTraceMutex());
        Wr64DolphinTraceState &s = wr64DolphinTraceState();

        if (!s.opened) {
            s.opened = true;
            s.file = std::fopen(wr64DolphinTracePath(), "wb");
            if (s.file != nullptr) {
                std::fprintf(s.file,
                    "submission_frame,transform,seg_addr,matrix_id,verdict,"
                    "had_record,prev_frame,age_frames,within_window,"
                    "step,x,y,z,stamp_call_seq\n");
                std::fflush(s.file);
            }
            else {
                std::fprintf(stderr, "[dolphintrace] could not open %s for writing\n",
                    wr64DolphinTracePath());
                std::fflush(stderr);
            }
        }

        if ((s.file == nullptr) || (s.written >= Wr64DolphinTraceMaxRows)) {
            return;
        }

        std::fprintf(s.file,
            "%llu,%u,%08X,%08X,%s,%u,%llu,%u,%u,%.3f,%.3f,%.3f,%.3f,%u\n",
            static_cast<unsigned long long>(frame),
            transform, segAddress, matrixId,
            wr64DolphinVerdictName(verdict),
            hadRecord ? 1u : 0u,
            static_cast<unsigned long long>(prevFrame),
            ageFrames, withinWindow ? 1u : 0u,
            step, x, y, z, stampCallSeq);
        std::fflush(s.file);
        s.written++;
    }
};
