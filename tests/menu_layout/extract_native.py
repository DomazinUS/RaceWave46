from pathlib import Path
import re
import subprocess
import sys
import tomllib

root, output = map(Path, sys.argv[1:3])
# Immutable pre-fix source: committing this repair must never make the
# byte-equivalence comparison silently compare the repaired code to itself.
baseline_commit = 'ce9c7363975c43dbdc845279439aec89be7a239a'
functions = [('funcs_6.c', 'func_80094338'), ('funcs_18.c', 'func_801E7FD8'), ('funcs_18.c', 'func_801E80B0'), ('funcs_17.c', 'func_801E3EE0')]
parts = ['#include "recomp.h"\n#include "funcs.h"\n']
hooks = tomllib.loads((root / 'config/us.rev1.toml').read_text())['patches']['hook']
for file, name in functions:
    relative = 'RecompiledFuncsPoint0/' + file
    for baseline in (False, True):
        text = (subprocess.check_output(['git', '-C', str(root), 'show', baseline_commit + ':' + relative], text=True)
                if baseline else (root / relative).read_text())
        match = re.search(r'void ' + name + r'\(uint8_t\* rdram, recomp_context\* ctx\) \{', text)
        assert match, name
        end = text.index('\n;}', match.end()) + 3
        body = text[match.start():end]
        if baseline:
            # Reapply the durable hooks to the immutable pre-fix producer.
            # This independently checks generated hand edits against the
            # regeneration recipe without requiring or copying a ROM asset.
            regenerated = body
            for hook in hooks:
                if hook['func'] != name:
                    continue
                marker = f"    // 0x{hook['before_vram']:08X}:"
                assert marker in regenerated, marker
                regenerated = regenerated.replace(marker, '    ' + hook['text'] + '\n' + marker, 1)
            parts.append(regenerated.replace(name, 'regenerated_' + name, 1))
            body = body.replace(name, 'baseline_' + name, 1)
        parts.append(body)
output.write_text('\n'.join(parts))
