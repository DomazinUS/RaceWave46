#define DYNAMIC_RENDER_PARAMS
#define VSMain Wr64ReflectionUnusedVSMain
#include "RasterVS.hlsl"
#undef VSMain
#include "Wr64RasterReflectionParams.hlsli"
ByteAddressBuffer wr64WorldPositions : register(t27, space0);

void VSMain(float4 position : POSITION, float2 uv : TEXCOORD, float4 color : COLOR,
    uint vertexId : SV_VertexID, out float4 clip : SV_POSITION,
    out float2 outUV : TEXCOORD0, out float4 smoothColor : COLOR0,
    out float4 flatColor : COLOR1, out float planeDistance : SV_ClipDistance0) {
    float4 unusedClip;
    RasterVS(getRenderParams(), position, uv, color, unusedClip, outUV, smoothColor, flatColor);
    const float3 worldPosition = asfloat(wr64WorldPositions.Load3(vertexId * 16));
    clip = wr64RasterReflectionClip(worldPosition);
    planeDistance = dot(wr64ReflectionPlane.xyz, worldPosition) + wr64ReflectionPlane.w - wr64ReflectionOptions.w;
}
