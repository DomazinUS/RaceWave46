// Independent RT sky visibility with Original water/object presentation.
// One deterministic reflection ray from the original rasterized water. This
// shader is selected only for verified water draws in the presentation renderer.
#define DYNAMIC_RENDER_PARAMS
#define PSMain Wr64BasePSMain
#include "RasterPS.hlsl"
#undef PSMain
#include "Wr64WaterParams.hlsli"
#ifdef WR64_RASTER_SHADOWS
#include "Wr64RasterShadow.hlsli"
#endif
RaytracingAccelerationStructure wr64Scene : register(t26, space0);
ByteAddressBuffer wr64Positions : register(t27, space0);
ByteAddressBuffer wr64Texcoords : register(t30, space0);
ByteAddressBuffer wr64Colors : register(t31, space0);
ByteAddressBuffer wr64Indices : register(t35, space0);
StructuredBuffer<uint4> wr64Geometry : register(t40, space0);
#include "Wr64WaterMaterial.hlsli"
#include "Wr64WaterShadow.hlsli"
#include "Wr64WaterTranslucent.hlsli"

#include "Wr64WaterCelestial.hlsli"
// Compile only in a dedicated diagnostic shader. Runtime-disabled UAV writes
// still trigger the AMD sky hang; the normal shader must omit them entirely.
#ifdef WR64_SKY_GPU_OBSERVATION
RWByteAddressBuffer wr64SkyCapture : register(u71, space0);
#endif

struct Wr64SkyLookupDiagnostic {
    uint reason;
    uint flags;
    float planeY;
    float radialAlpha;
    float uvResidual;
    float determinant;
    float2 uv;
    float cloudAlpha;
    float backdropAlpha;
};

void wr64CaptureWaterPixel(float4 position, uint state,
    Wr64SkyLookupDiagnostic diagnostic, float3 worldPosition, float nativeAlpha,
    float3 normal, float dotNV, float3 rayDirection, float hitT, float4 skyColor,
    uint geometry, uint primitive, float transmission, float finalAlpha) {
#ifdef WR64_SKY_GPU_OBSERVATION
    uint2 pixel = uint2(position.xy);
    [branch] if (wr64SkyCloudParams.w != 1 || any((pixel & 63u) != 32u)) return;
    uint slot;
    wr64SkyCapture.InterlockedAdd(0, 1, slot);
    if (slot >= 512) return;
    uint offset = 16 + slot * 128;
    wr64SkyCapture.Store4(offset, uint4(pixel.x | (pixel.y << 16), state, diagnostic.reason, diagnostic.flags));
    wr64SkyCapture.Store4(offset + 16, asuint(float4(worldPosition, nativeAlpha)));
    wr64SkyCapture.Store4(offset + 32, asuint(float4(normal, dotNV)));
    wr64SkyCapture.Store4(offset + 48, asuint(float4(rayDirection, hitT)));
    wr64SkyCapture.Store4(offset + 64, asuint(skyColor));
    wr64SkyCapture.Store4(offset + 80, uint4(geometry, primitive, asuint(transmission), asuint(finalAlpha)));
    wr64SkyCapture.Store4(offset + 96, asuint(float4(diagnostic.planeY, diagnostic.radialAlpha,
        diagnostic.uvResidual, diagnostic.determinant)));
    wr64SkyCapture.Store4(offset + 112, asuint(float4(diagnostic.uv, diagnostic.cloudAlpha, diagnostic.backdropAlpha)));
#endif
}

bool wr64FanColor(uint4 fan, float3 camera, float3 direction, out float4 color) {
    color = 0;
    if (fan.w == 0 || fan.z == 0 || fan.z > 6) return false;

    // A directional lookup starts at the sky camera, not the water surface.
    // Used for the native background cone and as a safe fallback for a cloud
    // fan whose presentation geometry cannot define a continuous UV chart.
    float nearest = 3.402823466e+38f;
    uint3 nearestIndices = 0;
    float2 nearestBarycentric = 0;
    bool found = false;
    const RenderParams fanParams = DynamicRenderParams[instanceRenderIndices[fan.y].instanceIndex];
    const bool cull = renderFlagCulling(fanParams.flags);
    [loop] for (uint face = 0; face < fan.z; ++face) {
        uint3 indices = wr64Indices.Load3((fan.x + face * 3) * 4);
        float3 a = asfloat(wr64Positions.Load3(indices.x * 16));
        float3 e1 = asfloat(wr64Positions.Load3(indices.y * 16)) - a;
        float3 e2 = asfloat(wr64Positions.Load3(indices.z * 16)) - a;
        float3 p = cross(direction, e2);
        float determinant = dot(e1, p);
        float edgeScale = sqrt(dot(e1, e1) * dot(e2, e2));
        if (!isfinite(edgeScale) || edgeScale < 1e-12f ||
            abs(determinant) <= edgeScale * 1e-7f) continue;
        // RSP already reverses front-culled indices into the native back-cull
        // convention. Keep that sidedness for the directional lookup: the sky
        // camera can leave the finite background cone during the opening, and
        // its near entry face must not replace the visible far sky with white
        // horizon texels merely because it is the closest intersection.
        if (cull && determinant < 0) continue;
        float3 delta = camera - a;
        float3 q = cross(delta, e1);
        float2 b = float2(dot(delta, p), dot(direction, q)) / determinant;
        float distance = dot(e2, q) / determinant;
        if (!all(isfinite(float3(b, distance))) || distance <= 1e-4f || distance >= nearest ||
            any(b < -1e-5f) || b.x + b.y > 1.00001f) continue;
        nearest = distance;
        nearestIndices = indices;
        b = max(b, 0.0f);
        nearestBarycentric = b / max(1.0f, b.x + b.y);
        found = true;
    }
    if (found) color = wr64NativeColor(fan.y, nearestIndices, nearestBarycentric, true, -1);
    return found;
}

float2 wr64ChartBarycentric(float2 delta, float2 e1, float2 e2, float determinant) {
    return float2(delta.x * e2.y - delta.y * e2.x,
                  e1.x * delta.y - e1.y * delta.x) / determinant;
}

bool wr64CloudSectorCoordinates(float2 chartPoint, out uint3 basis, out float2 barycentric) {
    basis = 0; barycentric = 0;
    if (wr64Sky.z != 6) return false;
    uint3 faces[6];
    [unroll] for (uint face = 0; face < 6; ++face)
        faces[face] = wr64Indices.Load3((wr64Sky.x + face * 3) * 4);
    // Only the proven closed six-sector fan may extend beyond its finite
    // perimeter. UV rebasing can invalidate a single affine fit while every
    // native sector remains a valid, continuous piecewise-linear chart.
    uint center = 0, centers = 0;
    [unroll] for (uint corner = 0; corner < 3; ++corner) {
        uint candidate = faces[0][corner];
        bool common = true;
        [unroll] for (uint face = 1; face < 6; ++face)
            common = common && any(faces[face] == candidate);
        if (common) { center = candidate; ++centers; }
    }
    if (centers != 1) return false;
    float orientation = 0;
    [unroll] for (uint face = 0; face < 6; ++face) {
        uint3 indices = faces[face];
        if (indices.y == center) indices = indices.yzx;
        else if (indices.z == center) indices = indices.zxy;
        if (indices.x != center || indices.y == center || indices.z == center ||
            indices.y == indices.z) return false;
        faces[face] = indices;
        float2 a = asfloat(wr64Positions.Load3(indices.x * 16)).xz;
        float2 e1 = asfloat(wr64Positions.Load3(indices.y * 16)).xz - a;
        float2 e2 = asfloat(wr64Positions.Load3(indices.z * 16)).xz - a;
        float determinant = e1.x * e2.y - e1.y * e2.x;
        float scale = length(e1) * length(e2);
        if (!isfinite(scale) || !isfinite(determinant) || scale < 1e-6f ||
            abs(determinant) < max(1e-6f, scale * 1e-5f)) return false;
        if (face == 0) orientation = determinant;
        else if ((orientation > 0) != (determinant > 0)) return false;
    }
    uint first = faces[0].y, current = first, visited = 0;
    [unroll] for (uint edge = 0; edge < 6; ++edge) {
        uint next = 0, matches = 0;
        [unroll] for (uint face = 0; face < 6; ++face) {
            if ((visited & (1u << face)) == 0 && faces[face].y == current) {
                next = face; ++matches;
            }
        }
        if (matches != 1) return false;
        visited |= 1u << next;
        current = faces[next].z;
    }
    if (current != first || visited != 63) return false;
    bool found = false;
    uint interiorMatches = 0;
    [unroll] for (uint face = 0; face < 6; ++face) {
        uint3 indices = faces[face];
        float2 a = asfloat(wr64Positions.Load3(indices.x * 16)).xz;
        float2 e1 = asfloat(wr64Positions.Load3(indices.y * 16)).xz - a;
        float2 e2 = asfloat(wr64Positions.Load3(indices.z * 16)).xz - a;
        float determinant = e1.x * e2.y - e1.y * e2.x;
        float2 b = wr64ChartBarycentric(chartPoint - a, e1, e2, determinant);
        if (!all(isfinite(b))) return false;
        if (all(b >= -1e-5f)) {
            if (all(b > 1e-5f)) ++interiorMatches;
            if (!found) { basis = indices; barycentric = max(b, 0.0f); found = true; }
        }
    }
    // Adjacent sectors agree on their shared radial edge. Multiple strictly
    // interior matches instead mean overlapping/corrupt geometry.
    return found && interiorMatches <= 1;
}

bool wr64CloudColor(float3 direction, out float4 color, out bool validChart,
    out Wr64SkyLookupDiagnostic diagnostic) {
    diagnostic = (Wr64SkyLookupDiagnostic)0;
    diagnostic.reason = 1;
    color = 0;
    validChart = false;
    if (wr64Sky.w == 0 || wr64Sky.z == 0 || wr64Sky.z > 6 || wr64SkyCloudParams.z != 1 ||
        !all(isfinite(wr64SkyCloudParams.xy)) ||
        wr64SkyCloudParams.x < -1 || wr64SkyCloudParams.x > -1e-6f ||
        wr64SkyCloudParams.y <= 0 || wr64SkyCloudParams.y > 4096 ||
        -wr64SkyCloudParams.y / wr64SkyCloudParams.x > 1e7f) return false;

    // The game projects a tiled cloud texture onto a horizontal plane. Fit its
    // actual presentation UVs, which already contain the native camera-height
    // projection and scrolling; do not replace them with a spherical mapping.
    uint3 basis = 0;
    float3 origin = 0;
    float2 e1 = 0, e2 = 0;
    float determinant = 0;
    [loop] for (uint face = 0; face < wr64Sky.z; ++face) {
        uint3 indices = wr64Indices.Load3((wr64Sky.x + face * 3) * 4);
        float3 a = asfloat(wr64Positions.Load3(indices.x * 16));
        float2 d1 = asfloat(wr64Positions.Load3(indices.y * 16)).xz - a.xz;
        float2 d2 = asfloat(wr64Positions.Load3(indices.z * 16)).xz - a.xz;
        float det = d1.x * d2.y - d1.y * d2.x;
        if (isfinite(det) && abs(det) > abs(determinant)) {
            determinant = det; basis = indices; origin = a; e1 = d1; e2 = d2;
        }
    }
    float edgeScale = length(e1) * length(e2);
    diagnostic.reason = 2;
    diagnostic.planeY = origin.y;
    diagnostic.determinant = determinant;
    if (!all(isfinite(origin)) || !isfinite(edgeScale) || edgeScale < 1e-6f ||
        abs(determinant) < max(1e-6f, edgeScale * 1e-5f)) return false;
    float2 uv0 = asfloat(wr64Texcoords.Load2(basis.x * 8));
    float2 uv1 = asfloat(wr64Texcoords.Load2(basis.y * 8)) - uv0;
    float2 uv2 = asfloat(wr64Texcoords.Load2(basis.z * 8)) - uv0;
    diagnostic.reason = 3;
    if (!all(isfinite(float4(uv0, uv1))) || !all(isfinite(uv2))) return false;
    float heightTolerance = 0.025f + max(length(e1), length(e2)) * 1e-6f;
    bool affineUV = true;
    [loop] for (uint checkFace = 0; checkFace < wr64Sky.z; ++checkFace) {
        uint3 indices = wr64Indices.Load3((wr64Sky.x + checkFace * 3) * 4);
        [unroll] for (uint corner = 0; corner < 3; ++corner) {
            float3 p = asfloat(wr64Positions.Load3(indices[corner] * 16));
            float2 uv = asfloat(wr64Texcoords.Load2(indices[corner] * 8));
            float2 b = wr64ChartBarycentric(p.xz - origin.xz, e1, e2, determinant);
            float2 expectedUV = uv0 + uv1 * b.x + uv2 * b.y;
            // Native s16 UVs are quantized to 1/32 texel. A rebased/interpolated
            // UV field need not be globally affine even on a valid native fan.
            diagnostic.reason = 4;
            if (!all(isfinite(p)) || !all(isfinite(float4(uv, expectedUV))) ||
                abs(p.y - origin.y) > heightTolerance) return false;
            diagnostic.uvResidual = max(diagnostic.uvResidual, max(abs(uv.x - expectedUV.x), abs(uv.y - expectedUV.y)));
            affineUV = affineUV && all(abs(uv - expectedUV) <= 0.04f);
        }
    }
    validChart = true;
    diagnostic.reason = 5;
    if (!all(isfinite(direction)) || direction.y <= 1e-7f) return false;
    float distance = (origin.y - wr64SkyCamera.y) / direction.y;
    diagnostic.reason = 6;
    if (!isfinite(distance) || distance <= 1e-4f) return false;
    float2 delta = direction.xz * distance;
    // Re-evaluate the native radial alpha rule continuously instead of
    // interpolating seven quantized vertex alphas. This lets clouds fade out
    // naturally beyond the finite fan without exposing its polygon boundary.
    float alpha = saturate((length(delta) * wr64SkyCloudParams.x + wr64SkyCloudParams.y) / 255.0f);
    diagnostic.radialAlpha = alpha;
    diagnostic.reason = 7;
    if (alpha <= 0) return false;
    float2 b = wr64ChartBarycentric(wr64SkyCamera.xz - origin.xz + delta, e1, e2, determinant);
    diagnostic.reason = 8;
    if (!all(isfinite(b))) return false;
    if (!affineUV && !wr64CloudSectorCoordinates(wr64SkyCamera.xz + delta, basis, b)) {
        diagnostic.reason = 9;
        validChart = false;
        return false;
    }
    color = wr64NativeColor(wr64Sky.y, basis, b, true, alpha);
    if (wr64SkyCloudParams.w == 1) {
        diagnostic.uv = asfloat(wr64Texcoords.Load2(basis.x * 8)) * (1 - b.x - b.y)
            + asfloat(wr64Texcoords.Load2(basis.y * 8)) * b.x
            + asfloat(wr64Texcoords.Load2(basis.z * 8)) * b.y;
    }
    diagnostic.reason = color.a > 0 ? 11 : 10;
    return color.a > 0;
}

bool wr64SkyColor(float3 direction, out float4 color, out Wr64SkyLookupDiagnostic diagnostic) {
    float4 backdrop = 0, clouds = 0;
    bool backgroundHit = wr64FanColor(wr64SkyBackdrop, wr64SkyBackdropCamera.xyz, direction, backdrop);
    // Native draw order: background, physical celestial bodies, then clouds.
    bool celestialHit = wr64CelestialColor(direction, backdrop);
    bool validChart;
    bool cloudHit = wr64CloudColor(direction, clouds, validChart, diagnostic);
    if (!validChart) cloudHit = wr64FanColor(wr64Sky, wr64SkyCamera.xyz, direction, clouds);
    diagnostic.flags = (backgroundHit ? 1u : 0u) | (cloudHit ? 2u : 0u) |
        (validChart ? 4u : 0u) | (celestialHit ? 8u : 0u);
    diagnostic.cloudAlpha = clouds.a;
    diagnostic.backdropAlpha = backdrop.a;
    // Both samplers return straight native material color. The background's
    // original texture/combiner sits behind the cloud alpha, just as on screen.
    float alpha = clouds.a + backdrop.a * (1 - clouds.a);
    color = float4((clouds.rgb * clouds.a + backdrop.rgb * backdrop.a * (1 - clouds.a)) /
        max(alpha, 1e-8f), alpha);
    return backgroundHit || celestialHit || cloudHit;
}

// Native water is retained whenever the reflected direction hits scenery.
// Only visibility is traced; no RT object color, beam or shadow is evaluated.
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
#ifdef WR64_RASTER_SHADOWS
    wr64ApplyRasterShadowNativeWater(wr64RasterWaterShadowTransmission(worldPosition, wr64ShadowReceiverNormal),
        pixelColor, pixelAlpha);
#endif
    float3 n = cross(ddx(worldPosition), ddy(worldPosition));
    if (wr64SmoothNormals != 0 && all(isfinite(reflectionNormal)) &&
        dot(reflectionNormal, reflectionNormal) > 1e-12f) n = reflectionNormal;
    float len2 = dot(n, n);
    if (wr64Enabled == 0 || !isfinite(len2) || len2 < 1e-12f) return;
    n *= rsqrt(len2);
    float3 viewDelta = wr64Camera.xyz - worldPosition;
    float viewLength = length(viewDelta);
    if (!isfinite(viewLength) || viewLength < 1e-5f) return;
    float3 v = viewDelta / viewLength;
    if (dot(n, v) < 0) n = -n;

    RayDesc ray;
    ray.Origin = worldPosition + n * 0.5f;
    ray.Direction = reflect(-v, n);
    ray.TMin = 0.5f;
    ray.TMax = wr64ReflectionMaxDistance();
    {
        RayQuery<RAY_FLAG_SKIP_PROCEDURAL_PRIMITIVES> query;
        query.TraceRayInline(wr64Scene, RAY_FLAG_NONE, 0xff, ray);
        while (query.Proceed()) {
            if (query.CandidateType() == CANDIDATE_NON_OPAQUE_TRIANGLE &&
                wr64CandidateCovered(query.CandidateGeometryIndex(), query.CandidatePrimitiveIndex(),
                    query.CandidateTriangleBarycentrics())) {
                query.CommitNonOpaqueTriangleHit();
            }
        }
        if (query.CommittedStatus() == COMMITTED_TRIANGLE_HIT) return;
    }
    float4 skyColor;
    Wr64SkyLookupDiagnostic diagnostic;
    if (!wr64SkyColor(ray.Direction, skyColor, diagnostic) || !all(isfinite(skyColor)) || skyColor.a <= 0) return;
    const float waterIOR = 1.333f;
    const float normalReflectance = (waterIOR - 1) / (waterIOR + 1);
    const float f0 = normalReflectance * normalReflectance;
    const float fresnel = f0 + (1 - f0) * pow(1 - saturate(dot(n, v)), 5.0f);
    const float reflectedAlpha = saturate(fresnel * wr64Strength) * skyColor.a;
    const float transmittedAlpha = saturate(pixelAlpha.a) * (1 - reflectedAlpha);
    const float combinedAlpha = reflectedAlpha + transmittedAlpha;
    if (reflectedAlpha > 0 && combinedAlpha > 0) {
        pixelColor.rgb = (skyColor.rgb * reflectedAlpha + pixelColor.rgb * transmittedAlpha) / combinedAlpha;
        pixelAlpha.a = combinedAlpha;
    }
    // Preserve the native coverage channel pixelColor.a.
}
