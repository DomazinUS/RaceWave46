//
// RT64
//

#pragma once

#include <algorithm>

#include "render/rt64_buffer_uploader.h"
#include "shared/rt64_extra_params.h"
#include "shared/rt64_gpu_tile.h"
#include "shared/rt64_rdp_params.h"
#include "shared/rt64_render_params.h"
#include "shared/rt64_rsp_fog.h"
#include "shared/rt64_rsp_light.h"
#include "shared/rt64_rsp_lookat.h"
#include "shared/rt64_rsp_viewport.h"

#include <unordered_map>

#include "rt64_command_warning.h"
#include "rt64_draw_call.h"
#include "rt64_framebuffer_changes.h"
#include "rt64_framebuffer_manager.h"
#include "rt64_framebuffer_pair.h"
#include "rt64_framebuffer_storage.h"
#include "rt64_transform_group.h"
#include "common/rt64_wr64_split_marker.h"
#include "common/rt64_wr64_rt_celestial.h"
#include "common/rt64_wr64_rt_shadow.h"
#include "common/rt64_wr64_native_water_distance.h"
#include "common/rt64_wr64_wave_distance.h"
#include "common/rt64_wr64_native_wave_distance.h"
#include "common/rt64_wr64_dolphin_sun_edge.h"

namespace RT64 {
    struct DrawData {
        std::vector<float> posFloats;
        std::vector<float> velFloats;
        std::vector<float> tcFloats;
        std::vector<float> tcVelFloats;
        std::vector<uint8_t> normColBytes;
        std::vector<uint16_t> viewProjIndices;
        std::vector<uint16_t> worldIndices;
        std::vector<uint16_t> fogIndices;
        std::vector<uint16_t> lightIndices;
        std::vector<uint8_t> lightCounts;
        std::vector<uint16_t> lookAtIndices;
        // Original segmented VTX source for every decoded global vertex.
        // CPU-only provenance used by game-specific call classification.
        std::vector<uint32_t> vertexSegmentedAddresses;
        // Opaque wrapped-grid cell identity used by Wave Race 64's generated
        // water. Captured when the RSP ingests each native frame so matching
        // does not confuse a reused output VTX slot with its previous cell.
        std::vector<uint32_t> wr64WaterProducerKeys;
        // CPU-only tag filled by GameFrame once the generated water draw has
        // been identified from its indexed vertex provenance. This lets
        // per-present diagnostics observe the exact sheet without treating
        // unrelated segment-3 scratch geometry as water.
        std::vector<uint8_t> wr64WaterVertexMask;
        std::vector<uint32_t> wr64WaterFaceIndices;
        // GPU presentation data for Wave Race 64's finite generated water
        // sheet.  Ordinary vertices contain zeroed records.  Water records
        // let RSPProcessCS evaluate the previous and current height/UV fields
        // at the actual presentation-time X/Z point instead of reducing that
        // moving sample to one linear endpoint velocity.
        std::vector<uint32_t> wr64WaterFieldInfo;
        std::vector<hlslpp::float4> wr64WaterFieldPrevPosShiftX;
        std::vector<hlslpp::float4> wr64WaterFieldPrevTcShiftZ;
        std::vector<uint32_t> wr64WaterFieldFaceIndices;
        // Native submission that produced the tagged water call. Diagnostics
        // use this to group the many presentation-rate evaluations belonging
        // to one 20 Hz game update. It has no rendering effect.
        uint64_t wr64WaterSubmissionFrame = 0;
        // Actual neutral annulus extent committed to this draw. Keep both
        // native endpoints available when the setting or camera scope changes.
        uint32_t wr64FarWaterDistanceMode = 0;
        std::array<Wr64NativeWaterDistanceView, 3> wr64NativeWaterDistance{};
        Wr64WaveDistanceDraw wr64WaveDistance;
        std::array<Wr64NativeWaveDistanceView, 3> wr64NativeWaveDistance;
        std::vector<uint32_t> faceIndices;
        std::vector<uint32_t> modifyPosUints;
        std::vector<hlslpp::float4> posTransformed;
        std::vector<hlslpp::float3> posScreen;
        std::vector<interop::RDPParams> rdpParams;
        std::vector<interop::ExtraParams> extraParams;
        std::vector<interop::RenderParams> renderParams;
        std::vector<interop::float4x4> viewTransforms;
        std::vector<interop::float4x4> projTransforms;
        std::vector<interop::float4x4> viewProjTransforms;
        std::vector<interop::float4x4> modViewTransforms;
        std::vector<interop::float4x4> modProjTransforms;
        std::vector<interop::float4x4> modViewProjTransforms;
        std::vector<interop::float4x4> prevViewTransforms;
        std::vector<interop::float4x4> prevProjTransforms;
        std::vector<interop::float4x4> prevViewProjTransforms;
        std::vector<interop::float4x4> worldTransforms;
        std::vector<interop::float4x4> prevWorldTransforms;
        std::vector<interop::float4x4> invTWorldTransforms;
        std::vector<interop::float4x4> lerpWorldTransforms;
        std::vector<interop::RDPTile> rdpTiles;
        std::vector<interop::RDPTile> lerpRdpTiles;
        std::vector<interop::GPUTile> gpuTiles;
        std::vector<DrawCallTile> callTiles;
        std::vector<interop::RSPViewport> rspViewports;
        std::vector<int16_t> viewportClipRatios;
        std::vector<uint16_t> viewportOrigins;
        std::vector<interop::RSPFog> rspFog;
        std::vector<interop::RSPLight> rspLights;
        std::vector<interop::RSPLookAt> rspLookAt;
        std::vector<interop::RSPLookAt> lerpRspLookAt;
        std::vector<LoadOperation> loadOperations;
        std::vector<float> triPosFloats;
        std::vector<float> triTcFloats;
        std::vector<float> triColorFloats;
        std::vector<TransformGroup> transformGroups;
        std::vector<uint32_t> worldTransformGroups;
        std::vector<uint32_t> viewProjTransformGroups;
        std::vector<uint32_t> worldTransformSegmentedAddresses;
        std::vector<uint32_t> worldTransformPhysicalAddresses;
        std::vector<uint32_t> worldTransformVertexIndices;
        // Appended cloud vertices use existing matrices but have no native
        // transform slots. Keep their suffix out of generic native matching.
        uint32_t wr64CloudNativeVertexCount = UINT32_MAX;

        uint32_t vertexCount() const {
            return uint32_t(worldIndices.size());
        }

        uint32_t modifyCount() const {
            return uint32_t(modifyPosUints.size()) / 2;
        }

        uint32_t rawTriVertexCount() const {
            return uint32_t(triPosFloats.size()) / 4;
        }

        uint32_t worldTransformVertexCount(uint32_t i) const {
            if (wr64CloudNativeVertexCount != UINT32_MAX) {
                const uint32_t start = std::min(worldTransformVertexIndices[i], wr64CloudNativeVertexCount);
                const uint32_t end = (i + 1 < worldTransformVertexIndices.size())
                    ? std::min(worldTransformVertexIndices[i + 1], wr64CloudNativeVertexCount)
                    : wr64CloudNativeVertexCount;
                return end >= start ? end - start : 0;
            }
            if (i < (worldTransformVertexIndices.size() - 1)) {
                return worldTransformVertexIndices[i + 1] - worldTransformVertexIndices[i];
            }
            else {
                return vertexCount() - worldTransformVertexIndices[i];
            }
        }
    };

    struct DrawRanges {
        typedef std::pair<size_t, size_t> Range;

        Range posFloats;
        Range velFloats;
        Range tcFloats;
        Range tcVelFloats;
        Range normColBytes;
        Range viewProjIndices;
        Range worldIndices;
        Range fogIndices;
        Range lightIndices;
        Range lightCounts;
        Range lookAtIndices;
        Range wr64WaterFieldInfo;
        Range wr64WaterFieldPrevPosShiftX;
        Range wr64WaterFieldPrevTcShiftZ;
        Range wr64WaterFieldFaceIndices;
        Range faceIndices;
        Range modifyPosUints;
        Range rdpParams;
        Range extraParams;
        Range renderParams;
        Range viewProjTransforms;
        Range worldTransforms;
        Range rdpTiles;
        Range gpuTiles;
        Range callTiles;
        Range rspViewports;
        Range rspFog;
        Range rspLights;
        Range rspLookAt;
        Range loadOperations;
        Range triPosFloats;
        Range triTcFloats;
        Range triColorFloats;
    };

    struct DrawBuffers {
        BufferPair positionBuffer;
        BufferPair velocityBuffer;
        BufferPair texcoordBuffer;
        BufferPair texcoordVelocityBuffer;
        BufferPair normalColorBuffer;
        BufferPair viewProjIndicesBuffer;
        BufferPair worldIndicesBuffer;
        BufferPair fogIndicesBuffer;
        BufferPair lightIndicesBuffer;
        BufferPair lightCountsBuffer;
        BufferPair lookAtIndicesBuffer;
        BufferPair wr64WaterFieldInfoBuffer;
        BufferPair wr64WaterFieldPrevPosShiftXBuffer;
        BufferPair wr64WaterFieldPrevTcShiftZBuffer;
        BufferPair wr64WaterFieldFaceIndicesBuffer;
        BufferPair faceIndicesBuffer;
        BufferPair modifyPosUintsBuffer;
        BufferPair rdpParamsBuffer;
        BufferPair rspParamsBuffer;
        BufferPair extraParamsBuffer;
        BufferPair renderParamsBuffer;
        BufferPair rdpTilesBuffer;
        BufferPair gpuTilesBuffer;
        BufferPair rspViewportsBuffer;
        BufferPair rspFogBuffer;
        BufferPair rspLightsBuffer;
        BufferPair rspLookAtBuffer;
        BufferPair worldTransformsBuffer;
        BufferPair viewProjTransformsBuffer;
        BufferPair prevWorldTransformsBuffer;
        BufferPair invTWorldTransformsBuffer;
        BufferPair triPosBuffer;
        BufferPair triTcBuffer;
        BufferPair triColorBuffer;
    };

    struct ComputedBuffer {
        std::unique_ptr<RenderBuffer> buffer;
        uint64_t allocatedSize = 0;
        uint64_t computedSize = 0;
    };

    struct OutputBuffers {
        ComputedBuffer screenPosBuffer;
        ComputedBuffer genTexCoordBuffer;
        ComputedBuffer shadedColBuffer;
        ComputedBuffer worldPosBuffer;
        ComputedBuffer worldNormBuffer;
        ComputedBuffer worldVelBuffer;
        ComputedBuffer testZIndexBuffer;
    };

    struct DebuggerRenderer {
        bool framebufferDepth;
        int32_t framebufferIndex;
        uint32_t framebufferAddress;
        int32_t globalDrawCallIndex;
        float interpolationWeight;
    };

    struct DebuggerCamera {
        bool enabled;
        uint32_t sceneIndex;
        hlslpp::float4x4 viewMatrix;
        hlslpp::float4x4 invViewMatrix;
        hlslpp::float4x4 projMatrix;
        float nearPlane;
        float farPlane;
        float fov;
    };

    struct SpriteCommand {
        uint32_t fbPairIndex;
        uint32_t projIndex;
        uint32_t callIndex;
        uint32_t callCount;
        uint64_t replacementHash;
    };

    struct Workload {
        uint64_t submissionFrame;
        bool wr64VerticalSplit = false;
        bool wr64SeparateWindows = false;
        // USA course/player/settings snapshot taken before queue publication.
        uint32_t wr64RtCourse = UINT32_MAX;
        Wr64DolphinSunEdgeScope wr64DolphinSunEdge = Wr64DolphinSunEdgeScope::None;
        bool wr64RtReflectionScope = false;
        bool wr64RtObjectReflectionScope = false;
        bool wr64RasterSkyScope = false;
        bool wr64RasterShadowScope = false;
        // Immutable producer snapshot shared by both native race views.
        uint32_t wr64RasterShadowDistanceMode = 0;
        bool wr64RasterReflectionScope = false;
        float wr64RasterReflectionPlaneY = 0.0f;
        bool wr64RasterReflectionPlaneValid = false;
        // Native race identity, independent of selected water effects or assets.
        bool wr64SplitWaterRoundnessScope = false;
        Wr64WaveDistanceSnapshot wr64WaveDistanceSnapshot;
        std::array<Wr64WaveDistanceSnapshot, 2> wr64WaveDistanceSnapshots;
        // Scoped producer-thread snapshot; render workers never read the UI
        // setting or mutable game memory to decide this workload's extent.
        uint32_t wr64FarWaterDistanceMode = 0;
        std::array<uint32_t, 2> wr64FarWaterDistanceViewModes{};
        std::array<uint32_t, 2> wr64FarWaterDistanceCameras{};
        std::array<bool, 2> wr64FarWaterDistanceViewScope{};
        bool wr64RtTwoPlayerScope = false;
        bool wr64RtMenuReflectionScope = false;
        bool wr64RtEndingScope = false;
        bool wr64RtSkyReflectionScope = false;
        // Native cloud alpha = clamp(distanceXZ * x + y, 0, 255).
        // z marks a validated producer snapshot; w is reserved.
        interop::float4 wr64RtSkyCloudParams = { 0.0f, 0.0f, 0.0f, 0.0f };
        Wr64RTCelestialSnapshot wr64RtCelestial;
        bool wr64RtShadowScope = false;
        bool wr64RtAoScope = false;
        Wr64RTShadowLight wr64RtShadowLight;
        uint8_t wr64PauseOwner = 0;
        uint32_t wr64PauseFirstCall = UINT32_MAX;
        uint32_t wr64PauseLastCall = 0;
        uint8_t wr64PauseDrawOwner = 0;
        Wr64LapScope wr64LapScope;
        DrawData drawData;
        DrawRanges drawRanges;
        DrawBuffers drawBuffers;
        OutputBuffers outputBuffers;
        std::vector<FramebufferPair> fbPairs;
        std::vector<CommandWarning> commandWarnings;
        std::vector<SpriteCommand> spriteCommands;
        std::vector<interop::PointLight> pointLights;
        uint32_t fbPairCount;
        uint32_t fbPairSubmitted;
        uint32_t gameCallCount;
        FramebufferChangePool fbChangePool;
        FramebufferStorage fbStorage;
        uint32_t viOriginalRate;
        hlslpp::uint2 viFbSize = {};
        DebuggerRenderer debuggerRenderer;
        DebuggerCamera debuggerCamera;
        std::multimap<uint32_t, uint32_t> transformIdMap;
        std::multimap<uint32_t, uint32_t> physicalAddressTransformMap;
        std::vector<uint32_t> transformIgnoredIds;

        // WR64 celestial rect interpolation (rt64_wr64_celestial_identity.h).
        // prevRects: filled ONCE PER TICK by the pairing pass in
        // GameFrame::match - each entry is a claimed sun rect paired with its
        // previous-frame self. lerpRects: rebuilt PER OUTPUT FRAME by the
        // transform processor from prevRects and the frame weight, then read
        // by the renderer in place of callDesc.rect for exactly those calls.
        // Same lifecycle as lerpWorldTransforms; kept on the Workload rather
        // than DrawData because DrawData's vectors mirror GPU uploads and
        // these never upload.
        struct Wr64CelestialRectPair {
            uint64_t key;
            FixedRect prevRect;
            FixedRect curRect;
        };
        std::vector<Wr64CelestialRectPair> wr64CelestialPrevRects;
        std::unordered_map<uint64_t, FixedRect> wr64CelestialLerpRects;
        std::vector<Wr64DolphinSunRectPair> wr64DolphinSunPairs;
        std::unordered_map<uint64_t, Wr64DolphinSunRect> wr64DolphinSunOutputRects;
        // The paired rects' TILES, current tile index -> previous tile index,
        // handed by GameFrame::match to the per-output-frame tile blend
        // (TileProcessor) - rect draws never reach the transform matcher, so
        // nothing else ever maps their tiles. Measured 2026-08-05: the DP
        // text does NOT scroll through the tile (its scroll is baked into
        // per-vertex texture coordinates and is folded into the rect blend
        // by the pairing pass instead); today these pairs blend values that
        // are already equal, and stay as the correct guard for any claimed
        // rect whose game does scroll the tile window.
        struct Wr64CelestialTilePair {
            uint32_t curTileIndex;
            uint32_t prevTileIndex;
        };
        std::vector<Wr64CelestialTilePair> wr64CelestialTilePairs;
        // The stunt rings' tiles, paired by the ring's own position identity
        // (rt64_wr64_stunt_ring_identity.h) instead of scene-based call
        // matching - registered with the tile blend by the same loop that
        // registers the celestial pairs above.
        std::vector<Wr64CelestialTilePair> wr64StuntRingTilePairs;


        uint64_t workloadId = 0;
        uint64_t presentId = 0;
        bool paused = false;

        struct {
            uint32_t testZIndexCount = 0;
            float ditherNoiseStrength = 1.0f;
            hlslpp::float2 texcoordWrapPoint = {};
        } extended;

        void reset();
        void resetDrawData();
        void resetDrawDataRanges();
        void resetRSPOutputBuffers();
        void resetWorldOutputBuffers();
        void updateDrawDataRanges();
        void uploadDrawData(RenderWorker *worker, BufferUploader *bufferUploader);
        void updateOutputBuffers(RenderWorker *worker);
        void nextDrawDataRanges();
        void begin(uint64_t submissionFrame);
        bool addFramebufferPair(uint32_t colorAddress, uint8_t colorFmt, uint8_t colorSiz, uint16_t colorWidth, uint32_t depthAddress);
        int currentFramebufferPairIndex() const;
    };
};
