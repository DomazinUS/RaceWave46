"""Replay native matrix preparation and buoy detail draw without simulation."""
from pathlib import Path
import hashlib
import sys
import tomllib

root,out=map(Path,sys.argv[1:3])
source=(root/'RecompiledFuncsPoint0/funcs_3.c').read_text()
def block(start,end):
    a=source.index(start);return source[a:source.index(end,a)]
matrix=block('L_8006FE40:','L_80070138:')
assert hashlib.sha256(matrix.encode()).hexdigest()=='f30ffa8ff90bbdc0a75d9a0e437d2cd0e51cf81f51a40956fe465e9de4c21c5c'
detail=block('L_800713E8:','L_800715F4:')
twilight=block('L_8007180C:','L_800718E0:')
twilight_update=block('L_8006E5BC:','L_8006E660:')
hooks=[h for h in tomllib.loads((root/'config/us.rev1.toml').read_text())['patches']['hook']
       if h['func']=='func_8006E674' and h['before_vram']==0x800713FC]
assert len(hooks)==1
line='    '+hooks[0]['text']+'\n'
assert detail.count(line)==1
original=detail.replace(line,'',1)
assert hashlib.sha256(original.encode()).hexdigest()=='19e8bee36eb747e5394de6437a5cf6c5c1a8821e1ed5d1ff45dcd5c95514b5b7'
assert original.replace('    // 0x800713FC:',line+'    // 0x800713FC:',1)==detail
def wrap(name,body,end):
    return ('RECOMP_FUNC void '+name+'(uint8_t* rdram,recomp_context* ctx) {\n'
            'uint64_t hi=0,lo=0,result=0; int c1cs=0;\n'+body+'\n'+end+': return;\n}\n')
parts=['#include "recomp.h"\n#include "funcs.h"\n#include "checked_memory.h"\n',
       wrap('native_buoy_matrices',matrix,'L_80070138'),
       wrap('baseline_buoy_detail',original,'L_800715F4'),
       wrap('enhanced_buoy_detail',detail,'L_800715F4'),
       wrap('native_twilight_segments',twilight,'L_800718E0'),
       wrap('native_twilight_animation_update',twilight_update,'L_8006E660')]
for file,name in [('funcs_0.c','SysUtils_MatrixLookAt'),('funcs_0.c','SysUtils_MtxFToMtx'),
                  ('funcs_15.c','_nsqrtf'),('funcs_6.c','SegmentedToVirtual')]:
    s=(root/'RecompiledFuncsPoint0'/file).read_text();a=s.index('RECOMP_FUNC void '+name+'(')
    parts.append(s[a:s.index('\n;}',a)+3])
out.write_text('\n'.join(parts))
