#ifndef RT64_WR64_RT_NEXTMARK_H
#define RT64_WR64_RT_NEXTMARK_H

#include <array>
#include <cstdint>

namespace RT64 {

// Native DrawNextMark's floating, blinking checkpoint arrow. These are
// segmented vertex sources, not texture hashes: course lighting can rebake
// buoy textures. Painted L/R quads have their own independent identity below.
// gfx_nextmark at 0102CE78 loads these four vertices then draws one quad.
inline bool wr64RTIsNextMark(const std::array<uint32_t, 6> &sources) {
    uint32_t all = 0;
    for (uint32_t triangle = 0; triangle < 2; ++triangle) {
        uint32_t mask = 0;
        for (uint32_t corner = 0; corner < 3; ++corner) {
            const uint32_t source = sources[triangle * 3 + corner];
            if (source < 0x0102CE38u || source > 0x0102CE68u ||
                ((source - 0x0102CE38u) & 15u)) return false;
            const uint32_t bit = 1u << ((source - 0x0102CE38u) >> 4);
            if (mask & bit) return false;
            mask |= bit;
        }
        all |= mask;
    }
    return all == 15u;
}

// The authored L/R lettering is a separate cutout quad from each buoy's
// five-vertex solid body. Excluding this identity affects shadows only; callers
// retain both body and lettering in the reflection scene. Matrix slots and
// texture colors cannot identify it reliably across animated course lighting.
inline bool wr64RTIsBuoyLetter(const std::array<uint32_t, 6> &sources) {
    const uint32_t base = (sources[0] >= 0x01029C98u && sources[0] <= 0x01029CC8u)
        ? 0x01029C98u : 0x0102AE48u;
    uint32_t all = 0;
    for (uint32_t triangle = 0; triangle < 2; ++triangle) {
        uint32_t mask = 0;
        for (uint32_t corner = 0; corner < 3; ++corner) {
            const uint32_t source = sources[triangle * 3 + corner];
            if (source < base || source > base + 48u || ((source - base) & 15u)) return false;
            const uint32_t bit = 1u << ((source - base) >> 4);
            if (mask & bit) return false;
            mask |= bit;
        }
        all |= mask;
    }
    return all == 15u;
}

} // namespace RT64

#endif
