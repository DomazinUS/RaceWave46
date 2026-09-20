#!/usr/bin/env python3
"""Verify the one ROM revision supported by the initial recompilation."""

from __future__ import annotations

import argparse
import hashlib
from pathlib import Path


EXPECTED_SIZE = 8_388_608
EXPECTED_SHA1 = "508dfc2d4caa42b6f6de5263d0aed5e44ac7966a"
EXPECTED_MAGIC = bytes.fromhex("80371240")
EXPECTED_TITLE = b"WAVE RACE 64"
EXPECTED_GAME_CODE = b"NWRE"
EXPECTED_REVISION = 1


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("rom", type=Path)
    args = parser.parse_args()

    rom = args.rom.read_bytes()
    sha1 = hashlib.sha1(rom).hexdigest()
    checks = {
        "size": len(rom) == EXPECTED_SIZE,
        "sha1": sha1 == EXPECTED_SHA1,
        "byte order": rom[:4] == EXPECTED_MAGIC,
        "title": rom[0x20:0x34].rstrip(b"\0 ") == EXPECTED_TITLE,
        "game code": rom[0x3B:0x3F] == EXPECTED_GAME_CODE,
        "revision": rom[0x3F] == EXPECTED_REVISION,
    }

    for label, passed in checks.items():
        print(f"{label:10}: {'ok' if passed else 'FAILED'}")
    print(f"sha1      : {sha1}")
    return 0 if all(checks.values()) else 1


if __name__ == "__main__":
    raise SystemExit(main())
