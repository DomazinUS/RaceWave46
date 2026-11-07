#!/usr/bin/env bash
# Builds and installs the RaceWave46 Flatpak for the current user from this
# source tree and your own ROM. See BUILDING.md.
set -euo pipefail

here="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
root="$(cd "$here/../../.." && pwd)"
manifest="$here/io.github.DomazinUS.RaceWave46.yml"
rom=''
install=1
builder_arguments=()

usage() {
    cat <<'EOF'
Usage: packaging/linux/flatpak/build.sh --rom FILE [--no-install] [-- flatpak-builder options]

  --rom FILE      Your unmodified Wave Race 64 USA Rev 1 ROM (.z64)
  --no-install    Build only; do not install for the current user

The ROM is copied into the ignored .flatpak-input directory for the build and
is used only to generate code; it is not installed. The resulting Flatpak
contains code generated from your ROM, so do not redistribute it.
EOF
}

while [ $# -gt 0 ]; do
    case "$1" in
        --rom) rom="$2"; shift 2 ;;
        --no-install) install=0; shift ;;
        -h|--help) usage; exit 0 ;;
        --) shift; builder_arguments+=("$@"); break ;;
        *) echo "Unknown option: $1" >&2; usage >&2; exit 2 ;;
    esac
done
if [ -z "$rom" ]; then usage >&2; exit 2; fi

python3 "$root/tools/verify_rom.py" "$rom" ||
    { echo 'The ROM must be an unmodified, big-endian USA Rev 1 ROM (.z64).' >&2; exit 1; }

input="$root/.flatpak-input"
mkdir -p "$input"
trap 'rm -f "$input/rom.z64"' EXIT
install -m 600 "$rom" "$input/rom.z64"

for ref in org.freedesktop.Sdk//26.08 org.freedesktop.Platform//26.08 \
    org.freedesktop.Sdk.Extension.rust-stable//26.08 org.freedesktop.Sdk.Extension.llvm22//26.08; do
    flatpak info "$ref" >/dev/null 2>&1 ||
        flatpak install --user -y --noninteractive flathub "$ref"
done

arguments=(--force-clean --state-dir="$root/.flatpak-builder" "${builder_arguments[@]}")
if [ "$install" -eq 1 ]; then arguments+=(--user --install); fi
flatpak-builder "${arguments[@]}" "$root/build-flatpak" "$manifest"
