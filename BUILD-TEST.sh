#!/usr/bin/env bash
# Linux counterpart of BUILD-TEST.ps1: builds and runs one CMake test suite.
set -euo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
suite=''
build_directory=''
python="${PYTHON:-python3}"
usa_rom="${WR64_TEST_ROM:-}"
jobs=4
cmake_options=()

usage() {
    cat <<'EOF'
Usage: BUILD-TEST.sh --suite NAME [options] [-- extra CMake options]

  --suite NAME        Directory under tests/
  --build-dir DIR     Default: build/tests/NAME
  --python FILE       Python 3.11 or newer (default: python3)
  --usa-rom FILE      Unmodified USA Rev 1 ROM for suites that need it
                      (default: $WR64_TEST_ROM)
  --jobs N            Parallel build jobs (default: 4)
EOF
}

while [ $# -gt 0 ]; do
    case "$1" in
        --suite) suite="$2"; shift 2 ;;
        --build-dir) build_directory="$2"; shift 2 ;;
        --python) python="$2"; shift 2 ;;
        --usa-rom) usa_rom="$2"; shift 2 ;;
        --jobs) jobs="$2"; shift 2 ;;
        -h|--help) usage; exit 0 ;;
        --) shift; cmake_options+=("$@"); break ;;
        *) echo "Unknown option: $1" >&2; usage >&2; exit 2 ;;
    esac
done
if ! [[ "$suite" =~ ^[A-Za-z0-9_]+$ ]]; then usage >&2; exit 2; fi
source_directory="$root/tests/$suite"
if [ ! -f "$source_directory/CMakeLists.txt" ]; then echo "No CMake test suite named $suite." >&2; exit 1; fi
build_directory="${build_directory:-$root/build/tests/$suite}"

arguments=(-S "$source_directory" -B "$build_directory" -G Ninja
    -DCMAKE_BUILD_TYPE=Release "-DPython3_EXECUTABLE=$(command -v "$python")")
if [ -n "$usa_rom" ]; then
    usa_rom="$(realpath "$usa_rom")"
    "$python" "$root/tools/verify_rom.py" "$usa_rom" ||
        { echo 'The test ROM must be an unmodified USA Rev 1 ROM.' >&2; exit 1; }
    arguments+=("-DWR64_TEST_ROM=$usa_rom" "-DWR64_GHOST_NATIVE_ROM=$usa_rom" "-DWR64_SHUTTER_NATIVE_ROM=$usa_rom")
fi

cmake "${arguments[@]}" "${cmake_options[@]}"
cmake --build "$build_directory" --parallel "$jobs"
ctest --test-dir "$build_directory" --output-on-failure
