#define DYNAMIC_RENDER_PARAMS
#define VSMain Wr64ShadowUnusedVSMain
#include "RasterVS.hlsl"
#undef VSMain
#define WR64_SHADOW_CAPTURE
#include "Wr64RasterShadow.hlsli"
ByteAddressBuffer wr64WorldPositions : register(t27, space0);

void VSMain(float4 position : POSITION, float2 uv : TEXCOORD, float4 color : COLOR,
    uint vertexId : SV_VertexID, out float4 clip : SV_POSITION,
    out float2 outUV : TEXCOORD0, out float4 smoothColor : COLOR0,
    out float4 flatColor : COLOR1) {
    // Native UV/shade semantics, but a light-space position without camera clips.
    float4 unusedClip;
    RasterVS(getRenderParams(), position, uv, color, unusedClip, outUV, smoothColor, flatColor);
    clip = wr64ShadowMapClip(asfloat(wr64WorldPositions.Load3(vertexId * 16)));
}
