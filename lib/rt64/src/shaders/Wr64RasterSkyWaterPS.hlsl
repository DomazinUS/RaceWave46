// Sky-only water reflection. Ordinary raster depth/coverage still decide
// which water fragments are visible; the shader does not trace scene objects.
#define DYNAMIC_RENDER_PARAMS
#define PSMain Wr64UnusedRasterPSMain
#include "RasterPS.hlsl"
#undef PSMain
#include "Wr64WaterParams.hlsli"
#ifdef WR64_RASTER_SHADOWS
#include "Wr64RasterShadow.hlsli"
#endif

Texture2D<float4> wr64RasterSky : register(t72, space0);

float4 wr64SampleRasterSky(float3 direction) {
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
    float4 sky = wr64SampleRasterSky(reflect(-v, n));
    if (!all(isfinite(sky)) || sky.a <= 0) return;

    const float waterIOR = 1.333f;
    const float normalReflectance = (waterIOR - 1) / (waterIOR + 1);
    const float f0 = normalReflectance * normalReflectance;
    float fresnel = saturate((f0 + (1 - f0) * pow(1 - saturate(dot(n, v)), 5.0f)) * wr64Strength);
    float reflectedAlpha = fresnel * sky.a;
    float transmittedAlpha = saturate(pixelAlpha.a) * (1 - reflectedAlpha);
    float combinedAlpha = reflectedAlpha + transmittedAlpha;
    if (reflectedAlpha > 0 && combinedAlpha > 0) {
        pixelColor.rgb = (sky.rgb * fresnel + pixelColor.rgb * transmittedAlpha) / combinedAlpha;
        pixelAlpha.a = combinedAlpha;
    }
    // Preserve pixelColor.a, which holds native coverage rather than opacity.
}
