"""Extract the actual wave-distance registration and callback for persistence checks."""
from pathlib import Path
import sys

root, output = map(Path, sys.argv[1:3])
source = (root / 'src/wr64_frontend.cpp').read_text(encoding='utf-8-sig')
start = source.index('enhancementsConfig.add_enum_option("wave_draw_distance"')
end = source.index('enhancementsConfig.add_enum_option("far_water_distance"', start)
registration = source[start:end]
assert registration.count('add_enum_option(') == 1
assert registration.count('add_option_change_callback(') == 1
assert 'RT64::setWr64WaveDistanceMode(' in registration
output.write_text('#include "librecomp/config.hpp"\n'
                  '#include "common/rt64_wr64_wave_distance.h"\n'
                  'void register_wave_schema(recomp::config::Config& enhancementsConfig) {\n'
                  + registration + '\n}\n', encoding='utf-8')
