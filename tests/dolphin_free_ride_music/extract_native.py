"""Compile the actual native initializer, music scheduler and queue producers."""
from pathlib import Path
import hashlib
import json
import re
import sys
import tomllib

root, output = map(Path, sys.argv[1:3])
hook = json.loads((Path(__file__).parent / "hooks.json").read_text())[0]
configured = tomllib.loads((root / "config/us.rev1.toml").read_text())["patches"]["hook"]
assert sum(candidate["func"] == hook["func"]
           and candidate.get("before_vram") == int(hook["before_vram"], 16)
           and candidate["text"] == hook["text"] for candidate in configured) == 1

names = {
    "funcs_12.c": ["n_alSynRemovePlayer"],
    "funcs_13.c": ["func_800C14D0", "func_800C1540"],
    "funcs_14.c": ["func_800C21F4", "AudioThread_QueueCmdF32"],
    "funcs_15.c": ["AudioThread_QueueCmdS32", "AudioThread_QueueCmdS8"],
}
pieces = ['#include "recomp.h"', '#include "funcs.h"', '#include "wr64_free_ride.h"',
          'void music_fixture_stub(uint32_t, recomp_context*);']
actual = {name for group in names.values() for name in group}
calls = set()
manifest = []
for filename, group in names.items():
    source = (root / "RecompiledFuncsPoint0" / filename).read_text()
    for name in group:
        start = source.index("RECOMP_FUNC void " + name + "(")
        current = source[start:source.index("\n;}", start) + 3]
        calls.update(re.findall(r"^    (\w+)\(rdram, ctx\);", current, re.M))
        if name == hook["func"]:
            body = "    " + hook["text"] + "\n"
            assert current.count(body) == 1
            baseline = current.replace(body, "", 1)
            marker = "    // " + hook["before_vram"] + ":"
            assert baseline.count(marker) == 1
            assert baseline.replace(marker, body + marker, 1) == current
            pieces.append(baseline.replace(name, "baseline_" + name, 1))
        else:
            baseline = current
        manifest.append({"function": name, "source": "RecompiledFuncsPoint0/" + filename,
                         "baseline_sha256": hashlib.sha256(baseline.encode()).hexdigest()})
        pieces.append(current)

# OS/synthesis/voice dependencies retain observable calls, but do not launch
# threads, wait for audio hardware or synthesize sound in the fixture.
stubs = sorted(calls - actual - {"AudioThread_QueueCmd"})
for index, name in enumerate(stubs):
    pieces.append(f"void {name}(uint8_t* rdram, recomp_context* ctx) "
                  + "{ music_fixture_stub(" + str(index) + ", ctx); }")
output.write_text("\n".join(pieces))
(output.parent / "native-extraction.json").write_text(json.dumps(
    {"functions": manifest, "stubbed_dependencies": stubs}, indent=2) + "\n")
