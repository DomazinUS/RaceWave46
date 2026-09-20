#ifndef WR64_RASTER_SKY_LOOKUP_INCLUDED
#define WR64_RASTER_SKY_LOOKUP_INCLUDED
// Bounded copy of the validated native sky/material lookup. Keep the existing
// RT shaders untouched while the independent raster capture is tested.
// Only native sky vertices/materials are read; no ray scene is declared.
#ifdef __spirv__
// Keep the large native RDP sampler shared between inline-ray call sites.
// Exhaustive SPIR-V inlining otherwise overflows the compiler's ID space.
[noinline]
#endif
float4 wr64NativeMaterialValues(uint drawIndex, float2 uv, float4 shade,
    bool sky, out float alphaCompareValue) {
    RenderIndices ri = instanceRenderIndices[drawIndex];
    RenderParams rp = DynamicRenderParams[ri.instanceIndex];
    OtherMode om = {rp.omL, rp.omH};
    RDPParams rdp = instanceRDPParams[ri.instanceIndex];
    float4 tex0 = float4(0, 0, 0, 1), tex1 = tex0;
    // Initial deterministic reflection uses native base-level texture sampling.
    // Explicit gradients avoid undefined derivatives inside divergent ray hits.
    if (renderFlagUsesTexture0(rp.flags) && ri.rdpTileCount > 0) {
        RDPTile tile = RDPTiles[ri.rdpTileIndex];
        if (!renderFlagDynamicTiles(rp.flags)) {
            tile.cms = renderCMS0(rp.flags); tile.cmt = renderCMT0(rp.flags);
            tile.nativeSampler = renderFlagNativeSampler0(rp.flags);
        }
        tex0 = sampleTexture(om, rp.flags, uv, 0.0f, 0.0f,
            tile, GPUTiles[ri.rdpTileIndex], false, 0);
    }
    if (renderFlagUsesTexture1(rp.flags) && ri.rdpTileCount > 0) {
        bool hardwareBug = om.cycleType() == G_CYC_1CYCLE;
        uint tileIndex = ri.rdpTileIndex + (hardwareBug ? 0 : min(1u, ri.rdpTileCount - 1));
        RDPTile tile = RDPTiles[tileIndex];
        if (!renderFlagDynamicTiles(rp.flags)) {
            tile.cms = hardwareBug ? renderCMS0(rp.flags) : renderCMS1(rp.flags);
            tile.cmt = hardwareBug ? renderCMT0(rp.flags) : renderCMT1(rp.flags);
            tile.nativeSampler = hardwareBug ? renderFlagNativeSampler0(rp.flags) : renderFlagNativeSampler1(rp.flags);
        }
        tex1 = sampleTexture(om, rp.flags, uv, 0.0f, 0.0f,
            tile, GPUTiles[tileIndex], hardwareBug, 0);
    }
    ColorCombiner cc = {rp.ccL, rp.ccH};
    ColorCombiner::Inputs inputs;
    inputs.otherMode = om;
    inputs.alphaOnly = false;
    inputs.texVal0 = tex0; inputs.texVal1 = tex1;
    inputs.primColor = rdp.primColor;
    inputs.shadeColor = shade;
    inputs.envColor = rdp.envColor;
    inputs.keyCenter = rdp.keyCenter; inputs.keyScale = rdp.keyScale;
    inputs.lodFraction = 0; inputs.primLodFrac = rdp.primLOD.x;
    inputs.noise = 0.5f;
    inputs.K4 = rdp.convertK[4] / 255.0f; inputs.K5 = rdp.convertK[5] / 255.0f;
    float4 color; float alpha;
    cc.run(inputs, color, alpha);
    alphaCompareValue = alpha;
    if (sky) {
        // Preserve native sky color and layer opacity. Its force-blend mode
        // returns straight RGB with the factor used to mix over its background.
        Blender::Inputs blender;
        blender.blendColor = rdp.blendColor;
        blender.fogColor = rdp.fogColor;
        blender.shadeAlpha = shade.a;
        color = Blender::run(om, rp.flags, blender, color, false);
    }
    return saturate(color);
}

float4 wr64NativeMaterial(uint drawIndex, uint3 indices, float2 barycentric, bool sky, float shadeAlpha, out float alphaCompareValue) {
    float3 b = float3(1.0f - barycentric.x - barycentric.y, barycentric);
    float2 uv = asfloat(wr64Texcoords.Load2(indices.x * 8)) * b.x
              + asfloat(wr64Texcoords.Load2(indices.y * 8)) * b.y
              + asfloat(wr64Texcoords.Load2(indices.z * 8)) * b.z;
    float4 shade = asfloat(wr64Colors.Load4(indices.x * 16)) * b.x
                 + asfloat(wr64Colors.Load4(indices.y * 16)) * b.y
                 + asfloat(wr64Colors.Load4(indices.z * 16)) * b.z;
    RenderParams rp = DynamicRenderParams[instanceRenderIndices[drawIndex].instanceIndex];
    if (!renderFlagSmoothShade(rp.flags)) shade.rgb = asfloat(wr64Colors.Load3(indices.x * 16));
    if (shadeAlpha >= 0) shade.a = shadeAlpha;
    return wr64NativeMaterialValues(drawIndex, uv, shade, sky, alphaCompareValue);
}

float4 wr64NativeColor(uint drawIndex, uint3 indices, float2 barycentric, bool sky, float shadeAlpha) {
    float alphaCompareValue;
    return wr64NativeMaterial(drawIndex, indices, barycentric, sky, shadeAlpha, alphaCompareValue);
}


#include "Wr64WaterCelestial.hlsli"

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


#endif
