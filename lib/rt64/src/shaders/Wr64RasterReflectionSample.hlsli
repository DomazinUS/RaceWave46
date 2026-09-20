#ifndef WR64_RASTER_REFLECTION_SAMPLE_INCLUDED
#define WR64_RASTER_REFLECTION_SAMPLE_INCLUDED
#include "Wr64RasterReflectionParams.hlsli"
Texture2D<float4> wr64RasterReflection : register(t76, space0);

float4 wr64RasterReflectionTexel(int2 p, uint width, uint height) {
    if (any(p < 0) || p.x >= int(width) || p.y >= int(height)) return 0;
    const float4 value = wr64RasterReflection.Load(int3(p, 0));
    return all(isfinite(value)) ? float4(value.rgb, saturate(value.a)) : 0;
}

float4 wr64SampleRasterReflection(float3 worldPosition, float3 normal, float3 viewDirection) {
    if (wr64ReflectionOptions.x != 1 || !all(isfinite(worldPosition)) ||
        !all(isfinite(wr64ReflectionPlane)) || !all(isfinite(normal)) || !all(isfinite(viewDirection))) return 0;
    const float3 planeNormal = wr64ReflectionPlane.xyz;
    const float lengthSquared = dot(planeNormal, planeNormal);
    if (!isfinite(lengthSquared) || abs(lengthSquared - 1) > 1e-3f) return 0;
    // Capture remains tied to the stable course sea datum. Waves perturb only
    // the in-plane lookup point, never the capture camera or its clipping plane.
    float3 samplePosition = worldPosition - planeNormal * (dot(planeNormal, worldPosition) + wr64ReflectionPlane.w);
    float3 bend = reflect(-viewDirection, normal) - reflect(-viewDirection, planeNormal);
    bend -= planeNormal * dot(bend, planeNormal);
    const float distortion = isfinite(wr64ReflectionOptions.z) ? clamp(wr64ReflectionOptions.z, 0, 128) : 0;
    samplePosition += bend * distortion;
    const float4 clip = wr64RasterReflectionClip(samplePosition);
    if (!all(isfinite(clip)) || clip.w <= 1e-5f) return 0;
    const float3 ndc = clip.xyz / clip.w;
    const float2 uv = float2(ndc.x * 0.5f + 0.5f, 0.5f - ndc.y * 0.5f);
    if (any(uv < 0) || any(uv > 1) || ndc.z < 0 || ndc.z > 1) return 0;
    uint width, height;
    wr64RasterReflection.GetDimensions(width, height);
    if (width == 0 || height == 0) return 0;
    const float2 texel = uv * float2(width, height) - 0.5f;
    const int2 origin = int2(floor(texel));
    const float2 f = frac(texel);
    const float4 a = lerp(wr64RasterReflectionTexel(origin, width, height),
        wr64RasterReflectionTexel(origin + int2(1, 0), width, height), f.x);
    const float4 b = lerp(wr64RasterReflectionTexel(origin + int2(0, 1), width, height),
        wr64RasterReflectionTexel(origin + int2(1, 1), width, height), f.x);
    return lerp(a, b, f.y);
}
#endif
