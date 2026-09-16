#include "rt64_wr64_raster_reflection.h"
#include "rt64_raster_shader.h"
#include "common/rt64_wr64_async_cache.h"
#include "common/rt64_wr64_rt_diagnostics.h"
#include <chrono>
#include <cstdio>
#include <vector>
#ifdef _WIN32
#include "plume_d3d12.h"
#include "shaders/Wr64WaterReflectionVS.hlsl.dxil.h"
#include "shaders/Wr64RasterReflectionCaptureVS.hlsl.dxil.h"
#include "shaders/Wr64RasterReflectionCapturePS.hlsl.dxil.h"
#include "shaders/Wr64RasterReflectionWaterPS.hlsl.dxil.h"
#include "shaders/Wr64RasterReflectionWaterPSMS.hlsl.dxil.h"
#include "shaders/Wr64RasterReflectionWaterShadowPS.hlsl.dxil.h"
#include "shaders/Wr64RasterReflectionWaterShadowPSMS.hlsl.dxil.h"
#include "shaders/Wr64RasterReflectionWaterSkyPS.hlsl.dxil.h"
#include "shaders/Wr64RasterReflectionWaterSkyPSMS.hlsl.dxil.h"
#include "shaders/Wr64RasterReflectionWaterSkyShadowPS.hlsl.dxil.h"
#include "shaders/Wr64RasterReflectionWaterSkyShadowPSMS.hlsl.dxil.h"
#include "shaders/Wr64RasterReflectionWaterRTSkyPS.hlsl.dxil.h"
#include "shaders/Wr64RasterReflectionWaterRTSkyPSMS.hlsl.dxil.h"
#include "shaders/Wr64RasterReflectionWaterRTSkyShadowPS.hlsl.dxil.h"
#include "shaders/Wr64RasterReflectionWaterRTSkyShadowPSMS.hlsl.dxil.h"
#endif

namespace RT64 {
    class Wr64RasterReflectionPipelineCache {
        static constexpr size_t MaxConfigurations = 64, KeysPerConfiguration = 10;
        struct Configuration {
            size_t slot = 0;
            RenderDevice *device = nullptr;
            const RenderPipelineLayout *layout = nullptr;
            RenderMultisampling samples{};
            Wr64RasterReflectionSkyMode sky = Wr64RasterReflectionSkyMode::SkyOff;
            bool hdr = false, rasterShadows = false, attempted = false;
            // Shader initialization runs only on this cache's single worker.
            std::unique_ptr<RenderShader> waterVS, waterPS, captureVS, capturePS;
        };
        struct Result { std::unique_ptr<RenderPipeline> pipeline; };
        bool async_ = true, capacityReported_ = false;
        std::vector<std::shared_ptr<Configuration>> configurations_;
        std::shared_ptr<Configuration> selected_;
        // Destroy worker results before the configuration shaders they use.
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
                c.captureVS = vs(Wr64RasterReflectionCaptureVSBlobDXIL, sizeof(Wr64RasterReflectionCaptureVSBlobDXIL));
                c.capturePS = ps(Wr64RasterReflectionCapturePSBlobDXIL, sizeof(Wr64RasterReflectionCapturePSBlobDXIL));
#define WR64_PLANAR_PIXEL(NAME) c.waterPS = ms ? ps(NAME##MSBlobDXIL, sizeof(NAME##MSBlobDXIL)) : ps(NAME##BlobDXIL, sizeof(NAME##BlobDXIL))
                switch (c.sky) {
                case Wr64RasterReflectionSkyMode::SkyOff:
                    if (c.rasterShadows) { WR64_PLANAR_PIXEL(Wr64RasterReflectionWaterShadowPS); }
                    else { WR64_PLANAR_PIXEL(Wr64RasterReflectionWaterPS); }
                    break;
                case Wr64RasterReflectionSkyMode::RasterSky:
                    if (c.rasterShadows) { WR64_PLANAR_PIXEL(Wr64RasterReflectionWaterSkyShadowPS); }
                    else { WR64_PLANAR_PIXEL(Wr64RasterReflectionWaterSkyPS); }
                    break;
                case Wr64RasterReflectionSkyMode::RTSkyOnly:
                    if (c.rasterShadows) { WR64_PLANAR_PIXEL(Wr64RasterReflectionWaterRTSkyShadowPS); }
                    else { WR64_PLANAR_PIXEL(Wr64RasterReflectionWaterRTSkyPS); }
                    break;
                default: break;
                }
#undef WR64_PLANAR_PIXEL
#endif
            }
            return c.waterVS && c.waterPS && c.captureVS && c.capturePS;
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
                        if (variant >= 8) {
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
                            d.renderTargetFormat[0] = RenderFormat::R16G16B16A16_FLOAT; d.renderTargetCount = 1;
                            d.depthTargetFormat = RenderFormat::D32_FLOAT;
                            d.depthEnabled = true; d.depthWriteEnabled = true;
                            d.depthFunction = RenderComparisonFunction::LESS; d.depthClipEnabled = true;
                            // Mirroring reverses the native FRONT-cull winding.
                            d.cullMode = variant == 9 ? RenderCullMode::BACK : RenderCullMode::NONE;
                            d.primitiveTopology = RenderPrimitiveTopology::TRIANGLE_LIST;
                            result->pipeline = c->device->createGraphicsPipeline(d);
                        }
                        else {
                            PipelineCreation p{};
                            p.device = c->device; p.pipelineLayout = c->layout;
                            p.vertexShader = c->waterVS.get(); p.pixelShader = c->waterPS.get();
                            p.zCmp = (variant & 1) != 0; p.zUpd = (variant & 2) != 0; p.cvgAdd = (variant & 4) != 0;
                            p.culling = false; p.NoN = true; p.alphaBlend = true;
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
                char details[192];
                const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count();
                std::snprintf(details, sizeof(details), "sky=%u raster_shadows=%u samples=%u hdr=%u variant=%u ready=%u elapsed_ms=%lld",
                    unsigned(c->sky), unsigned(c->rasterShadows), unsigned(c->samples.sampleCount), unsigned(c->hdr),
                    variant, unsigned(bool(result)), static_cast<long long>(elapsed));
                wr64RTDiagnostic("raster-reflection-pso", details);
                return result;
            }, !async_);
        }
    public:
        bool prepare(RenderDevice *device, const RenderPipelineLayout *layout, const RenderMultisampling &samples,
            bool hdr, bool async, Wr64RasterReflectionSkyMode sky, bool rasterShadows) {
            selected_.reset();
#ifndef _WIN32
            return false;
#else
            if (!device || !layout || unsigned(sky) > unsigned(Wr64RasterReflectionSkyMode::RTSkyOnly)) return false;
            async_ = async;
            for (const auto &c : configurations_) {
                if (c->device == device && c->layout == layout && c->hdr == hdr && c->sky == sky &&
                    c->rasterShadows == rasterShadows && sameSamples(c->samples, samples)) {
                    selected_ = c; break;
                }
            }
            if (!selected_) {
                if (configurations_.size() >= MaxConfigurations) {
                    if (!capacityReported_) wr64RTDiagnostic("raster-reflection-pso", "failed reason=configuration-capacity");
                    capacityReported_ = true; return false;
                }
                auto c = std::make_shared<Configuration>();
                c->slot = configurations_.size(); c->device = device; c->layout = layout;
                c->samples = samples; c->hdr = hdr; c->sky = sky; c->rasterShadows = rasterShadows;
                configurations_.push_back(c); selected_ = std::move(c);
            }
            bool ready = request(8) != nullptr;
            ready = (request(9) != nullptr) && ready;
            if (async_) return true;
            for (uint32_t i = 0; i < 8; ++i) ready = (request(i) != nullptr) && ready;
            return ready;
#endif
        }
        const RenderPipeline *get(uint32_t key) {
            const auto *result = request(key); return result ? result->pipeline.get() : nullptr;
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

    Wr64RasterReflectionPipelines::Wr64RasterReflectionPipelines() : cache_(std::make_unique<Wr64RasterReflectionPipelineCache>()) { }
    Wr64RasterReflectionPipelines::~Wr64RasterReflectionPipelines() = default;
    bool Wr64RasterReflectionPipelines::prepare(RenderDevice *device, const RenderPipelineLayout *layout,
        const RenderMultisampling &samples, bool hdr, bool async, Wr64RasterReflectionSkyMode sky, bool rasterShadows) {
        return cache_->prepare(device, layout, samples, hdr, async, sky, rasterShadows);
    }
    const RenderPipeline *Wr64RasterReflectionPipelines::capture(bool nativeCulling) { return cache_->get(nativeCulling ? 9 : 8); }
    const RenderPipeline *Wr64RasterReflectionPipelines::get(bool compare, bool write, bool coverage) {
        return cache_->get(uint32_t(compare) | (uint32_t(write) << 1) | (uint32_t(coverage) << 2));
    }
    Wr64RTPrewarmStatus Wr64RasterReflectionPipelines::prewarm() { return cache_->prewarm(); }
    void Wr64RasterReflectionPipelines::waitForPending() { cache_->waitForPending(); }
    void Wr64RasterReflectionPipelines::reset() { cache_->reset(); }

    bool Wr64RasterReflectionTarget::ensure(RenderWorker *worker, uint32_t width, uint32_t height) {
#ifndef _WIN32
        return false;
#else
        if (!worker || !worker->device || width == 0 || height == 0 || width > 4096 || height > 4096) return false;
        if (device_ == worker->device && width_ == width && height_ == height && color_ && depth_ && framebuffer_) return true;
        try {
            auto color = worker->device->createTexture(RenderTextureDesc::ColorTarget(width, height, RenderFormat::R16G16B16A16_FLOAT));
            auto depth = worker->device->createTexture(RenderTextureDesc::DepthTarget(width, height, RenderFormat::D32_FLOAT));
            if (!color || !depth || !static_cast<D3D12Texture *>(color.get())->d3d || !static_cast<D3D12Texture *>(depth.get())->d3d) return false;
            const RenderTexture *attachment = color.get();
            auto framebuffer = worker->device->createFramebuffer(RenderFramebufferDesc(&attachment, 1, depth.get()));
            if (!framebuffer) return false;
            color->setName("Wave Race raster reflection color"); depth->setName("Wave Race raster reflection depth");
            framebuffer_.reset(); color_ = std::move(color); depth_ = std::move(depth); framebuffer_ = std::move(framebuffer);
            device_ = worker->device; width_ = width; height_ = height; return true;
        } catch (...) { return false; }
#endif
    }
    void Wr64RasterReflectionTarget::reset() {
        framebuffer_.reset(); color_.reset(); depth_.reset(); device_ = nullptr; width_ = height_ = 0;
    }
}
