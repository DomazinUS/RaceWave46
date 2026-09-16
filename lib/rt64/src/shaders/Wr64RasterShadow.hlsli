#ifndef WR64_RASTER_SHADOW_INCLUDED
#define WR64_RASTER_SHADOW_INCLUDED

// Light rows map presentation-time world coordinates to D3D NDC (z in 0..1).
cbuffer Wr64RasterShadowParams : register(b73, space0) {
    float4 wr64ShadowMapRows[4];
    float4 wr64ShadowMapOptions; // inverse size, normalized bias, water/solid strength
    float4 wr64ShadowMapLight;   // direction toward light, enabled
};
#ifndef WR64_SHADOW_CAPTURE
Texture2D<float> wr64ShadowMap : register(t74, space0);
#endif

float4 wr64ShadowMapClip(float3 worldPosition) {
    const float4 p = float4(worldPosition, 1);
    return float4(dot(wr64ShadowMapRows[0], p), dot(wr64ShadowMapRows[1], p),
        dot(wr64ShadowMapRows[2], p), dot(wr64ShadowMapRows[3], p));
}

#ifndef WR64_SHADOW_CAPTURE
float wr64RasterShadowCompare(int2 texel, float3 receiver, float2 depthGradient, uint width, uint height) {
    if (any(texel < 0) || texel.x >= int(width) || texel.y >= int(height)) return 0;
    const float2 texelUV = (float2(texel) + 0.5f) / float2(width, height);
    // Every loaded texel represents a different point on a sloped receiver.
    // Compare against that point's plane depth, including bilinear corner offsets.
    const float receiverDepth = receiver.z + dot(depthGradient, texelUV - receiver.xy);
    if (!isfinite(receiverDepth) || receiverDepth <= 0 || receiverDepth >= 1) return 0;
    const float depth = wr64ShadowMap.Load(int3(texel, 0));
    return isfinite(depth) && depth < receiverDepth ? 1.0f : 0.0f;
}

float wr64RasterShadowBilinear(float2 uv, float3 receiver, float2 depthGradient, uint width, uint height) {
    const float2 texel = uv * float2(width, height) - 0.5f;
    const int2 origin = int2(floor(texel));
    const float2 f = frac(texel);
    // Filter comparison results, never depth values: blended depths invent occluders.
    const float a = lerp(wr64RasterShadowCompare(origin, receiver, depthGradient, width, height),
        wr64RasterShadowCompare(origin + int2(1, 0), receiver, depthGradient, width, height), f.x);
    const float b = lerp(wr64RasterShadowCompare(origin + int2(0, 1), receiver, depthGradient, width, height),
        wr64RasterShadowCompare(origin + int2(1, 1), receiver, depthGradient, width, height), f.x);
    return lerp(a, b, f.y);
}

bool wr64RasterShadowPlaneGradient(float3 normal, out float2 gradient) {
    gradient = 0;
    const float3 xRow = wr64ShadowMapRows[0].xyz;
    const float3 yRow = wr64ShadowMapRows[1].xyz;
    const float3 zRow = wr64ShadowMapRows[2].xyz;
    const float3 scaleSquared = float3(dot(xRow, xRow), dot(yRow, yRow), dot(zRow, zRow));
    const float normalSquared = dot(normal, normal);
    if (!all(isfinite(normal)) || !all(isfinite(scaleSquared)) ||
        any(scaleSquared <= 1e-20f) || !isfinite(normalSquared) || normalSquared <= 1e-20f) return false;
    // The capture matrix is orthographic with orthogonal basis rows. Express
    // N dot dWorld = 0 in (texture U, texture V, depth) coordinates, then solve
    // for dDepth/dUV. The V sign includes the D3D texture-coordinate Y flip.
    const float3 plane = float3(2 * dot(normal, xRow), -2 * dot(normal, yRow), dot(normal, zRow)) / scaleSquared;
    const float facing = abs(dot(normal, zRow)) * rsqrt(normalSquared * scaleSquared.z);
    // A plane parallel to the light does not have a finite depth over this
    // footprint. Leave that degenerate receiver unattenuated rather than
    // substituting a flat comparison that would recreate self-shadow stripes.
    if (!all(isfinite(plane)) || !isfinite(facing) || facing < 1e-4f) return false;
    gradient = -plane.xy / plane.z;
    return all(isfinite(gradient));
}

float wr64RasterShadowCoverage(float3 worldPosition, float3 normal, bool water) {
    if (wr64ShadowMapLight.w != 1 || !all(isfinite(worldPosition))) return 0;
    const float4 clip = wr64ShadowMapClip(worldPosition);
    if (!all(isfinite(clip)) || clip.w <= 1e-6f) return 0;
    const float3 ndc = clip.xyz / clip.w;
    const float2 uv = float2(ndc.x * 0.5f + 0.5f, 0.5f - ndc.y * 0.5f);
    if (any(uv <= 0) || any(uv >= 1) || ndc.z <= 0 || ndc.z >= 1) return 0;
    uint width, height;
    wr64ShadowMap.GetDimensions(width, height);
    if (width == 0 || height == 0) return 0;
    float2 depthGradient;
    if (!wr64RasterShadowPlaneGradient(normal, depthGradient)) return 0;
    const float2 invSize = 1.0f / float2(width, height);
    const float normalLength = dot(normal, normal);
    const float facing = all(isfinite(normal)) && normalLength > 1e-12f
        ? abs(dot(normal * rsqrt(normalLength), wr64ShadowMapLight.xyz)) : 1;
    const float bias = max(wr64ShadowMapOptions.y, 0) * (1 + 2 * (1 - saturate(facing)));
    float covered = 0;
    // Wider water filtering preserves the deliberately soft surface layer.
    const float radius = water ? 2.5f : 1.0f;
    [unroll] for (int y = -1; y <= 1; ++y) {
        [unroll] for (int x = -1; x <= 1; ++x) {
            covered += wr64RasterShadowBilinear(uv + float2(x, y) * radius * invSize,
                float3(uv, ndc.z - bias), depthGradient, width, height);
        }
    }
    const float edge = min(min(uv.x, uv.y), min(1 - uv.x, 1 - uv.y));
    return (covered / 9.0f) * saturate(edge / (8 * max(invSize.x, invSize.y)));
}

float wr64RasterWaterShadowTransmission(float3 worldPosition, float3 normal) {
    return 1 - clamp(wr64ShadowMapOptions.z, 0, 0.28f) * wr64RasterShadowCoverage(worldPosition, normal, true);
}

void wr64ApplyRasterShadowNativeWater(float transmission, inout float4 pixelColor, inout float4 pixelAlpha) {
    // Same weak transmission composition as the accepted RT water shadows.
    // Alpha here is the blend factor; pixelColor.a remains native coverage.
    if (transmission >= 1) return;
    const float alpha = saturate(pixelAlpha.a);
    const float combinedAlpha = 1 - transmission * (1 - alpha);
    pixelColor.rgb = transmission * alpha * pixelColor.rgb / max(combinedAlpha, 1e-8f);
    pixelAlpha.a = combinedAlpha;
}
#endif
#endif
