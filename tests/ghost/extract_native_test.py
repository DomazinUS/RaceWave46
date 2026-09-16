"""Select existing USA functions for a local ROM-backed integration test.

Output stays in the test build directory. This does not generate production
game code, copy Shindou functions, or contain/distribute ROM assets.
"""
from pathlib import Path
import re
import sys

root, output = map(Path, sys.argv[1:])
names = {"Mio0_Decompress", "func_80096048", "func_800965B8",
         "func_800967EC", "SegmentedToVirtual", "func_800AC098"}
selected = {}
for path in (root / "RecompiledFuncsPoint0").glob("funcs_*.c"):
    text = path.read_text()
    starts = list(re.finditer(r"^RECOMP_FUNC void (\w+)\(", text, re.M))
    for index, match in enumerate(starts):
        if match[1] in names:
            end = starts[index+1].start() if index+1 < len(starts) else len(text)
            selected[match[1]] = text[match.start():end].replace(
                '{\n', '{\n    wr64_ghost_test_check_context(ctx);\n', 1)
assert selected.keys() == names
output.write_text('#include "recomp.h"\n#include "funcs.h"\n'
                  'void wr64_ghost_test_check_context(recomp_context*);\n' + '\n'.join(selected.values()))
runtime_source = (root / 'lib/N64ModernRuntime/librecomp/src/pi.cpp').read_text()
start = runtime_source.index('void recomp::do_rom_read(')
end = runtime_source.index('void recomp::do_rom_pio(', start)
runtime_function = runtime_source[start:end].replace('{\n', '''{
    require(physical_addr >= recomp::rom_base, "runtime ROM read requires PI bus address");
    require(physical_addr - recomp::rom_base + num_bytes <= rom.size(), "runtime ROM read bounded");
''', 1)
output.with_name('runtime_rom_read_test.inc').write_text(runtime_function)
