"""Replay the complete native seven-vertex seabed producer with its real hook."""
from pathlib import Path
import hashlib
import sys
import tomllib

root, output = map(Path, sys.argv[1:3])
def extract(file, name):
    source = (root/'RecompiledFuncsPoint0'/file).read_text()
    start = source.index('RECOMP_FUNC void '+name+'(')
    return source[start:source.index('\n;}', start)+3]

body = extract('funcs_1.c', 'func_8004C998')
hooks = [h for h in tomllib.loads((root/'config/us.rev1.toml').read_text())['patches']['hook']
         if h['func']=='func_8004C998']
assert {h['before_vram'] for h in hooks}=={0x8004C998,0x8004CC48}
baseline = body
for h in hooks:
    line = '    '+h['text']+'\n'
    marker = f"    // 0x{h['before_vram']:08X}:"
    assert baseline.count(line+marker)==1
    baseline = baseline.replace(line+marker, marker, 1)
assert hashlib.sha256(baseline.encode()).hexdigest()=='8de09f55de5e46818c51b96f99572c3cf060354e338f44289225c2e26fcc54db'
regenerated = baseline
for h in hooks:
    marker = f"    // 0x{h['before_vram']:08X}:"
    regenerated = regenerated.replace(marker,'    '+h['text']+'\n'+marker,1)
assert regenerated==body
adapter_baseline = body
distance_hook = next(h for h in hooks if h['before_vram']==0x8004CC48)
adapter_baseline = adapter_baseline.replace('    '+distance_hook['text']+'\n', '', 1)
world = (root/'RecompiledFuncsPoint0/funcs_6.c').read_text()
start = world.index('L_80090420:')
packet = world[start:world.index('L_80090558:', start)]
assert hashlib.sha256(packet.encode()).hexdigest()=='af6b690035afee4951eb148bc392a385901b99fab89df965d22e72c84ec361cb'
output.write_text('\n'.join([
    '#include "recomp.h"\n#include "funcs.h"\n#include "checked_memory.h"\n'
    'void wr64_forensic_capture_sky(uint8_t*,uint32_t,uint32_t,uint32_t);\n',
    body, baseline.replace('void func_8004C998(', 'void baseline_unadapted_bottom_vertex('),
    adapter_baseline.replace('void func_8004C998(', 'void baseline_bottom_vertex('),
    'RECOMP_FUNC void native_bottom_packet(uint8_t* rdram,recomp_context* ctx) {\n'
    'uint64_t hi=0,lo=0,result=0; int c1cs=0;\n'+packet+'\nL_80090558: return;\n}\n',
    extract('funcs_0.c','SysUtils_Round')]))
