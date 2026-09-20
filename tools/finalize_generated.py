"""Apply host integration edits to freshly generated code."""

import re
from pathlib import Path


def replace_once(text, old, new):
    if text.count(old) != 1:
        raise ValueError("Generated hook anchor is missing or ambiguous")
    return text.replace(old, new, 1)


def finalize(directory: Path):
    path = directory / "funcs_1.c"
    text = path.read_text()
    text = replace_once(text, '#include "funcs.h"', '#include "funcs.h"\n\nextern void wr64_forensic_capture_sky(uint8_t* rdram, uint32_t phase, uint32_t a0, uint32_t output_address);')
    text = replace_once(text,
        '    { extern void wr64_sunny_sky_bottom_camera',
        '    const uint32_t wr64_forensic_a0 = (uint32_t)ctx->r4;\n'
        '    const uint32_t wr64_forensic_output = (uint32_t)ctx->r5;\n'
        '    wr64_forensic_capture_sky(rdram, 0, wr64_forensic_a0, wr64_forensic_output);\n'
        '    { extern void wr64_sunny_sky_bottom_camera')
    text = replace_once(text, '    { extern void wr64_seabed_distance_finish',
        '    wr64_forensic_capture_sky(rdram, 1, wr64_forensic_a0, wr64_forensic_output);\n'
        '    { extern void wr64_seabed_distance_finish')
    path.write_text(text, newline="\n")

    # Preserve the culling comparisons, including emitted delay-slot copies.
    addresses = {
        'funcs_5.c': [0x8008C140, 0x8008C2EC, 0x8008C490, 0x8008C648,
                      0x8008C7C8, 0x8008C7D8, 0x8008C960, 0x8008C970,
                      0x8008CB14, 0x8008CCEC, 0x8008CE94],
        'funcs_6.c': [0x80094418, 0x800944A8, 0x8009453C],
    }
    for name, pcs in addresses.items():
        path = directory / name
        text = path.read_text()
        for pc in pcs:
            pattern = rf'(// 0x{pc:08X}: slti[^\n]*\n\s*ctx->r1 = SIGNED\(ctx->r[56]\) < )0X(?:1A8|140)( \? 1 : 0;)'
            text, count = re.subn(pattern, r'\g<1>0X228\2', text)
            expected = 1 if pc in (0x8008C960, 0x8009453C) else 2
            if count != expected:
                raise ValueError(f"Unexpected culling instruction count at {pc:08X}: {count}")
        path.write_text(text, newline="\n")

    # Keep entry hooks in the same order as the release integration.
    path = directory / 'funcs_20.c'
    text = path.read_text()
    locals_block = '    uint64_t hi = 0, lo = 0, result = 0;\n    int c1cs = 0;\n'
    for name, hook in [
        ('func_801FB514', '    uint32_t wr64HudScoreBegin = 0;\n'),
        ('func_i1_802C59E8', '    { extern void wr64_hud_park_spawn(void); wr64_hud_park_spawn(); }\n'),
    ]:
        signature = f'RECOMP_FUNC void {name}(uint8_t* rdram, recomp_context* ctx) {{\n'
        text = replace_once(text, signature + locals_block + hook, signature + hook + locals_block)
    path.write_text(text, newline="\n")


def canonical_tokens(text):
    # Ignore comment/formatting changes and unordered RSP dispatch cases.
    text = re.sub(r'((?:^[ \t]*case 0x[0-9A-Fa-f]+: goto L_[0-9A-Fa-f]+;\n)+)',
                  lambda m: ''.join(sorted(m[0].splitlines(True))), text, flags=re.M)
    token = r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|//[^\n]*|/\*[\s\S]*?\*/|[A-Za-z_]\w*|(?:0[xX][0-9A-Fa-f]+|\d+(?:\.\d*)?(?:[eE][+-]?\d+)?)[uUlLfF]*|>>=|<<=|->|\+\+|--|<<|>>|<=|>=|==|!=|&&|\|\||\+=|-=|\*=|/=|%=|&=|\|=|\^=|[^\s]'
    return '\n'.join(t for t in re.findall(token, text) if not t.startswith(('//', '/*')))
