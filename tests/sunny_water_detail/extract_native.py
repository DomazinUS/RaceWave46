"""Replay the complete native draw, checking the durable material hook only."""
from pathlib import Path
import hashlib
import sys
import tomllib

root, output = map(Path, sys.argv[1:3])
source = (root/'RecompiledFuncsPoint0/funcs_6.c').read_text()
start = source.index('RECOMP_FUNC void Draw_WaterEffects(')
body = source[start:source.index('\n;}', start)+3]
hooks = tomllib.loads((root/'config/us.rev1.toml').read_text())['patches']['hook']
hooks = [h for h in hooks if h['func'] == 'Draw_WaterEffects' and 'wr64_sunny_water_' in h['text']]
assert {h['before_vram'] for h in hooks} == {0x80090F84,0x80091014,0x800911C4,0x80091228}
baseline=body
for h in hooks:
    line='    '+h['text']+'\n'
    marker=f"    // 0x{h['before_vram']:08X}:"
    assert baseline.count(line+marker)==1
    baseline=baseline.replace(line+marker,marker,1)
assert hashlib.sha256(baseline.encode()).hexdigest() == '6cd4d07f39fd3f896412f0dab616b28ecbd47b205cca4c939f119df2c31f6228'
rebuilt=baseline
for h in hooks:
    marker=f"    // 0x{h['before_vram']:08X}:"
    rebuilt=rebuilt.replace(marker,'    '+h['text']+'\n'+marker,1)
assert rebuilt==body
output.write_text('#include "recomp.h"\n#include "funcs.h"\n#include "checked_memory.h"\n'+
                  baseline.replace('Draw_WaterEffects(', 'baseline_Draw_WaterEffects(')+'\n'+body+'\n')
