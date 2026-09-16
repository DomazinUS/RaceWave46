"""Check the durable pause hooks against the actual generated native producer.

Only metadata statements may differ from the immutable pre-feature function.
No ROM, display-list asset, or game execution is needed.
"""
from pathlib import Path
import subprocess
import sys
import tomllib

root = Path(sys.argv[1])
baseline = "b24fa1920b2e92573e2ab0e9782127a757b6447c"
relative = "RecompiledFuncsPoint0/funcs_17.c"
function = "func_801E4440"
checks = 0


def require(condition, message):
    global checks
    checks += 1
    if not condition:
        raise AssertionError(message)


def extract(source):
    start = source.index(f"RECOMP_FUNC void {function}(")
    end = source.index("\nRECOMP_FUNC ", start + 1)
    return source[start:end]


source = (root / relative).read_text()
current = extract(source)
original = extract(subprocess.check_output(
    ["git", "show", f"{baseline}:{relative}"], cwd=root, text=True))
config = tomllib.loads((root / "config/us.rev1.toml").read_text())
hooks = [hook for hook in config["patches"]["hook"]
         if "wr64_split_screen_pause" in hook["text"]]
require(len(hooks) == 2, "There must be exactly two durable pause boundary hooks")
expected = {0x801E4A84: 1, 0x801E4BF4: 0}
require({hook["before_vram"] for hook in hooks} == expected.keys(),
        "Pause metadata must bracket the labels/cursor after the shared dimmer")
regenerated = original
for hook in hooks:
    address = hook["before_vram"]
    begin = expected[address]
    text = ("{ extern uint32_t wr64_split_screen_pause(uint8_t*, uint32_t, int); "
            "MEM_W(0x70, ctx->r29) = wr64_split_screen_pause(rdram, "
            f"MEM_W(0x70, ctx->r29), {begin}); }}")
    require(hook["func"] == function and hook["text"] == text,
            "Durable pause hook must update the native stack display-list cursor")
    anchor = f"    // 0x{address:08X}:"
    require(regenerated.count(anchor) == 1, "Pause boundary instruction must be unique")
    regenerated = regenerated.replace(anchor, f"    {text}\n{anchor}")
    require(current.count(text) == 1, "Generated native hook is missing or duplicated")

require(current == regenerated,
        "Generated pause function does not match its original plus the two durable hooks")
require(source.count("extern uint32_t wr64_split_screen_pause") == 2,
        "Unexpected extra pause metadata exists elsewhere in this generated file")
begin_position = current.index(hooks[0]["text"])
end_position = current.index(hooks[1]["text"])
require(current.index("// 0x801E4A78:") < begin_position <
        current.index("// 0x801E4BB0:") < current.index("// 0x801E4BE8:") < end_position,
        "Pause scope includes the dimmer or excludes the labels/cursor")
print(f"Passed {checks} native pause hook and regeneration checks.")
