#pragma once

// Headless-only producer for the production RSPWorld -> BLAS -> TLAS ->
// reflection path. Include this header at translation-unit scope. It submits
// no commands itself except when the harness explicitly requests a readback.
#include <array>
#include <cmath>
#include <cstring>
#include <memory>
#include <stdexcept>
#include <vector>

#include "render/rt64_vertex_processor.h"
#include "render/rt64_shader_library.h"
#include "render/rt64_wr64_rt_scene.h"

extern "C" {
    extern const char RSPWorldCSBlobSPIRV[];
    extern const size_t RSPWorldCSBlobSPIRV_size;
}

namespace RT64Tests {
    class VulkanRSPWorldFixture {
        struct Input {
            std::unique_ptr<plume::RenderBuffer> upload;
            std::unique_ptr<plume::RenderBuffer> buffer;
            std::unique_ptr<plume::RenderBufferFormattedView> view;
            uint64_t bytes = 0;
        };

        plume::RenderDevice *device_;
        std::vector<Input> inputs_;
        std::vector<std::array<float, 4>> expected_;
        std::vector<float> nativePositions_;
        RT64::OutputBuffers outputs_;
        RT64::ShaderLibrary shaders_{false, false};
        std::unique_ptr<plume::RenderShader> shader_;
        RT64::VertexProcessor processor_;
        RT64::Wr64RTScene scene_;
        std::unique_ptr<plume::RenderBuffer> readback_;
        float casterOffset_ = 0;
        uint32_t firstCasterVertex_;

        static void check(bool valid, const char *message) {
            if (!valid) throw std::runtime_error(message);
        }

        static void write(plume::RenderBuffer *buffer, const void *data, uint64_t bytes) {
            const plume::RenderRange noRead(0, 0);
            void *mapped = buffer->map(0, &noRead);
            check(mapped != nullptr, "RSP fixture input upload could not map");
            std::memcpy(mapped, data, size_t(bytes));
            const plume::RenderRange written(0, bytes);
            buffer->unmap(0, &written);
        }

        Input &input(const void *data, uint64_t bytes,
            plume::RenderFormat format = plume::RenderFormat::UNKNOWN) {
            Input value;
            value.bytes = bytes;
            value.upload = device_->createBuffer(plume::RenderBufferDesc::UploadBuffer(bytes));
            const auto flags = format == plume::RenderFormat::UNKNOWN ?
                plume::RenderBufferFlag::STORAGE : plume::RenderBufferFlag::FORMATTED;
            value.buffer = device_->createBuffer(plume::RenderBufferDesc::DefaultBuffer(bytes, flags));
            check(value.upload && value.buffer, "RSP fixture input allocation failed");
            if (format != plume::RenderFormat::UNKNOWN)
                value.view = value.buffer->createBufferFormattedView(format);
            write(value.upload.get(), data, bytes);
            inputs_.push_back(std::move(value));
            return inputs_.back();
        }

        void formatted(uint32_t binding, Input &value) {
            processor_.descriptorSet->setBuffer(binding, value.buffer.get(), value.view.get());
        }

        void structured(uint32_t binding, Input &value, uint32_t stride) {
            processor_.descriptorSet->setBuffer(binding, value.buffer.get(),
                plume::RenderBufferStructuredView(stride));
        }

    public:
        VulkanRSPWorldFixture(plume::RenderDevice *device, plume::RenderBuffer *faces,
            uint32_t indexCount, const float (*expectedWorld)[4], uint32_t vertexCount,
            uint32_t firstCasterVertex,
            const std::vector<RT64::Wr64RTSceneGeometry> &geometry)
            : device_(device), processor_(device), firstCasterVertex_(firstCasterVertex) {
            check(device && faces && expectedWorld && vertexCount > 0 &&
                firstCasterVertex < vertexCount, "RSP fixture arguments are invalid");
            inputs_.reserve(16);
            expected_.resize(vertexCount);
            nativePositions_.resize(size_t(vertexCount) * 3);
            for (uint32_t i = 0; i < vertexCount; ++i) {
                check(expectedWorld[i][3] == 1.0f, "RSP fixture expects affine world vertices");
                for (uint32_t j = 0; j < 4; ++j) expected_[i][j] = expectedWorld[i][j];
                // A non-identity world matrix verifies actual matrix evaluation.
                nativePositions_[i * 3] = expectedWorld[i][0] * 0.5f;
                nativePositions_[i * 3 + 1] = expectedWorld[i][1];
                nativePositions_[i * 3 + 2] = expectedWorld[i][2];
            }
            auto &set = *processor_.descriptorSet;
            formatted(set.srcPos, input(nativePositions_.data(), nativePositions_.size() * sizeof(float),
                plume::RenderFormat::R32_FLOAT));
            const std::vector<float> zeros(size_t(vertexCount) * 3, 0);
            formatted(set.srcVel, input(zeros.data(), zeros.size() * sizeof(float), plume::RenderFormat::R32_FLOAT));
            const std::vector<int8_t> normals(size_t(vertexCount) * 4, 0);
            formatted(set.srcNorm, input(normals.data(), normals.size(), plume::RenderFormat::R8_SINT));
            const std::vector<uint16_t> transforms(vertexCount, 0);
            formatted(set.srcIndices, input(transforms.data(), transforms.size() * sizeof(uint16_t),
                plume::RenderFormat::R16_UINT));
            const float worldMatrix[16] = {2,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
            const float inverseTranspose[16] = {.5f,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
            auto &worldMatrices = input(worldMatrix, sizeof(worldMatrix));
            structured(set.worldMats, worldMatrices, sizeof(worldMatrix));
            structured(set.prevWorldMats, worldMatrices, sizeof(worldMatrix));
            structured(set.invTWorldMats, input(inverseTranspose, sizeof(inverseTranspose)), sizeof(inverseTranspose));
            const std::vector<float> texcoords(size_t(vertexCount) * 2, 0);
            auto &tc = input(texcoords.data(), texcoords.size() * sizeof(float), plume::RenderFormat::R32_FLOAT);
            formatted(set.srcTc, tc);
            formatted(set.srcTcVel, tc);
            // Enable the production water branch but mark these ordinary
            // fixture vertices as non-water. Every optional descriptor is valid.
            const std::vector<uint32_t> fieldInfo(size_t(vertexCount) * 4, 0);
            structured(set.wr64WaterFieldInfo, input(fieldInfo.data(), fieldInfo.size() * sizeof(uint32_t)), 16);
            const std::vector<float> fieldPrev(size_t(vertexCount) * 4, 0);
            auto &previousField = input(fieldPrev.data(), fieldPrev.size() * sizeof(float));
            structured(set.wr64WaterFieldPrevPosShiftX, previousField, 16);
            structured(set.wr64WaterFieldPrevTcShiftZ, previousField, 16);
            const uint32_t noFaces = 0;
            structured(set.wr64WaterFieldFaceIndices, input(&noFaces, sizeof(noFaces)), 4);

            const uint64_t outputBytes = uint64_t(vertexCount) * sizeof(float) * 4;
            auto allocateOutput = [&](RT64::ComputedBuffer &buffer, plume::RenderBufferFlags extra) {
                buffer.allocatedSize = outputBytes;
                buffer.buffer = device_->createBuffer(plume::RenderBufferDesc::DefaultBuffer(outputBytes,
                    plume::RenderBufferFlag::STORAGE | plume::RenderBufferFlag::UNORDERED_ACCESS | extra));
                check(buffer.buffer != nullptr, "RSP fixture output allocation failed");
            };
            allocateOutput(outputs_.worldPosBuffer, plume::RenderBufferFlag::ACCELERATION_STRUCTURE_INPUT);
            allocateOutput(outputs_.worldNormBuffer, plume::RenderBufferFlag::NONE);
            allocateOutput(outputs_.worldVelBuffer, plume::RenderBufferFlag::NONE);
            set.setBuffer(set.dstPos, outputs_.worldPosBuffer.buffer.get(), plume::RenderBufferStructuredView(16));
            set.setBuffer(set.dstNorm, outputs_.worldNormBuffer.buffer.get(), plume::RenderBufferStructuredView(16));
            set.setBuffer(set.dstVel, outputs_.worldVelBuffer.buffer.get(), plume::RenderBufferStructuredView(16));
            processor_.worldCB = {0, vertexCount, 0.0f, 1.0f, 1};
            plume::RenderPipelineLayoutBuilder builder;
            builder.begin();
            builder.addPushConstant(0, 0, sizeof(RT64::VertexProcessor::WorldCB), plume::RenderShaderStageFlag::COMPUTE);
            builder.addDescriptorSet(set);
            builder.end();
            shaders_.rspWorld.pipelineLayout = builder.create(device_);
            shader_ = device_->createShader(RSPWorldCSBlobSPIRV, RSPWorldCSBlobSPIRV_size,
                "CSMain", plume::RenderShaderFormat::SPIRV);
            check(shaders_.rspWorld.pipelineLayout && shader_, "RSP fixture shader/layout creation failed");
            shaders_.rspWorld.pipeline = device_->createComputePipeline(plume::RenderComputePipelineDesc(
                shaders_.rspWorld.pipelineLayout.get(), shader_.get(), 64, 1, 1));
            check(shaders_.rspWorld.pipeline != nullptr, "RSP fixture compute pipeline creation failed");
            readback_ = device_->createBuffer(plume::RenderBufferDesc::ReadbackBuffer(outputBytes));
            check(readback_ != nullptr, "RSP fixture readback allocation failed");
            check(scene_.prepare(device_, outputs_.worldPosBuffer.buffer.get(), faces, vertexCount,
                indexCount, geometry), scene_.lastError().c_str());
        }

        void setCasterOffset(float x) {
            casterOffset_ = x;
            for (size_t i = 0; i < expected_.size(); ++i)
                nativePositions_[i * 3] = (expected_[i][0] + (i >= firstCasterVertex_ ? x : 0)) * 0.5f;
            write(inputs_.front().upload.get(), nativePositions_.data(), nativePositions_.size() * sizeof(float));
        }

        void bindReflection(RT64::FramebufferRendererDescriptorCommonSet &common) {
            common.setBuffer(common.posBuffer, outputs_.worldPosBuffer.buffer.get(), outputs_.worldPosBuffer.allocatedSize);
            common.setAccelerationStructure(common.SceneBVH, scene_.accelerationStructure());
            common.setBuffer(common.interleavedRasters, scene_.geometryBuffer(), scene_.geometryBufferSize(),
                plume::RenderBufferStructuredView(16));
            common.setBuffer(common.wr64FenceProxy, scene_.proxyBuffer(), scene_.proxyBufferSize());
        }

        // Invoke immediately after the harness begins its draw command list.
        // The resulting AS and the reflection draw belong to one submission.
        void record(RT64::RenderWorker &worker) {
            std::vector<plume::RenderBufferBarrier> barriers;
            for (auto &value : inputs_) barriers.emplace_back(value.buffer.get(), plume::RenderBufferAccess::WRITE);
            worker.commandList->barriers(plume::RenderBarrierStage::COPY, barriers);
            for (auto &value : inputs_)
                worker.commandList->copyBufferRegion(value.buffer->at(0), value.upload->at(0), value.bytes);
            for (auto &value : barriers) value.accessBits = plume::RenderBufferAccess::READ;
            worker.commandList->barriers(plume::RenderBarrierStage::ALL, barriers);
            processor_.recordCommandList(&worker, &shaders_, &outputs_);
            check(scene_.recordBuild(&worker), "RSP fixture compute-produced scene build failed");
        }

        void verifyPositions(RT64::RenderWorker &worker) {
            const auto bytes = outputs_.worldPosBuffer.allocatedSize;
            worker.commandList->begin();
            const plume::RenderBufferBarrier barriers[] = {
                {outputs_.worldPosBuffer.buffer.get(), plume::RenderBufferAccess::READ},
                {readback_.get(), plume::RenderBufferAccess::WRITE}
            };
            worker.commandList->barriers(plume::RenderBarrierStage::COPY, barriers, 2, nullptr, 0);
            worker.commandList->copyBufferRegion(readback_->at(0), outputs_.worldPosBuffer.buffer->at(0), bytes);
            worker.commandList->barriers(plume::RenderBarrierStage::GRAPHICS_AND_COMPUTE,
                plume::RenderBufferBarrier(outputs_.worldPosBuffer.buffer.get(), plume::RenderBufferAccess::READ));
            worker.commandList->end();
            worker.execute();
            worker.wait();
            const plume::RenderRange readRange(0, bytes), noWrite(0, 0);
            const float *actual = static_cast<const float *>(readback_->map(0, &readRange));
            check(actual != nullptr, "RSP fixture world-position readback failed");
            bool correct = true;
            for (size_t i = 0; i < expected_.size(); ++i) for (uint32_t j = 0; j < 4; ++j) {
                const float expected = expected_[i][j] + (j == 0 && i >= firstCasterVertex_ ? casterOffset_ : 0);
                correct &= std::isfinite(actual[i * 4 + j]) && std::abs(actual[i * 4 + j] - expected) <= 1e-5f;
            }
            readback_->unmap(0, &noWrite);
            check(correct, "RSP fixture compute-produced positions differ from known world coordinates");
        }
    };
}
