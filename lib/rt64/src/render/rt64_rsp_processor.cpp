//
// RT64
//

#include "rt64_rsp_processor.h"

#include "rt64_buffer_uploader.h"

#include "common/rt64_math.h"

#include <atomic>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <limits>

namespace {
    struct Wr64WaterEvaluatedVertex {
        hlslpp::float3 position = hlslpp::float3(0.0f, 0.0f, 0.0f);
        hlslpp::float2 texcoord = hlslpp::float2(0.0f, 0.0f);
        uint32_t fieldMode = 0;
    };

    bool wr64SampleWaterFieldCpu(const RT64::DrawData &drawData,
        const hlslpp::float2 &query, bool previousField, uint32_t triangleCount,
        float &sampledY, hlslpp::float2 &sampledTc)
    {
        const std::vector<uint32_t> &faces = drawData.wr64WaterFieldFaceIndices;
        const uint32_t availableTriangles = uint32_t(faces.size() / 3);
        const uint32_t count = std::min(triangleCount, availableTriangles);
        float bestPenalty = std::numeric_limits<float>::max();
        float bestY = 0.0f;
        hlslpp::float2 bestTc(0.0f, 0.0f);
        bool found = false;

        for (uint32_t triangle = 0; triangle < count; triangle++) {
            const uint32_t aIndex = faces[triangle * 3 + 0];
            const uint32_t bIndex = faces[triangle * 3 + 1];
            const uint32_t cIndex = faces[triangle * 3 + 2];
            const uint32_t vertexCount = drawData.vertexCount();
            if ((aIndex >= vertexCount) || (bIndex >= vertexCount) ||
                (cIndex >= vertexCount))
            {
                continue;
            }

            const auto readPosition = [&](uint32_t index) -> hlslpp::float3 {
                if (previousField &&
                    (index < drawData.wr64WaterFieldPrevPosShiftX.size()))
                {
                    const hlslpp::float4 &value =
                        drawData.wr64WaterFieldPrevPosShiftX[index];
                    return hlslpp::float3(float(value.x), float(value.y),
                        float(value.z));
                }

                const uint32_t p = index * 3;
                return hlslpp::float3(drawData.posFloats[p + 0],
                    drawData.posFloats[p + 1], drawData.posFloats[p + 2]);
            };
            const auto readTexcoord = [&](uint32_t index) -> hlslpp::float2 {
                if (previousField &&
                    (index < drawData.wr64WaterFieldPrevTcShiftZ.size()))
                {
                    const hlslpp::float4 &value =
                        drawData.wr64WaterFieldPrevTcShiftZ[index];
                    return hlslpp::float2(float(value.x), float(value.y));
                }

                const uint32_t t = index * 2;
                return hlslpp::float2(drawData.tcFloats[t + 0],
                    drawData.tcFloats[t + 1]);
            };

            const hlslpp::float3 a = readPosition(aIndex);
            const hlslpp::float3 b = readPosition(bIndex);
            const hlslpp::float3 c = readPosition(cIndex);
            const hlslpp::float2 uvA = readTexcoord(aIndex);
            const hlslpp::float2 uvB = readTexcoord(bIndex);
            const hlslpp::float2 uvC = readTexcoord(cIndex);
            const float determinant = ((float(b.z) - float(c.z)) *
                (float(a.x) - float(c.x))) +
                ((float(c.x) - float(b.x)) *
                (float(a.z) - float(c.z)));
            if (std::fabs(determinant) < 1.0e-7f) {
                continue;
            }

            const float wa = (((float(b.z) - float(c.z)) *
                (float(query.x) - float(c.x))) +
                ((float(c.x) - float(b.x)) *
                (float(query.y) - float(c.z)))) / determinant;
            const float wb = (((float(c.z) - float(a.z)) *
                (float(query.x) - float(c.x))) +
                ((float(a.x) - float(c.x)) *
                (float(query.y) - float(c.z)))) / determinant;
            const float wc = 1.0f - wa - wb;
            const float penalty = std::max(-wa, 0.0f) +
                std::max(-wb, 0.0f) + std::max(-wc, 0.0f);
            const float y = (wa * float(a.y)) + (wb * float(b.y)) +
                (wc * float(c.y));
            const hlslpp::float2 uv = (uvA * wa) + (uvB * wb) + (uvC * wc);

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

    Wr64WaterEvaluatedVertex wr64EvaluateWaterVertexCpu(
        const RT64::DrawData &drawData, uint32_t vertex, float curFrameWeight)
    {
        Wr64WaterEvaluatedVertex evaluated;
        const float inverseWeight = 1.0f - curFrameWeight;
        const uint32_t p = vertex * 3;
        const uint32_t t = vertex * 2;
        evaluated.position = hlslpp::float3(
            drawData.posFloats[p + 0] - drawData.velFloats[p + 0] * inverseWeight,
            drawData.posFloats[p + 1] - drawData.velFloats[p + 1] * inverseWeight,
            drawData.posFloats[p + 2] - drawData.velFloats[p + 2] * inverseWeight);
        evaluated.texcoord = hlslpp::float2(
            drawData.tcFloats[t + 0] - drawData.tcVelFloats[t + 0] * inverseWeight,
            drawData.tcFloats[t + 1] - drawData.tcVelFloats[t + 1] * inverseWeight);

        const uint32_t infoOffset = vertex * 4;
        if ((infoOffset + 3) >= drawData.wr64WaterFieldInfo.size()) {
            return evaluated;
        }

        const uint32_t mode = drawData.wr64WaterFieldInfo[infoOffset + 0];
        evaluated.fieldMode = mode;
        if ((mode == 0) ||
            (vertex >= drawData.wr64WaterFieldPrevPosShiftX.size()) ||
            (vertex >= drawData.wr64WaterFieldPrevTcShiftZ.size()))
        {
            return evaluated;
        }

        const hlslpp::float4 prevPosShiftX =
            drawData.wr64WaterFieldPrevPosShiftX[vertex];
        const hlslpp::float4 prevTcShiftZ =
            drawData.wr64WaterFieldPrevTcShiftZ[vertex];
        if (mode == 6) {
            const uint32_t source =
                drawData.wr64WaterFieldInfo[infoOffset + 1];
            const uint64_t sourceP = uint64_t(source) * 3ULL;
            const uint64_t sourceT = uint64_t(source) * 2ULL;
            if (((sourceP + 2ULL) < drawData.posFloats.size()) &&
                ((sourceP + 2ULL) < drawData.velFloats.size()) &&
                ((sourceT + 1ULL) < drawData.tcFloats.size()) &&
                ((sourceT + 1ULL) < drawData.tcVelFloats.size()))
            {
                evaluated.position.x = drawData.posFloats[p + 0] -
                    float(prevPosShiftX.w) * inverseWeight;
                evaluated.position.z = drawData.posFloats[p + 2] -
                    float(prevTcShiftZ.z) * inverseWeight;
                evaluated.position.y = drawData.posFloats[size_t(sourceP + 1)] -
                    drawData.velFloats[size_t(sourceP + 1)] * inverseWeight;
                evaluated.texcoord = hlslpp::float2(
                    drawData.tcFloats[size_t(sourceT + 0)] -
                        drawData.tcVelFloats[size_t(sourceT + 0)] * inverseWeight,
                    drawData.tcFloats[size_t(sourceT + 1)] -
                        drawData.tcVelFloats[size_t(sourceT + 1)] * inverseWeight);
            }
            return evaluated;
        }
        float coverageOffsetX = 0.0f;
        float coverageOffsetZ = 0.0f;
        const uint32_t coverageOffsetXBits = drawData.wr64WaterFieldInfo[infoOffset + 2];
        const uint32_t coverageOffsetZBits = drawData.wr64WaterFieldInfo[infoOffset + 3];
        std::memcpy(&coverageOffsetX, &coverageOffsetXBits, sizeof(float));
        std::memcpy(&coverageOffsetZ, &coverageOffsetZBits, sizeof(float));
        evaluated.position.x = drawData.posFloats[p + 0] + coverageOffsetX -
            float(prevPosShiftX.w) * inverseWeight;
        evaluated.position.z = drawData.posFloats[p + 2] + coverageOffsetZ -
            float(prevTcShiftZ.z) * inverseWeight;

        if ((mode == 1) || (mode == 4)) {
            float previousY = 0.0f;
            float currentY = 0.0f;
            hlslpp::float2 previousTc(0.0f, 0.0f);
            hlslpp::float2 currentTc(0.0f, 0.0f);
            const uint32_t triangleCount =
                drawData.wr64WaterFieldInfo[infoOffset + 1];
            const hlslpp::float2 query(
                float(evaluated.position.x), float(evaluated.position.z));
            const bool previousFound = wr64SampleWaterFieldCpu(drawData, query,
                true, triangleCount, previousY, previousTc);
            const bool currentFound = wr64SampleWaterFieldCpu(drawData, query,
                false, triangleCount, currentY, currentTc);
            if (previousFound && currentFound) {
                evaluated.position.y = previousY +
                    ((currentY - previousY) * curFrameWeight);
                if (mode == 1) {
                    evaluated.texcoord = previousTc +
                        ((currentTc - previousTc) * curFrameWeight);
                }
            }
        }
        else if (mode == 2) {
            evaluated.position.y = float(prevPosShiftX.y) +
                ((drawData.posFloats[p + 1] - float(prevPosShiftX.y)) *
                    curFrameWeight);
        }

        return evaluated;
    }

    FILE *wr64WaterPresentTraceFile() {
        static FILE *file = []() -> FILE * {
            const char *enabled = std::getenv("WR64_WATER_PRESENT_TRACE");
            if ((enabled == nullptr) || (enabled[0] == '\0') || (enabled[0] == '0')) {
                return nullptr;
            }

            const char *path = std::getenv("WR64_WATER_PRESENT_TRACE_PATH");
            if ((path == nullptr) || (path[0] == '\0')) {
                path = "wr64-water-present-trace.csv";
            }

            FILE *trace = nullptr;
#ifdef _WIN32
            fopen_s(&trace, path, "w");
#else
            trace = std::fopen(path, "w");
#endif
            if (trace != nullptr) {
                std::fprintf(trace,
                    "present,native_frame,weight,prev_weight,vertex,address,producer_key,view_proj,world,field_mode,"
                    "pos_x,pos_y,pos_z,vel_x,vel_y,vel_z,stock_x,stock_y,stock_z,actual_x,actual_y,actual_z,"
                    "tc_u,tc_v,tc_vel_u,tc_vel_v,stock_u,stock_v,actual_u,actual_v,"
                    "clip_x,clip_y,clip_z,clip_w,screen_x,screen_y,screen_z,"
                    "camera_local_x,camera_local_y,camera_local_z\n");
                std::fflush(trace);
            }
            return trace;
        }();
        return file;
    }

    uint64_t wr64WaterPresentIndex() {
        static std::atomic<uint64_t> index{ 0 };
        return index.fetch_add(1, std::memory_order_relaxed);
    }

    FILE *wr64WaterPresentTriangleTraceFile() {
        static FILE *file = []() -> FILE * {
            const char *enabled = std::getenv("WR64_WATER_PRESENT_TRACE");
            if ((enabled == nullptr) || (enabled[0] == '\0') || (enabled[0] == '0')) {
                return nullptr;
            }

            const char *path = std::getenv("WR64_WATER_PRESENT_TRI_TRACE_PATH");
            if ((path == nullptr) || (path[0] == '\0')) {
                path = "wr64-water-present-triangles.csv";
            }

            FILE *trace = nullptr;
#ifdef _WIN32
            fopen_s(&trace, path, "w");
#else
            trace = std::fopen(path, "w");
#endif
            if (trace != nullptr) {
                std::fprintf(trace, "present,weight,triangle,a,b,c,producerless_count\n");
                std::fflush(trace);
            }
            return trace;
        }();
        return file;
    }

    bool wr64WaterPresentAllTriangles() {
        static const bool enabled = []() {
            const char *value = std::getenv("WR64_WATER_PRESENT_ALL_TRIANGLES");
            return (value != nullptr) && (value[0] != '\0') && (value[0] != '0');
        }();
        return enabled;
    }
}

namespace RT64 {
    // RSPProcessor

    RSPProcessor::RSPProcessor(RenderDevice *device) {
        processSet = std::make_unique<RSPProcessDescriptorSet>(device);
        modifySet = std::make_unique<RSPModifyDescriptorSet>(device);
    }

    RSPProcessor::~RSPProcessor() { }
    
    void RSPProcessor::process(const ProcessParams &p) {
        const DrawData &drawData = *p.drawData;
        const uint32_t drawVertexCount = drawData.vertexCount();

        FILE *waterTrace = wr64WaterPresentTraceFile();
        if ((waterTrace != nullptr) &&
            (drawData.wr64WaterVertexMask.size() == drawVertexCount))
        {
            bool hasWater = false;
            for (uint8_t tagged : drawData.wr64WaterVertexMask) {
                if (tagged != 0) {
                    hasWater = true;
                    break;
                }
            }

            if (hasWater) {
                const uint64_t present = wr64WaterPresentIndex();
                const float inverseWeight = 1.0f - p.curFrameWeight;
                for (uint32_t vertex = 0; vertex < drawVertexCount; vertex++) {
                    if (drawData.wr64WaterVertexMask[vertex] == 0) {
                        continue;
                    }

                    const uint32_t posIndex = vertex * 3;
                    if (((posIndex + 2) >= drawData.posFloats.size()) ||
                        ((posIndex + 2) >= drawData.velFloats.size()) ||
                        (vertex >= drawData.viewProjIndices.size()) ||
                        (vertex >= drawData.worldIndices.size()))
                    {
                        continue;
                    }

                    const uint32_t viewProjIndex = drawData.viewProjIndices[vertex];
                    const uint32_t worldIndex = drawData.worldIndices[vertex];
                    if ((viewProjIndex >= drawData.modViewProjTransforms.size()) ||
                        (viewProjIndex >= drawData.rspViewports.size()) ||
                        (worldIndex >= drawData.worldTransforms.size()))
                    {
                        continue;
                    }

                    const hlslpp::float3 position(
                        drawData.posFloats[posIndex + 0],
                        drawData.posFloats[posIndex + 1],
                        drawData.posFloats[posIndex + 2]);
                    const hlslpp::float3 velocity(
                        drawData.velFloats[posIndex + 0],
                        drawData.velFloats[posIndex + 1],
                        drawData.velFloats[posIndex + 2]);
                    const hlslpp::float3 stockInterpolated = position - velocity * inverseWeight;
                    const uint32_t tcIndex = vertex * 2;
                    if (((tcIndex + 1) >= drawData.tcFloats.size()) ||
                        ((tcIndex + 1) >= drawData.tcVelFloats.size()))
                    {
                        continue;
                    }
                    const hlslpp::float2 texcoord(
                        drawData.tcFloats[tcIndex + 0], drawData.tcFloats[tcIndex + 1]);
                    const hlslpp::float2 texcoordVelocity(
                        drawData.tcVelFloats[tcIndex + 0], drawData.tcVelFloats[tcIndex + 1]);
                    const hlslpp::float2 stockTexcoord =
                        texcoord - texcoordVelocity * inverseWeight;
                    const Wr64WaterEvaluatedVertex actual =
                        wr64EvaluateWaterVertexCpu(drawData, vertex, p.curFrameWeight);
                    const hlslpp::float4x4 &worldTransform =
                        (drawData.lerpWorldTransforms.size() == drawData.worldTransforms.size()) ?
                            drawData.lerpWorldTransforms[worldIndex] : drawData.worldTransforms[worldIndex];
                    const hlslpp::float4 worldPosition = hlslpp::mul(
                        hlslpp::float4(actual.position, 1.0f),
                        worldTransform);
                    const hlslpp::float4 clip = hlslpp::mul(
                        worldPosition, drawData.modViewProjTransforms[viewProjIndex]);
                    const interop::RSPViewport &viewport = drawData.rspViewports[viewProjIndex];
                    const float safeW = (clip.w == 0.0f) ? 1.0e-6f : clip.w;
                    const hlslpp::float3 ndc = clip.xyz /
                        hlslpp::float3(safeW, -safeW, safeW);
                    const hlslpp::float3 screen = ndc * viewport.scale + viewport.translate;
                    hlslpp::float3 cameraLocal(0.0f, 0.0f, 0.0f);
                    if (viewProjIndex < drawData.modViewTransforms.size()) {
                        const hlslpp::float4 cameraWorld =
                            hlslpp::inverse(drawData.modViewTransforms[viewProjIndex])[3];
                        cameraLocal = hlslpp::mul(cameraWorld, hlslpp::inverse(worldTransform)).xyz;
                    }
                    const uint32_t address = (vertex < drawData.vertexSegmentedAddresses.size()) ?
                        drawData.vertexSegmentedAddresses[vertex] : 0;
                    const uint32_t producerKey = (vertex < drawData.wr64WaterProducerKeys.size()) ?
                        drawData.wr64WaterProducerKeys[vertex] : 0;

                    std::fprintf(waterTrace,
                        "%llu,%llu,%.9g,%.9g,%u,0x%08X,0x%08X,%u,%u,%u,"
                        "%.9g,%.9g,%.9g,%.9g,%.9g,%.9g,%.9g,%.9g,%.9g,%.9g,%.9g,%.9g,"
                        "%.9g,%.9g,%.9g,%.9g,%.9g,%.9g,%.9g,%.9g,"
                        "%.9g,%.9g,%.9g,%.9g,%.9g,%.9g,%.9g,%.9g,%.9g,%.9g\n",
                        static_cast<unsigned long long>(present),
                        static_cast<unsigned long long>(drawData.wr64WaterSubmissionFrame),
                        p.curFrameWeight, p.prevFrameWeight, vertex, address, producerKey,
                        viewProjIndex, worldIndex, actual.fieldMode,
                        float(position.x), float(position.y), float(position.z),
                        float(velocity.x), float(velocity.y), float(velocity.z),
                        float(stockInterpolated.x), float(stockInterpolated.y), float(stockInterpolated.z),
                        float(actual.position.x), float(actual.position.y), float(actual.position.z),
                        float(texcoord.x), float(texcoord.y),
                        float(texcoordVelocity.x), float(texcoordVelocity.y),
                        float(stockTexcoord.x), float(stockTexcoord.y),
                        float(actual.texcoord.x), float(actual.texcoord.y),
                        float(clip.x), float(clip.y), float(clip.z), float(clip.w),
                        float(screen.x), float(screen.y), float(screen.z),
                        float(cameraLocal.x), float(cameraLocal.y), float(cameraLocal.z));
                }

                FILE *triangleTrace = wr64WaterPresentTriangleTraceFile();
                if (triangleTrace != nullptr) {
                    const std::vector<uint32_t> &faces = drawData.wr64WaterFaceIndices;
                    for (size_t f = 0; (f + 2) < faces.size(); f += 3) {
                        const uint32_t a = faces[f + 0];
                        const uint32_t b = faces[f + 1];
                        const uint32_t c = faces[f + 2];
                        if ((a >= drawVertexCount) || (b >= drawVertexCount) || (c >= drawVertexCount)) {
                            continue;
                        }

                        const uint32_t producerlessCount =
                            ((a >= drawData.wr64WaterProducerKeys.size()) || (drawData.wr64WaterProducerKeys[a] == 0) ? 1U : 0U) +
                            ((b >= drawData.wr64WaterProducerKeys.size()) || (drawData.wr64WaterProducerKeys[b] == 0) ? 1U : 0U) +
                            ((c >= drawData.wr64WaterProducerKeys.size()) || (drawData.wr64WaterProducerKeys[c] == 0) ? 1U : 0U);
                        if ((producerlessCount == 0) && !wr64WaterPresentAllTriangles()) {
                            continue;
                        }

                        std::fprintf(triangleTrace, "%llu,%.9g,%zu,%u,%u,%u,%u\n",
                            static_cast<unsigned long long>(present), p.curFrameWeight,
                            f / 3, a, b, c, producerlessCount);
                    }
                    std::fflush(triangleTrace);
                }
                std::fflush(waterTrace);
            }
        }

        processCB.vertexStart = uint32_t(p.outputBuffers->screenPosBuffer.computedSize / (sizeof(float) * 4));
        processCB.vertexCount = drawVertexCount - processCB.vertexStart;
        processCB.prevFrameWeight = p.prevFrameWeight;
        processCB.curFrameWeight = p.curFrameWeight;
        p.outputBuffers->screenPosBuffer.computedSize += processCB.vertexCount * sizeof(float) * 4;
        p.outputBuffers->genTexCoordBuffer.computedSize += processCB.vertexCount * sizeof(float) * 2;
        p.outputBuffers->shadedColBuffer.computedSize += processCB.vertexCount * sizeof(float) * 4;
        processSet->setBuffer(processSet->srcPos, p.drawBuffers->positionBuffer.get(), p.drawBuffers->positionBuffer.getView(0));
        processSet->setBuffer(processSet->srcVel, p.drawBuffers->velocityBuffer.get(), p.drawBuffers->velocityBuffer.getView(0));
        processSet->setBuffer(processSet->srcTc, p.drawBuffers->texcoordBuffer.get(), p.drawBuffers->texcoordBuffer.getView(0));
        processSet->setBuffer(processSet->srcTcVel, p.drawBuffers->texcoordVelocityBuffer.get(), p.drawBuffers->texcoordVelocityBuffer.getView(0));
        processSet->setBuffer(processSet->srcCol, p.drawBuffers->normalColorBuffer.get(), p.drawBuffers->normalColorBuffer.getView(0));
        processSet->setBuffer(processSet->srcNorm, p.drawBuffers->normalColorBuffer.get(), p.drawBuffers->normalColorBuffer.getView(1));
        processSet->setBuffer(processSet->srcViewProjIndices, p.drawBuffers->viewProjIndicesBuffer.get(), p.drawBuffers->viewProjIndicesBuffer.getView(0));
        processSet->setBuffer(processSet->srcWorldIndices, p.drawBuffers->worldIndicesBuffer.get(), p.drawBuffers->worldIndicesBuffer.getView(0));
        processSet->setBuffer(processSet->srcFogIndices, p.drawBuffers->fogIndicesBuffer.get(), p.drawBuffers->fogIndicesBuffer.getView(0));
        processSet->setBuffer(processSet->srcLightIndices, p.drawBuffers->lightIndicesBuffer.get(), p.drawBuffers->lightIndicesBuffer.getView(0));
        processSet->setBuffer(processSet->srcLightCounts, p.drawBuffers->lightCountsBuffer.get(), p.drawBuffers->lightCountsBuffer.getView(0));
        processSet->setBuffer(processSet->srcLookAtIndices, p.drawBuffers->lookAtIndicesBuffer.get(), p.drawBuffers->lookAtIndicesBuffer.getView(0));
        processSet->setBuffer(processSet->rspViewportVector, p.drawBuffers->rspViewportsBuffer.get(), RenderBufferStructuredView(sizeof(interop::RSPViewport)));
        processSet->setBuffer(processSet->rspFogVector, p.drawBuffers->rspFogBuffer.get(), RenderBufferStructuredView(sizeof(interop::RSPFog)));
        processSet->setBuffer(processSet->rspLightVector, p.drawBuffers->rspLightsBuffer.get(), RenderBufferStructuredView(sizeof(interop::RSPLight)));
        processSet->setBuffer(processSet->rspLookAtVector, p.drawBuffers->rspLookAtBuffer.get(), RenderBufferStructuredView(sizeof(interop::RSPLookAt)));
        processSet->setBuffer(processSet->viewProjTransforms, p.drawBuffers->viewProjTransformsBuffer.get(), RenderBufferStructuredView(sizeof(interop::float4x4)));
        processSet->setBuffer(processSet->worldTransforms, p.drawBuffers->worldTransformsBuffer.get(), RenderBufferStructuredView(sizeof(interop::float4x4)));
        processSet->setBuffer(processSet->dstPos, p.outputBuffers->screenPosBuffer.buffer.get(), RenderBufferStructuredView(sizeof(float) * 4));
        processSet->setBuffer(processSet->dstTc, p.outputBuffers->genTexCoordBuffer.buffer.get(), RenderBufferStructuredView(sizeof(float) * 2));
        processSet->setBuffer(processSet->dstCol, p.outputBuffers->shadedColBuffer.buffer.get(), RenderBufferStructuredView(sizeof(float) * 4));
        processSet->setBuffer(processSet->wr64WaterFieldInfo, p.drawBuffers->wr64WaterFieldInfoBuffer.get(), RenderBufferStructuredView(sizeof(uint32_t) * 4));
        processSet->setBuffer(processSet->wr64WaterFieldPrevPosShiftX, p.drawBuffers->wr64WaterFieldPrevPosShiftXBuffer.get(), RenderBufferStructuredView(sizeof(float) * 4));
        processSet->setBuffer(processSet->wr64WaterFieldPrevTcShiftZ, p.drawBuffers->wr64WaterFieldPrevTcShiftZBuffer.get(), RenderBufferStructuredView(sizeof(float) * 4));
        processSet->setBuffer(processSet->wr64WaterFieldFaceIndices, p.drawBuffers->wr64WaterFieldFaceIndicesBuffer.get(), RenderBufferStructuredView(sizeof(uint32_t)));

        const uint32_t modifyCount = drawData.modifyCount();
        modifyCB.modifyCount = modifyCount;
        modifySet->setBuffer(modifySet->srcModifyPos, p.drawBuffers->modifyPosUintsBuffer.get(), p.drawBuffers->modifyPosUintsBuffer.getView(0));
        modifySet->setBuffer(modifySet->screenPos, p.outputBuffers->screenPosBuffer.buffer.get(), RenderBufferStructuredView(sizeof(float) * 4));
    }

    void RSPProcessor::recordCommandList(RenderWorker *worker, const ShaderLibrary *shaderLibrary, const OutputBuffers *outputBuffers) {
        const uint32_t ThreadGroupSize = 64;
        
        if (processCB.vertexCount > 0) {
            RenderBufferBarrier beforeBarriers[] = {
                RenderBufferBarrier(outputBuffers->screenPosBuffer.buffer.get(), RenderBufferAccess::WRITE),
                RenderBufferBarrier(outputBuffers->genTexCoordBuffer.buffer.get(), RenderBufferAccess::WRITE),
                RenderBufferBarrier(outputBuffers->shadedColBuffer.buffer.get(), RenderBufferAccess::WRITE)
            };

            RenderBufferBarrier afterBarriers[] = {
                RenderBufferBarrier(outputBuffers->screenPosBuffer.buffer.get(), RenderBufferAccess::READ),
                RenderBufferBarrier(outputBuffers->genTexCoordBuffer.buffer.get(), RenderBufferAccess::READ),
                RenderBufferBarrier(outputBuffers->shadedColBuffer.buffer.get(), RenderBufferAccess::READ)
            };

            const int dispatchCount = (processCB.vertexCount + ThreadGroupSize - 1) / ThreadGroupSize;
            worker->commandList->barriers(RenderBarrierStage::COMPUTE, beforeBarriers, uint32_t(std::size(beforeBarriers)));
            worker->commandList->setPipeline(shaderLibrary->rspProcess.pipeline.get());
            worker->commandList->setComputePipelineLayout(shaderLibrary->rspProcess.pipelineLayout.get());
            worker->commandList->setComputePushConstants(0, &processCB);
            worker->commandList->setComputeDescriptorSet(processSet->get(), 0);
            worker->commandList->dispatch(dispatchCount, 1, 1);
            worker->commandList->barriers(RenderBarrierStage::GRAPHICS, afterBarriers, uint32_t(std::size(afterBarriers)));
        }

        if (modifyCB.modifyCount > 0) {
            RenderBufferBarrier beforeBarrier = RenderBufferBarrier(outputBuffers->screenPosBuffer.buffer.get(), RenderBufferAccess::WRITE);
            RenderBufferBarrier afterBarrier = RenderBufferBarrier(outputBuffers->screenPosBuffer.buffer.get(), RenderBufferAccess::READ);
            const int dispatchCount = (modifyCB.modifyCount + ThreadGroupSize - 1) / ThreadGroupSize;
            worker->commandList->barriers(RenderBarrierStage::COMPUTE, beforeBarrier);
            worker->commandList->setPipeline(shaderLibrary->rspModify.pipeline.get());
            worker->commandList->setComputePipelineLayout(shaderLibrary->rspModify.pipelineLayout.get());
            worker->commandList->setComputePushConstants(0, &modifyCB);
            worker->commandList->setComputeDescriptorSet(modifySet->get(), 0);
            worker->commandList->dispatch(dispatchCount, 1, 1);
            worker->commandList->barriers(RenderBarrierStage::GRAPHICS, afterBarrier);
        }
    }
};
