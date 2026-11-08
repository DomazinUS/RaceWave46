# Building RaceWave46 on Windows

Install Visual Studio 2022 C++ Build Tools with the Windows 10 or 11 SDK and C++ CMake tools. The build uses MSVC x64, CMake 3.20 or newer, and Ninja. Code generation and regression tests require Python 3.11 or newer. Provide your own unmodified USA Rev 1 ROM in big-endian `.z64` format and N64Recomp/RSPRecomp tools.

Build the recompiler tools from the bundled `lib/N64ModernRuntime/N64Recomp` source in an x64 Visual Studio developer shell:

```powershell
cmake -S lib/N64ModernRuntime/N64Recomp -B build-tools -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build-tools --target N64RecompCLI RSPRecomp --parallel 8
```

From PowerShell in this directory:

```powershell
& .\BUILD-USA.ps1 -Rom "C:\ROMs\Wave Race 64 (USA) (Rev 1).z64" -N64Recomp .\build-tools\N64Recomp.exe -RSPRecomp .\build-tools\RSPRecomp.exe
```

The script discovers Visual Studio with `vswhere` and builds `build\WaveRace64Recompiled.exe` with the frontend and RT64 enabled and developer diagnostics disabled. Use `-BuildToolsRoot`, `-BuildDirectory`, and `-Jobs` to override installation and output choices. Keep the copied DLLs and `assets` directory beside the executable. The build does not launch the game.

The first configuration downloads the matching x64 compiler, runtime library and validator from Microsoft DXC 1.8.2502. It also downloads DXC 1.9.2607 for the selected Vulkan framebuffer and Wave Race reflection/shadow shaders that require that compiler. Remaining Vulkan shaders use 1.8.2502. The archives are pinned by SHA-256, and each of the three 1.8.2502 files is hash-checked. Downloaded tools stay in a versioned build directory. The 1.8.2502 release license, per-file mapping and source notices are retained under `lib/rt64/src/contrib/dxc/validator-1.8.2502`.

For an offline build, supply the matching Vulkan compiler with `-VulkanDxc 'C:\Tools\dxc-1.9.2607\bin\x64\dxc.exe'` and the complete 1.8.2502 x64 directory with `-DirectXDxcDirectory 'C:\Tools\dxc-1.8.2502\bin\x64'`; retain both compilers' accompanying DLLs. Keep `dxcompiler.dll` and `dxil.dll` from the build output together with that newly built executable; substituting only one DLL from another release is unsupported. Other dependency build inputs are included. SDL2 and FreeType are supplied as prebuilt third-party libraries with their notices.

The first configuration also downloads the pinned x64 [librashader](https://github.com/SnowflakePowered/librashader) 0.12.0 release and copies its `librashader.dll` beside the executable for the **CRT Shader** enhancement. The archive and the DLL are checked against their SHA-256. Pass `-Librashader 'C:\Tools\librashader.dll'` to bundle another build of the same C ABI (version 2), for example offline, or `-NoLibrashader` to leave it out; the game then shows the option as unavailable. The shader presets are copied from `assets/shaders` with the other assets.

Generation verifies the supplied ROM, applies the included widescreen patch to a temporary copy, runs both recompilers, and applies the host integration edits. It verifies all generated code against the release checksums before installing it into the ignored `RecompiledFuncsPoint0` and `rsp` directories. Your original ROM is unchanged. Subsequent builds can omit `-Rom` while those verified outputs remain available. `-Python` selects a Python executable.

To generate separately before using CMake directly:

```powershell
python tools/generate_code.py --rom "C:\ROMs\Wave Race 64 (USA) (Rev 1).z64" --n64recomp build-tools/N64Recomp.exe --rsprecomp build-tools/RSPRecomp.exe
```

Both building and playing require your own supported ROM. No ROM, save data, texture pack, or account data is included.

To run an individual regression suite:

```powershell
& .\BUILD-TEST.ps1 -Suite rt_reflection_setting
```

Some suites require a user-supplied ROM (`-UsaRom`) or explicit input files. They are not prerequisites for building the executable.

Use the bundled recompiler version, symbol tables, configuration and integration scripts together. Do not replace vendored dependencies with unmodified upstream checkouts: this project includes changes to them. If developing new hooks, update the generation checksums after reviewing the resulting code.

This validates a source build with the listed dependencies, not a byte-for-byte reproducible compiler toolchain or deterministic executable hash.

# Building RaceWave46 on Linux

The Linux host renders with RT64 through Vulkan into an SDL2 window and always includes the frontend. It needs a C/C++ toolchain (Clang is preferred and used when available), CMake 3.20 or newer, Ninja, Python 3.11 or newer, pkg-config, and development files for SDL2, Vulkan, libcurl, libsecret and D-Bus. The Freedesktop 26.08 SDK used by the Flatpak below provides all of them. Only x86_64 is supported, because the pinned DXC shader compilers are x86_64 binaries.

From this directory:

```sh
./BUILD-USA.sh --rom "/path/to/Wave Race 64 (USA) (Rev 1).z64"
```

The script builds `N64Recomp` and `RSPRecomp` from the bundled source into `build-tools` when they are missing, generates and verifies the code exactly as on Windows, and builds `build/WaveRace64Recompiled`. The generated code is identical on both platforms. Subsequent builds can omit `--rom`. The first configuration downloads Microsoft's pinned Linux DXC 1.8.2502 and 1.9.2607 archives and checks their hashes. For an offline build pass `--dxc-dir /path/to/dxc-1.8.2502/bin` (the extracted archive's `bin`, with its `lib` beside it) and `--vulkan-dxc /path/to/dxc-1.9.2607/bin/dxc`. Run `./BUILD-USA.sh --help` for the remaining options.

The **CRT Shader** enhancement loads `librashader.so` from the executable's directory, then a distribution's `librashader.so.2`. When `cargo` (Rust 1.88 or newer) is available, `BUILD-USA.sh` builds the pinned librashader 0.12.0 source release with only its Vulkan runtime through `tools/build_librashader.sh`, keeps it in `build-tools/librashader-0.12.0`, and copies it beside the game. That first build downloads the source archive, checked against its SHA-256, and its Rust dependencies. Without cargo, or when that build fails, the game is built without it and the option is shown as unavailable. Pass `--librashader FILE` to bundle an existing build of the same C ABI (version 2), or `--no-librashader` to skip it.

Start the game with `build/WaveRace64Recompiled`. It loads its `assets` from beside the executable, so the working directory does not matter.

Settings, the imported ROM, saves and ghosts are stored in `$XDG_DATA_HOME/racewave46` (normally `~/.local/share/racewave46`) instead of a `.runtime` directory beside the executable. `--runtime-dir` still selects another profile. The RetroAchievements login is kept in the desktop keyring through libsecret. Separate player windows require Direct3D 12 and are not available on Linux.

As on Windows, choose the ROM with **Select USA ROM** in the main menu. The file dialog goes through the xdg-desktop-portal FileChooser, so it works on any desktop with a portal backend (for example `xdg-desktop-portal-kde`, `xdg-desktop-portal-gnome` or `xdg-desktop-portal-wlr` with `xdg-desktop-portal-gtk`); no GTK or Qt library is linked into the game. Without a backend the game reports that the file dialog is unavailable.

To run a test suite, use `./BUILD-TEST.sh --suite achievements_platform`; `--usa-rom` and extra CMake options after `--` work like the PowerShell script's parameters. Suites that compile Windows code remain Windows-only.

## Flatpak

`packaging/linux` contains a Flatpak for the Freedesktop 26.08 runtime. It starts the game directly; on the first start, choose the ROM with **Select USA ROM** in the main menu, exactly as on Windows. Once a valid ROM is stored, the option reads **Start Game**.

Build and install it for the current user with `flatpak` and `flatpak-builder` installed:

```sh
packaging/linux/flatpak/build.sh --rom "/path/to/Wave Race 64 (USA) (Rev 1).z64"
flatpak run io.github.DomazinUS.RaceWave46
```

The script installs the Freedesktop SDK and its Rust and LLVM extensions from Flathub when needed, copies the ROM into the ignored `.flatpak-input` directory for the build, and deletes it afterwards. The ROM itself is not installed, but the package contains code generated from it: keep the Flatpak for your own use and do not redistribute it.

The sandbox has no file system access. Its profile is `~/.var/app/io.github.DomazinUS.RaceWave46/data/racewave46`. It uses the FileChooser and Documents portals for the ROM, the Secret portal for the RetroAchievements login, and the OpenURI portal for links and the mods folder. It requests network access for RetroAchievements, Wayland/X11, PulseAudio and `--device=all`; the last is needed because no portal exposes game controllers and rumble yet.

The manifest builds librashader from its pinned source release, with only the Vulkan runtime, and installs it beside the game. Its Rust dependencies come from `librashader-cargo-sources.json`; after changing the librashader version, regenerate that file from the release archive's `Cargo.lock` with flatpak-cargo-generator and update the archive hash here, in `tools/build_librashader.sh` and in `tools/prepare_librashader.cmake`.
