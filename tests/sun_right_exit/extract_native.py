"""Replay existing native functions without checking ROM data into the test suite."""
from pathlib import Path
import re
import subprocess
import sys
import tomllib

root, output = map(Path, sys.argv[1:3])
sys.path.insert(0, str(root / 'tests/dolphin_sun_native_exit'))
from hook_contract import without_trial_hooks, DEFAULT_OFF_STUBS
baseline_commit = "e0e228562e8efb00a655309ba6f6a419c53564e8"
relative = "RecompiledFuncsPoint0/funcs_5.c"
name = "func_8008962C"


def from_baseline(path):
    return subprocess.check_output(
        ["git", "-C", str(root), "show", baseline_commit + ":" + path], text=True
    )


def extract(text, function):
    match = re.search(r"void " + function + r"\(uint8_t\* rdram, recomp_context\* ctx\) \{", text)
    assert match, function
    return text[match.start():text.index("\n;}", match.end()) + 3]


baseline_source = from_baseline(relative)
current_source = (root / relative).read_text()
baseline = extract(baseline_source, name)
current = extract(current_source, name)
old_hooks = tomllib.loads(from_baseline("config/us.rev1.toml"))["patches"]["hook"]
hooks = tomllib.loads((root / "config/us.rev1.toml").read_text())["patches"]["hook"]
old_hooks = [hook for hook in old_hooks if hook["func"] == name]
hooks = [hook for hook in hooks if hook["func"] == name]
assert all(hook in hooks for hook in old_hooks), "Existing sun projection hooks changed"
added_hooks = [hook for hook in hooks if hook not in old_hooks]
assert {hook["before_vram"] for hook in added_hooks} == {0x800896F0, 0x80089B28, 0x80089648, 0x80089758}
assert len(added_hooks) == 4, "Expected right-exit and scoped 2P camera hooks"
regenerated = baseline
for hook in added_hooks:
    marker = f"    // 0x{hook['before_vram']:08X}:"
    assert regenerated.count(marker) == 1, marker
    regenerated = regenerated.replace(marker, "    " + hook["text"] + "\n" + marker, 1)

# Test-only control: let every positive-facing sun reach the ORIGINAL native
# projection. It supplies an independent expected record for the cases the
# production gate elects to keep; no projection arithmetic is rewritten.
angular_comparison = "c1cs = ctx->f10.fl < ctx->f8.fl;"
assert baseline.count(angular_comparison) == 1
projection_control = baseline.replace(angular_comparison, "c1cs = ctx->f10.fl <= 0.0f;", 1)
for helper in ("func_800895A0", "func_8008D94C"):
    actual = extract(current_source, helper)
    if helper == "func_8008D94C":
        actual = without_trial_hooks(root, actual)
    assert actual == extract(baseline_source, helper), helper + " unexpectedly changed"

# Dolphin Park's validated vertical lifecycle is independent of the widened
# horizontal visibility. Pin those production rules to their pre-change source.
rt64 = root / "lib/rt64"
rt64_baseline = "a38d8c17ca057d43d3be31403b137325fda9da16"
protected_regions = (
    ("src/common/rt64_wr64_celestial_identity.h", "    // ------------------------------------------- the parked sun (DP)",
        "    // Printed once, the first time a park transit"),
    ("src/hle/rt64_game_frame.cpp", "                // THE DP SUN PARK TRANSIT (DPSUN R1).",
        "                // Continuity on the rect centre"),
    ("src/render/rt64_framebuffer_renderer.cpp", "                if ((proj.type == Projection::Type::Rectangle) &&\n                    (!wr64CelRectOverridden)",
        "                wr64HudCensusRecord("),
)
for path, start, end in protected_regions:
    original = subprocess.check_output(["git", "-C", str(rt64), "show", rt64_baseline + ":" + path], text=True)
    present = (rt64 / path).read_text()
    def region(text):
        begin = text.index(start)
        return text[begin:text.index(end, begin)]
    assert region(present) == region(original), "Dolphin Park vertical sun rule changed: " + path

output.write_text("\n".join([
    '#include "recomp.h"',
    DEFAULT_OFF_STUBS,
    'uint32_t wr64_two_player_celestial_camera_address(uint8_t* rdram, uint32_t address) { return address; }',
    extract(current_source, "func_800895A0"),
    extract(current_source, "func_8008D94C"),
    baseline.replace(name, "baseline_" + name, 1),
    current,
    regenerated.replace(name, "regenerated_" + name, 1),
    projection_control.replace(name, "projection_control_" + name, 1),
]))
