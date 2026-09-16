"""Run native ending state/light bodies; isolate native viewport command prefix.

No game, renderer, file I/O, or game assets are invoked by the executable.
"""
from pathlib import Path
import re
import sys

root, output = map(Path, sys.argv[1:3])

def extract(file, name):
    source = (root / "RecompiledFuncsPoint0" / file).read_text(encoding="utf-8")
    start = source.index("RECOMP_FUNC void " + name + "(")
    return source[start:source.index("\n;}", start) + 3]

bodies = [extract("funcs_19.c", "func_801ECB98"),
          extract("funcs_23.c", "func_i15_802C6CAC"),
          extract("funcs_5.c", "func_8008E4B0")]
viewport = extract("funcs_6.c", "func_8008FB74")
# Stop after the native single-/two-player viewport and scissor branches.
# This prefix calls only matrix setup; all geometry, assets and drawing follow.
viewport = viewport[:viewport.index("L_8009008C:")]
viewport += "L_8009008C:\n    ctx->r2 = ctx->r6;\n    return;\n;}\n"
viewport = viewport.replace("func_8008FB74", "ending_native_viewport_prefix", 1)
bodies.append(viewport)
calls = sorted(set(re.findall(r"^    ([A-Za-z0-9_]+)\(rdram, ctx\);", "\n".join(bodies), re.M)))
output.write_text('#include "recomp.h"\n' +
    "\n".join("void " + name + "(uint8_t*, recomp_context*);" for name in calls) +
    "\n" + "\n".join(bodies), encoding="utf-8")
