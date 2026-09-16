"""Build the existing shadow/matrix/water-height routines for a CPU fixture."""
from pathlib import Path
import hashlib
import json
import sys
import tomllib

root, output = map(Path, sys.argv[1:3])
names = {
    'func_80069594': 'funcs_2.c', 'func_800694B8': 'funcs_2.c',
    'func_8006931C': 'funcs_2.c', 'func_8004D30C': 'funcs_1.c',
    'SysUtils_MtxFToMtx': 'funcs_0.c', '_nsqrtf': 'funcs_15.c',
}
hook = '{ extern uint32_t wr64_sunny_actor_shadows(uint8_t*, recomp_context*); if (wr64_sunny_actor_shadows(rdram, ctx)) return; }'
hooks = tomllib.loads((root/'config/us.rev1.toml').read_text())['patches']['hook']
assert any(h['func'] == 'func_80069594' and h['before_vram'] == 0x80069594 and h['text'] == hook for h in hooks)
parts = ['#include "recomp.h"\n#include "funcs.h"\n#include "../sunny_two_player_detail/checked_memory.h"\n']
manifest = {}
for name, file in names.items():
    source = (root/'RecompiledFuncsPoint0'/file).read_text()
    start = source.index('RECOMP_FUNC void '+name+'(')
    body = source[start:source.index('\n;}', start)+3]
    if name == 'func_80069594':
        assert body.count('    '+hook+'\n') == 1
        original = body.replace('    '+hook+'\n', '')
        assert body == original.replace('    // 0x80069594:', '    '+hook+'\n    // 0x80069594:', 1)
        parts.append(original.replace('void func_80069594(', 'void baseline_func_80069594(', 1))
        manifest['baseline_func_80069594'] = hashlib.sha256(original.encode()).hexdigest()
    parts.append(body)
    manifest[name] = hashlib.sha256(body.encode()).hexdigest()
output.write_text('\n'.join(parts))
output.with_suffix('.manifest.json').write_text(json.dumps(manifest, indent=2)+'\n')
