"""Extract the real ending and every 2D draw producer, without copying assets."""
from pathlib import Path
import hashlib
import json
import re
import sys
import tomllib

root, out = map(Path, sys.argv[1:3])
out.mkdir(parents=True, exist_ok=True)
functions = {}
for path in (root / 'RecompiledFuncsPoint0').glob('funcs_*.c'):
    for match in re.finditer(r'(?:RECOMP_FUNC )?void (\w+)\(uint8_t\* rdram, recomp_context\* ctx\) \{.*?\n;\}', path.read_text(encoding='utf-8'), re.S):
        functions[match[1]] = (path, match[0])

# Actual 2D producers and animation are never stubs. Camera matrices and the
# four rider miniature meshes are not rasterized by this CPU HUD fixture.
external = {'func_800481E0', 'func_80048A88', 'func_800484C8',
            'SysUtils_MtxToMtxF', 'SysUtils_MatrixAffineMultiply',
            'SysUtils_MtxFToMtx', 'func_800C489C', 'func_800CA210',
            'osVirtualToPhysical_recomp', 'func_801E4FE8'}
todo = ['func_i15_802C602C', 'func_i15_802C5800', 'func_i15_802C5CE8', 'func_i15_802C5EE4']
selected = {}
while todo:
    name = todo.pop()
    if name in selected or name in external:
        continue
    path, body = functions[name]
    selected[name] = (path, body)
    todo += re.findall(r'\n    (\w+)\(rdram, ctx\);', body)

parts = ['#include "recomp.h"\n#include "funcs.h"\nextern void ending_test_row_begin(uint8_t*,recomp_context*);\nextern void ending_test_row_end(uint8_t*,recomp_context*);']
provenance = {}
for name, (path, body) in selected.items():
    provenance[name] = {'path':str(path.relative_to(root)), 'sha256':hashlib.sha256(body.encode()).hexdigest()}
    if name == 'func_i15_802C5800':
        original = '\n'.join(line for line in body.split('\n') if 'wr64_ending_panel_retire' not in line)
        parts.append(original.replace('void ' + name + '(', 'void ending_test_baseline_update(', 1))
    if name == 'func_i15_802C602C':
        # A second copy of exactly the same native producer, removing only the
        # new ownership callbacks, proves that metadata cannot alter RAM or ABI.
        baseline = '\n'.join(line for line in body.split('\n')
                             if 'wr64EndingHud' not in line and 'wr64_ending_hud' not in line)
        parts.append(baseline.replace('void ' + name + '(', 'void ending_test_baseline_draw(', 1))
        body = body.replace('    // 0x802C6068:', '    ending_test_row_begin(rdram, ctx);\n    // 0x802C6068:', 1)
        body = body.replace('    // 0x802C6BDC:', '    ending_test_row_end(rdram, ctx);\n    // 0x802C6BDC:', 1)
    parts.append(body)
config = tomllib.loads((root/'config/us.rev1.toml').read_text(encoding='utf-8'))
def hook_entries(value):
    if isinstance(value, dict):
        if 'func' in value and 'before_vram' in value: yield value
        for item in value.values(): yield from hook_entries(item)
    elif isinstance(value, list):
        for item in value: yield from hook_entries(item)
hooks = [h for h in hook_entries(config) if h.get('func') == 'func_i15_802C5800' and 'wr64_ending_panel_retire' in h.get('text', '')]
assert len(hooks) == 1 and hooks[0]['before_vram'] == 0x802C5B20
assert selected['func_i15_802C5800'][1].count(hooks[0]['text']) == 1
assert hooks[0]['text'] + '\n    // 0x802C5B20:' in selected['func_i15_802C5800'][1]
(out / 'native_ending.c').write_text('\n'.join(parts), encoding='utf-8')
(out / 'native-provenance.json').write_text(json.dumps(provenance, indent=2), encoding='utf-8')
source = (root/'src/wr64_render_provenance.cpp').read_text(encoding='utf-8')
a = source.index('namespace {\nstruct PendingTask')
(out/'hud_bridge.cpp').write_text('#include "wr64_diagnostic_policy.h"\n#include "wr64_render_provenance.h"\n#include "common/rt64_wr64_hud_motion.h"\n#include "common/rt64_wr64_wave_distance.h"\n#include "common/rt64_wr64_dolphin_sun_sprite.h"\n#include <algorithm>\n#include <atomic>\n#include <deque>\n#include <cstdio>\n'+source[a:], encoding='utf-8')
print('Complete native producers:', ', '.join(sorted(selected)))
print('External fixture services:', ', '.join(sorted(external)))
