"""Replay the complete native celestial producers with an independent baseline."""
from pathlib import Path
import hashlib
import re
import sys
import tomllib

root, output = map(Path, sys.argv[1:3])
source = (root/'RecompiledFuncsPoint0/funcs_5.c').read_text()
hooks = tomllib.loads((root/'config/us.rev1.toml').read_text())['patches']['hook']
digests = {
    'func_800895A0':'682dd376e8c343c18109b01d9cda3e3d81429e7a11af6569d67ceaf960ac5500',
    'func_8008962C':'43198c44186f51ddcd7a0c8fc26d4f4cd4effd4e130c2e20061b4fe68b694ae7',
    'func_80089E24':'d26448ec954d94e557338e63aba1905b95a56c43c2e6f03987a942e7df61603f',
    'func_80089F28':'bd3f80649ad98df3203109968eb359b10f7ce00608af43746944b0ff5fa537d5',
    'func_80089C08':'299929d07c8c08e8bb0e1269ad3721c65fa23a97fcf6a9b0a0afb3551e939e0f',
    'func_80089DEC':'c0e4fe5abc51af0dae3fcc0673861d1deabe8f9d3a19fec0899a8b99392b0e32',
}
def extract(text, name):
    match = re.search(r'void '+name+r'\(uint8_t\* rdram, recomp_context\* ctx\) \{', text)
    assert match, name
    return text[match.start():text.index('\n;}', match.start())+3]

parts = ['#include "recomp.h"\n#include "funcs.h"\n#include "checked_memory.h"']
selected = [h for h in hooks if h['func'] in digests and 'wr64_two_player_celestial_' in h['text']]
assert {h['before_vram'] for h in selected} == {0x80089648,0x80089758,0x80089F2C,0x80089F5C}
for name,pc,symbol,file in [
    ('func_8008FB74',0x80090C8C,'wr64_two_player_celestial_draw','funcs_6.c'),
    ('func_800933C4',0x80093450,'wr64_two_player_sun_overlay','funcs_6.c'),
    ('func_80051538',0x80051538,'wr64_two_player_sun_skip_shared_wash','funcs_1.c'),
]:
    entries=[h for h in hooks if h['func']==name and h.get('before_vram')==pc and symbol in h['text']]
    assert len(entries)==1, name+' durable consumer hook missing'
    text=extract((root/'RecompiledFuncsPoint0'/file).read_text(),name)
    assert text.count('    '+entries[0]['text']+f'\n    // 0x{pc:08X}:')==1, name+' generated consumer hook differs'
baseline_parts = []
for name, digest in digests.items():
    current = extract(source, name)
    baseline = current
    own_hooks = [h for h in selected if h['func']==name]
    for h in own_hooks:
        marker = f"    // 0x{h['before_vram']:08X}:"
        line = '    '+h['text']+'\n'+marker
        assert baseline.count(line)==1
        baseline=baseline.replace(line, marker, 1)
    assert hashlib.sha256(baseline.encode()).hexdigest()==digest, name+' native body changed'
    rebuilt=baseline
    for h in own_hooks:
        marker=f"    // 0x{h['before_vram']:08X}:"
        rebuilt=rebuilt.replace(marker, '    '+h['text']+'\n'+marker, 1)
    assert rebuilt==current
    parts.append(current)
    for other in digests:
        baseline=baseline.replace(other+'(', 'baseline_'+other+'(')
    baseline_parts.append(baseline)
parts.insert(1, '\n'.join(f'void baseline_{name}(uint8_t*,recomp_context*);' for name in digests))
parts.extend(baseline_parts)
parts.append(extract((root/'RecompiledFuncsPoint0/funcs_0.c').read_text(), 'SysUtils_MtxToMtxF'))
for name in ['func_8008D94C','func_8008CFEC','func_8008D454','func_8008BD2C']:
    consumer=extract(source,name)
    if name=='func_8008BD2C':
        camera_hooks=[h for h in hooks if h['func']==name and 'wr64_two_player_celestial_camera_address' in h['text']]
        assert len(camera_hooks)==1 and camera_hooks[0]['before_vram']==0x8008BD84
        assert consumer.count('    '+camera_hooks[0]['text']+'\n    // 0x8008BD84:')==1
    parts.append(consumer)
wash=extract((root/'RecompiledFuncsPoint0/funcs_1.c').read_text(), 'func_80051538')
parts.append(wash)
for h in hooks:
    if h['func']=='func_80051538' and 'wr64_two_player_sun_' in h['text']:
        marker=f"    // 0x{h['before_vram']:08X}:"
        wash=wash.replace('    '+h['text']+'\n'+marker,marker,1)
parts.append(wash.replace('func_80051538(', 'baseline_func_80051538(',1))
output.write_text('\n'.join(parts))
