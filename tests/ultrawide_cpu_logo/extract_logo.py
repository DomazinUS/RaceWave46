"""Compile the existing USA CPU blitter with synthetic pixels, without a ROM or GPU."""
from pathlib import Path
import re, sys
root, output = map(Path, sys.argv[1:])
source = (root / 'RecompiledFuncsPoint0/funcs_6.c').read_text()
start = source.index('RECOMP_FUNC void func_800980D0(')
end = source.index('RECOMP_FUNC void ', start + 1)
function = source[start:end]
assert function.count('wr64_note_cpu_boot_logo(rdram, (uint32_t)ctx->r6)') == 1
output.write_text('#include "recomp.h"\n#include "funcs.h"\n' + function)
