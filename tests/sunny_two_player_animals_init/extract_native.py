"""Use the native animal initializer, allocator metadata and its math helpers."""
from pathlib import Path
import sys
import tomllib

root, output = map(Path, sys.argv[1:3])
def extract(file, name):
    text=(root/'RecompiledFuncsPoint0'/file).read_text()
    start=text.index('RECOMP_FUNC void '+name+'(')
    return text[start:text.index('\n;}',start)+3]

init=extract('funcs_10.c','func_800AC184')
hooks=[h for h in tomllib.loads((root/'config/us.rev1.toml').read_text())['patches']['hook']
       if h['func']=='func_800AC184' and 'wr64_sunny_animals_' in h['text']]
assert {h['before_vram'] for h in hooks}=={0x800AC5F0,0x800AC668}
base=init
for hook in hooks:
    line='    '+hook['text']+'\n'
    marker=f"    // 0x{hook['before_vram']:08X}:"
    assert base.count(line+marker)==1
    base=base.replace(line,'',1)
rebuilt=base
for hook in hooks:
    marker=f"    // 0x{hook['before_vram']:08X}:"
    rebuilt=rebuilt.replace(marker,'    '+hook['text']+'\n'+marker,1)
assert rebuilt==init
parts=['#include "recomp.h"\n#include "funcs.h"\n#include "checked_memory.h"\n',
       init,base.replace('void func_800AC184(','void baseline_animal_init(')]
for file,name in [('funcs_9.c','func_8009D5C0'),('funcs_0.c','SysUtils_Rand'),
                  ('funcs_0.c','SysUtils_MtxFToMtx'),('funcs_15.c','_nsqrtf'),
                  ('funcs_6.c','func_8009684C'),('funcs_10.c','Mio0_Decompress'),
                  ('funcs_6.c','func_80096048'),('funcs_6.c','func_800961B8'),
                  ('funcs_6.c','func_800963CC'),('funcs_6.c','func_800967EC'),
                  ('funcs_6.c','SegmentedToVirtual')]:
    parts.append(extract(file,name))
output.write_text('\n'.join(parts))
