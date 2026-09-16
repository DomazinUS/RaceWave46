#pragma once

#include "rt64_wr64_hud_anchor.h"
#include "rt64_wr64_ui_watercraft_bitmaps.h"
#include "rt64_wr64_ui_course_bitmaps.h"
#include <array>
#include <cstdint>

namespace RT64 {
    // Pure draw metadata, evaluated before shader selection. The texture is
    // identified independently for each draw, so 3D uses never inherit UI state.
    struct Wr64UiFilterDraw {
        int32_t projectionType = 0;
        uint64_t tmemHash = 0;
        uint32_t sampleWidth = 0, sampleHeight = 0;
        uint32_t triangles = 0, tiles = 0;
        uint8_t textureOn = 0;
        uint32_t combinerH = 0, combinerL = 0;
        uint32_t otherModeH = 0, otherModeL = 0;
        bool rawTMEM = false, tileCopyUsed = false;
    };

    // Full IA8 atlases matched byte-for-byte to the local USA Rev1 ROM. These
    // are RT64 TMEM fingerprints, not embedded font images. Include every
    // character rather than only characters encountered in a captured name.
    // Main: 0x129D48, 40 * 24 * 20 bytes.
    inline constexpr std::array<uint64_t, 40> Wr64UiMainFont = {
        0xF2F0A7BF9423E51EULL, 0x43B91B2FE4069F1AULL, 0x4521AB8BA061DA9DULL, 0xACC54F14220F157DULL,
        0xEEE66B1B35327C68ULL, 0x515F7DDA13AAF564ULL, 0xE4F8F4AA967BF979ULL, 0xC9BC7353A46283F9ULL,
        0x3CD58D557F6C1395ULL, 0x09764FA85588ABF2ULL, 0xE144EAB13F0D8ECBULL, 0x00F9F8A548769C47ULL,
        0x7FFBDEFC768C0945ULL, 0x40E8D33ED64B50B9ULL, 0x7BFB4EE37D30CA90ULL, 0x97F8537131F80BA4ULL,
        0xB5645A3BA79BC51FULL, 0x334E1C564AB3273AULL, 0xAA5E78F967AFBF94ULL, 0xCFF9502681043B78ULL,
        0xBCF9A10CA1570C59ULL, 0xDDBA0BCA1724D0E9ULL, 0xEB0F2FE3B3FAD03DULL, 0x37503618BD0373FAULL,
        0x43AF26761526A6BEULL, 0xA5ACD8F3125F2FF1ULL, 0x514C423BF587913CULL, 0x55987E4973C5EBD8ULL,
        0x658B596B8BCB8BC3ULL, 0x523E540000A916DBULL, 0x6CC2F36A0C035DA1ULL, 0xA427FA0F87B03FFBULL,
        0xF7CD5E43B9029A9FULL, 0xBB22909B998C752EULL, 0x791DA0E63E35EEBAULL, 0x073A8138C786B0AAULL,
        0xEA1F085D136847EAULL, 0x292259D0E9A755F9ULL, 0x617AEBEA91A879D8ULL, 0x6F165802E1916DE2ULL
    };

    // Small: 0x12E850, 42 * 8 * 8 bytes.
    inline constexpr std::array<uint64_t, 42> Wr64UiSmallFont = {
        0x77B01E979F3C0E90ULL, 0xC0B186E2CDE94E9FULL, 0xF4CD20A451616F89ULL, 0x92CFC51E53A42BD0ULL,
        0x49F6BAC053989176ULL, 0xDA68D96117AD4DCBULL, 0xEACE9962D70DF0A6ULL, 0x5427F54EB02D6527ULL,
        0x74FDE67D44E655AEULL, 0xCF35CC56FC0D7922ULL, 0x6D3CEFFBA94FB06EULL, 0x54452B5166A2D0EAULL,
        0x3EAA303BCDEA6DEEULL, 0x7746C59A8182AB1EULL, 0x5ECCD002D46DCB73ULL, 0x8A74331E33DC3C93ULL,
        0x9E59C72AC484F7CFULL, 0x701F8C2A3691D482ULL, 0x2189F67DD2713D25ULL, 0x6283664A0BDABDDEULL,
        0xD1F2C076047815DCULL, 0xD0FFC08F6D95C915ULL, 0xD0AC1B6FD270556AULL, 0xAEC8CABF5C1FB579ULL,
        0x14D99376867B2972ULL, 0x105D10B04E83A71DULL, 0x3921C0186DDF5EB3ULL, 0xBC7BA76A4C0B78F1ULL,
        0x8E1480FBA8A046A4ULL, 0x2D2A75FD4946F4E6ULL, 0xF2568C21C117F596ULL, 0x18C89B0C1A51A1DBULL,
        0x38A04CD61A347BA1ULL, 0xCA67E5049459E390ULL, 0x0176B2B2E1DD8832ULL, 0xA6D839A4F5992DB0ULL,
        0xB80EA2D4DC740C0CULL, 0xAA0A8088722E220DULL, 0x6859CD2305CDD9A5ULL, 0xA921138DC10CF498ULL,
        0x6D5A916B8CBD0D92ULL, 0x612DB9A128434A92ULL
    };

    // Select: 0x12F2D8, 46 * 16 * 12 bytes; shared by names and finish times.
    inline constexpr std::array<uint64_t, 46> Wr64UiSelectFont = {
        0xA96DAD369EB6FD77ULL, 0x5009956E5CCCD2A2ULL, 0x0FB5914E291DA6BAULL, 0x83428B1A568E7E20ULL,
        0xCF3E0D0EE9A5E075ULL, 0x38F5ACF02E429685ULL, 0xD16BD5B189CE2C46ULL, 0xF16E8C92416D055EULL,
        0xA25ACE7103977303ULL, 0x40CB4DD05C577014ULL, 0xD89C8003588C1353ULL, 0xA11154B56B12788EULL,
        0x8644CBBBFEE5D8BEULL, 0xC93640AF3CC06BFBULL, 0x9BCA697805FF2AE0ULL, 0x6139001CFBCDB40AULL,
        0xB3713986F6382C82ULL, 0x7382FEE0855BA029ULL, 0x363B66F96397B2D1ULL, 0xAE26CCADAEC323AAULL,
        0x44222DE654BAABFEULL, 0xC2E2715189DCFC82ULL, 0x8AEAA516A2C219C8ULL, 0x388EEAC306FBE316ULL,
        0xA8519E27F7CCC2E6ULL, 0xCCAE88406C14AF29ULL, 0xAE9B783B5D2DE585ULL, 0x727EA28773CEBBE4ULL,
        0x46AF1CCB190F15B5ULL, 0xDBE00DFB66D36C9BULL, 0xDEC743EBC49D56E8ULL, 0xB504FA612DE2884DULL,
        0x79CD2602917BCB1FULL, 0x2A02D4A5D8917873ULL, 0x612FF7950077AF05ULL, 0x2894D2AE3DCCD2B1ULL,
        0xA3F86F4CB3E28FF0ULL, 0xF0CBDEEB5EBD7CE6ULL, 0x3F130B49C2F3D9FEULL, 0x0E0AF566A2092DFBULL,
        0xB233A47A2ED609C8ULL, 0x2247C5D799140A3BULL, 0x88BBBEC3DB3C09A3ULL, 0x7902CE984DDE8E36ULL,
        0x1E22587E59E2CD5FULL, 0x84BB953665614FACULL
    };

    struct Wr64UiMainMenuBitmap {
        uint64_t tmemHash;
        uint32_t width, height;
        uint8_t combinerMask; // bit 0: ordinary label; bit 1: highlighted label
    };
    // Native USA whole-word IA8 bitmaps, independently recorded in the Main
    // Menu capture. Identity is available to diagnostics; eligibility still
    // requires the exact draw metadata checked below.
    inline constexpr std::array<Wr64UiMainMenuBitmap, 7> Wr64UiMainMenuBitmaps = {{
        {0x6EADDE9CB22F2DB8ULL,  96, 10, 3}, // CHAMPIONSHIP
        {0xBD23E01E9D3FBF31ULL,  80, 10, 3}, // TIME TRIALS
        {0x884632A34B93431EULL,  80, 10, 3}, // STUNT MODE
        {0x3DF731B17B60172EULL,  40, 10, 3}, // 2P VS.
        {0x2E2C2E2F45953104ULL,  56, 10, 3}, // OPTIONS
        {0x04D4302136DC2922ULL, 136, 12, 2}, // Press START to begin.
        {0x7AD6F20FB8A54652ULL, 128, 12, 1}  // copyright
    }};

    template <size_t N>
    inline bool wr64UiFontContains(const std::array<uint64_t, N> &font, uint64_t hash) {
        for (uint64_t candidate : font) if (candidate == hash) return true;
        return false;
    }

    template <typename Bitmap, size_t N>
    inline bool wr64UiBitmapContains(const std::array<Bitmap, N> &bitmaps,
        uint64_t hash, uint32_t width, uint32_t height) {
        for (const auto &bitmap : bitmaps)
            if (hash == bitmap.tmemHash && width == bitmap.width && height == bitmap.height) return true;
        return false;
    }

    inline bool wr64UiFilterEligible(const Wr64UiFilterDraw &draw) {
        // Projection values are stable RT64 ABI: 2=orthographic, 3=rectangle.
        // Rectangle is not sufficient: suns and tiled scene effects use it too.
        if ((draw.projectionType != 2 && draw.projectionType != 3) ||
            draw.rawTMEM || draw.tileCopyUsed || draw.tiles != 1 ||
            draw.triangles != 2 || draw.textureOn == 0 || draw.tmemHash == 0 ||
            draw.sampleWidth == 0 || draw.sampleHeight == 0 ||
            ((draw.otherModeH >> 20) & 3U) >= 2U) return false;

        // Complete fonts may use shaded orthographic quads as well as ordinary
        // texture rectangles. No world projection is admitted, even for a match.
        if (wr64UiFontContains(Wr64UiMainFont, draw.tmemHash))
            return draw.sampleWidth == 24 && draw.sampleHeight == 20;
        if (wr64UiFontContains(Wr64UiSmallFont, draw.tmemHash))
            return draw.sampleWidth == 8 && draw.sampleHeight == 8;
        if (wr64UiFontContains(Wr64UiSelectFont, draw.tmemHash))
            return draw.sampleWidth == 16 && draw.sampleHeight == 12;

        // Verified complete word images and menu widgets use the same filter
        // as individual glyphs. Selection/disabled tint comes from the combiner
        // and must not remove an otherwise identical UI bitmap from coverage.
        if (wr64UiBitmapContains(Wr64UiWatercraftBitmaps, draw.tmemHash,
                draw.sampleWidth, draw.sampleHeight) ||
            wr64UiBitmapContains(Wr64UiCourseBitmaps, draw.tmemHash,
                draw.sampleWidth, draw.sampleHeight)) return true;

        // Native USA Main Menu stores these words as complete IA8 bitmaps,
        // not atlas characters. Recorded in wr64-main-menu-hud-trace.csv:
        // selectable labels at lines 43228..43232, Press START at 25808,
        // copyright at 25133. Dimensions and content are confirmed by the
        // matching .v5.tile.json/.tmem files in the 20260716-024237 dump.
        // Selected and ordinary labels use the two exact combiner pairs below;
        // all five choices must retain filtering as the selection moves.
        if (draw.projectionType == 3 && draw.otherModeH == 0x00000CFFU &&
            draw.otherModeL == 0x00504240U) {
            const bool ordinaryLabel = draw.combinerH == 0xFFFCF279U &&
                draw.combinerL == 0xFCFFFFFFU;
            const bool highlightedLabel = draw.combinerH == 0xFF2FFFFFU &&
                draw.combinerL == 0xFC119623U;
            const uint8_t combinerBit = ordinaryLabel ? 1 : (highlightedLabel ? 2 : 0);
            for (const auto &bitmap : Wr64UiMainMenuBitmaps) {
                if (draw.tmemHash == bitmap.tmemHash && draw.sampleWidth == bitmap.width &&
                    draw.sampleHeight == bitmap.height && (bitmap.combinerMask & combinerBit)) return true;
            }
        }

        // Exact established DrawPowerMsg fingerprint; do not inherit the anchor
        // helper's logging or any layout state just to classify this draw.
        if (draw.projectionType == 2) {
            const bool banner =
                (draw.tmemHash == 0x1DF6E18FA3F51003ULL && draw.sampleWidth == 144) ||
                (draw.tmemHash == 0x90C84829FC9E5904ULL && draw.sampleWidth == 128);
            return banner && draw.sampleHeight == 20 &&
                draw.combinerH == 0xFF33FFFFU && draw.combinerL == 0xFC121824U &&
                draw.otherModeH == 0x00082CFFU && draw.otherModeL == 0x00504240U;
        }

        // Verified Watercraft Select heading (native USA census, 176x18).
        if (draw.tmemHash == 0x342EB798B5720B9AULL)
            return draw.sampleWidth == 176 && draw.sampleHeight == 18;

        // Finish portrait flag backgrounds are UI, separately verified in
        // rt64_wr64_finish_hud.h. The select-font timers are covered above.
        if (draw.tmemHash == 0x41F74C7752C03ACDULL)
            return draw.sampleWidth == 32 && draw.sampleHeight == 20;
        if (draw.tmemHash == 0x13E7FF64CEB499C2ULL)
            return draw.sampleWidth == 36 && draw.sampleHeight == 24;

        // Trusted HUD fingerprints include timer digits, labels, portraits,
        // power indicators and miss markers. Position deliberately does not
        // matter: both multiplayer halves and all aspect ratios share content.
        // The table's separate boot badge family must remain unfiltered.
        for (const auto &widget : wr64HudAnchorWidgets()) {
            if (widget.name != "opening_logo" && widget.tmemHash != 0 &&
                widget.tmemHash == draw.tmemHash) return true;
        }
        return false;
    }
}
