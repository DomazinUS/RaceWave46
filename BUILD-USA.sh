#!/usr/bin/env bash
# Linux counterpart of BUILD-USA.ps1. See BUILDING.md.
set -euo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
rom=''
n64recomp=''
rsprecomp=''
python="${PYTHON:-python3}"
build_directory="$root/build"
jobs="$(nproc 2>/dev/null || echo 8)"
vulkan_dxc=''
dxc_directory=''
librashader=''
bundle_librashader=1
configure_only=0

usage() {
    cat <<'EOF'
Usage: BUILD-USA.sh [options]

  --rom FILE              Unmodified USA Rev 1 ROM (.z64). Optional once the
                          verified generated code exists.
  --n64recomp FILE        N64Recomp executable (default: build-tools/N64Recomp,
                          built from lib/N64ModernRuntime/N64Recomp if missing)
  --rsprecomp FILE        RSPRecomp executable (default: build-tools/RSPRecomp)
  --python FILE           Python 3.11 or newer (default: python3)
  --build-dir DIR         Output directory (default: build)
  --jobs N                Parallel build jobs (default: all processors)
  --vulkan-dxc FILE       Offline DXC 1.9.2607 bin/dxc for the WR64 Vulkan shaders
  --dxc-dir DIR           Offline DXC 1.8.2502 bin directory (with ../lib)
  --librashader FILE      Prebuilt librashader 0.12.0 librashader.so to bundle
                          (default: build it with tools/build_librashader.sh
                          when cargo is available)
  --no-librashader        Do not bundle librashader
  --configure-only        Configure without building

CC and CXX select the compiler; Clang is used when available.
EOF
}

while [ $# -gt 0 ]; do
    case "$1" in
        --rom) rom="$2"; shift 2 ;;
        --n64recomp) n64recomp="$2"; shift 2 ;;
        --rsprecomp) rsprecomp="$2"; shift 2 ;;
        --python) python="$2"; shift 2 ;;
        --build-dir) build_directory="$2"; shift 2 ;;
        --jobs) jobs="$2"; shift 2 ;;
        --vulkan-dxc) vulkan_dxc="$2"; shift 2 ;;
        --dxc-dir) dxc_directory="$2"; shift 2 ;;
        --librashader) librashader="$2"; shift 2 ;;
        --no-librashader) bundle_librashader=0; shift ;;
        --configure-only) configure_only=1; shift ;;
        -h|--help) usage; exit 0 ;;
        *) echo "Unknown option: $1" >&2; usage >&2; exit 2 ;;
    esac
done

if [ -z "${CC:-}" ] && command -v clang >/dev/null 2>&1; then export CC=clang; fi
if [ -z "${CXX:-}" ] && command -v clang++ >/dev/null 2>&1; then export CXX=clang++; fi

"$python" -c 'import sys; sys.exit(sys.version_info < (3, 11))' ||
    { echo 'Python 3.11 or newer is required.' >&2; exit 1; }

if [ -n "$rom" ]; then
    if [ -z "$n64recomp" ] || [ -z "$rsprecomp" ]; then
        tools="$root/build-tools"
        if [ ! -x "$tools/N64Recomp" ] || [ ! -x "$tools/RSPRecomp" ]; then
            cmake -S "$root/lib/N64ModernRuntime/N64Recomp" -B "$tools" -G Ninja -DCMAKE_BUILD_TYPE=Release
            cmake --build "$tools" --target N64RecompCLI RSPRecomp --parallel "$jobs"
        fi
        n64recomp="${n64recomp:-$tools/N64Recomp}"
        rsprecomp="${rsprecomp:-$tools/RSPRecomp}"
    fi
    "$python" "$root/tools/generate_code.py" --rom "$rom" --n64recomp "$n64recomp" --rsprecomp "$rsprecomp" ||
        { echo 'Code generation is required. See BUILDING.md.' >&2; exit 1; }
else
    "$python" "$root/tools/generate_code.py" --verify ||
        { echo 'Code generation is required. See BUILDING.md.' >&2; exit 1; }
fi

if [ "$bundle_librashader" -eq 1 ] && [ -z "$librashader" ]; then
    librashader="$root/build-tools/librashader-0.12.0/librashader.so"
    if [ ! -f "$librashader" ]; then
        if command -v cargo >/dev/null 2>&1; then
            "$root/tools/build_librashader.sh" --output "$librashader" --jobs "$jobs" || {
                echo 'librashader could not be built; building without it (see BUILDING.md).' >&2
                librashader=''
            }
        else
            echo 'cargo was not found; building without librashader (see BUILDING.md).' >&2
            librashader=''
        fi
    fi
fi

arguments=(-S "$root" -B "$build_directory" -G Ninja
    -DCMAKE_BUILD_TYPE=Release -DWR64_ENABLE_RT64=ON -DWR64_ENABLE_FRONTEND=ON
    -DWR64_ENABLE_DIAGNOSTICS=OFF "-DPython3_EXECUTABLE=$(command -v "$python")")
if [ -n "$vulkan_dxc" ]; then arguments+=("-DRT64_WR64_VULKAN_DXC=$(realpath "$vulkan_dxc")"); fi
if [ -n "$dxc_directory" ]; then arguments+=("-DWR64_DXC_TOOLCHAIN_DIRECTORY=$(realpath "$dxc_directory")"); fi
if [ "$bundle_librashader" -eq 0 ]; then
    arguments+=(-DWR64_BUNDLE_LIBRASHADER=OFF)
else
    arguments+=(-DWR64_BUNDLE_LIBRASHADER=ON "-DWR64_LIBRASHADER_LIBRARY=${librashader:+$(realpath "$librashader")}")
fi

cmake "${arguments[@]}"
if [ "$configure_only" -eq 0 ]; then
    cmake --build "$build_directory" --target WaveRace64Recompiled --parallel "$jobs"
    echo "Built: $build_directory/WaveRace64Recompiled"
fi
