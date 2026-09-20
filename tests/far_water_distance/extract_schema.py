"""Compile only the two real frontend registrations and their callbacks."""
from pathlib import Path
import sys

root, output = map(Path, sys.argv[1:3])
source = (root / "src/wr64_frontend.cpp").read_text()

def registration(key, method):
    start = source.index('enhancementsConfig.' + method + '("' + key + '"')
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
    raise AssertionError("Unterminated registration")

blocks = ['#include "librecomp/config.hpp"', '#include "wr64_seabed_distance.hpp"',
          '#include "common/rt64_wr64_far_water_distance.h"',
          'void registered_water_distance_schema(recomp::config::Config& enhancementsConfig) {']
for key in ("far_water_distance", "seabed_draw_distance"):
    for method in ("add_enum_option", "add_option_change_callback"):
        blocks.append(registration(key, method))
output.write_text("\n".join(blocks + ["}"]))
