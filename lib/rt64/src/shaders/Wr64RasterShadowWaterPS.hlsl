#define DYNAMIC_RENDER_PARAMS
#define PSMain Wr64ShadowUnusedPSMain
#include "RasterPS.hlsl"
#undef PSMain
#include "Wr64WaterParams.hlsli"
#include "Wr64RasterShadow.hlsli"

void PSMain(float4 position : SV_POSITION, float2 uv : TEXCOORD0,
    float4 smoothColor : COLOR0, nointerpolation float4 flatColor : COLOR1,
    float3 worldPosition : TEXCOORD1, float3 reflectionNormal : TEXCOORD2,
    bool frontFace : SV_IsFrontFace,
    WR64_RT_COLOR_OUTPUT out float4 pixelColor : SV_TARGET0,
    WR64_RT_ALPHA_OUTPUT out float4 pixelAlpha : SV_TARGET1) {
    const float3 shadowReceiverNormal = cross(ddx(worldPosition), ddy(worldPosition));
    if (!RasterPS(getRenderParams(), position, uv, smoothColor, flatColor,
        frontFace, pixelColor, pixelAlpha)) discard;
    wr64ApplyRasterShadowNativeWater(wr64RasterWaterShadowTransmission(worldPosition, shadowReceiverNormal),
        pixelColor, pixelAlpha);
}
