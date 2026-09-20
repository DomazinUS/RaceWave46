"""Validate the unchanged private native archive before replay; never copy it."""
import hashlib
from pathlib import Path
import subprocess
import sys

executable, capture = sys.argv[1:3]
assert hashlib.sha256(Path(capture).read_bytes()).hexdigest() == (
    '08ee4482e164740514b61a5d917e115f53aae65f6e48c4597f869f1ac26fd104')
raise SystemExit(subprocess.call([executable, capture]))
