"""Extract the actual local gate, both native passes and their matrix routines."""
from pathlib import Path
import sys
import tomllib

root, out = map(Path, sys.argv[1:3])
source = (root / 'RecompiledFuncsPoint0/funcs_3.c').read_text()
start = source.index('L_80071DA0:')
body = source[start:source.index('L_80071DD4:', start)]
hooks = tomllib.loads((root / 'config/us.rev1.toml').read_text())['patches']['hook']
# This independent light fixture has no preceding distance-admission frame.
# Its integration with the restored visibility is covered by tests/draw_distance.
cleanup = next(h for h in hooks if h['func'] == 'func_8006E674' and h['before_vram'] == 0x80071DA0)
cleanup_line = '    ' + cleanup['text'] + '\n'
assert body.count(cleanup_line) == 1 and 'wr64_draw_distance_end' in cleanup_line
body = body.replace(cleanup_line, '', 1)
original = body
for address in (0x80071DA4, 0x80071DC8):
    selected = [h for h in hooks if h['func'] == 'func_8006E674' and h['before_vram'] == address]
    assert len(selected) == 1
    line = '    ' + selected[0]['text'] + '\n'
    assert original.count(line) == 1
    clean = original.replace(line, '', 1)
    marker = f'    // 0x{address:08X}:'
    assert clean.replace(marker, line + marker, 1) == original
    original = clean

def wrap(name, text):
    return ('RECOMP_FUNC void ' + name + '(uint8_t* rdram, recomp_context* ctx) {\n'
            'uint64_t hi=0,lo=0,result=0; int c1cs=0;\n' + text + '\nL_80071DD4: return;\n}\n')

parts = ['#include "recomp.h"\n#include "funcs.h"\n#include "checked_memory.h"\n',
         wrap('baseline_twilight_lights', original), wrap('enhanced_twilight_lights', body)]
for file, names in [('funcs_3.c', ['func_8006CB98', 'func_8006CDE8', 'func_8006A264']),
                    ('funcs_19.c', ['func_801EDFFC', 'func_801EDF9C', '_MtxF_to_Mtx'])]:
    s = (root / 'RecompiledFuncsPoint0' / file).read_text()
    for name in names:
        a = s.index('RECOMP_FUNC void ' + name + '(')
        parts.append(s[a:s.index('\n;}', a) + 3])
out.write_text('\n'.join(parts))
