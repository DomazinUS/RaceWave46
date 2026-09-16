//
// RT64
//

#pragma once

#include "shared/rt64_hlsl.h"

#ifdef HLSL_CPU
namespace interop {
#endif
    struct VideoInterfaceCB {
        float2 videoResolution;
        float2 textureResolution;
        float2 sourceUVOffset;
        float2 sourceUVScale;
        float gamma;
    };
#ifdef HLSL_CPU
};
#endif
