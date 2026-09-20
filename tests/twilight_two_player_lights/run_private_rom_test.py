"""Audit native light assets in memory, then run the native CPU fixture."""
from pathlib import Path
import hashlib
import struct
import subprocess
import sys

exe, rom_path = map(Path, sys.argv[1:3])
rom = rom_path.read_bytes()
assert hashlib.sha256(rom).hexdigest() == 'f35d2423ebcb86eaf86fa935b613c7532b123a7bc50fb74996984c3b02fc3999'
# SysMain loads both raw contiguous sections, 0xF6090..0xFE320 and
# 0xFE320..0x165C00, regardless of player count. Segment 1 addresses the whole.
bank = rom[0xF6090:0x165C00]
roots = [0x0102BF48, 0x0102BFD8, 0x0102C798, 0x0102C828]
seen, vertices, textures = set(), set(), set()

def resident(address, size):
    assert address >> 24 == 1
    offset = address & 0xFFFFFF
    assert offset + size <= len(bank)
    return offset

def walk(address):
    if address in seen:
        return
    seen.add(address)
    p = resident(address, 8)
    image = None
    for _ in range(128):
        a, b = struct.unpack_from('>II', bank, p)
        op = a >> 24
        if op == 0xB8:
            return
        if op == 0x06:
            walk(b)
            if a & 0x10000:
                return
        elif op == 0x04:
            # Native Fast3D DMA packs vertex count above the byte-length field.
            n = (a & 0x1FF) + 1
            assert n % 16 == 0 and n > 0
            assert n // 16 == (a >> 9) & 0x7F
            start = resident(b, n)
            vertices.add((start, n))
        elif op == 0xFD:
            resident(b, 1)
            textures.add(b)
            image = (b, (a >> 19) & 3)
        elif op == 0xF3:
            assert image is not None and image[1] == 2
            resident(image[0], (((b >> 12) & 0xFFF) + 1) * 2)
        p += 8
        assert p + 8 <= len(bank)
    raise AssertionError('unterminated light display list')

for root in roots:
    walk(root)
assert len(seen) == 8 and vertices and textures
ys = [struct.unpack_from('>h', bank, p + 2)[0]
      for start, length in vertices for p in range(start, start + length, 16)]
assert max(ys) == 500 and min(ys) == -250, 'native column and submerged base dimensions changed'
print(f'PASS private ROM: {len(seen)} resident light lists, {len(vertices)} vertex spans, '
      f'{len(textures)} texture references; Y range {min(ys)}..{max(ys)}', flush=True)
raise SystemExit(subprocess.call([str(exe), str(rom_path)]))
