from pathlib import Path
import re,sys,json,hashlib,tomllib
root,out=map(Path,sys.argv[1:3]);out.mkdir(parents=True,exist_ok=True)
s=(root/'RecompiledFuncsPoint0/funcs_20.c').read_text(encoding='utf-8')
# Check the persistent regeneration recipe against the checked-in native hook.
config=tomllib.loads((root/'config/us.rev1.toml').read_text(encoding='utf-8'))
def entries(value):
 if isinstance(value,dict):
  if 'func' in value and 'before_vram' in value:yield value
  for item in value.values():yield from entries(item)
 elif isinstance(value,list):
  for item in value:yield from entries(item)
hooks=[h for h in entries(config) if h.get('func')=='func_i0_802C6044' and 'wr64_title_menu_origin' in h.get('text','')]
assert len(hooks)==1, 'Expected exactly one persistent title-origin hook'
assert hooks[0]['before_vram']==0x802C60E8, 'Title hook must follow the native origin load'
assert s.count(hooks[0]['text'])==1, 'Generated hook must match the persistent recipe once'
assert hooks[0]['text']+'\n    // 0x802C60E8:' in s, 'Generated hook is at the wrong instruction'
names=['func_i0_802C6044','func_i0_802C63AC','func_i0_802C6878']
parts=['#include "recomp.h"\n#include "funcs.h"'];calls=set();manifest={}
for name in names:
 body=re.search(r'RECOMP_FUNC void '+name+r'\(uint8_t\* rdram, recomp_context\* ctx\) \{.*?\n;\}',s,re.S)[0]
 manifest[name]=hashlib.sha256(body.encode()).hexdigest()
 calls.update(re.findall(r'\n    (\w+)\(rdram, ctx\);',body))
 if name=='func_i0_802C6044':
  original='\n'.join(x for x in body.split('\n') if 'wr64_title_menu_origin' not in x)
  parts.append(original.replace('void '+name+'(', 'void title_menu_baseline_draw(',1))
 parts.append(body)
custom={'func_80094338','func_801E946C','func_801E3EE0','func_801E5554'}
for name in sorted(calls-set(names)-custom):parts.append('void '+name+'(uint8_t*r,recomp_context*c){c->r2=c->r4;}')
(out/'native_title.c').write_text('\n'.join(parts),encoding='utf-8')
(out/'provenance.json').write_text(json.dumps(manifest,indent=2),encoding='utf-8')
