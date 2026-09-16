"""Execute current native caller/projector with two read-only observations.

No arithmetic, native branch, or accepted hook is removed or rewritten.
Host camera selection/widescreen helpers are supplied by the C++ fixture.
"""
from pathlib import Path
import hashlib
import json
import re
import sys

root, output = map(Path, sys.argv[1:3])
source = (root / 'RecompiledFuncsPoint0/funcs_5.c').read_text(encoding='utf-8')

def extract(name):
    match = re.search(r'void ' + name + r'\(uint8_t\* rdram, recomp_context\* ctx\) \{', source)
    if not match:
        raise RuntimeError('Missing native function ' + name)
    return source[match.start():source.index('\n;}', match.end()) + 3]

original = {name: extract(name) for name in ('func_800895A0', 'func_8008962C', 'func_80089E24')}
projector = original['func_8008962C']
observations = {
    '    // 0x8008962C:': '    wr64_test_native_enter(rdram, ctx);\n',
    '    // 0x8008981C:': '    wr64_test_native_point(rdram, ctx);\n',
}
for marker, observer in observations.items():
    if projector.count(marker) != 1:
        raise RuntimeError('Unexpected observer anchor ' + marker)
    projector = projector.replace(marker, observer + marker, 1)
restored = projector
for observer in observations.values():
    restored = restored.replace(observer, '', 1)
if restored != original['func_8008962C']:
    raise RuntimeError('Native function changed outside observations')
output.write_text('\n'.join([
    '#include "recomp.h"',
    'void SysUtils_MtxToMtxF(uint8_t*, recomp_context*);',
    'void wr64_test_native_enter(uint8_t*, recomp_context*);',
    'void wr64_test_native_point(uint8_t*, recomp_context*);',
    original['func_800895A0'], projector, original['func_80089E24'],
]), encoding='utf-8')
output.with_suffix('.json').write_text(json.dumps({
    'source': 'RecompiledFuncsPoint0/funcs_5.c',
    'sha256': {name: hashlib.sha256(text.encode()).hexdigest() for name, text in original.items()},
    'observer_sites': ['8008962C: entry arguments', '8008981C: formed native world point before matrix multiply'],
    'all_native_arithmetic_branches_and_existing_hooks_retained': True,
}, indent=2) + '\n', encoding='utf-8')
