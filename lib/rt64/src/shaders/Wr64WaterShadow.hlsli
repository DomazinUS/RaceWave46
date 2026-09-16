#ifndef WR64_WATER_SHADOW_INCLUDED
#define WR64_WATER_SHADOW_INCLUDED

bool wr64MakeShadowRay(float3 worldPosition, float3 normal, out RayDesc ray) {
    ray.Origin = 0; ray.Direction = float3(0, 1, 0); ray.TMin = 0; ray.TMax = 0;
    if (wr64ShadowOptions.x != 1 || !all(isfinite(wr64ShadowOptions)) ||
        !all(isfinite(wr64ShadowLight)) || !all(isfinite(worldPosition)) ||
        !all(isfinite(normal)) || wr64ShadowOptions.y <= 0 ||
        wr64ShadowOptions.z <= wr64ShadowOptions.y) return false;
    float len2 = dot(wr64ShadowLight.xyz, wr64ShadowLight.xyz);
    if (!isfinite(len2) || len2 < 1e-12f) return false;
    ray.Origin = worldPosition + normal * wr64ShadowOptions.y;
    ray.Direction = wr64ShadowLight.xyz * rsqrt(len2);
    ray.TMin = wr64ShadowOptions.y;
    ray.TMax = wr64ShadowOptions.z;
    return true;
}

// Filter 0: all physical casters; 1: scenery only; 2: riders/watercraft only.
bool wr64TraceShadowRay(RayDesc ray, uint receiverDrawIndex, uint receiverFaceIndex, uint filter) {
    // Only explicitly admitted physical casters may terminate this visibility
    // query. Native cutout holes continue traversal to the next candidate.
    RayQuery<RAY_FLAG_FORCE_NON_OPAQUE | RAY_FLAG_SKIP_PROCEDURAL_PRIMITIVES |
        RAY_FLAG_ACCEPT_FIRST_HIT_AND_END_SEARCH> query;
    query.TraceRayInline(wr64Scene, RAY_FLAG_NONE, 0xff, ray);
    while (query.Proceed()) {
        if (query.CandidateType() != CANDIDATE_NON_OPAQUE_TRIANGLE) continue;
        const uint geometryIndex = query.CandidateGeometryIndex();
        const uint primitiveIndex = query.CandidatePrimitiveIndex();
        const uint4 geometry = wr64Geometry[geometryIndex];
        if ((geometry.w & 1u) == 0) continue;
        const bool actor = (geometry.w & 16u) != 0;
        if ((filter == 1 && actor) || (filter == 2 && !actor)) continue;
        // A native zero-thickness fence lies inside its approximate volume.
        // That proxy shades other surfaces, never the original card itself.
        if ((geometry.w & 8u) != 0 && geometry.y == receiverDrawIndex) continue;
        // A raster receiver and its AS triangle use the same presentation
        // vertices, but their interpolated/intersected points can differ by
        // rounding. Reject only that originating triangle. Another face in
        // the same native draw, including a thin cap or fence, remains a caster.
        if ((geometry.w & 8u) == 0 && receiverDrawIndex != 0xffffffffu && geometry.y == receiverDrawIndex &&
            geometry.x + primitiveIndex * 3 == receiverFaceIndex) continue;
        if (wr64ShadowCandidateCovered(geometryIndex, primitiveIndex,
            query.CandidateTriangleBarycentrics())) {
            query.CommitNonOpaqueTriangleHit();
        }
    }
    return query.CommittedStatus() == COMMITTED_TRIANGLE_HIT;
}

bool wr64SurfaceShadowBlocked(float3 worldPosition, float3 normal,
    uint receiverDrawIndex, uint receiverFaceIndex) {
    RayDesc ray;
    if (!wr64MakeShadowRay(worldPosition, normal, ray)) return false;
    return wr64TraceShadowRay(ray, receiverDrawIndex, receiverFaceIndex, 0);
}

bool wr64WaterShadowBlocked(float3 worldPosition, float3 normal) {
    // Water is not admitted into the caster AS. Retain its validated ray
    // interval and origin exactly; primitive exclusion is for world receivers.
    return wr64SurfaceShadowBlocked(worldPosition, normal, 0xffffffffu, 0xffffffffu);
}

// A conservative broad phase for the entire offset-ray bundle. Missing or
// malformed bounds cause full ray evaluation, never a disappearing shadow.
bool wr64ActorShadowNearby(RayDesc ray, float radius) {
    const uint racers = wr64SceneOptions.z;
    if (racers == 0 || (racers & ~15u) != 0 || (wr64SceneOptions.w & racers) != racers) return true;
    const float padding = radius + wr64ShadowOptions.y + 0.01f;
    [unroll] for (uint racer = 0; racer < 4; ++racer) {
        if ((racers & (1u << racer)) == 0) continue;
        float3 lo = wr64ActorShadowBoundsMin[racer].xyz;
        float3 hi = wr64ActorShadowBoundsMax[racer].xyz;
        if (!all(isfinite(lo)) || !all(isfinite(hi)) || any(lo > hi)) return true;
        lo -= padding; hi += padding;
        float nearT = ray.TMin, farT = ray.TMax;
        bool intersects = true;
        [unroll] for (uint axis = 0; axis < 3; ++axis) {
            if (abs(ray.Direction[axis]) < 1e-8f) {
                if (ray.Origin[axis] < lo[axis] || ray.Origin[axis] > hi[axis]) intersects = false;
            }
            else {
                float a = (lo[axis] - ray.Origin[axis]) / ray.Direction[axis];
                float b = (hi[axis] - ray.Origin[axis]) / ray.Direction[axis];
                nearT = max(nearT, min(a, b)); farT = min(farT, max(a, b));
            }
        }
        if (intersects && farT >= nearT) return true;
    }
    return false;
}

float wr64ActorShadowCoverage(float3 worldPosition, float3 normal, float radius,
    uint receiverDrawIndex, uint receiverFaceIndex) {
    if (wr64SceneOptions.y == 0 || !all(isfinite(normal))) return 0;
    const float normalLength2 = dot(normal, normal);
    if (normalLength2 < 1e-12f || !isfinite(normalLength2)) return 0;
    normal *= rsqrt(normalLength2);
    RayDesc centerRay;
    if (!wr64MakeShadowRay(worldPosition, normal, centerRay) || !wr64ActorShadowNearby(centerRay, radius)) return 0;
    float3 u = float3(normal.y, -normal.x, 0);
    const float uLength2 = dot(u, u);
    u = uLength2 < 1e-8f ? float3(1, 0, 0) : u * rsqrt(uLength2);
    const float3 v = cross(normal, u);
    // Eight antipodal pairs: r=sqrt((i+.5)/8), angle=i*pi*(3-sqrt(5)).
    // Equal weights, fixed in the receiving plane. No random/frame rotation
    // or history accumulation, and no center-hit test that clips the penumbra.
    const float2 pairs[8] = {
        float2(0.250000000f, 0.000000000f), float2(-0.319290090f, 0.292495877f),
        float2(0.048872466f, -0.556876541f), float2(0.402444479f, 0.524917557f),
        float2(-0.738535114f, -0.130636463f), float2(0.699604932f, -0.445031391f),
        float2(-0.234004158f, 0.870483805f), float2(-0.446271308f, -0.859268247f)
    };
    // Each reduced mode covers the complete disc with its own equal-area
    // radial strata. Truncating the original eight pairs would shrink the
    // shadow's softness radius. Retain the original table for 16-ray parity.
    const float2 reducedPairs[12] = {
        float2(0.500000000f, 0.000000000f), float2(-0.638580180f, 0.584991755f),
        float2(0.353553391f, 0.000000000f), float2(-0.451544376f, 0.413651637f),
        float2(0.069116104f, -0.787542357f), float2(0.569142440f, 0.742345528f),
        float2(0.288675135f, 0.000000000f), float2(-0.368684439f, 0.337745147f),
        float2(0.056433063f, -0.643025642f), float2(0.464702856f, 0.606122586f),
        float2(-0.852786894f, -0.150845994f), float2(0.807834192f, -0.513877987f)
    };
    const uint sampleCount = wr64ActorShadowSampleCount();
    const uint pairCount = sampleCount / 2;
    const uint reducedStart = pairCount == 2 ? 0 : (pairCount == 4 ? 2 : 6);
    float coverage = 0;
    [loop] for (uint i = 0; i < pairCount; ++i) {
        float2 pair = pairs[i];
        if (pairCount < 8) pair = reducedPairs[reducedStart + i];
        const float3 offset = radius * (u * pair.x + v * pair.y);
        RayDesc ray = centerRay;
        ray.Origin = centerRay.Origin + offset;
        coverage += wr64TraceShadowRay(ray, receiverDrawIndex, receiverFaceIndex, 2) ? 1 : 0;
        ray.Origin = centerRay.Origin - offset;
        coverage += wr64TraceShadowRay(ray, receiverDrawIndex, receiverFaceIndex, 2) ? 1 : 0;
    }
    return sampleCount == 16 ? coverage * (1.0f / 16.0f) : coverage / float(sampleCount);
}

float wr64WorldShadowCoverage(float3 worldPosition, float3 normal,
    uint receiverDrawIndex, uint receiverFaceIndex) {
    if (wr64SceneOptions.y == 0)
        return wr64SurfaceShadowBlocked(worldPosition, normal, receiverDrawIndex, receiverFaceIndex) ? 1 : 0;
    RayDesc ray;
    if (!wr64MakeShadowRay(worldPosition, normal, ray)) return 0;
    // Existing scenery shadows keep their visibility and maximum strength.
    // AS candidate order cannot decide whether the actor kernel is evaluated.
    if (wr64TraceShadowRay(ray, receiverDrawIndex, receiverFaceIndex, 1)) return 1;
    return wr64ActorShadowCoverage(worldPosition, normal, 2.5f, receiverDrawIndex, receiverFaceIndex);
}

float wr64WaterActorShadowCoverage(float3 worldPosition, float3 normal) {
    return wr64ActorShadowCoverage(worldPosition, normal, 7.5f, 0xffffffffu, 0xffffffffu);
}

float wr64WaterSceneryShadowCoverage(float3 worldPosition, float3 normal) {
    if (!all(isfinite(normal))) return 0;
    const float normalLength2 = dot(normal, normal);
    if (normalLength2 < 1e-12f || !isfinite(normalLength2)) return 0;
    normal *= rsqrt(normalLength2);
    RayDesc centerRay;
    if (!wr64MakeShadowRay(worldPosition, normal, centerRay)) return 0;
    float3 u = float3(normal.y, -normal.x, 0);
    const float uLength2 = dot(u, u);
    u = uLength2 < 1e-8f ? float3(1, 0, 0) : u * rsqrt(uLength2);
    const float3 v = cross(normal, u);
    // Scenery has a separate, bounded water filter. Each quality covers the
    // full disc with equal-area antipodal pairs; neither the camera nor frame
    // number moves this pattern. Do not gate on the center ray: a clear center
    // can still lie inside the soft edge of an eligible buoy or scenery shadow.
    const float2 pairs[6] = {
        float2(0.500000000f, 0.000000000f), float2(-0.638580180f, 0.584991755f),
        float2(0.353553391f, 0.000000000f), float2(-0.451544376f, 0.413651637f),
        float2(0.069116104f, -0.787542357f), float2(0.569142440f, 0.742345528f)
    };
    const uint sampleCount = wr64ActorShadowSampleCount() <= 8 ? 4 : 8;
    const uint pairCount = sampleCount / 2;
    const uint pairStart = sampleCount == 4 ? 0 : 2;
    float coverage = 0;
    [loop] for (uint i = 0; i < pairCount; ++i) {
        const float2 pair = pairs[pairStart + i];
        const float3 offset = 6.0f * (u * pair.x + v * pair.y);
        RayDesc ray = centerRay;
        ray.Origin = centerRay.Origin + offset;
        coverage += wr64TraceShadowRay(ray, 0xffffffffu, 0xffffffffu, 1) ? 1 : 0;
        ray.Origin = centerRay.Origin - offset;
        coverage += wr64TraceShadowRay(ray, 0xffffffffu, 0xffffffffu, 1) ? 1 : 0;
    }
    return coverage / float(sampleCount);
}

float wr64WaterSurfaceShadowCoverage(float3 worldPosition, float3 normal) {
    // Diagnostic coverage, before the independent actor/scenery strengths.
    return max(wr64WaterActorShadowCoverage(worldPosition, normal),
        wr64WaterSceneryShadowCoverage(worldPosition, normal));
}

float wr64WaterShadowTransmission(float coverage) {
    if (coverage <= 0) return 1;
    return 1 - clamp(wr64ShadowLight.w, 0.0f, 0.55f) * saturate(coverage);
}

float wr64SoftWaterShadowTransmission(float coverage) {
    // Deliberate gentle surface layer, separate from the solid seabed shadow.
    // At full occlusion it adds at most 18% darkening, not another 55% mask.
    if (coverage <= 0) return 1;
    return 1 - (0.18f / 0.55f) * clamp(wr64ShadowLight.w, 0.0f, 0.55f) * saturate(coverage);
}

float wr64WaterSurfaceShadowTransmission(float3 worldPosition, float3 normal) {
    const float actorTransmission = wr64SoftWaterShadowTransmission(
        wr64WaterActorShadowCoverage(worldPosition, normal));
    const float sceneryCoverage = wr64WaterSceneryShadowCoverage(worldPosition, normal);
    if (sceneryCoverage <= 0) return actorTransmission;
    const float sceneryTransmission = 1 - (0.28f / 0.55f) *
        clamp(wr64ShadowLight.w, 0.0f, 0.55f) * saturate(sceneryCoverage);
    // These describe one surface layer. Overlap takes its stronger attenuation
    // instead of multiplying two masks; actor-only water remains unchanged.
    return min(actorTransmission, sceneryTransmission);
}

void wr64SoftShadowNativeWater(float transmission, inout float4 pixelColor, inout float4 pixelAlpha) {
    if (transmission >= 1) return;
    const float alpha = saturate(pixelAlpha.a);
    const float combinedAlpha = 1 - transmission * (1 - alpha);
    pixelColor.rgb = transmission * alpha * pixelColor.rgb / max(combinedAlpha, 1e-8f);
    pixelAlpha.a = combinedAlpha;
}

void wr64SoftShadowReflectedWater(float transmission, float weight, float3 reflected,
    inout float4 pixelColor, inout float4 pixelAlpha) {
    if (transmission >= 1) { pixelColor.rgb = lerp(pixelColor.rgb, reflected, weight); return; }
    const float alpha = saturate(pixelAlpha.a);
    const float combinedAlpha = 1 - transmission * (1 - alpha);
    // Preserve A*F*reflection. Only the native water/transmitted scene receives
    // the broad, weak actor layer; coverage in pixelColor.a stays native.
    pixelColor.rgb = alpha * (transmission * (1 - weight) * pixelColor.rgb + weight * reflected) /
        max(combinedAlpha, 1e-8f);
    pixelAlpha.a = combinedAlpha;
}
#endif
