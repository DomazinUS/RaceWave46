"""Check the fixture and pre-existing paths without requiring the large trace."""
import hashlib
import json
from pathlib import Path
import sys


def preserved_regions(root):
    sys.path.insert(0, str(root / 'tests/dolphin_sun_native_exit'))
    from hook_contract import without_trial_hooks
    def read(path):
        return (root / path).read_text(encoding="utf-8-sig")

    def region(text, start, end):
        offset = text.index(start)
        return text[offset:text.index(end, offset)]

    renderer = read("lib/rt64/src/render/rt64_framebuffer_renderer.cpp")
    pairing = read("lib/rt64/src/hle/rt64_game_frame.cpp")
    producer = read("RecompiledFuncsPoint0/funcs_5.c")
    return {
        "native_sun_uv_producer": without_trial_hooks(root, region(producer,
            "RECOMP_FUNC void func_8008D94C(", "\n;}")),
        "dp_r3_pairing": region(pairing,
            "                // THE DP SUN PARK TRANSIT (DPSUN R1).",
            "                // Continuity on the rect centre"),
        "dp_r3_suppression": region(renderer,
            "                // WR64 PARKED-SUN SUPPRESSION (Dolphin Park).",
            "                wr64HudCensusRecord("),
        "frame_edge_snap": region(renderer,
            "    RT64::FixedRect wr64SnapRectToScissor(", "\n}\n"),
        "warmup_subpixels_and_rect_snap": region(renderer,
            "                            // Use the same mapping for every authenticated message",
            "                            const bool coversScissorWidth"),
    }


if __name__ == "__main__":
    folder = Path(__file__).resolve().parent
    root = Path(sys.argv[1]).resolve()
    metadata = json.loads((folder / "capture_metadata.json").read_text())
    fixture = folder / "capture.csv"
    assert hashlib.sha256(fixture.read_bytes()).hexdigest() == metadata["fixture_sha256"], \
        "Compact capture bytes changed without updating provenance"
    for name, content in preserved_regions(root).items():
        actual = hashlib.sha256(content.encode()).hexdigest()
        assert actual == metadata["preserved_source_sha256_lf"][name], \
            f"Existing {name} changed; this presentation fix must preserve it"
    print("PASS: compact capture and native UV / R3 / frame-edge paths preserved")
