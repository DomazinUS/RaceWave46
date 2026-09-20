"""Extract the production snapshot, reset, projection call and actor coverage gate."""
from pathlib import Path
import hashlib
import json
import re
import sys

root, output = map(Path, sys.argv[1:])
paths = {name: root / f"lib/rt64/src/{path}" for name, path in {
    "state": "hle/rt64_state.cpp", "reset": "hle/rt64_workload.cpp",
    "workload": "hle/rt64_workload.h", "renderer": "render/rt64_framebuffer_renderer.cpp"
}.items()}
sources = {name: path.read_text() for name, path in paths.items()}

def statement(source, marker):
    start = source.index(marker)
    return source[start:source.index(";", start) + 1]

def block(source, start):
    opening = source.index("{", start)
    depth = 1
    for pos in range(opening + 1, len(source)):
        depth += (source[pos] == "{") - (source[pos] == "}")
        if depth == 0:
            return source[start:pos + 1]
    raise AssertionError("Unclosed production block")

renderer = sources["renderer"]
actor = renderer.index("if (covered) rt->rasterShadowRacers |= 1u << racer;")
coverage = block(renderer, renderer.rfind("if (rt->prepared)", 0, actor))
assert "bounds.reliable" in coverage and "corner < 8" in coverage
projection = statement(renderer, "const auto projection = wr64BuildRasterShadowProjection(")
assert "p.curWorkload->wr64RasterShadowDistanceMode" in projection
assert not re.search(r"getWr64RTSettings|setWr64RasterShadowDistance", projection)
fields = [statement(sources["workload"], declaration) for declaration in
          ("bool wr64RasterShadowScope =", "uint32_t wr64RasterShadowDistanceMode =")]
reset = [statement(sources["reset"], field + " =") for field in
         ("wr64RasterShadowScope", "wr64RasterShadowDistanceMode")]
capture = [statement(sources["state"], "workload." + field + " =") for field in
           ("wr64RasterShadowScope", "wr64RasterShadowDistanceMode")]
output.write_text("\n".join([
    "// Generated from production source; do not edit.",
    "struct Snapshot {", *fields, "void reset() {", *reset, "} };",
    "void capture(Snapshot &workload, const Wr64RTSettings &wr64Selected,",
    "uint32_t wr64Course, uint32_t wr64Players, uint32_t wr64Phase, uint32_t wr64Mode, bool wr64LoadedEnhanced) {",
    *capture, "}",
    "Wr64RasterShadowProjection rendererProjection(const Snapshot &workload, const float camera[3], const float light[3]) {",
    "struct { const Snapshot *curWorkload; } p{&workload};",
    # The only adapter renames the renderer's existing camera/light inputs.
    projection.replace("shadowCamera", "camera").replace("shadowLight.toLight.data()", "light")
        .replace("shadowLight.toLight", "light"),
    "return projection; }",
    "void coverActors(ActorFixture *rt) {", coverage, "}"
]))
output.with_suffix(".json").write_text(json.dumps({
    str(path.relative_to(root)): hashlib.sha256(path.read_bytes()).hexdigest()
    for path in paths.values()
}, indent=2) + "\n")
