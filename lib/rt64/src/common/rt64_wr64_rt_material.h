#pragma once

#include <cstdint>

namespace RT64 {
    enum class Wr64RTMaterial : uint32_t {
        Rejected = 0,
        Opaque = 1,
        Cutout = 2
    };

    // Native OtherMode.L determines material coverage, independently of scene,
    // water, viewport, and semantic shadow-caster eligibility. Texture-edge
    // surfaces write depth but use texture alpha as coverage; their transparent
    // texels must be tested during ray traversal rather than treated as solid.
    constexpr Wr64RTMaterial wr64RTClassifyMaterial(uint32_t otherModeL) {
        constexpr uint32_t DepthWrite = 0x20;
        constexpr uint32_t DepthModeMask = 0xC00;
        constexpr uint32_t TranslucentDepthMode = 0x800;
        constexpr uint32_t CoverageTimesAlpha = 0x1000;
        const uint32_t alphaCompare = otherModeL & 3;
        if (!(otherModeL & DepthWrite) ||
            (otherModeL & DepthModeMask) == TranslucentDepthMode || alphaCompare >= 2) {
            return Wr64RTMaterial::Rejected;
        }
        return (otherModeL & CoverageTimesAlpha) || alphaCompare == 1
            ? Wr64RTMaterial::Cutout : Wr64RTMaterial::Opaque;
    }
}
