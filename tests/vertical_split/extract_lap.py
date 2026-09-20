"""Replay unchanged USA lap announcement, formatter and vertex-font producers."""
from pathlib import Path
import re
import subprocess
import sys
import tomllib

root, output = map(Path, sys.argv[1:3])
baseline = "a30ad50e8fac05fbf0a6fd58a2d95f4d911ce16e"


def extract(text, name):
    match = re.search(r"RECOMP_FUNC void " + name + r"\(uint8_t\* rdram, recomp_context\* ctx\) \{", text)
    assert match, name
    return text[match.start():text.index("\n;}", match.end()) + 3]


parts = ['#include "recomp.h"\n#include "funcs.h"']
old_hooks = tomllib.loads(subprocess.check_output(
    ["git", "show", f"{baseline}:config/us.rev1.toml"], cwd=root, text=True))["patches"]["hook"]
new_hooks = tomllib.loads((root / "config/us.rev1.toml").read_text())["patches"]["hook"]
for relative, names in (
    ("RecompiledFuncsPoint0/funcs_20.c", ["func_801FAEB8"]),
    ("RecompiledFuncsPoint0/funcs_18.c", ["func_801E93B4", "func_801E946C", "func_801E9858",
                                        "func_801E9B04", "func_801E80B0", "func_801E8800"]),
):
    current = (root / relative).read_text()
    original = subprocess.check_output(["git", "show", f"{baseline}:{relative}"], cwd=root, text=True)
    for name in names:
        function = extract(current, name)
        prior = extract(original, name)
        if name == "func_801FAEB8":
            hooks = [hook for hook in new_hooks if hook["func"] == name and hook not in old_hooks]
            assert len(hooks) == 4 and {hook["before_vram"] for hook in hooks} == {
                0x801FB31C, 0x801FB3F4, 0x801FB35C, 0x801FB418}, "Wrong native lap scope boundaries"
            regenerated = prior
            for hook in hooks:
                marker = f"    // 0x{hook['before_vram']:08X}:"
                assert regenerated.count(marker) == 1
                regenerated = regenerated.replace(marker, "    " + hook["text"] + "\n" + marker)
            assert function == regenerated, "Generated lap function differs from its durable hooks"
            parts.append(prior.replace(name, "baseline_" + name, 1))
        else:
            assert function == prior, name + ": native logic changed during presentation-only fix"
        if name == "func_801E80B0":
            function = function.replace(name, "native_emit_font", 1)
        parts.append(function)
output.write_text("\n".join(parts))
