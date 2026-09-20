"""Compile the two adjacent production registrations and their real callbacks."""
from pathlib import Path
import hashlib
import json
import sys

root, output = map(Path, sys.argv[1:3])
source = (root / 'src/wr64_frontend.cpp').read_text(encoding='utf-8-sig')
start = source.index('enhancementsConfig.add_enum_option("sunny_two_player_scenery"')
end = source.index('// Keep the unfinished ghost-management tab hidden.', start)
registration = source[start:end]
assert registration.count('add_enum_option(') == 1
assert registration.count('add_bool_option(') == 1
assert registration.count('add_option_change_callback(') == 2
assert registration.index('add_enum_option(') < registration.index('add_bool_option("dolphin_free_ride"')
assert 'std::get<bool>(value)' in registration
assert 'EnhancementsTabId,\n                false);' in source
output.write_text('#include "librecomp/config.hpp"\n'
                  '#include "wr64_sunny_detail.hpp"\n'
                  '#include "wr64_free_ride_menu.hpp"\n'
                  'void register_free_ride_schema(recomp::config::Config& enhancementsConfig) {\n'
                  + registration + '\n}\n', encoding='utf-8')
output.with_suffix('.json').write_text(json.dumps({
    'registration_sha256': hashlib.sha256(registration.encode()).hexdigest(),
    'option_order': ['sunny_two_player_scenery', 'dolphin_free_ride'],
    'callbacks': 'Unmodified production callback bodies',
}, indent=2) + '\n')
