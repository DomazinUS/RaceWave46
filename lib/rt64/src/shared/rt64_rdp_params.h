//
// RT64
//

#pragma once

#include "rt64_hlsl.h"

#ifdef HLSL_CPU
namespace interop {
#endif
    struct RDPParams {
        float4 primColor;
        float2 primLOD;
        float2 primDepth;
        float4 envColor;
        float4 fogColor;
        float4 blendColor;
        float3 keyCenter;
        float3 keyScale;
        int convertK[6];
        // Per draw, not per texture: a shared texture can also appear in 3D.
        uint wr64UiFilter;
        uint wr64UiPadding0;
        uint wr64UiPadding1;
        uint wr64UiPadding2;
    };
#ifdef HLSL_CPU
};
#endif
