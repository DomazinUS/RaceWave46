"""Build isolated integration fixtures; never modify the source texture pack."""
import argparse
import json
import pathlib
import zipfile

parser = argparse.ArgumentParser()
parser.add_argument("source", type=pathlib.Path)
parser.add_argument("output", type=pathlib.Path)
parser.add_argument("reference", type=pathlib.Path)
args = parser.parse_args()
args.output.mkdir(parents=True, exist_ok=True)
configuration = {"autoPath": "rt64", "configurationVersion": 3, "hashVersion": 5,
                 "defaultOperation": "preload", "defaultShift": "half", "wr64DolphinCompatible": True}
files = sorted(args.source.rglob("*.dds"))
assert len(files) == 2266
with zipfile.ZipFile(args.output / "all-dds-no-native-mappings.rtz", "w", zipfile.ZIP_DEFLATED) as archive:
    archive.writestr("rt64.json", json.dumps({"configuration": configuration, "textures": []}))
    for file in files:
        archive.write(file, file.relative_to(args.source).as_posix())

with zipfile.ZipFile(args.reference) as archive:
    reference = json.loads(archive.read("rt64.json"))
    entry = reference["textures"][0]
    payload = archive.read(entry["path"])
    for name, dynamic in [("static-override", False), ("same-fs-static-override", True)]:
        directory = args.output / name
        directory.mkdir(exist_ok=True)
        config = dict(configuration, wr64DolphinCompatible=dynamic)
        mapping = {"hashes": entry["hashes"], "path": "fixture-override.dds", "shift": "none"}
        (directory / "rt64.json").write_text(json.dumps({"configuration": config, "textures": [mapping]}))
        (directory / "fixture-override.dds").write_bytes(payload)
        if dynamic:
            (directory / entry["path"]).write_bytes(payload)
print("Prepared full 2266-DDS archive with zero native mappings and isolated override fixtures.")
