// WR64 power banners: stable draw identity, independent of emission order.
// DrawPowerMsg uses two orthographic triangles, one IA8 texture and the same
// combiner/render mode for both banners. Their native color and scale animate;
// framebuffer pair, projection and call indices vary with other visible draws.
// The previous finite signature table included those indices, so an unchanged
// banner could alternate between corrected and uncorrected placement.
//
// Texture hashes are byte-verified against the user's USA ROM (MAX POWER at
// 0x13C9A0, POWER UP! at0x13AFF0), and the complete fingerprint is corroborated
// by the existing multi-course object censuses. These are fingerprints only;
// this header contains no ROM texture or game code.
//
// Keep the established translations and two-player placement below. The draw
// bounding rectangle is deliberately not identity: it can be the full frame
// or a small conservative bound during the same banner's native animation.
#pragma once

#include "../../../../include/wr64_diagnostic_policy.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include "rt64_wr64_2p_frame.h"

namespace RT64 {
    inline constexpr uint64_t Wr64MaxPowerTexture = 0x1DF6E18FA3F51003ULL;
    inline constexpr uint64_t Wr64PowerUpTexture = 0x90C84829FC9E5904ULL;

    // ★ ALWAYS ON. POWER UP! and MAX POWER follow the power meter. Validated by
    // eye 2026-07-29 ("Just tested, it perfect now"), including the POWER UP!
    // that fires at the race start, which behaves differently from the buoy one.
    inline bool wr64BannerAnchorEnabled() {
        static const bool announced = [] {
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[banneranchor] APPLYING (2 stable banner identities)\n"); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            return true;
        }();
        (void)announced;
        return true;
    }

    inline void wr64BannerAnchorParse(int &dx, int &dy) {
        // ★ +11,+19 native pixels - the same translation the power meter itself receives.
        dx = 11;
        dy = 19;
    }

    // Optional trace retains its historical columns, including the diagnostic
    // composer signature. That signature is no longer used for matching.
    inline const char *wr64BannerAnchorTracePath() {
        static const char *p = std::getenv("WR64_BANNER_TRACE");
        return p;
    }

    // latched_half is diagnostic only: the shared HUD projection retains the
    // last world viewport's latch. world_y/banner_half record the banner's own
    // transform, which is what the existing two-player placement uses.
    inline bool wr64BannerAnchorTraceArmed() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool armed = [] {
            const char *p = wr64BannerAnchorTracePath();
            if (p == nullptr) { return false; }
            std::FILE *f = std::fopen(p, "w");
            if (f == nullptr) { return false; }
            std::fprintf(f, "signature,tmem_hash,proj_index,call_index,"
                            "rect_ulx,rect_uly,rect_lrx,rect_lry,"
                            "sci_ulx,sci_uly,sci_lrx,sci_lry,"
                            "two_p,latched_half,world_y,banner_half,dx_applied,dy_applied\n");
            std::fclose(f);
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stdout, "[banneranchor] trace armed -> %s\n", p); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
            return true;
        }();
        return armed;
    }

    inline void wr64BannerAnchorTrace(uint64_t signature, uint64_t tmemHash,
        uint32_t projIndex, uint32_t callIndex,
        int32_t ulx4, int32_t uly4, int32_t lrx4, int32_t lry4,
        int32_t sciUlx4, int32_t sciUly4, int32_t sciLrx4, int32_t sciLry4,
        float worldY, int bannerHalf, int32_t dx4, int32_t dy4)
    {
        if (!wr64BannerAnchorTraceArmed()) { return; }
        const char *p = wr64BannerAnchorTracePath();
        std::FILE *f = std::fopen(p, "a");
        if (f == nullptr) { return; }
        std::fprintf(f, "%016llX,%016llX,%u,%u,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%d,%d,%.3f,%d,%.2f,%.2f\n",
            (unsigned long long)signature, (unsigned long long)tmemHash,
            unsigned(projIndex), unsigned(callIndex),
            ulx4 / 4.0, uly4 / 4.0, lrx4 / 4.0, lry4 / 4.0,
            sciUlx4 / 4.0, sciUly4 / 4.0, sciLrx4 / 4.0, sciLry4 / 4.0,
            wr64TwoPFrameActive() ? 1 : 0, wr64TwoPFrameHalf(), double(worldY), bannerHalf,
            dx4 / 4.0, dy4 / 4.0);
        std::fclose(f);
    }

    // Equal opposite viewport edges translate without resizing. One player
    // receives the power meter's +11,+19 pixels. In two player, +19 would move
    // player one's banner across the seam: use the existing per-half HUD offset
    // derived from this banner's transform instead. Its full-frame rect cannot
    // identify a player. Return RDP 10.2 quarter-pixel units.
    inline void wr64BannerAnchorOffset(float worldY, int32_t &outDx4, int32_t &outDy4,
        int &outHalf, bool &outPlaceable)
    {
        static const int32_t dx4 = [] { int a, b; wr64BannerAnchorParse(a, b); return int32_t(a * 4); }();
        static const int32_t dy4 = [] { int a, b; wr64BannerAnchorParse(a, b); return int32_t(b * 4); }();
        outHalf = 0;
        outPlaceable = false;
        if (wr64TwoPFrameActive()) {
            outDx4 = Wr64TwoPHudDxRight4;
            // Zero unless the transform below places it. An unplaceable banner
            // stays exactly where the game drew it, which is the safe answer.
            outDy4 = 0;
            outHalf = wr64TwoPBannerHalfFromWorldY(worldY, outPlaceable);
            if (outPlaceable) {
                // The banner belongs to its half's HUD and travels with it -
                // the same single dy every other element in that half gets.
                outDy4 = wr64TwoPHudDy4(outHalf);
            }
            return;
        }
        outDx4 = dx4;
        outDy4 = dy4;
    }

    // Orthographic (2), textured two-triangle IA8 banner, with the original
    // complete render-state fingerprint. No call-order or animated-color key.
    inline bool wr64BannerAnchorMatch(int32_t projectionType, uint64_t tmemHash,
        uint16_t sampleWidth, uint16_t sampleHeight, uint32_t triangles,
        uint32_t tiles, uint8_t textureOn, uint32_t combinerH, uint32_t combinerL,
        uint32_t otherModeH, uint32_t otherModeL)
    {
        const bool texture = (tmemHash == Wr64MaxPowerTexture && sampleWidth == 144) ||
            (tmemHash == Wr64PowerUpTexture && sampleWidth == 128);
        return projectionType == 2 && texture && sampleHeight == 20 &&
            triangles == 2 && tiles == 1 && textureOn == 1 &&
            combinerH == 0xFF33FFFFU && combinerL == 0xFC121824U &&
            otherModeH == 0x00082CFFU && otherModeL == 0x00504240U &&
            wr64BannerAnchorEnabled();
    }
};
