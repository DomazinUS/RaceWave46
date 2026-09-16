"""Compile the actual push-constant stamp and shader tag branch on the CPU."""
from pathlib import Path
import sys

root, output = map(Path, sys.argv[1:3])
renderer = (root / "lib/rt64/src/render/rt64_framebuffer_renderer.cpp").read_text()
shader = (root / "lib/rt64/src/shaders/RasterPS.hlsl").read_text()
start = renderer.index("                rasterParams.padding.y = 0;")
end = renderer.index("                worker->commandList->setGraphicsPushConstants", start)
stamp = renderer[start:end]
start = shader.index("    if (gConstants.padding.z == WR64_DOLPHIN_SUN_FADE_TAG) {")
end = shader.index("\n    }", start) + len("\n    }")
branch = shader[start:end]
output.write_text("\n".join([
    "static void stampOpacity(interop::RasterParams &rasterParams, float loss) {",
    "    struct { float wr64DolphinSunOpacityLoss; } triangles{loss};",
    stamp,
    "}",
    "static bool shadeOpacity(const interop::RasterParams &gConstants, float &alpha, float &alphaCompareValue) {",
    "    struct { float a; } combinerColor{alpha};",
    branch,
    "    alpha = combinerColor.a;",
    "    return true;",
    "}",
]))
