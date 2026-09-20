// Native raster evaluation plus presentation-time world position for the
// selected static shore receivers. Water geometry/adjacency is not involved.
#define DYNAMIC_RENDER_PARAMS
#define VSMain Wr64WorldBaseVSMain
#include "RasterVS.hlsl"
#undef VSMain

ByteAddressBuffer wr64WorldPositions : register(t27, space0);

void VSMain(float4 position : POSITION, float2 uv : TEXCOORD, float4 color : COLOR,
    uint vertexId : SV_VertexID, out float4 clip : SV_POSITION,
    out float2 outUV : TEXCOORD0, out float4 smoothColor : COLOR0,
    out float4 flatColor : COLOR1, out float3 worldPosition : TEXCOORD1) {
    RasterVS(getRenderParams(), position, uv, color, clip, outUV, smoothColor, flatColor);
    worldPosition = asfloat(wr64WorldPositions.Load3(vertexId * 16));
}
