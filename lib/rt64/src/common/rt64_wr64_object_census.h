// WR64 draw census associates interpolation decisions with rendered objects.
// Join submission_frame/world_index to the transform-gate trace; the renderer
// adds texture and triangle metadata unavailable to the transform matcher.
// Record the first draw for every transform and join offline, avoiding shared
// cross-thread state between pipelined frames. WR64_OBJECT_CENSUS optionally
// names the CSV; flush every 2048 rows rather than relying on process shutdown.

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <deque>
#include <mutex>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

namespace RT64 {
    inline const char *wr64ObjectCensusPath() {
        static const char *path = std::getenv("WR64_OBJECT_CENSUS");
        return path;
    }

    inline bool wr64ObjectCensusArmed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool armed = [] {
            const char *p = wr64ObjectCensusPath();
            const bool on = (p != nullptr) && (p[0] != '\0') && (p[0] != '0');
            if (on) {
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[objectcensus] armed -> %s\n", p); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            }
            return on;
        }();
        return armed;
    }

    struct Wr64ObjectCensusRow {
        uint64_t frame;
        uint64_t texture;
        uint32_t worldIndex;
        uint32_t triangles;
        uint32_t projType;
        uint32_t combinerH, combinerL;
        uint32_t otherModeH, otherModeL;
        // R2. WHERE the thing is, which the first version did not record and
        // could not answer the question that matters for a 3D model.
        //
        // The fish were sprites in a contiguous block, so "which one is this"
        // came from position within the block. A dolphin or a helicopter is the
        // GANTRY's shape instead: several draws sharing one world transform,
        // named by rank among the claimed transforms. Rank only works if object
        // #0 this frame is the same physical object as #0 last frame - and
        // without a position there is no way to check that. Every complex model
        // screened as "slots churn", which is a non-answer, not a verdict.
        //
        // With translation recorded, the renderer's rank pairing can be compared
        // against the true nearest-neighbour pairing between consecutive frames.
        // Where they disagree IS the mis-pairing, measured rather than inferred.
        float x, y, z;
    };

    inline std::mutex &wr64ObjectCensusMutex() {
        static std::mutex m;
        return m;
    }

    // A hard stop, so a long session cannot fill the disk. If it is ever reached
    // the file says so - a census that silently stopped recording would read as
    // "the object was never drawn", which is exactly the wrong conclusion.
    //
    // R2 raises it from 500,000. Measured on a real survey: 106 rows per frame,
    // so 500,000 was 4,710 frames - about 78 SECONDS of racing. That was sized
    // for a single-course investigation and it silently became the binding
    // constraint the moment the job became "screen seven courses". It announced
    // itself, which is the only reason the run was not quietly wrong.
    //
    // 2,000,000 is roughly five and a half minutes, or two to three courses in
    // one sitting, at about 170 MB. Prefer one course per run anyway: the file
    // stays small and the course attribution is exact instead of inferred.
    static constexpr size_t Wr64ObjectCensusMaxRows = 2000000;

    // The duplicate filter is WINDOWED, not unbounded. R1 kept one set entry for
    // every (frame, transform) ever seen, so at the raised cap it would have held
    // two million pairs - well over a hundred megabytes of set nodes, inside the
    // game's own process, purely to suppress rows.
    //
    // Frames are pipelined but not by much, so a window of the last few frames
    // catches every real duplicate. If interleaving ever exceeded the window the
    // only consequence is a repeated row, which any reader can drop on
    // (submission_frame, world_index) - whereas running the machine out of memory
    // mid-session costs a play session.
    static constexpr size_t Wr64ObjectCensusFrameWindow = 16;

    struct Wr64ObjectCensusState {
        std::FILE *file = nullptr;
        std::deque<std::pair<uint64_t, std::unordered_set<uint32_t>>> seen;
        std::vector<Wr64ObjectCensusRow> pending;
        size_t written = 0;
        bool capped = false;
        bool opened = false;
    };

    inline Wr64ObjectCensusState &wr64ObjectCensusState() {
        static Wr64ObjectCensusState s;
        return s;
    }

    inline void wr64ObjectCensusFlushLocked() {
        Wr64ObjectCensusState &s = wr64ObjectCensusState();
        if (s.file == nullptr) {
            return;
        }

        for (const Wr64ObjectCensusRow &r : s.pending) {
            std::fprintf(s.file, "%llu,%u,%016llX,%u,%u,%08X,%08X,%08X,%08X,%.3f,%.3f,%.3f\n",
                static_cast<unsigned long long>(r.frame),
                r.worldIndex,
                static_cast<unsigned long long>(r.texture),
                r.triangles, r.projType,
                r.combinerH, r.combinerL, r.otherModeH, r.otherModeL,
                r.x, r.y, r.z);
        }

        s.pending.clear();
        std::fflush(s.file);
    }

    struct Wr64ObjectCensusCloser {
        ~Wr64ObjectCensusCloser() {
            std::lock_guard<std::mutex> lock(wr64ObjectCensusMutex());
            wr64ObjectCensusFlushLocked();
        }
    };

    inline void wr64ObjectCensusRecord(uint64_t frame, uint32_t worldIndex, uint64_t texture,
        uint32_t triangles, uint32_t projType,
        uint32_t combinerH, uint32_t combinerL, uint32_t otherModeH, uint32_t otherModeL,
        float x, float y, float z)
    {
        if (!wr64ObjectCensusArmed()) {
            return;
        }

        static Wr64ObjectCensusCloser closer;
        (void)closer;

        std::lock_guard<std::mutex> lock(wr64ObjectCensusMutex());
        Wr64ObjectCensusState &s = wr64ObjectCensusState();

        if (!s.opened) {
            s.opened = true;
            s.file = std::fopen(wr64ObjectCensusPath(), "wb");
            if (s.file != nullptr) {
                std::fprintf(s.file,
                    "submission_frame,world_index,texture,triangles,proj_type,"
                    "combiner_h,combiner_l,othermode_h,othermode_l,x,y,z\n");
                std::fflush(s.file);
            }
            else {
                std::fprintf(stderr, "[objectcensus] could not open %s for writing\n",
                    wr64ObjectCensusPath());
                std::fflush(stderr);
            }
        }

        if (s.file == nullptr) {
            return;
        }

        if (s.written >= Wr64ObjectCensusMaxRows) {
            if (!s.capped) {
                s.capped = true;
                std::fprintf(s.file, "# CAPPED at %zu rows - recording stopped, later frames are ABSENT\n",
                    Wr64ObjectCensusMaxRows);
                std::fflush(s.file);
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                    "[objectcensus] CAPPED at %zu rows; later frames are NOT recorded.\n"
                    "[objectcensus] That is about %zu frames of racing. Run one course at a\n"
                    "[objectcensus] time (RUN-SPRITE-SURVEY-R1.ps1 -Course <name>) rather than\n"
                    "[objectcensus] several in one sitting.\n",
                    Wr64ObjectCensusMaxRows, Wr64ObjectCensusMaxRows / 106); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            }
            return;
        }

        // One row per (frame, transform). The first draw wins: a transform can
        // back several draws and they all share its motion.
        auto it = s.seen.end();
        for (auto scan = s.seen.begin(); scan != s.seen.end(); ++scan) {
            if (scan->first == frame) { it = scan; break; }
        }
        if (it == s.seen.end()) {
            s.seen.emplace_back(frame, std::unordered_set<uint32_t>());
            it = std::prev(s.seen.end());
            while (s.seen.size() > Wr64ObjectCensusFrameWindow) {
                s.seen.pop_front();
                it = std::prev(s.seen.end());
            }
        }
        if (!it->second.insert(worldIndex).second) {
            return;
        }

        s.pending.push_back(Wr64ObjectCensusRow{
            frame, texture, worldIndex, triangles, projType,
            combinerH, combinerL, otherModeH, otherModeL, x, y, z });
        s.written++;

        if (s.pending.size() >= 2048) {
            wr64ObjectCensusFlushLocked();
        }
    }
};
