"""Extract production identity matching and matrix interpolation, without a GPU."""
from pathlib import Path
import re
import sys

root, output = map(Path, sys.argv[1:])
rsp = (root / 'lib/rt64/src/hle/rt64_rsp.cpp').read_text()
frame = (root / 'lib/rt64/src/hle/rt64_game_frame.cpp').read_text()
processor = (root / 'lib/rt64/src/render/rt64_transform_processor.cpp').read_text()


def block(source, declaration):
    start = source.index(declaration)
    brace = source.index('{', start)
    depth = 1
    end = brace + 1
    while depth:
        depth += (source[end] == '{') - (source[end] == '}')
        end += 1
    return source[start:end]


parts = [block(rsp, '    struct Wr64ArticulatedMatrixInfo {') + ';']
for signature in ('    static Wr64ArticulatedMatrixInfo decodeWr64ArticulatedMatrixAddress(',
                  '    static uint32_t wr64ArticulatedMatrixId(',
                  '    static TransformGroup makeWr64FinalMatrixGroup('):
    parts.append(block(rsp, signature))
parts.append(block(frame, '    void GameFrame::buildTransformIdMap('))

# Execute the actual mapping/rigid-body prefix. Geometry and UV interpolation that
# follows this prefix is outside this test's matrix-identity regression.
match = block(frame, '    void GameFrame::matchTransform(')
stop = match.index('        uint64_t curVertexHash = 0;')
parts.append(match[:stop] + '    }')
merge_start = frame.index('            auto curIt = curWorkload.transformIdMap.begin();')
merge_end = frame.index('\n\n', frame.index('                    prevIt++;', merge_start))
# The blank-line boundary occurs after the whole while loop, not inside it.
merge = frame[merge_start:merge_end]
assert merge.count('matchTransform(') == 1 and merge.count('{') == merge.count('}')
parts.append('''void GameFrame::matchIds(Workload &curWorkload, const Workload &prevWorkload,
    GameFrameMap::WorkloadMap &curWorkloadMap, const GameFrameMap::WorkloadMap *prevWorkloadMap) {
    ModifiedBuffers modifiedBuffers;
''' + merge + '\n}')

loop = block(processor, '                for (size_t t = 0; t < drawData.worldTransforms.size(); t++) {')
parts.append('''void interpolate(DrawData &drawData, const DrawData &prevDrawData,
    const GameFrameMap::WorkloadMap &workloadMap, float weight) {
    struct { float prevFrameWeight, curFrameWeight; } p{0.0f, weight};
    auto &lerpWorldTransforms = drawData.lerpWorldTransforms;
    auto &invTWorldTransforms = drawData.invTWorldTransforms;
    auto &prevWorldTransforms = drawData.prevWorldTransforms;
    lerpWorldTransforms.clear(); invTWorldTransforms.clear(); prevWorldTransforms.clear();
    hlslpp::float4x4 prevMatrix, curMatrix, invMatrix, invTMatrix;
''' + loop + '\n}')

parts.append(block(rsp, '    void RSP::pushViewport()'))
parts.append(block(rsp, '    void RSP::popViewport()'))

# Lock the real integration point and native viewport provenance. The vertical
# feature emits extended split markers; native viewport command addresses persist.
assert re.search(r'wr64ArticulatedMatrixId\(articulated,\s*wr64ViewportAddressStack\[viewportStackSize - 1\]\)', rsp)
assert 'wr64ViewportAddressStack[viewportStackSize - 1] = address;' in block(rsp, '    void RSP::setViewport(uint32_t address,')
assert 'wr64ViewportAddressStack[0] = 0;' in block(rsp, '    void RSP::reset()')
native = (root / 'RecompiledFuncsPoint0/funcs_6.c').read_text()
for pc, immediate in [('8008FFB4', '5730'), ('80090048', '5720')]:
    at = native.index('// 0x' + pc + ':')
    assert f'ctx->r15 = ADD32(ctx->r15, -0X{immediate});' in native[at:at + 180]
    assert 'ctx->r15 = S32(0X800E << 16);' in native[at - 800:at]
vertical = (root / 'src/wr64_split_screen.cpp').read_text()
assert 'wr64_split_screen_frame(' in vertical and 'vertical()' in vertical
assert 'wr64ViewportAddressStack' not in vertical and 'setViewport(' not in vertical

# Linear explicit identities are not eligible for the scene/call AUTO fallback.
assert '(group.matrixId == G_EX_ID_AUTO) || usesIdWithAutoOrdering' in frame
assert 'const bool matrixPairEligible' in frame
output.write_text('namespace RT64 {\n' + '\n\n'.join(parts) + '\n}\n')
print('Extracted actual RSP identity, matching prefix/merge, matrix output loop and viewport push/pop; source integration checks PASS.')
