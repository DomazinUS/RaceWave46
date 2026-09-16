// One deterministic reflection ray from the original rasterized water. This
// shader is selected only for verified water draws in the presentation renderer.
#define DYNAMIC_RENDER_PARAMS
#define PSMain Wr64BasePSMain
#include "RasterPS.hlsl"
#undef PSMain

#include "Wr64WaterParams.hlsli"
RaytracingAccelerationStructure wr64Scene : register(t26, space0);
ByteAddressBuffer wr64Positions : register(t27, space0);
ByteAddressBuffer wr64Texcoords : register(t30, space0);
ByteAddressBuffer wr64Colors : register(t31, space0);
ByteAddressBuffer wr64Indices : register(t35, space0);
StructuredBuffer<uint4> wr64Geometry : register(t40, space0);
#include "Wr64WaterMaterial.hlsli"
#include "Wr64WaterShadow.hlsli"
#include "Wr64WaterTranslucent.hlsli"
#ifdef WR64_RASTER_SHADOWS
#include "Wr64RasterShadow.hlsli"
#define wr64WaterSurfaceShadowTransmission(position, normal) wr64RasterWaterShadowTransmission(position, wr64ShadowReceiverNormal)
#define wr64WaterSurfaceShadowCoverage(position, normal) wr64RasterShadowCoverage(position, wr64ShadowReceiverNormal, true)
#endif

void PSMain(float4 position : SV_POSITION, float2 uv : TEXCOORD0,
    float4 smoothColor : COLOR0, nointerpolation float4 flatColor : COLOR1,
    float3 worldPosition : TEXCOORD1, float3 reflectionNormal : TEXCOORD2,
    bool frontFace : SV_IsFrontFace,
    WR64_RT_COLOR_OUTPUT out float4 pixelColor : SV_TARGET0,
    WR64_RT_ALPHA_OUTPUT out float4 pixelAlpha : SV_TARGET1) {
#ifdef WR64_RASTER_SHADOWS
    // Evaluate geometric receiver derivatives before native discard or divergent
    // reflection traversal. Optical smoothed normals do not define this plane.
    const float3 wr64ShadowReceiverNormal = cross(ddx(worldPosition), ddy(worldPosition));
#endif
    if (!RasterPS(getRenderParams(), position, uv, smoothColor, flatColor,
        frontFace, pixelColor, pixelAlpha)) discard;
    float3 dx = ddx(worldPosition), dy = ddy(worldPosition);
    float3 n = cross(dx, dy);
    // One continuous normal controls the ray and Fresnel together. Retain the
    // geometric fallback for an absent/degenerate adjacency neighborhood.
    if (wr64SmoothNormals != 0 && all(isfinite(reflectionNormal)) &&
        dot(reflectionNormal, reflectionNormal) > 1e-12f) n = reflectionNormal;
    float len2 = dot(n, n);
    if (wr64Enabled == 0 || len2 < 1e-12f) return;
    n *= rsqrt(len2);
    float3 viewDelta = wr64Camera.xyz - worldPosition;
    float viewLength = length(viewDelta);
    if (viewLength < 1e-5f) return;
    float3 v = viewDelta / viewLength;
    if (dot(n, v) < 0) n = -n;
    if (wr64DebugView == 1) { pixelColor.rgb = n * 0.5f + 0.5f; return; }

#ifdef WR64_RASTER_SHADOWS
    if (wr64DebugView == 5 && wr64ShadowMapLight.w == 1) {
#else
    if (wr64DebugView == 5 && wr64ShadowOptions.x == 1) {
#endif
        float coverage = wr64WaterSurfaceShadowCoverage(worldPosition, n);
        pixelColor.rgb = 1 - coverage;
        pixelAlpha.a = 1;
        return;
    }

    RayDesc ray;
    ray.Origin = worldPosition + n * 0.5f;
    ray.Direction = reflect(-v, n);
    ray.TMin = 0.5f;
    ray.TMax = wr64ReflectionMaxDistance();
    RayQuery<RAY_FLAG_SKIP_PROCEDURAL_PRIMITIVES> query;
    query.TraceRayInline(wr64Scene, RAY_FLAG_NONE, 0xff, ray);
    while (query.Proceed()) {
        if (query.CandidateType() == CANDIDATE_NON_OPAQUE_TRIANGLE &&
            wr64CandidateCovered(query.CandidateGeometryIndex(), query.CandidatePrimitiveIndex(),
                query.CandidateTriangleBarycentrics())) {
            query.CommitNonOpaqueTriangleHit();
        }
    }
    bool hit = query.CommittedStatus() == COMMITTED_TRIANGLE_HIT;
    if (wr64DebugView == 2) {
        pixelColor.rgb = hit ? float3(0, 1, 0.6f) : float3(0.45f, 0, 0.6f);
        return;
    }
    float4 beams = wr64TraceTranslucentBeams(ray, hit ? query.CommittedRayT() : ray.TMax);
    float surfaceTransmission = wr64WaterSurfaceShadowTransmission(worldPosition, n);
    // A miss keeps the native sky/water appearance. No invented environment map.
    if (hit) {
        float3 reflected = wr64HitColor(query.CommittedGeometryIndex(),
            query.CommittedPrimitiveIndex(), query.CommittedTriangleBarycentrics());
        if (beams.a > 0) reflected = wr64BeamsOverBackground(beams, float4(reflected, 1)).rgb;
        float fresnel = 0.08f + 0.35f * pow(1.0f - saturate(dot(n, v)), 5.0f);
        wr64SoftShadowReflectedWater(surfaceTransmission, saturate(fresnel * wr64Strength),
            reflected, pixelColor, pixelAlpha);
    }
    else {
        wr64SoftShadowNativeWater(surfaceTransmission, pixelColor, pixelAlpha);
        if (beams.a > 0) {
            float fresnel = 0.08f + 0.35f * pow(1.0f - saturate(dot(n, v)), 5.0f);
            wr64ReflectBeamsOverNative(beams, saturate(fresnel * wr64Strength), pixelColor, pixelAlpha);
        }
    }
}
