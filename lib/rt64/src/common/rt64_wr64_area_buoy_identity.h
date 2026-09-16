// WR64 area buoys: stable identity from position and billboard layer.
//
// Runtime capture wr64-matrix-track-multi-20260804_210834.csv shows static,
// integer-coordinate buoys whose segment-5 scratch slots change with visibility.
// An address therefore identifies an emission slot rather than a physical buoy.
//
// IDs combine family 0x57D, the layer index, and a sequential 16-bit hash of
// rounded x/z. Both layers need separate IDs because they use separate transforms.
// Use a sequential mix: symmetric XOR mixes collide on mirrored course positions.
// Same-frame duplicate IDs fall back to heuristic matching; continuity guards
// cross-frame collisions without withdrawing the ID.
//
// The two captured billboard textures each use one triangle. Render state is
// shared with other object families, so the original claims use texture identity.

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

namespace RT64 {
    // ---- The two billboard layers. Composer capture 1, 2026-08-04.
    static constexpr uint64_t Wr64AreaBuoyL5 = 0xBE02175811C60321ULL; // 1 tri
    static constexpr uint64_t Wr64AreaBuoyL6 = 0x21AB19727CE2E9F6ULL; // 1 tri

    inline int wr64AreaBuoyTextureIndex(uint64_t texture) {
        if (texture == Wr64AreaBuoyL5) return 0;
        if (texture == Wr64AreaBuoyL6) return 1;
        return -1;
    }

    // Course variants rebake the two billboard textures. The 2026-08-06 runtime
    // capture identifies them by exact render state and one triangle. Course-buoy
    // far sprites share that state, so the claim site must exclude already-owned
    // transforms. Values below use callDesc word order.
    static constexpr uint32_t Wr64AreaBuoyCombinerH  = 0x11FCF279u;
    static constexpr uint32_t Wr64AreaBuoyCombinerL  = 0xFC567EACu;
    static constexpr uint32_t Wr64AreaBuoyOtherModeH = 0x0008ACFFu;
    static constexpr uint32_t Wr64AreaBuoyOtherModeL = 0x00553078u;

    inline bool wr64AreaBuoyStateClaims(uint32_t combinerH, uint32_t combinerL,
                                        uint32_t otherModeH, uint32_t otherModeL,
                                        uint32_t triangleCount) {
        return (triangleCount == 1u) &&
               (combinerH == Wr64AreaBuoyCombinerH) && (combinerL == Wr64AreaBuoyCombinerL) &&
               (otherModeH == Wr64AreaBuoyOtherModeH) && (otherModeL == Wr64AreaBuoyOtherModeL);
    }

    // Shade changes rebake textures, so texture-hash bits cannot identify the two
    // layers continuously. Rank transforms at each fixed buoy position instead.
    // Reserve indices 0/1 for enumerated textures and 2..9 for variant layer ranks.
    static constexpr int Wr64AreaBuoyVariantBase = 2;
    static constexpr int Wr64AreaBuoyVariantMaxRank = 7;

    // Forced content interpolation bypasses the engine's normal hash guard.
    // On a texture rebake, snap content to the current bake while keeping position,
    // rotation, and scale interpolation. The diagnostic marker reports this once.
    inline void wr64AreaBuoyRebakeNote() {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        static bool announced = false;
        if (!announced) {
            announced = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[areabuoy] re-bake snap (shade content switched whole; "
                "the glide is kept)\n"); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }
    }

    // Printed once, the first time a fingerprint claim actually lands.
    // The run gate greps the binary for this literal, and the RUN log
    // shows it the moment a variant course's buoys are claimed - the
    // engagement proof the buoyframe round taught us to demand.
    inline void wr64AreaBuoyVariantNote() {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        static bool announced = false;
        if (!announced) {
            announced = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[areabuoy] course variant claimed by state fingerprint "
                "(a texture the hash list never met)\n"); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }
    }

    // Clear of every id already in use: 0x57000000 articulated limbs,
    // 0x57100000 watercraft selector, 0x57200000 course map, 0x57400000
    // gantry, 0x57500000 tropical fish, 0x57524300 sky, 0x57600000 sprite
    // families, 0x57700000 dolphins, 0x57800000 lake fish, 0x57900000 +
    // 0x57A00000 whales, 0x57B00000 ducks, 0x57C00000 course buoys.
    static constexpr uint32_t Wr64AreaBuoyIdBase = 0x57D00000u;

    // 100 units. Real per-tick motion measured at exactly 0.00; the nearest
    // two DIFFERENT buoys sit 334.82 units apart. Any threshold in that band
    // separates them perfectly; 100 is the family convention (ducks, course
    // buoys) and sits a third of the way up the gap. What it catches here is
    // not slot recycling - the id survives that by construction - but a
    // 16-bit hash collision handing one id between two distant buoys across
    // consecutive frames, which then keeps its name and drops its smoothing
    // for that single tick instead of sweeping across the course.
    static constexpr float Wr64AreaBuoyContinuityUnits = 100.0f;

    // 16-bit position hash. SEQUENTIAL mixing on purpose - see the header
    // comment for the mirror-collision measurement that refused the
    // symmetric form. Verified zero collisions across all 141 measured
    // positions.
    inline uint32_t wr64AreaBuoyPosHash16(float x, float z) {
        const uint32_t xi = uint32_t(int32_t(std::lround(x)));
        const uint32_t zi = uint32_t(int32_t(std::lround(z)));
        uint32_t h = xi;
        h = (h ^ 0x9E3779B9u) * 0x85EBCA6Bu;
        h ^= zi;
        h *= 0xC2B2AE35u;
        h ^= h >> 16;
        return h & 0xFFFFu;
    }

    inline uint32_t wr64AreaBuoyIdFor(float x, float z, int textureIndex) {
        // 0/1 are the enumerated layers; 2..9 are AREABUOY-R2 fingerprint
        // variants (three hash bits). All fold into the 0x57D page.
        if ((textureIndex < 0) || (textureIndex > 9)) {
            return 0;
        }
        return Wr64AreaBuoyIdBase | (uint32_t(textureIndex) << 16)
             | wr64AreaBuoyPosHash16(x, z);
    }

    inline bool wr64AreaBuoyIsOurs(uint32_t matrixId) {
        return (matrixId & 0xFFF00000u) == Wr64AreaBuoyIdBase;
    }

    // Default ON, like every validated correction in this tree. The variable
    // exists so the SAME BINARY can be A/B'd against the old behaviour; it is
    // not a feature switch.
    inline bool wr64AreaBuoyLerpEnabled() {
        static const bool enabled = [] {
            const char *value = std::getenv("WR64_AREA_BUOY_LERP");
            return (value == nullptr) || (value[0] != '0');
        }();
        return enabled;
    }

    // Printed once, the first time a buoy is actually claimed. A silent pass
    // and a pass that never fired look identical from the couch.
    inline void wr64AreaBuoyNote(size_t stamped, size_t collided, size_t moved) {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        static bool announced = false;
        if (!announced && (stamped > 0)) {
            announced = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[areabuoy] APPLYING (2 textures, id = position hash, "
                "continuity %.0f units, every component forced)\n",
                double(Wr64AreaBuoyContinuityUnits)); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        // A moved buoy here means a hash handoff, never a slot handoff - the
        // id does not contain the slot. Say so the first time, so a snap in
        // a log is never mistaken for the fix failing.
        static bool movedAnnounced = false;
        if (!movedAnnounced && (moved > 0)) {
            movedAnnounced = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[areabuoy] %zu transform(s) kept their name and snapped: "
                "one id crossed between two positions.\n", moved); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        (void)collided;
    }
};
