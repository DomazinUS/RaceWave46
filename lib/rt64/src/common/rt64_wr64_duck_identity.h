// WR64 Drake Lake ducks: address-based identity with whole-animal discontinuity.
//
// Composer capture 4/frame 1931 identifies seven textures in segment 6. Each duck
// uses seven consecutive 0x40-byte matrix slots and twelve draws: six single-draw
// slots and one slot shared by the six detail textures. Texture C7E16FE8A5BC21ED
// instead identifies static scenery and must not be treated as a duck.
//
// Claim by texture and render state, without a triangle-count restriction: several
// parts change triangle count during animation. Stable addresses avoid nearest-
// position pairing between neighboring pieces when the duck moves faster than
// their separation.
//
// Real movement and slot-relocation distances overlap, so per-piece continuity
// decisions can tear the animal. Reconstruct consecutive seven-slot groups each
// frame and snap the whole group when any piece is discontinuous. Preserve IDs,
// skip placement interpolation for that tick, and keep vertex/tile animation on.
// Do not retain group membership across frames because the allocation window moves.

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <cstddef>
#include <cstdint>
#include <cstdio>

namespace RT64 {
    // ---------------------------------------------------------------- assets --
    //
    // The seven textures of one duck, in Composer layer order. ALL SEVEN ARE
    // REQUIRED. Five of them are invisible to the object census - not rare,
    // absent - because the census keeps one row per (frame, transform), first
    // draw wins, and those five are never a transform's first draw. A list built
    // from the census alone carries two of seven and measures a third of the
    // animal. That is exactly how this family came to be "refused" once already.
    static constexpr uint64_t Wr64DuckTextureBody   = 0xF80AED736EA5C5E3ULL; // L78, six per duck
    static constexpr uint64_t Wr64DuckTextureD1     = 0x87D653A4EFF244E5ULL; // L79
    static constexpr uint64_t Wr64DuckTextureD2     = 0x0802E965833AF77BULL; // L80
    static constexpr uint64_t Wr64DuckTextureD3     = 0xAF7F087C761F318FULL; // L81
    static constexpr uint64_t Wr64DuckTextureD4     = 0x8EB5DF4336C95518ULL; // L82
    static constexpr uint64_t Wr64DuckTextureD5     = 0xEEC5FF0C276EE611ULL; // L83
    static constexpr uint64_t Wr64DuckTextureD6     = 0xE3BF645F42572CB5ULL; // L84

    static constexpr uint32_t Wr64DuckCombinerH  = 0xFFFFF238u;
    static constexpr uint32_t Wr64DuckCombinerL  = 0xFC127FFFu;
    static constexpr uint32_t Wr64DuckOtherModeH = 0x00182CFFu;
    static constexpr uint32_t Wr64DuckOtherModeL = 0xC8113078u;

    inline bool wr64DuckTextureClaimed(uint64_t tmemHash) {
        return (tmemHash == Wr64DuckTextureBody)
            || (tmemHash == Wr64DuckTextureD1)
            || (tmemHash == Wr64DuckTextureD2)
            || (tmemHash == Wr64DuckTextureD3)
            || (tmemHash == Wr64DuckTextureD4)
            || (tmemHash == Wr64DuckTextureD5)
            || (tmemHash == Wr64DuckTextureD6);
    }

    // Triangle count is NOT a parameter. See the header block.
    inline bool wr64DuckClaims(uint64_t tmemHash,
        uint32_t combinerH, uint32_t combinerL, uint32_t otherModeH, uint32_t otherModeL)
    {
        if (!wr64DuckTextureClaimed(tmemHash)) { return false; }
        if (combinerH  != Wr64DuckCombinerH)   { return false; }
        if (combinerL  != Wr64DuckCombinerL)   { return false; }
        if (otherModeH != Wr64DuckOtherModeH)  { return false; }
        if (otherModeL != Wr64DuckOtherModeL)  { return false; }
        return true;
    }

    // ------------------------------------------------------------------- ids --
    //
    // Segment 6 and its low 64 KiB, the same window the dolphins and the lake
    // fish use. Measured addresses run 0x060005D0 to 0x06001190 at 0x40 stride,
    // 48 of them over the session. Anything outside segment 6 is not covered by
    // this measurement, gets no id, and keeps today's behaviour rather than a
    // guessed one.
    static constexpr uint32_t Wr64DuckAddressSegment = 0x06000000u;
    static constexpr uint32_t Wr64DuckAddressMask    = 0xFFFF0000u;

    // The stride between a duck's consecutive pieces, and the only thing used to
    // rebuild the block. Derived per frame from the claimed set, never stored.
    static constexpr uint32_t Wr64DuckBlockStride = 0x40u;

    // Clear of every id already in use: 0x57000000 articulated limbs, 0x57100000
    // watercraft selector, 0x57200000 course map, 0x57400000 gantry, 0x57500000
    // tropical fish, 0x57524300 sky, 0x57600000 sprite families, 0x57700000
    // dolphins, 0x57800000 lake fish, 0x57900000 + 0x57A00000 whales. Each claims
    // a whole 64 KiB page and so does this one.
    //
    // A SEPARATE PAGE IS DELIBERATE even where two families never share a frame.
    // The low 16 bits are the address offset verbatim, so a shared page would
    // mint one id from two different animals and a trace could not say which
    // wrote it. Measured: 0 (frame, address) pairs shared with the dolphins and 0
    // with the lake fish, over the whole capture.
    static constexpr uint32_t Wr64DuckIdBase = 0x57B00000u;

    inline uint32_t wr64DuckIdForAddress(uint32_t segAddress) {
        if ((segAddress & Wr64DuckAddressMask) != Wr64DuckAddressSegment) {
            return 0;
        }

        const uint32_t offset = segAddress & 0x0000FFFFu;
        if (offset == 0) {
            return 0;
        }

        return Wr64DuckIdBase | offset;
    }

    inline bool wr64DuckIsOurs(uint32_t matrixId) {
        return (matrixId & 0xFFFF0000u) == Wr64DuckIdBase;
    }

    // ------------------------------------------------------- the continuity --
    //
    // 100.0 units per frame. The bands overlap here, so this is not the fish's
    // "any value in the empty band" situation and the number was chosen from a
    // sweep rather than from a gap:
    //
    //     threshold   re-slots caught      real motion falsely snapped
    //          70      108/122  88.5%        1,289/42,535   3.03%
    //         100      108/122  88.5%        1,261/42,535   2.96%
    //         200       95/122  77.9%        1,035/42,535   2.43%
    //         400       79/122  64.8%          515/42,535   1.21%
    //
    // 70 and 100 catch the same 108, so 100 is taken for the smaller false-snap
    // count. The bias is deliberately toward catching re-slots: a false snap
    // costs one frame of smoothing, a missed one interpolates a duck's piece into
    // another of its own pieces.
    //
    // The whole-block rule above is what makes the residue safe. A missed re-slot
    // on one piece can no longer tear the animal, because if any piece of the
    // block trips, all of them snap.
    static constexpr float Wr64DuckContinuityUnits = 100.0f;

    // --------------------------------------------------------------- announce --
    //
    // A validated fix is compiled in. There is no variable, not even an inverted
    // one - a fix that can be switched off is a fix nobody can rely on.
    inline bool wr64DuckIdentityEnabled() {
        return true;
    }

    inline void wr64DuckNote(size_t stamped, size_t skipped, size_t collided,
        size_t moved, size_t blockPropagated)
    {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        static bool announced = false;
        if (!announced) {
            announced = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[duck] APPLYING (7 textures, id = segment-6 matrix address,"
                " continuity %.0f units, snapped by whole 0x%X block)\n",
                double(Wr64DuckContinuityUnits), Wr64DuckBlockStride); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        static bool reported = false;
        if (!reported && (stamped > 0)) {
            reported = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[duck] stamped %zu transform(s) by address on first hit"
                " (%zu outside segment 6, %zu id collisions, %zu snapped)\n",
                stamped, skipped, collided, moved); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        // Two counters on purpose. blockPropagated is how many pieces snapped
        // ONLY because a blockmate tripped - that is the whole-block rule doing
        // its job, and it is the number that would have been torn frames under a
        // per-piece rule. If it ever reads zero across a whole race while moved
        // climbs, the block reconstruction has stopped working and the animal is
        // back to coming apart.
        static size_t lastMoved = 0;
        static size_t lastProp = 0;
        if (moved > 0) {
            lastMoved += moved;
            lastProp += blockPropagated;
            static size_t nextReport = 1;
            if (lastMoved >= nextReport) {
                nextReport = lastMoved * 2;
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                    "[duck] %zu transform(s) so far kept their name and snapped"
                    " (%zu of them because a blockmate did: the duck moves whole)\n",
                    lastMoved, lastProp); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            }
        }
    }
};
