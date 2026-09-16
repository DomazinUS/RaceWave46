"""Replay the production setting registration and callback with real Config."""
from pathlib import Path
import sys

root, output = map(Path, sys.argv[1:3])
source = (root / "src/wr64_frontend.cpp").read_text()


def registration(method):
    start = source.index('enhancementsConfig.' + method + '("split_screen_layout"')
    position = source.index("(", start)
    depth = 0
    quoted = False
    escaped = False
    while position < len(source):
        c = source[position]
        if quoted:
            if escaped:
                escaped = False
            elif c == "\\":
                escaped = True
            elif c == '"':
                quoted = False
        elif c == '"':
            quoted = True
        elif c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
            if depth == 0:
                assert source[position + 1] == ";"
                return source[start:position + 2]
        position += 1
    raise AssertionError("Unterminated production registration: " + method)


output.write_text('\n'.join([
    '#include "librecomp/config.hpp"', '#include "wr64_split_screen.hpp"',
    'void registered_split_schema(recomp::config::Config& enhancementsConfig) {',
    registration("add_enum_option"), registration("add_option_change_callback"), '}']))
