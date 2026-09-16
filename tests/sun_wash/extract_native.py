"""Compile existing native wash producers with synthetic state; no ROM is needed."""
from pathlib import Path
import re
import subprocess
import sys
import tomllib

root, output = map(Path, sys.argv[1:3])
baseline_commit = "bcaa4069427bac7fce8d26e5c7d29abbacb5401e"


def baseline_file(path):
    return subprocess.check_output(
        ["git", "-C", str(root), "show", baseline_commit + ":" + path], text=True
    )


def extract(text, name):
    match = re.search(r"(?:RECOMP_FUNC )?void " + name + r"\(uint8_t\* rdram, recomp_context\* ctx\) \{", text)
    assert match, name
    return text[match.start():text.index("\n;}", match.end()) + 3]


old_hooks = tomllib.loads(baseline_file("config/us.rev1.toml"))["patches"]["hook"]
new_hooks = tomllib.loads((root / "config/us.rev1.toml").read_text())["patches"]["hook"]
pieces = ['#include "recomp.h"',
          'uint32_t wr64_two_player_sun_skip_shared_wash(uint8_t* rdram) { return 0; }']
for relative, name in (("RecompiledFuncsPoint0/funcs_5.c", "func_8008BD2C"),
                       ("RecompiledFuncsPoint0/funcs_1.c", "func_80051538")):
    baseline = extract(baseline_file(relative), name)
    current = extract((root / relative).read_text(), name)
    prior = [hook for hook in old_hooks if hook["func"] == name]
    hooks = [hook for hook in new_hooks if hook["func"] == name]
    assert all(hook in hooks for hook in prior), name + ": existing hooks changed"
    added = [hook for hook in hooks if hook not in prior]
    if name == "func_8008BD2C":
        assert len(added) == 3 and {hook["before_vram"] for hook in added} == {0x8008BF30, 0x8008BF4C, 0x8008BFBC}, \
            "Expected opt-in DP factor, visibility-comparison and pre-truncation alpha hooks"
    else:
        assert len(added)==1 and added[0]['before_vram']==0x80051538, "Expected scoped two-player wash entry only"
        assert current.replace('    '+added[0]['text']+'\n', '', 1)==baseline, "Screen-wash emitter unexpectedly changed"
    regenerated = baseline
    for hook in added:
        marker = f"    // 0x{hook['before_vram']:08X}:"
        assert regenerated.count(marker) == 1, marker
        regenerated = regenerated.replace(marker, "    " + hook["text"] + "\n" + marker, 1)
    pieces.extend((baseline.replace(name, "baseline_" + name, 1), current,
                   regenerated.replace(name, "regenerated_" + name, 1)))

output.write_text("\n".join(pieces))
