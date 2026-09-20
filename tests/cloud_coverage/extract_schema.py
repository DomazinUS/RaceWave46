"""Extract the frontend's actual cloud setting and callback for config tests."""
from pathlib import Path
import sys

root, output = map(Path, sys.argv[1:3])
source = (root / 'src/wr64_frontend.cpp').read_text(encoding='utf-8-sig')
start = source.index('enhancementsConfig.add_enum_option("cloud_coverage"')
end = source.index('enhancementsConfig.add_enum_option("seabed_draw_distance"', start)
registration = source[start:end]
assert registration.count('add_enum_option(') == 1
assert registration.count('add_option_change_callback(') == 1
output.write_text('#include "librecomp/config.hpp"\n'
                  '#include "common/rt64_wr64_cloud_coverage_settings.h"\n'
                  'void register_cloud_schema(recomp::config::Config& enhancementsConfig) {\n'
                  + registration + '\n}\n', encoding='utf-8')
