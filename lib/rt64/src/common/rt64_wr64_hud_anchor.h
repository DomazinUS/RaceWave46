//
// WR64 HUD anchor, R3.
//
// ALWAYS ON. Validated by eye at H 50 / V 90, so the correction, the box, the
// strength and the 176-entry table are all compiled in - no enable variable and
// no table file.
//
// What it does
// ------------
// The HUD is authored inside an inset box and does not reach the corners of the
// widened frame. Each element is TRANSLATED to its anchor; size is never
// touched, so glyphs stay exactly as crisp and as large as they are now.
//
// Measured HUD extent, from the census (13,280 distinct draws over a
// championship race and a stunt run), taking every persistent Rectangle draw and
// excluding only the full-frame fills:
//
//     x 24..402   y 20..219      margins  L24  T20  R22  B21
//
// so the anchor offsets are  dxLeft -24, dxRight +22, dyTop -20, dyBottom +21.
//
// ★ R1 was withdrawn. Two reasons, both found by measurement
// ----------------------------------------------------------
// 1. Its inset box was CIRCULAR. It was derived from the census rows flagged
//    "contained", but that flag came from an earlier guess at the same box, so
//    elements outside it could never influence it. Querying the census without
//    the containment filter showed what had been silently excluded - some of the
//    most-drawn elements in the game:
//
//        (24,205)-(48,217)   MISS label     seen 19267
//        (56,205)-(124,217)  five MISS pips seen 20547..26757
//        (252,205)-(284,217) POWER label    seen 19267
//        (378,42)-(402,54)   km/h           seen 19747
//        (24,34)-(36,50)     a timer digit  seen 19267
//
// 2. Its grouping was CONTENT-DEPENDENT. R1 formed widgets at runtime by spatial
//    adjacency, so an element's offset depended on what else happened to be
//    drawn that frame. The dry run measured the damage: the SPEED label appeared
//    in 8 groups with 6 distinct offsets, dy -17.25 alone versus -5.50 once the
//    position icon stack merged with it - an 11.75 native pixel jump, about 35
//    screen pixels, the moment the stack appeared. POWER flags: 4 offsets, a
//    21 px jump. No adjacency threshold fixes that; any such rule computes the
//    offset from whatever is nearby this frame, and the HUD's neighbours change
//    constantly.
//
// R2 therefore uses a STATIC table. Regions are fixed constants derived from the
// census, an element's anchor depends only on its own rect, and nothing about
// the rest of the frame can change it. That also removes the circularity: the
// regions are not computed from a containment test.
//
// Scope
// -----
//   - Rectangle projections only. 1,174 Perspective and 431 Orthographic draws
//     also fall inside the HUD box; this cannot reach the 3D scene. That is also
//     why it does not touch the start-signal gantry, which is 3D and needs its
//     own fix.
//   - A call must lie ENTIRELY inside one region. A full-frame fill or a
//     transition matches nothing and does not move.
//   - Anything not in the table does not move. Unrecognised is inert, not
//     guessed at.
//   - Offsets are capped; anything asking for a wild move is left alone.
//
// ★ R2 was applied and rejected. Three findings
// ---------------------------------------------
// 1. TOO AGGRESSIVE. It anchored to the absolute frame edge, so the leftmost
//    element landed on x=0. The original keeps margins inside the frame; BEST
//    TIME / BEST LAP and the last POWER flag were clipped. R3 adds a STRENGTH
//    percentage so the amount is dialled by eye instead of guessed.
// 2. WRONG SCOPE. Regions are plain screen rectangles, so the Watercraft Select
//    slider, the .HAYAMI name plate, a course-presentation frame strip and the
//    title logo all matched and moved. Position cannot tell a race from a menu.
// 3. MODE-DEPENDENT LAYOUT. SPEED sits at native x 345..377 in a championship
//    race and around 280..310 in time trial, so a region that matches one misses
//    the other and splits the label from its digits.
//
// R3 therefore keys on (TEXTURE, region). DrawCallTile carries tmemHashOrID; the
// HUD font atlas is not the texture a menu slider samples, and a widget keeps its
// texture across every mode. A table entry with hash 0 matches any texture, which
// is the R2 behaviour and is kept only for comparison.
//
// The table is LOADED FROM A FILE when WR64_HUD_ANCHOR_TABLE names one, so
// regions, textures, anchors and the strength can be retuned without rebuilding.
//
//   WR64_HUD_ANCHOR        1 applies the correction. Default OFF.
//   WR64_HUD_ANCHOR_TABLE  CSV table to load; falls back to the built-in one
//   WR64_HUD_ANCHOR_STRENGTH  percent of the full offset, default 50
//   WR64_HUD_ANCHOR_TRACE  CSV of every matched and unmatched draw. Works with
//                          the correction off - that is the dry run.
//   WR64_HUD_ANCHOR_BOX    "left,top,right,bottom", default "24,20,402,219"
//   WR64_HUD_ANCHOR_CAP    maximum offset in native pixels, default 48
//

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <mutex>
#include <unordered_map>
#include <string>
#include <vector>

#include "rt64_common.h"
#include "rt64_wr64_2p_frame.h"

namespace RT64 {
    // Projection::Type::Rectangle. Kept as a literal so this header stays free of
    // hle dependencies; the build gates on the census agreeing it is 3.
    static constexpr int32_t Wr64HudAnchorRectangleType = 3;

    struct Wr64HudAnchorBox {
        int32_t left = 24;
        int32_t top = 20;
        int32_t right = 402;
        int32_t bottom = 219;
    };

    // ★ THE CONFIRMED DIALS, COMPILED IN. 12,18-413,221 is horizontal 50% /
    // vertical 90% - "the sides are overall good" and "my favorite setup is with
    // -Vertical 90". Not env-tunable: it is a validated value, not an option.
    inline const Wr64HudAnchorBox &wr64HudAnchorBox() {
        static const Wr64HudAnchorBox box = [] {
            Wr64HudAnchorBox b;
            b.left = 12; b.top = 18; b.right = 413; b.bottom = 221;
            return b;
        }();
        return box;
    }

    // ------------------------------------------------------- the widget table --
    //
    // ax/ay: -1 anchors to the left/top edge, +1 to the right/bottom, 0 leaves
    // that axis alone. Regions are padded a few pixels around the measured
    // extents so a glyph that shifts by a pixel between frames stays inside.
    // Regions must not overlap; the first match wins and the build gates on it.

    struct Wr64HudAnchorWidget {
        std::string name;
        uint64_t tmemHash = 0;   // 0 matches any texture
        int32_t x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        int8_t ax = 0, ay = 0;
    };

    // Percent of the full edge offset. R2 shipped the equivalent of 100 and the
    // result clipped elements against the frame edge.
    // ★ 100%. The box above already carries the dials, so the strength term is a
    // straight pass-through. Compiled in for the same reason as the box.
    inline int32_t wr64HudAnchorStrength() {
        return 100;
    }

    // The runtime table loader used to live here. It is deleted, not disabled:
    // as long as a file-reading path exists, a stray WR64_HUD_ANCHOR_TABLE in
    // someone's environment can change what the game does. The table below is
    // the only table.

    // ★ THE VALIDATED TABLE, COMPILED IN. 176 entries, eight roles:
    //     time_left 24, top_centre 35, top_right 48, right_stack 10,
    //     miss 3, power 21, opening_logo 7, lap_times 28.
    //
    // This used to be read from wr64-hud-anchor-table.csv at runtime, with the
    // old R2 eight-entry table as the fallback when the file was absent. That
    // was backwards: the fallback was the table that MOVED the Watercraft
    // slider, the .HAYAMI name plate, the course-presentation frame and the
    // title logo, so a missing file did not disable the correction - it
    // reinstated the broken one. There is no file and no fallback now.
    //
    // wr64-hud-anchor-table.csv stays in the tree as the editable source this
    // array is generated from, and the build gates that the two agree.
    inline const std::vector<Wr64HudAnchorWidget> &wr64HudAnchorWidgets() {
        static const std::vector<Wr64HudAnchorWidget> table = [] {
            std::vector<Wr64HudAnchorWidget> t;
            t.reserve(176);
        t.push_back({ "time_left", 0xEC9A15E02A2B4238ULL,   22,   19,  116,   56, -1, -1 });
        t.push_back({ "time_left", 0xC99791F2F5DF634FULL,   22,   19,  116,   56, -1, -1 });
        t.push_back({ "time_left", 0x89B3547DEDD81321ULL,   22,   19,  116,   56, -1, -1 });
        t.push_back({ "time_left", 0x38C5F52614C89DC7ULL,   22,   19,  116,   56, -1, -1 });
        t.push_back({ "time_left", 0x1F4FFC75D32804E2ULL,   22,   19,  116,   56, -1, -1 });
        t.push_back({ "time_left", 0xE4F662D7955F8533ULL,   22,   19,  116,   56, -1, -1 });
        t.push_back({ "time_left", 0x7302D8CF3CA5ECEEULL,   22,   19,  116,   56, -1, -1 });
        t.push_back({ "time_left", 0xF1119E85A624476DULL,   22,   19,  116,   56, -1, -1 });
        t.push_back({ "time_left", 0x7700E328A22C0434ULL,   22,   19,  116,   56, -1, -1 });
        t.push_back({ "time_left", 0xD68508FE51EDCE40ULL,   22,   19,  116,   56, -1, -1 });
        t.push_back({ "time_left", 0x96B6389337E9824FULL,   22,   19,  116,   56, -1, -1 });
        t.push_back({ "time_left", 0x1E7335B10ECFEC8BULL,   22,   19,  116,   56, -1, -1 });
        t.push_back({ "time_left", 0x6D64ACDB9B0F2D99ULL,   22,   19,  116,   56, -1, -1 });
        t.push_back({ "time_left", 0x6B16910DEC4A24C8ULL,   22,   19,  116,   56, -1, -1 });
        t.push_back({ "time_left", 0x23431FC5F752B005ULL,   22,   19,  116,   56, -1, -1 });
        t.push_back({ "time_left", 0x8060BB2461317BEEULL,   22,   19,  116,   56, -1, -1 });
        t.push_back({ "time_left", 0x8BD7FC46402A8B0AULL,   22,   19,  116,   56, -1, -1 });
        t.push_back({ "time_left", 0x7A0F84A00913D18BULL,   22,   19,  116,   56, -1, -1 });
        t.push_back({ "time_left", 0xC056B5FDBBF87FD7ULL,   22,   19,  116,   56, -1, -1 });
        t.push_back({ "time_left", 0xFAA009B45E6C9F05ULL,   22,   19,  116,   56, -1, -1 });
        t.push_back({ "time_left", 0x5DD31CE2EB3DA345ULL,   22,   19,  116,   56, -1, -1 });
        t.push_back({ "time_left", 0xC47752A026900CC3ULL,   22,   19,  116,   56, -1, -1 });
        t.push_back({ "time_left", 0xCB7CAA1F6A7CFB6EULL,   22,   19,  116,   56, -1, -1 });
        t.push_back({ "time_left", 0x209F2BA20F208AE7ULL,   22,   19,  116,   56, -1, -1 });
        t.push_back({ "top_centre", 0x291F55A8DF75C5C6ULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x0AB67D1E6D15F7FCULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x35D63295F9654291ULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x0E3E5120BB31F0F9ULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0xCF3E0D0EE9A5E075ULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0xF0CBDEEB5EBD7CE6ULL,  180,   19,  238,   60, +0, -1 });
        // DrawStatus's advancement target uses select-font 1..4 or dash37.
        // The census contained only4/dash;1..3 must follow the same arrow.
        // Exact USA ROM atlas match at0x12F2D8, IA8 16x12 glyphs.
        t.push_back({ "top_centre", 0x5009956E5CCCD2A2ULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x0FB5914E291DA6BAULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x83428B1A568E7E20ULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x89B3547DEDD81321ULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x1F4FFC75D32804E2ULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x0BDD9FD871D48225ULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x8FE9F9D481008E29ULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x0F56C0FD580F4BDBULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0xEC9A15E02A2B4238ULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x779A07A370F48A4CULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x85E57EBEBB760B14ULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x2521186172042023ULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x6CE264791E0DB1E1ULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0xBC67401030877D14ULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x4974303E49F2D29EULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x1E7335B10ECFEC8BULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x6B16910DEC4A24C8ULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0xD68508FE51EDCE40ULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x96B6389337E9824FULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x6D64ACDB9B0F2D99ULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x23431FC5F752B005ULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x7700E328A22C0434ULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x7302D8CF3CA5ECEEULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0xE4F662D7955F8533ULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x540624C8AE0CFFDDULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x59789723BB139197ULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x7929A5D949CE027FULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0x7EE6D79DCD561A0DULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_centre", 0xFB14684FBC4BDBE9ULL,  180,   19,  238,   60, +0, -1 });
        t.push_back({ "top_right", 0x5ECCD002D46DCB73ULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x2D2A75FD4946F4E6ULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x77B01E979F3C0E90ULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x6E320CD0CDC404E3ULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x0E20BACA0F8643C3ULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x54452B5166A2D0EAULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x8E1480FBA8A046A4ULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0xAA0A8088722E220DULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x74FDE67D44E655AEULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x6859CD2305CDD9A5ULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x5427F54EB02D6527ULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0xF4CD20A451616F89ULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x291F55A8DF75C5C6ULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x0F56C0FD580F4BDBULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x2189F67DD2713D25ULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0xD0AC1B6FD270556AULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0xC0B186E2CDE94E9FULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x49F6BAC053989176ULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0xD0FFC08F6D95C915ULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x6D3CEFFBA94FB06EULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x105D10B04E83A71DULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0xCF35CC56FC0D7922ULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x0AB67D1E6D15F7FCULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x6274B02CAE948904ULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x039043FD4459F7C8ULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x630E2A3C8C2C3FE6ULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x380066975BE8F4A3ULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0xEE1901ABC2EDFE32ULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0xFB14684FBC4BDBE9ULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x7929A5D949CE027FULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x8FE9F9D481008E29ULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0xCC96E6285DB1B8B4ULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x85F566E1FC94ABA3ULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x2047D4C647CB8B98ULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0xB084E175F1A93907ULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x3040E173EF85CECCULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x4AB42EF6BAC9517DULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x8ACC98AC4F6505AEULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0xF7D6DCA955397C7BULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x9780AE476F96843FULL,  262,   19,  404,   60, +1, -1 });
        t.push_back({ "top_right", 0x3E9B6182872A7F84ULL,  262,   19,  404,   60, +1, -1 });

        // --- time trial: BEST TIME / BEST LAP, added 2026-07-30 ---------------
        //
        // The digit font. top_right was a STRICT SUBSET of lap_times' 8x8 set -
        // it knew 17 of the 24 glyphs - because the original census only ever saw
        // whichever digits happened to be in the best time on the day. A digit the
        // table does not know does not move, while the digit beside it moves +11,-18,
        // and the panel comes apart. Measured on a two-course time trial capture:
        // exactly 4 screen slots out of 700 in the whole game were sometimes moved
        // and sometimes not, and all 4 were these.
        //
        // Three of the seven were caught in the act. The other four are the same
        // font and would have broken a different best time on a different course,
        // so they go in now rather than after the next report.
        //
        // Safe by construction: every one is already trusted elsewhere in this
        // table, no region overlaps top_right at all, and none of them is drawn
        // inside this box anywhere except the four digit slots.
        t.push_back({ "top_right", 0x0176B2B2E1DD8832ULL,  262,   19,  404,   60, +1, -1 });   // latent - never drawn in this corner during the capture
        t.push_back({ "top_right", 0x612DB9A128434A92ULL,  262,   19,  404,   60, +1, -1 });   // latent
        t.push_back({ "top_right", 0x701F8C2A3691D482ULL,  262,   19,  404,   60, +1, -1 });   // latent
        t.push_back({ "top_right", 0x92CFC51E53A42BD0ULL,  262,   19,  404,   60, +1, -1 });   // OBSERVED BROKEN at 376,31 and 384,31
        t.push_back({ "top_right", 0xBC7BA76A4C0B78F1ULL,  262,   19,  404,   60, +1, -1 });   // latent
        t.push_back({ "top_right", 0xDA68D96117AD4DCBULL,  262,   19,  404,   60, +1, -1 });   // OBSERVED BROKEN at 363,31
        t.push_back({ "top_right", 0xEACE9962D70DF0A6ULL,  262,   19,  404,   60, +1, -1 });   // OBSERVED BROKEN at 392,51
        t.push_back({ "right_stack", 0x900F997EFF175036ULL,  355,   60,  408,  170, +1, +0 });
        t.push_back({ "right_stack", 0xFF675B8437A41F00ULL,  355,   60,  408,  170, +1, +0 });
        t.push_back({ "right_stack", 0xC0B186E2CDE94E9FULL,  355,   60,  408,  170, +1, +0 });
        t.push_back({ "right_stack", 0x3865564DD6A7C98DULL,  355,   60,  408,  170, +1, +0 });
        t.push_back({ "right_stack", 0xB424A0547CF1D1B7ULL,  355,   60,  408,  170, +1, +0 });
        t.push_back({ "right_stack", 0xF4CD20A451616F89ULL,  355,   60,  408,  170, +1, +0 });
        t.push_back({ "right_stack", 0xBDAE6282AD01AEEDULL,  355,   60,  408,  170, +1, +0 });
        t.push_back({ "right_stack", 0x92CFC51E53A42BD0ULL,  355,   60,  408,  170, +1, +0 });
        t.push_back({ "right_stack", 0xCEC83F35BB73A226ULL,  355,   60,  408,  170, +1, +0 });
        t.push_back({ "right_stack", 0x49F6BAC053989176ULL,  355,   60,  408,  170, +1, +0 });
        t.push_back({ "miss", 0x8A99AECA3AE5D99CULL,   22,  200,  130,  222, -1, +1 });
        t.push_back({ "miss", 0x0FFFA9AECC98CCBEULL,   22,  200,  130,  222, -1, +1 });
        t.push_back({ "miss", 0x290960CFBAC9880DULL,   22,  200,  130,  222, -1, +1 });
        t.push_back({ "power", 0xDE4772DD15050CFCULL,  248,  200,  404,  222, +1, +1 });
        t.push_back({ "power", 0xB520EB4126CAB2EAULL,  248,  200,  404,  222, +1, +1 });
        t.push_back({ "power", 0x410116336E8619CCULL,  248,  200,  404,  222, +1, +1 });
        t.push_back({ "power", 0x7EFDF48B49DB2D4BULL,  248,  200,  404,  222, +1, +1 });
        t.push_back({ "power", 0x0F084D506ABB5A82ULL,  248,  200,  404,  222, +1, +1 });
        t.push_back({ "power", 0x02BEB1FD6AABA730ULL,  248,  200,  404,  222, +1, +1 });
        t.push_back({ "power", 0x4C2D17575B824792ULL,  248,  200,  404,  222, +1, +1 });
        t.push_back({ "power", 0xC88476715CF4B80CULL,  248,  200,  404,  222, +1, +1 });
        t.push_back({ "power", 0x9873E55DC46333F0ULL,  248,  200,  404,  222, +1, +1 });
        t.push_back({ "power", 0xFEFD655F7F8FB9A1ULL,  248,  200,  404,  222, +1, +1 });
        t.push_back({ "power", 0xC8BA0EA9685D3F65ULL,  248,  200,  404,  222, +1, +1 });
        t.push_back({ "power", 0xD2EFF551FD2D88AAULL,  248,  200,  404,  222, +1, +1 });
        t.push_back({ "power", 0x8EC3DC32287597C3ULL,  248,  200,  404,  222, +1, +1 });
        t.push_back({ "power", 0xE6F58EB481C6D12CULL,  248,  200,  404,  222, +1, +1 });
        t.push_back({ "power", 0xAD07B40EFD0758F9ULL,  248,  200,  404,  222, +1, +1 });
        t.push_back({ "power", 0xD61031B49CEEE615ULL,  248,  200,  404,  222, +1, +1 });
        t.push_back({ "power", 0x0E2C8BAF4623EA5CULL,  248,  200,  404,  222, +1, +1 });
        t.push_back({ "power", 0x0F14FF5C2F45888CULL,  248,  200,  404,  222, +1, +1 });
        t.push_back({ "power", 0xF14A889087C4301EULL,  248,  200,  404,  222, +1, +1 });
        t.push_back({ "power", 0x3536029E03EC4CF5ULL,  248,  200,  404,  222, +1, +1 });
        t.push_back({ "power", 0x4AEE8809019542DFULL,  248,  200,  404,  222, +1, +1 });
        t.push_back({ "opening_logo", 0x4DD7D9227C3C528EULL,   18,   26,  106,   58, +0, -1 });
        t.push_back({ "opening_logo", 0x3463E99B704A0E13ULL,   18,   26,  106,   58, +0, -1 });
        t.push_back({ "opening_logo", 0xF53E241390A5ED8AULL,   18,   26,  106,   58, +0, -1 });
        t.push_back({ "opening_logo", 0x76FEC2AD15017C5AULL,   18,   26,  106,   58, +0, -1 });
        t.push_back({ "opening_logo", 0xDA58EE81D9964038ULL,   18,   26,  106,   58, +0, -1 });
        t.push_back({ "opening_logo", 0x6BB5A3E825A61649ULL,   18,   26,  106,   58, +0, -1 });
        t.push_back({ "opening_logo", 0xEFB5DC4BEBC3930FULL,   18,   26,  106,   58, +0, -1 });
        t.push_back({ "lap_times", 0x0176B2B2E1DD8832ULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0x105D10B04E83A71DULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0x2189F67DD2713D25ULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0x2D2A75FD4946F4E6ULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0x49F6BAC053989176ULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0x5427F54EB02D6527ULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0x54452B5166A2D0EAULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0x5ECCD002D46DCB73ULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0x612DB9A128434A92ULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0x6283664A0BDABDDEULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0x6859CD2305CDD9A5ULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0x6D3CEFFBA94FB06EULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0x701F8C2A3691D482ULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0x74FDE67D44E655AEULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0x7746C59A8182AB1EULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0x77B01E979F3C0E90ULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0x8E1480FBA8A046A4ULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0x92CFC51E53A42BD0ULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0xAA0A8088722E220DULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0xAEC8CABF5C1FB579ULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0xBC7BA76A4C0B78F1ULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0xC0B186E2CDE94E9FULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0xCF35CC56FC0D7922ULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0xD0AC1B6FD270556AULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0xD0FFC08F6D95C915ULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0xDA68D96117AD4DCBULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0xEACE9962D70DF0A6ULL,   20,   50,  102,   92, -1, -1 });
        t.push_back({ "lap_times", 0xF4CD20A451616F89ULL,   20,   50,  102,   92, -1, -1 });
            return t;
        }();
        return table;
    }

    // ★ ALWAYS ON. Validated by eye 2026-07-29 at H 50 / V 90: the race HUD, the
    // lap splits, the RANK position dash and the boot badge all reach the frame
    // edges, and nothing in Watercraft Select, the course presentation, the title
    // screen or the results screen moves. A validated fix is not a switch.
    inline bool wr64HudAnchorEnabled() {
        static const bool announced = [] {
            const Wr64HudAnchorBox &b = wr64HudAnchorBox();
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[hudanchor] APPLYING (box %d,%d-%d,%d, %zu widgets, strength %d%%)\n",
                b.left, b.top, b.right, b.bottom, wr64HudAnchorWidgets().size(),
                wr64HudAnchorStrength()); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            return true;
        }();
        (void)announced;
        return true;
    }

    inline const char *wr64HudAnchorTracePath() {
        static const char *path = std::getenv("WR64_HUD_ANCHOR_TRACE");
        return path;
    }

    inline bool wr64HudAnchorTraceArmed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool armed = [] {
            const char *p = wr64HudAnchorTracePath();
            return (p != nullptr) && (p[0] != '\0') && (p[0] != '0');
        }();
        return armed;
    }

    inline bool wr64HudAnchorActive() {
        return wr64HudAnchorEnabled() || wr64HudAnchorTraceArmed();
    }

    // A safety clamp on the computed offset, never overridden in any validated
    // run, so it is a constant like the rest.
    //
    // 48 native pixels covered every offset the one-player table can produce -
    // the box's own edges bound those to 12 horizontally and 19 vertically, so
    // the clamp has never bitten. The two-player gap-time readout is centred by
    // the pillarbox offset (424 - 320) / 2 = 52, which is LARGER, and a clamp
    // that silently zeroed a correction the code derives would be a bug wearing
    // a safety belt. So the clamp is the larger of the two, written as the
    // maximum rather than as 52, and it stays a guard against a table or a box
    // gone wrong.
    inline int32_t wr64HudAnchorCap() {
        const int32_t pillarbox = Wr64TwoPHudDxCentre4 / 4;
        return (pillarbox > 48) ? pillarbox : 48;
    }

    // ---------------------------------------------------------------- trace --

    struct Wr64HudAnchorRow {
        int32_t ulx = 0, uly = 0, lrx = 0, lry = 0;
        int32_t dx = 0, dy = 0;
        std::string widget;
        uint32_t applied = 0;
        uint64_t seen = 0;
    };

    // Leaked deliberately: the exit dump must not touch destroyed storage.
    inline std::mutex &wr64HudAnchorMutex() {
        static std::mutex *m = new std::mutex();
        return *m;
    }

    inline std::unordered_map<uint64_t, Wr64HudAnchorRow> &wr64HudAnchorRows() {
        static std::unordered_map<uint64_t, Wr64HudAnchorRow> *map =
            new std::unordered_map<uint64_t, Wr64HudAnchorRow>();
        return *map;
    }

    // Caller holds the mutex.
    inline void wr64HudAnchorWriteLocked(bool announce) {
        auto &map = wr64HudAnchorRows();
        if (map.empty()) {
            return;
        }

        std::FILE *f = std::fopen(wr64HudAnchorTracePath(), "wb");
        if (f == nullptr) {
            return;
        }

        std::vector<Wr64HudAnchorRow> rows;
        rows.reserve(map.size());
        for (const auto &it : map) {
            rows.push_back(it.second);
        }
        std::sort(rows.begin(), rows.end(), [](const Wr64HudAnchorRow &a, const Wr64HudAnchorRow &b) {
            if (a.seen != b.seen) { return a.seen > b.seen; }
            if (a.uly != b.uly) { return a.uly < b.uly; }
            return a.ulx < b.ulx;
        });

        const Wr64HudAnchorBox &box = wr64HudAnchorBox();
        std::fprintf(f, "# box %d,%d-%d,%d  cap %d  applying %d\n",
            box.left, box.top, box.right, box.bottom, wr64HudAnchorCap(),
            wr64HudAnchorEnabled() ? 1 : 0);
        std::fprintf(f, "seen,widget,applied,ulx,uly,lrx,lry,w,h,dx,dy,new_ulx,new_uly,new_lrx,new_lry\n");

        uint64_t matched = 0;
        for (const Wr64HudAnchorRow &r : rows) {
            matched += r.widget.empty() ? 0 : 1;
            std::fprintf(f, "%llu,%s,%u,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g,%g\n",
                static_cast<unsigned long long>(r.seen),
                r.widget.empty() ? "-" : r.widget.c_str(),
                r.applied,
                r.ulx / 4.0, r.uly / 4.0, r.lrx / 4.0, r.lry / 4.0,
                (r.lrx - r.ulx) / 4.0, (r.lry - r.uly) / 4.0,
                r.dx / 4.0, r.dy / 4.0,
                (r.ulx + r.dx) / 4.0, (r.uly + r.dy) / 4.0,
                (r.lrx + r.dx) / 4.0, (r.lry + r.dy) / 4.0);
        }
        std::fclose(f);

        if (announce) {
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[hudanchor] %zu distinct draws, %llu matched a widget -> %s\n",
                rows.size(), static_cast<unsigned long long>(matched), wr64HudAnchorTracePath()); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }
    }

    inline void wr64HudAnchorDump() {
        if (!wr64HudAnchorTraceArmed()) {
            return;
        }

        std::lock_guard<std::mutex> lock(wr64HudAnchorMutex());
        wr64HudAnchorWriteLocked(true);
    }

    struct Wr64HudAnchorDumper {
        ~Wr64HudAnchorDumper() { wr64HudAnchorDump(); }
    };

    inline void wr64HudAnchorRecord(const Wr64HudAnchorRow &row) {
        std::mutex &mutex = wr64HudAnchorMutex();
        auto &map = wr64HudAnchorRows();

        static Wr64HudAnchorDumper dumper;
        (void)dumper;

        uint64_t h = 1469598103934665603ull;
        auto mix = [&h](uint64_t v) { h ^= v; h *= 1099511628211ull; };
        mix(uint64_t(row.ulx)); mix(uint64_t(row.uly));
        mix(uint64_t(row.lrx)); mix(uint64_t(row.lry));
        for (char c : row.widget) { mix(uint64_t(uint8_t(c))); }

        std::lock_guard<std::mutex> lock(mutex);
        auto it = map.find(h);
        if (it != map.end()) {
            it->second.seen++;
            return;
        }

        if (map.size() >= 65536) {
            return;
        }

        Wr64HudAnchorRow stored = row;
        stored.seen = 1;
        map.emplace(h, stored);

        if ((map.size() % 32) == 0) {
            wr64HudAnchorWriteLocked(false);
        }
    }

    // ---------------------------------------------------------------- apply --
    //
    // The offset depends ONLY on this call's own rect. There is no per-frame
    // state, no plan, and nothing that another draw can influence - which is the
    // whole point of R2.

    // Two-player horizontal anchoring uses a position rule within the measured HUD
    // box x=20..404, P1 y=13..116, and P2 y=123..226. Restrict it to workloads with
    // both half scissors and draws fully inside that box, avoiding menus.
    // Choose the horizontal edge by thirds of the frame width, as for the main
    // single-player widget groups. Keep this rule's dy zero: vertical placement is
    // handled separately, and per-widget vertical changes can split adjacent draws.
    struct Wr64TwoPHudBox {
        int32_t x1, x2, y1, y2;   // native pixels, the half's own y range
        int32_t lo, hi;           // the half's corrected top and bottom
    };

    inline Wr64TwoPHudBox wr64TwoPHudBox(int half) {
        if (half == 2) {
            return { Wr64TwoPHudBoxLeft, Wr64TwoPHudBoxRight,
                     Wr64TwoPHudP2Top,   Wr64TwoPHudP2Bottom,
                     Wr64TwoPFrameSeam / 4, Wr64TwoPFrameBottom / 4 };
        }
        return { Wr64TwoPHudBoxLeft, Wr64TwoPHudBoxRight,
                 Wr64TwoPHudP1Top,   Wr64TwoPHudP1Bottom,
                 Wr64TwoPFrameTop / 4, Wr64TwoPFrameSeam / 4 };
    }

    // Which half a rect lies in, or 0 if it straddles the seam or the trace has
    // no two-player frame to speak of. Straddling means it is not HUD.
    inline int wr64TwoPHudHalfForRect(const FixedRect &rect) {
        if (rect.lry <= Wr64TwoPFrameSeam) { return 1; }
        if (rect.uly >= Wr64TwoPFrameSeam) { return 2; }
        return 0;
    }

    // The two-player offset. Returns false when the rect is not a two-player HUD
    // draw at all, in which case NOTHING is applied - a pause overlay or a
    // results panel drawn outside the measured box is left exactly alone.
    inline bool wr64TwoPHudOffset(const FixedRect &rect, uint64_t tmemHash,
                                  int32_t &outDx4, int32_t &outDy4)
    {
        outDx4 = 0;
        outDy4 = 0;

        const int half = wr64TwoPHudHalfForRect(rect);
        if (half == 0) { return false; }

        // THE ON-TRACK OPPONENT MARKER IS NOT HUD, AND IT IS VETOED BEFORE
        // ANYTHING ELSE LOOKS AT IT. It is drawn out of three pieces and only
        // two of them can be reached from here, so the only arrangement in
        // which they stay together is the one where none of them moves. The
        // measurement is in rt64_wr64_2p_frame.h.
        if (wr64TwoPHudIsTrackMarker(rect.ulx, rect.uly, rect.lrx, rect.lry, tmemHash)) {
            return false;
        }

        const Wr64TwoPHudBox box = wr64TwoPHudBox(half);
        if ((rect.ulx < box.x1 * 4) || (rect.lrx > box.x2 * 4) ||
            (rect.uly < box.y1 * 4) || (rect.lry > box.y2 * 4))
        {
            return false;
        }

        // THE GAP-TIME READOUT FIRST, AND IT STOPS HERE. It is the one widget in
        // this HUD still placed in 320-space, so it takes the pillarbox offset
        // and not an edge one. It has to be taken before the thirds rule below,
        // because the third boundary at 141 runs straight through the middle of
        // it - which is exactly how R7 tore it. The whole measurement and the
        // three conditions are in rt64_wr64_2p_frame.h.
        if (wr64TwoPHudIsGapTimer(rect.ulx, rect.uly, rect.lrx, rect.lry, half)) {
            outDx4 = Wr64TwoPHudDxCentre4;
            outDy4 = wr64TwoPHudDy4(half);
            return true;
        }

        // Thirds of the frame width, in quarter-pixels. Integer only: 424*4 = 1696.
        const int32_t centreX4 = (rect.ulx + rect.lrx) / 2;
        const int32_t third4 = (424 * 4) / 3;

        // Move left/right groups by half their 20-pixel horizontal slack. Leave the
        // middle third unchanged: it contains world-tracking portraits and pieces of
        // multi-draw interval widgets, so position alone cannot safely recenter it.
        if (centreX4 < third4)            { outDx4 = Wr64TwoPHudDxLeft4; }
        else if (centreX4 > (2 * third4)) { outDx4 = Wr64TwoPHudDxRight4; }

        // Vertical. Only the band at the FRAME's top edge moves - player one's
        // readout and, in the modes that draw it, the lap list under it. The two
        // bands at the seam stay where the game put them, and player two's
        // bottom band is held until MAX POWER can travel with it. The whole
        // argument, and the measurement, is in rt64_wr64_2p_frame.h.
        // ONE dy FOR THE WHOLE HALF. Nothing inside a half moves relative to
        // anything else in it, so no widget can come apart and every element
        // keeps the spacing the game drew. See rt64_wr64_2p_frame.h.
        outDy4 = wr64TwoPHudDy4(half);
        return true;
    }

    inline const Wr64HudAnchorWidget *wr64HudAnchorWidgetForRect(const FixedRect &rect, uint64_t tmemHash) {
        for (const Wr64HudAnchorWidget &w : wr64HudAnchorWidgets()) {
            if ((w.tmemHash != 0) && (w.tmemHash != tmemHash)) continue;
            if ((rect.ulx >= w.x1 * 4) && (rect.uly >= w.y1 * 4) &&
                (rect.lrx <= w.x2 * 4) && (rect.lry <= w.y2 * 4)) return &w;
        }
        return nullptr;
    }

    // Reuse the measured complete-widget rules, including the two-player
    // interval timer exception. Screen position alone is not HUD identity.
    inline int wr64HudUltrawideAnchor(const FixedRect &rect, uint64_t tmemHash) {
        if (wr64TwoPFrameActive()) {
            int32_t dx = 0, dy = 0;
            if (!wr64TwoPHudOffset(rect, tmemHash, dx, dy)) return 0;
            if (dx == Wr64TwoPHudDxCentre4) return 0;
            return (dx > 0) - (dx < 0);
        }
        const auto *widget = wr64HudAnchorWidgetForRect(rect, tmemHash);
        return widget ? widget->ax : 0;
    }

    inline bool wr64HudAnchorOffsetForRect(int32_t projType, const FixedRect &rect,
        uint64_t tmemHash, int32_t &outDx, int32_t &outDy)
    {
        outDx = 0;
        outDy = 0;

        if (!wr64HudAnchorActive() || (projType != Wr64HudAnchorRectangleType) || rect.isNull()) {
            return false;
        }

        int32_t dx = 0;
        int32_t dy = 0;
        bool matched = false;
        std::string widgetName;

        // [WR64] TWO PLAYER TAKES THE RULE AND STOPS. The one-player table is
        // authored in one-player coordinates and describes a screen that is not
        // on show; letting it run here is what produced the label flying off its
        // own digits. See the long note above wr64TwoPHudOffset.
        if (wr64TwoPFrameActive()) {
            matched = wr64TwoPHudOffset(rect, tmemHash, dx, dy);
            if (matched) {
                widgetName = (wr64TwoPHudHalfForRect(rect) == 2) ? "2p_bottom" : "2p_top";
            }
        }
        else {
            const Wr64HudAnchorWidget *match = wr64HudAnchorWidgetForRect(rect, tmemHash);

            const Wr64HudAnchorBox &box = wr64HudAnchorBox();
            if (match != nullptr) {
                matched = true;
                widgetName = match->name;
                if (match->ax < 0)      { dx = -box.left * 4; }
                else if (match->ax > 0) { dx = (424 - box.right) * 4; }
                if (match->ay < 0)      { dy = -box.top * 4; }
                else if (match->ay > 0) { dy = (240 - box.bottom) * 4; }
            }
        }

        if (matched) {
            const int32_t strength = wr64HudAnchorStrength();
            dx = (dx * strength) / 100;
            dy = (dy * strength) / 100;
        }

        const int32_t cap4 = wr64HudAnchorCap() * 4;
        const bool within = (std::abs(dx) <= cap4) && (std::abs(dy) <= cap4);
        if (!within) {
            dx = 0;
            dy = 0;
        }

        const bool applying = matched && within && wr64HudAnchorEnabled();

        if (wr64HudAnchorTraceArmed()) {
            Wr64HudAnchorRow row;
            row.ulx = rect.ulx; row.uly = rect.uly;
            row.lrx = rect.lrx; row.lry = rect.lry;
            row.dx = dx; row.dy = dy;
            row.widget = widgetName;
            row.applied = applying ? 1u : 0u;
            wr64HudAnchorRecord(row);
        }

        if (!applying) {
            return false;
        }

        outDx = dx;
        outDy = dy;
        return true;
    }
};
