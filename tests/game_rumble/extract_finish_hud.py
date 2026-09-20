"""Compile actual finish-row renderer decisions without launching the game."""
from pathlib import Path
import sys

root, output = map(Path, sys.argv[1:3])
renderer = (root / 'lib/rt64/src/render/rt64_framebuffer_renderer.cpp').read_text(encoding='utf-8')

def section(start, end):
    first = renderer.index(start)
    return renderer[first:renderer.index(end, first)]

first = renderer.index('        std::vector<Wr64FinishHudRow> wr64FinishHudRows;')
opening = renderer.index('{', renderer.index('if (wr64FinishHudEnabled(', first))
depth = 1
end = opening + 1
while depth:
    depth += (renderer[end] == '{') - (renderer[end] == '}')
    end += 1
census = renderer[first:end] + '\n'
member = section('                const bool wr64FinishHudCall =',
                 '\n\n                // RECT TRACK.')
offset = section('                int32_t wr64HudAnchorDx = 0;',
                 '                const WR64LayerTrace::ComposerOverride')
anchor = section('                                    wr64WideHudAnchor =',
                 '                                    // STRETCH')

prefix = r'''#include "finish_hud_fixture.h"
#include "common/rt64_wr64_finish_hud.h"
#include "common/rt64_wr64_hud_anchor.h"
#include "common/rt64_wr64_ultrawide.h"
using namespace RT64;
namespace {
struct Projection { enum class Type { Orthographic = 2, Rectangle = 3 }; };
struct Desc { uint32_t tileCount = 1, tileIndex = 0; FixedRect rect; };
struct Call { Desc callDesc; };
struct FixtureProjection {
    Projection::Type type = Projection::Type::Rectangle;
    uint32_t gameCallCount = 0;
    std::vector<Call> gameCalls;
};
struct Pair { uint32_t projectionCount = 0; std::vector<FixtureProjection> projections; };
struct Tile { uint64_t tmemHashOrID; };
struct Data { std::vector<Tile> callTiles; };
struct Workload { Data drawData; };
struct Params { int fbWidth; Workload *curWorkload; };
}
std::vector<FinishHudFixtureResult> finishHudActualRenderer(
    const std::vector<FinishHudFixtureDraw> &draws, int framebufferWidth,
    float halfExtension, bool twoPlayer) {
    wr64TwoPFrameRenderWorkload(twoPlayer);
    Workload workload;
    Params p{framebufferWidth, &workload};
    Pair fbPair;
    Wr64UltrawideLayout wr64HudLayout;
    wr64HudLayout.halfExtension = halfExtension;
    for (const auto &input : draws) {
        FixtureProjection projection;
        projection.type = static_cast<Projection::Type>(input.projection);
        projection.gameCallCount = 1;
        projection.gameCalls.push_back({{1, uint32_t(workload.drawData.callTiles.size()), input.rect}});
        workload.drawData.callTiles.push_back({input.hash});
        fbPair.projections.push_back(projection);
    }
    fbPair.projectionCount = uint32_t(fbPair.projections.size());
'''
middle = r'''
    std::vector<FinishHudFixtureResult> results;
    for (const auto &proj : fbPair.projections) {
        for (const auto &call : proj.gameCalls) {
            const auto wr64HudTmemHash = workload.drawData.callTiles[call.callDesc.tileIndex].tmemHashOrID;
            FixedRect wr64ComposerCallRect = call.callDesc.rect;
            constexpr int wr64VerticalPauseHalf = 0, wr64VerticalLapHalf = 0;
            constexpr bool wr64VerticalSceneRect = false, wr64TwoPCelestialSceneRect = false;
            int wr64WideHudAnchor = 0;
'''
suffix = r'''
            results.push_back({wr64ComposerCallRect, wr64WideHudAnchor});
        }
    }
    wr64TwoPFrameRenderWorkload(false);
    return results;
}
'''
output.write_text(prefix + census + middle + member + '\n' + offset + anchor + suffix,
                  encoding='utf-8')
