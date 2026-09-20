from pathlib import Path
import sys

root=Path(sys.argv[1]);source=(root/'RecompiledFuncsPoint0/funcs_0.c').read_text()
start=source.index('RECOMP_FUNC void main_thread(')
end=source.index('\nRECOMP_FUNC ',start+1)
body=source[start:end]
hook='wr64_achievements_native_frame(rdram);'
assert body.count(hook)==1
assert body.index('if (ctx->r3 != ctx->r1)') < body.index(hook) < body.index('// 0x80047740:')
config=(root/'config/us.rev1.toml').read_text()
assert '{ func = "main_thread", before_vram = 0x80047740,' in config
Path(sys.argv[2]).write_text('#include "recomp.h"\n#include "funcs.h"\n'+body)
