// Preserve native sky composition and alpha-tested visibility without any
// observation UAV, object-color ray, shadow ray, or translucency ray.
RaytracingAccelerationStructure wr64Scene : register(t26, space0);
ByteAddressBuffer wr64Positions : register(t27, space0);
ByteAddressBuffer wr64Texcoords : register(t30, space0);
ByteAddressBuffer wr64Colors : register(t31, space0);
ByteAddressBuffer wr64Indices : register(t35, space0);
StructuredBuffer<uint4> wr64Geometry : register(t40, space0);
#include "Wr64RasterSkyLookup.hlsli"
bool wr64MaterialCovered(uint drawIndex, float4 color, float alphaCompareValue) {
    RenderIndices ri = instanceRenderIndices[drawIndex];
    RenderParams rp = DynamicRenderParams[ri.instanceIndex];
    OtherMode om = {rp.omL, rp.omH};
    if (!isfinite(alphaCompareValue) || !isfinite(color.a)) return false;
    // Native dither uses a pixel/frame random sequence without a stable
    // offscreen ray equivalent. Those draws remain outside this trial's AS.
    if (om.alphaCompare() == G_AC_DITHER) return false;
    if (om.alphaCompare() == G_AC_THRESHOLD) {
        float threshold = instanceRDPParams[ri.instanceIndex].blendColor.a;
        if (!isfinite(threshold) || alphaCompareValue < threshold) return false;
    }
    return !om.cvgXAlpha() || color.a >= 0.125f;
}

bool wr64CandidateCovered(uint geometryIndex, uint primitiveIndex, float2 barycentric) {
    uint4 geometry = wr64Geometry[geometryIndex];
    // Native beams are separate alpha layers. Fence proxy indices belong to a
    // private buffer and must never be dereferenced as original scene indices.
    if ((geometry.w & (4u | 8u)) != 0) return false;
    if ((geometry.w & 2u) == 0) return true;
    uint3 indices = wr64Indices.Load3((geometry.x + primitiveIndex * 3) * 4);
    float alphaCompareValue;
    float4 color = wr64NativeMaterial(geometry.y, indices, barycentric, false, -1, alphaCompareValue);
    return wr64MaterialCovered(geometry.y, color, alphaCompareValue);
}


float4 wr64ReflectionRaySky(float3 worldPosition, float3 normal, float3 direction) {
    RayDesc ray;
    ray.Origin = worldPosition + normal * 0.5f;
    ray.Direction = direction;
    ray.TMin = 0.5f;
    ray.TMax = wr64ReflectionMaxDistance();
    {
        RayQuery<RAY_FLAG_SKIP_PROCEDURAL_PRIMITIVES> query;
        query.TraceRayInline(wr64Scene, RAY_FLAG_NONE, 0xff, ray);
        while (query.Proceed()) {
            if (query.CandidateType() == CANDIDATE_NON_OPAQUE_TRIANGLE &&
                wr64CandidateCovered(query.CandidateGeometryIndex(), query.CandidatePrimitiveIndex(),
                    query.CandidateTriangleBarycentrics())) query.CommitNonOpaqueTriangleHit();
        }
        if (query.CommittedStatus() == COMMITTED_TRIANGLE_HIT) return 0;
    }
    float4 sky;
    Wr64SkyLookupDiagnostic diagnostic;
    if (!wr64SkyColor(direction, sky, diagnostic) || !all(isfinite(sky)) || sky.a <= 0) return 0;
    return float4(sky.rgb * sky.a, sky.a);
}
