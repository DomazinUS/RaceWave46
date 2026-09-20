// Presentation-only mapping of the USA game's two horizontal race cameras.
// Native camera matrices, half-scissors and interpolation identities remain
// untouched. The workload carries the explicit native race/settings gate.
#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>

namespace RT64 {
    struct Wr64VerticalRect {
        float left = 0, top = 0, right = 0, bottom = 0;
    };

    struct Wr64VerticalAffine {
        float scale = 1, dx = 0, dy = 0;
        float x(float value) const { return value * scale + dx; }
        float y(float value) const { return value * scale + dy; }
    };

    struct Wr64VerticalLayout {
        bool active = false;
        float width = 0, height = 0, nativeScale = 0, hudExtension = 0;
        float seam = 0, hudScale = 1;
    };

    inline Wr64VerticalLayout wr64VerticalLayout(bool enabled, float width,
        float height, float nativeScale, float hudExtension = 0)
    {
        Wr64VerticalLayout result;
        if (!enabled || !std::isfinite(width) || !std::isfinite(height) ||
            !std::isfinite(nativeScale) || !std::isfinite(hudExtension) ||
            width < 2 || height < 2 || nativeScale <= 0 || hudExtension < 0) return result;
        result.active = true;
        result.width = width;
        result.height = height;
        result.nativeScale = nativeScale;
        result.hudExtension = hudExtension;
        // One shared integer edge: an odd target has one additional right
        // column, with no overlap or uncovered column at the divider.
        result.seam = std::floor(width * 0.5f);
        result.hudScale = std::min(1.0f, result.seam / (424.0f * nativeScale));
        return result;
    }

    inline bool wr64VerticalPlayer(const Wr64VerticalLayout &layout, int half) {
        return layout.active && (half == 1 || half == 2);
    }

    inline Wr64VerticalRect wr64VerticalPane(const Wr64VerticalLayout &layout, int half) {
        if (!wr64VerticalPlayer(layout, half)) return {};
        return { half == 1 ? 0.0f : layout.seam, 0.0f,
            half == 1 ? layout.seam : layout.width, layout.height };
    }

    inline Wr64VerticalAffine wr64VerticalWorld(const Wr64VerticalLayout &layout, int half) {
        if (!wr64VerticalPlayer(layout, half)) return {};
        const auto pane = wr64VerticalPane(layout, half);
        return { 2.0f, (pane.left + pane.right) * 0.5f - layout.width,
            layout.height * (half == 1 ? 0.0f : -1.0f) };
    }

    // Keep each measured widget together. The HUD's existing edge placement
    // (including Clamp16:9) defines the source anchor; each player's pane defines
    // its destination. A uniform fit keeps circles and glyphs proportional.
    inline Wr64VerticalAffine wr64VerticalHud(const Wr64VerticalLayout &layout,
        int half, int anchorX, int anchorY)
    {
        if (!wr64VerticalPlayer(layout, half)) return {};
        const auto pane = wr64VerticalPane(layout, half);
        anchorX = std::clamp(anchorX, -1, 1);
        anchorY = std::clamp(anchorY, -1, 1);
        const float sourceX = layout.width * 0.5f + anchorX *
            (212.0f * layout.nativeScale + layout.hudExtension);
        const float sourceY = (half - 1) * layout.height * 0.5f +
            (anchorY + 1) * layout.height * 0.25f;
        const float targetX = (pane.left + pane.right) * 0.5f +
            anchorX * (pane.right - pane.left) * 0.5f;
        const float targetY = (anchorY + 1) * layout.height * 0.5f;
        return { layout.hudScale, targetX - layout.hudScale * sourceX,
            targetY - layout.hudScale * sourceY };
    }

    // A track indicator follows the scene point, while its icon retains the
    // same uniform scale as the HUD. All pieces must use the same center.
    inline Wr64VerticalAffine wr64VerticalMarker(const Wr64VerticalLayout &layout,
        int half, float centerX, float centerY)
    {
        if (!wr64VerticalPlayer(layout, half)) return {};
        const auto world = wr64VerticalWorld(layout, half);
        return { layout.hudScale, world.x(centerX) - layout.hudScale * centerX,
            world.y(centerY) - layout.hudScale * centerY };
    }

    inline Wr64VerticalAffine wr64VerticalAnnouncement(const Wr64VerticalLayout &layout,
        int half, float nativeOffsetY)
    {
        if (!wr64VerticalPlayer(layout, half)) return {};
        auto result = wr64VerticalHud(layout, half, 0, 0);
        // Indexed font vertices did not receive the ordinary rectangle HUD's
        // established per-half correction. Apply it once to the complete text.
        result.dy += result.scale * nativeOffsetY * layout.nativeScale;
        return result;
    }

    inline Wr64VerticalRect wr64VerticalMapRect(const Wr64VerticalAffine &mapping,
        const Wr64VerticalRect &rect)
    {
        return { mapping.x(rect.left), mapping.y(rect.top),
            mapping.x(rect.right), mapping.y(rect.bottom) };
    }

    inline Wr64VerticalRect wr64VerticalClip(const Wr64VerticalRect &rect,
        const Wr64VerticalRect &pane)
    {
        const float left = std::clamp(rect.left, pane.left, pane.right);
        const float top = std::clamp(rect.top, pane.top, pane.bottom);
        return { left, top, std::clamp(rect.right, left, pane.right),
            std::clamp(rect.bottom, top, pane.bottom) };
    }

    // Compose the pixel-space affine with RasterVS's final clip transform.
    // Keep the half-pixel raster convention outside the user-space scaling.
    inline void wr64VerticalCompose(const Wr64VerticalLayout &layout,
        const Wr64VerticalAffine &mapping, float &scaleX, float &scaleY,
        float &offsetX, float &offsetY)
    {
        if (!layout.active) return;
        const float pixelX = 1.0f / layout.width;
        const float pixelY = -1.0f / layout.height;
        scaleX *= mapping.scale;
        scaleY *= mapping.scale;
        offsetX = pixelX + mapping.scale * (offsetX - pixelX) +
            mapping.scale - 1.0f + 2.0f * mapping.dx / layout.width;
        offsetY = pixelY + mapping.scale * (offsetY - pixelY) +
            1.0f - mapping.scale - 2.0f * mapping.dy / layout.height;
    }

    // Exact source-half scissors, in RDP quarter pixels. The full-frame HUD,
    // depth clear, dimmer and transitions cannot accidentally select a player.
    inline int wr64VerticalHalfScissor(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
        if (x1 != 0 || x2 != 424 * 4) return 0;
        if (y1 == 0 && y2 == 120 * 4) return 1;
        if (y1 == 120 * 4 && y2 == 240 * 4) return 2;
        return 0;
    }

    // The native viewports are independent of projection/scissor batching.
    // This also identifies P1's signal pass, whose scissor is the full frame.
    enum class Wr64VerticalViewport { Shared, World, Signal, Indicator };
    inline Wr64VerticalViewport wr64VerticalViewport(float scaleX, float scaleY,
        float translateX, float translateY, int &half)
    {
        half = 0;
        if (scaleX != 212.0f || std::abs(scaleY) != 120.0f || translateX != 212.0f)
            return Wr64VerticalViewport::Shared;
        if (translateY == 60.0f || translateY == 180.0f) {
            half = translateY == 60.0f ? 1 : 2;
            return Wr64VerticalViewport::World;
        }
        if (translateY == 26.0f || translateY == 146.0f) {
            half = translateY == 26.0f ? 1 : 2;
            return Wr64VerticalViewport::Signal;
        }
        if (translateY == 28.0f || translateY == 138.0f) {
            half = translateY == 28.0f ? 1 : 2;
            return Wr64VerticalViewport::Indicator;
        }
        return Wr64VerticalViewport::Shared;
    }

    inline Wr64VerticalAffine wr64VerticalAuxiliary(const Wr64VerticalLayout &layout,
        Wr64VerticalViewport role, int half, float viewportY)
    {
        if (!wr64VerticalPlayer(layout, half) ||
            (role != Wr64VerticalViewport::Signal && role != Wr64VerticalViewport::Indicator)) return {};
        auto result = wr64VerticalMarker(layout, half, layout.width * 0.5f,
            viewportY * layout.nativeScale);
        if (role == Wr64VerticalViewport::Indicator && half == 2) {
            // Only the indicator retains the original110px viewport pitch.
            // Normalize its destination to P1 without mutating source data.
            result.dy += 20.0f * layout.nativeScale;
        }
        return result;
    }

    // These two final coverage-cleanup strips belong to the old horizontal
    // seam/bottom. They are not color fills or a divider to rotate into view.
    inline bool wr64VerticalCoverageStrip(int32_t x1, int32_t y1, int32_t x2,
        int32_t y2, uint32_t otherModeL, uint32_t fillColor)
    {
        return x1 == 8 * 4 && x2 == 415 * 4 &&
            ((y1 == 119 * 4 && y2 == 120 * 4) ||
             (y1 == 228 * 4 && y2 == 229 * 4)) &&
            otherModeL == 0x5F505240U && fillColor == 0xFFFFFFFFU;
    }
}
