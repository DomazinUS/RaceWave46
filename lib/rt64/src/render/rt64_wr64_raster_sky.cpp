#include "rt64_wr64_raster_sky.h"
#include "rt64_raster_shader.h"
#include "common/rt64_wr64_async_cache.h"
#include "common/rt64_wr64_rt_diagnostics.h"

#include <chrono>
#include <cstdio>
#include <vector>

#ifdef _WIN32
#include "plume_d3d12.h"
#include "shaders/FullScreenVS.hlsl.dxil.h"
#include "shaders/Wr64WaterReflectionVS.hlsl.dxil.h"
#include "shaders/Wr64RasterSkyCapturePS.hlsl.dxil.h"
#include "shaders/Wr64RasterSkyWaterPS.hlsl.dxil.h"
#include "shaders/Wr64RasterSkyWaterPSMS.hlsl.dxil.h"
#include "shaders/Wr64CachedSkyRTObjectsPS.hlsl.dxil.h"
#include "shaders/Wr64CachedSkyRTObjectsPSMS.hlsl.dxil.h"
#include "shaders/Wr64RayTracedSkyOnlyPS.hlsl.dxil.h"
#include "shaders/Wr64RayTracedSkyOnlyPSMS.hlsl.dxil.h"
#endif

namespace RT64 {
    class Wr64RasterSkyPipelineCache {
        static constexpr size_t MaxConfigurations = 32, KeysPerConfiguration = 9;
        struct Configuration {
            size_t slot = 0;
            RenderDevice *device = nullptr;
            const RenderPipelineLayout *layout = nullptr;
            RenderMultisampling samples{};
            Wr64SkyWaterMode mode = Wr64SkyWaterMode::RasterOnly;
            bool hdr = false, shadersAttempted = false;
            // Only this cache's single worker accesses shader initialization.
            std::unique_ptr<RenderShader> waterVS, waterPS, captureVS, capturePS;
        };
        struct Result { std::unique_ptr<RenderPipeline> pipeline; };
        bool async_ = true, capacityReported_ = false;
        std::vector<std::shared_ptr<Configuration>> configurations_;
        std::shared_ptr<Configuration> selected_;
        // Worker/results must be destroyed before their configuration shaders.
        Wr64AsyncCache<Result, MaxConfigurations * KeysPerConfiguration> builds_;

        static bool sameSamples(const RenderMultisampling &a, const RenderMultisampling &b) {
            if (a.sampleCount != b.sampleCount || a.sampleLocationsEnabled != b.sampleLocationsEnabled) return false;
            if (a.sampleLocationsEnabled)
                for (size_t i = 0; i < 16; ++i) if (a.sampleLocations[i] != b.sampleLocations[i]) return false;
            return true;
        }

        static bool prepareShaders(Configuration &config) {
            const bool cachedSky = config.mode != Wr64SkyWaterMode::RayTracedSkyOnly;
            if (config.shadersAttempted)
                return config.waterVS && config.waterPS && (!cachedSky || (config.captureVS && config.capturePS));
            config.shadersAttempted = true;
#ifdef _WIN32
            const bool ms = config.samples.sampleCount > 1;
            config.waterVS = config.device->createShader(Wr64WaterReflectionVSBlobDXIL,
                sizeof(Wr64WaterReflectionVSBlobDXIL), "VSMain", RenderShaderFormat::DXIL);
            const void *pixel = ms ? Wr64RasterSkyWaterPSMSBlobDXIL : Wr64RasterSkyWaterPSBlobDXIL;
            size_t pixelBytes = ms ? sizeof(Wr64RasterSkyWaterPSMSBlobDXIL) : sizeof(Wr64RasterSkyWaterPSBlobDXIL);
            if (config.mode == Wr64SkyWaterMode::CachedSkyWithRTObjects) {
                pixel = ms ? Wr64CachedSkyRTObjectsPSMSBlobDXIL : Wr64CachedSkyRTObjectsPSBlobDXIL;
                pixelBytes = ms ? sizeof(Wr64CachedSkyRTObjectsPSMSBlobDXIL) : sizeof(Wr64CachedSkyRTObjectsPSBlobDXIL);
            }
            else if (config.mode == Wr64SkyWaterMode::RayTracedSkyOnly) {
                pixel = ms ? Wr64RayTracedSkyOnlyPSMSBlobDXIL : Wr64RayTracedSkyOnlyPSBlobDXIL;
                pixelBytes = ms ? sizeof(Wr64RayTracedSkyOnlyPSMSBlobDXIL) : sizeof(Wr64RayTracedSkyOnlyPSBlobDXIL);
            }
            config.waterPS = config.device->createShader(pixel, pixelBytes, "PSMain", RenderShaderFormat::DXIL);
            if (cachedSky) {
                config.captureVS = config.device->createShader(FullScreenVSBlobDXIL,
                    sizeof(FullScreenVSBlobDXIL), "VSMain", RenderShaderFormat::DXIL);
                config.capturePS = config.device->createShader(Wr64RasterSkyCapturePSBlobDXIL,
                    sizeof(Wr64RasterSkyCapturePSBlobDXIL), "PSMain", RenderShaderFormat::DXIL);
            }
            return config.waterVS && config.waterPS && (!cachedSky || (config.captureVS && config.capturePS));
#else
            return false;
#endif
        }

        const Result *request(uint32_t variant) {
            if (!selected_ || variant >= KeysPerConfiguration) return nullptr;
            if (variant == 8 && selected_->mode == Wr64SkyWaterMode::RayTracedSkyOnly) return nullptr;
            auto config = selected_;
            return builds_.get(config->slot * KeysPerConfiguration + variant, [config, variant] {
                const auto begin = std::chrono::steady_clock::now();
                std::unique_ptr<Result> result;
                try {
                    if (prepareShaders(*config)) {
                        result = std::make_unique<Result>();
                        if (variant == 8) {
                            RenderGraphicsPipelineDesc desc;
                            desc.pipelineLayout = config->layout;
                            desc.vertexShader = config->captureVS.get();
                            desc.pixelShader = config->capturePS.get();
                            desc.renderTargetBlend[0] = RenderBlendDesc::Copy();
                            desc.renderTargetFormat[0] = RenderFormat::R16G16B16A16_FLOAT;
                            desc.renderTargetCount = 1;
                            desc.cullMode = RenderCullMode::NONE;
                            desc.depthEnabled = false;
                            desc.depthWriteEnabled = false;
                            desc.depthClipEnabled = false;
                            desc.primitiveTopology = RenderPrimitiveTopology::TRIANGLE_LIST;
                            result->pipeline = config->device->createGraphicsPipeline(desc);
                        }
                        else {
                            PipelineCreation c{};
                            c.device = config->device; c.pipelineLayout = config->layout;
                            c.vertexShader = config->waterVS.get(); c.pixelShader = config->waterPS.get();
                            c.alphaBlend = true; c.culling = false; c.NoN = true;
                            c.zCmp = (variant & 1) != 0; c.zUpd = (variant & 2) != 0;
                            c.cvgAdd = (variant & 4) != 0; c.usesHDR = config->hdr;
                            c.multisampling = config->samples;
                            result->pipeline = RasterShader::createPipeline(c);
                        }
                        bool ready = result->pipeline != nullptr;
#ifdef _WIN32
                        if (ready) ready = static_cast<D3D12GraphicsPipeline *>(result->pipeline.get())->d3d != nullptr;
#endif
                        if (!ready) result.reset();
                    }
                } catch (...) { result.reset(); }
                char details[160];
                const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::steady_clock::now() - begin).count();
                std::snprintf(details, sizeof(details), "pass=%s mode=%u samples=%u hdr=%u variant=%u ready=%u elapsed_ms=%lld",
                    variant == 8 ? "capture" : "water", unsigned(config->mode), unsigned(config->samples.sampleCount), unsigned(config->hdr),
                    variant, unsigned(bool(result)), static_cast<long long>(elapsed));
                wr64RTDiagnostic("raster-sky-pso", details);
                return result;
            }, !async_);
        }

    public:
        bool prepare(RenderDevice *device, const RenderPipelineLayout *layout,
            const RenderMultisampling &samples, bool hdr, bool async, Wr64SkyWaterMode mode) {
            selected_.reset();
#ifndef _WIN32
            return false;
#else
            if (!device || !layout) return false;
            if (mode != Wr64SkyWaterMode::RasterOnly && mode != Wr64SkyWaterMode::CachedSkyWithRTObjects &&
                mode != Wr64SkyWaterMode::RayTracedSkyOnly) return false;
            async_ = async;
            for (const auto &config : configurations_) {
                if (config->device == device && config->layout == layout && config->hdr == hdr && config->mode == mode &&
                    sameSamples(config->samples, samples)) {
                    selected_ = config;
                    break;
                }
            }
            if (!selected_) {
                if (configurations_.size() >= MaxConfigurations) {
                    if (!capacityReported_) wr64RTDiagnostic("raster-sky-pso", "failed reason=configuration-capacity");
                    capacityReported_ = true;
                    return false;
                }
                auto config = std::make_shared<Configuration>();
                config->slot = configurations_.size(); config->device = device; config->layout = layout;
                config->samples = samples; config->hdr = hdr; config->mode = mode;
                configurations_.push_back(config);
                selected_ = std::move(config);
            }
            const bool captureReady = mode == Wr64SkyWaterMode::RayTracedSkyOnly || request(8) != nullptr;
            if (async_) return true;
            bool ready = captureReady;
            for (uint32_t i = 0; i < 8; ++i) ready = (request(i) != nullptr) && ready;
            return ready;
#endif
        }
        const RenderPipeline *get(uint32_t variant) {
            const auto *result = request(variant);
            return result ? result->pipeline.get() : nullptr;
        }
        Wr64RTPrewarmStatus prewarm() {
            if (!selected_) return Wr64RTPrewarmStatus::Failed;
            const bool previousAsync = async_;
            async_ = true;
            bool pending = false, failed = false;
            const uint32_t count = selected_->mode == Wr64SkyWaterMode::RayTracedSkyOnly ? 8u : 9u;
            for (uint32_t variant = 0; variant < count; ++variant) {
                request(variant);
                const auto state = builds_.state(selected_->slot * KeysPerConfiguration + variant);
                failed |= state == decltype(builds_)::State::Failed;
                pending |= state == decltype(builds_)::State::Empty || state == decltype(builds_)::State::Queued;
            }
            async_ = previousAsync;
            return failed ? Wr64RTPrewarmStatus::Failed :
                (pending ? Wr64RTPrewarmStatus::Pending : Wr64RTPrewarmStatus::Ready);
        }
        void waitForPending() { builds_.waitForPending(); }
        void reset() {
            builds_.reset();
            selected_.reset(); configurations_.clear(); capacityReported_ = false;
        }
    };

    Wr64RasterSkyPipelines::Wr64RasterSkyPipelines() : cache_(std::make_unique<Wr64RasterSkyPipelineCache>()) { }
    Wr64RasterSkyPipelines::~Wr64RasterSkyPipelines() = default;
    bool Wr64RasterSkyPipelines::prepare(RenderDevice *device, const RenderPipelineLayout *layout,
        const RenderMultisampling &multisampling, bool hdr, bool async, Wr64SkyWaterMode mode) {
        return cache_->prepare(device, layout, multisampling, hdr, async, mode);
    }
    const RenderPipeline *Wr64RasterSkyPipelines::get(bool compare, bool write, bool add) {
        return cache_->get(uint32_t(compare) | (uint32_t(write) << 1) | (uint32_t(add) << 2));
    }
    const RenderPipeline *Wr64RasterSkyPipelines::capture() { return cache_->get(8); }
    Wr64RTPrewarmStatus Wr64RasterSkyPipelines::prewarm() { return cache_->prewarm(); }
    void Wr64RasterSkyPipelines::waitForPending() { cache_->waitForPending(); }
    void Wr64RasterSkyPipelines::reset() { cache_->reset(); }

    bool Wr64RasterSkyTarget::ensure(RenderWorker *worker, uint32_t width, uint32_t height) {
#ifndef _WIN32
        return false;
#else
        if (!worker || !worker->device || width == 0 || height == 0 || width > 4096 || height > 2048) return false;
        if (texture_ && framebuffer_ && device_ == worker->device && width_ == width && height_ == height) return true;
        try {
            auto texture = worker->device->createTexture(RenderTextureDesc::ColorTarget(width, height, RenderFormat::R16G16B16A16_FLOAT));
            if (!texture || !static_cast<D3D12Texture *>(texture.get())->d3d) return false;
            const RenderTexture *attachment = texture.get();
            auto framebuffer = worker->device->createFramebuffer(RenderFramebufferDesc(&attachment, 1));
            if (!framebuffer) return false;
            texture->setName("Wave Race raster sky cache");
            // Release the old framebuffer before its texture.
            framebuffer_.reset();
            texture_ = std::move(texture); framebuffer_ = std::move(framebuffer);
            device_ = worker->device; width_ = width; height_ = height;
            return true;
        } catch (...) { return false; }
#endif
    }
    void Wr64RasterSkyTarget::reset() {
        framebuffer_.reset(); texture_.reset(); device_ = nullptr; width_ = height_ = 0;
    }
}
