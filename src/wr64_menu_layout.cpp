#include "wr64_menu_layout.h"
#include "recomp.h"
#include "../lib/rt64/src/common/rt64_wr64_ultrawide.h"
#include <algorithm>
#include <cmath>
#include <cassert>

namespace {
uint32_t pair(int32_t high, int32_t low) {
    return (uint32_t(uint16_t(high)) << 16) | uint16_t(low);
}
void put(uint8_t* rdram, uint32_t address, uint32_t value) {
    MEM_W(0, S32(address)) = value;
}
uint32_t get(uint8_t* rdram, uint32_t address) {
    return MEM_W(0, S32(address));
}
}

extern "C" int32_t wr64_menu_half_extension() {
    return int32_t(std::ceil(std::max(0.0f,
        (RT64::wr64UltrawideLogicalWidth() - RT64::Wr64BaselineWidth) * 0.5f)));
}

extern "C" uint32_t wr64_menu_enable(uint8_t* rdram, uint32_t cursor) {
    // Standard F3DEX RT64 enable hook. The original cartridge command stream
    // is retained at the native aspect; extended packets are used only when
    // signed coordinates are required by the extra centered menu area.
    put(rdram, cursor, 0x00525464);
    put(rdram, cursor + 4, 0x10000064);
    return cursor + 8;
}

extern "C" void wr64_menu_promote_waku_rect(uint8_t* rdram, uint32_t cursor,
    int32_t x, int32_t width)
{
    // gDPLoadTextureBlock's existing load-sync slot is a no-op in RT64
    // (GBI_RDP::loadSync). Reuse it for extension enablement so a glyph or
    // frame strip adds no command bytes to the game's fixed display-list
    // buffers. Both native producers use this exact seven-command load.
    assert(get(rdram, cursor - 40) == 0xE6000000);
    wr64_menu_enable(rdram, cursor - 40);
    // Native ScisTextureRectangle has already clipped negative X and advanced
    // S. Recover the authored extent and S=0, leaving Y/T and the per-strip
    // dsdx/dtdy untouched. The extended packet has the same three-command size.
    const uint32_t nativeLR = get(rdram, cursor);
    const uint32_t nativeUL = get(rdram, cursor + 4);
    const uint32_t nativeST = get(rdram, cursor + 12);
    const uint32_t nativeStep = get(rdram, cursor + 20);
    put(rdram, cursor, 0x64000002);
    put(rdram, cursor + 4, 0x04004000); // both origins G_EX_ORIGIN_NONE, tile0
    put(rdram, cursor + 8, pair(x * 4, nativeUL & 0xFFF));
    put(rdram, cursor + 12, pair((x + width) * 4, nativeLR & 0xFFF));
    put(rdram, cursor + 16, nativeST & 0xFFFF); // restore unclipped horizontal UV
    put(rdram, cursor + 20, nativeStep);
}

extern "C" uint32_t wr64_menu_fill_rect(uint8_t* rdram, uint32_t cursor,
    int32_t left, int32_t top, int32_t right, int32_t bottom, int32_t half)
{
    if (left >= 424 + half || right < -half || top >= 240 || bottom < 0 ||
        right < left || bottom < top) return cursor;
    cursor = wr64_menu_enable(rdram, cursor);
    put(rdram, cursor, 0x64000003);
    put(rdram, cursor + 4, 0x00800800); // both origins G_EX_ORIGIN_NONE
    put(rdram, cursor + 8, pair(left * 4, std::max(top, 0) * 4));
    put(rdram, cursor + 12, pair((right + 1) * 4, (std::min(bottom, 239) + 1) * 4));
    return cursor + 16;
}


extern "C" int32_t wr64_title_menu_origin(uint8_t* rdram, uint32_t table, int32_t original) {
    // The widescreen IPS moves the first five title tables from X=98 to 150,
    // but omits table 5, unlocked after completing Expert (four difficulties,
    // including Reverse). Its frame already uses X=142. Correct only the local
    // label origin; ROM data, unlock flags, selection and other overlays stay native.
    constexpr uint32_t reverseTable = 0x802C6E80;
    if (!rdram || table != reverseTable || original != 98 ||
        get(rdram, 0x800DAB24) != 3 || get(rdram, 0x802C6EE0) != 5) return original;
    constexpr uint32_t expected[]{0x802C6DA8, 4, 4, 98, 78, 0};
    for (uint32_t i = 0; i < 6; ++i) {
        if (get(rdram, table + i * 4) != expected[i]) return original;
    }
    return 150;
}


extern "C" int32_t wr64_ending_panel_retire(uint8_t* rdram, uint32_t row, int32_t original) {
    // Native TourEnd retires scrolling rows at Y < -12 although their green
    // frame is 32 pixels tall. Keep the row alive until its whole frame leaves
    // the screen; the existing producers/scissor handle each clipped strip.
    // The total-ranking panel (content 10) has its own stop/fade state machine.
    constexpr uint32_t firstRow = 0x802C6E80;
    if (!rdram || row < firstRow || row >= firstRow + 10 * 16 ||
        (row - firstRow) % 16 != 0) return original;
    const auto mode = get(rdram, 0x800DAB24);
    if ((mode != 102 && mode != 103) || get(rdram, 0x801CE638) != 21 ||
        get(rdram, 0x800D8170) != 7 || get(rdram, 0x800DAB28) != 1 ||
        get(rdram, row) != 1 || get(rdram, row + 4) > 8) return original;
    return int32_t(get(rdram, row + 12)) < -32;
}
