// WR64 screen-rectangle diagnostics, enabled by WR64_RECT_TRACK.
// Watch the celestial and instruction texture families and record native/drawn
// rectangles, texture steps, color, render state, and per-projection call order.
// These values expose count changes, edge clamping, and discontinuities without
// modifying HUD or sky draws.
//
// The initial sun watch list comes from Sunset Bay Composer capture 2/frame 2962:
// 8A399FACE63FE583 (glow), 329E604758F9E8BC (disk), and B82E909F647A31AD (flares).
// Names are diagnostic labels inferred from color, not additional claim criteria.
// Call order distinguishes flares sharing a texture. Primitive alpha and texture
// steps are recorded because geometry alone does not explain clipped edge states.

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include "rt64_wr64_celestial_identity.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <deque>
#include <mutex>
#include <set>
#include <tuple>
#include <vector>

namespace RT64 {
    struct Wr64RectWatch {
        uint64_t texture;
        const char *family;
    };

    inline const std::vector<Wr64RectWatch> &wr64RectWatchList() {
        static const std::vector<Wr64RectWatch> list = {
            { 0x8A399FACE63FE583ULL, "sun_glow" },
            { 0x329E604758F9E8BCULL, "sun_disk" },
            { 0xB82E909F647A31ADULL, "sun_flare" },
            // Dolphin Park disk - one rect there, same flare texture as
            // Sunset Bay so the flares needed nothing.
            { 0x79185A8F164D1366ULL, "sun_disk_dp" },
            // Twilight City stars share one texture (Composer captures 12-18, 2026-08-04).
            // The moon reuses the Sunset Bay disk texture and its diagnostic family label.
            { 0xB81BF5D3B4FA6341ULL, "tc_star" },
            // Dolphin Park rolling instruction text - one rect, scrolling.
            { 0xFF7EE0806FE2A6B6ULL, "dp_text" },
            // The 2026-08-04 Composer sweep identified baked message textures with shared
            // render state. Keep this deduplicated watch list equal to the claim list in
            // rt64_wr64_celestial_identity.h.
            { 0x3D50564003C7B071ULL, "dp_text" },
            { 0xEF5F5B407FE5A4FEULL, "dp_text" },
            { 0xDFCE6E2C8E3DBB34ULL, "dp_text" },
            { 0x4F716395385841D5ULL, "dp_text" },
            { 0x1192FD217989EFC0ULL, "dp_text" },
            { 0xC43AC3E146A0F40EULL, "dp_text" },
            { 0xD7D5A9EB06E1BE83ULL, "dp_text" },
            { 0x561A29BFDE8C4A5EULL, "dp_text" },
            { 0x14B48652198DEE3CULL, "dp_text" },
            { 0xE40AAE5624E208B4ULL, "dp_text" },
            { 0xE7F244688ABE4C89ULL, "dp_text" },
            { 0x3C7197C83D20CDA5ULL, "dp_text" },
            { 0xE34CC53C275FDAC7ULL, "dp_text" },
            { 0xB20380CC72D2B86FULL, "dp_text" },
            { 0x2735E5049B76C5D5ULL, "dp_text" },
            { 0xF363BB7BC58CD429ULL, "dp_text" },
            { 0x03D0BADBC82D03BBULL, "dp_text" },
            { 0x38477FB1A0E51891ULL, "dp_text" },
            { 0x540DDC6493485F20ULL, "dp_text" },
            { 0x18B319D609761603ULL, "dp_text" },
            { 0xB51F7A8C26314617ULL, "dp_text" },
            { 0x4F6ADBB5B3AC452DULL, "dp_text" },
            { 0xFC81EE483D5B5767ULL, "dp_text" },
            { 0x5850E75F4B001927ULL, "dp_text" },
            { 0xF13236A2045F35BEULL, "dp_text" },
            { 0x70C20EAF2073F236ULL, "dp_text" },
            // Additional message identified in the 2026-08-05 capture.
            { 0x5662E4CD1EE68825ULL, "dp_text" },
        };
        return list;
    }

    inline const char *wr64RectWatchFamily(uint64_t texture) {
        for (const Wr64RectWatch &w : wr64RectWatchList()) {
            if (w.texture == texture) {
                return w.family;
            }
        }
        return nullptr;
    }

    inline const char *wr64RectTrackPath() {
        static const char *path = std::getenv("WR64_RECT_TRACK");
        return path;
    }

    inline bool wr64RectTrackArmed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool armed = [] {
            const char *p = wr64RectTrackPath();
            return (p != nullptr) && (p[0] != '\0') && (p[0] != '0');
        }();
        return armed;
    }

    struct Wr64RectTrackState {
        std::FILE *file = nullptr;
        bool opened = false;
        size_t written = 0;
        bool capped = false;
        // R6: one row per (frame, fbPair, proj, call, DRAWN STATE). The
        // authored rect is identical on every output frame of a tick, but
        // the DRAWN rect - the celestial blend - is not, and whether it
        // actually changes on screen is precisely the question this round
        // exists to answer. A drawn rect that glides writes up to nine rows
        // per tick; one that steps writes exactly one. The row count IS the
        // verdict, the same trick the matrix track has used since its R3.
        std::deque<std::pair<uint64_t, std::set<std::tuple<uint32_t, uint32_t, uint32_t, uint64_t>>>> seen;
    };

    inline std::mutex &wr64RectTrackMutex() {
        static std::mutex m;
        return m;
    }

    inline Wr64RectTrackState &wr64RectTrackState() {
        static Wr64RectTrackState s;
        return s;
    }

    static constexpr size_t Wr64RectTrackMaxRows = 2000000;
    static constexpr size_t Wr64RectTrackFrameWindow = 8;

    // Written DURING the run, flushed every row batch. Relying on a clean exit
    // has cost this project a play session twice; a recorder never does.
    inline void wr64RectTrackRecord(
        uint64_t frame, uint32_t fbPairIndex, uint32_t projIndex, uint32_t callIndex,
        uint64_t texture,
        int32_t ulx, int32_t uly, int32_t lrx, int32_t lry,
        int32_t dsdx, int32_t dtdy,
        uint32_t combinerH, uint32_t combinerL,
        uint32_t otherModeH, uint32_t otherModeL,
        float primR, float primG, float primB, float primA,
        uint32_t lerpFound,
        int32_t lerpUlx, int32_t lerpUly, int32_t lerpLrx, int32_t lerpLry,
        float u1, float v1, float u2, float v2,
        int32_t sciUlx, int32_t sciUly, int32_t sciLrx, int32_t sciLry)
    {
        if (!wr64RectTrackArmed()) {
            return;
        }

        const char *family = wr64RectWatchFamily(texture);
        if (family == nullptr) {
            // R7: any unlisted texture carrying the measured DP message
            // fingerprint records as dp_text - the recorder must see the
            // messages the hash sweep missed, or the next one costs another
            // play session. Same test the claim uses.
            if (wr64CelestialDpTextState(combinerH, combinerL, otherModeH, otherModeL, uly)) {
                family = "dp_text";
            }
            // The four stacked glyph strips use their own family label so diagnostics
            // distinguish scrolling letters from the message box beneath them.
            else if (wr64CelestialDpStripState(combinerH, combinerL, otherModeH, otherModeL, uly)) {
                family = "dp_strip";
            }
            else {
                return;
            }
        }

        std::lock_guard<std::mutex> lock(wr64RectTrackMutex());
        Wr64RectTrackState &s = wr64RectTrackState();

        if (!s.opened) {
            s.opened = true;
            s.file = std::fopen(wr64RectTrackPath(), "wb");
            if (s.file != nullptr) {
                // Rect coordinates are the NATIVE quarter-pixel values the game
                // submitted, before any composer, anchor or scaling adjustment.
                // The question is what the GAME does per tick; what the renderer
                // does with it afterwards is downstream of the fix.
                std::fprintf(s.file,
                    "submission_frame,fbpair,proj,call,texture,family,"
                    "ulx,uly,lrx,lry,dsdx,dtdy,combiner_h,combiner_l,"
                    "othermode_h,othermode_l,prim_r,prim_g,prim_b,prim_a,"
                    "lerp_found,lerp_ulx,lerp_uly,lerp_lrx,lerp_lry,"
                    "u1,v1,u2,v2,sci_ulx,sci_uly,sci_lrx,sci_lry\n");
                std::fflush(s.file);
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[recttrack] armed -> %s\n", wr64RectTrackPath()); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            }
            else {
                std::fprintf(stderr, "[recttrack] could not open %s\n", wr64RectTrackPath());
                std::fflush(stderr);
            }
        }
        if (s.file == nullptr) {
            return;
        }

        if (s.written >= Wr64RectTrackMaxRows) {
            if (!s.capped) {
                s.capped = true;
                std::fprintf(s.file, "# CAPPED at %zu rows\n", Wr64RectTrackMaxRows);
                std::fflush(s.file);
            }
            return;
        }

        auto it = s.seen.end();
        for (auto scan = s.seen.begin(); scan != s.seen.end(); ++scan) {
            if (scan->first == frame) { it = scan; break; }
        }
        if (it == s.seen.end()) {
            s.seen.emplace_back(frame, std::set<std::tuple<uint32_t, uint32_t, uint32_t, uint64_t>>());
            it = std::prev(s.seen.end());
            while (s.seen.size() > Wr64RectTrackFrameWindow) {
                s.seen.pop_front();
                it = std::prev(s.seen.end());
            }
        }
        // The drawn state folded into the key - distinct drawn rects on one
        // tick each get their own row; identical ones dedupe as before.
        uint64_t drawnHash = 1469598103934665603ULL;
        for (int32_t v : { lerpUlx, lerpUly, lerpLrx, lerpLry, int32_t(lerpFound),
                           sciUlx, sciUly, sciLrx, sciLry }) {
            drawnHash = (drawnHash ^ uint64_t(uint32_t(v))) * 1099511628211ULL;
        }
        if (!it->second.insert(std::make_tuple(fbPairIndex, projIndex, callIndex, drawnHash)).second) {
            return;
        }

        // Keep format conversions, arguments, and CSV columns synchronized. The final
        // four fields record the call's scissor, which clips the texture rectangle.
        std::fprintf(s.file, "%llu,%u,%u,%u,%016llX,%s,%d,%d,%d,%d,%d,%d,%08X,%08X,%08X,%08X,%.4f,%.4f,%.4f,%.4f,%u,%d,%d,%d,%d,%.4f,%.4f,%.4f,%.4f,%d,%d,%d,%d\n",
            static_cast<unsigned long long>(frame),
            fbPairIndex, projIndex, callIndex,
            static_cast<unsigned long long>(texture), family,
            ulx, uly, lrx, lry, dsdx, dtdy, combinerH, combinerL,
            otherModeH, otherModeL,
            double(primR), double(primG), double(primB), double(primA),
            lerpFound, lerpUlx, lerpUly, lerpLrx, lerpLry,
            double(u1), double(v1), double(u2), double(v2),
            sciUlx, sciUly, sciLrx, sciLry);
        s.written++;
        std::fflush(s.file);
    }
};
