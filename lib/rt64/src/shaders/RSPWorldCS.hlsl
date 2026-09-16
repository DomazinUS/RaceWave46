//
// RT64
//

#define GROUP_SIZE 64

struct RSPWorldCB {
    uint vertexStart;
    uint vertexCount;
    float prevFrameWeight;
    float curFrameWeight;
    uint wr64RtWater;
};

[[vk::push_constant]] ConstantBuffer<RSPWorldCB> gConstants : register(b0);
Buffer<float> srcPos : register(t1);
Buffer<float> srcVel : register(t2);
#ifdef __spirv__
// Match the native normal-color byte and world-transform index buffer views.
[[vk::image_format("r8i")]]
#endif
Buffer<int> srcNorm : register(t3);
#ifdef __spirv__
[[vk::image_format("r16ui")]]
#endif
Buffer<uint> srcIndices : register(t4);
StructuredBuffer<float4x4> worldMats : register(t5);
StructuredBuffer<float4x4> invTWorldMats : register(t6);
StructuredBuffer<float4x4> prevWorldMats : register(t7);
RWStructuredBuffer<float4> dstPos : register(u8);
RWStructuredBuffer<float4> dstNorm : register(u9);
RWStructuredBuffer<float4> dstVel : register(u10);
Buffer<float> srcTc : register(t11);
Buffer<float> srcTcVel : register(t12);
StructuredBuffer<uint4> wr64WaterFieldInfo : register(t13);
StructuredBuffer<float4> wr64WaterFieldPrevPosShiftX : register(t14);
StructuredBuffer<float4> wr64WaterFieldPrevTcShiftZ : register(t15);
StructuredBuffer<uint> wr64WaterFieldFaceIndices : register(t16);

#include "Wr64WaterVertex.hlsli"

[numthreads(GROUP_SIZE, 1, 1)]
void CSMain(uint vertexIndex : SV_DispatchThreadID) {
    if (vertexIndex >= gConstants.vertexCount) {
        return;
    }
    
    const uint vertexOffsetIndex = gConstants.vertexStart + vertexIndex;
    const uint transformIndex = srcIndices[vertexOffsetIndex];
    const uint posIndex = vertexOffsetIndex * 3;
    const uint normIndex = vertexOffsetIndex * 4;
    const float3 pos = float3(srcPos[posIndex + 0], srcPos[posIndex + 1], srcPos[posIndex + 2]);
    const float3 vel = float3(srcVel[posIndex + 0], srcVel[posIndex + 1], srcVel[posIndex + 2]);
    const float3 norm = float3(srcNorm[normIndex + 0], srcNorm[normIndex + 1], srcNorm[normIndex + 2]);
    float3 currentPos = pos - vel * (1.0f - gConstants.curFrameWeight);
    float3 previousPos = pos - vel * (1.0f - gConstants.prevFrameWeight);
    float2 unusedWaterTc;
    bool unusedWaterTcValid;
    if (gConstants.wr64RtWater != 0) {
        wr64EvaluateWaterVertex(vertexOffsetIndex, gConstants.curFrameWeight,
            currentPos, unusedWaterTc, unusedWaterTcValid);
        wr64EvaluateWaterVertex(vertexOffsetIndex, gConstants.prevFrameWeight,
            previousPos, unusedWaterTc, unusedWaterTcValid);
    }
    const float4 worldPos = mul(worldMats[transformIndex], float4(currentPos, 1.0f));
    const float4 worldNorm = all(norm == 0.0f) ? float4(0.0f, 0.0f, 0.0f, 1.0f) : float4(normalize(mul(invTWorldMats[transformIndex], float4(norm, 0.0f)).xyz), 1.0f);
    const float4 prevWorldPos = mul(prevWorldMats[transformIndex], float4(previousPos, 1.0f));
    dstPos[vertexOffsetIndex] = worldPos;
    dstNorm[vertexOffsetIndex] = worldNorm;
    dstVel[vertexOffsetIndex] = worldPos - prevWorldPos;
}
