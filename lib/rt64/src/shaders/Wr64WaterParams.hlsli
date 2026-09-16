#ifndef WR64_WATER_PARAMS_INCLUDED
#define WR64_WATER_PARAMS_INCLUDED
#include "shared/rt64_wr64_rt_celestial.h"

// The native raster pipeline uses dual-source blending into one attachment.
// Wrapper entry points must preserve RasterPS's Vulkan output decorations;
// SV_TARGET1 alone denotes a second attachment instead of the blend factor.
#ifdef __spirv__
#define WR64_RT_COLOR_OUTPUT [[vk::location(0)]] [[vk::index(0)]]
#define WR64_RT_ALPHA_OUTPUT [[vk::location(0)]] [[vk::index(1)]]
#else
#define WR64_RT_COLOR_OUTPUT
#define WR64_RT_ALPHA_OUTPUT
#endif

cbuffer Wr64ReflectionParams : register(b25, space0) {
    float4 wr64Camera;
    uint wr64DebugView;
    float wr64Strength;
    uint wr64Enabled;
    uint wr64SmoothNormals;
    uint4 wr64Sky;
    float4 wr64SkyCamera;
    float4 wr64SkyCloudParams;
    uint4 wr64SkyBackdrop;
    float4 wr64SkyBackdropCamera;
    float4 wr64CelestialProjection[3];
    uint4 wr64CelestialInfo;
    Wr64RTCelestialRecord wr64CelestialBodies[WR64_RT_CELESTIAL_MAX];
    uint4 wr64CelestialAlpha[WR64_RT_CELESTIAL_ALPHA_VECTORS];
    float4 wr64ShadowLight; // World direction toward light; strength in w.
    float4 wr64ShadowOptions; // Enabled, origin bias, maximum distance, reserved.
    uint4 wr64SceneOptions; // Beam count, actor count, actor racer mask, reliable bounds mask.
    float4 wr64ActorShadowBoundsMin[4];
    float4 wr64ActorShadowBoundsMax[4];
    float4 wr64AOOptions; // Enabled, short-ray radius, maximum attenuation, origin bias.
    float4 wr64QualityOptions; // Object/beam reflection distance, actor shadow ray count, reserved.
};

float wr64ReflectionMaxDistance() {
    const float value = wr64QualityOptions.x;
    // Zero preserves older callers and the validated default. Malformed
    // settings cannot produce an invalid ray interval or unbounded traversal.
    if (!isfinite(value) || value <= 0) return 30000.0f;
    return clamp(value, 7500.0f, 30000.0f);
}

uint wr64ActorShadowSampleCount() {
    const float value = wr64QualityOptions.y;
    if (!isfinite(value) || value <= 0) return 16;
    return uint(floor(clamp(value, 4.0f, 16.0f) * 0.25f + 0.5f)) * 4;
}
#endif
