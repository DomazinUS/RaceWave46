//
// WR64 HUD census, R3.
//
// MEASUREMENT ONLY. Nothing rendered changes. Dormant unless WR64_HUD_CENSUS
// names an output file.
//
// Why it exists
// -------------
// The HUD is authored inside an inset box and should reach the real corners of
// the window. Measured from five screenshots spanning three different HUD
// layouts - race with a banner, race with POWER UP, and stunt mode, which shares
// almost no elements with the other two - the glyphs land at the same margins
// every time:
//
//     left 26.2  top 21.8  right 23.6  bottom 23.8      (race, MAX POWER)
//     left 26.5  top 21.4  right 23.6  bottom 24.1      (race, POWER UP)
//     left 29.5  top 22.0  right 24.5  -                (stunt)
//
// So the HUD across every mode lives in roughly native (26,21)-(400,216) of a
// 424x240 frame. The intended correction scales an element's POSITION away from
// the frame centre and leaves its SIZE alone, so glyphs move to the corners
// without being stretched:
//
//     newCentre = frameCentre + (oldCentre - frameCentre) * k
//     kx = 212 / (212 - 26) = 1.140      ky = 120 / (120 - 21) = 1.212
//
// What has to be settled before writing that
// ------------------------------------------
// Which lever actually moves these glyphs. The existing edge trace only prints
// projections where usesViewport() is true - Perspective and Orthographic - so
// Rectangle projections never appear in it at all. If the HUD is texrects under
// Rectangle projections the lever is each call's rect; if it is triangles under
// an Orthographic projection the rect is meaningless and the lever is the
// projection's screen offset. Those are different edits and guessing between
// them is how this project has broken things before.
//
// This census records every draw call with its projection type, rect, triangle
// count, tile count and scissor, and flags whether its rect lies entirely inside
// the inset box. That answers which lever applies AND doubles as a dry run of
// the containment predicate: the rows flagged contained are exactly what the
// correction would move.
//
// R3 - texture identity
// ----------------------
// R2 recorded geometry only, and geometry turned out not to be a usable key: the
// applied HUD anchor moved the Watercraft Select slider, the .HAYAMI name plate,
// a course-presentation frame strip and the title logo, because those are
// texrects that happen to land in the same screen regions as HUD widgets. Screen
// position cannot tell a race from a menu.
//
// It also cannot tell one mode from another. SPEED sits at native x 345..377 in a
// championship race and around 280..310 in time trial, so a region that matches
// one misses the other and splits the widget from its digits.
//
// DrawCallTile carries tmemHashOrID plus the sampled dimensions, so this records
// the TEXTURE each draw samples. The HUD font atlas is not the texture a menu
// slider uses, and a widget keeps its texture across every mode. Keyed on
// (texture, region) instead of region alone, both failures should go away.
//
// R2 - why R1 produced nothing
// ----------------------------
// R1 wrote only from a static destructor, and its storage was ordinary function
// -local statics. Inside the record function the dumper static is constructed
// FIRST and the map and mutex are constructed later on that same call, so at
// exit they were destroyed BEFORE the dumper ran - which then locked a destroyed
// mutex and read a destroyed map. Nothing was written and nothing was printed.
// The frame-time probe survives the identical pattern only because its storage
// is a raw calloc pointer with a trivial destructor.
//
// Three changes, in order of how much they matter:
//   1. The map and mutex are leaked deliberately - allocated with new, never
//      destroyed - so there is no destruction-order hazard left to get wrong.
//   2. The file is rewritten every 32 new DISTINCT rows, not only at exit.
//      Distinct draws are bounded in the hundreds, so that is a handful of
//      rewrites across a whole session, and the file survives a hard exit.
//   3. One line on the first recorded row, so the terminal says immediately
//      whether the instrument is live rather than at the end.
//
//   WR64_HUD_CENSUS   output CSV path; dormant unless set
//   WR64_HUD_INSET    inset box override, "left,top,right,bottom" in native
//                     pixels; default "26,21,400,216"
//

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <mutex>
#include <unordered_map>
#include <vector>

#include "rt64_common.h"

namespace RT64 {
    inline const char *wr64HudCensusPath() {
        static const char *path = std::getenv("WR64_HUD_CENSUS");
        return path;
    }

    inline bool wr64HudCensusArmed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool armed = [] {
            const char *p = wr64HudCensusPath();
            return (p != nullptr) && (p[0] != '\0') && (p[0] != '0');
        }();
        return armed;
    }

    struct Wr64HudInset {
        int32_t left = 26;
        int32_t top = 21;
        int32_t right = 400;
        int32_t bottom = 216;
    };

    inline const Wr64HudInset &wr64HudInset() {
        static const Wr64HudInset inset = [] {
            Wr64HudInset box;
            const char *v = std::getenv("WR64_HUD_INSET");
            if (v != nullptr) {
                int l = 0, t = 0, r = 0, b = 0;
                if (std::sscanf(v, "%d,%d,%d,%d", &l, &t, &r, &b) == 4) {
                    box.left = l; box.top = t; box.right = r; box.bottom = b;
                }
            }
            return box;
        }();
        return inset;
    }

    struct Wr64HudCensusRow {
        int32_t projType = 0;
        int32_t rectUlx = 0, rectUly = 0, rectLrx = 0, rectLry = 0;
        int32_t sciUlx = 0, sciUly = 0, sciLrx = 0, sciLry = 0;
        uint32_t triangleCount = 0;
        uint32_t tileCount = 0;
        uint32_t hasRect = 0;
        uint32_t contained = 0;
        uint64_t tmemHash = 0;
        uint32_t sampleWidth = 0;
        uint32_t sampleHeight = 0;
        uint64_t seen = 0;
    };

    // Deliberately leaked. These outlive every static destructor, so the exit
    // dump cannot touch destroyed storage - which is exactly what R1 did.
    inline std::mutex &wr64HudCensusMutex() {
        static std::mutex *m = new std::mutex();
        return *m;
    }

    inline std::unordered_map<uint64_t, Wr64HudCensusRow> &wr64HudCensusMap() {
        static std::unordered_map<uint64_t, Wr64HudCensusRow> *map =
            new std::unordered_map<uint64_t, Wr64HudCensusRow>();
        return *map;
    }

    // Caller holds the mutex.
    inline void wr64HudCensusWriteLocked(bool announce) {
        auto &map = wr64HudCensusMap();
        if (map.empty()) {
            return;
        }

        std::FILE *f = std::fopen(wr64HudCensusPath(), "wb");
        if (f == nullptr) {
            return;
        }

        std::vector<Wr64HudCensusRow> rows;
        rows.reserve(map.size());
        for (const auto &it : map) {
            rows.push_back(it.second);
        }

        // Contained rows first, then by position, so the rows the correction
        // would move are the ones at the top of the file.
        std::sort(rows.begin(), rows.end(), [](const Wr64HudCensusRow &a, const Wr64HudCensusRow &b) {
            if (a.contained != b.contained) { return a.contained > b.contained; }
            if (a.rectUly != b.rectUly) { return a.rectUly < b.rectUly; }
            return a.rectUlx < b.rectUlx;
        });

        const Wr64HudInset &box = wr64HudInset();
        std::fprintf(f, "# inset box (%d,%d)-(%d,%d)\n", box.left, box.top, box.right, box.bottom);
        std::fprintf(f,
            "contained,proj_type,has_rect,tri_count,tile_count,"
            "rect_ulx,rect_uly,rect_lrx,rect_lry,"
            "sci_ulx,sci_uly,sci_lrx,sci_lry,tmem_hash,sample_w,sample_h,seen\n");

        uint64_t containedRows = 0;
        for (const Wr64HudCensusRow &r : rows) {
            containedRows += (r.contained != 0) ? 1 : 0;
            std::fprintf(f, "%u,%d,%u,%u,%u,%g,%g,%g,%g,%g,%g,%g,%g,%016llX,%u,%u,%llu\n",
                r.contained, r.projType, r.hasRect, r.triangleCount, r.tileCount,
                r.rectUlx / 4.0, r.rectUly / 4.0, r.rectLrx / 4.0, r.rectLry / 4.0,
                r.sciUlx / 4.0, r.sciUly / 4.0, r.sciLrx / 4.0, r.sciLry / 4.0,
                static_cast<unsigned long long>(r.tmemHash), r.sampleWidth, r.sampleHeight,
                static_cast<unsigned long long>(r.seen));
        }

        std::fclose(f);

        if (announce) {
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[hudcensus] %zu distinct draws, %llu inside the inset -> %s\n",
                rows.size(), static_cast<unsigned long long>(containedRows), wr64HudCensusPath()); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }
    }

    inline void wr64HudCensusDump() {
        if (!wr64HudCensusArmed()) {
            return;
        }

        std::lock_guard<std::mutex> lock(wr64HudCensusMutex());
        wr64HudCensusWriteLocked(true);
    }

    struct Wr64HudCensusDumper {
        ~Wr64HudCensusDumper() { wr64HudCensusDump(); }
    };

    // Call once per draw call, with the call's AUTHORED rect and scissor before
    // any correction has touched them.
    inline void wr64HudCensusRecord(
        int32_t projType,
        const FixedRect &rect,
        const FixedRect &scissorRect,
        uint32_t triangleCount,
        uint32_t tileCount,
        uint64_t tmemHash,
        uint32_t sampleWidth,
        uint32_t sampleHeight)
    {
        if (!wr64HudCensusArmed()) {
            return;
        }

        // Force the storage into existence before the exit dumper is registered.
        // Belt and braces - the storage is leaked, so the order no longer matters.
        std::mutex &mutex = wr64HudCensusMutex();
        auto &map = wr64HudCensusMap();

        static Wr64HudCensusDumper dumper;
        (void)dumper;

        const Wr64HudInset &box = wr64HudInset();
        const bool hasRect = !rect.isNull();

        // Quarter-pixel units throughout, matching FixedRect.
        const bool contained = hasRect &&
            (rect.ulx >= box.left * 4) && (rect.uly >= box.top * 4) &&
            (rect.lrx <= box.right * 4) && (rect.lry <= box.bottom * 4);

        uint64_t h = 1469598103934665603ull;
        auto mix = [&h](uint64_t v) { h ^= v; h *= 1099511628211ull; };
        mix(uint64_t(projType));
        mix(uint64_t(rect.ulx)); mix(uint64_t(rect.uly));
        mix(uint64_t(rect.lrx)); mix(uint64_t(rect.lry));
        mix(uint64_t(scissorRect.ulx)); mix(uint64_t(scissorRect.uly));
        mix(uint64_t(scissorRect.lrx)); mix(uint64_t(scissorRect.lry));
        mix(uint64_t(triangleCount)); mix(uint64_t(tileCount));
        mix(tmemHash); mix(uint64_t(sampleWidth)); mix(uint64_t(sampleHeight));

        std::lock_guard<std::mutex> lock(mutex);
        auto it = map.find(h);
        if (it != map.end()) {
            it->second.seen++;
            return;
        }

        // A runaway cap, well above any real session's distinct draw count.
        if (map.size() >= 65536) {
            return;
        }

        Wr64HudCensusRow row;
        row.projType = projType;
        row.rectUlx = rect.ulx; row.rectUly = rect.uly;
        row.rectLrx = rect.lrx; row.rectLry = rect.lry;
        row.sciUlx = scissorRect.ulx; row.sciUly = scissorRect.uly;
        row.sciLrx = scissorRect.lrx; row.sciLry = scissorRect.lry;
        row.triangleCount = triangleCount;
        row.tileCount = tileCount;
        row.hasRect = hasRect ? 1u : 0u;
        row.contained = contained ? 1u : 0u;
        row.tmemHash = tmemHash;
        row.sampleWidth = sampleWidth;
        row.sampleHeight = sampleHeight;
        row.seen = 1;
        map.emplace(h, row);

        if (map.size() == 1) {
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[hudcensus] armed, recording -> %s\n", wr64HudCensusPath()); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        // Write through periodically so the file exists during the run, not only
        // if the exit path behaves. Distinct draws are bounded in the hundreds.
        if ((map.size() % 32) == 0) {
            wr64HudCensusWriteLocked(false);
        }
    }
};
