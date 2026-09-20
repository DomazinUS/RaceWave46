"""Extract the independent original projector; omit only its visibility culls."""
from pathlib import Path
import re
import subprocess
import sys

root, output = map(Path, sys.argv[1:3])
source = subprocess.check_output(["git", "-C", str(root), "show",
    "e0e228562e8efb00a655309ba6f6a419c53564e8:RecompiledFuncsPoint0/funcs_5.c"], text=True)

def extract(name):
    match = re.search(r"void " + name + r"\(uint8_t\* rdram, recomp_context\* ctx\) \{", source)
    assert match, name
    return source[match.start():source.index("\n;}", match.end()) + 3]

projector = extract("func_8008962C")
gate = "c1cs = ctx->f10.fl < ctx->f8.fl;"
assert projector.count(gate) == 1
projector = projector.replace(gate, "c1cs = 0; /* Test: omit primary facing gate. */", 1)
marker = "    // 0x80089B28:"
assert projector.count(marker) == 1
projector = projector.replace(marker, "    goto L_80089BF4; /* Test: preserve projected record before screen culls. */\n" + marker, 1)
output.write_text('\n'.join(['#include "recomp.h"',
    'void SysUtils_MtxToMtxF(uint8_t*, recomp_context*);', extract("func_800895A0"), projector]))
