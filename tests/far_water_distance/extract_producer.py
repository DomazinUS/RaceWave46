"""Extract complete native water initialization and vertex production."""
from pathlib import Path
import hashlib
import sys

root, output = map(Path, sys.argv[1:3])
functions = [
    ('funcs_1.c', 'func_8004F9E0', 'f8d5e004d48b00c7939d484ba1c1682238529c733ba1fd6f49c167b4169eef74'),
    ('funcs_1.c', 'func_8004E614', '9da4c3a48f1e981a1b119ef021ec9b2493544922131a07ff7e761b3fd2bfd175'),
    ('funcs_1.c', 'func_8004F790', 'd8a70fc668d5ebe10de6d7f145358dfe1719a96e3be87b7b25150f08387425cb'),
    ('funcs_1.c', 'func_80050204', 'b39ac3ddde53fbdc2828ab5a76c2fa8ef80ebf9fca9004d28fdc27ef9cab73e2'),
    ('funcs_0.c', 'SysUtils_Rand', '8b49820493c6f5fc108cd409f38a8330f9ba3995e6f9f02249299330383ae4eb'),
]
parts = ['#include "recomp.h"\n#include "funcs.h"\n#include "checked_memory.h"\n']
for file, name, digest in functions:
    text = (root / 'RecompiledFuncsPoint0' / file).read_text()
    start = text.index('RECOMP_FUNC void ' + name + '(')
    code = text[start:text.index('\n;}', start) + 3]
    if name == 'func_80050204':
        # Wave scope replay executes this read-only hook in its own suite.
        # This baseline fixture retains the exact original native instruction
        # body and digest instead of acquiring an unrelated host dependency.
        hook = '    { extern void wr64_wave_distance_capture(uint8_t*, recomp_context*); wr64_wave_distance_capture(rdram, ctx); }\n'
        assert code.count(hook) == 1 and hook + '    // 0x80050B44:' in code
        assert 'before_vram = 0x80050B44' in (root / 'config/us.rev1.toml').read_text()
        code = code.replace(hook, '')
    assert hashlib.sha256(code.encode()).hexdigest() == digest, f'Native producer changed: {name}'
    parts.append(code)
output.write_text('\n'.join(parts))

# The generic sky fixture intentionally disables the accepted border removal.
# Compile its actual shipped shim for this viewport-admission replay instead.
shim = (root / 'src/recomp_shims.cpp').read_text()
start = shim.index('extern "C" uint32_t wr64_experimental_viewport_borders() {')
viewport = shim[start:shim.index('\n}', start) + 2]
assert 'return 1U;' in viewport
output.with_suffix('.viewport.inc').write_text(viewport)
