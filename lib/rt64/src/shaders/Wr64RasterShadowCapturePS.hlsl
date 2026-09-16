// Native cutout evaluation copied from Wr64WaterMaterial; no scene/ray resources.
#define DYNAMIC_RENDER_PARAMS
#define PSMain Wr64ShadowUnusedPSMain
#include "RasterPS.hlsl"
#undef PSMain
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


float PSMain(float4 position : SV_POSITION, float2 uv : TEXCOORD0,
    float4 smoothColor : COLOR0, nointerpolation float4 flatColor : COLOR1) : SV_TARGET0 {
    if ((gConstants.padding.x & 2u) != 0) {
        const RenderParams rp = getRenderParams();
        float4 shade = smoothColor;
        if (!renderFlagSmoothShade(rp.flags)) shade.rgb = flatColor.rgb;
        float alphaCompare;
        const float4 color = wr64NativeMaterialValues(gConstants.renderIndex, uv, shade, false, alphaCompare);
        if (!wr64MaterialCovered(gConstants.renderIndex, color, alphaCompare)) discard;
    }
    return position.z;
}
