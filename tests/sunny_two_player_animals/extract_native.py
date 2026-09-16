"""Compile the native animal dispatcher, wrapping, matrix and view-light code."""
from pathlib import Path
import hashlib
import sys
import tomllib

root, out = map(Path, sys.argv[1:3])
def function(file, name):
    source = (root / 'RecompiledFuncsPoint0' / file).read_text()
    begin = source.index('RECOMP_FUNC void ' + name + '(')
    return source[begin:source.index('\n;}', begin) + 3]

draw = function('funcs_10.c', 'func_800ADF90')
hooks = [h for h in tomllib.loads((root/'config/us.rev1.toml').read_text())['patches']['hook']
         if h['func']=='func_800ADF90' and 'wr64_sunny_animals_' in h['text']]
assert len(hooks)==3
original = draw
for hook in hooks:
    text = '    ' + hook['text'] + '\n'
    assert original.count(text)==1, hook
    original = original.replace(text, '', 1)
assert hashlib.sha256(original.encode()).hexdigest()=='7dea6f43aec3727e1ab846b612110584b57fc26b629c709bc871d72395411036'
rebuilt=original
for hook in hooks:
    at='    // 0x%08X:' % hook['before_vram']
    rebuilt=rebuilt.replace(at,'    '+hook['text']+'\n'+at,1)
assert rebuilt==draw, 'durable hooks differ from generated native dispatcher'
parts=['#include "recomp.h"\n#include "funcs.h"\n#include "checked_memory.h"\n', draw,
       original.replace('void func_800ADF90(', 'void baseline_animal_draw(', 1)]
for file, name in [('funcs_10.c','func_800ADD14'),('funcs_10.c','func_800ADC8C'),
                   ('funcs_6.c','func_800916B4'),('funcs_9.c','func_8009D96C'),('funcs_9.c','func_8009D564'),
                   ('funcs_0.c','func_80048A88'),('funcs_0.c','func_80049C9C'),('funcs_0.c','SysUtils_MtxFToMtx'),
                   ('funcs_0.c','SysUtils_LightsSetSource'),('funcs_0.c','SysUtils_LightsSetAmbient'),
                   ('funcs_0.c','SysUtils_LightsSetColor'),('funcs_0.c','SysUtils_LightsSetDirection'),('funcs_15.c','_nsqrtf'),
                   ('funcs_0.c','SysMain_GfxInitBuffers')]:
    parts.append(function(file,name))
if len(sys.argv)>3 and sys.argv[3] in ('integration', 'allcourses'):
    for file,name in [('funcs_9.c','func_8009E814'),('funcs_9.c','func_8009E794'),
                      ('funcs_9.c','func_800A10E4'),('funcs_9.c','func_800A16F0'),('funcs_9.c','func_800A1CFC'),
                      ('funcs_17.c','func_801E4C60'),('funcs_10.c','func_800ADE14'),('funcs_9.c','func_8009D3AC'),
                      ('funcs_9.c','Math_Normalize_Angle'),('funcs_19.c','func_801ED090'),
                      ('funcs_10.c','func_800AC184'),('funcs_9.c','func_8009D5C0'),('funcs_0.c','SysUtils_Rand'),
                      ('funcs_6.c','func_8009684C'),('funcs_10.c','Mio0_Decompress'),('funcs_6.c','func_80096048'),
                      ('funcs_6.c','func_800961B8'),('funcs_6.c','func_800963CC'),('funcs_6.c','func_800967EC'),
                      ('funcs_6.c','SegmentedToVirtual')]:
        parts.append(function(file,name))
    if sys.argv[3] == 'allcourses':
        init = function('funcs_10.c', 'func_800AC184')
        init_hooks = [h for h in tomllib.loads((root/'config/us.rev1.toml').read_text())['patches']['hook']
                      if h['func'] == 'func_800AC184' and 'wr64_sunny_animals_' in h['text']]
        assert {h['before_vram'] for h in init_hooks} == {0x800AC5F0, 0x800AC668}
        for hook in init_hooks:
            line = '    ' + hook['text'] + '\n'
            assert init.count(line + f"    // 0x{hook['before_vram']:08X}:") == 1
            init = init.replace(line, '', 1)
        parts.append(init.replace('void func_800AC184(', 'void baseline_animal_init(', 1))
        for file, name in [('funcs_6.c', 'func_800962F0'), ('funcs_6.c', 'func_800965B8'),
                           ('funcs_6.c', 'func_800964CC'), ('funcs_9.c', 'func_8009DB90'),
                           ('funcs_9.c', 'func_8009DC10'), ('funcs_9.c', 'func_8009F398'),
                           ('funcs_9.c', 'func_8009FCB0'), ('funcs_9.c', 'func_800A063C'),
                           ('funcs_9.c', 'func_800A2308'), ('funcs_9.c', 'func_800A28F4')]:
            parts.append(function(file, name))
out.write_text('\n'.join(parts))
