#!/usr/bin/env bash
# Builds the pinned librashader runtime for Linux with only the Vulkan runtime,
# which is the one the game uses there. See BUILDING.md.
set -euo pipefail

version='0.12.0'
archive_sha256='4bf8cf2489d00848dcabbf2163204093776082da4217d5a5db45e4cbf335cedf'
root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
work="$root/build-tools/librashader-$version"
source_directory=''
output="$work/librashader.so"
jobs="$(nproc 2>/dev/null || echo 8)"

usage() {
    cat <<'EOF'
Usage: tools/build_librashader.sh [options]

  --source DIR    Use an extracted librashader-v0.12.0 source tree (with its
                  dependencies vendored for an offline build) instead of
                  downloading the pinned release archive
  --output FILE   Where to write librashader.so
                  (default: build-tools/librashader-0.12.0/librashader.so)
  --jobs N        Parallel cargo jobs (default: all processors)

Requires cargo (Rust 1.88 or newer) and a C/C++ compiler.
EOF
}

while [ $# -gt 0 ]; do
    case "$1" in
        --source) source_directory="$2"; shift 2 ;;
        --output) output="$2"; shift 2 ;;
        --jobs) jobs="$2"; shift 2 ;;
        -h|--help) usage; exit 0 ;;
        *) echo "Unknown option: $1" >&2; usage >&2; exit 2 ;;
    esac
done

command -v cargo >/dev/null 2>&1 || { echo 'cargo is required to build librashader.' >&2; exit 1; }

if [ -z "$source_directory" ]; then
    archive="$work/librashader-v$version.tar.gz"
    mkdir -p "$work"
    if [ ! -f "$archive" ] || ! echo "$archive_sha256  $archive" | sha256sum --check --status; then
        curl --fail --location --silent --show-error --output "$archive.part" \
            "https://github.com/SnowflakePowered/librashader/archive/refs/tags/librashader-v$version.tar.gz"
        echo "$archive_sha256  $archive.part" | sha256sum --check --status ||
            { echo 'The librashader source archive does not match the pinned release.' >&2; rm -f "$archive.part"; exit 1; }
        mv "$archive.part" "$archive"
    fi
    source_directory="$work/source"
    rm -rf "$source_directory"
    mkdir -p "$source_directory"
    tar -xzf "$archive" -C "$source_directory" --strip-components=1
fi

cd "$source_directory"
cargo build --locked --jobs "$jobs" --package librashader-capi --profile optimized \
    --no-default-features --features runtime-vulkan
install -Dm755 target/optimized/liblibrashader_capi.so "$output"
echo "Built: $output"
