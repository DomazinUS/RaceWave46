//
// RT64
//

#pragma once
#include "shared/rt64_wr64_rt_celestial.h"

#include <stdint.h>
#include <cstdio>

#include "common/rt64_emulator_configuration.h"
#include "common/rt64_user_configuration.h"
#include "common/rt64_wr64_water_adjacency.h"
#include "common/rt64_wr64_rt_actor_shadow.h"
#include "common/rt64_wr64_rt_fence_proxy_cache.h"
#include "hle/rt64_framebuffer_manager.h"
#include "hle/rt64_workload.h"
#include "preset/rt64_preset_scene.h"
#include "shared/rt64_frame_params.h"
#include "shared/rt64_gpu_tile.h"
#include "shared/rt64_render_indices.h"
#include "shared/rt64_render_params.h"

#include "rt64_buffer_uploader.h"
#include "rt64_descriptor_sets.h"
#include "rt64_framebuffer_renderer_call.h"
#include "rt64_raster_shader_cache.h"
#include "rt64_render_target.h"
#include "rt64_rsp_processor.h"
#include "rt64_vertex_processor.h"
#include "rt64_wr64_rt_scene.h"
#include "rt64_wr64_rt_water.h"
#include "rt64_wr64_raster_sky.h"
#include "rt64_wr64_raster_shadow.h"
#include "rt64_wr64_raster_reflection.h"
#include "rt64_wr64_motion_blur.h"

#if RT_ENABLED
#   include "rt64_raytracing_resources.h"
#   include "rt64_raytracing_shader_cache.h"
#endif

namespace RT64 {
    struct DynamicTextureView {
        const RenderTexture *texture = nullptr;
        uint32_t dstIndex = 0;
        const RenderTextureView *textureView = nullptr;
    };

    struct RasterScene {
        std::vector<uint32_t> instanceIndices;

        RasterScene();
    };

    struct RenderTargetDrawCall {
        typedef std::pair<uint32_t, bool> SceneIndexPair;

        RenderFramebufferStorage *fbStorage = nullptr;
        std::vector<RasterScene> rasterScenes;
        std::vector<SceneIndexPair> sceneIndices;
#   if RT_ENABLED
        std::vector<RaytracingScene> rtScenes;
#   endif
    };

    struct RSPSmoothNormalGenerationCB {
        uint32_t indexStart;
        uint32_t indexCount;
    };

    struct FramebufferRenderer {
        std::vector<uint32_t> textureCacheVersions;
        std::vector<Texture *> textureCacheTextures;
        std::vector<Texture *> textureCacheTextureReplacements;
        std::vector<uint32_t> textureCacheFreeSpaces;
        uint32_t textureCacheSize = 0;
        uint32_t textureCacheGlobalVersion = 0;
        bool textureCacheReplacementMapEnabled = false;
        std::vector<InstanceDrawCall> instanceDrawCallVector;
        std::vector<RenderPipelineProgram> hitGroupVector;
        std::vector<interop::RenderIndices> renderIndicesVector;
        std::vector<DynamicTextureView> dynamicTextureViewVector;
        std::vector<RenderTextureBarrier> dynamicTextureBarrierVector;
        std::unique_ptr<BufferUploader> shaderUploader;
        std::vector<RSPSmoothNormalGenerationCB> rspSmoothNormalVector;
        std::array<RenderInputSlot, 3> vertexInputSlots;
        std::array<RenderVertexBufferView, 3> indexedVertexViews;
        std::array<RenderVertexBufferView, 3> rawVertexViews;
        RenderIndexBufferView indexBufferView;
        RenderBuffer *testZIndexBuffer = nullptr;
        RenderIndexBufferView testZIndexBufferView;
        BufferPair renderIndicesBuffer;
        BufferPair interleavedRastersBuffer;
        uint32_t interleavedRastersCount = 0;
        BufferPair frameParamsBuffer;
        RenderPipelineLayout *rendererPipelineLayout = nullptr;
        RenderPipeline *postBlendDitherNoiseAddPipeline = nullptr;
        RenderPipeline *postBlendDitherNoiseSubPipeline = nullptr;
        RenderPipeline *postBlendDitherNoiseSubNegativePipeline = nullptr;
        std::unique_ptr<FramebufferRendererDescriptorCommonSet> descCommonSet;
        std::unique_ptr<FramebufferRendererDescriptorTextureSet> descTextureSet;
        std::unique_ptr<RenderTexture> dummyColorTarget;
        std::unique_ptr<RenderTexture> dummyDepthTarget;
        std::unique_ptr<RenderTextureView> dummyColorTargetView;
        std::unique_ptr<RenderTextureView> dummyDepthTargetView;
        bool dummyColorTargetTransitioned = false;
        bool dummyDepthTargetTransitioned = false;
        std::vector<uint32_t> descriptorTextureVersions;
        uint32_t descriptorTextureGlobalVersion = 0;
        bool descriptorTextureReplacementMapEnabled = false;
        std::unique_ptr<RSPSmoothNormalDescriptorSet> smoothDescSet;
        std::unique_ptr<RSPVertexTestZDescriptorSet> vertexTestZSet;
        interop::FrameParams frameParams;
        const ShaderLibrary *shaderLibrary = nullptr;
        bool wr64RTSupported = false;
        bool wr64RasterSkySupported = false;
        float wr64RasterSkyStrength = 1.0f;
        RenderShaderFormat wr64RTShaderFormat = RenderShaderFormat::DXIL;
        static constexpr uint64_t Wr64SkyCaptureBytes = 16 + 512 * 128;
        static constexpr uint64_t Wr64SkyCaptureVertexBytes = 2 * 18 * 40;
        struct Wr64SkyCaptureDiagnostic {
            const char *reason = "missing-native-draw";
            uint32_t draw = UINT32_MAX, view = UINT32_MAX;
            float cameraDifference = -1.0f;
            int coefficientValid = -1, currentWorldIdentity = -1, lerpWorldIdentity = -1;
        };
        struct Wr64SkyCaptureLayer {
            std::array<uint32_t, 18> vertices = {};
            uint32_t count = 0;
            std::string material;
        };
        struct Wr64NativeShadowDraw {
            uint32_t drawIndex;
            uint32_t racerMask;
        };
        struct Wr64RTParams {
            interop::float4 camera;
            uint32_t debugView = 0;
            float strength = 1.0f;
            uint32_t enabled = 0;
            uint32_t smoothNormals = 0;
            // Current presentation's native sky fan, separate from the opaque AS.
            interop::uint4 sky = { 0, 0, 0, 0 }; // first index, draw index, triangle count, enabled
            interop::float4 skyCamera = { 0.0f, 0.0f, 0.0f, 0.0f };
            interop::float4 skyCloudParams = { 0.0f, 0.0f, 0.0f, 0.0f };
            interop::uint4 skyBackdrop = { 0, 0, 0, 0 };
            interop::float4 skyBackdropCamera = { 0.0f, 0.0f, 0.0f, 0.0f };
            interop::float4 celestialProjection[3] = {};
            interop::uint4 celestialInfo = { 0, 0, 0, 0 };
            interop::Wr64RTCelestialRecord celestialBodies[WR64_RT_CELESTIAL_MAX] = {};
            interop::uint4 celestialAlpha[WR64_RT_CELESTIAL_ALPHA_VECTORS] = {};
            interop::float4 shadowLight = {};
            interop::float4 shadowOptions = {};
            interop::uint4 sceneOptions = {}; // Beam count, actor count, actor racer mask, valid bounds mask.
            interop::float4 actorShadowBoundsMin[4] = {};
            interop::float4 actorShadowBoundsMax[4] = {};
            interop::float4 aoOptions = {};
            interop::float4 qualityOptions = {}; // Reflection ray distance, actor shadow samples, reserved.
        };
        static_assert(sizeof(Wr64RTParams) == 3728, "WR64 reflection constants must match the water shader");

        // One owner per native race view. GPU allocations and descriptor sets
        // survive together until the workload queue's existing completion fence.
        struct Wr64RTView {
            uint32_t projection = UINT32_MAX;
            uint32_t nativeRaceView = 0;
            std::unique_ptr<FramebufferRendererDescriptorCommonSet> descriptor;
            bool prepared = false;
            bool scopeSeen = false;
            bool endingWorldOnly = false;
            bool skyScopeSeen = false;
            bool rasterSky = false;
            bool traceReflections = false;
            bool raySkyOnly = false;
            bool rasterShadows = false;
            bool rasterReflections = false;
            bool reflectionCaptureRecorded = false;
            bool reflectionPlaneValid = false;
            float reflectionPlaneY = 0.0f;
            float reflectionViewRows[4][4] = {};
            float reflectionViewportScale[3] = {};
            float reflectionViewportTranslate[3] = {};
            float reflectionFramebufferSize[2] = {};
            Wr64RasterReflectionTarget rasterReflectionTarget;
            Wr64RasterReflectionParams rasterReflectionParams{};
            std::unique_ptr<RenderBuffer> rasterReflectionParamsBuffer;
            std::vector<Wr64RTSceneGeometry> rasterReflectors;
            bool shadowMapRecorded = false;
            uint32_t rasterShadowRacers = 0;
            Wr64RasterShadowTarget rasterShadowTarget;
            Wr64RasterShadowParams rasterShadowParams{};
            std::unique_ptr<RenderBuffer> rasterShadowParamsBuffer;
            std::vector<Wr64RTSceneGeometry> rasterShadowCasters;
            Wr64RasterSkyTarget rasterSkyTarget;
            uint32_t framebuffer = UINT32_MAX;
            uint64_t workload = 0;
            uint32_t vertexCount = 0, indexCount = 0;
            uint32_t skyMatches = 0, skyCandidates = 0;
            uint32_t backdropMatches = 0, backdropCandidates = 0;

            std::array<Wr64SkyCaptureDiagnostic, 2> skyCaptureDiagnostic = {};
            std::string previousSkyState;
            std::unique_ptr<RenderBuffer> skyCaptureBuffer, skyCaptureZero, skyCaptureReadback;
            std::FILE *skyCaptureFile = nullptr;
            bool skyCaptureRequested = false, skyCaptureArmed = false, skyCaptureCopied = false;
            bool skyCaptureFailed = false;
            uint64_t skyCaptureStartMs = 0, skyCaptureLastMs = 0, skyCapturePresent = 0;
            uint64_t skyCaptureNativePresent = 0, skyCaptureSubmission = 0, skyCaptureElapsedMs = 0;
            const DrawData *skyCaptureDrawData = nullptr;
            RenderBuffer *skyCapturePositions = nullptr, *skyCaptureTexcoords = nullptr,
                *skyCaptureColors = nullptr;

            std::array<Wr64SkyCaptureLayer, 2> skyCaptureLayers = {};
            std::vector<Wr64RTSceneGeometry> skyCaptureGeometry;
            Wr64RTScene scene;
            std::vector<Wr64RTSceneGeometry> geometry;
            std::vector<Wr64RTFenceProxy> fenceProxies;
            std::vector<uint32_t> waterDraws;
            std::vector<const RenderPipeline *> nativeWaterPipelines;
            std::vector<uint32_t> shoreDraws;
            std::vector<uint32_t> aoOnlyDraws;
            std::vector<const RenderPipeline *> nativeShorePipelines;
            uint32_t arrowShadowExclusions = 0;
            uint32_t letterShadowExclusions = 0;
            uint32_t shoreSelected = 0;
            uint32_t aoOnlySelected = 0;

            std::vector<Wr64NativeShadowDraw> nativeShadowDraws;
            uint32_t racerShadowCasters = 0;
            std::array<Wr64RTActorShadowBounds, 4> actorBounds;
            bool shadowWaterSelected = false;
            std::vector<uint32_t> waterIndices;
            Wr64WaterAdjacency waterAdjacency;
            std::unique_ptr<RenderBuffer> waterAdjacencyBuffer;
            uint64_t waterAdjacencyCapacity = 0;
            std::unique_ptr<RenderBuffer> paramsBuffer;
            Wr64RTParams params;

        };
        std::array<Wr64RTView, 2> wr64RTViews;
        // Immutable CPU expansions may be reused by both cameras and later
        // presentations. Current draw eligibility is checked before every hit.
        Wr64RTFenceExpansionCache wr64RTFenceExpansionCache;
        // 0: native/unassigned, 1: first view, 2: second view.
        std::vector<uint8_t> wr64RTDrawViews;
        Wr64RTWaterPipelines wr64RTWaterPipelines;
        Wr64RasterSkyPipelines wr64RasterSkyPipelines;
        Wr64RasterShadowPipelines wr64RasterShadowPipelines;
        Wr64RasterReflectionPipelines wr64RasterReflectionPipelines;
        Wr64RTWorldShadowPipelines wr64RTWorldShadowPipelines;
        Wr64MotionBlur wr64MotionBlur;
        struct Wr64MotionDrawParams {
            interop::float4x4 previousViewProjection;
            interop::float4 viewportScale;
            interop::float4 viewportTranslate;
        };
        static_assert(sizeof(Wr64MotionDrawParams) == 96, "Motion draw SRV stride");
        std::vector<Wr64MotionDrawParams> wr64MotionDrawParams;
        std::vector<uint32_t> wr64MotionActors;
        std::unique_ptr<RenderBuffer> wr64MotionDrawBuffer;
        uint64_t wr64MotionDrawCapacity = 0;
        uint32_t wr64MotionBoundary = UINT32_MAX;
        bool wr64MotionOrderRejected = false;
        bool wr64MotionPrepared = false;
        float wr64MotionTimeScale = 1.0f;
        float wr64MotionShutter = 0.0f;
        struct Wr64MotionDiagnostic {
            bool enabled = false, executed = false, menu = false, paused = false;
            const char *reason = "disabled";
            uint64_t workload = 0, present = 0;
            uint32_t course = UINT32_MAX, view = UINT32_MAX;
            uint32_t maskDraws = 0, missingPipelines = 0, emptyScissors = 0;
        } wr64MotionDiagnostic;
        const char *wr64MotionPreviousReason = nullptr;
        uint64_t wr64MotionDiagnosticFrames = 0;
        uint64_t wr64MotionNoExposureFrames = 0;
        uint32_t wr64MotionPreviousState = UINT32_MAX;

#   if RT_ENABLED
        const RenderTexture *blueNoiseTexture = nullptr;
        const RaytracingState *rtState = nullptr;
        const RenderPipelineLayout *rtPipelineLayout = nullptr;
        std::unique_ptr<RaytracingResources> rtResources;
        bool rtSupport = false;
#   endif

        struct Framebuffer {
            std::unique_ptr<RenderBuffer> paramsBuffer;
            std::unique_ptr<FramebufferRendererDescriptorFramebufferSet> descRealFbSet;
            std::unique_ptr<FramebufferRendererDescriptorFramebufferSet> descDummyFbSet;
            std::set<RenderTarget *> transitionRenderTargetSet;
            RenderTargetDrawCall renderTargetDrawCall;
            RenderViewport viewport;
        };

        std::vector<Framebuffer> framebufferVector;
        std::vector<BufferUploader *> pendingUploaders;
        uint32_t framebufferCount = 0;

        struct DrawParams {
            RenderWorker *worker;
            RenderFramebufferStorage *fbStorage;
            const Workload *curWorkload;
            uint32_t fbPairIndex;
            uint32_t fbWidth;
            uint32_t fbHeight;
            uint32_t targetWidth;
            uint32_t targetHeight;
            RasterShaderCache *rasterShaderCache;
            hlslpp::float2 resolutionScale;
            float aspectRatioSource;
            float aspectRatioTarget;
            float extAspectPercentage;
            float horizontalMisalignment;
            PresetScene presetScene;
            bool rtEnabled;
            bool wr64RtPresentation = false;
            float wr64RasterReflectionPlaneY = 0.0f;
            bool wr64RasterReflectionPlaneValid = false;
            uint64_t submissionFrame;
            float deltaTimeMs;
            float motionTimeScale = 1.0f;
            bool ubershadersOnly;
            bool postBlendNoise;
            bool postBlendNoiseNegative;
            uint32_t maxGameCall;
        };

        FramebufferRenderer(RenderWorker *worker, bool rtSupport, UserConfiguration::GraphicsAPI graphicsAPI, const ShaderLibrary *shaderLibrary);
        ~FramebufferRenderer();
        // Caller has drained render/present queues before replacing their layout.
        void resetWr64RTPipelines();
        // Boot only: no game workload has been submitted while the native
        // idle thread holds its logo. Called from the graphics API thread.
        Wr64RTPrewarmStatus prewarmWr64RTPipelines(RenderDevice *device,
            const RenderPipelineLayout *layout, const RenderMultisampling &multisampling,
            bool nativeSky, bool worldShadows, bool motionBlur,
            bool objectReflections = true, bool cachedSky = false, bool rasterShadows = false,
            bool rasterReflections = false);
        void resetFramebuffers(RenderWorker *worker, bool ubershadersVisible, float ditherNoiseStrength, const RenderMultisampling &multisampling);
        void updateTextureCache(TextureCache *textureCache);
        void createGPUTiles(const DrawCallTile *callTiles, uint32_t callTileCount, interop::GPUTile *dstGPUTiles, const FramebufferManager *fbManager, TextureCache *textureCache, uint64_t submissionFrame, uint32_t diagnosticPart = 0);
        uint32_t getDestinationIndex();
        uint32_t getTextureIndex(RenderTarget *renderTarget);
        uint32_t getTextureIndex(const FramebufferManager::TileCopy &tileCopy);
        void updateMultisampling();
        void updateShaderDescriptorSet(RenderWorker *worker, const DrawBuffers *drawBuffers, const OutputBuffers *outputBuffers, bool raytracingEnabled);
        void updateRSPSmoothNormalSet(RenderWorker *worker, const DrawBuffers *drawBuffers, const OutputBuffers *outputBuffers);
        void updateRSPVertexTestZSet(RenderWorker *worker, const DrawBuffers *drawBuffers, const OutputBuffers *outputBuffers);
        void updateShaderViews(RenderWorker *worker, const DrawBuffers *drawBuffers, const OutputBuffers *outputBuffers, bool raytracingEnabled);
        void submitRSPSmoothNormalCompute(RenderWorker *worker, const OutputBuffers *outputBuffers);
        bool submitDepthAccess(RenderWorker *worker, RenderFramebufferStorage *fbStorage, bool readOnly, bool &depthState);
        void submitRasterScene(RenderWorker *worker, const Framebuffer &framebuffer, RenderFramebufferStorage *fbStorage, const RasterScene &rasterScene, bool &depthState);
        void addFramebuffer(const DrawParams &p);
        void endFramebuffers(RenderWorker *worker, const DrawBuffers *drawBuffers, const OutputBuffers *outputBuffers, bool rtEnabled);
        void recordSetup(RenderWorker *worker, std::vector<BufferUploader *> bufferUploaders, RSPProcessor *rspProcessor, VertexProcessor *vertexProcessor, const OutputBuffers *outputBuffers, const DrawBuffers *drawBuffers, bool rtEnabled);
        void recordFramebuffer(RenderWorker *worker, uint32_t framebufferIndex);
        // Both callbacks run on the workload graphics thread. Readback consumes
        // only after its existing GPU wait; these methods never submit or wait.
        void recordWr64SkyCaptureReadback(RenderWorker *worker);
        void recordWr64SkyCaptureReadback(Wr64RTView *rt, RenderWorker *worker);
        void consumeWr64SkyCaptureReadback();
        void consumeWr64SkyCaptureReadback(Wr64RTView *rt);
        void armWr64SkyCapture(Wr64RTView *rt, RenderWorker *worker, const OutputBuffers *outputBuffers);
        void waitForUploaders();
        void advanceFrame(bool rtEnabled);

#   if RT_ENABLED
        void resetRaytracing(RaytracingShaderCache *rtShaderCache, const RenderTexture *blueNoiseTexture);
        void updateRaytracingScene(RenderWorker *worker, const RaytracingScene &rtScene);
        void submitRaytracingScene(RenderWorker *worker, RenderTarget *colorTarget, const RaytracingScene &rtScene);
        void setRaytracingConfig(const RaytracingConfiguration &rtConfig, bool resolutionChanged);
#   endif
    };
};
