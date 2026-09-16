#pragma once

#include <cstddef>
#include <cstdint>

namespace RT64 {
    // US Rev1 8006CDE8, called only by the one-player Twilight branch at
    // 80071DC8. These are translucent buoy light prisms, not opaque buoy parts.
    // Their IA16 texture alpha supplies standard source-over coverage; shade
    // supplies red/yellow RGB. See RT-TWILIGHT-BEAM-EVIDENCE-20260911.md.
    inline bool wr64RTTwilightBeamMaterial(uint32_t ccL, uint32_t ccH,
        uint32_t omL, uint32_t omH, uint32_t geometryMode,
        uint32_t triangleCount, uint32_t tileCount) {
        // OtherMode high inherits dither settings. Require the relevant native
        // one-cycle, perspective, three-point and no-TLUT texture semantics.
        constexpr uint32_t textureModeMask = 0x0038f000U;
        constexpr uint32_t textureMode = 0x00082000U;
        constexpr uint32_t geometryMask = 0x000f3205U;
        return ccL == 0xfc127e24U && ccH == 0xfffff3f9U &&
            omL == 0x005049d8U && (omH & textureModeMask) == textureMode &&
            (geometryMode & geometryMask) == 0x00002205U &&
            triangleCount == 8 && tileCount == 1;
    }

    // Indexed vertex provenance, rather than mutable texture hashes or a
    // shared combiner, separates these from unrelated translucent meshes.
    // Return 0 yellow, 1 red, -1 unrecognized. Triangle reordering and cyclic
    // rotation are harmless; duplicated, missing or reversed faces are not.
    inline int wr64RTTwilightBeamSourceFamily(const uint32_t *sources, size_t count) {
        if (sources == nullptr || count != 24) return -1;
        constexpr uint32_t bases[2] = { 0x0102bfe8U, 0x0102c838U };
        constexpr uint8_t triangles[8][3] = {
            {3,0,1}, {3,1,2}, {0,4,5}, {0,5,1},
            {7,3,2}, {7,2,6}, {4,7,6}, {4,6,5}
        };
        for (int family = 0; family < 2; ++family) {
            uint32_t seen = 0;
            bool valid = true;
            for (size_t face = 0; valid && face < 8; ++face) {
                uint32_t indices[3] = {};
                for (size_t corner = 0; corner < 3; ++corner) {
                    const uint32_t source = sources[face * 3 + corner];
                    if (source < bases[family] || source >= bases[family] + 128 ||
                        ((source - bases[family]) & 15) != 0) { valid = false; break; }
                    indices[corner] = (source - bases[family]) / 16;
                }
                if (!valid) break;
                uint32_t match = 8;
                for (uint32_t candidate = 0; candidate < 8; ++candidate) {
                    for (uint32_t rotation = 0; rotation < 3; ++rotation) {
                        if (indices[0] == triangles[candidate][rotation] &&
                            indices[1] == triangles[candidate][(rotation + 1) % 3] &&
                            indices[2] == triangles[candidate][(rotation + 2) % 3]) match = candidate;
                    }
                }
                if (match == 8 || (seen & (1U << match)) != 0) valid = false;
                else seen |= 1U << match;
            }
            if (valid && seen == 255) return family;
        }
        return -1;
    }
}
