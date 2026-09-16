"""Offline evidence that the gate precedes game initialization, not just presentation."""
from pathlib import Path
import tomllib

root = Path(__file__).resolve().parents[2]
source = (root / "RecompiledFuncsPoint0/funcs_0.c").read_text()
idle = source.split("RECOMP_FUNC void Main_IdleThread(", 1)[1].split("RECOMP_FUNC void ", 1)[0]
hook = "{ extern void wr64_wait_for_rt_startup(uint8_t*); wr64_wait_for_rt_startup(rdram); }"
assert idle.count(hook) == 1
assert idle.index("func_800980D0(rdram, ctx)") < idle.index("// 0x800479D0:")
assert idle.index("// 0x80047A00:") < idle.index("// 0x80047A08:") < idle.index(hook)
assert idle.index(hook) < idle.index("// 0x80047A10:") < idle.index("osCreatePiManager_recomp(rdram, ctx)")
assert idle.index(hook) < idle.index("osCreateThread_recomp(rdram, ctx)") < idle.index("osStartThread_recomp(rdram, ctx)")
config = tomllib.loads((root / "config/us.rev1.toml").read_text())
def dictionaries(value):
    if isinstance(value, dict):
        yield value
        for child in value.values():
            yield from dictionaries(child)
    elif isinstance(value, list):
        for child in value:
            yield from dictionaries(child)
matches = [d for d in dictionaries(config) if d.get("func") == "Main_IdleThread" and d.get("before_vram") == 0x80047A10]
assert len(matches) == 1 and matches[0]["text"] == hook
host = (root / "src/wr64_render_provenance.cpp").read_text()
wait = host.split('extern "C" void wr64_wait_for_rt_startup(', 1)[1].split('extern "C" void wr64_note_cpu_boot_logo', 1)[0]
assert "yield_self_1ms(rdram)" in wait and "!exited.load()" in wait
assert "MEM_" not in wait and "sleep_for" not in wait
renderer = (root / "src/rt64_renderer.cpp").read_text()
assert renderer.index("app->updateScreen();") < renderer.index("poll_startup_prewarm();")
print("PASS native startup boundary: logo swap/unblack precede wait; game/PI/audio startup follows; TOML hook matches generated code; cooperative quit-aware wait")
