"""Compile the actual setting registration/callback against real persistence."""
from pathlib import Path
import sys

root, output = map(Path, sys.argv[1:3])
source = (root / 'src/wr64_frontend.cpp').read_text()

def registration(method, key):
    start = source.index('enhancementsConfig.' + method + '("' + key + '"')
    position = source.index('(', start)
    depth = 0
    quoted = escaped = False
    while position < len(source):
        char = source[position]
        if quoted:
            if escaped:
                escaped = False
            elif char == '\\':
                escaped = True
            elif char == '"':
                quoted = False
        elif char == '"':
            quoted = True
        elif char == '(':
            depth += 1
        elif char == ')':
            depth -= 1
            if depth == 0:
                assert source[position + 1] == ';'
                return source[start:position + 2]
        position += 1
    raise AssertionError('Unterminated registration: ' + method)

output.write_text('\n'.join([
    '#include "librecomp/config.hpp"', '#include "wr64_draw_distance.hpp"',
    '#include "wr64_object_distance.hpp"',
    'void registered_draw_distance_schema(recomp::config::Config& enhancementsConfig) {',
    *[registration(method, key)
      for key in ('buoy_draw_distance', 'object_draw_distance')
      for method in ('add_enum_option', 'add_option_change_callback')], '}']))
