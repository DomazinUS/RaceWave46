"""Extract actual native routines, proving the five durable asset hooks are the only edits."""
from pathlib import Path
import hashlib
import json
import re
import sys
import tomllib

root, output = map(Path, sys.argv[1:3])
expected = {
    'unk_game_load': ('funcs_6.c', '305cb46ef0c754c1e651316b2f2b97b7d382f67d00234a165687427a73d91a16', {0x80095174}),
    'func_80095A28': ('funcs_6.c', 'e94577ee69063807bf628e0de38697a7255280aaa4a545ce78bf1efd3f2e0759', {0x80095A28, 0x80095B90}),
    'func_80071E70': ('funcs_3.c', '7e85452525cdce0d3744df9d3fd265869420fa8c8f1deaf72c7340442f923936', {0x80071F20, 0x80072034}),
}
hooks = tomllib.loads((root/'config/us.rev1.toml').read_text())['patches']['hook']
parts = ['#include "recomp.h"\n#include "funcs.h"\n#include "checked_memory.h"\n'
         'void baseline_func_80095A28(uint8_t*, recomp_context*);\n'
         'void capture_native_asset(uint8_t*, recomp_context*);\n']
manifest = {}

def extract(path, name):
    text = path.read_text()
    start = text.index('RECOMP_FUNC void '+name+'(')
    return text[start:text.index('\n;}', start)+3]

for name, (file, digest, sites) in expected.items():
    body = extract(root/'RecompiledFuncsPoint0'/file, name)
    selected = [h for h in hooks if h['func'] == name and 'wr64_sunny_detail_' in h['text']]
    assert {h['before_vram'] for h in selected} == sites and len(selected) == len(sites), name
    baseline = body
    for hook in selected:
        line = '    '+hook['text']+'\n'
        assert baseline.count(line) == 1, 'Missing or duplicated hook '+name
        baseline = baseline.replace(line, '', 1)
    assert hashlib.sha256(baseline.encode()).hexdigest() == digest, name+': native baseline altered beyond approved hooks'
    regenerated = baseline
    for hook in selected:
        marker = f"    // 0x{hook['before_vram']:08X}:"
        assert regenerated.count(marker) == 1, marker
        regenerated = regenerated.replace(marker, '    '+hook['text']+'\n'+marker, 1)
    assert regenerated == body, name+': durable hook regeneration mismatch'
    manifest[name] = {'baseline_sha256': digest, 'current_sha256': hashlib.sha256(body.encode()).hexdigest(),
                      'hook_sites': [f'{v:08X}' for v in sorted(sites)]}
    for prefix, version in [('baseline_', baseline), ('', body)]:
        for native in expected:
            version = re.sub(r'\b'+native+r'\b', prefix+native, version)
        if name == 'unk_game_load':
            # Replay the unmodified selection/queue control flow, recording its
            # call boundary. Complete native DMA/decompression is tested below
            # with the selected shape+common and collision records themselves.
            version = version.replace(prefix+'func_80095A28(rdram, ctx);', 'capture_native_asset(rdram, ctx);')
        parts.append(version)

mio = extract(root/'RecompiledFuncsPoint0/funcs_10.c', 'Mio0_Decompress')
parts.append(mio)
manifest['Mio0_Decompress'] = {'current_sha256': hashlib.sha256(mio.encode()).hexdigest()}
output.write_text('\n'.join(parts))
output.with_suffix('.manifest.json').write_text(json.dumps(manifest, indent=2)+'\n')
