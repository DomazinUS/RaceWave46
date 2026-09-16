"""Execute actual celestial rect pairing with a pre-partition negative control."""
from pathlib import Path
import sys

root, out = map(Path, sys.argv[1:])
source = (root / 'lib/rt64/src/hle/rt64_game_frame.cpp').read_text()
parts = []
for name in ('wr64CelestialRectView', 'wr64CelestialPairRects'):
    begin = source.rfind('\n', 0, source.index(name + '(')) + 1
    end = source.index('\n    }', begin) + len('\n    }')
    parts.append(source[begin:end])
assert source.count('wr64CelestialPairRects(curWorkload, prevWorkload)') == 1
negative = parts[1].replace('wr64CelestialPairRects(', 'wr64CelestialPairRectsOld(')
needle = 'const uint32_t view = wr64CelestialRectView(idx, desc.scissorRect);'
assert negative.count(needle) == 1
negative = negative.replace(needle, 'const uint32_t view = 0;')
out.write_text('namespace RT64 {\n' + '\n'.join(parts) + '\n' + negative + '\n}\n')

renderer = (root / 'lib/rt64/src/render/rt64_framebuffer_renderer.cpp').read_text()
begin = renderer.index('                const bool wr64TwoPCelestialSceneRect =')
predicate = renderer[begin:renderer.index(';', begin) + 1]
begin = renderer.index('                int32_t wr64HudAnchorDx = 0;')
apply = renderer[begin:renderer.index('                if (wr64FinishHudCall)', begin)]
assert apply.count('!wr64TwoPCelestialSceneRect &&') == 1
body = predicate + '\n' + apply + '\n    return wr64ComposerCallRect;\n'
signature = ('static FixedRect {name}(const Projection &proj, const Call &call, '
             'uint64_t wr64HudTmemHash, FixedRect wr64ComposerCallRect, '
             'bool wr64VerticalSceneRect, int wr64VerticalPauseHalf=0, int wr64VerticalLapHalf=0) {{\n')
(out.parent / 'renderer_anchor.inc').write_text('namespace RT64 {\n' +
    signature.format(name='applyProductionAnchor') + body + '}\n' +
    signature.format(name='applyOldAnchor') + body.replace('!wr64TwoPCelestialSceneRect &&', '') + '}\n}\n')
