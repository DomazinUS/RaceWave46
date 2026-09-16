"""Compile actual animal stamp functions against a small CPU workload model."""
from pathlib import Path
import sys

root, out = map(Path, sys.argv[1:])
source = (root / 'lib/rt64/src/hle/rt64_game_frame.cpp').read_text()
names = ['wr64FishStampTransformIdentity', 'wr64SeagullAssignTransformIdentity',
         'wr64SpriteFamilyStampTransformIdentity', 'wr64DolphinStampTransformIdentity',
         'wr64DrakeSchoolStampTransformIdentity', 'wr64WhaleStampTransformIdentity',
         'wr64DuckStampTransformIdentity']
parts = []
for name in names:
    begin = source.index('    static void ' + name + '(')
    end = source.index('\n    }', begin) + len('\n    }')
    parts.append(source[begin:end])
original = '\n'.join(parts)
assert original.count('wr64AnimalReplayAliases(drawData,') == 6
baseline = original.replace('wr64AnimalReplayAliases(drawData, wr64FishReplayUses)',
                            'std::map<uint32_t, uint32_t>{}')
baseline = baseline.replace('wr64AnimalReplayAliases(drawData, wr64SeagullReplayUses)',
                            'std::map<uint32_t, uint32_t>{}')
for prefix in ('Dolphin', 'Drake', 'Whale', 'Duck'):
    baseline = baseline.replace('wr64AnimalReplayAliases(drawData, wr64' + prefix + 'ReplayUses)',
                                'std::map<uint32_t, uint32_t>{}')
for name in names:
    baseline = baseline.replace(name, name + 'Baseline')
out.write_text('namespace RT64 {\n' + original + '\n' + baseline + '\n}\n')
