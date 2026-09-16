"""Compile unchanged production sky guards; check their real upload call order."""
from pathlib import Path
import csv
import sys

root, out = map(Path, sys.argv[1:])
sky = (root / 'lib/rt64/src/common/rt64_wr64_sky_bracket.h').read_text()
frame = (root / 'lib/rt64/src/hle/rt64_game_frame.cpp').read_text()
header = (root / 'lib/rt64/src/hle/rt64_game_frame.h').read_text()
draw = (root / 'lib/rt64/src/hle/rt64_draw_call.h').read_text()

def function(source, name):
    start = source.rfind('\n', 0, source.index(name + '(')) + 1
    end = source.index('\n    }', start) + len('\n    }')
    return source[start:end]

def structure(source, name):
    start = source.index('    struct ' + name + ' {')
    end = source.index('\n    };', start) + len('\n    };')
    return source[start:end]

types = draw[draw.index('    enum class DrawAttribute'):draw.index('    struct DrawStatus')]
types += '\n' + '\n'.join(structure(header, name) for name in
                          ['GameIndices', 'GameScene', 'ModifiedBuffers'])
types += '\n' + structure(sky, 'Wr64SkyBracketLocation')
with (Path(__file__).parent / 'captured-cloud-materials.csv').open() as f:
    captured = list(csv.DictReader(f))
assert len(captured) == 2
types += '\nconstexpr uint32_t CapturedSkyMaterial[2][6] = {\n'
for view, row in enumerate(captured):
    assert row['matrix_id'] == f'5752430{view}' and row['unique_vertices'] == '7'
    values = [int(row['tri_count'])] + [int(row[k], 16) for k in
              ['combiner_l', 'combiner_h', 'othermode_l', 'othermode_h', 'matrix_id']]
    types += '    {' + ','.join(f'0x{v:08X}U' for v in values) + '},\n'
types += '};\n'
(out / 'sky_types.inc').write_text('namespace RT64 {\n' + types + '\n}\n')

names = ['wr64SkyBracketEnvFlag', 'wr64SkyBracketEnabled',
         'wr64SkyBracketIsExactSkyCall', 'wr64SkyBracketFindAll',
         'wr64SkyTexcoordSmartEnabled', 'wr64SkyTexcoordJumpThreshold',
         'wr64SkyReanchorThreshold', 'wr64SkyTexcoordFixOne',
         'wr64SkyTexcoordFixApply', 'wr64SkyTexcoordFixSplitWorkload']
parts = [function(sky, name) for name in names]
# Reverse only the dither-mask change to preserve an executable old-classifier
# negative control. Finder and scene application bodies remain production code.
old = '\n'.join(function(sky, name) for name in
                ['wr64SkyBracketIsExactSkyCall', 'wr64SkyBracketFindAll', 'wr64SkyTexcoordFixApply'])
condition = '((desc.otherMode.H & ~rgbDitherMask) == 0x00882C3FU)'
assert condition in old
old = old.replace(condition, '(desc.otherMode.H == 0x00882C3FU)')
for name in ['wr64SkyBracketIsExactSkyCall', 'wr64SkyBracketFindAll', 'wr64SkyTexcoordFixApply']:
    old = old.replace(name, name + 'OldClassifier')
parts.append(old)

match_start = frame.index('    void GameFrame::match(')
match_end = frame.index('    void GameFrame::matchScene(', match_start)
match = frame[match_start:match_end]
late = match.index('wr64SkyTexcoordFixSplitWorkload(')
upload = match.index('if (!workloadsModified.empty())', late)
assert match.index('matchScenes(perspectiveScenes,') < late
assert match.index('matchScenes(orthographicScenes,') < late
assert match.rfind('curDraw.tcVelFloats[vertex * 2 + component] = delta;') < late
assert late < upload < match.index('velocityUploader->submit(worker, uploads)')
assert 'texcoordVelocityBuffer' in match[upload:]
# The existing fix is scene-based, so unmatched current scenes never reach it.
scene = frame[match_end:frame.index('    void GameFrame::', match_end + 10)]
assert 'if (curScene.projections.empty() || prevScene.projections.empty())' in scene
assert 'wr64SkyBracketEvaluate(workloadQueue, curScene, prevScene,' in scene
assert 'matchScene(workloadQueue, prevFrame, curScenes[candidate.curIndex]' in match
# Execute the real late loop too, including workload-index selection and merge.
loop_start = match.rfind('        for (const uint32_t workloadIndex : workloads)', 0, late)
assert loop_start >= 0
loop_end = match.index('\n        }', late) + len('\n        }')
parts.append('void applyLateLoop(WorkloadQueue &workloadQueue, '
             'const std::vector<uint32_t> &workloads, '
             'std::unordered_map<uint32_t, ModifiedBuffers> &workloadsModified) {\n' +
             match[loop_start:loop_end] + '\n}')
(out / 'sky_functions.inc').write_text(
    '#include "' + (root / 'include/wr64_diagnostic_policy.h').as_posix() + '"\n'
    'namespace RT64 {\n' + '\n'.join(parts) + '\n}\n')
print('PASS production integration: late correction follows matching/velocity writes and precedes upload')
