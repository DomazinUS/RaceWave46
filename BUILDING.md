# Building RaceWave46 on Windows

Install Visual Studio 2022 C++ Build Tools with the Windows 10 or 11 SDK and C++ CMake tools. The build uses MSVC x64, CMake 3.20 or newer, and Ninja. Regression tests additionally require Python 3.11 or newer.

From PowerShell in this directory:

```powershell
& .\BUILD-USA.ps1
```

The script discovers Visual Studio with `vswhere` and builds `build\WaveRace64Recompiled.exe` with the frontend and RT64 enabled and developer diagnostics disabled. Use `-BuildToolsRoot`, `-BuildDirectory`, and `-Jobs` to override installation and output choices. Keep the copied DLLs and `assets` directory beside the executable. The build does not launch the game.

The first configuration downloads the matching x64 compiler, runtime library and validator from Microsoft DXC 1.8.2502. It also downloads DXC 1.9.2607 for the selected Vulkan framebuffer and Wave Race reflection/shadow shaders that require that compiler. Remaining Vulkan shaders use 1.8.2502. The archives are pinned by SHA-256, and each of the three 1.8.2502 files is hash-checked. Downloaded tools stay in a versioned build directory. The 1.8.2502 release license, per-file mapping and source notices are retained under `lib/rt64/src/contrib/dxc/validator-1.8.2502`.

For an offline build, supply the matching Vulkan compiler with `-VulkanDxc 'C:\Tools\dxc-1.9.2607\bin\x64\dxc.exe'` and the complete 1.8.2502 x64 directory with `-DirectXDxcDirectory 'C:\Tools\dxc-1.8.2502\bin\x64'`; retain both compilers' accompanying DLLs. Keep `dxcompiler.dll` and `dxil.dll` from the build output together with that newly built executable; substituting only one DLL from another release is unsupported. Other dependency build inputs are included. SDL2 and FreeType are supplied as prebuilt third-party libraries with their notices.

The included `RecompiledFuncsPoint0` and `rsp` files are required build inputs. Compiling them does not require a ROM. Playing the game requires your own unmodified USA Rev 1 ROM; no ROM, save data, texture pack, or account data is included.

To run an individual regression suite:

```powershell
& .\BUILD-TEST.ps1 -Suite rt_reflection_setting
```

Some suites require a user-supplied ROM (`-UsaRom`) or explicit input files. They are not prerequisites for building the executable.

The N64Recomp and RSPRecomp source, symbol tables, and configuration files are retained for development. The checked-in generated files also contain targeted modifications; regenerating them from the ROM is not a replacement for these release inputs and is not part of the normal build. Do not replace vendored dependencies with unmodified upstream checkouts: this project includes changes to them.

This validates a source build with the listed dependencies, not a byte-for-byte reproducible compiler toolchain or deterministic executable hash.
