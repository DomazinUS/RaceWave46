// WR64 Stunt Mode rings: identity from fixed world position.
//
// Runtime capture wr64-matrix-track-multi-20260804_210834.csv shows static rings
// whose segment-5 scratch slots change with visibility. Their spin and collection
// scale animate, so stable position identity must cover every component.
//
// IDs combine family 0x57E, a collision rank, and a sequential 16-bit hash of
// rounded x/z. Resolve same-hash rings by stable (x,z) order. The 100-unit
// continuity guard rejects cross-frame hash reassignment: captured rings do not
// translate and are at least 1,010 units apart. Keep the ID while skipping the
// discontinuous tick.
//
// The white texture is tile 1 of the same draw, not another transform. The tile-0
// claim covers it; retain its hash in diagnostics to detect alternative ordering.

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

namespace RT64 {
    // ---- The torus, tile 0. Composer capture 8, 2026-08-04.
    static constexpr uint64_t Wr64StuntRingTexture = 0xA6589CB96E2D87C9ULL; // 48 tri

    static constexpr uint32_t Wr64StuntRingIdBase = 0x57E00000u;

    // Ring texture hashes vary with course and section. A perspective torus with
    // 48 triangles and the measured combiner/otherModeH identifies these variants.
    // Do not require otherModeL: its blender/fog state varies on Sunset Bay.
    // The full captured state remains below for diagnostics. This fingerprint was
    // checked across 26,984 runtime ring rows against the other watched families.
    static constexpr uint32_t Wr64StuntRingTriangles  = 48u;
    static constexpr uint32_t Wr64StuntRingCombinerH  = 0xF0FFF83Cu;
    static constexpr uint32_t Wr64StuntRingCombinerL  = 0xFC327E2Cu;
    static constexpr uint32_t Wr64StuntRingOtherModeH = 0x00182CFFu;
    static constexpr uint32_t Wr64StuntRingOtherModeL = 0xC8112078u;

    // Measured 2026-08-05 by the R9 ring48 net, 55,122 rows: Sunset Bay
    // tints the combiner's LOW word by one byte (2C -> A8) and changes
    // NOTHING else - triangles, combiner high word, both other-mode words
    // all identical to every other course's rings. (The R9 guess that the
    // fog word otherModeL was the course-tinted one was wrong; the capture
    // shows otherModeL identical everywhere and the tint in combinerL.)
    // Kept for the record; the test below no longer reads the low word,
    // because a course-tinted word has no business in an identity test and
    // the next themed course would just hide its rings behind another byte.
    static constexpr uint32_t Wr64StuntRingCombinerLSunset = 0xFC327EA8u;

    inline bool wr64StuntRingState(uint32_t triangles, uint32_t combinerH,
        uint32_t combinerL, uint32_t otherModeH)
    {
        (void)combinerL; // course-tinted; see Wr64StuntRingCombinerLSunset
        return (triangles == Wr64StuntRingTriangles) &&
               (combinerH == Wr64StuntRingCombinerH) &&
               (otherModeH == Wr64StuntRingOtherModeH);
    }

    // Printed once, the first time a claimed ring's combiner low word is
    // NOT the base value - i.e. the moment a course-tinted variant
    // (Sunset Bay's A8, or any sibling a future course brings) is caught
    // by the widened test. Also the run script's binary gate.
    inline void wr64StuntRingTintNote() {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        static bool announced = false;
        if (announced) {
            return;
        }
        announced = true;
        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
            "[stuntring] course-tinted combiner claimed (the one-byte variant that hid Sunset Bay)\n"); }
        { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
    }

    // Diagnostic marker for position-hash collision resolution. Port Blue rings
    // (-4673,-3600) and (-4192,-4527) both hash to 0x4F22 and require distinct ranks.
    inline void wr64StuntRingRankNote() {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        static bool announced = false;
        if (announced) {
            return;
        }
        announced = true;
        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
            "[stuntring] id collision resolved by position rank (colliding rings each keep their own name)\n"); }
        { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
    }

    // Printed once, the first time a ring is claimed by its render state
    // rather than the named hash - the proof, in a log, that a hash the
    // list never met was caught anyway. Also the run script's binary gate.
    inline void wr64StuntRingFingerprintNote() {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        static bool announced = false;
        if (announced) {
            return;
        }
        announced = true;
        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
            "[stuntring] ring claimed by fingerprint (render state, not texture hash)\n"); }
        { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
    }

    static constexpr float Wr64StuntRingContinuityUnits = 100.0f;

    // Identical mixing to wr64AreaBuoyPosHash16, restated rather than shared
    // so each family's header stays self-contained the way every identity
    // header in this tree is. If one changes, the other must not care.
    inline uint32_t wr64StuntRingPosHash16(float x, float z) {
        const uint32_t xi = uint32_t(int32_t(std::lround(x)));
        const uint32_t zi = uint32_t(int32_t(std::lround(z)));
        uint32_t h = xi;
        h = (h ^ 0x9E3779B9u) * 0x85EBCA6Bu;
        h ^= zi;
        h *= 0xC2B2AE35u;
        h ^= h >> 16;
        return h & 0xFFFFu;
    }

    inline uint32_t wr64StuntRingIdFor(float x, float z) {
        return Wr64StuntRingIdBase | wr64StuntRingPosHash16(x, z);
    }

    inline bool wr64StuntRingIsOurs(uint32_t matrixId) {
        return (matrixId & 0xFFF00000u) == Wr64StuntRingIdBase;
    }

    // Default ON, like every validated correction in this tree. The variable
    // exists so the SAME BINARY can be A/B'd against the old behaviour; it is
    // not a feature switch.
    inline bool wr64StuntRingLerpEnabled() {
        static const bool enabled = [] {
            const char *value = std::getenv("WR64_STUNT_RING_LERP");
            return (value == nullptr) || (value[0] != '0');
        }();
        return enabled;
    }

    // Diagnostic marker for identity-based tile pairing. Matrix interpolation alone
    // does not cover the tile motion contributing to a ring's spin.
    inline void wr64StuntRingTileNote() {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        static bool announced = false;
        if (announced) {
            return;
        }
        announced = true;
        { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
            "[stuntring] tile pairs riding the ring identity (spin texture blends on every course)\n"); }
        { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
    }

    // Printed once, the first time a ring is actually claimed.
    inline void wr64StuntRingNote(size_t stamped, size_t collided, size_t moved) {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        static bool announced = false;
        if (!announced && (stamped > 0)) {
            announced = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[stuntring] APPLYING (1 texture, id = position hash, "
                "continuity %.0f units, every component forced)\n",
                double(Wr64StuntRingContinuityUnits)); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        static bool movedAnnounced = false;
        if (!movedAnnounced && (moved > 0)) {
            movedAnnounced = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[stuntring] %zu transform(s) kept their name and snapped: "
                "one id crossed between two positions.\n", moved); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        (void)collided;
    }
};
