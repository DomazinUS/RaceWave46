// WR64 two-player frame coverage and viewport alignment.
//
// The native split-screen scissors retain safe-area borders. Match their exact
// RDP 10.2 rectangles and expand them to P1 (0,0)-(424,120) and P2
// (0,120)-(424,240). Keep these rectangles distinct and stable because projection
// pairing uses the scissor as part of each view's identity.
//
// Native producers are 8008FFD8, 80090068, 801E38BC, 801F0B08, 801F0DB4, and
// 802C92C0. Correcting the decoded RDP command covers all six without regenerating
// the recompiled functions.
//
// Recenter only the four two-player viewports: main centers 66/176 become 60/180;
// secondary centers 32/142 become 26/146. The ROM records are at 0x0950D0,
// 0x0950E0, 0x10A530, and 0x10A540. Preserve each secondary view's -34-line offset.
// Single-player viewports are separate records and must remain unchanged.
//
// HUD geometry uses a shared identity viewport and needs its own anchor correction;
// opening a scissor does not move it. WR64_2P_FRAME_TRACE optionally records scissor
// commands and corrections.

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <mutex>

namespace RT64 {
    // RDP scissor coordinates are 10.2 fixed point: native pixels * 4.
    static constexpr int32_t Wr64TwoPFrameLeft   = 0;
    static constexpr int32_t Wr64TwoPFrameTop    = 0;
    static constexpr int32_t Wr64TwoPFrameRight  = 424 * 4;
    static constexpr int32_t Wr64TwoPFrameBottom = 240 * 4;
    static constexpr int32_t Wr64TwoPFrameSeam   = 120 * 4;

    // The three authored two-player rects, exactly as the six producers build
    // them. Written as pixels * 4 so they can be read against the disassembly.
    static constexpr int32_t Wr64TwoPAuthoredLeft   =   8 * 4;   // 32
    static constexpr int32_t Wr64TwoPAuthoredRight  = 415 * 4;   // 1660
    static constexpr int32_t Wr64TwoPAuthoredTop    =  12 * 4;   // 48
    static constexpr int32_t Wr64TwoPAuthoredMid    = 122 * 4;   // 488
    static constexpr int32_t Wr64TwoPAuthoredBottom = 229 * 4;   // 916

    // [WR64] THE MEASURED TWO-PLAYER HUD BOX, native pixels. Taken the same way
    // the validated one-player box was - every settled textured Rectangle draw,
    // fills excluded - over three censuses (_010223, _180817, _181531), all
    // three agreeing exactly:
    //
    //   x  20..404  in BOTH halves
    //   P1 y  13..116  in a   0..120 half     top slack 13   bottom slack  4
    //   P2 y 123..226  in a 120..240 half     top slack  3   bottom slack 14
    //
    // It lives here rather than in the HUD anchor because the BANNER anchor
    // needs the same numbers - MAX POWER follows the power meter, so it has to
    // receive whatever the power meter receives - and both headers already
    // include this one. Duplicating the figures would let the two drift apart,
    // which is exactly how the banner ended up 19 pixels below a meter that had
    // moved by something else.
    static constexpr int32_t Wr64TwoPHudBoxLeft    =  20;
    static constexpr int32_t Wr64TwoPHudBoxRight   = 404;
    static constexpr int32_t Wr64TwoPHudP1Top      =  13;
    static constexpr int32_t Wr64TwoPHudP1Bottom   = 116;
    static constexpr int32_t Wr64TwoPHudP2Top      = 123;
    static constexpr int32_t Wr64TwoPHudP2Bottom   = 226;

    // Move each side by half its measured 20-pixel horizontal slack.
    static constexpr int32_t Wr64TwoPHudDxLeft4  = -((Wr64TwoPHudBoxLeft * 50) / 100) * 4;
    static constexpr int32_t Wr64TwoPHudDxRight4 = (((424 - Wr64TwoPHudBoxRight) * 50) / 100) * 4;

    // Translate each half's HUD as one rigid block. Native HUD origins are 110 lines
    // apart (13 and 123), while expanded viewport origins are 120 lines apart.
    // Independent top/bottom corrections stretch the HUD and separate adjacent draws.
    //
    // Each 120-line half contains a 103-line HUD, leaving 17 lines of total margin.
    // Targeting y=9 within each half gives offsets -4 for P1 and +6 for P2, preserving
    // the native layout and matching both players' positions. The one-line adjustment
    // from the geometric midpoint accounts for transparent padding in lower sprites.
    static constexpr int32_t Wr64TwoPHudTargetTop = 9;
    static constexpr int32_t Wr64TwoPHudDyP1_4 =
        (Wr64TwoPHudTargetTop - Wr64TwoPHudP1Top) * 4;              // -5 native
    static constexpr int32_t Wr64TwoPHudDyP2_4 =
        (Wr64TwoPHudTargetTop - (Wr64TwoPHudP2Top - 120)) * 4;      // +5 native

    inline int32_t wr64TwoPHudDy4(int half) {
        return (half == 2) ? Wr64TwoPHudDyP2_4 : Wr64TwoPHudDyP1_4;
    }

    // [WR64] THE GAP-TIME READOUT IS THE ONE THING STILL DRAWN IN 320-SPACE.
    //
    // The readout between the two boats - the sign, the seconds and the
    // thousandths, "-4 0\"101" over one half and "+4 0\"101" over the other - is
    // not centred on the screen. Measured off the census taken while it was up:
    //
    //     seven glyph draws per half, every one exactly 16 x 12
    //     half one   x 123..197   y  68.. 80
    //     half two   x 123..197   y 178..190
    //     block centre 160        frame centre 212
    //
    // 160 IS THE CENTRE OF A 320-WIDE SCREEN, and that is the whole diagnosis.
    // The widescreen frame is 424, and the game's own placement for this widget
    // was never moved into it. The gauge it is drawn on WAS moved: that bar is
    // 256 wide at x 84..340, and 84 = 32 + 52, 340 = 288 + 52. So the same
    // correction the bar already received, applied to the glyphs, puts them back
    // on their own gauge:
    //
    //     dx = (424 - 320) / 2 = 52
    //
    // - a derived pillarbox offset, not a number fitted to one screenshot. It
    // stays right if the gap grows a digit, because the game keeps centring the
    // block on 160 whatever it says.
    //
    // WHY NOT THE THIRDS RULE. It was tried in R7 and it tore the readout in
    // half: the third boundary is at 424/3 = 141, and the glyph centres are
    // 131, 141, 152, 162, 167, 178, 189 - two glyphs one side of it and five the
    // other. Only the five moved.
    //
    // WHY NOT A TEXTURE LIST. The glyphs are digits and they change. Two of the
    // eight textures in that census also draw elsewhere: F0CBDEEB5EBD7CE6, the
    // "-", is also a glyph at 205,95 on another screen. A texture list would
    // both miss the digits it has never seen and move the ones it recognises out
    // of context. Identifying the readout by WHERE IT IS AND WHAT SHAPE IT IS
    // does neither.
    //
    // THE THREE CONDITIONS, and each one is load-bearing:
    //
    //   exactly 16 x 12   the same font at 8 x 8 or 20 x 20 is not this widget,
    //                     and it is what excludes the water-spray sprite that
    //                     landed at 169,66-177,74 in census _010223.
    //   x within 60 of 160   generous enough that a wider readout is still
    //                     entirely inside - all seven glyphs move or none do -
    //                     and far from anything else on that row.
    //   the row, +/- 1    68 in half one, 178 in half two. This is what keeps
    //                     the same font at row 75 in census _181531 - two
    //                     two-digit numbers belonging to some other screen - and
    //                     the on-track position portrait at rows 91 and 201
    //                     out of it. The portrait follows a world position; it
    //                     must stay bound to its marker.
    //
    // Run over all four censuses - 22,878 draws - these three conditions match
    // exactly the fourteen readout glyphs and nothing else at all.
    static constexpr int32_t Wr64TwoPAuthoredWidth = 320;

    // (424 - 320) / 2 = 52 native.
    static constexpr int32_t Wr64TwoPHudDxCentre4 =
        (((Wr64TwoPFrameRight / 4) - Wr64TwoPAuthoredWidth) / 2) * 4;

    static constexpr int32_t Wr64TwoPGapGlyphW4   =  16 * 4;
    static constexpr int32_t Wr64TwoPGapGlyphH4   =  12 * 4;
    static constexpr int32_t Wr64TwoPGapRowP1_4   =  68 * 4;
    static constexpr int32_t Wr64TwoPGapRowP2_4   = 178 * 4;
    static constexpr int32_t Wr64TwoPGapRowSlack4 =   1 * 4;
    static constexpr int32_t Wr64TwoPGapCentre4   = (Wr64TwoPAuthoredWidth / 2) * 4;
    static constexpr int32_t Wr64TwoPGapSpan4     =  60 * 4;

    inline bool wr64TwoPHudIsGapTimer(int32_t ulx, int32_t uly, int32_t lrx, int32_t lry,
                                      int half)
    {
        if ((lrx - ulx) != Wr64TwoPGapGlyphW4) { return false; }
        if ((lry - uly) != Wr64TwoPGapGlyphH4) { return false; }
        if (ulx < (Wr64TwoPGapCentre4 - Wr64TwoPGapSpan4)) { return false; }
        if (lrx > (Wr64TwoPGapCentre4 + Wr64TwoPGapSpan4)) { return false; }
        const int32_t row = (half == 2) ? Wr64TwoPGapRowP2_4 : Wr64TwoPGapRowP1_4;
        return (uly >= (row - Wr64TwoPGapRowSlack4)) &&
               (uly <= (row + Wr64TwoPGapRowSlack4));
    }

    // [WR64] THE ON-TRACK OPPONENT MARKER IS DRAWN IN TWO PROJECTIONS AT ONCE,
    // AND ONLY ONE OF THEM CAN BE ANCHORED. So none of it is.
    //
    // The little ring out on the water that shows where the player behind you
    // is, with that player's portrait inside it, is three draws:
    //
    //     the ring        20 x 20  ORTHOGRAPHIC   texture 30B9BE1D3299DE00
    //     the ring's fill 20 x 20  RECTANGLE      untextured, the same rect
    //     the portrait    10 x 10  RECTANGLE      the rider's face, inset by 5
    //
    // wr64HudAnchorOffsetForRect only ever runs on RECTANGLE draws. So the two
    // Rectangle pieces were taking the half's offset and the Orthographic ring
    // could not, and the marker came apart by exactly that offset - which is
    // why it read as
    //
    //     upper half   portrait 4 px HIGH of its ring   (player one's dy is -4)
    //     lower half   portrait 6 px LOW  of its ring   (player two's dy is +6)
    //     and the further from the centre, the wider they part - because dx is
    //     0 in the middle third and 10 at either edge
    //
    // There is no offset that fixes this, because the ring cannot be given one.
    // The only arrangement where the three pieces stay together is the one the
    // game already draws: leave all of it alone. It tracks a world position, so
    // it was never ours to place.
    //
    // IDENTIFYING IT PER DRAW, with no texture list and no row - it travels the
    // whole width of a half and up and down it as well, so neither would work.
    // Measured over all four censuses, 600 markers and 1,200 Rectangle pieces:
    //
    //     EVERY Rectangle 10 x 10 draw is a marker portrait, sitting exactly
    //     concentric inside an Orthographic ring.               0 orphans.
    //     EVERY Rectangle 20 x 20 UNTEXTURED draw is a ring's own fill, at the
    //     ring's exact rect.                                    0 orphans.
    //
    // Nothing else in the two-player HUD is either shape. The position stack in
    // the corner draws the same rider portraits, but at 16 x 16 and 20 x 20 WITH
    // a texture, so the untextured test keeps it out - and it must, because that
    // stack is screen-anchored and does need the offset.
    static constexpr int32_t Wr64TwoPMarkerRing4     = 20 * 4;
    static constexpr int32_t Wr64TwoPMarkerPortrait4 = 10 * 4;

    inline bool wr64TwoPHudIsTrackMarker(int32_t ulx, int32_t uly, int32_t lrx, int32_t lry,
                                         uint64_t tmemHash)
    {
        const int32_t w = lrx - ulx;
        const int32_t h = lry - uly;
        if (w != h) { return false; }
        if (w == Wr64TwoPMarkerPortrait4) { return true; }
        return (w == Wr64TwoPMarkerRing4) && (tmemHash == 0);
    }

    // [WR64] WHICH HALF A BANNER IS IN, from the banner itself.
    //
    // MAX POWER and POWER UP! have no usable rect - it is the whole frame on
    // every call - and no usable scissor, and the render-side half latch holds
    // whichever half was walked last. But they are draws like any other, and
    // every draw carries call.callDesc.minWorldMatrix, an index into
    // drawData.worldTransforms. The object census has been reading [3].xyz off
    // that same field for months. The two banners are drawn 110 pixels apart on
    // screen, so those two transforms cannot be the same one.
    //
    // The seam is the threshold. The guard is the point: a transform that is not
    // a two-player HUD coordinate - identity, a world-space position, an index
    // that ran past the end - falls outside 0..240 and returns 0, which is
    // exactly today's behaviour. So the worst this can do is leave player two's
    // banner where it is; it can never move player one's down into its own power
    // meter.
    inline int wr64TwoPBannerHalfFromWorldY(float worldY, bool &outPlaceable) {
        outPlaceable = false;
        if (!(worldY >= 0.0f) || !(worldY <= 240.0f)) {
            return 0;
        }
        outPlaceable = true;
        return (worldY < float(Wr64TwoPFrameSeam / 4)) ? 1 : 2;
    }

    // [WR64] WHICH HALF IS BEING DRAWN, and whether this is a two-player race
    // at all. Nothing in RT64 knew either.
    //
    // wr64TwoPFrameCorrectScissor is the only place that can tell: its match is
    // an exact four-edge compare against the three authored two-player rects, so
    // it fires in two-player and never otherwise. Latching its answer costs one
    // store on a path that already runs.
    //
    // 0 = one player (or not yet known), 1 = player one's half, 2 = player two's.
    // "inset" leaves it alone: the shared HUD projection is drawn under that
    // scissor and must not clear which half the renderer is in.
    inline int &wr64TwoPFrameHalfRef() {
        static thread_local int half = 0;
        return half;
    }

    inline int wr64TwoPFrameHalf() {
        return wr64TwoPFrameHalfRef();
    }

    // True once a two-player rect has been corrected in this frame. The HUD
    // anchor needs this and cannot use the half, because the HUD is drawn on the
    // inset scissor rather than on either half's.
    inline bool &wr64TwoPFrameActiveRef() {
        static thread_local bool active = false;
        return active;
    }

    inline bool wr64TwoPFrameActive() {
        return wr64TwoPFrameActiveRef();
    }

    // [WR64] THE LATCH IS thread_local AND THE RENDERER IS NOT THE THREAD THAT
    // WRITES IT. This is why the two-player HUD table changed nothing on screen.
    //
    // wr64TwoPFrameCorrectScissor below runs in rt64_rdp.cpp, at RDP decode.
    // EVERY reader - the HUD anchor, the gantry anchor, the banner anchor - runs
    // in rt64_framebuffer_renderer.cpp, on a different thread, where these two
    // thread_local objects have never been written and are therefore 0 and false
    // for the life of the process.
    //
    // Measured, not inferred. wr64-banner-20260801_190705.csv logs
    // wr64TwoPFrameActive() on every matched call, and it reads 1 on exactly one
    // call in ten, in a fixed one-then-nine pattern (rows 1, 11, 21, ...). A flag
    // that is never cleared cannot go true and then false again on ONE thread, so
    // more than one thread executes the read and only one of them has ever
    // executed the write. Every two-player correction gated on this - the 41
    // measured widget regions, the shifted one-player regions, the per-half dy,
    // the gantry - therefore applied to one rendered frame in ten, which is
    // indistinguishable from not applying at all.
    //
    // SHARING THE LATCH ACROSS THREADS WOULD BE THE WRONG FIX. The half has to
    // vary WITHIN a frame - player one's draws and player two's draws are the
    // whole point - and a global would be read by a renderer that is a frame or
    // more behind the decoder. Instead the renderer rebuilds the same two values
    // on its OWN thread, from data it already holds: Projection::scissorRect
    // carries the corrected half rect, because the correction below has already
    // run by the time the projection is built.
    //
    // Semantics are kept identical to the decode side on purpose:
    //   * active is a property of the FRAME  - true when the workload contains
    //     both halves,
    //   * half is a property of the PROJECTION - set by either play scissor, and
    //     deliberately left alone by the inset, under which the shared HUD draws.

    // Does this scissor, AFTER correction, name one of the two halves?
    inline bool wr64TwoPFrameIsHalfScissor(int32_t ulx, int32_t uly, int32_t lrx, int32_t lry,
        int &outHalf)
    {
        outHalf = 0;
        if ((ulx != Wr64TwoPFrameLeft) || (lrx != Wr64TwoPFrameRight)) {
            return false;
        }
        if ((uly == Wr64TwoPFrameTop) && (lry == Wr64TwoPFrameSeam)) {
            outHalf = 1;
            return true;
        }
        if ((uly == Wr64TwoPFrameSeam) && (lry == Wr64TwoPFrameBottom)) {
            outHalf = 2;
            return true;
        }
        return false;
    }

    // Called by the renderer once per workload, before it walks the projections.
    // Leaving two player clears the half as well, so a one-player frame can never
    // inherit "player two" from the race before it.
    inline void wr64TwoPFrameRenderWorkload(bool twoPlayer) {
        wr64TwoPFrameActiveRef() = twoPlayer;
        if (!twoPlayer) {
            wr64TwoPFrameHalfRef() = 0;
        }
    }

    // Called by the renderer for each projection, before its draw calls. The
    // inset scissor leaves the half alone - same rule as at decode.
    inline void wr64TwoPFrameRenderProjection(int32_t ulx, int32_t uly, int32_t lrx, int32_t lry) {
        int half = 0;
        if (wr64TwoPFrameIsHalfScissor(ulx, uly, lrx, lry, half)) {
            wr64TwoPFrameHalfRef() = half;
        }
    }

    // The authored and corrected vertical extents of each half, in native
    // pixels. THE PITCH BETWEEN HALVES IS AUTHORED AS 110 - 122 minus 12 - and
    // the corrected halves are 120 apart. That ten-pixel difference is why the
    // second player's HUD does not land where the first player's does when the
    // same offset is applied to both.
    struct Wr64TwoPHalfSpan {
        int32_t authoredTop;
        int32_t authoredBottom;
        int32_t correctedTop;
        int32_t correctedBottom;
    };

    inline Wr64TwoPHalfSpan wr64TwoPHalfSpan(int half) {
        if (half == 2) {
            return { Wr64TwoPAuthoredMid / 4, Wr64TwoPAuthoredBottom / 4,
                     Wr64TwoPFrameSeam / 4,   Wr64TwoPFrameBottom / 4 };
        }
        return { Wr64TwoPAuthoredTop / 4, Wr64TwoPFrameSeam / 4,
                 Wr64TwoPFrameTop / 4,  Wr64TwoPFrameSeam / 4 };
    }

    // Returns a short tag naming which rect was corrected, or nullptr if the
    // command is not one of the three. Deliberately an exact four-edge match on
    // every edge: no tolerance, no range, nothing that could widen its reach to a
    // rect this analysis has not accounted for.
    inline const char *wr64TwoPFrameCorrectScissor(int32_t &ulx, int32_t &uly, int32_t &lrx, int32_t &lry) {
        if ((ulx != Wr64TwoPAuthoredLeft) || (lrx != Wr64TwoPAuthoredRight)) {
            return nullptr;
        }

        // P1 play area: (8,12)-(415,120) -> (0,0)-(424,120)
        if ((uly == Wr64TwoPAuthoredTop) && (lry == Wr64TwoPFrameSeam)) {
            ulx = Wr64TwoPFrameLeft;  uly = Wr64TwoPFrameTop;
            lrx = Wr64TwoPFrameRight; lry = Wr64TwoPFrameSeam;
            wr64TwoPFrameHalfRef() = 1;   // [WR64]
            wr64TwoPFrameActiveRef() = true;  // [WR64]
            return "p1_play";
        }

        // P2 play area, and the per-player loop's bottom half:
        // (8,122)-(415,229) -> (0,120)-(424,240)
        if ((uly == Wr64TwoPAuthoredMid) && (lry == Wr64TwoPAuthoredBottom)) {
            ulx = Wr64TwoPFrameLeft;  uly = Wr64TwoPFrameSeam;
            lrx = Wr64TwoPFrameRight; lry = Wr64TwoPFrameBottom;
            wr64TwoPFrameHalfRef() = 2;   // [WR64]
            wr64TwoPFrameActiveRef() = true;  // [WR64]
            return "p2_play";
        }

        // The whole inset frame, used by P1's secondary pass and the shared HUD
        // orthographic projection: (8,12)-(415,229) -> (0,0)-(424,240)
        if ((uly == Wr64TwoPAuthoredTop) && (lry == Wr64TwoPAuthoredBottom)) {
            ulx = Wr64TwoPFrameLeft;  uly = Wr64TwoPFrameTop;
            lrx = Wr64TwoPFrameRight; lry = Wr64TwoPFrameBottom;
            // [WR64] Deliberately does NOT touch the half. The shared HUD
            // projection draws under this scissor and the renderer must keep
            // whichever half it was last told about.
            wr64TwoPFrameActiveRef() = true;
            return "inset";
        }

        return nullptr;
    }

    // ---------------------------------------------------------------------
    // Diagnostic. Off unless WR64_2P_FRAME_TRACE names a file.
    //
    // It answers one question the fix itself cannot: did all six producers
    // actually fire? The rect does not identify the producer, but the census
    // does show which of the three corrected rects appeared and how often, and
    // it lists every scissor the game emitted that was NOT corrected - which is
    // where a missed two-player producer would show up.
    //
    // Written DURING the run, on each new distinct row plus a periodic refresh.
    // A trace that only writes from a static destructor loses everything if the
    // process does not run them; that has cost this project a play session twice.
    // ---------------------------------------------------------------------
    inline const char *wr64TwoPFrameTracePath() {
        static const char *path = std::getenv("WR64_2P_FRAME_TRACE");
        return path;
    }

    inline bool wr64TwoPFrameTraceArmed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool armed = [] {
            const char *p = wr64TwoPFrameTracePath();
            const bool on = (p != nullptr) && (p[0] != '\0') && (p[0] != '0');
            if (on) {
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[2pframe] scissor census armed -> %s\n", p); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            }
            return on;
        }();
        return armed;
    }

    struct Wr64TwoPFrameKey {
        int32_t ulx, uly, lrx, lry;
        bool corrected;

        bool operator<(const Wr64TwoPFrameKey &o) const {
            if (ulx != o.ulx) return ulx < o.ulx;
            if (uly != o.uly) return uly < o.uly;
            if (lrx != o.lrx) return lrx < o.lrx;
            if (lry != o.lry) return lry < o.lry;
            return int(corrected) < int(o.corrected);
        }
    };

    inline std::mutex &wr64TwoPFrameMutex() {
        static std::mutex m;
        return m;
    }

    inline std::map<Wr64TwoPFrameKey, uint64_t> &wr64TwoPFrameCensus() {
        static std::map<Wr64TwoPFrameKey, uint64_t> census;
        return census;
    }

    inline void wr64TwoPFrameWriteLocked() {
        std::FILE *f = std::fopen(wr64TwoPFrameTracePath(), "wb");
        if (f == nullptr) {
            return;
        }

        std::fprintf(f, "ulx,uly,lrx,lry,ulx_px,uly_px,lrx_px,lry_px,corrected,tag,count\n");
        for (const auto &entry : wr64TwoPFrameCensus()) {
            const Wr64TwoPFrameKey &k = entry.first;
            const char *tag = "-";
            if (k.corrected) {
                if (k.lry == Wr64TwoPFrameSeam)                                  tag = "p1_play";
                else if (k.uly == Wr64TwoPFrameSeam)                             tag = "p2_play";
                else                                                             tag = "inset";
            }
            std::fprintf(f, "%d,%d,%d,%d,%g,%g,%g,%g,%d,%s,%llu\n",
                k.ulx, k.uly, k.lrx, k.lry,
                k.ulx / 4.0, k.uly / 4.0, k.lrx / 4.0, k.lry / 4.0,
                int(k.corrected), tag,
                static_cast<unsigned long long>(entry.second));
        }
        std::fflush(f);
        std::fclose(f);
    }

    // Called with the command as authored, before the correction is applied, so
    // the census records what the game asked for rather than what it got.
    inline void wr64TwoPFrameRecord(int32_t ulx, int32_t uly, int32_t lrx, int32_t lry, bool corrected) {
        if (!wr64TwoPFrameTraceArmed()) {
            return;
        }

        std::lock_guard<std::mutex> lock(wr64TwoPFrameMutex());
        auto &census = wr64TwoPFrameCensus();
        const Wr64TwoPFrameKey key{ ulx, uly, lrx, lry, corrected };
        auto it = census.find(key);
        const bool isNew = (it == census.end());
        if (isNew) {
            census.emplace(key, uint64_t(1));
        }
        else {
            it->second += 1;
        }

        // Rewrite on every new distinct row, and every 4096 commands after that
        // so a long session keeps a current file without one write per call.
        static uint64_t sinceWrite = 0;
        if (isNew || (++sinceWrite >= 4096)) {
            sinceWrite = 0;
            wr64TwoPFrameWriteLocked();
        }
    }
};
