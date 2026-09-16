"""Extract native menu producers for an asset-free preview-layout regression."""
from pathlib import Path
import re
import subprocess
import sys
import tomllib

root, output = map(Path, sys.argv[1:3])
baseline_commit = "d10dfd1aef29fd43aa5df1b1dbb42df21626e665"


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
parts = ['#include "recomp.h"\n#include "funcs.h"']
for relative, name in (
    ("RecompiledFuncsPoint0/funcs_6.c", "func_8008FB74"),
    ("RecompiledFuncsPoint0/funcs_21.c", "func_i2_802C70EC"),
    ("RecompiledFuncsPoint0/funcs_21.c", "func_i2_802C5B4C"),
):
    baseline = extract(baseline_file(relative), name)
    current = extract((root / relative).read_text(), name)
    prior = [hook for hook in old_hooks if hook["func"] == name]
    hooks = [hook for hook in new_hooks if hook["func"] == name]
    assert all(hook in hooks for hook in prior), name + ": existing hooks changed"
    added = [hook for hook in hooks if hook not in prior]
    if name == "func_8008FB74":
        # Accepted two-player sky work landed after the original preview
        # oracle. Replay these exact durable hooks in all three copies; only
        # the camera hook executes before our deliberate world-render cutoff.
        # Keep an explicit allowlist so this cannot hide unrelated new edits.
        accepted_sky = {
            0x8008FBF4: "{ extern void wr64_sunny_sky_cloud_camera(uint8_t*, recomp_context*); wr64_sunny_sky_cloud_camera(rdram, ctx); }",
            0x80090194: "{ extern uint32_t wr64_sunny_sky_material_players(uint8_t*, uint32_t); ctx->r15 = S32(wr64_sunny_sky_material_players(rdram, (uint32_t)ctx->r15)); }",
            0x80090430: "{ extern uint32_t wr64_sunny_sky_material_players(uint8_t*, uint32_t); ctx->r15 = S32(wr64_sunny_sky_material_players(rdram, (uint32_t)ctx->r15)); }",
            0x80090524: "{ extern uint32_t wr64_sunny_sky_bottom_draw(uint8_t*, uint32_t); ctx->r15 = S32(wr64_sunny_sky_bottom_draw(rdram, (uint32_t)ctx->r15)); }",
            0x8009064C: "{ extern uint32_t wr64_sunny_sky_material_players(uint8_t*, uint32_t); ctx->r14 = S32(wr64_sunny_sky_material_players(rdram, (uint32_t)ctx->r14)); }",
            0x80090744: "{ extern uint32_t wr64_sunny_sky_fog_update(uint8_t*, uint32_t); ctx->r25 = S32(wr64_sunny_sky_fog_update(rdram, (uint32_t)ctx->r25)); }",
            0x80090C8C: "{ extern uint32_t wr64_two_player_celestial_draw(uint8_t*, recomp_context*, uint32_t); ctx->r6 = S32(wr64_two_player_celestial_draw(rdram, ctx, (uint32_t)ctx->r6)); }",
            0x80090D44: "{ extern uint32_t wr64_sunny_sky_material_players(uint8_t*, uint32_t); ctx->r3 = S32(wr64_sunny_sky_material_players(rdram, (uint32_t)ctx->r3)); }",
            0x80090E24: "{ extern void wr64_sunny_sky_cloud_color(uint8_t*, recomp_context*); wr64_sunny_sky_cloud_color(rdram, ctx); }",
            0x80090F38: "{ extern void wr64_sunny_sky_cloud_draw(uint8_t*, recomp_context*); wr64_sunny_sky_cloud_draw(rdram, ctx); }",
        }
        for address, text in accepted_sky.items():
            expected_hook = {"func": name, "before_vram": address, "text": text}
            assert expected_hook in added, "Accepted sky hook changed: " + hex(address)
            marker = f"    // 0x{address:08X}:"
            assert baseline.count(marker) == 1
            baseline = baseline.replace(marker, "    " + text + "\n" + marker, 1)
            added.remove(expected_hook)
    expected = {
        "func_8008FB74": {0x8008FD18, 0x8008FD40, 0x8008FDCC, 0x8008FDF4, 0x8008FE64, 0x8008FE8C},
        "func_i2_802C70EC": {0x802C7820, 0x802C786C},
        "func_i2_802C5B4C": {0x802C5B94, 0x802C5D04, 0x802C5D40, 0x802C5D64, 0x802C5E14},
    }[name]
    assert len(added) == len(expected) and {hook["before_vram"] for hook in added} == expected, \
        name + ": unexpected preview hook sites"
    regenerated = baseline
    for hook in added:
        marker = f"    // 0x{hook['before_vram']:08X}:"
        assert regenerated.count(marker) == 1, marker
        regenerated = regenerated.replace(marker, "    " + hook["text"] + "\n" + marker, 1)
    versions = [baseline, current, regenerated]
    if name == "func_8008FB74":
        # Run the real viewport/scissor prefix and stop before scene drawing.
        # The camera matrix loaders are intercepted by the fixture. The entire
        # omitted scene tail must remain byte-identical to the prior source.
        marker = "L_8009008C:"
        assert current[current.index(marker):] == baseline[baseline.index(marker):], \
            "Unrelated world rendering changed"
        assert regenerated[regenerated.index(marker):] == baseline[baseline.index(marker):], \
            "A preview hook escaped the viewport/scissor prefix"
        versions = [version[:version.index(marker)] + marker + "\n" +
            "    ctx->r2 = ctx->r6;\n" +
            "    ctx->r31 = MEM_W(0x14, ctx->r29);\n" +
            "    ctx->r29 = ADD32(ctx->r29, 0x1C0);\n    return;\n;}"
            for version in versions]
    parts.extend((versions[0].replace(name, "baseline_" + name, 1), versions[1],
                  versions[2].replace(name, "regenerated_" + name, 1)))

# The unchanged two-player wrapper must call the matching real caption
# producer in each replay, including its independent selection-state branches.
pair_name = "func_i2_802C7C50"
pair_source = extract((root / "RecompiledFuncsPoint0/funcs_21.c").read_text(), pair_name)
assert pair_source == extract(baseline_file("RecompiledFuncsPoint0/funcs_21.c"), pair_name), \
    "Two-player menu selection or miniature layout changed"
for prefix in ("baseline_", "native_pair_", "regenerated_"):
    caption_prefix = "" if prefix == "native_pair_" else prefix
    parts.append(pair_source.replace(pair_name, prefix + pair_name, 1).replace(
        "func_i2_802C70EC", caption_prefix + "func_i2_802C70EC"))

# The new layout must not rewrite cameras, normal small-font rendering, or the
# menu sequence that animates/selects the machines.
for relative, name in (
    ("RecompiledFuncsPoint0/funcs_1.c", "func_8004C998"),
    ("RecompiledFuncsPoint0/funcs_1.c", "func_8004C1D0"),
    ("RecompiledFuncsPoint0/funcs_18.c", "func_801E9858"),
    ("RecompiledFuncsPoint0/funcs_18.c", "func_801E9B04"),
    ("RecompiledFuncsPoint0/funcs_21.c", "func_i2_802C5E28"),
):
    accepted = extract(baseline_file(relative), name)
    if name == "func_8004C998":
        text = "{ extern void wr64_sunny_sky_bottom_camera(uint8_t*, recomp_context*); wr64_sunny_sky_bottom_camera(rdram, ctx); }"
        assert {"func": name, "before_vram": 0x8004C998, "text": text} in new_hooks
        marker = "    // 0x8004C998:"
        assert accepted.count(marker) == 1
        accepted = accepted.replace(marker, "    " + text + "\n" + marker, 1)
        text = "{ extern void wr64_seabed_distance_finish(uint8_t*, recomp_context*); wr64_seabed_distance_finish(rdram, ctx); }"
        assert {"func": name, "before_vram": 0x8004CC48, "text": text} in new_hooks
        marker = "    // 0x8004CC48:"
        assert accepted.count(marker) == 1
        accepted = accepted.replace(marker, "    " + text + "\n" + marker, 1)
    assert extract((root / relative).read_text(), name) == accepted, \
        name + ": existing camera, font, or menu animation changed"

# Replay the existing string formatter and ASCII converter as the independent
# measurement oracle. Capture the final pen position just before restoration;
# individual glyph emissions are intercepted by the C++ fixture.
font_text = (root / "RecompiledFuncsPoint0/funcs_18.c").read_text()
formatter = extract(font_text, "func_801E9858").replace("func_801E9858", "native_caption_string", 1)
marker = "    // 0x801E9AD0:"
assert formatter.count(marker) == 1
formatter = formatter.replace(marker,
    "    { extern void native_capture_pen(int32_t); native_capture_pen((int32_t)ctx->r16); }\n" + marker, 1)
parts.extend((formatter, extract(font_text, "func_801E9B04")))

# Options -> Change Names joins the accepted helper later. Keep its own
# pre-change baseline instead of moving the original Watercraft oracle.
name_baseline = "c8d5b9b580d61df4a5584f9893ae748489d96b1d"
name_path = "RecompiledFuncsPoint0/funcs_22.c"
name_old = subprocess.check_output(["git", "-C", str(root), "show", name_baseline + ":" + name_path], text=True)
name_new = (root / name_path).read_text()
name_config = tomllib.loads(subprocess.check_output(
    ["git", "-C", str(root), "show", name_baseline + ":config/us.rev1.toml"], text=True))["patches"]
current_config = tomllib.loads((root / "config/us.rev1.toml").read_text())["patches"]
name_functions = ("func_i8_802C63E4", "func_i8_802C5D3C")
for name in name_functions:
    baseline = extract(name_old, name)
    current = extract(name_new, name)
    prior = [hook for hook in name_config["hook"] if hook["func"] == name]
    hooks = [hook for hook in current_config["hook"] if hook["func"] == name]
    assert all(hook in hooks for hook in prior), name + ": accepted hooks changed"
    added = [hook for hook in hooks if hook not in prior]
    expected = {0x802C67E0} if name == "func_i8_802C63E4" else {0x802C5D7C,0x802C5E58,0x802C5EAC}
    assert len(added) == len(expected) and {hook["before_vram"] for hook in added} == expected, name
    regenerated = baseline
    if name == "func_i8_802C63E4":
        instructions = [item for item in current_config["instruction"] if item["func"] == name]
        assert instructions == [{"func":name,"vram":0x802C67E4,"value":0x24E7011C}]
        pattern = (r"(    // 0x802C67E4: addiu       \$a3, )\$zero"
                   r"(, 0x11C\n    ctx->r7 = ADD32\()0(, 0X11C\);)")
        regenerated, count = re.subn(pattern, r"\1$a3\2ctx->r7\3", regenerated)
        assert count == 2, "Change Names caption delay copies changed"
    for hook in added:
        marker = f"    // 0x{hook['before_vram']:08X}:"
        assert regenerated.count(marker) == 1, marker
        regenerated = regenerated.replace(marker, "    " + hook["text"] + "\n" + marker, 1)
    assert current == regenerated, name + ": checked-in source differs from durable recipe"
    for prefix, body in (("baseline_",baseline),("",current),("regenerated_",regenerated)):
        for nested in name_functions:
            body = body.replace(nested, prefix + nested)
        parts.append(body)

# Selection, keyboard handling, insertion, backspace, restore/default, commit,
# name-length checks and camera animation remain the existing native code.
for address in ("5800","5EB8","6ADC","6D58","6DA8","6E00","6E68","6EB8","6F4C","6FD4"):
    name = "func_i8_802C" + address
    assert extract(name_old,name) == extract(name_new,name), name + ": name editing/camera semantics changed"
output.write_text("\n".join(parts))
