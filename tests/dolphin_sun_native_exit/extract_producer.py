"""Compile the actual host-side producer without linking the game/runtime."""
from pathlib import Path
import sys

root, output = map(Path, sys.argv[1:])
source = (root / 'src/wr64_render_provenance.cpp').read_text()
begin = source.index('static uint32_t wr64HudContext(')
end = source.index('extern "C" void wr64_hud_score_draw(', begin)
output.write_text('\n'.join([
    '#include "wr64_diagnostic_policy.h"',
    '#include "wr64_render_provenance.h"',
    '#include "common/rt64_wr64_hud_motion.h"',
    '#include "common/rt64_wr64_dolphin_sun_sprite.h"',
    '#include <cstdio>', '#include <cstdlib>', '#include <cstring>',
    '#include <mutex>', '#include <cmath>',
    '#ifdef WR64_ENABLE_RT64', source[begin:end],
]))
