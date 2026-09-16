#include "rt64_wr64_motion_blur.h"
#include "rt64_render_target.h"
#include "rt64_render_worker.h"
#include "common/rt64_wr64_async_cache.h"
#include "common/rt64_wr64_rt_diagnostics.h"
#include "shared/rt64_wr64_motion_tiles.h"

#include <array>
#include <cmath>
#include <vector>

#ifdef _WIN32
#include "plume_d3d12.h"
#include "shaders/Wr64MotionVS.hlsl.dxil.h"
#include "shaders/Wr64MotionMaskPS.hlsl.dxil.h"
#include "shaders/Wr64MotionMaskPSMS.hlsl.dxil.h"
#include "shaders/Wr64MotionResolveVS.hlsl.dxil.h"
#include "shaders/Wr64MotionTilePS.hlsl.dxil.h"
#include "shaders/Wr64MotionTilePSMS.hlsl.dxil.h"
#include "shaders/Wr64MotionResolvePS.hlsl.dxil.h"
#include "shaders/Wr64MotionResolvePSMS.hlsl.dxil.h"
#endif

namespace RT64 {
    namespace {
        constexpr size_t ConfigurationLimit = 16;
        bool sameSamples(const RenderMultisampling &a, const RenderMultisampling &b) {
            if (a.sampleCount != b.sampleCount || a.sampleLocationsEnabled != b.sampleLocationsEnabled) return false;
            if (a.sampleLocationsEnabled)
                for (size_t i = 0; i < 16; ++i) if (a.sampleLocations[i] != b.sampleLocations[i]) return false;
            return true;
        }
        bool validPipeline(const std::unique_ptr<RenderPipeline> &pipeline) {
#ifdef _WIN32
            return pipeline && static_cast<D3D12GraphicsPipeline *>(pipeline.get())->d3d;
#else
            return false;
#endif
        }
        struct MotionDescriptorSet : RenderDescriptorSetBase {
            uint32_t source, motion, depth;
            std::array<uint32_t, WR64_MOTION_RACER_COUNT> guides;
            explicit MotionDescriptorSet(RenderDevice *device = nullptr) {
                builder.begin();
                source = builder.addTexture(0);motion = builder.addTexture(1);depth = builder.addTexture(2);
                for (uint32_t lane = 0; lane < guides.size(); ++lane) guides[lane] = builder.addTexture(3 + lane);
                builder.end();
                if (device) create(device);
            }
        };
    }

    struct Wr64MotionBlur::Impl {
        struct Configuration {
            size_t slot;
            RenderDevice *device;
            const RenderPipelineLayout *rendererLayout;
            RenderMultisampling samples;
            bool hdr;
        };
        struct Result {
            std::unique_ptr<RenderPipelineLayout> resolveLayout;
            std::unique_ptr<RenderShader> maskVS, maskPS, resolveVS, tilePS, resolvePS;
            std::array<std::unique_ptr<RenderPipeline>, 4> masks;
            std::unique_ptr<RenderPipeline> tile, resolve;
        };
        struct Targets {
            size_t configuration;
            RenderTarget *color = nullptr, *depth = nullptr;
            uint32_t width = 0, height = 0;
            std::unique_ptr<RenderTarget> source;
            std::unique_ptr<RenderTexture> motion;
            std::unique_ptr<RenderTextureView> motionView;
            std::array<std::unique_ptr<RenderTexture>, WR64_MOTION_RACER_COUNT> guides;
            std::array<std::unique_ptr<RenderTextureView>, WR64_MOTION_RACER_COUNT> guideViews;
            std::unique_ptr<MotionDescriptorSet> descriptors;
            std::unique_ptr<RenderFramebuffer> maskFramebuffer, guideFramebuffer, outputFramebuffer;
            bool recording = false, finished = false;
        };
        std::vector<std::shared_ptr<Configuration>> configurations;
        std::shared_ptr<Configuration> selected;
        const Result *ready = nullptr;
        std::unique_ptr<Targets> targets;
        Targets *active = nullptr;
        // The worker joins before captured configuration/layout references
        // disappear. Published PSOs remain stable until explicit reset.
        Wr64AsyncCache<Result, ConfigurationLimit> builds;

        static std::unique_ptr<Result> build(const Configuration &c) {
#ifdef _WIN32
            wr64RTDiagnostic("pso-build-start", "family=motion");
            auto result = std::make_unique<Result>();
            const bool ms = c.samples.sampleCount > 1;
            result->maskVS = c.device->createShader(Wr64MotionVSBlobDXIL, sizeof(Wr64MotionVSBlobDXIL), "VSMain", RenderShaderFormat::DXIL);
            result->maskPS = c.device->createShader(ms ? Wr64MotionMaskPSMSBlobDXIL : Wr64MotionMaskPSBlobDXIL,
                ms ? sizeof(Wr64MotionMaskPSMSBlobDXIL) : sizeof(Wr64MotionMaskPSBlobDXIL), "PSMain", RenderShaderFormat::DXIL);
            result->resolveVS = c.device->createShader(Wr64MotionResolveVSBlobDXIL, sizeof(Wr64MotionResolveVSBlobDXIL), "VSMain", RenderShaderFormat::DXIL);
            result->tilePS = c.device->createShader(ms ? Wr64MotionTilePSMSBlobDXIL : Wr64MotionTilePSBlobDXIL,
                ms ? sizeof(Wr64MotionTilePSMSBlobDXIL) : sizeof(Wr64MotionTilePSBlobDXIL), "PSMain", RenderShaderFormat::DXIL);
            result->resolvePS = c.device->createShader(ms ? Wr64MotionResolvePSMSBlobDXIL : Wr64MotionResolvePSBlobDXIL,
                ms ? sizeof(Wr64MotionResolvePSMSBlobDXIL) : sizeof(Wr64MotionResolvePSBlobDXIL), "PSMain", RenderShaderFormat::DXIL);
            if (!result->maskVS || !result->maskPS || !result->resolveVS || !result->tilePS || !result->resolvePS) return nullptr;
            MotionDescriptorSet descriptors;
            RenderPipelineLayoutBuilder layout;
            layout.begin();
            layout.addPushConstant(0, 0, sizeof(float) * 4, RenderShaderStageFlag::PIXEL);
            layout.addDescriptorSet(descriptors);layout.end();
            result->resolveLayout = layout.create(c.device);
            if (!result->resolveLayout) return nullptr;
            const RenderInputSlot slots[] = {RenderInputSlot(0, 16), RenderInputSlot(1, 8), RenderInputSlot(2, 16)};
            const RenderInputElement elements[] = {
                RenderInputElement("POSITION", 0, 0, RenderFormat::R32G32B32A32_FLOAT, 0, 0),
                RenderInputElement("TEXCOORD", 0, 1, RenderFormat::R32G32_FLOAT, 1, 0),
                RenderInputElement("COLOR", 0, 2, RenderFormat::R32G32B32A32_FLOAT, 2, 0)};
            for (uint32_t variant = 0; variant < 4; ++variant) {
                RenderGraphicsPipelineDesc desc;
                desc.pipelineLayout = c.rendererLayout;desc.vertexShader = result->maskVS.get();desc.pixelShader = result->maskPS.get();
                desc.renderTargetCount = 1;desc.renderTargetFormat[0] = RenderFormat::R32G32B32A32_FLOAT;
                desc.renderTargetBlend[0] = RenderBlendDesc::Copy();
                desc.depthTargetFormat = RenderFormat::D32_FLOAT;desc.depthEnabled = true;
                desc.depthFunction = RenderComparisonFunction::LESS_EQUAL;desc.depthWriteEnabled = false;
                desc.depthClipEnabled = (variant & 2) == 0;desc.cullMode = (variant & 1) ? RenderCullMode::FRONT : RenderCullMode::NONE;
                desc.multisampling = c.samples;
                desc.inputSlots = slots;desc.inputSlotsCount = 3;desc.inputElements = elements;desc.inputElementsCount = 3;
                result->masks[variant] = c.device->createGraphicsPipeline(desc);
                if (!validPipeline(result->masks[variant])) return nullptr;
            }
            RenderGraphicsPipelineDesc tileDesc;
            tileDesc.pipelineLayout = result->resolveLayout.get();tileDesc.vertexShader = result->resolveVS.get();tileDesc.pixelShader = result->tilePS.get();
            tileDesc.renderTargetCount = WR64_MOTION_RACER_COUNT;
            for (uint32_t lane = 0; lane < WR64_MOTION_RACER_COUNT; ++lane) {
                tileDesc.renderTargetFormat[lane] = RenderFormat::R32G32B32A32_FLOAT;
                tileDesc.renderTargetBlend[lane] = RenderBlendDesc::Copy();
            }
            result->tile = c.device->createGraphicsPipeline(tileDesc);
            if (!validPipeline(result->tile)) return nullptr;
            RenderGraphicsPipelineDesc desc;
            desc.pipelineLayout = result->resolveLayout.get();desc.vertexShader = result->resolveVS.get();desc.pixelShader = result->resolvePS.get();
            desc.renderTargetCount = 1;desc.renderTargetFormat[0] = RenderTarget::colorBufferFormat(c.hdr);
            desc.renderTargetBlend[0] = RenderBlendDesc::Copy();desc.multisampling = c.samples;
            result->resolve = c.device->createGraphicsPipeline(desc);
            if (!validPipeline(result->resolve)) return nullptr;
            wr64RTDiagnostic("pso-build-finish", "family=motion ready=1");
            return result;
#else
            return nullptr;
#endif
        }
    };

    Wr64MotionBlur::Wr64MotionBlur() : impl_(std::make_unique<Impl>()) { }
    Wr64MotionBlur::~Wr64MotionBlur() = default;
    Wr64RTPrewarmStatus Wr64MotionBlur::prewarm(RenderDevice *device, const RenderPipelineLayout *rendererLayout,
        const RenderMultisampling &samples, bool hdr) {
        auto &p = *impl_;p.ready = nullptr;p.selected.reset();p.active = nullptr;
#ifdef _WIN32
        if (!device || !rendererLayout) return Wr64RTPrewarmStatus::Failed;
        for (const auto &c : p.configurations)
            if (c->device == device && c->rendererLayout == rendererLayout && c->hdr == hdr && sameSamples(c->samples, samples)) { p.selected = c;break; }
        if (!p.selected) {
            if (p.configurations.size() >= ConfigurationLimit) return Wr64RTPrewarmStatus::Failed;
            p.selected = std::make_shared<Impl::Configuration>(Impl::Configuration{p.configurations.size(), device, rendererLayout, samples, hdr});
            p.configurations.push_back(p.selected);
        }
        auto config = p.selected;
        p.ready = p.builds.get(config->slot, [config] {return Impl::build(*config);}, false);
        if (p.ready) return Wr64RTPrewarmStatus::Ready;
        return p.builds.state(config->slot) == decltype(p.builds)::State::Failed ? Wr64RTPrewarmStatus::Failed : Wr64RTPrewarmStatus::Pending;
#else
        return Wr64RTPrewarmStatus::Failed;
#endif
    }
    bool Wr64MotionBlur::prepare(RenderDevice *device, const RenderPipelineLayout *layout, const RenderMultisampling &samples, bool hdr) {
        return prewarm(device, layout, samples, hdr) == Wr64RTPrewarmStatus::Ready;
    }
    const RenderPipeline *Wr64MotionBlur::getMask(bool culling, bool NoN) const {
        return impl_->ready ? impl_->ready->masks[uint32_t(culling) | (uint32_t(NoN) << 1)].get() : nullptr;
    }
    bool Wr64MotionBlur::ensureTargets(RenderWorker *worker, RenderTarget *color, RenderTarget *depth, const ShaderLibrary *) {
        auto &p = *impl_;p.active = nullptr;
        if (!worker || !p.ready || !p.selected || worker->device != p.selected->device || !color || !depth ||
            !color->texture || !depth->texture || !color->width || !color->height || color->width != depth->width || color->height != depth->height ||
            color->format != RenderTarget::colorBufferFormat(p.selected->hdr) || depth->format != RenderFormat::D32_FLOAT ||
            !sameSamples(color->multisampling, p.selected->samples) || !sameSamples(depth->multisampling, p.selected->samples)) return false;
        // WorkloadQueue waits for the previous submission before invoking
        // endFramebuffers/ensureTargets. Reuse only private textures, not raw
        // original-target identities that can be recycled during a resize.
        if (!p.targets || p.targets->configuration != p.selected->slot ||
            p.targets->width != color->width || p.targets->height != color->height) {
            p.targets.reset();
            auto created = std::make_unique<Impl::Targets>();
            created->configuration = p.selected->slot;created->width = color->width;created->height = color->height;
            created->source = std::make_unique<RenderTarget>(0, Framebuffer::Type::Color, RenderMultisampling(), p.selected->hdr);
            created->source->resize(worker, created->width, created->height);
            created->motion = worker->device->createTexture(RenderTextureDesc::ColorTarget(created->width, created->height, RenderFormat::R32G32B32A32_FLOAT, p.selected->samples));
            if (!created->source->texture || !created->motion) return false;
            created->motion->setName("WR64 actor motion mask");
            created->motionView = created->motion->createTextureView(RenderTextureViewDesc::Texture2D(RenderFormat::R32G32B32A32_FLOAT));
            created->descriptors = std::make_unique<MotionDescriptorSet>(worker->device);
            if (!created->motionView) return false;
            const uint32_t tileWidth = (created->width + WR64_MOTION_TILE_SIZE - 1) / WR64_MOTION_TILE_SIZE;
            const uint32_t tileHeight = (created->height + WR64_MOTION_TILE_SIZE - 1) / WR64_MOTION_TILE_SIZE;
            std::array<const RenderTexture *, WR64_MOTION_RACER_COUNT> attachments;
            for (uint32_t lane = 0; lane < WR64_MOTION_RACER_COUNT; ++lane) {
                created->guides[lane] = worker->device->createTexture(RenderTextureDesc::ColorTarget(tileWidth, tileHeight, RenderFormat::R32G32B32A32_FLOAT));
                if (!created->guides[lane]) return false;
                created->guideViews[lane] = created->guides[lane]->createTextureView(RenderTextureViewDesc::Texture2D(RenderFormat::R32G32B32A32_FLOAT));
                if (!created->guideViews[lane]) return false;
                attachments[lane] = created->guides[lane].get();
            }
            created->guideFramebuffer = worker->device->createFramebuffer(RenderFramebufferDesc(attachments.data(), uint32_t(attachments.size())));
            if (!created->guideFramebuffer) return false;
            p.targets = std::move(created);
        }
        auto *t = p.targets.get();
        t->color = color;t->depth = depth;t->recording = t->finished = false;
        const RenderTexture *motion = t->motion.get(), *output = color->texture.get();
        // Rebuild lightweight attachment views and depth binding every time:
        // same-size interpolation targets and recycled wrapper addresses must
        // never inherit a previous frame's DSV or shader-resource descriptor.
        t->maskFramebuffer = worker->device->createFramebuffer(RenderFramebufferDesc(&motion, 1, depth->texture.get(), true));
        t->outputFramebuffer = worker->device->createFramebuffer(RenderFramebufferDesc(&output, 1));
        t->descriptors->setTexture(t->descriptors->source, t->source->texture.get(), RenderTextureLayout::SHADER_READ, t->source->textureView.get());
        t->descriptors->setTexture(t->descriptors->motion, t->motion.get(), RenderTextureLayout::SHADER_READ, t->motionView.get());
        t->descriptors->setTexture(t->descriptors->depth, depth->texture.get(), RenderTextureLayout::DEPTH_READ, depth->textureView.get());
        for (uint32_t lane = 0; lane < WR64_MOTION_RACER_COUNT; ++lane)
            t->descriptors->setTexture(t->descriptors->guides[lane], t->guides[lane].get(), RenderTextureLayout::SHADER_READ, t->guideViews[lane].get());
        if (!t->motionView || !t->maskFramebuffer || !t->outputFramebuffer) return false;
        p.active = t;return true;
    }
    bool Wr64MotionBlur::beginMask(RenderWorker *worker, const ShaderLibrary *shaderLibrary) {
        auto &p = *impl_;auto *t = p.active;
        if (!worker || !shaderLibrary || !p.ready || !t || t->recording) return false;
        worker->commandList->setFramebuffer(nullptr);
        // copyFromTarget is exclusively a color/depth reinterpretation helper.
        // Resolve the scene normally, then copy its single-sample color bytes.
        t->color->markForResolve();t->color->resolveTarget(worker, shaderLibrary);
        RenderTexture *source = t->color->getResolvedTexture();
        worker->commandList->barriers(RenderBarrierStage::COPY, {
            RenderTextureBarrier(source, RenderTextureLayout::COPY_SOURCE),
            RenderTextureBarrier(t->source->texture.get(), RenderTextureLayout::COPY_DEST)});
        worker->commandList->copyTextureRegion(RenderTextureCopyLocation::Subresource(t->source->texture.get()), RenderTextureCopyLocation::Subresource(source));
        worker->commandList->barriers(RenderBarrierStage::GRAPHICS, {
            RenderTextureBarrier(source, RenderTextureLayout::SHADER_READ),
            RenderTextureBarrier(t->source->texture.get(), RenderTextureLayout::SHADER_READ),
            RenderTextureBarrier(t->motion.get(), RenderTextureLayout::COLOR_WRITE),
            RenderTextureBarrier(t->depth->texture.get(), RenderTextureLayout::DEPTH_READ)});
        worker->commandList->setFramebuffer(t->maskFramebuffer.get());
        worker->commandList->setViewports(RenderViewport(0, 0, float(t->width), float(t->height)));
        worker->commandList->setScissors(RenderRect(0, 0, t->width, t->height));
        worker->commandList->clearColor(0, RenderColor(0, 0, 0, 0));
        t->recording = true;t->finished = false;return true;
    }
    RenderFramebuffer *Wr64MotionBlur::maskFramebuffer() const { return impl_->active ? impl_->active->maskFramebuffer.get() : nullptr; }
    void Wr64MotionBlur::finishMask(RenderWorker *worker) {
        auto *t = impl_->active;if (!worker || !t || !t->recording) return;
        worker->commandList->setFramebuffer(nullptr);
        worker->commandList->barriers(RenderBarrierStage::GRAPHICS, RenderTextureBarrier(t->motion.get(), RenderTextureLayout::SHADER_READ));
        t->recording = false;t->finished = true;
    }
    bool Wr64MotionBlur::resolve(RenderWorker *worker, const float options[4]) {
        auto &p = *impl_;auto *t = p.active;
        if (!worker || !options || !p.ready || !t || !t->finished) return false;
        for (size_t i = 0; i < 4; ++i) if (!std::isfinite(options[i])) return false;
        // Native render targets retain their largest allocation after a window
        // shrinks. Operate only on the active zero-origin viewport, never the
        // stale rows/columns beyond it in the backing texture.
        if (options[0] <= 0 || options[1] <= 0 || options[0] > float(t->width) || options[1] > float(t->height) ||
            options[0] != std::floor(options[0]) || options[1] != std::floor(options[1]) ||
            options[2] < 0 || options[2] > WR64_MOTION_TILE_SIZE || options[3] < 0) return false;
        // Reduce the native MSAA mask once per tile. Empty full-resolution
        // background then needs only cached low-resolution guide reads.
        for (auto &guide : t->guides)
            worker->commandList->barriers(RenderBarrierStage::GRAPHICS, RenderTextureBarrier(guide.get(), RenderTextureLayout::COLOR_WRITE));
        worker->commandList->setFramebuffer(t->guideFramebuffer.get());
        worker->commandList->setPipeline(p.ready->tile.get());
        worker->commandList->setGraphicsPipelineLayout(p.ready->resolveLayout.get());
        worker->commandList->setGraphicsDescriptorSet(t->descriptors->get(), 0);
        worker->commandList->setGraphicsPushConstants(0, options);
        const uint32_t tileWidth = (uint32_t(options[0]) + WR64_MOTION_TILE_SIZE - 1) / WR64_MOTION_TILE_SIZE;
        const uint32_t tileHeight = (uint32_t(options[1]) + WR64_MOTION_TILE_SIZE - 1) / WR64_MOTION_TILE_SIZE;
        worker->commandList->setViewports(RenderViewport(0, 0, float(tileWidth), float(tileHeight)));
        worker->commandList->setScissors(RenderRect(0, 0, tileWidth, tileHeight));
        worker->commandList->setVertexBuffers(0, nullptr, 0, nullptr);worker->commandList->setIndexBuffer(nullptr);
        worker->commandList->drawInstanced(3, 1, 0, 0);
        worker->commandList->setFramebuffer(nullptr);
        for (auto &guide : t->guides)
            worker->commandList->barriers(RenderBarrierStage::GRAPHICS, RenderTextureBarrier(guide.get(), RenderTextureLayout::SHADER_READ));
        worker->commandList->barriers(RenderBarrierStage::GRAPHICS, RenderTextureBarrier(t->color->texture.get(), RenderTextureLayout::COLOR_WRITE));
        worker->commandList->setFramebuffer(t->outputFramebuffer.get());
        worker->commandList->setPipeline(p.ready->resolve.get());
        worker->commandList->setGraphicsPipelineLayout(p.ready->resolveLayout.get());
        worker->commandList->setGraphicsDescriptorSet(t->descriptors->get(), 0);
        worker->commandList->setGraphicsPushConstants(0, options);
        worker->commandList->setViewports(RenderViewport(0, 0, options[0], options[1]));
        worker->commandList->setScissors(RenderRect(0, 0, uint32_t(options[0]), uint32_t(options[1])));
        worker->commandList->setVertexBuffers(0, nullptr, 0, nullptr);worker->commandList->setIndexBuffer(nullptr);
        worker->commandList->drawInstanced(3, 1, 0, 0);
        t->color->markForResolve();t->finished = false;return true;
    }
    void Wr64MotionBlur::waitForPending() { impl_->builds.waitForPending(); }
    void Wr64MotionBlur::reset() {
        impl_->builds.waitForPending();impl_->active = nullptr;impl_->targets.reset();impl_->ready = nullptr;
        impl_->builds.reset();impl_->selected.reset();impl_->configurations.clear();
    }
}
