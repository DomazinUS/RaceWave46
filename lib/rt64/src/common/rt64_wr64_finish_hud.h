#pragma once

#include "rt64_common.h"
#include <array>
#include <vector>

namespace RT64 {
    // enstatus.c DrawRankFace: finished opponents use back3 (32x20),
    // the player uses back4 (36x24, starting at portrait tx-7). These hashes
    // were derived from exact reference/USA ROM byte matches using RT64's
    // TMEM row layout and XXH3 metadata; they are not position-only claims.
    inline constexpr uint64_t Wr64FinishBackground = 0x41F74C7752C03ACDULL;
    inline constexpr uint64_t Wr64FinishBackgroundEmphasized = 0x13E7FF64CEB499C2ULL;

    struct Wr64FinishHudRow {
        FixedRect background;
        int32_t portraitX = 0; // quarter-pixel coordinate before HUD anchoring
    };

    inline bool wr64FinishHudEnabled(int framebufferWidth, bool twoPlayer) {
        // The ordinary right-stack portraits/numerals already receive their
        // 11-pixel inset translation at the 424-wide baseline. Finished
        // checkerboards/times must receive it there too, even when the window
        // or selected HUD layout adds no ultrawide extension.
        return framebufferWidth == 424 && !twoPlayer;
    }

    inline bool wr64FinishHudBackground(const FixedRect &rect, uint64_t hash, Wr64FinishHudRow &row) {
        const bool emphasized = hash == Wr64FinishBackgroundEmphasized;
        if (hash != Wr64FinishBackground && !emphasized) return false;
        if (rect.isEmpty() || rect.lrx - rect.ulx != (emphasized ? 36 : 32) * 4 ||
            rect.lry - rect.uly != (emphasized ? 24 : 20) * 4) return false;
        row = { rect, rect.ulx + (emphasized ? 7 * 4 : 0) };
        return true;
    }

    // DrawLapTimeSub mode3 uses select-font digits0..9, minus37, apostrophe38,
    // quote39 and plus45. The same atlas appears in menus, so a hash alone is
    // insufficient: a same-frame finished portrait row must corroborate it.
    inline constexpr std::array<uint64_t, 14> Wr64FinishTimeGlyphs = {
        0xA96DAD369EB6FD77ULL, 0x5009956E5CCCD2A2ULL, 0x0FB5914E291DA6BAULL,
        0x83428B1A568E7E20ULL, 0xCF3E0D0EE9A5E075ULL, 0x38F5ACF02E429685ULL,
        0xD16BD5B189CE2C46ULL, 0xF16E8C92416D055EULL, 0xA25ACE7103977303ULL,
        0x40CB4DD05C577014ULL, 0xF0CBDEEB5EBD7CE6ULL, 0x3F130B49C2F3D9FEULL,
        0x0E0AF566A2092DFBULL, 0x84BB953665614FACULL
    };

    inline bool wr64FinishHudMember(const FixedRect &rect, uint64_t hash,
        const std::vector<Wr64FinishHudRow> &rows) {
        if (rows.empty()) return false;
        Wr64FinishHudRow background;
        if (wr64FinishHudBackground(rect, hash, background)) {
            for (const auto &row : rows) {
                if (rect.ulx == row.background.ulx && rect.uly == row.background.uly &&
                    rect.lrx == row.background.lrx && rect.lry == row.background.lry) return true;
            }
            return false;
        }
        if (rect.lrx - rect.ulx != 16 * 4 || rect.lry - rect.uly != 12 * 4) return false;
        bool glyph = false;
        for (uint64_t candidate : Wr64FinishTimeGlyphs) glyph |= hash == candidate;
        if (!glyph) return false;
        for (const auto &row : rows) {
            // DrawLapTime puts this row at tx-86; the optional sign extends
            // ten pixels left, the final digit ends at tx-7. RankFace's
            // chase animation can lift its background0..4px while time Y
            // remains at the row's original top+3.
            if (rect.ulx >= row.portraitX - 96 * 4 && rect.lrx <= row.portraitX - 7 * 4 &&
                rect.uly >= row.background.uly + 3 * 4 && rect.uly <= row.background.uly + 7 * 4 &&
                rect.lry <= row.background.lry) return true;
        }
        return false;
    }
}
