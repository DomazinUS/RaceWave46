#pragma once

#include "shared/rt64_hlsl.h"

#define WR64_RT_CELESTIAL_MAX 20
#define WR64_RT_CELESTIAL_ALPHA_VECTORS 129

#ifdef HLSL_CPU
namespace interop {
#endif
    struct Wr64RTCelestialRecord {
        float4 bounds; // Unclipped native pixels: left, top, right, bottom.
        float4 uv; // Start S/T and full S/T extent, in native texels.
        float4 color; // Native primitive RGB and effective material alpha.
        uint4 texture; // Packed alpha byte offset, width, height, flags (zero).
    };
#ifdef HLSL_CPU
}
#endif
