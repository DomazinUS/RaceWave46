// WR64 tropical fish: stable identities from texture, group, and ordinal.
//
// Runtime measurements identify two nine-fish blocks in canonical texture order:
// clownfish, butterflyfish, blue tang, three of each. The transform block's base
// index changes, so it is not a stable ID.
//
// Start a new group when canonical texture rank decreases. This preserves identity
// when a triple is culled; a plain per-texture ordinal would assign the second
// group the first group's IDs. The rule matched all 43,599 captured fish draws,
// including partial schools. Keep continuity guards to reject reused IDs rather
// than increasing motion tolerances to accept false pairings.

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <cstddef>
#include <cstdint>
#include <cstdio>

namespace RT64 {
    // ---------------------------------------------------------------- assets --
    //
    // Canonical slot order IS the emission order within a block. The group rule
    // below depends on it: rank must ascend within a block and can only fall at a
    // block boundary. Do not reorder these to taste.
    static constexpr uint64_t Wr64FishClownfish     = 0x4C91465E6EF00146ULL;   // 64x32, slot 0
    static constexpr uint64_t Wr64FishButterflyfish = 0x79BB32DB0213A7C9ULL;   // 32x32, slot 1
    static constexpr uint64_t Wr64FishBlueTang      = 0x6333853F362F64B5ULL;   // 64x32, slot 2

    static constexpr uint32_t Wr64FishSlotCount = 3;

    // Every school draw carries this state. Measured identical across all 43,599
    // draws in the session. It is what stops the claim from catching some other
    // 64x32 sprite that happens to hash the same in a future course.
    static constexpr uint32_t Wr64FishCombinerH  = 0xFFFFF238u;
    static constexpr uint32_t Wr64FishCombinerL  = 0xFC127FFFu;
    static constexpr uint32_t Wr64FishOtherModeH = 0x00182CFFu;
    static constexpr uint32_t Wr64FishOtherModeL = 0xC8113078u;
    static constexpr uint32_t Wr64FishTriangles  = 2u;

    // Returns the canonical slot, or -1 for anything that is not a school fish.
    inline int32_t wr64FishSchoolSlot(uint64_t tmemHash) {
        switch (tmemHash) {
        case Wr64FishClownfish:     return 0;
        case Wr64FishButterflyfish: return 1;
        case Wr64FishBlueTang:      return 2;
        default:                    return -1;
        }
    }

    inline bool wr64FishSchoolClaims(uint64_t tmemHash, uint32_t triangleCount,
        uint32_t combinerH, uint32_t combinerL, uint32_t otherModeH, uint32_t otherModeL)
    {
        if (triangleCount != Wr64FishTriangles) {
            return false;
        }

        if ((combinerH != Wr64FishCombinerH) || (combinerL != Wr64FishCombinerL) ||
            (otherModeH != Wr64FishOtherModeH) || (otherModeL != Wr64FishOtherModeL))
        {
            return false;
        }

        return wr64FishSchoolSlot(tmemHash) >= 0;
    }

    // ------------------------------------------------------------------- ids --
    //
    // Base 0x57500000 is clear of every id already in use: 0x57000000 articulated
    // limbs, 0x57100000 watercraft selector, 0x57200000 course map, 0x57400000
    // gantry (which reserves 256), 0x57524300 sky.
    //
    // Layout: Base + slot*24 + group*3 + ordinal.
    //
    //   slot 0 clownfish       0x57500000 .. 0x57500017
    //   slot 1 butterflyfish   0x57500018 .. 0x5750002F
    //   slot 2 blue tang       0x57500030 .. 0x57500047
    //
    // Sunny Beach uses two groups of the eight reserved. The headroom is there so
    // a course with a larger school gets distinct ids instead of colliding with
    // another fish's - a wrong pairing is worse than no pairing, which is the
    // lesson the gantry's first attempt paid for.
    static constexpr uint32_t Wr64FishSchoolBase      = 0x57500000u;
    static constexpr uint32_t Wr64FishSchoolMaxGroups = 8u;
    static constexpr uint32_t Wr64FishSchoolPerGroup  = 3u;
    static constexpr uint32_t Wr64FishSchoolPerSlot   = Wr64FishSchoolMaxGroups * Wr64FishSchoolPerGroup;
    static constexpr uint32_t Wr64FishSchoolIdCount   = Wr64FishSlotCount * Wr64FishSchoolPerSlot;

    // Returns 0 when the school is bigger than the reserved space. The caller must
    // leave those transforms at G_EX_ID_AUTO rather than wrap them onto an id that
    // belongs to a different fish.
    inline uint32_t wr64FishSchoolId(int32_t slot, uint32_t group, uint32_t ordinal) {
        if ((slot < 0) || (uint32_t(slot) >= Wr64FishSlotCount)) {
            return 0;
        }

        if ((group >= Wr64FishSchoolMaxGroups) || (ordinal >= Wr64FishSchoolPerGroup)) {
            return 0;
        }

        return Wr64FishSchoolBase + (uint32_t(slot) * Wr64FishSchoolPerSlot) +
               (group * Wr64FishSchoolPerGroup) + ordinal;
    }

    inline bool wr64FishSchoolIsOurs(uint32_t matrixId) {
        return (matrixId >= Wr64FishSchoolBase) &&
               (matrixId < (Wr64FishSchoolBase + Wr64FishSchoolIdCount));
    }

    // The 75-unit continuity limit separates normal swimming from slot reassignment.
    // The Dolphin Park capture has a 24.2-unit p95 and reassignment steps starting
    // at 150 units, with few steps between them. Keep the ID on a discontinuity and
    // snap placement for one tick; vertex/tile animation remains continuous.
    // Unlike Dolphin Park, the captured Sunny Beach school retained its member mapping.
    static constexpr float Wr64FishContinuityUnits = 75.0f;

    // --------------------------------------------------------------- announce --
    //
    // ALWAYS ON. Mirrors [gantryidentity], which is the same shape of fix and was
    // validated by eye on 2026-07-30.
    inline bool wr64FishSchoolEnabled() {
        static const bool announced = [] {
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[fishschool] APPLYING\n"); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            return true;
        }();
        (void)announced;
        return true;
    }

    // One line the first time the pass stamps anything, so a run where the pass
    // never fired is distinguishable from a run where it fired and changed
    // nothing. The gantry needed exactly this to catch a dead stamp.
    inline void wr64FishSchoolNote(size_t stamped, size_t groups, size_t skipped, size_t snapped) {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        if (stamped == 0) {
            return;
        }

        static bool announced = false;
        if (!announced) {
            announced = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[fishschool] stamped %zu fish in %zu group(s) on first hit\n",
                stamped, groups); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        // The slot really is reassigned between fish - measured ~once per tick
        // in Dolphin Park. Say so out loud the first time, so a pop is never
        // mistaken for the fix failing.
        static bool snapAnnounced = false;
        if ((snapped > 0) && !snapAnnounced) {
            snapAnnounced = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[fishschool] %zu fish kept their name and snapped: the slot was "
                "reassigned to a different fish.\n", snapped); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        // Overflow is silent otherwise, and silence would read as "the school is
        // small here" rather than "ids ran out".
        static bool overflowed = false;
        if ((skipped > 0) && !overflowed) {
            overflowed = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[fishschool] %zu fish beyond the reserved id space left unnamed\n",
                skipped); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }
    }
};
