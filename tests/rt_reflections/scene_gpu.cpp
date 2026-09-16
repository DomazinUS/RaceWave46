// Headless GPU test of the production Wr64RTScene helper. No window, swapchain,
// ROM, game process, input device, or texture assets are used.
#include <array>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <vector>

#include <d3d12sdklayers.h>
#include "plume_d3d12.h"
#include "render/rt64_render_worker.h"
#include "render/rt64_wr64_rt_scene.h"

using namespace plume;
using namespace RT64;

namespace {
    size_t checks = 0;
    void require(bool value, const char *message) {
        ++checks;
        if (!value) throw std::runtime_error(message);
    }
    void upload(RenderBuffer *buffer, const void *data, size_t size) {
        const RenderRange noRead(0, 0);
        void *mapped = buffer->map(0, &noRead);
        require(mapped != nullptr, "Upload mapping failed");
        std::memcpy(mapped, data, size);
        const RenderRange written(0, size);
        buffer->unmap(0, &written);
    }
    struct Result {
        uint32_t identity[4];
        float values[4];
        uint32_t proxyWords[12];
    };
    static_assert(sizeof(Result) == 80, "HLSL result stride mismatch");
    void expectHit(const Result &r, uint32_t geometry, uint32_t draw, uint32_t start, uint32_t primitive = 0) {
        require(r.identity[0] == 1, "Expected a triangle hit");
        require(r.identity[1] == geometry, "Wrong committed geometry index");
        require(r.identity[2] == draw, "Wrong original draw metadata");
        require(r.identity[3] == start, "Wrong original face-index offset");
        require(std::fabs(r.values[0] - 0.25f) < 1.0e-4f, "Wrong first barycentric coordinate");
        require(std::fabs(r.values[1] - 0.5f) < 1.0e-4f, "Wrong second barycentric coordinate");
        require(std::fabs(r.values[2] - 3.0f) < 1.0e-4f, "Wrong committed hit distance");
        require(r.values[3] == float(primitive), "Primitive index must be local to its geometry");
    }
    void expectMiss(const Result &r) {
        require(r.identity[0] == 0, "Expected a miss; stale geometry may remain");
        require(r.identity[1] == UINT32_MAX && r.identity[2] == UINT32_MAX,
            "Miss path must not read geometry metadata");
    }
}

int main(int argc, char **argv) {
    try {
        require(argc == 2, "Usage: scene_gpu.exe scene_gpu.dxil");
        std::ifstream shaderFile(argv[1], std::ios::binary);
        require(shaderFile.good(), "Could not open compute shader");
        std::vector<char> shaderBytes((std::istreambuf_iterator<char>(shaderFile)), {});
        require(!shaderBytes.empty(), "Compute shader is empty");

        ID3D12Debug *debug = nullptr;
        const bool debugLayer = SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debug)));
        if (debugLayer) {
            debug->EnableDebugLayer();
            debug->Release();
        }
        D3D12Interface renderInterface;
        require(renderInterface.isValid(), "D3D12 interface initialization failed");
        auto device = renderInterface.createDevice("");
        require(device != nullptr, "D3D12 device initialization failed");
        auto *native = static_cast<D3D12Device *>(device.get());
        D3D12_FEATURE_DATA_D3D12_OPTIONS5 options{};
        // Plume intentionally queries only SM6.0 for its ordinary raster path;
        // its cached shaderModel is not the hardware's maximum shader model.
        D3D12_FEATURE_DATA_SHADER_MODEL shaderModel{D3D_SHADER_MODEL_6_5};
        if (!device->getCapabilities().raytracing ||
            FAILED(native->d3d->CheckFeatureSupport(D3D12_FEATURE_SHADER_MODEL, &shaderModel, sizeof(shaderModel))) ||
            shaderModel.HighestShaderModel < D3D_SHADER_MODEL_6_5 ||
            FAILED(native->d3d->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS5, &options, sizeof(options))) ||
            options.RaytracingTier < D3D12_RAYTRACING_TIER_1_1)
        {
            std::puts("SKIP: shader model 6.5 and DXR 1.1 are required.");
            return 77;
        }

        ID3D12InfoQueue *messages = nullptr;
        native->d3d->QueryInterface(IID_PPV_ARGS(&messages));
        if (messages) messages->ClearStoredMessages();

        RenderWorker worker(device.get(), "Headless reflection AS test", RenderCommandListType::DIRECT);
        std::array<std::array<float, 4>, 6> vertices{{
            {{-1, -1, 3, 1}}, {{1, -1, 3, 1}}, {{0, 1, 3, 1}},
            {{4, -1, 3, 1}}, {{6, -1, 3, 1}}, {{5, 1, 3, 1}}
        }};
        const uint32_t indices[] = { 0, 1, 2, 3, 4, 5 };
        auto positions = device->createBuffer(RenderBufferDesc::DefaultBuffer(sizeof(vertices),
            RenderBufferFlag::STORAGE | RenderBufferFlag::UNORDERED_ACCESS | RenderBufferFlag::ACCELERATION_STRUCTURE_INPUT));
        auto faces = device->createBuffer(RenderBufferDesc::DefaultBuffer(sizeof(indices),
            RenderBufferFlag::INDEX | RenderBufferFlag::STORAGE | RenderBufferFlag::ACCELERATION_STRUCTURE_INPUT));
        auto positionUpload = device->createBuffer(RenderBufferDesc::UploadBuffer(sizeof(vertices)));
        auto indexUpload = device->createBuffer(RenderBufferDesc::UploadBuffer(sizeof(indices)));
        auto output = device->createBuffer(RenderBufferDesc::DefaultBuffer(sizeof(Result) * 4,
            RenderBufferFlag::STORAGE | RenderBufferFlag::UNORDERED_ACCESS));
        auto readback = device->createBuffer(RenderBufferDesc::ReadbackBuffer(sizeof(Result) * 4));
        require(positions && faces && positionUpload && indexUpload && output && readback, "Could not allocate probe buffers");
        upload(indexUpload.get(), indices, sizeof(indices));

        RenderDescriptorSetBuilder setBuilder;
        setBuilder.begin();
        const uint32_t asDescriptor = setBuilder.addAccelerationStructure(26);
        const uint32_t geometryDescriptor = setBuilder.addStructuredBuffer(40);
        const uint32_t proxyDescriptor = setBuilder.addByteAddressBuffer(41);
        const uint32_t resultDescriptor = setBuilder.addReadWriteStructuredBuffer(0);
        setBuilder.end();
        auto descriptors = setBuilder.create(device.get());
        RenderPipelineLayoutBuilder layoutBuilder;
        layoutBuilder.begin();
        layoutBuilder.addDescriptorSet(setBuilder.descriptorSetDesc);
        layoutBuilder.end();
        auto layout = layoutBuilder.create(device.get());
        auto shader = device->createShader(shaderBytes.data(), shaderBytes.size(), "CSMain", RenderShaderFormat::DXIL);
        auto pipeline = device->createComputePipeline(RenderComputePipelineDesc(layout.get(), shader.get(), 4, 1, 1));
        require(descriptors && layout && shader && pipeline, "Could not create the ray-query pipeline");
        const RenderBufferStructuredView resultView(sizeof(Result));
        descriptors->setBuffer(resultDescriptor, output.get(), sizeof(Result) * 4, &resultView);

        Wr64RTScene scene;
        auto executeScene = [&](Wr64RTScene &activeScene) {
            upload(positionUpload.get(), vertices.data(), sizeof(vertices));
            descriptors->setAccelerationStructure(asDescriptor, activeScene.accelerationStructure());
            const RenderBufferStructuredView metadataView(16);
            descriptors->setBuffer(geometryDescriptor, activeScene.geometryBuffer(), activeScene.geometryBufferSize(), &metadataView);
            descriptors->setBuffer(proxyDescriptor, activeScene.proxyBuffer(), activeScene.proxyBufferSize());
            worker.commandList->begin();
            const RenderBufferBarrier copy[] = {
                { positions.get(), RenderBufferAccess::WRITE }, { faces.get(), RenderBufferAccess::WRITE }
            };
            worker.commandList->barriers(RenderBarrierStage::COPY, copy, 2, nullptr, 0);
            worker.commandList->copyBufferRegion(positions->at(0), positionUpload->at(0), sizeof(vertices));
            worker.commandList->copyBufferRegion(faces->at(0), indexUpload->at(0), sizeof(indices));
            require(activeScene.recordBuild(&worker), "Production AS build was not recorded");
            worker.commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE,
                RenderBufferBarrier(output.get(), RenderBufferAccess::WRITE));
            worker.commandList->setComputePipelineLayout(layout.get());
            worker.commandList->setPipeline(pipeline.get());
            worker.commandList->setComputeDescriptorSet(descriptors.get(), 0);
            worker.commandList->dispatch(1, 1, 1);
            worker.commandList->barriers(RenderBarrierStage::COPY,
                RenderBufferBarrier(output.get(), RenderBufferAccess::READ));
            worker.commandList->copyBufferRegion(readback->at(0), output->at(0), sizeof(Result) * 4);
            worker.commandList->end();
            worker.execute();
            worker.wait();
            std::array<Result, 4> results;
            const RenderRange read(0, sizeof(results));
            const void *mapped = readback->map(0, &read);
            require(mapped != nullptr, "Readback mapping failed");
            std::memcpy(results.data(), mapped, sizeof(results));
            const RenderRange noWrite(0, 0);
            readback->unmap(0, &noWrite);
            return results;
        };
        auto execute = [&]() { return executeScene(scene); };

        const std::vector<Wr64RTSceneGeometry> first = {
            {0, 3, 17}, {0, 2, 999}, {UINT32_MAX, 3, 999}, {3, 6, 999}, {3, 3, 77}
        };
        require(scene.prepare(device.get(), positions.get(), faces.get(), 6, 6, first), scene.lastError().c_str());
        require(scene.stats().geometryCount == 2 && scene.stats().rejectedGeometryCount == 3,
            "Invalid ranges must be excluded without shifting valid hit metadata");
        require(scene.stats().triangleCount == 2 && scene.geometryBufferSize() == 32,
            "Wrong accepted scene geometry counts");
        const RenderAccelerationStructure *firstAS = scene.accelerationStructure();
        auto result = execute();
        expectHit(result[0], 0, 17, 0);
        expectHit(result[1], 1, 77, 3);
        expectMiss(result[2]);
        expectMiss(result[3]);

        // The fence above permits reuse. Move the geometry, remove the second
        // range, and change the draw identity without reallocating the AS.
        for (auto &vertex : vertices) vertex[0] += 10.0f;
        require(scene.prepare(device.get(), positions.get(), faces.get(), 6, 6, {{0, 3, 88}}), scene.lastError().c_str());
        require(scene.accelerationStructure() == firstAS, "Smaller scene should reuse AS allocations after its fence");
        require(scene.stats().geometryCount == 1 && scene.geometryBufferSize() == 16,
            "Rebuild retained stale geometry metadata");
        result = execute();
        expectMiss(result[0]);
        expectMiss(result[1]);
        expectHit(result[2], 0, 88, 0);
        expectMiss(result[3]);

        require(!scene.prepare(device.get(), positions.get(), faces.get(), 6, 6, {{6, 3, 0}}),
            "Entirely invalid scene should not prepare");
        require(!scene.prepared() && scene.accelerationStructure() == nullptr && scene.geometryBuffer() == nullptr,
            "Invalid scene must not expose the previous frame AS");
        require(!scene.recordBuild(&worker), "Invalid scene must not record GPU work");
        require(!scene.prepare(device.get(), positions.get(), faces.get(), 6, 6, {}),
            "Empty scene should not prepare");
        require(!scene.prepare(nullptr, positions.get(), faces.get(), 6, 6, first),
            "Missing device should not prepare");

#include "scene_proxy_cache_fixture.inl"

        uint32_t debugErrors = 0;
        if (messages) {
            const UINT64 count = messages->GetNumStoredMessagesAllowedByRetrievalFilter();
            for (UINT64 i = 0; i < count; ++i) {
                SIZE_T size = 0;
                messages->GetMessage(i, nullptr, &size);
                std::vector<char> bytes(size);
                auto *message = reinterpret_cast<D3D12_MESSAGE *>(bytes.data());
                if (SUCCEEDED(messages->GetMessage(i, message, &size)) &&
                    message->Severity <= D3D12_MESSAGE_SEVERITY_ERROR)
                {
                    std::fprintf(stderr, "D3D12 validation: %s\n", message->pDescription);
                    ++debugErrors;
                }
            }
            messages->Release();
        }
        require(debugErrors == 0, "D3D12 validation reported an error");
        std::printf("PASS: %zu checks; actual production BLAS/TLAS helper, RayQuery hit/miss, geometry IDs, barycentrics, distance, fenced rebuild, proxy payload caching/invalidation/per-view isolation, invalid ranges; debug layer %s.\n",
            checks, debugLayer ? "enabled" : "unavailable");
        return 0;
    }
    catch (const std::exception &error) {
        std::fprintf(stderr, "FAIL after %zu checks: %s\n", checks, error.what());
        return 1;
    }
}
