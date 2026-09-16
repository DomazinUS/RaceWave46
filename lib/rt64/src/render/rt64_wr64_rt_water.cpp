#include "rt64_wr64_rt_water.h"
#include "common/rt64_wr64_async_cache.h"
#include "common/rt64_wr64_rt_diagnostics.h"

#include <chrono>
#include <cstdio>
#include <vector>
#ifdef RT64_WR64_VULKAN_RT
#include "plume_vulkan.h"
#include "shaders/Wr64WaterReflectionVS.hlsl.spirv.h"
#include "shaders/Wr64WaterReflectionPS.hlsl.spirv.h"
#include "shaders/Wr64WaterReflectionPSMS.hlsl.spirv.h"
#include "shaders/Wr64WaterSkyReflectionPS.hlsl.spirv.h"
#include "shaders/Wr64WaterSkyReflectionPSMS.hlsl.spirv.h"
#include "shaders/Wr64WorldShadowVS.hlsl.spirv.h"
#include "shaders/Wr64WorldShadowPS.hlsl.spirv.h"
#include "shaders/Wr64WorldShadowPSMS.hlsl.spirv.h"
#endif

#ifdef _WIN32
#include "plume_d3d12.h"
#include "common/rt64_wr64_diagnostic_sky_shader.h"
#include "shaders/Wr64WaterReflectionVS.hlsl.dxil.h"
#include "shaders/Wr64WaterReflectionPS.hlsl.dxil.h"
#include "shaders/Wr64WaterReflectionPSMS.hlsl.dxil.h"
#include "shaders/Wr64WaterSkyReflectionPS.hlsl.dxil.h"
#include "shaders/Wr64WaterSkyReflectionPSMS.hlsl.dxil.h"
#include "shaders/Wr64WorldShadowVS.hlsl.dxil.h"
#include "shaders/Wr64WorldShadowPS.hlsl.dxil.h"
#include "shaders/Wr64WorldShadowPSMS.hlsl.dxil.h"
#endif

namespace RT64 {
    class Wr64RTPipelineCache {
        static constexpr size_t MaxConfigurations = 16;
        static constexpr size_t KeysPerConfiguration = 65; // 64 PSOs plus shader preparation.
        struct Configuration {
            size_t slot = 0;
            RenderDevice *device = nullptr;
            const RenderPipelineLayout *layout = nullptr;
            RenderMultisampling multisampling{};
            RenderShaderFormat shaderFormat = RenderShaderFormat::DXIL;
            bool hdr = false, sky = false;
            // Accessed only by this cache's single build worker.
            bool shadersAttempted = false;
            std::unique_ptr<RenderShader> vertex, pixel;
        };
        struct Result { std::unique_ptr<RenderPipeline> pipeline; };
        bool world_ = false, async_ = false, capacityReported_ = false;
        std::vector<std::shared_ptr<Configuration>> configurations_;
        std::shared_ptr<Configuration> selected_;
        // Destroy worker/results before configuration shaders and raw layout
        // references. The owner drains GPU users before reset/destruction.
        Wr64AsyncCache<Result, MaxConfigurations * KeysPerConfiguration> builds_;

        static bool sameMultisampling(const RenderMultisampling &a, const RenderMultisampling &b) {
            if (a.sampleCount != b.sampleCount || a.sampleLocationsEnabled != b.sampleLocationsEnabled) return false;
            if (a.sampleLocationsEnabled)
                for (size_t i = 0; i < 16; ++i) if (a.sampleLocations[i] != b.sampleLocations[i]) return false;
            return true;
        }

        static bool prepareShaders(Configuration &config, bool world) {
            if (config.shadersAttempted) return config.vertex && config.pixel;
            config.shadersAttempted = true;
            const bool ms = config.multisampling.sampleCount > 1;
#ifdef RT64_WR64_VULKAN_RT
            if (config.shaderFormat == RenderShaderFormat::SPIRV) {
                const void *vsBlob = world ? Wr64WorldShadowVSBlobSPIRV : Wr64WaterReflectionVSBlobSPIRV;
                const size_t vsSize = world ? Wr64WorldShadowVSBlobSPIRV_size : Wr64WaterReflectionVSBlobSPIRV_size;
                const void *psBlob = world ? (ms ? Wr64WorldShadowPSMSBlobSPIRV : Wr64WorldShadowPSBlobSPIRV) :
                    (config.sky ? (ms ? Wr64WaterSkyReflectionPSMSBlobSPIRV : Wr64WaterSkyReflectionPSBlobSPIRV) :
                        (ms ? Wr64WaterReflectionPSMSBlobSPIRV : Wr64WaterReflectionPSBlobSPIRV));
                const size_t psSize = world ? (ms ? Wr64WorldShadowPSMSBlobSPIRV_size : Wr64WorldShadowPSBlobSPIRV_size) :
                    (config.sky ? (ms ? Wr64WaterSkyReflectionPSMSBlobSPIRV_size : Wr64WaterSkyReflectionPSBlobSPIRV_size) :
                        (ms ? Wr64WaterReflectionPSMSBlobSPIRV_size : Wr64WaterReflectionPSBlobSPIRV_size));
                config.vertex = config.device->createShader(vsBlob, vsSize, "VSMain", RenderShaderFormat::SPIRV);
                config.pixel = config.device->createShader(psBlob, psSize, "PSMain", RenderShaderFormat::SPIRV);
                return config.vertex && config.pixel;
            }
#endif
#ifdef _WIN32
            if (config.shaderFormat != RenderShaderFormat::DXIL) return false;
            const void *vsBlob = world ? Wr64WorldShadowVSBlobDXIL : Wr64WaterReflectionVSBlobDXIL;
            const size_t vsSize = world ? sizeof(Wr64WorldShadowVSBlobDXIL) : sizeof(Wr64WaterReflectionVSBlobDXIL);
            const void *psBlob = world ? (ms ? Wr64WorldShadowPSMSBlobDXIL : Wr64WorldShadowPSBlobDXIL) :
                (config.sky ? (ms ? Wr64WaterSkyReflectionPSMSBlobDXIL : Wr64WaterSkyReflectionPSBlobDXIL) :
                    (ms ? Wr64WaterReflectionPSMSBlobDXIL : Wr64WaterReflectionPSBlobDXIL));
            size_t psSize = world ? (ms ? sizeof(Wr64WorldShadowPSMSBlobDXIL) : sizeof(Wr64WorldShadowPSBlobDXIL)) :
                (config.sky ? (ms ? sizeof(Wr64WaterSkyReflectionPSMSBlobDXIL) : sizeof(Wr64WaterSkyReflectionPSBlobDXIL)) :
                    (ms ? sizeof(Wr64WaterReflectionPSMSBlobDXIL) : sizeof(Wr64WaterReflectionPSBlobDXIL)));
            if (const auto *overrideBlob = wr64D3D12DiagnosticSkyShader(true, world, config.sky, ms)) {
                psBlob = overrideBlob->data();
                psSize = overrideBlob->size();
            }
            config.vertex = config.device->createShader(vsBlob, vsSize, "VSMain", RenderShaderFormat::DXIL);
            config.pixel = config.device->createShader(psBlob, psSize, "PSMain", RenderShaderFormat::DXIL);
            return config.vertex && config.pixel;
#else
            return false;
#endif
        }

        const Result *request(uint32_t variant) {
            if (!selected_ || variant >= KeysPerConfiguration) return nullptr;
            auto config = selected_;
            const bool world = world_;
            return builds_.get(config->slot * KeysPerConfiguration + variant, [config, world, variant] {
                const auto begin = std::chrono::steady_clock::now();
                char details[192];
                std::snprintf(details, sizeof(details), "family=%s sky=%u samples=%u hdr=%u variant=%u backend=%s",
                    world ? "shore" : "water", unsigned(config->sky), unsigned(config->multisampling.sampleCount),
                    unsigned(config->hdr), variant, config->shaderFormat == RenderShaderFormat::SPIRV ? "Vulkan" : "D3D12");
                wr64RTDiagnostic("pso-build-start", details);
                std::unique_ptr<Result> result;
                try {
                    if (prepareShaders(*config, world)) {
                        result = std::make_unique<Result>();
                        if (variant != 64) {
                            PipelineCreation c{};
                            c.device = config->device; c.pipelineLayout = config->layout;
                            c.vertexShader = config->vertex.get(); c.pixelShader = config->pixel.get();
                            c.alphaBlend = world ? (variant & 32) != 0 : true;
                            c.culling = world && (variant & 8) != 0;
                            c.NoN = !world || (variant & 16) != 0;
                            c.zCmp = (variant & 1) != 0; c.zUpd = (variant & 2) != 0;
                            c.cvgAdd = (variant & 4) != 0; c.usesHDR = config->hdr;
                            c.multisampling = config->multisampling;
                            result->pipeline = RasterShader::createPipeline(c);
                            bool ready = result->pipeline != nullptr;
#ifdef RT64_WR64_VULKAN_RT
                            if (ready && config->shaderFormat == RenderShaderFormat::SPIRV)
                                ready = static_cast<VulkanGraphicsPipeline *>(result->pipeline.get())->vk != VK_NULL_HANDLE;
#endif
#ifdef _WIN32
                            // Plume can return a wrapper even when the native
                            // CreateGraphicsPipelineState call failed. Only a
                            // real PSO may replace the working native pipeline.
                            if (ready && config->shaderFormat == RenderShaderFormat::DXIL)
                                ready = static_cast<D3D12GraphicsPipeline *>(result->pipeline.get())->d3d != nullptr;
#endif
                            if (!ready) result.reset();
                            else if (config->shaderFormat == RenderShaderFormat::SPIRV) {
                                // Static diagnostic categories let Vulkan report
                                // which RT pass was active after a device loss.
                                result->pipeline->setName(world ? "WR64 RT world shadow" :
                                    (config->sky ? "WR64 RT sky" : "WR64 RT water"));
                            }
                        }
                    }
                } catch (...) { result.reset(); }
                const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::steady_clock::now() - begin).count();
                std::snprintf(details, sizeof(details), "family=%s sky=%u samples=%u hdr=%u variant=%u ready=%u elapsed_ms=%lld backend=%s",
                    world ? "shore" : "water", unsigned(config->sky), unsigned(config->multisampling.sampleCount),
                    unsigned(config->hdr), variant, unsigned(bool(result)), static_cast<long long>(elapsed),
                    config->shaderFormat == RenderShaderFormat::SPIRV ? "Vulkan" : "D3D12");
                wr64RTDiagnostic("pso-build-finish", details);
                return result;
            }, !async_);
        }

    public:
        explicit Wr64RTPipelineCache(bool world) : world_(world) { }
        bool prepare(RenderDevice *device, const RenderPipelineLayout *layout,
            const RenderMultisampling &multisampling, bool hdr, bool sky, bool async, RenderShaderFormat shaderFormat) {
            selected_.reset();
            if (!device || !layout) return false;
            if (shaderFormat != RenderShaderFormat::DXIL && shaderFormat != RenderShaderFormat::SPIRV) return false;
            async_ = async;
            for (const auto &config : configurations_) {
                if (config->device == device && config->layout == layout && config->hdr == hdr &&
                    config->sky == sky && config->shaderFormat == shaderFormat && sameMultisampling(config->multisampling, multisampling)) {
                    selected_ = config; break;
                }
            }
            if (!selected_) {
                if (configurations_.size() >= MaxConfigurations) {
                    if (!capacityReported_) wr64RTDiagnostic("pso-cache-full", world_ ? "family=shore" : "family=water");
                    capacityReported_ = true;
                    return false;
                }
                auto config = std::make_shared<Configuration>();
                config->slot = configurations_.size(); config->device = device; config->layout = layout;
                config->multisampling = multisampling; config->hdr = hdr; config->sky = sky;
                config->shaderFormat = shaderFormat;
                configurations_.push_back(config); selected_ = std::move(config);
            }
            // Runtime preparation never performs a driver call or waits for a
            // compile. get() requests only pipeline variants actually drawn.
            if (async_) return true;
            if (world_) return request(64) != nullptr;
            for (uint32_t i = 0; i < 8; ++i) if (!request(i)) return false;
            return true;
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
            const uint32_t count = world_ ? 64 : 8;
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

    Wr64RTWaterPipelines::Wr64RTWaterPipelines() : cache_(std::make_unique<Wr64RTPipelineCache>(false)) { }
    Wr64RTWaterPipelines::~Wr64RTWaterPipelines() = default;
    Wr64RTWorldShadowPipelines::Wr64RTWorldShadowPipelines() : cache_(std::make_unique<Wr64RTPipelineCache>(true)) { }
    Wr64RTWorldShadowPipelines::~Wr64RTWorldShadowPipelines() = default;

    bool Wr64RTWaterPipelines::supported(RenderDevice *device, UserConfiguration::GraphicsAPI api) {
        if (!device) return false;
#ifdef RT64_WR64_VULKAN_RT
        // World shadows read the primitive ID in the fragment shader, which
        // requires SPIR-V's Geometry capability even without a geometry stage.
        if (api == UserConfiguration::GraphicsAPI::Vulkan)
            return device->getCapabilities().rayQueries && device->getCapabilities().geometryShader;
#endif
#ifdef _WIN32
        if (!device || api != UserConfiguration::GraphicsAPI::D3D12 || !device->getCapabilities().raytracing) return false;
        auto *native = static_cast<D3D12Device *>(device);
        D3D12_FEATURE_DATA_D3D12_OPTIONS5 options{};
        // Plume's cached shaderModel only probes 6.0; query the required tier
        // directly or every capable device would incorrectly fall back.
        D3D12_FEATURE_DATA_SHADER_MODEL shaderModel{D3D_SHADER_MODEL_6_5};
        return SUCCEEDED(native->d3d->CheckFeatureSupport(D3D12_FEATURE_SHADER_MODEL, &shaderModel, sizeof(shaderModel))) &&
            shaderModel.HighestShaderModel >= D3D_SHADER_MODEL_6_5 &&
            SUCCEEDED(native->d3d->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS5, &options, sizeof(options))) &&
            options.RaytracingTier >= D3D12_RAYTRACING_TIER_1_1;
#else
        return false;
#endif
    }

    bool Wr64RTWaterPipelines::prepare(RenderDevice *device, const RenderPipelineLayout *layout,
        const RenderMultisampling &multisampling, bool hdr, bool nativeSky, bool async, RenderShaderFormat shaderFormat) {
        return cache_->prepare(device, layout, multisampling, hdr, nativeSky, async, shaderFormat);
    }

    const RenderPipeline *Wr64RTWaterPipelines::get(bool compare, bool write, bool add) const {
        return cache_->get(uint32_t(compare) | (uint32_t(write) << 1) | (uint32_t(add) << 2));
    }

    bool Wr64RTWorldShadowPipelines::prepare(RenderDevice *device, const RenderPipelineLayout *layout,
        const RenderMultisampling &multisampling, bool hdr, bool async, RenderShaderFormat shaderFormat) {
        return cache_->prepare(device, layout, multisampling, hdr, false, async, shaderFormat);
    }

    const RenderPipeline *Wr64RTWorldShadowPipelines::get(bool compare, bool write, bool add,
        bool culling, bool NoN, bool alphaBlend) {
        const uint32_t index = uint32_t(compare) | (uint32_t(write) << 1) |
            (uint32_t(add) << 2) | (uint32_t(culling) << 3) |
            (uint32_t(NoN) << 4) | (uint32_t(alphaBlend) << 5);
        return cache_->get(index);
    }
    void Wr64RTWaterPipelines::waitForPending() { cache_->waitForPending(); }
    Wr64RTPrewarmStatus Wr64RTWaterPipelines::prewarm() { return cache_->prewarm(); }
    Wr64RTPrewarmStatus Wr64RTWorldShadowPipelines::prewarm() { return cache_->prewarm(); }
    void Wr64RTWorldShadowPipelines::waitForPending() { cache_->waitForPending(); }
    void Wr64RTWaterPipelines::reset() { cache_->reset(); }
    void Wr64RTWorldShadowPipelines::reset() { cache_->reset(); }
}
