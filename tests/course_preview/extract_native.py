"""Replay the native Course Select producers without loading a ROM asset."""
from pathlib import Path
import re
import subprocess
import sys
import tomllib

root, output = map(Path, sys.argv[1:3])
baseline_commit = "b60925a12c61b080465fac6cc83f41c4f8b54688"


def baseline_file(path):
    return subprocess.check_output(
        ["git", "-C", str(root), "show", baseline_commit + ":" + path], text=True)


def extract(text, name):
    match = re.search(r"(?:RECOMP_FUNC )?void " + name + r"\(uint8_t\* rdram, recomp_context\* ctx\) \{", text)
    assert match, name
    return text[match.start():text.index("\n;}", match.end()) + 3]


old_config = tomllib.loads(baseline_file("config/us.rev1.toml"))["patches"]
new_config = tomllib.loads((root / "config/us.rev1.toml").read_text())["patches"]
old_hooks, new_hooks = old_config["hook"], new_config["hook"]
instructions = [item for item in new_config["instruction"] if item["func"] == "func_i4_802C5CDC"]
expected_instructions = {0x802C6208:0x24E70127, 0x802C62BC:0x24E7012B, 0x802C62DC:0x24E7012B,
                         0x802C6330:0x24E7012B, 0x802C6374:0x24E7012B}
assert len(instructions) == 5 and {item["vram"]:item["value"] for item in instructions} == expected_instructions
names = ("func_i4_802C6778", "func_i4_802C5CDC")
parts = ['#include "recomp.h"\n#include "funcs.h"']
relative = "RecompiledFuncsPoint0/funcs_21.c"
old_text = baseline_file(relative)
new_text = (root / relative).read_text()
for name in names:
    baseline = extract(old_text, name)
    current = extract(new_text, name)
    prior = [hook for hook in old_hooks if hook["func"] == name]
    hooks = [hook for hook in new_hooks if hook["func"] == name]
    assert all(hook in hooks for hook in prior), name + ": existing hooks changed"
    added = [hook for hook in hooks if hook not in prior]
    assert added and all("wr64_course_preview_" in hook["text"] for hook in added), name
    expected_sites = ({0x802C6778, 0x802C69BC} if name == "func_i4_802C6778" else
        {0x802C5CDC,0x802C5DD8,0x802C5E40,0x802C5E64,0x802C5E8C,0x802C5EB0,0x802C5ED4,
         0x802C5EF8,0x802C5F90,0x802C5FA4,0x802C61B8,0x802C622C,0x802C624C,0x802C6528,
         0x802C65DC,0x802C672C,0x802C6204,0x802C62B8,0x802C62D8,0x802C632C,0x802C6370,
         0x802C60DC,0x802C6758})
    assert len(added) == len(expected_sites) and {hook["before_vram"] for hook in added} == expected_sites
    regenerated = baseline
    if name == "func_i4_802C5CDC":
        # These delay slots are deliberately made additive. The hook computes
        # only the scoped offset before JAL; the native delay slot still owns
        # its original caption coordinate on both emitted copies of the slot.
        for address, immediate in ((0x802C6208, 0x127), (0x802C62BC, 0x12B),
                                   (0x802C62DC, 0x12B), (0x802C6330, 0x12B), (0x802C6374, 0x12B)):
            pattern = (rf"(    // 0x{address:08X}: addiu       \$a3, )\$zero"
                       rf"(, 0x{immediate:X}\n    ctx->r7 = ADD32\()0(, 0X{immediate:X}\);)")
            regenerated, count = re.subn(pattern, r"\1$a3\2ctx->r7\3", regenerated)
            assert count == 2, f"missing native delay copies {address:08X}"
    for hook in added:
        marker = f"    // 0x{hook['before_vram']:08X}:"
        assert regenerated.count(marker) == 1, marker
        regenerated = regenerated.replace(marker, "    " + hook["text"] + "\n" + marker, 1)
    # This also rejects accidental edits to native geometry/animation logic.
    assert current == regenerated, name + ": checked-in native source differs from its durable hooks"
    for prefix, body in (("baseline_", baseline), ("", current), ("regenerated_", regenerated)):
        for nested in names:
            body = body.replace(nested, prefix + nested)
        parts.append(body)

# The menu animation, camera setup, score formatting, glyph widths and the
# unchanged difficulty frame remain the original native implementations.
for file, name, replay_name in (
    ("funcs_21.c", "func_i4_802C5B78", None),
    ("funcs_21.c", "func_i4_802C6BAC", None),
    ("funcs_21.c", "func_i4_802C6ED0", "func_i4_802C6ED0"),
    ("funcs_21.c", "func_i4_802C5800", None),
    ("funcs_21.c", "func_i4_802C58F8", None),
    ("funcs_2.c", "func_80069740", None),
    ("funcs_2.c", "func_8006977C", None),
    ("funcs_2.c", "func_80069798", None),
    ("funcs_21.c", "func_i4_802C69C4", "native_difficulty_frame"),
    ("funcs_6.c", "func_80094200", "native_score"),
    ("funcs_18.c", "func_801E8B24", "native_time"),
    ("funcs_18.c", "func_801E9858", "native_string"),
    ("funcs_18.c", "func_801E9B04", "func_801E9B04"),
):
    path = "RecompiledFuncsPoint0/" + file
    old = extract(baseline_file(path), name)
    new = extract((root / path).read_text(), name)
    assert old == new, name + ": native animation, camera or text producer changed"
    if replay_name:
        body = new.replace(name, replay_name, 1)
        if replay_name == "native_score":
            body = body.replace("func_801E9858(rdram, ctx)", "native_string(rdram, ctx)")
            body = "void native_string(uint8_t*, recomp_context*);\n" + body
        parts.append(body)
output.write_text("\n".join(parts))
