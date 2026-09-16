"""Run the actual camera/matrix builders and an independently unhooked baseline."""
from pathlib import Path
import hashlib
import re
import sys
import tomllib

root, output = map(Path, sys.argv[1:3])
def extract(file, name):
    text = (root / 'RecompiledFuncsPoint0' / file).read_text()
    start = text.index('void ' + name + '(')
    return text[start:text.index('\n;}', start) + 3]

hooks = tomllib.loads((root/'config/us.rev1.toml').read_text())['patches']['hook']
hooks = [h for h in hooks if 'wr64_camera_fov_lens' in h['text']]
assert len(hooks) == 1 and hooks[0]['func'] == 'func_801E11B4'
assert hooks[0]['before_vram'] == 0x801E11D4
current = extract('funcs_17.c', 'func_801E11B4')
hookline = '    '+hooks[0]['text']+'\n'
assert current.count(hookline+'    // 0x801E11D4:') == 1
baseline = current.replace(hookline, '', 1)
assert hashlib.sha256(baseline.encode()).hexdigest() == '204659392dc8a4561e21d7a502b049677ae4aed7041549a4fed2f00eec3dc57c', 'native camera body changed'
assert baseline.index('ctx->r6 = MEM_W(ctx->r16, 0X88);') < baseline.index('// 0x801E11D4:')
assert current.replace(hookline, '', 1).count('wr64_camera_fov') == 0
parts = ['#include "recomp.h"\n#include "funcs.h"\n#include "checked_memory.h"', current,
         baseline.replace('func_801E11B4(', 'baseline_camera(', 1)]
digests = {
    'func_800481E0':'b9a10b422b3177db404d2a7592755cf6d79caed89b381f3d6c6b485fa83f6872',
    'func_800484C8':'4ac4d534289151f976153a77c3be2e8ef233dc12794b22cd215a9804dae9e6ce',
    'SysUtils_Round':'d7bdae4d7d613037695552c0c5c7ebd8a1e66dbfe21b52e21aa43c1973f2148a',
    'SysUtils_MtxToMtxF':'4e1929c84c89a4bc3a8a8f6daddcf9ae003dafb3a125de7a9456f86db3ef4baa',
}
for name, digest in digests.items():
    body = extract('funcs_0.c', name)
    assert hashlib.sha256(body.encode()).hexdigest() == digest, name+' native math changed'
    parts.append(body)
parts.append(extract('funcs_0.c', 'SysUtils_MtxFToMtx'))
# Guard the evidence for the deliberately narrow chase-camera scope: native
# type 3 initialization takes per-preset lens data, then changes to type 4.
init = extract('funcs_16.c', 'func_801DDAB8')
assert 'ctx->f4.u32l = MEM_W(ctx->r1, 0X3940);' in init
assert 'ctx->r15 = ADD32(0, 0X4);' in init
assert '// 0x801DDC8C: sw          $t7, 0x0($a3)' in init
copy = extract('funcs_17.c', 'func_801E0F8C')
assert 'ctx->f10.u32l = MEM_W(ctx->r5, 0X38);' in copy
assert 'MEM_W(0X88, ctx->r4) = ctx->f10.u32l;' in copy
output.write_text('\n'.join(parts))
