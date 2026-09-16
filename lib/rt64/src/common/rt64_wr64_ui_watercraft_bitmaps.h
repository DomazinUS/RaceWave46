#pragma once

#include <array>
#include <cstdint>

namespace RT64 {
    struct Wr64UiWatercraftBitmap {
        uint64_t tmemHash;
        uint32_t width, height;
        const char *name;
    };

    // Native USA Watercraft Select UI identities, not replacement art.
    // All 17 entries were decoded from the existing 20260716-024237 TMEM dump
    // and joined by full hash to watercraft-21-census.csv: Rectangle projection,
    // two triangles, one tile, exact dimensions below. The independent fixture
    // tests/ui_filter/captured_watercraft_labels.h records the original Composer
    // draw modes and source line numbers. No preview/world textures are included.
    // Button icons are part of the complete A ENTER and B GO BACK bitmaps.
    // The last entry combines the 1P label and its selection rectangle.
    inline constexpr std::array<Wr64UiWatercraftBitmap, 17> Wr64UiWatercraftBitmaps = {{
        {0xC8E8F946EDBBEF0AULL, 128,  8, "WATERCRAFT SETTINGS"},
        {0x7EB83A89F696D6B0ULL,  48,  8, "NORMAL"},
        {0xF23E99DC669AB797ULL,  48,  8, "CUSTOM"},
        {0x1378F55FBE6F4D54ULL,  48, 10, "A ENTER"},
        {0xF3D20A634FAEEBBDULL,  64, 10, "B GO BACK"},
        {0xF7C7C306A552D4F4ULL,  64, 10, "HANDLING"},
        {0x23B35B0E34FFA7A7ULL,  32,  8, "LIGHT"},
        {0x8E696842C1BF0D3BULL,  40,  8, "HEAVY"},
        {0xA832E8EE225368EEULL,  48, 10, "ENGINE"},
        {0x903B91F90A97133CULL,  32,  8, "DASH"},
        {0x5DB402956F1CF38AULL,  48,  8, "TOP END"},
        {0xBE582F5F12A57B8DULL,  32, 10, "GRIP"},
        {0x9612D6978EF7D8B5ULL,  40,  8, "LOOSE"},
        {0xE77982B4A5E10E34ULL,  32,  8, "TIGHT"},
        {0xE1CB0DCFAA8FF1AAULL, 121,  8, "setting gauge track"},
        {0x0120D61382B0E913ULL,   9,  6, "setting gauge marker"},
        {0xEF056E615EDB1CEDULL,  64, 36, "1P label and selection border"}
    }};
}
