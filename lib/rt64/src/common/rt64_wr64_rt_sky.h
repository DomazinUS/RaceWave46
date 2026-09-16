#pragma once

#include <cstdint>

namespace RT64 {
    // Same proven six-triangle family as wr64SkyBracketIsExactSkyCall.
    // P2 changes only RGB dithering (00882C3F -> 00882CFF); that state does
    // not change the texture environment. Keep every other material bit exact.
    // Keep this small predicate independent of the interpolation diagnostics.
    inline constexpr bool wr64RTSkySignature(uint32_t triangles, uint32_t ccL,
        uint32_t ccH, uint32_t omL, uint32_t omH) {
        return triangles == 6 && ccL == 0xFC11C223U && ccH == 0xFF87FFFFU &&
            omL == 0x00504240U && (omH & ~0xC0U) == 0x00882C3FU;
    }

    inline constexpr bool wr64RTBackdropSignature(uint32_t triangles, uint32_t ccL,
        uint32_t ccH, uint32_t omL, uint32_t omH) {
        const uint32_t materialH = omH & ~0xC0U;
        return triangles == 6 && omL == 0x0F0A4000U &&
            ((ccL == 0xFC22FFFFU && ccH == 0x1FFCFA38U && materialH == 0x00982C3FU) ||
             (ccL == 0xFCFFFFFFU && ccH == 0xFFFCF279U && materialH == 0x00882C3FU));
    }

    // DL 010103B8 uses exactly these seven native backdrop vertices. The
    // earlier lower-plane fan at 06000000 shares the one-cycle material and
    // full viewport, so material identity alone must not enter ambiguity
    // accounting. Accept repeated indexed references, but require every vertex
    // from one complete producer block.
    inline bool wr64RTBackdropSourceFamily(const uint32_t *addresses, uint32_t count) {
        if (addresses == nullptr || count != 18) return false;
        uint32_t sourceBase = 0, sourceMask = 0;
        for (uint32_t i = 0; i < count; ++i) {
            const uint32_t source = addresses[i];
            const uint32_t base = source >= 0x060000E0 && source <= 0x06000140
                ? 0x060000E0 : source >= 0x06000150 && source <= 0x060001B0
                ? 0x06000150 : 0;
            if (base == 0 || (source - base) % 16 != 0 || (sourceBase && sourceBase != base))
                return false;
            sourceBase = base;
            sourceMask |= 1u << ((source - base) / 16);
        }
        return sourceMask == 0x7F;
    }

    // Native rectangles use quarter pixels. Allow the same two-pixel
    // inclusive-edge discrepancy already repaired by the presentation path.
    // An inset with the sky material must never become the environment map.
    inline constexpr bool wr64RTSkyFullCoverage(int32_t left, int32_t top,
        int32_t right, int32_t bottom, int32_t frameLeft, int32_t frameTop,
        int32_t frameRight, int32_t frameBottom) {
        constexpr int64_t Tolerance = 8;
        return right > left && bottom > top && frameRight > frameLeft &&
            frameBottom > frameTop && int64_t(left) <= int64_t(frameLeft) + Tolerance &&
            int64_t(top) <= int64_t(frameTop) + Tolerance &&
            int64_t(right) >= int64_t(frameRight) - Tolerance &&
            int64_t(bottom) >= int64_t(frameBottom) - Tolerance;
    }
}
