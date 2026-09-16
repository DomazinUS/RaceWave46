"""Replay the existing Championship map builder without distributing assets."""
from pathlib import Path
import re
import subprocess
import sys
import tomllib

root, output = map(Path, sys.argv[1:3])
baseline_commit = "d94caa90f0da4fccd8b901a34c3b731ebf61cf57"


def old_file(path):
    return subprocess.check_output(["git", "-C", str(root), "show", baseline_commit + ":" + path], text=True)


def extract(text, name):
    match = re.search(r"(?:RECOMP_FUNC )?void " + name + r"\(uint8_t\* rdram, recomp_context\* ctx\) \{", text)
    assert match, name
    return text[match.start():text.index("\n;}", match.end()) + 3]


old_config = tomllib.loads(old_file("config/us.rev1.toml"))["patches"]
new_config = tomllib.loads((root / "config/us.rev1.toml").read_text())["patches"]
name = "func_i3_802C6344"
path = "RecompiledFuncsPoint0/funcs_21.c"
baseline = extract(old_file(path), name)
current = extract((root / path).read_text(), name)
prior = [hook for hook in old_config["hook"] if hook["func"] == name]
hooks = [hook for hook in new_config["hook"] if hook["func"] == name]
assert all(hook in hooks for hook in prior), "Existing Championship hooks changed"
added = [hook for hook in hooks if hook not in prior]
assert len(added) == 2 and {hook["before_vram"] for hook in added} == {0x802C6344, 0x802C6E88}
assert all("wr64_championship_preview_" in hook["text"] for hook in added)
assert [item for item in new_config["instruction"] if item["func"] == name] == [
    item for item in old_config["instruction"] if item["func"] == name]
regenerated = baseline
for hook in added:
    marker = f"    // 0x{hook['before_vram']:08X}:"
    assert regenerated.count(marker) == 1
    regenerated = regenerated.replace(marker, "    " + hook["text"] + "\n" + marker, 1)
assert current == regenerated, "Checked-in Championship producer differs from durable recipe"
parts = ['#include "recomp.h"\n#include "funcs.h"',
    baseline.replace(name, "baseline_" + name, 1), current,
    regenerated.replace(name, "regenerated_" + name, 1)]

# Keep the original main/intro dispatch, fade/camera movement, map projection,
# generic rectangle producer and all record formatting unchanged. The complete
# target builder above still runs its own native fade transitions.
for file, native, replay in (
    ("funcs_21.c", "func_i3_802C5800", None),
    ("funcs_21.c", "func_i3_802C5AE8", None),
    ("funcs_21.c", "func_i3_802C5AF0", None),
    ("funcs_21.c", "func_i3_802C5B40", None),
    ("funcs_21.c", "func_i3_802C5D54", None),
    ("funcs_21.c", "func_i3_802C6E9C", None),
    ("funcs_2.c", "func_80069798", None),
    ("funcs_18.c", "func_801E7C58", "native_rectangle"),
    ("funcs_18.c", "func_801EB00C", "native_number"),
    ("funcs_18.c", "func_801E8B24", "native_time"),
    ("funcs_18.c", "func_801E9858", "native_string"),
    ("funcs_18.c", "func_801E9B04", "func_801E9B04"),
):
    path = "RecompiledFuncsPoint0/" + file
    original = extract(old_file(path), native)
    latest = extract((root / path).read_text(), native)
    assert latest == original, native + ": original intro/camera/record producer changed"
    if replay:
        body = latest.replace(native, replay, 1)
        if replay == "native_number":
            body = body.replace("func_801E9858(rdram, ctx)", "native_string(rdram, ctx)")
            body = "void native_string(uint8_t*, recomp_context*);\n" + body
        parts.append(body)
output.write_text("\n".join(parts))
