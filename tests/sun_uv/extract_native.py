"""Compile existing native producers into the test build; distribute no ROM data."""
from pathlib import Path
import re
import subprocess
import sys
import tomllib

root, output = map(Path, sys.argv[1:3])
sys.path.insert(0, str(root / 'tests/dolphin_sun_native_exit'))
from hook_contract import trial_hooks, DEFAULT_OFF_STUBS
baseline_commit = "60dca8199cf88a63ae430dc08a3578e358d5ee31"
relative = "RecompiledFuncsPoint0/funcs_5.c"
name = "func_8008D94C"


def from_baseline(path):
    return subprocess.check_output(
        ["git", "-C", str(root), "show", baseline_commit + ":" + path], text=True
    )


def extract(text):
    match = re.search(r"void " + name + r"\(uint8_t\* rdram, recomp_context\* ctx\) \{", text)
    assert match, name
    return text[match.start():text.index("\n;}", match.end()) + 3]


baseline = extract(from_baseline(relative))
current = extract((root / relative).read_text())
old_hooks = tomllib.loads(from_baseline("config/us.rev1.toml"))["patches"]["hook"]
hooks = tomllib.loads((root / "config/us.rev1.toml").read_text())["patches"]["hook"]
old_hooks = [hook for hook in old_hooks if hook["func"] == name]
hooks = [hook for hook in hooks if hook["func"] == name]
assert all(hook in hooks for hook in old_hooks), "Existing sun producer hooks changed"
added_hooks = [hook for hook in hooks if hook not in old_hooks]
trial = trial_hooks(root)
horizontal = [hook for hook in added_hooks if hook not in trial]
assert {hook["before_vram"] for hook in horizontal} == {0x8008DCD4, 0x8008DF70}
assert len(horizontal) == 2 and len(added_hooks) == 8, "Expected horizontal fixes plus exact opt-in trial hooks"
regenerated = baseline
for hook in added_hooks:
    marker = f"    // 0x{hook['before_vram']:08X}:"
    assert regenerated.count(marker) == 1, marker
    regenerated = regenerated.replace(marker, "    " + hook["text"] + "\n" + marker, 1)

output.write_text("\n".join([
    '#include "recomp.h"',
    DEFAULT_OFF_STUBS,
    baseline.replace(name, "baseline_" + name, 1),
    current,
    regenerated.replace(name, "regenerated_" + name, 1),
]))
