"""Compile complete production spray helpers without creating a GPU or game.

The C++ test substitutes renderer container types only. Texture classification,
native vertex provenance, assignment and writeback are production code.
"""
from pathlib import Path
import re
import sys

source, output = map(Path, sys.argv[1:])
text = source.read_text(encoding="utf-8-sig")
constant = re.search(r"    static constexpr uint64_t Wr64LateralDropletTextureHash = [^;]+;", text)
assert constant is not None
start = text.index("    static bool isWr64LateralDropletTexture(uint64_t textureHash) {")
end = text.index("    bool GameFrame::areFramebufferPairsCompatible(", start)
output.write_text(constant.group() + "\n" + text[start:end], encoding="utf-8")
