//
// RT64
//

#pragma once

#include "shared/rt64_hlsl.h"

// RasterPS-only use of the existing reserved lanes, preserving the 32-byte ABI.
// padding.y = float opacity loss bits when padding.z has this tag. Other
// pipelines have independent lane meanings (motion mask uses tag 1).
#define WR64_DOLPHIN_SUN_FADE_TAG 0x44505346u

#ifdef HLSL_CPU
namespace interop {
#endif
    struct RasterParams {
        uint renderIndex;
        uint3 padding;
        float2 screenScale;
        float2 screenOffset;
    };
#ifdef HLSL_CPU
};
#endif
