"""Verify automatic recording persistence across genuinely separate OS processes."""
import pathlib
import subprocess
import sys
import tempfile


def main():
    executable = pathlib.Path(sys.argv[1]).resolve(strict=True)
    parent = pathlib.Path(sys.argv[2]).resolve()
    parent.mkdir(parents=True, exist_ok=True)
    root = pathlib.Path(tempfile.mkdtemp(prefix="ghost-autosave-", dir=parent))
    print(f"Isolated automatic ghost test data: {root}", flush=True)
    subprocess.run([str(executable), "--invariants", str(root / "invariants")], check=True)
    base = root / "process-restart" / "profile.eep"
    subprocess.run([str(executable), "--write", str(base)], check=True)
    subprocess.run([str(executable), "--read", str(base)], check=True)
    print("Separate-process automatic save/load passed; no manual slot save/load calls.")


if __name__ == "__main__":
    main()
