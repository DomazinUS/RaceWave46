"""Validate the user's private input; do not save or redistribute any ROM bytes."""
from pathlib import Path
import hashlib
import subprocess
import sys

exe, rom = map(Path, sys.argv[1:3])
expected = 'f35d2423ebcb86eaf86fa935b613c7532b123a7bc50fb74996984c3b02fc3999'
assert hashlib.sha256(rom.read_bytes()).hexdigest() == expected, 'Expected unmodified USA Rev1 ROM'
raise SystemExit(subprocess.call([str(exe), str(rom)]))
