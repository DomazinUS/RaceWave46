# CRT shader presets

These RetroArch slang shader presets are listed under **Enhancements → CRT Shader**. librashader compiles and runs the selected one when the game starts or when it is picked. The menu offers **Off**, **CRT** (CRT Guest Advanced) and **Fast CRT** (zfast CRT); both shaders draw the image at the console's 240 lines, and Off returns to the unfiltered image at the window's resolution. [presets.json](presets.json) lists the menu entries. The `id` values are saved in the settings profile, so keep them stable.

## Source

`slang/` is an unmodified subset of [libretro/slang-shaders](https://github.com/libretro/slang-shaders) at commit `3685eda59ffd2ebe1b12cc4640581dc23552ce88`. It keeps the upstream directory layout and contains only the files the listed presets load: passes, includes, look-up textures and referenced presets. The `librashader_presets` test suite checks that each preset has everything it needs.

Presets were chosen because their license terms are clear and compatible with the project.

## Presets and licenses

| Menu choice | Preset | Author | License |
| --- | --- | --- | --- |
| CRT | `slang/crt/crt-guest-advanced.slangp` | guest(r) | GPL-2.0-or-later, including its look-up textures |
| Fast CRT | `slang/crt/zfast-crt.slangp` | Greg Hogan (SoltanGris42) | GPL-2.0-or-later |

`crt/shaders/guest/advanced/stock.slang` is libretro's pass-through shader. It copies the input image and has no license header.

Each shader keeps its original header and notice. To add a preset, copy the complete preset and every file it loads from the same upstream commit. Record its license here, add an entry with `id`, `label`, `name`, `description` and `path` to `presets.json`, and run `./BUILD-TEST.sh --suite librashader_presets`.
