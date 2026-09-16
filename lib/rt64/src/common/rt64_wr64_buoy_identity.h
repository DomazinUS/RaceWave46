// WR64 course-buoy identity and interpolation.
//
// Course buoys retain segment-5 matrix addresses across frames, while their visible
// animation also changes mesh vertices. Force the complete interpolation group:
// stable ID, linear ordering, decompose=false, and interpolated components.
// Changing only vertexInterpolation does not establish stable matching.
//
// Claim the eight known texture hashes. Buoy render state is shared with ducks and
// seagulls, and the buoy parts use different triangle counts; neither field alone
// identifies the complete object. Include the texture in the address-based ID
// because separate buoy parts can share a matrix address.
//
// Texture identification comes from WR64 Composer captures 3/frame 3143 and
// 5/frame 6122, cross-checked against the 2026-07-16 texture dump. The four
// L18/L19 hashes occupy consecutive addresses 0x00252B38, 0x00253338, 0x00253CE8,
// and 0x002544E8.

#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>

namespace RT64 {
    // ---- Yellow, the left-hand marker. Composer capture 3 / frame 3143.
    static constexpr uint64_t Wr64BuoyYellowL9  = 0xF12E5A7C9716DF55ULL; // 1 tri
    static constexpr uint64_t Wr64BuoyYellowL10 = 0xAC0C00790089DEB0ULL; // 1 tri
    static constexpr uint64_t Wr64BuoyYellowL18 = 0x1C107ECADB0C3559ULL; // 4 tri
    static constexpr uint64_t Wr64BuoyYellowL19 = 0xE5B734C89178B3F0ULL; // 2 tri

    // ---- Red, the right-hand marker. Composer capture 5 / frame 6122.
    static constexpr uint64_t Wr64BuoyRedL7     = 0xC093005232F26F52ULL; // 1 tri
    static constexpr uint64_t Wr64BuoyRedL8     = 0x6E4F42D43CE128EFULL; // 1 tri
    static constexpr uint64_t Wr64BuoyRedL18    = 0xDD932255D7967796ULL; // 4 tri
    static constexpr uint64_t Wr64BuoyRedL19    = 0x6CC118A4C1533415ULL; // 2 tri

    inline bool wr64BuoyClaims(uint64_t texture) {
        switch (texture) {
        case Wr64BuoyYellowL9:
        case Wr64BuoyYellowL10:
        case Wr64BuoyYellowL18:
        case Wr64BuoyYellowL19:
        case Wr64BuoyRedL7:
        case Wr64BuoyRedL8:
        case Wr64BuoyRedL18:
        case Wr64BuoyRedL19:
            return true;
        default:
            return false;
        }
    }

    // Use the complete explicit-identity interpolation recipe, including ordering
    // and all components. Family base 0x57C00000 does not overlap the other object
    // families; enabling vertex interpolation alone does not stabilize matching.
    static constexpr uint32_t Wr64BuoyIdBase = 0x57C00000u;

    // SEGMENT 05, unlike the ducks and whales. Measured 2026-08-03: every buoy
    // transform sits at 0x050096xx (the L9/L10 parts) or 0x05009Cxx (L18/L19),
    // and the slot is stable per buoy - 0 to 4 address changes over hundreds of
    // frames. Segment 05 is the pool that got texture C7E16FE8A5BC21ED refused,
    // so it is NOT trusted blindly: the continuity guard below is what makes it
    // safe, because the same slot was measured serving four different buoys over
    // one session.
    static constexpr uint32_t Wr64BuoyAddressMask    = 0xFF000000u;
    static constexpr uint32_t Wr64BuoyAddressSegment = 0x05000000u;

    // 100 units. A buoy is ANCHORED - x and z byte-identical across thousands of
    // frames - and its largest measured real step is 18.25 units in one tick.
    // Two different buoys are over 1,000 units apart. So the band between "the
    // biggest real move" and "this slot now holds a different buoy" is enormous
    // and 100 sits well inside it. Same value as the ducks, arrived at from this
    // object's own measurements rather than copied on faith.
    static constexpr float Wr64BuoyContinuityUnits = 100.0f;

    // Two buoy parts can share a matrix address while using different textures.
    // Include texture index in the ID, and reject only duplicate address/texture
    // pairs. This distinguishes real split-screen duplicates from the billboard
    // layers of one buoy. Layout: family 0x57C in bits 20-31, texture index 0-7 in
    // bits 16-18, and matrix-slot offset in bits 0-15.
    inline int wr64BuoyTextureIndex(uint64_t texture) {
        switch (texture) {
        case Wr64BuoyYellowL9:  return 0;
        case Wr64BuoyYellowL10: return 1;
        case Wr64BuoyYellowL18: return 2;
        case Wr64BuoyYellowL19: return 3;
        case Wr64BuoyRedL7:     return 4;
        case Wr64BuoyRedL8:     return 5;
        case Wr64BuoyRedL18:    return 6;
        case Wr64BuoyRedL19:    return 7;
        default:                return -1;
        }
    }

    inline uint32_t wr64BuoyIdFor(uint32_t segAddress, int textureIndex) {
        if ((segAddress & Wr64BuoyAddressMask) != Wr64BuoyAddressSegment) {
            return 0;
        }

        if ((textureIndex < 0) || (textureIndex > 7)) {
            return 0;
        }

        const uint32_t offset = segAddress & 0x0000FFFFu;
        if (offset == 0) {
            return 0;
        }

        return Wr64BuoyIdBase | (uint32_t(textureIndex) << 16) | offset;
    }

    // Twelve bits, not sixteen: the texture index lives at 16-18 now, so a
    // 0xFFFF0000 mask would report every buoy but texture 0 as not ours.
    inline bool wr64BuoyIsOurs(uint32_t matrixId) {
        return (matrixId & 0xFFF00000u) == Wr64BuoyIdBase;
    }

    // Default ON, like every other validated correction in this tree. The
    // variable exists so the SAME BINARY can be A/B'd against the old behaviour;
    // it is not a feature switch.
    inline bool wr64BuoyVertexLerpEnabled() {
        static const bool enabled = [] {
            const char *value = std::getenv("WR64_BUOY_VERTEX_LERP");
            return (value == nullptr) || (value[0] != '0');
        }();
        return enabled;
    }

    // Printed once, the first time a buoy is actually claimed. A silent pass and
    // a pass that never fired look identical from the couch, and a play session
    // spent on the wrong binary is how this project has lost days before.
    inline void wr64BuoyNote(size_t stamped, size_t skipped, size_t collided, size_t moved) {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        static bool announced = false;
        if (!announced && (stamped > 0)) {
            announced = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[buoy] APPLYING (8 textures, id = segment-5 matrix address, "
                "continuity %.0f units, every component forced)\n",
                double(Wr64BuoyContinuityUnits)); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        // The slot really is recycled between buoys - measured, one address
        // serving four different buoys in a session. Say so out loud the first
        // time it happens, so a snap is never mistaken for the fix failing.
        static bool movedAnnounced = false;
        if (!movedAnnounced && (moved > 0)) {
            movedAnnounced = true;
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout,
                "[buoy] %zu transform(s) kept their name and snapped: the slot was "
                "re-used by a different buoy.\n", moved); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
        }

        (void)skipped;
        (void)collided;
    }
};
