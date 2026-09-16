// Headless execution of the production ShaderLibrary and VertexProcessor.
// Unlike water_gpu.cpp, this tests the embedded shader, actual root constants,
// descriptor definitions, CPU binding code and command-recording path together.
#include <array>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include "plume_d3d12.h"
#include "render/rt64_shader_library.h"
#include "render/rt64_vertex_processor.h"

using namespace plume;
using namespace RT64;

namespace {
    size_t checks = 0;
    void require(bool value, const char *message) {
        ++checks;
        if (!value) throw std::runtime_error(message);
    }
    uint32_t bits(float value) { uint32_t result; std::memcpy(&result, &value, 4); return result; }
    void input(RenderDevice *device, BufferPair &pair, const void *data, size_t size,
        std::initializer_list<RenderFormat> formats = {}) {
        pair.defaultBuffer = device->createBuffer(RenderBufferDesc::UploadBuffer(size, RenderBufferFlag::STORAGE));
        pair.allocatedSize = size;
        require(pair.defaultBuffer != nullptr, "Input allocation failed");
        void *mapped = pair.defaultBuffer->map();
        require(mapped != nullptr, "Input mapping failed");
        std::memcpy(mapped, data, size);
        pair.defaultBuffer->unmap();
        for (auto format : formats) {
            pair.defaultViews.emplace_back(pair.defaultBuffer->createBufferFormattedView(format));
            require(pair.defaultViews.back() != nullptr, "Input formatted view failed");
        }
    }
    using Points = std::array<std::array<float, 4>, 3>;
    struct Result { Points positions, velocities; };
}

int main() {
    try {
        std::setvbuf(stdout, nullptr, _IONBF, 0);
        D3D12Interface renderInterface;
        require(renderInterface.isValid(), "D3D12 interface creation failed");
        auto device = renderInterface.createDevice("");
        require(device != nullptr, "D3D12 device creation failed");
        ShaderLibrary shaders(false, false);
        shaders.setupCommonShaders(&renderInterface, device.get());
        require(shaders.rspWorld.pipelineLayout != nullptr, "Production world pipeline layout is missing");
        require(shaders.rspWorld.pipeline != nullptr, "Production world compute PSO creation failed");
        auto *layout = static_cast<D3D12PipelineLayout *>(shaders.rspWorld.pipelineLayout.get());
        require(layout->pushConstantRanges.size() == 1, "Unexpected world root constant ranges");
        require(layout->pushConstantRanges[0].size == sizeof(VertexProcessor::WorldCB),
            "Production root constant range omits WorldCB fields");
        static_assert(sizeof(VertexProcessor::WorldCB) == 20, "WorldCB gate offset changed");

        DrawData data;
        data.posFloats = {4, 8, 12, 20, 30, 40, 50, 99, 60};
        data.worldIndices.assign(3, 0);
        const float velocities[] = {4, 4, 4, 4, 8, 12, 2, 8, 6};
        const float texcoords[6] = {};
        const uint8_t normals[12] = {};
        const uint16_t matrixIndices[3] = {};
        const float world[] = {2,0,0,0, 0,3,0,0, 0,0,4,0, 0,0,0,1};
        const float previousWorld[] = {1,0,0,0, 0,2,0,0, 0,0,3,0, 0,0,0,1};
        const float inverseTranspose[] = {.5f,0,0,0, 0,1.f/3,0,0, 0,0,.25f,0, 0,0,0,1};
        const uint32_t fieldInfo[] = {0,0,0,0, 2,0,bits(5),bits(-7), 6,0,0,0};
        const float previousPos[] = {0,0,0,0, 0,6,0,12, 0,0,0,8};
        const float previousTc[] = {0,0,0,0, 0,0,20,0, 0,0,16,0};
        const uint32_t fieldFaces[3] = {};
        DrawBuffers buffers;
        input(device.get(), buffers.positionBuffer, data.posFloats.data(), data.posFloats.size()*4, {RenderFormat::R32_FLOAT});
        input(device.get(), buffers.velocityBuffer, velocities, sizeof(velocities), {RenderFormat::R32_FLOAT});
        input(device.get(), buffers.texcoordBuffer, texcoords, sizeof(texcoords), {RenderFormat::R32_FLOAT});
        input(device.get(), buffers.texcoordVelocityBuffer, texcoords, sizeof(texcoords), {RenderFormat::R32_FLOAT});
        input(device.get(), buffers.normalColorBuffer, normals, sizeof(normals), {RenderFormat::R8_UINT, RenderFormat::R8_SINT});
        input(device.get(), buffers.worldIndicesBuffer, matrixIndices, sizeof(matrixIndices), {RenderFormat::R16_UINT});
        input(device.get(), buffers.worldTransformsBuffer, world, sizeof(world));
        input(device.get(), buffers.prevWorldTransformsBuffer, previousWorld, sizeof(previousWorld));
        input(device.get(), buffers.invTWorldTransformsBuffer, inverseTranspose, sizeof(inverseTranspose));
        input(device.get(), buffers.wr64WaterFieldInfoBuffer, fieldInfo, sizeof(fieldInfo));
        input(device.get(), buffers.wr64WaterFieldPrevPosShiftXBuffer, previousPos, sizeof(previousPos));
        input(device.get(), buffers.wr64WaterFieldPrevTcShiftZBuffer, previousTc, sizeof(previousTc));
        input(device.get(), buffers.wr64WaterFieldFaceIndicesBuffer, fieldFaces, sizeof(fieldFaces));
        OutputBuffers output;
        for (ComputedBuffer *target : {&output.worldPosBuffer, &output.worldNormBuffer, &output.worldVelBuffer}) {
            target->allocatedSize = sizeof(Points);
            target->buffer = device->createBuffer(RenderBufferDesc::DefaultBuffer(sizeof(Points),
                RenderBufferFlag::STORAGE | RenderBufferFlag::UNORDERED_ACCESS));
            require(target->buffer != nullptr, "Output allocation failed");
        }
        auto readback = device->createBuffer(RenderBufferDesc::ReadbackBuffer(sizeof(Result)));
        require(readback != nullptr, "Readback allocation failed");
        RenderWorker worker(device.get(), "Headless production world pipeline", RenderCommandListType::DIRECT);
        VertexProcessor processor(device.get());
        auto execute = [&](bool enabled) {
            output.worldPosBuffer.computedSize = output.worldNormBuffer.computedSize = output.worldVelBuffer.computedSize = 0;
            VertexProcessor::ProcessParams params;
            params.worker = &worker; params.drawData = &data; params.drawBuffers = &buffers; params.outputBuffers = &output;
            params.prevFrameWeight = .25f; params.curFrameWeight = .75f; params.wr64RtWater = enabled;
            processor.process(params);
            require(processor.worldCB.vertexCount == 3, "Production processor did not schedule the fixture vertices");
            worker.commandList->begin();
            processor.recordCommandList(&worker, &shaders, &output);
            const RenderBufferBarrier barriers[] = {
                {output.worldPosBuffer.buffer.get(), RenderBufferAccess::READ},
                {output.worldVelBuffer.buffer.get(), RenderBufferAccess::READ}
            };
            worker.commandList->barriers(RenderBarrierStage::COPY, barriers, 2, nullptr, 0);
            worker.commandList->copyBufferRegion(readback->at(0), output.worldPosBuffer.buffer->at(0), sizeof(Points));
            worker.commandList->copyBufferRegion(readback->at(sizeof(Points)), output.worldVelBuffer.buffer->at(0), sizeof(Points));
            worker.commandList->end(); worker.execute(); worker.wait();
            const RenderRange read(0, sizeof(Result));
            const void *mapped = readback->map(0, &read);
            require(mapped != nullptr, "Production world readback failed");
            Result result; std::memcpy(&result, mapped, sizeof(result));
            const RenderRange noWrite(0, 0); readback->unmap(0, &noWrite);
            return result;
        };
        const auto off = execute(false);
        const auto on = execute(true);
        const auto offAgain = execute(false);
        for (uint32_t v = 0; v < 3; ++v) for (uint32_t axis = 0; axis < 3; ++axis) {
            const uint32_t i = v*3+axis;
            const float current = data.posFloats[i] - velocities[i]*.25f;
            const float previous = data.posFloats[i] - velocities[i]*.75f;
            require(std::fabs(off.positions[v][axis] - current*(axis+2)) < 1e-4f, "Disabled native position changed");
            require(std::fabs(off.velocities[v][axis] - (current*(axis+2)-previous*(axis+1))) < 1e-4f,
                "Disabled previous world transform or weight is wrong");
            require(off.positions[v][axis] == offAgain.positions[v][axis], "Disabling left a stale water gate");
        }
        const float correctedCurrent[3][3] = {{3,7,11}, {22,24,28}, {48,7,56}};
        const float correctedPrevious[3][3] = {{1,5,9}, {16,12,18}, {44,5,48}};
        for (uint32_t v = 0; v < 3; ++v) for (uint32_t axis = 0; axis < 3; ++axis) {
            require(std::fabs(on.positions[v][axis] - correctedCurrent[v][axis]*(axis+2)) < 1e-4f,
                "Production gate/bindings did not apply native water correction");
            require(std::fabs(on.velocities[v][axis] - (correctedCurrent[v][axis]*(axis+2)-correctedPrevious[v][axis]*(axis+1))) < 1e-4f,
                "Production water previous position is wrong");
        }
        require(on.positions[1][1] != off.positions[1][1], "Gate must visibly distinguish corrected from disabled output");
        std::printf("PASS: %zu checks; production ShaderLibrary PSO/root constants, VertexProcessor bindings/dispatch, world transforms, water gate off/on/off reset and GPU readback. No window created.\n", checks);
        return 0;
    } catch (const std::exception &error) {
        std::fprintf(stderr, "FAIL: %s\n", error.what()); return 1;
    }
}
