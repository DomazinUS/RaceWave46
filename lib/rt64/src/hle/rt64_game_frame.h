//
// RT64
//

#pragma once

#include "preset/rt64_preset_scene.h"
#include "render/rt64_buffer_uploader.h"

#include "rt64_projection.h"
#include "rt64_rigid_body.h"

namespace RT64 {
    struct Workload;
    struct WorkloadQueue;

    // Controls the Wave Race 64 water-height Laplacian smoothing pass.
    // Zero preserves the original water heights; one moves each decoded
    // height fully to the mean of its six grid neighbours.
    void setWr64WaterLaplacianStrength(float strength);
    float getWr64WaterLaplacianStrength();

    struct GameIndices {
        struct FramebufferPair {
            uint32_t workloadIndex;
            uint32_t fbPairIndex;
        };

        struct Projection {
            uint32_t workloadIndex;
            uint32_t fbPairIndex;
            uint32_t projectionIndex;
        };

        struct Call {
            uint32_t workloadIndex;
            uint32_t fbPairIndex;
            uint32_t projectionIndex;
            uint32_t callIndex;
        };
    };

    struct GameScene {
        std::vector<GameIndices::Projection> projections;
    };

    inline bool operator==(const GameIndices::FramebufferPair &lhs, const GameIndices::FramebufferPair &rhs) {
        return (lhs.workloadIndex == rhs.workloadIndex) && (lhs.fbPairIndex == rhs.fbPairIndex);
    }

    struct GameFrameMap {
        struct ViewProjectionMap {
            RigidBody rigidBody;
            uint32_t prevTransformIndex = 0;
            bool mapped = false;
        };

        struct TransformMap {
            RigidBody rigidBody;
            uint32_t prevTransformIndex = 0;
            bool mapped = false;
        };

        struct TileMap {
            float deltaUls = 0;
            float deltaUlt = 0;
            float deltaLrs = 0;
            float deltaLrt = 0;
            float prevUls = 0;
            float prevUlt = 0;
            float prevLrs = 0;
            float prevLrt = 0;
            bool mapped = false;
        };

        struct LookAtMap {
            hlslpp::float3 deltaX = {};
            hlslpp::float3 deltaY = {};
            bool mapped = false;
        };

        struct WorkloadMap {
            std::vector<ViewProjectionMap> viewProjections;
            std::vector<TransformMap> transforms;
            std::vector<TileMap> tiles;
            std::vector<LookAtMap> lookAt;
            std::vector<bool> prevTransformsMapped;
            std::vector<bool> prevTilesMapped;
            std::vector<bool> prevLookAtMapped;
            uint32_t prevWorkloadIndex = 0;
            bool mapped = false;
        };

        std::vector<WorkloadMap> workloads;

        void clear() {
            workloads.clear();
        }
    };

    struct GameCallMap {
        uint32_t sceneProjIndex : 10;
        uint32_t callIndex : 20;
        uint32_t doTransformMatching : 1;
        uint32_t doTileInterpolation : 1;
        uint32_t doTileMatching : 1;
    };

    struct ModifiedBuffers {
        bool positionVelocity = false;
        bool texcoordVelocity = false;
        // WATERLOCK-R20: set when the water's heights were smoothed after the
        // first upload, so the positions are sent again.
        bool position = false;
        bool wr64WaterField = false;
        bool wr64WaterCoverage = false;

        void merge(const ModifiedBuffers &modifiedBuffers) {
            positionVelocity |= modifiedBuffers.positionVelocity;
            texcoordVelocity |= modifiedBuffers.texcoordVelocity;
            position |= modifiedBuffers.position;
            wr64WaterField |= modifiedBuffers.wr64WaterField;
            wr64WaterCoverage |= modifiedBuffers.wr64WaterCoverage;
        }

        bool empty() const {
            return !positionVelocity && !texcoordVelocity && !position &&
                !wr64WaterField && !wr64WaterCoverage;
        }
    };

    struct GameFrame {
        PresetScene presetScene;
        GameFrameMap frameMap;
        std::vector<GameScene> perspectiveScenes;
        std::vector<GameScene> orthographicScenes;
        std::vector<uint32_t> workloads;
        bool matched = false;

        bool areFramebufferPairsCompatible(const WorkloadQueue &workloadQueue, const GameIndices::FramebufferPair &first, const GameIndices::FramebufferPair &second);
        bool isSceneCompatible(const WorkloadQueue &workloadQueue, const GameScene &scene, const GameIndices::Projection &proj);
        void set(WorkloadQueue &workloadQueue, const uint32_t *workloadIndices, uint32_t indicesCount);
        void match(RenderWorker *worker, WorkloadQueue &workloadQueue, const GameFrame &prevFrame, BufferUploader *velocityUploader, bool &velocityUploaderUsed, bool &tileInterpolationUsed, bool &lookAtInterpolationUsed);
        void matchScene(WorkloadQueue &workloadQueue, const GameFrame &prevFrame, const GameScene &curScene, const GameScene &prevScene, std::unordered_map<uint32_t, ModifiedBuffers> &workloadsModified, bool &tileInterpolationUsed, bool &lookAtInterpolationUsed);
        void matchTransform(Workload &curWorkload, const Workload &prevWorkload, GameFrameMap::WorkloadMap &curWorkloadMap, const GameFrameMap::WorkloadMap *prevWorkloadMap, uint32_t curTransformIndex, uint32_t prevTransformIndex, ModifiedBuffers &modifiedBuffers, bool forceGeneratedVertexInterpolation, bool protectExactSkyChartCut, const hlslpp::float4x4 *curViewProj, const hlslpp::float4x4 *prevViewProj);
        void buildCallHashMap(uint32_t sceneProjIndex, const Workload &workload, const Projection &proj, std::multimap<uint64_t, GameCallMap> &hashMap) const;
        void buildTransformIdMap(const Workload &workload, std::multimap<uint32_t, uint32_t> &idMap, std::vector<uint32_t> &ignoredIdVector) const;
        uint64_t hashFromCall(const GameCall &call, uint32_t matrixIdHash) const;
        bool isDebuggerCameraEnabled(const WorkloadQueue &workloadQueue);
    };
};
