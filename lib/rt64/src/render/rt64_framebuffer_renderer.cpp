//
// RT64
//

#include "../../../../include/wr64_diagnostic_policy.h"

#include "rt64_framebuffer_renderer.h"
#include "common/rt64_wr64_cloud_coverage_integration.h"
#include "../common/rt64_wr64_rt_view.h"
#include "rt64_wr64_layer_trace.h"
#include "common/rt64_wr64_motion_timing.h"
#include "common/rt64_wr64_raster_shadow_math.h"
#include "common/rt64_wr64_planar_reflection_math.h"

#include "common/rt64_wr64_hud_census.h"
// [WR64] wr64TwoPFrameIsHalfScissor / wr64TwoPFrameRenderWorkload /
// wr64TwoPFrameRenderProjection. It arrives transitively through the banner
// anchor as well; named here because this file calls it directly and a
// transitive include is not a dependency, it is a coincidence.
#include "common/rt64_wr64_2p_frame.h"
#include "common/rt64_wr64_hud_anchor.h"
#include "common/rt64_wr64_banner_anchor.h"
#include "common/rt64_wr64_gantry_anchor.h"
#include "common/rt64_wr64_buoy_identity.h"
#include "common/rt64_wr64_area_buoy_identity.h"
#include "common/rt64_wr64_matrix_slots.h"
#include "common/rt64_wr64_object_census.h"
#include "common/rt64_wr64_rect_track.h"
#include "common/rt64_wr64_celestial_identity.h"
#include "common/rt64_wr64_ultrawide.h"
#include "common/rt64_wr64_menu_identity.h"
#include "common/rt64_wr64_sun_output_trace.h"
#include "common/rt64_wr64_warmup_trace.h"
#include "common/rt64_wr64_finish_hud.h"
#include "common/rt64_wr64_ending_models.h"
#include "common/rt64_wr64_shutter.h"
#include "common/rt64_wr64_vertical_split.h"
#include "common/rt64_wr64_ui_filter.h"
#include "common/rt64_wr64_ui_filter_scope.h"
#include "common/rt64_wr64_ui_filter_diagnostics.h"
#include "common/rt64_wr64_rt_diagnostics.h"
#include "common/rt64_wr64_rt_diagnostic_options.h"
#include "common/rt64_wr64_rt_settings.h"
#include "common/rt64_wr64_rt_sky.h"
#include "common/rt64_wr64_rt_preview.h"
#include "common/rt64_wr64_rt_material.h"
#include "common/rt64_wr64_rt_nextmark.h"
#include "common/rt64_wr64_rt_beam.h"
#include "common/rt64_wr64_rt_fence_proxy.h"
#include "shared/rt64_wr64_rt_ao.h"

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <chrono>
#include <filesystem>
#include <sstream>
#include <iomanip>
#include <stdexcept>

#include "../include/rt64_extended_gbi.h"

// WR64 EDGE TRACE (diagnostic, WR64_EDGE_TRACE=1): on the aspect-expanded
// hi-res pass only (resolutionScale.x != resolutionScale.y), log one line per
// unique draw-call mapping so we can see exactly which calls can and cannot
// paint the outer columns of the presented target. Dedup capped; stdout.
namespace {
    uint64_t wr64SkyCaptureClockMs() {
        return uint64_t(std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count());
    }

    void wr64SkyCaptureWords(std::ostream &stream, const void *data, size_t count) {
        stream << '[';
        for (size_t i = 0; i < count; ++i) {
            uint32_t word = 0;
            std::memcpy(&word, static_cast<const uint8_t *>(data) + i * 4, 4);
            if (i) stream << ',';
            stream << word;
        }
        stream << ']';
    }

    bool wr64EdgeTraceEnabled() {
        if (!WR64_DIAGNOSTIC_ENABLED) return false;
        static const bool enabled = []() {
            const char *value = std::getenv("WR64_EDGE_TRACE");
            return (value != nullptr) && (value[0] == '1') && (value[1] == '\0');
        }();
        return enabled;
    }

    bool wr64EdgeTraceSeen(uint64_t key) {
        static std::set<uint64_t> seen;
        if (seen.size() >= 4096) {
            return true;
        }
        return !seen.insert(key).second;
    }

    uint64_t wr64EdgeHash(const char *tag, long a, long b, long c, long d, long e, long f) {
        uint64_t h = 1469598103934665603ull;
        auto mix = [&h](uint64_t v) { h ^= v; h *= 1099511628211ull; };
        for (const char *p = tag; *p != '\0'; p++) { mix(uint64_t(uint8_t(*p))); }
        mix(uint64_t(a)); mix(uint64_t(b)); mix(uint64_t(c));
        mix(uint64_t(d)); mix(uint64_t(e)); mix(uint64_t(f));
        return h;
    }

    // EDGE-TRACE-R2. The six-argument key above was written for the widescreen
    // work and mixes HORIZONTAL edges only. That is why the 2P measurement came
    // back with one perspective row instead of two: player 1 and player 2 differ
    // only vertically, so they hash identically and the second one is swallowed
    // as a duplicate. A question about vertical layout needs every edge in the
    // key, and the raw viewport rather than the clip rect derived from it.
    template <typename... Args>
    uint64_t wr64EdgeHashN(const char *tag, Args... args) {
        uint64_t h = 1469598103934665603ull;
        auto mix = [&h](uint64_t v) { h ^= v; h *= 1099511628211ull; };
        for (const char *p = tag; *p != '\0'; p++) { mix(uint64_t(uint8_t(*p))); }
        const long values[] = { long(args)... };
        for (long v : values) { mix(uint64_t(v)); }
        return h;
    }

    // WR64_RECT_EDGE_SNAP (EXP-019): the IPS-native game authors "full frame"
    // rects and scissors inclusively as (0,0)-(423,239). RT64 treats those
    // bounds exclusively, so such fills/texrects cover one native pixel less
    // than the frame, and such call scissors CLIP every layer under them
    // (triangles included) one native pixel short: x3.018868 that is ~3px of
    // stale/underlying pixels at the right and bottom edges (the menu strips).
    // On a real TV the missing pixel sat inside overscan; on a borderless
    // display it is visible. Under the gate, any fill rect, texrect, or call
    // scissor edge within one native pixel of the framebuffer-pair scissor
    // edge snaps onto that edge. One-pixel tolerance only: interior elements
    // are never touched.
    // ★ VALIDATED FIX, COMPILED IN. No environment variable.
    bool wr64RectEdgeSnapEnabled() {
        return true;
    }

    RT64::FixedRect wr64SnapRectToScissor(RT64::FixedRect rect, const RT64::FixedRect &fbScissor) {
        const int32_t Tolerance = 8; // two native pixels in 10.2 fixed point.
        // EXP-026: the decoded game rects sit one fixed-point unit below the
        // nominal value (e.g. a "(0,0)-(423,239)" fill stores lrx=1691, lry=955),
        // so the original one-pixel window missed them by a single unit. Verified
        // by EXP-025 trace: the steady menu background texrect (0,0)-(423,241) and
        // black fill (0,0)-(423,239) both escaped the snap and produce the 3px
        // right/bottom content edge.
        if (!rect.isNull() && !fbScissor.isNull()) {
            if ((rect.lrx < fbScissor.lrx) && (rect.lrx >= fbScissor.lrx - Tolerance)) { rect.lrx = fbScissor.lrx; }
            if ((rect.lry < fbScissor.lry) && (rect.lry >= fbScissor.lry - Tolerance)) { rect.lry = fbScissor.lry; }
            if ((rect.ulx > fbScissor.ulx) && (rect.ulx <= fbScissor.ulx + Tolerance)) { rect.ulx = fbScissor.ulx; }
            if ((rect.uly > fbScissor.uly) && (rect.uly <= fbScissor.uly + Tolerance)) { rect.uly = fbScissor.uly; }
        }
        return rect;
    }
}

#include "common/rt64_elapsed_timer.h"
#include "common/rt64_math.h"
#include "common/rt64_wr64_stall_probe.h"
#include "hle/rt64_color_converter.h"
#include "gbi/rt64_f3d.h"
#include "shared/rt64_framebuffer_params.h"
#include "shared/rt64_raster_params.h"

#include "rt64_descriptor_sets.h"
#include "rt64_render_worker.h"

// TODO: Move to shared.

namespace interop {
    struct BicubicCB {
        uint2 InputResolution;
        uint2 OutputResolution;
    };

    struct HistogramAverageCB {
        uint pixelCount;
        float minLuminance;
        float luminanceRange;
        float timeDelta;
        float tau;
    };

    struct HistogramSetCB {
        float luminanceValue;
    };

    struct LuminanceHistogramCB {
        uint inputWidth;
        uint inputHeight;
        float minLuminance;
        float oneOverLuminanceRange;
    };

    struct TextureCB {
        uint2 TextureSize;
        float2 TexelSize;
    };
};

namespace RT64 {
    // Helper functions.
    
    RenderRect convertFixedRect(FixedRect rect, hlslpp::float2 resScale, int32_t fbWidth, float aspectRatioScale, float extOriginPercentage, int32_t horizontalMisalignment, uint16_t leftOrigin, uint16_t rightOrigin) {
        if (!rect.isNull()) {
            auto computeOrigin = [=](uint16_t origin) {
                if (origin < G_EX_ORIGIN_NONE) {
                    return std::lround(((fbWidth * origin) / G_EX_ORIGIN_RIGHT) * extOriginPercentage + (fbWidth / 2) * (1.0f - extOriginPercentage));
                }
                else {
                    return fbWidth / 2L;
                }
            };

            auto correctMisalignment = [=](int32_t coord, uint16_t origin) {
                if (origin < G_EX_ORIGIN_NONE) {
                    return int32_t(coord - (coord % std::lround(resScale[1]))) - horizontalMisalignment;
                }
                else {
                    return coord;
                }
            };

            int32_t left = static_cast<int32_t>(std::floor((computeOrigin(leftOrigin) + (rect.left(true) - computeOrigin(leftOrigin)) * aspectRatioScale) * resScale.x));
            int32_t right = static_cast<int32_t>(std::ceil((computeOrigin(rightOrigin) + (rect.right(true) - computeOrigin(rightOrigin)) * aspectRatioScale) * resScale.x));
            int32_t top = lround(rect.top(true) * resScale.y);
            int32_t bottom = lround(rect.bottom(true) * resScale.y);
            left = correctMisalignment(left, leftOrigin);
            right = correctMisalignment(right, rightOrigin);
            return RenderRect(left, top, right, bottom);
        }
        else {
            return RenderRect(0, 0, 0, 0);
        }
    }
    
    RenderViewport convertViewportRect(FixedRect rect, hlslpp::float2 resScale, int32_t fbWidth, float aspectRatioScale, float extOriginPercentage, float horizontalMisalignment, uint16_t leftOrigin, uint16_t rightOrigin, bool preserveHorizontalSubpixels = false, bool preserveVerticalSubpixels = false) {
        auto computeOrigin = [=](uint16_t origin) {
            if (origin < G_EX_ORIGIN_NONE) {
                return ((fbWidth * origin) / G_EX_ORIGIN_RIGHT) * extOriginPercentage + (fbWidth / 2) * (1.0f - extOriginPercentage);
            }
            else {
                return float(fbWidth) / 2;
            }
        };
        
        auto correctMisalignment = [=](float coord, uint16_t origin) {
            if (origin < G_EX_ORIGIN_NONE) {
                return (coord - std::fmod(coord, resScale[1])) - horizontalMisalignment;
            }
            else {
                return coord;
            }
        };
        
        // Interpolated warm-up text carries quarter-pixel horizontal motion.
        // Native-pixel ceiling here discarded three of every four positions,
        // and independently rounding the edges also made its width fluctuate.
        const float nativeLeft = preserveHorizontalSubpixels ? rect.ulx * 0.25f : float(rect.left(true));
        const float nativeRight = preserveHorizontalSubpixels ? rect.lrx * 0.25f : float(rect.right(true));
        float left = (computeOrigin(leftOrigin) + (nativeLeft - computeOrigin(leftOrigin)) * aspectRatioScale) * resScale.x;
        float right = (computeOrigin(rightOrigin) + (nativeRight - computeOrigin(rightOrigin)) * aspectRatioScale) * resScale.x;
        if (!preserveHorizontalSubpixels) {
            left = std::round(left);
            right = std::round(right);
        }
        float top = preserveVerticalSubpixels ? rect.uly * 0.25f * float(resScale.y) : std::round(rect.top(true) * resScale.y);
        float bottom = preserveVerticalSubpixels ? rect.lry * 0.25f * float(resScale.y) : std::round(rect.bottom(true) * resScale.y);
        left = correctMisalignment(left, leftOrigin);
        right = correctMisalignment(right, rightOrigin);
        return RenderViewport(left, top, right - left, bottom - top);
    }

    hlslpp::float3 viewPositionFrom(hlslpp::float4x4 viewI) {
        return viewI[3].xyz;
    }

    hlslpp::float3 viewDirectionFrom(hlslpp::float4x4 viewI) {
        return hlslpp::normalize(viewI[2].xyz);
    }

    RenderColor toRenderColor(hlslpp::float4 v) {
        return { v.x, v.y, v.z, v.w };
    }

    static RenderRect viewportScissorIntersection(const RenderViewport &viewport, const RenderRect &scissor) {
        return RenderRect{
            std::max(static_cast<int32_t>(std::floor(viewport.x)), scissor.left),
            std::max(static_cast<int32_t>(std::floor(viewport.y)), scissor.top),
            std::min(static_cast<int32_t>(std::ceil(viewport.x + viewport.width)), scissor.right),
            std::min(static_cast<int32_t>(std::ceil(viewport.y + viewport.height)), scissor.bottom)
        };
    }

    // RasterScene

    RasterScene::RasterScene() { }

    // FramebufferRenderer
    
    FramebufferRenderer::FramebufferRenderer(RenderWorker *worker, bool rtSupport, UserConfiguration::GraphicsAPI graphicsAPI, const ShaderLibrary *shaderLibrary) {
        assert(worker != nullptr);

        this->shaderLibrary = shaderLibrary;
        // Expose ray-traced enhancements only on Direct3D 12. Retained settings must
        // not initialize the unsupported Vulkan ray-tracing path.
        wr64RTSupported = graphicsAPI == UserConfiguration::GraphicsAPI::D3D12 &&
            Wr64RTWaterPipelines::supported(worker->device, graphicsAPI);
        wr64RasterSkySupported = graphicsAPI == UserConfiguration::GraphicsAPI::D3D12;
        wr64RTShaderFormat = graphicsAPI == UserConfiguration::GraphicsAPI::Vulkan ?
            RenderShaderFormat::SPIRV : RenderShaderFormat::DXIL;
        if (graphicsAPI == UserConfiguration::GraphicsAPI::D3D12 && wr64D3D12DiagnosticSkyDisabled(true)) {
            { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr, "[d3d12-diagnostic] sky_reflections_disabled=1 backend=D3D12 path=basic_water_shader scope=process settings_unchanged=1\n"); }
            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stderr); }
        }

        frameParams.frameCount = 0;
        frameParams.viewUbershaders = false;
        frameParams.ditherNoiseStrength = 1.0f;

        shaderUploader = std::make_unique<BufferUploader>(worker->device);
        descCommonSet = std::make_unique<FramebufferRendererDescriptorCommonSet>(shaderLibrary->samplerLibrary,
            worker->device->getCapabilities().raytracing || worker->device->getCapabilities().rayQueries, worker->device);
        for (auto &view : wr64RTViews) {
            view.descriptor = std::make_unique<FramebufferRendererDescriptorCommonSet>(shaderLibrary->samplerLibrary,
                worker->device->getCapabilities().raytracing || worker->device->getCapabilities().rayQueries, worker->device);
        }

#   if RT_ENABLED
        if (rtSupport) {
            this->rtSupport = rtSupport;
            rtResources = std::make_unique<RaytracingResources>(worker, graphicsAPI);
    }
#   endif
    }

    FramebufferRenderer::~FramebufferRenderer() {
        // The workload owner destroys this renderer before its device/layout.
        wr64RTWaterPipelines.waitForPending();
        wr64RasterSkyPipelines.waitForPending();
        wr64RasterShadowPipelines.waitForPending();
        wr64RasterReflectionPipelines.waitForPending();
        wr64RTWorldShadowPipelines.waitForPending();
        wr64MotionBlur.waitForPending();
        for (auto &view : wr64RTViews) if (view.skyCaptureFile) std::fclose(view.skyCaptureFile);
        dummyColorTargetView.reset();
        dummyDepthTargetView.reset();
        dummyColorTarget.reset();
        dummyDepthTarget.reset();
    }

    void FramebufferRenderer::resetWr64RTPipelines() {
        // Only called after both queues are idle. Join outstanding driver work
        // and discard layout-keyed entries before the old layout is destroyed.
        wr64RTWaterPipelines.reset();
        wr64RasterSkyPipelines.reset();
        wr64RasterShadowPipelines.reset();
        wr64RasterReflectionPipelines.reset();
        wr64RTWorldShadowPipelines.reset();
        wr64MotionBlur.reset();
        rendererPipelineLayout = nullptr;
    }

    static Wr64RasterShadowWaterMode wr64ShadowWaterMode(bool objects, bool raySky, bool cachedSky) {
        if (objects) return cachedSky ? Wr64RasterShadowWaterMode::RTObjectsRasterSky :
            raySky ? Wr64RasterShadowWaterMode::RTSky : Wr64RasterShadowWaterMode::RTObjects;
        return cachedSky ? Wr64RasterShadowWaterMode::RasterSky :
            raySky ? Wr64RasterShadowWaterMode::RTSkyOnly : Wr64RasterShadowWaterMode::Native;
    }

    Wr64RTPrewarmStatus FramebufferRenderer::prewarmWr64RTPipelines(RenderDevice *device,
        const RenderPipelineLayout *layout, const RenderMultisampling &multisampling,
        bool nativeSky, bool worldShadows, bool motionBlur, bool objectReflections, bool cachedSky, bool rasterShadows,
        bool rasterReflections) {
        if ((objectReflections || nativeSky) && !wr64RTSupported) {
            objectReflections = false;
            nativeSky = false;
        }
        nativeSky = nativeSky && !wr64D3D12DiagnosticSkyDisabled(wr64RTShaderFormat == RenderShaderFormat::DXIL);
        bool pending = false, failed = false;
        auto collect = [&](Wr64RTPrewarmStatus status) {
            pending |= status == Wr64RTPrewarmStatus::Pending;
            failed |= status == Wr64RTPrewarmStatus::Failed;
        };
        // Prepare both water programs when sky is selected: the stable one is
        // still used by native scenes without a usable sky capture.
        if (wr64RasterSkySupported && (cachedSky || (nativeSky && !objectReflections))) {
            const auto mode = cachedSky ? (objectReflections ? Wr64SkyWaterMode::CachedSkyWithRTObjects : Wr64SkyWaterMode::RasterOnly)
                : Wr64SkyWaterMode::RayTracedSkyOnly;
            collect(wr64RasterSkyPipelines.prepare(device, layout, multisampling,
                shaderLibrary->usesHDR, true, mode) ? wr64RasterSkyPipelines.prewarm() : Wr64RTPrewarmStatus::Failed);
        }
        else if (objectReflections) {
            for (uint32_t sky = 0; sky <= uint32_t(nativeSky); ++sky) {
                collect(wr64RTWaterPipelines.prepare(device, layout, multisampling,
                    shaderLibrary->usesHDR, sky != 0, true, wr64RTShaderFormat) ? wr64RTWaterPipelines.prewarm() : Wr64RTPrewarmStatus::Failed);
            }
        }
        if (worldShadows && objectReflections) {
            collect(wr64RTWorldShadowPipelines.prepare(device, layout, multisampling,
                shaderLibrary->usesHDR, true, wr64RTShaderFormat) ? wr64RTWorldShadowPipelines.prewarm() : Wr64RTPrewarmStatus::Failed);
        }
        if (rasterShadows && wr64RasterSkySupported) {
            const auto mode = wr64ShadowWaterMode(objectReflections, nativeSky, cachedSky);
            collect(wr64RasterShadowPipelines.prepare(device, layout, multisampling,
                shaderLibrary->usesHDR, true, mode) ? wr64RasterShadowPipelines.prewarm() : Wr64RTPrewarmStatus::Failed);
        }
        if (motionBlur) collect(wr64MotionBlur.prewarm(device, layout, multisampling, shaderLibrary->usesHDR));
        if (rasterReflections && wr64RasterSkySupported) {
            const auto sky = cachedSky ? Wr64RasterReflectionSkyMode::RasterSky :
                nativeSky ? Wr64RasterReflectionSkyMode::RTSkyOnly : Wr64RasterReflectionSkyMode::SkyOff;
            collect(wr64RasterReflectionPipelines.prepare(device, layout, multisampling,
                shaderLibrary->usesHDR, true, sky, rasterShadows)
                ? wr64RasterReflectionPipelines.prewarm() : Wr64RTPrewarmStatus::Failed);
        }
        return failed ? Wr64RTPrewarmStatus::Failed :
            (pending ? Wr64RTPrewarmStatus::Pending : Wr64RTPrewarmStatus::Ready);
    }
    
    void FramebufferRenderer::resetFramebuffers(RenderWorker *worker, bool ubershadersVisible, float ditherNoiseStrength, const RenderMultisampling &multisampling) {
        const auto wr64Quality = getWr64RTSettings();
        wr64RasterSkyStrength = float(std::clamp(wr64Quality.rasterSkyStrengthPercent, 100u, 200u)) / 100.0f;
        for (auto &view : wr64RTViews) {
            auto *rt = &view;
            rt->projection = UINT32_MAX;
            rt->nativeRaceView = 0;
            rt->params.enabled = 0;
            rt->params.strength = 1.0f;
            rt->prepared = false;
            rt->scopeSeen = false;
            rt->endingWorldOnly = false;
            rt->skyScopeSeen = false;
            rt->rasterSky = false;
            rt->traceReflections = false;
            rt->raySkyOnly = false;
            rt->rasterShadows = false;
            rt->rasterReflections = false;
            rt->reflectionCaptureRecorded = false;
            rt->reflectionPlaneValid = false;
            rt->reflectionPlaneY = 0.0f;
            rt->rasterReflectionParams = {};
            rt->rasterReflectors.clear();
            rt->shadowMapRecorded = false;
            rt->rasterShadowRacers = 0;
            rt->rasterShadowParams = {};
            rt->rasterShadowCasters.clear();
            rt->framebuffer = UINT32_MAX;
            rt->skyMatches = 0;
            rt->skyCandidates = 0;
            rt->backdropMatches = 0;
            rt->backdropCandidates = 0;
            if (WR64_DIAGNOSTIC_ENABLED) {
            rt->skyCaptureDiagnostic = {};
            ++rt->skyCapturePresent;
            rt->skyCaptureArmed = false;
            rt->skyCaptureCopied = false;
            rt->skyCaptureDrawData = nullptr;
            rt->skyCaptureLayers = {};
            const char *skyCapture = WR64_DIAGNOSTIC_ENABLED ? std::getenv("WR64_RT_SKY_CAPTURE") : nullptr;
            rt->skyCaptureRequested = WR64_DIAGNOSTIC_ENABLED && skyCapture && skyCapture[0] == '1' && skyCapture[1] == '\0' &&
                !rt->skyCaptureFailed;
            if (rt->skyCaptureStartMs && wr64SkyCaptureClockMs() - rt->skyCaptureStartMs >= 30000)
                rt->skyCaptureRequested = false;
            }
            rt->params.sky = { 0, 0, 0, 0 };
            rt->params.skyCamera = { 0.0f, 0.0f, 0.0f, 0.0f };
            rt->params.skyCloudParams = { 0.0f, 0.0f, 0.0f, 0.0f };
            rt->params.skyBackdrop = { 0, 0, 0, 0 };
            rt->params.skyBackdropCamera = { 0.0f, 0.0f, 0.0f, 0.0f };
            rt->params.celestialInfo = { 0, 0, 0, 0 };
            rt->params.shadowLight = {};
            rt->params.shadowOptions = {};
            rt->params.aoOptions = {};
            // One atomic frontend snapshot for this renderer setup. Quality changes
            // only the ray budget; native raster resolution and sky direction remain
            // unchanged, and the maximum values reproduce the validated rendering.
            rt->params.qualityOptions = { 300.0f * wr64Quality.reflectionDistancePercent,
                float(wr64Quality.shadowSamples), 0.0f, 0.0f };
            rt->params.sceneOptions = {};
            rt->actorBounds = {};
            for (uint32_t racer = 0; racer < 4; ++racer) {
                rt->params.actorShadowBoundsMin[racer] = {};
                rt->params.actorShadowBoundsMax[racer] = {};
            }
            rt->geometry.clear();
            rt->fenceProxies.clear();
            rt->waterDraws.clear();
            rt->nativeWaterPipelines.clear();
            rt->shoreDraws.clear();
            rt->aoOnlyDraws.clear();
            rt->nativeShorePipelines.clear();
            rt->arrowShadowExclusions = 0;
            rt->letterShadowExclusions = 0;
            rt->shoreSelected = 0;
            rt->aoOnlySelected = 0;
            rt->nativeShadowDraws.clear();
            rt->racerShadowCasters = 0;
            rt->shadowWaterSelected = false;
            rt->waterIndices.clear();
            rt->waterAdjacency = {};
            rt->params.smoothNormals = 0;
            rt->scene.reset();
        }
        wr64RTDrawViews.clear();
        wr64MotionDrawParams.clear();
        wr64MotionActors.clear();
        wr64MotionBoundary = UINT32_MAX;
        wr64MotionOrderRejected = false;
        wr64MotionPrepared = false;
        wr64MotionTimeScale = 1.0f;
        wr64MotionShutter = 0.0f;
        wr64MotionDiagnostic = {};
        const char *motionExperiment = std::getenv("WR64_OBJECT_MOTION_BLUR_EXPERIMENT");
        wr64MotionDiagnostic.enabled = wr64RTDevelopmentEffectsAllowed() &&
            motionExperiment && motionExperiment[0] == '1' && motionExperiment[1] == '\0';
        wr64MotionDiagnostic.reason = wr64MotionDiagnostic.enabled ? "no-actors" : "disabled";
        instanceDrawCallVector.clear();
        hitGroupVector.clear();
        renderIndicesVector.clear();
        rspSmoothNormalVector.clear();
        frameParams.viewUbershaders = ubershadersVisible;
        frameParams.ditherNoiseStrength = ditherNoiseStrength;
        framebufferCount = 0;

        // Create dummy color target if it hasn't been created yet.
        if (dummyColorTarget == nullptr) {
            RenderTextureDesc dummyColorDesc = RenderTextureDesc::ColorTarget(4, 4, RenderTarget::colorBufferFormat(shaderLibrary->usesHDR), multisampling);
            dummyColorTarget = worker->device->createTexture(dummyColorDesc);
            dummyColorTarget->setName("Framebuffer Renderer Color Dummy");
            dummyColorTargetView = dummyColorTarget->createTextureView(RenderTextureViewDesc::Texture2D(dummyColorDesc.format));
            dummyColorTargetTransitioned = false;
        }

        // Create dummy depth target if it hasn't been created yet.
        if (dummyDepthTarget == nullptr) {
            RenderTextureDesc dummyDepthDesc = RenderTextureDesc::DepthTarget(4, 4, RenderFormat::D32_FLOAT, multisampling);
            dummyDepthTarget = worker->device->createTexture(dummyDepthDesc);
            dummyDepthTarget->setName("Framebuffer Renderer Depth Dummy");
            dummyDepthTargetView = dummyDepthTarget->createTextureView(RenderTextureViewDesc::Texture2D(dummyDepthDesc.format));
            dummyDepthTargetTransitioned = false;
        }
    }

#if RT_ENABLED
    void FramebufferRenderer::resetRaytracing(RaytracingShaderCache *rtShaderCache, const RenderTexture *blueNoiseTexture) {
        assert(rtResources != nullptr);
        assert(rtShaderCache != nullptr);
        assert(blueNoiseTexture != nullptr);

        const int32_t stateIndex = rtShaderCache->getActiveState();
        rtState = &rtShaderCache->states[stateIndex];
        rtPipelineLayout = rtShaderCache->pipelineLayout.get();
        rtResources->resetBottomLevelAS();

        this->blueNoiseTexture = blueNoiseTexture;
    }
#endif

    void FramebufferRenderer::updateTextureCache(TextureCache *textureCache) {
        // Takes the same mutex the upload thread holds across a whole cohort commit,
        // and then copies four vectors whose length is the entire texture cache while
        // still holding it. Both halves of that cost grow with the cache.
        WR64StallProbeHot cacheProbe("fb-texture-cache-copy");
        const std::unique_lock<std::mutex> textureMapLock(textureCache->textureMapMutex);
        textureCacheVersions = textureCache->textureMap.versions;
        textureCacheTextures = textureCache->textureMap.textures;
        textureCacheTextureReplacements = textureCache->textureMap.textureReplacements;
        textureCacheFreeSpaces = textureCache->textureMap.freeSpaces;
        textureCacheSize = static_cast<uint32_t>(textureCacheTextures.size());
        textureCacheGlobalVersion = textureCache->textureMap.globalVersion;
        textureCacheReplacementMapEnabled = textureCache->textureMap.replacementMapEnabled;
        dynamicTextureViewVector.clear();
        dynamicTextureBarrierVector.clear();
        cacheProbe.setDetail(uint64_t(textureCacheSize));
    }

    void FramebufferRenderer::createGPUTiles(const DrawCallTile *callTiles, uint32_t callTileCount, interop::GPUTile *dstGPUTiles, const FramebufferManager *fbManager, 
        TextureCache *textureCache, uint64_t submissionFrame, uint32_t diagnosticPart)
    {
        const bool diagnose = wr64UiFilterDiagnosticEnabled();
        const uint32_t selectedMode = diagnose ? getWr64UiFilter() : 0;
        static thread_local Wr64UiFilterDiagnosticBudget candidateBudget, knownUiBudget;
        const bool summarize = diagnose && candidateBudget.observe(submissionFrame, selectedMode, diagnosticPart);
        if (diagnose) knownUiBudget.observe(submissionFrame, selectedMode);
        size_t created = 0, mappingMisses = 0, knownUiCount = 0, knownUiFlagBlocks = 0;
        auto knownUiIdentity = [](const DrawCallTile &tile) {
            // Priority for diagnostics only; draw eligibility still requires
            // the real projection, modes and other guards in the classifier.
            const uint64_t hash = tile.tmemHashOrID;
            const uint32_t width = tile.sampleWidth, height = tile.sampleHeight;
            if ((width == 24 && height == 20 && wr64UiFontContains(Wr64UiMainFont, hash)) ||
                (width == 8 && height == 8 && wr64UiFontContains(Wr64UiSmallFont, hash)) ||
                (width == 16 && height == 12 && wr64UiFontContains(Wr64UiSelectFont, hash))) return true;
            for (const auto &bitmap : Wr64UiMainMenuBitmaps)
                if (hash == bitmap.tmemHash && width == bitmap.width && height == bitmap.height) return true;
            if (wr64UiBitmapContains(Wr64UiWatercraftBitmaps, hash, width, height) ||
                wr64UiBitmapContains(Wr64UiCourseBitmaps, hash, width, height)) return true;
            for (const auto &widget : wr64HudAnchorWidgets())
                if (widget.name != "opening_logo" && widget.tmemHash != 0 && hash == widget.tmemHash) return true;
            return (hash == 0x342EB798B5720B9AULL && width == 176 && height == 18) ||
                (hash == 0x41F74C7752C03ACDULL && width == 32 && height == 20) ||
                (hash == 0x13E7FF64CEB499C2ULL && width == 36 && height == 24) ||
                (hash == 0x1DF6E18FA3F51003ULL && width == 144 && height == 20) ||
                (hash == 0x90C84829FC9E5904ULL && width == 128 && height == 20);
        };
        for (uint32_t i = 0; i < callTileCount; i++) {
            const DrawCallTile &callTile = callTiles[i];
            if (!callTile.valid) {
                continue;
            }
            
            interop::GPUTile &gpuTile = dstGPUTiles[i];
            bool gpuFieldsAssigned = false, textureDimensionsAvailable = false;
            if (callTile.tileCopyUsed) {
                const auto &it = fbManager->tileCopies.find(callTile.tmemHashOrID);
                if (it != fbManager->tileCopies.end()) {
                    const FramebufferManager::TileCopy &tileCopy = it->second;
                    gpuTile.tcScale.x = static_cast<float>(tileCopy.usedWidth) / static_cast<float>(callTile.tileCopyWidth);
                    gpuTile.tcScale.y = static_cast<float>(tileCopy.usedHeight) / static_cast<float>(callTile.tileCopyHeight);
                    gpuTile.ulScale.x = tileCopy.ulScaleS ? gpuTile.tcScale.x : 1.0f;
                    gpuTile.ulScale.y = tileCopy.ulScaleT ? gpuTile.tcScale.y : 1.0f;
                    gpuTile.texelShift = tileCopy.texelShift;
                    gpuTile.texelMask = tileCopy.texelMask;
                    gpuTile.textureIndex = getTextureIndex(tileCopy);
                    gpuTile.textureDimensions = interop::float3(float(tileCopy.textureWidth), float(tileCopy.textureHeight), 1.0f);
                    gpuTile.flags.alphaIsCvg = !callTile.reinterpretTile;
                    gpuTile.flags.highRes = true;
                    gpuTile.flags.fromCopy = true;
                    gpuTile.flags.rawTMEM = false;
                    gpuTile.flags.hasMipmaps = false;
                    gpuFieldsAssigned = textureDimensionsAvailable = true;
                }
            }
            else {
                // Retrieve the texture from the cache or use a blank texture if not found.
                uint32_t textureIndex = 0;
                bool textureReplaced = false;
                bool hasMipmaps = false;
                bool shiftedByHalf = false;
                textureDimensionsAvailable = textureCache->useTexture(callTile.tmemHashOrID, submissionFrame, textureIndex, gpuTile.tcScale, gpuTile.textureDimensions, textureReplaced, hasMipmaps, shiftedByHalf);

                // Describe the GPU tile for a regular texture.
                gpuTile.ulScale.x = gpuTile.tcScale.x;
                gpuTile.ulScale.y = gpuTile.tcScale.y;
                gpuTile.texelShift = { 0, 0 };
                gpuTile.texelMask = { UINT_MAX, UINT_MAX };
                gpuTile.textureIndex = textureIndex;
                gpuTile.flags.alphaIsCvg = false;
                gpuTile.flags.highRes = textureReplaced;
                gpuTile.flags.fromCopy = false;
                gpuTile.flags.rawTMEM = !textureReplaced && callTile.rawTMEM;
                gpuTile.flags.hasMipmaps = hasMipmaps;
                gpuTile.flags.shiftedByHalf = shiftedByHalf;
                gpuFieldsAssigned = true;
            }
            if (diagnose) {
                ++created;
                mappingMisses += !textureDimensionsAvailable;
                const bool known = knownUiIdentity(callTile);
                knownUiCount += known;
                // Read only fields assigned above. In particular, a missing
                // copy mapping assigns nothing and a native cache miss leaves
                // textureDimensions unchanged. Neither is safe to inspect.
                const uint32_t flags = gpuFieldsAssigned
                    ? (unsigned(gpuTile.flags.alphaIsCvg) | (unsigned(gpuTile.flags.highRes) << 1) |
                       (unsigned(gpuTile.flags.fromCopy) << 2) | (unsigned(gpuTile.flags.rawTMEM) << 3) |
                       (unsigned(gpuTile.flags.hasMipmaps) << 4)) : 0;
                const bool flagsAllow = gpuFieldsAssigned && flags == 0;
                knownUiFlagBlocks += known && !flagsAllow;
                const bool firstCandidate = candidateBudget.firstHash(callTile.tmemHashOrID);
                const bool firstKnown = known && knownUiBudget.firstHash(callTile.tmemHashOrID);
                if (firstCandidate || firstKnown) {
                    char details[768];
                    std::snprintf(details, sizeof(details),
                        "frame=%llu selected_current=%u tile_batch_index=%u hash=%016llX ui_identity=%u valid=1 raw=%u copy=%u sample=%ux%u gpu_fields_assigned=%u mapping_found=%u gpu_filter_flags=%02X gpu_flags_allow=%u texture_index=%u dimensions_available=%u dimensions=%gx%gx%g tcScale=%g,%g",
                        (unsigned long long)submissionFrame, selectedMode, i,
                        (unsigned long long)callTile.tmemHashOrID, unsigned(known),
                        unsigned(callTile.rawTMEM), unsigned(callTile.tileCopyUsed),
                        unsigned(callTile.sampleWidth), unsigned(callTile.sampleHeight),
                        unsigned(gpuFieldsAssigned), unsigned(textureDimensionsAvailable), flags,
                        unsigned(flagsAllow), gpuFieldsAssigned ? gpuTile.textureIndex : 0,
                        unsigned(textureDimensionsAvailable),
                        textureDimensionsAvailable ? double(gpuTile.textureDimensions.x) : 0.0,
                        textureDimensionsAvailable ? double(gpuTile.textureDimensions.y) : 0.0,
                        textureDimensionsAvailable ? double(gpuTile.textureDimensions.z) : 0.0,
                        gpuFieldsAssigned ? double(gpuTile.tcScale.x) : 0.0,
                        gpuFieldsAssigned ? double(gpuTile.tcScale.y) : 0.0);
                    wr64UiFilterDiagnostic(firstKnown ? "tile-created-ui" : "tile-created-candidate", details);
                }
            }
        }
        if (summarize) {
            char details[320];
            std::snprintf(details, sizeof(details),
                "frame=%llu selected_current=%u part=%u tile_batch_count=%u valid=%zu mapping_misses=%zu ui_identities=%zu ui_gpu_flag_blocks=%zu",
                (unsigned long long)submissionFrame, selectedMode, diagnosticPart, callTileCount,
                created, mappingMisses, knownUiCount, knownUiFlagBlocks);
            wr64UiFilterDiagnostic("tile-created-summary", details);
        }
    }

    uint32_t FramebufferRenderer::getDestinationIndex() {
        uint32_t dstIndex;
        if (textureCacheFreeSpaces.empty()) {
            dstIndex = textureCacheSize++;
        }
        else {
            dstIndex = textureCacheFreeSpaces.back();
            textureCacheFreeSpaces.pop_back();
        }

        return dstIndex;
    }
    
    uint32_t FramebufferRenderer::getTextureIndex(RenderTarget *renderTarget) {
        assert(renderTarget != nullptr);

        uint32_t dstIndex = getDestinationIndex();
        dynamicTextureViewVector.emplace_back(DynamicTextureView{ renderTarget->getResolvedTexture(), dstIndex, renderTarget->getResolvedTextureView()});
        return dstIndex;
    }
    
    uint32_t FramebufferRenderer::getTextureIndex(const FramebufferManager::TileCopy &tileCopy) {
        assert(tileCopy.texture != nullptr);

        uint32_t dstIndex = getDestinationIndex();
        dynamicTextureViewVector.emplace_back(DynamicTextureView{ tileCopy.texture.get(), dstIndex, nullptr });
        dynamicTextureBarrierVector.emplace_back(RenderTextureBarrier(tileCopy.texture.get(), RenderTextureLayout::SHADER_READ));
        return dstIndex;
    }
    
    void FramebufferRenderer::updateShaderDescriptorSet(RenderWorker *worker, const DrawBuffers *drawBuffers, const OutputBuffers *outputBuffers, const bool raytracingEnabled) {
        assert(worker != nullptr);
        assert(drawBuffers != nullptr);
        
        const bool createSet = (descTextureSet == nullptr) || (descTextureSet->textureCacheSize < (textureCacheSize + 1));
        if (createSet) {
            // Grow only bindless heap. Reallocating it also throws away every version
            // stamp below, which forces a full rewrite of every descriptor in the same
            // call. Rare by design, expensive when it happens, so it is worth naming.
            WR64StallProbe createProbe("fb-descriptor-set-create", uint64_t(textureCacheSize));
            descTextureSet = std::make_unique<FramebufferRendererDescriptorTextureSet>(worker->device, ((textureCacheSize + 1) * 3) / 2);
        }

        if (createSet || (descriptorTextureReplacementMapEnabled != textureCacheReplacementMapEnabled)) {
            descriptorTextureVersions.clear();
            descriptorTextureGlobalVersion = 0;
            descriptorTextureReplacementMapEnabled = textureCacheReplacementMapEnabled;
        }

#   if RT_ENABLED
        if (raytracingEnabled) {
            descCommonSet->setBuffer(descCommonSet->posBuffer, outputBuffers->worldPosBuffer.buffer.get(), outputBuffers->worldPosBuffer.allocatedSize);
            descCommonSet->setBuffer(descCommonSet->normBuffer, outputBuffers->worldNormBuffer.buffer.get(), outputBuffers->worldNormBuffer.allocatedSize);
            descCommonSet->setBuffer(descCommonSet->velBuffer, outputBuffers->worldVelBuffer.buffer.get(), outputBuffers->worldVelBuffer.allocatedSize);
            descCommonSet->setBuffer(descCommonSet->genTexCoordBuffer, outputBuffers->genTexCoordBuffer.buffer.get(), outputBuffers->genTexCoordBuffer.allocatedSize);
            descCommonSet->setBuffer(descCommonSet->shadedColBuffer, outputBuffers->shadedColBuffer.buffer.get(), outputBuffers->shadedColBuffer.allocatedSize);
            descCommonSet->setBuffer(descCommonSet->srcFogIndices, drawBuffers->fogIndicesBuffer.get(), drawBuffers->fogIndicesBuffer.allocatedSize);
            descCommonSet->setBuffer(descCommonSet->srcLightIndices, drawBuffers->lightIndicesBuffer.get(), drawBuffers->lightIndicesBuffer.allocatedSize);
            descCommonSet->setBuffer(descCommonSet->srcLightCounts, drawBuffers->lightCountsBuffer.get(), drawBuffers->lightCountsBuffer.allocatedSize);
            descCommonSet->setBuffer(descCommonSet->indexBuffer, drawBuffers->faceIndicesBuffer.get(), drawBuffers->faceIndicesBuffer.allocatedSize);
            descCommonSet->setBuffer(descCommonSet->RSPFogVector, drawBuffers->rspFogBuffer.get(), drawBuffers->rspFogBuffer.allocatedSize, RenderBufferStructuredView(sizeof(interop::RSPFog)));
            descCommonSet->setBuffer(descCommonSet->RSPLightVector, drawBuffers->rspLightsBuffer.get(), drawBuffers->rspLightsBuffer.allocatedSize, RenderBufferStructuredView(sizeof(interop::RSPLight)));
            descCommonSet->setTexture(descCommonSet->gViewDirection, rtResources->viewDirectionTexture.get(), RenderTextureLayout::GENERAL);
            descCommonSet->setTexture(descCommonSet->gShadingPosition, rtResources->shadingPositionTexture.get(), RenderTextureLayout::GENERAL);
            descCommonSet->setTexture(descCommonSet->gShadingNormal, rtResources->shadingNormalTexture.get(), RenderTextureLayout::GENERAL);
            descCommonSet->setTexture(descCommonSet->gShadingSpecular, rtResources->shadingSpecularTexture.get(), RenderTextureLayout::GENERAL);
            descCommonSet->setTexture(descCommonSet->gDiffuse, rtResources->diffuseTexture.get(), RenderTextureLayout::GENERAL);
            descCommonSet->setTexture(descCommonSet->gInstanceId, rtResources->instanceIdTexture.get(), RenderTextureLayout::GENERAL);
            descCommonSet->setTexture(descCommonSet->gDirectLightAccum, rtResources->directLightTexture[rtResources->swapBuffers ? 1 : 0].get(), RenderTextureLayout::GENERAL);
            descCommonSet->setTexture(descCommonSet->gIndirectLightAccum, rtResources->indirectLightTexture[rtResources->swapBuffers ? 1 : 0].get(), RenderTextureLayout::GENERAL);
            descCommonSet->setTexture(descCommonSet->gReflection, rtResources->reflectionTexture.get(), RenderTextureLayout::GENERAL);
            descCommonSet->setTexture(descCommonSet->gRefraction, rtResources->refractionTexture.get(), RenderTextureLayout::GENERAL);
            descCommonSet->setTexture(descCommonSet->gTransparent, rtResources->transparentTexture.get(), RenderTextureLayout::GENERAL);
            descCommonSet->setTexture(descCommonSet->gFlow, rtResources->flowTexture.get(), RenderTextureLayout::GENERAL);
            descCommonSet->setTexture(descCommonSet->gReactiveMask, rtResources->reactiveMaskTexture.get(), RenderTextureLayout::GENERAL);
            descCommonSet->setTexture(descCommonSet->gLockMask, rtResources->lockMaskTexture.get(), RenderTextureLayout::GENERAL);
            descCommonSet->setTexture(descCommonSet->gNormalRoughness, rtResources->normalRoughnessTexture[rtResources->swapBuffers ? 1 : 0].get(), RenderTextureLayout::GENERAL);
            descCommonSet->setTexture(descCommonSet->gDepth, rtResources->depthTexture[rtResources->swapBuffers ? 1 : 0].get(), RenderTextureLayout::GENERAL);
            descCommonSet->setTexture(descCommonSet->gPrevNormalRoughness, rtResources->normalRoughnessTexture[rtResources->swapBuffers ? 0 : 1].get(), RenderTextureLayout::GENERAL);
            descCommonSet->setTexture(descCommonSet->gPrevDepth, rtResources->depthTexture[rtResources->swapBuffers ? 0 : 1].get(), RenderTextureLayout::GENERAL);
            descCommonSet->setTexture(descCommonSet->gPrevDirectLightAccum, rtResources->directLightTexture[rtResources->swapBuffers ? 0 : 1].get(), RenderTextureLayout::GENERAL);
            descCommonSet->setTexture(descCommonSet->gPrevIndirectLightAccum, rtResources->indirectLightTexture[rtResources->swapBuffers ? 0 : 1].get(), RenderTextureLayout::GENERAL);
            descCommonSet->setTexture(descCommonSet->gFilteredDirectLight, rtResources->filteredDirectLightTexture[1].get(), RenderTextureLayout::GENERAL);
            descCommonSet->setTexture(descCommonSet->gFilteredIndirectLight, rtResources->filteredIndirectLightTexture[1].get(), RenderTextureLayout::GENERAL);

            const uint32_t hitBufferPixelCount = rtResources->textureWidth * rtResources->textureHeight * RaytracingResources::MaxHitQueries;
            descCommonSet->setBuffer(descCommonSet->gHitVelocityDistance, rtResources->hitVelocityDistanceBuffer.get(), hitBufferPixelCount * 16, rtResources->hitVelocityDistanceBufferView.get());
            descCommonSet->setBuffer(descCommonSet->gHitColor, rtResources->hitColorBuffer.get(), hitBufferPixelCount * 4, rtResources->hitColorBufferView.get());
            descCommonSet->setBuffer(descCommonSet->gHitNormalFog, rtResources->hitNormalFogBuffer.get(), hitBufferPixelCount * 8, rtResources->hitNormalFogBufferView.get());
            descCommonSet->setBuffer(descCommonSet->gHitInstanceId, rtResources->hitInstanceIdBuffer.get(), hitBufferPixelCount * 2, rtResources->hitInstanceIdBufferView.get());
            descCommonSet->setAccelerationStructure(descCommonSet->SceneBVH, rtResources->topLevelAS.get());
            descCommonSet->setBuffer(descCommonSet->SceneLights, rtResources->lightsBuffer.get(), sizeof(interop::PointLight) * std::max(rtResources->rtParams.lightsCount, 1U), RenderBufferStructuredView(sizeof(interop::PointLight)));
            descCommonSet->setBuffer(descCommonSet->interleavedRasters, interleavedRastersBuffer.get(), sizeof(interop::InterleavedRaster) * std::max(interleavedRastersCount, 1U), RenderBufferStructuredView(sizeof(interop::InterleavedRaster)));
            descCommonSet->setTexture(descCommonSet->gBlueNoise, blueNoiseTexture, RenderTextureLayout::SHADER_READ);
            descCommonSet->setBuffer(descCommonSet->instanceExtraParams, drawBuffers->extraParamsBuffer.get(), RenderBufferStructuredView(sizeof(interop::ExtraParams)));
            descCommonSet->setBuffer(descCommonSet->RtParams, rtResources->rtParamsBuffer.get(), sizeof(interop::RaytracingParams));
        }
#   endif

        for (auto &view : wr64RTViews) {
            auto *rt = &view;
            if (rt->prepared) {
                if (rt->traceReflections)
                    rt->descriptor->setAccelerationStructure(rt->descriptor->SceneBVH, rt->scene.accelerationStructure());
                if (rt->rasterSky)
                    rt->descriptor->setTexture(rt->descriptor->wr64RasterSky,
                        rt->rasterSkyTarget.texture(), RenderTextureLayout::SHADER_READ);
                if (rt->rasterShadows) {
                    rt->descriptor->setBuffer(rt->descriptor->wr64RasterShadowParams,
                        rt->rasterShadowParamsBuffer.get(), sizeof(Wr64RasterShadowParams));
                    rt->descriptor->setTexture(rt->descriptor->wr64RasterShadowMap,
                        rt->rasterShadowTarget.color(), RenderTextureLayout::SHADER_READ);
                }
                if (rt->rasterReflections) {
                    rt->descriptor->setBuffer(rt->descriptor->wr64RasterReflectionParams,
                        rt->rasterReflectionParamsBuffer.get(), sizeof(Wr64RasterReflectionParams));
                    rt->descriptor->setTexture(rt->descriptor->wr64RasterReflectionColor,
                        rt->rasterReflectionTarget.color(), RenderTextureLayout::SHADER_READ);
                }
                rt->descriptor->setBuffer(rt->descriptor->RtParams, rt->paramsBuffer.get(), sizeof(Wr64RTParams));
                if (!rt->rasterReflections && !rt->rasterSky && !rt->raySkyOnly && rt->skyScopeSeen && rt->skyCaptureBuffer)
                    rt->descriptor->setBuffer(rt->descriptor->wr64SkyCapture, rt->skyCaptureBuffer.get(), Wr64SkyCaptureBytes);
                rt->descriptor->setBuffer(rt->descriptor->posBuffer, outputBuffers->worldPosBuffer.buffer.get(), outputBuffers->worldPosBuffer.allocatedSize);
                rt->descriptor->setBuffer(rt->descriptor->genTexCoordBuffer, outputBuffers->genTexCoordBuffer.buffer.get(), outputBuffers->genTexCoordBuffer.allocatedSize);
                rt->descriptor->setBuffer(rt->descriptor->shadedColBuffer, outputBuffers->shadedColBuffer.buffer.get(), outputBuffers->shadedColBuffer.allocatedSize);
                rt->descriptor->setBuffer(rt->descriptor->indexBuffer, drawBuffers->faceIndicesBuffer.get(), drawBuffers->faceIndicesBuffer.allocatedSize);
                if (rt->traceReflections)
                    rt->descriptor->setBuffer(rt->descriptor->interleavedRasters, rt->scene.geometryBuffer(),
                        rt->scene.geometryBufferSize(), RenderBufferStructuredView(16));
                rt->descriptor->setBuffer(rt->descriptor->wr64WaterAdjacency,
                    rt->waterAdjacencyBuffer.get(), rt->waterAdjacencyCapacity);
                // Scene preparation provides a zeroed fallback record when there
                // are no private fence volumes, so t69 is always initialized.
                if (rt->traceReflections)
                    rt->descriptor->setBuffer(rt->descriptor->wr64FenceProxy,
                        rt->scene.proxyBuffer(), rt->scene.proxyBufferSize());
                rt->descriptor->setBuffer(rt->descriptor->FrParams, frameParamsBuffer.get(), sizeof(interop::FrameParams));
                rt->descriptor->setBuffer(rt->descriptor->instanceRenderIndices, renderIndicesBuffer.get(), RenderBufferStructuredView(sizeof(interop::RenderIndices)));
                rt->descriptor->setBuffer(rt->descriptor->instanceRDPParams, drawBuffers->rdpParamsBuffer.get(), RenderBufferStructuredView(sizeof(interop::RDPParams)));
                rt->descriptor->setBuffer(rt->descriptor->RDPTiles, drawBuffers->rdpTilesBuffer.get(), RenderBufferStructuredView(sizeof(interop::RDPTile)));
                rt->descriptor->setBuffer(rt->descriptor->GPUTiles, drawBuffers->gpuTilesBuffer.get(), RenderBufferStructuredView(sizeof(interop::GPUTile)));
                rt->descriptor->setBuffer(rt->descriptor->DynamicRenderParams, drawBuffers->renderParamsBuffer.get(), RenderBufferStructuredView(sizeof(interop::RenderParams)));
            }
        }
        if (wr64MotionPrepared) {
            descCommonSet->setBuffer(descCommonSet->posBuffer, outputBuffers->worldPosBuffer.buffer.get(), outputBuffers->worldPosBuffer.allocatedSize);
            descCommonSet->setBuffer(descCommonSet->velBuffer, outputBuffers->worldVelBuffer.buffer.get(), outputBuffers->worldVelBuffer.allocatedSize);
            descCommonSet->setBuffer(descCommonSet->wr64MotionDraws, wr64MotionDrawBuffer.get(), wr64MotionDrawCapacity,
                RenderBufferStructuredView(sizeof(Wr64MotionDrawParams)));
        }
        descCommonSet->setBuffer(descCommonSet->FrParams, frameParamsBuffer.get(), sizeof(interop::FrameParams));
        descCommonSet->setBuffer(descCommonSet->instanceRenderIndices, renderIndicesBuffer.get(), RenderBufferStructuredView(sizeof(interop::RenderIndices)));
        descCommonSet->setBuffer(descCommonSet->instanceRDPParams, drawBuffers->rdpParamsBuffer.get(), RenderBufferStructuredView(sizeof(interop::RDPParams)));
        descCommonSet->setBuffer(descCommonSet->RDPTiles, drawBuffers->rdpTilesBuffer.get(), RenderBufferStructuredView(sizeof(interop::RDPTile)));
        descCommonSet->setBuffer(descCommonSet->GPUTiles, drawBuffers->gpuTilesBuffer.get(), RenderBufferStructuredView(sizeof(interop::GPUTile)));
        descCommonSet->setBuffer(descCommonSet->DynamicRenderParams, drawBuffers->renderParamsBuffer.get(), RenderBufferStructuredView(sizeof(interop::RenderParams)));

        // Make sure the versions vector matches the texture cache size.
        descriptorTextureVersions.resize(textureCacheSize, 0);

        // Update texture vector with static textures from the cache and dynamic resource views.
        if (descriptorTextureGlobalVersion != textureCacheGlobalVersion) {
            // Normally a handful of changed entries. After a set recreation above,
            // every stamp is zero and this rewrites the entire heap in one frame,
            // which is the shape that would show up as a single hitch. detail is how
            // many descriptors were actually written.
            WR64StallProbeHot rewriteProbe("fb-descriptor-rewrite");
            uint64_t rewritten = 0;
            const uint32_t textureVersionSize = static_cast<uint32_t>(textureCacheVersions.size());
            for (uint32_t i = 0; i < textureVersionSize; i++) {
                if (textureCacheVersions[i] == descriptorTextureVersions[i]) {
                    continue;
                }

                rewritten++;
                descriptorTextureVersions[i] = textureCacheVersions[i];
                if (textureCacheTextures[i] == nullptr) {
                    continue;
                }

                if (textureCacheReplacementMapEnabled && (textureCacheTextureReplacements[i] != nullptr)) {
                    descTextureSet->setTexture(i, textureCacheTextureReplacements[i]->texture.get(), RenderTextureLayout::SHADER_READ);
                }
                else if (textureCacheTextures[i]->texture != nullptr) {
                    descTextureSet->setTexture(i, textureCacheTextures[i]->texture.get(), RenderTextureLayout::SHADER_READ);
                }
                else {
                    descTextureSet->setTexture(i, textureCacheTextures[i]->tmem.get(), RenderTextureLayout::SHADER_READ);
                }
            }

            rewriteProbe.setDetail(rewritten);
            descriptorTextureGlobalVersion = textureCacheGlobalVersion;
        }

        for (const DynamicTextureView &dynamicView : dynamicTextureViewVector) {
            descTextureSet->setTexture(dynamicView.dstIndex, dynamicView.texture, RenderTextureLayout::SHADER_READ, dynamicView.textureView);
            descriptorTextureVersions[dynamicView.dstIndex] = 0;
        }
    }

    void FramebufferRenderer::updateRSPSmoothNormalSet(RenderWorker *worker, const DrawBuffers *drawBuffers, const OutputBuffers *outputBuffers) {
        assert(worker != nullptr);

        if (smoothDescSet == nullptr) {
            smoothDescSet = std::make_unique<RSPSmoothNormalDescriptorSet>(worker->device);
        }

        smoothDescSet->setBuffer(smoothDescSet->srcWorldPos, outputBuffers->worldPosBuffer.buffer.get(), outputBuffers->worldPosBuffer.allocatedSize, RenderBufferStructuredView(sizeof(float) * 4));
        smoothDescSet->setBuffer(smoothDescSet->srcCol, drawBuffers->normalColorBuffer.get(), drawBuffers->normalColorBuffer.allocatedSize, RenderBufferStructuredView(sizeof(uint8_t) * 4));
        smoothDescSet->setBuffer(smoothDescSet->srcFaceIndices, drawBuffers->faceIndicesBuffer.get(), drawBuffers->faceIndicesBuffer.allocatedSize, RenderBufferStructuredView(sizeof(uint32_t)));
        smoothDescSet->setBuffer(smoothDescSet->dstWorldNorm, outputBuffers->worldNormBuffer.buffer.get(), outputBuffers->worldNormBuffer.allocatedSize, RenderBufferStructuredView(sizeof(float) * 4));
    }

    void FramebufferRenderer::updateRSPVertexTestZSet(RenderWorker *worker, const DrawBuffers *drawBuffers, const OutputBuffers *outputBuffers) {
        assert(worker != nullptr);

        if (vertexTestZSet == nullptr) {
            vertexTestZSet = std::make_unique<RSPVertexTestZDescriptorSet>(worker->device);
        }
        
        vertexTestZSet->setBuffer(vertexTestZSet->screenPos, outputBuffers->screenPosBuffer.buffer.get(), RenderBufferStructuredView(sizeof(float) * 4));
        vertexTestZSet->setBuffer(vertexTestZSet->srcFaceIndices, drawBuffers->faceIndicesBuffer.get(), drawBuffers->faceIndicesBuffer.allocatedSize, RenderBufferStructuredView(sizeof(uint32_t)));
        vertexTestZSet->setBuffer(vertexTestZSet->dstFaceIndices, outputBuffers->testZIndexBuffer.buffer.get(), outputBuffers->testZIndexBuffer.allocatedSize, RenderBufferStructuredView(sizeof(uint32_t)));
    }

    void FramebufferRenderer::updateShaderViews(RenderWorker *worker, const DrawBuffers *drawBuffers, const OutputBuffers *outputBuffers, const bool raytracingEnabled) {
        updateShaderDescriptorSet(worker, drawBuffers, outputBuffers, raytracingEnabled);
        updateRSPVertexTestZSet(worker, drawBuffers, outputBuffers);

#   if RT_ENABLED
        if (raytracingEnabled) {
            updateRSPSmoothNormalSet(worker, drawBuffers, outputBuffers);
            rtResources->updateShaderSets(worker, shaderLibrary);
        }
#   endif
    }

    bool FramebufferRenderer::submitDepthAccess(RenderWorker *worker, RenderFramebufferStorage *fbStorage, bool readOnly, bool &depthState) {
        if (depthState == readOnly) {
            return false;
        }
        
        RenderFramebuffer *renderFramebuffer = readOnly ? fbStorage->colorWriteDepthRead.get() : fbStorage->colorDepthWrite.get();
        const RenderTextureLayout depthReadState = RenderTextureLayout::DEPTH_READ;
        const RenderTextureLayout depthWriteState = RenderTextureLayout::DEPTH_WRITE;
        worker->commandList->barriers(RenderBarrierStage::GRAPHICS, RenderTextureBarrier(fbStorage->depthTarget->texture.get(), readOnly ? depthReadState : RenderTextureLayout::DEPTH_WRITE));
        worker->commandList->setFramebuffer(renderFramebuffer);
        depthState = readOnly;
        return true;
    }
    
    void FramebufferRenderer::submitRasterScene(RenderWorker *worker, const Framebuffer &framebuffer, RenderFramebufferStorage *fbStorage, const RasterScene &rasterScene, bool &depthState) {
        InstanceDrawCall::Type previousCallType = InstanceDrawCall::Type::Unknown;
        bool previousVertexTestZ = false;
        const RenderPipeline *previousPipeline = nullptr;
        RenderRect previousScissor;
        interop::RasterParams rasterParams{};
        RenderDescriptorSet *descRealFbSet = framebuffer.descRealFbSet->get();
        RenderDescriptorSet *descDummyFbSet = framebuffer.descDummyFbSet->get();

        RenderDescriptorSet *boundCommonSet = nullptr;
        auto switchToGraphicsPipeline = [&]() {
            previousCallType = InstanceDrawCall::Type::Unknown;
            previousVertexTestZ = false;
            previousPipeline = nullptr;
            previousScissor = RenderRect();
            worker->commandList->setGraphicsPipelineLayout(rendererPipelineLayout);
            worker->commandList->setGraphicsDescriptorSet(descCommonSet->get(), 0);
            boundCommonSet = descCommonSet->get();
            worker->commandList->setGraphicsDescriptorSet(descTextureSet->get(), 1);
            worker->commandList->setGraphicsDescriptorSet(descTextureSet->get(), 2);
            worker->commandList->setGraphicsDescriptorSet(depthState ? descRealFbSet : descDummyFbSet, 3);
            worker->commandList->setViewports(framebuffer.viewport);
        };

        auto switchToDepthRead = [&]() {
            if (submitDepthAccess(worker, fbStorage, true, depthState)) {
                worker->commandList->setGraphicsDescriptorSet(descRealFbSet, 3);
            }
        };

        auto switchToDepthWrite = [&]() {
            if (submitDepthAccess(worker, fbStorage, false, depthState)) {
                worker->commandList->setGraphicsDescriptorSet(descDummyFbSet, 3);
            }
        };

        auto drawCallTriangles = [&](const InstanceDrawCall &drawCall) {
            if (drawCall.type == InstanceDrawCall::Type::IndexedTriangles) {
                worker->commandList->drawIndexedInstanced(drawCall.triangles.faceCount * 3, 1, drawCall.triangles.indexStart, 0, 0);
            }
            else {
                worker->commandList->drawInstanced(drawCall.triangles.faceCount * 3, 1, drawCall.triangles.indexStart, 0);
            }
        };

        if (fbStorage->colorTarget != nullptr) {
            switchToGraphicsPipeline();
        }

        auto drawObjectMotionBlur = [&]() {
            if (!wr64MotionPrepared || fbStorage != framebufferVector[wr64RTViews[0].framebuffer].renderTargetDrawCall.fbStorage)
                return;
            if (!wr64MotionBlur.beginMask(worker, shaderLibrary)) {
                wr64MotionDiagnostic.reason = "begin-mask-failed";
                return;
            }
            depthState = true; // The mask uses the final native depth read-only.
            switchToGraphicsPipeline();
            worker->commandList->setFramebuffer(wr64MotionBlur.maskFramebuffer());
            worker->commandList->setVertexBuffers(0, indexedVertexViews.data(), uint32_t(indexedVertexViews.size()), vertexInputSlots.data());
            worker->commandList->setIndexBuffer(&indexBufferView);
            for (uint32_t actor : wr64MotionActors) {
                const auto &triangles = instanceDrawCallVector[actor].triangles;
                const auto *pipeline = wr64MotionBlur.getMask(triangles.shaderDesc.flags.culling, triangles.shaderDesc.flags.NoN);
                wr64MotionDiagnostic.missingPipelines += pipeline == nullptr;
                wr64MotionDiagnostic.emptyScissors += triangles.scissor.isEmpty();
                if (!pipeline || triangles.scissor.isEmpty()) continue;
                worker->commandList->setScissors(triangles.scissor);
                worker->commandList->setPipeline(pipeline);
                interop::RasterParams motionParams{};
                motionParams.renderIndex = actor;
                motionParams.screenScale = triangles.screenScale;
                motionParams.screenOffset = triangles.screenOffset;
                motionParams.padding.x = uint32_t(wr64MotionDrawParams[actor].viewportTranslate.w);
                std::memcpy(&motionParams.padding.y, &wr64MotionTimeScale, sizeof(wr64MotionTimeScale));
                motionParams.padding.z = 1;
                worker->commandList->setGraphicsPushConstants(0, &motionParams);
                worker->commandList->drawIndexedInstanced(triangles.faceCount * 3, 1, triangles.indexStart, 0, 0);
                ++wr64MotionDiagnostic.maskDraws;
            }
            wr64MotionBlur.finishMask(worker);
            const float options[4] = { framebuffer.viewport.width, framebuffer.viewport.height, 16.0f, wr64MotionShutter };
            wr64MotionDiagnostic.executed = wr64MotionBlur.resolve(worker, options);
            wr64MotionDiagnostic.reason = !wr64MotionDiagnostic.executed ? "resolve-failed" :
                (wr64MotionDiagnostic.maskDraws ? "executed" : "empty-mask-draws");
            worker->commandList->setFramebuffer(fbStorage->colorWriteDepthRead.get());
            switchToGraphicsPipeline();
        };
        
        for (uint32_t i : rasterScene.instanceIndices) {
            if (i == wr64MotionBoundary) drawObjectMotionBlur();
            const InstanceDrawCall &drawCall = instanceDrawCallVector[i];
            const uint32_t owner = i < wr64RTDrawViews.size() ? wr64RTDrawViews[i] : 0;
            auto *rt = &wr64RTViews[owner ? owner - 1 : 0];
            // Replace the native water-height blob only after the replacement
            // water pipeline and this frame's AS build both succeeded. A failed
            // build clears enabled, so native shadows survive every fallback.
            if (rt->prepared && rt->shadowWaterSelected && rt->params.enabled &&
                ((float(rt->params.shadowOptions.x) == 1.0f && rt->scene.buildRecorded()) ||
                    (rt->rasterShadows && rt->shadowMapRecorded)) &&
                std::isfinite(float(rt->params.shadowLight.w)) && float(rt->params.shadowLight.w) > 0.0f &&
                rt->racerShadowCasters != 0) {
                const auto blob = std::lower_bound(rt->nativeShadowDraws.begin(), rt->nativeShadowDraws.end(), i,
                    [](const Wr64NativeShadowDraw &candidate, uint32_t index) { return candidate.drawIndex < index; });
                if (blob != rt->nativeShadowDraws.end() && blob->drawIndex == i &&
                    (blob->racerMask & (rt->rasterShadows ? rt->rasterShadowRacers : rt->racerShadowCasters)) != 0) {
                    continue;
                }
            }
            switch (drawCall.type) {
            case InstanceDrawCall::Type::IndexedTriangles: 
            case InstanceDrawCall::Type::RawTriangles:
            case InstanceDrawCall::Type::RegularRect: {
                assert(fbStorage->colorTarget != nullptr);

                const bool typeDifferent = (drawCall.type != previousCallType);
                const bool testZDifferent = (drawCall.type == InstanceDrawCall::Type::IndexedTriangles) && (drawCall.triangles.vertexTestZ != previousVertexTestZ);
                if (typeDifferent || testZDifferent) {
                    switch (drawCall.type) {
                    case InstanceDrawCall::Type::IndexedTriangles:
                        worker->commandList->setVertexBuffers(0, indexedVertexViews.data(), uint32_t(indexedVertexViews.size()), vertexInputSlots.data());
                        worker->commandList->setIndexBuffer(drawCall.triangles.vertexTestZ ? &testZIndexBufferView : &indexBufferView);
                        previousVertexTestZ = drawCall.triangles.vertexTestZ;
                        break;
                    case InstanceDrawCall::Type::RawTriangles:
                    case InstanceDrawCall::Type::RegularRect:
                        worker->commandList->setVertexBuffers(0, rawVertexViews.data(), uint32_t(rawVertexViews.size()), vertexInputSlots.data());
                        worker->commandList->setIndexBuffer(nullptr);
                        break;
                    default:
                        assert(false && "Unknown draw call type.");
                        break;
                    };

                    previousCallType = drawCall.type;
                }

                const auto &triangles = drawCall.triangles;
                assert(triangles.pipeline != nullptr);

                // Draw calls can sometimes end up with empty scissors and cause validation errors. We just skip them.
                if (triangles.scissor.isEmpty()) {
                    wr64SunOutputIssued(i, true);
                    continue;
                }

                // Only shader draws bind graphics resources. Native depth-only
                // clears do not establish a graphics pipeline layout, and must
                // remain valid even at the beginning of a fresh command list.
                auto *common = owner && rt->prepared && (!rt->traceReflections || rt->scene.buildRecorded())
                    ? rt->descriptor->get() : descCommonSet->get();
                if (common != boundCommonSet) {
                    worker->commandList->setGraphicsDescriptorSet(common, 0);
                    boundCommonSet = common;
                }

                // A new pass must be started if decals are required and something wrote to the depth buffer before this call.
                const interop::OtherMode otherMode = triangles.shaderDesc.otherMode;
                bool depthDecal = (otherMode.zMode() == ZMODE_DEC);
                bool depthWrite = otherMode.zUpd();
                if (depthDecal) {
                    switchToDepthRead();
                }
                else if (!depthDecal && depthWrite) {
                    switchToDepthWrite();
                }

                if (previousScissor != triangles.scissor) {
                    worker->commandList->setScissors(triangles.scissor);
                    previousScissor = triangles.scissor;
                }

                if (previousPipeline != triangles.pipeline) {
                    worker->commandList->setPipeline(triangles.pipeline);
                    previousPipeline = triangles.pipeline;
                }
                
                rasterParams.renderIndex = i;
                rasterParams.padding.x = std::binary_search(rt->aoOnlyDraws.begin(),
                    rt->aoOnlyDraws.end(), i) ? WR64_AO_ONLY_RECEIVER : 0u;
                rasterParams.screenScale = triangles.screenScale;
                rasterParams.screenOffset = triangles.screenOffset;
                // Reset on every draw: the preceding disk must not fade a flare,
                // HUD element, triangle, or the next workload's first draw.
                rasterParams.padding.y = 0;
                rasterParams.padding.z = 0;
                if (triangles.wr64DolphinSunOpacityLoss > 0.0f) {
                    std::memcpy(&rasterParams.padding.y, &triangles.wr64DolphinSunOpacityLoss, sizeof(float));
                    rasterParams.padding.z = WR64_DOLPHIN_SUN_FADE_TAG;
                }
                worker->commandList->setGraphicsPushConstants(0, &rasterParams);

                drawCallTriangles(drawCall);
                wr64SunOutputIssued(i, false);

                // Simulate dither noise.
                if (triangles.postBlendDitherNoise) {
                    if (triangles.postBlendDitherNoiseNegative) {
                        worker->commandList->setPipeline(postBlendDitherNoiseSubNegativePipeline);
                    }
                    else {
                        worker->commandList->setPipeline(postBlendDitherNoiseAddPipeline);
                        drawCallTriangles(drawCall);

                        worker->commandList->setPipeline(postBlendDitherNoiseSubPipeline);
                    }

                    drawCallTriangles(drawCall);
                    previousPipeline = nullptr;
                }

                break;
            };
            case InstanceDrawCall::Type::FillRect: {
                const auto &clearRect = drawCall.clearRect;
                RenderTarget *chosenTarget = (fbStorage->colorTarget != nullptr) ? fbStorage->colorTarget : fbStorage->depthTarget;
                bool rectCoversWholeTarget = (clearRect.rect.left == 0) && (clearRect.rect.top == 0) && (uint32_t(clearRect.rect.right) == chosenTarget->width) && (uint32_t(clearRect.rect.bottom) == chosenTarget->height);
                const RenderRect *clearRects = rectCoversWholeTarget ? nullptr : &clearRect.rect;
                uint32_t clearRectCount = rectCoversWholeTarget ? 0 : 1;
                if (fbStorage->colorTarget != nullptr) {
                    worker->commandList->clearColor(0, clearRect.color, clearRects, clearRectCount);
                }
                else {
                    worker->commandList->clearDepth(true, clearRect.depth, clearRects, clearRectCount);
                }

                break;
            };
            case InstanceDrawCall::Type::VertexTestZ: {
                assert(testZIndexBuffer != nullptr);
                assert(fbStorage->colorTarget != nullptr);

                const interop::RSPVertexTestZCB &testZCB = drawCall.vertexTestZ;
                switchToDepthRead();

                const bool useMSAA = (fbStorage->colorTarget->multisampling.sampleCount > 0);
                const auto &rspVertexTestZ = useMSAA ? shaderLibrary->rspVertexTestZMS : shaderLibrary->rspVertexTestZ;
                worker->commandList->barriers(RenderBarrierStage::COMPUTE, RenderBufferBarrier(testZIndexBuffer, RenderBufferAccess::WRITE));
                worker->commandList->setPipeline(rspVertexTestZ.pipeline.get());
                worker->commandList->setComputePipelineLayout(rspVertexTestZ.pipelineLayout.get());
                worker->commandList->setComputePushConstants(0, &testZCB);
                worker->commandList->setComputeDescriptorSet(vertexTestZSet->get(), 0);
                worker->commandList->setComputeDescriptorSet(descRealFbSet, 1);
                worker->commandList->dispatch(1, 1, 1);
                worker->commandList->barriers(RenderBarrierStage::GRAPHICS, RenderBufferBarrier(testZIndexBuffer, RenderBufferAccess::READ));

                switchToGraphicsPipeline();
                break;
            };
            default:
                // Do nothing.
                break;
            }
        }

        // Mark targets for resolve.
        if (fbStorage->colorTarget != nullptr) {
            fbStorage->colorTarget->markForResolve();
        }

        if (fbStorage->depthTarget != nullptr) {
            fbStorage->depthTarget->markForResolve();
        }
    }

    void FramebufferRenderer::updateMultisampling() {
        dummyColorTargetView.reset();
        dummyDepthTargetView.reset();
        dummyColorTarget.reset();
        dummyDepthTarget.reset();
#   if RT_ENABLED
        if (rtResources != nullptr) {
            rtResources->updateMultisampling();
        }
#   endif
    }

#if RT_ENABLED
    void FramebufferRenderer::updateRaytracingScene(RenderWorker *worker, const RaytracingScene &rtScene) {
        auto &rtParams = rtResources->rtParams;
        const bool lumaActive = rtScene.presetScene.luminanceRange > 0.0f;

        // Only use jitter when an upscaler is active.
        Upscaler *upscaler = rtResources->getUpscaler(rtResources->upscalerMode);
        bool jitterActive = rtResources->upscaleActive && (upscaler != nullptr);
        if (jitterActive) {
            const int phaseCount = upscaler->getJitterPhaseCount(rtResources->textureWidth, rtScene.screenWidth);
            rtParams.pixelJitter = HaltonJitter(frameParams.frameCount, phaseCount);
        }
        else {
            rtParams.pixelJitter = { 0.0f, 0.0f };
        }

        rtParams.viewport.x = rtScene.viewport.x;
        rtParams.viewport.y = rtScene.viewport.y;
        rtParams.viewport.z = rtScene.viewport.width;
        rtParams.viewport.w = rtScene.viewport.height;

        const auto &preset = rtScene.presetScene;
        rtParams.ambientBaseColor = hlslpp::float4(preset.ambientBaseColor, 0.0f);
        rtParams.ambientNoGIColor = hlslpp::float4(preset.ambientNoGIColor, 0.0f);
        rtParams.eyeLightDiffuseColor = hlslpp::float4(preset.eyeLightDiffuseColor, 0.0f);
        rtParams.eyeLightSpecularColor = hlslpp::float4(preset.eyeLightSpecularColor, 0.0f);
        rtParams.giDiffuseStrength = preset.giDiffuseStrength;
        rtParams.giBackgroundStrength = preset.giBackgroundStrength;
        rtParams.tonemapExposure = preset.tonemapExposure;
        rtParams.tonemapWhite = preset.tonemapWhite;
        rtParams.tonemapBlack = preset.tonemapBlack;

        const auto &proj = rtScene.curProjMatrix;
        rtParams.fovRadians = fovFromProj(proj);
        rtParams.nearDist = nearPlaneFromProj(proj);
        rtParams.farDist = farPlaneFromProj(proj);

        if (isnan(rtParams.fovRadians)) {
            rtParams.fovRadians = 0.75f;
        }

        if (isnan(rtParams.nearDist)) {
            rtParams.nearDist = 1.0f;
        }

        if (isnan(rtParams.farDist)) {
            rtParams.farDist = 1000.0f;
        }

        rtParams.view = rtScene.curViewMatrix;
        rtParams.projection = rtScene.curProjMatrix;

        rtParams.viewI = hlslpp::inverse(rtParams.view);
        rtParams.projectionI = hlslpp::inverse(rtParams.projection);
        rtParams.viewProj = hlslpp::mul(rtParams.view, rtParams.projection);
        rtParams.prevViewProj = hlslpp::mul(rtScene.prevViewMatrix, rtScene.prevProjMatrix);

        // TODO: There's probably a way to compute this without calculating the FOV/Near/Far values.
        // Pinhole camera vectors to generate non-normalized ray direction.
        // TODO: Make a fake target and focal distance at the midpoint of the near/far planes
        // until the game sends that data in some way in the future.
        const float FocalDistance = (rtParams.nearDist + rtParams.farDist) / 2.0f;
        const hlslpp::float3 Up(0.0f, 1.0f, 0.0f);
        const hlslpp::float3 Pos = viewPositionFrom(rtParams.viewI);
        const hlslpp::float3 Target = Pos + viewDirectionFrom(rtParams.viewI) * FocalDistance;
        hlslpp::float3 cameraW = hlslpp::normalize(Target - Pos) * FocalDistance;
        hlslpp::float3 cameraU = hlslpp::normalize(hlslpp::cross(cameraW, Up));
        hlslpp::float3 cameraV = hlslpp::normalize(hlslpp::cross(cameraU, cameraW));
        const float ulen = FocalDistance * std::tan(rtParams.fovRadians * 0.5f);// * rtParams.aspectRatio;
        const float vlen = FocalDistance * std::tan(rtParams.fovRadians * 0.5f);
        cameraU = cameraU * ulen;
        cameraV = cameraV * vlen;
        rtParams.cameraU = hlslpp::float4(cameraU, 0.0f);
        rtParams.cameraV = hlslpp::float4(cameraV, 0.0f);
        rtParams.cameraW = hlslpp::float4(cameraW, 0.0f);

        // Enable light reprojection if denoising is enabled.
#   ifdef DI_REPROJECTION_SUPPORT
        globalParamsBufferData.diReproject = !rtResources->skipReprojection && denoiserEnabled && (globalParamsBufferData.diSamples > 0) && (rtResources->upscalerMode != UpscaleMode::DLSS) ? 1 : 0;
#   else
        rtParams.diReproject = 0;
#   endif

        rtParams.giReproject = !rtResources->skipReprojection && rtResources->denoiserEnabled && (rtParams.giSamples > 0) && (rtResources->upscalerMode != UpscaleMode::DLSS) ? 1 : 0;
        rtParams.binaryLockMask = (rtResources->upscalerMode != UpscaleMode::FSR);
        rtParams.interleavedRastersCount = interleavedRastersCount;
        
        Framebuffer &framebuffer = framebufferVector[framebufferCount - 1];
        RenderDescriptorSet *descRealDepthSet = framebuffer.descRealFbSet->get();
        RenderDescriptorSet *descriptorSets[] = { descCommonSet->get(), descTextureSet->get(), descTextureSet->get(), descRealDepthSet };
        rtResources->updateTopLevelASResources(worker, instanceDrawCallVector, rtScene.instanceIndices);
        rtResources->createShaderBindingTable(worker, rtState, descriptorSets, uint32_t(std::size(descriptorSets)), hitGroupVector);
        rtResources->updateLightsBuffer(worker, rtScene);
    }
    
    void FramebufferRenderer::submitRaytracingScene(RenderWorker *worker, RenderTarget *colorTarget, const RaytracingScene &rtScene) {
        // Unbind any render targets.
        worker->commandList->setFramebuffer(nullptr);

        // Resolve the color target if necessary before using it as the RT scene background.
        colorTarget->resolveTarget(worker, shaderLibrary);
        worker->commandList->barriers(RenderBarrierStage::COMPUTE, RenderTextureBarrier(colorTarget->getResolvedTexture(), RenderTextureLayout::SHADER_READ));

        if (rtResources->transitionOutputBuffers) {
            RenderTextureBarrier afterCreationBarriers[] = {
                RenderTextureBarrier(rtResources->viewDirectionTexture.get(), RenderTextureLayout::GENERAL),
                RenderTextureBarrier(rtResources->shadingPositionTexture.get(), RenderTextureLayout::GENERAL),
                RenderTextureBarrier(rtResources->shadingNormalTexture.get(), RenderTextureLayout::GENERAL),
                RenderTextureBarrier(rtResources->shadingSpecularTexture.get(), RenderTextureLayout::GENERAL),
                RenderTextureBarrier(rtResources->instanceIdTexture.get(), RenderTextureLayout::GENERAL),
                RenderTextureBarrier(rtResources->directLightTexture[0].get(), RenderTextureLayout::GENERAL),
                RenderTextureBarrier(rtResources->directLightTexture[1].get(), RenderTextureLayout::GENERAL),
                RenderTextureBarrier(rtResources->indirectLightTexture[0].get(), RenderTextureLayout::GENERAL),
                RenderTextureBarrier(rtResources->indirectLightTexture[1].get(), RenderTextureLayout::GENERAL),
                RenderTextureBarrier(rtResources->normalRoughnessTexture[0].get(), RenderTextureLayout::GENERAL),
                RenderTextureBarrier(rtResources->normalRoughnessTexture[1].get(), RenderTextureLayout::GENERAL),
                RenderTextureBarrier(rtResources->filteredDirectLightTexture[0].get(), RenderTextureLayout::GENERAL),
                RenderTextureBarrier(rtResources->filteredDirectLightTexture[1].get(), RenderTextureLayout::GENERAL),
                RenderTextureBarrier(rtResources->filteredIndirectLightTexture[0].get(), RenderTextureLayout::GENERAL),
                RenderTextureBarrier(rtResources->filteredIndirectLightTexture[1].get(), RenderTextureLayout::GENERAL)
            };

            worker->commandList->barriers(RenderBarrierStage::COMPUTE, afterCreationBarriers, uint32_t(std::size(afterCreationBarriers)));
            rtResources->transitionOutputBuffers = false;
        }

        // Make sure all these buffers are usable as UAVs.
        RenderTextureBarrier preDispatchBarriers[] = {
            RenderTextureBarrier(rtResources->diffuseTexture.get(), RenderTextureLayout::GENERAL),
            RenderTextureBarrier(rtResources->reflectionTexture.get(), RenderTextureLayout::GENERAL),
            RenderTextureBarrier(rtResources->refractionTexture.get(), RenderTextureLayout::GENERAL),
            RenderTextureBarrier(rtResources->transparentTexture.get(), RenderTextureLayout::GENERAL),
            RenderTextureBarrier(rtResources->flowTexture.get(), RenderTextureLayout::GENERAL),
            RenderTextureBarrier(rtResources->reactiveMaskTexture.get(), RenderTextureLayout::GENERAL),
            RenderTextureBarrier(rtResources->lockMaskTexture.get(), RenderTextureLayout::GENERAL),
            RenderTextureBarrier(rtResources->depthTexture[0].get(), RenderTextureLayout::GENERAL),
            RenderTextureBarrier(rtResources->depthTexture[1].get(), RenderTextureLayout::GENERAL)
        };

        worker->commandList->barriers(RenderBarrierStage::COMPUTE, preDispatchBarriers, uint32_t(std::size(preDispatchBarriers)));
        
        // Bind pipeline and dispatch primary rays.
        RT64_LOG_PRINTF("Dispatching primary rays");
        Framebuffer &framebuffer = framebufferVector[framebufferCount - 1];
        RenderDescriptorSet *descRealFbSet = framebuffer.descRealFbSet->get();
        rtResources->shaderBindingTableInfo.groups.rayGen.startIndex = 0;
        worker->commandList->setPipeline(rtState->pipeline.get());
        worker->commandList->setRaytracingPipelineLayout(rtPipelineLayout);
        worker->commandList->setRaytracingDescriptorSet(descCommonSet->get(), 0);
        worker->commandList->setRaytracingDescriptorSet(descTextureSet->get(), 1);
        worker->commandList->setRaytracingDescriptorSet(descTextureSet->get(), 2);
        worker->commandList->setRaytracingDescriptorSet(descRealFbSet, 3);
        worker->commandList->traceRays(rtResources->textureWidth, rtResources->textureHeight, 1, rtResources->shaderBindingTableBuffer->at(0), rtResources->shaderBindingTableInfo.groups);

        // Barriers for shading buffers before dispatching secondary rays.
        RenderTextureBarrier shadingBarriers[] = {
            RenderTextureBarrier(rtResources->instanceIdTexture.get(), RenderTextureLayout::GENERAL),
            RenderTextureBarrier(rtResources->shadingPositionTexture.get(), RenderTextureLayout::GENERAL),
            RenderTextureBarrier(rtResources->viewDirectionTexture.get(), RenderTextureLayout::GENERAL),
            RenderTextureBarrier(rtResources->shadingNormalTexture.get(), RenderTextureLayout::GENERAL),
            RenderTextureBarrier(rtResources->shadingSpecularTexture.get(), RenderTextureLayout::GENERAL),
            RenderTextureBarrier(rtResources->reflectionTexture.get(), RenderTextureLayout::GENERAL),
            RenderTextureBarrier(rtResources->refractionTexture.get(), RenderTextureLayout::GENERAL),
            RenderTextureBarrier(rtResources->normalRoughnessTexture[rtResources->swapBuffers ? 1 : 0].get(), RenderTextureLayout::GENERAL),
        };

        worker->commandList->barriers(RenderBarrierStage::COMPUTE, shadingBarriers, uint32_t(std::size(shadingBarriers)));

        // Dispatch rays for direct light.
        RT64_LOG_PRINTF("Dispatching direct light rays");
        rtResources->shaderBindingTableInfo.groups.rayGen.startIndex = 1;
        worker->commandList->traceRays(rtResources->textureWidth, rtResources->textureHeight, 1, rtResources->shaderBindingTableBuffer->at(0), rtResources->shaderBindingTableInfo.groups);

        // Dispatch rays for indirect light.
        RT64_LOG_PRINTF("Dispatching indirect light rays");
        rtResources->shaderBindingTableInfo.groups.rayGen.startIndex = 2;
        worker->commandList->traceRays(rtResources->textureWidth, rtResources->textureHeight, 1, rtResources->shaderBindingTableBuffer->at(0), rtResources->shaderBindingTableInfo.groups);

        // Wait until indirect light is done before dispatching reflection or refraction rays.
        // TODO: This is only required to prevent simultaneous usage of the anyhit buffers.
        // This barrier can be removed if this no longer happens, resulting in less serialization of the commands.
        worker->commandList->barriers(RenderBarrierStage::COMPUTE, RenderTextureBarrier(rtResources->indirectLightTexture[rtResources->swapBuffers ? 1 : 0].get(), RenderTextureLayout::GENERAL));

        // Dispatch rays for refraction.
        RT64_LOG_PRINTF("Dispatching refraction rays");
        rtResources->shaderBindingTableInfo.groups.rayGen.startIndex = 4;
        worker->commandList->traceRays(rtResources->textureWidth, rtResources->textureHeight, 1, rtResources->shaderBindingTableBuffer->at(0), rtResources->shaderBindingTableInfo.groups);

        // Wait until refraction is done before dispatching reflection rays.
        // TODO: This is only required to prevent simultaneous usage of the anyhit buffers.
        // This barrier can be removed if this no longer happens, resulting in less serialization of the commands.
        worker->commandList->barriers(RenderBarrierStage::COMPUTE, RenderTextureBarrier(rtResources->refractionTexture.get(), RenderTextureLayout::GENERAL));

        // Reflection passes.
        int reflections = rtResources->maxReflections;
        while (reflections > 0) {
            // Dispatch rays for reflection.
            RT64_LOG_PRINTF("Dispatching reflection rays");
            rtResources->shaderBindingTableInfo.groups.rayGen.startIndex = 3;
            worker->commandList->traceRays(rtResources->textureWidth, rtResources->textureHeight, 1, rtResources->shaderBindingTableBuffer->at(0), rtResources->shaderBindingTableInfo.groups);
            reflections--;

            // Add a barrier to wait for the input UAVs to be finished if there's more passes left to be done.
            if (reflections > 0) {
                RenderTextureBarrier newInputBarriers[] = {
                    RenderTextureBarrier(rtResources->viewDirectionTexture.get(), RenderTextureLayout::GENERAL),
                    RenderTextureBarrier(rtResources->shadingNormalTexture.get(), RenderTextureLayout::GENERAL),
                    RenderTextureBarrier(rtResources->instanceIdTexture.get(), RenderTextureLayout::GENERAL),
                    RenderTextureBarrier(rtResources->reflectionTexture.get(), RenderTextureLayout::GENERAL)
                };

                worker->commandList->barriers(RenderBarrierStage::COMPUTE, newInputBarriers, uint32_t(std::size(newInputBarriers)));
            }
        }

        // Copy direct light raw buffer to the first direct filtered buffer.
        {
            RenderTexture *source = rtResources->directLightTexture[rtResources->swapBuffers ? 1 : 0].get();
            RenderTexture *dest = rtResources->filteredDirectLightTexture[1].get();

            RenderTextureBarrier beforeCopyBarriers[] = {
                RenderTextureBarrier(source, RenderTextureLayout::COPY_SOURCE),
                RenderTextureBarrier(dest, RenderTextureLayout::COPY_DEST)
            };

            worker->commandList->barriers(RenderBarrierStage::COPY, beforeCopyBarriers, uint32_t(std::size(beforeCopyBarriers)));
            worker->commandList->copyTexture(dest, source);

            RenderTextureBarrier afterCopyBarriers[] = {
                RenderTextureBarrier(source, RenderTextureLayout::GENERAL),
                RenderTextureBarrier(dest, RenderTextureLayout::SHADER_READ)
            };

            worker->commandList->barriers(RenderBarrierStage::COMPUTE, afterCopyBarriers, uint32_t(std::size(afterCopyBarriers)));
        }

        // Copy indirect light raw buffer to the first indirect filtered buffer.
        bool denoiseGI = rtResources->denoiserEnabled && (rtResources->rtParams.giSamples > 0) && (rtResources->upscalerMode != UpscaleMode::DLSS);
        {
            RenderTexture *source = rtResources->indirectLightTexture[rtResources->swapBuffers ? 1 : 0].get();
            RenderTexture *dest = rtResources->filteredIndirectLightTexture[denoiseGI ? 0 : 1].get();

            RenderTextureBarrier beforeCopyBarriers[] = {
                RenderTextureBarrier(source, RenderTextureLayout::COPY_SOURCE),
                RenderTextureBarrier(dest, RenderTextureLayout::COPY_DEST)
            };

            worker->commandList->barriers(RenderBarrierStage::COPY, beforeCopyBarriers, uint32_t(std::size(beforeCopyBarriers)));
            worker->commandList->copyTexture(dest, source);

            RenderTextureBarrier afterCopyBarriers[] = {
                RenderTextureBarrier(source, RenderTextureLayout::GENERAL),
                RenderTextureBarrier(dest, RenderTextureLayout::SHADER_READ)
            };

            worker->commandList->barriers(RenderBarrierStage::COMPUTE, afterCopyBarriers, uint32_t(std::size(afterCopyBarriers)));
        }

        // Apply a gaussian filter to the indirect light with a compute shader.
        if (denoiseGI) {
            for (int i = 0; i < 5; i++) {
                const uint32_t ThreadGroupWorkCount = 8;
                uint32_t dispatchX = (rtResources->textureWidth + ThreadGroupWorkCount - 1) / ThreadGroupWorkCount;
                uint32_t dispatchY = (rtResources->textureHeight + ThreadGroupWorkCount - 1) / ThreadGroupWorkCount;
                const ShaderRecord &gaussianFilter = shaderLibrary->gaussianFilterRGB3x3;
                interop::TextureCB textureCB;
                textureCB.TextureSize = { rtResources->textureWidth, rtResources->textureHeight };
                textureCB.TexelSize = { 1.0f / rtResources->textureWidth, 1.0f / rtResources->textureHeight };

                worker->commandList->setPipeline(gaussianFilter.pipeline.get());
                worker->commandList->setComputePipelineLayout(gaussianFilter.pipelineLayout.get());
                worker->commandList->setComputePushConstants(0, &textureCB);
                worker->commandList->setComputeDescriptorSet(rtResources->indirectFilterSets[i % 2]->get(), 0);
                worker->commandList->dispatch(dispatchX, dispatchY, 1);

                RenderTextureBarrier afterBlurBarriers[] = {
                    RenderTextureBarrier(rtResources->filteredIndirectLightTexture[(i % 2) ? 1 : 0].get(), RenderTextureLayout::GENERAL),
                    RenderTextureBarrier(rtResources->filteredIndirectLightTexture[(i % 2) ? 0 : 1].get(), RenderTextureLayout::SHADER_READ)
                };

                worker->commandList->barriers(RenderBarrierStage::COMPUTE, afterBlurBarriers, uint32_t(std::size(afterBlurBarriers)));
            }
        }

        // Compose the output buffer.
        RenderTexture *rtOutputCur = rtResources->outputTexture[rtResources->swapBuffers ? 1 : 0].get();

        // Barriers for shading buffers after rays are finished.
        RenderTextureBarrier afterDispatchBarriers[] = {
            RenderTextureBarrier(rtOutputCur, RenderTextureLayout::COLOR_WRITE),
            RenderTextureBarrier(colorTarget->texture.get(), RenderTextureLayout::COLOR_WRITE),
            RenderTextureBarrier(rtResources->diffuseTexture.get(), RenderTextureLayout::SHADER_READ),
            RenderTextureBarrier(rtResources->reflectionTexture.get(), RenderTextureLayout::SHADER_READ),
            RenderTextureBarrier(rtResources->refractionTexture.get(), RenderTextureLayout::SHADER_READ),
            RenderTextureBarrier(rtResources->transparentTexture.get(), RenderTextureLayout::SHADER_READ)
        };

        worker->commandList->barriers(RenderBarrierStage::GRAPHICS, afterDispatchBarriers, uint32_t(std::size(afterDispatchBarriers)));

        // Set the output as the current render target.
        worker->commandList->setFramebuffer(rtResources->outputFramebuffer[rtResources->swapBuffers ? 1 : 0].get());

        // Apply the scissor and viewport to the size of the output texture.
        worker->commandList->setViewports(RenderViewport(0.0f, 0.0f, float(rtResources->textureWidth), float(rtResources->textureHeight)));
        worker->commandList->setScissors(RenderRect(0, 0, rtResources->textureWidth, rtResources->textureHeight));

        // Draw the raytracing output.
        RT64_LOG_PRINTF("Composing the raytracing output");
        const ShaderRecord &composeShader = shaderLibrary->compose;
        worker->commandList->setVertexBuffers(0, nullptr, 0, nullptr);
        worker->commandList->setPipeline(composeShader.pipeline.get());
        worker->commandList->setGraphicsPipelineLayout(composeShader.pipelineLayout.get());
        worker->commandList->setGraphicsDescriptorSet(rtResources->composeSet->get(), 0);
        worker->commandList->drawInstanced(3, 1, 0, 0);

        // Switch resources to the correct states after composing the image
        RenderTextureBarrier afterComposeBarriers[] = {
            RenderTextureBarrier(rtOutputCur, RenderTextureLayout::SHADER_READ),
            RenderTextureBarrier(rtResources->filteredDirectLightTexture[1].get(), RenderTextureLayout::GENERAL),
            RenderTextureBarrier(rtResources->filteredIndirectLightTexture[1].get(), RenderTextureLayout::GENERAL),
            RenderTextureBarrier(rtResources->flowTexture.get(), RenderTextureLayout::SHADER_READ),
            RenderTextureBarrier(rtResources->reactiveMaskTexture.get(), RenderTextureLayout::SHADER_READ),
            RenderTextureBarrier(rtResources->lockMaskTexture.get(), RenderTextureLayout::SHADER_READ)
        };

        worker->commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE, afterComposeBarriers, uint32_t(std::size(afterComposeBarriers)));

        const bool lumaActive = rtScene.presetScene.luminanceRange > 0.0f;
        if (lumaActive) {
            const uint32_t ThreadGroupWorkRegionDim = 8;
            worker->commandList->barriers(RenderBarrierStage::COMPUTE, RenderTextureBarrier(rtResources->downscaledOutputTexture.get(), RenderTextureLayout::GENERAL));

            RT64_LOG_PRINTF("Do the downscaling shader");
            {
                // Execute the compute shader for downscaling the image.
                const ShaderRecord &bicubicScaling = shaderLibrary->bicubicScaling;
                uint32_t dispatchX = ((rtResources->textureWidth / 8) + ThreadGroupWorkRegionDim - 1) / ThreadGroupWorkRegionDim;
                uint32_t dispatchY = ((rtResources->textureHeight / 8) + ThreadGroupWorkRegionDim - 1) / ThreadGroupWorkRegionDim;
                interop::BicubicCB bicubicCB;
                bicubicCB.InputResolution = { rtResources->textureWidth, rtResources->textureHeight };
                bicubicCB.OutputResolution = { rtResources->textureWidth / 8, rtResources->textureHeight / 8 };
                worker->commandList->setPipeline(bicubicScaling.pipeline.get());
                worker->commandList->setComputePipelineLayout(bicubicScaling.pipelineLayout.get());
                worker->commandList->setComputePushConstants(0, &bicubicCB);
                worker->commandList->setComputeDescriptorSet(rtResources->downscaleSet->get(), 0);
                worker->commandList->dispatch(dispatchX, dispatchY, 1);
            }


            worker->commandList->barriers(RenderBarrierStage::COMPUTE, RenderTextureBarrier(rtResources->downscaledOutputTexture.get(), RenderTextureLayout::GENERAL));

            RT64_LOG_PRINTF("Do the luminance histogram shader");
            {
                // Execute the compute shader for the luminance histogram.
                const ShaderRecord &luminanceHistogram = shaderLibrary->luminanceHistogram;
                uint32_t dispatchX = ((rtResources->textureWidth / 8) + ThreadGroupWorkRegionDim - 1) / ThreadGroupWorkRegionDim;
                uint32_t dispatchY = ((rtResources->textureHeight / 8) + ThreadGroupWorkRegionDim - 1) / ThreadGroupWorkRegionDim;
                interop::LuminanceHistogramCB histogramCB;
                histogramCB.inputWidth = rtResources->textureWidth / 8;
                histogramCB.inputHeight = rtResources->textureHeight / 8;
                histogramCB.minLuminance = rtScene.presetScene.minLuminance;
                histogramCB.oneOverLuminanceRange = 1.0f / rtScene.presetScene.luminanceRange;
                worker->commandList->setPipeline(luminanceHistogram.pipeline.get());
                worker->commandList->setComputePipelineLayout(luminanceHistogram.pipelineLayout.get());
                worker->commandList->setComputePushConstants(0, &histogramCB);
                worker->commandList->setComputeDescriptorSet(rtResources->lumaSet->get(), 0);
                worker->commandList->dispatch(dispatchX, dispatchY, 1);
            }

            worker->commandList->barriers(RenderBarrierStage::COMPUTE, RenderTextureBarrier(rtResources->downscaledOutputTexture.get(), RenderTextureLayout::SHADER_READ));

            RT64_LOG_PRINTF("Do the luminance average shader");
            {
                // Execute the compute shader for the luminance histogram average.
                const ShaderRecord &histogramAverage = shaderLibrary->histogramAverage;
                interop::HistogramAverageCB averageCB;
                averageCB.pixelCount = (rtResources->textureWidth / 8) * (rtResources->textureHeight / 8);
                averageCB.minLuminance = rtScene.presetScene.minLuminance;
                averageCB.luminanceRange = rtScene.presetScene.luminanceRange;
                averageCB.timeDelta = rtScene.deltaTime;
                averageCB.tau = rtScene.presetScene.lumaUpdateTime;
                worker->commandList->barriers(RenderBarrierStage::COMPUTE, RenderTextureBarrier(rtResources->lumaAverageTexture.get(), RenderTextureLayout::GENERAL));
                worker->commandList->setPipeline(histogramAverage.pipeline.get());
                worker->commandList->setComputePipelineLayout(histogramAverage.pipelineLayout.get());
                worker->commandList->setComputePushConstants(0, &averageCB);
                worker->commandList->setComputeDescriptorSet(rtResources->lumaAvgSet->get(), 0);
                worker->commandList->dispatch(ThreadGroupWorkRegionDim, ThreadGroupWorkRegionDim, 1);
                worker->commandList->barriers(RenderBarrierStage::COMPUTE, RenderTextureBarrier(rtResources->lumaAverageTexture.get(), RenderTextureLayout::SHADER_READ));
            }

            RT64_LOG_PRINTF("Do the histogram clear shader");
            {
                // Execute the compute shader for clearing the luminance histogram.
                const ShaderRecord &histogramClear = shaderLibrary->histogramClear;
                worker->commandList->setPipeline(histogramClear.pipeline.get());
                worker->commandList->setComputePipelineLayout(histogramClear.pipelineLayout.get());
                worker->commandList->setComputeDescriptorSet(rtResources->lumaClearSet->get(), 0);
                worker->commandList->dispatch(ThreadGroupWorkRegionDim, ThreadGroupWorkRegionDim, 1);
            }
        }
        else {
            RT64_LOG_PRINTF("Do the histogram set shader");
            {
                // Execute the compute shader for setting the luminance value.
                const ShaderRecord &histogramSet = shaderLibrary->histogramSet;
                interop::HistogramSetCB setCB;
                setCB.luminanceValue = rtScene.presetScene.minLuminance;
                worker->commandList->barriers(RenderBarrierStage::COMPUTE, RenderTextureBarrier(rtResources->lumaAverageTexture.get(), RenderTextureLayout::GENERAL));
                worker->commandList->setPipeline(histogramSet.pipeline.get());
                worker->commandList->setComputePipelineLayout(histogramSet.pipelineLayout.get());
                worker->commandList->setComputePushConstants(0, &setCB);
                worker->commandList->setComputeDescriptorSet(rtResources->lumaSetSet->get(), 0);
                worker->commandList->dispatch(1, 1, 1);
                worker->commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE, RenderTextureBarrier(rtResources->lumaAverageTexture.get(), RenderTextureLayout::SHADER_READ));
            }
        }

        Upscaler *upscaler = rtResources->getUpscaler(rtResources->upscalerMode);
        const bool upscalerActive = rtResources->upscaleActive && (upscaler != nullptr);
        if (upscalerActive) {
            thread_local std::vector<RenderTextureBarrier> beforeBarriers;
            thread_local std::vector<RenderTextureBarrier> afterBarriers;
            beforeBarriers.clear();
            afterBarriers.clear();

            beforeBarriers.push_back(RenderTextureBarrier(rtResources->upscaledOutputTexture.get(), RenderTextureLayout::GENERAL));
            afterBarriers.push_back(RenderTextureBarrier(rtResources->upscaledOutputTexture.get(), RenderTextureLayout::SHADER_READ));
            RenderTexture *rtDepthCur = rtResources->depthTexture[rtResources->swapBuffers ? 1 : 0].get();
            if (upscaler->requiresNonShaderResourceInputs()) {
                for (RenderTexture *res : { rtOutputCur, rtResources->flowTexture.get(), rtResources->reactiveMaskTexture.get(), rtResources->lockMaskTexture.get(), rtDepthCur }) {
                    beforeBarriers.push_back(RenderTextureBarrier(res, RenderTextureLayout::SHADER_READ));
                    afterBarriers.push_back(RenderTextureBarrier(res, RenderTextureLayout::SHADER_READ));
                }
            }

            worker->commandList->barriers(RenderBarrierStage::COMPUTE, beforeBarriers);

            Upscaler::UpscaleParameters params;
            params.inRect = { 0, 0, static_cast<int>(rtResources->textureWidth), static_cast<int>(rtResources->textureHeight) };
            params.inDiffuseAlbedo = rtResources->diffuseTexture.get();
            params.inSpecularAlbedo = rtResources->shadingSpecularTexture.get();
            params.inNormalRoughness = rtResources->normalRoughnessTexture[rtResources->swapBuffers ? 1 : 0].get();
            params.inColor = rtOutputCur;
            params.inFlow = rtResources->flowTexture.get();
            params.inReactiveMask = rtResources->upscalerReactiveMask ? rtResources->reactiveMaskTexture.get() : nullptr;
            params.inLockMask = rtResources->upscalerLockMask ? rtResources->lockMaskTexture.get() : nullptr;
            params.inDepth = rtDepthCur;
            params.outColor = rtResources->upscaledOutputTexture.get();
            params.jitterX = -rtResources->rtParams.pixelJitter.x;
            params.jitterY = -rtResources->rtParams.pixelJitter.y;
            params.deltaTime = rtScene.deltaTime * 1000.0f;
            params.nearPlane = rtResources->rtParams.nearDist;
            params.farPlane = rtResources->rtParams.farDist;
            params.fovY = rtResources->rtParams.fovRadians;
            params.resetAccumulation = false; // TODO: Make this configurable via the API.
            upscaler->upscale(worker, params);

            worker->commandList->barriers(RenderBarrierStage::GRAPHICS, afterBarriers);
        }

        // Set the final render target. Apply the same scissor and viewport that was determined for the raytracing step.
        worker->commandList->setFramebuffer(colorTarget->textureFramebuffer.get());
        worker->commandList->setViewports(rtScene.viewport);
        worker->commandList->setScissors(rtScene.scissor);
        worker->commandList->setVertexBuffers(0, nullptr, 0, nullptr);

        // Draw final output.
        const ShaderRecord &postProcess = shaderLibrary->postProcess;
        worker->commandList->setPipeline(postProcess.pipeline.get());
        worker->commandList->setGraphicsPipelineLayout(postProcess.pipelineLayout.get());
        worker->commandList->setGraphicsDescriptorSet(rtResources->postProcessSet->get(), 0);
        worker->commandList->drawInstanced(3, 1, 0, 0);

        // Draw debug view on top.
        if (rtResources->rtParams.visualizationMode != interop::VisualizationMode::Final) {
            const ShaderRecord &debugShader = shaderLibrary->debug;
            worker->commandList->setPipeline(debugShader.pipeline.get());
            worker->commandList->setGraphicsPipelineLayout(debugShader.pipelineLayout.get());
            worker->commandList->setGraphicsDescriptorSet(descCommonSet->get(), 0);
            worker->commandList->setGraphicsDescriptorSet(descTextureSet->get(), 1);
            worker->commandList->setGraphicsDescriptorSet(descTextureSet->get(), 2);
            worker->commandList->setGraphicsDescriptorSet(descRealFbSet, 3);
            worker->commandList->drawInstanced(3, 1, 0, 0);
        }

        // Mark targets for resolve.
        colorTarget->markForResolve();
    }
#endif

    void FramebufferRenderer::submitRSPSmoothNormalCompute(RenderWorker *worker, const OutputBuffers *outputBuffers) {
        if (rspSmoothNormalVector.empty()) {
            return;
        }
        
        worker->commandList->barriers(RenderBarrierStage::COMPUTE, RenderBufferBarrier(outputBuffers->worldNormBuffer.buffer.get(), RenderBufferAccess::WRITE));

        const int ThreadGroupSize = 64;
        const auto &rspSmoothNormal = shaderLibrary->rspSmoothNormal;
        for (const RSPSmoothNormalGenerationCB &cb : rspSmoothNormalVector) {
            const uint32_t triangleCount = cb.indexCount / 3;
            const uint32_t dispatchCount = (triangleCount + ThreadGroupSize - 1) / ThreadGroupSize;
            worker->commandList->setPipeline(rspSmoothNormal.pipeline.get());
            worker->commandList->setComputePipelineLayout(rspSmoothNormal.pipelineLayout.get());
            worker->commandList->setComputePushConstants(0, &cb);
            worker->commandList->setComputeDescriptorSet(smoothDescSet->get(), 0);
            worker->commandList->dispatch(dispatchCount, 1, 1);
        }
    }

    void FramebufferRenderer::recordSetup(RenderWorker *worker, std::vector<BufferUploader *> bufferUploaders, RSPProcessor *rspProcessor,
        VertexProcessor *vertexProcessor, const OutputBuffers *outputBuffers, const DrawBuffers *drawBuffers, bool rtEnabled) {
        if (!dummyColorTargetTransitioned) {
            worker->commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE, RenderTextureBarrier(dummyColorTarget.get(), RenderTextureLayout::SHADER_READ));
            dummyColorTargetTransitioned = true;
        }

        if (!dummyDepthTargetTransitioned) {
            worker->commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE, RenderTextureBarrier(dummyDepthTarget.get(), RenderTextureLayout::DEPTH_READ));
            dummyDepthTargetTransitioned = true;
        }

        for (BufferUploader *uploader : bufferUploaders) {
            uploader->commandListBeforeBarriers(worker);
        }

        shaderUploader->commandListBeforeBarriers(worker);

        for (BufferUploader *uploader : bufferUploaders) {
            uploader->commandListCopyResources(worker);
        }

        shaderUploader->commandListCopyResources(worker);

        for (BufferUploader *uploader : bufferUploaders) {
            uploader->commandListAfterBarriers(worker);
        }

        if (rspProcessor != nullptr) {
            rspProcessor->recordCommandList(worker, shaderLibrary, outputBuffers);
        }

        if (vertexProcessor != nullptr) {
            vertexProcessor->recordCommandList(worker, shaderLibrary, outputBuffers);
        }

        for (auto &view : wr64RTViews) {
            auto *rt = &view;
            if (rt->prepared && !rt->rasterReflections && !rt->rasterSky && !rt->raySkyOnly && rt->skyScopeSeen && rt->skyCaptureBuffer) {
                if (rt->skyCaptureArmed) {
                    worker->commandList->barriers(RenderBarrierStage::COPY,
                        RenderBufferBarrier(rt->skyCaptureBuffer.get(), RenderBufferAccess::WRITE));
                    worker->commandList->copyBufferRegion(rt->skyCaptureBuffer->at(0), rt->skyCaptureZero->at(0), Wr64SkyCaptureBytes);
                }
                worker->commandList->barriers(RenderBarrierStage::GRAPHICS,
                    RenderBufferBarrier(rt->skyCaptureBuffer.get(), RenderBufferAccess::WRITE));
            }
    
            if (rt->prepared && rt->traceReflections) {
                if (!rt->scene.recordBuild(worker)) {
                    wr64RTDiagnostic("build-failed", rt->scene.lastError().c_str());
                    // Restore the actual raster pipelines, so fallback does not
                    // depend on mapping constants or binding a failed AS.
                    rt->params.enabled = 0;
                    rt->prepared = false;
                    rt->shadowWaterSelected = false;
                    rt->shoreSelected = 0;
                    rt->aoOnlySelected = 0;
                    for (size_t j = 0; j < rt->nativeWaterPipelines.size(); ++j) {
                        instanceDrawCallVector[rt->waterDraws[j]].triangles.pipeline = rt->nativeWaterPipelines[j];
                    }
                    for (size_t j = 0; j < rt->nativeShorePipelines.size(); ++j) {
                        instanceDrawCallVector[rt->shoreDraws[j]].triangles.pipeline = rt->nativeShorePipelines[j];
                    }
                }
            }
        }

#   if RT_ENABLED
        if (rtEnabled) {
            assert(rtResources != nullptr);
            if (!rtResources->bottomLevelASVector.empty()) {
                if (!rspSmoothNormalVector.empty()) {
                    submitRSPSmoothNormalCompute(worker, outputBuffers);
                }

                rtResources->submitBottomLevelASCreation(worker);
                rtResources->submitTopLevelASCreation(worker);
            }
        }
#   endif

        shaderUploader->commandListAfterBarriers(worker);
        pendingUploaders = bufferUploaders;

        if (!dynamicTextureBarrierVector.empty()) {
            worker->commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE, dynamicTextureBarrierVector);
        }

        // Capture physical silhouettes from the light after all presentation
        // geometry and textures are ready. The depth map uses its own viewport;
        // native raster scissors are restored by submitRasterScene below.
        for (auto &view : wr64RTViews) {
            if (!view.rasterShadows || !view.prepared || !view.shadowWaterSelected) continue;
            auto &map = view.rasterShadowTarget;
            worker->commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE,
                RenderBufferBarrier(outputBuffers->worldPosBuffer.buffer.get(), RenderBufferAccess::READ));
            const RenderBufferBarrier vertexReads[] = {
                RenderBufferBarrier(outputBuffers->genTexCoordBuffer.buffer.get(), RenderBufferAccess::READ),
                RenderBufferBarrier(outputBuffers->shadedColBuffer.buffer.get(), RenderBufferAccess::READ),
                RenderBufferBarrier(drawBuffers->faceIndicesBuffer.defaultBuffer.get(), RenderBufferAccess::READ)
            };
            worker->commandList->barriers(RenderBarrierStage::GRAPHICS, vertexReads, uint32_t(std::size(vertexReads)));
            const RenderTextureBarrier targets[] = {
                RenderTextureBarrier(map.color(), RenderTextureLayout::COLOR_WRITE),
                RenderTextureBarrier(map.depth(), RenderTextureLayout::DEPTH_WRITE)
            };
            worker->commandList->barriers(RenderBarrierStage::GRAPHICS, targets, uint32_t(std::size(targets)));
            worker->commandList->setFramebuffer(map.framebuffer());
            worker->commandList->clearColor(0, RenderColor(1, 1, 1, 1));
            worker->commandList->clearDepth(true, 1.0f);
            worker->commandList->setGraphicsPipelineLayout(rendererPipelineLayout);
            worker->commandList->setGraphicsDescriptorSet(view.descriptor->get(), 0);
            worker->commandList->setGraphicsDescriptorSet(descTextureSet->get(), 1);
            worker->commandList->setGraphicsDescriptorSet(descTextureSet->get(), 2);
            worker->commandList->setGraphicsDescriptorSet(framebufferVector[view.framebuffer].descDummyFbSet->get(), 3);
            worker->commandList->setViewports(RenderViewport(0, 0, 1024, 1024));
            worker->commandList->setScissors(RenderRect(0, 0, 1024, 1024));
            worker->commandList->setVertexBuffers(0, indexedVertexViews.data(), uint32_t(indexedVertexViews.size()), vertexInputSlots.data());
            worker->commandList->setIndexBuffer(&indexBufferView);
            worker->commandList->setPipeline(wr64RasterShadowPipelines.capture());
            for (const auto &caster : view.rasterShadowCasters) {
                interop::RasterParams params{};
                params.renderIndex = caster.drawIndex;
                params.padding.x = caster.shadowFlags;
                params.screenScale = instanceDrawCallVector[caster.drawIndex].triangles.screenScale;
                params.screenOffset = instanceDrawCallVector[caster.drawIndex].triangles.screenOffset;
                worker->commandList->setGraphicsPushConstants(0, &params);
                worker->commandList->drawIndexedInstanced(caster.indexCount, 1, caster.faceIndicesStart, 0, 0);
            }
            worker->commandList->setFramebuffer(nullptr);
            worker->commandList->barriers(RenderBarrierStage::GRAPHICS,
                RenderTextureBarrier(map.color(), RenderTextureLayout::SHADER_READ));
            view.shadowMapRecorded = true;
        }

        if (wr64RTDiagnosticEnabled()) {
            static thread_local std::array<uint32_t, 2> previousStates = {UINT32_MAX, UINT32_MAX};
            for (uint32_t index = 0; index < wr64RTViews.size(); ++index) {
                const auto &view = wr64RTViews[index];
                auto &previous = previousStates[index];
                const uint32_t state = uint32_t(view.rasterShadows) | (uint32_t(view.prepared) << 1) |
                    (uint32_t(view.shadowMapRecorded) << 2) | (uint32_t(view.shadowWaterSelected) << 3) |
                    (view.nativeRaceView << 4);
                if (state != previous && (view.rasterShadows || (previous != UINT32_MAX && (previous & 1u)))) {
                    char detail[256];
                    std::snprintf(detail, sizeof(detail),
                        "native_view=%u scope=%u ready=%u captured=%u water=%zu shore=%u casters=%zu actor_mask=%u map=1024 ray_scene=%u",
                        view.nativeRaceView, unsigned(view.rasterShadows), unsigned(view.prepared), unsigned(view.shadowMapRecorded),
                        view.waterDraws.size(), view.shoreSelected, view.rasterShadowCasters.size(),
                        view.rasterShadowRacers, unsigned(view.traceReflections));
                    wr64RTDiagnostic("raster-shadow", detail);
                }
                previous = state;
            }
        }

        // Capture only after all presentation geometry, draw parameters and
        // native sky textures are uploaded. Each workload owns its target until
        // its normal completion fence, just like its water vertex buffers.
        for (auto &view : wr64RTViews) {
            if (!view.rasterSky || !view.prepared || !view.shadowWaterSelected) continue;
            auto &sky = view.rasterSkyTarget;
            // RSP output UV/color streams normally serve as vertex inputs. The
            // sky lookup also reads them (and face indices) as pixel-shader SRVs.
            const RenderBufferBarrier skyReads[] = {
                RenderBufferBarrier(outputBuffers->worldPosBuffer.buffer.get(), RenderBufferAccess::READ),
                RenderBufferBarrier(outputBuffers->genTexCoordBuffer.buffer.get(), RenderBufferAccess::READ),
                RenderBufferBarrier(outputBuffers->shadedColBuffer.buffer.get(), RenderBufferAccess::READ),
                RenderBufferBarrier(drawBuffers->faceIndicesBuffer.defaultBuffer.get(), RenderBufferAccess::READ)
            };
            worker->commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE, skyReads, uint32_t(std::size(skyReads)));
            worker->commandList->barriers(RenderBarrierStage::GRAPHICS,
                RenderTextureBarrier(sky.texture(), RenderTextureLayout::COLOR_WRITE));
            worker->commandList->setFramebuffer(sky.framebuffer());
            worker->commandList->setGraphicsPipelineLayout(rendererPipelineLayout);
            worker->commandList->setGraphicsDescriptorSet(view.descriptor->get(), 0);
            worker->commandList->setGraphicsDescriptorSet(descTextureSet->get(), 1);
            worker->commandList->setGraphicsDescriptorSet(descTextureSet->get(), 2);
            worker->commandList->setGraphicsDescriptorSet(framebufferVector[view.framebuffer].descDummyFbSet->get(), 3);
            worker->commandList->setViewports(RenderViewport(0, 0, float(sky.width()), float(sky.height())));
            worker->commandList->setScissors(RenderRect(0, 0, sky.width(), sky.height()));
            worker->commandList->setPipeline(wr64RasterSkyPipelines.capture());
            worker->commandList->drawInstanced(3, 1, 0, 0);
            worker->commandList->setFramebuffer(nullptr);
            worker->commandList->barriers(RenderBarrierStage::GRAPHICS,
                RenderTextureBarrier(sky.texture(), RenderTextureLayout::SHADER_READ));
            const RenderBufferBarrier vertexReads[] = {
                RenderBufferBarrier(outputBuffers->genTexCoordBuffer.buffer.get(), RenderBufferAccess::READ),
                RenderBufferBarrier(outputBuffers->shadedColBuffer.buffer.get(), RenderBufferAccess::READ),
                RenderBufferBarrier(drawBuffers->faceIndicesBuffer.defaultBuffer.get(), RenderBufferAccess::READ)
            };
            worker->commandList->barriers(RenderBarrierStage::GRAPHICS, vertexReads, uint32_t(std::size(vertexReads)));
        }

        // Reflect current presentation geometry about the native mean sea
        // plane. This pass owns its color/depth targets and never samples the
        // active scene framebuffer or requires an acceleration structure.
        for (auto &view : wr64RTViews) {
            if (!view.rasterReflections || !view.prepared || !view.shadowWaterSelected) continue;
            auto &capture = view.rasterReflectionTarget;
            const RenderBufferBarrier reads[] = {
                RenderBufferBarrier(outputBuffers->worldPosBuffer.buffer.get(), RenderBufferAccess::READ),
                RenderBufferBarrier(outputBuffers->genTexCoordBuffer.buffer.get(), RenderBufferAccess::READ),
                RenderBufferBarrier(outputBuffers->shadedColBuffer.buffer.get(), RenderBufferAccess::READ),
                RenderBufferBarrier(drawBuffers->faceIndicesBuffer.defaultBuffer.get(), RenderBufferAccess::READ)
            };
            worker->commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE, reads, uint32_t(std::size(reads)));
            const RenderTextureBarrier targets[] = {
                RenderTextureBarrier(capture.color(), RenderTextureLayout::COLOR_WRITE),
                RenderTextureBarrier(capture.depth(), RenderTextureLayout::DEPTH_WRITE)
            };
            worker->commandList->barriers(RenderBarrierStage::GRAPHICS, targets, uint32_t(std::size(targets)));
            worker->commandList->setFramebuffer(capture.framebuffer());
            worker->commandList->clearColor(0, RenderColor(0, 0, 0, 0));
            worker->commandList->clearDepth(true, 1.0f);
            worker->commandList->setGraphicsPipelineLayout(rendererPipelineLayout);
            worker->commandList->setGraphicsDescriptorSet(view.descriptor->get(), 0);
            worker->commandList->setGraphicsDescriptorSet(descTextureSet->get(), 1);
            worker->commandList->setGraphicsDescriptorSet(descTextureSet->get(), 2);
            worker->commandList->setGraphicsDescriptorSet(framebufferVector[view.framebuffer].descDummyFbSet->get(), 3);
            worker->commandList->setViewports(RenderViewport(0, 0, float(capture.width()), float(capture.height())));
            worker->commandList->setScissors(RenderRect(0, 0, capture.width(), capture.height()));
            worker->commandList->setVertexBuffers(0, indexedVertexViews.data(), uint32_t(indexedVertexViews.size()), vertexInputSlots.data());
            worker->commandList->setIndexBuffer(&indexBufferView);
            for (const auto &object : view.rasterReflectors) {
                const auto &triangles = instanceDrawCallVector[object.drawIndex].triangles;
                worker->commandList->setPipeline(wr64RasterReflectionPipelines.capture(triangles.shaderDesc.flags.culling));
                interop::RasterParams params{};
                params.renderIndex = object.drawIndex;
                params.padding.x = object.shadowFlags;
                params.screenScale = triangles.screenScale;
                params.screenOffset = triangles.screenOffset;
                worker->commandList->setGraphicsPushConstants(0, &params);
                worker->commandList->drawIndexedInstanced(object.indexCount, 1, object.faceIndicesStart, 0, 0);
            }
            worker->commandList->setFramebuffer(nullptr);
            worker->commandList->barriers(RenderBarrierStage::GRAPHICS,
                RenderTextureBarrier(capture.color(), RenderTextureLayout::SHADER_READ));
            view.reflectionCaptureRecorded = true;
        }
        if (wr64RTDiagnosticEnabled()) {
            static thread_local std::array<uint32_t, 2> previousStates = {UINT32_MAX, UINT32_MAX};
            for (uint32_t index = 0; index < wr64RTViews.size(); ++index) {
                const auto &view = wr64RTViews[index];
                auto &previous = previousStates[index];
                const uint32_t state = uint32_t(view.rasterReflections) | (uint32_t(view.prepared) << 1) |
                    (uint32_t(view.reflectionCaptureRecorded) << 2) | (uint32_t(view.shadowWaterSelected) << 3) |
                    (view.nativeRaceView << 4);
                if (state != previous && (view.rasterReflections || (previous != UINT32_MAX && (previous & 1u)))) {
                    char detail[256];
                    std::snprintf(detail, sizeof(detail),
                        "native_view=%u scope=%u ready=%u captured=%u water=%zu objects=%zu size=%ux%u plane=%.2f plane_valid=%u ray_scene=%u",
                        view.nativeRaceView, unsigned(view.rasterReflections), unsigned(view.prepared), unsigned(view.reflectionCaptureRecorded),
                        view.waterDraws.size(), view.rasterReflectors.size(), view.rasterReflectionTarget.width(),
                        view.rasterReflectionTarget.height(), view.reflectionPlaneY, unsigned(view.reflectionPlaneValid),
                        unsigned(view.traceReflections));
                    wr64RTDiagnostic("raster-reflection", detail);
                }
                previous = state;
            }
        }

        // The new combined/sky-only D3D12 shaders read native vertex streams as
        // SRVs as well as IA inputs. COMMON permits promotion to both read states
        // without changing the established RT path or its backend abstractions.
        const bool mixedReads = std::any_of(wr64RTViews.begin(), wr64RTViews.end(), [](const auto &view) {
            return view.prepared && ((view.traceReflections && (view.rasterSky || view.raySkyOnly)) ||
                view.rasterShadows || view.rasterReflections);
        });
        if (mixedReads) {
            const RenderBufferBarrier reads[] = {
                RenderBufferBarrier(outputBuffers->genTexCoordBuffer.buffer.get(), RenderBufferAccess::READ),
                RenderBufferBarrier(outputBuffers->shadedColBuffer.buffer.get(), RenderBufferAccess::READ),
                RenderBufferBarrier(drawBuffers->faceIndicesBuffer.defaultBuffer.get(), RenderBufferAccess::READ)
            };
            worker->commandList->barriers(RenderBarrierStage::COMPUTE, reads, uint32_t(std::size(reads)));
        }
    }

    void FramebufferRenderer::recordFramebuffer(RenderWorker *worker, uint32_t framebufferIndex) {
        // Submit all transition barriers first.
        thread_local std::vector<RenderTextureBarrier> startBarriers;
        startBarriers.clear();

        const Framebuffer &framebuffer = framebufferVector[framebufferIndex];
        for (RenderTarget *target : framebuffer.transitionRenderTargetSet) {
            startBarriers.emplace_back(RenderTextureBarrier(target->getResolvedTexture(), RenderTextureLayout::SHADER_READ));
        }
        
        const RenderTargetDrawCall &targetDrawCall = framebuffer.renderTargetDrawCall;
        RenderTarget *colorTarget = targetDrawCall.fbStorage->colorTarget;
        RenderTarget *depthTarget = targetDrawCall.fbStorage->depthTarget;
        if (colorTarget != nullptr) {
            startBarriers.emplace_back(RenderTextureBarrier(colorTarget->texture.get(), RenderTextureLayout::COLOR_WRITE));
        }

        startBarriers.emplace_back(RenderTextureBarrier(depthTarget->texture.get(), RenderTextureLayout::DEPTH_WRITE));
        worker->commandList->barriers(RenderBarrierStage::GRAPHICS, startBarriers);

        bool depthState = false;
        worker->commandList->setFramebuffer(targetDrawCall.fbStorage->colorDepthWrite.get());
        for (const auto &pair : targetDrawCall.sceneIndices) {
#       if RT_ENABLED
            if (pair.second) {
                const auto &rtScene = targetDrawCall.rtScenes[pair.first];

                // Draw all the interleaved rasterized buffers that will be used in the render target.
                thread_local std::vector<RenderTextureBarrier> interleavedBarriers;
                interleavedBarriers.clear();
                for (uint32_t i = 0; i < interleavedRastersCount; i++) {
                    bool interleavedDepthState = false;
                    const uint32_t sceneIndex = rtScene.interleavedRasters[i].rasterSceneIndex;
                    RenderTarget *colorRenderTarget = rtResources->interleavedColorTargetVector[i].get();
                    RenderTarget *depthRenderTarget = rtResources->interleavedDepthTargetVector[i].get();
                    worker->commandList->barriers(RenderBarrierStage::GRAPHICS, {
                        RenderTextureBarrier(colorRenderTarget->texture.get(), RenderTextureLayout::COLOR_WRITE),
                        RenderTextureBarrier(depthRenderTarget->texture.get(), RenderTextureLayout::DEPTH_WRITE)
                    });

                    RenderFramebufferStorage *fbStorage = rtResources->interleavedFramebufferStorageVector[i].get();
                    worker->commandList->setFramebuffer(fbStorage->colorDepthWrite.get());
                    worker->commandList->clearColor();
                    worker->commandList->clearDepth();

                    submitDepthAccess(worker, fbStorage, false, interleavedDepthState);
                    submitRasterScene(worker, framebuffer, fbStorage, targetDrawCall.rasterScenes[sceneIndex], interleavedDepthState);

                    // Resolve the interleaved scene.
                    // TODO: Depth textures need to be thrown into a separate view vector for multisampled textures.
                    fbStorage->colorTarget->resolveTarget(worker, shaderLibrary);

                    interleavedBarriers.emplace_back(RenderTextureBarrier(colorRenderTarget->texture.get(), RenderTextureLayout::SHADER_READ));
                    interleavedBarriers.emplace_back(RenderTextureBarrier(depthRenderTarget->texture.get(), RenderTextureLayout::DEPTH_READ));
                }

                if (!interleavedBarriers.empty()) {
                    worker->commandList->barriers(RenderBarrierStage::COMPUTE, interleavedBarriers);
                }

                submitDepthAccess(worker, targetDrawCall.fbStorage, true, depthState);
                submitRaytracingScene(worker, targetDrawCall.fbStorage->colorTarget, rtScene);
            }
            else
#       endif
            {
                const RasterScene &rasterScene = targetDrawCall.rasterScenes[pair.first];
                submitDepthAccess(worker, targetDrawCall.fbStorage, false, depthState);
                submitRasterScene(worker, framebuffer, targetDrawCall.fbStorage, rasterScene, depthState);
            }
        }
    }

    void FramebufferRenderer::waitForUploaders() {
        shaderUploader->wait();

        for (BufferUploader *uploader : pendingUploaders) {
            uploader->wait();
        }
    }

#if RT_ENABLED
    void FramebufferRenderer::setRaytracingConfig(const RaytracingConfiguration &rtConfig, bool resolutionChanged) {
        assert(rtResources != nullptr);
        rtResources->setRaytracingConfig(rtConfig, resolutionChanged);
    }
#endif

    void FramebufferRenderer::addFramebuffer(const DrawParams &p) {
        auto *rt = &wr64RTViews[0];
        const bool wr64RTTwoPlayer = p.curWorkload->wr64RtTwoPlayerScope;
        const bool wr64RTBackendAllowed = !wr64RTTwoPlayer || wr64RTShaderFormat == RenderShaderFormat::DXIL;

        wr64MotionDiagnostic.workload = p.curWorkload->workloadId;
        wr64MotionDiagnostic.present = p.curWorkload->presentId;
        wr64MotionDiagnostic.course = p.curWorkload->wr64RtCourse;
        wr64MotionDiagnostic.menu = p.curWorkload->wr64RtMenuReflectionScope;
        wr64MotionDiagnostic.paused = p.curWorkload->paused || p.curWorkload->wr64PauseOwner;
        assert(p.fbStorage != nullptr);
        
        // Setup framebuffer pair data and descriptor set.
        const FramebufferPair &fbPair = p.curWorkload->fbPairs[p.fbPairIndex];

        // [WR64] REBUILD THE TWO-PLAYER LATCHES ON THIS THREAD.
        //
        // wr64TwoPFrameActive() and wr64TwoPFrameHalf() are thread_local and are
        // written in rt64_rdp.cpp, at RDP decode, on a thread that is not this
        // one. Read from here they were false and 0 for the life of the process,
        // which silently disabled every two-player HUD, gantry and banner
        // correction. See the long note in rt64_wr64_2p_frame.h - the one-in-ten
        // reading in wr64-banner-20260801_190705.csv is the measurement.
        //
        // The scan is over the WHOLE workload rather than this one pair, because
        // the shared HUD's pair need not be the pair that carries the two scene
        // projections. It runs once per workload per thread; a workload holds
        // tens of projections, so this is a few hundred integer compares a frame.
        {
            static thread_local uint64_t wr64TwoPScannedFrame = ~uint64_t(0);
            static thread_local bool wr64TwoPScannedResult = false;
            if (wr64TwoPScannedFrame != p.curWorkload->submissionFrame) {
                bool wr64SawP1 = false;
                bool wr64SawP2 = false;
                // fbPairCount and projectionCount are HIGH-WATER MARKS over
                // vectors that are reused between frames, so both are clamped to
                // the container rather than trusted. No std::min: this file gets
                // <algorithm> transitively and an include that arrives by
                // accident has already cost this project one build.
                uint32_t wr64PairCount = p.curWorkload->fbPairCount;
                if (wr64PairCount > uint32_t(p.curWorkload->fbPairs.size())) {
                    wr64PairCount = uint32_t(p.curWorkload->fbPairs.size());
                }
                for (uint32_t wr64Pi = 0; wr64Pi < wr64PairCount; wr64Pi++) {
                    const FramebufferPair &wr64Pair = p.curWorkload->fbPairs[wr64Pi];
                    uint32_t wr64ProjCount = wr64Pair.projectionCount;
                    if (wr64ProjCount > uint32_t(wr64Pair.projections.size())) {
                        wr64ProjCount = uint32_t(wr64Pair.projections.size());
                    }
                    for (uint32_t wr64Pr = 0; wr64Pr < wr64ProjCount; wr64Pr++) {
                        const FixedRect &wr64Sci = wr64Pair.projections[wr64Pr].scissorRect;
                        int wr64Half = 0;
                        if (wr64TwoPFrameIsHalfScissor(wr64Sci.ulx, wr64Sci.uly,
                                wr64Sci.lrx, wr64Sci.lry, wr64Half)) {
                            if (wr64Half == 1) { wr64SawP1 = true; }
                            else if (wr64Half == 2) { wr64SawP2 = true; }
                        }
                    }
                }
                wr64TwoPScannedFrame = p.curWorkload->submissionFrame;
                wr64TwoPScannedResult = wr64SawP1 && wr64SawP2;
            }
            wr64TwoPFrameRenderWorkload(wr64TwoPScannedResult);
        }

        if (WR64_DIAGNOSTIC_ENABLED) WR64LayerTrace::observeFramebuffer(*p.curWorkload, p.fbPairIndex,
            p.fbWidth, p.fbHeight, p.targetWidth, p.targetHeight);
        interop::FramebufferParams fbParams;
        fbParams.resolution = { p.targetWidth / p.resolutionScale.x, p.targetHeight / p.resolutionScale.y };
        fbParams.resolutionScale = p.resolutionScale;
        fbParams.horizontalMisalignment = p.horizontalMisalignment;
        framebufferCount++;

        while (framebufferCount > framebufferVector.size()) {
            framebufferVector.emplace_back();
            framebufferVector.back().paramsBuffer = p.worker->device->createBuffer(RenderBufferDesc::UploadBuffer(256, RenderBufferFlag::CONSTANT));
            framebufferVector.back().descRealFbSet = std::make_unique<FramebufferRendererDescriptorFramebufferSet>(p.worker->device);
            framebufferVector.back().descDummyFbSet = std::make_unique<FramebufferRendererDescriptorFramebufferSet>(p.worker->device);
        }

        Framebuffer &framebuffer = framebufferVector[framebufferCount - 1];
        void *paramBufferBytes = framebuffer.paramsBuffer->map();
        memcpy(paramBufferBytes, &fbParams, sizeof(interop::FramebufferParams));
        framebuffer.paramsBuffer->unmap();

        RenderTexture *backgroundColorTexture = (p.fbStorage->colorTarget != nullptr) ? p.fbStorage->colorTarget->getResolvedTexture() : dummyColorTarget.get();
        RenderTextureView *backgroundColorTextureView = (p.fbStorage->colorTarget != nullptr) ? p.fbStorage->colorTarget->getResolvedTextureView() : dummyColorTargetView.get();
        framebuffer.descRealFbSet->setBuffer(framebuffer.descRealFbSet->FbParams, framebuffer.paramsBuffer.get(), sizeof(interop::FramebufferParams));
        framebuffer.descRealFbSet->setTexture(framebuffer.descRealFbSet->gBackgroundColor, backgroundColorTexture, RenderTextureLayout::SHADER_READ, backgroundColorTextureView);
        framebuffer.descRealFbSet->setTexture(framebuffer.descRealFbSet->gBackgroundDepth, p.fbStorage->depthTarget->texture.get(), RenderTextureLayout::DEPTH_READ, p.fbStorage->depthTarget->textureView.get());
        framebuffer.descDummyFbSet->setBuffer(framebuffer.descDummyFbSet->FbParams, framebuffer.paramsBuffer.get(), sizeof(interop::FramebufferParams));
        framebuffer.descDummyFbSet->setTexture(framebuffer.descDummyFbSet->gBackgroundColor, backgroundColorTexture, RenderTextureLayout::SHADER_READ, backgroundColorTextureView);
        framebuffer.descDummyFbSet->setTexture(framebuffer.descDummyFbSet->gBackgroundDepth, dummyDepthTarget.get(), RenderTextureLayout::DEPTH_READ, dummyDepthTargetView.get());

        // Store ubershader and other effect pipelines.
        const RasterShaderUber *rasterShaderUber = p.rasterShaderCache->getGPUShaderUber();
        rendererPipelineLayout = rasterShaderUber->pipelineLayout.get();
        postBlendDitherNoiseAddPipeline = rasterShaderUber->postBlendDitherNoiseAddPipeline.get();
        postBlendDitherNoiseSubPipeline = rasterShaderUber->postBlendDitherNoiseSubPipeline.get();
        postBlendDitherNoiseSubNegativePipeline = rasterShaderUber->postBlendDitherNoiseSubNegativePipeline.get();

        // Make a new render target draw call.
        RenderTargetDrawCall &targetDrawCall = framebuffer.renderTargetDrawCall;
        const DrawData &drawData = p.curWorkload->drawData;
        const bool wr64FilterDiagnose = wr64UiFilterDiagnosticEnabled();
        const uint32_t wr64FilterSelectedMode = wr64FilterDiagnose ? getWr64UiFilter() : 0;
        static thread_local Wr64UiFilterDiagnosticBudget wr64FilterCandidateBudget, wr64FilterAppliedBudget;
        const bool wr64FilterSummarize = wr64FilterDiagnose &&
            wr64FilterCandidateBudget.observe(p.curWorkload->submissionFrame, wr64FilterSelectedMode, p.fbPairIndex);
        if (wr64FilterDiagnose)
            wr64FilterAppliedBudget.observe(p.curWorkload->submissionFrame, wr64FilterSelectedMode);
        size_t wr64FilterPreparedCount = 0, wr64FilterAppliedCount = 0;
        size_t wr64FilterParameterMismatchCount = 0;
        const DrawBuffers &drawBuffers = p.curWorkload->drawBuffers;
        const OutputBuffers &outputBuffers = p.curWorkload->outputBuffers;
        const RenderBuffer *screenPosRes = outputBuffers.screenPosBuffer.buffer.get();
        const RenderBuffer *tcRes = outputBuffers.genTexCoordBuffer.buffer.get();
        const RenderBuffer *indexRes = drawBuffers.faceIndicesBuffer.get();
        const RenderBuffer *shadedColRes = outputBuffers.shadedColBuffer.buffer.get();
        const RenderBuffer *worldPosRes = outputBuffers.worldPosBuffer.buffer.get();
        const RenderBuffer *worldNormRes = outputBuffers.worldNormBuffer.buffer.get();
        const RenderBuffer *worldVelRes = outputBuffers.worldVelBuffer.buffer.get();
        const RenderBuffer *triPosRes = drawBuffers.triPosBuffer.get();
        const RenderBuffer *triTcRes = drawBuffers.triTcBuffer.get();
        const RenderBuffer *triColRes = drawBuffers.triColorBuffer.get();
        const uint32_t PosStride = sizeof(float) * 4;
        const uint32_t ColStride = sizeof(float) * 4;
        const uint32_t WorldNormStride = sizeof(float) * 4;
        const uint32_t WorldVelStride = sizeof(float) * 4;
        const uint32_t TcStride = sizeof(float) * 2;
        const uint32_t IndexStride = sizeof(uint32_t);
        const uint32_t vertexCount = drawData.vertexCount();
        const uint32_t indexCount = uint32_t(drawData.faceIndices.size());
        const uint32_t rawTriVertexCount = drawData.rawTriVertexCount();
        // Select each native race camera, or the proven live-water menu pane.
        // Water comes from native producer tags, never its color or texture.
        auto wr64IsWater = [&](const GameCall &call) {
            const uint64_t first = call.meshDesc.faceIndicesStart;
            const uint64_t count = uint64_t(call.callDesc.triangleCount) * 3;
            if (!count || first + count > drawData.faceIndices.size()) return false;
            for (uint64_t i = first; i < first + count; ++i) {
                const uint32_t v = drawData.faceIndices[size_t(i)];
                if (v >= drawData.wr64WaterVertexMask.size() || !drawData.wr64WaterVertexMask[v]) return false;
            }
            return true;
        };
        auto wr64HasWater = [&](const GameCall &call) {
            const uint64_t first = call.meshDesc.faceIndicesStart;
            const uint64_t end = first + uint64_t(call.callDesc.triangleCount) * 3;
            if (end > drawData.faceIndices.size()) return true;
            for (uint64_t i = first; i < end; ++i) {
                const uint32_t v = drawData.faceIndices[size_t(i)];
                if (v < drawData.wr64WaterVertexMask.size() && drawData.wr64WaterVertexMask[v]) return true;
            }
            return false;
        };
        auto wr64DrawSources = [&](const GameCall &call, uint32_t *sources, size_t count) {
            const uint64_t first = call.meshDesc.faceIndicesStart;
            if (uint64_t(call.callDesc.triangleCount) * 3 != count ||
                first + count > drawData.faceIndices.size()) return false;
            for (size_t i = 0; i < count; ++i) {
                const uint32_t vertex = drawData.faceIndices[size_t(first) + i];
                if (vertex >= drawData.vertexSegmentedAddresses.size()) return false;
                sources[i] = drawData.vertexSegmentedAddresses[vertex];
            }
            return true;
        };
        auto wr64NextMark = [&](const GameCall &call) {
            std::array<uint32_t, 6> sources{};
            return wr64DrawSources(call, sources.data(), sources.size()) && wr64RTIsNextMark(sources);
        };
        auto wr64BuoyLetter = [&](const GameCall &call) {
            std::array<uint32_t, 6> sources{};
            return wr64DrawSources(call, sources.data(), sources.size()) && wr64RTIsBuoyLetter(sources);
        };
        auto wr64TwilightBeam = [&](const GameCall &call) {
            const auto &d = call.callDesc;
            if (!d.textureOn || !wr64RTTwilightBeamMaterial(d.colorCombiner.L, d.colorCombiner.H,
                d.otherMode.L, d.otherMode.H, d.geometryMode, d.triangleCount, d.tileCount)) return false;
            std::array<uint32_t, 24> sources{};
            return wr64DrawSources(call, sources.data(), sources.size()) &&
                wr64RTTwilightBeamSourceFamily(sources.data(), sources.size()) >= 0;
        };
        auto wr64StaticShoreReceiver = [&](const GameCall &call) {
            const uint64_t first = call.meshDesc.faceIndicesStart;
            const uint64_t count = uint64_t(call.callDesc.triangleCount) * 3;
            if (!count || first + count > drawData.faceIndices.size()) return false;
            for (uint64_t i = first; i < first + count; ++i) {
                const uint32_t vertex = drawData.faceIndices[size_t(i)];
                if (vertex >= drawData.worldIndices.size()) return false;
                const uint32_t world = drawData.worldIndices[vertex];
                if (world >= drawData.worldTransformSegmentedAddresses.size() ||
                    drawData.worldTransformSegmentedAddresses[world] != 0x02000A40) return false;
            }
            return true;
        };
        auto wr64AppendSunnyFenceProxy = [&](const GameCall &call, uint32_t drawIndex) {
            const auto &desc = call.callDesc;
            // Native i_cottage_6 rope/post cards only. Source-family identity
            // below distinguishes them from equally sized wall/START textures.
            if (p.curWorkload->wr64RtCourse != 1 || !desc.textureOn || desc.tileCount != 1 ||
                desc.colorCombiner.L != 0xFC127FFF || desc.colorCombiner.H != 0xFFFFF238 ||
                desc.otherMode.L != 0xC8113078 || desc.otherMode.H != 0x00182CFF ||
                desc.triangleCount == 0 || (desc.triangleCount & 1) ||
                desc.tileIndex >= drawData.callTiles.size()) return;
            const auto &tile = drawData.callTiles[desc.tileIndex];
            const auto &nativeTile = tile.loadTile;
            if (!tile.valid || tile.tileCopyUsed || tile.reinterpretTile ||
                tile.sampleWidth != 64 || tile.sampleHeight != 32 ||
                nativeTile.fmt != G_IM_FMT_RGBA || nativeTile.siz != G_IM_SIZ_16b ||
                nativeTile.cms != G_TX_WRAP || nativeTile.cmt != G_TX_CLAMP ||
                nativeTile.masks != 6 || nativeTile.maskt != 5 ||
                nativeTile.shifts != 0 || nativeTile.shiftt != 0) return;
            const uint64_t first = call.meshDesc.faceIndicesStart;
            const uint64_t count = uint64_t(desc.triangleCount) * 3;
            if (first + count > drawData.faceIndices.size()) return;
            auto identity = [](const interop::float4x4 &matrix) {
                for (uint32_t row = 0; row < 4; ++row)
                    for (uint32_t column = 0; column < 4; ++column)
                        if (float(matrix[row][column]) != (row == column ? 1.0f : 0.0f)) return false;
                return true;
            };
            Wr64RTFenceProxy proxy;
            proxy.drawIndex = drawIndex;
            for (uint64_t face = first; face < first + count; face += 6) {
                std::array<uint32_t, 6> vertices{}, sources{};
                for (size_t i = 0; i < vertices.size(); ++i) {
                    vertices[i] = drawData.faceIndices[size_t(face) + i];
                    if (vertices[i] >= drawData.vertexSegmentedAddresses.size()) return;
                    sources[i] = drawData.vertexSegmentedAddresses[vertices[i]];
                }
                if (!wr64RTIsSunnyFenceQuad(p.curWorkload->wr64RtCourse, sources)) continue;
                const uint32_t sourceFirst = *std::min_element(sources.begin(), sources.end());
                std::array<Wr64RTFenceVertex, 4> quad{};
                std::array<uint32_t, 4> seen{ UINT32_MAX, UINT32_MAX, UINT32_MAX, UINT32_MAX };
                for (size_t i = 0; i < vertices.size(); ++i) {
                    const uint32_t vertex = vertices[i], slot = (sources[i] - sourceFirst) / 16;
                    if (seen[slot] != UINT32_MAX) {
                        if (seen[slot] != vertex) return;
                        continue;
                    }
                    seen[slot] = vertex;
                    const size_t pos = size_t(vertex) * 3, tc = size_t(vertex) * 2;
                    if (vertex >= drawData.worldIndices.size() || vertex >= drawData.lookAtIndices.size() ||
                        pos + 3 > drawData.posFloats.size() || pos + 3 > drawData.velFloats.size() ||
                        tc + 2 > drawData.tcFloats.size() || tc + 2 > drawData.tcVelFloats.size() ||
                        drawData.lookAtIndices[vertex] != 0) return;
                    const uint32_t world = drawData.worldIndices[vertex];
                    if (world >= drawData.worldTransformSegmentedAddresses.size() ||
                        drawData.worldTransformSegmentedAddresses[world] != 0x02000A40 ||
                        world >= drawData.worldTransforms.size() || !identity(drawData.worldTransforms[world]) ||
                        (!drawData.lerpWorldTransforms.empty() &&
                            (world >= drawData.lerpWorldTransforms.size() || !identity(drawData.lerpWorldTransforms[world])))) return;
                    // With no velocity/field/texgen and identity original and
                    // presentation transforms, these CPU inputs are exactly the
                    // current RSPWorld/RSPProcess outputs at every frame weight.
                    // No readback or previous-frame geometry is required.
                    for (size_t component = 0; component < 3; ++component) {
                        if (drawData.velFloats[pos + component] != 0) return;
                        quad[slot].position[component] = drawData.posFloats[pos + component];
                    }
                    if (!drawData.wr64WaterFieldInfo.empty()) {
                        if (size_t(vertex) * 4 + 4 > drawData.wr64WaterFieldInfo.size()) return;
                        for (size_t component = 0; component < 4; ++component)
                            if (drawData.wr64WaterFieldInfo[size_t(vertex) * 4 + component] != 0) return;
                    }
                    for (size_t component = 0; component < 2; ++component) {
                        if (drawData.tcVelFloats[tc + component] != 0) return;
                        quad[slot].uv[component] = drawData.tcFloats[tc + component];
                    }
                    quad[slot].position[3] = 1;
                    // This exact combiner's two alpha outputs use TEXEL0.a;
                    // vertex lighting/fog only changes unused proxy RGB.
                    quad[slot].shade = { 1, 1, 1, 1 };
                }
                Wr64RTFenceExpansionKey expansion;
                for (uint32_t slot = 0; slot < 4; ++slot) expansion.sources[slot] = sourceFirst + slot * 16;
                expansion.material = { p.curWorkload->wr64RtCourse, desc.colorCombiner.L,
                    desc.colorCombiner.H, desc.otherMode.L, desc.otherMode.H, desc.geometryMode };
                expansion.quad = quad;
                if (!wr64RTFenceExpansionCache.append(expansion, proxy)) return;
            }
            if (!proxy.triangles.empty()) rt->fenceProxies.push_back(std::move(proxy));
        };
        auto wr64NativeWaterShadowRacer = [&](const GameCall &call) -> uint32_t {
            const auto &desc = call.callDesc;
            if (desc.triangleCount != 1 || !desc.textureOn || desc.tileCount != 1 ||
                desc.colorCombiner.L != 0xFC127E24 || desc.colorCombiner.H != 0xFFFFF3F9 ||
                desc.otherMode.L != 0x005049D8 || desc.otherMode.H != 0x00082CFF) return UINT32_MAX;
            const uint64_t first = call.meshDesc.faceIndicesStart;
            if (first + 3 > drawData.faceIndices.size()) return UINT32_MAX;
            uint32_t sourceMask = 0, shadowWorld = UINT32_MAX;
            for (uint64_t i = first; i < first + 3; ++i) {
                const uint32_t vertex = drawData.faceIndices[size_t(i)];
                if (vertex >= drawData.vertexSegmentedAddresses.size() ||
                    vertex >= drawData.worldIndices.size()) return UINT32_MAX;
                // func_800694B8 emits DL010068B0, whose sole triangle uses
                // these three vertices and matrix0300F808 + racer*0x40.
                const uint32_t source = drawData.vertexSegmentedAddresses[vertex];
                if (source < 0x010068C8 || source > 0x010068E8 ||
                    (source - 0x010068C8) % 0x10 != 0) return UINT32_MAX;
                sourceMask |= 1u << ((source - 0x010068C8) / 0x10);
                const uint32_t world = drawData.worldIndices[vertex];
                if (shadowWorld != UINT32_MAX && shadowWorld != world) return UINT32_MAX;
                shadowWorld = world;
            }
            if (sourceMask != 7 || shadowWorld >= drawData.worldTransformSegmentedAddresses.size()) return UINT32_MAX;
            const uint32_t matrix = drawData.worldTransformSegmentedAddresses[shadowWorld];
            if (matrix < 0x0300F808 || matrix > 0x0300F8C8 || (matrix - 0x0300F808) % 0x40 != 0) return UINT32_MAX;
            return (matrix - 0x0300F808) / 0x40;
        };
        auto wr64ArticulatedShadowCasterMask = [&](const GameCall &call) -> uint32_t {
            const uint64_t first = call.meshDesc.faceIndicesStart;
            const uint64_t count = uint64_t(call.callDesc.triangleCount) * 3;
            // Only ranges accepted by Wr64RTScene::prepare may replace a blob.
            // Also validate every vertex's native actor-matrix provenance.
            if (!count || count > UINT32_MAX || first + count > rt->indexCount ||
                first + count > drawData.faceIndices.size()) return 0;
            uint32_t racerMask = 0;
            for (uint64_t i = first; i < first + count; ++i) {
                const uint32_t vertex = drawData.faceIndices[size_t(i)];
                if (vertex >= rt->vertexCount || vertex >= drawData.worldIndices.size()) return 0;
                const uint32_t world = drawData.worldIndices[vertex];
                if (world >= drawData.worldTransformSegmentedAddresses.size()) return 0;
                const uint32_t matrix = drawData.worldTransformSegmentedAddresses[world];
                if (!wr64RTAccumulateActorRacer(racerMask, matrix)) return 0;
            }
            return racerMask;
        };
        auto wr64ExpandActorShadowBounds = [&](const GameCall &call, uint32_t racerMask) {
            uint32_t racer = 0;
            while ((1u << racer) != racerMask) ++racer;
            auto &bounds = rt->actorBounds[racer];
            // Normal presentation clamps weights to [0,1]. A paused debugger
            // can supply a free-form value; retain full actor testing then.
            const float debuggerWeight = p.curWorkload->debuggerRenderer.interpolationWeight;
            if (p.curWorkload->paused && (!std::isfinite(debuggerWeight) ||
                debuggerWeight < 0.0f || debuggerWeight > 1.0f)) bounds.invalidate();
            const uint64_t first = call.meshDesc.faceIndicesStart;
            const uint64_t end = first + uint64_t(call.callDesc.triangleCount) * 3;
            // Identity/provenance and face bounds already passed the actor
            // classifier. Bounds are only an optimization: any missing stream
            // invalidates this racer instead of removing its caster identity.
            for (uint64_t face = first; bounds.reliable && face < end; ++face) {
                const uint32_t vertex = drawData.faceIndices[size_t(face)];
                const size_t pos = size_t(vertex) * 3;
                const uint32_t world = drawData.worldIndices[vertex];
                if (pos + 3 > drawData.posFloats.size() || pos + 3 > drawData.velFloats.size() ||
                    world >= drawData.worldTransforms.size() ||
                    (!drawData.lerpWorldTransforms.empty() &&
                        drawData.lerpWorldTransforms.size() != drawData.worldTransforms.size())) {
                    bounds.invalidate(); break;
                }
                if (!drawData.wr64WaterFieldInfo.empty()) {
                    if (size_t(vertex) * 4 + 4 > drawData.wr64WaterFieldInfo.size()) {
                        bounds.invalidate(); break;
                    }
                    for (size_t component = 0; component < 4; ++component)
                        if (drawData.wr64WaterFieldInfo[size_t(vertex) * 4 + component] != 0) bounds.invalidate();
                    if (!bounds.reliable) break;
                }
                const auto &worldMatrix = drawData.lerpWorldTransforms.empty() ?
                    drawData.worldTransforms[world] : drawData.lerpWorldTransforms[world];
                std::array<float, 16> matrix{};
                for (uint32_t row = 0; row < 4; ++row)
                    for (uint32_t column = 0; column < 4; ++column)
                        matrix[row * 4 + column] = float(worldMatrix[row][column]);
                bounds.include({ drawData.posFloats[pos], drawData.posFloats[pos + 1], drawData.posFloats[pos + 2] },
                    { drawData.velFloats[pos], drawData.velFloats[pos + 1], drawData.velFloats[pos + 2] }, matrix);
            }
        };

        const bool wr64RTMenuScope = p.curWorkload->wr64RtMenuReflectionScope;
        WR64RTPreviewDomain wr64RTWaterDomain;
        auto wr64ViewDomain = [&](const Projection &projection, const FixedRect &scissor) {
            WR64RTViewDomain domain;
            const uint32_t view = projection.transformsIndex;
            if (view >= drawData.rspViewports.size() || scissor.isNull()) return domain;
            const auto &viewport = drawData.rspViewports[view];
            domain.perspective = projection.type == Projection::Type::Perspective;
            domain.menuModelPreview = projection.wr64MenuModelPreview;
            domain.menuWaterPreview = projection.wr64MenuWaterPreview;
            for (uint32_t i = 0; i < 3; ++i) {
                domain.scale[i] = viewport.scale[i];
                domain.translate[i] = viewport.translate[i];
            }
            domain.scissor[0] = scissor.ulx; domain.scissor[1] = scissor.uly;
            domain.scissor[2] = scissor.lrx; domain.scissor[3] = scissor.lry;
            return domain;
        };
        auto wr64RaceView = [&](const Projection &projection, const FixedRect &scissor) {
            return wr64RTNativeRaceView(wr64ViewDomain(projection, scissor));
        };
        auto wr64PreviewDomain = [&](const Projection &projection, const FixedRect &scissor) {
            WR64RTPreviewDomain domain;
            const uint32_t view = projection.transformsIndex;
            if (!projection.wr64MenuWaterPreview || view >= drawData.rspViewports.size() || scissor.isNull())
                return domain;
            const auto &viewport = drawData.rspViewports[view];
            domain.nativeWaterViewport = true;
            domain.scale[0] = viewport.scale.x;
            domain.scale[1] = viewport.scale.y;
            domain.scale[2] = viewport.scale.z;
            domain.translate[0] = viewport.translate.x;
            domain.translate[1] = viewport.translate.y;
            domain.translate[2] = viewport.translate.z;
            domain.scissor[0] = scissor.ulx;
            domain.scissor[1] = scissor.uly;
            domain.scissor[2] = scissor.lrx;
            domain.scissor[3] = scissor.lry;
            return domain;
        };
        for (uint32_t rtIndex = 0; rtIndex < (wr64RTTwoPlayer ? 2u : 1u); ++rtIndex) {
            rt = &wr64RTViews[rtIndex];
            const bool rasterSkyScope = wr64RasterSkySupported && p.curWorkload->wr64RasterSkyScope;
            const bool rasterShadowScope = wr64RasterSkySupported && p.curWorkload->wr64RasterShadowScope;
            const bool rasterReflectionScope = wr64RasterSkySupported && p.curWorkload->wr64RasterReflectionScope;
            const bool rayScope = wr64RTSupported && p.curWorkload->wr64RtReflectionScope &&
                (p.curWorkload->wr64RtObjectReflectionScope || wr64RasterSkySupported);
            if (wr64RTBackendAllowed && p.wr64RtPresentation && (rayScope || rasterSkyScope || rasterShadowScope || rasterReflectionScope)) {
                rt->scopeSeen = true;
                rt->rasterSky = rasterSkyScope;
                rt->traceReflections = rayScope;
                rt->raySkyOnly = rayScope && !p.curWorkload->wr64RtObjectReflectionScope;
                rt->rasterShadows = rasterShadowScope;
                rt->rasterReflections = rasterReflectionScope;
                // Use the existing water blend multiplier only for raster sky.
                // Queued RT workloads keep their original strength even when
                // the frontend has just switched modes or adjusted the slider.
                rt->params.strength = rasterSkyScope && !rayScope ? wr64RasterSkyStrength : 1.0f;
                rt->params.qualityOptions.z = rasterSkyScope && rayScope ? wr64RasterSkyStrength : 0.0f;
                rt->skyScopeSeen |= rasterSkyScope || (p.curWorkload->wr64RtSkyReflectionScope &&
                    !wr64D3D12DiagnosticSkyDisabled(wr64RTShaderFormat == RenderShaderFormat::DXIL));
                rt->workload = p.curWorkload->workloadId;
            }
            if (wr64RTBackendAllowed && p.wr64RtPresentation &&
                (rayScope || rasterSkyScope || rasterShadowScope || rasterReflectionScope) &&
                rt->framebuffer == UINT32_MAX && p.fbStorage->colorTarget && fbPair.depthWrite) {
                for (uint32_t pi = 0; pi < fbPair.projectionCount && rt->projection == UINT32_MAX; ++pi) {
                    const auto &projection = fbPair.projections[pi];
                    if (projection.type != Projection::Type::Perspective || projection.wr64MenuModelPreview) continue;
                    if (wr64RTMenuScope && !projection.wr64MenuWaterPreview) continue;
                    for (uint32_t ci = 0; ci < projection.gameCallCount; ++ci) {
                        const auto &call = projection.gameCalls[ci];
                        if (!wr64IsWater(call)) continue;
                        if (wr64RTTwoPlayer && wr64RaceView(projection, call.callDesc.scissorRect) != rtIndex + 1) continue;
                        if (wr64RTMenuScope) {
                            wr64RTWaterDomain = wr64PreviewDomain(projection, call.callDesc.scissorRect);
                            if (!wr64RTSamePreviewDomain(wr64RTWaterDomain, wr64RTWaterDomain)) continue;
                        }
                        rt->projection = projection.transformsIndex;
                        break;
                    }
                }
                // The award camera can show only the podium, riders and shore.
                // Its shadows must not disappear just because no water was drawn.
                // This fallback is exclusive to the native ending and depth-writing
                // opaque/cutout world geometry under its full 424x240 camera.
                if (rt->projection == UINT32_MAX && p.curWorkload->wr64RtEndingScope &&
                    (p.curWorkload->wr64RtShadowScope || rasterShadowScope)) {
                    for (uint32_t pi = 0; pi < fbPair.projectionCount && rt->projection == UINT32_MAX; ++pi) {
                        const auto &projection = fbPair.projections[pi];
                        for (uint32_t ci = 0; ci < projection.gameCallCount; ++ci) {
                            const auto &call = projection.gameCalls[ci];
                            const auto &desc = call.callDesc;
                            if (!desc.triangleCount || !desc.otherMode.zCmp() || !desc.otherMode.zUpd() ||
                                wr64RTClassifyMaterial(desc.otherMode.L) == Wr64RTMaterial::Rejected ||
                                !wr64RTEndingWorldView(true, wr64ViewDomain(projection, desc.scissorRect))) continue;
                            rt->projection = projection.transformsIndex;
                            rt->endingWorldOnly = true;
                            // No planar water exists in this framebuffer. Do not
                            // access a first water draw while preparing its shadows.
                            rt->rasterReflections = false;
                            break;
                        }
                    }
                }
                if (rt->projection < drawData.modViewTransforms.size()) {
                    rt->framebuffer = framebufferCount - 1;
                    rt->nativeRaceView = wr64RTTwoPlayer ? rtIndex + 1 : 0;
                    if (wr64RTTwoPlayer) rt->skyCaptureRequested = false;
                    wr64MotionDiagnostic.view = rt->projection;
                    wr64MotionTimeScale = p.motionTimeScale;
                    wr64MotionShutter = wr64MotionShutterScale(p.deltaTimeMs);
                    rt->workload = p.curWorkload->workloadId;
                    rt->vertexCount = vertexCount;
                    rt->skyCaptureDrawData = &drawData;
                    rt->skyCaptureNativePresent = p.curWorkload->presentId;
                    rt->skyCaptureSubmission = p.curWorkload->submissionFrame;
                    rt->indexCount = indexCount;
                    const auto eye = viewPositionFrom(hlslpp::inverse(drawData.modViewTransforms[rt->projection]));
                    rt->params.camera = hlslpp::float4(eye, 1.0f);
                    if (rasterReflectionScope && p.wr64RasterReflectionPlaneValid &&
                        rt->projection < drawData.modViewProjTransforms.size() &&
                        rt->projection < drawData.rspViewports.size()) {
                        // The producer owns the native mean sea height; the
                        // queue interpolates it with this presentation's water.
                        // Save the VP now and apply the final water draw's
                        // screen transform after framebuffer assembly finishes.
                        float nativeMatrix[16];
                        hlslpp::store(nativeMatrix, drawData.modViewProjTransforms[rt->projection]);
                        for (uint32_t row = 0; row < 4; ++row)
                            for (uint32_t col = 0; col < 4; ++col)
                                rt->reflectionViewRows[row][col] = nativeMatrix[col * 4 + row];
                        const auto &vp = drawData.rspViewports[rt->projection];
                        rt->reflectionViewportScale[0] = vp.scale.x;
                        rt->reflectionViewportScale[1] = vp.scale.y;
                        rt->reflectionViewportScale[2] = vp.scale.z;
                        rt->reflectionViewportTranslate[0] = vp.translate.x;
                        rt->reflectionViewportTranslate[1] = vp.translate.y;
                        rt->reflectionViewportTranslate[2] = vp.translate.z;
                        rt->reflectionFramebufferSize[0] = float(fbParams.resolution.x);
                        rt->reflectionFramebufferSize[1] = float(fbParams.resolution.y);
                        rt->reflectionPlaneY = p.wr64RasterReflectionPlaneY;
                        rt->reflectionPlaneValid = true;
                    }
                    const auto &shadowLight = p.curWorkload->wr64RtShadowLight;
                    if (p.curWorkload->wr64RtAoScope)
                        rt->params.aoOptions = { 1.0f, 24.0f, 0.12f, 0.5f };
                    if ((p.curWorkload->wr64RtShadowScope || rasterShadowScope) && shadowLight.valid) {
                        auto luminance = [](const std::array<float, 3> &rgb) {
                            return rgb[0] * 0.2126f + rgb[1] * 0.7152f + rgb[2] * 0.0722f;
                        };
                        const float direct = luminance(shadowLight.diffuse);
                        const float ambient = luminance(shadowLight.ambient);
                        const float strength = std::clamp(direct / std::max(direct + ambient, 1e-6f), 0.0f, 0.55f);
                        rt->params.shadowLight = { shadowLight.toLight[0], shadowLight.toLight[1],
                            shadowLight.toLight[2], strength };
                        rt->params.shadowOptions = { rasterShadowScope ? 0.0f : 1.0f, 0.5f, 30000.0f, 0.0f };
                        if (rasterShadowScope) {
                            float camera[3] = {float(eye.x), float(eye.y), float(eye.z)};
                            const auto projection = wr64BuildRasterShadowProjection(camera, shadowLight.toLight.data(),
                                p.curWorkload->wr64RasterShadowDistanceMode);
                            if (projection.valid) {
                                std::memcpy(rt->rasterShadowParams.lightRows, projection.rows, sizeof(projection.rows));
                                rt->rasterShadowParams.options[0] = 1.0f / 1024.0f;
                                rt->rasterShadowParams.options[1] = 1.0f / 16384.0f;
                                rt->rasterShadowParams.options[2] = strength * (0.18f / 0.55f);
                                rt->rasterShadowParams.options[3] = strength;
                                std::copy(shadowLight.toLight.begin(), shadowLight.toLight.end(), rt->rasterShadowParams.light);
                                rt->rasterShadowParams.light[3] = 1.0f;
                            }
                        }
                    }
                    if ((p.curWorkload->wr64RtSkyReflectionScope || rasterSkyScope) && !wr64RTMenuScope &&
                        rt->projection < drawData.projTransforms.size()) {
                        // Snapshot native bodies before sprite culling, then place
                        // them using the same presentation camera as the water.
                        std::array<float, 16> celestialView{}, celestialProjection{};
                        hlslpp::store(celestialView.data(), drawData.modViewTransforms[rt->projection]);
                        // Fixed native 424x240 chart: use its authored projection,
                        // not the aspect-expanded output projection. Otherwise
                        // fixed-size discs/stars stretch horizontally on ultrawide.
                        hlslpp::store(celestialProjection.data(), drawData.projTransforms[rt->projection]);
                        const auto &snapshot = p.curWorkload->wr64RtCelestial;
                        const auto projected = wr64RTCelestialProject(snapshot, celestialView,
                            celestialProjection, { float(eye.x), float(eye.y), float(eye.z) });
                        auto vector4 = [](const std::array<float, 4> &v) {
                            return hlslpp::float4(v[0], v[1], v[2], v[3]);
                        };
                        for (uint32_t row = 0; row < 3; ++row) {
                            rt->params.celestialProjection[row] = vector4(projected.projectionRows[row]);
                        }
                        rt->params.celestialInfo = { projected.count, snapshot.count, 0, 0 };
                        for (uint32_t i = 0; i < projected.count; ++i) {
                            const auto &source = projected.records[i];
                            auto &target = rt->params.celestialBodies[i];
                            target.bounds = vector4(source.rect);
                            target.uv = { source.texcoords[0], source.texcoords[1],
                                source.texcoords[2] * (source.rect[2] - source.rect[0]),
                                source.texcoords[3] * (source.rect[3] - source.rect[1]) };
                            target.color = vector4(source.color);
                            const uint32_t dimension = source.texture == 2 ? 4 : 32;
                            target.texture = { source.texture * 1024, dimension, dimension, 0 };
                        }
                        static_assert(sizeof(rt->params.celestialAlpha) == sizeof(snapshot.alphaWords));
                        std::memcpy(rt->params.celestialAlpha, snapshot.alphaWords.data(), sizeof(snapshot.alphaWords));
                    }
                    const char *debug = std::getenv("WR64_RT_REFLECTIONS_DEBUG");
                    rt->params.debugView = debug && debug[0] >= '1' && debug[0] <= '6' && debug[1] == '\0'
                        ? uint32_t(debug[0] - '0') : 0;
                    rt->params.enabled = 1;
                }
                else rt->projection = UINT32_MAX;
            }
        }
        auto wr64CaptureSky = [&](const GameCall &call, const Projection &projection,
            uint32_t drawIndex, bool originalMapping, bool backdrop) {
            const auto &desc = call.callDesc;
            if (wr64RTTwoPlayer && wr64RaceView(projection, desc.scissorRect) != rt->nativeRaceView) return;
            auto &matches = backdrop ? rt->backdropMatches : rt->skyMatches;
            auto &candidates = backdrop ? rt->backdropCandidates : rt->skyCandidates;
            auto &selectedFan = backdrop ? rt->params.skyBackdrop : rt->params.sky;
            auto &selectedEye = backdrop ? rt->params.skyBackdropCamera : rt->params.skyCamera;
            const uint32_t previousCandidates = candidates;
            int currentWorldIdentity = -1, lerpWorldIdentity = -1;
            ++matches;
            const auto &scissor = desc.scissorRect;
            const auto &frameScissor = fbPair.scissorRect;
            auto coversFrame = [&](const FixedRect &rect) {
                return !rect.isNull() && !frameScissor.isNull() &&
                    wr64RTSkyFullCoverage(rect.ulx, rect.uly, rect.lrx, rect.lry,
                        frameScissor.ulx, frameScissor.uly, frameScissor.lrx, frameScissor.lry);
            };
            const uint32_t viewIndex = projection.transformsIndex;
            const bool validView = viewIndex < drawData.modViewTransforms.size() &&
                viewIndex < drawData.rspViewports.size();
            bool fullViewport = false;
            if (validView) {
                const auto &viewport = drawData.rspViewports[viewIndex];
                const float left = (viewport.translate.x - std::abs(viewport.scale.x)) * 4.0f;
                const float top = (viewport.translate.y - std::abs(viewport.scale.y)) * 4.0f;
                const float right = (viewport.translate.x + std::abs(viewport.scale.x)) * 4.0f;
                const float bottom = (viewport.translate.y + std::abs(viewport.scale.y)) * 4.0f;
                fullViewport = std::isfinite(left) && std::isfinite(top) &&
                    std::isfinite(right) && std::isfinite(bottom) && left <= frameScissor.ulx + 8.0f &&
                    top <= frameScissor.uly + 8.0f && right >= frameScissor.lrx - 8.0f &&
                    bottom >= frameScissor.lry - 8.0f;
            }

            const char *rejection = validView ? nullptr : "invalid-view-transform";
            if (rejection == nullptr && wr64RTMenuScope) {
                if (!validView || !wr64RTSamePreviewDomain(wr64PreviewDomain(projection, scissor), wr64RTWaterDomain))
                    rejection = "outside-live-water-preview";
            }
            else if (rejection == nullptr && !wr64RTTwoPlayer && !wr64RTMenuScope &&
                (!coversFrame(scissor) || !fullViewport)) rejection = "inset-or-invalid-viewport";
            const uint64_t first = call.meshDesc.faceIndicesStart;
            const uint64_t end = first + uint64_t(desc.triangleCount) * 3;
            if (rejection == nullptr && backdrop) {
                uint32_t sourceAddresses[18] = {};
                bool validSources = end <= drawData.faceIndices.size() && end - first == 18;
                for (uint64_t i = first; validSources && i < end; ++i) {
                    const uint32_t vertex = drawData.faceIndices[size_t(i)];
                    validSources = vertex < drawData.vertexSegmentedAddresses.size();
                    if (validSources) sourceAddresses[i - first] = drawData.vertexSegmentedAddresses[vertex];
                }
                if (!validSources || !wr64RTBackdropSourceFamily(sourceAddresses, 18))
                    rejection = "unrecognized-backdrop-provenance";
            }
            // Count full-scene members of the recognized family before their
            // material/stream validation. A second family member invalidates
            // both even if its later validation fails; unrelated earlier fans
            // with the same combiner never consume a backdrop candidate.
            if (rejection == nullptr && ++candidates != 1) rejection = "ambiguous-full-scene";
            if (candidates > 1) {
                selectedFan.w = 0;
                if (!backdrop) rt->params.skyCloudParams = { 0.0f, 0.0f, 0.0f, 0.0f };
            }
            if (rejection == nullptr && (!originalMapping || projection.wr64MenuModelPreview ||
                instanceDrawCallVector[drawIndex].type != InstanceDrawCall::Type::IndexedTriangles))
                rejection = "modified-raster-mapping";

            hlslpp::float3 eye(0.0f, 0.0f, 0.0f);
            float viewDifference = -1.0f;
            if (rejection == nullptr) {
                // Sky may follow a different origin, but reflected world
                // directions must keep the same orientation and units. Use its
                // own current eye and reject unrelated rotated/scaled cameras.
                hlslpp::float4x4 skyOrientation = drawData.modViewTransforms[viewIndex];
                hlslpp::float4x4 waterOrientation = drawData.modViewTransforms[rt->projection];
                skyOrientation[3] = hlslpp::float4(0.0f, 0.0f, 0.0f, 1.0f);
                waterOrientation[3] = hlslpp::float4(0.0f, 0.0f, 0.0f, 1.0f);
                viewDifference = matrixDifference(skyOrientation, waterOrientation);
                eye = viewPositionFrom(hlslpp::inverse(drawData.modViewTransforms[viewIndex]));
                if (!std::isfinite(viewDifference) || viewDifference >= 1e-4f ||
                    !std::isfinite(float(eye.x)) || !std::isfinite(float(eye.y)) || !std::isfinite(float(eye.z)))
                    rejection = "incompatible-camera";
            }

            uint32_t uniqueVertices[7] = {};
            uint32_t uniqueCount = 0;
            if (rejection == nullptr && end > drawData.faceIndices.size()) rejection = "invalid-indices";
            for (uint64_t i = first; rejection == nullptr && i < end; ++i) {
                const uint32_t vertex = drawData.faceIndices[size_t(i)];
                if (vertex >= vertexCount || vertex >= drawData.worldIndices.size() ||
                    vertex >= drawData.viewProjIndices.size() ||
                    drawData.viewProjIndices[vertex] != viewIndex ||
                    drawData.worldIndices[vertex] >= drawData.worldTransforms.size() ||
                    (uint64_t(vertex) + 1) * 3 > drawData.posFloats.size() ||
                    (uint64_t(vertex) + 1) * 3 > drawData.velFloats.size() ||
                    (uint64_t(vertex) + 1) * 2 > drawData.tcFloats.size() ||
                    (uint64_t(vertex) + 1) * 2 > drawData.tcVelFloats.size() ||
                    (uint64_t(vertex) + 1) * 4 > drawData.normColBytes.size()) {
                    rejection = "invalid-vertex-stream";
                    break;
                }
                if (std::find(uniqueVertices, uniqueVertices + uniqueCount, vertex) == uniqueVertices + uniqueCount) {
                    if (uniqueCount == 7) { rejection = "not-seven-vertex-fan"; break; }
                    uniqueVertices[uniqueCount++] = vertex;
                }
                // RSPWorldCS and RSPProcessCS share repaired positions, frame
                // weight, and presentation world matrices. G_MODIFYVTX is the
                // exception: it edits only screenPos after those evaluations.
                for (size_t m = 0; m + 1 < drawData.modifyPosUints.size(); m += 2) {
                    if ((drawData.modifyPosUints[m] >> 1) == vertex) {
                        rejection = "screen-modified-vertex";
                        break;
                    }
                }
            }
            if (rejection == nullptr && uniqueCount != 7) rejection = "not-seven-vertex-fan";
            if (rejection == nullptr && (desc.callIndex >= drawData.rdpParams.size() ||
                desc.callIndex >= drawData.renderParams.size() || desc.tileCount == 0 ||
                uint64_t(desc.tileIndex) + desc.tileCount > drawData.callTiles.size() ||
                uint64_t(desc.tileIndex) + desc.tileCount > drawData.rdpTiles.size())) rejection = "invalid-material";
            for (uint32_t t = 0; rejection == nullptr && t < desc.tileCount; ++t) {
                const auto &tile = drawData.callTiles[desc.tileIndex + t];
                if (!tile.valid || tile.tileCopyUsed || tile.sampleWidth == 0 || tile.sampleHeight == 0)
                    rejection = "unavailable-native-texture";
                if (backdrop) {
                    const auto &rdpTile = drawData.rdpTiles[desc.tileIndex + t];
                    if (tile.sampleWidth != 4 || tile.sampleHeight != 64 || rdpTile.fmt != 0 ||
                        rdpTile.siz != 2 || rdpTile.cms != G_TX_CLAMP || rdpTile.cmt != G_TX_CLAMP ||
                        rdpTile.masks != 0 || rdpTile.maskt != 0)
                        rejection = "unrecognized-backdrop-texture";
                }
            }
            if (rejection == nullptr && backdrop &&
                desc.tileCount != (desc.colorCombiner.L == 0xFC22FFFF ? 2u : 1u))
                rejection = "unrecognized-backdrop-tile-count";
            if (rejection == nullptr) {
                selectedFan = { uint32_t(first), drawIndex, desc.triangleCount, 1 };
                selectedEye = hlslpp::float4(eye, 1.0f);
                if (rt->skyCaptureRequested) {
                    auto &layer = rt->skyCaptureLayers[backdrop ? 1 : 0];
                    layer.count = uint32_t(end - first);
                    for (uint32_t i = 0; i < layer.count; ++i)
                        layer.vertices[i] = drawData.faceIndices[size_t(first + i)];
                    std::ostringstream metadata;
                    metadata << "{\"draw\":" << drawIndex << ",\"native_call\":" << desc.callIndex
                        << ",\"view\":" << viewIndex << ",\"first_index\":" << first
                        << ",\"combiner\":[" << desc.colorCombiner.L << ',' << desc.colorCombiner.H
                        << "],\"other_mode\":[" << desc.otherMode.L << ',' << desc.otherMode.H
                        << "],\"geometry_mode\":" << desc.geometryMode << ",\"rdp_u32\":";
                    wr64SkyCaptureWords(metadata, &drawData.rdpParams[desc.callIndex], sizeof(interop::RDPParams) / 4);
                    metadata << ",\"tiles\":[";
                    for (uint32_t t = 0; t < desc.tileCount; ++t) {
                        if (t) metadata << ',';
                        const auto &tile = drawData.callTiles[desc.tileIndex + t];
                        metadata << "{\"index\":" << desc.tileIndex + t << ",\"hash\":\""
                            << std::hex << tile.tmemHashOrID << std::dec << "\",\"sample\":["
                            << tile.sampleWidth << ',' << tile.sampleHeight << "],\"raw_tmem\":"
                            << unsigned(tile.rawTMEM) << ",\"rdp_u32\":";
                        wr64SkyCaptureWords(metadata, &drawData.rdpTiles[desc.tileIndex + t], sizeof(interop::RDPTile) / 4);
                        metadata << '}';
                    }
                    metadata << "],\"source_addresses\":[";
                    for (uint32_t i = 0; i < layer.count; ++i) {
                        if (i) metadata << ',';
                        const uint32_t vertex = layer.vertices[i];
                        metadata << (vertex < drawData.vertexSegmentedAddresses.size() ?
                            drawData.vertexSegmentedAddresses[vertex] : UINT32_MAX);
                    }
                    metadata << "]}";
                    layer.material = metadata.str();
                }
            }
            if (rejection == nullptr && !backdrop) {
                // The native alpha field is measured in source XZ units from
                // the camera. Only extend it when source and presentation
                // positions share those world units and axes. An unsupported
                // transform retains the finite native fan path.
                const bool validCloudCoefficients = p.curWorkload->wr64RtSkyCloudParams.z == 1.0f;
                auto identityWorld = [](const interop::float4x4 &matrix) {
                    for (uint32_t row = 0; row < 4; ++row) {
                        for (uint32_t column = 0; column < 4; ++column) {
                            const float value = matrix[row][column];
                            if (!std::isfinite(value) ||
                                std::abs(value - (row == column ? 1.0f : 0.0f)) > 1e-5f)
                                return false;
                        }
                    }
                    return true;
                };
                currentWorldIdentity = 1;
                lerpWorldIdentity = 1;
                for (uint32_t i = 0; i < uniqueCount; ++i) {
                    const uint32_t worldIndex = drawData.worldIndices[uniqueVertices[i]];
                    currentWorldIdentity &= identityWorld(drawData.worldTransforms[worldIndex]) ? 1 : 0;
                    if (worldIndex < drawData.lerpWorldTransforms.size())
                        lerpWorldIdentity &= identityWorld(drawData.lerpWorldTransforms[worldIndex]) ? 1 : 0;
                }
                const bool nativeCloudCoordinates = validCloudCoefficients && currentWorldIdentity && lerpWorldIdentity;
                rt->params.skyCloudParams = nativeCloudCoordinates
                    ? p.curWorkload->wr64RtSkyCloudParams
                    : interop::float4{ 0.0f, 0.0f, 0.0f, 0.0f };
            }
            // Save the relevant layer result for the complete presentation.
            // The unrelated lower fan shares the backdrop combiner, so logging
            // every candidate made its harmless rejection obscure the real sky.
            // A later inset draw likewise must not overwrite a selected layer.
            if (WR64_DIAGNOSTIC_ENABLED && !(backdrop && rejection && std::strcmp(rejection, "unrecognized-backdrop-provenance") == 0) &&
                (candidates > previousCandidates || candidates == 0)) {
                auto &diagnostic = rt->skyCaptureDiagnostic[backdrop ? 1 : 0];
                diagnostic.reason = rejection ? rejection : "selected";
                diagnostic.draw = drawIndex;
                diagnostic.view = viewIndex;
                diagnostic.cameraDifference = viewDifference;
                if (!backdrop) {
                    diagnostic.coefficientValid = p.curWorkload->wr64RtSkyCloudParams.z == 1.0f ? 1 : 0;
                    diagnostic.currentWorldIdentity = currentWorldIdentity;
                    diagnostic.lerpWorldIdentity = lerpWorldIdentity;
                }
            }
        };
        vertexInputSlots[0] = RenderInputSlot(0, PosStride);
        vertexInputSlots[1] = RenderInputSlot(1, TcStride);
        vertexInputSlots[2] = RenderInputSlot(2, ColStride);
        indexedVertexViews[0] = RenderVertexBufferView(RenderBufferReference(screenPosRes), PosStride * vertexCount);
        indexedVertexViews[1] = RenderVertexBufferView(RenderBufferReference(tcRes), TcStride * vertexCount);
        indexedVertexViews[2] = RenderVertexBufferView(RenderBufferReference(shadedColRes), ColStride * vertexCount);
        indexBufferView = RenderIndexBufferView(RenderBufferReference(indexRes), IndexStride * indexCount, RenderFormat::R32_UINT);
        rawVertexViews[0] = RenderVertexBufferView(RenderBufferReference(triPosRes), PosStride * rawTriVertexCount);
        rawVertexViews[1] = RenderVertexBufferView(RenderBufferReference(triTcRes), TcStride * rawTriVertexCount);
        rawVertexViews[2] = RenderVertexBufferView(RenderBufferReference(triColRes), ColStride * rawTriVertexCount);
        testZIndexBuffer = outputBuffers.testZIndexBuffer.buffer.get();
        testZIndexBufferView = RenderIndexBufferView(testZIndexBuffer, uint32_t(outputBuffers.testZIndexBuffer.allocatedSize), RenderFormat::R32_UINT);

        RasterScene rasterScene;
        auto checkRasterScene = [&](RasterScene &rasterScene) {
            if (!rasterScene.instanceIndices.empty()) {
                uint32_t sceneIndex = static_cast<uint32_t>(targetDrawCall.rasterScenes.size());
                targetDrawCall.rasterScenes.push_back(rasterScene);
                targetDrawCall.sceneIndices.push_back({ sceneIndex, false });
                rasterScene.instanceIndices.clear();

                return true;
            }
            else {
                return false;
            }
        };

        targetDrawCall.rasterScenes.clear();

#   if RT_ENABLED
        RaytracingScene rtScene;
        auto checkRtScene = [&](RaytracingScene &rtScene) {
            if (!rtScene.instanceIndices.empty()) {
                uint32_t sceneIndex = static_cast<uint32_t>(targetDrawCall.rtScenes.size());
                targetDrawCall.rtScenes.push_back(rtScene);
                targetDrawCall.sceneIndices.push_back({ sceneIndex, true });
                rtScene.instanceIndices.clear();

                return true;
            }
            else {
                return false;
            }
        };

        targetDrawCall.rtScenes.clear();
#   endif

        targetDrawCall.fbStorage = p.fbStorage;
        targetDrawCall.sceneIndices.clear();

        const float SimilarityPercentage = 0.1f; // TODO: Make more strict once VI ratios are in.
        const float scissorRatio = static_cast<float>(fbPair.scissorRect.width(false, true)) / static_cast<float>(fbPair.scissorRect.height(false, true));
        const bool adjustRatio = (abs((scissorRatio / p.aspectRatioSource) - 1.0f) < SimilarityPercentage);
        const float aspectRatioScale = adjustRatio ? (p.aspectRatioTarget / p.aspectRatioSource) : 1.0f;
        InstanceDrawCall instanceDrawCall;
        interop::RenderIndices renderIndices;
        uint32_t globalCallIndex = 0;
        const float wideWidth = p.fbWidth * p.resolutionScale.x;
        const float originalWidth = p.fbWidth * p.resolutionScale.y;
        const float commonHeight = float(p.targetHeight);
        const Wr64UltrawideLayout wr64WideLayout =
            wr64UltrawideLayout(float(p.resolutionScale.x), float(p.resolutionScale.y), p.fbWidth);
        const Wr64UltrawideLayout wr64HudLayout =
            wr64UltrawideHudLayout(wr64WideLayout, p.extAspectPercentage);
        const Wr64VerticalLayout wr64Vertical = wr64VerticalLayout(
            p.curWorkload->wr64VerticalSplit && p.fbWidth == 424,
            wideWidth, commonHeight, float(p.resolutionScale.y), wr64HudLayout.halfExtension);
        float wr64VerticalPauseCenterY = -1.0f;
        if (wr64Vertical.active && p.curWorkload->wr64PauseDrawOwner != 0) {
            int32_t top = INT32_MAX, bottom = INT32_MIN;
            for (uint32_t i = 0; i < fbPair.projectionCount; i++) {
                const auto &projection = fbPair.projections[i];
                if (projection.type != Projection::Type::Rectangle) continue;
                for (uint32_t j = 0; j < projection.gameCallCount; j++) {
                    const auto &desc = projection.gameCalls[j].callDesc;
                    if (desc.callIndex < p.curWorkload->wr64PauseFirstCall ||
                        desc.callIndex >= p.curWorkload->wr64PauseLastCall || desc.rect.isNull()) continue;
                    top = std::min(top, desc.rect.uly);
                    bottom = std::max(bottom, desc.rect.lry);
                }
            }
            if (top < bottom) {
                wr64VerticalPauseCenterY = (top + bottom) * 0.125f * float(p.resolutionScale.y);
            }
        }
        std::vector<Wr64FinishHudRow> wr64FinishHudRows;
        if (wr64FinishHudEnabled(p.fbWidth, wr64TwoPFrameActive())) {
            for (uint32_t pr = 0; pr < fbPair.projectionCount; pr++) {
                const auto &projection = fbPair.projections[pr];
                if (projection.type != Projection::Type::Rectangle) continue;
                for (uint32_t d = 0; d < projection.gameCallCount; d++) {
                    const auto &desc = projection.gameCalls[d].callDesc;
                    if (desc.tileCount != 1 || desc.tileIndex >= p.curWorkload->drawData.callTiles.size()) continue;
                    Wr64FinishHudRow row;
                    if (wr64FinishHudBackground(desc.rect,
                        p.curWorkload->drawData.callTiles[desc.tileIndex].tmemHashOrID, row)) {
                        wr64FinishHudRows.push_back(row);
                    }
                }
            }
        }
        Wr64EndingModelPanel wr64EndingModelPanel;
        if (!p.curWorkload->wr64CelestialLerpRects.empty()) {
            // TourEnd draws the ranking panel, clears Z through a temporary
            // color-image binding, then restores color and draws the models.
            // Those nonempty passes are separate framebuffer pairs. Follow the
            // authenticated panel across earlier pairs of THIS workload/target;
            // another target or a later panel cannot supply its presentation.
            for (uint32_t sourcePairIndex = 0;
                 sourcePairIndex < p.curWorkload->fbPairCount && sourcePairIndex <= uint32_t(p.fbPairIndex);
                 ++sourcePairIndex) {
                const auto &sourcePair = p.curWorkload->fbPairs[sourcePairIndex];
                if (sourcePair.colorImage.address != fbPair.colorImage.address ||
                    sourcePair.colorImage.width != fbPair.colorImage.width ||
                    sourcePair.colorImage.fmt != fbPair.colorImage.fmt ||
                    sourcePair.colorImage.siz != fbPair.colorImage.siz) continue;
                for (uint32_t pr = 0; pr < sourcePair.projectionCount; ++pr) {
                    const auto &projection = sourcePair.projections[pr];
                    if (projection.type != Projection::Type::Rectangle) continue;
                    for (uint32_t d = 0; d < projection.gameCallCount; ++d) {
                        const auto &desc = projection.gameCalls[d].callDesc;
                        if (desc.wr64HudMotion.kind != 3 || desc.wr64HudMotion.content != 10) continue;
                        const auto found = p.curWorkload->wr64CelestialLerpRects.find(
                            wr64CelestialRectKey(sourcePairIndex, pr, d));
                        if (found != p.curWorkload->wr64CelestialLerpRects.end()) {
                            wr64EndingModelPanel.include(desc.wr64HudMotion, desc.rect, found->second);
                        }
                    }
                }
            }
        }
        const bool wr64WideWatercraftSelect = wr64WideLayout.active() &&
            wr64WatercraftSelectFramebuffer(*p.curWorkload, uint32_t(p.fbPairIndex));
        if (wr64WideWatercraftSelect) {
            static std::atomic<bool> announced{false};
            if (!announced.exchange(true, std::memory_order_relaxed)) {
                { if (WR64_DIAGNOSTIC_ENABLED) std::fprintf(stderr, "[ultrawide] Watercraft Select: centred craft viewports; full-width tiled backdrop/shade\n"); }
            }
        }
        framebuffer.viewport = RenderViewport(0.0f, 0.0f, wideWidth, commonHeight);
        
        const interop::float2 halfViewportSize = { framebuffer.viewport.width / 2.0f, framebuffer.viewport.height / 2.0f };
        const interop::float2 halfPixelOffset = { 1.0f / framebuffer.viewport.width, -1.0f / framebuffer.viewport.height };
        const float middleViewport = (wideWidth / 2.0f) - (originalWidth / 2.0f);
        const float extOriginPercentage = p.extAspectPercentage;
        uint32_t vertexTestZFaceIndicesStart = 0;
        int32_t vertexTestZCallIndex = -1;
        RenderViewport viewportClip;
        for (uint32_t pr = 0; (pr < fbPair.projectionCount) && (globalCallIndex < p.maxGameCall); pr++) {
            const Projection &proj = fbPair.projections[pr];
            if (proj.scissorRect.isNull()) {
                continue;
            }

            // [WR64] Which half this projection draws into, latched on THIS
            // thread. A play scissor sets it; the inset leaves it alone, so the
            // shared HUD keeps whichever half the renderer was last in - exactly
            // the rule wr64TwoPFrameCorrectScissor follows at decode.
            wr64TwoPFrameRenderProjection(proj.scissorRect.ulx, proj.scissorRect.uly,
                proj.scissorRect.lrx, proj.scissorRect.lry);
            int wr64VerticalViewportHalf = 0;
            auto wr64VerticalViewportRole = Wr64VerticalViewport::Shared;
            if (wr64Vertical.active && proj.usesViewport() &&
                proj.transformsIndex < drawData.rspViewports.size()) {
                const auto &vp = drawData.rspViewports[proj.transformsIndex];
                wr64VerticalViewportRole = wr64VerticalViewport(vp.scale.x, vp.scale.y,
                    vp.translate.x, vp.translate.y, wr64VerticalViewportHalf);
            }

#       if RT_ENABLED
            // TODO: Move heuristics of RT proj elsewhere?
            // TODO: Use detected scenes logic instead.
            const bool perspProj = (proj.type == Projection::Type::Perspective);
            bool rtProj = p.rtEnabled && perspProj && fbPair.depthWrite && targetDrawCall.rtScenes.empty(); // TODO: Remove the last condition once multiple heaps per RT scene are supported.

            // Make sure the matrices are compatible if we're switching to a new projection.
            bool rtProjCompatible = true;
            if (rtProj && (!rtScene.instanceIndices.empty())) {
                const float Threshold = 1e-6f;
                const float viewMatrixDiff = matrixDifference(drawData.modViewTransforms[proj.transformsIndex], rtScene.curViewMatrix);
                const float projMatrixDiff = matrixDifference(drawData.modProjTransforms[proj.transformsIndex], rtScene.curProjMatrix);
                rtProjCompatible = (viewMatrixDiff < Threshold) && (projMatrixDiff < Threshold);
            }

            // TODO: Remove this condition once multiple heaps per RT scene are supported.
            if (rtProj && !rtProjCompatible) {
                rtProj = false;
            }
#       endif
            
            auto &triangles = instanceDrawCall.triangles;
            triangles.screenScale = { 1.0f, 1.0f };
            triangles.screenOffset = halfPixelOffset;

            float projInvRatioScale = 1.0f / aspectRatioScale;
            const int16_t *viewportClipRatios = &drawData.viewportClipRatios[proj.transformsIndex * 4];
            const uint16_t viewportOrigin = drawData.viewportOrigins[proj.transformsIndex];
            if (proj.usesViewport()) {
                // The call's scissor spans the whole width of the framebuffer pair scissor. Custom origin must not be in use to be able to use the stretched viewport.
                const auto &viewport = drawData.rspViewports[proj.transformsIndex];
                FixedRect intersectionRect = proj.scissorRect.intersection(viewport.rect(viewportClipRatios));
                bool coversWholeWidth = !intersectionRect.isEmpty() && (intersectionRect.ulx <= fbPair.scissorRect.ulx) && (intersectionRect.lrx >= fbPair.scissorRect.lrx);
                bool horizontalRatio = !intersectionRect.isEmpty() && (intersectionRect.width(true, true) > intersectionRect.height(true, true));
                bool useWideViewport = (viewportOrigin == G_EX_ORIGIN_NONE) && coversWholeWidth && horizontalRatio;

                // WR64_TRI_WIDE_SPACE (EXP-020): the IPS-native game authors ALL geometry in
                // the wide 424x240 logical space, including menu panes whose ortho viewports
                // are offset for slide/scroll animation. Offset viewports legitimately fail
                // the coversWholeWidth heuristic above, sending the ENTIRE steady-state menu
                // through the native-aspect centered fallback: x3.018868 x 0.99375 = exactly
                // x3.0, centered at +4px -- the pixel-measured menu image [4,1273)x[0,717)
                // whose stale surround is the "menu edge strips". Under the gate, orthographic
                // projections with no extended origin ALWAYS take the wide branch (matching
                // the WR64_RECT_WIDE_SPACE / WR64_FILL_WIDE_SPACE architecture rule).
                // Perspective projections (gameplay 3D) are deliberately untouched.
                // EXP-021 correction: the menu projections classify as Type::Perspective
                // (enum: None=0, Perspective=1, Orthographic=2, ...), so keying on
                // Orthographic (EXP-020) never applied. Key on the projection SCISSOR
                // spanning the full framebuffer-pair scissor width instead, regardless of
                // type: menu panes with offset slide/scroll viewports are caught; the
                // inset-scissor watercraft preview box is untouched; gameplay 3D and 2P
                // half-frame projections have full-width scissors AND full-width viewports,
                // so they already take the wide branch and forcing it is a no-op for them.
                // ★ VALIDATED FIX, COMPILED IN. No environment variable.
                if ((viewportOrigin == G_EX_ORIGIN_NONE) &&
                    (proj.scissorRect.ulx <= fbPair.scissorRect.ulx) && (proj.scissorRect.lrx >= fbPair.scissorRect.lrx)) {
                    useWideViewport = true;
                }
                if (wr64WideWatercraftSelect) {
                    useWideViewport = wr64WatercraftShadeProjection(*p.curWorkload,
                        uint32_t(p.fbPairIndex), pr);
                }
                if (wr64WideLayout.active() && proj.wr64MenuModelPreview) {
                    // Keep the whole native result-row viewport centered with
                    // its black rectangle; expanding the offset viewport center
                    // while contracting its projection separates the two.
                    useWideViewport = false;
                }

                if (useWideViewport) {
                    projInvRatioScale = 1.0f;
                }
                else {
                    triangles.screenScale.x = originalWidth / wideWidth;

                    if (viewportOrigin < G_EX_ORIGIN_NONE) {
                        const float centerOffset = ((middleViewport * viewportOrigin) / G_EX_ORIGIN_CENTER) * extOriginPercentage + middleViewport * (1.0f - extOriginPercentage);
                        triangles.screenOffset.x = halfPixelOffset.x + ((centerOffset - middleViewport) / halfViewportSize.x);
                    }
                }

                if (wr64EdgeTraceEnabled()) {
                    const FixedRect vpTraceRect = viewport.rect(viewportClipRatios);
                    // R2: every edge of both rects, plus the raw viewport, so two
                    // projections that differ only vertically stay distinct.
                    const float vpScaleX = viewport.scale.x;
                    const float vpScaleY = viewport.scale.y;
                    const float vpTransX = viewport.translate.x;
                    const float vpTransY = viewport.translate.y;
                    const uint64_t key = wr64EdgeHashN("proj",
                        vpTraceRect.ulx, vpTraceRect.uly, vpTraceRect.lrx, vpTraceRect.lry,
                        proj.scissorRect.ulx, proj.scissorRect.uly, proj.scissorRect.lrx, proj.scissorRect.lry,
                        fbPair.scissorRect.uly, fbPair.scissorRect.lry,
                        lround(vpScaleY * 16.0f), lround(vpTransY * 16.0f),
                        long(useWideViewport) + 2 * lround(wideWidth), long(proj.type));
                    if (!wr64EdgeTraceSeen(key)) {
                        std::printf("[edge] PROJ type=%d vp=(%g,%g)-(%g,%g) vpScale=(%g,%g) vpTrans=(%g,%g) projScissor=(%g,%g)-(%g,%g) fbScissor=(%g,%g)-(%g,%g) covers=%d hRatio=%d origin=%u wide=%d scaleX=%g offX=%g wideW=%g origW=%g\n",
                            int(proj.type), vpTraceRect.ulx / 4.0, vpTraceRect.uly / 4.0, vpTraceRect.lrx / 4.0, vpTraceRect.lry / 4.0,
                            double(vpScaleX), double(vpScaleY), double(vpTransX), double(vpTransY),
                            proj.scissorRect.ulx / 4.0, proj.scissorRect.uly / 4.0, proj.scissorRect.lrx / 4.0, proj.scissorRect.lry / 4.0,
                            fbPair.scissorRect.ulx / 4.0, fbPair.scissorRect.uly / 4.0, fbPair.scissorRect.lrx / 4.0, fbPair.scissorRect.lry / 4.0,
                            coversWholeWidth ? 1 : 0, horizontalRatio ? 1 : 0, unsigned(viewportOrigin), useWideViewport ? 1 : 0,
                            double(triangles.screenScale.x), double(triangles.screenOffset.x), double(wideWidth), double(originalWidth));
                        { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
                    }
                }

                viewportClip = convertViewportRect(viewport.rect(viewportClipRatios), p.resolutionScale, p.fbWidth, projInvRatioScale, extOriginPercentage, 0.0f, viewportOrigin, viewportOrigin);
                // Model rotation still uses RT64's matrix interpolation. Only
                // the native preview's screen translation/clip follows the
                // same ending panel phase as its black backdrop and labels.
                const float wr64EndingModelDy = wr64EndingModelPanel.offsetY(
                    proj.wr64MenuModelPreview, viewport.translate.x, viewport.translate.y);
                if (wr64EndingModelDy != 0.0f) {
                    viewportClip.y += wr64EndingModelDy * p.resolutionScale.y;
                    triangles.screenOffset.y -= wr64EndingModelDy * p.resolutionScale.y / halfViewportSize.y;
                }
            }

            for (uint32_t d = 0; (d < proj.gameCallCount) && (globalCallIndex < p.maxGameCall); d++) {
                triangles.wr64DolphinSunOpacityLoss = 0.0f;
                const GameCall &call = proj.gameCalls[d];
                const int wr64VerticalPauseHalf = wr64Vertical.active &&
                    call.callDesc.callIndex >= p.curWorkload->wr64PauseFirstCall &&
                    call.callDesc.callIndex < p.curWorkload->wr64PauseLastCall
                    ? p.curWorkload->wr64PauseDrawOwner : 0;
                const int wr64VerticalLapHalf = wr64Vertical.active
                    ? wr64LapOwner(p.curWorkload->wr64LapScope, call.callDesc.callIndex) : 0;
                const bool wr64VerticalSceneRect = wr64Vertical.active &&
                    proj.type == Projection::Type::Rectangle &&
                    wr64VerticalHalfScissor(call.callDesc.scissorRect.ulx, call.callDesc.scissorRect.uly,
                        call.callDesc.scissorRect.lrx, call.callDesc.scissorRect.lry) != 0;
                // The old final coverage strips describe the horizontal seam,
                // not scene color. Keep their bookkeeping index, but do not
                // draw horizontal strips across a vertical race presentation.
                if (wr64Vertical.active && call.callDesc.extendedType == DrawExtendedType::None &&
                    wr64VerticalCoverageStrip(call.callDesc.rect.ulx, call.callDesc.rect.uly,
                        call.callDesc.rect.lrx, call.callDesc.rect.lry,
                        call.callDesc.otherMode.L, call.callDesc.fillColor)) {
                    globalCallIndex++;
                    continue;
                }
                FixedRect wr64ComposerCallRect = call.callDesc.rect;
                FixedRect wr64ComposerScissorRect = call.callDesc.scissorRect;
                bool wr64WideLocalRectangle = false;
                bool wr64WideCelestialRectangle = false;
                int wr64WideHudAnchor = 0;

                // HUD-CENSUS-R1. Measurement only, dormant unless WR64_HUD_CENSUS
                // names a file. Records the AUTHORED rect and scissor, before any
                // correction touches them, so the census describes the game rather
                // than this renderer. Rectangle projections never reach the
                // usesViewport() trace above, which is exactly the gap this fills.
                // Texture identity for this call. Screen position alone cannot tell a
                // race HUD glyph from a menu slider that happens to land in the same
                // place, and cannot tell one game mode from another; the sampled
                // texture can do both.
                uint64_t wr64HudTmemHash = 0;
                uint32_t wr64HudSampleW = 0;
                uint32_t wr64HudSampleH = 0;
                if ((call.callDesc.tileCount > 0) && (p.curWorkload != nullptr) &&
                    (call.callDesc.tileIndex < p.curWorkload->drawData.callTiles.size()))
                {
                    const DrawCallTile &wr64HudTile = p.curWorkload->drawData.callTiles[call.callDesc.tileIndex];
                    wr64HudTmemHash = wr64HudTile.tmemHashOrID;
                    wr64HudSampleW = wr64HudTile.sampleWidth;
                    wr64HudSampleH = wr64HudTile.sampleHeight;
                }
                // These restored sky sprites follow the scene camera. The
                // positional 2P HUD rules would otherwise move them when they
                // enter the HUD's inset box, including a vertical jump at its
                // side edges. Preserve their interpolated coordinates in both
                // layouts; ordinary HUD rectangles retain their own anchors.
                const bool wr64TwoPCelestialSceneRect = wr64TwoPFrameActive() &&
                    proj.type == Projection::Type::Rectangle &&
                    wr64VerticalHalfScissor(call.callDesc.scissorRect.ulx, call.callDesc.scissorRect.uly,
                        call.callDesc.scissorRect.lrx, call.callDesc.scissorRect.lry) != 0 &&
                    (wr64HudTmemHash == Wr64CelestialSunGlow || wr64HudTmemHash == Wr64CelestialSunDisk ||
                        wr64HudTmemHash == Wr64CelestialSunFlare || wr64HudTmemHash == Wr64CelestialTcStar);
                const bool wr64FinishHudCall = proj.type == Projection::Type::Rectangle &&
                    wr64FinishHudMember(call.callDesc.rect, wr64HudTmemHash, wr64FinishHudRows);

                // RECT TRACK. Diagnostic, dormant unless WR64_RECT_TRACK names a
                // file, and filtered to the celestial watch list inside the
                // recorder. Records the AUTHORED rect - call.callDesc.rect, the
                // native quarter-pixel values the game submitted - not the
                // composer/anchor-adjusted copy, because the question this
                // answers is what the GAME does per tick. READS ONLY. Runs here
                // rather than in GameFrame::match because match never walks
                // Rectangle projections at all, which is itself the finding.
                if ((proj.type == Projection::Type::Rectangle) && (p.curWorkload != nullptr)) {
                    // dsdx/dtdy, other mode and prim colour joined 2026-08-04
                    // for the DP corner-square investigation; the recorder
                    // header says what each is for. The prim colour is read
                    // through a bound reference and explicit float casts -
                    // the same idiom rt64_state.cpp already uses - because
                    // interop vector members are not assumed to be PODs here.
                    const interop::float4 &wr64RectPrim = call.callDesc.rdpParams.primColor;
                    // R6: the DRAWN side of the story. The blended rect this
                    // OUTPUT frame (the same lookup the apply site below does)
                    // and the call's authored vertex UVs. Whether the blend
                    // actually changes per output frame on screen is the
                    // question the R5 verdict left open; these columns close
                    // it with a row count instead of an argument.
                    uint32_t wr64RectLerpFound = 0;
                    int32_t wr64RectLerpUlx = 0, wr64RectLerpUly = 0;
                    int32_t wr64RectLerpLrx = 0, wr64RectLerpLry = 0;
                    if (!p.curWorkload->wr64CelestialLerpRects.empty()) {
                        const auto wr64RectLerpIt = p.curWorkload->wr64CelestialLerpRects.find(
                            wr64CelestialRectKey(uint32_t(p.fbPairIndex), pr, d));
                        if (wr64RectLerpIt != p.curWorkload->wr64CelestialLerpRects.end()) {
                            wr64RectLerpFound = 1;
                            wr64RectLerpUlx = wr64RectLerpIt->second.ulx;
                            wr64RectLerpUly = wr64RectLerpIt->second.uly;
                            wr64RectLerpLrx = wr64RectLerpIt->second.lrx;
                            wr64RectLerpLry = wr64RectLerpIt->second.lry;
                        }
                    }
                    float wr64RectU1 = 0.0f, wr64RectV1 = 0.0f;
                    float wr64RectU2 = 0.0f, wr64RectV2 = 0.0f;
                    {
                        const auto &wr64RectTc = p.curWorkload->drawData.triTcFloats;
                        const size_t wr64RectTcBase = size_t(call.meshDesc.rawVertexStart) * 2;
                        if ((wr64RectTcBase + 8) <= wr64RectTc.size()) {
                            wr64RectU1 = wr64RectTc[wr64RectTcBase + 0];
                            wr64RectV1 = wr64RectTc[wr64RectTcBase + 1];
                            wr64RectU2 = wr64RectTc[wr64RectTcBase + 6];
                            wr64RectV2 = wr64RectTc[wr64RectTcBase + 7];
                        }
                    }
                    wr64RectTrackRecord(
                        p.curWorkload->submissionFrame,
                        uint32_t(p.fbPairIndex), pr, d,
                        wr64HudTmemHash,
                        call.callDesc.rect.ulx, call.callDesc.rect.uly,
                        call.callDesc.rect.lrx, call.callDesc.rect.lry,
                        int32_t(call.callDesc.rectDsdx), int32_t(call.callDesc.rectDtdy),
                        call.callDesc.colorCombiner.H, call.callDesc.colorCombiner.L,
                        call.callDesc.otherMode.H, call.callDesc.otherMode.L,
                        float(wr64RectPrim.x), float(wr64RectPrim.y),
                        float(wr64RectPrim.z), float(wr64RectPrim.w),
                        wr64RectLerpFound,
                        wr64RectLerpUlx, wr64RectLerpUly, wr64RectLerpLrx, wr64RectLerpLry,
                        wr64RectU1, wr64RectV1, wr64RectU2, wr64RectV2,
                        call.callDesc.scissorRect.ulx, call.callDesc.scissorRect.uly,
                        call.callDesc.scissorRect.lrx, call.callDesc.scissorRect.lry);
                }

                // WR64 CELESTIAL RECT INTERPOLATION. The transform processor
                // rebuilt lerpRects for THIS output frame from the pairs the
                // match pass made; a hit replaces the authored rect with the
                // blended one before anything downstream sees it, so the
                // composer's own deltas still stack on top untouched. The map
                // holds ONLY sun draws - claimed by texture in the pairing
                // pass - so every HUD rect misses this lookup by construction,
                // and the empty() test keeps the miss free for the 99% of
                // frames with no sun. The recorder above stays on the AUTHORED
                // rect on purpose: it measures the game, not this fix.
                bool wr64CelRectOverridden = false;
                if ((proj.type == Projection::Type::Rectangle) && (p.curWorkload != nullptr) &&
                    !p.curWorkload->wr64CelestialLerpRects.empty())
                {
                    const auto wr64CelIt = p.curWorkload->wr64CelestialLerpRects.find(
                        wr64CelestialRectKey(uint32_t(p.fbPairIndex), pr, d));
                    if (wr64CelIt != p.curWorkload->wr64CelestialLerpRects.end()) {
                        wr64ComposerCallRect = wr64CelIt->second;
                        wr64CelRectOverridden = true;
                    }
                }

                // Suppress unpaired Dolphin Park disk rectangles shortened by the native
                // top-edge clamp. Use authored geometry after the interpolation lookup;
                // full-height rectangles remain visible. Reconstructed transit pairs already
                // carry the correct exit/entry position and must bypass this collapse.
                // Collapse other parked draws to a zero-area point at their horizontal center,
                // y=24 qpx. Both y edges stay outside the scissor snap tolerance, so snapping
                // cannot reopen their height even if an x edge is adjusted at the corner.
                if ((proj.type == Projection::Type::Rectangle) &&
                    (!wr64CelRectOverridden) &&
                    (wr64HudTmemHash == Wr64CelestialSunDiskDP) &&
                    (call.callDesc.rect.uly == 0) &&
                    (call.callDesc.rect.lry < Wr64CelestialDpFullRectQuarterPx))
                {
                    const int32_t wr64ParkCentreX = (wr64ComposerCallRect.ulx + wr64ComposerCallRect.lrx) / 2;
                    wr64ComposerCallRect.ulx = wr64ParkCentreX;
                    wr64ComposerCallRect.lrx = wr64ParkCentreX;
                    wr64ComposerCallRect.uly = 24;
                    wr64ComposerCallRect.lry = 24;
                    wr64CelestialParkNote();
                }

                wr64HudCensusRecord(int32_t(proj.type), call.callDesc.rect, call.callDesc.scissorRect,
                    call.callDesc.triangleCount, call.callDesc.tileCount,
                    wr64HudTmemHash, wr64HudSampleW, wr64HudSampleH);

                // Keep the R3 parked-sun suppression above intact. Only the
                // already-admitted disk receives this output-frame fade.
                const bool wr64DolphinSunEdge = proj.type == Projection::Type::Rectangle &&
                    wr64HudTmemHash == Wr64CelestialSunDiskDP &&
                    p.curWorkload->wr64DolphinSunEdge != Wr64DolphinSunEdgeScope::None;
                if (wr64DolphinSunEdge) {
                    triangles.wr64DolphinSunOpacityLoss = 1.0f - wr64DolphinSunEdgeOpacity(
                        p.curWorkload->wr64DolphinSunEdge, wr64HudTmemHash, true,
                        float(wr64ComposerCallRect.uly));
                }

                const bool wr64DolphinSunPresentation = p.wr64RtPresentation &&
                    wr64DolphinSunClaimValid(call.callDesc, drawData, proj.type == Projection::Type::Rectangle);
                Wr64DolphinSunRect wr64DolphinSunRect{};
                bool wr64DolphinSunInterpolated = false;
                if (wr64DolphinSunPresentation) {
                    wr64DolphinSunRect = wr64DolphinSunFullRect(call.callDesc.wr64DolphinSunSprite);
                    const auto key = wr64CelestialRectKey(uint32_t(p.fbPairIndex), pr, d);
                    const auto found = p.curWorkload->wr64DolphinSunOutputRects.find(key);
                    if (found != p.curWorkload->wr64DolphinSunOutputRects.end()) {
                        wr64DolphinSunRect = found->second;
                        wr64DolphinSunInterpolated = true;
                    }
                }

                // HUD-ANCHOR-R2. A TRANSLATION, never a scale, so glyph size and
                // intra-widget spacing are untouched. The offset depends only on
                // this call's own rect and the static widget table - no per-frame
                // state, so nothing else being drawn can change it. Returns false
                // unless the correction is armed and the rect matches a widget.
                int32_t wr64HudAnchorDx = 0;
                int32_t wr64HudAnchorDy = 0;
                if (wr64VerticalPauseHalf == 0 && wr64VerticalLapHalf == 0 && !wr64VerticalSceneRect &&
                    !wr64TwoPCelestialSceneRect &&
                    wr64HudAnchorOffsetForRect(int32_t(proj.type), call.callDesc.rect,
                        wr64HudTmemHash, wr64HudAnchorDx, wr64HudAnchorDy)) {
                    wr64ComposerCallRect.ulx += wr64HudAnchorDx;
                    wr64ComposerCallRect.lrx += wr64HudAnchorDx;
                    wr64ComposerCallRect.uly += wr64HudAnchorDy;
                    wr64ComposerCallRect.lry += wr64HudAnchorDy;
                }
                if (wr64FinishHudCall) {
                    // Portraits already receive this inset translation from
                    // right_stack. Apply the same amount to the newly identified
                    // finish-only members at baseline and expanded HUD widths.
                    const int32_t dx = (424 - wr64HudAnchorBox().right) * 4;
                    wr64ComposerCallRect.ulx += dx;
                    wr64ComposerCallRect.lrx += dx;
                }
                const WR64LayerTrace::ComposerOverride wr64ComposerOverride =
                    WR64LayerTrace::composerCallOverride(*p.curWorkload, p.fbPairIndex, pr, d,
                        proj, call, p.fbWidth, p.fbHeight, p.targetWidth, p.targetHeight);
                int32_t wr64ViewportLeft = wr64ComposerOverride.viewportLeft;
                int32_t wr64ViewportTop = wr64ComposerOverride.viewportTop;
                int32_t wr64ViewportRight = wr64ComposerOverride.viewportRight;
                int32_t wr64ViewportBottom = wr64ComposerOverride.viewportBottom;
                // ★ VALIDATED FIXES, COMPILED IN. No environment variables.
                constexpr bool wr64OptionsOrthoViewportFix = true;
                constexpr bool wr64WatercraftOrthoViewportFix = true;
                constexpr uint64_t WR64OptionsOrthoBackgroundSignature = 0xF071DB66857C923FULL;
                constexpr uint64_t WR64ChangeNamesOrthoBackgroundSignature = 0x13221A032A3D060CULL;
                constexpr uint64_t WR64WatercraftOrthoEdgeSignature = 0x6FA7628759844120ULL;
                const bool wr64HasManualViewportOverride =
                    (wr64ViewportLeft != 0) || (wr64ViewportTop != 0) ||
                    (wr64ViewportRight != 0) || (wr64ViewportBottom != 0);
                const bool wr64OptionsBackgroundCall =
                    (wr64ComposerOverride.signature == WR64OptionsOrthoBackgroundSignature) ||
                    (wr64ComposerOverride.signature == WR64ChangeNamesOrthoBackgroundSignature);
                const bool wr64WatercraftEdgeCall =
                    (wr64ComposerOverride.signature == WR64WatercraftOrthoEdgeSignature);
                // Banner identity cannot include emission order: other visible
                // draws change those indices while MAX POWER remains on screen.
                // Match its texture, sample dimensions, geometry and render state.
                const bool wr64BannerAnchorCall =
                    wr64BannerAnchorMatch(int32_t(proj.type), wr64HudTmemHash,
                        wr64HudSampleW, wr64HudSampleH, call.callDesc.triangleCount,
                        call.callDesc.tileCount, call.callDesc.textureOn,
                        call.callDesc.colorCombiner.H, call.callDesc.colorCombiner.L,
                        call.callDesc.otherMode.H, call.callDesc.otherMode.L);
                // GANTRY ANCHOR. The race-start traffic light assembly is a 3D scene
                // object, so a per-call signature is the wrong key - it hashes the
                // call index, which moves as scene objects come and go. This keys on
                // the draw's own identity instead: texture, triangle count, combiner
                // and other mode. Gated on Perspective first. Default OFF.
                const bool wr64GantryAnchorCall =
                    (proj.type == Projection::Type::Perspective) &&
                    wr64GantryAnchorMatch(wr64HudTmemHash, call.callDesc.triangleCount,
                        call.callDesc.colorCombiner.H, call.callDesc.colorCombiner.L,
                        call.callDesc.otherMode.H, call.callDesc.otherMode.L);
                if (wr64OptionsOrthoViewportFix && wr64OptionsBackgroundCall &&
                    !wr64HasManualViewportOverride) {
                    // Validated native N64 edge discrepancy: two pixels right,
                    // one pixel bottom. Values remain in RDP 10.2 coordinates
                    // and are scaled by the active internal resolution below.
                    wr64ViewportRight = 2 * 4;
                    wr64ViewportBottom = 1 * 4;
                }
                else if (wr64WatercraftOrthoViewportFix && wr64WatercraftEdgeCall &&
                    !wr64HasManualViewportOverride) {
                    // Watercraft Select has the same two-pixel right-edge
                    // discrepancy but no bottom-edge discrepancy.
                    wr64ViewportRight = 2 * 4;
                    wr64ViewportBottom = 0;
                }
                else if (wr64GantryAnchorCall && !wr64HasManualViewportOverride) {
                    // Equal opposite edges again: translation only, never a resize.
                    int32_t wr64GantryDx4 = 0;
                    int32_t wr64GantryDy4 = 0;
                    wr64GantryAnchorOffset(wr64GantryDx4, wr64GantryDy4);
                    wr64ViewportLeft = wr64GantryDx4;
                    wr64ViewportRight = wr64GantryDx4;
                    wr64ViewportTop = wr64GantryDy4;
                    wr64ViewportBottom = wr64GantryDy4;
                }
                else if (wr64BannerAnchorCall && !wr64HasManualViewportOverride) {
                    // Equal opposite edges. The renderer turns these into
                    //   screenScale  += (right - left) / width      -> 0
                    //   screenOffset += (right + left) / width      -> the move
                    // so this translates the banner and cannot resize it.
                    // [WR64] R2. wr64BannerAnchorOffset is now two-player aware
                    // by itself: both halves take the power meter's two-player
                    // offset, +10,0, so there is no half to derive and R1's
                    // half-from-the-rect function is gone. It could never have
                    // worked - the rect is the whole frame on every single call.
                    // [WR64] R5. THE BANNER'S OWN POSITION, at last.
                    //
                    // Its rect is the whole frame and its scissor is the whole
                    // frame, so neither can place it - but it is a draw like any
                    // other and carries minWorldMatrix. drawData.worldTransforms
                    // [3].y is the same quantity the object census has been
                    // recording off this exact field, and the two banners are
                    // drawn 110 pixels apart, so their transforms differ.
                    // Bounds-checked the same way the census is: an index can run
                    // past the end on the frame a workload is rebuilt, and a
                    // correction must never be the thing that crashes a session.
                    float wr64BannerWorldY = -1.0f;
                    {
                        const uint32_t wr64BannerWorld = uint32_t(call.callDesc.minWorldMatrix);
                        if ((p.curWorkload != nullptr) &&
                            (wr64BannerWorld < p.curWorkload->drawData.worldTransforms.size()))
                        {
                            const hlslpp::float4x4 &wr64BannerM =
                                p.curWorkload->drawData.worldTransforms[wr64BannerWorld];
                            // MATERIALISE THE float3 FIRST. m[3].xyz is a
                            // swizzle3 proxy and has no .y member - chaining off
                            // it is C2039. Three lines down from here the object
                            // census does exactly this, and it is the reason it
                            // compiles.
                            const hlslpp::float3 wr64BannerPos = wr64BannerM[3].xyz;
                            wr64BannerWorldY = float(wr64BannerPos.y);
                        }
                    }
                    int32_t wr64BannerDx4 = 0;
                    int32_t wr64BannerDy4 = 0;
                    int wr64BannerHalf = 0;
                    bool wr64BannerPlaceable = false;
                    wr64BannerAnchorOffset(wr64BannerWorldY, wr64BannerDx4, wr64BannerDy4,
                        wr64BannerHalf, wr64BannerPlaceable);

                    // [WR64] R2 trace. The texture and the two call-graph indices
                    // are what R1 was missing: every one of its rows had the same
                    // full-frame rect, so nothing in it could say which draw a
                    // matched signature belonged to. Still armed, because four
                    // signatures fired 12,085 and 8,155 times in one session and
                    // no banner does that. See rt64_wr64_banner_anchor.h.
                    wr64BannerAnchorTrace(wr64ComposerOverride.signature, wr64HudTmemHash, pr, d,
                        call.callDesc.rect.ulx, call.callDesc.rect.uly,
                        call.callDesc.rect.lrx, call.callDesc.rect.lry,
                        call.callDesc.scissorRect.ulx, call.callDesc.scissorRect.uly,
                        call.callDesc.scissorRect.lrx, call.callDesc.scissorRect.lry,
                        wr64BannerWorldY, wr64BannerPlaceable ? wr64BannerHalf : -1,
                        wr64BannerDx4, wr64BannerDy4);
                    wr64ViewportLeft = wr64BannerDx4;
                    wr64ViewportRight = wr64BannerDx4;
                    wr64ViewportTop = wr64BannerDy4;
                    wr64ViewportBottom = wr64BannerDy4;
                }
                const bool wr64ApplyOrthoViewport =
                    (proj.type == Projection::Type::Orthographic) &&
                    (wr64ComposerOverride.matched ||
                        (wr64OptionsOrthoViewportFix && wr64OptionsBackgroundCall) ||
                        (wr64WatercraftOrthoViewportFix && wr64WatercraftEdgeCall) ||
                        wr64BannerAnchorCall);
                // Same viewport nudge, but the gantry is a Perspective draw, so it
                // cannot go through the Orthographic gate above.
                const bool wr64ApplyViewportNudge = wr64ApplyOrthoViewport || wr64GantryAnchorCall;

                // GANTRY LERP TRACE. Dormant unless WR64_GANTRY_LERP_TRACE names a
                // file.
                //
                // The link from a draw to its world transform is minWorldMatrix,
                // filled by RSP::drawIndexedTri straight out of DrawData::worldIndices
                // as the triangles are emitted. The first version of this scanned
                // worldTransformVertexIndices for the range containing the draw's
                // first vertex - reinventing this, and getting it wrong on 10-25% of
                // draws. Use the value the RSP already computed.
                //
                // A row is recorded on EVERY matched draw, so an empty file can never
                // be confused with a trace that did not arm. The group column carries
                // a sentinel when there is nothing to resolve against:
                //   FFFFFFF0  no workload
                //   FFFFFFF1  minWorldMatrix past the end of the transform arrays
                if (wr64GantryAnchorCall && wr64GantryLerpTraceArmed()) {
                    uint32_t wr64GantryGroup = 0xFFFFFFF0u;
                    uint32_t wr64GantryMatrixId = 0;
                    uint32_t wr64GantryPhysAddr = 0;
                    uint32_t wr64GantrySegAddr = 0;
                    uint8_t wr64GantryPosInterp = 0xFF;
                    uint8_t wr64GantryVtxInterp = 0xFF;
                    bool wr64GantryMoves = false;
                    bool wr64GantryLerped = false;

                    if (p.curWorkload != nullptr) {
                        const auto &wr64GantryData = p.curWorkload->drawData;
                        const size_t wr64GantryWorld = call.callDesc.minWorldMatrix;
                        if ((wr64GantryWorld < wr64GantryData.worldTransforms.size()) &&
                            (wr64GantryWorld < wr64GantryData.prevWorldTransforms.size()) &&
                            (wr64GantryWorld < wr64GantryData.worldTransformGroups.size()))
                        {
                            wr64GantryGroup = wr64GantryData.worldTransformGroups[wr64GantryWorld];
                            if (wr64GantryGroup < wr64GantryData.transformGroups.size()) {
                                const TransformGroup &wr64GantryTg =
                                    wr64GantryData.transformGroups[wr64GantryGroup];
                                wr64GantryPosInterp = wr64GantryTg.positionInterpolation;
                                wr64GantryVtxInterp = wr64GantryTg.vertexInterpolation;
                                wr64GantryMatrixId = wr64GantryTg.matrixId;
                            }
                            if (wr64GantryWorld < wr64GantryData.worldTransformPhysicalAddresses.size()) {
                                wr64GantryPhysAddr =
                                    wr64GantryData.worldTransformPhysicalAddresses[wr64GantryWorld];
                            }
                            if (wr64GantryWorld < wr64GantryData.worldTransformSegmentedAddresses.size()) {
                                wr64GantrySegAddr =
                                    wr64GantryData.worldTransformSegmentedAddresses[wr64GantryWorld];
                            }

                            const size_t wr64GantryMatBytes =
                                sizeof(wr64GantryData.worldTransforms[wr64GantryWorld]);
                            wr64GantryMoves = wr64GantryBytesDiffer(
                                &wr64GantryData.worldTransforms[wr64GantryWorld],
                                &wr64GantryData.prevWorldTransforms[wr64GantryWorld],
                                wr64GantryMatBytes);
                            if (wr64GantryWorld < wr64GantryData.lerpWorldTransforms.size()) {
                                wr64GantryLerped = wr64GantryBytesDiffer(
                                    &wr64GantryData.lerpWorldTransforms[wr64GantryWorld],
                                    &wr64GantryData.worldTransforms[wr64GantryWorld],
                                    wr64GantryMatBytes);
                            }
                        }
                        else {
                            wr64GantryGroup = 0xFFFFFFF1u;
                        }
                    }

                    wr64GantryLerpRecord(wr64HudTmemHash, call.callDesc.triangleCount,
                        wr64GantryGroup, wr64GantryMatrixId, wr64GantryPhysAddr,
                        wr64GantrySegAddr, wr64GantryPosInterp, wr64GantryVtxInterp,
                        wr64GantryMoves, wr64GantryLerped);
                }

                // MATRIX SLOT REUSE TRACE. Dormant unless WR64_MATRIX_SEG_TRACE names
                // a file. Runs for EVERY draw, not just gantry ones - the whole point
                // is to find out who else uses the start lights' matrix slots before a
                // matrixId rule is keyed on those addresses. is_gantry says whether the
                // gantry table would have claimed the draw.
                if (wr64SegTraceArmed() && (p.curWorkload != nullptr)) {
                    const auto &wr64SegData = p.curWorkload->drawData;
                    const size_t wr64SegWorld = call.callDesc.minWorldMatrix;
                    if (wr64SegWorld < wr64SegData.worldTransformSegmentedAddresses.size()) {
                        const uint32_t wr64SegAddr =
                            wr64SegData.worldTransformSegmentedAddresses[wr64SegWorld];
                        if (wr64SegTraceInWindow(wr64SegAddr)) {
                            uint32_t wr64SegPhys = 0;
                            if (wr64SegWorld < wr64SegData.worldTransformPhysicalAddresses.size()) {
                                wr64SegPhys =
                                    wr64SegData.worldTransformPhysicalAddresses[wr64SegWorld];
                            }
                            wr64SegTraceRecord(wr64SegAddr, wr64SegPhys, wr64HudTmemHash,
                                call.callDesc.triangleCount, uint32_t(proj.type),
                                call.callDesc.colorCombiner.H, call.callDesc.colorCombiner.L,
                                call.callDesc.otherMode.H, call.callDesc.otherMode.L,
                                wr64GantryAnchorCall);
                        }
                    }
                }
                // OBJECT CENSUS. Dormant unless WR64_OBJECT_CENSUS names a file.
                // One row per (submission frame, world transform): what that
                // transform actually draws. It exists to be JOINED to the
                // lerp-gate trace, which knows which transform got gated and how
                // far it appeared to move but has no idea what the thing is.
                // Both sides key on the workload's submissionFrame and on the
                // same world transform index, so the join is exact.
                // See common/rt64_wr64_object_census.h.
                if (wr64ObjectCensusArmed() && (p.curWorkload != nullptr)) {
                    // R2: the transform's own translation. Bounds-checked because a
                    // draw can carry an index past the end on the frame a workload
                    // is rebuilt, and a recorder must never be the thing that
                    // crashes a play session.
                    float wr64CensusX = 0.0f, wr64CensusY = 0.0f, wr64CensusZ = 0.0f;
                    const uint32_t wr64CensusWorld = uint32_t(call.callDesc.minWorldMatrix);
                    if (wr64CensusWorld < p.curWorkload->drawData.worldTransforms.size()) {
                        // [3].xyz is the SAME quantity RigidBody::updateLinear reads
                        // and the lerp gate compares, so the recorded position and the
                        // gate's decision are about the same number by construction.
                        // float(v.x) is this codebase's idiom - see
                        // wr64SkyBracketProjectClip.
                        const hlslpp::float4x4 &wr64CensusM =
                            p.curWorkload->drawData.worldTransforms[wr64CensusWorld];
                        const hlslpp::float3 wr64CensusPos = wr64CensusM[3].xyz;
                        wr64CensusX = float(wr64CensusPos.x);
                        wr64CensusY = float(wr64CensusPos.y);
                        wr64CensusZ = float(wr64CensusPos.z);
                    }
                    wr64ObjectCensusRecord(p.curWorkload->submissionFrame,
                        wr64CensusWorld, wr64HudTmemHash,
                        call.callDesc.triangleCount, uint32_t(proj.type),
                        call.callDesc.colorCombiner.H, call.callDesc.colorCombiner.L,
                        call.callDesc.otherMode.H, call.callDesc.otherMode.L,
                        wr64CensusX, wr64CensusY, wr64CensusZ);
                }

                // MATRIX SLOT TRACE. Dormant unless WR64_MATRIX_SLOTS or
                // WR64_MATRIX_TRACK names a file. See
                // common/rt64_wr64_matrix_slots.h.
                //
                // Runs for EVERY draw, deliberately. The question is whether an
                // object's matrix ADDRESS is its identity or a recycled scratch
                // slot, and a slot only looks exclusive if nothing else was
                // filtered out before the count was taken. The gantry answer -
                // one slot carrying 46 different textures - could not have been
                // reached by a trace that recorded only gantry draws.
                //
                // The header filters to the watch list for its per-frame file;
                // the session-wide summary takes everything.
                if (wr64MatrixAnyArmed() && (p.curWorkload != nullptr)) {
                    const auto &wr64MatrixData = p.curWorkload->drawData;
                    const uint32_t wr64MatrixWorld = uint32_t(call.callDesc.minWorldMatrix);

                    // Bounds-checked for the same reason the census is: a draw
                    // can carry an index past the end on the frame a workload is
                    // rebuilt, and a recorder must never be the thing that
                    // crashes a play session.
                    uint32_t wr64MatrixSeg = 0;
                    uint32_t wr64MatrixPhys = 0;
                    if (wr64MatrixWorld < wr64MatrixData.worldTransformSegmentedAddresses.size()) {
                        wr64MatrixSeg =
                            wr64MatrixData.worldTransformSegmentedAddresses[wr64MatrixWorld];
                    }
                    if (wr64MatrixWorld < wr64MatrixData.worldTransformPhysicalAddresses.size()) {
                        wr64MatrixPhys =
                            wr64MatrixData.worldTransformPhysicalAddresses[wr64MatrixWorld];
                    }

                    float wr64MatrixX = 0.0f, wr64MatrixY = 0.0f, wr64MatrixZ = 0.0f;
                    float wr64MatrixSx = 0.0f, wr64MatrixSy = 0.0f, wr64MatrixSz = 0.0f;
                    // R2, 2026-08-03: the upper 3x3, RAW and unnormalised.
                    // Scale already records the basis lengths, so normalising
                    // here would throw away the only thing these columns exist
                    // to show. Zero when the index is out of range, same as the
                    // position columns above - a recorder must never be the
                    // thing that crashes a play session.
                    float wr64MatrixM00 = 0.0f, wr64MatrixM01 = 0.0f, wr64MatrixM02 = 0.0f;
                    float wr64MatrixM10 = 0.0f, wr64MatrixM11 = 0.0f, wr64MatrixM12 = 0.0f;
                    float wr64MatrixM20 = 0.0f, wr64MatrixM21 = 0.0f, wr64MatrixM22 = 0.0f;

                    // R3: the transform ACTUALLY DRAWN this output frame, and the
                    // group's own interpolation modes. lerpOk stays 0 when the
                    // index is out of range so that "not interpolated" and "not
                    // available" never look alike in the CSV.
                    float wr64MatrixLx = 0.0f, wr64MatrixLy = 0.0f, wr64MatrixLz = 0.0f;
                    uint32_t wr64MatrixLerpOk = 0;
                    uint32_t wr64MatrixPosInterp = 0xFFu;
                    uint32_t wr64MatrixVtxInterp = 0xFFu;
                    uint32_t wr64MatrixMatrixId = 0xFFFFFFFFu;
                    // R5: the drawn ROTATION as well as the drawn translation.
                    float wr64MatrixLm00 = 0.0f, wr64MatrixLm01 = 0.0f, wr64MatrixLm02 = 0.0f;
                    float wr64MatrixLm10 = 0.0f, wr64MatrixLm11 = 0.0f, wr64MatrixLm12 = 0.0f;
                    float wr64MatrixLm20 = 0.0f, wr64MatrixLm21 = 0.0f, wr64MatrixLm22 = 0.0f;
                    if (wr64MatrixWorld < wr64MatrixData.lerpWorldTransforms.size()) {
                        // BIND TO hlslpp::float4x4 FIRST. These vectors hold
                        // interop::float4x4, whose operator[] returns a raw
                        // const float *, so indexing the element directly and
                        // asking for .xyz does not compile. The position read a
                        // few lines below goes through exactly this conversion;
                        // this mirrors it rather than inventing a second way.
                        const hlslpp::float4x4 &wr64MatrixLerpM =
                            wr64MatrixData.lerpWorldTransforms[wr64MatrixWorld];
                        const hlslpp::float3 wr64MatrixLerpPos = wr64MatrixLerpM[3].xyz;
                        wr64MatrixLx = float(wr64MatrixLerpPos.x);
                        wr64MatrixLy = float(wr64MatrixLerpPos.y);
                        wr64MatrixLz = float(wr64MatrixLerpPos.z);
                        wr64MatrixLerpOk = 1;

                        wr64MatrixLm00 = float(wr64MatrixLerpM[0].x);
                        wr64MatrixLm01 = float(wr64MatrixLerpM[0].y);
                        wr64MatrixLm02 = float(wr64MatrixLerpM[0].z);
                        wr64MatrixLm10 = float(wr64MatrixLerpM[1].x);
                        wr64MatrixLm11 = float(wr64MatrixLerpM[1].y);
                        wr64MatrixLm12 = float(wr64MatrixLerpM[1].z);
                        wr64MatrixLm20 = float(wr64MatrixLerpM[2].x);
                        wr64MatrixLm21 = float(wr64MatrixLerpM[2].y);
                        wr64MatrixLm22 = float(wr64MatrixLerpM[2].z);
                    }

                    // R5: DOES THE MESH ACTUALLY MOVE? R4 turned vertex
                    // interpolation on for 12 buoy transforms and the tail still
                    // steps. matchTransform only interpolates vertices when the
                    // hash CHANGED, so a rigid buoy makes that fix a guaranteed
                    // no-op - and a constant hash here proves it outright rather
                    // than leaving it as the thing nobody checked.
                    //
                    // FNV-1a over the raw position bytes. Deliberately not XXH3:
                    // this file does not already pull xxHash in, and a recorder
                    // is not worth a new include in a translation unit this size.
                    uint32_t wr64MatrixVtxCount = 0;
                    uint64_t wr64MatrixVtxHash = 0;
                    uint64_t wr64MatrixColHash = 0;
                    if ((wr64MatrixWorld + 1) < wr64MatrixData.worldTransformVertexIndices.size()) {
                        const uint32_t wr64MatrixVtxIndex =
                            wr64MatrixData.worldTransformVertexIndices[wr64MatrixWorld];
                        const uint32_t wr64MatrixVtxN =
                            wr64MatrixData.worldTransformVertexCount(wr64MatrixWorld);
                        const size_t wr64MatrixVtxEnd =
                            (size_t(wr64MatrixVtxIndex) + size_t(wr64MatrixVtxN)) * 3;
                        if ((wr64MatrixVtxN > 0) && (wr64MatrixVtxEnd <= wr64MatrixData.posFloats.size())) {
                            wr64MatrixVtxCount = wr64MatrixVtxN;
                            const uint8_t *wr64MatrixVtxBytes = reinterpret_cast<const uint8_t *>(
                                &wr64MatrixData.posFloats[size_t(wr64MatrixVtxIndex) * 3]);
                            const size_t wr64MatrixVtxByteCount =
                                size_t(wr64MatrixVtxN) * 3 * sizeof(float);
                            wr64MatrixVtxHash = 1469598103934665603ULL;
                            for (size_t b = 0; b < wr64MatrixVtxByteCount; b++) {
                                wr64MatrixVtxHash =
                                    (wr64MatrixVtxHash ^ uint64_t(wr64MatrixVtxBytes[b]))
                                    * 1099511628211ULL;
                            }

                            // SEAGULL R2: the colour channel, 4 bytes per vertex
                            // (normColBytes - the layout the water attribute
                            // trace already established). The one vertex channel
                            // interpolation never touches; a per-tick flip here
                            // is an authored 20 Hz pose swap.
                            const size_t wr64MatrixColOffset = size_t(wr64MatrixVtxIndex) * 4;
                            const size_t wr64MatrixColByteCount = size_t(wr64MatrixVtxN) * 4;
                            if ((wr64MatrixColOffset + wr64MatrixColByteCount) <=
                                wr64MatrixData.normColBytes.size())
                            {
                                const uint8_t *wr64MatrixColBytes =
                                    &wr64MatrixData.normColBytes[wr64MatrixColOffset];
                                wr64MatrixColHash = 1469598103934665603ULL;
                                for (size_t b = 0; b < wr64MatrixColByteCount; b++) {
                                    wr64MatrixColHash =
                                        (wr64MatrixColHash ^ uint64_t(wr64MatrixColBytes[b]))
                                        * 1099511628211ULL;
                                }
                            }
                        }
                    }
                    if (wr64MatrixWorld < wr64MatrixData.worldTransformGroups.size()) {
                        const uint32_t wr64MatrixGroupIndex =
                            wr64MatrixData.worldTransformGroups[wr64MatrixWorld];
                        if (wr64MatrixGroupIndex < wr64MatrixData.transformGroups.size()) {
                            const TransformGroup &wr64MatrixTg =
                                wr64MatrixData.transformGroups[wr64MatrixGroupIndex];
                            wr64MatrixPosInterp = uint32_t(wr64MatrixTg.positionInterpolation);
                            wr64MatrixVtxInterp = uint32_t(wr64MatrixTg.vertexInterpolation);
                            wr64MatrixMatrixId = uint32_t(wr64MatrixTg.matrixId);
                        }
                    }

                    if (wr64MatrixWorld < wr64MatrixData.worldTransforms.size()) {
                        const hlslpp::float4x4 &wr64MatrixM =
                            wr64MatrixData.worldTransforms[wr64MatrixWorld];
                        const hlslpp::float3 wr64MatrixPos = wr64MatrixM[3].xyz;
                        wr64MatrixX = float(wr64MatrixPos.x);
                        wr64MatrixY = float(wr64MatrixPos.y);
                        wr64MatrixZ = float(wr64MatrixPos.z);

                        // Record basis-vector lengths to distinguish differently scaled instances
                        // of a shared model. Use the same implicit hlslpp conversion as matchTransform.
                        wr64MatrixSx = hlslpp::length(wr64MatrixM[0].xyz);
                        wr64MatrixSy = hlslpp::length(wr64MatrixM[1].xyz);
                        wr64MatrixSz = hlslpp::length(wr64MatrixM[2].xyz);

                        wr64MatrixM00 = float(wr64MatrixM[0].x);
                        wr64MatrixM01 = float(wr64MatrixM[0].y);
                        wr64MatrixM02 = float(wr64MatrixM[0].z);
                        wr64MatrixM10 = float(wr64MatrixM[1].x);
                        wr64MatrixM11 = float(wr64MatrixM[1].y);
                        wr64MatrixM12 = float(wr64MatrixM[1].z);
                        wr64MatrixM20 = float(wr64MatrixM[2].x);
                        wr64MatrixM21 = float(wr64MatrixM[2].y);
                        wr64MatrixM22 = float(wr64MatrixM[2].z);
                    }

                    // R6: the tile the GPU actually samples this output
                    // frame, next to the authored one - the ring spin's other
                    // channel, recorded where it can no longer be argued
                    // about. lerpRdpTiles is only filled on frames the tile
                    // processor ran; the valid flag keeps "not lerped" and
                    // "not available" from ever looking alike in the CSV.
                    float wr64MatrixTileUls = 0.0f, wr64MatrixTileUlt = 0.0f;
                    float wr64MatrixLerpTileUls = 0.0f, wr64MatrixLerpTileUlt = 0.0f;
                    uint32_t wr64MatrixTileLerpValid = 0;
                    {
                        const uint32_t wr64MatrixTileIndex = call.callDesc.tileIndex;
                        if ((call.callDesc.tileCount > 0) &&
                            (wr64MatrixTileIndex < wr64MatrixData.rdpTiles.size()))
                        {
                            wr64MatrixTileUls = wr64MatrixData.rdpTiles[wr64MatrixTileIndex].uls;
                            wr64MatrixTileUlt = wr64MatrixData.rdpTiles[wr64MatrixTileIndex].ult;
                        }
                        if ((call.callDesc.tileCount > 0) &&
                            (wr64MatrixTileIndex < wr64MatrixData.lerpRdpTiles.size()))
                        {
                            wr64MatrixLerpTileUls = wr64MatrixData.lerpRdpTiles[wr64MatrixTileIndex].uls;
                            wr64MatrixLerpTileUlt = wr64MatrixData.lerpRdpTiles[wr64MatrixTileIndex].ult;
                            wr64MatrixTileLerpValid = 1;
                        }
                    }
                    wr64MatrixSlotsRecord(p.curWorkload->submissionFrame,
                        wr64MatrixWorld, wr64MatrixSeg, wr64MatrixPhys, wr64HudTmemHash,
                        call.callDesc.triangleCount,
                        call.callDesc.colorCombiner.H, call.callDesc.colorCombiner.L,
                        call.callDesc.otherMode.H, call.callDesc.otherMode.L,
                        wr64MatrixX, wr64MatrixY, wr64MatrixZ,
                        wr64MatrixSx, wr64MatrixSy, wr64MatrixSz,
                        wr64MatrixM00, wr64MatrixM01, wr64MatrixM02,
                        wr64MatrixM10, wr64MatrixM11, wr64MatrixM12,
                        wr64MatrixM20, wr64MatrixM21, wr64MatrixM22,
                        wr64MatrixLx, wr64MatrixLy, wr64MatrixLz, wr64MatrixLerpOk,
                        wr64MatrixPosInterp, wr64MatrixVtxInterp, wr64MatrixMatrixId,
                        wr64MatrixLm00, wr64MatrixLm01, wr64MatrixLm02,
                        wr64MatrixLm10, wr64MatrixLm11, wr64MatrixLm12,
                        wr64MatrixLm20, wr64MatrixLm21, wr64MatrixLm22,
                        wr64MatrixVtxCount, wr64MatrixVtxHash,
                        wr64MatrixTileUls, wr64MatrixTileUlt,
                        wr64MatrixLerpTileUls, wr64MatrixLerpTileUlt,
                        wr64MatrixTileLerpValid, wr64MatrixColHash);
                }

                RenderViewport wr64ComposerViewportClip = viewportClip;
                if (wr64ComposerOverride.matched) {
                    wr64ComposerCallRect.ulx += wr64ComposerOverride.rectTranslateX + wr64ComposerOverride.rectLeft;
                    wr64ComposerCallRect.uly += wr64ComposerOverride.rectTranslateY + wr64ComposerOverride.rectTop;
                    wr64ComposerCallRect.lrx += wr64ComposerOverride.rectTranslateX + wr64ComposerOverride.rectRight;
                    wr64ComposerCallRect.lry += wr64ComposerOverride.rectTranslateY + wr64ComposerOverride.rectBottom;
                    wr64ComposerScissorRect.ulx += wr64ComposerOverride.scissorTranslateX + wr64ComposerOverride.scissorLeft;
                    wr64ComposerScissorRect.uly += wr64ComposerOverride.scissorTranslateY + wr64ComposerOverride.scissorTop;
                    wr64ComposerScissorRect.lrx += wr64ComposerOverride.scissorTranslateX + wr64ComposerOverride.scissorRight;
                    wr64ComposerScissorRect.lry += wr64ComposerOverride.scissorTranslateY + wr64ComposerOverride.scissorBottom;

                    // Marker calls maintain renderer bookkeeping and must not be suppressed.
                    if (wr64ComposerOverride.suppress &&
                        (call.callDesc.extendedType == DrawExtendedType::None)) {
                        globalCallIndex++;
                        continue;
                    }
                }
                if (wr64ApplyViewportNudge) {
                    const float viewportLeft = (wr64ViewportLeft / 4.0f) * p.resolutionScale.x;
                    const float viewportTop = (wr64ViewportTop / 4.0f) * p.resolutionScale.y;
                    const float viewportRight = (wr64ViewportRight / 4.0f) * p.resolutionScale.x;
                    const float viewportBottom = (wr64ViewportBottom / 4.0f) * p.resolutionScale.y;
                    wr64ComposerViewportClip.x += viewportLeft;
                    wr64ComposerViewportClip.y += viewportTop;
                    wr64ComposerViewportClip.width = std::max(0.0f,
                        wr64ComposerViewportClip.width + viewportRight - viewportLeft);
                    wr64ComposerViewportClip.height = std::max(0.0f,
                        wr64ComposerViewportClip.height + viewportBottom - viewportTop);
                }
                renderIndices.instanceIndex = call.callDesc.callIndex;
                renderIndices.faceIndicesStart = call.meshDesc.faceIndicesStart;
                renderIndices.rdpTileIndex = call.callDesc.tileIndex;
                renderIndices.rdpTileCount = call.callDesc.tileCount;
                const uint32_t wr64EffectiveHighlightColor =
                    (wr64ComposerOverride.matched && (wr64ComposerOverride.highlightColor != 0))
                    ? wr64ComposerOverride.highlightColor
                    : call.debuggerDesc.highlightColor;
                renderIndices.highlightColor = wr64EffectiveHighlightColor;
                renderIndicesVector.push_back(renderIndices);

                if (wr64FilterDiagnose) {
                    const auto &desc = call.callDesc;
                    const size_t index = desc.callIndex;
                    const DrawCallTile *tile = desc.tileCount != 0 && desc.tileIndex < drawData.callTiles.size()
                        ? &drawData.callTiles[desc.tileIndex] : nullptr;
                    const bool validTile = tile && tile->valid;
                    const interop::RDPTile *rdpTile = validTile && desc.tileIndex < drawData.rdpTiles.size()
                        ? &drawData.rdpTiles[desc.tileIndex] : nullptr;
                    const uint32_t arrayMode = index < drawData.rdpParams.size()
                        ? drawData.rdpParams[index].wr64UiFilter : UINT32_MAX;
                    const uint32_t arrayUpscale = index < drawData.renderParams.size()
                        ? drawData.renderParams[index].flags.upscale2D : UINT32_MAX;
                    const uint32_t appliedMode = desc.rdpParams.wr64UiFilter;
                    const uint64_t hash = validTile ? tile->tmemHashOrID : 0;
                    // GPUTiles are created after addFramebuffer; do not inspect
                    // that array here. The tile-created event joins by hash/frame.
                    ++wr64FilterPreparedCount;
                    wr64FilterAppliedCount += appliedMode != 0;
                    wr64FilterParameterMismatchCount += arrayMode != appliedMode ||
                        arrayUpscale != call.shaderDesc.flags.upscale2D;
                    const bool firstCandidate = (int32_t(proj.type) == 2 || int32_t(proj.type) == 3) &&
                        wr64FilterCandidateBudget.firstHash(hash);
                    const bool firstApplied = appliedMode != 0 && wr64FilterAppliedBudget.firstHash(hash);
                    if (firstCandidate || firstApplied) {
                        char details[1024];
                        std::snprintf(details, sizeof(details),
                            "frame=%llu selected=%u pair=%u projection=%u call=%zu render_index=%zu instance=%u proj=%d hash=%016llX applied=%u array_mode=%u upscale=%u array_upscale=%u tiles=%u valid=%u raw=%u copy=%u tile_shifts=%g,%g sample=%ux%u resolution_scale=%g,%g target=%ux%u modeH=%08X modeL=%08X",
                            (unsigned long long)p.curWorkload->submissionFrame, wr64FilterSelectedMode,
                            unsigned(p.fbPairIndex), pr, index, renderIndicesVector.size() - 1,
                            renderIndices.instanceIndex, int32_t(proj.type), (unsigned long long)hash,
                            appliedMode, arrayMode, unsigned(call.shaderDesc.flags.upscale2D), arrayUpscale,
                            desc.tileCount, unsigned(validTile), unsigned(validTile && tile->rawTMEM),
                            unsigned(validTile && tile->tileCopyUsed),
                            rdpTile ? double(rdpTile->shifts) : 0.0,
                            rdpTile ? double(rdpTile->shiftt) : 0.0,
                            validTile ? unsigned(tile->sampleWidth) : 0, validTile ? unsigned(tile->sampleHeight) : 0,
                            double(p.resolutionScale.x), double(p.resolutionScale.y),
                            p.targetWidth, p.targetHeight, desc.otherMode.H, desc.otherMode.L);
                        wr64UiFilterDiagnostic(firstApplied ? "prepared-applied" : "prepared-candidate", details);
                    }
                }

                uint32_t cycleType = call.callDesc.otherMode.cycleType();
                if (cycleType == G_CYC_FILL) {
                    instanceDrawCall.type = InstanceDrawCall::Type::FillRect;

                    auto &clearRect = instanceDrawCall.clearRect;
                    if (wr64EffectiveHighlightColor > 0) {
                        clearRect.color = toRenderColor(ColorConverter::RGBA32::toRGBAF(wr64EffectiveHighlightColor));
                    }
                    else {
                        if (p.fbStorage->colorTarget == nullptr) {
                            clearRect.depth = ColorConverter::D16::toF(call.callDesc.fillColor & 0xFFFF);
                        }
                        else if (fbPair.colorImage.siz == G_IM_SIZ_32b) {
                            clearRect.color = toRenderColor(ColorConverter::RGBA32::toRGBAF(call.callDesc.fillColor));
                        }
                        else {
                            clearRect.color = toRenderColor(ColorConverter::RGBA16::toRGBAF(call.callDesc.fillColor & 0xFFFF));
                        }
                    }

                    float invRatioScale = 1.0f / aspectRatioScale;
                    int32_t horizontalMisalignment = 0;

                    // WR64_FILL_WIDE_SPACE (EXP-018): the IPS-native game authors every fill
                    // in the wide 424x240 logical space, so fills must scale with the frame
                    // exactly like STRETCH-aspect texrects (WR64_RECT_WIDE_SPACE) instead of
                    // being aspect-corrected toward center. The stock condition below fails
                    // for inclusive full-frame fills like (0,0)-(423,239): raw lrx 423.75 is
                    // one fixed-point unit short of the 424 scissor edge, so the game's
                    // full-frame backdrop fill lands at [1,1273] of the 1280-wide target and
                    // the outer columns keep stale pixels from the previous screen (the menu
                    // edge strips). Under the gate, fills always map wide with no
                    // misalignment shift; convertFixedRect's inclusive right(true) then
                    // covers the full expanded width.
                    // ★ VALIDATED FIX, COMPILED IN. No environment variable.
                    constexpr bool wr64FillWideEnabled = true;
                    // EXP-019: snap inclusive-authored edge rects onto the frame edge.
                    const FixedRect wr64FillRect = wr64RectEdgeSnapEnabled() ?
                        wr64SnapRectToScissor(wr64ComposerCallRect, fbPair.scissorRect) : wr64ComposerCallRect;

                    if (wr64FillWideEnabled) {
                        invRatioScale = 1.0f;
                    }
                    // A rect that spans the whole width of the scissor.
                    else if ((wr64FillRect.ulx <= fbPair.scissorRect.ulx) && (wr64FillRect.lrx >= fbPair.scissorRect.lrx)) {
                        invRatioScale = 1.0f;
                    }
                    // A regular rectangle that should correct its misalignment.
                    else {
                        horizontalMisalignment = int32_t(p.horizontalMisalignment);
                    }

                    clearRect.rect = convertFixedRect(wr64FillRect, p.resolutionScale, p.fbWidth, invRatioScale, extOriginPercentage, horizontalMisalignment, call.callDesc.rectLeftOrigin, call.callDesc.rectRightOrigin);

                    // Full-width clears/washes continue to cover the target.
                    // Local UI fills stay registered with the centred menu
                    // plane, preserving the width of bars and cursor boxes.
                    if (wr64WideLayout.active() &&
                        (call.callDesc.rectLeftOrigin == G_EX_ORIGIN_NONE) &&
                        (call.callDesc.rectRightOrigin == G_EX_ORIGIN_NONE) &&
                        !((wr64FillRect.ulx <= fbPair.scissorRect.ulx) &&
                          (wr64FillRect.lrx >= fbPair.scissorRect.lrx))) {
                        clearRect.rect.left = int32_t(std::floor(wr64WideLayout.position(float(clearRect.rect.left))));
                        clearRect.rect.right = int32_t(std::ceil(wr64WideLayout.position(float(clearRect.rect.right))));
                    }

                    if (wr64EdgeTraceEnabled()) {
                        // R2: vertical edges included, so a black bar drawn as a
                        // fill cannot hide behind a full-width one that shares its
                        // left and right edges.
                        const uint64_t key = wr64EdgeHashN("fill",
                            call.callDesc.rect.ulx, call.callDesc.rect.uly, call.callDesc.rect.lrx, call.callDesc.rect.lry,
                            clearRect.rect.left, clearRect.rect.top, clearRect.rect.right, clearRect.rect.bottom,
                            long(invRatioScale * 100000.0f), long(horizontalMisalignment), long(call.callDesc.fillColor));
                        if (!wr64EdgeTraceSeen(key)) {
                            std::printf("[edge] FILL native=(%g,%g)-(%g,%g) out=(%d,%d)-(%d,%d) invRatio=%g mis=%d aspect=%u wideW=%g color=%08X\n",
                                call.callDesc.rect.ulx / 4.0, call.callDesc.rect.uly / 4.0, call.callDesc.rect.lrx / 4.0, call.callDesc.rect.lry / 4.0,
                                clearRect.rect.left, clearRect.rect.top, clearRect.rect.right, clearRect.rect.bottom,
                                double(invRatioScale), horizontalMisalignment, unsigned(call.callDesc.rectAspect), double(wideWidth), call.callDesc.fillColor);
                            { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
                        }
                    }
                }
                else if (call.callDesc.extendedType != DrawExtendedType::None) {
                    switch (call.callDesc.extendedType) {
                    case DrawExtendedType::VertexTestZ:
                        instanceDrawCall.type = InstanceDrawCall::Type::VertexTestZ;
                        instanceDrawCall.vertexTestZ.vertexIndex = call.callDesc.extendedData.vertexTestZ.vertexIndex;
                        instanceDrawCall.vertexTestZ.resolutionScale = p.resolutionScale;
                        instanceDrawCall.vertexTestZ.srcIndexStart = call.meshDesc.faceIndicesStart + 3;
                        instanceDrawCall.vertexTestZ.dstIndexStart = vertexTestZFaceIndicesStart;
                        instanceDrawCall.vertexTestZ.indexCount = 0;
                        vertexTestZCallIndex = int32_t(instanceDrawCallVector.size());
                        break;
                    case DrawExtendedType::EndVertexTestZ:
                        instanceDrawCall.type = InstanceDrawCall::Type::Unknown;
                        vertexTestZCallIndex = -1;
                        break;
                    default:
                        assert(false && "Unknown extended type.");
                        break;
                    }
                }
                else {
#               if RT_ENABLED
                    if (rtProj) {
                        instanceDrawCall.type = InstanceDrawCall::Type::Raytracing;

                        if (hitGroupVector.empty()) {
                            // TODO: Support specialized shaders.
                            //const RaytracingShaderPrograms &shaderPrograms = p.ubershadersOnly ? rtState->shaderProgramsMap.find(UberShaderHash)->second : rtState->getShaderPrograms(call.shaderDesc);
                            const RaytracingShaderPrograms &shaderPrograms = rtState->shaderProgramsMap.find(UberShaderHash)->second;
                            hitGroupVector.emplace_back(shaderPrograms.surface);
                            hitGroupVector.emplace_back(shaderPrograms.shadow);
                        }

                        auto &raytracing = instanceDrawCall.raytracing;
                        raytracing.hitGroupIndex = 0;
                        raytracing.cullDisable = !call.shaderDesc.flags.culling;

                        const interop::OtherMode &otherMode = call.callDesc.otherMode;
                        raytracing.queryMask = (otherMode.zCmp() || otherMode.zUpd()) ? DepthRayQueryMask : NoDepthRayQueryMask;
                        if (drawData.extraParams[call.callDesc.callIndex].shadowCatcherFactor > 0.0f) {
                            raytracing.queryMask |= ShadowCatcherRayQueryMask;
                        }

                        const RenderBottomLevelASMesh asMesh(indexRes->at(call.meshDesc.faceIndicesStart *IndexStride), worldPosRes->at(0), RenderFormat::R32_UINT, RenderFormat::R32G32B32_FLOAT, call.callDesc.triangleCount * 3, vertexCount, PosStride, false);
                        rtResources->addBottomLevelASMesh(asMesh);

                        if (false) { // TODO: call.shaderDesc.flags.smoothNormal
                            RSPSmoothNormalGenerationCB rspSmoothNormal;
                            rspSmoothNormal.indexStart = call.meshDesc.faceIndicesStart;
                            rspSmoothNormal.indexCount = call.callDesc.triangleCount * 3;
                            rspSmoothNormalVector.push_back(rspSmoothNormal);
                        }
                    }
                    else 
#               endif
                    {
                        triangles.shaderDesc = call.shaderDesc;

                        RasterShader *gpuShader = p.ubershadersOnly ? nullptr : p.rasterShaderCache->getGPUShader(call.shaderDesc);
                        if (gpuShader != nullptr) {
                            triangles.pipeline = gpuShader->pipeline.get();
                        }
                        else {
                            const bool copyMode = (call.shaderDesc.otherMode.cycleType() == G_CYC_COPY);
                            triangles.pipeline = rasterShaderUber->getPipeline(
                                !copyMode && call.shaderDesc.otherMode.zCmp() && (call.shaderDesc.otherMode.zMode() != ZMODE_DEC),
                                !copyMode && call.shaderDesc.otherMode.zUpd(),
                                (call.shaderDesc.otherMode.cvgDst() == CVG_DST_WRAP) || (call.shaderDesc.otherMode.cvgDst() == CVG_DST_SAVE));
                        }
                        
                        triangles.faceCount = call.callDesc.triangleCount;
                        triangles.vertexTestZ = (vertexTestZCallIndex >= 0);
                        triangles.postBlendDitherNoise = false;

                        float invRatioScale = 1.0f / aspectRatioScale;
                        float horizontalMisalignment = 0.0f;
                        switch (proj.type) {
                        case Projection::Type::Perspective:
                        case Projection::Type::Orthographic: {
                            instanceDrawCall.type = InstanceDrawCall::Type::IndexedTriangles;
                            triangles.indexStart = triangles.vertexTestZ ? vertexTestZFaceIndicesStart : call.meshDesc.faceIndicesStart;
                            invRatioScale = projInvRatioScale;
                            break;
                        }
                        case Projection::Type::Rectangle: {
                            instanceDrawCall.type = InstanceDrawCall::Type::RegularRect;
                            triangles.indexStart = wr64DolphinSunPresentation ?
                                call.callDesc.wr64DolphinSunVertexStart : call.meshDesc.rawVertexStart;

                            bool tileCopiesUsed = false;
                            for (uint32_t t = 0; (t < call.callDesc.tileCount) && !tileCopiesUsed; t++) {
                                tileCopiesUsed = drawData.callTiles[call.callDesc.tileIndex + t].tileCopyUsed;
                            }

                            // The call's scissor spans the whole width of the framebuffer pair scissor. The rect must not be using extended origins.
                            const bool regularOrigins = (call.callDesc.rectLeftOrigin == G_EX_ORIGIN_NONE) && (call.callDesc.rectRightOrigin == G_EX_ORIGIN_NONE);

                            // Use the same mapping for every authenticated message
                            // part, including its first frame before history exists.
                            // Stunt awards and other rectangles retain pixel rounding.
                            const bool wr64WarmupSubpixels = regularOrigins &&
                                call.callDesc.wr64HudMotion.kind == 1 && call.callDesc.wr64HudMotion.generation != 0;
                            const bool wr64EndingSubpixels = regularOrigins &&
                                call.callDesc.wr64HudMotion.kind == 3 && call.callDesc.wr64HudMotion.generation != 0;

                            // EXP-019: snap inclusive-authored edge rects onto the frame edge.
                            // Warm-up text has its own inset scissor: snapping its
                            // moving rectangle to the frame stretches the whole strip.
                            const FixedRect wr64DrawRect = (wr64RectEdgeSnapEnabled() && regularOrigins && !wr64WarmupSubpixels && !wr64EndingSubpixels) ?
                                wr64SnapRectToScissor(wr64ComposerCallRect, fbPair.scissorRect) : wr64ComposerCallRect;

                            const bool coversScissorWidth = regularOrigins && (wr64DrawRect.ulx <= fbPair.scissorRect.ulx) && (wr64DrawRect.lrx >= fbPair.scissorRect.lrx);
                            if ((tileCopiesUsed || coversScissorWidth || call.callDesc.rectAspect == G_EX_ASPECT_STRETCH) && (call.callDesc.rectAspect != G_EX_ASPECT_ADJUST)) {
                                invRatioScale = 1.0f;
                            }
                            else {
                                horizontalMisalignment = p.horizontalMisalignment;
                            }

                            RenderViewport viewportRect = convertViewportRect(wr64DrawRect, p.resolutionScale, p.fbWidth, invRatioScale, extOriginPercentage, horizontalMisalignment, call.callDesc.rectLeftOrigin, call.callDesc.rectRightOrigin, wr64WarmupSubpixels, wr64EndingSubpixels);
                            if (wr64WideLayout.active() && regularOrigins) {
                                // These five measured identities are sky effects.
                                // The other celestial-interpolation identities
                                // are Dolphin Park text and remain local UI.
                                wr64WideCelestialRectangle =
                                    (wr64HudTmemHash == Wr64CelestialSunGlow) ||
                                    (wr64HudTmemHash == Wr64CelestialSunDisk) ||
                                    (wr64HudTmemHash == Wr64CelestialSunFlare) ||
                                    (wr64HudTmemHash == Wr64CelestialSunDiskDP) ||
                                    (wr64HudTmemHash == Wr64CelestialTcStar);
                                if (wr64WideCelestialRectangle) {
                                    // Native producers already use the expanded
                                    // logical plane. Map their coordinates once,
                                    // including UV-cropped partial edge exits.
                                    const float left = std::round(wr64DrawRect.ulx * 0.25f * p.resolutionScale.y);
                                    const float right = std::round(wr64DrawRect.lrx * 0.25f * p.resolutionScale.y);
                                    viewportRect.x = left;
                                    viewportRect.width = right - left;
                                }
                                else if (!coversScissorWidth && !(wr64WideWatercraftSelect && pr == 0 &&
                                    wr64HudSampleW == 96 && (wr64HudSampleH == 5 || wr64HudSampleH == 1))) {
                                    // makeMainGlistMachine emits only its tiled
                                    // common backdrop before the first matrix
                                    // projection. Like the Shindou host path,
                                    // that first Rectangle projection fills the
                                    // target; its individual strips are not UI
                                    // glyphs just because each is narrower than
                                    // the complete framebuffer.
                                    wr64WideLocalRectangle = true;
                                    wr64WideHudAnchor = (wr64VerticalPauseHalf || wr64VerticalLapHalf || wr64VerticalSceneRect) ? 0 : wr64FinishHudCall ? 1 :
                                        wr64HudUltrawideAnchor(call.callDesc.rect, wr64HudTmemHash);
                                    // STRETCH is the IPS default, not evidence
                                    // that a glyph should become wider. A rect
                                    // already using ADJUST has retained its size.
                                    if (invRatioScale == 1.0f) {
                                        viewportRect.x = wr64HudLayout.position(viewportRect.x, wr64WideHudAnchor);
                                        viewportRect.width = wr64WideLayout.extent(viewportRect.width);
                                    }
                                    else {
                                        viewportRect.x += wr64WideHudAnchor * wr64HudLayout.halfExtension;
                                    }
                                }
                            }
                            if (wr64DolphinSunPresentation) {
                                // The native packet and the old snap/park paths
                                // above remain unchanged. This authenticated
                                // presentation uses one signed full quad and
                                // immutable full UVs; the GPU scissor crops it.
                                const float center = float(p.fbWidth) * 0.5f;
                                const float left = wr64DolphinSunRect[0];
                                const float top = wr64DolphinSunRect[1];
                                const float width = wr64DolphinSunRect[2] - left;
                                const float height = wr64DolphinSunRect[3] - top;
                                viewportRect.x = (center + (left - center) * invRatioScale) * p.resolutionScale.x;
                                viewportRect.width = width * invRatioScale * p.resolutionScale.x;
                                if (wr64WideLayout.active()) {
                                    viewportRect.x = left * p.resolutionScale.y;
                                    viewportRect.width = width * p.resolutionScale.y;
                                }
                                viewportRect.y = top * p.resolutionScale.y;
                                viewportRect.height = height * p.resolutionScale.y;
                            }
                            triangles.screenScale = { viewportRect.width / framebuffer.viewport.width, viewportRect.height / framebuffer.viewport.height };
                            triangles.screenOffset.x = halfPixelOffset.x + ((viewportRect.x + viewportRect.width / 2.0f) - halfViewportSize.x) / halfViewportSize.x;
                            triangles.screenOffset.y = halfPixelOffset.y + (halfViewportSize.y - (viewportRect.y + viewportRect.height / 2.0f)) / halfViewportSize.y;

                            if (wr64EdgeTraceEnabled()) {
                                const bool nearLeftEdge = viewportRect.x < 12.0f;
                                const bool nearRightEdge = (viewportRect.x + viewportRect.width) > (wideWidth - 12.0f);
                                if (nearLeftEdge || nearRightEdge) {
                                    const uint64_t key = wr64EdgeHash("rect", call.callDesc.rect.ulx, call.callDesc.rect.lrx, long(viewportRect.x), long(viewportRect.width), long(invRatioScale * 100000.0f), long(call.callDesc.rectAspect));
                                    if (!wr64EdgeTraceSeen(key)) {
                                        std::printf("[edge] TEXRECT native=(%g,%g)-(%g,%g) out=(%g,%g %gx%g) invRatio=%g mis=%g aspect=%u tileCopies=%d coversW=%d wideW=%g\n",
                                            call.callDesc.rect.ulx / 4.0, call.callDesc.rect.uly / 4.0, call.callDesc.rect.lrx / 4.0, call.callDesc.rect.lry / 4.0,
                                            double(viewportRect.x), double(viewportRect.y), double(viewportRect.width), double(viewportRect.height),
                                            double(invRatioScale), double(horizontalMisalignment), unsigned(call.callDesc.rectAspect),
                                            tileCopiesUsed ? 1 : 0, coversScissorWidth ? 1 : 0, double(wideWidth));
                                        { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
                                    }
                                }
                            }

                            if (p.postBlendNoise) {
                                // Indicate if post blend dither noise should be applied.
                                bool rgbDitherNoise = (call.shaderDesc.otherMode.rgbDither() == G_CD_NOISE);
                                triangles.postBlendDitherNoise = rgbDitherNoise && !call.shaderDesc.otherMode.zCmp() && !call.shaderDesc.otherMode.zUpd();
                                triangles.postBlendDitherNoiseNegative = p.postBlendNoiseNegative;
                            }

                            break;
                        }
                        case Projection::Type::Triangle: {
                            instanceDrawCall.type = InstanceDrawCall::Type::RawTriangles;
                            triangles.indexStart = call.meshDesc.rawVertexStart;
                            break;
                        }
                        case Projection::Type::None:
                        default:
                            break;
                        }

                        // EXP-019: snap inclusive-authored call scissors onto the frame edge --
                        // a (0,0)-(423,239) scissor otherwise clips EVERY layer under it
                        // (triangles included) one native pixel short of the right/bottom edges.
                        const bool wr64RegularScissorOrigins = (call.callDesc.scissorLeftOrigin == G_EX_ORIGIN_NONE) && (call.callDesc.scissorRightOrigin == G_EX_ORIGIN_NONE);
                        const FixedRect wr64CallScissorRect = (wr64RectEdgeSnapEnabled() && wr64RegularScissorOrigins) ?
                            wr64SnapRectToScissor(wr64ComposerScissorRect, fbPair.scissorRect) : wr64ComposerScissorRect;
                        triangles.scissor = convertFixedRect(wr64CallScissorRect, p.resolutionScale, p.fbWidth, invRatioScale, extOriginPercentage, int32_t(horizontalMisalignment), call.callDesc.scissorLeftOrigin, call.callDesc.scissorRightOrigin);
                        if (wr64WideCelestialRectangle) {
                            triangles.scissor.left = 0;
                            triangles.scissor.right = int32_t(wideWidth);
                        }
                        else if (wr64WideLocalRectangle && wr64RegularScissorOrigins) {
                            if ((wr64CallScissorRect.ulx <= fbPair.scissorRect.ulx) &&
                                (wr64CallScissorRect.lrx >= fbPair.scissorRect.lrx)) {
                                // Edge HUD may occupy either extension; retain
                                // its native vertical clip, including2P halves.
                                triangles.scissor.left = 0;
                                triangles.scissor.right = int32_t(wideWidth);
                            }
                            else if (invRatioScale == 1.0f) {
                                triangles.scissor.left = int32_t(std::floor(wr64HudLayout.position(float(triangles.scissor.left), wr64WideHudAnchor)));
                                triangles.scissor.right = int32_t(std::ceil(wr64HudLayout.position(float(triangles.scissor.right), wr64WideHudAnchor)));
                            }
                            else {
                                const int32_t shift = int32_t(std::round(wr64WideHudAnchor * wr64HudLayout.halfExtension));
                                triangles.scissor.left += shift;
                                triangles.scissor.right += shift;
                            }
                        }

                        bool usesViewport = (proj.type == Projection::Type::Perspective) || (proj.type == Projection::Type::Orthographic);
                        if (usesViewport) {
                            triangles.scissor = viewportScissorIntersection(wr64ComposerViewportClip, triangles.scissor);
                        }

                        if (wr64EdgeTraceEnabled() && usesViewport) {
                            const uint64_t key = wr64EdgeHash("tri", call.callDesc.scissorRect.ulx, call.callDesc.scissorRect.lrx, triangles.scissor.left, triangles.scissor.right, long(triangles.screenScale.x * 100000.0f), long(call.callDesc.triangleCount));
                            if (!wr64EdgeTraceSeen(key)) {
                                std::printf("[edge] TRI type=%d tris=%u nativeScissor=(%g,%g)-(%g,%g) outScissor=(%d,%d)-(%d,%d) screenScaleX=%g screenOffX=%g clip=(%g,%g %gx%g) cyc=%u zUpd=%d wideW=%g\n",
                                    int(proj.type), unsigned(call.callDesc.triangleCount),
                                    call.callDesc.scissorRect.ulx / 4.0, call.callDesc.scissorRect.uly / 4.0, call.callDesc.scissorRect.lrx / 4.0, call.callDesc.scissorRect.lry / 4.0,
                                    triangles.scissor.left, triangles.scissor.top, triangles.scissor.right, triangles.scissor.bottom,
                                    double(triangles.screenScale.x), double(triangles.screenOffset.x),
                                    double(viewportClip.x), double(viewportClip.y), double(viewportClip.width), double(viewportClip.height),
                                    unsigned(cycleType), call.shaderDesc.otherMode.zUpd() ? 1 : 0, double(wideWidth));
                                { if (WR64_DIAGNOSTIC_ENABLED) std::fflush(stdout); }
                            }
                        }
                        
                        if (triangles.vertexTestZ && usesViewport) {
                            instanceDrawCallVector[vertexTestZCallIndex].vertexTestZ.indexCount += call.callDesc.triangleCount * 3;
                            vertexTestZFaceIndicesStart += call.callDesc.triangleCount * 3;
                        }
                    }
                }

                // Determine to use the draw call either in the RT scene or the raster scene.
                const uint32_t instanceIndex = static_cast<uint32_t>(instanceDrawCallVector.size());
#           if RT_ENABLED
                bool rtCall = instanceDrawCall.type == InstanceDrawCall::Type::Raytracing;
                if (rtCall) {
                    // If the current scene is not compatible, we submit it before the raster scene.
                    if (!rtProjCompatible) {
                        checkRtScene(rtScene);
                    }

                    const bool addedRasterScene = checkRasterScene(rasterScene);
                    if (rtScene.instanceIndices.empty()) {
                        float projRatioScale = 1.0f / aspectRatioScale;
                        float invRatioScale = 1.0f / aspectRatioScale;
                        const bool coversScissorWidth = (proj.scissorRect.ulx <= fbPair.scissorRect.ulx) && (proj.scissorRect.lrx >= fbPair.scissorRect.lrx);
                        if (coversScissorWidth) {
                            invRatioScale = 1.0f;
                        }
                        else {
                            projRatioScale = 1.0f;
                        }

                        rtScene.curViewMatrix = drawData.modViewTransforms[proj.transformsIndex];
                        rtScene.curProjMatrix = drawData.modProjTransforms[proj.transformsIndex];
                        rtScene.prevViewMatrix = drawData.prevViewTransforms[proj.transformsIndex];
                        rtScene.prevProjMatrix = drawData.prevProjTransforms[proj.transformsIndex];

                        const auto &viewport = drawData.rspViewports[proj.transformsIndex];
                        rtScene.viewport = convertViewportRect(viewport.rect(viewportClipRatios), p.resolutionScale, p.fbWidth, invRatioScale, extOriginPercentage, 0.0f, G_EX_ORIGIN_NONE, G_EX_ORIGIN_NONE);
                        rtScene.scissor = convertFixedRect(proj.scissorRect, p.resolutionScale, p.fbWidth, invRatioScale, extOriginPercentage, 0, G_EX_ORIGIN_NONE, G_EX_ORIGIN_NONE);

                        rtScene.presetScene = p.presetScene;
                        rtScene.screenWidth = lround(static_cast<float>(p.fbWidth) * p.resolutionScale.x);
                        rtScene.screenHeight = lround(static_cast<float>(p.fbHeight) * p.resolutionScale.y);

                        if (proj.pointLightCount > 0) {
                            rtScene.pointLights = proj.pointLights.data();
                            rtScene.lightCount = proj.pointLightCount;
                        }
                        else {
                            rtScene.pointLights = nullptr;
                            rtScene.lightCount = 0;
                        }
                    }
                    else if (rtProjCompatible && addedRasterScene) {
                        targetDrawCall.sceneIndices.pop_back();
                        const uint32_t rasterSceneIndex = static_cast<uint32_t>(targetDrawCall.rasterScenes.size() - 1);
                        const auto &rasterScene = targetDrawCall.rasterScenes[rasterSceneIndex];
                        rtScene.interleavedRasters.push_back({ rasterSceneIndex, rasterScene.instanceIndices.back(), 0, 0 });
                    }

                    rtScene.instanceIndices.push_back(instanceIndex);
                }
                else 
#           endif
                {
                    rasterScene.instanceIndices.push_back(instanceIndex);
                }

                instanceDrawCallVector.push_back(instanceDrawCall);

                // Once world drawing reaches the native screen overlay, keep
                // every later HUD glyph/lens flare sharp. Unexpected world
                // interleaving rejects the trial for this frame.
                const uint32_t wr64RTCallOwner = wr64RTTwoPlayer ? wr64RaceView(proj, call.callDesc.scissorRect) : 1u;
                rt = &wr64RTViews[wr64RTCallOwner ? wr64RTCallOwner - 1 : 0];
                const bool wr64RTCallScope = wr64RTCallOwner != 0 && rt->framebuffer == framebufferCount - 1;
                if (rt->framebuffer == framebufferCount - 1 && !wr64MotionActors.empty()) {
                    if (proj.type != Projection::Type::Perspective && wr64MotionBoundary == UINT32_MAX)
                        wr64MotionBoundary = instanceIndex;
                    else if (proj.type == Projection::Type::Perspective && wr64MotionBoundary != UINT32_MAX)
                        wr64MotionOrderRejected = true;
                }

                const bool wr64RTSkyCall = wr64RTSkySignature(call.callDesc.triangleCount,
                    call.callDesc.colorCombiner.L, call.callDesc.colorCombiner.H,
                    call.callDesc.otherMode.L, call.callDesc.otherMode.H);
                const auto wr64RTMaterial = wr64RTClassifyMaterial(call.callDesc.otherMode.L);
                const auto &wr64BackdropDesc = call.callDesc;
                const bool wr64RTBackdropCall = wr64RTBackdropSignature(wr64BackdropDesc.triangleCount,
                    wr64BackdropDesc.colorCombiner.L, wr64BackdropDesc.colorCombiner.H,
                    wr64BackdropDesc.otherMode.L, wr64BackdropDesc.otherMode.H);
                if (wr64RTCallScope && rt->projection != UINT32_MAX &&
                    (p.curWorkload->wr64RtSkyReflectionScope || rt->rasterSky) &&
                    proj.type == Projection::Type::Perspective && (wr64RTSkyCall || wr64RTBackdropCall)) {
                    wr64CaptureSky(call, proj, instanceIndex,
                        !wr64ComposerOverride.matched && !wr64ApplyViewportNudge && !triangles.vertexTestZ,
                        wr64RTBackdropCall);
                }

                if (wr64RTCallScope && rt->projection != UINT32_MAX &&
                    instanceDrawCall.type == InstanceDrawCall::Type::IndexedTriangles &&
                    proj.type == Projection::Type::Perspective && !proj.wr64MenuModelPreview &&
                    (!wr64RTMenuScope || wr64RTSamePreviewDomain(
                        wr64PreviewDomain(proj, call.callDesc.scissorRect), wr64RTWaterDomain)) &&
                    proj.transformsIndex < drawData.modViewTransforms.size() &&
                    matrixDifference(drawData.modViewTransforms[proj.transformsIndex],
                        drawData.modViewTransforms[rt->projection]) < 1e-4f) {
                    if (wr64RTDrawViews.size() <= instanceIndex) wr64RTDrawViews.resize(size_t(instanceIndex) + 1, 0);
                    wr64RTDrawViews[instanceIndex] = uint8_t(wr64RTCallOwner);
                    if ((p.curWorkload->wr64RtShadowScope || rt->rasterShadows) && p.curWorkload->wr64RtShadowLight.valid &&
                        !wr64ComposerOverride.matched && !wr64ApplyViewportNudge && !triangles.vertexTestZ) {
                        const uint32_t racer = wr64NativeWaterShadowRacer(call);
                        if (racer < 4) {
                            // Calls are visited in increasing instance-index order.
                            rt->nativeShadowDraws.push_back({ instanceIndex, 1u << racer });
                        }
                    }
                    if (wr64IsWater(call)) {
                        rt->waterDraws.push_back(instanceIndex);
                        const auto first = drawData.faceIndices.begin() + call.meshDesc.faceIndicesStart;
                        rt->waterIndices.insert(rt->waterIndices.end(), first,
                            first + call.callDesc.triangleCount * 3);
                    }
                    else if ((rt->traceReflections || rt->rasterShadows || rt->rasterReflections) && !wr64RTSkyCall && !wr64HasWater(call) &&
                        (wr64RTMaterial != Wr64RTMaterial::Rejected || wr64TwilightBeam(call))) {
                        bool tileCopy = false;
                        for (uint32_t ti = 0; ti < call.callDesc.tileCount; ++ti) {
                            const uint32_t t = call.callDesc.tileIndex + ti;
                            if (t >= drawData.callTiles.size() || drawData.callTiles[t].tileCopyUsed) { tileCopy = true; break; }
                        }
                        const bool beam = wr64TwilightBeam(call);
                        if (!tileCopy && (!beam || (!wr64ComposerOverride.matched && !wr64ApplyViewportNudge &&
                            !wr64HasManualViewportOverride && !triangles.vertexTestZ))) {
                            // Opaque admission is retained; native coverage/threshold cutouts
                            // now enter with an explicit material test on each ray candidate.
                            // Native light columns keep their alpha and never become casters.
                            const auto &desc = call.callDesc;
                            const char *stateFamily = wr64MatrixStateFamily(desc.triangleCount,
                                desc.colorCombiner.H, desc.colorCombiner.L,
                                desc.otherMode.H, desc.otherMode.L);
                            const bool wrongWayArrow = stateFamily &&
                                std::strcmp(stateFamily, "wrongway_arrow") == 0;
                            const bool trafficLights = wr64GantryIdentityClaims(wr64HudTmemHash,
                                desc.triangleCount, desc.colorCombiner.H, desc.colorCombiner.L,
                                desc.otherMode.H, desc.otherMode.L);
                            const bool nextMark = wr64NextMark(call);
                            const bool buoyLetter = wr64BuoyLetter(call);
                            rt->arrowShadowExclusions += nextMark ? 1 : 0;
                            rt->letterShadowExclusions += buoyLetter ? 1 : 0;
                            const bool shadowCaster = !wrongWayArrow && !trafficLights &&
                                !nextMark && !buoyLetter && !beam && desc.otherMode.zMode() != ZMODE_DEC &&
                                !wr64ComposerOverride.matched && !wr64ApplyViewportNudge &&
                                !wr64HasManualViewportOverride && !triangles.vertexTestZ;
                            const uint32_t actorMask = shadowCaster ? wr64ArticulatedShadowCasterMask(call) : 0u;
                            const uint32_t geometryFlags = (shadowCaster ? 1u : 0u) |
                                (wr64RTMaterial == Wr64RTMaterial::Cutout ? 2u : 0u) | (beam ? 4u : 0u) |
                                (actorMask ? 16u : 0u);
                            rt->geometry.push_back({call.meshDesc.faceIndicesStart,
                                desc.triangleCount * 3, instanceIndex, geometryFlags});
                            if ((rt->rasterShadows || rt->rasterReflections) && shadowCaster) {
                                const uint64_t first = call.meshDesc.faceIndicesStart;
                                const uint64_t count = uint64_t(desc.triangleCount) * 3;
                                if (count && first + count <= rt->indexCount && first + count <= drawData.faceIndices.size() &&
                                    std::all_of(drawData.faceIndices.begin() + first, drawData.faceIndices.begin() + first + count,
                                        [&](uint32_t vertex) { return vertex < rt->vertexCount; })) {
                                    if (rt->rasterShadows) rt->rasterShadowCasters.push_back(rt->geometry.back());
                                    if (rt->rasterReflections) rt->rasterReflectors.push_back(rt->geometry.back());
                                }
                            }
                            if (actorMask) {
                                rt->racerShadowCasters |= actorMask;
                                ++rt->params.sceneOptions.y;
                                rt->params.sceneOptions.z |= actorMask;
                                wr64ExpandActorShadowBounds(call, actorMask);
                                const char *blur = std::getenv("WR64_OBJECT_MOTION_BLUR_EXPERIMENT");
                                const bool blurEnabled = wr64RTDevelopmentEffectsAllowed() &&
                                    blur && blur[0] == '1' && blur[1] == '\0';
                                const uint32_t view = proj.transformsIndex;
                                if (blurEnabled && !wr64RTTwoPlayer && !wr64RTMenuScope && !p.curWorkload->paused &&
                                    !p.curWorkload->wr64PauseOwner && !p.curWorkload->wr64VerticalSplit &&
                                    desc.otherMode.zCmp() && desc.otherMode.zUpd() &&
                                    view < drawData.prevViewProjTransforms.size() && view < drawData.rspViewports.size()) {
                                    wr64MotionDrawParams.resize(instanceDrawCallVector.size());
                                    auto &motion = wr64MotionDrawParams[instanceIndex];
                                    const auto &viewport = drawData.rspViewports[view];
                                    motion.previousViewProjection = drawData.prevViewProjTransforms[view];
                                    motion.viewportScale = hlslpp::float4(viewport.scale, 1.0f);
                                    motion.viewportTranslate = hlslpp::float4(viewport.translate, float(actorMask));
                                    wr64MotionActors.push_back(instanceIndex);
                                }
                            }
                            if (beam) ++rt->params.sceneOptions.x;
                            if (shadowCaster && (rt->params.shadowOptions.x == 1.0f || rt->params.aoOptions.x == 1.0f || rt->rasterShadows)) {
                                const bool staticShore = wr64StaticShoreReceiver(call);
                                const bool directionalReceiver = rt->params.shadowOptions.x == 1.0f;
                                if (directionalReceiver || staticShore || rt->params.aoOptions.x == 1.0f) {
                                    // Reuse the same physical-caster admission and presented geometry
                                    // for receiving shadows, including actors and transformed objects.
                                    // Source-face rejection preserves shadows from other faces of a draw.
                                    rt->shoreDraws.push_back(instanceIndex);
                                    if (!directionalReceiver && !staticShore) rt->aoOnlyDraws.push_back(instanceIndex);
                                    if (staticShore && rt->traceReflections) wr64AppendSunnyFenceProxy(call, instanceIndex);
                                }
                            }
                        }
                    }
                }

                // Keep native six-triangle identity and reflection capture
                // above unchanged. Only the actual raster index range includes
                // the authenticated annulus; its native prefix is identical.
                if (wr64RTSkyCall && p.wr64RtPresentation &&
                    proj.type == Projection::Type::Perspective &&
                    instanceDrawCallVector.back().type == InstanceDrawCall::Type::IndexedTriangles &&
                    !triangles.vertexTestZ && !wr64ComposerOverride.matched && !wr64ApplyViewportNudge &&
                    wr64CloudCoveragePresentationValid(drawData, call, proj.transformsIndex)) {
                    auto &stored = instanceDrawCallVector.back().triangles;
                    stored.indexStart = call.wr64CloudCoverage.faceIndicesStart;
                    stored.faceCount = call.wr64CloudCoverage.faceCount;
                }

                // Composer viewport edges adjust only the matched
                // call's stored transform. Coupled with the per-call viewport
                // clip above, this exposes the actual geometry/clip boundary
                // without changing the projection shared by sibling calls.
                if (wr64ApplyViewportNudge &&
                    (instanceDrawCallVector.back().type == InstanceDrawCall::Type::IndexedTriangles)) {
                    auto &storedTriangles = instanceDrawCallVector.back().triangles;
                    const float wr64OffsetScaleX = (wr64WideLayout.active() &&
                        !wr64OptionsBackgroundCall && !wr64WatercraftEdgeCall)
                        ? float(p.resolutionScale.y) : float(p.resolutionScale.x);
                    const float left = (wr64ViewportLeft / 4.0f) * wr64OffsetScaleX;
                    const float top = (wr64ViewportTop / 4.0f) * p.resolutionScale.y;
                    const float right = (wr64ViewportRight / 4.0f) * wr64OffsetScaleX;
                    const float bottom = (wr64ViewportBottom / 4.0f) * p.resolutionScale.y;
                    if (framebuffer.viewport.width > 0.0f) {
                        storedTriangles.screenScale.x += (right - left) / framebuffer.viewport.width;
                        storedTriangles.screenOffset.x += (right + left) / framebuffer.viewport.width;
                    }
                    if (framebuffer.viewport.height > 0.0f) {
                        storedTriangles.screenScale.y += (bottom - top) / framebuffer.viewport.height;
                        storedTriangles.screenOffset.y -= (bottom + top) / framebuffer.viewport.height;
                    }
                }

                if (wr64WideLayout.active() &&
                    (instanceDrawCallVector.back().type == InstanceDrawCall::Type::IndexedTriangles)) {
                    auto &storedTriangles = instanceDrawCallVector.back().triangles;
                    if (wr64BannerAnchorCall) {
                        // The whole banner follows the measured POWER widget.
                        storedTriangles.screenOffset.x += 2.0f * wr64HudLayout.halfExtension / wideWidth;
                        storedTriangles.scissor.left = 0;
                        storedTriangles.scissor.right = int32_t(wideWidth);
                    }
                    else if (wr64OptionsBackgroundCall || (wr64WatercraftEdgeCall && !wr64WideWatercraftSelect)) {
                        // These existing measured background identities are
                        // coverage surfaces, unlike sibling menu glyphs/craft.
                        // Undo the extra projection squeeze for this call only.
                        const float expansion = 1.0f / wr64WideLayout.inverseExpansion;
                        storedTriangles.screenScale.x *= expansion;
                        storedTriangles.screenOffset.x = halfPixelOffset.x +
                            (storedTriangles.screenOffset.x - halfPixelOffset.x) * expansion;
                        storedTriangles.scissor.left = 0;
                        storedTriangles.scissor.right = int32_t(wideWidth);
                    }
                }

                if (wr64WideLayout.active() &&
                    instanceDrawCallVector.back().type == InstanceDrawCall::Type::IndexedTriangles &&
                    wr64UsaShutterCall(drawData, call)) {
                    auto &stored = instanceDrawCallVector.back().triangles;
                    const auto mapping = wr64UsaShutterMapping(stored.screenScale.x,
                        stored.screenOffset.x, halfPixelOffset.x, 1.0f / wr64WideLayout.inverseExpansion);
                    stored.screenScale.x = mapping.scale;
                    stored.screenOffset.x = mapping.offset;
                    stored.scissor.left = 0;
                    stored.scissor.right = int32_t(wideWidth);
                }

                // WR64_OPTIONS_BACKGROUND_EDGE_FIX: Composer capture 1 identified the
                // Options navy background as a single orthographic two-triangle draw.
                // Its authored 424x240 terminal edges can leave the last rendered pixel
                // uncovered after the 424x239 framebuffer/viewport conversion. Expand
                // only this proven call's right and bottom edges by one rendered pixel.
                // The offset compensation keeps the left and top edges bit-identical.
                static const bool wr64OptionsBackgroundEdgeFix = []() {
                    const char *value = std::getenv("WR64_OPTIONS_BACKGROUND_EDGE_FIX");
                    return (value != nullptr) && (value[0] == '1') && (value[1] == '\0');
                }();
                constexpr uint64_t WR64OptionsBackgroundSignature = 0xF071DB66857C923FULL;
                if (wr64OptionsBackgroundEdgeFix &&
                    (wr64ComposerOverride.signature == WR64OptionsBackgroundSignature) &&
                    (instanceDrawCallVector.back().type == InstanceDrawCall::Type::IndexedTriangles)) {
                    auto &storedTriangles = instanceDrawCallVector.back().triangles;
                    const float dx = (framebuffer.viewport.width > 0.0f) ?
                        (1.0f / framebuffer.viewport.width) : 0.0f;
                    const float dy = (framebuffer.viewport.height > 0.0f) ?
                        (1.0f / framebuffer.viewport.height) : 0.0f;
                    storedTriangles.screenScale.x += dx;
                    storedTriangles.screenOffset.x += dx;
                    storedTriangles.screenScale.y += dy;
                    storedTriangles.screenOffset.y -= dy;
                    storedTriangles.scissor.right += 1;
                    storedTriangles.scissor.bottom += 1;
                }
                // Observe the final stored transform and GPU target, after every
                // existing correction. Neither this trace nor its native inventory
                // changes sun identity, pairing, coordinates, scissors or drawing.
                // Vertical split is a final presentation transform. Native
                // matrices, vertex data, camera culling and frame matching
                // retain their original horizontal identities.
                if (wr64Vertical.active && call.callDesc.extendedType == DrawExtendedType::None) {
                    auto &storedCall = instanceDrawCallVector.back();
                    const bool raster = storedCall.type == InstanceDrawCall::Type::IndexedTriangles ||
                        storedCall.type == InstanceDrawCall::Type::RegularRect ||
                        storedCall.type == InstanceDrawCall::Type::RawTriangles;
                    const bool colorFill = storedCall.type == InstanceDrawCall::Type::FillRect &&
                        p.fbStorage->colorTarget != nullptr;
                    int half = 0;
                    bool worldClip = false;
                    Wr64VerticalAffine mapping;
                    const auto &sourceRect = call.callDesc.rect;
                    const auto &sourceScissor = call.callDesc.scissorRect;
                    const int scissorHalf = wr64VerticalHalfScissor(sourceScissor.ulx,
                        sourceScissor.uly, sourceScissor.lrx, sourceScissor.lry);
                    const uint32_t worldIndex = call.callDesc.minWorldMatrix;
                    const bool hasWorld = worldIndex != 0xFFFF && worldIndex < drawData.worldTransforms.size();
                    float nativeWorldY = -1.0f;
                    if (hasWorld) {
                        const hlslpp::float4x4 &world = drawData.worldTransforms[worldIndex];
                        nativeWorldY = float(world[3].y);
                    }
                    const uint32_t worldSegment = hasWorld && worldIndex < drawData.worldTransformSegmentedAddresses.size()
                        ? drawData.worldTransformSegmentedAddresses[worldIndex] : 0;

                    // Shared font projection: the native scope brackets only
                    // pause choices and both cursor cubes, after the dimmer.
                    if (wr64VerticalPauseHalf != 0) {
                        half = wr64VerticalPauseHalf;
                        mapping = wr64VerticalHud(wr64Vertical, half, 0, 0);
                        if (wr64VerticalPauseCenterY >= 0.0f) {
                            mapping.dy = commonHeight * 0.5f - mapping.scale * wr64VerticalPauseCenterY;
                        }
                    }
                    else if (wr64VerticalLapHalf != 0) {
                        // LAP/FINAL LAP are shaded indexed font vertices under
                        // the shared HUD projection, not rectangle widgets or
                        // GWord models. The native bracket owns the full phrase.
                        half = wr64VerticalLapHalf;
                        mapping = wr64VerticalAnnouncement(wr64Vertical, half,
                            wr64TwoPHudDy4(half) * 0.25f);
                    }
                    else if (wr64BannerAnchorCall && nativeWorldY >= 0.0f && nativeWorldY <= 240.0f) {
                        half = nativeWorldY < 120.0f ? 1 : 2;
                        mapping = wr64VerticalHud(wr64Vertical, half, 1, 1);
                    }
                    else if (raster && proj.type == Projection::Type::Rectangle &&
                        wr64TwoPHudIsTrackMarker(sourceRect.ulx, sourceRect.uly,
                            sourceRect.lrx, sourceRect.lry, wr64HudTmemHash)) {
                        half = scissorHalf ? scissorHalf :
                            ((sourceRect.uly + sourceRect.lry) < 240 * 4 ? 1 : 2);
                        const auto &stored = storedCall.triangles;
                        const float centerX = wideWidth * 0.5f *
                            (1.0f + stored.screenOffset.x - halfPixelOffset.x);
                        const float centerY = commonHeight * 0.5f *
                            (1.0f - stored.screenOffset.y + halfPixelOffset.y);
                        mapping = wr64VerticalMarker(wr64Vertical, half, centerX, centerY);
                    }
                    else if (raster && proj.type == Projection::Type::Orthographic &&
                        wr64HudTmemHash == 0x30B9BE1D3299DE00ULL && hasWorld &&
                        proj.transformsIndex < drawData.modViewProjTransforms.size()) {
                        // Use the same interpolated transform as this icon's
                        // vertices, not a guessed native bounding rectangle.
                        const hlslpp::float4x4 &wm = worldIndex < drawData.lerpWorldTransforms.size()
                            ? drawData.lerpWorldTransforms[worldIndex] : drawData.worldTransforms[worldIndex];
                        const hlslpp::float4x4 &viewProjection = drawData.modViewProjTransforms[proj.transformsIndex];
                        const hlslpp::float4 point = hlslpp::mul(wm[3], viewProjection);
                        const float w = float(point.w);
                        if (std::isfinite(w) && std::abs(w) > 0.000001f) {
                            const auto &vp = drawData.rspViewports[proj.transformsIndex];
                            const float x = float(point.x) / w * vp.scale.x + vp.translate.x;
                            const float y = -float(point.y) / w * vp.scale.y + vp.translate.y;
                            const auto &stored = storedCall.triangles;
                            const float centerX = wideWidth * 0.5f * (1.0f +
                                (x * 2.0f / float(fbParams.resolution.x) - 1.0f) * stored.screenScale.x +
                                stored.screenOffset.x - halfPixelOffset.x);
                            const float centerY = commonHeight * 0.5f * (1.0f -
                                (1.0f - y * 2.0f / float(fbParams.resolution.y)) * stored.screenScale.y -
                                stored.screenOffset.y + halfPixelOffset.y);
                            half = scissorHalf ? scissorHalf : (y < 120.0f ? 1 : 2);
                            mapping = wr64VerticalMarker(wr64Vertical, half, centerX, centerY);
                        }
                    }
                    else if (wr64VerticalViewportRole == Wr64VerticalViewport::Signal ||
                        wr64VerticalViewportRole == Wr64VerticalViewport::Indicator) {
                        half = wr64VerticalViewportHalf;
                        const auto &vp = drawData.rspViewports[proj.transformsIndex];
                        mapping = wr64VerticalAuxiliary(wr64Vertical, wr64VerticalViewportRole,
                            half, vp.translate.y);
                    }
                    else if (proj.type == Projection::Type::Rectangle) {
                        int32_t dx = 0, dy = 0;
                        if (scissorHalf == 0 && wr64TwoPHudOffset(sourceRect, wr64HudTmemHash, dx, dy)) {
                            half = wr64TwoPHudHalfForRect(sourceRect);
                            const bool gap = wr64TwoPHudIsGapTimer(sourceRect.ulx, sourceRect.uly,
                                sourceRect.lrx, sourceRect.lry, half);
                            const int anchorX = gap ? 0 : (dx > 0) - (dx < 0);
                            const int localTop = sourceRect.uly / 4 - (half == 2 ? 110 : 0);
                            const int anchorY = gap ? 0 : (localTop >= 96 ? 1 : -1);
                            mapping = wr64VerticalHud(wr64Vertical, half, anchorX, anchorY);
                        }
                        else if (scissorHalf != 0) {
                            // Rectangular sky/water effects are emitted inside
                            // the owning scene scissor; full-frame transitions
                            // and the shared dimmer cannot select this branch.
                            half = scissorHalf;
                            worldClip = true;
                            mapping = wr64VerticalWorld(wr64Vertical, half);
                        }
                    }
                    else if (wr64VerticalViewportRole == Wr64VerticalViewport::World) {
                        half = wr64VerticalViewportHalf;
                        worldClip = true;
                        mapping = wr64VerticalWorld(wr64Vertical, half);
                    }
                    else if (raster && proj.type == Projection::Type::Orthographic &&
                        worldSegment >= 0x07000900 && worldSegment <= 0x07000A00 &&
                        ((worldSegment - 0x07000900) % 0x40) == 0 &&
                        nativeWorldY >= 0.0f && nativeWorldY <= 240.0f) {
                        // Other per-player GWord messages use the same small
                        // dedicated model-matrix slots as the pause cursor.
                        half = nativeWorldY < 120.0f ? 1 : 2;
                        mapping = wr64VerticalHud(wr64Vertical, half, 0, 0);
                    }

                    if (wr64VerticalPlayer(wr64Vertical, half) && (raster || colorFill)) {
                        const auto pane = wr64VerticalPane(wr64Vertical, half);
                        if (raster) {
                            auto &stored = storedCall.triangles;
                            float scaleX = stored.screenScale.x, scaleY = stored.screenScale.y;
                            float offsetX = stored.screenOffset.x, offsetY = stored.screenOffset.y;
                            wr64VerticalCompose(wr64Vertical, mapping, scaleX, scaleY, offsetX, offsetY);
                            stored.screenScale = { scaleX, scaleY };
                            stored.screenOffset = { offsetX, offsetY };
                            Wr64VerticalRect clip = pane;
                            if (worldClip) {
                                clip = wr64VerticalClip(wr64VerticalMapRect(mapping,
                                    { float(stored.scissor.left), float(stored.scissor.top),
                                      float(stored.scissor.right), float(stored.scissor.bottom) }), pane);
                            }
                            stored.scissor = { int32_t(std::floor(clip.left)), int32_t(std::floor(clip.top)),
                                int32_t(std::ceil(clip.right)), int32_t(std::ceil(clip.bottom)) };
                        }
                        else {
                            const auto &rect = storedCall.clearRect.rect;
                            const auto mapped = wr64VerticalClip(wr64VerticalMapRect(mapping,
                                { float(rect.left), float(rect.top), float(rect.right), float(rect.bottom) }), pane);
                            storedCall.clearRect.rect = { int32_t(std::floor(mapped.left)), int32_t(std::floor(mapped.top)),
                                int32_t(std::ceil(mapped.right)), int32_t(std::ceil(mapped.bottom)) };
                        }
                    }
                }

                // Independent full-band census: do not filter by the same
                // texture/state predicate whose missing coverage is under test.
                // Read the final stored transform after all presentation mapping.
                if (wr64WarmupTraceArmed() && proj.type == Projection::Type::Rectangle &&
                    wr64WarmupTraceCandidate(call.callDesc.rect.uly, call.callDesc.rect.lry,
                        call.callDesc.wr64HudMotion.kind)) {
                    Wr64WarmupTraceRow row;
                    const auto &desc = call.callDesc;
                    const auto &motion = desc.wr64HudMotion;
                    const auto &storedCall = instanceDrawCallVector.back();
                    row.workload = p.curWorkload->workloadId;
                    row.submission = p.curWorkload->submissionFrame;
                    row.present = p.curWorkload->presentId;
                    row.key = wr64CelestialRectKey(p.fbPairIndex, pr, d);
                    row.fbpair = p.fbPairIndex; row.projection = pr; row.call = d;
                    row.instance = instanceIndex; row.drawType = uint32_t(storedCall.type);
                    row.triangleCount = desc.triangleCount; row.tileCount = desc.tileCount;
                    row.rawVertexStart = call.meshDesc.rawVertexStart;
                    row.texture = wr64HudTmemHash;
                    if (desc.tileCount && desc.tileIndex < drawData.callTiles.size()) {
                        const auto &tile = drawData.callTiles[desc.tileIndex];
                        row.sampleWidth = tile.sampleWidth; row.sampleHeight = tile.sampleHeight;
                        row.tileValid = tile.valid; row.tileCopy = tile.tileCopyUsed; row.rawTmem = tile.rawTMEM;
                    }
                    row.combinerH = desc.colorCombiner.H; row.combinerL = desc.colorCombiner.L;
                    row.otherModeH = desc.otherMode.H; row.otherModeL = desc.otherMode.L;
                    row.dsdx = desc.rectDsdx; row.dtdy = desc.rectDtdy;
                    row.generation = motion.generation; row.kind = motion.kind; row.slot = motion.slot;
                    row.part = motion.part; row.content = motion.content; row.age = motion.age;
                    row.context = motion.context; row.nativeX = motion.x; row.nativeY = motion.y;
                    row.raw = { desc.rect.ulx, desc.rect.uly, desc.rect.lrx, desc.rect.lry };
                    row.chosen = { wr64ComposerCallRect.ulx, wr64ComposerCallRect.uly,
                        wr64ComposerCallRect.lrx, wr64ComposerCallRect.lry };
                    row.nativeScissor = { desc.scissorRect.ulx, desc.scissorRect.uly,
                        desc.scissorRect.lrx, desc.scissorRect.lry };
                    row.lerpFound = wr64CelRectOverridden;
                    for (const auto &pair : p.curWorkload->wr64CelestialPrevRects) {
                        if (pair.key != row.key) continue;
                        row.pairFound = true;
                        row.previous = { pair.prevRect.ulx, pair.prevRect.uly, pair.prevRect.lrx, pair.prevRect.lry };
                        row.current = { pair.curRect.ulx, pair.curRect.uly, pair.curRect.lrx, pair.curRect.lry };
                        break;
                    }
                    const size_t uvBase = size_t(call.meshDesc.rawVertexStart) * 2;
                    if (desc.triangleCount && uvBase + 8 <= drawData.triTcFloats.size()) {
                        const auto &tc = drawData.triTcFloats;
                        row.uvValid = true;
                        row.uv = { tc[uvBase], tc[uvBase + 1], tc[uvBase + 6], tc[uvBase + 7] };
                    }
                    if (storedCall.type == InstanceDrawCall::Type::RegularRect) {
                        const auto &stored = storedCall.triangles;
                        const float width = stored.screenScale.x * framebuffer.viewport.width;
                        const float height = stored.screenScale.y * framebuffer.viewport.height;
                        row.outputValid = true;
                        row.viewport = {
                            (stored.screenOffset.x - halfPixelOffset.x) * halfViewportSize.x + halfViewportSize.x - width * 0.5f,
                            halfViewportSize.y - (stored.screenOffset.y - halfPixelOffset.y) * halfViewportSize.y - height * 0.5f,
                            width, height };
                        row.outputScissor = { stored.scissor.left, stored.scissor.top, stored.scissor.right, stored.scissor.bottom };
                    }
                    else if (storedCall.type == InstanceDrawCall::Type::FillRect) {
                        const auto &rect = storedCall.clearRect.rect;
                        row.outputValid = true;
                        row.viewport = { float(rect.left), float(rect.top),
                            float(rect.right - rect.left), float(rect.bottom - rect.top) };
                        row.outputScissor = { rect.left, rect.top, rect.right, rect.bottom };
                    }
                    row.fbWidth = p.fbWidth; row.fbHeight = p.fbHeight;
                    row.targetWidth = p.targetWidth; row.targetHeight = p.targetHeight;
                    row.scaleX = p.resolutionScale.x; row.scaleY = p.resolutionScale.y;
                    wr64WarmupTraceWrite(row);
                }

                if (wr64SunOutputTraceArmed() && wr64SunOutputTexture(wr64HudTmemHash) &&
                    instanceDrawCallVector.back().type == InstanceDrawCall::Type::RegularRect) {
                    auto row = wr64SunOutputContext().output;
                    const auto &stored = instanceDrawCallVector.back().triangles;
                    const auto &desc = call.callDesc;
                    const auto &tile = p.curWorkload->drawData.callTiles[desc.tileIndex];
                    row.workload = p.curWorkload->workloadId;
                    row.submission = p.curWorkload->submissionFrame;
                    row.present = p.curWorkload->presentId;
                    row.fbpair = p.fbPairIndex; row.projection = pr; row.call = d;
                    row.hash = wr64HudTmemHash;
                    row.target = reinterpret_cast<uintptr_t>(p.fbStorage->colorTarget);
                    row.pipeline = reinterpret_cast<uintptr_t>(stored.pipeline);
                    row.colorAddress = fbPair.colorImage.address; row.depthAddress = fbPair.depthImage.address;
                    row.fbWidth = p.fbWidth; row.fbHeight = p.fbHeight;
                    row.targetWidth = p.targetWidth; row.targetHeight = p.targetHeight;
                    if (p.fbStorage->colorTarget) {
                        row.allocatedWidth = p.fbStorage->colorTarget->width;
                        row.allocatedHeight = p.fbStorage->colorTarget->height;
                        row.samples = p.fbStorage->colorTarget->multisampling.sampleCount;
                    }
                    row.sampleWidth = tile.sampleWidth; row.sampleHeight = tile.sampleHeight;
                    row.tileCopy = tile.tileCopyUsed; row.rawTMEM = tile.rawTMEM; row.tileValid = tile.valid;
                    row.raw = { desc.rect.ulx, desc.rect.uly, desc.rect.lrx, desc.rect.lry };
                    row.chosen = { wr64ComposerCallRect.ulx, wr64ComposerCallRect.uly, wr64ComposerCallRect.lrx, wr64ComposerCallRect.lry };
                    row.nativeScissor = { desc.scissorRect.ulx, desc.scissorRect.uly, desc.scissorRect.lrx, desc.scissorRect.lry };
                    row.scissor = { stored.scissor.left, stored.scissor.top, stored.scissor.right, stored.scissor.bottom };
                    row.lerpFound = wr64CelRectOverridden;
                    row.wide = wr64WideCelestialRectangle;
                    row.scaleX = p.resolutionScale.x; row.scaleY = p.resolutionScale.y;
                    const uint64_t key = wr64CelestialRectKey(p.fbPairIndex, pr, d);
                    for (const auto &pair : p.curWorkload->wr64CelestialPrevRects) {
                        if (pair.key != key) continue;
                        row.pairFound = true;
                        row.previous = { pair.prevRect.ulx, pair.prevRect.uly, pair.prevRect.lrx, pair.prevRect.lry };
                        break;
                    }
                    const float width = stored.screenScale.x * framebuffer.viewport.width;
                    const float height = stored.screenScale.y * framebuffer.viewport.height;
                    row.viewport = {
                        (stored.screenOffset.x - halfPixelOffset.x) * halfViewportSize.x + halfViewportSize.x - width * 0.5f,
                        halfViewportSize.y - (stored.screenOffset.y - halfPixelOffset.y) * halfViewportSize.y - height * 0.5f,
                        width, height };
                    const auto &tc = p.curWorkload->drawData.triTcFloats;
                    const size_t uvBase = size_t(stored.indexStart) * 2;
                    if (uvBase + 8 <= tc.size()) row.uv = { tc[uvBase], tc[uvBase + 1], tc[uvBase + 6], tc[uvBase + 7] };
                    if (wr64DolphinSunPresentation) {
                        // chosen/previous retain the trace's integer-qpx ABI;
                        // final viewport above preserves the actual floats.
                        for (size_t edge = 0; edge < 4; ++edge)
                            row.chosen[edge] = int32_t(std::lround(wr64DolphinSunRect[edge] * 4.0f));
                        row.lerpFound = wr64DolphinSunInterpolated;
                        for (const auto &pair : p.curWorkload->wr64DolphinSunPairs) {
                            if (pair.key != key) continue;
                            row.pairFound = true;
                            for (size_t edge = 0; edge < 4; ++edge)
                                row.previous[edge] = int32_t(std::lround(pair.previous[edge] * 4.0f));
                            break;
                        }
                    }
                    row.otherModeH = desc.otherMode.H; row.otherModeL = desc.otherMode.L;
                    row.combinerH = desc.colorCombiner.H; row.combinerL = desc.colorCombiner.L;
                    const auto &prim = desc.rdpParams.primColor;
                    row.prim = { float(prim.x), float(prim.y), float(prim.z), float(prim.w) };
                    wr64SunOutputPrepared(instanceIndex, row);
                }
                globalCallIndex++;
            }
        }

#   if RT_ENABLED
        checkRtScene(rtScene);
#   endif
        checkRasterScene(rasterScene);
        for (auto &view : wr64RTViews) {
            rt = &view;
            if (rt->framebuffer == framebufferCount - 1 && !rt->waterIndices.empty()) {
                // Coincident native endpoints may move apart during interpolation.
                // Weld only vertices with identical position-evaluation inputs too.
                const bool hasField = !drawData.wr64WaterFieldInfo.empty();
                const bool validStreams = drawData.velFloats.size() == size_t(rt->vertexCount) * 3 &&
                    (!hasField || (drawData.wr64WaterFieldInfo.size() == size_t(rt->vertexCount) * 4 &&
                        drawData.wr64WaterFieldPrevPosShiftX.size() == rt->vertexCount &&
                        drawData.wr64WaterFieldPrevTcShiftZ.size() == rt->vertexCount));
                if (validStreams) {
                    std::vector<Wr64WaterAdjacency::Payload> payloads(rt->vertexCount);
                    auto bits = [](float value) {
                        uint32_t result = 0;
                        if (value != 0.0f) std::memcpy(&result, &value, sizeof(result));
                        return result;
                    };
                    for (uint32_t vertex : rt->waterIndices) {
                        auto &payload = payloads[vertex];
                        for (size_t c = 0; c < 3; ++c)
                            payload[c] = bits(drawData.velFloats[size_t(vertex) * 3 + c]);
                        if (hasField) {
                            for (size_t c = 0; c < 4; ++c)
                                payload[3 + c] = drawData.wr64WaterFieldInfo[size_t(vertex) * 4 + c];
                            payload[7] = bits(float(drawData.wr64WaterFieldPrevPosShiftX[vertex].y));
                            payload[8] = bits(float(drawData.wr64WaterFieldPrevPosShiftX[vertex].w));
                            payload[9] = bits(float(drawData.wr64WaterFieldPrevTcShiftZ[vertex].z));
                        }
                    }
                    rt->waterAdjacency.build(rt->vertexCount, drawData.posFloats,
                        drawData.worldIndices, rt->waterIndices, payloads);
                }
                else rt->waterAdjacency.error = "normal-presentation-streams";
            }
        }
        if (wr64FilterSummarize) {
            char details[448];
            std::snprintf(details, sizeof(details),
                "frame=%llu selected=%u pair=%u prepared=%zu applied=%zu parameter_mismatches=%zu target=%ux%u resolution_scale=%g,%g",
                (unsigned long long)p.curWorkload->submissionFrame, wr64FilterSelectedMode,
                unsigned(p.fbPairIndex), wr64FilterPreparedCount, wr64FilterAppliedCount,
                wr64FilterParameterMismatchCount,
                p.targetWidth, p.targetHeight, double(p.resolutionScale.x), double(p.resolutionScale.y));
            wr64UiFilterDiagnostic("prepared-summary", details);
        }
    }

    void FramebufferRenderer::armWr64SkyCapture(Wr64RTView *rt, RenderWorker *worker, const OutputBuffers *outputBuffers) {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        if (!rt->skyCaptureRequested || !rt->skyCaptureDrawData || !rt->skyCaptureBuffer ||
            !outputBuffers || !outputBuffers->worldPosBuffer.buffer ||
            !outputBuffers->genTexCoordBuffer.buffer || !outputBuffers->shadedColBuffer.buffer)
            return;
        const uint64_t now = wr64SkyCaptureClockMs();
        if (!rt->skyCaptureStartMs) rt->skyCaptureStartMs = now;
        if (now - rt->skyCaptureStartMs >= 30000 ||
            (rt->skyCaptureLastMs && now - rt->skyCaptureLastMs < 34)) return;

        // Selection can be invalidated by a later ambiguous native draw. Only
        // read back vertices belonging to the final enabled layer.
        for (size_t layerIndex = 0; layerIndex < rt->skyCaptureLayers.size(); ++layerIndex) {
            auto &layer = rt->skyCaptureLayers[layerIndex];
            if (!(layerIndex == 0 ? rt->params.sky.w : rt->params.skyBackdrop.w))
                layer.count = 0;
            for (uint32_t i = 0; i < layer.count; ++i) {
                const uint64_t endVertex = uint64_t(layer.vertices[i]) + 1;
                if (endVertex * 16 > outputBuffers->worldPosBuffer.allocatedSize ||
                    endVertex * 8 > outputBuffers->genTexCoordBuffer.allocatedSize ||
                    endVertex * 16 > outputBuffers->shadedColBuffer.allocatedSize) return;
            }
        }
        try {
            if (!rt->skyCaptureZero) {
                auto zero = worker->device->createBuffer(RenderBufferDesc::UploadBuffer(Wr64SkyCaptureBytes));
                void *bytes = zero ? zero->map() : nullptr;
                if (!bytes) throw std::runtime_error("sky capture zero upload unavailable");
                std::memset(bytes, 0, size_t(Wr64SkyCaptureBytes));
                zero->unmap();
                rt->skyCaptureZero = std::move(zero);
            }
            if (!rt->skyCaptureReadback)
                rt->skyCaptureReadback = worker->device->createBuffer(RenderBufferDesc::ReadbackBuffer(
                    Wr64SkyCaptureBytes + Wr64SkyCaptureVertexBytes));
            if (!rt->skyCaptureReadback) throw std::runtime_error("sky capture readback unavailable");
            if (!rt->skyCaptureFile) {
                std::filesystem::create_directories(".runtime");
                rt->skyCaptureFile = std::fopen(".runtime/rt-sky-drop.jsonl", "wb");
                if (!rt->skyCaptureFile) throw std::runtime_error("sky capture file unavailable");
                wr64RTDiagnostic("sky-capture", "started path=.runtime/rt-sky-drop.jsonl limit_ms=30000 interval_ms=34");
            }
            // Snapshot the AS map while its owning workload and native draw
            // metadata are still current. GPU geometry IDs refer to this order.
            rt->skyCaptureGeometry.clear();
            for (const auto &geometry : rt->geometry) {
                if ((geometry.shadowFlags & 8u) || !geometry.indexCount || geometry.indexCount % 3 ||
                    geometry.faceIndicesStart > rt->indexCount ||
                    geometry.indexCount > rt->indexCount - geometry.faceIndicesStart) continue;
                rt->skyCaptureGeometry.push_back(geometry);
            }
        } catch (...) {
            rt->skyCaptureFailed = true;
            wr64RTDiagnostic("sky-capture", "disabled reason=capture-resource-or-file-failure");
            return;
        }
        rt->params.skyCloudParams.w = 1.0f;
        void *parameters = rt->paramsBuffer->map();
        if (!parameters) {
            // The earlier successful upload has w=0. Optional diagnostics do
            // not invalidate a working native/RT rendering path.
            rt->params.skyCloudParams.w = 0.0f;
            rt->skyCaptureFailed = true;
            wr64RTDiagnostic("sky-capture", "disabled reason=capture-parameter-upload-failure");
            return;
        }
        std::memcpy(parameters, &rt->params, sizeof(rt->params));
        rt->paramsBuffer->unmap();
        rt->skyCapturePositions = outputBuffers->worldPosBuffer.buffer.get();
        rt->skyCaptureTexcoords = outputBuffers->genTexCoordBuffer.buffer.get();
        rt->skyCaptureColors = outputBuffers->shadedColBuffer.buffer.get();
        rt->skyCaptureElapsedMs = now - rt->skyCaptureStartMs;
        rt->skyCaptureLastMs = now;
        rt->skyCaptureArmed = true;
    }

    void FramebufferRenderer::recordWr64SkyCaptureReadback(RenderWorker *worker) {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        for (auto &view : wr64RTViews) recordWr64SkyCaptureReadback(&view, worker);
    }

    void FramebufferRenderer::recordWr64SkyCaptureReadback(Wr64RTView *rt, RenderWorker *worker) {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        if (!rt->skyCaptureArmed || !rt->prepared || !rt->shadowWaterSelected) return;
        // Called after this presentation's draws, before its existing submit.
        // COPY-stage READ means copy source in Plume (there is no COPY_SOURCE
        // buffer access enumerator). The destination is a readback heap.
        const RenderBufferBarrier barriers[] = {
            { rt->skyCaptureBuffer.get(), RenderBufferAccess::READ },
            { rt->skyCapturePositions, RenderBufferAccess::READ },
            { rt->skyCaptureTexcoords, RenderBufferAccess::READ },
            { rt->skyCaptureColors, RenderBufferAccess::READ }
        };
        worker->commandList->barriers(RenderBarrierStage::COPY, barriers, uint32_t(std::size(barriers)));
        worker->commandList->copyBufferRegion(rt->skyCaptureReadback->at(0), rt->skyCaptureBuffer->at(0), Wr64SkyCaptureBytes);
        for (size_t layerIndex = 0; layerIndex < rt->skyCaptureLayers.size(); ++layerIndex) {
            const auto &layer = rt->skyCaptureLayers[layerIndex];
            for (uint32_t i = 0; i < layer.count; ++i) {
                const uint64_t vertex = layer.vertices[i];
                const uint64_t offset = Wr64SkyCaptureBytes + (layerIndex * 18 + i) * 40;
                worker->commandList->copyBufferRegion(rt->skyCaptureReadback->at(offset), rt->skyCapturePositions->at(vertex * 16), 16);
                worker->commandList->copyBufferRegion(rt->skyCaptureReadback->at(offset + 16), rt->skyCaptureTexcoords->at(vertex * 8), 8);
                worker->commandList->copyBufferRegion(rt->skyCaptureReadback->at(offset + 24), rt->skyCaptureColors->at(vertex * 16), 16);
            }
        }
        const RenderBufferBarrier restored[] = {
            { rt->skyCapturePositions, RenderBufferAccess::READ },
            { rt->skyCaptureTexcoords, RenderBufferAccess::READ },
            { rt->skyCaptureColors, RenderBufferAccess::READ }
        };
        worker->commandList->barriers(RenderBarrierStage::GRAPHICS, restored, uint32_t(std::size(restored)));
        rt->skyCaptureCopied = true;
    }

    void FramebufferRenderer::consumeWr64SkyCaptureReadback() {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        for (auto &view : wr64RTViews) consumeWr64SkyCaptureReadback(&view);
    }

    void FramebufferRenderer::consumeWr64SkyCaptureReadback(Wr64RTView *rt) {
        if (!WR64_DIAGNOSTIC_ENABLED) return;
        if (!rt->skyCaptureCopied) return;
        rt->skyCaptureCopied = false;
        const RenderRange readRange(0, Wr64SkyCaptureBytes + Wr64SkyCaptureVertexBytes);
        const auto *bytes = static_cast<const uint8_t *>(rt->skyCaptureReadback->map(0, &readRange));
        if (!bytes) {
            rt->skyCaptureFailed = true;
            wr64RTDiagnostic("sky-capture", "disabled reason=readback-map-failure");
            return;
        }
        const RenderRange noWrite(0, 0);
        try {
            uint32_t appended = 0;
            std::memcpy(&appended, bytes, 4);
            const uint32_t count = std::min(appended, 512u);
            std::ostringstream out;
            out << "{\"schema\":1,\"elapsed_ms\":" << rt->skyCaptureElapsedMs
                << ",\"workload\":" << rt->workload << ",\"submission\":" << rt->skyCaptureSubmission
                << ",\"native_present\":" << rt->skyCaptureNativePresent << ",\"presentation\":" << rt->skyCapturePresent
                << ",\"appended\":" << appended << ",\"camera_u32\":";
            wr64SkyCaptureWords(out, &rt->params.camera, 4);
            out << ",\"sky_camera_u32\":"; wr64SkyCaptureWords(out, &rt->params.skyCamera, 4);
            out << ",\"backdrop_camera_u32\":"; wr64SkyCaptureWords(out, &rt->params.skyBackdropCamera, 4);
            out << ",\"cloud_params_u32\":"; wr64SkyCaptureWords(out, &rt->params.skyCloudParams, 4);
            out << ",\"sky_u32\":"; wr64SkyCaptureWords(out, &rt->params.sky, 4);
            out << ",\"backdrop_u32\":"; wr64SkyCaptureWords(out, &rt->params.skyBackdrop, 4);
            out << ",\"layers\":[";
            for (size_t layerIndex = 0; layerIndex < rt->skyCaptureLayers.size(); ++layerIndex) {
                if (layerIndex) out << ',';
                const auto &layer = rt->skyCaptureLayers[layerIndex];
                out << "{\"material\":" << (layer.count ? layer.material : "null") << ",\"vertices\":[";
                for (uint32_t i = 0; i < layer.count; ++i) {
                    if (i) out << ',';
                    out << "{\"id\":" << layer.vertices[i] << ",\"gpu_u32\":";
                    wr64SkyCaptureWords(out, bytes + Wr64SkyCaptureBytes + (layerIndex * 18 + i) * 40, 10);
                    out << '}';
                }
                out << "]}";
            }
            std::set<uint32_t> hitGeometries;
            std::set<std::pair<uint32_t, uint32_t>> hitFaces;
            out << "],\"records_u32\":[";
            for (uint32_t i = 0; i < count; ++i) {
                if (i) out << ',';
                const uint8_t *packet = bytes + 16 + i * 128;
                wr64SkyCaptureWords(out, packet, 32);
                uint32_t geometry = 0, primitive = 0;
                std::memcpy(&geometry, packet + 20 * 4, 4);
                std::memcpy(&primitive, packet + 21 * 4, 4);
                if (geometry < rt->skyCaptureGeometry.size()) {
                    hitGeometries.insert(geometry);
                    hitFaces.emplace(geometry, primitive);
                }
            }
            out << "],\"hit_geometries\":[";
            bool comma = false;
            for (uint32_t index : hitGeometries) {
                if (comma) out << ',';
                comma = true;
                const auto &geometry = rt->skyCaptureGeometry[index];
                out << "{\"index\":" << index << ",\"first_index\":" << geometry.faceIndicesStart
                    << ",\"index_count\":" << geometry.indexCount << ",\"draw\":" << geometry.drawIndex
                    << ",\"flags\":" << geometry.shadowFlags;
                if (geometry.drawIndex < renderIndicesVector.size() && geometry.drawIndex < instanceDrawCallVector.size()) {
                    const auto &desc = instanceDrawCallVector[geometry.drawIndex].triangles.shaderDesc;
                    out << ",\"native_call\":" << renderIndicesVector[geometry.drawIndex].instanceIndex
                        << ",\"combiner\":[" << desc.colorCombiner.L << ',' << desc.colorCombiner.H
                        << "],\"other_mode\":[" << desc.otherMode.L << ',' << desc.otherMode.H << ']';
                }
                out << '}';
            }
            out << "],\"hit_faces\":[";
            comma = false;
            for (const auto &face : hitFaces) {
                const auto &geometry = rt->skyCaptureGeometry[face.first];
                const uint64_t local = uint64_t(face.second) * 3;
                const uint64_t start = uint64_t(geometry.faceIndicesStart) + local;
                if (local + 3 > geometry.indexCount || !rt->skyCaptureDrawData ||
                    start + 3 > rt->skyCaptureDrawData->faceIndices.size()) continue;
                if (comma) out << ',';
                comma = true;
                out << "{\"geometry\":" << face.first << ",\"primitive\":" << face.second << ",\"vertex_ids\":[";
                for (uint32_t j = 0; j < 3; ++j) {
                    if (j) out << ',';
                    out << rt->skyCaptureDrawData->faceIndices[size_t(start + j)];
                }
                out << "],\"source_addresses\":[";
                for (uint32_t j = 0; j < 3; ++j) {
                    if (j) out << ',';
                    const uint32_t vertex = rt->skyCaptureDrawData->faceIndices[size_t(start + j)];
                    out << (vertex < rt->skyCaptureDrawData->vertexSegmentedAddresses.size() ?
                        rt->skyCaptureDrawData->vertexSegmentedAddresses[vertex] : UINT32_MAX);
                }
                out << "]}";
            }
            out << "]}\n";
            const std::string line = out.str();
            if (std::fwrite(line.data(), 1, line.size(), rt->skyCaptureFile) != line.size() ||
                std::fflush(rt->skyCaptureFile) != 0) throw std::runtime_error("sky capture write failed");
        } catch (...) {
            rt->skyCaptureFailed = true;
            wr64RTDiagnostic("sky-capture", "disabled reason=capture-serialization-or-write-failure");
        }
        rt->skyCaptureReadback->unmap(0, &noWrite);
    }

    void FramebufferRenderer::endFramebuffers(RenderWorker *worker, const DrawBuffers *drawBuffers, const OutputBuffers *outputBuffers, bool rtEnabled) {
        if (!wr64MotionActors.empty()) {
            wr64MotionDiagnostic.reason = wr64MotionOrderRejected ? "world-after-hud" :
                wr64MotionBoundary == UINT32_MAX ? "missing-hud-boundary" :
                wr64RTViews[0].framebuffer >= framebufferCount ? "missing-framebuffer" :
                !outputBuffers->worldVelBuffer.buffer ? "missing-velocity" : "prepared-not-executed";
        }
        if (!wr64MotionActors.empty() && !wr64MotionOrderRejected && wr64MotionBoundary != UINT32_MAX &&
            wr64RTViews[0].framebuffer < framebufferCount && outputBuffers->worldVelBuffer.buffer) {
            const auto &targetDraw = framebufferVector[wr64RTViews[0].framebuffer].renderTargetDrawCall;
            // A split raster/RT scene could make our HUD boundary belong to a
            // different pass. The initial experiment accepts one native scene.
            const auto &viewport = framebufferVector[wr64RTViews[0].framebuffer].viewport;
            const bool oneScene = targetDraw.rasterScenes.size() == 1 && targetDraw.sceneIndices.size() == 1 &&
                viewport.x == 0 && viewport.y == 0;
            auto *color = targetDraw.fbStorage->colorTarget;
            const bool motionPipelineReady = oneScene && color &&
                wr64MotionBlur.prepare(worker->device, rendererPipelineLayout, color->multisampling, shaderLibrary->usesHDR);
            wr64MotionPrepared = motionPipelineReady &&
                wr64MotionBlur.ensureTargets(worker, color, targetDraw.fbStorage->depthTarget, shaderLibrary);
            wr64MotionDiagnostic.reason = !oneScene ? "scene-or-viewport-guard" : !color ? "missing-color" :
                !motionPipelineReady ? "pipeline-not-ready" : !wr64MotionPrepared ? "targets-failed" : "prepared-not-executed";
            if (wr64MotionPrepared) {
                const uint64_t bytes = wr64MotionDrawParams.size() * sizeof(Wr64MotionDrawParams);
                if (!wr64MotionDrawBuffer || wr64MotionDrawCapacity < bytes) {
                    wr64MotionDrawBuffer = worker->device->createBuffer(RenderBufferDesc::UploadBuffer(bytes, RenderBufferFlag::STORAGE));
                    wr64MotionDrawCapacity = wr64MotionDrawBuffer ? bytes : 0;
                }
                void *mapped = wr64MotionDrawBuffer ? wr64MotionDrawBuffer->map() : nullptr;
                wr64MotionPrepared = mapped != nullptr;
                if (!mapped) wr64MotionDiagnostic.reason = "draw-params-upload-failed";
                if (mapped) {
                    std::memcpy(mapped, wr64MotionDrawParams.data(), size_t(bytes));
                    wr64MotionDrawBuffer->unmap();
                }
            }
        }
        for (auto &view : wr64RTViews) {
            auto *rt = &view;
            rt->params.sceneOptions.w = 0;
            for (uint32_t racer = 0; racer < 4; ++racer) {
                const auto &bounds = rt->actorBounds[racer];
                if ((uint32_t(rt->params.sceneOptions.z) & (1u << racer)) && bounds.reliable && bounds.populated) {
                    rt->params.sceneOptions.w |= 1u << racer;
                    rt->params.actorShadowBoundsMin[racer] = { bounds.minimum[0], bounds.minimum[1], bounds.minimum[2], 0.0f };
                    rt->params.actorShadowBoundsMax[racer] = { bounds.maximum[0], bounds.maximum[1], bounds.maximum[2], 0.0f };
                }
            }
            if (rt->framebuffer < framebufferCount &&
                (!rt->waterDraws.empty() || (rt->endingWorldOnly && !rt->shoreDraws.empty())) &&
                (!rt->traceReflections || !rt->geometry.empty())) {
                auto *target = framebufferVector[rt->framebuffer].renderTargetDrawCall.fbStorage->colorTarget;
                const auto shadowWaterMode = wr64ShadowWaterMode(rt->traceReflections && !rt->raySkyOnly,
                    rt->traceReflections && rt->skyScopeSeen && !rt->rasterSky, rt->rasterSky);
                if (rt->rasterShadows) {
                    rt->prepared = target && rt->rasterShadowParams.light[3] == 1.0f && !rt->rasterShadowCasters.empty() &&
                        wr64RasterShadowPipelines.prepare(worker->device, rendererPipelineLayout, target->multisampling,
                            shaderLibrary->usesHDR, true, shadowWaterMode) &&
                        wr64RasterShadowPipelines.capture() && rt->rasterShadowTarget.ensure(worker);
                    if (rt->prepared && !rt->rasterShadowParamsBuffer)
                        rt->rasterShadowParamsBuffer = worker->device->createBuffer(RenderBufferDesc::UploadBuffer(256, RenderBufferFlag::CONSTANT));
                    if (rt->prepared) {
                        void *mapped = rt->rasterShadowParamsBuffer ? rt->rasterShadowParamsBuffer->map() : nullptr;
                        rt->prepared = mapped != nullptr;
                        if (mapped) {
                            std::memcpy(mapped, &rt->rasterShadowParams, sizeof(rt->rasterShadowParams));
                            rt->rasterShadowParamsBuffer->unmap();
                        }
                    }
                    if (rt->prepared && rt->rasterSky) {
                        // Sky capture stays the accepted raster program. Only
                        // the water receiver changes to add mapped shadows.
                        rt->prepared = wr64RasterSkyPipelines.prepare(worker->device, rendererPipelineLayout,
                            target->multisampling, shaderLibrary->usesHDR, true) &&
                            wr64RasterSkyPipelines.capture() && rt->rasterSkyTarget.ensure(worker);
                    }
                    if (rt->prepared) {
                        for (uint32_t racer = 0; racer < 4; ++racer) {
                            const auto &bounds = rt->actorBounds[racer];
                            if (!bounds.reliable || !bounds.populated || !(rt->racerShadowCasters & (1u << racer))) continue;
                            bool covered = true;
                            for (uint32_t corner = 0; corner < 8; ++corner) {
                                float point[4] = {bounds.minimum[0], bounds.minimum[1], bounds.minimum[2], 1.0f};
                                for (uint32_t axis = 0; axis < 3; ++axis) if (corner & (1u << axis)) point[axis] = bounds.maximum[axis];
                                float clip[3]{};
                                for (uint32_t row = 0; row < 3; ++row)
                                    for (uint32_t col = 0; col < 4; ++col) clip[row] += rt->rasterShadowParams.lightRows[row][col] * point[col];
                                covered &= std::isfinite(clip[0]) && std::isfinite(clip[1]) && std::isfinite(clip[2]) &&
                                    std::abs(clip[0]) < 0.8f && std::abs(clip[1]) < 0.8f && clip[2] > 0.05f && clip[2] < 0.95f;
                            }
                            if (covered) rt->rasterShadowRacers |= 1u << racer;
                        }
                    }
                }
                else if (!rt->rasterReflections && (rt->rasterSky || rt->raySkyOnly)) {
                    const auto mode = rt->raySkyOnly ? Wr64SkyWaterMode::RayTracedSkyOnly :
                        rt->traceReflections ? Wr64SkyWaterMode::CachedSkyWithRTObjects : Wr64SkyWaterMode::RasterOnly;
                    rt->prepared = target && wr64RasterSkyPipelines.prepare(worker->device, rendererPipelineLayout,
                        target->multisampling, shaderLibrary->usesHDR, true, mode);
                    if (rt->prepared && rt->rasterSky)
                        rt->prepared = wr64RasterSkyPipelines.capture() && rt->rasterSkyTarget.ensure(worker);
                }
                else if (!rt->rasterReflections) rt->prepared = target && wr64RTWaterPipelines.prepare(worker->device, rendererPipelineLayout,
                    target->multisampling, shaderLibrary->usesHDR, rt->skyScopeSeen, true, wr64RTShaderFormat);
                if (rt->rasterReflections) {
                    const auto &water = instanceDrawCallVector[rt->waterDraws.front()].triangles;
                    const float scale[2] = {water.screenScale.x, water.screenScale.y};
                    const float offset[2] = {water.screenOffset.x, water.screenOffset.y};
                    const auto clip = wr64BuildPlanarD3DClipProjection(rt->reflectionViewRows,
                        rt->reflectionViewportScale, rt->reflectionViewportTranslate,
                        rt->reflectionFramebufferSize, scale, offset);
                    const auto reflected = clip.valid
                        ? wr64BuildPlanarReflectionProjection(clip.rows, rt->reflectionPlaneY)
                        : Wr64PlanarReflectionProjection{};
                    const auto sky = rt->rasterSky ? Wr64RasterReflectionSkyMode::RasterSky :
                        rt->raySkyOnly ? Wr64RasterReflectionSkyMode::RTSkyOnly : Wr64RasterReflectionSkyMode::SkyOff;
                    rt->prepared = (!rt->rasterShadows || rt->prepared) && target &&
                        rt->reflectionPlaneValid && reflected.valid &&
                        wr64RasterReflectionPipelines.prepare(worker->device, rendererPipelineLayout,
                            target->multisampling, shaderLibrary->usesHDR, true, sky, rt->rasterShadows) &&
                        wr64RasterReflectionPipelines.capture(false) && wr64RasterReflectionPipelines.capture(true);
                    if (rt->prepared) {
                        const auto &viewport = framebufferVector[rt->framebuffer].viewport;
                        // Half-size capture, bounded at 1024 pixels wide. The
                        // final native viewport's aspect is retained at every
                        // internal resolution; capture sampling uses clip UVs.
                        // Each player retains full-frame coordinates, including
                        // the final horizontal/vertical pane transform, in a
                        // separate target. No other player's pixels are sampled.
                        const float captureScale = std::min(0.5f, 1024.0f / std::max(viewport.width, 1.0f));
                        const uint32_t width = std::max(1u, uint32_t(std::ceil(viewport.width * captureScale)));
                        const uint32_t height = std::max(1u, uint32_t(std::ceil(viewport.height * captureScale)));
                        rt->prepared = rt->rasterReflectionTarget.ensure(worker, width, height);
                        std::memcpy(rt->rasterReflectionParams.reflectedRows, reflected.rows, sizeof(reflected.rows));
                        std::memcpy(rt->rasterReflectionParams.plane, reflected.clipPlane, sizeof(reflected.clipPlane));
                        rt->rasterReflectionParams.options[0] = 1.0f;
                        rt->rasterReflectionParams.options[1] = 1.0f;
                        rt->rasterReflectionParams.options[2] = 64.0f;
                        rt->rasterReflectionParams.options[3] = 0.5f;
                    }
                    if (rt->prepared && !rt->rasterReflectionParamsBuffer)
                        rt->rasterReflectionParamsBuffer = worker->device->createBuffer(
                            RenderBufferDesc::UploadBuffer(256, RenderBufferFlag::CONSTANT));
                    if (rt->prepared) {
                        void *mapped = rt->rasterReflectionParamsBuffer ? rt->rasterReflectionParamsBuffer->map() : nullptr;
                        rt->prepared = mapped != nullptr;
                        if (mapped) {
                            std::memcpy(mapped, &rt->rasterReflectionParams, sizeof(rt->rasterReflectionParams));
                            rt->rasterReflectionParamsBuffer->unmap();
                        }
                    }
                    if (rt->prepared && rt->rasterSky && !rt->rasterShadows)
                        rt->prepared = wr64RasterSkyPipelines.prepare(worker->device, rendererPipelineLayout,
                            target->multisampling, shaderLibrary->usesHDR, true) &&
                            wr64RasterSkyPipelines.capture() && rt->rasterSkyTarget.ensure(worker);
                }
                if (rt->prepared && rt->traceReflections)
                    rt->prepared = rt->scene.prepare(worker->device, outputBuffers->worldPosBuffer.buffer.get(),
                        drawBuffers->faceIndicesBuffer.defaultBuffer.get(), rt->vertexCount,
                        rt->indexCount, rt->geometry, rt->fenceProxies);
                if (rt->prepared) {
                    if (!rt->paramsBuffer) rt->paramsBuffer = worker->device->createBuffer(RenderBufferDesc::UploadBuffer(
                        (sizeof(Wr64RTParams) + 255) & ~uint64_t(255), RenderBufferFlag::CONSTANT));
                    rt->prepared = rt->paramsBuffer != nullptr;
                }
                if (rt->prepared && !rt->rasterReflections && !rt->rasterSky && !rt->raySkyOnly && rt->skyScopeSeen) {
                    // The sky shader declares this UAV even when capture is off.
                    // Allocation failure keeps the native raster pipeline selected.
                    // Planar variants never use it, including when a saved RT
                    // sky selection is unsupported by the current adapter.
                    if (!rt->skyCaptureBuffer) {
                        try {
                            rt->skyCaptureBuffer = worker->device->createBuffer(RenderBufferDesc::DefaultBuffer(
                                Wr64SkyCaptureBytes, RenderBufferFlag::STORAGE | RenderBufferFlag::UNORDERED_ACCESS));
                        } catch (...) { rt->skyCaptureBuffer.reset(); }
                    }
                    rt->prepared = rt->skyCaptureBuffer != nullptr;
                }
                if (rt->prepared) {
                    const uint64_t adjacencyBytes = rt->waterAdjacency.words.size() * sizeof(uint32_t);
                    // Bind a valid SRV even for geometric-normal fallback after
                    // topology rejection. Allocation failure keeps native rendering.
                    const uint64_t required = std::max(uint64_t(8), adjacencyBytes);
                    if (!rt->waterAdjacencyBuffer || rt->waterAdjacencyCapacity < required) {
                        rt->waterAdjacencyBuffer = worker->device->createBuffer(
                            RenderBufferDesc::UploadBuffer(required, RenderBufferFlag::STORAGE));
                        rt->waterAdjacencyCapacity = rt->waterAdjacencyBuffer ? required : 0;
                    }
                    rt->prepared = rt->waterAdjacencyBuffer != nullptr;
                    if (rt->prepared) {
                        void *bytes = rt->waterAdjacencyBuffer->map();
                        rt->prepared = bytes != nullptr;
                        if (bytes) {
                            if (adjacencyBytes) std::memcpy(bytes, rt->waterAdjacency.words.data(), adjacencyBytes);
                            else std::memset(bytes, 0, size_t(required));
                            rt->waterAdjacencyBuffer->unmap();
                            const char *flat = std::getenv("WR64_RT_FLAT_NORMALS");
                            const bool forceFlat = flat && flat[0] == '1' && flat[1] == '\0';
                            rt->params.smoothNormals = adjacencyBytes && !forceFlat ? 1 : 0;
                        }
                    }
                }
                if (rt->prepared) {
                    void *bytes = rt->paramsBuffer->map();
                    rt->prepared = bytes != nullptr;
                    if (bytes) {
                        std::memcpy(bytes, &rt->params, sizeof(rt->params));
                        rt->paramsBuffer->unmap();
                    }
                }
                if (rt->prepared) {
                    std::vector<const RenderPipeline *> readyWaterPipelines;
                    readyWaterPipelines.reserve(rt->waterDraws.size());
                    bool allWaterPipelinesReady = true;
                    for (uint32_t i : rt->waterDraws) {
                        auto &triangles = instanceDrawCallVector[i].triangles;
                        const auto &om = triangles.shaderDesc.otherMode;
                        rt->nativeWaterPipelines.push_back(triangles.pipeline);
                        const bool compare = om.zCmp() && om.zMode() != ZMODE_DEC;
                        const bool coverageAdd = om.cvgDst() == CVG_DST_WRAP || om.cvgDst() == CVG_DST_SAVE;
                        const auto *pipeline = rt->rasterReflections
                            ? wr64RasterReflectionPipelines.get(compare, om.zUpd(), coverageAdd)
                            : rt->rasterShadows
                            ? wr64RasterShadowPipelines.getWater(shadowWaterMode, compare, om.zUpd(), coverageAdd)
                            : (rt->rasterSky || rt->raySkyOnly)
                            ? wr64RasterSkyPipelines.get(compare, om.zUpd(), coverageAdd)
                            : wr64RTWaterPipelines.get(compare, om.zUpd(), coverageAdd);
                        readyWaterPipelines.push_back(pipeline);
                        allWaterPipelinesReady &= pipeline != nullptr;
                    }
                    // Driver compilation may take seconds on first use. Continue
                    // drawing the complete native scene until its water variants
                    // are ready; never install a null pipeline or stall this thread.
                    if (allWaterPipelinesReady) {
                        if (!rt->rasterReflections && !rt->rasterSky && !rt->raySkyOnly && rt->skyScopeSeen) armWr64SkyCapture(rt, worker, outputBuffers);
                        for (size_t j = 0; j < rt->waterDraws.size(); ++j)
                            instanceDrawCallVector[rt->waterDraws[j]].triangles.pipeline = readyWaterPipelines[j];
                        rt->shadowWaterSelected = true;
                    }
                    if (!rt->shoreDraws.empty() && (rt->rasterShadows || wr64RTWorldShadowPipelines.prepare(worker->device,
                        rendererPipelineLayout, target->multisampling, shaderLibrary->usesHDR, true, wr64RTShaderFormat))) {
                        for (uint32_t i : rt->shoreDraws) {
                            auto &triangles = instanceDrawCallVector[i].triangles;
                            const auto &om = triangles.shaderDesc.otherMode;
                            rt->nativeShorePipelines.push_back(triangles.pipeline);
                            const auto *shadowPipeline = rt->rasterShadows ? wr64RasterShadowPipelines.world(
                                om.zCmp() && om.zMode() != ZMODE_DEC, om.zUpd(),
                                om.cvgDst() == CVG_DST_WRAP || om.cvgDst() == CVG_DST_SAVE,
                                triangles.shaderDesc.flags.culling, triangles.shaderDesc.flags.NoN,
                                interop::Blender::usesAlphaBlend(om)) : wr64RTWorldShadowPipelines.get(
                                om.zCmp() && om.zMode() != ZMODE_DEC, om.zUpd(),
                                om.cvgDst() == CVG_DST_WRAP || om.cvgDst() == CVG_DST_SAVE,
                                triangles.shaderDesc.flags.culling, triangles.shaderDesc.flags.NoN,
                                interop::Blender::usesAlphaBlend(om));
                            if (shadowPipeline && allWaterPipelinesReady) {
                                triangles.pipeline = shadowPipeline;
                                ++rt->shoreSelected;
                                rt->aoOnlySelected += std::binary_search(rt->aoOnlyDraws.begin(), rt->aoOnlyDraws.end(), i);
                            }
                        }
                    }
                }
            }
            if (wr64RTDiagnosticEnabled() && (rt->scopeSeen || !rt->previousSkyState.empty())) {
                const auto &cloud = rt->skyCaptureDiagnostic[0];
                const auto &backdrop = rt->skyCaptureDiagnostic[1];
                const char *extensionReason = rt->params.sky.w == 0 ? cloud.reason :
                    cloud.coefficientValid != 1 ? "invalid-native-coefficients" :
                    cloud.currentWorldIdentity != 1 ? "nonidentity-current-world" :
                    cloud.lerpWorldIdentity != 1 ? "nonidentity-presentation-world" : "enabled";
                char state[640];
                std::snprintf(state, sizeof(state),
                    "native_view=%u scope=%u ready=%u water_rt_selected=%u cloud_candidates=%u cloud_enabled=%u cloud_extension=%u coefficient_valid=%d current_world_identity=%d lerp_world_identity=%d cloud_result=%s extension_result=%s backdrop_candidates=%u backdrop_enabled=%u backdrop_result=%s",
                    rt->nativeRaceView, unsigned(rt->skyScopeSeen), unsigned(rt->prepared), unsigned(rt->shadowWaterSelected),
                    rt->skyCandidates, rt->params.sky.w, unsigned(rt->params.skyCloudParams.z == 1.0f),
                    cloud.coefficientValid, cloud.currentWorldIdentity, cloud.lerpWorldIdentity,
                    cloud.reason, extensionReason, rt->backdropCandidates, rt->params.skyBackdrop.w, backdrop.reason);
                // Check every presentation, including absent native draws, but emit
                // only transitions. Periodic summaries alone miss one-frame drops.
                if (rt->previousSkyState != state) {
                    char details[896];
                    std::snprintf(details, sizeof(details),
                        "workload=%llu %s cloud_draw=%u cloud_view=%u cloud_camera_diff=%g backdrop_draw=%u backdrop_view=%u backdrop_camera_diff=%g",
                        (unsigned long long)rt->workload, state, cloud.draw, cloud.view,
                        double(cloud.cameraDifference), backdrop.draw, backdrop.view,
                        double(backdrop.cameraDifference));
                    wr64RTDiagnostic("sky-selection", details);
                    rt->previousSkyState = state;
                }
            }
            if (rt->scopeSeen && wr64RTDiagnosticEnabled()) {
                static thread_local uint64_t diagnosticCount = 0;
                if (diagnosticCount++ < 4 || diagnosticCount % 3600 == 0) {
                    const auto &stats = rt->scene.stats();
                    char details[768];
                    std::snprintf(details, sizeof(details), "workload=%llu supported=%u ready=%u water_draws=%zu geometries=%u triangles=%llu as_bytes=%llu debug=%u sky_scope=%u sky_matches=%u sky_candidates=%u sky_enabled=%u sky_draw=%u cloud_extension=%u coefficient_valid=%d current_world_identity=%d lerp_world_identity=%d backdrop_matches=%u backdrop_candidates=%u backdrop_enabled=%u backdrop_draw=%u celestial_bodies=%u celestial_snapshot=%u error=%s",
                        (unsigned long long)rt->workload, unsigned(wr64RTSupported), unsigned(rt->prepared), rt->waterDraws.size(), stats.geometryCount,
                        (unsigned long long)stats.triangleCount, (unsigned long long)stats.accelerationStructureBytes,
                        rt->params.debugView, unsigned(rt->skyScopeSeen), rt->skyMatches, rt->skyCandidates,
                        rt->params.sky.w, rt->params.sky.y, unsigned(rt->params.skyCloudParams.z == 1.0f),
                        rt->skyCaptureDiagnostic[0].coefficientValid, rt->skyCaptureDiagnostic[0].currentWorldIdentity,
                        rt->skyCaptureDiagnostic[0].lerpWorldIdentity, rt->backdropMatches, rt->backdropCandidates,
                        rt->params.skyBackdrop.w, rt->params.skyBackdrop.y,
                        rt->params.celestialInfo.x, rt->params.celestialInfo.y, rt->scene.lastError().c_str());
                    wr64RTDiagnostic("renderer", details);
                    char qualityDetails[128];
                    std::snprintf(qualityDetails, sizeof(qualityDetails),
                        "reflection_distance=%.1f actor_shadow_samples=%.0f source=frontend",
                        float(rt->params.qualityOptions.x), float(rt->params.qualityOptions.y));
                    wr64RTDiagnostic("quality", qualityDetails);
                    const size_t cutoutCount = std::count_if(rt->geometry.begin(), rt->geometry.end(),
                        [](const Wr64RTSceneGeometry &geometry) { return (geometry.shadowFlags & 2) != 0; });
                    char materialDetails[160];
                    std::snprintf(materialDetails, sizeof(materialDetails),
                        "ready=%u native_cutout_geometries=%zu opaque_geometries=%zu translucent_beams=%u",
                        unsigned(rt->prepared), cutoutCount,
                        rt->geometry.size() - cutoutCount - rt->params.sceneOptions.x,
                        unsigned(rt->params.sceneOptions.x));
                    wr64RTDiagnostic("materials", materialDetails);
                    if (rt->params.shadowOptions.x == 1.0f) {
                        const size_t casterCount = std::count_if(rt->geometry.begin(), rt->geometry.end(),
                            [](const Wr64RTSceneGeometry &geometry) { return (geometry.shadowFlags & 1) != 0; });
                        char shadowDetails[512];
                        std::snprintf(shadowDetails, sizeof(shadowDetails),
                            "ready=%u casters=%zu direction=%.6f,%.6f,%.6f strength=%.3f bias=%.3f max_distance=%.1f shore_receivers=%u arrow_exclusions=%u letter_exclusions=%u water_overlay=soft_actor_and_scenery proxy_geometries=%u proxy_triangles=%llu actor_geometries=%u actor_racers=%u actor_bounds=%u",
                            unsigned(rt->prepared), casterCount, float(rt->params.shadowLight.x),
                            float(rt->params.shadowLight.y), float(rt->params.shadowLight.z),
                            float(rt->params.shadowLight.w), float(rt->params.shadowOptions.y),
                            float(rt->params.shadowOptions.z), rt->shoreSelected - rt->aoOnlySelected, rt->arrowShadowExclusions,
                            rt->letterShadowExclusions, rt->scene.stats().proxyGeometryCount,
                            (unsigned long long)rt->scene.stats().proxyTriangleCount,
                            unsigned(rt->params.sceneOptions.y), unsigned(rt->params.sceneOptions.z),
                            unsigned(rt->params.sceneOptions.w));
                        wr64RTDiagnostic("shadows", shadowDetails);
                    }
                    char normalDetails[256];
                    char aoDetails[256];
                    std::snprintf(aoDetails, sizeof(aoDetails),
                        "ready=%u enabled=%u receiver_candidates=%zu receivers_selected=%u shore_selected=%u ao_only_candidates=%zu ao_only_selected=%u radius=%.3f strength=%.3f bias=%.3f",
                        unsigned(rt->prepared), unsigned(rt->params.aoOptions.x == 1.0f), rt->shoreDraws.size(),
                        rt->shoreSelected, rt->shoreSelected - rt->aoOnlySelected, rt->aoOnlyDraws.size(),
                        rt->aoOnlySelected, float(rt->params.aoOptions.y), float(rt->params.aoOptions.z), float(rt->params.aoOptions.w));
                    wr64RTDiagnostic("ambient-occlusion", aoDetails);
                    std::snprintf(normalDetails, sizeof(normalDetails),
                        "smooth=%u nodes=%u welded=%u triangles=%u bytes=%llu error=%s",
                        rt->params.smoothNormals, rt->waterAdjacency.validNodes,
                        rt->waterAdjacency.weldDuplicates, rt->waterAdjacency.triangles,
                        (unsigned long long)(rt->waterAdjacency.words.size() * sizeof(uint32_t)),
                        rt->waterAdjacency.error);
                    wr64RTDiagnostic("water-normals", normalDetails);
                }
            }
        }
        bool shaderViewRtEnabled = false;
        std::vector<BufferUploader::Upload> shaderUploads = {
            { renderIndicesVector.data(), { 0, renderIndicesVector.size() }, sizeof(interop::RenderIndices), RenderBufferFlag::STORAGE, { }, &renderIndicesBuffer},
            { &frameParams, { 0, 1 }, sizeof(interop::FrameParams), RenderBufferFlag::CONSTANT, { }, &frameParamsBuffer}
        };

#   if RT_ENABLED
        // FIXME: Add support for multiple raytracing scenes.
        Framebuffer *chosenFramebuffer = nullptr;
        RaytracingScene *chosenRtScene = nullptr;
        if (rtEnabled) {
            rtResources->updateBottomLevelASResources(worker);

            for (uint32_t i = 0; i < framebufferCount; i++) {
                RenderTargetDrawCall &targetDrawCall = framebufferVector[i].renderTargetDrawCall;
                if (!targetDrawCall.rtScenes.empty()) {
                    chosenFramebuffer = &framebufferVector[i];
                    chosenRtScene = &targetDrawCall.rtScenes[0];
                }
            }
        }

        if (chosenRtScene != nullptr) {
            if (rtResources->updateOutputBuffers) {
                rtResources->createOutputBuffers(worker, chosenRtScene->screenWidth, chosenRtScene->screenHeight);
                rtResources->updateOutputBuffers = false;
            }

            const RenderTarget *framebufferTarget = chosenFramebuffer->renderTargetDrawCall.fbStorage->colorTarget;
            interleavedRastersCount = static_cast<uint32_t>(chosenRtScene->interleavedRasters.size());
            rtResources->updateInterleavedRenderTargets(worker, chosenRtScene->screenWidth, chosenRtScene->screenHeight, interleavedRastersCount, framebufferTarget->multisampling, framebufferTarget->usesHDR);

            for (uint32_t i = 0; i < interleavedRastersCount; i++) {
                auto &intRaster = chosenRtScene->interleavedRasters[i];
                RenderTarget *colorTarget = rtResources->interleavedColorTargetVector[i].get();
                RenderTarget *depthTarget = rtResources->interleavedDepthTargetVector[i].get();
                intRaster.colorTextureIndex = getTextureIndex(colorTarget);
                intRaster.depthTextureIndex = getTextureIndex(depthTarget);
                chosenFramebuffer->transitionRenderTargetSet.emplace(colorTarget);
                chosenFramebuffer->transitionRenderTargetSet.emplace(depthTarget);
            }

            // Must have at least one element in the vector.
            if (chosenRtScene->interleavedRasters.empty()) {
                chosenRtScene->interleavedRasters.emplace_back();
            }

            shaderUploads.push_back({ &rtResources->rtParams, { 0, 1 }, sizeof(interop::RaytracingParams), RenderBufferFlag::CONSTANT, { }, &rtResources->rtParamsBuffer });
            shaderUploads.push_back({ chosenRtScene->interleavedRasters.data(), { 0, chosenRtScene->interleavedRasters.size() }, sizeof(interop::InterleavedRaster), RenderBufferFlag::STORAGE, { }, &interleavedRastersBuffer });

            updateRaytracingScene(worker, *chosenRtScene);
            shaderViewRtEnabled = true;
        }
#   endif

        shaderUploader->submit(worker, shaderUploads);
        updateShaderViews(worker, drawBuffers, outputBuffers, shaderViewRtEnabled);
    }

    void FramebufferRenderer::advanceFrame(bool rtEnabled) {
        // Count suppressed exposure between transition/heartbeat snapshots;
        // issuing mask draw commands alone cannot establish visible motion.
        if (!wr64MotionActors.empty() && (!std::isfinite(wr64MotionTimeScale) ||
            !std::isfinite(wr64MotionShutter) || wr64MotionTimeScale <= 0 || wr64MotionShutter <= 0))
            ++wr64MotionNoExposureFrames;
        // Readiness alone does not prove the HUD boundary was reached or a mask
        // draw/resolve was recorded. Report the final outcome, including frames
        // with no admitted actors, without writing a line for every frame.
        if (wr64MotionDiagnostic.enabled && wr64RTDiagnosticEnabled()) {
            const uint32_t state = uint32_t(!wr64MotionActors.empty()) |
                (uint32_t(wr64MotionPrepared) << 1) | (uint32_t(wr64MotionDiagnostic.executed) << 2) |
                (uint32_t(wr64MotionOrderRejected) << 3) | (uint32_t(wr64MotionDiagnostic.menu) << 4) |
                (uint32_t(wr64MotionDiagnostic.paused) << 5) |
                (uint32_t(wr64MotionDiagnostic.missingPipelines != 0) << 6) |
                (uint32_t(wr64MotionDiagnostic.emptyScissors != 0) << 7);
            const bool changed = state != wr64MotionPreviousState || !wr64MotionPreviousReason ||
                std::strcmp(wr64MotionPreviousReason, wr64MotionDiagnostic.reason) != 0;
            if (wr64MotionDiagnosticFrames++ < 4 || changed || wr64MotionDiagnosticFrames % 3600 == 0) {
                char details[832];
                std::snprintf(details, sizeof(details),
                    "frame=%llu workload=%llu present=%llu course=%u view=%u framebuffer=%u/%u eligible=%u actors=%zu ready=%u executed=%u mask_draws=%u missing_pipelines=%u empty_scissors=%u hud_boundary=%u order_rejected=%u menu=%u paused=%u reason=%s camera=%g,%g,%g time_scale=%g shutter_frames=%g no_exposure_frames=%llu exposure_seconds=0.011111 max_radius=16 method=actor-tiles",
                    (unsigned long long)wr64MotionDiagnosticFrames, (unsigned long long)wr64MotionDiagnostic.workload,
                    (unsigned long long)wr64MotionDiagnostic.present, wr64MotionDiagnostic.course, wr64MotionDiagnostic.view,
                    wr64RTViews[0].framebuffer, framebufferCount, unsigned(!wr64MotionActors.empty()), wr64MotionActors.size(),
                    unsigned(wr64MotionPrepared), unsigned(wr64MotionDiagnostic.executed), wr64MotionDiagnostic.maskDraws,
                    wr64MotionDiagnostic.missingPipelines, wr64MotionDiagnostic.emptyScissors, wr64MotionBoundary,
                    unsigned(wr64MotionOrderRejected), unsigned(wr64MotionDiagnostic.menu), unsigned(wr64MotionDiagnostic.paused),
                    wr64MotionDiagnostic.reason, double(wr64RTViews[0].params.camera.x), double(wr64RTViews[0].params.camera.y), double(wr64RTViews[0].params.camera.z),
                    double(wr64MotionTimeScale), double(wr64MotionShutter), (unsigned long long)wr64MotionNoExposureFrames);
                wr64RTDiagnostic("object-motion", details);
            }
            wr64MotionPreviousState = state;
            wr64MotionPreviousReason = wr64MotionDiagnostic.reason;
        }
        frameParams.frameCount++;

#   if RT_ENABLED
        if (rtEnabled) {
            rtResources->swapBuffers = !rtResources->swapBuffers;
            rtResources->skipReprojection = false;
        }
#   endif
    }
};

/*
void RT64::View::renderIm3d() {
    if (Im3d::GetDrawListCount() > 0) {
        commandList->SetGraphicsRootSignature(worker->device->getIm3dRootSignature());

        commandList->SetDescriptorHeaps(1, &descriptorHeap);
        commandList->SetGraphicsRootDescriptorTable(0, descriptorHeap->GetGPUDescriptorHandleForHeapStart());
        commandList->RSSetViewports(1, &rtViewport);
        commandList->RSSetScissorRects(1, &rtScissor);

        unsigned int totalVertexCount = 0;
        for (Im3d::U32 i = 0, n = Im3d::GetDrawListCount(); i < n; ++i) {
            auto &drawList = Im3d::GetDrawLists()[i];
            totalVertexCount += drawList.m_vertexCount;
        }

        if (totalVertexCount > 0) {
            // Release the previous vertex buffer if it should be bigger.
            if (!im3dVertexBuffer.IsNull() && (totalVertexCount > im3dVertexCount)) {
                im3dVertexBuffer.Release();
            }

            // Create the vertex buffer if it's empty.
            const UINT vertexBufferSize = totalVertexCount * sizeof(Im3d::VertexData);
            if (im3dVertexBuffer.IsNull()) {
                CD3DX12_RESOURCE_DESC uploadBufferDesc = CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize);
                im3dVertexBuffer = worker->device->allocateResource(D3D12_HEAP_TYPE_UPLOAD, &uploadBufferDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr);
                im3dVertexCount = totalVertexCount;
                im3dVertexBufferView.BufferLocation = im3dVertexBuffer.Get()->GetGPUVirtualAddress();
                im3dVertexBufferView.StrideInBytes = sizeof(Im3d::VertexData);
                im3dVertexBufferView.SizeInBytes = vertexBufferSize;
            }

            // Copy data to vertex buffer.
            UINT8 *pDataBegin;
            CD3DX12_RANGE readRange(0, 0);
            D3D12_CHECK(im3dVertexBuffer.Get()->Map(0, &readRange, reinterpret_cast<void **>(&pDataBegin)));
            for (Im3d::U32 i = 0, n = Im3d::GetDrawListCount(); i < n; ++i) {
                auto &drawList = Im3d::GetDrawLists()[i];
                size_t copySize = sizeof(Im3d::VertexData) * drawList.m_vertexCount;
                memcpy(pDataBegin, drawList.m_vertexData, copySize);
                pDataBegin += copySize;
            }

            im3dVertexBuffer.Get()->Unmap(0, nullptr);

            unsigned int vertexOffset = 0;
            for (Im3d::U32 i = 0, n = Im3d::GetDrawListCount(); i < n; ++i) {
                auto &drawList = Im3d::GetDrawLists()[i];
                commandList->IASetVertexBuffers(0, 1, &im3dVertexBufferView);
                switch (drawList.m_primType) {
                case Im3d::DrawPrimitive_Points:
                    commandList->SetPipelineState(worker->device->getIm3dPipelineStatePoint());
                    commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
                    break;
                case Im3d::DrawPrimitive_Lines:
                    commandList->SetPipelineState(worker->device->getIm3dPipelineStateLine());
                    commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
                    break;
                case Im3d::DrawPrimitive_Triangles:
                    commandList->SetPipelineState(worker->device->getIm3dPipelineStateTriangle());
                    commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                    break;
                default:
                    break;
                }

                commandList->DrawInstanced(drawList.m_vertexCount, 1, vertexOffset, 0);
                vertexOffset += drawList.m_vertexCount;
            }
        }
    }
}
*/

/*
namespace RT64 {
    class View {
    private:
        // Im3D
        AllocatedResource im3dVertexBuffer;
        D3D12_VERTEX_BUFFER_VIEW im3dVertexBufferView;
        unsigned int im3dVertexCount;
    };
};
*/
