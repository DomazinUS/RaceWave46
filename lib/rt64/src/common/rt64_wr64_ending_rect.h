#pragma once

#include <cstdint>
#include "rt64_wr64_hud_motion.h"

namespace RT64 {
// The native ending frame/font producers clip a strip above y=0 by advancing
// T and clamping its top. Undo that exact carrier operation before the panel
// is translated at presentation time; the GPU scissor still clips the image.
// No extra pixels are visible at native frame time, and T(y) is unchanged.
inline bool wr64EndingRestoreTop(const Wr64HudMotion &motion,
    uint32_t combinerH, uint32_t combinerL, uint32_t otherH, uint32_t otherL,
    bool regularAlignment, bool flip, int32_t ulx, int32_t &uly,
    int32_t lrx, int32_t lry, int16_t &ult, int16_t dsdx, int16_t dtdy)
{
    const uint32_t mode = motion.context >> 24;
    if (motion.kind != 3 || !motion.generation || motion.content > 8 ||
        (motion.context & 0x00ffffffu) != 0x00150107u || (mode != 102 && mode != 103) ||
        !regularAlignment || flip || uly != 0 || ulx >= lrx || lry <= 0 || (lry & 3) ||
        ult <= 0 || (ult & 31) || dtdy != 1024 || otherL != 0x00504240u) return false;

    const bool frame = combinerH == 0xff2fffffu && combinerL == 0xfc119623u;
    const bool font = combinerH == 0xfffcf279u && combinerL == 0xfcffffffu;
    const bool frameStrip = frame && otherH == 0x00002cffu && dsdx == 728;
    const bool textStrip = (frame || font) && otherH == 0x00000cffu && dsdx == 1024;
    if (!frameStrip && !textStrip) return false;

    const int32_t clippedPixels = ult / 32;
    const int32_t originalTop = -clippedPixels * 4;
    const int64_t panelOffset = int64_t(originalTop) - int64_t(motion.y) * 4;
    // A round-results panel is 32 native pixels high. Its texture carriers are
    // integral rows contained in that panel; reject unrelated or malformed UVs.
    if (clippedPixels >= 32 || lry / 4 + clippedPixels > 32 ||
        panelOffset < 0 || panelOffset >= 128 || int64_t(lry) - int64_t(motion.y) * 4 > 128) return false;
    uly = originalTop;
    ult = 0;
    return true;
}
} // namespace RT64
