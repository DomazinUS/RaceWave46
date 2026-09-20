"""Run offline executables with WR64 variables absent, preserving the caller."""
import argparse
import os
from pathlib import Path
import subprocess
import sys
import tempfile

parser = argparse.ArgumentParser()
group = parser.add_mutually_exclusive_group(required=True)
group.add_argument("--single", type=Path)
group.add_argument("--root", type=Path)
args = parser.parse_args()
environment = {key: value for key, value in os.environ.items() if not key.upper().startswith("WR64_")}
assert not any(key.upper().startswith("WR64_") for key in environment)


def run(executable, *arguments):
    executable = executable.resolve(strict=True)
    print(f"No-override offline test: {executable.name}", flush=True)
    subprocess.run([str(executable), *map(str, arguments)], cwd=executable.parent,
                   env=environment, check=True)


if args.single:
    run(args.single)
else:
    root = args.root.resolve(strict=True)
    build = root / "build"
    targets = (
        ("game_rumble", "wr64_game_rumble_test"),
        ("game_rumble", "wr64_ultrawide_test"),
        ("graphics_config", "wr64_graphics_config_test"),
        ("watercraft_preview", "wr64_watercraft_preview_test"),
        ("course_preview", "wr64_course_preview_test"),
        ("championship_preview", "wr64_championship_preview_test"),
    )
    suffix = ".exe" if os.name == "nt" else ""
    for suite, executable in targets:
        run(build / (suite + "-tests") / (executable + suffix))
    ghost = build / "ghost-tests" / ("wr64_ghost_autosave_test" + suffix)
    # The existing runner verifies actual writer termination and fresh reader
    # processes; it never calls manual slot-save/load or a graphical executable.
    ghost.resolve(strict=True)
    isolated = Path(tempfile.mkdtemp(prefix="release-autosave-", dir=build / "release_defaults-tests"))
    subprocess.run([sys.executable, str(root / "tests/ghost/run_autosave_test.py"),
                    str(ghost), str(isolated)], env=environment, check=True)
    print("All reused default-enhancement and persistent-ghost contracts passed.", flush=True)
