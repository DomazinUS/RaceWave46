"""Compile the actual sky builder and cloud geometry, not a reimplementation."""
from pathlib import Path
import hashlib
import re
import sys
import tomllib

root, output = map(Path, sys.argv[1:3])
def extract(file, name):
    text = (root/'RecompiledFuncsPoint0'/file).read_text()
    start = text.index('RECOMP_FUNC void '+name+'(')
    return text[start:text.index('\n;}', start)+3]

body = extract('funcs_6.c', 'func_8008FB74')
# The later two-player Watercraft menu layout has its own complete native
# replay. Its four menu-only hooks are outside this pinned race-sky oracle.
preview_hooks = [h for h in tomllib.loads((root/'config/us.rev1.toml').read_text())['patches']['hook']
                 if h['func']=='func_8008FB74' and 'wr64_two_player_preview_' in h['text']]
assert {h['before_vram'] for h in preview_hooks}=={0x8008FDCC,0x8008FE64,0x8008FDF4,0x8008FE8C}
for h in preview_hooks:
    line = '    '+h['text']+'\n'
    marker = f"    // 0x{h['before_vram']:08X}:"
    assert body.count(line+marker)==1
    body = body.replace(line,'',1)
# Celestial projection/draw has its own native fixture. Here it is a no-op so
# the established cloud, seabed and fog evidence remains independently pinned.
celestial = [h for h in tomllib.loads((root/'config/us.rev1.toml').read_text())['patches']['hook']
             if h['func']=='func_8008FB74' and 'wr64_two_player_celestial_draw' in h['text']]
assert len(celestial)==1 and celestial[0]['before_vram']==0x80090C8C
celestial_line = '    '+celestial[0]['text']+'\n'
assert body.count(celestial_line)==1
body = body.replace(celestial_line, '', 1)
hooks = [h for h in tomllib.loads((root/'config/us.rev1.toml').read_text())['patches']['hook']
         if h['func']=='func_8008FB74' and 'wr64_sunny_sky_' in h['text']]
assert {h['before_vram'] for h in hooks} == {0x8008FBF4,0x80090194,0x80090430,0x80090524,0x8009064C,0x80090744,0x80090D44,0x80090E24,0x80090F38}
baseline = body
for h in hooks:
    line = '    '+h['text']+'\n'
    marker = f"    // 0x{h['before_vram']:08X}:"
    assert baseline.count(line+marker)==1
    baseline = baseline.replace(line+marker, marker, 1)
assert hashlib.sha256(baseline.encode()).hexdigest() == '11235e960279db848fdd8382dfe28ef01549c59215ec3d55f82beb9f9f7c2a0f'
rebuilt = baseline
for h in hooks:
    marker = f"    // 0x{h['before_vram']:08X}:"
    rebuilt = rebuilt.replace(marker, '    '+h['text']+'\n'+marker, 1)
assert rebuilt == body
cloud = extract('funcs_1.c', 'func_8004C1D0')
assert hashlib.sha256(cloud.encode()).hexdigest() == 'f8ef9705824c487b10e35fcac622b268b44cae53827695cfc6f7f32daf75fefe'
bottom = extract('funcs_1.c', 'func_8004C998')
# The separate Sunny 1P seabed-distance experiment is exercised by its own
# complete native producer replay; keep this established sky oracle pinned.
seabed_hooks = [h for h in tomllib.loads((root/'config/us.rev1.toml').read_text())['patches']['hook']
                if h['func']=='func_8004C998' and 'wr64_seabed_distance_' in h['text']]
assert len(seabed_hooks)==1 and seabed_hooks[0]['before_vram']==0x8004CC48
seabed_line = '    '+seabed_hooks[0]['text']+'\n'
assert bottom.count(seabed_line+'    // 0x8004CC48:')==1
bottom = bottom.replace(seabed_line,'',1)
bottom_hooks = [h for h in tomllib.loads((root/'config/us.rev1.toml').read_text())['patches']['hook']
                if h['func']=='func_8004C998' and 'wr64_sunny_sky_' in h['text']]
assert len(bottom_hooks)==1 and bottom_hooks[0]['before_vram']==0x8004C998
line = '    '+bottom_hooks[0]['text']+'\n'
assert bottom.count(line)==1
bottom_baseline = bottom.replace(line,'',1)
assert hashlib.sha256(bottom_baseline.encode()).hexdigest() == '8de09f55de5e46818c51b96f99572c3cf060354e338f44289225c2e26fcc54db'
assert bottom_baseline.replace('    // 0x8004C998:',line+'    // 0x8004C998:',1)==bottom
parts = ['#include "recomp.h"\n#include "funcs.h"\n#include "checked_memory.h"\n'
         'void baseline_bottom_vertex(uint8_t*,recomp_context*);\n'
         'void wr64_forensic_capture_sky(uint8_t*,uint32_t,uint32_t,uint32_t);\n',
         baseline.replace('void func_8008FB74(', 'void baseline_func_8008FB74(')
                 .replace('func_8004C998(rdram, ctx);','baseline_bottom_vertex(rdram, ctx);'), body,
         cloud.replace('void func_8004C1D0(', 'void actual_cloud_vertex('),
         bottom, bottom_baseline.replace('void func_8004C998(', 'void baseline_bottom_vertex('),
         extract('funcs_0.c', 'SysUtils_Round')]
output.write_text('\n'.join(parts))
