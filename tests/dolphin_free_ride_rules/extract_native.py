"""Extract native functions and apply the delivery hooks, without a game/ROM.

The timer test uses the unmodified native entry through 801F43E4; the remainder
of the large mixed HUD function is structurally verified, rather than replacing
its speed renderer with a transcription. Other functions execute in full.
"""
from pathlib import Path
import hashlib
import json
import re
import sys
import tomllib

root, output = map(Path, sys.argv[1:3])
hooks = json.loads((Path(__file__).parent / "hooks.json").read_text())
configured = tomllib.loads((root / "config/us.rev1.toml").read_text())["patches"]["hook"]
for hook in hooks:
    match = [candidate for candidate in configured
             if candidate["func"] == hook["func"]
             and candidate.get("before_vram") == int(hook["before_vram"], 16)
             and candidate["text"] == hook["text"]]
    assert len(match) == 1, "Durable config hook absent or changed: " + hook["func"]
functions = [
    ("funcs_3.c", "func_800762D0"),
    ("funcs_14.c", "func_800C32A0"),
    ("funcs_14.c", "func_800C377C"),
    ("funcs_15.c", "AudioThread_QueueCmdS8"),
    ("funcs_20.c", "func_i1_802C5DF4"),
    ("funcs_20.c", "func_801F4120"),
    ("funcs_20.c", "func_801FBFB4"),
    ("funcs_20.c", "func_801FAEB8"),
]
pieces = ['#include "recomp.h"', '#include "funcs.h"', '#include "wr64_free_ride.h"',
          'void baseline_AudioThread_QueueCmdS8(uint8_t*, recomp_context*);']
manifest = []
for filename, name in functions:
    source = (root / "RecompiledFuncsPoint0" / filename).read_text()
    start = source.index("RECOMP_FUNC void " + name + "(")
    current = source[start:source.index("\n;}", start) + 3]
    baseline = current
    matching = [hook for hook in hooks if hook["func"] == name]
    for hook in matching:
        body = "    " + hook["text"] + "\n"
        assert baseline.count(body) <= 1, name + ": duplicate Free Ride hook"
        baseline = baseline.replace(body, "", 1)
    assert "wr64_free_ride_" not in baseline, name + ": unrecognized Free Ride hook"
    patched = baseline
    for hook in matching:
        marker = "    // " + hook["before_vram"] + ":"
        assert patched.count(marker) == 1, (name, marker)
        patched = patched.replace(marker, "    " + hook["text"] + "\n" + marker, 1)
    assert current == patched, name + ": generated native function/config hook mismatch"
    manifest.append({"function": name, "source": "RecompiledFuncsPoint0/" + filename,
                     "baseline_sha256": hashlib.sha256(baseline.encode()).hexdigest(),
                     "hook_sites": [hook["before_vram"] for hook in matching]})
    if name == "func_801FAEB8":
        # Its existing split-HUD bridge is outside this isolated rules target.
        # Verify complete source preservation plus the single entry guard.
        continue
    # Free Ride changes only the timer branch; speed instructions remain exact.
    if name == "func_801F4120":
        stop = "L_801F43E4:\n"
        assert baseline[baseline.index(stop):] == patched[patched.index(stop):]
        baseline = baseline[:baseline.index(stop)] + stop + "    return;\n;}"
        patched = patched[:patched.index(stop)] + stop + "    return;\n;}"
    old = baseline.replace(name, "baseline_" + name, 1)
    if name != "AudioThread_QueueCmdS8":
        old = old.replace("    AudioThread_QueueCmdS8(rdram, ctx);",
                          "    baseline_AudioThread_QueueCmdS8(rdram, ctx);")
    pieces += [old, patched]

output.write_text("\n".join(pieces))
(output.parent / "native-extraction.json").write_text(json.dumps(manifest, indent=2) + "\n")
