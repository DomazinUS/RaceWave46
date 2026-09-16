// WR64 celestial screen-rectangle interpolation.
//
// The sun, glow, and flares are rectangle projections, which the world-transform
// matcher does not visit. Pair consecutive-frame draws by texture and equal-count
// order, then blend their coordinates with the frame interpolation weight.
// Count changes or absence break pairing rather than reusing a stale rectangle.
//
// Capture wr64-rect-track-sun-20260803_212128.csv contains 531 Sunset Bay sun
// frames and four exits. Real fast pans reach 372 quarter-pixels per tick; the
// 848-quarter-pixel continuity limit admits those pans but rejects large jumps.
// Camera-cut suppression already sets the blend weight to the current frame.
// Texture-scoped claims leave unrelated HUD rectangles and the sky fan unchanged.

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>

namespace RT64 {
    static constexpr uint64_t Wr64CelestialSunGlow   = 0x8A399FACE63FE583ULL;
    static constexpr uint64_t Wr64CelestialSunDisk   = 0x329E604758F9E8BCULL;
    static constexpr uint64_t Wr64CelestialSunFlare  = 0xB82E909F647A31ADULL;
    // Dolphin Park, Composer capture 13 / frame 32598. ONE rect for the whole
    // disk there (Sunset Bay uses two), same combiner and other mode as the
    // Sunset Bay disk, and THE SAME flare texture as Sunset Bay - so DP's nine
    // flares were already claimed the moment R2 shipped. Only the disk is new.
    //
    // DP also draws a 28-triangle PERSPECTIVE glow mesh (EEFCBAB804DF4B9E).
    // That is deliberately NOT in this list: the pairing pass walks Rectangle
    // projections only, a rect blend cannot express a mesh, and claiming it
    // here would be a silent no-op that reads as coverage. It is watched by
    // the matrix-track diagnostic instead, and gets its own fix from that
    // measurement if it steps.
    static constexpr uint64_t Wr64CelestialSunDiskDP = 0x79185A8F164D1366ULL;

    // Twilight City stars share one texture across sizes and colors (Composer
    // captures 12-18, 2026-08-04). The moon reuses Wr64CelestialSunDisk.
    // Stars use equal-count order pairing; a count change holds the current frame.
    // An equal-count simultaneous entry/exit remains a limitation of order identity.
    static constexpr uint64_t Wr64CelestialTcStar    = 0xB81BF5D3B4FA6341ULL;

    // Dolphin Park instruction rectangle identified by Composer capture 3/frame
    // 6714 (2026-08-04). Its scrolling geometry uses the rectangle pairing path.
    static constexpr uint64_t Wr64CelestialDpText    = 0xFF7EE0806FE2A6B6ULL;

    // Each message has its own baked texture. The Composer sweep identified these
    // siblings sharing the same rectangle state and instruction-window band.
    // Keep this list synchronized with the diagnostic watch list. State-based claims
    // below cover further messages without pairing two different textures together.
    static constexpr uint64_t Wr64CelestialDpTextSiblings[] = {
        0x3D50564003C7B071ULL, 0xEF5F5B407FE5A4FEULL, 0xDFCE6E2C8E3DBB34ULL,
        0x4F716395385841D5ULL, 0x1192FD217989EFC0ULL, 0xC43AC3E146A0F40EULL,
        0xD7D5A9EB06E1BE83ULL, 0x561A29BFDE8C4A5EULL, 0x14B48652198DEE3CULL,
        0xE40AAE5624E208B4ULL, 0xE7F244688ABE4C89ULL, 0x3C7197C83D20CDA5ULL,
        0xE34CC53C275FDAC7ULL, 0xB20380CC72D2B86FULL, 0x2735E5049B76C5D5ULL,
        0xF363BB7BC58CD429ULL, 0x03D0BADBC82D03BBULL, 0x38477FB1A0E51891ULL,
        0x540DDC6493485F20ULL, 0x18B319D609761603ULL, 0xB51F7A8C26314617ULL,
        0x4F6ADBB5B3AC452DULL, 0xFC81EE483D5B5767ULL, 0x5850E75F4B001927ULL,
        0xF13236A2045F35BEULL, 0x70C20EAF2073F236ULL,
        // Additional single-line message with the same instruction render state.
        0x5662E4CD1EE68825ULL,
    };
    static constexpr int Wr64CelestialDpTextSiblingCount =
        int(sizeof(Wr64CelestialDpTextSiblings) / sizeof(Wr64CelestialDpTextSiblings[0]));

    // Claim the instruction family by render state and its narrow y band, covering
    // messages beyond the enumerated texture list. The runtime capture has 142,713
    // text rows with one state. callDesc H/L word order is opposite to Composer's
    // display. Pairing still requires the same texture on both sides, so a message
    // change never blends different text. Native line origins are y=800 and 828 qpx.
    static constexpr uint32_t Wr64CelestialDpTextCombinerH  = 0xFFFCF279u;
    static constexpr uint32_t Wr64CelestialDpTextCombinerL  = 0xFCFFFFFFu;
    static constexpr uint32_t Wr64CelestialDpTextOtherModeH = 0x00000CFFu;
    static constexpr uint32_t Wr64CelestialDpTextOtherModeL = 0x00504240u;
    static constexpr int32_t  Wr64CelestialDpTextUlyMin = 780;
    static constexpr int32_t  Wr64CelestialDpTextUlyMax = 880;

    inline bool wr64CelestialDpTextState(uint32_t combinerH, uint32_t combinerL,
        uint32_t otherModeH, uint32_t otherModeL, int32_t uly)
    {
        return (combinerH == Wr64CelestialDpTextCombinerH) &&
               (combinerL == Wr64CelestialDpTextCombinerL) &&
               (otherModeH == Wr64CelestialDpTextOtherModeH) &&
               (otherModeL == Wr64CelestialDpTextOtherModeL) &&
               (uly >= Wr64CelestialDpTextUlyMin) &&
               (uly <= Wr64CelestialDpTextUlyMax);
    }

    // Scrolling glyphs are four stacked 20-qpx strips at y=788/808/828/848, each
    // with its own baked texture. Composer measurements distinguish their render
    // state from the message-box state above: combiner H=FF2FFFFF/L=FC119623,
    // other mode H=00002CFF/L=00504240, and primitive alpha 2/3.
    // Claim the strips separately so letter motion follows the interpolated box.
    static constexpr uint32_t Wr64CelestialDpStripCombinerH  = 0xFF2FFFFFu;
    static constexpr uint32_t Wr64CelestialDpStripCombinerL  = 0xFC119623u;
    static constexpr uint32_t Wr64CelestialDpStripOtherModeH = 0x00002CFFu;
    static constexpr uint32_t Wr64CelestialDpStripOtherModeL = 0x00504240u;

    inline bool wr64CelestialDpStripState(uint32_t combinerH, uint32_t combinerL,
        uint32_t otherModeH, uint32_t otherModeL, int32_t uly)
    {
        return (combinerH == Wr64CelestialDpStripCombinerH) &&
               (combinerL == Wr64CelestialDpStripCombinerL) &&
               (otherModeH == Wr64CelestialDpStripOtherModeH) &&
               (otherModeL == Wr64CelestialDpStripOtherModeL) &&
               (uly >= Wr64CelestialDpTextUlyMin) &&
               (uly <= Wr64CelestialDpTextUlyMax);
    }

    // Printed once, the first time a letter strip is claimed. Also the
    // run script's binary gate.
    inline void wr64CelestialStripNote() {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        static bool announced = false;
        if (announced) {
            return;
        }
        announced = true;
        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
            "[celestial] letter strips claimed (the four-layer text rides the same blend as its box)\n"); }
        { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
    }

    // Diagnostic marker for forward UV folding on a pinned message rectangle.
    // Blending [cur -> cur-shift] keeps the moving left edge beneath its crop line;
    // backward folding would briefly reveal background at the start of each tick.
    inline void wr64CelestialPinnedNote() {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        static bool announced = false;
        if (announced) {
            return;
        }
        announced = true;
        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
            "[celestial] pinned message scroll folded forward (message slots only; the crop edge holds still)\n"); }
        { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
    }

    // Diagnostic marker for the message crop/rebake exception. Pair only the narrow
    // crop shape: identical left/top/bottom edges and a small right-edge reduction.
    // This preserves scrolling across a rebake without treating a message swap as
    // continuous motion.
    inline void wr64CelestialCropNote() {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        static bool announced = false;
        if (announced) {
            return;
        }
        announced = true;
        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
            "[celestial] cropped message re-bake paired (left-edge exit glides)\n"); }
        { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
    }

    inline void wr64CelestialFingerprintNote() {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        static bool announced = false;
        if (announced) {
            return;
        }
        announced = true;
        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
            "[celestial] message claimed by fingerprint (a texture the hash list never met)\n"); }
        { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
    }

    // The pairing pass sizes its per-texture claim arrays from this. It must
    // equal the number of textures wr64CelestialClaims accepts and the
    // number wr64CelestialTextureIndex can return an index for: the six
    // named constants at indices 0..5, then the sibling table from 6 up.
    static constexpr int Wr64CelestialTextureCount = 6 + Wr64CelestialDpTextSiblingCount;
    static_assert(Wr64CelestialTextureCount == 33,
        "the celestial claim list changed size without this note being updated");

    inline bool wr64CelestialClaims(uint64_t texture) {
        switch (texture) {
        case Wr64CelestialSunGlow:
        case Wr64CelestialSunDisk:
        case Wr64CelestialSunFlare:
        case Wr64CelestialSunDiskDP:
        case Wr64CelestialTcStar:
        case Wr64CelestialDpText:
            return true;
        default:
            break;
        }
        for (int i = 0; i < Wr64CelestialDpTextSiblingCount; i++) {
            if (texture == Wr64CelestialDpTextSiblings[i]) {
                return true;
            }
        }
        return false;
    }

    inline int wr64CelestialTextureIndex(uint64_t texture) {
        if (texture == Wr64CelestialSunGlow)   return 0;
        if (texture == Wr64CelestialSunDisk)   return 1;
        if (texture == Wr64CelestialSunFlare)  return 2;
        if (texture == Wr64CelestialSunDiskDP) return 3;
        if (texture == Wr64CelestialTcStar)    return 4;
        if (texture == Wr64CelestialDpText)    return 5;
        for (int i = 0; i < Wr64CelestialDpTextSiblingCount; i++) {
            if (texture == Wr64CelestialDpTextSiblings[i]) {
                return 6 + i;
            }
        }
        return -1;
    }

    // Half the native screen width (424 px * 4 quarter-px / 2), per tick,
    // measured on the rect CENTRE. See the header comment for why this is
    // generous on purpose.
    static constexpr float Wr64CelestialMaxStepQuarterPx = 848.0f;

    // Dolphin Park's native sun rectangle is 96 quarter-pixels square. Capture
    // wr64-rect-track-corner-20260804_094257.csv shows the game clamping its upper
    // edge to zero and retaining a shortened rectangle, with a 48-qpx resting height.
    // Primitive alpha is zero for both visible and parked states, so it cannot
    // identify the unwanted remnant.
    //
    // The renderer suppresses shortened authored disk rectangles after interpolation,
    // except for reconstructed transit pairs described below. A full rectangle that
    // just touches the edge remains visible. Scope this rule to the Dolphin Park disk;
    // flares legitimately touch the same edge. Keep parked rectangles in the pairing
    // pass so a subsequent transit can be reconstructed continuously.
    static constexpr int32_t Wr64CelestialDpFullRectQuarterPx = 96;

    // Reconstruct top-edge transits from the shortened rectangle. Its clamped motion
    // is compressed 2:1: lry=96 maps to a full disk at uly=0, and lry=48 maps to a
    // fully hidden disk at uly=-96. Thus uly'=(lry-96)*2 and lry'=uly'+96.
    // Pair while height moves by at least 8 qpx/tick, or while crossing between full
    // and shortened states. Captured transits step 12-20 qpx; parked wobble stays
    // below 8. Unpaired plateau/deep-park frames remain suppressed.
    inline bool wr64CelestialDpParkShortened(int32_t uly, int32_t lry) {
        return (uly == 0) && (lry < Wr64CelestialDpFullRectQuarterPx);
    }

    static constexpr int32_t Wr64CelestialDpParkTransitStepQuarterPx = 8;

    // Allow shortened exit frames for six ticks after the last full disk. Captured
    // exits take 3-4 ticks; the bounded tail excludes the persistent parked plateau.
    static constexpr int64_t Wr64CelestialDpExitTailTicks = 6;

    // Printed once, the first time a park transit is reconstructed and
    // paired. Also the run script's binary gate.
    inline void wr64CelestialUnparkNote() {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        static bool announced = false;
        if (announced) {
            return;
        }
        announced = true;
        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
            "[celestial] DP sun transit reconstructed (full clamp inverse: park height 48 is fully off-screen)\n"); }
        { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
    }

    // Printed once, the first time a parked rect is actually suppressed, so
    // the run log can PROVE the rule fired and the binary carries a string
    // the build and run gates can find. Same shape as wr64CelestialNote.
    // "whole-or-nothing" is R3's distinguishing marker: R2 binaries carry
    // the shorter sentence, so a gate looking for this exact text cannot
    // pass on a stale R2 executable.
    inline void wr64CelestialParkNote() {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        static bool announced = false;
        if (announced) {
            return;
        }
        announced = true;
        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
            "[celestial] parked sun rect suppressed (Dolphin Park, top edge, whole-or-nothing)\n"); }
        { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
    }

    // One key formula, used by the pairing pass AND the renderer lookup. Two
    // hand-rolled copies of a bit-packing is how an off-by-one in a shift
    // becomes a fix that silently never applies.
    inline uint64_t wr64CelestialRectKey(uint32_t fbPairIndex, uint32_t projIndex, uint32_t callIndex) {
        return (uint64_t(fbPairIndex) << 40) | (uint64_t(projIndex) << 20) | uint64_t(callIndex);
    }

    // Default ON, like every validated correction in this tree. The variable
    // exists so the SAME BINARY can be A/B'd against the old behaviour; it is
    // not a feature switch.
    inline bool wr64CelestialRectLerpEnabled() {
        static const bool enabled = [] {
            const char *value = std::getenv("WR64_CELESTIAL_RECT_LERP");
            return (value == nullptr) || (value[0] != '0');
        }();
        return enabled;
    }

    // Printed once, the first time a paired rect's UVs actually moved
    // between two frames - the scrolling-text left-edge case. SUNEXIT R2:
    // the whole UV fold, forward AND backward, is entered only for the
    // message slots now - an edge-clamped sun takes the plain corner
    // blend, which keeps the screen edge sealed and the disk and glow
    // glued through a clipped exit. Measured
    // 2026-08-05: when a DP message's rect reaches the screen's left edge
    // the game pins the corner and advances the TEXREC command's S start,
    // which RT64 bakes into per-vertex texture coordinates at decode time.
    // The pairing pass folds that UV shift into the previous rect's corners
    // so the validated rect blend carries the letters too. This line in a
    // log is the proof the fold fired on real play; R4's tile-based attempt
    // never printed its line, which is how the wrong window was caught.
    inline void wr64CelestialUvNote() {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        static bool announced = false;
        if (announced) {
            return;
        }
        announced = true;
        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
            "[celestial] text UV scroll folded into the rect blend (message slots only; letters glide with the box)\n"); }
        { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
    }

    // Printed once, the first time a paired rect's TILE actually moved
    // between two frames. Measured 2026-08-05: the DP text does NOT scroll
    // through the tile (this note stayed silent through a full DP session -
    // the scroll is in the per-vertex UVs, see wr64CelestialUvNote). The
    // tile path stays as the correct guard for any future claimed rect that
    // does scroll its tile window.
    inline void wr64CelestialTileNote() {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        static bool announced = false;
        if (announced) {
            return;
        }
        announced = true;
        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
            "[celestial] text tile scroll interpolated (letters ride the same blend as the box)\n"); }
        { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
    }

    // Printed once, the first time a pair is actually made. A silent pass and
    // an absent pass look identical from the couch.
    inline void wr64CelestialNote(size_t paired) {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        static bool announced = false;
        if (announced || (paired == 0)) {
            return;
        }
        announced = true;
        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
            "[celestial] APPLYING rect interpolation (%zu rect(s) paired on first hit; "
            "equal-count + continuity guarded)\n", paired); }
        { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
    }
};
