#ifndef WR64_WATER_MATERIAL_INCLUDED
#define WR64_WATER_MATERIAL_INCLUDED

ByteAddressBuffer wr64FenceProxyVertices : register(t69, space0);

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

float3 wr64HitColor(uint geometryIndex, uint primitiveIndex, float2 barycentric) {
    uint4 geometry = wr64Geometry[geometryIndex];
    uint3 indices = wr64Indices.Load3((geometry.x + primitiveIndex * 3) * 4);
    return wr64NativeColor(geometry.y, indices, barycentric, false, -1).rgb;
}

// A cutout is tested with the same two distinct alpha values as RasterPS:
// first-cycle alpha for alpha compare, final-cycle alpha for coverage.
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

bool wr64ShadowCandidateCovered(uint geometryIndex, uint primitiveIndex, float2 barycentric) {
    const uint4 geometry = wr64Geometry[geometryIndex];
    if ((geometry.w & 8u) == 0) return wr64CandidateCovered(geometryIndex, primitiveIndex, barycentric);
    if ((geometry.w & 4u) != 0) return false;
    const uint first = (geometry.x + primitiveIndex * 3) * 48;
    const float3 b = float3(1-barycentric.x-barycentric.y,barycentric);
    const float2 uv = asfloat(wr64FenceProxyVertices.Load2(first+16))*b.x +
        asfloat(wr64FenceProxyVertices.Load2(first+48+16))*b.y +
        asfloat(wr64FenceProxyVertices.Load2(first+96+16))*b.z;
    float4 shade = asfloat(wr64FenceProxyVertices.Load4(first+32))*b.x +
        asfloat(wr64FenceProxyVertices.Load4(first+48+32))*b.y +
        asfloat(wr64FenceProxyVertices.Load4(first+96+32))*b.z;
    const RenderParams rp = DynamicRenderParams[instanceRenderIndices[geometry.y].instanceIndex];
    if (!renderFlagSmoothShade(rp.flags)) shade.rgb = asfloat(wr64FenceProxyVertices.Load3(first+32));
    float alphaCompareValue;
    const float4 color = wr64NativeMaterialValues(geometry.y,uv,shade,false,alphaCompareValue);
    return wr64MaterialCovered(geometry.y,color,alphaCompareValue);
}

#endif
