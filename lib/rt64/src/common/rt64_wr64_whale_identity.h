//
// WR64 Southern Island whales - named by MATRIX ADDRESS.
//
// The third family on the dolphin recipe, after the dolphins themselves and the
// Drake Lake school. It is here because the whales are the last measured object
// on the list and because the handover's conclusion about them was wrong in a
// way worth writing down.
//
// THE HANDOVER SAID THE KEY WAS (ADDRESS, SCALE). IT IS NOT, AND PUTTING SCALE
// IN THE KEY WOULD HAVE REINTRODUCED A BUG THAT WAS ALREADY FIXED ONCE.
//
// The observation behind it is real: one of the two segment-6 blocks flips its
// scale between 0.20 and 0.05 thirteen times across the run, and at each flip
// the slot is genuinely holding a different animal. The conclusion drawn from it
// was that the id had to carry the scale so the two would not be confused.
//
// That is R2's mistake in another costume. An id that changes is an id that
// LAPSES, and buildTransformIdMap matches the current frame's map against the
// previous frame's by equality: a slot whose id changes on the flip frame finds
// no partner on that frame AND no partner on the next one, because the next
// frame's new id is absent from the flip frame's map. Both of those frames have
// already been stamped with the full interpolation recipe, and
// RigidBody::updateLinear only runs its own discontinuity gate for
// G_EX_COMPONENT_AUTO - so a transform carrying INTERPOLATE is smoothed
// unconditionally against whatever the heuristic matcher hands it. The whole R4
// block in rt64_game_frame.cpp is about that mechanism.
//
// So the scale stays OUT of the key and becomes a SKIP TRIGGER instead. The id
// is the address and never lapses; the flip frame keeps its name and loses its
// smoothing. Measured, the two agree completely - all 50 flip transitions also
// move at least 236 units, so the position test alone would have caught every
// one - but the scale test is sharper and costs a divide, so both are armed.
//
// Three whales, two groups, and they are not one model drawn twice
// -----------------------------------------------------------------
// The handover also said "two whales = one model drawn twice at different
// scales". Measured across 13,543 frames:
//
//   whale_g1   SEGMENT 3, 12 addresses at 0x100 stride, 0x0300E788..0x0300F288
//              ONE whale. All twelve pieces sit inside a 45-unit ball and
//              articulate within it. Scale 0.1000 on every address, always.
//              Live on ALL 4,170 of its frames - never culled, never recycled.
//              The cleanest object in this game: the address alone is a
//              complete identity and the continuity test never fires on it.
//
//   whale_g2   SEGMENT 6, 10 addresses at 0x40 stride, TWO blocks of five:
//                06000610..06000710   scale flips 0.20 <-> 0.05, thirteen runs
//                06000790..06000890   scale 0.05, one unbroken run
//              TWO whales, one per block. Live on 1,020 frames.
//
// g1 and g2 are different animals, not one drawn twice. On the 167 frames
// carrying both, the closest g1-to-g2 distance is 3,514 units and the median is
// 10,021. Different segments, different strides, different lifetimes - 4,170
// frames against 1,020, and different render states besides.
//
// WITHIN g2, though, the two blocks ARE the same model at two sizes, and the
// arithmetic says so: at scale 0.20 block A's pieces span 363 units and at 0.05
// block B's span 90, and 363/90 = 4.03 against a scale ratio of exactly 4. That
// is what the flip is - the slot changing which of the two it is drawing.
//
// THE ADDRESSES ARE SHARED WITH HALF THE GAME, AND THAT IS FINE
// --------------------------------------------------------------
// whale_g2's ten segment-6 addresses are the same ten the dolphins, the Drake
// Lake school and the tropical fish use, and the seagulls use them too - on 853
// of the same frames. Not one of those is a hazard, for two separate reasons:
//
//   Not one shares a (frame, address) pair with a whale. 0 of 9,885.
//   No texture appears in more than one family. Checked pairwise across all
//   nine families in the capture: zero overlaps.
//
// The claim reads the texture before it ever reads an address, so the address
// sharing never comes up. That is the rule stated once in
// rt64_wr64_dolphin_identity.h and it has now held for four families.
//
// The seagulls are worth naming separately because they are the one family that
// coexists in the same frames: they are keyed by RANK inside 0x57600000
// (rt64_wr64_sprite_families.h), not by address, so there is no id to collide
// with either.
//
// THE THRESHOLD
// -------------
// Adjacent-frame steps at constant scale:
//
//     whale_g1   49,476 steps   median 44.64   p99 59.34   MAX 67.49
//     whale_g2    9,755 steps   median 40.57   p99 64.48   MAX 132.35
//     ------------------------------------------------------------------
//     smallest step across a scale flip                          236.28
//
// So 180.0, above both maxima and below the smallest discontinuity.
//
// g2's twenty-five steps between 80 and 132 were checked one by one and every
// single one is address 0x06000690 ALONE, moving 80 to 132 while its four
// blockmates move 50 to 65 on the same frame. That is the piece furthest from
// the block's centre - 211 units out at scale 0.20 - swinging as the animal
// turns. A limb at the end of a body travels furthest. It is motion, not a
// handover, and the threshold has to clear it.
//
// TRIANGLE COUNT IS NOT PART OF THE KEY, same as the dolphins: g1's pieces were
// seen at 1 through 6 triangles and g2's at 4 through 13. An exact count would
// claim them only sometimes, which is how a family ends up half-named.
//
// g1 CARRIES TWO RENDER STATES AND BOTH ARE ACCEPTED. Every one of its eleven
// textures appears under both, so the state cannot narrow the claim there and
// requiring one of them would drop 28,608 of 100,080 draws - a whale rendered
// with two thirds of itself named. g2's six textures each appear under exactly
// one state, the game's shared animal setting.
//
// This is a fix, so it is compiled in and always on. There is no variable.
//

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <set>

namespace RT64 {
    // ------------------------------------------------------------- the groups --
    static constexpr int Wr64WhaleGroupNone = 0;
    static constexpr int Wr64WhaleGroupG1   = 1;
    static constexpr int Wr64WhaleGroupG2   = 2;

    // g1's two render states. Both accepted; see the header block.
    static constexpr uint32_t Wr64WhaleG1CombinerHA  = 0xFFFFF238u;
    static constexpr uint32_t Wr64WhaleG1CombinerLA  = 0xFC127FFFu;
    static constexpr uint32_t Wr64WhaleG1OtherModeHA = 0x0018ACFFu;
    static constexpr uint32_t Wr64WhaleG1OtherModeLA = 0xC8112078u;

    static constexpr uint32_t Wr64WhaleG1CombinerHB  = 0xFFFFF3F9u;
    static constexpr uint32_t Wr64WhaleG1CombinerLB  = 0xFC127E24u;
    static constexpr uint32_t Wr64WhaleG1OtherModeHB = 0x0008ACFFu;
    static constexpr uint32_t Wr64WhaleG1OtherModeLB = 0x00552078u;

    // g2's single state - the game's shared animal setting, worn by the tropical
    // fish, the seagulls, the dolphins and the Drake Lake school alike. It
    // discriminates nothing on its own; the texture does the work.
    static constexpr uint32_t Wr64WhaleG2CombinerH  = 0xFFFFF238u;
    static constexpr uint32_t Wr64WhaleG2CombinerL  = 0xFC127FFFu;
    static constexpr uint32_t Wr64WhaleG2OtherModeH = 0x00182CFFu;
    static constexpr uint32_t Wr64WhaleG2OtherModeL = 0xC8113078u;

    // Eleven pieces of the segment-3 whale, all captured on Southern Island.
    inline const std::set<uint64_t> &wr64WhaleG1Textures() {
        static const std::set<uint64_t> textures = {
            0x482331AC450564E2ULL,
            0x567DFF81F4AA3880ULL,
            0x63C781AA25BE36A9ULL,
            0x881DD4775FBA91AAULL,
            0x941ACFE6EABED169ULL,
            0x9FC3A165B8D0F63EULL,
            0xA48B25B56BDC7F73ULL,
            0xC417848AC758985FULL,
            0xD27BAEEF67D18D73ULL,
            0xE68E048DEE5D10EAULL,
            0xFA988B67A76DE549ULL,
        };
        return textures;
    }

    // Six pieces of the segment-6 whales. The same six serve both blocks, which
    // is the other half of the evidence that the blocks are one model at two
    // sizes.
    inline const std::set<uint64_t> &wr64WhaleG2Textures() {
        static const std::set<uint64_t> textures = {
            0x2B2B0452B5B6FA70ULL,
            0x577A3C810CB0AE45ULL,
            0xA3B1F651ACE68FD6ULL,
            0xAE8AE5E6F2B06CE2ULL,
            0xB878872207DB804CULL,
            0xF633FB1461BACE0EULL,
        };
        return textures;
    }

    // Returns which group this draw belongs to, or Wr64WhaleGroupNone.
    // TEXTURE AND RENDER STATE FIRST, address second - the segment-6 block shares
    // every one of its addresses with four other families.
    inline int wr64WhaleGroupForDraw(uint64_t tmemHash,
        uint32_t combinerH, uint32_t combinerL, uint32_t otherModeH, uint32_t otherModeL)
    {
        if (wr64WhaleG1Textures().count(tmemHash) > 0) {
            const bool stateA = (combinerH  == Wr64WhaleG1CombinerHA)  &&
                                (combinerL  == Wr64WhaleG1CombinerLA)  &&
                                (otherModeH == Wr64WhaleG1OtherModeHA) &&
                                (otherModeL == Wr64WhaleG1OtherModeLA);
            const bool stateB = (combinerH  == Wr64WhaleG1CombinerHB)  &&
                                (combinerL  == Wr64WhaleG1CombinerLB)  &&
                                (otherModeH == Wr64WhaleG1OtherModeHB) &&
                                (otherModeL == Wr64WhaleG1OtherModeLB);
            return (stateA || stateB) ? Wr64WhaleGroupG1 : Wr64WhaleGroupNone;
        }

        if (wr64WhaleG2Textures().count(tmemHash) > 0) {
            if ((combinerH  == Wr64WhaleG2CombinerH)  &&
                (combinerL  == Wr64WhaleG2CombinerL)  &&
                (otherModeH == Wr64WhaleG2OtherModeH) &&
                (otherModeL == Wr64WhaleG2OtherModeL))
            {
                return Wr64WhaleGroupG2;
            }
        }

        return Wr64WhaleGroupNone;
    }

    // ------------------------------------------------------------------- ids --
    //
    // One page per group. Clear of every id already in use: 0x57000000
    // articulated limbs, 0x57100000 watercraft selector, 0x57200000 course map,
    // 0x57400000 gantry, 0x57500000 tropical fish, 0x57524300 sky, 0x57600000
    // sprite families, 0x57700000 dolphins, 0x57800000 Drake Lake school.
    //
    // Two pages rather than one because the groups live in different SEGMENTS,
    // and folding both into one page would make the id depend on nothing but the
    // 16-bit offset - so a future course putting a g2-style whale at g1's offset
    // would mint one id for two animals. The low 16 bits are the address offset
    // verbatim either way, so an id read out of a trace names its slot.
    static constexpr uint32_t Wr64WhaleG1IdBase = 0x57900000u;
    static constexpr uint32_t Wr64WhaleG2IdBase = 0x57A00000u;

    static constexpr uint32_t Wr64WhaleG1AddressSegment = 0x03000000u;
    static constexpr uint32_t Wr64WhaleG2AddressSegment = 0x06000000u;
    static constexpr uint32_t Wr64WhaleAddressMask      = 0xFFFF0000u;

    // The group decides which segment is acceptable, so a segment-3 draw can
    // never mint a segment-6 id or the reverse.
    inline uint32_t wr64WhaleIdForAddress(uint32_t segAddress, int group) {
        uint32_t segment = 0;
        uint32_t base = 0;
        if (group == Wr64WhaleGroupG1) {
            segment = Wr64WhaleG1AddressSegment;
            base = Wr64WhaleG1IdBase;
        }
        else if (group == Wr64WhaleGroupG2) {
            segment = Wr64WhaleG2AddressSegment;
            base = Wr64WhaleG2IdBase;
        }
        else {
            return 0;
        }

        if ((segAddress & Wr64WhaleAddressMask) != segment) {
            return 0;
        }

        const uint32_t offset = segAddress & 0x0000FFFFu;
        if (offset == 0) {
            return 0;
        }

        return base | offset;
    }

    inline bool wr64WhaleIsOurs(uint32_t matrixId) {
        const uint32_t page = matrixId & 0xFFFF0000u;
        return (page == Wr64WhaleG1IdBase) || (page == Wr64WhaleG2IdBase);
    }

    // ------------------------------------------------------- the continuity --
    //
    // 180.0 units per frame. Above g1's largest observed step (67.49 over 49,476
    // transitions) and g2's largest (132.35 over 9,755), below the smallest step
    // across a scale flip (236.28 over 50). See the header block for why g2's
    // 80-to-132 tail is one articulating piece rather than a handover.
    static constexpr float Wr64WhaleContinuityUnits = 180.0f;

    // THE SECOND TRIGGER, and the one that makes the first insurance rather than
    // the mechanism. A whale does not change size; a slot that reports a
    // different scale than it did last frame is holding a different animal.
    //
    // A RATIO, NOT AN EQUALITY, AND ON THE X BASIS. The first draft of this
    // compared the two floats exactly, on the reasoning that the game writes the
    // matrix and the same bytes give the same length every frame. The capture
    // says otherwise, because "scale" here is the LENGTH OF A BASIS VECTOR and
    // the animal's rotation is baked into the same matrix:
    //
    //     axis      max ratio between consecutive frames at one size
    //     scale_x   1.0000
    //     scale_y   1.0000
    //     scale_z   1.0080          <-- the rotation lands here
    //
    //     smallest ratio across a real size change:  4.0000 on x and y
    //
    // So x and y are clean and z jitters by up to 0.8%, which an exact
    // comparison would have reported as a size change on every frame the whale
    // turned - snapping a swimming whale several times a second. The X basis is
    // read, and the test is a ratio with a trip point of 2.0: 2x the worst
    // jitter any axis shows and half the real change. Nothing has ever been
    // measured between 1.008 and 4.0.
    //
    // Scale is deliberately NOT part of the id. See the header block: an id that
    // changes is an id that lapses, and a lapsed id costs two frames of pairing
    // with the safety gate bypassed on both.
    static constexpr float Wr64WhaleScaleRatioTrip = 2.0f;

    inline bool wr64WhaleScaleChanged(float previousScale, float currentScale) {
        // A zero or negative basis length is a degenerate matrix, not a resize.
        // Reporting it as a size change would snap on a frame that carries no
        // information either way.
        if (!(previousScale > 0.0f) || !(currentScale > 0.0f)) {
            return false;
        }

        const float ratio = (currentScale > previousScale)
            ? (currentScale / previousScale)
            : (previousScale / currentScale);
        return ratio > Wr64WhaleScaleRatioTrip;
    }

    // Frames are pipelined, so "the previous frame" is a small window rather than
    // exactly one back. A LABEL, not a gate - the R4 demotion. Both g1 and g2
    // have real absences in the capture (g1 has 47 frame gaps, g2 has 8), and a
    // return from one is exactly the case where suppressing interpolation costs
    // nothing because there was nothing to interpolate from.
    static constexpr uint64_t Wr64WhaleContinuityFrames = 3;

    // --------------------------------------------------------------- announce --
    //
    // A validated fix is compiled in. There is no variable, not even an inverted
    // one - a fix that can be switched off is a fix nobody can rely on.
    inline bool wr64WhaleIdentityEnabled() {
        return true;
    }

    inline void wr64WhaleNote(size_t stamped, size_t skipped, size_t collided,
        size_t movedPosition, size_t movedScale)
    {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        static bool announced = false;
        if (!announced) {
            announced = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[whale] APPLYING (%zu + %zu textures, id = matrix address,"
                " continuity %.0f units, scale change also snaps)\n",
                wr64WhaleG1Textures().size(), wr64WhaleG2Textures().size(),
                double(Wr64WhaleContinuityUnits)); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        static bool reported = false;
        if (!reported && (stamped > 0)) {
            reported = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[whale] stamped %zu transform(s) by address on first hit"
                " (%zu outside the group's segment, %zu id collisions)\n",
                stamped, skipped, collided); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        // The two triggers are counted separately on purpose. They agreed on all
        // 50 flips in the capture, so a run where the scale column climbs and the
        // position column does not - or the reverse - is new behaviour and worth
        // seeing. Printed on doubling so a long race does not spam.
        static size_t lastPosition = 0;
        static size_t lastScale = 0;
        if ((movedPosition > 0) || (movedScale > 0)) {
            lastPosition += movedPosition;
            lastScale += movedScale;
            static size_t nextReport = 1;
            if ((lastPosition + lastScale) >= nextReport) {
                nextReport = (lastPosition + lastScale) * 2;
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                    "[whale] %zu transform(s) so far kept their name and snapped:"
                    " %zu moved too far, %zu changed size.\n",
                    lastPosition + lastScale, lastPosition, lastScale); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            }
        }
    }
};
