//
// WR64 dolphin identity - named by MATRIX ADDRESS, not by rank.
//
// What is different about this one
// --------------------------------
// Every family before it names its members by their ORDER among the claimed
// transforms. That was always a workaround: the game emits no G_EX_MATRIXGROUP,
// so every transform arrives as G_EX_ID_AUTO, buildTransformIdMap skips it, and
// pairing falls to a heuristic. Rank replaces the heuristic with a stable
// position in a sorted set - which only means anything while the set holds its
// shape and its size.
//
// It did not hold for the dolphins. Measured against true nearest-neighbour
// pairing, rank was 94.7% correct with the animals 853 units apart, so the 5.3%
// would slide a dolphin most of a screen once interpolation was forced on. That
// is the R1 buoy-arrow failure at four times the distance, and it is why the
// dolphins were refused twice.
//
// This names them by the address their matrix was read from instead.
//
// The measurement that changed the answer  (Sunset Bay, 2026-07-31)
// -----------------------------------------------------------------
//   73,707 adjacent-frame transitions, threshold 10x the dolphins' own median
//   motion of 24.9 units - the same factor the lerp gate itself uses.
//
//       rank      5.3%   wrong
//       address   0.06%  wrong        45 of 73,707
//
//   And the 45 are not spread out. They fall into THREE moments: frames 62 and
//   71-88, both inside the opening attract, and frames 769-770 where all fifteen
//   transforms move ~13,000 units at once, which is a scene cut. During actual
//   racing there was not one mis-identification. Eight frames out of 4,977
//   carry any at all.
//
// Why the same idea died for the start gantry
// -------------------------------------------
// The gantry's matrices live in SEGMENT 5: 0x05004140-0x050047C0, a pool of 27
// recycled scratch slots at 0x40 stride, each shared with 7 to 46 unrelated
// textures - the biggest occupant of 0x05004340 being the MAX POWER banner. An
// address-keyed id there would have told RT64 a banner and a traffic light were
// the same object.
//
// The dolphins live in SEGMENT 6, and the layout is per-object:
//
//     06000610 06000650 06000690 060006D0 06000710     dolphin 1
//     06000790 060007D0 06000810 06000850 06000890     dolphin 2
//     06000910 06000950 06000990 060009D0 06000A10     dolphin 3
//
// Five matrices per animal at 0x40 stride, three animals at 0x180 stride. The
// worst sharing on any of those fifteen slots is 4 textures - the pieces of that
// same dolphin - and not one is shared with another object. The segment number
// is the tell: segment 5 is scratch, segment 6 is model data.
//
// THE COUNT IS NOT A HAZARD HERE, which is the other thing the run corrected.
// The game draws all three dolphins - all fifteen transforms - every frame,
// whether they are on screen or not, on 98% of the run. The frames carrying only
// five are the opening Dolphin Park attract, 2 to 93. The 15/5 split in the
// earlier census was attract versus race, not culling.
//
// What is deliberately NOT done
// -----------------------------
// The lerp gate is not touched and must not be. The residual 0.06% are scene
// cuts, and refusing to smooth a scene cut is the gate behaving correctly. This
// does not replace the gate; it removes about 99% of what the gate currently has
// to catch.
//
// The address alone is not enough to claim a draw. The rule is texture AND
// render state first, address second - segment 6 carries plenty that is not a
// dolphin, and claiming by address would sweep all of it in.
//

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <cstdint>
#include <cstdio>
#include <set>

namespace RT64 {
    // One render state for all six pieces. Identical to the tropical fish, the
    // seagulls and the Southern Island whale's second group - this is the
    // game's animal setting, so it cannot discriminate on its own and the
    // texture is what does the work.
    static constexpr uint32_t Wr64DolphinCombinerH  = 0xFFFFF238u;
    static constexpr uint32_t Wr64DolphinCombinerL  = 0xFC127FFFu;
    static constexpr uint32_t Wr64DolphinOtherModeH = 0x00182CFFu;
    static constexpr uint32_t Wr64DolphinOtherModeL = 0xC8113078u;

    // All six captured with the Composer on Sunset Bay. Two of them -
    // 9DA7414E1DCAEC6C and F1A0EACF0258DBD7 - never appear in the object census
    // at all, because the census records only a transform's FIRST draw and they
    // are never first. Claiming a model's pieces from census data alone is what
    // left the Marine Fortress birds half-named and warping.
    //
    // TRIANGLE COUNT IS NOT PART OF THE KEY. The pieces were seen at 4, 25, 34
    // and 13 triangles, and an exact count would claim them only sometimes.
    inline const std::set<uint64_t> &wr64DolphinTextures() {
        static const std::set<uint64_t> textures = {
            0x197A0A7C04303EE1ULL,
            0x78B25A815B714850ULL,
            0x9DA7414E1DCAEC6CULL,
            0xF1A0EACF0258DBD7ULL,
            0x7AC3BE72B5A94F0DULL,
            0x2908030C8A159B72ULL,
        };
        return textures;
    }

    inline bool wr64DolphinClaims(uint64_t tmemHash,
        uint32_t combinerH, uint32_t combinerL, uint32_t otherModeH, uint32_t otherModeL)
    {
        if (combinerH  != Wr64DolphinCombinerH)  { return false; }
        if (combinerL  != Wr64DolphinCombinerL)  { return false; }
        if (otherModeH != Wr64DolphinOtherModeH) { return false; }
        if (otherModeL != Wr64DolphinOtherModeL) { return false; }
        return wr64DolphinTextures().count(tmemHash) > 0;
    }

    // ------------------------------------------------------------- the id --
    //
    // Segment 6 only, and only its low 64 KiB - the measured addresses run
    // 06000610 to 06000A10. An address outside that window is not something this
    // measurement covers, so it gets no id and stays on today's behaviour rather
    // than getting a guessed one.
    static constexpr uint32_t Wr64DolphinAddressSegment = 0x06000000u;
    static constexpr uint32_t Wr64DolphinAddressMask    = 0xFFFF0000u;

    // Clear of every id already in use: 0x57000000 articulated limbs,
    // 0x57100000 watercraft selector, 0x57200000 course map, 0x57400000 gantry,
    // 0x57500000 tropical fish, 0x57524300 sky, 0x57600000 sprite families
    // (stride 0x10000 per family). The low 16 bits are the address offset
    // verbatim, so an id read out of a trace names the slot it came from.
    static constexpr uint32_t Wr64DolphinIdBase = 0x57700000u;

    inline uint32_t wr64DolphinIdForAddress(uint32_t segAddress) {
        if ((segAddress & Wr64DolphinAddressMask) != Wr64DolphinAddressSegment) {
            return 0;
        }

        const uint32_t offset = segAddress & 0x0000FFFFu;
        if (offset == 0) {
            return 0;
        }

        return Wr64DolphinIdBase | offset;
    }

    inline bool wr64DolphinIsOurs(uint32_t matrixId) {
        return (matrixId & 0xFFFF0000u) == Wr64DolphinIdBase;
    }

    // ------------------------------------------------ R2: the continuity test --
    //
    // R1 SHIPPED AND WAS RIGHT MOST OF THE TIME AND WRONG VISIBLY.
    //
    // The full interpolation recipe does not merely enable smoothing, it takes
    // the safety net away. RigidBody::updateLinear reads:
    //
    //     if (componentInterpolation == G_EX_COMPONENT_AUTO) { ...gate... }
    //     else { lerpTranslation = (componentInterpolation == INTERPOLATE); }
    //
    // so a transform carrying INTERPOLATE is smoothed unconditionally and the
    // discontinuity gate never runs for it. The measurement said the address is
    // wrong in 45 of 73,707 transitions - and with the gate gone, those 45 stop
    // being a one-frame snap and become a smooth 300 to 500 unit GLIDE across
    // the water, which is more visible than the fault it replaced. Thirty of the
    // 45 are in the opening attract, which is exactly where it was reported.
    //
    // WHY THE OBVIOUS CORRECTION IS WRONG. Leaving the components on AUTO to get
    // the gate back was tried for the start gantry and is written up in
    // rt64_game_frame.cpp: the gate vetoes fast motion, and fast motion is
    // precisely when interpolation matters most - for the gantry, its exit; for
    // a dolphin, its leap. That trade makes the most visible moment the rough
    // one. The recipe stays whole.
    //
    // So the recipe is kept and the CLAIM is checked instead. An address is a
    // claim of identity, and an identity that teleports is not the same object:
    // if the thing at this address has moved further in one frame than a dolphin
    // can, either the address has been handed to a different animal or the game
    // has relocated this one, and either way that frame must not be smoothed.
    //
    // The threshold comes from the measurement, not from taste. Normal dolphin
    // motion on Sunset Bay: median 24.9 units per frame, p99 74.9, p99.9 93.6.
    // The genuine handovers ran from 288 units to 13,795. There is a clean
    // three-fold gap between 93.6 and 288 and this sits in the middle of it.
    //
    // THE DECISION TRACE CONFIRMED THAT GAP EXACTLY. Of 27,000 consecutive-frame
    // steps recorded on Sunset Bay, 26,950 are under 100 units and 50 are over
    // 200. Not one row lands between 100 and 200. This threshold sits in empty
    // space and there is no tuning left to do on it.
    static constexpr float Wr64DolphinContinuityUnits = 150.0f;

    // Frames are pipelined, so "the previous frame" is a small window rather
    // than exactly one back.
    //
    // R4 DEMOTED THIS FROM A GATE TO A LABEL. R2 tested the step only inside the
    // window, reasoning that past it there is no previous-frame transform to
    // slide between. The trace found the near miss: the dolphins returned at
    // frame 191 after 93 absent frames, 12,900 units from their last recorded
    // position, and were stamped with full interpolation because the age
    // disqualified the step. Nothing paired with them, so nothing happened. The
    // test now runs at any age, since suppressing interpolation on a frame that
    // had nothing to interpolate from costs exactly nothing.
    static constexpr uint64_t Wr64DolphinContinuityFrames = 3;

    // -------------------------------------- R4: what a discontinuity now does --
    //
    // R2 WITHDREW THE IDENTITY ON A DISCONTINUITY. THAT WAS THE DEFECT.
    //
    // It reads as the conservative choice - hand the frame back to the heuristic
    // matcher and the AUTO gate, which is where the transform was before any of
    // this work. It is not, because ids are matched per frame against the
    // previous frame's map. Withdrawing an id costs TWO frames of pairing: the
    // teleport frame has no id, and the frame after it has an id the previous
    // frame's map does not contain, so neither one pairs. The second frame is
    // the harmful one - it has already been stamped with the full recipe, so it
    // carries INTERPOLATE, which means updateLinear skips its gate and smooths
    // it unconditionally against whatever the heuristic matcher hands it.
    //
    // Measured on Sunset Bay the relocation is staggered over three consecutive
    // frames, so R2 cost three frames of dolphins in the heuristic matcher with
    // the safety gate bypassed, on the single event the test existed to catch.
    //
    // R4 keeps the id on every frame and drops the INTERPOLATION on the frame
    // that jumped, via G_EX_COMPONENT_SKIP. With decompose off, lerp() copies
    // every disabled component straight from the current matrix, so the frame
    // renders as one clean snap - what the console did - and the frame after it
    // pairs by id and interpolates normally. See the R4 block in
    // rt64_game_frame.cpp for the frame-by-frame account.

    // A validated fix is compiled in. There is no variable, not even an inverted
    // one - a fix that can be switched off is a fix nobody can rely on.
    inline bool wr64DolphinIdentityEnabled() {
        return true;
    }

    inline void wr64DolphinNote(size_t stamped, size_t skipped, size_t collided, size_t moved) {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        static bool announced = false;
        if (!announced) {
            announced = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[dolphin] APPLYING (%zu textures, id = segment-6 matrix address,"
                " continuity %.0f units)\n",
                wr64DolphinTextures().size(), double(Wr64DolphinContinuityUnits)); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        static bool reported = false;
        if (!reported && (stamped > 0)) {
            reported = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[dolphin] stamped %zu transform(s) by address on first hit"
                " (%zu outside segment 6, %zu id collisions, %zu snapped)\n",
                stamped, skipped, collided, moved); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        // The running total of suppressed frames, because the first-hit line will
        // almost always show zero: the relocations happen later, and a count that
        // only ever prints once cannot show that. Printed on change, so a clean
        // session stays quiet and a session with a burst says so.
        //
        // R4 CHANGED WHAT THIS SENTENCE MEANS. It used to say the address had
        // been refused. Nothing is refused now - the transform is named exactly
        // as it always is, and only the smoothing is dropped for that one frame.
        static size_t lastMoved = 0;
        if (moved > 0) {
            lastMoved += moved;
            static size_t nextReport = 1;
            if (lastMoved >= nextReport) {
                nextReport = lastMoved * 2;
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                    "[dolphin] %zu transform(s) so far kept their name and snapped:"
                    " they moved more than a dolphin can in one frame.\n", lastMoved); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            }
        }
    }
};
