// Exact cached-sky lookup shared in semantics with Wr64RasterSkyWaterPS.
Texture2D<float4> wr64RasterSky : register(t72, space0);

float4 wr64ReflectionCachedSky(float3 direction) {
    uint width, height;
    wr64RasterSky.GetDimensions(width, height);
    if (width == 0 || height == 0 || !all(isfinite(direction))) return 0;
    const float pi = 3.14159265358979323846f;
    float2 uv = float2(frac(atan2(direction.x, direction.z) / (2 * pi) + 0.5f),
        acos(clamp(direction.y, -1.0f, 1.0f)) / pi);
    float2 texel = uv * float2(width, height) - 0.5f;
    int2 origin = int2(floor(texel));
    float2 f = frac(texel);
    int x0 = (origin.x + int(width)) % int(width), x1 = (x0 + 1) % int(width);
    int y0 = clamp(origin.y, 0, int(height) - 1), y1 = clamp(origin.y + 1, 0, int(height) - 1);
    float4 a = lerp(wr64RasterSky.Load(int3(x0, y0, 0)), wr64RasterSky.Load(int3(x1, y0, 0)), f.x);
    float4 b = lerp(wr64RasterSky.Load(int3(x0, y1, 0)), wr64RasterSky.Load(int3(x1, y1, 0)), f.x);
    return lerp(a, b, f.y);
}
