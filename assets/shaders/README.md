# librashader shader presets

These RetroArch slang shader presets are listed under **Enhancements → librashader**. librashader compiles and runs them when the game starts or when you pick a preset. [presets.json](presets.json) lists the menu entries. The `id` values are saved in the settings profile, so keep them stable.

## Source

`slang/` is an unmodified subset of [libretro/slang-shaders](https://github.com/libretro/slang-shaders) at commit `3685eda59ffd2ebe1b12cc4640581dc23552ce88`. It keeps the upstream directory layout and contains only the files the listed presets load: passes, includes, look-up textures and referenced presets. The `librashader_presets` test suite checks that each preset has everything it needs.

`racewave46/` contains presets written for RaceWave46. They are covered by the project's GPL-3.0 license and use the upstream shaders listed below.

Presets were chosen because their license terms are clear and compatible with the project. Presets with ambiguous or missing terms were left out.

## Presets and licenses

| Menu name | Preset | Author | License |
| --- | --- | --- | --- |
| CRT Geom | `slang/crt/crt-geom.slangp` | cgwg, Themaister and DOLLS | GPL-2.0-or-later |
| CRT Lottes | `slang/crt/crt-lottes.slangp` | Timothy Lottes | Public domain |
| CRT Pi | `slang/crt/crt-pi.slangp` | davej | GPL-2.0-or-later |
| zfast CRT | `slang/crt/zfast-crt.slangp` | Greg Hogan (SoltanGris42) | GPL-2.0-or-later |
| CRT Guest Advanced | `slang/crt/crt-guest-advanced.slangp` | guest(r) | GPL-2.0-or-later, including its look-up textures |
| SMAA | `slang/anti-aliasing/smaa.slangp` | Jorge Jimenez, Jose I. Echevarria, Belen Masia, Fernando Navarro and Diego Gutierrez; slang passes by libretro contributors | MIT (`SMAA.hlsl`, `AreaTex.png`, `SearchTex.png`); Unlicense (passes) |
| AMD FSR 1.0 | `slang/edge-smoothing/fsr/fsr.slangp` | Advanced Micro Devices; slang passes by libretro contributors | MIT (`ffx_a.h`, `ffx_fsr1.h`); Unlicense (passes) |
| Adaptive Sharpen | `slang/sharpen/adaptive-sharpen.slangp` | bacondither | BSD-2-Clause |
| ScaleFX | `slang/edge-smoothing/scalefx/scalefx.slangp` | Sp00kyFox | MIT |
| Vivid Colours | `racewave46/vivid-colours.slangp` | RaceWave46, using `image-adjustment.slang` by hunterk | GPL-3.0 preset; public-domain shader |

`stock.slang` and `crt/shaders/guest/advanced/stock.slang` are libretro's pass-through shaders. They copy the input image and have no license header.

Each shader keeps its original header and notice. To add a preset, copy the complete preset and every file it loads from the same upstream commit. Record its license here, add an entry to `presets.json`, and run `./BUILD-TEST.sh --suite librashader_presets`.
