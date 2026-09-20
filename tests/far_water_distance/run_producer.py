"""Validate private inputs; never copy ROM/RAM into build artifacts."""
from pathlib import Path
import hashlib
import subprocess
import sys

exe, rom, capture = map(Path, sys.argv[1:4])
assert hashlib.sha256(rom.read_bytes()).hexdigest() == 'f35d2423ebcb86eaf86fa935b613c7532b123a7bc50fb74996984c3b02fc3999', 'Expected original USA Rev1 ROM'
assert hashlib.sha256(capture.read_bytes()).hexdigest() == '89c56cd26e8227a150b6e7a460519e981d7fdb94d6c78db4783e300b1712aa09', 'Expected verified native RAM input'
raise SystemExit(subprocess.call([str(exe), str(rom), str(capture)]))
