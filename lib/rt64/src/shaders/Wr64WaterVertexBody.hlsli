// Intentionally included inside a shader/function scope without an include
// guard. The shared body retains the original raster expression context: DXC
// can otherwise reassociate recentering arithmetic across function boundaries.
// Caller supplies vertexOffsetIndex, posIndex, pos, wr64EvaluatedTc,
// wr64EvaluatedTcValid and WR64_WATER_FRAME_WEIGHT; resources are declared by
// the including compute shader. Wr64WaterVertex.hlsli supplies the sampler.
    const uint4 waterInfo = wr64WaterFieldInfo[vertexOffsetIndex];
    if (waterInfo.x == 6) {
        const uint sourceVertex = waterInfo.y;
        const uint sourcePosIndex = sourceVertex * 3;
        const uint sourceTcIndex = sourceVertex * 2;
        const float4 patchShiftX =
            wr64WaterFieldPrevPosShiftX[vertexOffsetIndex];
        const float4 patchShiftZ =
            wr64WaterFieldPrevTcShiftZ[vertexOffsetIndex];
        pos.x = srcPos[posIndex + 0] -
            patchShiftX.w * (1.0f - WR64_WATER_FRAME_WEIGHT);
        pos.z = srcPos[posIndex + 2] -
            patchShiftZ.z * (1.0f - WR64_WATER_FRAME_WEIGHT);
        pos.y = srcPos[sourcePosIndex + 1] -
            srcVel[sourcePosIndex + 1] * (1.0f - WR64_WATER_FRAME_WEIGHT);
        wr64EvaluatedTc = float2(
            srcTc[sourceTcIndex + 0] - srcTcVel[sourceTcIndex + 0] *
                (1.0f - WR64_WATER_FRAME_WEIGHT),
            srcTc[sourceTcIndex + 1] - srcTcVel[sourceTcIndex + 1] *
                (1.0f - WR64_WATER_FRAME_WEIGHT));
        wr64EvaluatedTcValid = true;
    }
    else if (waterInfo.x != 0) {
        const float4 prevPosShiftX = wr64WaterFieldPrevPosShiftX[vertexOffsetIndex];
        const float4 prevTcShiftZ = wr64WaterFieldPrevTcShiftZ[vertexOffsetIndex];
        const float2 coverageOffset = asfloat(waterInfo.zw);
        pos.x = srcPos[posIndex + 0] + coverageOffset.x -
            (prevPosShiftX.w * (1.0f - WR64_WATER_FRAME_WEIGHT));
        pos.z = srcPos[posIndex + 2] + coverageOffset.y -
            (prevTcShiftZ.z * (1.0f - WR64_WATER_FRAME_WEIGHT));
        if ((waterInfo.x == 1) || (waterInfo.x == 4)) {
            float prevY;
            float curY;
            float2 prevWaterTc;
            float2 curWaterTc;
            const bool prevFound = wr64SampleWaterField(pos.xz, true, waterInfo.y, prevY, prevWaterTc);
            const bool curFound = wr64SampleWaterField(pos.xz, false, waterInfo.y, curY, curWaterTc);
            if (prevFound && curFound) {
                pos.y = lerp(prevY, curY, WR64_WATER_FRAME_WEIGHT);
                if (waterInfo.x == 1) {
                    wr64EvaluatedTc = lerp(prevWaterTc, curWaterTc, WR64_WATER_FRAME_WEIGHT);
                    wr64EvaluatedTcValid = true;
                }
            }
        }
        else if (waterInfo.x == 2) {
            pos.y = lerp(prevPosShiftX.y, srcPos[posIndex + 1], WR64_WATER_FRAME_WEIGHT);
        }
    }
