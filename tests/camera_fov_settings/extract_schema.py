"""Replay the real frontend registration and callback without a window."""
from pathlib import Path
import sys

root, output = map(Path, sys.argv[1:3])
source = (root / "src/wr64_frontend.cpp").read_text()


def registration(method):
    start = source.index('enhancementsConfig.' + method + '("camera_fov_extra_degrees"')
    position = source.index("(", start)
    depth = 0
    quoted = escaped = False
    while position < len(source):
        char = source[position]
        if quoted:
            if escaped:
                escaped = False
            elif char == "\\":
                escaped = True
            elif char == '"':
                quoted = False
        elif char == '"':
            quoted = True
        elif char == "(":
            depth += 1
        elif char == ")":
            depth -= 1
            if depth == 0:
                assert source[position + 1] == ";"
                return source[start:position + 2]
        position += 1
    raise AssertionError("Unterminated registration: " + method)


output.write_text('\n'.join([
    '#include "librecomp/config.hpp"', '#include "wr64_camera_fov.hpp"', '#include <cmath>',
    'void registered_fov_schema(recomp::config::Config& enhancementsConfig) {',
    registration("add_number_option"), registration("add_option_change_callback"), '}']))
