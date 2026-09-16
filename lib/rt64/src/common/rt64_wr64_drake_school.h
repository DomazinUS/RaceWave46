// WR64 Drake Lake fish: identity from the segment-6 matrix address.
//
// Each fish has three pieces in consecutive 0x40-byte slots, but the allocation
// window slides. Fixed block indices or emission ranks would rename fish as that
// window moves. Claim by texture and render state before consulting the address;
// the address range also hosts dolphins in other scenes.
//
// The 2026-08-02 runtime capture contains 22,428 draws over 1,872 frames, with one
// transform per frame/address. Real adjacent-frame motion reaches 22.52 units;
// relocations start at 82.19. The 50-unit guard lies between those populations.
// Retain the ID on a relocation and skip matrix interpolation for that tick;
// withdrawing it also loses the following frame's explicit pairing. Keep
// decompose=false. The three pieces relocate together, so no persistent grouping
// is needed. Runtime duplicate-address guards handle shared slots separately.

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <cstddef>
#include <cstdint>
#include <cstdio>

namespace RT64 {
    // ---------------------------------------------------------------- assets --
    //
    // ONE texture, and it does all of the discriminating. The render state below
    // is the game's shared animal setting - identical to the tropical fish, the
    // seagulls, the dolphins and the Southern Island whale's second group - so it
    // narrows nothing on its own and is here to stop a future course's texture
    // collision from being claimed by accident.
    static constexpr uint64_t Wr64DrakeSchoolTexture = 0x2867951E0BDA7D0BULL;

    static constexpr uint32_t Wr64DrakeSchoolCombinerH  = 0xFFFFF238u;
    static constexpr uint32_t Wr64DrakeSchoolCombinerL  = 0xFC127FFFu;
    static constexpr uint32_t Wr64DrakeSchoolOtherModeH = 0x00182CFFu;
    static constexpr uint32_t Wr64DrakeSchoolOtherModeL = 0xC8113078u;

    // Two triangles on all 22,428 draws in the capture - a flat card, like the
    // tropical fish. This is a real tightening rather than the dolphins' case,
    // where the pieces were seen at 4, 25, 34 and 13 triangles and the count had
    // to be left out of the key.
    //
    // If a future course draws this fish at another detail level the claim simply
    // does not fire and those transforms keep today's behaviour. That is a safe
    // failure and it cannot half-claim a fish, because all three pieces carry the
    // same count as each other.
    static constexpr uint32_t Wr64DrakeSchoolTriangles = 2u;

    inline bool wr64DrakeSchoolClaims(uint64_t tmemHash, uint32_t triangleCount,
        uint32_t combinerH, uint32_t combinerL, uint32_t otherModeH, uint32_t otherModeL)
    {
        if (tmemHash      != Wr64DrakeSchoolTexture)    { return false; }
        if (triangleCount != Wr64DrakeSchoolTriangles)  { return false; }
        if (combinerH     != Wr64DrakeSchoolCombinerH)  { return false; }
        if (combinerL     != Wr64DrakeSchoolCombinerL)  { return false; }
        if (otherModeH    != Wr64DrakeSchoolOtherModeH) { return false; }
        if (otherModeL    != Wr64DrakeSchoolOtherModeL) { return false; }
        return true;
    }

    // ------------------------------------------------------------------- ids --
    //
    // Segment 6 and its low 64 KiB, the same window the dolphins use. The
    // measured addresses run 0x06000610 to 0x06001590; anything outside segment 6
    // is not covered by this measurement, so it gets no id and stays on today's
    // behaviour rather than getting a guessed one.
    static constexpr uint32_t Wr64DrakeSchoolAddressSegment = 0x06000000u;
    static constexpr uint32_t Wr64DrakeSchoolAddressMask    = 0xFFFF0000u;

    // Clear of every id already in use: 0x57000000 articulated limbs, 0x57100000
    // watercraft selector, 0x57200000 course map, 0x57400000 gantry, 0x57500000
    // tropical fish, 0x57524300 sky, 0x57600000 sprite families, 0x57700000
    // dolphins. Each of those claims a whole 64 KiB page and so does this one.
    //
    // A SEPARATE BASE FROM THE DOLPHINS IS DELIBERATE even though the two never
    // share a frame. The low 16 bits are the address offset verbatim, so the four
    // slots both animals use would otherwise produce the same id from two
    // different objects, and a trace could not tell which had written it.
    static constexpr uint32_t Wr64DrakeSchoolIdBase = 0x57800000u;

    inline uint32_t wr64DrakeSchoolIdForAddress(uint32_t segAddress) {
        if ((segAddress & Wr64DrakeSchoolAddressMask) != Wr64DrakeSchoolAddressSegment) {
            return 0;
        }

        const uint32_t offset = segAddress & 0x0000FFFFu;
        if (offset == 0) {
            return 0;
        }

        return Wr64DrakeSchoolIdBase | offset;
    }

    inline bool wr64DrakeSchoolIsOurs(uint32_t matrixId) {
        return (matrixId & 0xFFFF0000u) == Wr64DrakeSchoolIdBase;
    }

    // ------------------------------------------------------- the continuity --
    //
    // 50.0 units per frame, from the empty band between the fastest measured swim
    // (22.52) and the smallest measured relocation (82.19). Zero of 21,589 steps
    // land between those two numbers. See the header block for how the band was
    // established and why every step above it was confirmed to be a whole triple
    // moving at once.
    static constexpr float Wr64DrakeSchoolContinuityUnits = 50.0f;

    // Frames are pipelined, so "the previous frame" is a small window rather than
    // exactly one back. This is a LABEL, not a gate - the same demotion R4 made
    // for the dolphins after a return-from-absence was stamped with full
    // interpolation because its age had disqualified a 12,900-unit step.
    // Suppressing interpolation on a frame that had nothing to interpolate from
    // costs exactly nothing.
    static constexpr uint64_t Wr64DrakeSchoolContinuityFrames = 3;

    // --------------------------------------------------------------- announce --
    //
    // A validated fix is compiled in. There is no variable, not even an inverted
    // one - a fix that can be switched off is a fix nobody can rely on.
    inline bool wr64DrakeSchoolEnabled() {
        return true;
    }

    inline void wr64DrakeSchoolNote(size_t stamped, size_t skipped, size_t collided, size_t moved) {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        static bool announced = false;
        if (!announced) {
            announced = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[drakeschool] APPLYING (1 texture, id = segment-6 matrix address,"
                " continuity %.0f units)\n",
                double(Wr64DrakeSchoolContinuityUnits)); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        static bool reported = false;
        if (!reported && (stamped > 0)) {
            reported = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[drakeschool] stamped %zu transform(s) by address on first hit"
                " (%zu outside segment 6, %zu id collisions, %zu snapped)\n",
                stamped, skipped, collided, moved); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        // The running total of suppressed frames. The first-hit line will show
        // zero, because the relocations start later - and at 7.05% of transitions
        // this counter climbs steadily, which is the expected picture here rather
        // than a warning. Printed on doubling so a long race does not spam.
        static size_t lastMoved = 0;
        if (moved > 0) {
            lastMoved += moved;
            static size_t nextReport = 1;
            if (lastMoved >= nextReport) {
                nextReport = lastMoved * 2;
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                    "[drakeschool] %zu transform(s) so far kept their name and snapped:"
                    " the game handed the slot to a different fish.\n", lastMoved); }
                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            }
        }
    }
};
