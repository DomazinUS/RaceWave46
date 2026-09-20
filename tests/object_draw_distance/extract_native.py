"""Replay unchanged native visibility and the complete opaque object draw pass."""
from pathlib import Path
import hashlib
import json
import sys
import tomllib

root, output = map(Path, sys.argv[1:3])
source = (root / 'RecompiledFuncsPoint0/funcs_3.c').read_text()
hooks = tomllib.loads((root / 'config/us.rev1.toml').read_text())['patches']['hook']
selected = [h for h in hooks if 'wr64_object_distance_' in h['text']]
assert {(h['func'], h['before_vram']) for h in selected} == {
    ('func_8006E674', 0x80071630), ('func_8006E674', 0x8007180C)}
assert len(selected) == 2
begin = next(h for h in selected if h['before_vram'] == 0x80071630)
end = next(h for h in selected if h['before_vram'] == 0x8007180C)
for hook in selected:
    assert source.count('    ' + hook['text'] + '\n    // 0x%08X:' % hook['before_vram']) == 1

def wrap(name, body, end_label, epilogue=''):
    return ('RECOMP_FUNC void ' + name + '(uint8_t* rdram,recomp_context* ctx) {\n'
            'uint64_t hi=0,lo=0,result=0; int c1cs=0;\n' + body + '\n' + end_label + ':\n' + epilogue + '\nreturn;\n}\n')

a = source.index('L_8006E9A0:')
visibility = source[a:source.index('L_8006EE9C:', a)]
# Keep all three original lists, stripping only the separately validated buoy
# feature's hooks. Its exact native digest prevents algorithm substitutions.
for hook in hooks:
    if 'wr64_draw_distance_' in hook['text'] or 'wr64_area_draw_distance_' in hook['text']:
        visibility = visibility.replace('    ' + hook['text'] + '\n', '')
assert hashlib.sha256(visibility.encode()).hexdigest() == '80563bbf1d682adde8b96e30d0b7e2b57184da28e1ea0bccb8dd40fa7abb95fa'
a = source.index('    // 0x80071630:')
draw = source[a:source.index('L_8007180C:', a)]
assert hashlib.sha256(draw.encode()).hexdigest() == '344ad66e1c6765caa276cc275dc7d97495d95c5f03075a657f93c99343cb877d'
parts = ['#include "recomp.h"\n#include "funcs.h"\n#include "checked_memory.h"\n',
         wrap('original_visibility', visibility, 'L_8006EE9C'),
         wrap('original_draw', draw, 'L_8007180C'),
         wrap('enhanced_draw', begin['text'] + '\n' + draw, 'L_8007180C', end['text']),
         wrap('enhanced_begin', begin['text'], 'end'), wrap('enhanced_end', end['text'], 'end')]
manifest = {'visibility_sha256': hashlib.sha256(visibility.encode()).hexdigest(),
            'draw_sha256': hashlib.sha256(draw.encode()).hexdigest(),
            'hooks': {hex(h['before_vram']): h['text'] for h in selected},
            'production_files': {path: hashlib.sha256((root / path).read_bytes()).hexdigest()
                for path in ('src/wr64_object_distance.cpp', 'include/wr64_object_distance.hpp',
                             'config/us.rev1.toml', 'RecompiledFuncsPoint0/funcs_3.c')}}
for file, name in [('funcs_15.c', '_nsqrtf'), ('funcs_19.c', '_MtxF_to_Mtx')]:
    text = (root / 'RecompiledFuncsPoint0' / file).read_text()
    a = text.index('RECOMP_FUNC void ' + name + '(')
    native = text[a:text.index('\n;}', a) + 3]
    parts.append(native)
    manifest[name] = hashlib.sha256(native.encode()).hexdigest()
output.write_text('\n'.join(parts))
output.with_suffix('.json').write_text(json.dumps(manifest, indent=2) + '\n')
