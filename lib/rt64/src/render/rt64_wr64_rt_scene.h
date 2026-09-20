//
// RT64
//

#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "common/rt64_plume.h"
#include "common/rt64_wr64_rt_fence_proxy.h"

namespace RT64 {
    struct RenderWorker;

    // An opaque draw already selected by the Wave Race scene classifier. All
    // ranges in one scene must use the same world coordinate system. drawIndex
    // addresses FramebufferRenderer's RenderIndices array, not an RDP call ID.
    struct Wr64RTSceneGeometry {
        uint32_t faceIndicesStart = 0;
        uint32_t indexCount = 0;
        uint32_t drawIndex = 0;
        uint32_t shadowFlags = 0; // Bit 0: caster; bit 1: cutout; bit 2: beam; bit 3: private proxy; bit 4: rider/craft.
    };

    struct Wr64RTSceneStats {
        uint32_t geometryCount = 0;
        uint32_t rejectedGeometryCount = 0;
        uint64_t triangleCount = 0;
        uint64_t accelerationStructureBytes = 0;
        uint64_t scratchBytes = 0;
        uint32_t proxyGeometryCount = 0;
        uint64_t proxyTriangleCount = 0;
        bool proxyPayloadReused = false;
        uint64_t proxyUploadBytes = 0;
    };

    // One BLAS containing the selected draw geometries, and one identity TLAS
    // instance. RayQuery::CommittedGeometryIndex() indexes the uint4 metadata:
    // { faceIndicesStart, drawIndex, indexCount, shadowFlags }. Primitive indices are local
    // to that geometry, so the original face indices and materials remain usable.
    //
    // GPU lifetime contract: each instance belongs to one in-flight scene. Before
    // prepare(), reset(), or destruction, the owner must wait for every command
    // list that consumes its previous contents. The source world/index buffers
    // must also remain alive and unchanged through build AND reflection sampling.
    // Separate framebuffer batches that share one submission need separate scene
    // instances. No GPU submission or wait is hidden inside this helper.
    class Wr64RTScene {
    public:
        bool prepare(RenderDevice *device, RenderBuffer *worldPositions,
            RenderBuffer *faceIndices, uint32_t vertexCount, uint32_t indexCount,
            const std::vector<Wr64RTSceneGeometry> &geometries,
            const std::vector<Wr64RTFenceProxy> &proxies = {});

        // Record after uploads and world-position compute on the same graphics
        // command list, before raster reflection draws. Emits BLAS/TLAS and UAV
        // dependencies. Upload-heap inputs remain in their required GENERIC_READ
        // state; they must not be transitioned like default-heap buffers.
        bool recordBuild(RenderWorker *worker);

        // Clears availability while retaining allocations for the next fenced
        // prepare. Only exact, validated private proxy payloads can be reused;
        // current scene membership, material indices and AS builds are refreshed.
        void reset();

        bool prepared() const { return prepared_; }
        bool buildRecorded() const { return buildRecorded_; }
        const RenderAccelerationStructure *accelerationStructure() const {
            return prepared_ ? topLevelAS_.get() : nullptr;
        }
        RenderBuffer *geometryBuffer() const {
            return prepared_ ? geometryUpload_.get() : nullptr;
        }
        uint64_t geometryBufferSize() const { return metadataBytes_; }
        RenderBuffer *proxyBuffer() const { return prepared_ ? proxyVerticesUpload_.get() : nullptr; }
        // Even an empty proxy scene supplies a valid zero-filled SRV record.
        uint64_t proxyBufferSize() const { return proxyVertexBytes_; }
        const Wr64RTSceneStats &stats() const { return stats_; }
        const std::string &lastError() const { return lastError_; }

    private:
        // AS objects must be destroyed before their backing buffer on resize and
        // at destruction; declaration order provides the latter automatically.
        std::unique_ptr<RenderBuffer> bottomLevelBuffer_;
        std::unique_ptr<RenderAccelerationStructure> bottomLevelAS_;
        std::unique_ptr<RenderBuffer> topLevelBuffer_;
        std::unique_ptr<RenderAccelerationStructure> topLevelAS_;
        std::unique_ptr<RenderBuffer> scratchBuffer_;
        std::unique_ptr<RenderBuffer> instancesUpload_;
        std::unique_ptr<RenderBuffer> geometryUpload_;
        std::unique_ptr<RenderBuffer> proxyVerticesUpload_;
        std::unique_ptr<RenderBuffer> proxyIndicesUpload_;
        uint64_t bottomLevelCapacity_ = 0;
        uint64_t topLevelCapacity_ = 0;
        uint64_t scratchCapacity_ = 0;
        uint64_t instancesCapacity_ = 0;
        uint64_t metadataCapacity_ = 0;
        uint64_t metadataBytes_ = 0;
        uint64_t proxyVertexCapacity_ = 0;
        uint64_t proxyIndexCapacity_ = 0;
        uint64_t proxyVertexBytes_ = 0;
        // CPU and upload payloads belong to this fenced scene instance. Ranges
        // store {first, count, input proxy ordinal}, never a cached drawIndex.
        std::vector<Wr64RTFenceVertex> proxyVertices_;
        std::vector<uint32_t> proxyIndices_;
        std::vector<std::array<uint32_t, 3>> proxyRanges_;
        bool proxyPayloadValid_ = false;
        bool proxyUploadValid_ = false;
        RenderDevice *device_ = nullptr;
        RenderBuffer *worldPositions_ = nullptr;
        RenderBuffer *faceIndices_ = nullptr;
        RenderBottomLevelASBuildInfo bottomLevelInfo_;
        RenderTopLevelASBuildInfo topLevelInfo_;
        Wr64RTSceneStats stats_;
        std::string lastError_;
        bool prepared_ = false;
        bool buildRecorded_ = false;
    };
}
