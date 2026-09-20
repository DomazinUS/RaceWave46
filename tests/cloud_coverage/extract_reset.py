"""Compile production reset, raster override and tile decoding with real types."""
from pathlib import Path
import sys

root, output = map(Path, sys.argv[1:])
source = (root / 'lib/rt64/src/hle/rt64_workload.cpp').read_text()
start = source.index('    void Workload::resetDrawData() {')
end = source.index('\n    void Workload::resetDrawDataRanges()', start)
function = source[start:end].replace('void Workload::resetDrawData()',
    'void wr64TestActualResetDrawData(DrawData &drawData)', 1)
renderer = (root / 'lib/rt64/src/render/rt64_framebuffer_renderer.cpp').read_text()
begin = renderer.index('                if (wr64RTSkyCall && p.wr64RtPresentation &&')
finish = renderer.index('\n                // Composer viewport edges', begin)
override = renderer[begin:finish]
wrapper = '''
void wr64TestActualCloudRasterOverride(const DrawData &drawData, const GameCall &call,
    const Projection &proj, InstanceDrawCall &drawCall, bool composerMatched, bool viewportNudge, bool presentation) {
    std::vector<InstanceDrawCall> instanceDrawCallVector{drawCall};
    const auto &triangles = drawCall.triangles;
    const bool wr64RTSkyCall = wr64RTSkySignature(call.callDesc.triangleCount,
        call.callDesc.colorCombiner.L, call.callDesc.colorCombiner.H,
        call.callDesc.otherMode.L, call.callDesc.otherMode.H);
    struct { bool matched; } wr64ComposerOverride{composerMatched};
    const bool wr64ApplyViewportNudge = viewportNudge;
    struct { bool wr64RtPresentation; } p{presentation};
''' + override + '''
    drawCall = instanceDrawCallVector.back();
}
'''
state = (root / 'lib/rt64/src/hle/rt64_state.cpp').read_text()
snapshot_begin = state.index('            float slope = 0.0f, intercept = 0.0f;', state.index('if (wr64CloudCoverageEnabled())'))
snapshot_end = state.index('            // Keep a bounded sample', snapshot_begin)
append_begin = state.index('                        const bool appended = wr64AppendCloudCoverage', snapshot_end)
append_end = state.index('                        if (WR64_DIAGNOSTIC_ENABLED', append_begin)
ending_wrapper = '''
unsigned wr64TestActualEndingCloudPreparation(const uint8_t *RDRAM, DrawData &draw,
    GameCall &call, uint32_t view) {
    struct Cache { unsigned submissions=0; void submit(const ShaderDescription &) { ++submissions; } } cache;
    struct { Cache *rasterShaderCache; } ext{&cache};
    struct { DrawData &drawData; } workload{draw};
    struct { uint32_t transformsIndex; } projection{view};
''' + state[snapshot_begin:snapshot_end] + state[append_begin:append_end] + '''
    return cache.submissions;
}
'''
scale_begin = state.index('    const float ShiftScaleMap[] = {')
scale_end = state.index('\n    };', scale_begin) + len('\n    };')
sampling_begin = state.index('                    const bool RGBA32 = (tile.siz')
sampling_end = state.index('                    // Check if we need to use raw TMEM', sampling_begin)
decode_begin = state.index('                    dstRDPTile.fmt = tile.fmt;')
decode_end = state.index('                    auto clampAlignedToMask = ', decode_begin)
tile_wrapper = state[scale_begin:scale_end] + '''
void wr64TestActualDecodeCloudTile(const LoadTile &tile, const DrawCall &drawCall,
    DrawCallTile &dstCallTile, interop::RDPTile &dstRDPTile) {
    dstCallTile.valid = tile.line != 0;
    dstCallTile.loadTile = tile;
''' + state[sampling_begin:sampling_end] + state[decode_begin:decode_end] + '\n}\n'
output.write_text('#include "common/rt64_wr64_cloud_coverage_integration.h"\n'
    '#include "common/rt64_wr64_rt_scope.h"\n'
    '#include "render/rt64_framebuffer_renderer_call.h"\nnamespace RT64 {\n'
    + function + wrapper + tile_wrapper + ending_wrapper + '\n}\n')
