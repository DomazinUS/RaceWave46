// Per-draw surface-effect policy shared by the renderer and native world PS.
#pragma once

// Uses RasterParams.padding.x without changing its ABI. Native shader paths
// ignore this value. AO-only receivers must not gain directional shadows.
#define WR64_AO_ONLY_RECEIVER 0x414F0001u
