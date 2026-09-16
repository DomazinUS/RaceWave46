"""Select existing USA producers into the test build directory, without assets."""
from pathlib import Path
import re
import sys
root, output = map(Path, sys.argv[1:])
names = {"SysUtils_Round", "SysUtils_TaylorSeries", "func_800481E0",
         "func_80048A88", "_nsqrtf", "FadeTransition_SetProps",
         "func_801E74BC", "func_801E76C0", "func_801E7908"}
selected = {}
for number in (0, 15, 18):
    source = (root / f"RecompiledFuncsPoint0/funcs_{number}.c").read_text()
    starts = list(re.finditer(r"^RECOMP_FUNC void (\w+)\(", source, re.M))
    for i, match in enumerate(starts):
        if match[1] in names:
            end = starts[i+1].start() if i+1 < len(starts) else len(source)
            selected[match[1]] = source[match.start():end]
assert selected.keys() == names, names - selected.keys()
output.write_text('#include "recomp.h"\n#include "funcs.h"\n' + '\n'.join(selected.values()))
