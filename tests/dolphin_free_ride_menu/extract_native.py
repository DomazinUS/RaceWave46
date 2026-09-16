"""Run the actual native menu and prove only the declared hooks were added."""
from pathlib import Path
import hashlib, json, re, sys, tomllib
root, output = map(Path, sys.argv[1:3])
source = (root/'RecompiledFuncsPoint0/funcs_21.c').read_text(encoding='utf-8')
original_hashes = {'func_i4_802C58F8': '249dad0d970819e20736957d8a2faacb6b006778044cd3613ba6e12dba6db37e', 'func_i4_802C6C2C': '0139e030288e7836981bb57c1dc35ea48d720abce9045900b4835fa12e9541bf', 'func_i4_802C7474': 'a48604c7a845ab4fc53b074f3f325d1b47d0d4a2ed8e0e544527c23cee3df2dc'}
names = ['func_i4_802C58F8', 'func_i4_802C6C2C', 'func_i4_802C7474']
hooks = tomllib.loads((root/'config/us.rev1.toml').read_text(encoding='utf-8'))['patches']['hook']
def body(text, name):
    start = text.index('RECOMP_FUNC void '+name+'(')
    return text[start:text.index('\n;}', start)+3]
parts = ['#include "recomp.h"\n#include "funcs.h"\n#include "checked_memory.h"']
parts += ['void baseline_'+name+'(uint8_t*, recomp_context*);' for name in names]
for name in names:
    current = body(source, name)
    original = current
    for h in hooks:
        if h['func'] == name and 'wr64_free_ride_' in h['text']:
            line = '    '+h['text']+'\n'
            assert original.count(line) == 1
            original = original.replace(line, '', 1)
    assert hashlib.sha256(original.encode()).hexdigest() == original_hashes[name], name+': unrelated native edit'
    for prefix, version in [('', current), ('baseline_', original)]:
        for n in names: version = re.sub(r'\b'+n+r'\b', prefix+n, version)
        parts.append(version)
calls = set(re.findall(r'\b(func_\w+)\(rdram, ctx\)', '\n'.join(parts)))
for name in sorted(calls - set(names)):
    if not name.startswith('baseline_'):
        parts.append('void '+name+'(uint8_t* rdram, recomp_context* ctx) { (void)rdram; (void)ctx; }')
parts.append('void SysUtils_Rand(uint8_t* rdram, recomp_context* ctx) { (void)rdram; ctx->r2 = 0; }')
parts.append('void FadeTransition_SetProps(uint8_t* rdram, recomp_context* ctx) { (void)rdram; (void)ctx; }')
output.write_text('\n'.join(parts), encoding='utf-8')
