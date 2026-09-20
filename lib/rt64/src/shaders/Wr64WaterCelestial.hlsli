// Native sun/moon/star rectangles reconstructed before the game's camera
// visibility cull. Sampling uses the original IA16 alpha bytes and primitive
// colors; the intensity channel is absent from these native color combiners.
float wr64CelestialTexel(uint offset, uint width, uint height, int2 p) {
    p = clamp(p, int2(0, 0), int2(width, height) - 1);
    uint address = offset + uint(p.y) * width + uint(p.x);
    uint word = address >> 2;
    return ((wr64CelestialAlpha[word >> 2][word & 3] >> ((address & 3) * 8)) & 255) / 255.0f;
}

float wr64CelestialAlphaAt(uint4 texture, float2 uv) {
    // Same clamped three-point reconstruction as native G_TF_BILERP. UVs
    // already include the native rectangle's start and dS/dX, dT/dY.
    uv = round(uv * 128.0f) / 128.0f;
    int2 p = int2(floor(uv));
    float2 f = frac(uv);
    float a00 = wr64CelestialTexel(texture.x, texture.y, texture.z, p);
    float a10 = wr64CelestialTexel(texture.x, texture.y, texture.z, p + int2(1, 0));
    float a01 = wr64CelestialTexel(texture.x, texture.y, texture.z, p + int2(0, 1));
    float a11 = wr64CelestialTexel(texture.x, texture.y, texture.z, p + int2(1, 1));
    return f.x + f.y < 1 ? a00 + (a10 - a00) * f.x + (a01 - a00) * f.y
        : a11 + (a01 - a11) * (1 - f.x) + (a10 - a11) * (1 - f.y);
}

bool wr64CelestialColor(float3 direction, inout float4 background) {
    if (wr64CelestialInfo.x == 0 || wr64CelestialInfo.x > WR64_RT_CELESTIAL_MAX) return false;
    float4 d = float4(direction, 0);
    float3 projected = float3(dot(wr64CelestialProjection[0], d),
        dot(wr64CelestialProjection[1], d), dot(wr64CelestialProjection[2], d));
    if (!all(isfinite(projected)) || projected.z <= 1e-6f) return false;
    float2 lookupPosition = projected.xy / projected.z;
    bool contributed = false;
    [loop] for (uint i = 0; i < wr64CelestialInfo.x; ++i) {
        Wr64RTCelestialRecord body = wr64CelestialBodies[i];
        if (!all(isfinite(body.bounds)) || !all(isfinite(body.uv)) || !all(isfinite(body.color)) ||
            any(body.bounds.zw <= body.bounds.xy) || any(lookupPosition < body.bounds.xy) || any(lookupPosition >= body.bounds.zw) ||
            body.texture.y == 0 || body.texture.z == 0 || body.texture.y > 32 || body.texture.z > 32 ||
            body.texture.w != 0 || body.texture.x > WR64_RT_CELESTIAL_ALPHA_VECTORS * 16 ||
            body.texture.y * body.texture.z > WR64_RT_CELESTIAL_ALPHA_VECTORS * 16 - body.texture.x) continue;
        float2 fraction = (lookupPosition - body.bounds.xy) / (body.bounds.zw - body.bounds.xy);
        float2 uv = body.uv.xy + fraction * body.uv.zw;
        if (!all(isfinite(uv)) || any(abs(uv) > 65536)) continue;
        float alpha = saturate(wr64CelestialAlphaAt(body.texture, uv) * body.color.a);
        if (alpha <= 0) continue;
        float remainingAlpha = background.a * (1 - alpha);
        float combinedAlpha = alpha + remainingAlpha;
        background = float4((saturate(body.color.rgb) * alpha + background.rgb * remainingAlpha) /
            max(combinedAlpha, 1e-8f), combinedAlpha);
        contributed = true;
    }
    return contributed;
}
