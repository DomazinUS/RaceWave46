"""Build a GPU-free harness from the production queue consumer and callbacks."""
import pathlib
import sys


ROOT = pathlib.Path(__file__).resolve().parents[2]


def function(source, signature):
    start = source.index(signature)
    brace = source.index("{", start)
    depth = 1
    end = brace + 1
    while depth:
        depth += (source[end] == "{") - (source[end] == "}")
        end += 1
    return source[start:end]


renderer = (ROOT / "lib/RecompFrontend/recompui/src/renderer/rt64_render_context.cpp").read_text()
header = (ROOT / "lib/RecompFrontend/recompui/include/recompui/renderer.h").read_text()
bridge = (ROOT / "src/wr64_texture_packs.cpp").read_text()
state = function(header, "struct TexturePackState") + ";"
actions = renderer[renderer.index("struct TexturePackEnableAction"):renderer.index("unsigned int MI_INTR_REG")]
names = [
    "void renderer::check_texture_pack_actions",
    "void renderer::trigger_texture_pack_update",
    "void renderer::enable_texture_pack",
    "void renderer::disable_texture_pack",
    "void renderer::secondary_enable_texture_pack",
    "void renderer::secondary_disable_texture_pack",
    "bool renderer::is_texture_pack_enable_config_option",
]
implementation = actions + "\n".join(function(renderer, name) for name in names)
implementation += "\n" + "\n".join(line for line in bridge.splitlines() if not line.startswith("#include"))
test = (ROOT / "tests/texture_packs/texture_packs_test.cpp").read_text()
test = test.replace("// PRODUCTION_STATE", state).replace("// PRODUCTION_IMPLEMENTATION", implementation)
output = pathlib.Path(sys.argv[1]).resolve()
output.parent.mkdir(parents=True, exist_ok=True)
output.write_text(test)
print(output)
