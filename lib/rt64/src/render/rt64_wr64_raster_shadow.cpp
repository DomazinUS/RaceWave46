#include "rt64_wr64_raster_shadow.h"
#include "rt64_raster_shader.h"
#include "common/rt64_wr64_async_cache.h"
#include "common/rt64_wr64_rt_diagnostics.h"
#include <chrono>
#include <cstdio>
#include <vector>
#ifdef _WIN32
#include "plume_d3d12.h"
#include "shaders/Wr64RasterShadowCaptureVS.hlsl.dxil.h"
#include "shaders/Wr64RasterShadowCapturePS.hlsl.dxil.h"
#include "shaders/Wr64RasterShadowWorldPS.hlsl.dxil.h"
#include "shaders/Wr64RasterShadowWorldPSMS.hlsl.dxil.h"
#include "shaders/Wr64WorldShadowVS.hlsl.dxil.h"
#include "shaders/Wr64WaterReflectionVS.hlsl.dxil.h"
#include "shaders/Wr64RasterShadowWaterPS.hlsl.dxil.h"
#include "shaders/Wr64RasterShadowWaterPSMS.hlsl.dxil.h"
#include "shaders/Wr64RasterSkyWaterPSRasterShadow.hlsl.dxil.h"
#include "shaders/Wr64RasterSkyWaterPSRasterShadowMS.hlsl.dxil.h"
#include "shaders/Wr64WaterReflectionPSRasterShadow.hlsl.dxil.h"
#include "shaders/Wr64WaterReflectionPSRasterShadowMS.hlsl.dxil.h"
#include "shaders/Wr64WaterSkyReflectionPSRasterShadow.hlsl.dxil.h"
#include "shaders/Wr64WaterSkyReflectionPSRasterShadowMS.hlsl.dxil.h"
#include "shaders/Wr64CachedSkyRTObjectsPSRasterShadow.hlsl.dxil.h"
#include "shaders/Wr64CachedSkyRTObjectsPSRasterShadowMS.hlsl.dxil.h"
#include "shaders/Wr64RayTracedSkyOnlyPSRasterShadow.hlsl.dxil.h"
#include "shaders/Wr64RayTracedSkyOnlyPSRasterShadowMS.hlsl.dxil.h"
#endif

namespace RT64 {
    class Wr64RasterShadowPipelineCache {
        static constexpr size_t MaxConfigurations = 32, KeysPerConfiguration = 73;
        static constexpr uint32_t CaptureKey = 72;
        struct Configuration {
            size_t slot = 0;
            RenderDevice *device = nullptr;
            const RenderPipelineLayout *layout = nullptr;
            RenderMultisampling samples{};
            Wr64RasterShadowWaterMode mode = Wr64RasterShadowWaterMode::Native;
            bool hdr = false, attempted = false;
            std::unique_ptr<RenderShader> waterVS, waterPS, worldVS, worldPS, captureVS, capturePS;
        };
        struct Result { std::unique_ptr<RenderPipeline> pipeline; };
        bool async_ = true, capacityReported_ = false;
        std::vector<std::shared_ptr<Configuration>> configurations_;
        std::shared_ptr<Configuration> selected_;
        Wr64AsyncCache<Result, MaxConfigurations * KeysPerConfiguration> builds_;
        static bool sameSamples(const RenderMultisampling &a, const RenderMultisampling &b) {
            if (a.sampleCount != b.sampleCount || a.sampleLocationsEnabled != b.sampleLocationsEnabled) return false;
            if (a.sampleLocationsEnabled)
                for (size_t i = 0; i < 16; ++i) if (a.sampleLocations[i] != b.sampleLocations[i]) return false;
            return true;
        }
        static bool shaders(Configuration &c) {
            if (!c.attempted) {
                c.attempted = true;
#ifdef _WIN32
                const bool ms = c.samples.sampleCount > 1;
                auto vs = [&](const void *blob, size_t size) { return c.device->createShader(blob, size, "VSMain", RenderShaderFormat::DXIL); };
                auto ps = [&](const void *blob, size_t size) { return c.device->createShader(blob, size, "PSMain", RenderShaderFormat::DXIL); };
                c.waterVS = vs(Wr64WaterReflectionVSBlobDXIL, sizeof(Wr64WaterReflectionVSBlobDXIL));
                c.worldVS = vs(Wr64WorldShadowVSBlobDXIL, sizeof(Wr64WorldShadowVSBlobDXIL));
                c.captureVS = vs(Wr64RasterShadowCaptureVSBlobDXIL, sizeof(Wr64RasterShadowCaptureVSBlobDXIL));
                c.capturePS = ps(Wr64RasterShadowCapturePSBlobDXIL, sizeof(Wr64RasterShadowCapturePSBlobDXIL));
                c.worldPS = ms ? ps(Wr64RasterShadowWorldPSMSBlobDXIL, sizeof(Wr64RasterShadowWorldPSMSBlobDXIL)) :
                    ps(Wr64RasterShadowWorldPSBlobDXIL, sizeof(Wr64RasterShadowWorldPSBlobDXIL));
                switch (c.mode) {
                case Wr64RasterShadowWaterMode::Native:
                    c.waterPS = ms ? ps(Wr64RasterShadowWaterPSMSBlobDXIL, sizeof(Wr64RasterShadowWaterPSMSBlobDXIL)) : ps(Wr64RasterShadowWaterPSBlobDXIL, sizeof(Wr64RasterShadowWaterPSBlobDXIL));
                    break;
                case Wr64RasterShadowWaterMode::RasterSky:
                    c.waterPS = ms ? ps(Wr64RasterSkyWaterPSRasterShadowMSBlobDXIL, sizeof(Wr64RasterSkyWaterPSRasterShadowMSBlobDXIL)) : ps(Wr64RasterSkyWaterPSRasterShadowBlobDXIL, sizeof(Wr64RasterSkyWaterPSRasterShadowBlobDXIL));
                    break;
                case Wr64RasterShadowWaterMode::RTObjects:
                    c.waterPS = ms ? ps(Wr64WaterReflectionPSRasterShadowMSBlobDXIL, sizeof(Wr64WaterReflectionPSRasterShadowMSBlobDXIL)) : ps(Wr64WaterReflectionPSRasterShadowBlobDXIL, sizeof(Wr64WaterReflectionPSRasterShadowBlobDXIL));
                    break;
                case Wr64RasterShadowWaterMode::RTSky:
                    c.waterPS = ms ? ps(Wr64WaterSkyReflectionPSRasterShadowMSBlobDXIL, sizeof(Wr64WaterSkyReflectionPSRasterShadowMSBlobDXIL)) : ps(Wr64WaterSkyReflectionPSRasterShadowBlobDXIL, sizeof(Wr64WaterSkyReflectionPSRasterShadowBlobDXIL));
                    break;
                case Wr64RasterShadowWaterMode::RTObjectsRasterSky:
                    c.waterPS = ms ? ps(Wr64CachedSkyRTObjectsPSRasterShadowMSBlobDXIL, sizeof(Wr64CachedSkyRTObjectsPSRasterShadowMSBlobDXIL)) : ps(Wr64CachedSkyRTObjectsPSRasterShadowBlobDXIL, sizeof(Wr64CachedSkyRTObjectsPSRasterShadowBlobDXIL));
                    break;
                case Wr64RasterShadowWaterMode::RTSkyOnly:
                    c.waterPS = ms ? ps(Wr64RayTracedSkyOnlyPSRasterShadowMSBlobDXIL, sizeof(Wr64RayTracedSkyOnlyPSRasterShadowMSBlobDXIL)) : ps(Wr64RayTracedSkyOnlyPSRasterShadowBlobDXIL, sizeof(Wr64RayTracedSkyOnlyPSRasterShadowBlobDXIL));
                    break;
                default: break;
                }
#endif
            }
            return c.waterVS && c.waterPS && c.worldVS && c.worldPS && c.captureVS && c.capturePS;
        }
        const Result *request(uint32_t variant) {
            if (!selected_ || variant >= KeysPerConfiguration) return nullptr;
            auto c = selected_;
            return builds_.get(c->slot * KeysPerConfiguration + variant, [c, variant] {
                const auto begin = std::chrono::steady_clock::now();
                std::unique_ptr<Result> result;
                try {
                    if (shaders(*c)) {
                        result = std::make_unique<Result>();
                        if (variant == CaptureKey) {
                            // Match native stream slots while projecting positions from t27.
                            static const RenderInputSlot slots[] = {
                                RenderInputSlot(0, 16), RenderInputSlot(1, 8), RenderInputSlot(2, 16) };
                            static const RenderInputElement elements[] = {
                                RenderInputElement("POSITION", 0, 0, RenderFormat::R32G32B32A32_FLOAT, 0, 0),
                                RenderInputElement("TEXCOORD", 0, 1, RenderFormat::R32G32_FLOAT, 1, 0),
                                RenderInputElement("COLOR", 0, 2, RenderFormat::R32G32B32A32_FLOAT, 2, 0) };
                            RenderGraphicsPipelineDesc d;
                            d.pipelineLayout = c->layout; d.vertexShader = c->captureVS.get(); d.pixelShader = c->capturePS.get();
                            d.inputSlots = slots; d.inputSlotsCount = uint32_t(std::size(slots));
                            d.inputElements = elements; d.inputElementsCount = uint32_t(std::size(elements));
                            d.renderTargetBlend[0] = RenderBlendDesc::Copy();
                            d.renderTargetFormat[0] = RenderFormat::R32_FLOAT; d.renderTargetCount = 1;
                            d.depthTargetFormat = RenderFormat::D32_FLOAT;
                            d.depthEnabled = true; d.depthWriteEnabled = true;
                            d.depthFunction = RenderComparisonFunction::LESS;
                            d.depthClipEnabled = true; d.cullMode = RenderCullMode::NONE;
                            d.primitiveTopology = RenderPrimitiveTopology::TRIANGLE_LIST;
                            result->pipeline = c->device->createGraphicsPipeline(d);
                        }
                        else {
                            const bool world = variant >= 8;
                            const uint32_t flags = world ? variant - 8 : variant;
                            PipelineCreation p{};
                            p.device = c->device; p.pipelineLayout = c->layout;
                            p.vertexShader = world ? c->worldVS.get() : c->waterVS.get();
                            p.pixelShader = world ? c->worldPS.get() : c->waterPS.get();
                            p.zCmp = (flags & 1) != 0; p.zUpd = (flags & 2) != 0; p.cvgAdd = (flags & 4) != 0;
                            p.culling = world && (flags & 8) != 0;
                            p.NoN = !world || (flags & 16) != 0;
                            p.alphaBlend = !world || (flags & 32) != 0;
                            p.usesHDR = c->hdr; p.multisampling = c->samples;
                            result->pipeline = RasterShader::createPipeline(p);
                        }
                        bool valid = result->pipeline != nullptr;
#ifdef _WIN32
                        if (valid) valid = static_cast<D3D12GraphicsPipeline *>(result->pipeline.get())->d3d != nullptr;
#endif
                        if (!valid) result.reset();
                    }
                } catch (...) { result.reset(); }
                char details[160];
                const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count();
                std::snprintf(details, sizeof(details), "mode=%u samples=%u hdr=%u variant=%u ready=%u elapsed_ms=%lld",
                    unsigned(c->mode), unsigned(c->samples.sampleCount), unsigned(c->hdr), variant, unsigned(bool(result)), static_cast<long long>(elapsed));
                wr64RTDiagnostic("raster-shadow-pso", details);
                return result;
            }, !async_);
        }
    public:
        bool prepare(RenderDevice *device, const RenderPipelineLayout *layout, const RenderMultisampling &samples,
            bool hdr, bool async, Wr64RasterShadowWaterMode mode) {
            selected_.reset();
#ifndef _WIN32
            return false;
#else
            if (!device || !layout || unsigned(mode) > unsigned(Wr64RasterShadowWaterMode::RTSkyOnly)) return false;
            async_ = async;
            for (const auto &c : configurations_) {
                if (c->device == device && c->layout == layout && c->hdr == hdr && c->mode == mode && sameSamples(c->samples, samples)) {
                    selected_ = c; break;
                }
            }
            if (!selected_) {
                if (configurations_.size() >= MaxConfigurations) {
                    if (!capacityReported_) wr64RTDiagnostic("raster-shadow-pso", "failed reason=configuration-capacity");
                    capacityReported_ = true; return false;
                }
                auto c = std::make_shared<Configuration>();
                c->slot = configurations_.size(); c->device = device; c->layout = layout;
                c->samples = samples; c->hdr = hdr; c->mode = mode;
                configurations_.push_back(c); selected_ = std::move(c);
            }
            const bool captureReady = request(CaptureKey) != nullptr;
            if (async_) return true;
            bool ready = captureReady;
            for (uint32_t i = 0; i < CaptureKey; ++i) ready = (request(i) != nullptr) && ready;
            return ready;
#endif
        }
        const RenderPipeline *get(uint32_t key) {
            const auto *result = request(key); return result ? result->pipeline.get() : nullptr;
        }
        const RenderPipeline *water(Wr64RasterShadowWaterMode mode, uint32_t key) {
            return selected_ && selected_->mode == mode && key < 8 ? get(key) : nullptr;
        }
        Wr64RTPrewarmStatus prewarm() {
            if (!selected_) return Wr64RTPrewarmStatus::Failed;
            const bool previous = async_; async_ = true;
            bool pending = false, failed = false;
            for (uint32_t key = 0; key < KeysPerConfiguration; ++key) {
                request(key);
                const auto state = builds_.state(selected_->slot * KeysPerConfiguration + key);
                failed |= state == decltype(builds_)::State::Failed;
                pending |= state == decltype(builds_)::State::Empty || state == decltype(builds_)::State::Queued;
            }
            async_ = previous;
            return failed ? Wr64RTPrewarmStatus::Failed : pending ? Wr64RTPrewarmStatus::Pending : Wr64RTPrewarmStatus::Ready;
        }
        void waitForPending() { builds_.waitForPending(); }
        void reset() { builds_.reset(); selected_.reset(); configurations_.clear(); capacityReported_ = false; }
    };

    Wr64RasterShadowPipelines::Wr64RasterShadowPipelines() : cache_(std::make_unique<Wr64RasterShadowPipelineCache>()) { }
    Wr64RasterShadowPipelines::~Wr64RasterShadowPipelines() = default;
    bool Wr64RasterShadowPipelines::prepare(RenderDevice *device, const RenderPipelineLayout *layout,
        const RenderMultisampling &samples, bool hdr, bool async, Wr64RasterShadowWaterMode mode) {
        return cache_->prepare(device, layout, samples, hdr, async, mode);
    }
    const RenderPipeline *Wr64RasterShadowPipelines::capture() { return cache_->get(72); }
    const RenderPipeline *Wr64RasterShadowPipelines::getWater(Wr64RasterShadowWaterMode mode, bool compare, bool write, bool coverage) {
        return cache_->water(mode, uint32_t(compare) | (uint32_t(write) << 1) | (uint32_t(coverage) << 2));
    }
    const RenderPipeline *Wr64RasterShadowPipelines::nativeWater(bool compare, bool write, bool coverage) {
        return getWater(Wr64RasterShadowWaterMode::Native, compare, write, coverage);
    }
    const RenderPipeline *Wr64RasterShadowPipelines::world(bool compare, bool write, bool coverage, bool culling, bool NoN, bool alphaBlend) {
        return cache_->get(8 + (uint32_t(compare) | (uint32_t(write) << 1) | (uint32_t(coverage) << 2) |
            (uint32_t(culling) << 3) | (uint32_t(NoN) << 4) | (uint32_t(alphaBlend) << 5)));
    }
    Wr64RTPrewarmStatus Wr64RasterShadowPipelines::prewarm() { return cache_->prewarm(); }
    void Wr64RasterShadowPipelines::waitForPending() { cache_->waitForPending(); }
    void Wr64RasterShadowPipelines::reset() { cache_->reset(); }

    bool Wr64RasterShadowTarget::ensure(RenderWorker *worker, uint32_t size) {
#ifndef _WIN32
        return false;
#else
        if (!worker || !worker->device || size == 0 || size > 4096) return false;
        if (device_ == worker->device && size_ == size && color_ && depth_ && framebuffer_) return true;
        try {
            auto color = worker->device->createTexture(RenderTextureDesc::ColorTarget(size, size, RenderFormat::R32_FLOAT));
            auto depth = worker->device->createTexture(RenderTextureDesc::DepthTarget(size, size, RenderFormat::D32_FLOAT));
            if (!color || !depth || !static_cast<D3D12Texture *>(color.get())->d3d || !static_cast<D3D12Texture *>(depth.get())->d3d) return false;
            const RenderTexture *attachment = color.get();
            auto framebuffer = worker->device->createFramebuffer(RenderFramebufferDesc(&attachment, 1, depth.get()));
            if (!framebuffer) return false;
            color->setName("Wave Race raster shadow map"); depth->setName("Wave Race raster shadow depth");
            framebuffer_.reset(); color_ = std::move(color); depth_ = std::move(depth); framebuffer_ = std::move(framebuffer);
            device_ = worker->device; size_ = size; return true;
        } catch (...) { return false; }
#endif
    }
    void Wr64RasterShadowTarget::reset() {
        framebuffer_.reset(); color_.reset(); depth_.reset(); device_ = nullptr; size_ = 0;
    }
}
