// Wave Race 64 HUD/menu-only texture reconstruction.
// This is an original Scale2x-style implementation, not xBRZ. It only operates
// on decoded native UI tiles explicitly selected by the Wave Race frontend.

#pragma once

float4 wr64UiPremultiply(float4 color) {
    return float4(color.rgb * color.a, color.a);
}

float4 wr64UiUnpremultiply(float4 color) {
    return (color.a > (1.0f / 65536.0f)) ? float4(color.rgb / color.a, color.a) : 0.0f;
}

float4 wr64UiSample(const RDPTile rdpTile, const GPUTile gpuTile, int2 texel, uint tlut) {
    float4 color;
    if (rdpTile.nativeSampler == NATIVE_SAMPLER_NONE) {
        color = clampWrapMirrorSample(rdpTile, gpuTile, gpuTile.tcScale, texel, tlut, false, 0);
    }
    else {
        color = sampleTextureNative(gTextures[NonUniformResourceIndex(gpuTile.textureIndex)],
            rdpTile.nativeSampler, texel, gpuTile.textureDimensions.xy);
    }

    // Interpolate premultiplied values so arbitrary RGB in transparent texels
    // cannot create a dark/colored fringe around lettering and sprite edges.
    return wr64UiPremultiply(color);
}

bool wr64UiSimilar(float4 a, float4 b) {
    // Alpha participates in the comparison. The small tolerance accommodates
    // decoded 4-/5-bit values while preserving distinct outlines and shadows.
    const float4 difference = abs(a - b);
    return max(max(difference.r, difference.g), max(difference.b, difference.a)) <= (1.0f / 16.0f);
}

float4 wr64UiCorner(float4 center, float4 north, float4 west, float4 east, float4 south, int2 quadrant) {
    float4 vertical = (quadrant.y == 0) ? north : south;
    float4 horizontal = (quadrant.x == 0) ? west : east;

    // Reconstruct a corner only when adjacent edges agree and both opposing
    // directions differ. A one-pixel line or isolated dot therefore survives.
    if (!wr64UiSimilar(north, south) && !wr64UiSimilar(west, east) && wr64UiSimilar(vertical, horizontal)) {
        return (vertical + horizontal) * 0.5f;
    }

    return center;
}

float4 wr64UiVirtualTexel(float4 samples[12], int2 parentOffset, int2 quadrant) {
    const int x = parentOffset.x;
    const int y = parentOffset.y;
    float4 center = samples[y * 2 + x];
    float4 north = (y == 0) ? samples[4 + x] : samples[x];
    float4 south = (y == 0) ? samples[2 + x] : samples[6 + x];
    float4 west = (x == 0) ? samples[8 + y] : samples[y * 2];
    float4 east = (x == 0) ? samples[y * 2 + 1] : samples[10 + y];
    return wr64UiCorner(center, north, west, east, south, quadrant);
}

float4 wr64UiEnhanced(const RDPTile rdpTile, const GPUTile gpuTile, float2 texelCoord, uint tlut) {
    // Each source pixel contributes four virtual samples at +/- 1/4 texel.
    // Interpolation crosses source-pixel boundaries using the same virtual
    // grid on both sides, avoiding seams from per-pixel corner overlays.
    const float2 virtualCoord = texelCoord * 2.0f + 0.5f;
    const int2 virtualBase = int2(floor(virtualCoord));
    const int2 sourceBase = int2(floor(float2(virtualBase) * 0.5f));
    float4 samples[12];
    samples[0] = wr64UiSample(rdpTile, gpuTile, sourceBase, tlut);
    samples[1] = wr64UiSample(rdpTile, gpuTile, sourceBase + int2(1, 0), tlut);
    samples[2] = wr64UiSample(rdpTile, gpuTile, sourceBase + int2(0, 1), tlut);
    samples[3] = wr64UiSample(rdpTile, gpuTile, sourceBase + int2(1, 1), tlut);
    samples[4] = wr64UiSample(rdpTile, gpuTile, sourceBase + int2(0, -1), tlut);
    samples[5] = wr64UiSample(rdpTile, gpuTile, sourceBase + int2(1, -1), tlut);
    samples[6] = wr64UiSample(rdpTile, gpuTile, sourceBase + int2(0, 2), tlut);
    samples[7] = wr64UiSample(rdpTile, gpuTile, sourceBase + int2(1, 2), tlut);
    samples[8] = wr64UiSample(rdpTile, gpuTile, sourceBase + int2(-1, 0), tlut);
    samples[9] = wr64UiSample(rdpTile, gpuTile, sourceBase + int2(-1, 1), tlut);
    samples[10] = wr64UiSample(rdpTile, gpuTile, sourceBase + int2(2, 0), tlut);
    samples[11] = wr64UiSample(rdpTile, gpuTile, sourceBase + int2(2, 1), tlut);

    float4 corners[4];
    [unroll]
    for (uint i = 0; i < 4; i++) {
        int2 virtualTexel = virtualBase + int2(i & 1, i >> 1);
        int2 parent = int2(floor(float2(virtualTexel) * 0.5f));
        int2 quadrant = virtualTexel - parent * 2;
        corners[i] = wr64UiVirtualTexel(samples, parent - sourceBase, quadrant);
    }

    float2 fraction = frac(virtualCoord);
    return wr64UiUnpremultiply(lerp(lerp(corners[0], corners[1], fraction.x),
        lerp(corners[2], corners[3], fraction.x), fraction.y));
}

float4 wr64UiLight(const RDPTile rdpTile, const GPUTile gpuTile, float2 texelCoord, uint tlut) {
    const int2 base = int2(floor(texelCoord));
    float4 sample00 = wr64UiSample(rdpTile, gpuTile, base, tlut);
    float4 sample10 = wr64UiSample(rdpTile, gpuTile, base + int2(1, 0), tlut);
    float4 sample01 = wr64UiSample(rdpTile, gpuTile, base + int2(0, 1), tlut);
    float4 sample11 = wr64UiSample(rdpTile, gpuTile, base + int2(1, 1), tlut);

    // Ordinary bilinear reconstruction softens native pixel boundaries even
    // at integer magnification. Sharp-bilinear plateaus would reproduce point
    // sampling exactly at those scales and make this option appear inactive.
    float2 blend = frac(texelCoord);
    return wr64UiUnpremultiply(lerp(lerp(sample00, sample10, blend.x),
        lerp(sample01, sample11, blend.x), blend.y));
}

bool wr64UiCanFilter(uint mode, OtherMode otherMode, const GPUTile gpuTile, float2 footprint) {
    return (mode >= 1) && (mode <= 2) && (otherMode.cycleType() != G_CYC_COPY)
        && !gpuTileFlagRawTMEM(gpuTile.flags) && !gpuTileFlagHighRes(gpuTile.flags)
        && !gpuTileFlagFromCopy(gpuTile.flags) && !gpuTileFlagAlphaIsCvg(gpuTile.flags)
        && !gpuTileFlagHasMipmaps(gpuTile.flags) && all(footprint <= 1.0f);
}
