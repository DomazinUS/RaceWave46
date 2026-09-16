"""Compile the actual native receiver admission; do not duplicate its predicates."""
from pathlib import Path
import sys

root, output = map(Path, sys.argv[1:])
source = (root / 'lib/rt64/src/render/rt64_framebuffer_renderer.cpp').read_text()


def block(declaration):
    start = source.index(declaration)
    brace = source.index('{', start)
    end, depth = brace + 1, 1
    while depth:
        depth += (source[end] == '{') - (source[end] == '}')
        end += 1
    return source[start:end]


static_receiver = block('        auto wr64StaticShoreReceiver = ')
caster_start = source.index('                            const bool shadowCaster = ')
caster = source[caster_start:source.index(';', caster_start) + 1]
selection = block('                            if (shadowCaster && (rt->params.shadowOptions.x == 1.0f')

# The tested block still sits behind native water/sky/material, texture-copy,
# camera-domain and ordinary indexed-triangle admission in the actual renderer.
outer = source[source.index('                const auto wr64RTMaterial = '):caster_start]
for guard in ('wr64IsWater(call)', '!wr64RTSkyCall && !wr64HasWater(call)',
              'wr64RTMaterial != Wr64RTMaterial::Rejected', '!tileCopy',
              'matrixDifference(drawData.modViewTransforms[proj.transformsIndex]'):
    assert guard in outer, guard

output.write_text('''void selectNativeReceiver(const Fixture &fixture, DrawData &drawData, Result &result) {
    auto *rt = &result;
    const auto &call = fixture.call;
    const auto &desc = call.callDesc;
    const auto &triangles = fixture.triangles;
    const bool wrongWayArrow = fixture.wrongWayArrow, trafficLights = fixture.trafficLights;
    const bool nextMark = fixture.nextMark, buoyLetter = fixture.buoyLetter, beam = fixture.beam;
    const auto &wr64ComposerOverride = fixture.composer;
    const bool wr64ApplyViewportNudge = fixture.viewportNudge;
    const bool wr64HasManualViewportOverride = fixture.manualViewport;
    const uint32_t instanceIndex = fixture.draw;
    auto wr64AppendSunnyFenceProxy = [&](const GameCall &, uint32_t draw) { result.fenceCandidates.push_back(draw); };
    if (RT64::wr64RTClassifyMaterial(desc.otherMode.L) == RT64::Wr64RTMaterial::Rejected) return;
''' + static_receiver + ';\n' + caster + '\n' + selection + '\n}\n')
print('Extracted production caster predicate, source-matrix classification and receiver selection; outer guards verified.')
