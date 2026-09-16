//
// WR64 gantry anchor - the race-start traffic light assembly.
//
// ALWAYS ON. Position anchor and judder fix, both validated by eye.
//
// The problem
// -----------
// The start signal hangs 19.4 native lines below the top of the frame. That is
// not an arbitrary gap: the ORIGINAL 4:3 game renders its 3D scene in a reduced
// viewport that starts at native y=20 - the band the HUD used to sit in - and the
// gantry was authored to reach the top of THAT viewport. This port widened the
// scene viewport to the full 0..240, so the assembly now floats exactly one
// original letterbox below the top edge. dy = -20 restores the authored
// relationship rather than nudging it into place by eye.
//
// Why not key on the signature
// ----------------------------
// The banner anchor keys on the per-call signature, which hashes
// (framebufferPairIndex, projectionIndex, callIndex). That works for a HUD
// element emitted at a handful of call indices. This is a draw inside the 3D
// scene: the capture shows call 2, but that index moves as scene objects come and
// go, and covering it by enumeration would take thousands of entries per part.
//
// So this keys on the draw's own identity with the call-graph position removed:
//
//     texture hash + triangle count + colour combiner + other mode
//
// All four are available at the call site, and together they are an exact
// identity for one mesh in one render state. It is not a position heuristic and
// not a signature; it is the same draw wherever the scene happens to emit it.
//
// The parts
// ---------
//   F7735FE2DB9187B9  92 tri   the holder frame              CAPTURED (layer 257)
//   F7735FE2DB9187B9   8 tri   the holder's 2nd member draw  INFERRED, see below
//   3DAB4ADFF15B4895   8 tri   the red lights                CAPTURED (layer 129)
//
// The second holder draw is inferred but not guessed: the capture says layer 257
// has 2 member draws, and across eleven censuses that texture at 8 triangles
// tracks its 92-triangle draw exactly - 843/843, 819/819, 827/827, 795/795,
// 843/843 - which only happens if they are emitted together every frame.
//
// The last three came from WR64_GANTRY_ANCHOR_TRACE, which logs every perspective
// draw sharing this exact combiner and other mode. That list came back with six
// rows and no more, so it is the complete assembly - the census could never have
// separated them, because the holder's texture atlas is drawn 180,697 times
// across the scene. All six are confirmed by eye.
//
// Note the shape of it: 3DAB4ADFF15B4895 at 8 triangles is ONE light, not three,
// even though its layer reported three member draws. The lights are split across
// several textures and triangle counts, which is why guessing would have gone
// wrong and why the trace was worth an extra run.
//
// ALWAYS ON, no environment variable, offset fixed at 0,-20 native pixels.
// Both the position anchor and the transform identity below are validated, so
// they are compiled in - see wr64_user_rules, "a fix is a fix".
//   WR64_GANTRY_ANCHOR_EXTRA  additional parts, "hash:tris,hash:tris,...". Not
//                             needed for the start lights any more - all six are
//                             built in. Same combiner and other mode are still
//                             required, so a wrong hash never matches.
//   WR64_GANTRY_ANCHOR_TRACE  file. Logs every perspective draw sharing the
//                             assembly's combiner AND other mode, one row per
//                             distinct (texture, triangle count). Dedups, writes
//                             at exit. This is what named the last three parts.
//   WR64_GANTRY_LERP_TRACE    file. Interpolation diagnosis for the parts that
//                             ARE in the table. Writes as it goes - see below.
//
// The interpolation question
// -------------------------
// The assembly is not fluid. Three things were already ruled out by measurement:
// it judders with the anchor off, so the viewport nudge is not the cause; the
// AUTO discontinuity gate evaluated 78,498 times over 794 frames and gated on
// only 2 of them, so it is not being rejected there; and the census shows ~843
// draws per countdown, which is display rate rather than the ~90 that native
// rate would give, so it IS being emitted on interpolated frames.
//
// That leaves the world transform. rt64_framebuffer_renderer.cpp only ever reads
// view and projection transforms - object motion is already baked into the vertex
// data by the time a draw reaches it - so the interpolation decision happens
// upstream. The link from a draw to its transform is DrawCall::minWorldMatrix /
// maxWorldMatrix, which RSP::drawIndexedTri fills directly from
// DrawData::worldIndices as the triangles are emitted. Everything else follows
// from worldTransformGroups, transformGroups, worldTransformPhysicalAddresses
// and worldTransformSegmentedAddresses.
//
// ROUND 1 RESULT, and the two mistakes in it
// ------------------------------------------
// The first version resolved the transform by scanning worldTransformVertexIndices
// for the range containing the draw's first vertex. That was reinvention: the
// exact answer was already sitting in the DrawCall as minWorldMatrix. The scan
// also failed outright on 10-25% of draws per part (960 of 4,764), which is what
// the old "unowned-vertex" rows were. It is gone.
//
// Worse, the legend was written from memory and was INVERTED. rt64_extended_gbi.h:
//
//     G_EX_COMPONENT_SKIP         0x0
//     G_EX_COMPONENT_INTERPOLATE  0x1
//     G_EX_COMPONENT_AUTO         0x2
//
// So round 1's "pos_interp 2, vtx_interp 0" was not "position SKIP" - it is
// position AUTO and vertex SKIP, i.e. the plain TransformGroup defaults. Reading
// it the wrong way round would have condemned the display list for a setting it
// never made. Round 1's real findings, which stand:
//
//   - All six parts share ONE transform group, so a fix moves them coherently.
//   - positionInterpolation is AUTO, so the discontinuity gate decides - and that
//     gate was already measured firing on 2 frames out of 794. Not the cause.
//   - Whenever the transform moved, a lerp WAS produced (moves=1 -> lerped=1 on
//     5,186 draws, and not one moves=1/lerped=0 row). Interpolation runs.
//   - But 38% of resolved draws had moves=0: the transform is byte-identical to
//     the previous frame, then jumps. Interpolating a staircase looks exactly
//     like judder, and no interpolation setting can fix it.
//
// That last one is now the question, and it has two very different answers:
// either the game genuinely holds the matrix and steps it, or GameFrame::match
// failed to pair the transform and prev was filled from cur. matrix_id, phys_addr
// and seg_addr are here to settle it - a transform identified by ROM address can
// be followed across frames, and it is also the lever a fix would use, the same
// way decodeWr64ArticulatedMatrixAddress and isWr64CourseSelectorMapMatrixAddress
// already give specific WR64 matrices their own groups in rt64_rsp.cpp.
//
// Matrices are compared by bytes, not by component, so this does not depend on
// interop::float4x4's element layout.
//
// Three things about this trace were wrong on the first attempt. All three are
// now gated in BUILD-HUD-COMPLETE-R1.ps1:
//
//   It only wrote from a static destructor. rt64_wr64_hud_census.h had already
//   been through this: if the process does not run static destructors at exit,
//   everything collected is lost. So it now announces "[gantrylerp] armed" on
//   the first row and rewrites the file whenever a NEW distinct state appears,
//   plus every 64th draw so the counters stay fresh.
//
//   It only recorded rows where transform resolution SUCCEEDED, so an empty file
//   could not be distinguished from a trace that never armed. Every matched draw
//   now produces a row, with a sentinel naming what failed.
//
//   Wr64GantryLerpRow::operator< left group out of the key, which silently merged
//   rows that differed only by transform group - the exact thing being measured.
//

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <mutex>
#include <set>
#include <string>
#include <utility>

// [WR64] wr64TwoPFrameHalf / wr64TwoPFrameActive / wr64TwoPHalfSpan. This header
// includes no other project header, so there is nothing else to hang this off.
#include "rt64_wr64_2p_frame.h"

namespace RT64 {
    // Every part of the assembly shares these. They are part of the key, so a
    // texture reused elsewhere in the scene under a different state cannot match.
    static constexpr uint32_t Wr64GantryCombinerH = 0xFF33FFFFu;
    static constexpr uint32_t Wr64GantryCombinerL = 0xFC121824u;
    static constexpr uint32_t Wr64GantryOtherModeH = 0x00082CFFu;
    static constexpr uint32_t Wr64GantryOtherModeL = 0x00552078u;

    // ★ ALWAYS ON. The start-signal assembly reaches the top of the frame.
    // Validated by eye 2026-07-29 ("Looks perfect now!").
    inline bool wr64GantryAnchorEnabled() {
        static const bool announced = [] {
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[gantryanchor] APPLYING\n"); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            return true;
        }();
        (void)announced;
        return true;
    }

    inline void wr64GantryAnchorParse(int &dx, int &dy) {
        // ★ 0,-20 native pixels. -20 is exactly the original 4:3 scene viewport's top inset.
        dx = 0;
        dy = -20;
    }

    // Native pixels, returned in RDP 10.2 quarter-pixel units. The caller sets
    // left == right and top == bottom, which cancels the renderer's two
    // screenScale terms exactly: the assembly is TRANSLATED, never resized.
    // [WR64] TWO PLAYER: the inset is per half, so the offset is too.
    //
    // The -20 above is documented as "exactly the original 4:3 scene viewport's
    // top inset", and that is the rule this follows rather than a new one. Each
    // two-player half has its own inset, straight out of the authored scissor
    // rects in rt64_wr64_2p_frame.h:
    //
    //   player one   authored play 12..120, corrected   0..120  ->  inset 12
    //   player two   authored play 122..229, corrected 120..240  ->  inset  2
    //
    // One flat -20 puts the start signal in the wrong place in BOTH halves,
    // which is why the lights needed adjusting on each side and not just one.
    //
    // The half comes from the scissor latch, which is exact: the gantry is
    // perspective geometry drawn under p1_play or p2_play, never under the
    // shared inset the HUD uses.
    inline int32_t wr64GantryAnchorHalfDy(int half) {
        const Wr64TwoPHalfSpan span = wr64TwoPHalfSpan(half);
        return -(span.authoredTop - span.correctedTop);
    }

    inline void wr64GantryAnchorOffset(int32_t &outDx4, int32_t &outDy4) {
        static const int32_t dx4 = [] { int a, b; wr64GantryAnchorParse(a, b); return int32_t(a * 4); }();
        static const int32_t dy4 = [] { int a, b; wr64GantryAnchorParse(a, b); return int32_t(b * 4); }();
        outDx4 = dx4;

        const int half = wr64TwoPFrameHalf();
        if (wr64TwoPFrameActive() && (half != 0)) {
            outDy4 = wr64GantryAnchorHalfDy(half) * 4;
            return;
        }
        outDy4 = dy4;
    }

    inline const std::set<std::pair<uint64_t, uint32_t>> &wr64GantryAnchorParts() {
        static const std::set<std::pair<uint64_t, uint32_t>> parts = [] {
            std::set<std::pair<uint64_t, uint32_t>> s;
            s.emplace(0xF7735FE2DB9187B9ULL, 92u);   // holder frame, captured
            s.emplace(0xF7735FE2DB9187B9ULL, 8u);    // holder 2nd member draw
            s.emplace(0x3DAB4ADFF15B4895ULL, 8u);    // one red light, captured
            s.emplace(0x35EF901078A1D21BULL, 8u);    // from the trace, confirmed by eye
            s.emplace(0x3C7F23CD4A8BFFB6ULL, 28u);   // from the trace, confirmed by eye
            s.emplace(0xEF8847446A29037BULL, 28u);   // from the trace, confirmed by eye
            const char *extra = std::getenv("WR64_GANTRY_ANCHOR_EXTRA");
            if (extra != nullptr) {
                const char *p = extra;
                while (*p != '\0') {
                    unsigned long long h = 0;
                    unsigned t = 0;
                    int consumed = 0;
                    if (std::sscanf(p, "%llx:%u%n", &h, &t, &consumed) == 2) {
                        s.emplace(uint64_t(h), uint32_t(t));
                        p += consumed;
                    }
                    else {
                        break;
                    }
                    while ((*p == ',') || (*p == ' ')) { p++; }
                }
            }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[gantryanchor] %zu parts\n", s.size()); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            return s;
        }();
        return parts;
    }

    // -------------------------------------------------- transform identity --
    //
    // The judder fix. Always on.
    //
    // The assembly's transforms carry the default TransformGroup, whose matrixId is
    // G_EX_ID_AUTO. GameFrame::buildTransformIdMap opens with
    //
    //     if (group.matrixId == G_EX_ID_AUTO) { continue; }
    //
    // so they never enter transformIdMap and are never matched by identity. They
    // fall to the heuristic matcher in matchScene, which re-derives pairing from
    // geometry every frame. Measured over one countdown, the assembly's root went
    // unmatched on 58.3% of frames against 0-0.6% for its siblings, and an unmatched
    // transform gets prev = lerp = the raw 20 Hz matrix in
    // TransformProcessor::process. That is the judder: it snaps and holds.
    //
    // WHY NOT KEY ON THE MATRIX ADDRESS. That was the first plan and the measurement
    // killed it. WR64_MATRIX_SEG_TRACE over a full session showed 0x05004140-0x050047C0
    // is a recycled scratch pool: 27 slots at a uniform 0x40 stride, the assembly
    // landing on TEN different ones across a session, every slot shared with 7 to 46
    // other textures. The biggest single occupant of 0x05004340 is 1DF6E18FA3F51003 -
    // the MAX POWER banner. An address-keyed matrixId would have told RT64 that a
    // banner and a traffic light are the same object because they used the same
    // scratch slot on different frames, which is worse than the heuristic it replaced.
    // The existing address-keyed code in rt64_rsp.cpp is safe only because racer limbs
    // and watercraft-selector matrices live at genuinely fixed addresses.
    //
    // So the identity comes from the DRAW, not the matrix: texture + triangle count +
    // combiner + other mode, the same key the position fix uses and the only thing
    // proven stable across every course.
    //
    // The ordinal is the part's position in wr64GantryAnchorParts(), which is a
    // std::set and therefore sorted by texture then triangle count - deterministic
    // across frames and runs, which is the requirement, because the previous frame's
    // workload must derive the same id. (WR64_GANTRY_ANCHOR_EXTRA does shift the
    // ordinals, but it is constant within a run and is for probing only.)
    //
    // Base 0x57400000 is clear of every id already in use: 0x57000000 articulated
    // limbs, 0x57100000 watercraft selector, 0x57200000 course map, 0x57524300 sky.
    static constexpr uint32_t Wr64GantryIdentityBase = 0x57400000u;

    // ★ ALWAYS ON. The judder fix. Validated by eye 2026-07-30 ("Smooth as
    // butter") once the whole makeWr64FinalMatrixGroup recipe was applied.
    inline bool wr64GantryIdentityEnabled() {
        static const bool announced = [] {
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[gantryidentity] APPLYING\n"); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            return true;
        }();
        (void)announced;
        return true;
    }

    inline const std::map<std::pair<uint64_t, uint32_t>, uint32_t> &wr64GantryPartOrdinals() {
        static const std::map<std::pair<uint64_t, uint32_t>, uint32_t> *ordinals = [] {
            auto *m = new std::map<std::pair<uint64_t, uint32_t>, uint32_t>();
            uint32_t next = 0;
            for (const auto &part : wr64GantryAnchorParts()) {
                m->emplace(part, next++);
            }
            return m;
        }();
        return *ordinals;
    }

    // ATTEMPT 1 WAS WRONG AND THE MEASUREMENT CAUGHT IT. The first version derived the
    // id from the PART - each entry in the table got its own ordinal. But all six
    // parts share ONE world transform: the assembly is a single rigid object drawn in
    // six pieces. So a transform's id came from whichever of its draws the walk hit
    // first, and which draws are present varies frame to frame. The same part showed
    // up as 57400000 in some frames and 57400002 in others, so cur and prev never
    // agreed on a key and the id map could never pair them. An id that flips is worse
    // than no id at all - it was measured changing nothing, byte for byte.
    //
    // The id must therefore depend only on things that are the same every frame. It is
    // now the transform's RANK among the claimed transforms, ascending by transform
    // index: one claimed transform always gets Base+0 regardless of which of its draws
    // appear. If the assembly ever splits across several transforms they get Base+0,
    // Base+1 ... in a stable order, and same-id siblings pair by emission ordinal,
    // which is the G_EX_ORDER_LINEAR behaviour already confirmed correct by eye for
    // the three red lights.
    //
    // So the table's job here is only to answer "is this draw part of the assembly".
    inline bool wr64GantryIdentityClaims(uint64_t tmemHash, uint32_t triangleCount,
        uint32_t combinerH, uint32_t combinerL, uint32_t otherModeH, uint32_t otherModeL)
    {
        if ((combinerH != Wr64GantryCombinerH) || (combinerL != Wr64GantryCombinerL) ||
            (otherModeH != Wr64GantryOtherModeH) || (otherModeL != Wr64GantryOtherModeL))
        {
            return false;
        }

        const auto &ordinals = wr64GantryPartOrdinals();
        return ordinals.find(std::make_pair(tmemHash, triangleCount)) != ordinals.end();
    }

    inline uint32_t wr64GantryIdentityRankedId(uint32_t rank) {
        return Wr64GantryIdentityBase + rank;
    }

    inline bool wr64GantryIdentityIsOurs(uint32_t matrixId) {
        return (matrixId >= Wr64GantryIdentityBase) &&
               (matrixId < (Wr64GantryIdentityBase + 256u));
    }

    // ------------------------------------------------------- match trace --
    //
    // WR64_GANTRY_MATCH_TRACE. Measures `mapped` DIRECTLY instead of inferring it.
    //
    // The lerp trace inferred matching from prev/lerp matrix bytes, and that inference
    // was not sound: an unmatched transform and a matched-but-stationary one produce
    // identical bytes. It reported the same 81% for the fix on and off, which said
    // nothing either way. GameFrameMap::TransformMap::mapped is the ground truth and
    // it is right there in GameFrame::match - read it instead of guessing.
    //
    // in_cur / in_prev say whether the id reached transformIdMap on each side, which
    // separates "the stamp never landed" from "it landed but the ids disagree" from
    // "they agree and matching still failed".
    inline const char *wr64GantryMatchTracePath() {
        static const char *path = std::getenv("WR64_GANTRY_MATCH_TRACE");
        return path;
    }

    inline bool wr64GantryMatchTraceArmed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool armed = [] {
            const char *p = wr64GantryMatchTracePath();
            return (p != nullptr) && (p[0] != '\0') && (p[0] != '0');
        }();
        return armed;
    }

    struct Wr64GantryMatchRow {
        uint32_t matrixId = 0;
        uint32_t claimedCount = 0;
        uint8_t inCur = 0;
        uint8_t inPrev = 0;
        uint8_t mapped = 0;

        bool operator<(const Wr64GantryMatchRow &o) const {
            if (matrixId != o.matrixId) { return matrixId < o.matrixId; }
            if (claimedCount != o.claimedCount) { return claimedCount < o.claimedCount; }
            if (inCur != o.inCur) { return inCur < o.inCur; }
            if (inPrev != o.inPrev) { return inPrev < o.inPrev; }
            return mapped < o.mapped;
        }
    };

    inline std::mutex &wr64GantryMatchMutex() {
        static std::mutex *m = new std::mutex();
        return *m;
    }

    inline std::map<Wr64GantryMatchRow, uint64_t> &wr64GantryMatchRows() {
        static std::map<Wr64GantryMatchRow, uint64_t> *m = new std::map<Wr64GantryMatchRow, uint64_t>();
        return *m;
    }

    inline void wr64GantryMatchDumpLocked() {
        std::map<Wr64GantryMatchRow, uint64_t> &rows = wr64GantryMatchRows();
        std::FILE *f = std::fopen(wr64GantryMatchTracePath(), "wb");
        if (f == nullptr) {
            return;
        }

        std::fprintf(f, "# mapped is GameFrameMap::TransformMap::mapped, read straight out of\n");
        std::fprintf(f, "#   GameFrame::match. Not inferred from matrix bytes.\n");
        std::fprintf(f, "# in_cur / in_prev: was this matrixId in that side's transformIdMap.\n");
        std::fprintf(f, "# claimed: how many transforms the gantry table claimed that frame.\n");
        std::fprintf(f, "matrix_id,claimed,in_cur,in_prev,mapped,frames\n");
        for (const auto &it : rows) {
            std::fprintf(f, "%08X,%u,%u,%u,%u,%llu\n",
                it.first.matrixId, it.first.claimedCount, unsigned(it.first.inCur),
                unsigned(it.first.inPrev), unsigned(it.first.mapped),
                static_cast<unsigned long long>(it.second));
        }
        std::fclose(f);
    }

    inline void wr64GantryMatchDump() {
        if (!wr64GantryMatchTraceArmed()) {
            return;
        }

        std::lock_guard<std::mutex> lock(wr64GantryMatchMutex());
        wr64GantryMatchDumpLocked();
        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[gantrymatch] %zu distinct states -> %s\n",
            wr64GantryMatchRows().size(), wr64GantryMatchTracePath()); }
        { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
    }

    struct Wr64GantryMatchDumper {
        ~Wr64GantryMatchDumper() { wr64GantryMatchDump(); }
    };

    inline void wr64GantryMatchRecord(uint32_t matrixId, uint32_t claimedCount,
        bool inCur, bool inPrev, bool mapped)
    {
        if (!wr64GantryMatchTraceArmed()) {
            return;
        }

        static Wr64GantryMatchDumper dumper;
        (void)dumper;

        Wr64GantryMatchRow row;
        row.matrixId = matrixId;
        row.claimedCount = claimedCount;
        row.inCur = inCur ? 1u : 0u;
        row.inPrev = inPrev ? 1u : 0u;
        row.mapped = mapped ? 1u : 0u;

        std::lock_guard<std::mutex> lock(wr64GantryMatchMutex());
        std::map<Wr64GantryMatchRow, uint64_t> &rows = wr64GantryMatchRows();

        static bool announced = false;
        if (!announced) {
            announced = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[gantrymatch] armed -> %s\n", wr64GantryMatchTracePath()); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        const size_t before = rows.size();
        if ((rows.size() < 256) || (rows.find(row) != rows.end())) {
            rows[row]++;
        }

        static uint64_t recorded = 0;
        recorded++;
        if ((rows.size() != before) || ((recorded % 64) == 0)) {
            wr64GantryMatchDumpLocked();
        }
    }

    // One line the first time the pass stamps anything, so a run that changed nothing
    // is distinguishable from a run where the pass never fired.
    inline void wr64GantryIdentityNote(size_t stamped) {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        if (stamped == 0) {
            return;
        }

        static bool announced = false;
        if (!announced) {
            announced = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[gantryidentity] stamped %zu transform(s) on first hit\n", stamped); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }
    }

    // ---------------------------------------------------------------- trace --

    inline const char *wr64GantryAnchorTracePath() {
        static const char *path = std::getenv("WR64_GANTRY_ANCHOR_TRACE");
        return path;
    }

    inline bool wr64GantryAnchorTraceArmed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool armed = [] {
            const char *p = wr64GantryAnchorTracePath();
            return (p != nullptr) && (p[0] != '\0') && (p[0] != '0');
        }();
        return armed;
    }

    inline std::mutex &wr64GantryTraceMutex() {
        static std::mutex *m = new std::mutex();
        return *m;
    }

    inline std::set<std::pair<uint64_t, uint32_t>> &wr64GantryTraceRows() {
        static std::set<std::pair<uint64_t, uint32_t>> *s = new std::set<std::pair<uint64_t, uint32_t>>();
        return *s;
    }

    inline void wr64GantryTraceDump() {
        if (!wr64GantryAnchorTraceArmed()) {
            return;
        }

        std::lock_guard<std::mutex> lock(wr64GantryTraceMutex());
        std::set<std::pair<uint64_t, uint32_t>> &rows = wr64GantryTraceRows();
        std::FILE *f = std::fopen(wr64GantryAnchorTracePath(), "wb");
        if (f == nullptr) {
            return;
        }

        std::fprintf(f, "# perspective draws sharing the gantry's combiner and other mode\n");
        std::fprintf(f, "texture,triangles,in_table\n");
        const std::set<std::pair<uint64_t, uint32_t>> &parts = wr64GantryAnchorParts();
        for (const auto &r : rows) {
            std::fprintf(f, "%016llX,%u,%d\n", static_cast<unsigned long long>(r.first),
                r.second, (parts.find(r) != parts.end()) ? 1 : 0);
        }
        std::fclose(f);
        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[gantryanchor] %zu distinct (texture, triangles) -> %s\n",
            rows.size(), wr64GantryAnchorTracePath()); }
        { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
    }

    struct Wr64GantryTraceDumper {
        ~Wr64GantryTraceDumper() { wr64GantryTraceDump(); }
    };

    // ------------------------------------------------- interpolation trace --

    inline const char *wr64GantryLerpTracePath() {
        static const char *path = std::getenv("WR64_GANTRY_LERP_TRACE");
        return path;
    }

    inline bool wr64GantryLerpTraceArmed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool armed = [] {
            const char *p = wr64GantryLerpTracePath();
            return (p != nullptr) && (p[0] != '\0') && (p[0] != '0');
        }();
        return armed;
    }

    // Layout-agnostic on purpose: the caller hands over raw storage so this does
    // not need to know how interop::float4x4 indexes its elements.
    inline bool wr64GantryBytesDiffer(const void *a, const void *b, size_t n) {
        return std::memcmp(a, b, n) != 0;
    }

    struct Wr64GantryLerpRow {
        uint64_t texture = 0;
        uint32_t triangles = 0;
        uint32_t group = 0;
        uint32_t matrixId = 0;
        uint32_t physAddr = 0;
        uint32_t segAddr = 0;
        uint8_t posInterp = 0xFF;
        uint8_t vtxInterp = 0xFF;
        uint8_t moves = 0;
        uint8_t lerped = 0;
        uint64_t seen = 0;

        // group HAS to be part of the key. Leaving it out collapsed all four
        // "could not resolve" sentinels into one row - they share texture,
        // triangles, posInterp 255, vtxInterp 255, moves 0 and lerped 0, so
        // whichever arrived first kept its label and the other three vanished
        // into its counter. It also merged two different transform groups that
        // happened to interpolate the same way, which is exactly the thing this
        // trace exists to tell apart.
        bool operator<(const Wr64GantryLerpRow &o) const {
            if (texture != o.texture) { return texture < o.texture; }
            if (triangles != o.triangles) { return triangles < o.triangles; }
            if (group != o.group) { return group < o.group; }
            if (matrixId != o.matrixId) { return matrixId < o.matrixId; }
            if (physAddr != o.physAddr) { return physAddr < o.physAddr; }
            if (segAddr != o.segAddr) { return segAddr < o.segAddr; }
            if (posInterp != o.posInterp) { return posInterp < o.posInterp; }
            if (vtxInterp != o.vtxInterp) { return vtxInterp < o.vtxInterp; }
            if (moves != o.moves) { return moves < o.moves; }
            return lerped < o.lerped;
        }
    };

    inline std::mutex &wr64GantryLerpMutex() {
        static std::mutex *m = new std::mutex();
        return *m;
    }

    inline std::map<Wr64GantryLerpRow, uint64_t> &wr64GantryLerpRows() {
        static std::map<Wr64GantryLerpRow, uint64_t> *m = new std::map<Wr64GantryLerpRow, uint64_t>();
        return *m;
    }

    // Caller already holds wr64GantryLerpMutex(). std::mutex is not recursive, so
    // the write path has to be reachable without taking it again - this is what
    // lets wr64GantryLerpRecord persist a row the moment it appears.
    // The group column is a number for a real transform group and a word for the
    // sentinels the renderer uses when it could not get that far. Printing
    // 4294967283 and expecting the reader to recognise 0xFFFFFFF3 is not a
    // diagnostic.
    inline const char *wr64GantryLerpGroupLabel(uint32_t group, char *scratch, size_t scratchSize) {
        switch (group) {
        case 0xFFFFFFF0u: return "no-workload";
        case 0xFFFFFFF1u: return "out-of-range";
        default:
            std::snprintf(scratch, scratchSize, "%u", group);
            return scratch;
        }
    }

    inline void wr64GantryLerpDumpLocked() {
        std::map<Wr64GantryLerpRow, uint64_t> &rows = wr64GantryLerpRows();
        std::FILE *f = std::fopen(wr64GantryLerpTracePath(), "wb");
        if (f == nullptr) {
            return;
        }

        std::fprintf(f, "# G_EX_COMPONENT: 0=SKIP 1=INTERPOLATE 2=AUTO, 255=unresolved.\n");
        std::fprintf(f, "#   Checked against rt64_extended_gbi.h - do NOT reorder these from memory.\n");
        std::fprintf(f, "# moves = world != prev.  lerped = lerp != world.\n");
        std::fprintf(f, "# group: a number is the transform group. A word means the draw could not be\n");
        std::fprintf(f, "#   resolved to a world transform - no-workload, out-of-range. Those rows\n");
        std::fprintf(f, "#   still prove the trace ran.\n");
        std::fprintf(f, "# matrix_id/phys_addr/seg_addr identify the transform on the ROM side.\n");
        std::fprintf(f, "texture,triangles,group,matrix_id,phys_addr,seg_addr,pos_interp,vtx_interp,moves,lerped,draws\n");
        for (const auto &it : rows) {
            char wr64GroupScratch[16];
            std::fprintf(f, "%016llX,%u,%s,%08X,%08X,%08X,%u,%u,%u,%u,%llu\n",
                static_cast<unsigned long long>(it.first.texture), it.first.triangles,
                wr64GantryLerpGroupLabel(it.first.group, wr64GroupScratch, sizeof(wr64GroupScratch)),
                it.first.matrixId, it.first.physAddr, it.first.segAddr,
                unsigned(it.first.posInterp), unsigned(it.first.vtxInterp),
                unsigned(it.first.moves), unsigned(it.first.lerped),
                static_cast<unsigned long long>(it.second));
        }
        std::fclose(f);
    }

    inline void wr64GantryLerpDump() {
        if (!wr64GantryLerpTraceArmed()) {
            return;
        }

        std::lock_guard<std::mutex> lock(wr64GantryLerpMutex());
        wr64GantryLerpDumpLocked();
        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[gantrylerp] %zu distinct states -> %s\n",
            wr64GantryLerpRows().size(), wr64GantryLerpTracePath()); }
        { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
    }

    struct Wr64GantryLerpDumper {
        ~Wr64GantryLerpDumper() { wr64GantryLerpDump(); }
    };

    inline void wr64GantryLerpRecord(uint64_t texture, uint32_t triangles, uint32_t group,
        uint32_t matrixId, uint32_t physAddr, uint32_t segAddr,
        uint8_t posInterp, uint8_t vtxInterp, bool moves, bool lerped)
    {
        if (!wr64GantryLerpTraceArmed()) {
            return;
        }

        static Wr64GantryLerpDumper dumper;
        (void)dumper;

        Wr64GantryLerpRow row;
        row.texture = texture;
        row.triangles = triangles;
        row.group = group;
        row.matrixId = matrixId;
        row.physAddr = physAddr;
        row.segAddr = segAddr;
        row.posInterp = posInterp;
        row.vtxInterp = vtxInterp;
        row.moves = moves ? 1u : 0u;
        row.lerped = lerped ? 1u : 0u;

        std::lock_guard<std::mutex> lock(wr64GantryLerpMutex());
        std::map<Wr64GantryLerpRow, uint64_t> &rows = wr64GantryLerpRows();

        // The previous version only wrote from the static destructor, and the file
        // never appeared - the same way rt64_wr64_hud_census.h failed before it was
        // changed to write as it went. A process that does not run static
        // destructors at exit loses everything. So: announce on the first row, and
        // rewrite the file every time a NEW distinct state shows up. There are a
        // handful of states at most, so the whole file is a few hundred bytes and
        // rewriting it costs nothing. Repeat draws only bump a counter.
        static bool announced = false;
        if (!announced) {
            announced = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[gantrylerp] armed -> %s\n", wr64GantryLerpTracePath()); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        const size_t before = rows.size();
        if ((rows.size() < 512) || (rows.find(row) != rows.end())) {
            rows[row]++;
        }

        // Write on a new state, and every 64th draw after that. Without the second
        // condition the draws column froze at whatever it held when the last new
        // state appeared - in the stub run a state seen twice still read 1, because
        // the repeat bumped the counter but triggered no write. 64 keeps a per-draw
        // fopen out of the render loop while still landing ~13 refreshes across a
        // countdown's ~843 draws.
        static uint64_t recorded = 0;
        recorded++;
        if ((rows.size() != before) || ((recorded % 64) == 0)) {
            wr64GantryLerpDumpLocked();
        }
    }

    // ---------------------------------------- segmented address reuse trace --
    //
    // WR64_MATRIX_SEG_TRACE. Answers one question before the interpolation fix is
    // written: are the start lights' matrix slots used by anything else?
    //
    // The judder was traced to frame matching. The assembly's transform group is
    // G_EX_ID_AUTO, so GameFrame::buildTransformIdMap skips it outright and it
    // falls to the heuristic matcher in matchScene - which the game's double
    // buffered matrix pool defeats. Two physical families 0xB2F0 apart carry the
    // SAME segmented addresses, so a part's physical address alternates every
    // frame while its segmented address stays put. Measured over one countdown,
    // the root matrix went unmatched on 58.3% of frames against 0-0.6% for its
    // four siblings.
    //
    // The intended fix is the idiom rt64_rsp.cpp already uses for racer limbs and
    // the watercraft selector: hand these matrices an explicit matrixId keyed on
    // the SEGMENTED address, which puts them in transformIdMap and matches them by
    // identity every frame. That is only safe if the five slots belong to the
    // assembly alone.
    //
    // So this logs every draw whose world transform sits in the window, anywhere
    // in the game, with enough identity to recognise it - and a flag saying whether
    // the gantry table would claim it. A run that produces only is_gantry=1 rows
    // says the narrow rule is safe. Any is_gantry=0 row names exactly what else
    // would be caught.
    static constexpr uint32_t Wr64SegTraceFirst = 0x05004000u;
    static constexpr uint32_t Wr64SegTraceLast  = 0x050047FFu;

    inline const char *wr64SegTracePath() {
        static const char *path = std::getenv("WR64_MATRIX_SEG_TRACE");
        return path;
    }

    inline bool wr64SegTraceArmed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool armed = [] {
            const char *p = wr64SegTracePath();
            return (p != nullptr) && (p[0] != '\0') && (p[0] != '0');
        }();
        return armed;
    }

    inline bool wr64SegTraceInWindow(uint32_t segAddr) {
        return (segAddr >= Wr64SegTraceFirst) && (segAddr <= Wr64SegTraceLast);
    }

    struct Wr64SegTraceRow {
        uint32_t segAddr = 0;
        uint32_t physAddr = 0;
        uint64_t texture = 0;
        uint32_t triangles = 0;
        uint32_t projType = 0;
        uint32_t combinerH = 0;
        uint32_t combinerL = 0;
        uint32_t otherModeH = 0;
        uint32_t otherModeL = 0;
        uint8_t isGantry = 0;

        bool operator<(const Wr64SegTraceRow &o) const {
            if (segAddr != o.segAddr) { return segAddr < o.segAddr; }
            if (physAddr != o.physAddr) { return physAddr < o.physAddr; }
            if (texture != o.texture) { return texture < o.texture; }
            if (triangles != o.triangles) { return triangles < o.triangles; }
            if (projType != o.projType) { return projType < o.projType; }
            if (combinerH != o.combinerH) { return combinerH < o.combinerH; }
            if (combinerL != o.combinerL) { return combinerL < o.combinerL; }
            if (otherModeH != o.otherModeH) { return otherModeH < o.otherModeH; }
            if (otherModeL != o.otherModeL) { return otherModeL < o.otherModeL; }
            return isGantry < o.isGantry;
        }
    };

    inline std::mutex &wr64SegTraceMutex() {
        static std::mutex *m = new std::mutex();
        return *m;
    }

    inline std::map<Wr64SegTraceRow, uint64_t> &wr64SegTraceRows() {
        static std::map<Wr64SegTraceRow, uint64_t> *m = new std::map<Wr64SegTraceRow, uint64_t>();
        return *m;
    }

    inline void wr64SegTraceDumpLocked() {
        std::map<Wr64SegTraceRow, uint64_t> &rows = wr64SegTraceRows();
        std::FILE *f = std::fopen(wr64SegTracePath(), "wb");
        if (f == nullptr) {
            return;
        }

        std::fprintf(f, "# Every draw whose world transform's SEGMENTED address falls in\n");
        std::fprintf(f, "#   %08X..%08X - the start lights' matrix block.\n",
            Wr64SegTraceFirst, Wr64SegTraceLast);
        std::fprintf(f, "# is_gantry: 1 = the gantry table claims this draw, 0 = something else\n");
        std::fprintf(f, "#   is using the same matrix slot. Any 0 row means a matrixId rule keyed\n");
        std::fprintf(f, "#   on the segmented address alone would catch it too.\n");
        std::fprintf(f, "# proj_type: 0 None 1 Perspective 2 Orthographic 3 Rectangle 4 Triangle\n");
        std::fprintf(f, "seg_addr,phys_addr,texture,triangles,proj_type,combiner_h,combiner_l,other_h,other_l,is_gantry,draws\n");
        for (const auto &it : rows) {
            std::fprintf(f, "%08X,%08X,%016llX,%u,%u,%08X,%08X,%08X,%08X,%u,%llu\n",
                it.first.segAddr, it.first.physAddr,
                static_cast<unsigned long long>(it.first.texture), it.first.triangles,
                it.first.projType, it.first.combinerH, it.first.combinerL,
                it.first.otherModeH, it.first.otherModeL, unsigned(it.first.isGantry),
                static_cast<unsigned long long>(it.second));
        }
        std::fclose(f);
    }

    inline void wr64SegTraceDump() {
        if (!wr64SegTraceArmed()) {
            return;
        }

        std::lock_guard<std::mutex> lock(wr64SegTraceMutex());
        wr64SegTraceDumpLocked();
        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[segtrace] %zu distinct draws -> %s\n",
            wr64SegTraceRows().size(), wr64SegTracePath()); }
        { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
    }

    struct Wr64SegTraceDumper {
        ~Wr64SegTraceDumper() { wr64SegTraceDump(); }
    };

    inline void wr64SegTraceRecord(uint32_t segAddr, uint32_t physAddr, uint64_t texture,
        uint32_t triangles, uint32_t projType, uint32_t combinerH, uint32_t combinerL,
        uint32_t otherModeH, uint32_t otherModeL, bool isGantry)
    {
        if (!wr64SegTraceArmed()) {
            return;
        }

        static Wr64SegTraceDumper dumper;
        (void)dumper;

        Wr64SegTraceRow row;
        row.segAddr = segAddr;
        row.physAddr = physAddr;
        row.texture = texture;
        row.triangles = triangles;
        row.projType = projType;
        row.combinerH = combinerH;
        row.combinerL = combinerL;
        row.otherModeH = otherModeH;
        row.otherModeL = otherModeL;
        row.isGantry = isGantry ? 1u : 0u;

        std::lock_guard<std::mutex> lock(wr64SegTraceMutex());
        std::map<Wr64SegTraceRow, uint64_t> &rows = wr64SegTraceRows();

        // Same write-as-you-go rule as the lerp trace: announce on the first row and
        // rewrite whenever a new distinct draw appears, plus a periodic refresh so
        // the counters do not freeze. Never rely on the static destructor alone.
        static bool announced = false;
        if (!announced) {
            announced = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[segtrace] armed -> %s (window %08X..%08X)\n",
                wr64SegTracePath(), Wr64SegTraceFirst, Wr64SegTraceLast); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        const size_t before = rows.size();
        if ((rows.size() < 4096) || (rows.find(row) != rows.end())) {
            rows[row]++;
        }

        static uint64_t recorded = 0;
        recorded++;
        if ((rows.size() != before) || ((recorded % 256) == 0)) {
            wr64SegTraceDumpLocked();
        }
    }

    // The caller has already established that this is a Perspective call.
    inline bool wr64GantryAnchorMatch(uint64_t tmemHash, uint32_t triangleCount,
        uint32_t combinerH, uint32_t combinerL, uint32_t otherModeH, uint32_t otherModeL)
    {
        if ((combinerH != Wr64GantryCombinerH) || (combinerL != Wr64GantryCombinerL) ||
            (otherModeH != Wr64GantryOtherModeH) || (otherModeL != Wr64GantryOtherModeL))
        {
            return false;
        }

        if (wr64GantryAnchorTraceArmed()) {
            static Wr64GantryTraceDumper dumper;
            (void)dumper;
            std::lock_guard<std::mutex> lock(wr64GantryTraceMutex());
            std::set<std::pair<uint64_t, uint32_t>> &rows = wr64GantryTraceRows();
            if (rows.size() < 4096) {
                rows.emplace(tmemHash, triangleCount);
            }
        }

        if (!wr64GantryAnchorEnabled()) {
            return false;
        }

        const std::set<std::pair<uint64_t, uint32_t>> &parts = wr64GantryAnchorParts();
        return parts.find(std::make_pair(tmemHash, triangleCount)) != parts.end();
    }
};
