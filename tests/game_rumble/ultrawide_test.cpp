#include "common/rt64_wr64_ultrawide.h"
#include "common/rt64_wr64_hud_anchor.h"
#include "common/rt64_wr64_finish_hud.h"
#include "wr64_ultrawide.hpp"

#include <cstdlib>
#include <iostream>
#include <limits>

using namespace RT64;

void require(bool result, const char *message) {
    if (!result) { std::cerr << message << '\n'; std::exit(1); }
}
void close(float actual, float expected, const char *message) {
    require(std::abs(actual - expected) < 0.0005f, message);
}

int main() {
    close(wr64UltrawideExpansion(4.0f / 3.0f), 1.0f, "4:3 must not change baseline");
    close(wr64UltrawideExpansion(16.0f / 9.0f), 1.0f, "16:9 must not change baseline");
    close(wr64UltrawideExpansion(21.0f / 9.0f), 21.0f / 16.0f, "21:9 extension");
    close(wr64UltrawideExpansion(32.0f / 9.0f), 2.0f, "32:9 extension");
    close(wr64UltrawideExpansion(std::numeric_limits<float>::quiet_NaN()), 1.0f, "invalid aspect fallback");
    close(wr64UltrawideExpansion(20.0f), 2.0f, "supported maximum");
    require(!wr64UltrawideLayout(3, 3, 424).active(), "baseline renderer must take old branch");
    require(!wr64UltrawideLayout(6, 3, 320).active(), "offscreen/native320 buffers must be excluded");

    for (const auto size : {Wr64PresentationExtent{1280, 720}, {1260, 540}, {1920, 540}}) {
        const auto fit = wr64UsaPresentationExtent(size.width, size.height);
        require(fit.width == size.width && fit.height == size.height,
            "16:9 through32:9 must preserve exact presentation dimensions");
    }
    const auto narrow = wr64UsaPresentationExtent(800, 600);
    close(narrow.width, 800, "narrow image width");
    close(narrow.height, 450, "4:3 window must letterbox16:9 image");
    const auto portrait = wr64UsaPresentationExtent(600, 900);
    close(portrait.height, 337.5f, "portrait window must preserve scene shape");
    const auto wider = wr64UsaPresentationExtent(2560, 540);
    close(wider.width, 1920, "beyond32:9 must pillarbox supported scene");
    close(wider.height, 540, "wide window image height");
    const auto minimized = wr64UsaPresentationExtent(0, 0);
    require(minimized.width == 0 && minimized.height == 0, "minimized presentation guard");

    for (const auto size : {Wr64PresentationExtent{1280, 720}, {1260, 540}, {1920, 540}}) {
        const float aspect = size.width / size.height;
        close(wr64UsaSceneAspect(aspect, true), aspect, "Expand preserves the supported world aspect");
        close(wr64UsaSceneAspect(aspect, false), Wr64BaselineAspect, "Native 16:9 disables extra world expansion");
        const auto nativeFit = wr64UsaPresentationExtent(size.width, size.height, false);
        close(nativeFit.width, size.height * Wr64BaselineAspect, "Native 16:9 fits without horizontal stretching");
        close(nativeFit.height, size.height, "Native 16:9 retains presentation height");
        close(wr64UsaHudExtensionPercentage(aspect, Wr64BaselineAspect), 0.0f,
            "16:9 HUD has no extra edge translation");
    }
    const auto nativeNarrow = wr64UsaPresentationExtent(800, 600, false);
    close(nativeNarrow.width, narrow.width, "native and expand agree below 16:9 width");
    close(nativeNarrow.height, narrow.height, "native and expand agree below 16:9 height");
    close(wr64UsaHudExtensionPercentage(32.0f / 9.0f, 32.0f / 9.0f), 1.0f, "expanded HUD reaches full scene edges");
    close(wr64UsaHudExtensionPercentage(32.0f / 9.0f, 24.0f / 9.0f), 0.5f, "intermediate HUD ratio scales only additional width");

    for (float aspect : {16.0f / 9.0f, 21.0f / 9.0f, 32.0f / 9.0f}) {
        const float expansion = wr64UltrawideExpansion(aspect);
        const auto layout = wr64UltrawideLayout(3.0f * expansion, 3.0f, 424);
        // Glyph authored at x10 after the established inset correction.
        // Its width12 and left margin10 stay unchanged in native pixel units.
        close(layout.position(30.0f * expansion, -1), 30.0f, "left widget margin");
        close(layout.extent(36.0f * expansion), 36.0f, "glyph width");
        close(layout.width - layout.position(414.0f * 3.0f * expansion, 1), 30.0f, "right widget margin");
        close(layout.position(212.0f * 3.0f * expansion), layout.width / 2.0f, "menu centre");
        // Native20px separation between two pieces must remain20px after the
        // complete group translates. This guards against per-glyph anchoring.
        close(layout.position(50.0f * expansion, -1) - layout.position(30.0f * expansion, -1), 20.0f, "widget internal spacing");
        const auto nativeHud = wr64UltrawideHudLayout(layout,
            wr64UsaHudExtensionPercentage(aspect, Wr64BaselineAspect));
        const auto expandedHud = wr64UltrawideHudLayout(layout, 1.0f);
        close(nativeHud.position(30.0f * expansion, -1), layout.halfExtension + 30.0f,
            "native HUD stays inside centered baseline plane");
        close(expandedHud.position(30.0f * expansion, -1), layout.position(30.0f * expansion, -1),
            "expanded HUD exactly preserves prior edge placement");
        close(nativeHud.extent(36.0f * expansion), expandedHud.extent(36.0f * expansion),
            "HUD placement changes no glyph widths");
        close(nativeHud.position(50.0f * expansion, -1) - nativeHud.position(30.0f * expansion, -1), 20.0f,
            "native HUD keeps each widget's internal spacing");
        close(nativeHud.position(layout.width * 0.5f), expandedHud.position(layout.width * 0.5f),
            "centered menu content does not follow HUD edge setting");
    }

    const auto queuedFrame = wr64UltrawideLayout(3.0f * (21.0f / 16.0f), 3, 424);
    wr64UltrawidePublishAspect(32.0f / 9.0f);
    close(wr64UltrawideLogicalWidth(), 848, "published native plane");
    close(wr64_sun_half_extension(), 212, "celestial additive centre");
    require(wr64_sun_logical_right_edge() == 847, "expanded reflection bound");
    require(wr64_sun_horizontal_cull_limit() == 976, "expanded cull bound");
    close(wr64_sun_record_window_limit(), 1360, "expanded record window");
    // A point60px right of centre must keep that displacement. A multiplier
    // here would incorrectly double the angular offset at32:9.
    close((272 + wr64_sun_half_extension()) - wr64_sun_logical_width() * 0.5f, 60, "celestial/world registration");
    close(queuedFrame.halfExtension, 198.75f, "queued frame must not read new resize state");
    wr64UltrawidePublishAspect(wr64UsaSceneAspect(32.0f / 9.0f, false));
    close(wr64UltrawideLogicalWidth(), 424, "native plane returns to baseline");
    close(wr64_sun_half_extension(), 0, "baseline celestial coordinate no-op");
    require(wr64_sun_logical_width_bits() == 0x43D40000, "baseline native width bits");
    require(wr64_sun_logical_right_edge() == 423, "baseline reflection bound");
    require(wr64_sun_horizontal_cull_limit() == 552, "baseline validated cull bound");
    close(wr64_sun_record_window_limit(), 1024, "baseline validated record window");

    wr64TwoPFrameRenderWorkload(false);
    require(wr64HudAnchorWidgets().size() == 176, "measured table and three advancement digits changed unexpectedly");
    for (const auto &widget : wr64HudAnchorWidgets()) {
        const FixedRect rect(widget.x1 * 4, widget.y1 * 4, widget.x2 * 4, widget.y2 * 4);
        require(wr64HudAnchorWidgetForRect(rect, widget.tmemHash) != nullptr, "measured widget lost");
        require(wr64HudUltrawideAnchor(rect, widget.tmemHash) == widget.ax, "table semantic anchor changed");
        int32_t dx = 0, dy = 0;
        require(wr64HudAnchorOffsetForRect(3, rect, widget.tmemHash, dx, dy), "baseline table match changed");
        require(dx == (widget.ax < 0 ? -48 : widget.ax > 0 ? 44 : 0), "baseline horizontal offset changed");
        require(dy == (widget.ay < 0 ? -72 : widget.ay > 0 ? 76 : 0), "baseline vertical offset changed");
    }
    require(wr64HudUltrawideAnchor(FixedRect(24 * 4, 34 * 4, 36 * 4, 50 * 4), 0x1234) == 0,
        "unknown texture must remain centred even in HUD coordinates");

    wr64TwoPFrameRenderWorkload(true);
    require(wr64HudUltrawideAnchor(FixedRect(123 * 4, 68 * 4, 139 * 4, 80 * 4), 0) == 0,
        "interval timer must stay together across third boundary");
    require(wr64HudUltrawideAnchor(FixedRect(147 * 4, 68 * 4, 163 * 4, 80 * 4), 0) == 0,
        "interval timer digits must stay centred");
    require(wr64HudUltrawideAnchor(FixedRect(30 * 4, 20 * 4, 42 * 4, 32 * 4), 0) == -1,
        "two-player left HUD");
    require(wr64HudUltrawideAnchor(FixedRect(370 * 4, 130 * 4, 382 * 4, 142 * 4), 0) == 1,
        "two-player right HUD");
    require(wr64HudUltrawideAnchor(FixedRect(30 * 4, 20 * 4, 40 * 4, 30 * 4), 0) == 0,
        "world-tracking portrait must not anchor");
    wr64TwoPFrameRenderWorkload(false);
    require(!wr64FinishHudEnabled(320, false), "finish grouping must not affect unrelated framebuffer widths");
    require(!wr64FinishHudEnabled(424, true), "finish grouping must not affect two-player HUD");
    require(wr64FinishHudEnabled(424, false), "baseline and expanded single-player finish group enabled");
    std::vector<Wr64FinishHudRow> finishRows;
    for (int rank = 0; rank < 4; rank++) {
        const int x = 374, y = 60 + rank * 24;
        const bool emphasized = rank == 0;
        const FixedRect background((x - (emphasized ? 7 : 0)) * 4, y * 4,
            (x + (emphasized ? 29 : 32)) * 4, (y + (emphasized ? 24 : 20)) * 4);
        Wr64FinishHudRow row;
        require(wr64FinishHudBackground(background, emphasized ? Wr64FinishBackgroundEmphasized : Wr64FinishBackground, row),
            "all four finishing checkerboards must be identified");
        require(row.portraitX == x * 4, "emphasized checkerboard must retain portrait origin");
        finishRows.push_back(row);
    }
    for (size_t rank = 0; rank < finishRows.size(); rank++) {
        const auto &row = finishRows[rank];
        const uint64_t backgroundHash = rank == 0 ? Wr64FinishBackgroundEmphasized : Wr64FinishBackground;
        require(wr64FinishHudMember(row.background, backgroundHash, finishRows), "checkerboard must follow its portrait");
        for (uint64_t hash : Wr64FinishTimeGlyphs) {
            const FixedRect glyph(row.portraitX - 86 * 4, row.background.uly + 3 * 4,
                row.portraitX - 70 * 4, row.background.uly + 15 * 4);
            require(wr64FinishHudMember(glyph, hash, finishRows), "every finish-time glyph must follow each portrait row");
            require(!wr64FinishHudMember(glyph, hash, {}), "shared menu font without finish background must not move");
            const FixedRect unrelated(80 * 4, glyph.uly, 96 * 4, glyph.lry);
            require(!wr64FinishHudMember(unrelated, hash, finishRows), "unrelated same-row menu glyph must not move");
            const FixedRect wrongRow(glyph.ulx, row.background.uly - 12 * 4, glyph.lrx, row.background.uly);
            require(!wr64FinishHudMember(wrongRow, hash, { row }), "font above corroborating portrait row must not move");
        }
        for (float aspect : {21.0f / 9.0f, 32.0f / 9.0f}) {
            const float expansion = wr64UltrawideExpansion(aspect);
            const auto layout = wr64UltrawideLayout(3 * expansion, 3, 424);
            const float portrait = row.portraitX / 4.0f + 5;
            const float time = row.portraitX / 4.0f - 86;
            // Both pieces receive the established11px inset and the same
            // additional right anchor, so the source spacing cannot change.
            const float portraitOut = layout.position((portrait + 11) * 3 * expansion, 1);
            const float timeOut = layout.position((time + 11) * 3 * expansion, 1);
            close(portraitOut - timeOut, (portrait - time) * 3, "finish-time/portrait spacing survives ultrawide expansion");
        }
    }
    Wr64FinishHudRow rejected;
    require(!wr64FinishHudBackground(FixedRect(374 * 4, 60 * 4, 406 * 4, 80 * 4), 0x900F997EFF175036ULL, rejected),
        "unfinished portrait background must not activate finish glyph matching");
    require(!wr64FinishHudBackground(FixedRect(0, 0, 128, 79), Wr64FinishBackground, rejected),
        "wrong-sized reused texture must not become finish background");
    std::cout << "Ultrawide invariants and176 identified widgets passed\n";
}
