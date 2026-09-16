"""Actual native wash/flare producers, before effects and regenerated variants."""
from pathlib import Path
import hashlib
import json
import re
import subprocess
import sys
import tomllib

root, output = map(Path, sys.argv[1:3])
base = Path(__file__).resolve().parent
commit = 'bcaa4069427bac7fce8d26e5c7d29abbacb5401e'
def git_file(path):
    return subprocess.check_output(['git', '-C', str(root), 'show', commit+':'+path], text=True)
def extract(text, name):
    match = re.search(r'(?:RECOMP_FUNC )?void '+name+r'\(uint8_t\* rdram, recomp_context\* ctx\) \{', text)
    assert match, name
    return text[match.start():text.index('\n;}', match.end())+3]
def insert(original, old_hooks, new_hooks, name):
    prior = [h for h in old_hooks if h['func'] == name]
    hooks = [h for h in new_hooks if h['func'] == name]
    assert all(h in hooks for h in prior), 'Unexpected mutation of pre-existing native hook'
    result = original
    for h in hooks:
        if h in prior: continue
        marker = f"    // 0x{h['before_vram']:08X}:"
        assert result.count(marker) == 1, marker
        result = result.replace(marker, '    '+h['text']+'\n'+marker, 1)
    return result
def without_hook_comments(text):
    return re.sub(r' /\* WR64[^\n]*?\*/', '', text)
old = tomllib.loads(git_file('config/us.rev1.toml'))['patches']['hook']
prior = json.loads((base/'pre_effects_hooks.json').read_text())
current = tomllib.loads((root/'config/us.rev1.toml').read_text())['patches']['hook']
pieces = ['#include "recomp.h"', 'uint32_t wr64_two_player_sun_skip_shared_wash(uint8_t* ram) { return 0; }']
audit = []
for path, name in [('RecompiledFuncsPoint0/funcs_5.c','func_8008BD2C'), ('RecompiledFuncsPoint0/funcs_1.c','func_80051538')]:
    original = extract(git_file(path), name)
    before = insert(original, old, prior, name)
    regenerated = insert(original, old, current, name)
    actual = extract((root/path).read_text(), name)
    assert without_hook_comments(actual) == without_hook_comments(regenerated), name+': durable TOML differs from checked-in native source'
    if name == 'func_80051538':
        assert before == regenerated, 'Screen-wash packet producer changed'
    pieces.extend([before.replace(name, 'before_'+name, 1), actual,
        regenerated.replace(name, 'regenerated_'+name, 1)])
    audit.append({'function':name, 'actual_sha256':hashlib.sha256(actual.encode()).hexdigest(),
        'durable_hooks_equal_current_ignoring_marker_comments':True})
output.write_text('\n'.join(pieces))
(output.parent/'effects-extraction.json').write_text(json.dumps(audit,indent=2)+'\n')
