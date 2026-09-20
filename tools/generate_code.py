"""Generate the release's CPU and RSP sources from a supplied ROM."""

import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import tempfile

from finalize_generated import canonical_tokens, finalize


ROOT = Path(__file__).resolve().parents[1]
RECIPE = ROOT / 'config/generated-code.json'


def digest(data):
    return hashlib.sha256(data).hexdigest()


def apply_ips(rom, patch):
    if patch[:5] != b'PATCH':
        raise ValueError('Invalid IPS header')
    data = bytearray(rom)
    pos = 5
    while patch[pos:pos + 3] != b'EOF':
        if pos + 5 > len(patch):
            raise ValueError('Truncated IPS record')
        offset = int.from_bytes(patch[pos:pos + 3], 'big')
        length = int.from_bytes(patch[pos + 3:pos + 5], 'big')
        pos += 5
        if length:
            replacement = patch[pos:pos + length]
            if len(replacement) != length:
                raise ValueError('Truncated IPS payload')
            pos += length
        else:
            if pos + 3 > len(patch):
                raise ValueError('Truncated IPS repeat')
            length = int.from_bytes(patch[pos:pos + 2], 'big')
            replacement = bytes([patch[pos + 2]]) * length
            pos += 3
        if offset + length > 16 * 1024 * 1024:
            raise ValueError('IPS output exceeds the supported ROM size')
        if offset + length > len(data):
            data.extend(bytes(offset + length - len(data)))
        data[offset:offset + length] = replacement
    if pos + 3 != len(patch):
        raise ValueError('Unexpected IPS trailer')
    return bytes(data)


def verify(directory, recipe):
    expected = recipe['outputs']
    actual = {p.relative_to(directory).as_posix()
              for folder in ('RecompiledFuncsPoint0', 'rsp')
              for p in (directory / folder).glob('*')
              if p.is_file() and p.suffix in ('.c', '.cpp', '.h', '.inl')}
    if actual != set(expected):
        raise ValueError('Generated files are missing or unexpected. Run tools/generate_code.py with your ROM and recompiler tools.')
    for name, checksum in expected.items():
        if digest(canonical_tokens((directory / name).read_text()).encode()) != checksum:
            raise ValueError(f'Generated code does not match this release: {name}')


def check_inputs(recipe):
    for name, checksum in recipe['inputs'].items():
        path = ROOT / name
        content = path.read_bytes() if path.suffix == '.ips' else path.read_text().encode()
        if digest(content) != checksum:
            raise ValueError(f'Generation input does not match this release: {name}')


def tool_path(value):
    path = shutil.which(value)
    if not path:
        raise ValueError(f'Recompiler not found: {value}')
    return str(Path(path).resolve())


def generate(rom_path, n64recomp, rsprecomp, destination, recipe):
    rom = rom_path.read_bytes()
    if digest(rom) != recipe['rom_sha256']:
        raise ValueError('Supply the unmodified, big-endian USA Rev 1 ROM (.z64).')
    n64recomp, rsprecomp = tool_path(n64recomp), tool_path(rsprecomp)
    patched = apply_ips(rom, (ROOT / 'data/waverace64-widescreen.ips').read_bytes())
    if digest(patched) != recipe['patched_rom_sha256']:
        raise ValueError('Patched ROM verification failed')
    # Inputs stay local and are discarded once generation completes.
    with tempfile.TemporaryDirectory(prefix='racewave46-generate-') as temp:
        work = Path(temp)
        (work / 'input.z64').write_bytes(patched)
        (work / 'RecompiledFuncsPoint0').mkdir()
        (work / 'rsp').mkdir()
        replacements = {
            '../Wave Race 64 - Kawasaki Jet Ski (USA) (Rev 1).z64': (work / 'input.z64').as_posix(),
            '../symbols/waverace64.us.rev1.toml': (ROOT / 'symbols/waverace64.us.rev1.toml').as_posix(),
            '../RecompiledFuncsPoint0': (work / 'RecompiledFuncsPoint0').as_posix(),
            '../rsp/aspMain.cpp': (work / 'rsp/aspMain.cpp').as_posix(),
        }
        for config, tool in [('us.rev1.toml', n64recomp), ('aspMain.us.rev1.toml', rsprecomp)]:
            text = (ROOT / 'config' / config).read_text()
            for old, new in replacements.items():
                text = text.replace(old, new)
            filename = work / config
            filename.write_text(text, newline='\n')
            result = subprocess.run([tool, str(filename)], cwd=work, capture_output=True, text=True)
            if result.returncode:
                raise RuntimeError(f'{Path(tool).name} failed:\n{result.stdout}\n{result.stderr}')
        finalize(work / 'RecompiledFuncsPoint0')
        verify(work, recipe)
        for name in recipe['outputs']:
            output = destination / name
            output.parent.mkdir(parents=True, exist_ok=True)
            pending = output.with_suffix(output.suffix + '.tmp')
            pending.write_bytes((work / name).read_bytes())
            os.replace(pending, output)
    verify(destination, recipe)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--rom', type=Path)
    parser.add_argument('--n64recomp', default='N64Recomp')
    parser.add_argument('--rsprecomp', default='RSPRecomp')
    parser.add_argument('--output-root', type=Path, default=ROOT)
    parser.add_argument('--verify', action='store_true')
    args = parser.parse_args()
    try:
        recipe = json.loads(RECIPE.read_text())
        check_inputs(recipe)
        if args.verify:
            verify(args.output_root.resolve(), recipe)
        else:
            if not args.rom:
                parser.error('--rom is required for generation')
            generate(args.rom.resolve(), args.n64recomp, args.rsprecomp, args.output_root.resolve(), recipe)
        print('Verified CPU and RSP generated code.')
    except (ValueError, OSError, RuntimeError) as error:
        parser.exit(1, f'{error}\n')


if __name__ == '__main__':
    main()
