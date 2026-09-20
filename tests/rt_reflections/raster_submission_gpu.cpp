// Actual production submitRasterScene regression: depth-only native clear is
// the first operation on a fresh command list, before any graphics layout.
#include <cstdio>
#include <stdexcept>
#include "plume_d3d12.h"
#include "render/rt64_framebuffer_renderer.h"

using namespace plume;
using namespace RT64;

namespace {
    size_t checks = 0;
    void require(bool value, const char *message) {
        ++checks;
        if (!value) throw std::runtime_error(message);
    }
    void fillSamplers(RenderDevice *device, SamplerSet &set, RenderFilter filter) {
        std::unique_ptr<RenderSampler> *entries[] = {
            &set.wrapWrap, &set.wrapMirror, &set.wrapClamp, &set.mirrorWrap, &set.mirrorMirror,
            &set.mirrorClamp, &set.clampWrap, &set.clampMirror, &set.clampClamp
        };
        const RenderTextureAddressMode modes[] = {RenderTextureAddressMode::WRAP,
            RenderTextureAddressMode::MIRROR, RenderTextureAddressMode::CLAMP};
        for (uint32_t i = 0; i < 9; ++i) {
            RenderSamplerDesc desc;
            desc.minFilter = desc.magFilter = filter;
            desc.addressU = modes[i / 3]; desc.addressV = modes[i % 3];
            *entries[i] = device->createSampler(desc);
        }
    }
}

int main() {
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    try {
        D3D12Interface renderInterface;
        require(renderInterface.isValid(), "D3D12 interface initialization failed");
        auto device = renderInterface.createDevice("");
        require(device != nullptr, "D3D12 device initialization failed");
        std::printf("Actual submitRasterScene probe: %s\n", device->getDescription().name.c_str());
        RenderWorker worker(device.get(), "Native depth-first raster submission regression", RenderCommandListType::DIRECT);
        ShaderLibrary shaders(false, false);
        fillSamplers(device.get(), shaders.samplerLibrary.nearest, RenderFilter::NEAREST);
        fillSamplers(device.get(), shaders.samplerLibrary.linear, RenderFilter::LINEAR);
        for (uint32_t samples : {1u, 4u}) {
            const RenderMultisampling ms(samples);
            FramebufferRenderer renderer(&worker, false, UserConfiguration::GraphicsAPI::D3D12, &shaders);
            FramebufferRenderer::Framebuffer framebuffer;
            framebuffer.descRealFbSet = std::make_unique<FramebufferRendererDescriptorFramebufferSet>(device.get());
            framebuffer.descDummyFbSet = std::make_unique<FramebufferRendererDescriptorFramebufferSet>(device.get());
            RenderTarget depth(0, Framebuffer::Type::Depth, ms, false);
            require(depth.resize(&worker, 64, 64), "Native depth target allocation failed");
            RenderFramebufferStorage storage;
            storage.setup(device.get(), RenderFramebufferKey{}, nullptr, &depth);
            InstanceDrawCall clear;
            clear.type = InstanceDrawCall::Type::FillRect;
            clear.clearRect.rect = RenderRect(0, 0, 64, 64);
            clear.clearRect.depth = .25f;
            renderer.instanceDrawCallVector.push_back(clear);
            RasterScene scene;
            scene.instanceIndices = {0};
            bool depthState = false;
            worker.commandList->begin();
            worker.commandList->barriers(RenderBarrierStage::GRAPHICS,
                RenderTextureBarrier(depth.texture.get(), RenderTextureLayout::DEPTH_WRITE));
            worker.commandList->setFramebuffer(storage.colorDepthWrite.get());
            auto *nativeCommands = static_cast<D3D12CommandList *>(worker.commandList.get());
            require(nativeCommands->activeGraphicsPipelineLayout == nullptr,
                "Depth-first regression accidentally installed a graphics layout");
            std::printf("%ux: calling actual depth-only FillRect with no graphics layout\n", samples);
            renderer.submitRasterScene(&worker, framebuffer, &storage, scene, depthState);
            require(nativeCommands->activeGraphicsPipelineLayout == nullptr,
                "A native depth clear unnecessarily installed a graphics layout");
            worker.commandList->end(); worker.execute(); worker.wait();
            require(SUCCEEDED(static_cast<D3D12Device *>(device.get())->d3d->GetDeviceRemovedReason()),
                "Depth-first native submission removed the graphics device");
            require(depth.resolvedTextureDirty, "Actual native depth clear did not mark its output for resolve");
            std::printf("%ux: native depth-first submit completed\n", samples);
        }
        std::printf("PASS: %zu actual production depth-first submission checks.\n", checks);
        return 0;
    }
    catch (const std::exception &e) {
        std::fprintf(stderr, "FAIL after %zu checks: %s\n", checks, e.what());
        return 1;
    }
}
