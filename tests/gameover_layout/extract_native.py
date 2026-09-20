"""Exercise the existing Game Over caller without loading any ROM assets."""
from pathlib import Path
import re
import subprocess
import sys
import tomllib

root, output = map(Path, sys.argv[1:3])
baseline_commit = "61f81ae19053452b8738224ed3a6321a84ceec71"


def baseline_file(path):
    return subprocess.check_output(
        ["git", "-C", str(root), "show", baseline_commit + ":" + path], text=True
    )


def extract(text, name):
    match = re.search(r"(?:RECOMP_FUNC )?void " + name + r"\(uint8_t\* rdram, recomp_context\* ctx\) \{", text)
    assert match, name
    return text[match.start():text.index("\n;}", match.end()) + 3]


relative = "RecompiledFuncsPoint0/funcs_22.c"
name = "func_i5_802C7698"
old_text = baseline_file(relative)
new_text = (root / relative).read_text()
baseline = extract(old_text, name)
current = extract(new_text, name)
old_hooks = tomllib.loads(baseline_file("config/us.rev1.toml"))["patches"]["hook"]
new_hooks = tomllib.loads((root / "config/us.rev1.toml").read_text())["patches"]["hook"]
prior = [hook for hook in old_hooks if hook["func"] == name]
hooks = [hook for hook in new_hooks if hook["func"] == name]
assert all(hook in hooks for hook in prior), "Existing Game Over hooks changed"
added = [hook for hook in hooks if hook not in prior]
expected_sites = {0x802C76D8, 0x802C7700, 0x802C778C, 0x802C77B4, 0x802C77DC, 0x802C7804}
assert len(added) == 6 and {hook["before_vram"] for hook in added} == expected_sites, \
    "Expected six Game Over draw-argument hooks"
regenerated = baseline
for hook in added:
    marker = f"    // 0x{hook['before_vram']:08X}:"
    assert regenerated.count(marker) == 1, marker
    regenerated = regenerated.replace(marker, "    " + hook["text"] + "\n" + marker, 1)

# The correction belongs to the layout caller. Its animation state machine,
# frame, label, number and font-state producers must retain their existing code.
for path, function in (
    (relative, "func_i5_802C781C"),
    ("RecompiledFuncsPoint0/funcs_6.c", "func_80094338"),
    ("RecompiledFuncsPoint0/funcs_17.c", "func_801E3EE0"),
    ("RecompiledFuncsPoint0/funcs_18.c", "func_801E946C"),
    ("RecompiledFuncsPoint0/funcs_18.c", "func_801EB00C"),
):
    assert extract((root / path).read_text(), function) == extract(baseline_file(path), function), \
        function + ": Game Over centering unexpectedly changed an existing producer or animation"

output.write_text("\n".join((
    '#include "recomp.h"\n#include "funcs.h"',
    baseline.replace(name, "baseline_" + name, 1),
    current,
    regenerated.replace(name, "regenerated_" + name, 1),
)))
