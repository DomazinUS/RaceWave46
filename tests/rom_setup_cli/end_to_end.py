"""End-to-end check of --check-rom and --import-rom against a built game."""

import argparse
from pathlib import Path
import subprocess
import sys
import tempfile


def run(game, profile, *arguments):
    result = subprocess.run([str(game), '--runtime-dir', str(profile), *arguments],
                            capture_output=True, text=True, timeout=120)
    lines = [line for line in result.stdout.splitlines() if line.startswith('status=')]
    if len(lines) != 1:
        raise AssertionError(f'expected one status line, got {result.stdout!r}')
    return result.returncode, lines[0][len('status='):]


def expect(actual, expected, label):
    if actual != expected:
        raise AssertionError(f'{label}: expected {expected}, got {actual}')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--game', type=Path, required=True)
    parser.add_argument('--rom', type=Path, required=True)
    args = parser.parse_args()
    rom = args.rom.read_bytes()
    with tempfile.TemporaryDirectory(prefix='racewave46-rom-setup-') as temp:
        temp = Path(temp)
        swapped = bytearray(rom)
        swapped[0::2], swapped[1::2] = rom[1::2], rom[0::2]
        (temp / 'swapped.v64').write_bytes(swapped)
        (temp / 'junk.bin').write_bytes(b'\0' * 4096)
        (temp / 'truncated.z64').write_bytes(rom[:0x100000])

        profile = temp / 'profile'
        expect(run(args.game, profile, '--check-rom'), (1, 'missing'), 'empty profile')
        expect(run(args.game, profile, '--import-rom', temp / 'absent.z64'), (1, 'failed-to-open'), 'absent file')
        expect(run(args.game, profile, '--import-rom', temp / 'junk.bin'), (1, 'not-a-rom'), 'junk file')
        expect(run(args.game, profile, '--import-rom', temp / 'truncated.z64'), (1, 'incorrect-version'), 'truncated ROM')
        expect(run(args.game, profile, '--check-rom'), (1, 'missing'), 'profile after rejected imports')
        expect(run(args.game, profile, '--import-rom', args.rom), (0, 'good'), 'supplied ROM')
        expect(run(args.game, profile, '--check-rom'), (0, 'valid'), 'profile after import')

        swapped_profile = temp / 'swapped-profile'
        expect(run(args.game, swapped_profile, '--import-rom', temp / 'swapped.v64'), (0, 'good'), 'byte-swapped ROM')
        stored = sorted(p.name for p in swapped_profile.iterdir())
        expect((profile / stored[0]).read_bytes() == (swapped_profile / stored[0]).read_bytes(), True,
               'byte order normalisation')
    print('ROM setup end-to-end checks passed')


if __name__ == '__main__':
    try:
        main()
    except AssertionError as error:
        sys.exit(str(error))
