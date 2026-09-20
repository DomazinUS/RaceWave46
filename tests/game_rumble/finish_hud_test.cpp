#include "finish_hud_fixture.h"
#include "common/rt64_wr64_finish_hud.h"
#include "common/rt64_wr64_ultrawide.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace RT64;
namespace {
int checks = 0;
void require(bool condition, const char *message) {
    ++checks;
    if (!condition) { std::cerr << message << '\n'; std::exit(1); }
}
bool same(const FixedRect &a, const FixedRect &b) {
    return a.ulx == b.ulx && a.uly == b.uly && a.lrx == b.lrx && a.lry == b.lry;
}
FinishHudFixtureDraw rectangle(int x, int y, int w, int h, uint64_t hash) {
    return {{x * 4, y * 4, (x + w) * 4, (y + h) * 4}, hash};
}
// DrawRankFace/enstatus.c native relative positions: emphasized back tx-7,
// face tx+5, number tx-4; ordinary back tx, face tx+9, number tx+2.
std::vector<FinishHudFixtureDraw> nativeRows(bool finished, int playerRank = 0) {
    std::vector<FinishHudFixtureDraw> rows;
    const uint64_t portraits[] = {0x3865564DD6A7C98DULL, 0xB424A0547CF1D1B7ULL,
        0xBDAE6282AD01AEEDULL, 0xCEC83F35BB73A226ULL};
    const uint64_t numbers[] = {0xC0B186E2CDE94E9FULL, 0xF4CD20A451616F89ULL,
        0x92CFC51E53A42BD0ULL, 0x49F6BAC053989176ULL};
    for (int rank = 0; rank < 4; ++rank) {
        const int tx = 374, ty = 60 + rank * 24 + (rank > playerRank ? 4 : 0);
        const bool emphasized = rank == playerRank;
        const uint64_t background = finished ? (emphasized ? Wr64FinishBackgroundEmphasized : Wr64FinishBackground)
            : (emphasized ? 0x900F997EFF175036ULL : 0xFF675B8437A41F00ULL);
        rows.push_back(rectangle(tx - (emphasized ? 7 : 0), ty, emphasized ? 36 : 32,
            emphasized ? 24 : 20, background));
        rows.push_back(rectangle(tx + (emphasized ? 5 : 9), ty + 2,
            emphasized ? 20 : 16, emphasized ? 20 : 16, portraits[rank]));
        rows.push_back(rectangle(tx + (emphasized ? -4 : 2), ty + (emphasized ? 4 : 2),
            8, 8, numbers[rank]));
        if (finished) {
            for (int column = 0; column < 7; ++column)
                rows.push_back(rectangle(tx - 86 + column * 10, ty + 3, 16, 12,
                    Wr64FinishTimeGlyphs[column]));
        }
    }
    return rows;
}
}
int main() {
    const auto finish = nativeRows(true), racing = nativeRows(false);
    // Includes narrow-window letterboxing, 16:9, ultrawide with centered HUD,
    // and ultrawide with expanded HUD. All use the USA 424-wide framebuffer.
    for (const auto extent : {Wr64PresentationExtent{960,720}, {1280,720}, {1680,720}, {2560,720}}) {
        const auto fit = wr64UsaPresentationExtent(extent.width, extent.height);
        const float scale = fit.height / 240;
        const float expansion = wr64UltrawideExpansion(fit.width / fit.height);
        const auto scene = wr64UltrawideLayout(scale * expansion, scale, 424);
        for (float hudExtension : {0.0f, 1.0f}) {
            const auto layout = wr64UltrawideHudLayout(scene, hudExtension);
            const auto after = finishHudActualRenderer(finish, 424, layout.halfExtension, false);
            const auto ordinary = finishHudActualRenderer(racing, 424, layout.halfExtension, false);
            for (size_t i = 0; i < finish.size(); ++i) {
                require(after[i].rect.ulx - finish[i].rect.ulx == 44,
                    "finished background/time/portrait/number must share the native 11-pixel right inset");
                require(after[i].rect.lrx - finish[i].rect.lrx == 44, "right edge must translate equally");
                require(after[i].rect.uly == finish[i].rect.uly && after[i].rect.lry == finish[i].rect.lry,
                    "finish-row correction must not move or resize vertically");
                require(after[i].anchor == 1, "every finish component must share the right ultrawide anchor");
            }
            for (size_t i = 0; i < racing.size(); ++i) {
                require(ordinary[i].rect.ulx - racing[i].rect.ulx == 44,
                    "ordinary racing portraits/numbers/backgrounds retain the validated inset");
                require(ordinary[i].anchor == 1, "ordinary racing anchor remains right");
            }
            for (size_t row = 0; row < 4; ++row) {
                const size_t base = row * 10;
                const auto &back = after[base], &face = after[base+1], &number = after[base+2];
                const int nativeFaceOffset = row == 0 ? 12 : 9;
                const int nativeNumberOffset = row == 0 ? 3 : 2;
                const auto project = [&](const FinishHudFixtureResult &draw) {
                    return layout.position(draw.rect.ulx * 0.25f * scale * expansion, draw.anchor);
                };
                require(std::abs(project(face) - project(back) - nativeFaceOffset * scale) < 0.001f,
                    "native portrait inset must survive final presentation at every aspect/HUD mode");
                require(std::abs(project(number) - project(back) - nativeNumberOffset * scale) < 0.001f,
                    "native rank numeral inset must survive final presentation");
            }
        }
    }
    // The player can finish at any rank: the larger background must remain
    // aligned there too, including the native 4-pixel gap below that row.
    for (int playerRank : {1,2,3}) {
        const auto rows = nativeRows(true, playerRank);
        const auto after = finishHudActualRenderer(rows,424,0,false);
        for (size_t i=0;i<rows.size();++i)
            require(after[i].rect.ulx - rows[i].rect.ulx == 44,
                "all possible player finishing positions must share the same inset");
    }
    // No finished checkerboard means shared time-font assets remain ordinary
    // menu text; both unknown textures and non-rectangle reuse are excluded.
    const std::vector<FinishHudFixtureDraw> menu = {
        rectangle(288,63,16,12,Wr64FinishTimeGlyphs[0]),
        rectangle(30,30,32,20,0x123456789ULL)};
    const auto menuOut = finishHudActualRenderer(menu,424,0,false);
    for (size_t i=0;i<menu.size();++i) require(same(menu[i].rect,menuOut[i].rect), "unrelated menus must stay unchanged");
    auto orthographic = finish;
    for (auto &draw : orthographic) draw.projection = 2;
    const auto orthoOut = finishHudActualRenderer(orthographic,424,0,false);
    for(size_t i=0;i<orthographic.size();++i) require(same(orthographic[i].rect,orthoOut[i].rect), "non-rectangle draws must stay unchanged");
    const auto otherWidth = finishHudActualRenderer(finish,320,0,false);
    require(same(finish[0].rect,otherWidth[0].rect), "offscreen/native320 checkerboard must not acquire new inset");
    require(same(finish[3].rect,otherWidth[3].rect), "offscreen/native320 time must not acquire new inset");
    // Two-player uses its established positional HUD rule; it must not receive
    // a second, finish-only offset. Compare against the same draws whose
    // checkerboard fingerprints do not activate the one-player census.
    auto twoPlayerControl = finish;
    for (size_t row=0;row<4;++row) twoPlayerControl[row*10].hash = 0x123456789ULL;
    const auto twoPlayer = finishHudActualRenderer(finish,424,200,true);
    const auto twoPlayerExpected = finishHudActualRenderer(twoPlayerControl,424,200,true);
    for(size_t i=0;i<finish.size();++i) require(same(twoPlayer[i].rect,twoPlayerExpected[i].rect), "two-player finish draws must retain only their existing rule");
    std::cout << checks << " actual renderer finish-HUD checks passed\n";
}
