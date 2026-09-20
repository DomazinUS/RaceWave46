"""Maintainer-only extraction; normal CTest needs only the compact fixture."""
import csv
import hashlib
import json
from pathlib import Path
import sys
from verify_preservation import preserved_regions

root = Path(sys.argv[1]).resolve()
source = Path(sys.argv[2]).resolve()
folder = Path(__file__).resolve().parent
scenarios = {
    **{sf: "opening" for sf in (190, 193, 194, 195)},
    352: "away_from_edge",
    260: "opening_cut", 261: "opening_park",
    **{sf: "nominal_exit" for sf in range(699, 709)},
    733: "entry_park", 734: "entry",
    **{sf: "cutoff_exit" for sf in range(750, 761)},
    819: "settled_park",
}
fields = ["scenario", "scope", "output", "submission", "weight", "hash",
          "raw_uly", "raw_lry", "chosen_uly", "chosen_lry", "viewport_top",
          "viewport_height", "u1", "v1", "u2", "v2", "target"]
selected = []
flare_seen = set()
source_rows = 0
for row in csv.DictReader(source.open(newline="")):
    source_rows += 1
    sf = int(row["submission"])
    if sf not in scenarios or row["event"] != "issued" or \
            row["target_width"] != "1908" or row["target_height"] != "1080":
        continue
    if row["hash"] == "B82E909F647A31AD":
        if sf in flare_seen:
            continue
        flare_seen.add(sf)
    elif row["hash"] != "79185A8F164D1366":
        continue
    selected.append({
        **{key: row[key] for key in fields if key in row},
        "scenario": scenarios[sf],
        "scope": "Opening" if sf < 600 else "Gameplay",
        "target": "1908x1080",
    })
fixture = folder / "capture.csv"
with fixture.open("w", newline="", encoding="utf-8") as stream:
    writer = csv.DictWriter(stream, fieldnames=fields, lineterminator="\n")
    writer.writeheader()
    writer.writerows(selected)
metadata = {
    "source_name": source.name,
    "source_sha256": hashlib.sha256(source.read_bytes()).hexdigest(),
    "source_size_bytes": source.stat().st_size,
    "source_rows": source_rows,
    "selection": "Final issued rows at 1908x1080: every DP disk output in listed submissions, plus the first shared flare per submission. Native-size preparation excluded.",
    "scope_annotation": "Opening/Gameplay are test inputs based on the selected scene groups; the CSV trace does not contain a game-phase field.",
    "submissions": sorted(scenarios),
    "fixture_rows": len(selected),
    "fixture_sha256": hashlib.sha256(fixture.read_bytes()).hexdigest(),
    "preservation_normalization": "UTF-8 text with CRLF normalized to LF; all other source bytes, including whitespace and comments, are retained.",
    "preserved_source_sha256_lf": {
        name: hashlib.sha256(content.encode()).hexdigest()
        for name, content in preserved_regions(root).items()
    },
}
(folder / "capture_metadata.json").write_text(json.dumps(metadata, indent=2) + "\n")
print(f"Wrote {len(selected)} compact capture rows ({fixture.stat().st_size} bytes)")
