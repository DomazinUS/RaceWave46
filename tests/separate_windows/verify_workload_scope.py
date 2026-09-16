"""Check exact native-marker handoff and recycled-workload reset wiring."""
from pathlib import Path
import re
import sys

root = Path(sys.argv[1])
workload = (root / 'lib/rt64/src/hle/rt64_workload.cpp').read_text(encoding='utf-8-sig')
reset = workload.split('void Workload::reset() {', 1)[1].split('void Workload::', 1)[0]
for statement in ('wr64VerticalSplit = false;', 'wr64SeparateWindows = false;',
                  'wr64PauseOwner = 0;', 'wr64PauseFirstCall = UINT32_MAX;',
                  'wr64PauseLastCall = 0;', 'wr64PauseDrawOwner = 0;', 'wr64LapScope = {};'):
    assert statement in reset, f'Recycled workload retained ownership: {statement}'
gbi = (root / 'lib/rt64/src/gbi/rt64_gbi_extended.cpp').read_text(encoding='utf-8-sig')
hook = gbi.split('void noOpHook(', 1)[1].split('uint32_t magicNumber', 1)[0]
assert '(*dl)->w0 == Wr64SeparateWindowsMarker' in hook
assert re.search(r'wr64DecodeSplitMarker\([^;]+&workload\.wr64SeparateWindows', hook)
print('PASS: seven actual workload ownership resets and native separate-marker handoff')
