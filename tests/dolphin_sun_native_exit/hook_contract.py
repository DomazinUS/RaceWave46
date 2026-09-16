"""Verify exact trial insertions while retaining older native source guards."""
from pathlib import Path
import json
import tomllib

SITES = {0x8008D94C, 0x8008D978, 0x8008DD70, 0x8008DD78, 0x8008DFC0, 0x8008DFC4}

def trial_hooks(root):
    hooks = json.loads((root / 'tests/dolphin_sun_native_exit/hooks.json').read_text())
    assert len(hooks) == 6 and {h['before_vram'] for h in hooks} == SITES
    assert all(h['func'] == 'func_8008D94C' for h in hooks)
    configured = tomllib.loads((root / 'config/us.rev1.toml').read_text())['patches']['hook']
    assert all(configured.count(h) == 1 for h in hooks), 'Trial recipe does not match durable hooks'
    source = (root / 'RecompiledFuncsPoint0/funcs_5.c').read_text()
    for h in hooks:
        insertion = '    ' + h['text'] + f"\n    // 0x{h['before_vram']:08X}:"
        assert source.count(insertion) == 1, 'Trial insertion does not match generated source'
    return hooks

def without_trial_hooks(root, text):
    for hook in trial_hooks(root):
        line = '    ' + hook['text'] + '\n'
        assert text.count(line) == 1, 'Missing or duplicate trial insertion'
        text = text.replace(line, '', 1)
    return text

DEFAULT_OFF_STUBS = '''
uint32_t wr64_dolphin_sun_begin(uint8_t* ram, float x, float y) { return 0; }
void wr64_dolphin_sun_packet(uint8_t* ram, uint32_t token, uint32_t address) {}
'''
