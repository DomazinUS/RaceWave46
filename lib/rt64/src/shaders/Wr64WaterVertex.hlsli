// Shared presentation-time evaluation for the native generated water sheet.
// Include after declaring srcPos/srcVel/srcTc/srcTcVel and the four
// wr64WaterField* buffers. Keep raster and world/BVH positions on the same
// recentered height field; ordinary vertices retain the caller's position.
#ifndef WR64_WATER_VERTEX_HLSLI
#define WR64_WATER_VERTEX_HLSLI

bool wr64SampleWaterField(float2 query, bool previousField, uint triangleCount,
    out float sampledY, out float2 sampledTc)
{
    float bestPenalty = 1.0e30f;
    float bestY = 0.0f;
    float2 bestTc = 0.0f;
    bool found = false;

    for (uint triIndex = 0; triIndex < triangleCount; triIndex++) {
        const uint faceOffset = triIndex * 3;
        const uint ia = wr64WaterFieldFaceIndices[faceOffset + 0];
        const uint ib = wr64WaterFieldFaceIndices[faceOffset + 1];
        const uint ic = wr64WaterFieldFaceIndices[faceOffset + 2];
        const uint pa = ia * 3;
        const uint pb = ib * 3;
        const uint pc = ic * 3;
        const uint ta = ia * 2;
        const uint tb = ib * 2;
        const uint tc = ic * 2;

        const float4 prevA = wr64WaterFieldPrevPosShiftX[ia];
        const float4 prevB = wr64WaterFieldPrevPosShiftX[ib];
        const float4 prevC = wr64WaterFieldPrevPosShiftX[ic];
        const float3 a = previousField ? prevA.xyz :
            float3(srcPos[pa + 0], srcPos[pa + 1], srcPos[pa + 2]);
        const float3 b = previousField ? prevB.xyz :
            float3(srcPos[pb + 0], srcPos[pb + 1], srcPos[pb + 2]);
        const float3 c = previousField ? prevC.xyz :
            float3(srcPos[pc + 0], srcPos[pc + 1], srcPos[pc + 2]);
        const float2 prevTcA = wr64WaterFieldPrevTcShiftZ[ia].xy;
        const float2 prevTcB = wr64WaterFieldPrevTcShiftZ[ib].xy;
        const float2 prevTcC = wr64WaterFieldPrevTcShiftZ[ic].xy;
        const float2 uvA = previousField ? prevTcA : float2(srcTc[ta + 0], srcTc[ta + 1]);
        const float2 uvB = previousField ? prevTcB : float2(srcTc[tb + 0], srcTc[tb + 1]);
        const float2 uvC = previousField ? prevTcC : float2(srcTc[tc + 0], srcTc[tc + 1]);

        const float determinant = ((b.z - c.z) * (a.x - c.x)) +
            ((c.x - b.x) * (a.z - c.z));
        if (abs(determinant) < 1.0e-7f) {
            continue;
        }

        const float wa = (((b.z - c.z) * (query.x - c.x)) +
            ((c.x - b.x) * (query.y - c.z))) / determinant;
        const float wb = (((c.z - a.z) * (query.x - c.x)) +
            ((a.x - c.x) * (query.y - c.z))) / determinant;
        const float wc = 1.0f - wa - wb;
        const float penalty = max(-wa, 0.0f) + max(-wb, 0.0f) + max(-wc, 0.0f);
        const float y = (wa * a.y) + (wb * b.y) + (wc * c.y);
        const float2 uv = (wa * uvA) + (wb * uvB) + (wc * uvC);

        if (penalty <= 1.0e-4f) {
            sampledY = y;
            sampledTc = uv;
            return true;
        }

        if (penalty < bestPenalty) {
            bestPenalty = penalty;
            bestY = y;
            bestTc = uv;
            found = true;
        }
    }

    sampledY = bestY;
    sampledTc = bestTc;
    return found;
}

void wr64EvaluateWaterVertex(uint vertexOffsetIndex, float frameWeight,
    inout float3 pos, out float2 wr64EvaluatedTc, out bool wr64EvaluatedTcValid)
{
    const uint posIndex = vertexOffsetIndex * 3;
    wr64EvaluatedTc = 0.0f;
    wr64EvaluatedTcValid = false;

#define WR64_WATER_FRAME_WEIGHT frameWeight
#include "Wr64WaterVertexBody.hlsli"
#undef WR64_WATER_FRAME_WEIGHT
}

#endif
