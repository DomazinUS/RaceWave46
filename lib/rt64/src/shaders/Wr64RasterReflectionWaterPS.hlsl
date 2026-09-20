// Planar scenery capture combined with independently selected sky and shadows.
// Only the optional RT-sky variant declares a ray scene.
#define DYNAMIC_RENDER_PARAMS
#define PSMain Wr64ReflectionUnusedPSMain
#include "RasterPS.hlsl"
#undef PSMain
#include "Wr64WaterParams.hlsli"
#include "Wr64RasterReflectionSample.hlsli"
#ifdef WR64_RASTER_SHADOWS
#include "Wr64RasterShadow.hlsli"
#endif
#ifdef WR64_PLANAR_CACHED_SKY
#include "Wr64RasterReflectionCachedSky.hlsli"
#elif defined(WR64_PLANAR_RT_SKY)
#include "Wr64RasterReflectionRaySky.hlsli"
#endif

void PSMain(float4 position : SV_POSITION, float2 uv : TEXCOORD0,
    float4 smoothColor : COLOR0, nointerpolation float4 flatColor : COLOR1,
    float3 worldPosition : TEXCOORD1, float3 reflectionNormal : TEXCOORD2,
    bool frontFace : SV_IsFrontFace,
    WR64_RT_COLOR_OUTPUT out float4 pixelColor : SV_TARGET0,
    WR64_RT_ALPHA_OUTPUT out float4 pixelAlpha : SV_TARGET1) {
    const float3 geometricNormal = cross(ddx(worldPosition), ddy(worldPosition));
    if (!RasterPS(getRenderParams(), position, uv, smoothColor, flatColor,
        frontFace, pixelColor, pixelAlpha)) discard;
    const float nativeAlpha = saturate(pixelAlpha.a);
    const float3 nativeColor = pixelColor.rgb;
    float transmission = 1;
#ifdef WR64_RASTER_SHADOWS
    transmission = wr64RasterWaterShadowTransmission(worldPosition, geometricNormal);
    wr64ApplyRasterShadowNativeWater(transmission, pixelColor, pixelAlpha);
#endif
    float3 n = geometricNormal;
    if (wr64SmoothNormals != 0 && all(isfinite(reflectionNormal)) &&
        dot(reflectionNormal, reflectionNormal) > 1e-12f) n = reflectionNormal;
    const float normalSquared = dot(n, n);
    const float3 viewDelta = wr64Camera.xyz - worldPosition;
    const float viewLength = length(viewDelta);
    if (wr64Enabled == 0 || !isfinite(normalSquared) || normalSquared < 1e-12f ||
        !isfinite(viewLength) || viewLength < 1e-5f) return;
    n *= rsqrt(normalSquared);
    const float3 v = viewDelta / viewLength;
    if (dot(n, v) < 0) n = -n;
    const float4 objects = wr64SampleRasterReflection(worldPosition, n, v);
    float4 sky = 0;
    // A fully covered planar reflection already identifies the visible object;
    // do not evaluate an expensive native sky or visibility ray behind it.
    if (objects.a < 1) {
#ifdef WR64_PLANAR_CACHED_SKY
        sky = wr64ReflectionCachedSky(reflect(-v, n));
#elif defined(WR64_PLANAR_RT_SKY)
        sky = wr64ReflectionRaySky(worldPosition, n, reflect(-v, n));
#endif
    }
    if (objects.a <= 0 && sky.a <= 0) return;
    const float anglePower = pow(1 - saturate(dot(n, v)), 5.0f);
    const float strength = isfinite(wr64ReflectionOptions.y) ? saturate(wr64ReflectionOptions.y) : 0;
    const float objectWeight = saturate((0.08f + 0.35f * anglePower) * strength);
    const float waterIOR = 1.333f;
    const float normalReflectance = (waterIOR - 1) / (waterIOR + 1);
    const float f0 = normalReflectance * normalReflectance;
    const float skyWeight = saturate((f0 + (1 - f0) * anglePower) * wr64Strength) * (1 - objects.a);
    const float skyAlpha = skyWeight * sky.a;
    const float combinedAlpha = pixelAlpha.a + (1 - pixelAlpha.a) * skyAlpha;
    if (combinedAlpha <= 0) return;
    // Split coverage between opaque captured objects and the independent sky.
    // Preserve the validated object response (A*F*object) even on shadowed
    // water; only native water/transmission receives the weak surface mask.
    const float3 premultiplied = nativeAlpha * transmission *
        (1 - objectWeight * objects.a - skyAlpha) * nativeColor +
        nativeAlpha * objectWeight * objects.rgb + skyWeight * sky.rgb;
    pixelColor.rgb = premultiplied / combinedAlpha;
    pixelAlpha.a = combinedAlpha;
    // pixelColor.a remains native coverage, not reflected opacity.
}
