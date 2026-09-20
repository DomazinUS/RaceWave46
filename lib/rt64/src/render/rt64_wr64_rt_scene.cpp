//
// RT64
//

#include "rt64_wr64_rt_scene.h"

#include <algorithm>
#include <array>
#include <cstring>
#include <limits>

#include "rt64_render_worker.h"

namespace RT64 {
    namespace {
        bool uploadBytes(RenderBuffer *buffer, const void *bytes, uint64_t size) {
            const RenderRange noRead(0, 0);
            void *mapped = buffer->map(0, &noRead);
            if (mapped == nullptr) {
                return false;
            }

            std::memcpy(mapped, bytes, size_t(size));
            const RenderRange written(0, size);
            buffer->unmap(0, &written);
            return true;
        }
    }

    void Wr64RTScene::reset() {
        prepared_ = false;
        buildRecorded_ = false;
        worldPositions_ = nullptr;
        faceIndices_ = nullptr;
        metadataBytes_ = 0;
        proxyVertexBytes_ = 0;
        stats_ = {};
        lastError_.clear();
    }

    bool Wr64RTScene::prepare(RenderDevice *device, RenderBuffer *worldPositions,
        RenderBuffer *faceIndices, uint32_t vertexCount, uint32_t indexCount,
        const std::vector<Wr64RTSceneGeometry> &geometries,
        const std::vector<Wr64RTFenceProxy> &proxies)
    {
        reset();
        if ((device == nullptr) || (!device->getCapabilities().raytracing && !device->getCapabilities().rayQueries)) {
            lastError_ = "Hardware ray tracing is unavailable.";
            return false;
        }

        if ((device_ != nullptr) && (device_ != device)) {
            lastError_ = "The scene cannot move between graphics devices.";
            return false;
        }

        if ((worldPositions == nullptr) || (faceIndices == nullptr) ||
            (vertexCount == 0) || (indexCount == 0) || (geometries.empty() && proxies.empty()))
        {
            lastError_ = "No eligible scene geometry was submitted.";
            return false;
        }

        if (geometries.size() > std::numeric_limits<uint32_t>::max() ||
            proxies.size() > std::numeric_limits<uint32_t>::max() - geometries.size()) {
            lastError_ = "The scene contains too many geometry ranges.";
            return false;
        }

        device_ = device;
        std::vector<RenderBottomLevelASMesh> meshes;
        std::vector<std::array<uint32_t, 4>> metadata;
        meshes.reserve(geometries.size()+proxies.size());
        metadata.reserve(geometries.size()+proxies.size());
        for (const Wr64RTSceneGeometry &geometry : geometries) {
            // Subtraction prevents overflow for malformed offsets. Individual
            // index values are supplied by the renderer's validated draw data.
            if ((geometry.shadowFlags & 8u) != 0 || (geometry.indexCount == 0) || (geometry.indexCount % 3 != 0) ||
                (geometry.faceIndicesStart > indexCount) ||
                (geometry.indexCount > indexCount - geometry.faceIndicesStart))
            {
                stats_.rejectedGeometryCount++;
                continue;
            }

            meshes.emplace_back(faceIndices->at(uint64_t(geometry.faceIndicesStart) * sizeof(uint32_t)),
                worldPositions->at(0), RenderFormat::R32_UINT, RenderFormat::R32G32B32_FLOAT,
                geometry.indexCount, vertexCount, uint32_t(sizeof(float) * 4), (geometry.shadowFlags & 6u) == 0);
            metadata.push_back({ geometry.faceIndicesStart, geometry.drawIndex, geometry.indexCount, geometry.shadowFlags });
            stats_.triangleCount += geometry.indexCount / 3;
        }

        // Match the entire ordered payload, not an address/hash or draw index.
        // Native culling and visibility may change the list each presentation.
        // The shader's current material ownership is populated below even on a
        // hit. Failed/rejected inputs are never admitted to this cache.
        bool reuseProxyPayload = proxyPayloadValid_ && proxyRanges_.size() == proxies.size();
        for (size_t i = 0; reuseProxyPayload && i < proxies.size(); ++i) {
            const auto &range = proxyRanges_[i];
            const auto &triangles = proxies[i].triangles;
            reuseProxyPayload = triangles.size() == range[1] &&
                std::memcmp(triangles.data(), proxyVertices_.data() + range[0],
                    triangles.size() * sizeof(Wr64RTFenceVertex)) == 0;
        }
        stats_.proxyPayloadReused = reuseProxyPayload;
        constexpr size_t maximumProxyVertices = 262144;
        if (!reuseProxyPayload) {
            proxyPayloadValid_ = false;
            proxyUploadValid_ = false;
            proxyVertices_.clear();
            proxyIndices_.clear();
            proxyRanges_.clear();
            for (size_t ordinal = 0; ordinal < proxies.size(); ++ordinal) {
                const auto &proxy = proxies[ordinal];
                bool valid = !proxy.triangles.empty() && proxy.triangles.size()%3 == 0 &&
                    proxy.triangles.size() <= 24576 &&
                    proxyVertices_.size()+proxy.triangles.size() <= maximumProxyVertices;
                if (valid) for (const auto &vertex : proxy.triangles) {
                    for (float value : vertex.position) valid &= std::isfinite(value);
                    for (float value : vertex.uv) valid &= std::isfinite(value);
                    for (float value : vertex.shade) valid &= std::isfinite(value);
                    valid &= std::abs(vertex.position[3]-1.0f) <= 1e-5f;
                }
                if (!valid) { stats_.rejectedGeometryCount++; continue; }
                const uint32_t first = uint32_t(proxyVertices_.size()), count = uint32_t(proxy.triangles.size());
                proxyRanges_.push_back({first, count, uint32_t(ordinal)});
                proxyVertices_.insert(proxyVertices_.end(), proxy.triangles.begin(), proxy.triangles.end());
                for (uint32_t i = 0; i < count; ++i) proxyIndices_.push_back(first + i);
            }
            // The private shader SRV remains initialized with no proxy draws.
            if (proxyVertices_.empty()) proxyVertices_.emplace_back();
            proxyPayloadValid_ = proxyRanges_.size() == proxies.size();
        }
        proxyVertexBytes_ = proxyVertices_.size()*sizeof(Wr64RTFenceVertex);
        if (!proxyVerticesUpload_ || proxyVertexCapacity_ < proxyVertexBytes_) {
            proxyUploadValid_ = false;
            proxyVerticesUpload_ = device->createBuffer(RenderBufferDesc::UploadBuffer(proxyVertexBytes_,
                RenderBufferFlag::STORAGE | RenderBufferFlag::ACCELERATION_STRUCTURE_INPUT));
            proxyVertexCapacity_ = proxyVerticesUpload_ ? proxyVertexBytes_ : 0;
            if (proxyVerticesUpload_) proxyVerticesUpload_->setName("WR64 native fence shadow proxy vertices");
        }
        const uint64_t proxyIndexBytes = proxyIndices_.size()*sizeof(uint32_t);
        if (proxyIndexBytes && (!proxyIndicesUpload_ || proxyIndexCapacity_ < proxyIndexBytes)) {
            proxyUploadValid_ = false;
            proxyIndicesUpload_ = device->createBuffer(RenderBufferDesc::UploadBuffer(proxyIndexBytes,
                RenderBufferFlag::ACCELERATION_STRUCTURE_INPUT));
            proxyIndexCapacity_ = proxyIndicesUpload_ ? proxyIndexBytes : 0;
            if (proxyIndicesUpload_) proxyIndicesUpload_->setName("WR64 native fence shadow proxy indices");
        }
        if (!proxyUploadValid_) {
            if (!proxyVerticesUpload_ || !uploadBytes(proxyVerticesUpload_.get(),proxyVertices_.data(),proxyVertexBytes_) ||
                (proxyIndexBytes && (!proxyIndicesUpload_ || !uploadBytes(proxyIndicesUpload_.get(),proxyIndices_.data(),proxyIndexBytes)))) {
                lastError_ = "Could not upload fence shadow proxy data.";
                return false;
            }
            proxyUploadValid_ = true;
            stats_.proxyUploadBytes = proxyVertexBytes_ + proxyIndexBytes;
        }
        for (const auto &range : proxyRanges_) {
            meshes.emplace_back(proxyIndicesUpload_->at(uint64_t(range[0])*sizeof(uint32_t)),
                proxyVerticesUpload_->at(0),RenderFormat::R32_UINT,RenderFormat::R32G32B32_FLOAT,
                range[1],uint32_t(proxyVertices_.size()),uint32_t(sizeof(Wr64RTFenceVertex)),false);
            // x indexes private vertices, not the original face-index stream.
            metadata.push_back({range[0],proxies[range[2]].drawIndex,range[1],11u});
            stats_.proxyGeometryCount++;
            stats_.proxyTriangleCount += range[1]/3;
            stats_.triangleCount += range[1]/3;
        }

        if (meshes.empty()) {
            lastError_ = "All scene geometry ranges were empty or invalid.";
            return false;
        }

        // Rebuild from current interpolated positions; no stale offscreen cache
        // or BLAS update assumptions are introduced by this first experiment.
        device->setBottomLevelASBuildInfo(bottomLevelInfo_, meshes.data(), uint32_t(meshes.size()), true, false);
        if ((bottomLevelInfo_.accelerationStructureSize == 0) || (bottomLevelInfo_.scratchSize == 0)) {
            lastError_ = "The graphics backend did not provide BLAS build sizes.";
            return false;
        }

        if (!bottomLevelAS_ || (bottomLevelCapacity_ < bottomLevelInfo_.accelerationStructureSize)) {
            bottomLevelAS_.reset();
            bottomLevelBuffer_ = device->createBuffer(RenderBufferDesc::AccelerationStructureBuffer(bottomLevelInfo_.accelerationStructureSize));
            if (!bottomLevelBuffer_) {
                lastError_ = "Could not allocate the scene BLAS.";
                return false;
            }
            bottomLevelCapacity_ = bottomLevelInfo_.accelerationStructureSize;
            bottomLevelBuffer_->setName("WR64 reflection scene BLAS");
            bottomLevelAS_ = device->createAccelerationStructure(RenderAccelerationStructureDesc(
                RenderAccelerationStructureType::BOTTOM_LEVEL, bottomLevelBuffer_->at(0), bottomLevelCapacity_));
        }

        if (!bottomLevelAS_) {
            lastError_ = "Could not create the scene BLAS view.";
            return false;
        }

        // Positions are already in world space. Geometry IDs identify material
        // ranges; there is no second instance transform to apply to the vertices.
        RenderTopLevelASInstance instance(bottomLevelBuffer_->at(0), 0, 0xFF, 0, true, RenderAffineTransform());
        instance.bottomLevelASDeviceAddress = bottomLevelAS_->getDeviceAddress();
        if (instance.bottomLevelASDeviceAddress == 0) {
            lastError_ = "The graphics backend did not provide a BLAS device address.";
            return false;
        }
        device->setTopLevelASBuildInfo(topLevelInfo_, &instance, 1, true, false);
        if ((topLevelInfo_.accelerationStructureSize == 0) || (topLevelInfo_.scratchSize == 0) ||
            topLevelInfo_.instancesBufferData.empty())
        {
            lastError_ = "The graphics backend did not provide TLAS build data.";
            return false;
        }

        if (!topLevelAS_ || (topLevelCapacity_ < topLevelInfo_.accelerationStructureSize)) {
            topLevelAS_.reset();
            topLevelBuffer_ = device->createBuffer(RenderBufferDesc::AccelerationStructureBuffer(topLevelInfo_.accelerationStructureSize));
            if (!topLevelBuffer_) {
                lastError_ = "Could not allocate the scene TLAS.";
                return false;
            }
            topLevelCapacity_ = topLevelInfo_.accelerationStructureSize;
            topLevelBuffer_->setName("WR64 reflection scene TLAS");
            topLevelAS_ = device->createAccelerationStructure(RenderAccelerationStructureDesc(
                RenderAccelerationStructureType::TOP_LEVEL, topLevelBuffer_->at(0), topLevelCapacity_));
        }

        const uint64_t scratchSize = std::max(bottomLevelInfo_.scratchSize, topLevelInfo_.scratchSize);
        if (scratchCapacity_ < scratchSize) {
            scratchBuffer_ = device->createBuffer(RenderBufferDesc::DefaultBuffer(scratchSize,
                RenderBufferFlag::ACCELERATION_STRUCTURE_SCRATCH | RenderBufferFlag::UNORDERED_ACCESS));
            scratchCapacity_ = scratchBuffer_ ? scratchSize : 0;
            if (scratchBuffer_) {
                scratchBuffer_->setName("WR64 reflection AS scratch");
            }
        }

        const uint64_t instancesSize = topLevelInfo_.instancesBufferData.size();
        if (instancesCapacity_ < instancesSize) {
            instancesUpload_ = device->createBuffer(RenderBufferDesc::UploadBuffer(instancesSize,
                RenderBufferFlag::ACCELERATION_STRUCTURE_INPUT));
            instancesCapacity_ = instancesUpload_ ? instancesSize : 0;
            if (instancesUpload_) {
                instancesUpload_->setName("WR64 reflection TLAS instance");
            }
        }

        const uint64_t metadataSize = metadata.size() * sizeof(metadata.front());
        static_assert(sizeof(std::array<uint32_t, 4>) == 16, "Reflection geometry metadata must match HLSL uint4.");
        if (metadataCapacity_ < metadataSize) {
            geometryUpload_ = device->createBuffer(RenderBufferDesc::UploadBuffer(metadataSize, RenderBufferFlag::STORAGE));
            metadataCapacity_ = geometryUpload_ ? metadataSize : 0;
            if (geometryUpload_) {
                geometryUpload_->setName("WR64 reflection draw metadata");
            }
        }

        if (!topLevelAS_ || topLevelAS_->getDeviceAddress() == 0 ||
            !scratchBuffer_ || !instancesUpload_ || !geometryUpload_) {
            lastError_ = "Could not allocate reflection scene resources.";
            return false;
        }

        if (!uploadBytes(instancesUpload_.get(), topLevelInfo_.instancesBufferData.data(), instancesSize) ||
            !uploadBytes(geometryUpload_.get(), metadata.data(), metadataSize))
        {
            lastError_ = "Could not upload reflection scene metadata.";
            return false;
        }

        worldPositions_ = worldPositions;
        faceIndices_ = faceIndices;
        metadataBytes_ = metadataSize;
        stats_.geometryCount = uint32_t(meshes.size());
        stats_.accelerationStructureBytes = bottomLevelInfo_.accelerationStructureSize + topLevelInfo_.accelerationStructureSize;
        stats_.scratchBytes = scratchSize;
        prepared_ = true;
        return true;
    }

    bool Wr64RTScene::recordBuild(RenderWorker *worker) {
        if (!prepared_ || (worker == nullptr) || (worker->device != device_) || !worker->commandList) {
            return false;
        }

        // Finish RSP/world-position UAV writes before AS reads. ALL_SHADER_RESOURCE
        // includes NON_PIXEL_SHADER_RESOURCE required by D3D12 AS input buffers.
        const RenderBufferBarrier before[] = {
            RenderBufferBarrier(worldPositions_, RenderBufferAccess::READ),
            RenderBufferBarrier(faceIndices_, RenderBufferAccess::READ),
            RenderBufferBarrier(scratchBuffer_.get(), RenderBufferAccess::WRITE),
            RenderBufferBarrier(bottomLevelBuffer_.get(), RenderBufferAccess::WRITE),
            RenderBufferBarrier(topLevelBuffer_.get(), RenderBufferAccess::WRITE)
        };
        worker->commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE,
            before, uint32_t(std::size(before)), nullptr, 0);
        worker->commandList->buildBottomLevelAS(bottomLevelAS_.get(), scratchBuffer_->at(0), bottomLevelInfo_);

        // Both dependencies matter: TLAS reads BLAS, and reuses its scratch.
        const RenderBufferBarrier between[] = {
            RenderBufferBarrier(bottomLevelBuffer_.get(), RenderBufferAccess::READ),
            RenderBufferBarrier(scratchBuffer_.get(), RenderBufferAccess::WRITE)
        };
        worker->commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE,
            between, uint32_t(std::size(between)), nullptr, 0);
        worker->commandList->buildTopLevelAS(topLevelAS_.get(), scratchBuffer_->at(0), instancesUpload_->at(0), topLevelInfo_);
        worker->commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE,
            RenderBufferBarrier(topLevelBuffer_.get(), RenderBufferAccess::READ));
        buildRecorded_ = true;
        return true;
    }
}
