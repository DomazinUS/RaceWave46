// Presentation-to-presentation motion of proven native rider/craft geometry.
#define DYNAMIC_RENDER_PARAMS
#define VSMain Wr64MotionBaseVSMain
#include "RasterVS.hlsl"
#undef VSMain

ByteAddressBuffer wr64MotionPositions : register(t27, space0);
ByteAddressBuffer wr64MotionVelocities : register(t29, space0);
struct Wr64MotionDraw {
    float4x4 previousViewProjection;
    float4 viewportScale;
    float4 viewportTranslate;
};
StructuredBuffer<Wr64MotionDraw> wr64MotionDraws : register(t70, space0);

void VSMain(float4 position : POSITION, float2 uv : TEXCOORD, float4 color : COLOR,
    uint vertexId : SV_VertexID, out float4 clip : SV_POSITION,
    out float2 outUV : TEXCOORD0, out float4 smoothColor : COLOR0,
    out float4 flatColor : COLOR1, out float4 currentClip : TEXCOORD1,
    out float4 previousClip : TEXCOORD2) {
    RenderParams rp = getRenderParams();
    RasterVS(rp, position, uv, color, clip, outUV, smoothColor, flatColor);
    currentClip = clip;
    previousClip = clip;
    Wr64MotionDraw d = wr64MotionDraws[gConstants.renderIndex];
    float3 world = asfloat(wr64MotionPositions.Load3(vertexId * 16));
    float3 velocity = asfloat(wr64MotionVelocities.Load3(vertexId * 16));
    float4 prev = mul(d.previousViewProjection, float4(world - velocity, 1));
    // Invalid/cut history has no motion; never stretch a near-plane crossing.
    if (d.viewportScale.w != 1 || !all(isfinite(prev)) || prev.w <= 0.01 ||
        !all(isfinite(world)) || !all(isfinite(velocity)) || clip.w <= 0.01) return;
    float3 ndc = prev.xyz / float3(prev.w, -prev.w, prev.w);
    float4 screen = float4(ndc * d.viewportScale.xyz + d.viewportTranslate.xyz, prev.w);
    float2 unusedUV; float4 unusedSmooth, unusedFlat;
    RasterVS(rp, screen, uv, color, previousClip, unusedUV, unusedSmooth, unusedFlat);
}
