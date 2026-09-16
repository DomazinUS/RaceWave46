#!/usr/bin/env python3
"""Generate N64Recomp TOML symbols from LLONSIT's Wave Race metadata.

The upstream project does not publish an N64Recomp symbol dump. This tool
combines its Splat code-section layout, linker symbol files, n64sym database,
and address-bearing function names in the source tree. Function sizes are
inferred from the next known function boundary in the same ROM section.
"""

from __future__ import annotations

import argparse
import re
import struct
import tomllib
from dataclasses import dataclass, field
from pathlib import Path


SEGMENT_START_RE = re.compile(r"^  - name:\s*([^#\s]+)")
HEX_FIELD_RE = re.compile(r"^    (start|vram):\s*(0x[0-9A-Fa-f]+)")
TYPE_RE = re.compile(r"^    type:\s*([^#\s]+)")
SUBSEGMENT_RE = re.compile(r"^\s+- \[(0x[0-9A-Fa-f]+),\s*([^,\]\s]+)")
ASSIGNMENT_RE = re.compile(
    r"^\s*([A-Za-z_][A-Za-z0-9_]*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;(?P<comment>.*)$"
)
N64SYM_RE = re.compile(r"^\s*([0-9A-Fa-f]{8})\s+([A-Za-z_][A-Za-z0-9_.]*)\s*$")
ADDRESS_NAME_RE = re.compile(
    r"\b((?:func|recomp)_(?P<qualifiers>(?:[A-Za-z0-9]+_)*)"
    r"(?P<address>[0-9A-Fa-f]{8}))\b"
)
SIZE_RE = re.compile(r"\bsize:\s*(0x[0-9A-Fa-f]+|\d+)")
SEGMENT_COMMENT_RE = re.compile(r"\bsegment:([A-Za-z0-9_]+)")

CODE_TYPES = {"c", "hasm", "asm"}
REJECTED_PREFIXES = (
    "D_", "B_", "R_", "g", "s", "jtbl_", "jlabel_", "dlabel_",
)
REJECTED_SUFFIXES = (
    "_ROM_START", "_ROM_END", "_VRAM", "_VRAM_END", "_TEXT_START",
    "_TEXT_END", "_DATA_START", "_DATA_END", "_BSS_START", "_BSS_END",
)


@dataclass
class Section:
    name: str
    rom: int
    vram: int
    size: int
    functions: dict[int, tuple[str, int | None]] = field(default_factory=dict)

    @property
    def end_vram(self) -> int:
        return self.vram + self.size


def parse_sections(config_path: Path) -> list[Section]:
    lines = config_path.read_text(encoding="utf-8").splitlines()
    raw: list[dict[str, object]] = []
    current: dict[str, object] | None = None

    for line in lines:
        segment_match = SEGMENT_START_RE.match(line)
        if segment_match:
            if current is not None:
                raw.append(current)
            current = {"name": segment_match.group(1), "subsegments": []}
            continue
        if current is None:
            continue
        field_match = HEX_FIELD_RE.match(line)
        if field_match:
            current[field_match.group(1)] = int(field_match.group(2), 16)
            continue
        type_match = TYPE_RE.match(line)
        if type_match:
            current["type"] = type_match.group(1)
            continue
        subsegment_match = SUBSEGMENT_RE.match(line)
        if subsegment_match:
            subsegments = current["subsegments"]
            assert isinstance(subsegments, list)
            subsegments.append((int(subsegment_match.group(1), 16), subsegment_match.group(2)))

    if current is not None:
        raw.append(current)

    sections: list[Section] = []
    for index, segment in enumerate(raw):
        if segment.get("type") != "code" or "start" not in segment or "vram" not in segment:
            continue
        subsegments = segment["subsegments"]
        assert isinstance(subsegments, list)
        code_parts = [(offset, kind) for offset, kind in subsegments if kind in CODE_TYPES]
        if not code_parts:
            continue
        start = int(segment["start"])
        first_code = code_parts[0][0]
        if first_code != start:
            start = first_code

        end = None
        began_code = False
        for offset, kind in subsegments:
            if offset < start:
                continue
            if kind in CODE_TYPES:
                began_code = True
            elif began_code:
                end = offset
                break
        if end is None:
            for later in raw[index + 1 :]:
                if "start" in later and int(later["start"]) > start:
                    end = int(later["start"])
                    break
        if end is None or end <= start:
            raise ValueError(f"Cannot determine text extent for {segment['name']}")

        vram = int(segment["vram"]) + (start - int(segment["start"]))
        sections.append(Section(str(segment["name"]), start, vram, end - start))

    return sections


def section_for_address(
    sections: list[Section], address: int, section_hint: str | None = None
) -> list[Section]:
    matches = [section for section in sections if section.vram <= address < section.end_vram]
    if section_hint:
        hinted = [section for section in matches if section.name == section_hint]
        if hinted:
            return hinted
    return matches if len(matches) == 1 else []


def name_score(name: str) -> tuple[int, int]:
    # Prefer descriptive names, then address-bearing generic names.
    generic = name.startswith(("func_", "recomp_"))
    return (0 if generic else 1, -len(name))


def add_function(section: Section, address: int, name: str, size: int | None = None) -> None:
    if address % 4 or not (section.vram <= address < section.end_vram):
        return
    existing = section.functions.get(address)
    if existing is None or name_score(name) > name_score(existing[0]):
        section.functions[address] = (name, size if size is not None else existing[1] if existing else None)
    elif existing[1] is None and size is not None:
        section.functions[address] = (existing[0], size)


def plausible_function(name: str) -> bool:
    return not name.startswith(REJECTED_PREFIXES) and not name.endswith(REJECTED_SUFFIXES)


def collect_functions(reference: Path, sections: list[Section]) -> None:
    linker_dir = reference / "linker_scripts" / "us" / "rev1"
    symbol_files = list(linker_dir.glob("*.txt")) + [reference / "files" / "symbol_addrs.txt"]
    for symbol_file in symbol_files:
        if not symbol_file.exists():
            continue
        for line in symbol_file.read_text(encoding="utf-8", errors="replace").splitlines():
            match = ASSIGNMENT_RE.match(line)
            if not match:
                continue
            name, value, comment = match.group(1), match.group(2), match.group("comment")
            if not plausible_function(name):
                continue
            address = int(value, 16)
            hint_match = SEGMENT_COMMENT_RE.search(comment)
            hint = hint_match.group(1) if hint_match else None
            prefix_match = re.match(r"func_(i\d+)_", name)
            if prefix_match:
                hint = f"ovl_{prefix_match.group(1)}"
            size_match = SIZE_RE.search(comment)
            size = int(size_match.group(1), 0) if size_match else None
            for section in section_for_address(sections, address, hint):
                add_function(section, address, name, size)

    n64sym = reference / "n64sym.txt"
    for line in n64sym.read_text(encoding="utf-8", errors="replace").splitlines():
        match = N64SYM_RE.match(line)
        if not match:
            continue
        address, name = int(match.group(1), 16), match.group(2).replace(".", "_")
        if not plausible_function(name):
            continue
        for section in section_for_address(sections, address):
            add_function(section, address, name)

    for source in (reference / "src").rglob("*"):
        if source.suffix not in {".c", ".h", ".s"}:
            continue
        text = source.read_text(encoding="utf-8", errors="replace")
        path_hint = None
        for part in source.parts:
            if re.fullmatch(r"ovl_i\d+", part):
                path_hint = part
                break
        for match in ADDRESS_NAME_RE.finditer(text):
            name = match.group(1)
            address = int(match.group("address"), 16)
            hint = path_hint
            qualifiers = match.group("qualifiers").rstrip("_").split("_")
            overlay_qualifier = next(
                (part for part in qualifiers if re.fullmatch(r"i\d+", part)), None
            )
            if overlay_qualifier:
                hint = f"ovl_{overlay_qualifier}"
            if hint is None:
                # Three small root-level segments use names such as
                # func_1C3780_802C5800. Match that qualifier to the section's
                # ROM start, which disambiguates their shared overlay VRAM.
                for section in sections:
                    if f"{section.rom:X}" in qualifiers:
                        hint = section.name
                        break
            for section in section_for_address(sections, address, hint):
                add_function(section, address, name)

    entry = next(section for section in sections if section.name == "entry")
    add_function(entry, 0x80046800, "recomp_entrypoint", entry.size)


def discover_direct_calls(rom_path: Path, sections: list[Section]) -> int:
    """Add function boundaries that are direct JAL targets in executable code."""
    rom = rom_path.read_bytes()
    discovered = 0
    for caller_section in sections:
        section_bytes = rom[caller_section.rom : caller_section.rom + caller_section.size]
        for offset in range(0, len(section_bytes) - 3, 4):
            instruction = struct.unpack_from(">I", section_bytes, offset)[0]
            if instruction >> 26 != 0x03:  # jal
                continue
            pc = caller_section.vram + offset
            target = ((pc + 4) & 0xF0000000) | ((instruction & 0x03FFFFFF) << 2)
            matches = [section for section in sections if section.vram <= target < section.end_vram]
            if len(matches) > 1:
                matches = [section for section in matches if section is caller_section]
            if len(matches) != 1:
                continue
            target_section = matches[0]
            if target in target_section.functions:
                continue
            qualifier = ""
            if target_section.name.startswith("ovl_i"):
                qualifier = target_section.name.removeprefix("ovl_") + "_"
            elif target_section.name in {"segment_1B1FB0", "seg_1C3780", "seg_1C3D00"}:
                qualifier = f"{target_section.rom:X}_"
            add_function(target_section, target, f"func_{qualifier}{target:08X}")
            discovered += 1
    return discovered


def apply_overrides(path: Path, sections: list[Section]) -> None:
    if not path.exists():
        return
    data = tomllib.loads(path.read_text(encoding="utf-8"))
    sections_by_name = {section.name: section for section in sections}
    for removal in data.get("function_remove", []):
        section = sections_by_name[removal["section"]]
        address = int(removal["vram"])
        if section.functions.pop(address, None) is None:
            raise ValueError(f"Cannot remove unknown function at 0x{address:08X}")
    for override in data.get("function", []):
        section = sections_by_name[override["section"]]
        add_function(
            section,
            int(override["vram"]),
            str(override["name"]),
            int(override["size"]) if "size" in override else None,
        )
    for override in data.get("function_span", []):
        section = sections_by_name[override["section"]]
        address = int(override["vram"])
        existing = section.functions.get(address)
        if existing is None:
            raise ValueError(f"Cannot size unknown function at 0x{address:08X}")
        section.functions[address] = (existing[0], int(override["size"]))


def validate_and_write(sections: list[Section], output: Path) -> tuple[int, list[str]]:
    warnings: list[str] = []
    count = 0
    output.parent.mkdir(parents=True, exist_ok=True)
    with output.open("w", encoding="utf-8", newline="\n") as handle:
        handle.write("# Generated by tools/generate_symbols.py; do not edit by hand.\n")
        handle.write("# Source: LLONSIT/Wave-Race-64 US Rev 1 metadata.\n")
        for section in sections:
            ordered = sorted(section.functions.items())
            if not ordered:
                warnings.append(f"{section.name}: no functions found")
                continue
            handle.write("\n[[section]]\n")
            handle.write(f'name = "{section.name}"\n')
            handle.write(f"rom = 0x{section.rom:08X}\n")
            handle.write(f"vram = 0x{section.vram:08X}\n")
            handle.write(f"size = 0x{section.size:X}\n\n")
            handle.write("functions = [\n")
            for index, (address, (name, explicit_size)) in enumerate(ordered):
                next_address = ordered[index + 1][0] if index + 1 < len(ordered) else section.end_vram
                size = explicit_size if explicit_size is not None else next_address - address
                if size <= 0 or size % 4:
                    warnings.append(f"{section.name}:{name}: suspicious size 0x{size:X}")
                    continue
                handle.write(
                    f'    {{ name = "{name}", vram = 0x{address:08X}, size = 0x{size:X} }},\n'
                )
                count += 1
            handle.write("]\n")
    return count, warnings


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("reference", type=Path, help="LLONSIT/Wave-Race-64 checkout")
    parser.add_argument(
        "--rom", type=Path, help="optional canonical ROM used to discover direct JAL targets"
    )
    parser.add_argument(
        "--output", type=Path, default=Path("symbols/waverace64.us.rev1.toml")
    )
    parser.add_argument(
        "--overrides", type=Path, default=Path("config/symbol_overrides.toml")
    )
    args = parser.parse_args()

    config = args.reference / "waverace64.us.rev1.yaml"
    sections = parse_sections(config)
    collect_functions(args.reference, sections)
    discovered = discover_direct_calls(args.rom, sections) if args.rom else 0
    apply_overrides(args.overrides, sections)
    count, warnings = validate_and_write(sections, args.output)
    print(f"wrote {count} functions across {len(sections)} code sections to {args.output}")
    if args.rom:
        print(f"discovered {discovered} additional direct-call targets from the ROM")
    for warning in warnings:
        print(f"warning: {warning}")
    return 0 if count else 1


if __name__ == "__main__":
    raise SystemExit(main())
