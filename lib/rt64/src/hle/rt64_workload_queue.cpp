//
// RT64
//

#include "../../../../include/wr64_diagnostic_policy.h"

#include "rt64_workload_queue.h"
#include "common/rt64_wr64_separate_windows.h"

#include <cstdio>
#include <cstdlib>

#include "common/rt64_thread.h"
#include "common/rt64_wr64_stall_probe.h"
#include "common/rt64_wr64_camcut_trace.h"
#include "common/rt64_wr64_cadence_meter.h"
#include "common/rt64_wr64_backpressure_meter.h"
#include "common/rt64_wr64_ultrawide.h"
#include "common/rt64_wr64_sun_output_trace.h"
#include "common/rt64_wr64_motion_timing.h"
#include "common/rt64_wr64_water_roundness.h"
#include "rt64_game_frame.h"
#include "common/rt64_wr64_frame_pacing_diagnostic.h"

#include "rt64_present_queue.h"
#include "rt64_wr64_cadence_trace.h"

#define ENABLE_HIGH_RESOLUTION_RENDERER 1

namespace RT64 {
    static FILE *wr64SprayPresentTraceFile() {
        if (!WR64_DIAGNOSTIC_ENABLED) return nullptr;
        static FILE *traceFile = []() -> FILE * {
            const char *enabled = std::getenv("WR64_SPRAY_PRESENT_TRACE");
            if ((enabled == nullptr) || (enabled[0] == '\0') || (enabled[0] == '0')) {
                return nullptr;
            }

            const char *path = std::getenv("WR64_SPRAY_PRESENT_TRACE_PATH");
            if ((path == nullptr) || (path[0] == '\0')) {
                path = "wr64-spray-present-trace.csv";
            }

            FILE *file = nullptr;
#ifdef _WIN32
            fopen_s(&file, path, "w");
#else
            file = std::fopen(path, "w");
#endif
            if (file != nullptr) {
                std::fprintf(file,
                    "workload_id,present_id,native_rate,target_rate,frame_index,display_frames,"
                    "generate_interpolated,logical_ticks,display_ticks,prev_weight,cur_weight\n");
                std::fflush(file);
            }

            return file;
        }();

        return traceFile;
    }

    static void wr64WriteSprayPresentTrace(uint64_t workloadId, uint64_t presentId,
        int32_t nativeRate, int32_t targetRate, uint32_t frameIndex, uint32_t displayFrames,
        bool generateInterpolated, int64_t logicalTicks, int64_t displayTicks,
        float prevWeight, float curWeight)
    {
        FILE *file = wr64SprayPresentTraceFile();
        if (file == nullptr) {
            return;
        }

        std::fprintf(file, "%llu,%llu,%d,%d,%u,%u,%d,%lld,%lld,%.9g,%.9g\n",
            static_cast<unsigned long long>(workloadId),
            static_cast<unsigned long long>(presentId),
            nativeRate, targetRate, frameIndex, displayFrames,
            generateInterpolated ? 1 : 0,
            static_cast<long long>(logicalTicks),
            static_cast<long long>(displayTicks),
            prevWeight, curWeight);
        std::fflush(file);
    }

    // WorkloadQueue

    WorkloadQueue::WorkloadQueue() {
        reset();
    }

    WorkloadQueue::~WorkloadQueue() {
        threadsRunning = false;
        cursorCondition.notify_all();
        idleCondition.notify_all();

        if (renderThread != nullptr) {
            renderThread->join();
            delete renderThread;
        }

        if (idleThread != nullptr) {
            idleThread->join();
            delete idleThread;
        }

        workloadIdCondition.notify_all();
    }

    void WorkloadQueue::reset() {
        for (Workload &w : workloads) {
            w.reset();
        }

        threadCursor = 0;
        writeCursor = 0;
        barrierCursor = int(workloads.size()) - 1;
        workloadId = 0;
        lastPresentId = 0;
    }

    void WorkloadQueue::advanceToNextWorkload() {
        int nextWriteCursor = (writeCursor + 1) % workloads.size();

        // Stall the thread until the barrier is lifted if we're trying to write on a workload being used by the GPU.
        bool waitForBarrier;
        do {
            const std::scoped_lock lock(cursorMutex);
            waitForBarrier = (nextWriteCursor == barrierCursor);
        } while (waitForBarrier);

        // Modify the cursor and notify anything waiting on the queue.
        {
            const std::scoped_lock lock(cursorMutex);
            writeCursor = nextWriteCursor;
        }

        cursorCondition.notify_all();
    }

    void WorkloadQueue::repeatLastWorkload() {
        {
            const std::scoped_lock lock(cursorMutex);
            threadCursor = previousWriteCursor();
        }

        cursorCondition.notify_all();
    }

    uint32_t WorkloadQueue::previousWriteCursor() const {
        if (writeCursor > 0) {
            return writeCursor - 1;
        }
        else {
            return uint32_t(workloads.size()) - 1;
        }
    }

    void WorkloadQueue::waitForIdle() {
        std::unique_lock<std::mutex> threadLock(threadMutex);
    }

    void WorkloadQueue::waitForWorkloadId(uint64_t waitId) {
        std::unique_lock<std::mutex> workloadLock(workloadIdMutex);
        workloadIdCondition.wait(workloadLock, [&]() {
            return (waitId <= workloadId) || !threadsRunning;
        });
    }

    void WorkloadQueue::setup(const External &ext) {
        this->ext = ext;

        rspProcessor = std::make_unique<RSPProcessor>(ext.device);
        vertexProcessor = std::make_unique<VertexProcessor>(ext.device);
        framebufferRenderer = std::make_unique<FramebufferRenderer>(ext.workloadGraphicsWorker, true, ext.createdGraphicsAPI, ext.shaderLibrary);
        renderFramebufferManager = std::make_unique<RenderFramebufferManager>(ext.device);
        queryPool = ext.device->createQueryPool(2);

        projectionProcessor.setup(ext.workloadGraphicsWorker);
        transformProcessor.setup(ext.workloadGraphicsWorker);
        tileProcessor.setup(ext.workloadGraphicsWorker);
        lookAtProcessor.setup(ext.workloadGraphicsWorker);

        threadsRunning = true;
        renderThread = new std::thread(&WorkloadQueue::renderThreadLoop, this);
        idleThread = new std::thread(&WorkloadQueue::idleThreadLoop, this);
    }

    void WorkloadQueue::updateMultisampling() {
        renderFramebufferManager->destroyAll();
        dummyDepthTarget.reset();
        framebufferRenderer->updateMultisampling();
    }

    void WorkloadQueue::threadConfigurationUpdate(hlslpp::uint2 viFbSize, WorkloadConfiguration &workloadConfig, bool separateWindows) {
        const std::scoped_lock lock(ext.sharedResources->configurationMutex);
        const bool sizeChanged = ext.sharedResources->swapChainSizeChanged ||
            workloadConfig.wr64SeparateWindows != separateWindows;
        workloadConfig.wr64SeparateWindows = separateWindows;
        ext.sharedResources->swapChainSizeChanged = false;
        
        // Retrieve the reference height to be used for determining the resolution scale. Impose a minimum in case
        // the game is using too small of a portion of the VI.
        const uint32_t MinimumReferenceHeight = 60;
        const uint32_t referenceHeight = (viFbSize[1] > 0) ? std::max(viFbSize[1], MinimumReferenceHeight) : 240;

        // Compute the aspect ratio to be used for the frame.
        workloadConfig.aspectRatioSource = (viFbSize[1] > 0) ? float(viFbSize[0]) / float(viFbSize[1]) : (4.0f / 3.0f);

        const auto ratioMode = ext.sharedResources->userConfig.aspectRatio;
        switch (ratioMode) {
        case UserConfiguration::AspectRatio::Expand:
            if ((ext.sharedResources->swapChainWidth > 0) && (ext.sharedResources->swapChainHeight > 0)) {
                const float derivedRatioTarget = float(ext.sharedResources->swapChainWidth) / float(ext.sharedResources->swapChainHeight);
                workloadConfig.aspectRatioTarget = std::max(derivedRatioTarget, workloadConfig.aspectRatioSource);
            }
            else {
                workloadConfig.aspectRatioTarget = workloadConfig.aspectRatioSource;
            }

            break;
        case UserConfiguration::AspectRatio::Manual:
            workloadConfig.aspectRatioTarget = float(ext.sharedResources->userConfig.aspectTarget);
            break;
        case UserConfiguration::AspectRatio::Original:
        default:
            workloadConfig.aspectRatioTarget = workloadConfig.aspectRatioSource;
            break;
        }

        // Compute the extended GBI aspect ratio percentage to be used for the frame.
        const auto extRatioMode = ext.sharedResources->userConfig.extAspectRatio;
        switch (extRatioMode) {
        case UserConfiguration::AspectRatio::Expand:
            workloadConfig.extAspectPercentage = 1.0f;
            break;
        case UserConfiguration::AspectRatio::Manual:
            if ((ext.sharedResources->swapChainWidth > 0) && (ext.sharedResources->swapChainHeight > 0)) {
                const float reducedExtTarget = float(ext.sharedResources->userConfig.extAspectTarget) - workloadConfig.aspectRatioSource;
                const float reducedDisplayTarget = workloadConfig.aspectRatioTarget - workloadConfig.aspectRatioSource;
                if ((reducedExtTarget > 0.0f) && (reducedDisplayTarget > 0.0f)) {
                    workloadConfig.extAspectPercentage = std::clamp((reducedExtTarget / reducedDisplayTarget), 0.0f, 1.0f);
                }
                else {
                    workloadConfig.extAspectPercentage = 0.0f;
                }
            }
            else {
                workloadConfig.extAspectPercentage = 0.0f;
            }

            break;
        case UserConfiguration::AspectRatio::Original:
        default:
            workloadConfig.extAspectPercentage = 0.0f;
            break;
        }

        // Compute the resolution scaling to be used for the frame.
        float resolutionMultiplier;
        const auto resolutionMode = ext.sharedResources->userConfig.resolution;
        switch (resolutionMode) {
        case UserConfiguration::Resolution::WindowIntegerScale:
            if (ext.sharedResources->swapChainHeight > 0) {
                resolutionMultiplier = std::max(float((ext.sharedResources->swapChainHeight + referenceHeight - 1) / referenceHeight), 1.0f);
            }
            else {
                resolutionMultiplier = 1.0f;
            }

            break;
        case UserConfiguration::Resolution::Manual:
            resolutionMultiplier = float(ext.sharedResources->userConfig.resolutionMultiplier);
            break;
        case UserConfiguration::Resolution::Original:
        default:
            resolutionMultiplier = 1.0f;
            break;
        }

        uint32_t msaaSampleCount = ext.sharedResources->userConfig.msaaSampleCount();

        // The IPS-authored game already has a 424-wide, 16:9 presentation pipeline.
        // Applying aspect expansion again squeezes menu projection geometry relative
        // to full-width rectangles. Preserve that baseline and expand only the width
        // beyond 16:9; final presentation fills the small native aspect difference.
        const float wr64DisplayAspect = (ext.sharedResources->swapChainHeight > 0)
            ? float(ext.sharedResources->swapChainWidth) / float(ext.sharedResources->swapChainHeight)
            : Wr64BaselineAspect;
        const float wr64SceneAspect = separateWindows ? Wr64SeparateWindowsAspect :
            wr64UsaSceneAspect(wr64DisplayAspect, ratioMode != UserConfiguration::AspectRatio::Original);
        const float wr64ExtraAspect = wr64UltrawideExpansion(wr64SceneAspect);
        wr64UltrawidePublishAspect(wr64SceneAspect);
        workloadConfig.aspectRatioTarget = workloadConfig.aspectRatioSource * wr64ExtraAspect;
        // Recompute against the corrected IPS baseline, rather than treating
        // 424/240 as a narrow original image that still needs 16:9 expansion.
        switch (extRatioMode) {
        case UserConfiguration::AspectRatio::Expand:
            workloadConfig.extAspectPercentage = 1.0f;
            break;
        case UserConfiguration::AspectRatio::Manual:
            workloadConfig.extAspectPercentage = wr64UsaHudExtensionPercentage(
                wr64SceneAspect, float(ext.sharedResources->userConfig.extAspectTarget));
            break;
        default:
            workloadConfig.extAspectPercentage = 0.0f;
            break;
        }

        // Build the resolution scale vector from the configuration.
        workloadConfig.aspectRatioScale = workloadConfig.aspectRatioTarget / workloadConfig.aspectRatioSource;
        workloadConfig.resolutionScale = { resolutionMultiplier * workloadConfig.aspectRatioScale, resolutionMultiplier };
        workloadConfig.downsampleMultiplier = ext.sharedResources->userConfig.downsampleMultiplier;
        ext.sharedResources->resolutionScale = workloadConfig.resolutionScale;

        // Find the target refresh rate from the configuration.
        const auto refreshRate = ext.sharedResources->userConfig.refreshRate;
        switch (refreshRate) {
        case UserConfiguration::RefreshRate::Display:
            workloadConfig.targetRate = ext.sharedResources->swapChainRate;
            break;
        case UserConfiguration::RefreshRate::Manual:
            workloadConfig.targetRate = ext.sharedResources->userConfig.refreshRateTarget;

            // Limit the target rate to the rate detected by the swap chain.
            if ((ext.sharedResources->swapChainRate > 0) && (workloadConfig.targetRate > ext.sharedResources->swapChainRate)) {
                workloadConfig.targetRate = ext.sharedResources->swapChainRate;
            }

            break;
        case UserConfiguration::RefreshRate::Original:
        default:
            workloadConfig.targetRate = 0;
            break;
        }

        // Store the rate that was chosen for the configuration.
        ext.sharedResources->targetRate = workloadConfig.targetRate;

#   if RT_ENABLED
        workloadConfig.raytracingEnabled = rtEnabled;

        if (workloadConfig.raytracingEnabled && (ext.sharedResources->rtConfigChanged || ext.sharedResources->fbConfigChanged || sizeChanged)) {
            // Only load the RT pipeline if the device supports it.
             if (ext.device->getCapabilities().raytracing && !ext.rtShaderCache->isSetup()) {
                 ext.rtShaderCache->setup();
            }

            framebufferRenderer->setRaytracingConfig(ext.sharedResources->rtConfig, ext.sharedResources->fbConfigChanged || sizeChanged);
            ext.sharedResources->rtConfigChanged = false;
        }
#   endif
        
        workloadConfig.postBlendNoise = ext.sharedResources->emulatorConfig.dither.postBlendNoise;
        workloadConfig.postBlendNoiseNegative = ext.sharedResources->emulatorConfig.dither.postBlendNoiseNegative;
        
        if (ext.sharedResources->fbConfigChanged || sizeChanged) {
            {
                // Wait until the other queue has stopped using the interpolated color targets.
                std::unique_lock<std::mutex> interpolatedLock(ext.sharedResources->interpolatedMutex);
                InterpolatedFrameCounters &curFrameCounters = ext.sharedResources->interpolatedFrames[ext.sharedResources->interpolatedFramesIndex];
                ext.sharedResources->interpolatedCondition.wait(interpolatedLock, [&]() {
                    return curFrameCounters.presented >= curFrameCounters.available;
                });
            }

            std::scoped_lock<std::mutex> managerLock(ext.sharedResources->managerMutex);
            FramebufferManager &fbManager = ext.sharedResources->framebufferManager;
            RenderTargetManager &targetManager = ext.sharedResources->renderTargetManager;
            renderFramebufferManager->destroyAll();
            targetManager.destroyAll();
            fbManager.destroyAllTileCopies();
            ext.sharedResources->fbConfigChanged = false;
            ext.sharedResources->interpolatedColorTargets.clear();
        }

        if (ext.sharedResources->userConfigChanged) {
            idleMutex.lock();
            idleActive = ext.sharedResources->userConfig.idleWorkActive;
            idleMutex.unlock();
            idleCondition.notify_all();
        }
    }

    void WorkloadQueue::threadConfigurationValidate() {
        const std::scoped_lock lock(ext.sharedResources->configurationMutex);
        if (ext.sharedResources->userConfigChanged) {
            ext.sharedResources->newConfigValidated = true;
            ext.sharedResources->userConfigChanged = false;
        }
    }
    
    void WorkloadQueue::threadRenderFrame(GameFrame &curFrame, const GameFrame &prevFrame, const WorkloadConfiguration &workloadConfig,
        const DebuggerRenderer &debuggerRenderer, const DebuggerCamera &debuggerCamera, float curFrameWeight, float prevFrameWeight,
        float deltaTimeMs, RenderTargetKey overrideTargetKey, int32_t overrideTargetFbPairIndex, RenderTarget *overrideTarget,
        uint32_t overrideTargetModifier, bool uploadVelocity, bool uploadExtras, bool interpolateTiles, bool interpolateLookAts)
    {
#   if ENABLE_HIGH_RESOLUTION_RENDERER
        std::scoped_lock<std::mutex> managerLock(ext.sharedResources->workloadMutex);
        FramebufferManager &fbManager = ext.sharedResources->framebufferManager;
        RenderTargetManager &targetManager = ext.sharedResources->renderTargetManager;
        const bool usingMSAA = (targetManager.multisampling.sampleCount > 1);

        // Inventory native commands before any target/projection can be skipped.
        // This is diagnostic only; an output row also exists when no sun is emitted.
        if (wr64SunOutputTraceArmed()) {
            wr64SunOutputBegin(curFrameWeight, prevFrameWeight, prevFrame.matched, overrideTarget != nullptr);
            for (uint32_t w : curFrame.workloads) {
                const Workload &traceWorkload = workloads[w];
                for (uint32_t f = 0; f < traceWorkload.fbPairCount; f++) {
                    const FramebufferPair &pair = traceWorkload.fbPairs[f];
                    for (uint32_t pr = 0; pr < pair.projectionCount; pr++) {
                        const Projection &projection = pair.projections[pr];
                        if (projection.type != Projection::Type::Rectangle) continue;
                        for (uint32_t c = 0; c < projection.gameCallCount; c++) {
                            const auto &desc = projection.gameCalls[c].callDesc;
                            if (desc.tileCount == 0 || desc.tileIndex >= traceWorkload.drawData.callTiles.size()) continue;
                            const auto &tile = traceWorkload.drawData.callTiles[desc.tileIndex];
                            if (!wr64SunOutputTexture(tile.tmemHashOrID)) continue;
                            auto row = wr64SunOutputContext().output;
                            row.workload = traceWorkload.workloadId;
                            row.submission = traceWorkload.submissionFrame;
                            row.present = traceWorkload.presentId;
                            row.fbpair = f; row.projection = pr; row.call = c;
                            row.hash = tile.tmemHashOrID;
                            row.colorAddress = pair.colorImage.address;
                            row.depthAddress = pair.depthImage.address;
                            row.fbWidth = pair.colorImage.width;
                            row.sampleWidth = tile.sampleWidth; row.sampleHeight = tile.sampleHeight;
                            row.tileCopy = tile.tileCopyUsed; row.rawTMEM = tile.rawTMEM; row.tileValid = tile.valid;
                            row.raw = { desc.rect.ulx, desc.rect.uly, desc.rect.lrx, desc.rect.lry };
                            row.nativeScissor = { desc.scissorRect.ulx, desc.scissorRect.uly, desc.scissorRect.lrx, desc.scissorRect.lry };
                            row.otherModeH = desc.otherMode.H; row.otherModeL = desc.otherMode.L;
                            row.combinerH = desc.colorCombiner.H; row.combinerL = desc.colorCombiner.L;
                            const auto &prim = desc.rdpParams.primColor;
                            row.prim = { float(prim.x), float(prim.y), float(prim.z), float(prim.w) };
                            wr64SunOutputWrite("native", row);
                        }
                    }
                }
            }
        }

        rendererCPUProfiler.start();

        bool wr64RTFrame = false;
        if (framebufferRenderer->wr64RTSupported || framebufferRenderer->wr64RasterSkySupported) {
            for (uint32_t w : curFrame.workloads) {
                if ((workloads[w].wr64RtReflectionScope && framebufferRenderer->wr64RTSupported) ||
                    ((workloads[w].wr64RasterSkyScope || workloads[w].wr64RasterShadowScope ||
                        workloads[w].wr64RasterReflectionScope) && framebufferRenderer->wr64RasterSkySupported)) {
                    wr64RTFrame = true;
                    break;
                }
            }
        }
        // The first RT presentation also needs a camera and initialized inverse/
        // previous world matrices. Native uploads only supply current matrices.
        const GameFrame *matchedPrevFrame = prevFrame.matched ? &prevFrame : nullptr;
        const bool aspectRatioAdjustment = (abs(workloadConfig.aspectRatioScale - 1.0f) > 1e-6f);
        const bool processProjections = aspectRatioAdjustment || prevFrame.matched || wr64RTFrame || curFrame.isDebuggerCameraEnabled(*this);
        bool uploadProjections = false;
        if (processProjections) {
            ProjectionProcessor::ProcessParams projParams;
            projParams.worker = ext.workloadGraphicsWorker;
            projParams.workloadQueue = this;
            projParams.curFrame = &curFrame;
            projParams.prevFrame = wr64RTFrame ? matchedPrevFrame : &prevFrame;
            projParams.curFrameWeight = curFrameWeight;
            projParams.prevFrameWeight = prevFrameWeight;
            projParams.aspectRatioScale = workloadConfig.aspectRatioScale;
            projectionProcessor.process(projParams);
            projectionProcessor.upload(projParams);
            uploadProjections = true;
        }

        const bool processTransforms = prevFrame.matched || wr64RTFrame;
        bool uploadTransforms = false;
        if (processTransforms) {
            TransformProcessor::ProcessParams transformParams;
            transformParams.worker = ext.workloadGraphicsWorker;
            transformParams.workloadQueue = this;
            transformParams.curFrame = &curFrame;
            transformParams.prevFrame = matchedPrevFrame;
            transformParams.curFrameWeight = curFrameWeight;
            transformParams.prevFrameWeight = prevFrameWeight;
            transformProcessor.process(transformParams);
            transformProcessor.upload(transformParams);
            uploadTransforms = true;
        }

        bool uploadTiles = false;
        if (interpolateTiles) {
            TileProcessor::ProcessParams tileParams;
            tileParams.worker = ext.workloadGraphicsWorker;
            tileParams.workloadQueue = this;
            tileParams.curFrame = &curFrame;
            tileParams.prevFrame = &prevFrame;
            tileParams.curFrameWeight = curFrameWeight;
            tileParams.prevFrameWeight = prevFrameWeight;
            tileProcessor.process(tileParams);
            tileProcessor.upload(tileParams);
            uploadTiles = true;
        }

        bool uploadLookAts = false;
        if (interpolateLookAts) {
            LookAtProcessor::ProcessParams lookAtParams;
            lookAtParams.worker = ext.workloadGraphicsWorker;
            lookAtParams.workloadQueue = this;
            lookAtParams.curFrame = &curFrame;
            lookAtParams.prevFrame = &prevFrame;
            lookAtParams.curFrameWeight = curFrameWeight;
            lookAtParams.prevFrameWeight = prevFrameWeight;
            lookAtProcessor.process(lookAtParams);
            lookAtProcessor.upload(lookAtParams);
            uploadLookAts = true;
        }

        // Reset the max height tracking for all active framebuffers.
        fbManager.resetTracking();

        if ((overrideTarget != nullptr) && !usingMSAA) {
            targetManager.setOverride(overrideTargetKey, overrideTarget);
        }

        for (uint32_t w = 0; w < curFrame.workloads.size(); w++) {
            Workload &workload = workloads[curFrame.workloads[w]];

            float wr64ReflectionPlaneY = workload.wr64RasterReflectionPlaneY;
            const bool wr64ReflectionPlaneValid = workload.wr64RasterReflectionScope &&
                workload.wr64RasterReflectionPlaneValid;
            // Use the same matched workload and presentation weight as the
            // world transforms and positions, including moving native sea level.
            // prevFrameWeight describes the previous presentation, not 1-current.
            if (wr64ReflectionPlaneValid && matchedPrevFrame != nullptr &&
                curFrame.workloads[w] < curFrame.frameMap.workloads.size()) {
                const auto &workloadMap = curFrame.frameMap.workloads[curFrame.workloads[w]];
                if (workloadMap.mapped) {
                    const Workload &prevWorkload = workloads[workloadMap.prevWorkloadIndex];
                    if (prevWorkload.wr64RasterReflectionScope && prevWorkload.wr64RasterReflectionPlaneValid &&
                        prevWorkload.wr64RtCourse == workload.wr64RtCourse) {
                        wr64ReflectionPlaneY -= (wr64ReflectionPlaneY - prevWorkload.wr64RasterReflectionPlaneY) *
                            (1.0f - curFrameWeight);
                    }
                }
            }

            // There's no guarantee the RSP was processed if framebuffers were not rendered.
            const bool processRSP = true;
            if (processRSP) {
                workload.resetRSPOutputBuffers();

                RSPProcessor::ProcessParams rspParams;
                rspParams.worker = ext.workloadGraphicsWorker;
                rspParams.drawData = &workload.drawData;
                rspParams.drawBuffers = &workload.drawBuffers;
                rspParams.outputBuffers = &workload.outputBuffers;
                rspParams.prevFrameWeight = prevFrameWeight;
                rspParams.curFrameWeight = curFrameWeight;
                rspProcessor->process(rspParams);
            }

            // Water effects need presentation-owned world positions and wave
            // normals. Raster effects do not create or bind a ray tracing scene.
            const bool wr64RTWater = (workload.wr64RtReflectionScope && framebufferRenderer->wr64RTSupported) ||
                ((workload.wr64RasterSkyScope || workload.wr64RasterShadowScope ||
                    workload.wr64RasterReflectionScope) && framebufferRenderer->wr64RasterSkySupported);
            const bool processWorldVertices = prevFrame.matched || wr64RTWater;
            if (processWorldVertices) {
                workload.resetWorldOutputBuffers();

                VertexProcessor::ProcessParams vertexParams;
                vertexParams.worker = ext.workloadGraphicsWorker;
                vertexParams.drawData = &workload.drawData;
                vertexParams.drawBuffers = &workload.drawBuffers;
                vertexParams.outputBuffers = &workload.outputBuffers;
                vertexParams.curFrameWeight = curFrameWeight;
                vertexParams.prevFrameWeight = prevFrameWeight;
                vertexParams.wr64RtWater = wr64RTWater;
                vertexProcessor->process(vertexParams);
            }

            hlslpp::float2 fixedResScale;
            Framebuffer *colorFb;
            Framebuffer *depthFb;
            uint32_t nativeColorWidth;
            uint32_t nativeColorHeight;
            uint32_t targetWidth;
            uint32_t targetHeight;
            uint32_t targetMisalignX;
            uint32_t rtWidth;
            uint32_t rtHeight;
            RenderTarget *colorTarget;
            RenderTarget *depthTarget;
            RenderFramebufferKey fbKey;
            FixedRect effectiveDrawColorRect;
            auto getTargetsFromPair = [&](uint32_t f) {
                const FramebufferPair &fbPair = workload.fbPairs[f];
                const auto &colorImg = fbPair.colorImage;
                const auto &depthImg = fbPair.depthImage;
                effectiveDrawColorRect = fbPair.drawColorRect;

                // WR64_FULLFRAME_PAIR_EDGE_FIX: the IPS-wide Options foreground
                // framebuffer reports draw coverage one native pixel short at its
                // terminal right/bottom edges, even though its declared scissor is
                // the complete 424x240 target. Normalize that pair extent before
                // render-target sizing and preserve the same extent for write
                // bookkeeping. This is deliberately restricted to the IPS-native
                // 424x240 full-frame class and never changes interior rectangles.
                // ★ VALIDATED FIX, COMPILED IN. No environment variable.
                if ((colorImg.width == 424) &&
                    !effectiveDrawColorRect.isEmpty() && !fbPair.scissorRect.isEmpty() &&
                    (fbPair.scissorRect.ulx == 0) && (fbPair.scissorRect.uly == 0) &&
                    (fbPair.scissorRect.lrx == 1696) && (fbPair.scissorRect.lry == 960) &&
                    (effectiveDrawColorRect.ulx <= 0) && (effectiveDrawColorRect.uly <= 0)) {
                    const int32_t rightGap = fbPair.scissorRect.lrx - effectiveDrawColorRect.lrx;
                    const int32_t bottomGap = fbPair.scissorRect.lry - effectiveDrawColorRect.lry;
                    if ((rightGap > 0) && (rightGap <= 4)) {
                        effectiveDrawColorRect.lrx = fbPair.scissorRect.lrx;
                    }
                    if ((bottomGap > 0) && (bottomGap <= 4)) {
                        effectiveDrawColorRect.lry = fbPair.scissorRect.lry;
                    }
                }
                fixedResScale = workloadConfig.resolutionScale;
                if (!effectiveDrawColorRect.isEmpty()) {
                    colorFb = nullptr;
                    depthFb = nullptr;
                    nativeColorWidth = colorImg.width;
                    nativeColorHeight = effectiveDrawColorRect.bottom(true);

                    // When the target is much bigger than the reference height, we reduce the resolution scaling (but clamped to 1.0).
                    const uint32_t heightThreshold = (workload.viFbSize[1] > 0) ? ((workload.viFbSize[1] * 3) / 2) : 360;
                    uint32_t downsampleMultiplier = workloadConfig.downsampleMultiplier;
                    if ((nativeColorHeight >= heightThreshold) && (fixedResScale[1] >= 2.0f)) {
                        fixedResScale = hlslpp::max(fixedResScale / 2.0f, hlslpp::float2(1.0f, 1.0f));
                        downsampleMultiplier = std::max(downsampleMultiplier / 2U, 1U);
                    }

                    if (fbPair.depthRead || fbPair.depthWrite || fbPair.fastPaths.clearDepthOnly) {
                        uint32_t depthAddress = fbPair.fastPaths.clearDepthOnly ? colorImg.address : depthImg.address;
                        depthFb = &fbManager.get(depthAddress, G_IM_SIZ_16b, nativeColorWidth, nativeColorHeight);
                        depthFb->everUsedAsDepth = true;
                    }
                    else {
                        depthFb = nullptr;
                    }

                    // Ensure dimensions are the same for the color and depth targets based on their previous sizes.
                    fbKey = RenderFramebufferKey();

                    if (!fbPair.fastPaths.clearDepthOnly) {
                        colorFb = &fbManager.get(colorImg.address, colorImg.siz, nativeColorWidth, nativeColorHeight);
                    }

                    if (colorFb != nullptr) {
                        fbKey.colorTargetKey = RenderTargetKey(colorFb->addressStart, colorFb->width, colorFb->siz, Framebuffer::Type::Color);
                        colorTarget = &targetManager.get(fbKey.colorTargetKey);
                    }
                    else {
                        colorTarget = nullptr;
                    }

                    // Apply the modifier key if we retrieved the override target.
                    if ((colorTarget != nullptr) && (colorTarget == overrideTarget)) {
                        fbKey.modifierKey = overrideTargetModifier;
                    }

                    fixedResScale = RenderTarget::computeFixedResolutionScale(colorImg.width, fixedResScale);
                    RenderTarget::computeScaledSize(nativeColorWidth, nativeColorHeight, fixedResScale, targetWidth, targetHeight, targetMisalignX);

                    rtWidth = targetWidth;
                    rtHeight = targetHeight;

                    // The desired size should not be less than the existing size of the color and depth targets.
                    RenderTarget *chosenRt = nullptr;
                    if (depthFb != nullptr) {
                        fbKey.depthTargetKey = RenderTargetKey(depthFb->addressStart, depthFb->width, depthFb->siz, Framebuffer::Type::Depth);
                        depthTarget = &targetManager.get(fbKey.depthTargetKey);
                        depthTarget->resolutionScale = fixedResScale;
                        rtWidth = std::max(rtWidth, depthTarget->width);
                        rtHeight = std::max(rtHeight, depthTarget->height);
                        chosenRt = depthTarget;
                    }
                    else {
                        depthTarget = nullptr;
                    }

                    if (colorTarget != nullptr) {
                        rtWidth = std::max(rtWidth, colorTarget->width);
                        rtHeight = std::max(rtHeight, colorTarget->height);
                        chosenRt = colorTarget;
                    }

                    assert(chosenRt != nullptr);
                    chosenRt->resolutionScale = fixedResScale;
                    chosenRt->downsampleMultiplier = downsampleMultiplier;
                    if (colorTarget) colorTarget->wr64SeparateWindows = workload.wr64SeparateWindows && nativeColorWidth == 424;
                    chosenRt->misalignX = targetMisalignX;
                    chosenRt->invMisalignX = (targetMisalignX > 0) ? (std::lround(fixedResScale.y) - targetMisalignX) : 0;

                    assert((colorTarget != nullptr) || (depthTarget != nullptr));
                    return true;
                }
                else {
                    return false;
                }
            };

            thread_local std::unordered_set<RenderTarget *> resizedTargets;
            thread_local std::vector<std::pair<RenderTarget *, RenderTarget *>> colorDepthPairs;
            resizedTargets.clear();
            colorDepthPairs.clear();

            const uint32_t fbPairCount = (debuggerRenderer.framebufferIndex >= 0) ? (debuggerRenderer.framebufferIndex + 1) : workload.fbPairCount;
            for (uint32_t f = 0; f < fbPairCount; f++) {
                const FramebufferPair &fbPair = workload.fbPairs[f];
#           if RT_ENABLED
                for (uint32_t p = 0; p < fbPair.projectionCount; p++) {
                    const Projection &proj = fbPair.projections[p];
                    const bool perspProj = (proj.type == Projection::Type::Perspective);
                    const bool rtProj = (perspProj && workloadConfig.raytracingEnabled && fbPair.depthWrite); // TODO: Move this condition out of here, ideally by moving the shader submission elsewhere.
                    if (!rtProj) {
                        continue;
                    }

                    // Submit RT shaders if it's an RT proj.
                    for (uint32_t d = 0; d < proj.gameCallCount; d++) {
                        const GameCall &call = proj.gameCalls[d];
                        ext.rtShaderCache->submit(call.shaderDesc);
                    }
                }
#           endif

                // Resize the render targets for this framebuffer pair if necessary.
                if (getTargetsFromPair(f)) {
                    // Resize the native target buffers.
                    if (colorFb != nullptr) {
                        colorFb->nativeTarget.resetBufferHistory();
                    }

                    if (depthFb != nullptr) {
                        depthFb->nativeTarget.resetBufferHistory();
                    }

                    if ((colorTarget != nullptr) && colorTarget->resize(ext.workloadGraphicsWorker, rtWidth, rtHeight)) {
                        resizedTargets.emplace(colorTarget);
                        colorFb->readHeight = 0;
                    }

                    // Set up the dummy target used for rendering the depth if no depth framebuffer is active.
                    if (depthFb == nullptr) {
                        if (dummyDepthTarget == nullptr) {
                            dummyDepthTarget = std::make_unique<RenderTarget>(0, Framebuffer::Type::Depth, targetManager.multisampling, targetManager.usesHDR);
                            dummyDepthTarget->setupDepth(ext.workloadGraphicsWorker, rtWidth, rtHeight);
                        }

                        if ((dummyDepthTarget != nullptr) && dummyDepthTarget->resize(ext.workloadGraphicsWorker, rtWidth, rtHeight)) {
                            resizedTargets.emplace(dummyDepthTarget.get());
                        }

                        if (colorTarget != nullptr) {
                            colorDepthPairs.emplace_back(colorTarget, dummyDepthTarget.get());
                        }
                    }
                    else if (depthTarget != nullptr) {
                        if (colorTarget != nullptr) {
                            colorDepthPairs.emplace_back(colorTarget, depthTarget);
                        }

                        if (depthTarget->resize(ext.workloadGraphicsWorker, rtWidth, rtHeight)) {
                            resizedTargets.emplace(depthTarget);
                            depthFb->readHeight = 0;
                        }
                    }
                }

                fbManager.setupOperations(ext.workloadGraphicsWorker, fbPair.startFbOperations, fixedResScale, targetManager, &resizedTargets);
                fbManager.setupOperations(ext.workloadGraphicsWorker, fbPair.endFbOperations, fixedResScale, targetManager, &resizedTargets);
            }

            // Make sure all depth targets are at least bigger than their corresponding color targets.
            for (auto colorDepthPair : colorDepthPairs) {
                if (colorDepthPair.second->resize(ext.workloadGraphicsWorker, colorDepthPair.first->width, colorDepthPair.first->height)) {
                    resizedTargets.emplace(colorDepthPair.second);
                }
            }

            for (RenderTarget *renderTarget : resizedTargets) {
                renderFramebufferManager->destroyAllWithRenderTarget(renderTarget);
            }

            uint32_t gameCallCursor = 0;
            const uint32_t gameCallCountMax = (debuggerRenderer.globalDrawCallIndex >= 0) ? (debuggerRenderer.globalDrawCallIndex + 1) : workload.gameCallCount;
            thread_local std::vector<BufferUploader *> bufferUploaders;
            bufferUploaders.clear();

            // Indicate to the texture cache the textures must not be deleted.
            ext.textureCache->incrementLock();

            // Reset the texture cache vectors for the framebuffer renderer.
            framebufferRenderer->updateTextureCache(ext.textureCache);

            for (uint32_t f = 0; f < fbPairCount; f++) {
                const FramebufferPair &fbPair = workload.fbPairs[f];
                fbManager.performDiscards(fbPair.startFbDiscards);
            }
            
            // Add all framebuffer pairs to the framebuffer renderer and setup the operations.
            scratchFbChangePool.reset();
            fbManager.resetOperations();
            framebufferRenderer->resetFramebuffers(ext.workloadGraphicsWorker, ubershadersVisible, workload.extended.ditherNoiseStrength, targetManager.multisampling);

#       if RT_ENABLED
            if (workloadConfig.raytracingEnabled) {
                framebufferRenderer->resetRaytracing(ext.rtShaderCache, ext.blueNoiseTexture);
            }
#       endif

            for (uint32_t f = 0; f < fbPairCount; f++) {
                const FramebufferPair &fbPair = workload.fbPairs[f];
                if (getTargetsFromPair(f)) {
                    RenderFramebufferStorage &fbStorage = renderFramebufferManager->get(fbKey, colorTarget, (depthTarget != nullptr) ? depthTarget : dummyDepthTarget.get());
                    FramebufferRenderer::DrawParams drawParams;
                    drawParams.worker = ext.workloadGraphicsWorker;
                    drawParams.fbStorage = &fbStorage;
                    drawParams.curWorkload = &workload;
                    drawParams.wr64RtPresentation = true;
                    drawParams.wr64RasterReflectionPlaneY = wr64ReflectionPlaneY;
                    drawParams.wr64RasterReflectionPlaneValid = wr64ReflectionPlaneValid;
                    drawParams.fbPairIndex = f;
                    drawParams.fbWidth = nativeColorWidth;
                    drawParams.fbHeight = nativeColorHeight;
                    drawParams.targetWidth = targetWidth;
                    drawParams.targetHeight = targetHeight;
                    drawParams.rasterShaderCache = ext.rasterShaderCache;
                    drawParams.resolutionScale = fixedResScale;
                    drawParams.aspectRatioSource = workloadConfig.aspectRatioSource;
                    drawParams.aspectRatioTarget = workloadConfig.aspectRatioTarget;
                    drawParams.extAspectPercentage = workloadConfig.extAspectPercentage;
                    drawParams.horizontalMisalignment = (colorTarget != nullptr) ? float(colorTarget->misalignX) : float(depthTarget->misalignX);
                    drawParams.presetScene = curFrame.presetScene;
                    drawParams.rtEnabled = workloadConfig.raytracingEnabled;
                    drawParams.submissionFrame = workload.submissionFrame;
                    drawParams.deltaTimeMs = deltaTimeMs;
                    // deltaTimeMs is historically named but contains seconds:
                    // 1 / targetRate, or 1 / nativeRate without interpolation.
                    drawParams.motionTimeScale = wr64MotionTimeScale(curFrameWeight, prevFrameWeight,
                        workload.viOriginalRate, deltaTimeMs);
                    drawParams.ubershadersOnly = ubershadersOnly;
                    drawParams.postBlendNoise = workloadConfig.postBlendNoise;
                    drawParams.postBlendNoiseNegative = workloadConfig.postBlendNoiseNegative;
                    drawParams.maxGameCall = std::min(gameCallCountMax - gameCallCursor, fbPair.gameCallCount);
                    framebufferRenderer->addFramebuffer(drawParams);
                }
                
                gameCallCursor += fbPair.gameCallCount;
            }

            // Create all GPU tile mappings and upload them.
            if (!workload.drawData.gpuTiles.empty()) {
                std::pair<size_t, size_t> gpuTileRange;
                gpuTileRange.first = 0;
                gpuTileRange.second = workload.drawData.gpuTiles.size();
                framebufferRenderer->createGPUTiles(workload.drawData.callTiles.data(), uint32_t(workload.drawData.gpuTiles.size()),
                    workload.drawData.gpuTiles.data(), &fbManager, ext.textureCache, workload.submissionFrame);

                // Upload the GPU tiles.
                ext.workloadTilesUploader->submit(ext.workloadGraphicsWorker, {
                    { workload.drawData.gpuTiles.data(), gpuTileRange, sizeof(interop::GPUTile), RenderBufferFlag::STORAGE, { }, &workload.drawBuffers.gpuTilesBuffer}
                });

                bufferUploaders.emplace_back(ext.workloadTilesUploader);
            }

            if (uploadVelocity) {
                bufferUploaders.emplace_back(ext.workloadVelocityUploader);
                uploadVelocity = false;
            }

            if (uploadExtras) {
                bufferUploaders.emplace_back(ext.workloadExtrasUploader);
                uploadExtras = false;
            }

            if (uploadProjections) {
                bufferUploaders.emplace_back(projectionProcessor.bufferUploader.get());
                uploadProjections = false;
            }

            if (uploadTransforms) {
                bufferUploaders.emplace_back(transformProcessor.bufferUploader.get());
                uploadTransforms = false;
            }

            if (uploadTiles) {
                bufferUploaders.emplace_back(tileProcessor.bufferUploader.get());
                uploadTiles = false;
            }

            if (uploadLookAts) {
                bufferUploaders.emplace_back(lookAtProcessor.bufferUploader.get());
                uploadLookAts = false;
            }

#       if RT_ENABLED
            if (workloadConfig.raytracingEnabled) {
                ext.rtShaderCache->setNextState();
            }
#       endif

            workerMutex.lock();
            ext.workloadGraphicsWorker->commandList->begin();
            ext.workloadGraphicsWorker->commandList->resetQueryPool(queryPool.get(), 0, 2);
            ext.workloadGraphicsWorker->commandList->writeTimestamp(queryPool.get(), 0);
            framebufferRenderer->endFramebuffers(ext.workloadGraphicsWorker, &workload.drawBuffers, &workload.outputBuffers, workloadConfig.raytracingEnabled);
            framebufferRenderer->recordSetup(ext.workloadGraphicsWorker, bufferUploaders, processRSP ? rspProcessor.get() : nullptr, processWorldVertices ? vertexProcessor.get() : nullptr, &workload.outputBuffers, &workload.drawBuffers, workloadConfig.raytracingEnabled);
            
            // Record all framebuffer pairs.
            uint32_t framebufferIndex = 0;
            uint32_t pacingBackingWidth = 0, pacingBackingHeight = 0;
            for (uint32_t f = 0; f < fbPairCount; f++) {
                const FramebufferPair &fbPair = workload.fbPairs[f];
                bool validTargets = getTargetsFromPair(f);
                fbManager.recordOperations(ext.workloadGraphicsWorker, &workload.fbChangePool, &workload.fbStorage, ext.shaderLibrary, ext.textureCache,
                    fbPair.startFbOperations, targetManager, fixedResScale, f, workload.submissionFrame);

                if (validTargets) {
                    // This is backing allocation extent, not the viewport or
                    // swapchain output; the presentation report records output.
                    if (colorTarget != nullptr) {
                        pacingBackingWidth = std::max(pacingBackingWidth, colorTarget->width);
                        pacingBackingHeight = std::max(pacingBackingHeight, colorTarget->height);
                    }
                    const auto &colorImg = fbPair.colorImage;
                    const auto &depthImg = fbPair.depthImage;
                    bool colorFormatUpdated = false;
                    if (colorFb != nullptr) {
                        if (colorImg.formatChanged) {
                            colorFb->discardLastWrite();
                        }
                        else if (colorFb->isLastWriteDifferent(Framebuffer::Type::Color)) {
                            RenderTargetKey otherColorTargetKey(colorFb->addressStart, colorFb->width, colorFb->siz, colorFb->lastWriteType);
                            RenderTarget &otherColorTarget = targetManager.get(otherColorTargetKey);
                            if (!otherColorTarget.isEmpty()) {
                                const FixedRect &r = colorFb->lastWriteRect;
                                colorTarget->copyFromTarget(ext.workloadGraphicsWorker, &otherColorTarget, r.left(false), r.top(false), r.width(false, true), r.height(false, true), ext.shaderLibrary);
                                colorFb->discardLastWrite();
                                colorFormatUpdated = true;
                            }
                        }

                        if (colorImg.formatChanged) {
                            colorTarget->clearColorTarget(ext.workloadGraphicsWorker);
                            colorFb->readHeight = 0;
                        }

                        if (colorFb->height > colorFb->readHeight) {
                            uint32_t readRowCount = colorFb->height - colorFb->readHeight;
                            FramebufferChange *colorFbChange = colorFb->readChangeFromStorage(ext.workloadGraphicsWorker, workload.fbStorage, scratchFbChangePool,
                                Framebuffer::Type::Color, colorImg.fmt, f, colorFb->readHeight, readRowCount, ext.shaderLibrary);

                            if (colorFbChange != nullptr) {
                                colorTarget->copyFromChanges(ext.workloadGraphicsWorker, *colorFbChange, colorFb->width, readRowCount, colorFb->readHeight, ext.shaderLibrary);
                            }

                            colorFb->readHeight = colorFb->height;
                        }
                    }

                    bool depthFormatUpdated = false;
                    bool depthFbChanged = false;
                    bool depthFbTypeChanged = false;
                    if (depthFb != nullptr) {
                        depthFbTypeChanged = (depthFb->lastWriteType == Framebuffer::Type::Color);

                        bool imgFormatChanged = (colorFb == nullptr) ? colorImg.formatChanged : depthImg.formatChanged;
                        if (imgFormatChanged) {
                            depthFb->discardLastWrite();
                        }
                        else if (depthFb->isLastWriteDifferent(Framebuffer::Type::Depth)) {
                            RenderTargetKey otherDepthTargetKey(depthFb->addressStart, depthFb->width, depthFb->siz, depthFb->lastWriteType);
                            RenderTarget &otherDepthTarget = targetManager.get(otherDepthTargetKey);
                            if (!otherDepthTarget.isEmpty()) {
                                const FixedRect &r = depthFb->lastWriteRect;
                                depthTarget->copyFromTarget(ext.workloadGraphicsWorker, &otherDepthTarget, r.left(false), r.top(false), r.width(false, true), r.height(false, true), ext.shaderLibrary);
                                depthFb->discardLastWrite();
                                depthFormatUpdated = true;
                            }
                        }

                        if (imgFormatChanged) {
                            depthTarget->clearDepthTarget(ext.workloadGraphicsWorker);
                            depthFb->readHeight = 0;
                        }

                        if (depthFb->height > depthFb->readHeight) {
                            uint32_t readRowCount = depthFb->height - depthFb->readHeight;
                            FramebufferChange *depthFbChange = depthFb->readChangeFromStorage(ext.workloadGraphicsWorker, workload.fbStorage, scratchFbChangePool, Framebuffer::Type::Depth,
                                G_IM_FMT_DEPTH, f, depthFb->readHeight, readRowCount, ext.shaderLibrary);

                            if (depthFbChange != nullptr) {
                                depthTarget->copyFromChanges(ext.workloadGraphicsWorker, *depthFbChange, depthFb->width, readRowCount, depthFb->readHeight, ext.shaderLibrary);
                                depthFbChanged = true;
                            }

                            depthFb->readHeight = depthFb->height;
                        }
                    }
                    
                    framebufferRenderer->recordFramebuffer(ext.workloadGraphicsWorker, framebufferIndex++);

                    // Transition the render targets in case the present queue will show them so it doesn't have to perform transitions.
                    if (colorTarget != nullptr && depthTarget != nullptr) {
                        RenderTextureBarrier textureBarriers[] = {
                            RenderTextureBarrier(colorTarget->texture.get(), RenderTextureLayout::SHADER_READ),
                            RenderTextureBarrier(depthTarget->texture.get(), RenderTextureLayout::SHADER_READ)
                        };

                        ext.workloadGraphicsWorker->commandList->barriers(RenderBarrierStage::GRAPHICS, textureBarriers, uint32_t(std::size(textureBarriers)));
                    }
                    else {
                        RenderTarget *chosenTarget = (colorTarget != nullptr) ? colorTarget : depthTarget;
                        ext.workloadGraphicsWorker->commandList->barriers(RenderBarrierStage::GRAPHICS, RenderTextureBarrier(chosenTarget->texture.get(), RenderTextureLayout::SHADER_READ));
                    }

                    // Do the resolve if using MSAA while target override is active and we're on the correct framebuffer pair index.
                    if (usingMSAA && (overrideTarget != nullptr) && ((uint32_t)overrideTargetFbPairIndex == f)) {
                        overrideTarget->resize(ext.workloadGraphicsWorker, colorTarget->width, colorTarget->height);
                        overrideTarget->resolveFromTarget(ext.workloadGraphicsWorker, colorTarget, ext.shaderLibrary);
                        overrideTarget->wr64SeparateWindows = colorTarget->wr64SeparateWindows;
                    }

                    const uint64_t writeTimestamp = fbManager.nextWriteTimestamp();
                    FixedRect depthFbRect;
                    if (colorFb != nullptr) {
                        colorFb->lastWriteRect.merge(effectiveDrawColorRect.scaled(fixedResScale.x, fixedResScale.y));
                        colorFb->lastWriteType = Framebuffer::Type::Color;
                        colorFb->lastWriteFmt = colorImg.fmt;
                        colorFb->lastWriteTimestamp = writeTimestamp;
                        depthFbRect = fbPair.drawDepthRect;
                    }
                    else {
                        depthFbRect = effectiveDrawColorRect;
                    }
                    
                    const bool depthWrite = ((colorFb == nullptr) || depthFbChanged || depthFbTypeChanged || fbPair.depthWrite) && (depthFb != nullptr);
                    if (depthWrite && !depthFbRect.isNull()) {
                        depthFb->lastWriteRect.merge(depthFbRect.scaled(fixedResScale.x, fixedResScale.y));
                        depthFb->lastWriteType = Framebuffer::Type::Depth;
                        depthFb->lastWriteFmt = G_IM_FMT_DEPTH;
                        depthFb->lastWriteTimestamp = writeTimestamp;
                    }
                }
                
                fbManager.recordOperations(ext.workloadGraphicsWorker, &workload.fbChangePool, &workload.fbStorage, ext.shaderLibrary, ext.textureCache,
                    fbPair.endFbOperations, targetManager, fixedResScale, f, workload.submissionFrame);
            }

            if (WR64_DIAGNOSTIC_ENABLED) framebufferRenderer->recordWr64SkyCaptureReadback(ext.workloadGraphicsWorker);
            ext.workloadGraphicsWorker->commandList->writeTimestamp(queryPool.get(), 1);
            ext.workloadGraphicsWorker->commandList->end();
            framebufferRenderer->waitForUploaders();
            ext.workloadGraphicsWorker->execute();
            ext.workloadGraphicsWorker->wait();
            if (WR64_DIAGNOSTIC_ENABLED) framebufferRenderer->consumeWr64SkyCaptureReadback();
            workerMutex.unlock();

            // Update the GPU profiler with the results from the timestamps of the frame.
            queryPool->queryResults();
            const uint64_t *frameTimestamps = queryPool->getResults();
            rendererGPUProfiler.log(double(frameTimestamps[1] - frameTimestamps[0]) / 1000000.0);
            if (WR64_DIAGNOSTIC_ENABLED) {
            Wr64FramePacingRenderSample pacingSample;
            pacingSample.gpuMs = frameTimestamps[1] >= frameTimestamps[0]
                ? double(frameTimestamps[1] - frameTimestamps[0]) / 1000000.0 : -1.0;
            pacingSample.width = pacingBackingWidth;
            pacingSample.height = pacingBackingHeight;
            pacingSample.viOriginalRate = workload.viOriginalRate;
            pacingSample.targetRate = workloadConfig.targetRate;
            pacingSample.samples = targetManager.multisampling.sampleCount;
            pacingSample.reflections = workload.wr64RtReflectionScope;
            pacingSample.shadows = workload.wr64RtShadowScope;
            wr64RecordFramePacingRender(pacingSample);
            }

            // Indicate to the texture cache it's safe to delete the textures if no locks are active.
            ext.textureCache->decrementLock();
        }

        if ((overrideTarget != nullptr) && !usingMSAA) {
            targetManager.removeOverride(overrideTargetKey);
        }

        framebufferRenderer->advanceFrame(workloadConfig.raytracingEnabled);
        rendererCPUProfiler.end();
        rendererCPUProfiler.log();
        rendererCPUProfiler.reset();
#   endif
    }

    void WorkloadQueue::threadAdvanceBarrier() {
        std::scoped_lock<std::mutex> cursorLock(cursorMutex);
        barrierCursor = (barrierCursor + 1) % workloads.size();
    }

    void WorkloadQueue::threadAdvanceWorkloadId(uint64_t newWorkloadId) {
        {
            std::scoped_lock<std::mutex> cursorLock(workloadIdMutex);
            workloadId = newWorkloadId;
        }

        workloadIdCondition.notify_all();
    }

    void WorkloadQueue::renderThreadLoop() {
        Thread::setCurrentThreadName("RT64 Workload");
        wr64StallProbeNameThread("workload");

        WorkloadConfiguration workloadConfig;
        int64_t logicalTicks = 0;
        int64_t displayTicks = 0;
        uint32_t originalRateForTicks = 0;
        uint32_t displayRateForTicks = 0;
        int processCursor = -1;
        // ★ VALIDATED FIX, COMPILED IN. No environment variable.
        constexpr bool wr64ExactInterpolatedCadence = true;
        bool frameReduction = false;
        while (threadsRunning) {
            {
                std::unique_lock<std::mutex> cursorLock(cursorMutex);
                cursorCondition.wait(cursorLock, [&]() {
                    return (writeCursor != threadCursor) || !threadsRunning;
                });

                if (threadsRunning) {
                    processCursor = threadCursor;
                    threadCursor = (threadCursor + 1) % workloads.size();
                }
            }

            if (processCursor >= 0) {
                std::unique_lock<std::mutex> threadLock(threadMutex);
                Workload &workload = workloads[processCursor];
                ext.presentQueue->waitForPresentId(workload.presentId);

                if (!threadsRunning) {
                    continue;
                }

                // Heartbeat at native frame rate, about twenty a second. Cheap enough
                // to leave on and it gives the context dump a ruler: without it there
                // is no way to tell from the dump which side of a frame boundary an
                // expensive call landed on.
                wr64StallProbeMarkEvent("native-frame", workload.workloadId);

                ElapsedTimer workloadTimer;
                workloadProfiler.start();
                threadConfigurationUpdate(workload.viFbSize, workloadConfig, workload.wr64SeparateWindows);

                // FIXME: This is a very hacky way to find out if we need to advance the frame if the workload was paused for the first time.
                if (!workload.paused || (!gameFrames[curFrameIndex].workloads.empty() && (gameFrames[curFrameIndex].workloads[0] != (uint32_t)processCursor))) {
                    prevFrameIndex = curFrameIndex;
                    curFrameIndex = (curFrameIndex + 1) % gameFrames.size();
                }
                
                // TODO: The frame detection needs to be more elaborate than just matching one workload to one frame.
                GameFrame &curFrame = gameFrames[curFrameIndex];
                const GameFrame &prevFrame = gameFrames[prevFrameIndex];
                uint32_t workloadIndex = processCursor;
                {
                    // Whole frame match: builds the call hash map for every draw call
                    // in the workload and then walks the candidate list. Runs once per
                    // native frame on the thread that everything else waits behind, so
                    // a spike here is a spike in every interpolated frame after it.
                    WR64StallProbe frameSetProbe("workload-frame-set", workload.workloadId);
                    curFrame.set(*this, &workloadIndex, 1);
                }

                // Detect the color image to interpolate for this workload.
                RenderTargetKey interpolationTargetKey;
                int32_t interpolationTargetFbPairIndex = -1;

                // R6 instrumentation. The loop below walks the framebuffer pairs the
                // game drew this native frame and picks one to interpolate. There are
                // five separate ways it can finish without picking anything, and when
                // that happens the frame after it is shown once instead of nine times,
                // which is the stutter. These counters record which of the five exits
                // each pair took so the answer is read out of the log rather than
                // guessed at. Counting happens inside the lock below because that is
                // where the data lives; nothing is written to the log until after the
                // lock is released.
                uint32_t targetPairsSeen = 0;
                uint32_t targetRejectEmptyRect = 0;
                uint32_t targetRejectDuplicate = 0;
                uint32_t targetRejectNotCandidate = 0;
                uint32_t targetRejectNoFramebuffer = 0;
                uint32_t targetRejectInterpolationOff = 0;
                uint32_t targetLastCandidateAddress = 0;
                {
                    std::scoped_lock<std::mutex> managerLock(ext.sharedResources->managerMutex);
                    FramebufferManager &fbManager = ext.sharedResources->framebufferManager;
                    std::vector<uint32_t> &colorVector = ext.sharedResources->colorImageAddressVector;
                    std::unordered_set<uint32_t> &colorSet = ext.sharedResources->colorImageAddressSet;
                    colorVector.clear();
                    colorSet.clear();
                    for (int32_t f = workload.fbPairCount - 1; f >= 0; f--) {
                        const FramebufferPair &fbPair = workload.fbPairs[f];
                        bool interpolationCandidate = fbPair.earlyPresentCandidate();
                        targetPairsSeen++;
                        if (fbPair.drawColorRect.isEmpty()) {
                            targetRejectEmptyRect++;
                            continue;
                        }

                        const auto &colorImg = fbPair.colorImage;
                        if (colorSet.find(colorImg.address) != colorSet.end()) {
                            targetRejectDuplicate++;
                            continue;
                        }
                        else {
                            if (interpolationCandidate) {
                                colorVector.push_back(colorImg.address);
                            }

                            colorSet.insert(colorImg.address);
                        }

                        if (!interpolationCandidate || !interpolationTargetKey.isEmpty()) {
                            // Split apart only for counting. A pair that is simply after
                            // an already chosen target is not a rejection and is not
                            // counted as one, so this tallies the first half alone.
                            if (!interpolationCandidate) {
                                targetRejectNotCandidate++;
                            }

                            continue;
                        }

                        // The last address that got as far as asking the framebuffer
                        // manager for a buffer. If the manager is the one saying no,
                        // this is the address it could not find.
                        targetLastCandidateAddress = colorImg.address;

                        Framebuffer *interpolationFb = fbManager.find(colorImg.address);
                        if ((interpolationFb != nullptr) && interpolationFb->interpolationEnabled) {
                            interpolationTargetKey.fbType = Framebuffer::Type::Color;
                            interpolationTargetKey.address = fbPair.colorImage.address;
                            interpolationTargetKey.siz = fbPair.colorImage.siz;
                            interpolationTargetKey.width = fbPair.colorImage.width;
                            interpolationTargetFbPairIndex = f;
                        }
                        else if (interpolationFb == nullptr) {
                            targetRejectNoFramebuffer++;
                        }
                        else {
                            targetRejectInterpolationOff++;
                        }
                    }
                }

                // R6. The lock went out of scope on the line above, so writing to the
                // log here cannot hold up anything else. One line per native frame
                // either way: the "found" line describes a normal frame and the "empty"
                // line describes a broken one, and reading the two next to each other
                // is what says which pair went missing or which check changed its mind.
                {
                    uint64_t targetDetail = 0;
                    targetDetail |= uint64_t(targetPairsSeen & 0xFF);
                    targetDetail |= uint64_t(targetRejectEmptyRect & 0xFF) << 8;
                    targetDetail |= uint64_t(targetRejectDuplicate & 0xFF) << 16;
                    targetDetail |= uint64_t(targetRejectNotCandidate & 0xFF) << 24;
                    targetDetail |= uint64_t(targetRejectNoFramebuffer & 0xFF) << 32;
                    targetDetail |= uint64_t(targetRejectInterpolationOff & 0xFF) << 40;
                    targetDetail |= uint64_t(uint32_t(interpolationTargetFbPairIndex + 1) & 0xFF) << 48;

                    if (interpolationTargetKey.isEmpty()) {
                        wr64StallProbeMarkEvent("workload-target-empty", targetDetail);

                        // Written only when the loop failed, so it costs nothing during
                        // a normal race and there is no reason to pack it in with the
                        // rest. Zero means no pair ever reached the manager at all.
                        wr64StallProbeMarkEvent("workload-target-empty-address", uint64_t(targetLastCandidateAddress));
                    }
                    else {
                        wr64StallProbeMarkEvent("workload-target-found", targetDetail);
                    }
                }

                float prevFrameWeight = 0.0f;
                float curFrameWeight = 1.0f;
                float deltaTimeMs = 1.0f / 30.0f;
                // Native-rate RT still needs producer-owned water identities and
                // matching field data. This does not enable extra presentations.
                const bool wr64RTFrameMatching = (workload.wr64RtReflectionScope && framebufferRenderer->wr64RTSupported) ||
                    ((workload.wr64RasterSkyScope || workload.wr64RasterShadowScope ||
                        workload.wr64RasterReflectionScope) && framebufferRenderer->wr64RasterSkySupported);
                // Roundness updates native endpoints even without extra
                // presentations or selected reflection/shadow passes. The
                // captured camera scopes also admit one-player water, even
                // when Water Surface Distance itself is set to Original.
                const bool wr64RoundnessFrameMatching = wr64SplitWaterRoundnessMatching(
                    workload.wr64SplitWaterRoundnessScope || workload.wr64FarWaterDistanceViewScope[0] ||
                        workload.wr64FarWaterDistanceViewScope[1], getWr64WaterLaplacianStrength());
                bool wr64FarWaterFrameMatching = workload.wr64FarWaterDistanceViewModes[0] ||
                    workload.wr64FarWaterDistanceViewModes[1];
                bool wr64WaveFrameMatching = workload.wr64WaveDistanceSnapshot.valid && workload.wr64WaveDistanceSnapshot.mode;
                for (uint32_t previous : prevFrame.workloads) {
                    if (previous < workloads.size()) wr64WaveFrameMatching = wr64WaveFrameMatching ||
                        (workloads[previous].wr64WaveDistanceSnapshot.valid && workloads[previous].wr64WaveDistanceSnapshot.mode);
                    if (previous < workloads.size()) wr64FarWaterFrameMatching = wr64FarWaterFrameMatching ||
                        workloads[previous].wr64FarWaterDistanceViewModes[0] || workloads[previous].wr64FarWaterDistanceViewModes[1];
                }
                const bool requiresFrameMatching = (workloadConfig.targetRate > 0) ||
                    workloadConfig.raytracingEnabled || wr64RTFrameMatching || wr64RoundnessFrameMatching || wr64FarWaterFrameMatching || wr64WaveFrameMatching;
                bool generateInterpolatedFrames = false;
                // Never blend a full menu frame with the two-player composite.
                bool sameLayout = true;
                for (uint32_t previous : prevFrame.workloads) {
                    if (previous < workloads.size() && workloads[previous].wr64SeparateWindows != workload.wr64SeparateWindows)
                        sameLayout = false;
                }
                // The cadence meter needs resetTicks, which is scoped to the block
                // below. Hoisted rather than recomputed: recomputing it here would
                // read originalRateForTicks AFTER the reset has already overwritten
                // it, so the copy would always say "no reset" - which is precisely
                // the value the meter exists to capture.
                bool wr64CadenceResetTicks = false;
                bool velocityUploaderUsed = false;
                bool tileInterpolationUsed = false;
                bool lookAtInterpolationUsed = false;
                if (requiresFrameMatching) {
                    matchingProfiler.reset();
                    matchingProfiler.start();
                    {
                        // Cross frame matching for the whole workload. Runs once per
                        // native frame on the thread every interpolated frame waits
                        // behind, and it was the largest uninstrumented block left on
                        // that thread after R4. Hot floor rather than always on: it
                        // fires twenty times a second and is normally sub millisecond.
                        WR64StallProbeHot matchProbe("workload-match", workload.workloadId);
                        // A layout boundary must not interpolate menus into either player pane.
                        if (sameLayout) curFrame.match(ext.workloadGraphicsWorker, *this, prevFrame, ext.workloadVelocityUploader, velocityUploaderUsed, tileInterpolationUsed, lookAtInterpolationUsed);
                    }
                    matchingProfiler.end();
                    matchingProfiler.log();

                    const bool displayRateAboveOriginal = (workload.viOriginalRate > 0) && (workloadConfig.targetRate > workload.viOriginalRate);
                    generateInterpolatedFrames = sameLayout && !workload.paused && displayRateAboveOriginal && !interpolationTargetKey.isEmpty();

                    const bool resetTicks = !generateInterpolatedFrames || (originalRateForTicks != workload.viOriginalRate) || (displayRateForTicks != workloadConfig.targetRate) || !displayRateAboveOriginal;
                    wr64CadenceResetTicks = resetTicks;
                    if (resetTicks) {
                        logicalTicks = 0;
                        displayTicks = 0;
                        originalRateForTicks = workload.viOriginalRate;
                        displayRateForTicks = workloadConfig.targetRate;
                    }
                }

                // Estimate amount of frames to render based on how many display frames it'd take to reach the next logical frame.
                uint32_t displayFrames = 1;
                if (generateInterpolatedFrames) {
                    logicalTicks += workloadConfig.targetRate;
                    displayFrames = uint32_t((logicalTicks - displayTicks) / workload.viOriginalRate);
                    deltaTimeMs = 1.0f / float(workloadConfig.targetRate);

                    if ((displayFrames > 1) && frameReduction) {
                        displayTicks += workload.viOriginalRate;
                        displayFrames--;
                        frameReduction = false;
                    }

                    assert((logicalTicks > displayTicks) && "Logical ticks must always remain bigger than the display ticks.");
                    assert(((logicalTicks - displayTicks) <= (workloadConfig.targetRate + workload.viOriginalRate)) && "The gap between logical ticks and display ticks can't be bigger than the target rate.");
                    assert((displayFrames > 0) && "At least one display frame must be generated.");
                }
                else if (workload.viOriginalRate > 0) {
                    deltaTimeMs = 1.0f / float(workload.viOriginalRate);
                }

                // ---- CADENCE METER. Records only; changes nothing.
                //
                // Placed here because this is the first point where displayFrames is
                // final for this native frame - after the accumulator has advanced and
                // after the frameReduction branch that could still decrement it. Any
                // earlier and the number written down is not the number the presenter
                // is given.
                //
                // R3 adds the queue depth: how many workloads are already waiting
                // when this one is picked up. A short interval with depth 0 means
                // the thread simply got through its own work faster; depth 1 or
                // more means the game had run ahead and the thread is catching up.
                // Read from the same two cursors the wait predicate above uses.
                const uint32_t wr64CadenceQueueDepth = uint32_t(
                    (writeCursor - threadCursor + int(workloads.size())) % int(workloads.size()));
                wr64CadenceMeterRecord(workload.submissionFrame, workload.workloadId,
                    workload.presentId, workload.viOriginalRate, workloadConfig.targetRate,
                    displayFrames, (logicalTicks - displayTicks), wr64CadenceResetTicks,
                    generateInterpolatedFrames, workload.paused, wr64CadenceQueueDepth);

                ext.sharedResources->viOriginalRate = workload.viOriginalRate;
                
                // Get the current and previous set of frame counters. The other set can be in use by the present queue. Skip if no new present event has arrived before this workload event.
                InterpolatedFrameCounters &prevFrameCounters = ext.sharedResources->interpolatedFrames[ext.sharedResources->interpolatedFramesIndex];
                // BACK-PRESSURE METER. Records only; changes nothing.
                //
                // Read BEFORE the wait below, so the row says what the previous
                // counter set looked like when this batch began. Reading it after
                // would only ever show a drained set, which is the very thing the
                // run is trying to distinguish.
                //
                // UNDER THE MUTEX. The present thread writes these three fields, so
                // reading them bare would be a data race - benign on x86 for aligned
                // 32-bit words, but a measurement that races the thing it measures
                // is not worth defending. Once per native frame, twenty times a
                // second, uncontended: the cost is nothing and the read is honest.
                uint32_t wr64BpPrevPresented = 0;
                uint32_t wr64BpPrevAvailable = 0;
                uint32_t wr64BpPrevCount = 0;
                if (wr64BackpressureMeterArmed()) {
                    std::scoped_lock<std::mutex> wr64BpLock(ext.sharedResources->interpolatedMutex);
                    wr64BpPrevPresented = prevFrameCounters.presented;
                    wr64BpPrevAvailable = prevFrameCounters.available;
                    wr64BpPrevCount = prevFrameCounters.count;
                }
                int64_t wr64BpCounterWaitUs = 0;
                const bool useDifferentCounters = (lastPresentId != workload.presentId);
                if (useDifferentCounters) {
                    ext.sharedResources->interpolatedFramesIndex = ext.sharedResources->interpolatedFramesIndex ^ 1;
                    lastPresentId = workload.presentId;
                }
                // If the same set of counters is used, we wait until the presentation of its targets is finished so the targets are available to use. Waiting is ignored
                // if the frame counter has never presented anything yet, as it'll only be a valid value if the previous present event actually did something.
                else if (generateInterpolatedFrames) {
                    // Producer parked because the same counter set is still in flight
                    // on the present side. If this is where the time goes, the two
                    // threads are ping ponging on one set of counters rather than
                    // double buffering them, which is a different bug to a slow frame.
                    //
                    // Declared before the lock deliberately. Destruction runs in reverse
                    // order, so the lock is released before any report reaches the log.
                    // Declaring it after the lock would write a log line while holding
                    // interpolatedMutex, which is the one mutex the present thread is
                    // waiting on, and the measurement would become a cause of stalls.
                    //
                    // This one runs once per native frame rather than per display frame,
                    // twenty times a second, so the hot floor is affordable here and
                    // worth keeping: a short but repeated park is exactly the shape of
                    // the ping pong this site exists to detect.
                    WR64StallProbeHot counterReuseProbe("workload-counter-reuse-wait", workload.presentId);

                    // Clock read OUTSIDE the mutex, deliberately. Taking it while
                    // holding interpolatedMutex - the one mutex the present thread
                    // waits on - would make the measurement a cause of stalls, which
                    // is exactly what the stall probe comments here warn about.
                    const std::chrono::steady_clock::time_point wr64BpCounterStart =
                        WR64_DIAGNOSTIC_ENABLED ? std::chrono::steady_clock::now() : std::chrono::steady_clock::time_point{};
                    {
                        std::unique_lock<std::mutex> interpolatedLock(ext.sharedResources->interpolatedMutex);
                        ext.sharedResources->interpolatedCondition.wait(interpolatedLock, [&]() {
                            return (prevFrameCounters.presented == 0) || (prevFrameCounters.presented >= prevFrameCounters.available);
                        });
                    }
                    if (WR64_DIAGNOSTIC_ENABLED) wr64BpCounterWaitUs = std::chrono::duration_cast<std::chrono::microseconds>(
                        std::chrono::steady_clock::now() - wr64BpCounterStart).count();
                }

                InterpolatedFrameCounters &curFrameCounters = ext.sharedResources->interpolatedFrames[ext.sharedResources->interpolatedFramesIndex];
                curFrameCounters.skipped = false;
                curFrameCounters.presented = 0;
                curFrameCounters.available = 0;
                curFrameCounters.count = displayFrames;

                // Batch shape for this native frame. R4 showed the screen going dark
                // for one whole native period with nothing instrumented in the window,
                // which is the exact signature of a period that produced one frame
                // instead of nine. detail carries displayFrames in the low byte, and
                // when interpolation was declined, the reason in the next byte:
                //   1 frame matching not required        2 workload paused
                //   3 display rate not above original    4 no interpolation target found
                {
                    uint64_t batchDetail = uint64_t(displayFrames) & 0xFF;
                    if (!generateInterpolatedFrames) {
                        uint64_t declineReason = 4;
                        if (!requiresFrameMatching) {
                            declineReason = 1;
                        }
                        else if (workload.paused) {
                            declineReason = 2;
                        }
                        else if (!((workload.viOriginalRate > 0) && (workloadConfig.targetRate > workload.viOriginalRate))) {
                            declineReason = 3;
                        }

                        batchDetail |= (declineReason << 8);
                    }

                    wr64StallProbeMarkEvent("workload-batch", batchDetail);
                }

                if (wr64CadenceTraceEnabled()) {
                    WR64CadenceTraceRow traceRow;
                    traceRow.event = "workload";
                    traceRow.presentId = workload.presentId;
                    traceRow.workloadId = workload.workloadId;
                    traceRow.viOriginalRate = workload.viOriginalRate;
                    traceRow.targetRate = workloadConfig.targetRate;
                    traceRow.paused = workload.paused;
                    traceRow.requiresFrameMatching = requiresFrameMatching;
                    traceRow.displayRateAboveOriginal = (workload.viOriginalRate > 0) && (workloadConfig.targetRate > workload.viOriginalRate);
                    traceRow.targetAddress = interpolationTargetKey.address;
                    traceRow.targetWidth = interpolationTargetKey.width;
                    traceRow.targetSiz = interpolationTargetKey.siz;
                    traceRow.targetPairIndex = interpolationTargetFbPairIndex;
                    traceRow.targetFound = !interpolationTargetKey.isEmpty();
                    traceRow.generateInterpolatedFrames = generateInterpolatedFrames;
                    traceRow.displayFrames = displayFrames;
                    traceRow.transformGroupCount = uint32_t(workload.drawData.transformGroups.size());
                    for (const TransformGroup &transformGroup : workload.drawData.transformGroups) {
                        const uint32_t family = transformGroup.matrixId & 0xFFF00000;
                        traceRow.articulatedGroupCount += (family == 0x57000000);
                        traceRow.selectorGroupCount += (family == 0x57100000);
                        traceRow.courseMapGroupCount += (family == 0x57200000);
                    }
                    traceRow.counterCount = curFrameCounters.count;
                    traceRow.counterAvailable = curFrameCounters.available;
                    traceRow.counterSkipped = curFrameCounters.skipped;
                    traceRow.framebufferPairCount = workload.fbPairCount;
                    wr64WriteCadenceTrace(traceRow);
                }

                // Create as many render targets as required to store the interpolated targets.
                auto &interpolatedTargets = ext.sharedResources->interpolatedColorTargets;
                const bool usingMSAA = (ext.sharedResources->renderTargetManager.multisampling.sampleCount > 1);
                const bool usesHDR = ext.sharedResources->renderTargetManager.usesHDR;
                uint32_t requiredFrames = (usingMSAA && generateInterpolatedFrames) ? displayFrames : (displayFrames - 1);
                if ((requiredFrames > 0) && (interpolatedTargets.size() < requiredFrames)) {
                    // Grow only high water mark on the interpolated target pool. At a
                    // locked cadence this settles in the first second and never fires
                    // again, so if it fires mid race the cadence moved, which is worth
                    // knowing on its own. detail is the new count.
                    WR64StallProbe targetGrowProbe("workload-interpolated-target-grow", uint64_t(requiredFrames));
                    uint32_t previousSize = uint32_t(interpolatedTargets.size());
                    interpolatedTargets.resize(requiredFrames);
                    for (uint32_t i = previousSize; i < requiredFrames; i++) {
                        interpolatedTargets[i] = std::make_unique<RenderTarget>(interpolationTargetKey.address, Framebuffer::Type::Color, RenderMultisampling(), usesHDR);
                    }
                }
                
                const int64_t originalTimeMicro = (workload.viOriginalRate > 0) ? (1000000 / workload.viOriginalRate) : 0;
                const int64_t setupTimeMicro = workloadTimer.elapsedMicroseconds();
                const int64_t adjustedTimeWindowMicro = originalTimeMicro - setupTimeMicro;
                const int64_t maxTimePerFrameMicro = adjustedTimeWindowMicro / displayFrames;
                bool skippedFrames = false;
                bool skipWorkloadNow = false;
                uint32_t targetIndex = 0;
                uint32_t framesRendered = 0;
                int64_t renderTimeTotalMicro = 0;
                // CAMCUT-R2 truth test. Consumed once per native frame, before the
                // interpolated frames of this pair are walked. The camera guard
                // already proved it detects every cut; breaking only the viewProj
                // match changed nothing visible, because world transforms, world
                // vertices, tiles and lookAt are gated separately and interpolate
                // straight through. Forcing the weights below suppresses all of them
                // at once, and cannot upload out of a cleared vector the way marking
                // the workload maps unmapped would.
                const bool wr64CutFrame = wr64CamCutConsumePendingCut();

                // BACK-PRESSURE METER. The batch begins here; every wait inside the
                // loop is accumulated into this frame's row and wr64BackpressureEnd
                // writes it once the loop is done.
                wr64BackpressureBegin(workload.submissionFrame, displayFrames,
                    useDifferentCounters, wr64BpPrevPresented, wr64BpPrevAvailable,
                    wr64BpPrevCount, wr64BpCounterWaitUs);

                for (uint32_t frame = 0; (frame < displayFrames) && !skipWorkloadNow; frame++) {
                    // Evaluate if this frame should be skipped. Measure the current time and compare it to what frame is estimated should be have been rendered by now.
                    if (!wr64ExactInterpolatedCadence && (frame > 0) && (originalTimeMicro > 0)) {
                        const int64_t currentTimeMicro = workloadTimer.elapsedMicroseconds() - setupTimeMicro;
                        const int64_t expectedTimeMicro = frame * maxTimePerFrameMicro;
                        const int64_t measuredFrameMicro = renderTimeTotalMicro / framesRendered;
                        if ((currentTimeMicro > expectedTimeMicro) || ((currentTimeMicro + measuredFrameMicro) > adjustedTimeWindowMicro)) {
                            displayTicks += workload.viOriginalRate;
                            skippedFrames = true;
                            continue;
                        }
                    }

                    RenderTarget *overrideTarget = nullptr;
                    uint32_t overrideModifier = 0;
                    if (generateInterpolatedFrames) {
                        prevFrameWeight = std::clamp((workloadConfig.targetRate + displayTicks - logicalTicks) / float(workloadConfig.targetRate), 0.0f, 1.0f);
                        displayTicks += workload.viOriginalRate;
                        curFrameWeight = std::clamp((workloadConfig.targetRate + displayTicks - logicalTicks) / float(workloadConfig.targetRate), 0.0f, 1.0f);

                        // Override the render target.
                        if (usingMSAA || (frame > 0)) {
                            overrideTarget = interpolatedTargets[targetIndex].get();
                            overrideModifier = (targetIndex + 1);

                            if (useDifferentCounters && (prevFrameCounters.available > 0) && (targetIndex < prevFrameCounters.available)) {
                                // Back pressure from the presenter onto the producer. The
                                // two threads are locked together here, so a delay on
                                // either side arrives at the other one frame later. If a
                                // stall shows up on this line the presenter was late
                                // first and this is the echo, not the cause.
                                //
                                // Declared before the lock deliberately. Destruction runs
                                // in reverse order, so the lock is released first and any
                                // report reaches the log after the mutex is free. The
                                // other way round writes a log line while holding the one
                                // mutex the present thread is waiting on, which would turn
                                // the measurement into a cause of the thing it measures.
                                //
                                // Floor rather than the hot threshold: this site is meant
                                // to block. It sits here for most of a frame period every
                                // frame as normal back pressure, so at the 0.5 ms hot
                                // floor it would land in the ring 180 times a second and
                                // crowd out the entries a dump exists to show. Seven
                                // milliseconds is above its healthy cost and well under
                                // the 11 ms hitch threshold.
                                WR64StallProbeGate targetReuseProbe("workload-target-reuse-wait", 7.0, targetIndex);

                                // BACK-PRESSURE METER. This wait IS the thread's
                                // pacing - the cycle costs about 50 ms because of
                                // it. When the producer discarded 30 ms in one
                                // frame, these are what must have stopped blocking.
                                //
                                // Both clock reads sit OUTSIDE the lock scope, for
                                // the same reason the stall probe is declared before
                                // it: interpolatedMutex is the one mutex the present
                                // thread waits on.
                                const std::chrono::steady_clock::time_point wr64BpWaitStart =
                                    WR64_DIAGNOSTIC_ENABLED ? std::chrono::steady_clock::now() : std::chrono::steady_clock::time_point{};
                                {
                                    // Wait until the target has finished presenting if the alternate frame counter (used by the present queue) is making use of this target.
                                    std::unique_lock<std::mutex> interpolatedLock(ext.sharedResources->interpolatedMutex);
                                    ext.sharedResources->interpolatedCondition.wait(interpolatedLock, [&]() {
                                        if (!wr64ExactInterpolatedCadence) {
                                            frameReduction = frameReduction || (prevFrameCounters.presented <= targetIndex);
                                        }
                                        return prevFrameCounters.presented > targetIndex;
                                    });
                                }
                                if (WR64_DIAGNOSTIC_ENABLED) wr64BackpressureWait(std::chrono::duration_cast<std::chrono::microseconds>(
                                    std::chrono::steady_clock::now() - wr64BpWaitStart).count());
                            }

                            targetIndex++;
                        }
                    }
                    else if (workload.paused) {
                        curFrameWeight = workload.debuggerRenderer.interpolationWeight;
                        prevFrameWeight = 1.0f - curFrameWeight;
                    }
                    else {
                        prevFrameWeight = 0.0f;
                        curFrameWeight = 1.0f;
                    }

                    // Show the incoming native frame outright for every display frame
                    // of a cut pair instead of lerping into it. Both weights go to 1
                    // so the motion vectors come out zero as well - across a cut there
                    // is no motion to describe, and a prev weight of 0 would hand the
                    // renderer an enormous bogus velocity for every pixel.
                    if (wr64CutFrame && wr64CamCutSuppressEnabled()) {
                        prevFrameWeight = 1.0f;
                        curFrameWeight = 1.0f;
                    }

                    wr64WriteSprayPresentTrace(
                        workload.workloadId,
                        workload.presentId,
                        workload.viOriginalRate,
                        workloadConfig.targetRate,
                        frame,
                        displayFrames,
                        generateInterpolatedFrames,
                        logicalTicks,
                        displayTicks,
                        prevFrameWeight,
                        curFrameWeight);

                    const bool uploadExtras = (frame == 0) && workloadConfig.raytracingEnabled;
                    if (uploadExtras) {
                        BufferUploader::Upload extrasUpload = { workload.drawData.extraParams.data(), { 0, workload.drawData.extraParams.size() }, sizeof(interop::ExtraParams), RenderBufferFlag::STORAGE, {}, &workload.drawBuffers.extraParamsBuffer };
                        ext.workloadExtrasUploader->submit(ext.workloadGraphicsWorker, { extrasUpload });
                    }

                    int64_t renderTimeMicro = workloadTimer.elapsedMicroseconds();
                    {
                        // One interpolated frame. The presenter cannot show frame n
                        // until this call has finished producing it, so this is the
                        // clock the whole 180 Hz cadence actually runs on. Nine of
                        // these have to fit in a 50 ms native period, so the budget
                        // per call is about 5.5 ms. detail is the frame index inside
                        // the batch, which says whether it is the first one after
                        // matching that is expensive or a later one.
                        //
                        // Floor rather than the hot threshold, for the same reason as the
                        // back pressure wait above: this call runs 180 times a second and
                        // is supposed to take about 5.5 ms every single time. Recording
                        // all of them would recycle the ring faster than the dump window
                        // it feeds. Seven milliseconds is above the healthy cost, so this
                        // stays silent while the cadence holds and speaks up the moment
                        // one frame runs long. Nine calls at 10 ms each would all be
                        // caught, and so would one call at 45 ms.
                        WR64StallProbeGate renderFrameProbe("workload-render-frame", 7.0, frame);
                        threadRenderFrame(curFrame, prevFrame, workloadConfig, workload.debuggerRenderer, workload.debuggerCamera, curFrameWeight, prevFrameWeight, deltaTimeMs,
                            interpolationTargetKey, interpolationTargetFbPairIndex, overrideTarget, overrideModifier, velocityUploaderUsed, uploadExtras, tileInterpolationUsed, lookAtInterpolationUsed);
                    }

                    // Add total time the frame took to render.
                    renderTimeTotalMicro += workloadTimer.elapsedMicroseconds() - renderTimeMicro;

                    // After one frame is rendered, we indicate the workload has been processed so the present thread can start presenting frames as soon as it can.
                    if (frame == 0) {
                        threadAdvanceWorkloadId(workload.workloadId);
                    }

                    // For every additional frame, we increase the frames available and notify the present queue.
                    if (generateInterpolatedFrames && (usingMSAA || (frame > 0))) {
                        {
                            std::scoped_lock<std::mutex> cursorLock(cursorMutex);
                            skipWorkloadNow = !wr64ExactInterpolatedCadence &&
                                ((frame + 1) < displayFrames) && (writeCursor != threadCursor);
                        }

                        {
                            std::scoped_lock<std::mutex> managerLock(ext.sharedResources->interpolatedMutex);
                            curFrameCounters.skipped = skipWorkloadNow;
                            curFrameCounters.available++;
                        }

                        // Add the amount of display ticks that correspond to the remaining frames.
                        if (skipWorkloadNow) {
                            displayTicks += workload.viOriginalRate * (displayFrames - (frame + 1));
                        }

                        ext.sharedResources->interpolatedCondition.notify_all();
                    }

                    framesRendered++;
                }

                // BACK-PRESSURE METER. The batch is finished; write its row.
                wr64BackpressureEnd();

                // Set the skipped parameter on the frame counter if the workload wasn't skipped but some of its frames were.
                if (skippedFrames && !skipWorkloadNow) {
                    {
                        std::scoped_lock<std::mutex> managerLock(ext.sharedResources->interpolatedMutex);
                        curFrameCounters.skipped = true;
                    }

                    ext.sharedResources->interpolatedCondition.notify_all();
                }

                threadConfigurationValidate();

                if (!workload.paused) {
                    threadAdvanceBarrier();
                }

                processCursor = -1;
                workloadProfiler.end();
                workloadProfiler.log();
                workloadProfiler.reset();
            }
        }
    }
    
    void WorkloadQueue::idleThreadLoop() {
        // Beware traveler as you enter the zone of dirty driver hacks. Given N64 games are not exactly a demanding thing to render
        // nowadays for modern GPUs and due to how the plugin's cooperative multiqueue system works, it's sometimes just not possible
        // to keep the GPU busy at all times. It is often the case that the GPU might've already rendered all the frames it needed to
        // generate before the screen update event from the emulator even arrives on time.
        // 
        // Under this situation, some drivers are a bit too trigger-happy to downclock the GPU and lower the power consumption, eventually
        // resulting in very low power states that cause unwanted frametime spikes that can no longer reach the target framerate. This
        // results in visible judder during gameplay.
        //
        // This thread will take care of sending some GPU work that does nothing useful while the GPU is not actually busy generating
        // new frames. The waiting interval is close to the minimum resolution the OS provides and big enough to not cause any significant
        // delays or unwanted power consumption: it's just enough to keep the driver from downclocking to a power state level that is
        // usually intended for 2D work or video playback.
        //
        // This workaround is not required if the driver is configured to be at the "Max Performance" power state.

        Thread::setCurrentThreadName("RT64 Idle");

        const ShaderRecord &idle = ext.shaderLibrary->idle;
        RenderCommandList *commandList = ext.workloadGraphicsWorker->commandList.get();
        while (threadsRunning) {
            {
                std::unique_lock<std::mutex> idleLock(idleMutex);
                idleCondition.wait(idleLock, [&]() {
                    return idleActive || !threadsRunning;
                });
            }

            if (threadsRunning) {
                if (workerMutex.try_lock()) {
                    commandList->begin();
                    commandList->setPipeline(idle.pipeline.get());
                    commandList->setComputePipelineLayout(idle.pipelineLayout.get());
                    commandList->dispatch(1, 1, 1);
                    commandList->end();
                    ext.workloadGraphicsWorker->execute();
                    ext.workloadGraphicsWorker->wait();
                    workerMutex.unlock();
                }
                
                Thread::sleepMilliseconds(1);
            }
        }
    }
};
