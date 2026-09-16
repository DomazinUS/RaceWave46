"""Replay native course visibility, including the following unextended lists."""
from pathlib import Path
import hashlib
import sys
import tomllib

root, output = map(Path, sys.argv[1:3])
source = (root / 'RecompiledFuncsPoint0/funcs_3.c').read_text()
start = source.index('L_8006E9A0:')
current = source[start:source.index('L_8006EE9C:', start)]
hooks = [h for h in tomllib.loads((root / 'config/us.rev1.toml').read_text())['patches']['hook']
         if 'wr64_draw_distance_' in h['text'] or 'wr64_area_draw_distance_' in h['text']]
assert {(h['func'], h['before_vram']) for h in hooks} == {
    ('func_8006E674', 0x8006E9B0), ('func_8006E674', 0x8006EBC0), ('func_8006E674', 0x8006FE2C),
    ('func_8006E674', 0x80071DA0), ('func_8006E674', 0x8006EBD4), ('func_8006E674', 0x8006ED4C),
    ('func_8006E674', 0x8006EF10), ('func_8006E674', 0x8006FDF4)}
assert len(hooks) == 8
visibility_hooks = [h for h in hooks if h['before_vram'] in (0x8006E9B0, 0x8006EBC0, 0x8006EBD4, 0x8006ED4C)]
baseline = current
for h in visibility_hooks:
    line = '    ' + h['text'] + '\n'
    assert baseline.count(line) == 1
    baseline = baseline.replace(line, '', 1)
assert hashlib.sha256(baseline.encode()).hexdigest() == '80563bbf1d682adde8b96e30d0b7e2b57184da28e1ea0bccb8dd40fa7abb95fa'
regenerated = baseline
for h in visibility_hooks:
    marker = f"    // 0x{h['before_vram']:08X}:"
    assert regenerated.count(marker) == 1
    regenerated = regenerated.replace(marker, '    ' + h['text'] + '\n' + marker, 1)
assert regenerated == current, 'durable hooks differ from checked-in generated code'

def wrap(name, body, end):
    return ('RECOMP_FUNC void ' + name + '(uint8_t* rdram,recomp_context* ctx) {\n'
            'uint64_t hi=0,lo=0,result=0; int c1cs=0;\n' + body + '\n' + end + ': return;\n}\n')

parts = ['#include "recomp.h"\n#include "funcs.h"\n#include "checked_memory.h"\n',
         wrap('baseline_visibility', baseline, 'L_8006EE9C'),
         wrap('enhanced_visibility', current, 'L_8006EE9C'),
         wrap('regenerated_visibility', regenerated, 'L_8006EE9C')]
camera_start = source.index('    // 0x8006E80C:')
camera_prefix = source[camera_start:source.index('L_8006E858:', camera_start)]
parts.append(wrap('native_camera_direction', camera_prefix, 'L_8006E858'))
a = source.index('L_8006FE40:')
matrices = source[a:source.index('L_80070138:', a)]
assert hashlib.sha256(matrices.encode()).hexdigest() == 'f30ffa8ff90bbdc0a75d9a0e437d2cd0e51cf81f51a40956fe465e9de4c21c5c'
parts.append(wrap('native_buoy_matrices', matrices, 'L_80070138'))
a = source.index('    // 0x8006FE2C:')
matrix_prefix = source[a:source.index('L_80070138:', a)]
assert hashlib.sha256(matrix_prefix.encode()).hexdigest() == 'a5a3e7a1f40c37d8e2be5a91b8124e962b7e71c6266944d2787dda78108d212f'
capacity_hook = next(h for h in hooks if h['before_vram'] == 0x8006FE2C)
line = '    ' + capacity_hook['text'] + '\n'
assert source.count(line + matrix_prefix) == 1
parts.append(wrap('enhanced_buoy_matrices', line + matrix_prefix, 'L_80070138'))
end_hook = next(h for h in hooks if h['before_vram'] == 0x80071DA0)
line = '    ' + end_hook['text'] + '\n'
assert source.count(line + '    // 0x80071DA0:') == 1
assert source.index('L_800715F4:') < source.index(line + '    // 0x80071DA0:') < source.index('    // 0x80071DA4:')
parts.append(wrap('enhanced_buoy_end', line, 'end'))
light_start = source.index('L_80071DA0:')
light_body = source[light_start:source.index('L_80071DD4:', light_start)]
assert light_body.count(line) == 1
parts.append(wrap('native_twilight_tail', light_body.replace(line, '', 1), 'L_80071DD4'))
parts.append(wrap('extended_twilight_tail', light_body, 'L_80071DD4'))
body_start = source.index('L_80070138:')
checkpoint_body = source[body_start:source.index('L_800715F4:', body_start)]
assert hashlib.sha256(checkpoint_body.encode()).hexdigest() == 'd3c6e90f187667bcdc1ec6cb88f45650e2af0f21d28e343560abcac47c1ad9a4'
parts.append(wrap('native_checkpoint_body', checkpoint_body, 'L_800715F4'))
all_hooks = tomllib.loads((root / 'config/us.rev1.toml').read_text())['patches']['hook']
object_begin = next(h for h in all_hooks if h['before_vram'] == 0x80071630 and h['func'] == 'func_8006E674')
object_end = next(h for h in all_hooks if h['before_vram'] == 0x8007180C and h['func'] == 'func_8006E674')
body_start = source.index('    // 0x80071630:')
object_body = source[body_start:source.index('L_8007180C:', body_start)]
assert hashlib.sha256(object_body.encode()).hexdigest() == '344ad66e1c6765caa276cc275dc7d97495d95c5f03075a657f93c99343cb877d'
parts.append(wrap('native_object_body', object_body, 'L_8007180C'))
parts.append(wrap('extended_object_body', object_begin['text'] + '\n' + object_body,
                  'L_8007180C').replace('L_8007180C: return;', 'L_8007180C: ' + object_end['text'] + '\nreturn;'))
area_capacity_hook = next(h for h in hooks if h['before_vram'] == 0x8006EF10)
line = '    ' + area_capacity_hook['text'] + '\n'
a = source.index('    // 0x8006EF10:')
area_matrices = source[a:source.index('L_8006F050:', a)]
assert hashlib.sha256(area_matrices.encode()).hexdigest() == '008784b0592da889d6747f6193ac04c7da53a9e8bccc7cbb907cb5ca36ea3109'
assert source.count(line + area_matrices) == 1
parts.append(wrap('enhanced_area_matrices', line + area_matrices, 'L_8006F050'))
parts.append(wrap('native_area_matrices', area_matrices, 'L_8006F050'))
area_end_hook = next(h for h in hooks if h['before_vram'] == 0x8006FDF4)
line = '    ' + area_end_hook['text'] + '\n'
assert source.count(line + '    // 0x8006FDF4:') == 1
parts.append(wrap('enhanced_area_end', line, 'end'))
for name, start, end, digest in [
    ('area_type0_top', '8006F34C', '8006F450', '57f8c6370d39f6be49f19f70e325884919f74e69c44d58e71e9ad985b2ffd9c2'),
    ('area_type0_bottom', '8006F53C', '8006F60C', '6358a0b9f85a194026742a75860b4b9190f6dda4d40f2cbab376954a137942d9'),
    ('area_type1_top', '8006F788', '8006F884', '27a87427e154739feda9d449ef87aeb590f0ebe46c0b4fc16f48a4a0614d7f30'),
    ('area_type1_bottom', '8006F95C', '8006FA2C', '162592adecb8e7eeae5acb7eada4e9ec22d7072570427ee38dc33a9e1a030532')]:
    a = source.index('    // 0x' + start + ':')
    body = source[a:source.index('L_' + end + ':', a)]
    assert hashlib.sha256(body.encode()).hexdigest() == digest
    parts.append(wrap(name, body, 'L_' + end))
for file, names in [('funcs_0.c', ['SysUtils_MatrixLookAt', 'SysUtils_MtxFToMtx']),
                    ('funcs_3.c', ['func_8006CB98', 'func_8006CDE8']),
                    ('funcs_19.c', ['func_801EDFFC', 'func_801EDF9C', '_MtxF_to_Mtx']),
                    ('funcs_15.c', ['_nsqrtf'])]:
    text = (root / 'RecompiledFuncsPoint0' / file).read_text()
    for name in names:
        a = text.index('RECOMP_FUNC void ' + name + '(')
        parts.append(text[a:text.index('\n;}', a) + 3])
output.write_text('\n'.join(parts))
