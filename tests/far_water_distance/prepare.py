"""Prepare real native water and verbatim renderer functions for a CPU replay."""
import hashlib
import importlib.util
import json
from pathlib import Path
import sys

root = Path(__file__).resolve().parents[2]
spec = importlib.util.spec_from_file_location("water_prepare", root / "tests/water_dense_recovery/prepare.py")
shared = importlib.util.module_from_spec(spec)
spec.loader.exec_module(shared)

if __name__ == "__main__":
    # Reuse the native trace parser and exact production fragment boundaries.
    previous_index = sys.argv.index("--previous")
    previous = Path(sys.argv[previous_index + 1])
    del sys.argv[previous_index:previous_index + 2]
    shared.main()
    output = Path(sys.argv[sys.argv.index("--output") + 1])
    assert "--baseline" in sys.argv, "An explicit pre-feature baseline is required"
    baseline = Path(sys.argv[sys.argv.index("--baseline") + 1])
    (output / "water_previous.inc").write_text(shared.fragment(previous.read_text()))
    previous_header = previous.with_name("lib__rt64__src__common__rt64_wr64_far_water_distance.h")
    (output / "water_previous_header.inc").write_text(previous_header.read_text().replace("namespace RT64 {", "namespace previous_distance {", 1))
    harness = (root / "tests/water_dense_recovery/recovery.cpp").read_text()
    harness = harness[:harness.index("int main(")]
    assert harness.count("uint32_t wr64FarWaterDistanceMode = 0;") == 2
    (output / "water_fixture.inc").write_text(harness)
    state = (root / "lib/rt64/src/hle/rt64_state.cpp").read_text()
    begin = state.index("        // Capture both native camera selectors before presentation remaps either view.")
    end = state.index("        uint16_t wr64MenuLayout", begin)
    capture = state[begin:end]
    assert "workload.wr64FarWaterDistanceViewScope[view] = wr64FarWaterDistanceScope(" in capture
    (output / "water_capture.inc").write_text(capture)
    workload = (root / "lib/rt64/src/hle/rt64_workload.cpp").read_text()
    assert "        wr64FarWaterDistanceMode = 0;" in workload
    assert "        drawData.wr64FarWaterDistanceMode = 0;" in workload
    manifest = json.loads((output / "manifest.json").read_text())
    manifest["baseline"] = str(baseline.resolve())
    manifest["baseline_sha256"] = hashlib.sha256(baseline.read_bytes()).hexdigest()
    manifest["previous"] = str(previous.resolve())
    manifest["previous_sha256"] = hashlib.sha256(previous.read_bytes()).hexdigest()
    manifest["previous_header_sha256"] = hashlib.sha256(previous_header.read_bytes()).hexdigest()
    manifest["current_header_sha256"] = hashlib.sha256((root / "lib/rt64/src/common/rt64_wr64_far_water_distance.h").read_bytes()).hexdigest()
    manifest["state_sha256"] = hashlib.sha256((root / "lib/rt64/src/hle/rt64_state.cpp").read_bytes()).hexdigest()
    (output / "manifest.json").write_text(json.dumps(manifest, indent=2))
