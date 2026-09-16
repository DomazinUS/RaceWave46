// Headless raster readback using the production descriptor definitions,
// Wr64RTWaterPipelines PSOs, embedded VS/PS shaders, and Wr64RTScene helper.
// Synthetic scenes plus documented archived sky geometry; no window, swapchain,
// ROM or game process.
#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <limits>
#include <stdexcept>
#include <thread>
#include <utility>
#include <vector>

#include "plume_d3d12.h"
#include "plume_vulkan.h"
#include "render/rt64_descriptor_sets.h"
#include "render/rt64_render_worker.h"
#include "render/rt64_raster_shader.h"
#include "render/rt64_framebuffer_renderer.h"
#include "render/rt64_wr64_rt_scene.h"
#include "render/rt64_wr64_rt_water.h"
#include "render/rt64_wr64_raster_sky.h"
#include "render/rt64_wr64_raster_shadow.h"
#include "common/rt64_wr64_water_adjacency.h"
#include "common/rt64_wr64_planar_reflection_math.h"
#include "common/rt64_wr64_rt_preview.h"
#include "native_sky_archive_fixture.h"
#include "native_sky_transition_fixture.h"
#include "native_backdrop_crossing_fixture.h"
#include "shared/rt64_frame_params.h"
#include "shared/rt64_framebuffer_params.h"
#include "shared/rt64_raster_params.h"
#include "shared/rt64_rdp_params.h"
#include "shared/rt64_rdp_tile.h"
#include "shared/rt64_gpu_tile.h"
#include "shared/rt64_render_indices.h"
#include "shared/rt64_other_mode.h"
#include "shared/rt64_wr64_rt_celestial.h"
#include "shared/rt64_wr64_rt_ao.h"
#include "vulkan_rsp_fixture.h"
#include "opening_sky_capture.h"

using namespace plume;
using namespace RT64;

namespace {
    uint32_t Width = 64, Height = 64;
    size_t checks = 0;
    struct FixtureWaterPipelines : Wr64RTWaterPipelines {
        RenderShaderFormat format;
        explicit FixtureWaterPipelines(RenderShaderFormat selected) : format(selected) { }
        bool prepare(RenderDevice *device, const RenderPipelineLayout *layout,
            const RenderMultisampling &samples, bool hdr, bool sky = false, bool async = false) {
            return Wr64RTWaterPipelines::prepare(device, layout, samples, hdr, sky, async, format);
        }
    };
    struct FixtureWorldPipelines : Wr64RTWorldShadowPipelines {
        RenderShaderFormat format;
        explicit FixtureWorldPipelines(RenderShaderFormat selected) : format(selected) { }
        bool prepare(RenderDevice *device, const RenderPipelineLayout *layout,
            const RenderMultisampling &samples, bool hdr, bool async = false) {
            return Wr64RTWorldShadowPipelines::prepare(device, layout, samples, hdr, async, format);
        }
    };
    struct VulkanValidation {
        VkInstance instance = VK_NULL_HANDLE;
        VkDebugUtilsMessengerEXT messenger = VK_NULL_HANDLE;
        std::atomic_uint errors{0}, warnings{0};
        static VKAPI_ATTR VkBool32 VKAPI_CALL callback(VkDebugUtilsMessageSeverityFlagBitsEXT severity,
            VkDebugUtilsMessageTypeFlagsEXT, const VkDebugUtilsMessengerCallbackDataEXT *message, void *data) {
            auto &self = *static_cast<VulkanValidation *>(data);
            if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) ++self.errors;
            else if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) ++self.warnings;
            std::fprintf(stderr, "VULKAN VALIDATION %s: %s\n",
                severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT ? "ERROR" : "WARNING", message->pMessage);
            return VK_FALSE;
        }
        bool install(VkInstance selected) {
            if (!vkCreateDebugUtilsMessengerEXT || !vkDestroyDebugUtilsMessengerEXT) return false;
            instance = selected;
            VkDebugUtilsMessengerCreateInfoEXT info{VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT};
            info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            info.pfnUserCallback = callback;
            info.pUserData = this;
            return vkCreateDebugUtilsMessengerEXT(instance, &info, nullptr, &messenger) == VK_SUCCESS;
        }
        ~VulkanValidation() {
            if (messenger) vkDestroyDebugUtilsMessengerEXT(instance, messenger, nullptr);
        }
    };
    void require(bool value, const char *message) {
        ++checks;
        if (!value) throw std::runtime_error(message);
    }
    struct FixtureWorker : RenderWorker {
        bool vulkan;
        size_t waitCount = 0;
        FixtureWorker(RenderDevice *device, bool selectedVulkan)
            : RenderWorker(device, "Headless production water raster test", RenderCommandListType::DIRECT), vulkan(selectedVulkan) { }
        void wait() {
            if (vulkan) ++waitCount;
            // The production backend now propagates failed completion instead
            // of allowing stale readback comparisons. Exercise that exact path.
            RenderWorker::wait();
        }
    };
    void fill(RenderBuffer *buffer, const void *data, size_t size) {
        const RenderRange noRead(0, 0);
        void *mapped = buffer->map(0, &noRead);
        require(mapped != nullptr, "Could not map an upload buffer");
        std::memcpy(mapped, data, size);
        const RenderRange written(0, size);
        buffer->unmap(0, &written);
    }
    struct CelestialRecord {
        float bounds[4] = {};
        float uv[4] = {};
        float color[4] = {};
        uint32_t meta[4] = {};
    };
    static_assert(sizeof(CelestialRecord) == 64, "Celestial record layout mismatch");
    static_assert(sizeof(CelestialRecord) == sizeof(interop::Wr64RTCelestialRecord) &&
        WR64_RT_CELESTIAL_MAX == 20 && WR64_RT_CELESTIAL_ALPHA_VECTORS == 129,
        "Headless celestial payload no longer matches the production shared declaration");
    struct Params {
        float camera[4] = {0, 10, -10, 1};
        uint32_t debugView = 0;
        float strength = 1;
        uint32_t enabled = 0;
        uint32_t smoothNormals = 0;
        uint32_t sky[4] = {9, 2, 4, 0};
        float skyCamera[4] = {0, 10, -10, 1};
        float skyCloudParams[4] = {0, 0, 0, 0};
        uint32_t skyBackdrop[4] = {};
        float skyBackdropCamera[4] = {};
        float celestialProjection[3][4] = {};
        uint32_t celestialInfo[4] = {};
        CelestialRecord celestial[20] = {};
        uint32_t celestialAlpha[129][4] = {};
        float shadowLight[4] = {};
        float shadowOptions[4] = {};
        uint32_t sceneOptions[4] = {};
        float actorBoundsMin[4][4] = {};
        float actorBoundsMax[4][4] = {};
        float aoOptions[4] = {};
        float qualityOptions[4] = {};
    };
    static_assert(sizeof(Params) == 3728, "Reflection constant layout mismatch");
    // Keep readbacks on the heap: independent fixture snapshots collectively
    // exceed the default Windows executable stack once the sky suite is added.
    using Pixels = std::vector<uint8_t>;
    std::array<uint8_t, 4> center(const Pixels &pixels) {
        const size_t offset = ((Height / 2) * Width + Width / 2) * 4;
        return { pixels[offset], pixels[offset + 1], pixels[offset + 2], pixels[offset + 3] };
    }
    bool nearByte(uint8_t a, uint8_t b, int tolerance = 2) { return std::abs(int(a) - int(b)) <= tolerance; }
    template<class Request> const RenderPipeline* awaitAsyncPipeline(const char* name,Request request) {
        const auto start=std::chrono::steady_clock::now();size_t polls=0;double maxRequestMs=0;
        const RenderPipeline* pipeline=nullptr;
        while(!pipeline) {
            const auto t=std::chrono::steady_clock::now();pipeline=request();++polls;
            const double duration=std::chrono::duration<double,std::milli>(std::chrono::steady_clock::now()-t).count();
            maxRequestMs=std::max(maxRequestMs,duration);
            if(std::chrono::steady_clock::now()-start>std::chrono::seconds(120))throw std::runtime_error("Async production pipeline never became ready");
            if(!pipeline)std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        const double readyMs=std::chrono::duration<double,std::milli>(std::chrono::steady_clock::now()-start).count();
        std::printf("async %s: polls%zu ready_ms%.3f max_request_ms%.6f\n",name,polls,readyMs,maxRequestMs);
        require(maxRequestMs<100,"An async pipeline request synchronously waited for driver compilation");
        return pipeline;
    }
    void writePPM(const std::string &path, const Pixels &pixels) {
        std::ofstream output(path, std::ios::binary);
        output << "P6\n" << Width << ' ' << Height << "\n255\n";
        for (size_t i = 0; i < pixels.size(); i += 4) output.write(reinterpret_cast<const char *>(&pixels[i]), 3);
    }
    void fillSamplers(RenderDevice *device, SamplerSet &set, RenderFilter filter) {
        std::unique_ptr<RenderSampler> *entries[] = {
            &set.wrapWrap, &set.wrapMirror, &set.wrapClamp,
            &set.mirrorWrap, &set.mirrorMirror, &set.mirrorClamp,
            &set.clampWrap, &set.clampMirror, &set.clampClamp
        };
        const RenderTextureAddressMode modes[] = {
            RenderTextureAddressMode::WRAP, RenderTextureAddressMode::MIRROR, RenderTextureAddressMode::CLAMP
        };
        for (uint32_t i = 0; i < 9; ++i) {
            RenderSamplerDesc desc;
            desc.minFilter = filter; desc.magFilter = filter;
            desc.addressU = modes[i / 3]; desc.addressV = modes[i % 3];
            desc.addressW = RenderTextureAddressMode::CLAMP;
            desc.mipLODBias = -0.25f;
            desc.anisotropyEnabled = filter == RenderFilter::LINEAR;
            *entries[i] = device->createSampler(desc);
        }
    }
#include "vulkan_as_fixture.h"
#include "vulkan_failure_fixture.h"
#include "vulkan_upload_sync_fixture.h"
#include "vulkan_native_fb_fixture.h"
#include "vulkan_rsp_process_fixture.h"
#include "vulkan_lifecycle_fixture.h"
#include "raster_sky_fixture.inl"
#include "raster_shadow_fixture.inl"
#include "planar_reflection_fixture.inl"
#include "two_player_raster_fixture.inl"
}

int main(int argc, char **argv) {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    try {
        const std::string outputPrefix = argc > 1 ? argv[1] : "raster_gpu";
        auto selected = [&](const char *flag) {
            for (int i = 2; i < argc; ++i) if (std::string(argv[i]) == flag) return true;
            return false;
        };
        const bool vulkan = selected("--vulkan");
        const bool validateVulkan = selected("--vulkan-validation");
        const bool lifecycle = selected("--vulkan-msaa-lifecycle");
        const bool rspCompute = selected("--vulkan-rsp-compute");
        const bool combinedSky = selected("--vulkan-combined-sky");
        if (selected("--resolution-1280x720")) { Width = 1280; Height = 720; }
        if (selected("--resolution-2560x1440")) { Width = 2560; Height = 1440; }
        const bool largeRaster = Width != 64 || Height != 64;
        require(!largeRaster || ((rspCompute || combinedSky) && vulkan && selected("--msaa-4-only")), "Large rasters require a bounded Vulkan4x fixture");
        const auto graphicsAPI = vulkan ? UserConfiguration::GraphicsAPI::Vulkan : UserConfiguration::GraphicsAPI::D3D12;
        const auto shaderFormat = vulkan ? RenderShaderFormat::SPIRV : RenderShaderFormat::DXIL;
        const bool skyTransitionBaseline = selected("--sky-transition-baseline");
        const bool backdropCullBaseline = selected("--sky-backdrop-baseline");
        // Parked AO has its own unbuilt research shader. Production fixtures
        // exercise only the shaders actually shipped in the game.
        const bool aoExperiment = selected("--ao-experiment");
        const bool traceReadbacks = selected("--readback-trace");
        const bool qualityOptions = selected("--quality-options");
        // Observation instructions are excluded from the production shader.
        // Opt in only when loading a separately compiled diagnostic variant.
        const bool noSkyObservation = !selected("--sky-observation");
        const bool explicitQualityDefaults = traceReadbacks && selected("--explicit-quality-defaults");
        std::ofstream waterReadbackTrace;
        bool captureWaterReadbacks = true;
        if (selected("--water-readback-trace")) {
            waterReadbackTrace.open(outputPrefix + "-water-readbacks.rgba", std::ios::binary);
            require(waterReadbackTrace.good(), "Could not open accepted water readbacks");
        }
        std::ofstream actorReadbackTrace;
        bool captureActorReadbacks = false;
        if (selected("--actor-readback-trace")) {
            actorReadbackTrace.open(outputPrefix + "-actor-readbacks.rgba", std::ios::binary);
            require(actorReadbackTrace.good(), "Could not open actor preservation readbacks");
        }
        std::ofstream readbackTrace;
        if (traceReadbacks) {
            readbackTrace.open(outputPrefix + "-readbacks.rgba", std::ios::binary);
            require(readbackTrace.good(), "Could not open exact production readback trace");
        }
        std::unique_ptr<RenderInterface> renderInterface;
        if (vulkan) {
            auto instance = std::make_unique<VulkanInterface>();
            require(instance->isValid(), "Vulkan interface initialization failed");
            renderInterface = std::move(instance);
        }
        else {
            auto instance = std::make_unique<D3D12Interface>();
            require(instance->isValid(), "D3D12 interface initialization failed");
            renderInterface = std::move(instance);
        }
        VulkanValidation validation;
        if (validateVulkan) {
            uint32_t layerCount = 0;
            require(vulkan && vkEnumerateInstanceLayerProperties(&layerCount, nullptr) == VK_SUCCESS,
                "Could not enumerate Vulkan validation layers");
            std::vector<VkLayerProperties> layers(layerCount);
            require(vkEnumerateInstanceLayerProperties(&layerCount, layers.data()) == VK_SUCCESS,
                "Could not read Vulkan validation layers");
            require(std::any_of(layers.begin(), layers.end(), [](const VkLayerProperties &layer) {
                return std::strcmp(layer.layerName, "VK_LAYER_KHRONOS_validation") == 0;
            }), "VK_LAYER_KHRONOS_validation is not installed");
            const char *enabledLayers = std::getenv("VK_INSTANCE_LAYERS");
            require(enabledLayers && std::strstr(enabledLayers, "VK_LAYER_KHRONOS_validation"),
                "Vulkan validation requested without the isolated loader opt-in");
            const char *syncValidation = std::getenv("VK_LAYER_VALIDATE_SYNC");
            require(syncValidation && std::strcmp(syncValidation, "1") == 0,
                "Vulkan validation requires synchronization checking in the isolated test process");
            require(vulkan && validation.install(static_cast<VulkanInterface *>(renderInterface.get())->instance),
                "Vulkan validation messenger unavailable in this Plume build");
        }
        { // Destroy all GPU resources/device while the validation messenger is live.
        auto device = renderInterface->createDevice("");
        require(device != nullptr, "Graphics device initialization failed");
        std::printf("Headless backend: %s, device: %s, validation: %s\n", vulkan ? "Vulkan" : "D3D12",
            device->getDescription().name.c_str(), validateVulkan ? "core + synchronization" : "disabled");
        if (vulkan) std::printf("Vulkan sample-location capability: %s\n", device->getCapabilities().sampleLocations ? "supported" : "unavailable");
        auto deviceStatus = [&](const char *stage) {
            if (vulkan) {
                require(static_cast<VulkanDevice *>(device.get())->isValid(), stage);
                require(validation.errors.load() == 0, "Vulkan validation reported an error");
            }
            else {
                const HRESULT reason = static_cast<D3D12Device *>(device.get())->d3d->GetDeviceRemovedReason();
                if (FAILED(reason)) std::fprintf(stderr, "%s: device removed 0x%08X\n", stage, unsigned(reason));
                require(SUCCEEDED(reason), stage);
            }
        };
        if (selected("--two-player-raster-only")) {
            require(!vulkan, "Two-player raster fixture requires D3D12");
            FixtureWorker worker(device.get(), false);
            verifyTwoPlayerRaster(device.get(), worker, outputPrefix);
            deviceStatus("After two-player raster fixture");
            std::printf("PASS: %zu two-player raster checks; no AS allocation, build or binding.\n", checks);
            return 0;
        }
        if (selected("--planar-reflections-only")) {
            require(!vulkan, "Planar reflection fixture requires D3D12");
            FixtureWorker worker(device.get(), false);
            verifyPlanarReflections(device.get(), worker, outputPrefix);
            deviceStatus("After planar reflection fixture");
            std::printf("PASS: %zu planar reflection checks; no AS descriptor, allocation, build or binding.\n", checks);
            return 0;
        }
        if (selected("--raster-shadows-only")) {
            require(!vulkan, "Raster-shadow first fixture requires D3D12");
            FixtureWorker worker(device.get(), false);
            verifyRasterShadows(device.get(), worker, outputPrefix);
            deviceStatus("After raster-only shadow fixture");
            std::printf("PASS: %zu raster-only shadow checks; no AS descriptor, allocation, build or binding.\n", checks);
            return 0;
        }
        if (selected("--raster-sky-only")) {
            require(!vulkan, "Raster-sky first fixture requires D3D12");
            FixtureWorker worker(device.get(), false);
            verifyRasterSky(device.get(), worker, outputPrefix);
            deviceStatus("After raster-only sky fixture");
            std::printf("PASS: %zu raster-only sky checks; no AS descriptor, allocation, build or binding.\n", checks);
            return 0;
        }
        if (!Wr64RTWaterPipelines::supported(device.get(), graphicsAPI)) {
            std::puts(vulkan ? "SKIP: production water pipeline requires Vulkan inline ray queries." :
                "SKIP: production water pipeline capability check requires DXR 1.1 / SM6.5.");
            return 77;
        }
        FixtureWorker worker(device.get(), vulkan);
        if (selected("--vulkan-rsp-process-only")) {
            require(vulkan && validateVulkan, "RSPProcess fixture requires Vulkan core/sync validation");
            verifyVulkanRSPProcess(device.get(), worker, validation);
            require(validation.errors.load() == 0 && validation.warnings.load() == 0, "RSPProcess emitted validation messages");
            std::printf("PASS: %zu RSPProcess checks; Vulkan validation errors=%u warnings=%u.\n",
                checks, validation.errors.load(), validation.warnings.load());
            return 0;
        }
        if (selected("--vulkan-native-depth-ms-only")) {
            require(vulkan && validateVulkan, "Native 4x depth fixture requires Vulkan core/sync validation");
            verifyVulkanNativeDepthMS(device.get(), worker, validation);
            require(validation.errors.load() == 0 && validation.warnings.load() == 0, "Native 4x depth emitted validation messages");
            std::printf("PASS: %zu native 4x depth checks; Vulkan validation errors=%u warnings=%u.\n",
                checks, validation.errors.load(), validation.warnings.load());
            return 0;
        }
        if (selected("--vulkan-native-fb-only")) {
            require(vulkan && validateVulkan, "Native framebuffer fixture requires Vulkan core/sync validation");
            verifyVulkanNativeFramebuffer(device.get(), worker, validation);
            require(validation.errors.load() == 0 && validation.warnings.load() == 0, "Native framebuffer emitted validation messages");
            std::printf("PASS: %zu native framebuffer checks; Vulkan validation errors=%u warnings=%u.\n",
                checks, validation.errors.load(), validation.warnings.load());
            return 0;
        }
        if (selected("--vulkan-upload-sync-only")) {
            require(vulkan, "Vulkan upload synchronization requires Vulkan backend");
            verifyVulkanUploadSynchronization(device.get(), worker);
            require(validation.errors.load() == 0 && validation.warnings.load() == 0, "Vulkan upload synchronization emitted validation messages");
            std::printf("PASS: %zu upload synchronization checks; Vulkan validation errors=%u warnings=%u.\n",
                checks, validation.errors.load(), validation.warnings.load());
            return 0;
        }
        if (selected("--vulkan-error-contract-only")) {
            require(vulkan, "Vulkan error contract requires Vulkan backend");
            verifyVulkanFailurePropagation(worker);
            return 0;
        }
        if (vulkan && !rspCompute && !combinedSky) {
            verifyVulkanOffsetAS(device.get(), worker);
            deviceStatus("After Vulkan multi-geometry and offset-scratch AS build");
        }
        std::vector<std::unique_ptr<RenderBuffer>> buffers;
        auto upload = [&](const void *data, size_t size, RenderBufferFlags flags) {
            const uint64_t allocation = (flags & RenderBufferFlag::CONSTANT) ? (size + 255) & ~uint64_t(255) : size;
            auto buffer = device->createBuffer(RenderBufferDesc::UploadBuffer(allocation, flags));
            require(buffer != nullptr, "Could not allocate upload buffer");
            fill(buffer.get(), data, size);
            RenderBuffer *result = buffer.get();
            buffers.push_back(std::move(buffer));
            return result;
        };

        SamplerLibrary samplers;
        fillSamplers(device.get(), samplers.nearest, RenderFilter::NEAREST);
        fillSamplers(device.get(), samplers.linear, RenderFilter::LINEAR);
        {
            RenderDescriptorSetBuilder mixed;
            mixed.begin();
            const uint32_t cbv = mixed.addConstantBuffer(0);
            const uint32_t fixed0 = mixed.addImmutableSampler(1, samplers.nearest.wrapWrap.get());
            const uint32_t dynamic = mixed.addSampler(2);
            const uint32_t srv = mixed.addTexture(3);
            const uint32_t fixed1 = mixed.addImmutableSampler(4, samplers.nearest.clampClamp.get());
            const uint32_t raw = mixed.addByteAddressBuffer(5);
            mixed.end();
            auto descriptors = mixed.create(device.get());
            if (vulkan) {
                const auto *set = static_cast<VulkanDescriptorSet *>(descriptors.get())->setLayout;
                require(set && set->vk, "Vulkan mixed descriptor layout creation failed");
                require(set->setBindings[set->descriptorBindingIndices[cbv]].binding == 0 &&
                    set->setBindings[set->descriptorBindingIndices[srv]].binding == 3 &&
                    set->setBindings[set->descriptorBindingIndices[raw]].binding == 5,
                    "Vulkan immutable samplers changed explicit resource bindings");
                require(set->setBindings[set->descriptorBindingIndices[fixed0]].pImmutableSamplers &&
                    set->setBindings[set->descriptorBindingIndices[fixed1]].pImmutableSamplers &&
                    !set->setBindings[set->descriptorBindingIndices[dynamic]].pImmutableSamplers,
                    "Vulkan fixed/mutable sampler distinction was lost");
            }
            else {
            const auto *nativeMixed = static_cast<D3D12DescriptorSet *>(descriptors.get());
            require(nativeMixed->viewAllocation.count == 3 && nativeMixed->samplerAllocation.count == 1,
                "Static samplers consumed descriptor heap space");
            require(nativeMixed->descriptorHeapIndices[cbv] == 0 &&
                nativeMixed->descriptorHeapIndices[srv] == 1 && nativeMixed->descriptorHeapIndices[raw] == 2,
                "Interleaved static/dynamic samplers shifted view descriptors");
            require(nativeMixed->descriptorHeapIndices[fixed0] == UINT32_MAX &&
                nativeMixed->descriptorHeapIndices[fixed1] == UINT32_MAX &&
                nativeMixed->descriptorHeapIndices[dynamic] == 0,
                "Logical descriptor indices or mutable sampler offsets changed");
            }
            descriptors->setSampler(dynamic, samplers.nearest.wrapWrap.get());
            deviceStatus("After mutable sampler update");
        }
        FramebufferRendererDescriptorCommonSet common(samplers, true, device.get());
        // Regression: immutable samplers s7..s24 must not consume CBV/SRV
        // heap entries. Otherwise native pre-sampler RDP color works while
        // b25/t27/t40 silently read zero and reflections remain disabled.
        if (vulkan) {
            const auto *set = static_cast<VulkanDescriptorSet *>(common.get())->setLayout;
            require(set && set->vk, "Vulkan production descriptor layout creation failed");
            require(set->setBindings[set->descriptorBindingIndices[common.RtParams]].binding == 25 &&
                set->setBindings[set->descriptorBindingIndices[common.posBuffer]].binding == 27 &&
                set->setBindings[set->descriptorBindingIndices[common.interleavedRasters]].binding == 40,
                "Vulkan production reflection bindings disagree with SPIR-V registers");
        }
        else {
        const auto *nativeCommon = static_cast<D3D12DescriptorSet *>(common.get());
        require(nativeCommon->descriptorHeapIndices[common.RtParams] == 6 &&
            nativeCommon->descriptorHeapIndices[common.posBuffer] == 8 &&
            nativeCommon->descriptorHeapIndices[common.interleavedRasters] == 21,
            "Immutable samplers shifted the production reflection descriptors");
        }
        FramebufferRendererDescriptorTextureSet textures(device.get(), combinedSky ? 128 : 2);
        FramebufferRendererDescriptorFramebufferSet framebufferSet(device.get());
        RenderPipelineLayoutBuilder layoutBuilder;
        layoutBuilder.begin(false, true);
        layoutBuilder.addPushConstant(0, 0, sizeof(interop::RasterParams), RenderShaderStageFlag::VERTEX | RenderShaderStageFlag::PIXEL);
        layoutBuilder.addDescriptorSet(common);
        layoutBuilder.addDescriptorSet(textures);
        layoutBuilder.addDescriptorSet(textures);
        layoutBuilder.addDescriptorSet(framebufferSet);
        layoutBuilder.end();
        auto layout = layoutBuilder.create(device.get());
        require(layout != nullptr, "Could not create the production raster descriptor layout");

        // The quad's raster coordinates correspond to a flat world-space water
        // surface. The separate red triangle is reached by its reflected rays.
        float screen[16][4] = {
            {0, 0, .5f, 1}, {64, 0, .5f, 1}, {64, 64, .5f, 1}, {0, 64, .5f, 1},
            {0, 0, 0, 1}, {0, 0, 0, 1}, {0, 0, 0, 1}
        };
        float world[16][4] = {
            {-5, 0, 5, 1}, {5, 0, 5, 1}, {5, 0, -5, 1}, {-5, 0, -5, 1},
            {-40, -10, 10, 1}, {40, -10, 10, 1}, {0, 50, 10, 1}
        };
        float uv[16][2] = {};
        float colors[16][4] = {
            {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1},
            {1, 0, 0, 1}, {1, 0, 0, 1}, {1, 0, 0, 1}
        };
        // Project a finite, non-planar sky fan onto the same screen positions
        // reached by reflection from the flat water. Its clip W varies from
        // 1 to 4: a native-raster reference therefore catches accidental
        // affine interpolation, wrong camera origin, and double UV division.
        // The fan is deliberately excluded from the scene acceleration data.
        const float skyScreen[][3] = {
            {0, 0, 1}, {64, 0, 2}, {64, 64, 3}, {0, 64, 4}, {32, 32, 2}
        };
        for (uint32_t i = 0; i < 5; ++i) {
            const uint32_t v = 7 + i;
            const float x = skyScreen[i][0], y = skyScreen[i][1], w = skyScreen[i][2];
            screen[v][0] = x; screen[v][1] = y; screen[v][2] = .5f; screen[v][3] = w;
            world[v][0] = (x / 6.4f - 5.0f) * w;
            world[v][1] = 10.0f + 10.0f * w;
            world[v][2] = -10.0f + (15.0f - y / 6.4f) * w;
            world[v][3] = 1;
            uv[v][0] = x * .75f + 5; uv[v][1] = y * .75f + 5;
            colors[v][0] = x / 64.0f; colors[v][1] = y / 64.0f;
            colors[v][2] = .3f; colors[v][3] = 1;
        }
        uint32_t indices[54] = {0, 1, 2, 0, 2, 3, 4, 5, 6,
            7, 8, 11, 8, 9, 11, 9, 10, 11, 10, 7, 11};
        if (largeRaster) for (auto &vertex : screen) {
            vertex[0] *= float(Width) / 64;
            vertex[1] *= float(Height) / 64;
        }
        auto positions = device->createBuffer(RenderBufferDesc::DefaultBuffer(sizeof(world),
            RenderBufferFlag::STORAGE | RenderBufferFlag::UNORDERED_ACCESS | RenderBufferFlag::ACCELERATION_STRUCTURE_INPUT));
        auto faces = device->createBuffer(RenderBufferDesc::DefaultBuffer(sizeof(indices),
            RenderBufferFlag::INDEX | RenderBufferFlag::STORAGE | RenderBufferFlag::ACCELERATION_STRUCTURE_INPUT));
        RenderBuffer *worldUpload = upload(world, sizeof(world), 0);
        RenderBuffer *indexUpload = upload(indices, sizeof(indices), 0);
        RenderBuffer *screenBuffer = upload(screen, sizeof(screen), RenderBufferFlag::VERTEX);
        RenderBuffer *uvBuffer = upload(uv, sizeof(uv), RenderBufferFlag::VERTEX | RenderBufferFlag::STORAGE);
        RenderBuffer *colorBuffer = upload(colors, sizeof(colors), RenderBufferFlag::VERTEX | RenderBufferFlag::STORAGE);

        interop::FrameParams frame{};
        interop::FramebufferParams fb{};
        fb.resolution = hlslpp::float2(float(Width), float(Height));
        fb.resolutionScale = hlslpp::float2(1, 1);
        interop::RenderIndices renderIndices[4] = {{0, 0, 0, 0, 0}, {1, 6, 0, 0, 0}, {2, 9, 0, 1, 0}, {3, 3, 0, 0, 0}};
        interop::RDPParams rdp[4]{};
        rdp[0].primColor = hlslpp::float4(.1f, .2f, .7f, 1);
        rdp[1].primColor = hlslpp::float4(1, .05f, .02f, 1);
        rdp[2].primColor = hlslpp::float4(.05f, .9f, .1f, 1);
        rdp[3] = rdp[0];
        interop::RenderParams params[4]{};
        for (auto &p : params) {
            // (0 - 0) * 0 + primitive, for RGB and alpha in both cycles.
            p.ccL = (8u << 20) | (31u << 15) | (7u << 12) | (7u << 9) | (8u << 5) | 31u;
            p.ccH = (8u << 28) | (8u << 24) | (7u << 21) | (7u << 18) | (3u << 15) |
                (7u << 12) | (3u << 9) | (3u << 6) | (7u << 3) | 3u;
            p.flags.NoN = 1;
            p.flags.smoothShade = 1;
        }
        interop::RDPTile rdpTile{};
        rdpTile.shifts = rdpTile.shiftt = 1;
        rdpTile.lrs = rdpTile.lrt = 63 * 4;
        rdpTile.cms = rdpTile.cmt = 2;
        rdpTile.nativeSampler = NATIVE_SAMPLER_CLAMP_CLAMP;
        interop::GPUTile gpuTile{};
        gpuTile.ulScale = gpuTile.tcScale = hlslpp::float2(1, 1);
        gpuTile.textureDimensions = hlslpp::float3(64, 64, 1);
        // A smooth two-dimensional texture makes a wrong directional or
        // perspective mapping measurable, without texel-boundary tolerances.
        constexpr uint32_t SkyTextureSize = 64;
        Pixels skyTexels(SkyTextureSize * SkyTextureSize * 4);
        for (uint32_t y = 0; y < SkyTextureSize; ++y) for (uint32_t x = 0; x < SkyTextureSize; ++x) {
            const uint32_t p = (y * SkyTextureSize + x) * 4;
            skyTexels[p] = uint8_t(20 + x * 3);
            skyTexels[p + 1] = uint8_t(30 + y * 3);
            skyTexels[p + 2] = uint8_t(210 - x - y);
            skyTexels[p + 3] = 255;
        }
        auto skyTexture = device->createTexture(RenderTextureDesc::Texture2D(SkyTextureSize, SkyTextureSize, 1, RenderFormat::R8G8B8A8_UNORM));
        auto skyTextureView = skyTexture->createTextureView(RenderTextureViewDesc::Texture2D(RenderFormat::R8G8B8A8_UNORM));
        auto skyTextureUpload = upload(skyTexels.data(), skyTexels.size(), 0);
        textures.setTexture(0, skyTexture.get(), RenderTextureLayout::SHADER_READ, skyTextureView.get());
        textures.setTexture(1, skyTexture.get(), RenderTextureLayout::SHADER_READ, skyTextureView.get());
        if (combinedSky) for (uint32_t i = 2; i < 128; ++i)
            textures.setTexture(i, skyTexture.get(), RenderTextureLayout::SHADER_READ, skyTextureView.get());
        Params reflection;
        RenderBuffer *reflectionBuffer = upload(&reflection, sizeof(reflection), RenderBufferFlag::CONSTANT);
        RenderBuffer *renderParamsBuffer = upload(params, sizeof(params), RenderBufferFlag::STORAGE);
        RenderBuffer *renderIndicesBuffer = upload(renderIndices, sizeof(renderIndices), RenderBufferFlag::STORAGE);
        RenderBuffer *rdpTileBuffer = upload(&rdpTile, sizeof(rdpTile), RenderBufferFlag::STORAGE);
        RenderBuffer *rdpParamsBuffer = upload(rdp, sizeof(rdp), RenderBufferFlag::STORAGE);
        RenderBuffer *gpuTileBuffer = upload(&gpuTile, sizeof(gpuTile), RenderBufferFlag::STORAGE);
        common.setBuffer(common.FrParams, upload(&frame, sizeof(frame), RenderBufferFlag::CONSTANT), sizeof(frame));
        common.setBuffer(common.instanceRDPParams, rdpParamsBuffer, sizeof(rdp), RenderBufferStructuredView(sizeof(interop::RDPParams)));
        common.setBuffer(common.RDPTiles, rdpTileBuffer, sizeof(rdpTile), RenderBufferStructuredView(sizeof(rdpTile)));
        common.setBuffer(common.GPUTiles, gpuTileBuffer, sizeof(gpuTile), RenderBufferStructuredView(sizeof(gpuTile)));
        common.setBuffer(common.instanceRenderIndices, renderIndicesBuffer, sizeof(renderIndices), RenderBufferStructuredView(sizeof(interop::RenderIndices)));
        common.setBuffer(common.DynamicRenderParams, renderParamsBuffer, sizeof(params), RenderBufferStructuredView(sizeof(interop::RenderParams)));
        common.setBuffer(common.RtParams, reflectionBuffer, sizeof(reflection));
        common.setBuffer(common.posBuffer, positions.get(), sizeof(world));
        common.setBuffer(common.genTexCoordBuffer, uvBuffer, sizeof(uv));
        common.setBuffer(common.shadedColBuffer, colorBuffer, sizeof(colors));
        common.setBuffer(common.indexBuffer, faces.get(), sizeof(indices));
        const std::array<uint32_t, 28> emptyAdjacency{};
        common.setBuffer(common.wr64WaterAdjacency,
            upload(emptyAdjacency.data(), sizeof(emptyAdjacency), RenderBufferFlag::STORAGE), sizeof(emptyAdjacency));
        constexpr uint32_t SkyCaptureCapacity = 512, SkyCaptureRecordWords = 32;
        constexpr size_t SkyCaptureBytes = 16 + SkyCaptureCapacity * SkyCaptureRecordWords * sizeof(uint32_t);
        const std::vector<uint32_t> zeroSkyCapture(SkyCaptureBytes / sizeof(uint32_t));
        auto skyCapture = device->createBuffer(RenderBufferDesc::DefaultBuffer(SkyCaptureBytes,
            RenderBufferFlag::STORAGE | RenderBufferFlag::UNORDERED_ACCESS));
        auto skyCaptureReadback = device->createBuffer(RenderBufferDesc::ReadbackBuffer(SkyCaptureBytes));
        auto skyCaptureUpload = upload(zeroSkyCapture.data(), SkyCaptureBytes, 0);
        require(skyCapture && skyCaptureReadback, "Could not allocate the bounded sky diagnostic buffers");
        common.setBuffer(common.wr64SkyCapture, skyCapture.get(), SkyCaptureBytes);
        std::vector<uint32_t> capturedSkyWords;
        bool readSkyCapture = false;
        framebufferSet.setBuffer(framebufferSet.FbParams, upload(&fb, sizeof(fb), RenderBufferFlag::CONSTANT), sizeof(fb));

        Wr64RTScene scene;
        require(scene.prepare(device.get(), positions.get(), faces.get(), 14, 27, {{6, 3, 1}}), scene.lastError().c_str());
        common.setAccelerationStructure(common.SceneBVH, scene.accelerationStructure());
            common.setBuffer(common.wr64FenceProxy,scene.proxyBuffer(),scene.proxyBufferSize());
        common.setBuffer(common.interleavedRasters, scene.geometryBuffer(), scene.geometryBufferSize(), RenderBufferStructuredView(16));
        worker.commandList->begin();
        const RenderBufferBarrier copy[] = {{positions.get(), RenderBufferAccess::WRITE}, {faces.get(), RenderBufferAccess::WRITE}};
        worker.commandList->barriers(RenderBarrierStage::COPY, copy, 2, nullptr, 0);
        worker.commandList->copyBufferRegion(positions->at(0), worldUpload->at(0), sizeof(world));
        worker.commandList->copyBufferRegion(faces->at(0), indexUpload->at(0), sizeof(indices));
        worker.commandList->barriers(RenderBarrierStage::COPY,
            RenderBufferBarrier(skyCapture.get(), RenderBufferAccess::WRITE));
        worker.commandList->copyBufferRegion(skyCapture->at(0), skyCaptureUpload->at(0), SkyCaptureBytes);
        worker.commandList->barriers(RenderBarrierStage::GRAPHICS,
            RenderBufferBarrier(skyCapture.get(), RenderBufferAccess::WRITE));
        worker.commandList->barriers(RenderBarrierStage::COPY, RenderTextureBarrier(skyTexture.get(), RenderTextureLayout::COPY_DEST));
        worker.commandList->copyTextureRegion(RenderTextureCopyLocation::Subresource(skyTexture.get()),
            RenderTextureCopyLocation::PlacedFootprint(skyTextureUpload, RenderFormat::R8G8B8A8_UNORM, SkyTextureSize, SkyTextureSize, 1, SkyTextureSize));
        worker.commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE,
            RenderTextureBarrier(skyTexture.get(), RenderTextureLayout::SHADER_READ));
        if (!rspCompute && !combinedSky) require(scene.recordBuild(&worker), "Could not record the production scene build");
        worker.commandList->end(); worker.execute(); worker.wait();
        deviceStatus("After scene build");

        auto rebuildPositions = [&]() {
            fill(worldUpload, world, sizeof(world));
            worker.commandList->begin();
            worker.commandList->barriers(RenderBarrierStage::COPY, RenderBufferBarrier(positions.get(), RenderBufferAccess::WRITE));
            worker.commandList->copyBufferRegion(positions->at(0), worldUpload->at(0), sizeof(world));
            require(scene.recordBuild(&worker), "Could not rebuild the fixture scene");
            worker.commandList->end(); worker.execute(); worker.wait();
            deviceStatus("After fixture scene rebuild");
        };
        auto setSkyTextureAlpha = [&](uint8_t alpha) {
            for (size_t i = 3; i < skyTexels.size(); i += 4) skyTexels[i] = alpha;
            fill(skyTextureUpload, skyTexels.data(), skyTexels.size());
            worker.commandList->begin();
            worker.commandList->barriers(RenderBarrierStage::COPY,
                RenderTextureBarrier(skyTexture.get(), RenderTextureLayout::COPY_DEST));
            worker.commandList->copyTextureRegion(RenderTextureCopyLocation::Subresource(skyTexture.get()),
                RenderTextureCopyLocation::PlacedFootprint(skyTextureUpload, RenderFormat::R8G8B8A8_UNORM, SkyTextureSize, SkyTextureSize, 1, SkyTextureSize));
            worker.commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE,
                RenderTextureBarrier(skyTexture.get(), RenderTextureLayout::SHADER_READ));
            worker.commandList->end(); worker.execute(); worker.wait();
            deviceStatus("After fixture sky texture update");
        };

        const RenderInputSlot inputSlots[] = {RenderInputSlot(0, 16), RenderInputSlot(1, 8), RenderInputSlot(2, 16)};
        const RenderVertexBufferView vertexBuffers[] = {
            RenderVertexBufferView(screenBuffer->at(0), sizeof(screen)),
            RenderVertexBufferView(uvBuffer->at(0), sizeof(uv)),
            RenderVertexBufferView(colorBuffer->at(0), sizeof(colors))
        };
        const RenderIndexBufferView indexView(faces->at(0), sizeof(indices), RenderFormat::R32_UINT);
        interop::RasterParams push{};
        push.screenScale = hlslpp::float2(1, 1);
        FixtureWaterPipelines pipelines(shaderFormat);
        std::unique_ptr<FixtureWorldPipelines> lifecycleWorld;
        if (lifecycle) lifecycleWorld = std::make_unique<FixtureWorldPipelines>(shaderFormat);
        uint32_t lifecycleGeneration = 0;
        const std::vector<uint32_t> sampleSequence = lifecycle ? std::vector<uint32_t>{4, 1, 4} : std::vector<uint32_t>{1, 4};

        for (uint32_t samples : sampleSequence) {
            if ((selected("--msaa-1-only") && samples != 1) || (selected("--msaa-4-only") && samples != 4)) continue;
            require((device->getSampleCountsSupported(RenderFormat::R8G8B8A8_UNORM) & samples) != 0,
                "Requested raster MSAA mode is unavailable");
            const bool nativeSampleLocations = selected("--native-sample-locations");
            const RenderMultisampling ms = nativeSampleLocations ?
                RasterShader::generateMultisamplingPattern(samples, device->getCapabilities().sampleLocations) : RenderMultisampling(samples);
            if (nativeSampleLocations && samples > 1) {
                require(ms.sampleCount == samples && ms.sampleLocationsEnabled, "Native MSAA sample locations are unavailable");
                std::printf("%ux MSAA uses the production RasterShader custom sample locations.\n", samples);
            }
            if (lifecycle) {
                // Every fixture submission is already fenced. Match application
                // reconfiguration ordering: join/reset caches, then replace the
                // shaderUber-owned layout, then recreate targets and prewarm.
                if (lifecycleGeneration) {
                    pipelines.reset();
                    lifecycleWorld->reset();
                    layout.reset();
                    layout = layoutBuilder.create(device.get());
                    require(layout != nullptr, "Lifecycle could not recreate the raster pipeline layout");
                }
                ++lifecycleGeneration;
                std::printf("Lifecycle generation%u: selecting %ux on same device/common descriptors/input buffers; layout=%p\n",
                    lifecycleGeneration, samples, static_cast<void *>(layout.get()));
                prewarmLifecyclePipelines(pipelines, *lifecycleWorld, device.get(), layout.get(), ms, lifecycleGeneration);
                deviceStatus("After lifecycle production prewarm");
            }
            if (rspCompute || combinedSky) {
                FixtureWorldPipelines prewarmWorld(shaderFormat);
                prewarmLifecyclePipelines(pipelines, prewarmWorld, device.get(), layout.get(), ms, 1);
                deviceStatus("After compute fixture production prewarm");
            }
            require(pipelines.prepare(device.get(), layout.get(), ms, false), "Production water PSO creation failed");
            deviceStatus("After production PSO creation");
            for (auto &p : params) p.flags.sampleCount = samples == 1 ? 0 : 2;
            fill(renderParamsBuffer, params, sizeof(params));
            auto target = device->createTexture(RenderTextureDesc::ColorTarget(Width, Height, RenderFormat::R8G8B8A8_UNORM, ms));
            auto resolved = device->createTexture(RenderTextureDesc::Texture2D(Width, Height, 1, RenderFormat::R8G8B8A8_UNORM));
            auto depthDesc = RenderTextureDesc::DepthTarget(Width, Height, RenderFormat::D32_FLOAT, ms);
            // Plume derives SAMPLE_LOCATIONS_COMPATIBLE_DEPTH from this shared
            // multisampling description when creating the native depth image.
            auto dummyDepth = device->createTexture(depthDesc);
            auto dummyDepthView = dummyDepth->createTextureView(RenderTextureViewDesc::Texture2D(RenderFormat::D32_FLOAT));
            auto readback = device->createBuffer(RenderBufferDesc::ReadbackBuffer(Width * Height * 4));
            const RenderTexture *attachments[] = {target.get()};
            // Vulkan requires the attachment formats declared by the PSO's
            // render pass even when this fixture selects depth testing off.
            // Production has D32 attached; retain D3D12's original readback path.
            auto framebuffer = device->createFramebuffer(RenderFramebufferDesc(attachments, 1,
                vulkan ? dummyDepth.get() : nullptr, vulkan));
            require(target && resolved && dummyDepth && readback && framebuffer, "Could not allocate raster targets");
            deviceStatus("After raster target allocation");
            framebufferSet.setTexture(framebufferSet.gBackgroundDepth, dummyDepth.get(), RenderTextureLayout::DEPTH_READ, dummyDepthView.get());

            RenderColor clearDestination(0, 0, 0, 0);
            RenderRect drawScissor(0, 0, Width, Height);
            const RenderPipeline *pipelineOverride = nullptr;
            const RenderPipeline *prepassPipeline = nullptr;
            const RenderVertexBufferView *vertexBufferOverride=nullptr;
            const RenderIndexBufferView *indexBufferOverride=nullptr;
            uint32_t prepassDrawIndex=0,prepassFirstIndex=0,prepassIndexCount=0;
            std::function<void()> beforeDrawRecord;
            auto render = [&](uint32_t enabled, uint32_t debugView, uint32_t drawIndex = 0,
                uint32_t firstIndex = 0, uint32_t indexCount = 6, bool splitWaterDraws = false) {
                reflection.enabled = enabled; reflection.debugView = debugView;
                if (explicitQualityDefaults) {
                    reflection.qualityOptions[0]=30000; reflection.qualityOptions[1]=16;
                }
                push.renderIndex = drawIndex;
                fill(reflectionBuffer, &reflection, sizeof(reflection));
                worker.commandList->begin();
                if (beforeDrawRecord) beforeDrawRecord();
                if (readSkyCapture) {
                    worker.commandList->barriers(RenderBarrierStage::COPY,
                        RenderBufferBarrier(skyCapture.get(), RenderBufferAccess::WRITE));
                    worker.commandList->copyBufferRegion(skyCapture->at(0), skyCaptureUpload->at(0), SkyCaptureBytes);
                }
                worker.commandList->barriers(RenderBarrierStage::GRAPHICS,
                    RenderBufferBarrier(skyCapture.get(), RenderBufferAccess::WRITE));
                worker.commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE,
                    RenderTextureBarrier(target.get(), RenderTextureLayout::COLOR_WRITE));
                worker.commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE,
                    RenderTextureBarrier(dummyDepth.get(), RenderTextureLayout::DEPTH_READ));
                worker.commandList->setFramebuffer(framebuffer.get());
                worker.commandList->clearColor(0, clearDestination);
                worker.commandList->setGraphicsPipelineLayout(layout.get());
                worker.commandList->setGraphicsDescriptorSet(common.get(), 0);
                worker.commandList->setGraphicsDescriptorSet(textures.get(), 1);
                worker.commandList->setGraphicsDescriptorSet(textures.get(), 2);
                worker.commandList->setGraphicsDescriptorSet(framebufferSet.get(), 3);
                worker.commandList->setGraphicsPushConstants(0, &push);
                worker.commandList->setPipeline(pipelineOverride ? pipelineOverride : pipelines.get(false, false, false));
                worker.commandList->setViewports(RenderViewport(0, 0, float(Width), float(Height)));
                worker.commandList->setScissors(drawScissor);
                worker.commandList->setVertexBuffers(0, vertexBufferOverride?vertexBufferOverride:vertexBuffers, 3, inputSlots);
                worker.commandList->setIndexBuffer(indexBufferOverride?indexBufferOverride:&indexView);
                if(prepassPipeline) {
                    push.renderIndex=prepassDrawIndex;
                    worker.commandList->setGraphicsPushConstants(0,&push);
                    worker.commandList->setPipeline(prepassPipeline);
                    worker.commandList->drawIndexedInstanced(prepassIndexCount,1,prepassFirstIndex,0,0);
                    push.renderIndex=drawIndex;
                    worker.commandList->setGraphicsPushConstants(0,&push);
                    worker.commandList->setPipeline(pipelineOverride?pipelineOverride:pipelines.get(false,false,false));
                }
                if (splitWaterDraws) {
                    worker.commandList->drawIndexedInstanced(3, 1, 0, 0, 0);
                    push.renderIndex = 3;
                    worker.commandList->setGraphicsPushConstants(0, &push);
                    worker.commandList->drawIndexedInstanced(3, 1, 3, 0, 0);
                }
                else worker.commandList->drawIndexedInstanced(indexCount, 1, firstIndex, 0, 0);
                RenderTexture *source = target.get();
                if (samples > 1) {
                    const RenderTextureBarrier barriers[] = {
                        {target.get(), RenderTextureLayout::RESOLVE_SOURCE}, {resolved.get(), RenderTextureLayout::RESOLVE_DEST}
                    };
                    // Match RenderTarget::resolveFromTarget: Vulkan hardware
                    // resolves run in the transfer stage, not raster stages.
                    worker.commandList->barriers(vulkan ? RenderBarrierStage::COPY : RenderBarrierStage::GRAPHICS_AND_COMPUTE,
                        nullptr, 0, barriers, 2);
                    worker.commandList->resolveTexture(resolved.get(), target.get());
                    source = resolved.get();
                }
                worker.commandList->barriers(RenderBarrierStage::COPY, RenderTextureBarrier(source, RenderTextureLayout::COPY_SOURCE));
                // Plume's texture-to-buffer copy currently dereferences the
                // absent destination texture while setting sample positions.
                // Use the native readback command after its normal barriers.
                if (vulkan) {
                    // The abstraction has no image-to-buffer branch on Vulkan.
                    // Copy the resolved RGBA8 image with the same tight row order
                    // as D3D12 after the production COPY_SOURCE transition.
                    auto *commands = static_cast<VulkanCommandList *>(worker.commandList.get());
                    commands->endActiveRenderPass();
                    VkBufferImageCopy copy{};
                    copy.bufferRowLength = Width;
                    copy.bufferImageHeight = Height;
                    copy.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
                    copy.imageSubresource.layerCount = 1;
                    copy.imageExtent = {Width, Height, 1};
                    vkCmdCopyImageToBuffer(commands->vk, static_cast<VulkanTexture *>(source)->vk,
                        VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, static_cast<VulkanBuffer *>(readback.get())->vk, 1, &copy);
                }
                else {
                D3D12_TEXTURE_COPY_LOCATION dst{};
                dst.pResource = static_cast<D3D12Buffer *>(readback.get())->d3d;
                dst.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
                dst.PlacedFootprint.Footprint = {DXGI_FORMAT_R8G8B8A8_UNORM, Width, Height, 1, Width * 4};
                D3D12_TEXTURE_COPY_LOCATION src{};
                src.pResource = static_cast<D3D12Texture *>(source)->d3d;
                src.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
                static_cast<D3D12CommandList *>(worker.commandList.get())->d3d->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);
                }
                if (readSkyCapture) {
                    const RenderBufferBarrier captureBarriers[] = {
                        {skyCapture.get(), RenderBufferAccess::READ},
                        {skyCaptureReadback.get(), RenderBufferAccess::WRITE}
                    };
                    worker.commandList->barriers(RenderBarrierStage::COPY, captureBarriers, 2, nullptr, 0);
                    worker.commandList->copyBufferRegion(skyCaptureReadback->at(0), skyCapture->at(0), SkyCaptureBytes);
                }
                worker.commandList->end();
                const auto submissionStart = std::chrono::steady_clock::now();
                if (largeRaster) std::printf("Raster %ux%u %ux: submit fence%zu enabled%u debug%u draw%u\n", Width, Height, samples, worker.waitCount + 1, enabled, debugView, drawIndex);
                worker.execute(); worker.wait();
                if (largeRaster) std::printf("Raster completed fence%zu submit_to_fence_ms=%.3f\n", worker.waitCount,
                    std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - submissionStart).count());
                deviceStatus("After raster draw and readback copy");
                Pixels pixels(Width * Height * 4);
                const RenderRange read(0, pixels.size());
                const void *mapped = readback->map(0, &read);
                require(mapped != nullptr, "Raster readback mapping failed");
                std::memcpy(pixels.data(), mapped, pixels.size());
                const RenderRange noWrite(0, 0); readback->unmap(0, &noWrite);
                if (readSkyCapture) {
                    const RenderRange captureRange(0, SkyCaptureBytes);
                    const void *captureData = skyCaptureReadback->map(0, &captureRange);
                    require(captureData != nullptr, "Sky diagnostic readback mapping failed");
                    capturedSkyWords.resize(SkyCaptureBytes / sizeof(uint32_t));
                    std::memcpy(capturedSkyWords.data(), captureData, SkyCaptureBytes);
                    skyCaptureReadback->unmap(0, &noWrite);
                }
                if (traceReadbacks) {
                    readbackTrace.write(reinterpret_cast<const char *>(pixels.data()), std::streamsize(pixels.size()));
                    require(readbackTrace.good(), "Could not write exact production readback trace");
                }
                if (captureWaterReadbacks && waterReadbackTrace.is_open() &&
                    !pipelineOverride && !prepassPipeline && drawIndex == 0) {
                    waterReadbackTrace.write(reinterpret_cast<const char *>(pixels.data()), std::streamsize(pixels.size()));
                    require(waterReadbackTrace.good(), "Could not write accepted water readbacks");
                }
                if (captureActorReadbacks && actorReadbackTrace.is_open()) {
                    actorReadbackTrace.write(reinterpret_cast<const char *>(pixels.data()), std::streamsize(pixels.size()));
                    require(actorReadbackTrace.good(), "Could not write actor preservation readbacks");
                }
                return pixels;
            };

            if (selected("--planar-ray-sky-only")) {
                require(!vulkan && !largeRaster, "Planar ray-sky fixture requires bounded D3D12 rendering");
                captureWaterReadbacks = false;
#include "planar_ray_sky_fixture.inl"
                continue;
            }
            if (selected("--sky-methods-only")) {
                require(!vulkan && !largeRaster, "Sky methods fixture requires bounded D3D12 rendering");
                captureWaterReadbacks = false;
#include "sky_methods_fixture.inl"
                continue;
            }
            if (selected("--southern-ramp-only")) {
                require(!vulkan && !largeRaster, "Southern ramp fixture requires bounded D3D12 rendering");
                captureWaterReadbacks = false;
#include "southern_ramp_shadow_fixture.inl"
                continue;
            }
            if (selected("--solid-self-only")) {
                require(!vulkan && !largeRaster, "Solid self-shadow fixture requires bounded D3D12 rendering");
                captureWaterReadbacks = false;
#include "solid_self_shadow_fixture.inl"
                continue;
            }
            if (selected("--two-player-only")) {
                require(!vulkan && !largeRaster, "Two-player fixture requires bounded D3D12 rendering");
#include "two_player_fixture.inl"
                continue;
            }
            if (combinedSky) {
#include "vulkan_combined_sky_fixture.inl"
                continue;
            }
            if (rspCompute) {
                RT64Tests::VulkanRSPWorldFixture computed(device.get(), faces.get(), 27, world, 12, 4, {{6, 3, 1}});
                computed.bindReflection(common);
                beforeDrawRecord = [&]() { computed.record(worker); };
                require(pipelines.prepare(device.get(), layout.get(), ms, false, true), "Compute fixture sky PSO missing");
                reflection.sky[3] = 1;
                std::printf("%ux RSP fixture: first AS/query activation uses staged native input -> RSPWorldCS -> BLAS/TLAS -> sky PS in one submission.\n", samples);
                const auto computedSky = render(1, 0);
                computed.verifyPositions(worker);
                const auto computedSkyMask = render(1, 2);
                require(render(1, 0) == computedSky, "Repeated compute/AS sky draw changed identical pixels");

                // Build the independently CPU-uploaded scene only after the
                // first actual compute-to-query submission has completed.
                beforeDrawRecord = nullptr;
                common.setBuffer(common.posBuffer, positions.get(), sizeof(world));
                common.setAccelerationStructure(common.SceneBVH, scene.accelerationStructure());
                common.setBuffer(common.interleavedRasters, scene.geometryBuffer(), scene.geometryBufferSize(), RenderBufferStructuredView(16));
                common.setBuffer(common.wr64FenceProxy, scene.proxyBuffer(), scene.proxyBufferSize());
                worker.commandList->begin();
                require(scene.recordBuild(&worker), "Compute fixture CPU reference scene build failed");
                worker.commandList->end(); worker.execute(); worker.wait();
                const auto cpuSky = render(1, 0), cpuMask = render(1, 2);
                require(computedSky == cpuSky && computedSkyMask == cpuMask,
                    "Production RSPWorld output changed reflected sky/scene pixels compared with known CPU world positions");
                const auto native = render(0, 0);
                size_t effectPixels = 0;
                for (size_t p = 0; p < native.size(); p += 4)
                    effectPixels += computedSky[p] != native[p] || computedSky[p + 1] != native[p + 1] || computedSky[p + 2] != native[p + 2];
                require(effectPixels > Width * Height / 2, "Compute fixture lacks a visible positive reflection effect");

                computed.bindReflection(common);
                beforeDrawRecord = [&]() { computed.record(worker); };
                reflection.sky[3] = 0;
                require(pipelines.prepare(device.get(), layout.get(), ms, false), "Compute fixture stable PSO missing");
                const auto initial = render(1, 0);
                computed.setCasterOffset(1000);
                require(render(1, 0) == native, "Changed compute input did not move the reflector out of the AS ray path");
                computed.verifyPositions(worker);
                computed.setCasterOffset(0);
                require(render(1, 0) == initial, "Restored compute input did not restore exact reflection pixels");
                computed.verifyPositions(worker);
#include "vulkan_high_resolution_fixture.inl"
                beforeDrawRecord = nullptr;
                common.setBuffer(common.posBuffer, positions.get(), sizeof(world));
                common.setAccelerationStructure(common.SceneBVH, scene.accelerationStructure());
                common.setBuffer(common.interleavedRasters, scene.geometryBuffer(), scene.geometryBufferSize(), RenderBufferStructuredView(16));
                common.setBuffer(common.wr64FenceProxy, scene.proxyBuffer(), scene.proxyBufferSize());
                reflection.sky[3] = 0;
                std::printf("%ux RSP fixture PASS: exact CPU/compute sky+hit parity, %zu effect pixels, staged-input motion/miss/reset and position readbacks.\n", samples, effectPixels);
                continue;
            }

            const auto original = render(0, 0);
            const auto reflected = render(1, 0);
            const auto normals = render(1, 1);
            const auto hits = render(1, 2);
            const auto originalAgain = render(0, 0);
            const auto a = center(original), b = center(reflected), n = center(normals), h = center(hits);
            std::printf("%ux MSAA center: off=%u,%u,%u on=%u,%u,%u normal=%u,%u,%u hit=%u,%u,%u\n",
                samples, a[0], a[1], a[2], b[0], b[1], b[2], n[0], n[1], n[2], h[0], h[1], h[2]);
            require(nearByte(a[0], 26) && nearByte(a[1], 51) && nearByte(a[2], 178), "Disabled reflection did not preserve the native blue water color");
            require(b[0] > a[0] + 10 && b[2] < a[2] - 8, "Enabled production reflection shader did not change water toward the red scene hit");
            require(nearByte(n[0], 128) && nearByte(n[1], 255) && nearByte(n[2], 128), "Actual VS world-position interpolation or water normal debug output is wrong");
            require(nearByte(h[0], 0) && nearByte(h[1], 255) && nearByte(h[2], 153), "Actual raster RayQuery did not report the expected hit");
            require(original == originalAgain, "Turning the reflection shader back off did not restore identical pixels");
            size_t changed = 0;
            for (size_t pixel = 0; pixel < Width * Height; ++pixel) {
                const size_t i = pixel * 4;
                changed += original[i] != reflected[i] || original[i + 1] != reflected[i + 1] || original[i + 2] != reflected[i + 2];
            }
            require(changed > Width * Height / 2, "Reflection changed too few actual raster pixels");
            const std::string prefix = outputPrefix + "-" + std::to_string(samples) + "x-";
            writePPM(prefix + "original.ppm", original);
            writePPM(prefix + "reflection.ppm", reflected);
            writePPM(prefix + "normals.ppm", normals);
            writePPM(prefix + "hits.ppm", hits);
            std::printf("%ux MSAA: %zu/%u reflected pixels changed; toggle-off is byte-identical.\n", samples, changed, Width * Height);

            if (qualityOptions) {
                reflection.qualityOptions[0]=30000; reflection.qualityOptions[1]=16;
                require(render(1,0)==reflected && render(0,0)==original,
                    "Explicit default RT quality changed the validated stable output");
                float distanceVertices[3][4]; std::memcpy(distanceVertices,world+4,sizeof(distanceVertices));
                const float farTriangle[3][4]={{-40000,-10000,10000,1},{40000,-10000,10000,1},{0,50000,10000,1}};
                std::memcpy(world+4,farTriangle,sizeof(farTriangle)); rebuildPositions();
                Pixels nearLimit,farLimit;
                size_t distanceComparisons=0,nearHits=0,farHits=0;
                for(float limit:{7500.f,15000.f,22500.f,30000.f}) {
                    reflection.qualityOptions[0]=limit;
                    const auto mask=render(1,2);
                    size_t hitCount=0;
                    for(uint32_t y=2;y<62;++y) for(uint32_t x=2;x<62;++x) {
                        const double px=(x+.5)*10/Width-5,pz=5-(y+.5)*10/Height;
                        const double distance=(10000-pz)*std::sqrt(px*px+100+(pz+10)*(pz+10))/(pz+10);
                        if(std::abs(distance-limit)<.1)continue;
                        const size_t p=(y*Width+x)*4;
                        const bool hit=distance<limit;
                        require(mask[p+1]==(hit?255:0),"Reflection distance disagrees with analytic far-triangle intersection");
                        require(mask[p+3]==original[p+3],"Reflection distance changed native alpha/coverage");
                        hitCount+=hit; ++distanceComparisons;
                    }
                    require(render(1,2)==mask,"Reflection range flickered between identical frames");
                    if(limit==7500) {nearLimit=mask;nearHits=hitCount;}
                    if(limit==30000) {farLimit=mask;farHits=hitCount;}
                }
                require(nearHits==0&&farHits>3000,"Distance fixture does not distinguish near and far ranges");
                for(float invalid:{0.f,-1.f,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity(),40000.f}) {
                    reflection.qualityOptions[0]=invalid;
                    require(render(1,2)==farLimit,"Invalid/default reflection range did not safely preserve 30000 units");
                }
                reflection.qualityOptions[0]=1;
                require(render(1,2)==nearLimit,"Reflection range below the minimum did not clamp to 7500 units");
                std::memcpy(world+4,distanceVertices,sizeof(distanceVertices)); rebuildPositions();
                reflection.qualityOptions[0]=reflection.qualityOptions[1]=0;
                require(render(1,0)==reflected,"Distance fixture did not restore the native scene");
                std::printf("%ux RT quality distance: analytic comparisons%zu near-hits%zu far-hits%zu; finite/clamp/default guards passed.\n",samples,distanceComparisons,nearHits,farHits);
            }

            reflection.sky[3] = 1;
            require(render(1, 0) == reflected,
                "Default stable PS sampled experimental sky metadata");
            require(pipelines.prepare(device.get(), layout.get(), ms, false, true),
                "Experimental sky PSO creation failed");
            const auto foregroundWithSky = render(1, 0);
            size_t foregroundPixels = 0;
            bool foregroundPreserved = true;
            for (size_t p = 0; p < Width * Height; ++p) {
                const size_t i = p * 4;
                if (hits[i + 1] != 255) continue;
                ++foregroundPixels;
                for (size_t c = 0; c < 4; ++c) foregroundPreserved &= foregroundWithSky[i + c] == reflected[i + c];
            }
            require(foregroundPixels > Width * Height / 2 && foregroundPreserved,
                "Native sky replaced or contaminated an opaque foreground reflection");
            require(render(0, 0) == original, "Disabled RT sampled the enabled sky");

            // These use the production asynchronous cache adapter and actual
            // D3D12 objects, then render into this same target for an exact
            // comparison with the blocking cache path above. Fake long-job
            // tests separately guarantee nonblocking behavior on cold builds.
            {
                FixtureWaterPipelines asyncWater(shaderFormat);
                const auto* asyncStable=awaitAsyncPipeline("water-stable",[&]() {
                    if(!asyncWater.prepare(device.get(),layout.get(),ms,false,false,true))throw std::runtime_error("Async stable configuration failed");
                    return asyncWater.get(false,false,false);
                });
                pipelineOverride=asyncStable;
                require(render(1,0)==reflected&&render(0,0)==original,"Async stable pipeline changed native/reflection pixels");
                const auto* asyncSky=awaitAsyncPipeline("water-sky",[&]() {
                    if(!asyncWater.prepare(device.get(),layout.get(),ms,false,true,true))throw std::runtime_error("Async sky configuration failed");
                    return asyncWater.get(false,false,false);
                });
                pipelineOverride=asyncSky;
                require(render(1,0)==foregroundWithSky&&render(0,0)==original,"Async sky pipeline changed native/reflection pixels");
                require(asyncWater.prepare(device.get(),layout.get(),ms,false,false,true)&&asyncWater.get(false,false,false)==asyncStable,"Stable/sky configuration switching discarded a ready PSO");
                require(asyncWater.prepare(device.get(),layout.get(),ms,false,true,true)&&asyncWater.get(false,false,false)==asyncSky,"Returning to sky discarded its ready PSO");
                const RenderMultisampling otherSamples(samples==1?4:1);
                awaitAsyncPipeline("water-other-MSAA",[&]() {
                    if(!asyncWater.prepare(device.get(),layout.get(),otherSamples,false,true,true))throw std::runtime_error("Other MSAA configuration failed");
                    return asyncWater.get(false,false,false);
                });
                require(asyncWater.prepare(device.get(),layout.get(),ms,false,true,true)&&asyncWater.get(false,false,false)==asyncSky,"MSAA configuration switching invalidated the previous PSO");
                asyncWater.waitForPending();pipelineOverride=nullptr;
            }

            // Move only the opaque scene triangle out of the reflected view.
            // Its BLAS remains valid, but every water ray now tests the miss
            // fallback instead of relying on an empty or unbound TLAS.
            for (uint32_t v = 4; v < 7; ++v) world[v][0] += 1000;
            rebuildPositions();
            reflection.sky[3] = 0;
            require(render(1, 0) == original, "Scene miss without native sky changed the original water");
            reflection.sky[3] = 1;
            reflection.sky[2] = 0;
            require(render(1, 0) == original, "Empty native sky fan did not preserve fallback");
            reflection.sky[2] = 4;
            require(pipelines.prepare(device.get(), layout.get(), ms, false),
                "Could not switch back to default stable PS");
            require(render(1, 0) == original,
                "Default stable PS changed water on a miss with enabled sky metadata");
            require(pipelines.prepare(device.get(), layout.get(), ms, false, true),
                "Could not switch back to experimental sky PS");
            const auto solidSky = render(1, 0);
            const auto skyCoverage = render(1, 3);
            const auto s = center(solidSky), sc = center(skyCoverage);
            require(s[1] > a[1] + 2 && s[2] < a[2] - 2,
                "A scene miss did not reflect the green native sky draw material");
            require(nearByte(sc[0], 0) && nearByte(sc[1], 166) && nearByte(sc[2], 255),
                "Sky debug coverage did not distinguish sky from world and fallback");

            if (qualityOptions) {
                float directionalVertices[5][4];std::memcpy(directionalVertices,world+7,sizeof(directionalVertices));
                // Keep every native sky direction/UV but put its finite
                // geometry beyond even the maximum physical reflection range.
                for(uint32_t v=7;v<12;++v) for(uint32_t c=0;c<3;++c)
                    world[v][c]=reflection.skyCamera[c]+(world[v][c]-reflection.skyCamera[c])*10000;
                rebuildPositions();reflection.qualityOptions[0]=30000;
                const auto farDirectionalSky=render(1,0),farDirectionalCoverage=render(1,3);
                reflection.qualityOptions[0]=7500;
                require(render(1,0)==farDirectionalSky&&render(1,3)==farDirectionalCoverage,
                    "Physical reflection range incorrectly clipped the directional native sky");
                require(farDirectionalCoverage==skyCoverage,"Far sky fixture lost native directional coverage");
                std::memcpy(world+7,directionalVertices,sizeof(directionalVertices));rebuildPositions();
                reflection.qualityOptions[0]=0;
                require(render(1,0)==solidSky,"Directional range fixture did not restore native sky output");
            }

            // This reference goes through the actual embedded RasterVS and
            // RasterPS. It is not a second implementation of the lookup math.
            auto compareSkyReference = [&](const char *mode) {
                const auto nativeSky = render(0, 0, 2, 9, 12);
                const auto sampledSky = render(1, 4);
                size_t compared = 0, disagree = 0;
                int maxError = 0;
                for (uint32_t y = 4; y < Height - 4; ++y) for (uint32_t x = 4; x < Width - 4; ++x) {
                    const uint32_t i = (y * Width + x) * 4;
                    int error = 0;
                    for (size_t c = 0; c < 3; ++c) error = std::max(error,
                        std::abs(int(nativeSky[i + c]) - int(sampledSky[i + c])));
                    maxError = std::max(maxError, error);
                    disagree += error > 2;
                    ++compared;
                }
                std::printf("%ux MSAA %s sky/native raster: %zu/%zu pixels within2, maximum channel error%d.\n",
                    samples, mode, compared - disagree, compared, maxError);
                // Minor coverage differences at fan seams may affect a few
                // samples, but any directional/UV error changes whole regions.
                require(disagree < compared / 100 && maxError <= 5,
                    "Reflected native sky does not match the real raster reference");
                const std::string modePrefix = prefix + std::string(mode);
                writePPM(modePrefix + "-sky-native.ppm", nativeSky);
                writePPM(modePrefix + "-sky-reflected.ppm", sampledSky);
                return sampledSky;
            };
            compareSkyReference("primitive");

            const interop::RenderParams primitiveSkyParams = params[2];
            // Native TEXEL0 color/alpha, with two-dimensional variation and
            // changing clip W. Test both N64 texture-perspective states.
            params[2].ccH = (8u << 28) | (8u << 24) | (7u << 21) | (7u << 18) | (1u << 15) |
                (7u << 12) | (1u << 9) | (1u << 6) | (7u << 3) | 1u;
            params[2].flags.usesTexture0 = 1;
            params[2].flags.nativeSampler0 = NATIVE_SAMPLER_CLAMP_CLAMP;
            params[2].flags.cms0 = params[2].flags.cmt0 = 2;
            params[2].flags.linearFiltering = 1;
            params[2].omH = G_TP_PERSP | G_TF_BILERP;
            fill(renderParamsBuffer, params, sizeof(params));
            const auto perspectiveSky = compareSkyReference("texture-perspective");
            params[2].omH = G_TP_NONE | G_TF_BILERP;
            fill(renderParamsBuffer, params, sizeof(params));
            const auto noPerspectiveSky = compareSkyReference("texture-no-perspective");
            require(perspectiveSky != noPerspectiveSky, "Sky fixture did not distinguish native texture-perspective modes");

            // Use the real game's verified native sky material signature.
            // Its color is TEXEL0 * primitive, while alpha is TEXEL0_ALPHA *
            // SHADE_ALPHA. The framebuffer blend must not turn transparent
            // sky into a black reflection or ignore its fading opacity.
            const interop::RenderParams textureSkyParams = params[2];
            params[2].ccL = 0xFC11C223; params[2].ccH = 0xFF87FFFF;
            params[2].omL = 0x00504240; params[2].omH = 0x00882C3F;
            fill(renderParamsBuffer, params, sizeof(params));
            compareSkyReference("native-signature-opaque");
            const auto opaqueNativeBlend = render(1, 0);
            for (uint32_t v = 7; v < 12; ++v) colors[v][3] = .5f;
            fill(colorBuffer, colors, sizeof(colors));
            compareSkyReference("native-signature-half-shade");
            const auto halfShadeBlend = render(1, 0);
            setSkyTextureAlpha(128);
            compareSkyReference("native-signature-quarter-alpha");
            const auto quarterAlphaBlend = render(1, 0);
            bool alphaContribution = true;
            double opaqueDifference = 0, halfDifference = 0, quarterDifference = 0;
            for (uint32_t y = 4; y < Height - 4; ++y) for (uint32_t x = 4; x < Width - 4; ++x) {
                const uint32_t i = (y * Width + x) * 4;
                for (size_t c = 0; c < 3; ++c) {
                    const float delta = float(opaqueNativeBlend[i + c]) - float(original[i + c]);
                    alphaContribution &= std::abs(float(halfShadeBlend[i + c]) - (float(original[i + c]) + delta * .5f)) <= 2;
                    alphaContribution &= std::abs(float(quarterAlphaBlend[i + c]) - (float(original[i + c]) + delta * (128.0f / 255.0f * .5f))) <= 2;
                    opaqueDifference += std::abs(delta);
                    halfDifference += std::abs(int(halfShadeBlend[i + c]) - int(original[i + c]));
                    quarterDifference += std::abs(int(quarterAlphaBlend[i + c]) - int(original[i + c]));
                }
            }
            require(alphaContribution && opaqueDifference > 10000 &&
                halfDifference < opaqueDifference * .7 && halfDifference > opaqueDifference * .3 &&
                quarterDifference < opaqueDifference * .4 && quarterDifference > opaqueDifference * .1,
                "Native texture/shade alpha was not preserved in the water contribution");
            setSkyTextureAlpha(0);
            require(render(1, 0) == original, "Fully transparent native sky changed the original water");
            compareSkyReference("native-signature-transparent");
            setSkyTextureAlpha(255);
            for (uint32_t v = 7; v < 12; ++v) colors[v][3] = 0;
            fill(colorBuffer, colors, sizeof(colors));
            require(render(1, 0) == original, "Zero native shade alpha changed the original water");
            for (uint32_t v = 7; v < 12; ++v) colors[v][3] = 1;
            fill(colorBuffer, colors, sizeof(colors));
            params[2] = textureSkyParams;
            fill(renderParamsBuffer, params, sizeof(params));

            // Translation/recentering must leave environment lookup unchanged.
            // Shift water, opaque scene, finite sky mesh and both cameras by
            // the same large representable offset; screen/UV inputs stay fixed.
            const float shift[3] = {1024, -512, 2048};
            for (auto &vertex : world) for (size_t c = 0; c < 3; ++c) vertex[c] += shift[c];
            for (size_t c = 0; c < 3; ++c) {
                reflection.camera[c] += shift[c]; reflection.skyCamera[c] += shift[c];
            }
            rebuildPositions();
            const auto translatedSky = render(1, 4);
            bool translationStable = true;
            for (size_t p = 0; p < Width * Height; ++p) for (size_t c = 0; c < 3; ++c) {
                translationStable &= nearByte(translatedSky[p * 4 + c], noPerspectiveSky[p * 4 + c]);
            }
            require(translationStable, "Native sky changed when camera/world were recentered together");
            for (auto &vertex : world) for (size_t c = 0; c < 3; ++c) vertex[c] -= shift[c];
            for (size_t c = 0; c < 3; ++c) {
                reflection.camera[c] -= shift[c]; reflection.skyCamera[c] -= shift[c];
            }
            rebuildPositions();

            // A finite native sky fan cannot invent colors outside its angular
            // coverage. Restrict it to its first triangle and compare actual
            // triangle raster coverage rather than a copy of intersection math.
            reflection.sky[2] = 1;
            const auto partialSky = render(1, 4);
            const auto partialNative = render(0, 0, 2, 9, 3);
            size_t covered = 0, uncovered = 0;
            bool finiteCoverage = true;
            for (uint32_t y = 4; y < Height - 4; ++y) for (uint32_t x = 4; x < Width - 4; ++x) {
                // Avoid fan triangle edges, where raster MSAA coverage and a
                // single pixel-center direction intentionally differ.
                if (std::abs(int(x) - int(y)) <= 2 || std::abs(int(x + y) - 63) <= 2) continue;
                const uint32_t i = (y * Width + x) * 4;
                // RDP framebuffer alpha stores coverage, not display opacity.
                // The fixture's texture is strictly nonblack, so RGB is an
                // unambiguous independent coverage mask away from edges.
                if (partialNative[i] || partialNative[i + 1] || partialNative[i + 2]) {
                    ++covered;
                    for (size_t c = 0; c < 3; ++c) finiteCoverage &= nearByte(partialSky[i + c], partialNative[i + c]);
                }
                else {
                    ++uncovered;
                    finiteCoverage &= partialSky[i] == 0 && partialSky[i + 1] == 0 && partialSky[i + 2] == 0;
                }
            }
            std::printf("%ux MSAA finite native sky: covered%zu uncovered%zu matched%d.\n", samples, covered, uncovered, int(finiteCoverage));
            writePPM(prefix + "sky-partial-native.ppm", partialNative);
            writePPM(prefix + "sky-partial-reflected.ppm", partialSky);
            require(covered > 400 && uncovered > 1500 && finiteCoverage,
                "Native sky leaked beyond its finite triangle coverage or ignored the triangle count");
            reflection.sky[2] = 4;
            for (uint32_t v = 7; v < 12; ++v) world[v][0] += 1000;
            rebuildPositions();
            require(render(1, 0) == original, "A sky fan outside the reflected direction did not preserve native water");
            for (uint32_t v = 7; v < 12; ++v) world[v][0] -= 1000;
            for (uint32_t v = 4; v < 7; ++v) world[v][0] -= 1000;
            rebuildPositions();
            params[2] = primitiveSkyParams;
            fill(renderParamsBuffer, params, sizeof(params));
            reflection.sky[3] = 0;
            require(render(0, 0) == original, "Sky experiments failed to restore the exact disabled water output");
            require(pipelines.prepare(device.get(), layout.get(), ms, false),
                "Could not restore default stable PS after sky suite");
            require(render(1, 0) == reflected,
                "Restored stable PS did not preserve the original opaque reflection pixels");
            writePPM(prefix + "sky-blended.ppm", solidSky);
            writePPM(prefix + "sky-coverage.ppm", skyCoverage);
            std::printf("%ux MSAA: native sky fallback, foreground precedence, native raster agreement, finite coverage and recentering passed.\n", samples);

            // Unlike the planar sky fixture, this water patch has a real
            // crease. Its shared diagonal is represented by duplicate vertex
            // IDs in separate water draws, as generated native geometry can be.
            // A large opaque textured wall gives a continuous reflected color
            // gradient; seam checks therefore test actual RayQuery/material
            // output, not only a normal-debug image or copied reflection math.
            float savedWorld[16][4], savedScreen[16][4], savedUV[16][2], savedColors[16][4];
            std::memcpy(savedWorld, world, sizeof(world));
            std::memcpy(savedScreen, screen, sizeof(screen));
            std::memcpy(savedUV, uv, sizeof(uv));
            std::memcpy(savedColors, colors, sizeof(colors));
            const auto savedReflection = reflection;
            const auto savedReflectorParams = params[1];
            const auto savedReflectorIndices = renderIndices[1];
            reflection.camera[0] = 0; reflection.camera[1] = 4.5f; reflection.camera[2] = -15;
            reflection.sky[3] = 0;
            world[1][1] = world[3][1] = 1.0f;
            for (const auto pair : {std::pair<uint32_t, uint32_t>{12, 0}, {13, 2}}) {
                std::memcpy(world[pair.first], world[pair.second], sizeof(world[0]));
                std::memcpy(screen[pair.first], screen[pair.second], sizeof(screen[0]));
                std::memcpy(colors[pair.first], colors[pair.second], sizeof(colors[0]));
            }
            indices[3] = 12; indices[4] = 13;
            const float wall[3][4] = {{-100, -20, 10, 1}, {100, -20, 10, 1}, {0, 80, 10, 1}};
            for (uint32_t v = 4; v < 7; ++v) {
                std::memcpy(world[v], wall[v - 4], sizeof(world[0]));
                uv[v][0] = 32;
                uv[v][1] = (world[v][1] + 5) * 4;
            }
            params[1] = textureSkyParams;
            renderIndices[1].rdpTileCount = 1;
            fill(renderParamsBuffer, params, sizeof(params));
            fill(renderIndicesBuffer, renderIndices, sizeof(renderIndices));
            fill(screenBuffer, screen, sizeof(screen));
            fill(uvBuffer, uv, sizeof(uv));
            fill(colorBuffer, colors, sizeof(colors));
            auto refreshFixtureIndices = [&]() {
                fill(indexUpload, indices, sizeof(indices));
                worker.commandList->begin();
                worker.commandList->barriers(RenderBarrierStage::COPY, RenderBufferBarrier(faces.get(), RenderBufferAccess::WRITE));
                worker.commandList->copyBufferRegion(faces->at(0), indexUpload->at(0), sizeof(indices));
                worker.commandList->end(); worker.execute(); worker.wait();
                rebuildPositions();
            };
            refreshFixtureIndices();
            auto bindWaterAdjacency = [&](bool differentPresentation = false) {
                std::vector<float> localPositions;
                for (const auto &vertex : world) for (uint32_t c = 0; c < 3; ++c) localPositions.push_back(vertex[c]);
                std::vector<Wr64WaterAdjacency::Payload> presentation(16);
                if (differentPresentation) {
                    // Matching current endpoints are insufficient evidence
                    // that vertices share their presentation-time trajectory.
                    presentation[12][0] = presentation[13][0] = 0x3f800000u;
                }
                Wr64WaterAdjacency adjacency;
                require(adjacency.build(16, localPositions, std::vector<uint16_t>(16, 0),
                    std::vector<uint32_t>(indices, indices + 6), presentation),
                    "Production water adjacency rejected the seam fixture");
                const size_t bytes = adjacency.words.size() * sizeof(uint32_t);
                common.setBuffer(common.wr64WaterAdjacency,
                    upload(adjacency.words.data(), bytes, RenderBufferFlag::STORAGE), bytes);
                return adjacency;
            };
            const auto duplicateAdjacency = bindWaterAdjacency();
            require(duplicateAdjacency.weldDuplicates == 2 && duplicateAdjacency.triangles == 2,
                "Fixture did not exercise production welding across duplicate water vertices");
            const auto creaseOff = render(0, 0, 0, 0, 6, true);
            const auto creaseFlat = render(1, 0, 0, 0, 6, true);
            const auto creaseFlatNormals = render(1, 1, 0, 0, 6, true);
            const auto creaseFlatHits = render(1, 2, 0, 0, 6, true);
            reflection.smoothNormals = 1;
            common.setBuffer(common.wr64WaterAdjacency,
                upload(emptyAdjacency.data(), sizeof(emptyAdjacency), RenderBufferFlag::STORAGE), sizeof(emptyAdjacency));
            require(render(1, 0, 0, 0, 6, true) == creaseFlat,
                "Unavailable shared normals failed to preserve face-normal reflection fallback");
            bindWaterAdjacency();
            const auto creaseSmooth = render(1, 0, 0, 0, 6, true);
            const auto creaseSmoothNormals = render(1, 1, 0, 0, 6, true);
            const auto creaseSmoothHits = render(1, 2, 0, 0, 6, true);
            require(pipelines.prepare(device.get(), layout.get(), ms, false, true),
                "Could not select experimental PS for shared-normal foreground check");
            require(render(1, 0, 0, 0, 6, true) == creaseSmooth,
                "Stable and experimental PS disagree on opaque reflections with shared normals");
            require(pipelines.prepare(device.get(), layout.get(), ms, false),
                "Could not restore stable PS after shared-normal foreground check");
            auto diagonalJump = [&](const Pixels &pixels) {
                double total = 0;
                int maximum = 0;
                for (uint32_t k = 16; k < 48; ++k) {
                    const size_t p = (k * Width + k + 1) * 4;
                    const size_t q = ((k + 1) * Width + k) * 4;
                    int jump = 0;
                    for (size_t c = 0; c < 3; ++c)
                        jump = std::max(jump, std::abs(int(pixels[p + c]) - int(pixels[q + c])));
                    total += jump;
                    maximum = std::max(maximum, jump);
                }
                return std::pair<double, int>{total / 32, maximum};
            };
            bool seamHits = true;
            for (uint32_t k = 16; k < 48; ++k) for (const size_t p : {
                (size_t(k) * Width + k + 1) * 4, (size_t(k + 1) * Width + k) * 4}) {
                for (const auto *mask : {&creaseFlatHits, &creaseSmoothHits})
                    seamHits &= (*mask)[p] == 0 && (*mask)[p + 1] == 255 && nearByte((*mask)[p + 2], 153);
            }
            const auto flatColorJump = diagonalJump(creaseFlat), smoothColorJump = diagonalJump(creaseSmooth);
            const auto flatNormalJump = diagonalJump(creaseFlatNormals), smoothNormalJump = diagonalJump(creaseSmoothNormals);
            std::printf("%ux MSAA creased water seam: color mean/max flat %.3f/%d smooth %.3f/%d; normals %.3f/%d -> %.3f/%d; hits %d.\n",
                samples, flatColorJump.first, flatColorJump.second, smoothColorJump.first, smoothColorJump.second,
                flatNormalJump.first, flatNormalJump.second, smoothNormalJump.first, smoothNormalJump.second, int(seamHits));
            require(seamHits, "Water seam comparison crossed opaque scene coverage or miss boundaries");
            require(flatColorJump.first >= 3 && flatNormalJump.first >= 10,
                "Nonplanar fixture did not expose the existing face-normal reflection seam");
            require(smoothColorJump.first < flatColorJump.first * .5 && smoothColorJump.second <= 3 &&
                smoothNormalJump.first < flatNormalJump.first * .2 && smoothNormalJump.second <= 2,
                "Shared reflection normals did not remove the actual reflected-color seam");
            const auto separatedAdjacency = bindWaterAdjacency(true);
            require(separatedAdjacency.weldDuplicates == 0 && separatedAdjacency.triangles == 2,
                "Coincident endpoints with different presentation payloads were incorrectly welded");
            const auto separatedSmooth = render(1, 0, 0, 0, 6, true);
            const auto separatedJump = diagonalJump(separatedSmooth);
            bool separatedMatchesFlat = true;
            for (size_t p = 0; p < separatedSmooth.size(); ++p)
                separatedMatchesFlat &= nearByte(separatedSmooth[p], creaseFlat[p], 1);
            require(separatedMatchesFlat && separatedJump.first >= flatColorJump.first * .9,
                "Presentation-distinct water patches incorrectly received shared reflection normals");
            std::printf("%ux MSAA presentation guard: equal payload welded %u; distinct payload welded %u, seam %.3f/%d.\n",
                samples, duplicateAdjacency.weldDuplicates, separatedAdjacency.weldDuplicates,
                separatedJump.first, separatedJump.second);
            bindWaterAdjacency();
            require(render(1, 0, 0, 0, 6, true) == creaseSmooth,
                "Restoring equal presentation payloads did not restore welded reflection output");
            require(render(0, 0, 0, 0, 6, true) == creaseOff,
                "Smooth reflection normals changed native pixels with RT disabled");
            require(render(1, 0) == creaseSmooth,
                "Splitting the welded water patch into separate draws changed reflection pixels");
            indices[3] = 0; indices[4] = 2;
            refreshFixtureIndices();
            bindWaterAdjacency();
            require(render(1, 0, 0, 0, 6, true) == creaseSmooth,
                "Duplicate versus shared water vertex IDs changed smooth reflection pixels");

            // Keep the adjacency unchanged while presentation positions move:
            // normals must come from current GPU world positions, not a cached
            // normal calculated when the CPU topology was prepared.
            world[1][1] = world[3][1] = 1.6f;
            rebuildPositions();
            const auto movingSmooth = render(1, 0, 0, 0, 6, true);
            const auto movingNormals = render(1, 1, 0, 0, 6, true);
            require(movingSmooth != creaseSmooth && movingNormals != creaseSmoothNormals,
                "Water reflection normals did not follow current presentation geometry");
            const auto movingJump = diagonalJump(movingSmooth);
            require(movingJump.second <= 3,
                "Changing wave slopes reintroduced a shared-edge reflected-color seam");
            const float translation[3] = {1024, -512, 2048};
            for (auto &vertex : world) for (size_t c = 0; c < 3; ++c) vertex[c] += translation[c];
            for (size_t c = 0; c < 3; ++c) reflection.camera[c] += translation[c];
            rebuildPositions();
            const auto shiftedSmooth = render(1, 0, 0, 0, 6, true);
            bool shiftedStable = true;
            for (size_t p = 0; p < shiftedSmooth.size(); ++p) shiftedStable &= nearByte(shiftedSmooth[p], movingSmooth[p]);
            require(shiftedStable, "Smooth water reflections changed under a common world/camera translation");
            writePPM(prefix + "creased-flat.ppm", creaseFlat);
            writePPM(prefix + "creased-smooth.ppm", creaseSmooth);
            writePPM(prefix + "creased-flat-normals.ppm", creaseFlatNormals);
            writePPM(prefix + "creased-smooth-normals.ppm", creaseSmoothNormals);

            std::memcpy(world, savedWorld, sizeof(world));
            std::memcpy(screen, savedScreen, sizeof(screen));
            std::memcpy(uv, savedUV, sizeof(uv));
            std::memcpy(colors, savedColors, sizeof(colors));
            reflection = savedReflection;
            params[1] = savedReflectorParams;
            renderIndices[1] = savedReflectorIndices;
            fill(renderParamsBuffer, params, sizeof(params));
            fill(renderIndicesBuffer, renderIndices, sizeof(renderIndices));
            fill(screenBuffer, screen, sizeof(screen));
            fill(uvBuffer, uv, sizeof(uv));
            fill(colorBuffer, colors, sizeof(colors));
            refreshFixtureIndices();
            require(render(1, 0) == reflected,
                "Nonplanar fixture failed to restore the original planar reflection output");

            // Replay measured native cloud geometry/UVs without launching the
            // game. Material pixels below are synthetic, explicitly separate
            // from the archived frame. Native topology and radial-alpha law
            // have independent code provenance in the fixture header.
            const auto savedTile = rdpTile;
            const auto savedCloudTexture = skyTexels;
            uint32_t savedIndices[54];
            std::memcpy(savedIndices, indices, sizeof(indices));
            for (size_t c = 0; c < 3; ++c)
                reflection.camera[c] = reflection.skyCamera[c] = float(NativeSkyArchiveFixture::DerivedCamera[c]);
            const float eyeX = reflection.camera[0], eyeZ = reflection.camera[2];
            const float cloudWater[4][4] = {
                {eyeX - 900, 0, eyeZ - 230, 1}, {eyeX - 100, 0, eyeZ - 230, 1},
                {eyeX - 100, 0, eyeZ - 130, 1}, {eyeX - 900, 0, eyeZ - 130, 1}
            };
            std::memcpy(world, cloudWater, sizeof(cloudWater));
            for (uint32_t v = 0; v < 7; ++v) {
                std::memcpy(world[7 + v], NativeSkyArchiveFixture::Positions[v], 3 * sizeof(float));
                world[7 + v][3] = 1;
                std::memcpy(uv[7 + v], NativeSkyArchiveFixture::Texcoords[v], sizeof(uv[0]));
                const float dx = world[7 + v][0] - eyeX, dz = world[7 + v][2] - eyeZ;
                const float alpha = std::round(NativeSkyArchiveFixture::NativeAlphaIntercept +
                    NativeSkyArchiveFixture::NativeAlphaSlope * std::sqrt(dx * dx + dz * dz));
                colors[7 + v][0] = colors[7 + v][1] = colors[7 + v][2] = 1;
                colors[7 + v][3] = std::clamp(alpha, 0.f, 255.f) / 255.f;
            }
            for (uint32_t i = 0; i < 18; ++i) indices[9 + i] = 7 + NativeSkyArchiveFixture::NativeFanIndices[i];
            reflection.sky[2] = 6; reflection.sky[3] = 1;
            reflection.skyCloudParams[0] = NativeSkyArchiveFixture::NativeAlphaSlope;
            reflection.skyCloudParams[1] = NativeSkyArchiveFixture::NativeAlphaIntercept;
            reflection.skyCloudParams[2] = 0;
            params[2] = textureSkyParams;
            params[2].ccL = NativeSkyArchiveFixture::ColorCombiner[0];
            params[2].ccH = NativeSkyArchiveFixture::ColorCombiner[1];
            params[2].omL = NativeSkyArchiveFixture::OtherMode[0];
            params[2].omH = NativeSkyArchiveFixture::OtherMode[1];
            params[2].flags.nativeSampler0 = NATIVE_SAMPLER_WRAP_WRAP;
            params[2].flags.cms0 = params[2].flags.cmt0 = 0;
            rdpTile.cms = rdpTile.cmt = 0;
            rdpTile.fmt = NativeSkyArchiveFixture::Format;
            rdpTile.siz = NativeSkyArchiveFixture::Size;
            rdpTile.stride = 128;
            rdpTile.nativeSampler = NATIVE_SAMPLER_WRAP_WRAP;
            rdpTile.masks = 64; rdpTile.maskt = 32;
            rdpTile.lrs = 252; rdpTile.lrt = 124;
            fill(rdpTileBuffer, &rdpTile, sizeof(rdpTile));
            fill(renderParamsBuffer, params, sizeof(params));
            fill(uvBuffer, uv, sizeof(uv));
            fill(colorBuffer, colors, sizeof(colors));
            for (auto &byte : skyTexels) byte = 255;
            setSkyTextureAlpha(255);
            refreshFixtureIndices();
            bindWaterAdjacency();
            reflection.smoothNormals = 1;
            require(pipelines.prepare(device.get(), layout.get(), ms, false, true),
                "Could not prepare native cloud-plane test pipeline");
            const auto cloudOff = render(0, 0);
            const auto cloudFinite = render(1, 0);
            const auto finiteMask = render(1, 3);
            reflection.skyCloudParams[2] = 1;
            const auto cloudExtended = render(1, 0);
            const auto extendedMask = render(1, 3);
            // Exercise the exact production sparse UAV capture on a known
            // accepted native cloud chart. The existing render wait is also
            // the diagnostic readback fence; there is no extra submission.
            readSkyCapture = true;
            require(render(1, 0) == cloudExtended && capturedSkyWords[0] == 0,
                "Disabled sky capture wrote records or changed rendered pixels");
            reflection.skyCloudParams[3] = 1;
            const auto capturedCloud = render(1, 0);
            require(capturedCloud == cloudExtended,
                "Enabling sparse sky diagnostics changed rendered pixels");
            const uint32_t capturedCount = capturedSkyWords[0];
            require(noSkyObservation ? capturedCount == 0 :
                (capturedCount > 0 && capturedCount <= samples && capturedCount <= SkyCaptureCapacity),
                "Sparse sky diagnostic record count was empty or exceeded its pixel/sample bound");
            auto capturedFloat = [&](size_t word) {
                float result;
                std::memcpy(&result, &capturedSkyWords[word], sizeof(result));
                return result;
            };
            float capturedMinAlpha = 1, capturedMaxAlpha = 0;
            for (uint32_t r = 0; r < capturedCount; ++r) {
                const size_t base = 4 + size_t(r) * SkyCaptureRecordWords;
                require(capturedSkyWords[base] == (32u | (32u << 16)),
                    "Sky diagnostic sampled a pixel outside its sparse capture grid");
                require(capturedSkyWords[base + 1] == 5 && capturedSkyWords[base + 2] == 11 &&
                    (capturedSkyWords[base + 3] & 6u) == 6u,
                    "Sky diagnostic did not report the accepted cloud chart and positive reflected sky");
                const float skyAlpha = capturedFloat(base + 19);
                const float planeY = capturedFloat(base + 24);
                const float radialAlpha = capturedFloat(base + 25);
                const float rayX = capturedFloat(base + 12), rayY = capturedFloat(base + 13), rayZ = capturedFloat(base + 14);
                require(std::isfinite(skyAlpha) && skyAlpha > 0 && skyAlpha <= 1 &&
                    std::isfinite(planeY) && std::abs(planeY - NativeSkyArchiveFixture::Positions[0][1]) < .001f && rayY > 0,
                    "Sky diagnostic returned invalid opacity, plane height, or reflected direction");
                const float distance = (planeY - reflection.skyCamera[1]) / rayY;
                const float expectedAlpha = std::clamp((NativeSkyArchiveFixture::NativeAlphaIntercept +
                    NativeSkyArchiveFixture::NativeAlphaSlope * distance * std::sqrt(rayX * rayX + rayZ * rayZ)) / 255.f, 0.f, 1.f);
                require(std::abs(radialAlpha - expectedAlpha) < .0001f &&
                    std::abs(skyAlpha - expectedAlpha) < .0001f &&
                    std::abs(capturedFloat(base + 30) - expectedAlpha) < .0001f,
                    "Sky diagnostic cloud opacity disagreed with the known native radial-alpha law");
                capturedMinAlpha = std::min(capturedMinAlpha, skyAlpha);
                capturedMaxAlpha = std::max(capturedMaxAlpha, skyAlpha);
            }
            if (noSkyObservation) {
                std::printf("%ux MSAA observation-free sky: zero records with capture requested; full cloud pixels identical.\n", samples);
            }
            else {
                std::printf("%ux MSAA sparse sky capture: records%u, pixel32,32 result5 reason11, alpha%.6f..%.6f; enabled/disabled pixels identical.\n",
                    samples, capturedCount, capturedMinAlpha, capturedMaxAlpha);
            }
            {
                std::ofstream captureOutput(prefix + "-sky-capture.jsonl");
                captureOutput << "{\"schema\":1,\"fixture\":\"headless archived cloud with synthetic pixels\",\"appended\":"
                    << capturedCount << ",\"records_u32\":[";
                for (uint32_t r = 0; r < capturedCount; ++r) {
                    if (r) captureOutput << ',';
                    captureOutput << '[';
                    for (uint32_t c = 0; c < SkyCaptureRecordWords; ++c) {
                        if (c) captureOutput << ',';
                        captureOutput << capturedSkyWords[4 + size_t(r) * SkyCaptureRecordWords + c];
                    }
                    captureOutput << ']';
                }
                captureOutput << "]}\n";
                require(bool(captureOutput), "Could not save the observed GPU sky diagnostic packet");
            }
            reflection.skyCloudParams[3] = 0;
            require(render(1, 0) == cloudExtended && capturedSkyWords[0] == 0,
                "Restoring capture-disabled mode left stale records or changed cloud pixels");
            readSkyCapture = false;
            const auto isSky = [&](const Pixels &pixels, size_t p) {
                return pixels[p] == 0 && nearByte(pixels[p + 1], 166) && pixels[p + 2] == 255;
            };
            size_t extensionPixels = 0, oldBoundaryPairs = 0;
            double finiteBoundaryJump = 0, extendedBoundaryJump = 0;
            int extendedBoundaryMax = 0;
            for (uint32_t y = 4; y < Height - 4; ++y) for (uint32_t x = 4; x < Width - 5; ++x) {
                const size_t p = (y * Width + x) * 4, q = p + 4;
                if (!isSky(finiteMask, p) && isSky(extendedMask, p) &&
                    (cloudExtended[p] != cloudOff[p] || cloudExtended[p + 1] != cloudOff[p + 1] || cloudExtended[p + 2] != cloudOff[p + 2]))
                    ++extensionPixels;
                if (isSky(finiteMask, p) == isSky(finiteMask, q)) continue;
                int before = 0, after = 0;
                for (size_t c = 0; c < 3; ++c) {
                    before = std::max(before, std::abs(int(cloudFinite[p + c]) - int(cloudFinite[q + c])));
                    after = std::max(after, std::abs(int(cloudExtended[p + c]) - int(cloudExtended[q + c])));
                }
                finiteBoundaryJump += before; extendedBoundaryJump += after;
                extendedBoundaryMax = std::max(extendedBoundaryMax, after);
                ++oldBoundaryPairs;
            }
            std::printf("%ux MSAA archived cloud plane: exterior colored %zu; boundary pairs %zu, finite mean %.3f extended mean %.3f/max%d.\n",
                samples, extensionPixels, oldBoundaryPairs, finiteBoundaryJump / std::max(size_t(1), oldBoundaryPairs),
                extendedBoundaryJump / std::max(size_t(1), oldBoundaryPairs), extendedBoundaryMax);
            require(extensionPixels > 100 && oldBoundaryPairs > 20 && finiteBoundaryJump > 100,
                "Archived sky fixture did not expose the old finite-fan coverage edge");
            require(extendedBoundaryMax <= 3 && extendedBoundaryJump < finiteBoundaryJump * .2,
                "Continuous native cloud-plane lookup retained a finite-fan color discontinuity");
            require(render(0, 0) == cloudOff, "Cloud-plane extension changed native output with RT disabled");

            // A separate synthetic opaque backdrop tests the composition
            // contract. It intentionally reuses the measured finite geometry
            // with a different material; it is not a captured background cone.
            const auto savedBackdropRdp = rdp[3];
            rdp[3].primColor = hlslpp::float4(.85f, .1f, .02f, 1);
            fill(rdpParamsBuffer, rdp, sizeof(rdp));
            const auto cloudOnlyRaw = render(1, 4);
            reflection.skyBackdrop[0] = 9; reflection.skyBackdrop[1] = 3;
            reflection.skyBackdrop[2] = 6; reflection.skyBackdrop[3] = 1;
            std::memcpy(reflection.skyBackdropCamera, reflection.skyCamera, sizeof(reflection.skyCamera));
            const auto combinedSkyRaw = render(1, 4);
            reflection.sky[3] = 0;
            const auto backdropOnlyRaw = render(1, 4);
            reflection.sky[3] = 1;
            size_t backdropCompared = 0;
            bool layeredSky = true;
            for (uint32_t y = 4; y < Height - 4; ++y) for (uint32_t x = 4; x < Width - 4; ++x) {
                const size_t p = (y * Width + x) * 4;
                if (!isSky(finiteMask, p) || backdropOnlyRaw[p] < 200) continue;
                const float cloudOpacity = float(cloudOnlyRaw[p + 1]) / (255.f * .9f);
                for (size_t c = 0; c < 3; ++c) {
                    const float expected = float(cloudOnlyRaw[p + c]) + float(backdropOnlyRaw[p + c]) * (1.f - cloudOpacity);
                    layeredSky &= std::abs(float(combinedSkyRaw[p + c]) - expected) <= 2;
                }
                ++backdropCompared;
            }
            require(backdropCompared > 300 && layeredSky,
                "Native clouds were not alpha-composited over their separate backdrop");
            setSkyTextureAlpha(0);
            require(render(1, 4) == backdropOnlyRaw,
                "Transparent clouds obscured or darkened their opaque backdrop");
            setSkyTextureAlpha(255);
            reflection.skyBackdrop[3] = 0;
            rdp[3] = savedBackdropRdp;
            fill(rdpParamsBuffer, rdp, sizeof(rdp));

            #include "sky_transition_gpu.inc"

            // Planar geometry and valid topology are hard prerequisites. A
            // malformed candidate must use the previous finite lookup exactly.
            for (uint32_t invalidCase = 0; invalidCase < 3; ++invalidCase) {
                if (invalidCase == 0) world[7][1] += 20;
                else if (invalidCase == 1) { uv[7][0] += 10; indices[12] = indices[9]; indices[13] = indices[10]; indices[14] = indices[11]; }
                else reflection.skyCloudParams[0] = 0.055f;
                refreshFixtureIndices(); fill(uvBuffer, uv, sizeof(uv));
                reflection.skyCloudParams[2] = 0;
                const auto finiteInvalid = render(1, 0);
                reflection.skyCloudParams[2] = 1;
                require(render(1, 0) == finiteInvalid,
                    "Invalid plane, duplicated fan sector or radial-alpha law did not retain finite fallback");
                if (invalidCase == 0) world[7][1] -= 20;
                else if (invalidCase == 1) { uv[7][0] -= 10; for (uint32_t i = 0; i < 18; ++i) indices[9+i] = 7 + NativeSkyArchiveFixture::NativeFanIndices[i]; }
                else reflection.skyCloudParams[0] = NativeSkyArchiveFixture::NativeAlphaSlope;
            }
            rebuildPositions(); fill(uvBuffer, uv, sizeof(uv));

            // Exercise wrapped texture and its own alpha on the smoothly
            // deformed water, using a periodic field so texture-border seams
            // cannot masquerade as chart discontinuities.
            for (uint32_t y = 0; y < Height; ++y) for (uint32_t x = 0; x < Width; ++x) {
                const size_t p = (y * Width + x) * 4;
                const float wave = .5f + .25f * std::cos(x * 6.283185307f / 64) + .25f * std::sin(y * 6.283185307f / 32);
                skyTexels[p] = skyTexels[p + 1] = skyTexels[p + 2] = uint8_t(std::round(96 + 159 * wave));
            }
            setSkyTextureAlpha(255);
            world[1][1] = world[3][1] = 1.5f;
            rebuildPositions();
            const auto texturedCloud = render(1, 0);
            setSkyTextureAlpha(128);
            const auto halfCloud = render(1, 0);
            bool nativeCloudAlpha = true;
            size_t texturedChanges = 0;
            for (size_t p = 0; p < Width * Height; ++p) for (size_t c = 0; c < 3; ++c) {
                const size_t i = p * 4 + c;
                const float delta = float(texturedCloud[i]) - float(cloudOff[i]);
                nativeCloudAlpha &= std::abs(float(halfCloud[i]) - (float(cloudOff[i]) + delta * (128.f / 255.f))) <= 2;
                texturedChanges += std::abs(delta) > 2;
            }
            require(nativeCloudAlpha && texturedChanges > 500,
                "Extended native clouds lost their texture opacity or became an inactive test");
            setSkyTextureAlpha(0);
            require(render(1, 0) == cloudOff, "Zero cloud texture alpha changed water on the extended plane");
            setSkyTextureAlpha(128);
            world[1][1] += .0001f; world[3][1] += .0001f;
            rebuildPositions();
            const auto smallWaveStep = render(1, 0);
            int smallStepMaximum = 0;
            for (size_t p = 0; p < smallWaveStep.size(); ++p)
                smallStepMaximum = std::max(smallStepMaximum, std::abs(int(smallWaveStep[p]) - int(halfCloud[p])));
            require(smallStepMaximum <= 1,
                "A tiny smooth-wave change caused a cloud-map color discontinuity");
            world[1][1] -= .0001f; world[3][1] -= .0001f;
            for (uint32_t v = 0; v < 4; ++v) world[v][0] -= 10000;
            rebuildPositions();
            require(render(1, 0) == cloudOff,
                "Cloud extension did not fade to native water beyond the native radial-alpha range");
            for (uint32_t v = 0; v < 4; ++v) world[v][0] += 10000;
            const float cloudTranslation[3] = {1024, -512, 2048};
            for (auto &vertex : world) for (size_t c = 0; c < 3; ++c) vertex[c] += cloudTranslation[c];
            for (size_t c = 0; c < 3; ++c) {
                reflection.camera[c] += cloudTranslation[c]; reflection.skyCamera[c] += cloudTranslation[c];
            }
            rebuildPositions();
            const auto shiftedCloud = render(1, 0);
            bool cloudTranslationStable = true;
            for (size_t p = 0; p < shiftedCloud.size(); ++p) cloudTranslationStable &= nearByte(shiftedCloud[p], halfCloud[p]);
            require(cloudTranslationStable, "Extended cloud map changed under common camera/mesh translation");
            for (auto &vertex : world) for (size_t c = 0; c < 3; ++c) vertex[c] -= cloudTranslation[c];
            for (size_t c = 0; c < 3; ++c) {
                reflection.camera[c] -= cloudTranslation[c]; reflection.skyCamera[c] -= cloudTranslation[c];
            }

            // An opaque wall now intercepts these rays before any sky lookup.
            // It must remain exactly identical between stable and sky PSOs.
            const float blockingWall[3][4] = {{eyeX - 20000, -10000, eyeZ - 500, 1},
                {eyeX + 20000, -10000, eyeZ - 500, 1}, {eyeX, 20000, eyeZ - 500, 1}};
            std::memcpy(world[4], blockingWall, sizeof(blockingWall));
            rebuildPositions();
            const auto opaqueCloud = render(1, 0);
            const auto opaqueCloudMask = render(1, 2);
            require(pipelines.prepare(device.get(), layout.get(), ms, false), "Could not select stable cloud-occlusion reference");
            const auto opaqueStable = render(1, 0);
            size_t opaqueChecks = 0;
            bool opaqueUnchanged = true;
            for (size_t p = 0; p < Width * Height; ++p) {
                if (opaqueCloudMask[p * 4 + 1] != 255) continue;
                ++opaqueChecks;
                for (size_t c = 0; c < 4; ++c) opaqueUnchanged &= opaqueCloud[p * 4 + c] == opaqueStable[p * 4 + c];
            }
            require(opaqueChecks > 3000 && opaqueUnchanged,
                "Cloud-plane extension contaminated stable opaque scene reflections");
            writePPM(prefix + "archive-cloud-finite.ppm", cloudFinite);
            writePPM(prefix + "archive-cloud-extended.ppm", cloudExtended);
            writePPM(prefix + "archive-cloud-textured.ppm", texturedCloud);

            std::memcpy(world, savedWorld, sizeof(world));
            std::memcpy(uv, savedUV, sizeof(uv));
            std::memcpy(colors, savedColors, sizeof(colors));
            std::memcpy(indices, savedIndices, sizeof(indices));
            reflection = savedReflection;
            params[2] = primitiveSkyParams;
            rdpTile = savedTile; skyTexels = savedCloudTexture;
            fill(rdpTileBuffer, &rdpTile, sizeof(rdpTile));
            fill(renderParamsBuffer, params, sizeof(params));
            fill(uvBuffer, uv, sizeof(uv)); fill(colorBuffer, colors, sizeof(colors));
            setSkyTextureAlpha(255);
            refreshFixtureIndices();
            require(render(1, 0) == reflected, "Archived cloud fixture failed to restore original reflection state");

            // Native background material uses two independent 4x64 RGBA16
            // gradients blended by ENV color. Compare its real raster path
            // with the reflected sampler, retaining perspective-varying W.
            // Synthetic decoded colors differ deliberately between tiles, so
            // binding TEXEL1 to TEXEL0 cannot accidentally pass the test.
            std::unique_ptr<RenderTexture> gradientTextures[2];
            std::unique_ptr<RenderTextureView> gradientViews[2];
            for (uint32_t t = 0; t < 2; ++t) {
                Pixels textureUpload(Height * 256, 0);
                for (uint32_t y = 0; y < 64; ++y) for (uint32_t x = 0; x < 4; ++x) {
                    const size_t p = y * 256 + x * 4;
                    textureUpload[p] = uint8_t(t ? 220 - y * 2 : 20 + y * 3);
                    textureUpload[p + 1] = uint8_t(t ? 40 + y * 3 : 60);
                    textureUpload[p + 2] = uint8_t(t ? 30 : 200 - y * 2);
                    textureUpload[p + 3] = 255;
                }
                gradientTextures[t] = device->createTexture(RenderTextureDesc::Texture2D(4, 64, 1, RenderFormat::R8G8B8A8_UNORM));
                gradientViews[t] = gradientTextures[t]->createTextureView(RenderTextureViewDesc::Texture2D(RenderFormat::R8G8B8A8_UNORM));
                RenderBuffer *source = upload(textureUpload.data(), textureUpload.size(), 0);
                worker.commandList->begin();
                worker.commandList->barriers(RenderBarrierStage::COPY,
                    RenderTextureBarrier(gradientTextures[t].get(), RenderTextureLayout::COPY_DEST));
                worker.commandList->copyTextureRegion(RenderTextureCopyLocation::Subresource(gradientTextures[t].get()),
                    RenderTextureCopyLocation::PlacedFootprint(source, RenderFormat::R8G8B8A8_UNORM, 4, 64, 1, 64));
                worker.commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE,
                    RenderTextureBarrier(gradientTextures[t].get(), RenderTextureLayout::SHADER_READ));
                worker.commandList->end(); worker.execute(); worker.wait();
                textures.setTexture(t, gradientTextures[t].get(), RenderTextureLayout::SHADER_READ, gradientViews[t].get());
            }
            interop::RDPTile gradientTiles[2]{};
            interop::GPUTile gradientGpuTiles[2]{};
            for (uint32_t t = 0; t < 2; ++t) {
                gradientTiles[t].fmt = 0; gradientTiles[t].siz = 2; gradientTiles[t].stride = 8;
                gradientTiles[t].shifts = gradientTiles[t].shiftt = 1;
                gradientTiles[t].masks = 4; gradientTiles[t].maskt = 64;
                gradientTiles[t].lrs = 12; gradientTiles[t].lrt = 252;
                gradientTiles[t].cms = gradientTiles[t].cmt = 2;
                gradientTiles[t].nativeSampler = NATIVE_SAMPLER_CLAMP_CLAMP;
                gradientGpuTiles[t].ulScale = gradientGpuTiles[t].tcScale = hlslpp::float2(1, 1);
                gradientGpuTiles[t].textureIndex = t;
                gradientGpuTiles[t].textureDimensions = hlslpp::float3(4, 64, 1);
            }
            common.setBuffer(common.RDPTiles, upload(gradientTiles, sizeof(gradientTiles), RenderBufferFlag::STORAGE),
                sizeof(gradientTiles), RenderBufferStructuredView(sizeof(interop::RDPTile)));
            common.setBuffer(common.GPUTiles, upload(gradientGpuTiles, sizeof(gradientGpuTiles), RenderBufferFlag::STORAGE),
                sizeof(gradientGpuTiles), RenderBufferStructuredView(sizeof(interop::GPUTile)));
            const auto savedGradientRdp = rdp[2];
            params[2] = textureSkyParams;
            params[2].ccL = 0xFC22FFFF; params[2].ccH = 0x1FFCFA38;
            params[2].omL = 0x0F0A4000; params[2].omH = 0x00982C3F;
            params[2].flags.usesTexture0 = params[2].flags.usesTexture1 = 1;
            params[2].flags.cms0 = params[2].flags.cmt0 = params[2].flags.cms1 = params[2].flags.cmt1 = 2;
            params[2].flags.nativeSampler0 = params[2].flags.nativeSampler1 = NATIVE_SAMPLER_CLAMP_CLAMP;
            renderIndices[2].rdpTileCount = 2;
            fill(renderParamsBuffer, params, sizeof(params));
            fill(renderIndicesBuffer, renderIndices, sizeof(renderIndices));
            for (uint32_t v = 4; v < 7; ++v) world[v][0] += 1000;
            rebuildPositions();
            reflection.sky[3] = 0;
            reflection.skyBackdrop[0] = 9; reflection.skyBackdrop[1] = 2;
            reflection.skyBackdrop[2] = 4; reflection.skyBackdrop[3] = 1;
            std::memcpy(reflection.skyBackdropCamera, reflection.skyCamera, sizeof(reflection.skyCamera));
            require(pipelines.prepare(device.get(), layout.get(), ms, false, true), "Could not prepare native backdrop raster-reference check");
            Pixels gradientSamples[3];
            uint32_t gradientSample = 0;
            for (float blend : {0.f, .5f, 1.f}) {
                rdp[2].envColor = hlslpp::float4(blend, blend, blend, blend);
                fill(rdpParamsBuffer, rdp, sizeof(rdp));
                if (vulkan) std::printf("%ux backdrop ENV%.1f: begin native raster, next fence%zu\n", samples, blend, worker.waitCount + 1);
                const auto nativeGradient = render(0, 0, 2, 9, 12);
                if (vulkan) std::printf("%ux backdrop ENV%.1f: native complete; begin reflected sample, next fence%zu\n", samples, blend, worker.waitCount + 1);
                const auto reflectedGradient = render(1, 4);
                if (vulkan) std::printf("%ux backdrop ENV%.1f: reflected sample complete\n", samples, blend);
                size_t compared = 0, disagree = 0;
                int maxError = 0;
                for (uint32_t y = 4; y < Height - 4; ++y) for (uint32_t x = 4; x < Width - 4; ++x) {
                    const size_t p = (y * Width + x) * 4;
                    int error = 0;
                    for (size_t c = 0; c < 3; ++c) error = std::max(error,
                        std::abs(int(nativeGradient[p + c]) - int(reflectedGradient[p + c])));
                    maxError = std::max(maxError, error);
                    disagree += error > 2; ++compared;
                }
                std::printf("%ux MSAA native two-tile backdrop ENV %.1f: %zu/%zu within2, max error%d.\n",
                    samples, blend, compared - disagree, compared, maxError);
                require(disagree == 0 && maxError <= 2,
                    "Native two-cycle backdrop reflection disagrees with production raster material/tiles");
                gradientSamples[gradientSample++] = reflectedGradient;
            }
            size_t endpointDifferences = 0;
            bool halfGradient = true;
            for (uint32_t y = 4; y < Height - 4; ++y) for (uint32_t x = 4; x < Width - 4; ++x) {
                const size_t p = (y * Width + x) * 4;
                for (size_t c = 0; c < 3; ++c) {
                    endpointDifferences += std::abs(int(gradientSamples[0][p + c]) - int(gradientSamples[2][p + c])) > 10;
                    halfGradient &= std::abs(float(gradientSamples[1][p + c]) -
                        (float(gradientSamples[0][p + c]) + float(gradientSamples[2][p + c])) * .5f) <= 2;
                }
            }
            require(endpointDifferences > 3000 && halfGradient,
                "Native backdrop fixture failed to distinguish its two source textures and ENV blend");
            if (selected("--backdrop-probe-only")) {
                std::printf("PASS: targeted %ux native two-tile reflected backdrop and all preceding fixtures; %zu checks.\n", samples, checks);
                return 0;
            }
            // Actual generated sky inputs straddle the user's opening dropout.
            // Replay its recorded ray with flat synthetic water and compare
            // against the production native raster path with backface culling.
            // Both use the native material above and explicitly synthetic pixels.
            {
                float crossingWorld[16][4], crossingScreen[16][4], crossingUV[16][2], crossingColors[16][4];
                uint32_t crossingIndices[54];
                std::memcpy(crossingWorld, world, sizeof(world)); std::memcpy(crossingScreen, screen, sizeof(screen));
                std::memcpy(crossingUV, uv, sizeof(uv)); std::memcpy(crossingColors, colors, sizeof(colors));
                std::memcpy(crossingIndices, indices, sizeof(indices));
                const auto crossingParams = params[2]; const auto crossingReflection = reflection;
                const auto crossingRdp = rdp[2];
                FixtureWorldPipelines crossingNative(shaderFormat);
                require(crossingNative.prepare(device.get(), layout.get(), ms, false),
                    "Could not prepare culled native backdrop raster reference");
                reflection = Params{}; reflection.sky[3] = 0;
                reflection.skyBackdrop[0] = 9; reflection.skyBackdrop[1] = 2;
                reflection.skyBackdrop[2] = 6; reflection.skyBackdrop[3] = 1;
                params[2].flags.culling = 1;
                rdp[2].envColor = hlslpp::float4(0, 0, 0, 0);
                fill(rdpParamsBuffer, rdp, sizeof(rdp));
                Pixels capturedCulled[2], capturedDouble[2], capturedNative[2];
                for (uint32_t endpoint = 0; endpoint < 2; ++endpoint) {
                    const auto &capture = NativeBackdropCrossingFixture::Frames[endpoint];
                    const hlslpp::float3 forward(capture.ray[0], capture.ray[1], capture.ray[2]);
                    const hlslpp::float3 right = hlslpp::normalize(hlslpp::cross(forward, hlslpp::float3(0, 1, 0)));
                    const hlslpp::float3 up = hlslpp::cross(right, forward);
                    constexpr float receiverDistance = 100.f;
                    reflection.camera[0] = -capture.ray[0] * receiverDistance;
                    reflection.camera[1] = capture.ray[1] * receiverDistance;
                    reflection.camera[2] = -capture.ray[2] * receiverDistance;
                    std::memcpy(reflection.skyBackdropCamera, capture.camera, sizeof(capture.camera));
                    reflection.skyBackdropCamera[3] = 1;
                    // Pixel(32,32) corresponds exactly to the captured direction;
                    // the small surrounding field stays within the same far face.
                    for (uint32_t v = 0; v < 4; ++v) {
                        world[v][0] = (screen[v][0] - 32.5f) / 32.f;
                        world[v][1] = 0;
                        world[v][2] = (32.5f - screen[v][1]) / 32.f;
                    }
                    for (uint32_t v = 0; v < 7; ++v) {
                        const uint32_t dst = 7 + v;
                        std::memcpy(world[dst], capture.vertices[v], 4 * sizeof(float));
                        std::memcpy(uv[dst], capture.vertices[v] + 4, 2 * sizeof(float));
                        std::memcpy(colors[dst], capture.vertices[v] + 6, 4 * sizeof(float));
                        const hlslpp::float3 relative(world[dst][0] - capture.camera[0],
                            world[dst][1] - capture.camera[1], world[dst][2] - capture.camera[2]);
                        const float w = hlslpp::dot(relative, forward);
                        screen[dst][0] = 32.5f + float(hlslpp::dot(relative, right)) * 3200.f / w;
                        screen[dst][1] = 32.5f - float(hlslpp::dot(relative, up)) * 3200.f / w;
                        screen[dst][2] = .5f; screen[dst][3] = w;
                    }
                    for (uint32_t i = 0; i < 18; ++i) indices[9 + i] = 7 + NativeBackdropCrossingFixture::Indices[i];
                    fill(screenBuffer, screen, sizeof(screen)); fill(uvBuffer, uv, sizeof(uv));
                    fill(colorBuffer, colors, sizeof(colors)); refreshFixtureIndices();
                    params[2].flags.culling = 1; fill(renderParamsBuffer, params, sizeof(params));
                    capturedCulled[endpoint] = render(1, 4);
                    params[2].flags.culling = 0; fill(renderParamsBuffer, params, sizeof(params));
                    capturedDouble[endpoint] = render(1, 4);
                    params[2].flags.culling = 1; fill(renderParamsBuffer, params, sizeof(params));
                    pipelineOverride = crossingNative.get(false, false, false, true, true, true);
                    require(pipelineOverride != nullptr, "Native culled backdrop reference pipeline is unavailable");
                    capturedNative[endpoint] = render(0, 0, 2, 9, 18);
                    pipelineOverride = nullptr;
                    size_t compared = 0, disagree = 0; int maximum = 0;
                    for (uint32_t y = 16; y < 48; ++y) for (uint32_t x = 16; x < 48; ++x) {
                        const size_t p = (y * Width + x) * 4;
                        require(capturedNative[endpoint][p + 3] > 0,
                            "Captured backdrop native-reference pixel was uncovered");
                        for (uint32_t c = 0; c < 3; ++c) {
                            const int error = std::abs(int(capturedCulled[endpoint][p + c]) - int(capturedNative[endpoint][p + c]));
                            ++compared; disagree += error > 2; maximum = std::max(maximum, error);
                        }
                    }
                    std::printf("%ux MSAA captured backdrop %ums: native comparisons%zu mismatch%zu max%d; culled(%u,%u,%u) double(%u,%u,%u) native(%u,%u,%u).\n",
                        samples, capture.elapsedMs, compared, disagree, maximum,
                        center(capturedCulled[endpoint])[0], center(capturedCulled[endpoint])[1], center(capturedCulled[endpoint])[2],
                        center(capturedDouble[endpoint])[0], center(capturedDouble[endpoint])[1], center(capturedDouble[endpoint])[2],
                        center(capturedNative[endpoint])[0], center(capturedNative[endpoint])[1], center(capturedNative[endpoint])[2]);
                    if (backdropCullBaseline && endpoint == 1)
                        require(disagree > 1500 && maximum > 100,
                            "Old library did not reproduce the captured near-backface color regression");
                    else require(disagree == 0 && maximum <= 2,
                        "Reflected captured backdrop disagrees with native one-sided rasterization");
                }
                size_t doubleJump = 0, culledJump = 0;
                for (uint32_t y = 16; y < 48; ++y) for (uint32_t x = 16; x < 48; ++x) for (uint32_t c = 0; c < 3; ++c) {
                    const size_t p = (y * Width + x) * 4 + c;
                    doubleJump += std::abs(int(capturedDouble[0][p]) - int(capturedDouble[1][p])) > 100;
                    culledJump += std::abs(int(capturedCulled[0][p]) - int(capturedCulled[1][p])) > 2;
                }
                require(doubleJump > 1500, "Capture replay did not retain the explicitly double-sided discontinuity control");
                require(backdropCullBaseline ? culledJump > 1500 : culledJump == 0,
                    "Captured native culling did not preserve the correct continuous backdrop color");
                if (backdropCullBaseline) {
                    std::printf("PASS: captured old-library failure reproduced; %zu double-sided color jumps.\n", doubleJump);
                    return 0;
                }
                std::memcpy(world, crossingWorld, sizeof(world)); std::memcpy(screen, crossingScreen, sizeof(screen));
                std::memcpy(uv, crossingUV, sizeof(uv)); std::memcpy(colors, crossingColors, sizeof(colors));
                std::memcpy(indices, crossingIndices, sizeof(indices));
                reflection = crossingReflection; params[2] = crossingParams; rdp[2] = crossingRdp;
                fill(renderParamsBuffer, params, sizeof(params)); fill(rdpParamsBuffer, rdp, sizeof(rdp));
                fill(screenBuffer, screen, sizeof(screen)); fill(uvBuffer, uv, sizeof(uv)); fill(colorBuffer, colors, sizeof(colors));
                refreshFixtureIndices();
            }
            for (uint32_t v = 4; v < 7; ++v) world[v][0] -= 1000;
            rebuildPositions();
            reflection = savedReflection;
            params[2] = primitiveSkyParams; rdp[2] = savedGradientRdp;
            renderIndices[2].rdpTileCount = 1;
            fill(renderParamsBuffer, params, sizeof(params));
            fill(renderIndicesBuffer, renderIndices, sizeof(renderIndices));
            fill(rdpParamsBuffer, rdp, sizeof(rdp));
            common.setBuffer(common.RDPTiles, rdpTileBuffer, sizeof(rdpTile), RenderBufferStructuredView(sizeof(rdpTile)));
            common.setBuffer(common.GPUTiles, gpuTileBuffer, sizeof(gpuTile), RenderBufferStructuredView(sizeof(gpuTile)));
            textures.setTexture(0, skyTexture.get(), RenderTextureLayout::SHADER_READ, skyTextureView.get());
            textures.setTexture(1, skyTexture.get(), RenderTextureLayout::SHADER_READ, skyTextureView.get());
            require(pipelines.prepare(device.get(), layout.get(), ms, false), "Could not restore stable PS after native backdrop suite");
            require(render(1, 0) == reflected, "Native backdrop fixture failed to restore stable reflection output");

            // Final-target regression for the native Sunset water material.
            // Its one-cycle combiner emits TEXEL0 RGBA and its blender uses
            // texture alpha as SRC1_ALPHA. Opaque-water/debug-only references
            // cannot detect accidentally multiplying reflected sky by that
            // native alpha again at the final hardware blend.
            const auto alphaWaterParams = params[0];
            const auto alphaSkyParams = params[2];
            const auto alphaSkyRdp = rdp[2];
            const auto alphaWaterIndices = renderIndices[0];
            auto waterTexture = device->createTexture(RenderTextureDesc::Texture2D(32, 32, 1,
                RenderFormat::R8G8B8A8_UNORM));
            auto waterTextureView = waterTexture->createTextureView(
                RenderTextureViewDesc::Texture2D(RenderFormat::R8G8B8A8_UNORM));
            Pixels waterBytes(32 * 256, 0);
            auto waterTextureUpload = upload(waterBytes.data(), waterBytes.size(), 0);
            auto setNativeWaterAlpha = [&](uint8_t alpha) {
                for (uint32_t y = 0; y < 32; ++y) for (uint32_t x = 0; x < 32; ++x) {
                    const size_t p = y * 256 + x * 4;
                    waterBytes[p] = 26; waterBytes[p + 1] = 51;
                    waterBytes[p + 2] = 179; waterBytes[p + 3] = alpha;
                }
                fill(waterTextureUpload, waterBytes.data(), waterBytes.size());
                worker.commandList->begin();
                worker.commandList->barriers(RenderBarrierStage::COPY,
                    RenderTextureBarrier(waterTexture.get(), RenderTextureLayout::COPY_DEST));
                worker.commandList->copyTextureRegion(RenderTextureCopyLocation::Subresource(waterTexture.get()),
                    RenderTextureCopyLocation::PlacedFootprint(waterTextureUpload,
                        RenderFormat::R8G8B8A8_UNORM, 32, 32, 1, 64));
                worker.commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE,
                    RenderTextureBarrier(waterTexture.get(), RenderTextureLayout::SHADER_READ));
                worker.commandList->end(); worker.execute(); worker.wait();
            };
            interop::RDPTile alphaTiles[2] = {rdpTile, rdpTile};
            alphaTiles[1].fmt = 0; alphaTiles[1].siz = 3;
            alphaTiles[1].lrs = alphaTiles[1].lrt = 31 * 4;
            alphaTiles[1].stride = 32 * 4;
            interop::GPUTile alphaGpuTiles[2] = {gpuTile, gpuTile};
            alphaGpuTiles[1].textureIndex = 1;
            alphaGpuTiles[1].textureDimensions = hlslpp::float3(32, 32, 1);
            common.setBuffer(common.RDPTiles, upload(alphaTiles, sizeof(alphaTiles), RenderBufferFlag::STORAGE),
                sizeof(alphaTiles), RenderBufferStructuredView(sizeof(interop::RDPTile)));
            common.setBuffer(common.GPUTiles, upload(alphaGpuTiles, sizeof(alphaGpuTiles), RenderBufferFlag::STORAGE),
                sizeof(alphaGpuTiles), RenderBufferStructuredView(sizeof(interop::GPUTile)));
            textures.setTexture(1, waterTexture.get(), RenderTextureLayout::SHADER_READ, waterTextureView.get());
            params[0] = textureSkyParams;
            params[0].ccL = 0xFCFFFFFF; params[0].ccH = 0xFFFCF279;
            params[0].omL = 0x005049D8; params[0].omH = 0x00082CFF;
            renderIndices[0].rdpTileIndex = 1; renderIndices[0].rdpTileCount = 1;
            params[2] = primitiveSkyParams;
            // Standard alpha-over native blender; test sky color stays a
            // constant, independent of the sampled native water texture.
            params[2].omL = 0x00504240; params[2].omH = 0x00882C3F;
            fill(renderParamsBuffer, params, sizeof(params));
            fill(renderIndicesBuffer, renderIndices, sizeof(renderIndices));
            clearDestination = RenderColor(.8f, .4f, .2f, 1);
            const float destinationRGB[3] = {204, 102, 51};
            const float textureRGB[3] = {26, 51, 179};
            const float environmentRGB[3] = {.05f, .9f, .1f};
            for (uint32_t v = 4; v < 7; ++v) world[v][0] += 1000;
            reflection.sky[3] = 1;
            require(pipelines.prepare(device.get(), layout.get(), ms, false, true),
                "Could not select sky PS for native-water alpha regression");
            bool waterBaselineCorrect = true, physicalCompositionCorrect = true;
            bool debugIndependentOfWater = true, coverageDebugIndependentOfWater = true, coverageUnchanged = true;
            size_t totalCompositionPixels = 0, compositionDisagreements = 0;
            int maximumCompositionError = 0, maximumOldModelError = 0;
            for (float eyeHeight : {.05f, 1.0f, 10.0f, 100.0f}) {
                reflection.camera[1] = reflection.skyCamera[1] = eyeHeight;
                for (uint32_t v = 7; v < 12; ++v)
                    world[v][1] = eyeHeight * (1.0f + screen[v][3]);
                rebuildPositions();
                for (uint8_t waterAlpha : {uint8_t(0), uint8_t(64), uint8_t(128), uint8_t(179), uint8_t(255)}) {
                    setNativeWaterAlpha(waterAlpha);
                    const auto nativeWater = render(0, 0);
                    const float nativeA = waterAlpha / 255.0f;
                    for (float skyOpacity : {0.0f, .5f, 1.0f}) {
                        rdp[2].primColor = hlslpp::float4(environmentRGB[0], environmentRGB[1],
                            environmentRGB[2], skyOpacity);
                        fill(rdpParamsBuffer, rdp, sizeof(rdp));
                        const auto finalWater = render(1, 0);
                        const auto directSky = render(1, 4);
                        const auto directCoverage = render(1, 3);
                        int casePhysicalError = 0, caseOldError = 0;
                        for (uint32_t y = 4; y < Height - 4; ++y) for (uint32_t x = 4; x < Width - 4; ++x) {
                            const size_t p = (y * Width + x) * 4;
                            const double wx = (x + .5) / 6.4 - 5;
                            const double wz = 5 - (y + .5) / 6.4;
                            const double ndv = eyeHeight / std::sqrt(wx * wx + eyeHeight * eyeHeight + (10 + wz) * (10 + wz));
                            const double edge = std::pow(1 - ndv, 5);
                            const double f0 = std::pow((1.333 - 1) / (1.333 + 1), 2);
                            const double skyWeight = (f0 + (1 - f0) * edge) * skyOpacity;
                            const double oldWeight = (.08 + .35 * edge) * skyOpacity;
                            int error = 0;
                            for (size_t c = 0; c < 3; ++c) {
                                const double nativeExpected = textureRGB[c] * nativeA + destinationRGB[c] * (1 - nativeA);
                                waterBaselineCorrect &= std::abs(nativeWater[p + c] - nativeExpected) <= 1.1;
                                const double expected = nativeWater[p + c] * (1 - skyWeight) + environmentRGB[c] * 255 * skyWeight;
                                const double oldExpected = nativeExpected + nativeA * oldWeight * (environmentRGB[c] * 255 - textureRGB[c]);
                                const int channelError = int(std::ceil(std::abs(finalWater[p + c] - expected)));
                                error = std::max(error, channelError);
                                caseOldError = std::max(caseOldError, int(std::ceil(std::abs(finalWater[p + c] - oldExpected))));
                                debugIndependentOfWater &= std::abs(directSky[p + c] - environmentRGB[c] * 255 * skyOpacity) <= 1.1;
                                // This finite fan geometrically covers the
                                // lookup even when its material is transparent.
                                const float marker[3] = {0.0f, .65f, 1.0f};
                                coverageDebugIndependentOfWater &= std::abs(directCoverage[p + c] - marker[c] * 255) <= 1.1;
                            }
                            coverageUnchanged &= finalWater[p + 3] == nativeWater[p + 3];
                            compositionDisagreements += error > 2;
                            ++totalCompositionPixels;
                            casePhysicalError = std::max(casePhysicalError, error);
                        }
                        maximumCompositionError = std::max(maximumCompositionError, casePhysicalError);
                        maximumOldModelError = std::max(maximumOldModelError, caseOldError);
                        physicalCompositionCorrect &= casePhysicalError <= 2;
                        if (skyOpacity == 1 && (waterAlpha == 0 || waterAlpha == 179 || waterAlpha == 255)) {
                            const auto n = center(nativeWater), f = center(finalWater);
                            std::printf("%ux MSAA native water alpha %u eyeY %.2f: offRGB %u,%u,%u onRGB %u,%u,%u; physical error%d old A*F error%d.\n",
                                samples, unsigned(waterAlpha), eyeHeight, n[0], n[1], n[2], f[0], f[1], f[2], casePhysicalError, caseOldError);
                        }
                        require(render(0, 0) == nativeWater,
                            "Disabled native water changed after sky material/opacity updates");
                    }
                }
            }
            std::printf("%ux MSAA native-water composition: %zu/%zu pixels within2; max physical error%d, old-model error%d, baseline%d directSky%d coverage%d.\n",
                samples, totalCompositionPixels - compositionDisagreements, totalCompositionPixels,
                maximumCompositionError, maximumOldModelError, int(waterBaselineCorrect),
                int(debugIndependentOfWater), int(coverageUnchanged));
            require(waterBaselineCorrect, "Native water fixture did not reproduce texture-alpha framebuffer blending");
            require(physicalCompositionCorrect, "Final sky contribution was attenuated by native water alpha or used the wrong angular response");
            require(debugIndependentOfWater, "Direct sky diagnostics were attenuated by native water alpha");
            require(coverageDebugIndependentOfWater, "Sky coverage diagnostics were attenuated by native water alpha");
            require(coverageUnchanged, "Sky compositing changed native water coverage values");
            std::memcpy(world, savedWorld, sizeof(world));
            rebuildPositions();
            reflection = savedReflection;
            reflection.sky[3] = 1;
            setNativeWaterAlpha(179);
            require(pipelines.prepare(device.get(), layout.get(), ms, false),
                "Could not select stable PS for native-alpha foreground reference");
            const auto nativeAlphaForeground = render(1, 0);
            require(pipelines.prepare(device.get(), layout.get(), ms, false, true),
                "Could not select sky PS for native-alpha foreground reference");
            const auto nativeAlphaWithSky = render(1, 0);
            bool nativeAlphaHitsUnchanged = true;
            size_t nativeAlphaHitCount = 0;
            for (size_t p = 0; p < Width * Height; ++p) {
                const size_t i = p * 4;
                if (hits[i + 1] != 255) continue;
                ++nativeAlphaHitCount;
                for (size_t c = 0; c < 4; ++c)
                    nativeAlphaHitsUnchanged &= nativeAlphaForeground[i + c] == nativeAlphaWithSky[i + c];
            }
            require(nativeAlphaHitCount > 3000 && nativeAlphaHitsUnchanged,
                "Sky composition changed existing opaque-hit reflections through native translucent water");
            reflection = savedReflection;
            clearDestination = RenderColor(0, 0, 0, 0);
            params[0] = alphaWaterParams; params[2] = alphaSkyParams;
            rdp[2] = alphaSkyRdp; renderIndices[0] = alphaWaterIndices;
            fill(renderParamsBuffer, params, sizeof(params));
            fill(rdpParamsBuffer, rdp, sizeof(rdp));
            fill(renderIndicesBuffer, renderIndices, sizeof(renderIndices));
            common.setBuffer(common.RDPTiles, rdpTileBuffer, sizeof(rdpTile), RenderBufferStructuredView(sizeof(rdpTile)));
            common.setBuffer(common.GPUTiles, gpuTileBuffer, sizeof(gpuTile), RenderBufferStructuredView(sizeof(gpuTile)));
            textures.setTexture(1, skyTexture.get(), RenderTextureLayout::SHADER_READ, skyTextureView.get());
            require(pipelines.prepare(device.get(), layout.get(), ms, false), "Could not restore stable PS after alpha regression");
            require(render(1, 0) == reflected, "Native-water alpha fixture failed to restore stable reflection output");

            // A live menu preview has its own world/camera, an oversized native
            // viewport and a tighter inset scissor. Thumbnail geometry shares
            // the frame's GPU streams but must not enter its reflection scene.
            // Exercise actual ray-hit colors, including an intentionally wrong
            // AS that proves the closer foreign-camera decoy is consequential.
            const float previewShift[3] = {100, 30, -200};
            for (uint32_t v = 0; v < 12; ++v)
                for (size_t c = 0; c < 3; ++c) world[v][c] = savedWorld[v][c] + previewShift[c];
            for (size_t c = 0; c < 3; ++c) {
                reflection.camera[c] = savedReflection.camera[c] + previewShift[c];
                reflection.skyCamera[c] = savedReflection.skyCamera[c] + previewShift[c];
            }
            for (uint32_t v = 0; v < 4; ++v) {
                screen[v][0] = 8 + savedScreen[v][0] * .875f;
                screen[v][1] = 12 + savedScreen[v][1] * .75f;
            }
            fill(screenBuffer, screen, sizeof(screen));
            clearDestination = RenderColor(77.0f / 255, 33.0f / 255, 91.0f / 255, 1);
            bindWaterAdjacency();
            reflection.smoothNormals = 1;
            WR64RTPreviewDomain previewDomain{}, decoyDomain{};
            auto preparePreviewScene = [&](bool forceIncludeDecoy) {
                std::vector<Wr64RTSceneGeometry> geometry;
                if (wr64RTSamePreviewDomain(previewDomain, previewDomain)) geometry.push_back({6, 3, 1});
                if (forceIncludeDecoy || wr64RTSamePreviewDomain(decoyDomain, previewDomain))
                    geometry.push_back({9, 3, 2});
                require(scene.prepare(device.get(), positions.get(), faces.get(), 14, 27, geometry),
                    "Could not prepare inset preview acceleration structure");
                common.setAccelerationStructure(common.SceneBVH, scene.accelerationStructure());
            common.setBuffer(common.wr64FenceProxy,scene.proxyBuffer(),scene.proxyBufferSize());
                common.setBuffer(common.interleavedRasters, scene.geometryBuffer(),
                    scene.geometryBufferSize(), RenderBufferStructuredView(16));
                rebuildPositions();
            };
            auto panelChanged = [&](const Pixels &a, const Pixels &b) {
                size_t changed = 0;
                for (int y = drawScissor.top; y < drawScissor.bottom; ++y)
                    for (int x = drawScissor.left; x < drawScissor.right; ++x) {
                        const size_t p = (size_t(y) * Width + x) * 4;
                        bool pixelChanged = false;
                        for (size_t c = 0; c < 3; ++c)
                            pixelChanged |= std::abs(int(a[p + c]) - int(b[p + c])) > 2;
                        changed += pixelChanged;
                    }
                return changed;
            };
            auto outsidePanelUnchanged = [&](const Pixels &pixels) {
                const uint8_t sentinel[4] = {77, 33, 91, 255};
                size_t checked = 0;
                bool untouched = true;
                for (uint32_t y = 0; y < Height; ++y) for (uint32_t x = 0; x < Width; ++x) {
                    if (int(x) >= drawScissor.left && int(x) < drawScissor.right &&
                        int(y) >= drawScissor.top && int(y) < drawScissor.bottom) continue;
                    ++checked;
                    for (size_t c = 0; c < 4; ++c)
                        untouched &= pixels[(y * Width + x) * 4 + c] == sentinel[c];
                }
                return untouched && checked > 2000;
            };
            for (const RenderRect &panel : {RenderRect(32, 20, 60, 56), RenderRect(16, 20, 60, 56)}) {
                drawScissor = panel;
                previewDomain.nativeWaterViewport = wr64RTMenuWaterViewport(0x800DA8F0);
                previewDomain.scale[0] = 212; previewDomain.scale[1] = 120; previewDomain.scale[2] = 511;
                previewDomain.translate[0] = 278; previewDomain.translate[1] = 156; previewDomain.translate[2] = 511;
                previewDomain.scissor[0] = panel.left * 4; previewDomain.scissor[1] = panel.top * 4;
                previewDomain.scissor[2] = panel.right * 4; previewDomain.scissor[3] = panel.bottom * 4;
                decoyDomain = previewDomain;
                decoyDomain.nativeWaterViewport = wr64RTMenuWaterViewport(0x07001280);
                require(wr64RTSamePreviewDomain(previewDomain, previewDomain) &&
                    !wr64RTSamePreviewDomain(decoyDomain, previewDomain),
                    "Native preview-domain helper admitted the thumbnail's foreign viewport source");
                // Native sky vertices are unused in this stage and provide
                // storage for a green triangle closer than the red preview
                // object. Its draw belongs to a different synthetic camera.
                const uint32_t decoyIds[3] = {7, 8, 11};
                const float decoy[3][3] = {{-100, -100, 5}, {100, -100, 5}, {0, 200, 5}};
                for (size_t v = 0; v < 3; ++v) for (size_t c = 0; c < 3; ++c)
                    world[decoyIds[v]][c] = decoy[v][c] + previewShift[c];
                reflection.sky[3] = 0; reflection.skyBackdrop[3] = 0;
                preparePreviewScene(false);
                const auto insetOff = render(0, 0);
                const auto isolatedPreview = render(1, 0);
                const size_t reflectionPixels = panelChanged(insetOff, isolatedPreview);
                require(reflectionPixels > 900 && outsidePanelUnchanged(insetOff) && outsidePanelUnchanged(isolatedPreview),
                    "Inset preview missed native water or changed pixels outside its scissor");

                preparePreviewScene(true);
                const auto contaminatedPreview = render(1, 0);
                const size_t contaminatedPixels = panelChanged(isolatedPreview, contaminatedPreview);
                require(contaminatedPixels > 900 && outsidePanelUnchanged(contaminatedPreview),
                    "Foreign-camera decoy did not provide a meaningful contaminated-AS positive control");
                preparePreviewScene(false);
                require(render(1, 0) == isolatedPreview,
                    "Removing unrelated thumbnail geometry failed to restore inset reflections exactly");
                // Even the same source viewport/camera cannot admit another
                // pane with different clipping. Use the actual CPU helper to
                // build the AS instead of assuming source identity is enough.
                decoyDomain.nativeWaterViewport = true;
                decoyDomain.scissor[0] += 12;
                require(!wr64RTSamePreviewDomain(decoyDomain, previewDomain),
                    "Preview-domain helper admitted another pane's scissor");
                preparePreviewScene(false);
                require(render(1, 0) == isolatedPreview,
                    "Another pane sharing the viewport source contaminated the preview reflection");
                for (uint32_t v : decoyIds) world[v][0] += 10000;
                rebuildPositions();
                require(render(1, 0) == isolatedPreview,
                    "Animation in an excluded thumbnail changed the preview's reflection");
                for (size_t c = 0; c < 3; ++c) reflection.camera[c] = savedReflection.camera[c];
                const auto wrongCameraPreview = render(1, 0);
                const size_t wrongCameraPixels = panelChanged(isolatedPreview, wrongCameraPreview);
                require(wrongCameraPixels > 900,
                    "Inset fixture could not distinguish its own camera from a different scene camera");
                for (size_t c = 0; c < 3; ++c) reflection.camera[c] = savedReflection.camera[c] + previewShift[c];
                require(render(1, 0) == isolatedPreview && render(0, 0) == insetOff,
                    "Restoring the preview camera or disabling RT failed to restore its original output");

                // Native menu submode 2 draws its sky backdrop without the
                // cloud fan. Verify that a valid local backdrop alone supplies
                // reflected sky and remains confined to the live preview.
                for (uint32_t v = 7; v < 12; ++v) for (size_t c = 0; c < 3; ++c)
                    world[v][c] = savedWorld[v][c] + previewShift[c];
                for (uint32_t v = 4; v < 7; ++v) world[v][0] += 1000;
                rebuildPositions();
                reflection.skyBackdrop[0] = 9; reflection.skyBackdrop[1] = 2;
                reflection.skyBackdrop[2] = 4; reflection.skyBackdrop[3] = 1;
                for (size_t c = 0; c < 3; ++c)
                    reflection.skyBackdropCamera[c] = savedReflection.skyCamera[c] + previewShift[c];
                require(pipelines.prepare(device.get(), layout.get(), ms, false, true),
                    "Could not select sky pipeline for inset backdrop-only preview");
                const auto backdropPreview = render(1, 0);
                const auto backdropCoverage = render(1, 3);
                const size_t backdropPixels = panelChanged(insetOff, backdropPreview);
                size_t localSkyPixels = 0;
                for (int y = panel.top; y < panel.bottom; ++y) for (int x = panel.left; x < panel.right; ++x) {
                    const size_t p = (size_t(y) * Width + x) * 4;
                    localSkyPixels += nearByte(backdropCoverage[p], 0) &&
                        nearByte(backdropCoverage[p + 1], 166) && nearByte(backdropCoverage[p + 2], 255);
                }
                require(backdropPixels > 900 && localSkyPixels > 900 &&
                    outsidePanelUnchanged(backdropPreview) && outsidePanelUnchanged(backdropCoverage),
                    "Backdrop-only menu preview failed to reflect its local sky or escaped its scissor");
                reflection.skyBackdrop[3] = 0;
                require(render(1, 0) == insetOff && render(0, 0) == insetOff,
                    "Inset preview without sky or opaque coverage changed native water fallback");
                for (uint32_t v = 4; v < 7; ++v) world[v][0] -= 1000;
                rebuildPositions();
                require(pipelines.prepare(device.get(), layout.get(), ms, false),
                    "Could not restore stable preview pipeline");
                std::printf("%ux MSAA inset preview [%d,%d,%d,%d]: reflected%zu foreign-decoy%zu wrong-camera%zu backdrop%zu; outside sentinel unchanged.\n",
                    samples, panel.left, panel.top, panel.right, panel.bottom,
                    reflectionPixels, contaminatedPixels, wrongCameraPixels, backdropPixels);
            }
            std::memcpy(world, savedWorld, sizeof(world));
            std::memcpy(screen, savedScreen, sizeof(screen));
            fill(screenBuffer, screen, sizeof(screen));
            reflection = savedReflection;
            drawScissor = RenderRect(0, 0, Width, Height);
            clearDestination = RenderColor(0, 0, 0, 0);
            preparePreviewScene(false);
            require(render(1, 0) == reflected && render(0, 0) == original,
                "Inset fixture failed to restore the full-frame reflection and disabled baselines");

            // Celestial bodies are native screen sprites reconstructed before
            // camera culling. Exercise the real bounded shader payload against
            // the original raster sampler, rather than a matching CPU sampler.
            // The projection below maps the reflected direction of this water
            // quad to its 64x64 native-pixel coordinates. Translation has no
            // place in these direction-only projection rows.
            const auto celestialStart = reflection;
            const auto celestialRdp = rdp[2];
            const auto celestialParams = params[2];
            const auto celestialOpaqueParams = params[1];
            const auto celestialOpaqueRdp = rdp[1];
            float celestialSavedUV[16][2];
            std::memcpy(celestialSavedUV, uv, sizeof(uv));
            for (uint32_t v = 4; v < 7; ++v) world[v][0] += 1000;
            rebuildPositions();
            reflection.sky[3] = reflection.skyBackdrop[3] = 0;
            reflection.celestialProjection[0][0] = 64;
            reflection.celestialProjection[0][1] = 32;
            reflection.celestialProjection[1][1] = 96;
            reflection.celestialProjection[1][2] = -64;
            reflection.celestialProjection[2][1] = 1;
            require(pipelines.prepare(device.get(), layout.get(), ms, false, true),
                "Could not select celestial reflection pipeline");
            const auto emptyCelestial = render(1, 0);
            require(emptyCelestial == original, "An empty celestial list changed native miss fallback");
            auto packCelestialAlpha = [&](size_t offset, uint8_t value) {
                if (offset >= 2064) throw std::runtime_error("Celestial test alpha packing exceeded its native buffer");
                uint32_t &word = reflection.celestialAlpha[offset / 16][(offset / 4) % 4];
                const uint32_t shift = uint32_t(offset % 4) * 8;
                word = (word & ~(255u << shift)) | uint32_t(value) << shift;
            };
            auto celestialRecord = [&](float left, float top, float right, float bottom,
                float red, float green, float blue, float alpha, uint32_t offset, uint32_t size) {
                CelestialRecord record;
                record.bounds[0] = left; record.bounds[1] = top;
                record.bounds[2] = right; record.bounds[3] = bottom;
                record.uv[2] = record.uv[3] = float(size);
                record.color[0] = red; record.color[1] = green;
                record.color[2] = blue; record.color[3] = alpha;
                record.meta[0] = offset; record.meta[1] = record.meta[2] = size;
                return record;
            };
            // Decoded native IA alpha, with an asymmetric interior pattern that
            // distinguishes native three-point filtering from ordinary bilerp.
            Pixels celestialBytes(32 * 256, 0);
            for (uint32_t y = 0; y < 32; ++y) for (uint32_t x = 0; x < 32; ++x) {
                const float dx = float(x) - 15.5f, dy = float(y) - 15.5f;
                const float radius = std::sqrt(dx * dx + dy * dy);
                const uint8_t a = radius >= 14 ? 0 : (radius < 11 ?
                    uint8_t(17 * (3 + (x * 7 + y * 11) % 13)) : uint8_t(17 * int((14 - radius) * 5)));
                packCelestialAlpha(y * 32 + x, a);
                packCelestialAlpha(1024 + y * 32 + x, a);
                const size_t p = y * 256 + x * 4;
                celestialBytes[p] = celestialBytes[p + 1] = celestialBytes[p + 2] = 255;
                celestialBytes[p + 3] = a;
            }
            for (size_t i = 2048; i < 2064; ++i) packCelestialAlpha(i, 255);
            auto celestialTexture = device->createTexture(RenderTextureDesc::Texture2D(32, 32, 1,
                RenderFormat::R8G8B8A8_UNORM));
            auto celestialTextureView = celestialTexture->createTextureView(
                RenderTextureViewDesc::Texture2D(RenderFormat::R8G8B8A8_UNORM));
            auto celestialUpload = upload(celestialBytes.data(), celestialBytes.size(), 0);
            worker.commandList->begin();
            worker.commandList->barriers(RenderBarrierStage::COPY,
                RenderTextureBarrier(celestialTexture.get(), RenderTextureLayout::COPY_DEST));
            worker.commandList->copyTextureRegion(RenderTextureCopyLocation::Subresource(celestialTexture.get()),
                RenderTextureCopyLocation::PlacedFootprint(celestialUpload,
                    RenderFormat::R8G8B8A8_UNORM, 32, 32, 1, 64));
            worker.commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE,
                RenderTextureBarrier(celestialTexture.get(), RenderTextureLayout::SHADER_READ));
            worker.commandList->end(); worker.execute(); worker.wait();
            textures.setTexture(0, celestialTexture.get(), RenderTextureLayout::SHADER_READ, celestialTextureView.get());
            interop::RDPTile celestialTile = rdpTile;
            celestialTile.fmt = 3; celestialTile.siz = 1; celestialTile.stride = 32;
            celestialTile.lrs = celestialTile.lrt = 31 * 4;
            interop::GPUTile celestialGpuTile = gpuTile;
            celestialGpuTile.textureDimensions = hlslpp::float3(32, 32, 1);
            common.setBuffer(common.RDPTiles, upload(&celestialTile, sizeof(celestialTile), RenderBufferFlag::STORAGE),
                sizeof(celestialTile), RenderBufferStructuredView(sizeof(celestialTile)));
            common.setBuffer(common.GPUTiles, upload(&celestialGpuTile, sizeof(celestialGpuTile), RenderBufferFlag::STORAGE),
                sizeof(celestialGpuTile), RenderBufferStructuredView(sizeof(celestialGpuTile)));
            params[2] = textureSkyParams;
            params[2].flags.rect = 1;
            params[2].flags.linearFiltering = 0;
            params[2].omL = 0x00504240; params[2].omH = 0x00802C3F;
            auto nativeCelestialRaster = [&]() {
                // Native Rectangle flags expect clip-space raw vertices;
                // the water path instead consumes native pixel positions.
                float nativeScreen[4][4];
                std::memcpy(nativeScreen, screen, sizeof(nativeScreen));
                for (uint32_t v = 0; v < 4; ++v) {
                    screen[v][0] = nativeScreen[v][0] / 32 - 1;
                    screen[v][1] = 1 - nativeScreen[v][1] / 32;
                }
                fill(screenBuffer, screen, sizeof(screen));
                auto pixels = render(0, 0, 2, 0, 6);
                std::memcpy(screen, nativeScreen, sizeof(nativeScreen));
                fill(screenBuffer, screen, sizeof(screen));
                return pixels;
            };
            reflection.celestialInfo[0] = 1;
            reflection.celestial[0] = celestialRecord(0, 0, 64, 64, .3f, .7f, .9f, 1, 0, 32);
            size_t nativeCelestialCompared = 0, filteringControlPixels = 0;
            for (uint32_t material = 0; material < 5; ++material) {
                // Sun alpha comes from TEXEL0 despite native primitive alpha
                // zero. Moon/star alpha additionally uses primitive alpha.
                // Include the native endpoint spans: Sunset's fixed-point
                // 667 step gives31.25; DP's1365 gives31.96875; moon1536 gives36.
                // The final case deliberately crosses both clamp boundaries.
                const bool sunMaterial = material < 2 || material == 4;
                params[2].ccL = sunMaterial ? 0xFCFFFFFF : 0xFCFF97FF;
                params[2].ccH = sunMaterial ? 0xFFFDF2F9 : 0xFF2DFEFF;
                const float alpha = material == 3 ? 110.f / 255 : 1;
                rdp[2].primColor = hlslpp::float4(.3f, .7f, .9f, sunMaterial ? 0.f : alpha);
                reflection.celestial[0].color[3] = alpha;
                reflection.celestial[0].meta[0] = material == 3 ? 1024 : 0;
                const float span = material == 0 ? 31.25f : material == 1 ? 31.96875f : 36.f;
                reflection.celestial[0].uv[0] = material == 4 ? -2.25f : 0;
                reflection.celestial[0].uv[1] = material == 4 ? -1.125f : 0;
                reflection.celestial[0].uv[2] = material == 4 ? 35.5f : span;
                reflection.celestial[0].uv[3] = material == 4 ? 34.25f : span;
                for (uint32_t v = 0; v < 4; ++v) {
                    uv[v][0] = reflection.celestial[0].uv[0] + screen[v][0] / 64 * reflection.celestial[0].uv[2];
                    uv[v][1] = reflection.celestial[0].uv[1] + screen[v][1] / 64 * reflection.celestial[0].uv[3];
                }
                fill(uvBuffer, uv, sizeof(uv));
                fill(renderParamsBuffer, params, sizeof(params)); fill(rdpParamsBuffer, rdp, sizeof(rdp));
                const auto nativeSprite = nativeCelestialRaster();
                const auto reflectedSprite = render(1, 4);
                size_t disagreements = 0, visible = 0, transparent = 0;
                int maximum = 0;
                for (uint32_t y = 2; y < 62; ++y) for (uint32_t x = 2; x < 62; ++x) {
                    const size_t p = (y * Width + x) * 4;
                    int error = 0;
                    for (size_t c = 0; c < 3; ++c) error = std::max(error,
                        std::abs(int(nativeSprite[p + c]) - int(reflectedSprite[p + c])));
                    maximum = std::max(maximum, error); disagreements += error > 2;
                    visible += nativeSprite[p + 2] > 20;
                    transparent += nativeSprite[p] == 0 && nativeSprite[p + 1] == 0 && nativeSprite[p + 2] == 0;
                    ++nativeCelestialCompared;
                }
                std::printf("%ux MSAA celestial native material%u: disagreement%zu/3600 max%d visible%zu transparent%zu.\n",
                    samples, material, disagreements, maximum, visible, transparent);
                require(disagreements == 0 && visible > 1000 && transparent > 300,
                    "Celestial alpha/clamping/UV disagrees with its actual native three-point raster material");
                if (material == 4) {
                    params[2].flags.linearFiltering = 1;
                    fill(renderParamsBuffer, params, sizeof(params));
                    const auto bilinearSprite = nativeCelestialRaster();
                    for (size_t p = 0; p < Width * Height; ++p)
                        filteringControlPixels += std::abs(int(bilinearSprite[p * 4 + 2]) - int(nativeSprite[p * 4 + 2])) > 3;
                    require(filteringControlPixels > 300,
                        "Celestial native-sampler fixture cannot distinguish ordinary bilerp from N64 three-point filtering");
                    params[2].flags.linearFiltering = 0;
                }
            }
            params[2] = celestialParams; rdp[2] = celestialRdp;
            fill(renderParamsBuffer, params, sizeof(params)); fill(rdpParamsBuffer, rdp, sizeof(rdp));
            std::memcpy(uv, celestialSavedUV, sizeof(uv)); fill(uvBuffer, uv, sizeof(uv));
            textures.setTexture(0, skyTexture.get(), RenderTextureLayout::SHADER_READ, skyTextureView.get());
            common.setBuffer(common.RDPTiles, rdpTileBuffer, sizeof(rdpTile), RenderBufferStructuredView(sizeof(rdpTile)));
            common.setBuffer(common.GPUTiles, gpuTileBuffer, sizeof(gpuTile), RenderBufferStructuredView(sizeof(gpuTile)));

            // Each of all sixteen native stars receives an independent tint
            // and footprint; a loop that only samples one or a truncated prefix
            // cannot satisfy the per-star center checks.
            reflection.celestialInfo[0] = 16;
            for (uint32_t star = 0; star < 16; ++star) {
                const float x = 1.f + (star % 4) * 16.f, y = 1.f + (star / 4) * 16.f;
                reflection.celestial[star] = celestialRecord(x, y, x + 10, y + 10,
                    .15f + star * .045f, .8f - star * .03f, .2f + star * .035f, 1, 2048, 4);
            }
            const auto allStars = render(1, 4);
            for (uint32_t star = 0; star < 16; ++star) {
                const uint32_t x = 5 + (star % 4) * 16, y = 5 + (star / 4) * 16;
                const size_t p = (y * Width + x) * 4;
                for (size_t c = 0; c < 3; ++c)
                    require(std::abs(int(allStars[p + c]) - reflection.celestial[star].color[c] * 255) <= 1,
                        "A native star was omitted, inherited another tint, or used the wrong packed alpha offset");
            }
            // Final four records prove the complete fixed-capacity payload is
            // live, including two co-located moon passes with the same texture.
            reflection.celestialInfo[0] = 20;
            reflection.celestial[16] = celestialRecord(26, 26, 38, 38, 1, 1, 0, .4314f, 2048, 4);
            reflection.celestial[17] = celestialRecord(26, 26, 38, 38, 1, 1, 1, .5f, 2048, 4);
            reflection.celestial[18] = celestialRecord(26, 26, 38, 38, 1, 0, 0, .25f, 2048, 4);
            reflection.celestial[19] = celestialRecord(26, 26, 38, 38, 0, 0, 1, .25f, 2048, 4);
            const auto allBodies = render(1, 4);
            float ordered[3] = {0, 0, 0};
            // The center is outside all sixteen star footprints.
            for (uint32_t record = 16; record < 20; ++record) for (size_t c = 0; c < 3; ++c)
                ordered[c] = reflection.celestial[record].color[c] * reflection.celestial[record].color[3] +
                    ordered[c] * (1 - reflection.celestial[record].color[3]);
            const auto orderedCenter = center(allBodies);
            for (size_t c = 0; c < 3; ++c)
                require(std::abs(float(orderedCenter[c]) - ordered[c] * 255) <= 1,
                    "Celestial layers were deduplicated, reordered, or the last bounded records were ignored");
            std::swap(reflection.celestial[16], reflection.celestial[17]);
            require(center(render(1, 4)) != orderedCenter,
                "Overlapping moon fixture does not distinguish native layer order");
            std::swap(reflection.celestial[16], reflection.celestial[17]);
            const auto celestialOff = render(0, 0);
            require(celestialOff == original, "RT Off sampled populated celestial metadata");
            require(pipelines.prepare(device.get(), layout.get(), ms, false), "Could not select stable celestial exclusion reference");
            require(render(1, 0) == emptyCelestial, "Stable object-only pipeline sampled celestial records");
            require(pipelines.prepare(device.get(), layout.get(), ms, false, true), "Could not restore sky celestial pipeline");

            // Neither the screen rectangle nor its ray lookup is clipped to
            // the primary display. A source at native X+1024 still reflects
            // identically when the directional projector describes that field.
            reflection.celestialProjection[0][1] += 1024;
            for (uint32_t i = 0; i < 20; ++i) {
                reflection.celestial[i].bounds[0] += 1024;
                reflection.celestial[i].bounds[2] += 1024;
            }
            require(render(1, 4) == allBodies, "Unculled offscreen celestial bodies disappeared from reflected lookup");
            reflection.celestialProjection[0][1] += 100;
            require(render(1, 4) != allBodies, "Celestial fixture cannot detect an incorrect presentation projector");
            reflection.celestialProjection[0][1] -= 1124;
            for (uint32_t i = 0; i < 20; ++i) {
                reflection.celestial[i].bounds[0] -= 1024;
                reflection.celestial[i].bounds[2] -= 1024;
            }
            const float celestialShift[3] = {1024, 64, -2048};
            for (auto &vertex : world) for (size_t c = 0; c < 3; ++c) vertex[c] += celestialShift[c];
            for (size_t c = 0; c < 3; ++c) reflection.camera[c] += celestialShift[c];
            rebuildPositions();
            require(render(1, 4) == allBodies, "Directional celestial reflection changed under camera/world translation");
            for (auto &vertex : world) for (size_t c = 0; c < 3; ++c) vertex[c] -= celestialShift[c];
            for (size_t c = 0; c < 3; ++c) reflection.camera[c] -= celestialShift[c];
            rebuildPositions();

            // Full, partial and absent native clouds composite over celestial
            // bodies. A synthetic opaque backdrop ensures this also exercises
            // straight/premultiplied conversion instead of only black misses.
            reflection.skyBackdrop[0] = 9; reflection.skyBackdrop[1] = 2;
            reflection.skyBackdrop[2] = 4; reflection.skyBackdrop[3] = 1;
            std::memcpy(reflection.skyBackdropCamera, reflection.skyCamera, sizeof(reflection.skyCamera));
            const auto behindClouds = render(1, 4);
            params[1] = primitiveSkyParams;
            params[1].omL = 0x00504240; params[1].omH = 0x00882C3F;
            rdp[1].primColor = hlslpp::float4(.12f, .24f, .8f, .5f);
            fill(renderParamsBuffer, params, sizeof(params)); fill(rdpParamsBuffer, rdp, sizeof(rdp));
            reflection.sky[0] = 9; reflection.sky[1] = 1; reflection.sky[2] = 4; reflection.sky[3] = 1;
            reflection.skyCloudParams[2] = 0;
            const auto partialClouds = render(1, 4);
            const float cloudRgb[3] = {.12f, .24f, .8f};
            bool cloudsOverBodies = true;
            for (uint32_t y = 2; y < 62; ++y) for (uint32_t x = 2; x < 62; ++x) for (size_t c = 0; c < 3; ++c) {
                const size_t p = (y * Width + x) * 4 + c;
                cloudsOverBodies &= std::abs(partialClouds[p] - (.5f * behindClouds[p] + .5f * 255 * cloudRgb[c])) <= 2;
            }
            require(cloudsOverBodies, "Native cloud opacity did not correctly cover the celestial layer over its backdrop");
            rdp[1].primColor = hlslpp::float4(.12f, .24f, .8f, 1);
            fill(rdpParamsBuffer, rdp, sizeof(rdp));
            const auto opaqueCloudBodies = render(1, 4);
            reflection.celestialInfo[0] = 0;
            require(render(1, 4) == opaqueCloudBodies, "Opaque native clouds leaked celestial bodies through their surface");
            reflection.sky[3] = reflection.skyBackdrop[3] = 0;
            require(render(1, 0) == emptyCelestial, "Removing celestial and sky data failed to restore byte-identical fallback");
            reflection.celestialInfo[0] = 21;
            require(render(1, 0) == emptyCelestial, "Oversized celestial list was read past its fixed native capacity");
            reflection.celestialInfo[0] = 20;
            reflection.celestialProjection[2][1] = -1;
            require(render(1, 0) == emptyCelestial, "Behind-camera celestial projection was accepted");
            reflection.celestialProjection[2][1] = 1;
            reflection.celestialInfo[0] = 1;
            const auto validBody = reflection.celestial[0];
            for (uint32_t invalid = 0; invalid < 5; ++invalid) {
                reflection.celestial[0] = validBody;
                if (invalid == 0) reflection.celestial[0].meta[0] = 2060;
                if (invalid == 1) reflection.celestial[0].meta[1] = 33;
                if (invalid == 2) reflection.celestial[0].meta[3] = 1;
                if (invalid == 3) reflection.celestial[0].bounds[2] = reflection.celestial[0].bounds[0];
                if (invalid == 4) reflection.celestial[0].color[0] = std::numeric_limits<float>::quiet_NaN();
                require(render(1, 0) == emptyCelestial,
                    "Invalid celestial dimensions, packed-alpha bounds, flags, color or footprint were sampled");
            }
            reflection.celestial[0] = validBody; reflection.celestialInfo[0] = 20;
            params[1] = celestialOpaqueParams; rdp[1] = celestialOpaqueRdp;
            fill(renderParamsBuffer, params, sizeof(params)); fill(rdpParamsBuffer, rdp, sizeof(rdp));
            for (uint32_t v = 4; v < 7; ++v) world[v][0] -= 1000;
            rebuildPositions();
            require(render(1, 0) == reflected,
                "Celestial lookup changed an opaque scene reflection instead of respecting ray-hit priority");
            reflection = celestialStart;
            require(pipelines.prepare(device.get(), layout.get(), ms, false), "Could not restore stable pipeline after celestial suite");
            require(render(1, 0) == reflected && render(0, 0) == original,
                "Celestial fixture failed to restore stable and native baselines");
            std::printf("%ux MSAA celestial: %zu native material samples; bilerp positive control%zu pixels; all16stars/20records, ordering, offscreen lookup, translation, cloud/object occlusion and guards passed.\n",
                samples, nativeCelestialCompared, filteringControlPixels);

            // Diagnostic water visibility shares the production reflection AS.
            // The water layer uses independently softened physical scenery.
            // The analytic reference casts equal-area disc rays into this triangle.
            // This separate horizontal triangle is behind the reflected-ray
            // footprint, but lies on a subset of the rays toward the light.
            // Thus its shadow is measurable without becoming the reflection.
            const auto shadowStart = reflection;
            const uint32_t shadowIds[3] = {7, 8, 11};
            const float shadowCaster[3][4] = {{-100, 5, -30, 1}, {100, 5, -30, 1}, {0, 5, -9, 1}};
            for (size_t v = 0; v < 3; ++v) std::memcpy(world[shadowIds[v]], shadowCaster[v], sizeof(shadowCaster[v]));
            for (uint32_t v = 4; v < 7; ++v) world[v][0] += 1000;
            reflection.shadowLight[0] = 0;
            reflection.shadowLight[1] = 1.f / std::sqrt(5.f);
            reflection.shadowLight[2] = -2.f / std::sqrt(5.f);
            reflection.shadowLight[3] = .55f;
            reflection.shadowOptions[0] = 1;
            reflection.shadowOptions[1] = .5f;
            reflection.shadowOptions[2] = 30000;
            auto prepareShadowScene = [&](uint32_t casterFlags) {
                require(scene.prepare(device.get(), positions.get(), faces.get(), 14, 27,
                    {{6, 3, 1, 0}, {9, 3, 2, casterFlags}}), "Could not prepare shared shadow/reflection AS");
                common.setAccelerationStructure(common.SceneBVH, scene.accelerationStructure());
            common.setBuffer(common.wr64FenceProxy,scene.proxyBuffer(),scene.proxyBufferSize());
                common.setBuffer(common.interleavedRasters, scene.geometryBuffer(),
                    scene.geometryBufferSize(), RenderBufferStructuredView(16));
                rebuildPositions();
            };
            prepareShadowScene(1);
            reflection.shadowOptions[0] = 0;
            const auto noShadow = render(1, 0);
            reflection.shadowOptions[0] = 1;
            const auto shadowMask = render(1, 5);
            const auto shadowedWater = render(1, 0);
            auto sceneryTriangleCoverage = [&](uint32_t x, uint32_t y, uint32_t count=8u) {
                const double px=(x+.5)/6.4-5, pz=5-(y+.5)/6.4;
                uint32_t hits=0;
                for(uint32_t pair=0;pair<count/2;++pair) for(double sign:{-1.0,1.0}) {
                    const double radius=6*std::sqrt((pair+.5)/(count/2)),angle=pair*3.14159265358979323846*(3-std::sqrt(5.0));
                    const double hx=px+sign*radius*std::cos(angle),hz=pz-9-sign*radius*std::sin(angle);
                    const double t=(hz+30)/21;
                    hits+=t>=0&&t<=1&&std::abs(hx)<=100*(1-t);
                }
                return hits/double(count);
            };
            size_t blockedPixels = 0, litPixels = 0, fractionalSceneryPixels=0;
            bool shadowFloor = true, shadowCoverage = true;
            for (size_t p = 0; p < Width * Height; ++p) {
                const size_t i = p * 4;
                const bool blocked = shadowMask[i] == 0;
                blockedPixels += blocked; litPixels += shadowMask[i] == 255;
                fractionalSceneryPixels += shadowMask[i]>0&&shadowMask[i]<255;
                const double coverage=sceneryTriangleCoverage(uint32_t(p%Width),uint32_t(p/Width));
                const float q = float(1-.28*coverage);
                shadowFloor &= std::abs(shadowMask[i]-255*(1-coverage))<=1;
                for (size_t c = 0; c < 3; ++c)
                    shadowFloor &= std::abs(float(shadowedWater[i + c]) - q*noShadow[i + c]) <= 2;
                shadowCoverage &= shadowedWater[i + 3] == noShadow[i + 3];
            }
            require(noShadow == original && fractionalSceneryPixels > 1000 &&
                blockedPixels + litPixels + fractionalSceneryPixels == Width * Height, "Scenery disc rays missed their independently expected soft edge");
            require(shadowFloor && shadowCoverage,
                "Scenery water attenuation disagreed with analytic coverage or changed native coverage");
            require(render(0, 0) == original, "RT Off retained the populated water-shadow options");
            reflection.shadowLight[3] = 0;
            require(render(1, 0) == noShadow, "Zero shadow strength did not preserve exact legacy output");
            reflection.shadowLight[3] = .55f;
            auto shadowWhite=[](const Pixels& pixels) {
                for(size_t p=0;p<pixels.size();p+=4) if(pixels[p]!=255||pixels[p+1]!=255||pixels[p+2]!=255) return false;
                return true;
            };
            reflection.shadowLight[2] = -reflection.shadowLight[2];
            require(shadowWhite(render(1,5)), "Wrong light direction still hit the diagnostic blocker");
            reflection.shadowLight[2] = -reflection.shadowLight[2];
            prepareShadowScene(0);
            require(shadowWhite(render(1,5)), "Reflection-only geometry incorrectly terminated a diagnostic shadow ray");
            prepareShadowScene(1);
            for (uint32_t v : shadowIds) world[v][0] += 1000;
            rebuildPositions();
            require(shadowWhite(render(1,5)), "Shadow query used stale caster positions after the shared AS update");
            for (uint32_t v : shadowIds) world[v][0] -= 1000;
            rebuildPositions();
            require(render(1,5)==shadowMask, "Restoring the current caster did not restore its exact diagnostic mask");
            reflection.shadowOptions[1] = 8;
            require(shadowWhite(render(1,5)), "A caster below the biased shadow origin contaminated its diagnostic mask");
            reflection.shadowOptions[1] = .5f;
            for (uint32_t invalid = 0; invalid < 4; ++invalid) {
                const auto validLight = reflection;
                if (invalid == 0) reflection.shadowLight[0] = std::numeric_limits<float>::quiet_NaN();
                if (invalid == 1) reflection.shadowOptions[1] = std::numeric_limits<float>::quiet_NaN();
                if (invalid == 2) reflection.shadowOptions[2] = -1;
                if (invalid == 3) reflection.shadowLight[0] = 1e30f;
                require(shadowWhite(render(1,5))&&render(1,0)==noShadow, "Invalid diagnostic shadow direction, normalization, bias or distance changed the native result");
                reflection = validLight;
            }

            // Surface attenuation includes native water and transmitted destination,
            // while retaining native framebuffer coverage and its zero-strength path.
            params[0] = textureSkyParams;
            params[0].ccL = 0xFCFFFFFF; params[0].ccH = 0xFFFCF279;
            params[0].omL = 0x005049D8; params[0].omH = 0x00082CFF;
            renderIndices[0].rdpTileIndex = 1; renderIndices[0].rdpTileCount = 1;
            fill(renderParamsBuffer, params, sizeof(params));
            fill(renderIndicesBuffer, renderIndices, sizeof(renderIndices));
            common.setBuffer(common.RDPTiles, upload(alphaTiles, sizeof(alphaTiles), RenderBufferFlag::STORAGE),
                sizeof(alphaTiles), RenderBufferStructuredView(sizeof(interop::RDPTile)));
            common.setBuffer(common.GPUTiles, upload(alphaGpuTiles, sizeof(alphaGpuTiles), RenderBufferFlag::STORAGE),
                sizeof(alphaGpuTiles), RenderBufferStructuredView(sizeof(interop::GPUTile)));
            textures.setTexture(1, waterTexture.get(), RenderTextureLayout::SHADER_READ, waterTextureView.get());
            clearDestination = RenderColor(.8f, .4f, .2f, 1);
            size_t translucentChecks = 0, waterOnlyControl = 0;
            int shadowAlphaMaximum = 0;
            for (uint8_t alpha : {uint8_t(0), uint8_t(64), uint8_t(179), uint8_t(255)}) {
                setNativeWaterAlpha(alpha);
                reflection.shadowOptions[0] = 0;
                const auto nativeTransmission = render(1, 0);
                reflection.shadowOptions[0] = 1;
                const auto shadowTransmission = render(1, 0);
                bool correctTransmission = true, sameCoverage = true;
                for (uint32_t y = 2; y < 62; ++y) for (uint32_t x = 2; x < 62; ++x) {
                    const size_t p = (y * Width + x) * 4;
                    const float q = float(1-.28*sceneryTriangleCoverage(x,y));
                    for (size_t c = 0; c < 3; ++c) {
                        const int error = int(std::ceil(std::abs(float(shadowTransmission[p + c]) - q*nativeTransmission[p + c])));
                        shadowAlphaMaximum = std::max(shadowAlphaMaximum, error);
                        correctTransmission &= error <= 2;
                        const float wrongWaterOnly = q*(alpha/255.f)*(c==0?26.f:c==1?51.f:179.f)+(1-alpha/255.f)*destinationRGB[c];
                        waterOnlyControl += q < 1 && std::abs(shadowTransmission[p + c] - wrongWaterOnly) > 10;
                    }
                    sameCoverage &= shadowTransmission[p + 3] == nativeTransmission[p + 3];
                    ++translucentChecks;
                }
                require(correctTransmission && sameCoverage,
                    "Soft scenery water changed the intended native/transmission composition");
                reflection.shadowLight[3] = 0;
                require(render(1, 0) == nativeTransmission, "Zero-strength translucent shadow was not byte-identical");
                reflection.shadowLight[3] = .55f;
            }
            require(waterOnlyControl > 5000,
                "Native-alpha fixture cannot distinguish attenuating only water from the complete transmitted base");

            // Preserve the complete reflected-object/native-water blend.
            // Reintroduce the red wall into the same AS as the shadow blocker.
            setNativeWaterAlpha(179);
            for (uint32_t v = 4; v < 7; ++v) world[v][0] -= 1000;
            rebuildPositions();
            reflection.shadowOptions[0] = 0;
            const auto unshadowedObject = render(1, 0);
            // Debug2 deliberately retains native water alpha. Capture its
            // ray-hit classification with opaque water, then restore the real
            // translucent material for the composition comparison.
            setNativeWaterAlpha(255);
            const auto objectMask = render(1, 2);
            setNativeWaterAlpha(179);
            reflection.shadowOptions[0] = 1;
            const auto shadowedObject = render(1, 0);
            size_t objectShadowChecks = 0, darkReflectionControl = 0;
            bool objectContributionPreserved = true;
            float objectMaximumError = 0;
            const float waterA = 179.f / 255;
            const float nativeWaterRGB[3] = {26, 51, 179};
            for (uint32_t y = 2; y < 62; ++y) for (uint32_t x = 2; x < 62; ++x) {
                const size_t p = (y * Width + x) * 4;
                if (objectMask[p + 1] != 255) continue;
                const float px = (x + .5f) / 6.4f - 5, pz = 5 - (y + .5f) / 6.4f;
                const float nDotV = 10 / std::sqrt(px * px + 100 + (pz + 10) * (pz + 10));
                const float fresnel = .08f + .35f * std::pow(1 - nDotV, 5);
                const float q = float(1-.28*sceneryTriangleCoverage(x,y));
                for (size_t c = 0; c < 3; ++c) {
                    const float attenuatedTerm = waterA * (1 - fresnel) * nativeWaterRGB[c] + (1 - waterA) * destinationRGB[c];
                    const float expected = unshadowedObject[p + c]-(1-q)*attenuatedTerm;
                    const float error = std::abs(shadowedObject[p + c] - expected);
                    objectMaximumError = std::max(objectMaximumError, error);
                    objectContributionPreserved &= error <= 2;
                    darkReflectionControl += q < 1 && std::abs(float(shadowedObject[p + c]) - q * unshadowedObject[p + c]) > 3;
                }
                objectContributionPreserved &= shadowedObject[p + 3] == unshadowedObject[p + 3];
                ++objectShadowChecks;
            }
            std::printf("%ux MSAA shadow/object composition: compared%zu maxerror%.3f post-darkening control%zu.\n",
                samples, objectShadowChecks, objectMaximumError, darkReflectionControl);
            require(objectShadowChecks > 3000 && objectContributionPreserved && darkReflectionControl > 500,
                "Water shadow darkened the reflected object or used the wrong native/transmission blend order");

            // The same invariant applies to the newer environment composition.
            // A bright celestial record at a grazing angle makes incorrectly
            // darkening the reflection itself a strong positive control.
            for (uint32_t v = 4; v < 7; ++v) world[v][0] += 1000;
            rebuildPositions();
            reflection.camera[1] = 1;
            reflection.celestialProjection[0][0] = 64; reflection.celestialProjection[0][1] = 32;
            reflection.celestialProjection[1][1] = 96; reflection.celestialProjection[1][2] = -64;
            reflection.celestialProjection[2][1] = 1;
            reflection.celestialInfo[0] = 1;
            for (size_t i = 2048; i < 2064; ++i) packCelestialAlpha(i, 255);
            reflection.celestial[0] = celestialRecord(-100000, -100000, 100000, 100000, .9f, .8f, .2f, 1, 2048, 4);
            require(pipelines.prepare(device.get(), layout.get(), ms, false, true), "Could not select sky-shadow composition test");
            reflection.shadowOptions[0] = 0;
            const auto nativeSkyShadow = render(0, 0);
            const auto unshadowedSky = render(1, 0);
            const auto directSkyUnshadowed = render(1, 4);
            reflection.shadowOptions[0] = 1;
            const auto shadowedSky = render(1, 0);
            bool skyTermPreserved = true;
            size_t skyShadowChecks = 0, darkSkyControl = 0;
            const float iorTerm = (1.333f - 1) / (1.333f + 1), skyF0 = iorTerm * iorTerm;
            for (uint32_t y = 2; y < 62; ++y) for (uint32_t x = 2; x < 62; ++x) {
                const size_t p = (y * Width + x) * 4;
                const float px = (x + .5f) / 6.4f - 5, pz = 5 - (y + .5f) / 6.4f;
                const float nDotV = 1 / std::sqrt(px * px + 1 + (pz + 10) * (pz + 10));
                const float fresnel = skyF0 + (1 - skyF0) * std::pow(1 - nDotV, 5);
                const float q = float(1-.28*sceneryTriangleCoverage(x,y));
                for (size_t c = 0; c < 3; ++c) {
                    const float expected = unshadowedSky[p + c]-(1-fresnel)*(1-q)*nativeSkyShadow[p+c];
                    skyTermPreserved &= std::abs(shadowedSky[p + c] - expected) <= 2;
                    darkSkyControl += q < 1 && std::abs(float(shadowedSky[p + c]) - q * unshadowedSky[p + c]) > 10;
                }
                skyTermPreserved &= shadowedSky[p + 3] == unshadowedSky[p + 3];
                ++skyShadowChecks;
            }
            require(skyTermPreserved && darkSkyControl > 2000,
                "Water shadow attenuated reflected sky/celestial light or changed its final compositing response");
            require(render(1, 4) == directSkyUnshadowed && render(0, 0) == nativeSkyShadow,
                "Shadows altered the sky diagnostic or native RT-Off result");
            reflection.shadowLight[3] = 0;
            require(render(1, 0) == unshadowedSky, "Zero shadow strength did not restore exact celestial/sky output");

            std::memcpy(world, savedWorld, sizeof(world));
            reflection = shadowStart;
            params[0] = alphaWaterParams; renderIndices[0] = alphaWaterIndices;
            fill(renderParamsBuffer, params, sizeof(params)); fill(renderIndicesBuffer, renderIndices, sizeof(renderIndices));
            common.setBuffer(common.RDPTiles, rdpTileBuffer, sizeof(rdpTile), RenderBufferStructuredView(sizeof(rdpTile)));
            common.setBuffer(common.GPUTiles, gpuTileBuffer, sizeof(gpuTile), RenderBufferStructuredView(sizeof(gpuTile)));
            textures.setTexture(1, skyTexture.get(), RenderTextureLayout::SHADER_READ, skyTextureView.get());
            clearDestination = RenderColor(0, 0, 0, 0);
            require(scene.prepare(device.get(), positions.get(), faces.get(), 14, 27, {{6, 3, 1}}),
                "Could not restore original acceleration structure after shadow tests");
            common.setAccelerationStructure(common.SceneBVH, scene.accelerationStructure());
            common.setBuffer(common.wr64FenceProxy,scene.proxyBuffer(),scene.proxyBufferSize());
            common.setBuffer(common.interleavedRasters, scene.geometryBuffer(), scene.geometryBufferSize(), RenderBufferStructuredView(16));
            rebuildPositions();
            require(pipelines.prepare(device.get(), layout.get(), ms, false), "Could not restore stable PS after shadow tests");
            require(render(1, 0) == reflected && render(0, 0) == original,
                "Shadow fixtures failed to restore the original reflection/native baselines");
            std::printf("%ux MSAA shadow: blocked%zu lit%zu, translucent%zu maxerror%d, object%zu sky%zu; rejected surface/reflection controls%zu/%zu/%zu, currentAS/flags/direction/bias/invalid/Off guards passed.\n",
                samples, blockedPixels, litPixels, translucentChecks, shadowAlphaMaximum, objectShadowChecks, skyShadowChecks,
                waterOnlyControl, darkReflectionControl, darkSkyControl);

            // Native cutouts use actual combiner/discard semantics at each
            // candidate hit. A top-down camera maps this near card's reflected
            // UVs exactly onto an independent native-raster reference card.
            // Holes must reveal the farther red object rather than stop at a
            // transparent green texel. The same material also gates shadows.
            const auto cutoutStart = reflection;
            const auto cutoutParams = params[2];
            const auto cutoutRdp = rdp[2];
            float cutoutScreen[16][4], cutoutUV[16][2], cutoutColors[16][4];
            std::memcpy(cutoutScreen, screen, sizeof(screen));
            std::memcpy(cutoutUV, uv, sizeof(uv));
            std::memcpy(cutoutColors, colors, sizeof(colors));
            reflection.camera[0] = reflection.camera[2] = 0; reflection.camera[1] = 10;
            const uint32_t cardIds[4] = {7, 8, 9, 11};
            const float cardPositions[4][4] = {{-7.25f, 5, 7.25f, 1}, {7.25f, 5, 7.25f, 1},
                {7.25f, 5, -7.25f, 1}, {-7.25f, 5, -7.25f, 1}};
            const float farCard[3][4] = {{-100, 10, 100, 1}, {100, 10, 100, 1}, {0, 10, -100, 1}};
            std::memcpy(world[4], farCard, sizeof(farCard));
            for (uint32_t v = 0; v < 4; ++v) {
                std::memcpy(world[cardIds[v]], cardPositions[v], sizeof(cardPositions[v]));
                std::memcpy(screen[cardIds[v]], screen[v], sizeof(screen[v]));
                uv[cardIds[v]][0] = screen[v][0] * .5f;
                uv[cardIds[v]][1] = screen[v][1] * .5f;
                for (size_t c = 0; c < 4; ++c) colors[cardIds[v]][c] = 1;
            }
            fill(screenBuffer, screen, sizeof(screen)); fill(uvBuffer, uv, sizeof(uv)); fill(colorBuffer, colors, sizeof(colors));
            auto prepareCutoutScene = [&](bool includeCard, uint32_t flags) {
                std::vector<Wr64RTSceneGeometry> geometry = {{6, 3, 1, 0}};
                if (includeCard) geometry.push_back({9, 6, 2, flags});
                require(scene.prepare(device.get(), positions.get(), faces.get(), 14, 27, geometry),
                    "Could not prepare native-cutout candidate scene");
                common.setAccelerationStructure(common.SceneBVH, scene.accelerationStructure());
            common.setBuffer(common.wr64FenceProxy,scene.proxyBuffer(),scene.proxyBufferSize());
                common.setBuffer(common.interleavedRasters, scene.geometryBuffer(), scene.geometryBufferSize(), RenderBufferStructuredView(16));
                rebuildPositions();
            };
            Pixels cutoutBytes(32 * 256, 0);
            for (uint32_t y = 0; y < 32; ++y) for (uint32_t x = 0; x < 32; ++x) {
                const size_t p = y * 256 + x * 4;
                cutoutBytes[p] = cutoutBytes[p + 1] = cutoutBytes[p + 2] = 255;
                cutoutBytes[p + 3] = ((x / 4 + y / 4) % 2) ? 255 : 0;
            }
            auto cutoutTexture = device->createTexture(RenderTextureDesc::Texture2D(32, 32, 1, RenderFormat::R8G8B8A8_UNORM));
            auto cutoutView = cutoutTexture->createTextureView(RenderTextureViewDesc::Texture2D(RenderFormat::R8G8B8A8_UNORM));
            auto cutoutUpload = upload(cutoutBytes.data(), cutoutBytes.size(), 0);
            worker.commandList->begin();
            worker.commandList->barriers(RenderBarrierStage::COPY, RenderTextureBarrier(cutoutTexture.get(), RenderTextureLayout::COPY_DEST));
            worker.commandList->copyTextureRegion(RenderTextureCopyLocation::Subresource(cutoutTexture.get()),
                RenderTextureCopyLocation::PlacedFootprint(cutoutUpload, RenderFormat::R8G8B8A8_UNORM, 32, 32, 1, 64));
            worker.commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE, RenderTextureBarrier(cutoutTexture.get(), RenderTextureLayout::SHADER_READ));
            worker.commandList->end(); worker.execute(); worker.wait();
            textures.setTexture(0, cutoutTexture.get(), RenderTextureLayout::SHADER_READ, cutoutView.get());
            interop::RDPTile cutoutTile = rdpTile;
            cutoutTile.fmt = 0; cutoutTile.siz = 3; cutoutTile.stride = 128;
            cutoutTile.lrs = cutoutTile.lrt = 31 * 4;
            interop::GPUTile cutoutGpuTile = gpuTile;
            cutoutGpuTile.textureDimensions = hlslpp::float3(32, 32, 1);
            common.setBuffer(common.RDPTiles, upload(&cutoutTile, sizeof(cutoutTile), RenderBufferFlag::STORAGE),
                sizeof(cutoutTile), RenderBufferStructuredView(sizeof(cutoutTile)));
            common.setBuffer(common.GPUTiles, upload(&cutoutGpuTile, sizeof(cutoutGpuTile), RenderBufferFlag::STORAGE),
                sizeof(cutoutGpuTile), RenderBufferStructuredView(sizeof(cutoutGpuTile)));
            auto setCutoutAlphaCycle = [&](bool second, uint32_t a, uint32_t b, uint32_t c, uint32_t d) {
                if (second) {
                    const uint32_t mask = (7u << 21) | (7u << 18) | (7u << 3) | 7u;
                    params[2].ccH = (params[2].ccH & ~mask) | (a << 21) | (c << 18) | (b << 3) | d;
                }
                else {
                    params[2].ccL = (params[2].ccL & ~((7u << 12) | (7u << 9))) | (a << 12) | (c << 9);
                    params[2].ccH = (params[2].ccH & ~((7u << 12) | (7u << 9))) | (b << 12) | (d << 9);
                }
            };
            auto configureCutout = [&](uint32_t mode) {
                params[2] = primitiveSkyParams;
                params[2].flags.usesTexture0 = 1;
                params[2].flags.nativeSampler0 = NATIVE_SAMPLER_CLAMP_CLAMP;
                params[2].flags.cms0 = params[2].flags.cmt0 = 2;
                params[2].flags.linearFiltering = 0;
                params[2].omL = Z_UPD | Z_CMP | G_AC_THRESHOLD;
                params[2].omH = G_TP_PERSP | G_TF_POINT;
                rdp[2].primColor = hlslpp::float4(.05f, .9f, .1f, 1);
                rdp[2].envColor = hlslpp::float4(1, 1, 1, 1);
                rdp[2].blendColor = hlslpp::float4(0, 0, 0, .5f);
                for (uint32_t v = 0; v < 4; ++v) colors[cardIds[v]][3] = 1;
                setCutoutAlphaCycle(true, 7, 7, 7, 1); // TEXEL0_ALPHA.
                if (mode == 1 || mode == 2) {
                    params[2].omL = Z_UPD | Z_CMP | CVG_X_ALPHA;
                    params[2].omH = G_TP_PERSP | G_TF_BILERP;
                }
                if (mode == 2) {
                    setCutoutAlphaCycle(true, 1, 7, 4, 7); // TEXEL0_ALPHA * SHADE_ALPHA.
                    params[2].flags.smoothShade = 0; // Alpha must still interpolate.
                    colors[7][3] = colors[11][3] = 0;
                }
                if (mode >= 3 && mode <= 6) {
                    params[2].omH = G_TP_PERSP | G_CYC_2CYCLE;
                    setCutoutAlphaCycle(false, 7, 7, 7, 3); // First-cycle primitive alpha.
                    setCutoutAlphaCycle(true, 7, 7, 7, 5); // Second-cycle environment alpha.
                    rdp[2].primColor = hlslpp::float4(.05f, .9f, .1f, mode == 3 || mode == 6 ? .25f : .75f);
                    rdp[2].envColor = hlslpp::float4(1, 1, 1, mode == 4 || mode == 5 ? 0.f : 1.f);
                    if (mode == 5) params[2].omL |= CVG_X_ALPHA;
                    if (mode == 6) params[2].omL = Z_UPD | Z_CMP | CVG_X_ALPHA;
                }
                if (mode >= 7) {
                    setCutoutAlphaCycle(true, 7, 7, 7, 3);
                    const float alpha = mode == 7 ? .5f : mode == 8 ? .499f : mode == 9 ? .501f :
                        mode == 10 ? .125f : mode == 11 ? .124f : 0;
                    rdp[2].primColor = hlslpp::float4(.05f, .9f, .1f, alpha);
                    if (mode >= 10) params[2].omL = Z_UPD | Z_CMP | (mode == 12 ? 0 : CVG_X_ALPHA);
                }
                if (mode == 13) {
                    // Archived Sunny Beach START rope/poles material. Its
                    // decoded test texture stays synthetic; use a visible fog
                    // color so raster acceptance remains observable at any
                    // shade-alpha fog weight without confusing black with discard.
                    params[2].ccL = 0xFC127FFF; params[2].ccH = 0xFFFFF238;
                    params[2].omL = 0xC8113078; params[2].omH = 0x00182CFF;
                    rdp[2].fogColor = hlslpp::float4(.05f, .9f, .1f, 1);
                }
                fill(renderParamsBuffer, params, sizeof(params)); fill(rdpParamsBuffer, rdp, sizeof(rdp));
                fill(colorBuffer, colors, sizeof(colors));
            };
            auto nativeCutoutMask = [&](bool shadowProjection, double offsetX=0, double offsetZ=0) {
                if (shadowProjection) {
                    for (uint32_t v : cardIds) {
                        screen[v][0] = float((world[v][0] + 5-offsetX) * 6.4);
                        screen[v][1] = float((5 - world[v][2]+offsetZ) * 6.4);
                    }
                    fill(screenBuffer, screen, sizeof(screen));
                }
                const auto result = render(0, 0, 2, 9, 6);
                if (shadowProjection) {
                    for (uint32_t v = 0; v < 4; ++v) std::memcpy(screen[cardIds[v]], screen[v], sizeof(screen[v]));
                    fill(screenBuffer, screen, sizeof(screen));
                }
                return result;
            };
            configureCutout(0);
            prepareCutoutScene(false, 0);
            const auto farOpaque = render(1, 0);
            prepareCutoutScene(true, 0);
            const auto solidNear = render(1, 0);
            require(solidNear != farOpaque, "Cutout fixture did not distinguish the near and far reflection materials");
            prepareCutoutScene(true, 3);
            reflection.shadowLight[0] = reflection.shadowLight[2] = 0;
            reflection.shadowLight[1] = 1; reflection.shadowLight[3] = .55f;
            reflection.shadowOptions[1] = .5f; reflection.shadowOptions[2] = 30000;
            size_t reflectedCutoutChecks = 0, shadowCutoutChecks = 0;
            Pixels texturedCardMask;
            for (uint32_t mode = 0; mode < 14; ++mode) {
                configureCutout(mode);
                reflection.shadowOptions[0] = 0;
                Pixels materialNear = solidNear;
                if (mode == 13) {
                    prepareCutoutScene(true, 0);
                    materialNear = render(1, 0);
                    prepareCutoutScene(true, 3);
                }
                const auto nativeMask = nativeCutoutMask(false);
                const auto cutoutReflection = render(1, 0);
                size_t admitted = 0, holes = 0, disagreements = 0;
                for (uint32_t y = 2; y < 62; ++y) for (uint32_t x = 2; x < 62; ++x) {
                    const size_t p = (y * Width + x) * 4;
                    const bool covered = nativeMask[p + 1] > 100;
                    admitted += covered; holes += !covered;
                    const auto &expected = covered ? materialNear : farOpaque;
                    for (size_t c = 0; c < 4; ++c) disagreements += cutoutReflection[p + c] != expected[p + c];
                    ++reflectedCutoutChecks;
                }
                std::printf("%ux MSAA native-cutout mode%u: admitted%zu holes%zu reflection mismatch%zu.\n",
                    samples, mode, admitted, holes, disagreements);
                require(disagreements == 0,
                    "Candidate alpha acceptance disagrees with native raster first-cycle threshold/final coverage semantics");
                if (mode == 0) {
                    require(admitted > 1000 && holes > 1000, "Textured cutout card did not exercise both near hits and revealed far geometry");
                    texturedCardMask = nativeMask;
                }
                if (mode == 3 || mode == 5 || mode == 8 || mode == 11)
                    require(admitted == 0, "Native constant-alpha rejection reference unexpectedly admitted its card");
                if (mode == 4 || mode == 6 || mode == 7 || mode == 9 || mode == 10 || mode == 12)
                    require(holes == 0, "Native constant-alpha equality/coverage reference unexpectedly rejected its card");
                std::array<Pixels,8> nativeShadowTaps,nativeShadowTapsMin,nativeShadowTapsMax;
                for(uint32_t pair=0;pair<4;++pair)for(uint32_t antipode=0;antipode<2;++antipode) {
                    const double radius=6*std::sqrt((pair+.5)/4),angle=pair*3.14159265358979323846*(3-std::sqrt(5.0));
                    const double sign=antipode?-1.0:1.0;
                    const uint32_t tap=pair*2+antipode;
                    const double dx=sign*radius*std::cos(angle),dz=-sign*radius*std::sin(angle);
                    nativeShadowTaps[tap]=nativeCutoutMask(true,dx,dz);
                    nativeShadowTapsMin[tap]=nativeShadowTapsMax[tap]=nativeShadowTaps[tap];
                    // D3D12 native raster positions have eight fractional bits.
                    // Independently bound that grid's one-subpixel uncertainty
                    // around each shifted reference, not around shader readback.
                    // Stable taps must match exactly; only a varying native
                    // acceptance can contribute one tap of coverage uncertainty.
                    constexpr double rasterSubpixel=1.0/(256.0*6.4);
                    for(double jx:{-rasterSubpixel,rasterSubpixel})for(double jz:{-rasterSubpixel,rasterSubpixel}) {
                        const auto adjacent=nativeCutoutMask(true,dx+jx,dz+jz);
                        for(size_t p=0;p<adjacent.size();p+=4) {
                            nativeShadowTapsMin[tap][p+1]=std::min(nativeShadowTapsMin[tap][p+1],adjacent[p+1]);
                            nativeShadowTapsMax[tap][p+1]=std::max(nativeShadowTapsMax[tap][p+1],adjacent[p+1]);
                        }
                    }
                }
                reflection.shadowOptions[0] = 1;
                const auto alphaShadowMask = render(1, 5);
                bool matchedShadow = true;size_t cutoutTapMismatches=0,cutoutBoundaryPixels=0;int cutoutTapMaxError=0;
                for (uint32_t y = 2; y < 62; ++y) for (uint32_t x = 2; x < 62; ++x) {
                    const size_t p = (y * Width + x) * 4;
                                        double expectedCoverage=0,minimumCoverage=0,maximumCoverage=0;
                    for(uint32_t tap=0;tap<8;++tap) {
                        expectedCoverage+=nativeShadowTaps[tap][p+1]>100;
                        minimumCoverage+=nativeShadowTapsMin[tap][p+1]>100;
                        maximumCoverage+=nativeShadowTapsMax[tap][p+1]>100;
                    }
                    cutoutBoundaryPixels+=minimumCoverage!=maximumCoverage;
                    const int err=int(std::ceil(std::abs(alphaShadowMask[p]-255*(1-expectedCoverage/8))));
                    matchedShadow &= alphaShadowMask[p]>=255*(1-maximumCoverage/8)-1&&alphaShadowMask[p]<=255*(1-minimumCoverage/8)+1;
                    cutoutTapMismatches+=err>1;cutoutTapMaxError=std::max(cutoutTapMaxError,err);
                    ++shadowCutoutChecks;
                }
                std::printf("%ux native-cutout water mode%u: raw offset differences%zu bounded-subpixel-pixels%zu max-error%d.\n",samples,mode,cutoutTapMismatches,cutoutBoundaryPixels,cutoutTapMaxError);
                require(matchedShadow&&cutoutBoundaryPixels<100, "Alpha-aware shadow rays disagreed with independently bounded native cutout acceptance");
            }
            reflection.shadowOptions[0] = 0;
            configureCutout(0);
            params[2].omL = (params[2].omL & ~3u) | G_AC_DITHER;
            fill(renderParamsBuffer, params, sizeof(params));
            require(render(1, 0) == farOpaque, "Unsupported stochastic alpha-compare material terminated a reflection candidate");
            configureCutout(0);
            prepareCutoutScene(true, 1);
            require(render(1, 0) == solidNear, "Opaque geometry was unexpectedly filtered using cutout alpha");
            prepareCutoutScene(true, 2);
            reflection.shadowOptions[0] = 1;
            const auto noCasterMask = render(1, 5);
            size_t noCasterWhite = 0;
            for (size_t p = 0; p < Width * Height; ++p) noCasterWhite += noCasterMask[p * 4] == 255;
            require(noCasterWhite == Width * Height, "Alpha-aware reflection-only geometry cast a shadow without its caster flag");
            reflection.shadowOptions[0] = 0;

            // With no farther object, rejected texels must continue to the
            // existing sky/celestial miss path rather than turn into black.
            for (uint32_t v = 4; v < 7; ++v) world[v][0] += 1000;
            reflection.celestialProjection[0][0] = 64; reflection.celestialProjection[0][1] = 32;
            reflection.celestialProjection[1][1] = 96; reflection.celestialProjection[1][2] = -64;
            reflection.celestialProjection[2][1] = 1;
            reflection.celestialInfo[0] = 1;
            for (size_t i = 2048; i < 2064; ++i) packCelestialAlpha(i, 255);
            reflection.celestial[0] = celestialRecord(-100000, -100000, 100000, 100000, .9f, .8f, .05f, 1, 2048, 4);
            require(pipelines.prepare(device.get(), layout.get(), ms, false, true), "Could not select sky-through-cutout test");
            prepareCutoutScene(false, 0);
            const auto skyThrough = render(1, 0);
            prepareCutoutScene(true, 2);
            const auto mixedSkyCutout = render(1, 0);
            bool skyHolesCorrect = true;
            size_t skyHolePixels = 0;
            for (uint32_t y = 2; y < 62; ++y) for (uint32_t x = 2; x < 62; ++x) {
                const size_t p = (y * Width + x) * 4;
                const bool covered = texturedCardMask[p + 1] > 100;
                const auto &expected = covered ? solidNear : skyThrough;
                for (size_t c = 0; c < 4; ++c) skyHolesCorrect &= mixedSkyCutout[p + c] == expected[p + c];
                skyHolePixels += !covered;
            }
            require(skyHolesCorrect && skyHolePixels > 1000,
                "Rejected native cutout candidates failed to reveal the existing sky/celestial reflection");
            require(render(0, 0) == original, "Native RT-Off water changed after enabling alpha-aware candidate geometry");

            std::memcpy(world, savedWorld, sizeof(world)); std::memcpy(screen, cutoutScreen, sizeof(screen));
            std::memcpy(uv, cutoutUV, sizeof(uv)); std::memcpy(colors, cutoutColors, sizeof(colors));
            fill(screenBuffer, screen, sizeof(screen)); fill(uvBuffer, uv, sizeof(uv)); fill(colorBuffer, colors, sizeof(colors));
            reflection = cutoutStart; params[2] = cutoutParams; rdp[2] = cutoutRdp;
            fill(renderParamsBuffer, params, sizeof(params)); fill(rdpParamsBuffer, rdp, sizeof(rdp));
            common.setBuffer(common.RDPTiles, rdpTileBuffer, sizeof(rdpTile), RenderBufferStructuredView(sizeof(rdpTile)));
            common.setBuffer(common.GPUTiles, gpuTileBuffer, sizeof(gpuTile), RenderBufferStructuredView(sizeof(gpuTile)));
            textures.setTexture(0, skyTexture.get(), RenderTextureLayout::SHADER_READ, skyTextureView.get());
            require(scene.prepare(device.get(), positions.get(), faces.get(), 14, 27, {{6, 3, 1}}),
                "Could not restore acceleration structure after cutout tests");
            common.setAccelerationStructure(common.SceneBVH, scene.accelerationStructure());
            common.setBuffer(common.wr64FenceProxy,scene.proxyBuffer(),scene.proxyBufferSize());
            common.setBuffer(common.interleavedRasters, scene.geometryBuffer(), scene.geometryBufferSize(), RenderBufferStructuredView(16));
            rebuildPositions();
            require(pipelines.prepare(device.get(), layout.get(), ms, false), "Could not restore stable PS after cutout tests");
            require(render(1, 0) == reflected && render(0, 0) == original,
                "Native cutout suite failed to restore prior opaque reflection/native baselines");
            std::printf("%ux MSAA native cutouts: reflection%zu shadow%zu native-raster comparisons; sky holes%zu; opaque flags, stochastic exclusion and restored baselines passed.\n",
                samples, reflectedCutoutChecks, shadowCutoutChecks, skyHolePixels);

            // Native Twilight light prism: actual eight-vertex source shape and
            // F3DWAVE quad topology, with synthetic IA16 alpha pixels. Native
            // RasterPS is an independent three-point/blender/culling reference.
            const auto beamStart = reflection;
            const auto beamParams1 = params[1], beamParams2 = params[2], beamParams3 = params[3];
            const auto beamRdp1 = rdp[1], beamRdp2 = rdp[2], beamRdp3 = rdp[3];
            const auto beamIndices2 = renderIndices[2], beamIndices3 = renderIndices[3];
            FixtureWorldPipelines iterationWorldPipelines(shaderFormat);
            auto &worldPipelines = lifecycle ? *lifecycleWorld : iterationWorldPipelines;
            require(worldPipelines.prepare(device.get(), layout.get(), ms, false), "World receiver PSO preparation failed");
            const float nativePrism[8][5] = {
                {0,500,120,4096,0},{0,-150,50,4096,1024},{50,-150,0,2560,1024},{120,500,0,0,0},
                {-120,500,0,8192,0},{-50,-150,0,5632,1024},{0,-150,-50,4096,1024},{0,500,-120,4096,0}
            };
            constexpr uint32_t prismFaces[24] = {3,0,1,3,1,2,0,4,5,0,5,1,7,3,2,7,2,6,4,7,6,4,6,5};
            reflection = Params{}; reflection.camera[0] = reflection.camera[2] = 0;
            reflection.camera[1] = 10; reflection.sky[3] = 0; reflection.sceneOptions[0] = 1;
            // A narrower synthetic water frustum gives the native prism enough
            // pixels to compare interiors independently of 4x MSAA boundaries.
            for(uint32_t v=0;v<4;++v) { world[v][0]*=.8f; world[v][2]*=.8f; }
            reflection.celestialInfo[0] = 1; reflection.celestialProjection[2][1] = 1;
            reflection.celestial[0].bounds[0] = reflection.celestial[0].bounds[1] = -1;
            reflection.celestial[0].bounds[2] = reflection.celestial[0].bounds[3] = 1;
            reflection.celestial[0].meta[1] = reflection.celestial[0].meta[2] = 4;
            reflection.celestial[0].color[0] = .05f; reflection.celestial[0].color[1] = .2f;
            reflection.celestial[0].color[2] = .7f; reflection.celestial[0].color[3] = 1;
            for (uint32_t i = 0; i < 4; ++i) reflection.celestialAlpha[0][i] = 0xffffffff;
            for (uint32_t i = 0; i < 8; ++i) {
                const uint32_t v = 7 + i;
                world[v][0] = nativePrism[i][0] * .03f + 3;
                world[v][1] = nativePrism[i][1] * .03f + 6;
                world[v][2] = nativePrism[i][2] * .03f;
                world[v][3] = 1;
                const float w = (world[v][1] + 9.5f) / 10;
                screen[v][0] = (world[v][0] / w + 4) * 8;
                screen[v][1] = (4 - world[v][2] / w) * 8;
                screen[v][2] = .5f; screen[v][3] = w;
                uv[v][0] = nativePrism[i][3] / 32;
                uv[v][1] = nativePrism[i][4] / 32;
                colors[v][0] = 1; colors[v][1] = 132.f/255; colors[v][2] = 121.f/255; colors[v][3] = 1;
            }
            for (uint32_t i = 0; i < 24; ++i) indices[9+i] = 7 + prismFaces[i];
            params[2] = textureSkyParams; params[2].ccL = 0xfc127e24; params[2].ccH = 0xfffff3f9;
            params[2].omL = 0x005049d8; params[2].omH = 0x00082cff;
            params[2].flags.smoothShade = 1;
            params[2].flags.nativeSampler0 = NATIVE_SAMPLER_WRAP_CLAMP;
            params[2].flags.cms0 = 0; params[2].flags.cmt0 = 2;
            params[2].flags.linearFiltering = 0;
            renderIndices[2].rdpTileCount = 1; renderIndices[2].faceIndicesStart = 9;
            rdp[2].primColor = hlslpp::float4(0,0,0,0); // Native primitive alpha must not erase the beam.
            Pixels beamBytes(32*256, 0);
            for (uint32_t y = 0; y < 32; ++y) for (uint32_t x = 0; x < 16; ++x) {
                const size_t p = y*256+x*4;
                beamBytes[p] = beamBytes[p+1] = beamBytes[p+2] = 255;
                beamBytes[p+3] = uint8_t((195*y/31) * (x%3 == 0 ? .8f : 1));
            }
            auto beamTexture = device->createTexture(RenderTextureDesc::Texture2D(16,32,1,RenderFormat::R8G8B8A8_UNORM));
            auto beamView = beamTexture->createTextureView(RenderTextureViewDesc::Texture2D(RenderFormat::R8G8B8A8_UNORM));
            auto beamUpload = upload(beamBytes.data(),beamBytes.size(),0);
            auto uploadBeam = [&]() {
                fill(beamUpload,beamBytes.data(),beamBytes.size());
                worker.commandList->begin();
                worker.commandList->barriers(RenderBarrierStage::COPY,RenderTextureBarrier(beamTexture.get(),RenderTextureLayout::COPY_DEST));
                worker.commandList->copyTextureRegion(RenderTextureCopyLocation::Subresource(beamTexture.get()),
                    RenderTextureCopyLocation::PlacedFootprint(beamUpload,RenderFormat::R8G8B8A8_UNORM,16,32,1,64));
                worker.commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE,RenderTextureBarrier(beamTexture.get(),RenderTextureLayout::SHADER_READ));
                worker.commandList->end(); worker.execute(); worker.wait();
            };
            uploadBeam(); textures.setTexture(0,beamTexture.get(),RenderTextureLayout::SHADER_READ,beamView.get());
            interop::RDPTile beamTile = rdpTile;
            beamTile.fmt = 3; beamTile.siz = 2; beamTile.stride = 32;
            beamTile.lrs = 15*4; beamTile.lrt = 31*4;
            // RDPTile stores decoded multipliers: native shift bits0 mean1.
            beamTile.shifts = beamTile.shiftt = 1;
            beamTile.cms = 0; beamTile.cmt = 2; beamTile.masks = 16; beamTile.maskt = 32;
            beamTile.nativeSampler = NATIVE_SAMPLER_WRAP_CLAMP;
            interop::GPUTile beamGpuTile = gpuTile; beamGpuTile.textureDimensions = hlslpp::float3(16,32,1);
            common.setBuffer(common.RDPTiles,upload(&beamTile,sizeof(beamTile),RenderBufferFlag::STORAGE),sizeof(beamTile),RenderBufferStructuredView(sizeof(beamTile)));
            common.setBuffer(common.GPUTiles,upload(&beamGpuTile,sizeof(beamGpuTile),RenderBufferFlag::STORAGE),sizeof(beamGpuTile),RenderBufferStructuredView(sizeof(beamGpuTile)));
            fill(renderParamsBuffer,params,sizeof(params)); fill(renderIndicesBuffer,renderIndices,sizeof(renderIndices));
            fill(rdpParamsBuffer,rdp,sizeof(rdp)); fill(screenBuffer,screen,sizeof(screen)); fill(uvBuffer,uv,sizeof(uv)); fill(colorBuffer,colors,sizeof(colors));
            auto prepareBeamScene = [&](std::vector<Wr64RTSceneGeometry> geometry) {
                require(scene.prepare(device.get(),positions.get(),faces.get(),16,54,geometry),"Beam/receiver AS preparation failed");
                common.setAccelerationStructure(common.SceneBVH,scene.accelerationStructure());
            common.setBuffer(common.wr64FenceProxy,scene.proxyBuffer(),scene.proxyBufferSize());
                common.setBuffer(common.interleavedRasters,scene.geometryBuffer(),scene.geometryBufferSize(),RenderBufferStructuredView(16));
                refreshFixtureIndices();
            };
            prepareBeamScene({{9,24,2,4}});
            require(pipelines.prepare(device.get(),layout.get(),ms,false,true),"Beam sky PSO creation failed");
            reflection.sceneOptions[0] = 0;
            const auto skyWithoutBeam = render(1,4);
            const auto nativeBeforeBeam = render(0,0);
            reflection.sceneOptions[0] = 1;
            const auto prismSky = render(1,4);
            clearDestination = RenderColor(.05f,.2f,.7f,0);
            pipelineOverride = worldPipelines.get(false,false,false,true,true,true);
            require(pipelineOverride != nullptr,"Native one-sided prism reference PSO failed");
            const auto nativePrismSky = render(0,0,2,9,24);
            pipelineOverride = nullptr; clearDestination = RenderColor(0,0,0,0);
            size_t prismCompared = 0, prismVisible = 0, prismBad = 0; int prismMaximum = 0;
            for (uint32_t y=2;y<62;++y) for (uint32_t x=2;x<62;++x) {
                const size_t p=(y*Width+x)*4;
                bool stableNeighborhood = nativePrismSky[p+3]==0 || nativePrismSky[p+3]==8;
                // Raster MSAA evaluates silhouette/shared-edge coverage from
                // subpixel samples; the reflected ray is pixel-frequency.
                // Compare interiors beyond the sample footprint, retaining
                // exact UV/color checks rather than increasing tolerances.
                for(uint32_t f=0;f<24;f+=3) for(uint32_t e=0;e<3;++e) {
                    const float* t0=screen[7+prismFaces[f]];
                    const float* t1=screen[7+prismFaces[f+1]];
                    const float* t2=screen[7+prismFaces[f+2]];
                    // This is the native one-sided raster reference; culled
                    // back-face edges do not bound any rasterized fragment.
                    if((t1[0]-t0[0])*(t2[1]-t0[1])-(t1[1]-t0[1])*(t2[0]-t0[0])>=0) continue;
                    const float* a=screen[7+prismFaces[f+e]];
                    const float* b=screen[7+prismFaces[f+(e+1)%3]];
                    const float dx=b[0]-a[0],dy=b[1]-a[1],d2=dx*dx+dy*dy;
                    if(d2<=1e-8f) continue;
                    const float t=std::max(0.f,std::min(1.f,((x+.5f-a[0])*dx+(y+.5f-a[1])*dy)/d2));
                    const float px=x+.5f-a[0]-t*dx,py=y+.5f-a[1]-t*dy;
                    stableNeighborhood &= px*px+py*py>1.0f;
                }
                if (!stableNeighborhood) continue;
                ++prismCompared; prismVisible += prismSky[p] > skyWithoutBeam[p]+5;
                if(prismSky[p]>skyWithoutBeam[p]+5 && prismVisible<4)
                    std::printf("beam sample%u,%u native(%u,%u,%u,%u) ray(%u,%u,%u,%u)\n",x,y,nativePrismSky[p],nativePrismSky[p+1],nativePrismSky[p+2],nativePrismSky[p+3],prismSky[p],prismSky[p+1],prismSky[p+2],prismSky[p+3]);
                for(size_t c=0;c<3;++c) {
                    const int e=std::abs(int(prismSky[p+c])-int(nativePrismSky[p+c]));
                    prismMaximum=std::max(prismMaximum,e); prismBad += e>2;
                }
            }
            writePPM(prefix+"beam-native.ppm",nativePrismSky); writePPM(prefix+"beam-reflected.ppm",prismSky);
            std::printf("%ux MSAA native beam prism: compared%zu visible%zu mismatch%zu max%d.\n",samples,prismCompared,prismVisible,prismBad,prismMaximum);
            require(prismCompared>2000 && prismVisible>60 && prismBad==0,"Reflected native prism disagrees with native one-sided alpha/material rasterization");
            require(render(0,0)==nativeBeforeBeam,"Beams altered native RT-Off pixels");
            if (qualityOptions) {
                float qualityPrism[8][4];std::memcpy(qualityPrism,world+7,sizeof(qualityPrism));
                const auto qualityBeamParams=reflection;
                // Dilate about the virtual reflected camera. The native
                // prism's direction stays fixed while all geometry moves
                // farther than 7500 units (minimum world Y is now 10990.5).
                for(uint32_t v=7;v<15;++v) {
                    world[v][0]*=1000;world[v][2]*=1000;
                    world[v][1]=-9.5f+(world[v][1]+9.5f)*1000;
                }
                rebuildPositions();reflection.strength=20;
                for(bool skyVariant:{false,true}) {
                    require(pipelines.prepare(device.get(),layout.get(),ms,false,skyVariant),"Quality beam range PSO failed");
                    reflection.qualityOptions[0]=30000;reflection.sceneOptions[0]=0;
                    const auto beamBackground=render(1,0);
                    reflection.sceneOptions[0]=1;const auto distantBeam=render(1,0);
                    size_t visible=0;bool alphaPreserved=true;
                    for(size_t p=0;p<distantBeam.size();p+=4) {
                        visible+=std::abs(int(distantBeam[p])-int(beamBackground[p]))>2;
                        alphaPreserved &= distantBeam[p+3]==beamBackground[p+3];
                    }
                    require(visible>50&&alphaPreserved,"Far beam quality fixture is inactive or changes native coverage");
                    reflection.qualityOptions[0]=7500;
                    require(render(1,0)==beamBackground,"Physical beam escaped the reduced reflection range, or directional sky was clipped");
                    reflection.sceneOptions[0]=0;
                    require(render(1,0)==beamBackground,"Reflection range changed the native celestial background");
                    std::printf("%ux RT quality beam %s: far-visible%zu near-range exact background.\n",samples,skyVariant?"sky":"stable",visible);
                }
                std::memcpy(world+7,qualityPrism,sizeof(qualityPrism));rebuildPositions();reflection=qualityBeamParams;
                require(render(1,4)==prismSky,"Beam range fixture left altered geometry or settings");
            }
            // Alpha0 must preserve exact sky and stable-water branches, not
            // attenuate unknown background or turn the prism into a solid hit.
            for(uint32_t y=0;y<32;++y) for(uint32_t x=0;x<16;++x) beamBytes[y*256+x*4+3]=0;
            uploadBeam(); require(render(1,4)==skyWithoutBeam,"Zero-alpha beam altered sky output");
            require(pipelines.prepare(device.get(),layout.get(),ms,false),"Stable beam PSO failed");
            reflection.sceneOptions[0]=0; const auto stableNoBeam=render(1,0);
            reflection.sceneOptions[0]=1; require(render(1,0)==stableNoBeam,"Zero-alpha beam altered stable water");
            // Constant alpha makes independent coincident red/yellow ordering
            // exact, and reveals accidental entry+exit or shared-edge blending.
            for(uint32_t y=0;y<32;++y) for(uint32_t x=0;x<16;++x) beamBytes[y*256+x*4+3]=128;
            uploadBeam();
            params[3]=primitiveSkyParams; params[3].omL=0x005049d8; params[3].omH=0x00082cff;
            rdp[3].primColor=hlslpp::float4(227.f/255,245.f/255,108.f/255,128.f/255);
            fill(renderParamsBuffer,params,sizeof(params)); fill(rdpParamsBuffer,rdp,sizeof(rdp));
            require(pipelines.prepare(device.get(),layout.get(),ms,false,true),"Layered beam sky PSO failed");
            prepareBeamScene({{9,24,2,4}}); reflection.sceneOptions[0]=1; const auto redPrism=render(1,4);
            prepareBeamScene({{9,24,3,4}}); const auto yellowPrism=render(1,4);
            prepareBeamScene({{9,24,2,4},{9,24,3,4}}); reflection.sceneOptions[0]=2;
            const auto layeredPrism=render(1,4); size_t orderedPixels=0; bool beamOrdered=true; float beamOrderMax=0;
            for(size_t p=0;p<layeredPrism.size();p+=4) {
                if(redPrism[p] <= skyWithoutBeam[p]+15 || yellowPrism[p] <= skyWithoutBeam[p]+15) continue;
                ++orderedPixels;
                for(size_t c=0;c<3;++c) {
                    const float expected=yellowPrism[p+c]+(1-128.f/255)*(redPrism[p+c]-skyWithoutBeam[p+c]);
                    beamOrderMax=std::max(beamOrderMax,std::abs(layeredPrism[p+c]-expected));
                    beamOrdered &= std::abs(layeredPrism[p+c]-expected)<=2;
                }
            }
            std::printf("%ux MSAA coincident beams: visible%zu maximum error%.3f.\n",samples,orderedPixels,beamOrderMax);
            require(orderedPixels>60 && beamOrdered,"Coincident independent beam alpha/order is wrong");
            prepareBeamScene({{9,24,3,4},{9,24,2,4}});
            require(render(1,4)==layeredPrism,"Beam ordering follows AS insertion instead of native draw order");
            reflection.shadowOptions[0]=1; reflection.shadowOptions[1]=.1f; reflection.shadowOptions[2]=100;
            reflection.shadowLight[1]=1; reflection.shadowLight[3]=.55f;
            const auto noncastingBeams=render(1,5);
            size_t beamShadowWhite=0; for(size_t p=0;p<noncastingBeams.size();p+=4) beamShadowWhite+=noncastingBeams[p]==255;
            require(beamShadowWhite==Width*Height,"Translucent light prism cast a shadow");
            reflection.shadowOptions[0]=0;

            // Move the prism above a near blocker. The far blocker must
            // remain visible through beam alpha; the near blocker must stop
            // all beam layers, in both the stable and sky shader variants.
            for(uint32_t v=7;v<15;++v) world[v][1]+=4;
            std::memcpy(world[4],farCard,sizeof(farCard));
            for(uint32_t v=4;v<7;++v) world[v][1]=30;
            params[1]=primitiveSkyParams; rdp[1].primColor=hlslpp::float4(.03f,.1f,.8f,1);
            fill(renderParamsBuffer,params,sizeof(params));fill(rdpParamsBuffer,rdp,sizeof(rdp));
            prepareBeamScene({{9,24,2,4}}); reflection.sceneOptions[0]=1;
            const auto raisedPrism=render(1,4);
            reflection.strength=20; // Saturated Fresnel isolates reflected RGB.
            size_t behindBeamChecks=0, behindBeamVisible=0;
            for(bool skyVariant:{false,true}) {
                require(pipelines.prepare(device.get(),layout.get(),ms,false,skyVariant),"Beam solid-occlusion PSO failed");
                prepareBeamScene({{6,3,1,0},{9,24,2,4}});
                const auto overFarSolid=render(1,0); reflection.sceneOptions[0]=0;
                const auto farSolid=render(1,0); reflection.sceneOptions[0]=1;
                bool correct=true;
                for(uint32_t y=2;y<62;++y) for(uint32_t x=2;x<62;++x) {
                    const size_t p=(y*Width+x)*4;
                    if(raisedPrism[p]<=skyWithoutBeam[p]+15) continue;
                    ++behindBeamVisible;
                    for(size_t c=0;c<3;++c) {
                        const float expected=raisedPrism[p+c]+(1-128.f/255)*(farSolid[p+c]-skyWithoutBeam[p+c]);
                        correct &= std::abs(overFarSolid[p+c]-expected)<=2;
                        ++behindBeamChecks;
                    }
                }
                require(correct && behindBeamVisible>60,"Beam does not source-over the farther opaque reflection");
                for(uint32_t v=4;v<7;++v) world[v][1]=2;
                rebuildPositions();
                const auto blockedBeam=render(1,0); reflection.sceneOptions[0]=0;
                require(render(1,0)==blockedBeam,"Foreground opaque reflection did not occlude light prism");
                reflection.sceneOptions[0]=1;
                for(uint32_t v=4;v<7;++v) world[v][1]=30;
                rebuildPositions();
            }
            reflection.strength=1;
            // Texture-alpha holes in that foreground plane reveal the prism
            // and sky; its opaque texels must still terminate reflection rays.
            for(uint32_t v=4;v<7;++v) {
                world[v][1]=2;
                const float w=(world[v][1]+9.5f)/10;
                screen[v][0]=(world[v][0]/w+4)*8;
                screen[v][1]=(4-world[v][2]/w)*8;
                screen[v][2]=.5f;screen[v][3]=w;
                uv[v][0]=screen[v][0]*.5f;uv[v][1]=screen[v][1]*.5f;
                colors[v][0]=colors[v][1]=colors[v][2]=colors[v][3]=1;
            }
            interop::RDPTile beamCutoutTiles[2]={beamTile,cutoutTile};
            interop::GPUTile beamCutoutGpuTiles[2]={beamGpuTile,cutoutGpuTile};
            beamCutoutGpuTiles[1].textureIndex=1;
            common.setBuffer(common.RDPTiles,upload(beamCutoutTiles,sizeof(beamCutoutTiles),RenderBufferFlag::STORAGE),sizeof(beamCutoutTiles),RenderBufferStructuredView(sizeof(beamTile)));
            common.setBuffer(common.GPUTiles,upload(beamCutoutGpuTiles,sizeof(beamCutoutGpuTiles),RenderBufferFlag::STORAGE),sizeof(beamCutoutGpuTiles),RenderBufferStructuredView(sizeof(beamGpuTile)));
            textures.setTexture(1,cutoutTexture.get(),RenderTextureLayout::SHADER_READ,cutoutView.get());
            params[3]=textureSkyParams;params[3].omH=G_TP_PERSP|G_TF_POINT;
            params[3].omL=G_AC_THRESHOLD;params[3].flags.linearFiltering=0;
            rdp[3].blendColor=hlslpp::float4(0,0,0,.5f);
            renderIndices[3].rdpTileIndex=1;renderIndices[3].rdpTileCount=1;
            fill(renderParamsBuffer,params,sizeof(params));fill(rdpParamsBuffer,rdp,sizeof(rdp));fill(renderIndicesBuffer,renderIndices,sizeof(renderIndices));
            fill(screenBuffer,screen,sizeof(screen));fill(uvBuffer,uv,sizeof(uv));fill(colorBuffer,colors,sizeof(colors));
            require(pipelines.prepare(device.get(),layout.get(),ms,false,true),"Cutout-beam sky PSO failed");
            prepareBeamScene({{6,3,3,2},{9,24,2,4}});
            pipelineOverride=worldPipelines.get(false,false,false,false,true,true);
            const auto beamHoleNative=render(0,0,3,6,3);pipelineOverride=nullptr;
            const auto beamHoleSky=render(1,4);
            size_t beamHoleChecks=0, exposedBeamPixels=0;bool holesCorrect=true;
            for(uint32_t y=2;y<62;++y) for(uint32_t x=2;x<62;++x) {
                const size_t p=(y*Width+x)*4;const bool covered=beamHoleNative[p]>127;
                for(size_t c=0;c<3;++c) holesCorrect &= std::abs(int(beamHoleSky[p+c])-(covered?0:int(raisedPrism[p+c])))<=1;
                exposedBeamPixels+=!covered&&raisedPrism[p]>skyWithoutBeam[p]+15;++beamHoleChecks;
            }
            require(holesCorrect&&exposedBeamPixels>20,"Foreground cutout holes failed to expose reflected light prism");
            std::printf("%ux MSAA beam solid/cutout: opaque-composition channels%zu, visible%zu, holechecks%zu exposedbeam%zu.\n",samples,behindBeamChecks,behindBeamVisible,beamHoleChecks,exposedBeamPixels);

            // Selected shore receiver uses its own native alpha/coverage.
            // The same native cutout caster must shade receiver RGB while
            // preserving destination transmission and coverage alpha exactly.
            std::memcpy(world,savedWorld,sizeof(world));
            for(uint32_t v=0;v<4;++v) world[v][1]=2;
            std::memcpy(world[4],farCard,sizeof(farCard));
            for(uint32_t v=4;v<7;++v) world[v][1]=7;
            std::memcpy(screen,savedScreen,sizeof(screen)); std::memcpy(uv,savedUV,sizeof(uv)); std::memcpy(colors,savedColors,sizeof(colors));
            std::memcpy(indices,savedIndices,sizeof(indices));
            fill(screenBuffer,screen,sizeof(screen));fill(uvBuffer,uv,sizeof(uv));fill(colorBuffer,colors,sizeof(colors));
            reflection=Params{}; reflection.sky[3]=0; reflection.shadowOptions[0]=1;
            reflection.shadowOptions[1]=.1f; reflection.shadowOptions[2]=100;
            reflection.shadowLight[1]=1;reflection.shadowLight[3]=.55f;
            prepareBeamScene({{6,3,1,1}});
            clearDestination=RenderColor(.1f,.2f,.4f,0);
            pipelineOverride=worldPipelines.get(false,false,false,false,true,true);
            size_t shorePixels=0, shoreBlocked=0; int shoreMaxError=0;
            // Standard native opaque and two-cycle fog blenders, including
            // fully fogged output and unsupported forced alpha-blend fallback.
            for(uint32_t shoreMode=0;shoreMode<5;++shoreMode) {
                params[0]=primitiveSkyParams;
                params[0].omL=shoreMode==4?0x005049d8:shoreMode==0?0:0xc8112078;
                params[0].omH=shoreMode>0&&shoreMode<4?0x00182cff:0x00082cff;
                const float fogAmount=shoreMode==2?.4f:shoreMode==3?1.f:0.f;
                rdp[0].primColor=hlslpp::float4(.6f,.3f,.1f,.5f);
                rdp[0].fogColor=hlslpp::float4(.12f,.35f,.8f,1);
                for(uint32_t v=0;v<4;++v) colors[v][3]=fogAmount;
                fill(renderParamsBuffer,params,sizeof(params));fill(rdpParamsBuffer,rdp,sizeof(rdp));
                fill(colorBuffer,colors,sizeof(colors));
                const auto nativeShore=render(0,0); const auto shadowedShore=render(1,0);
                if(shoreMode==0) {
                    FixtureWorldPipelines asyncWorld(shaderFormat);
                    const auto* savedPipeline=pipelineOverride;
                    const auto* asyncShore=awaitAsyncPipeline("world-shadow",[&]() {
                        if(!asyncWorld.prepare(device.get(),layout.get(),ms,false,true))throw std::runtime_error("Async shore configuration failed");
                        return asyncWorld.get(false,false,false,false,true,true);
                    });
                    pipelineOverride=asyncShore;
                    require(render(0,0)==nativeShore&&render(1,0)==shadowedShore,"Async world PSO changed native or shadowed readback");
                    const auto* otherState=awaitAsyncPipeline("world-other-state",[&]() {
                        return asyncWorld.get(true,false,false,true,true,true);
                    });
                    require(otherState&&asyncWorld.get(false,false,false,false,true,true)==asyncShore,"World fixed-state request invalidated a ready PSO");
                    asyncWorld.waitForPending();
                    pipelineOverride=savedPipeline;
                }
                reflection.shadowLight[3]=0;
                require(render(1,0)==nativeShore,"Zero-strength shore shadow failed exact native preservation");
                reflection.shadowLight[3]=.55f;
                if(shoreMode>=3) {
                    require(shadowedShore==nativeShore,"Fully fogged/unsupported shore material changed native output");
                    continue;
                }
                const auto shoreMask=render(1,5);
                bool shoreCorrect=true;
                for(uint32_t y=2;y<62;++y) for(uint32_t x=2;x<62;++x) {
                    const size_t p=(y*Width+x)*4; const float q=shoreMask[p]==0?.45f:1;
                    shoreBlocked+=shoreMask[p]==0;
                    const float fog[]={.12f,.35f,.8f};
                    for(size_t c=0;c<3;++c) {
                        const float expected=q*nativeShore[p+c]+255*(1-q)*fogAmount*fog[c];
                        const int error=int(std::ceil(std::abs(shadowedShore[p+c]-expected)));
                        shoreMaxError=std::max(shoreMaxError,error); shoreCorrect &= error<=2;
                    }
                    shoreCorrect &= shadowedShore[p+3]==nativeShore[p+3]; ++shorePixels;
                }
                require(shoreCorrect,"Shore shadow altered native fog, alpha or coverage");
                require(render(0,0)==nativeShore,"Disabled shore shadow changed native material");
            }
            require(shorePixels==10800 && shoreBlocked>9000,"Shore caster failed positive shadow coverage");
            std::printf("%ux MSAA shore receiver: compared%zu blocked%zu maxerror%d, native fog and alpha/coverage preserved.\n",
                samples,shorePixels,shoreBlocked,shoreMaxError);
            // A native textured fence casts through its actual alpha holes
            // onto a separate shore mesh. Include that receiving mesh in the
            // shared AS as well, so normal bias must avoid self-shadowing.
            for(uint32_t v=0;v<4;++v) {
                const uint32_t id=cardIds[v];
                std::memcpy(world[id],world[v],sizeof(world[id]));world[id][1]=7;
                std::memcpy(screen[id],screen[v],sizeof(screen[id]));
                uv[id][0]=screen[v][0]*.5f;uv[id][1]=screen[v][1]*.5f;
                colors[id][0]=colors[id][1]=colors[id][2]=colors[id][3]=1;
            }
            textures.setTexture(0,cutoutTexture.get(),RenderTextureLayout::SHADER_READ,cutoutView.get());
            common.setBuffer(common.RDPTiles,upload(&cutoutTile,sizeof(cutoutTile),RenderBufferFlag::STORAGE),sizeof(cutoutTile),RenderBufferStructuredView(sizeof(cutoutTile)));
            common.setBuffer(common.GPUTiles,upload(&cutoutGpuTile,sizeof(cutoutGpuTile),RenderBufferFlag::STORAGE),sizeof(cutoutGpuTile),RenderBufferStructuredView(sizeof(cutoutGpuTile)));
            configureCutout(13);
            params[0]=primitiveSkyParams;params[0].omL=0;params[0].omH=0x00082cff;
            rdp[0].primColor=hlslpp::float4(.6f,.3f,.1f,1);
            fill(renderParamsBuffer,params,sizeof(params));fill(rdpParamsBuffer,rdp,sizeof(rdp));
            fill(screenBuffer,screen,sizeof(screen));fill(uvBuffer,uv,sizeof(uv));fill(colorBuffer,colors,sizeof(colors));
            clearDestination=RenderColor(0,0,0,0);
            prepareBeamScene({{0,6,0,1},{9,6,2,3}});
            const auto nativeFence=render(0,0,2,9,6);
            const auto fenceShoreMask=render(1,5);const auto fenceShore=render(1,0);
            const auto plainShore=render(0,0);
            size_t fenceLit=0,fenceDark=0;bool fenceCorrect=true;
            for(uint32_t y=2;y<62;++y) for(uint32_t x=2;x<62;++x) {
                const size_t p=(y*Width+x)*4;const bool accepted=nativeFence[p+1]>127;
                fenceCorrect &= fenceShoreMask[p]==(accepted?0:255);
                accepted?++fenceDark:++fenceLit;
                for(size_t c=0;c<3;++c) fenceCorrect &= std::abs(fenceShore[p+c]-(accepted?.45f:1.f)*plainShore[p+c])<=2;
                fenceCorrect &= fenceShore[p+3]==plainShore[p+3];
            }
            require(fenceCorrect&&fenceDark>1000&&fenceLit>500,"Native fence holes or receiver self-bias failed shore shadow test");
            for(uint32_t v=4;v<7;++v) world[v][1]=9;
            prepareBeamScene({{0,6,0,1},{9,6,2,2},{6,3,1,1}});
            const auto casterBehindNoncaster=render(1,5);
            for(uint32_t y=2;y<62;++y) for(uint32_t x=2;x<62;++x)
                require(casterBehindNoncaster[(y*Width+x)*4]==0,"Reflection-only cutout stopped a shadow ray before a valid farther caster");
            std::printf("%ux MSAA shore native fence: blocked%zu clear%zu, self-bias and farther-caster traversal passed.\n",samples,fenceDark,fenceLit);
            pipelineOverride=nullptr; clearDestination=RenderColor(0,0,0,0);
            std::memcpy(world,savedWorld,sizeof(world));std::memcpy(screen,savedScreen,sizeof(screen));
            std::memcpy(uv,savedUV,sizeof(uv));std::memcpy(colors,savedColors,sizeof(colors));std::memcpy(indices,savedIndices,sizeof(indices));
            params[0]=alphaWaterParams;renderIndices[0]=alphaWaterIndices;rdp[0].primColor=hlslpp::float4(.1f,.2f,.7f,1);
            params[1]=beamParams1;params[2]=beamParams2;params[3]=beamParams3;rdp[1]=beamRdp1;rdp[2]=beamRdp2;rdp[3]=beamRdp3;
            renderIndices[2]=beamIndices2;renderIndices[3]=beamIndices3;reflection=beamStart;
            fill(renderParamsBuffer,params,sizeof(params));fill(renderIndicesBuffer,renderIndices,sizeof(renderIndices));fill(rdpParamsBuffer,rdp,sizeof(rdp));
            fill(screenBuffer,screen,sizeof(screen));fill(uvBuffer,uv,sizeof(uv));fill(colorBuffer,colors,sizeof(colors));
            common.setBuffer(common.RDPTiles,rdpTileBuffer,sizeof(rdpTile),RenderBufferStructuredView(sizeof(rdpTile)));
            common.setBuffer(common.GPUTiles,gpuTileBuffer,sizeof(gpuTile),RenderBufferStructuredView(sizeof(gpuTile)));
            textures.setTexture(0,skyTexture.get(),RenderTextureLayout::SHADER_READ,skyTextureView.get());
            prepareBeamScene({{6,3,1,0}});
            require(pipelines.prepare(device.get(),layout.get(),ms,false),"Failed to restore stable PS after beams/shore");
            require(render(1,0)==reflected && render(0,0)==original,"Beam/shore fixtures did not restore prior native/reflection baselines");
            std::printf("%ux MSAA beams: native prism%zu ordered%zu no-caster%zu; shore alpha/coverage%zu; zero/Off and prior baselines passed.\n",samples,prismCompared,orderedPixels,beamShadowWhite,shorePixels);

            // Actual sequential rendering, rather than substituting a constant
            // clear color for the seabed. Oblique light separates surface and
            // bottom footprints; their overlap exposes a second attenuation.
            const auto layeredStart=reflection;
            const auto layeredP0=params[0],layeredP1=params[1],layeredP2=params[2];
            const auto layeredR0=rdp[0],layeredR1=rdp[1],layeredR2=rdp[2];
            const auto layeredI0=renderIndices[0],layeredI1=renderIndices[1],layeredI2=renderIndices[2];
            for(uint32_t v=0;v<4;++v) {
                std::memcpy(world[7+v],world[v],sizeof(world[v]));world[7+v][1]=-4;
                std::memcpy(screen[7+v],screen[v],sizeof(screen[v]));screen[7+v][2]=.75f;
                colors[7+v][0]=colors[7+v][1]=colors[7+v][2]=1;colors[7+v][3]=0;
            }
            const float layerCaster[3][4]={{-1,3,-6,1},{7,3,-6,1},{3,3,6,1}};
            std::memcpy(world[4],layerCaster,sizeof(layerCaster));
            const uint32_t floorFaces[6]={7,8,9,7,9,10};std::memcpy(indices+9,floorFaces,sizeof(floorFaces));
            params[1]=primitiveSkyParams;params[1].omL=0;params[1].omH=0x00082cff;
            rdp[1].primColor=hlslpp::float4(.6f,.3f,.12f,1);
            renderIndices[1].faceIndicesStart=9;
            params[2]=primitiveSkyParams;rdp[2].primColor=hlslpp::float4(1,1,1,1);
            params[0]=textureSkyParams;params[0].ccL=0xfcffffff;params[0].ccH=0xfffcf279;
            params[0].omL=0x005049d8;params[0].omH=0x00082cff;
            renderIndices[0].rdpTileIndex=1;renderIndices[0].rdpTileCount=1;
            common.setBuffer(common.RDPTiles,upload(alphaTiles,sizeof(alphaTiles),RenderBufferFlag::STORAGE),sizeof(alphaTiles),RenderBufferStructuredView(sizeof(interop::RDPTile)));
            common.setBuffer(common.GPUTiles,upload(alphaGpuTiles,sizeof(alphaGpuTiles),RenderBufferFlag::STORAGE),sizeof(alphaGpuTiles),RenderBufferStructuredView(sizeof(interop::GPUTile)));
            textures.setTexture(1,waterTexture.get(),RenderTextureLayout::SHADER_READ,waterTextureView.get());
            fill(renderParamsBuffer,params,sizeof(params));fill(rdpParamsBuffer,rdp,sizeof(rdp));fill(renderIndicesBuffer,renderIndices,sizeof(renderIndices));
            fill(screenBuffer,screen,sizeof(screen));fill(colorBuffer,colors,sizeof(colors));
            reflection=Params{};reflection.camera[2]=0;reflection.strength=0;
            reflection.shadowOptions[0]=1;reflection.shadowOptions[1]=.5f;reflection.shadowOptions[2]=30000;
            reflection.shadowLight[0]=.6f;reflection.shadowLight[1]=.8f;reflection.shadowLight[3]=.55f;
            prepareBeamScene({{9,6,1,1},{6,3,2,1}});
            pipelineOverride=worldPipelines.get(false,false,false,false,true,true);
            const auto renderedFloor=render(1,0,1,9,6);
            const auto renderedFloorMask=render(1,5,1,9,6);
            pipelineOverride=nullptr;setNativeWaterAlpha(255);
            const auto renderedSurfaceMask=render(1,5);
            size_t doubleOverlap=0,surfaceOnly=0,layeredPixels=0;int layeredMaxError=0;bool layeredCorrect=true;
            for(size_t p=0;p<renderedFloor.size();p+=4) {
                doubleOverlap+=renderedFloorMask[p]==0&&renderedSurfaceMask[p]<255;
                surfaceOnly+=renderedFloorMask[p]==255&&renderedSurfaceMask[p]<255;
            }
            prepassPipeline=worldPipelines.get(false,false,false,false,true,true);
            prepassDrawIndex=1;prepassFirstIndex=9;prepassIndexCount=6;
            for(uint8_t alpha:{uint8_t(0),uint8_t(179),uint8_t(255)}) {
                setNativeWaterAlpha(alpha);const auto sequential=render(1,0);
                int maxForAlpha=0;size_t oldModelDifferences=0;
                for(uint32_t y=2;y<62;++y) for(uint32_t x=2;x<62;++x) {
                    const size_t p=(y*Width+x)*4;const float a=alpha/255.f;
                    const float waterRGB[]={26,51,179};const float q=1-.28f*(1-renderedSurfaceMask[p]/255.f);
                    for(size_t c=0;c<3;++c) {
                        const float baseline=a*waterRGB[c]+(1-a)*renderedFloor[p+c];
                        const float expected=q*baseline;
                        const int e=int(std::ceil(std::abs(sequential[p+c]-expected)));
                        maxForAlpha=std::max(maxForAlpha,e);layeredCorrect &= e<=2;
                        oldModelDifferences+=std::abs(sequential[p+c]-(1-.55f*(1-renderedSurfaceMask[p]/255.f))*baseline)>5;
                    }
                    ++layeredPixels;
                }
                layeredMaxError=std::max(layeredMaxError,maxForAlpha);
                std::printf("%ux MSAA sequential water alpha%u: error%d, old overlay control%zu channels.\n",samples,unsigned(alpha),maxForAlpha,oldModelDifferences);
            }
            prepassPipeline=nullptr;
            std::printf("%ux MSAA sequential shadow layers: overlap%zu surface-only%zu compared%zu max%d.\n",samples,doubleOverlap,surfaceOnly,layeredPixels,layeredMaxError);
            require(doubleOverlap>100&&surfaceOnly>100,"Layered receiver fixture did not separate surface and seabed footprints");
            require(layeredCorrect,"Scenery surface/seabed composition disagreed with the bounded soft surface layer");
            params[0]=layeredP0;params[1]=layeredP1;params[2]=layeredP2;
            rdp[0]=layeredR0;rdp[1]=layeredR1;rdp[2]=layeredR2;
            renderIndices[0]=layeredI0;renderIndices[1]=layeredI1;renderIndices[2]=layeredI2;reflection=layeredStart;
            std::memcpy(world,savedWorld,sizeof(world));std::memcpy(screen,savedScreen,sizeof(screen));
            std::memcpy(colors,savedColors,sizeof(colors));std::memcpy(indices,savedIndices,sizeof(indices));
            fill(renderParamsBuffer,params,sizeof(params));fill(rdpParamsBuffer,rdp,sizeof(rdp));fill(renderIndicesBuffer,renderIndices,sizeof(renderIndices));
            fill(screenBuffer,screen,sizeof(screen));fill(colorBuffer,colors,sizeof(colors));
            common.setBuffer(common.RDPTiles,rdpTileBuffer,sizeof(rdpTile),RenderBufferStructuredView(sizeof(rdpTile)));
            common.setBuffer(common.GPUTiles,gpuTileBuffer,sizeof(gpuTile),RenderBufferStructuredView(sizeof(gpuTile)));
            textures.setTexture(1,skyTexture.get(),RenderTextureLayout::SHADER_READ,skyTextureView.get());
            prepareBeamScene({{6,3,1,0}});
            require(render(1,0)==reflected&&render(0,0)==original,"Sequential shadow fixture failed to restore native/reflection baseline");

            // Real source triangles: Port Blue u_pkabe8_txt and Twilight City
            // u_wall18_txt. Their exact native normals are +X/-X, tangent to
            // native light(0,1,1). The third case shears Port's plane without
            // changing that tangency, stressing cancellation in derivatives.
            const float nativeWalls[2][3][3]={
                {{5750,600,-8000},{5750,600,-6000},{5750,-100,-6000}},
                {{600,150,-6850},{600,350,-7500},{600,150,-7500}}
            };
            size_t wallCases=0,wallFalseHits=0,wallSameDrawHits=0,wallThinHits=0;
            const auto wallParams0=params[0],wallParams2=params[2];
            const auto wallRdp0=rdp[0],wallRdp2=rdp[2];const auto wallIndices0=renderIndices[0];
            for(uint32_t wallKind=0;wallKind<3;++wallKind) for(float translate:{0.f,32768.f})
            for(bool perspective:{false,true}) for(bool nativeCutout:{false,true}) {
                const uint32_t family=wallKind==1?1:0;const float outward=family==0?1.f:-1.f;
                const float wallX=nativeWalls[family][0][0];
                float yTop=-1e20f,zLow=1e20f,zHigh=-1e20f;
                for(uint32_t v=0;v<3;++v) {
                    for(uint32_t c=0;c<3;++c) world[v][c]=nativeWalls[family][v][c];world[v][3]=1;
                    yTop=std::max(yTop,world[v][1]);zLow=std::min(zLow,world[v][2]);zHigh=std::max(zHigh,world[v][2]);
                    screen[v][0]=v==0?4:60;screen[v][1]=v==1?60:4;
                    screen[v][2]=.5f;screen[v][3]=perspective?float(1u<<v):1.f;
                    uv[v][0]=screen[v][0]*.5f;uv[v][1]=screen[v][1]*.5f;
                    colors[v][0]=colors[v][1]=colors[v][2]=1;colors[v][3]=v==0?0.f:v==1?.4f:1.f;
                }
                auto setWallCap=[&](uint32_t first,float nearX,float farX,float capY) {
                    const float cap[4][3]={{farX,capY,zLow-10000},{nearX,capY,zLow-10000},{nearX,capY,zHigh+10000},{farX,capY,zHigh+10000}};
                    for(uint32_t v=0;v<(first==7?4u:3u);++v) {
                        for(uint32_t c=0;c<3;++c) world[first+v][c]=cap[v][c];world[first+v][3]=1;
                    }
                };
                setWallCap(4,wallX,wallX-outward*8,yTop+120);
                const uint32_t wallFaces[12]={0,1,2,4,5,6,7,8,9,7,9,10};std::memcpy(indices,wallFaces,sizeof(wallFaces));
                auto transformWall=[&]() {
                    for(uint32_t v=0;v<11;++v) {
                        if(wallKind==2) world[v][0]+=(world[v][1]-world[v][2])*.125f;
                        world[v][0]+=translate;world[v][1]+=translate;world[v][2]-=translate;
                    }
                };
                transformWall();
                params[0]=primitiveSkyParams;params[0].omL=0;params[0].omH=0x00082cff;
                rdp[0].primColor=hlslpp::float4(.6f,.4f,.2f,1);
                if(nativeCutout) {
                    params[0]=textureSkyParams;params[0].ccL=0xfc127fff;params[0].ccH=0xfffff238;
                    params[0].omL=0xc8113078;params[0].omH=0x00182cff;params[0].flags.linearFiltering=0;
                    rdp[0].primColor=hlslpp::float4(1,1,1,0);rdp[0].fogColor=hlslpp::float4(.1f,.3f,.6f,1);
                }
                renderIndices[0].faceIndicesStart=0;renderIndices[0].rdpTileIndex=0;renderIndices[0].rdpTileCount=1;
                params[2]=primitiveSkyParams;rdp[2].primColor=hlslpp::float4(1,1,1,1);
                common.setBuffer(common.RDPTiles,upload(&cutoutTile,sizeof(cutoutTile),RenderBufferFlag::STORAGE),sizeof(cutoutTile),RenderBufferStructuredView(sizeof(cutoutTile)));
                common.setBuffer(common.GPUTiles,upload(&cutoutGpuTile,sizeof(cutoutGpuTile),RenderBufferFlag::STORAGE),sizeof(cutoutGpuTile),RenderBufferStructuredView(sizeof(cutoutGpuTile)));
                textures.setTexture(0,cutoutTexture.get(),RenderTextureLayout::SHADER_READ,cutoutView.get());
                fill(renderParamsBuffer,params,sizeof(params));fill(rdpParamsBuffer,rdp,sizeof(rdp));fill(renderIndicesBuffer,renderIndices,sizeof(renderIndices));
                fill(screenBuffer,screen,sizeof(screen));fill(uvBuffer,uv,sizeof(uv));fill(colorBuffer,colors,sizeof(colors));
                reflection=Params{};reflection.shadowOptions[0]=1;reflection.shadowOptions[1]=.5f;reflection.shadowOptions[2]=30000;
                reflection.shadowLight[1]=reflection.shadowLight[2]=1;reflection.shadowLight[3]=.55f;
                prepareBeamScene({{0,6,0,nativeCutout?3u:1u}});
                clearDestination=RenderColor(1,1,1,1);reflection.shadowOptions[0]=1;pipelineOverride=worldPipelines.get(false,false,false,false,true,true);
                const auto nativeWall=render(0,0,0,0,3);const auto litWall=render(1,0,0,0,3);
                const auto tangentMask=render(1,5,0,0,3);
                size_t falseHits=0;for(size_t q=0;q<tangentMask.size();q+=4) falseHits+=tangentMask[q]!=255||tangentMask[q+1]!=255||tangentMask[q+2]!=255;
                wallFalseHits+=falseHits;
                std::printf("%ux MSAA wall%u translation%.0f perspective%u cutout%u: falsehits%zu nativeequal%u.\n",samples,wallKind,translate,unsigned(perspective),unsigned(nativeCutout),falseHits,unsigned(nativeWall==litWall));
                require(falseHits==0&&nativeWall==litWall,"Tangent native wall self-shadowed or drifted across native fog/discard pixels");
                // Restore untransformed coordinates before moving only a cap.
                for(uint32_t v=0;v<11;++v) {
                    world[v][0]-=translate;world[v][1]-=translate;world[v][2]+=translate;
                    if(wallKind==2) world[v][0]-=(world[v][1]-world[v][2])*.125f;
                }
                if(nativeCutout) {
                    // A distinct thin nearby surface at normal offsets .4-.6
                    // remains hittable with the existing .5-world-unit bias.
                    // Two triangles cover the full Z interval even when the
                    // biased ray runs through the middle of this thin width.
                    setWallCap(7,wallX+outward*.4f,wallX+outward*.6f,yTop+1);
                    transformWall();prepareBeamScene({{0,6,0,3},{6,6,2,1}});
                }
                else {
                    // This cap is another primitive in the same draw/AS
                    // geometry: excluding the whole receiver is incorrect.
                    setWallCap(4,wallX,wallX+outward*8,yTop+120);
                    transformWall();prepareBeamScene({{0,6,0,1}});
                }
                const auto capMask=render(1,5,0,0,3);size_t capHits=0;
                for(size_t q=0;q<capMask.size();q+=4) capHits+=capMask[q]<128;
                if(nativeCutout) wallThinHits+=capHits;else wallSameDrawHits+=capHits;
                std::printf("%ux MSAA wall positive control: thin%u covered%zu.\n",samples,unsigned(nativeCutout),capHits);
                require(capHits>400,"Receiver exclusion or bias erased another face/nearby thin caster");
                ++wallCases;
            }
            std::printf("%ux MSAA native wall stability: cases%zu falsehits%zu same-draw-caster%zu thin-caster%zu.\n",samples,wallCases,wallFalseHits,wallSameDrawHits,wallThinHits);
            pipelineOverride=nullptr;clearDestination=RenderColor(0,0,0,0);
            params[0]=wallParams0;params[2]=wallParams2;rdp[0]=wallRdp0;rdp[2]=wallRdp2;renderIndices[0]=wallIndices0;
            reflection=layeredStart;std::memcpy(world,savedWorld,sizeof(world));std::memcpy(screen,savedScreen,sizeof(screen));
            std::memcpy(uv,savedUV,sizeof(uv));std::memcpy(colors,savedColors,sizeof(colors));std::memcpy(indices,savedIndices,sizeof(indices));
            fill(renderParamsBuffer,params,sizeof(params));fill(rdpParamsBuffer,rdp,sizeof(rdp));fill(renderIndicesBuffer,renderIndices,sizeof(renderIndices));
            fill(screenBuffer,screen,sizeof(screen));fill(uvBuffer,uv,sizeof(uv));fill(colorBuffer,colors,sizeof(colors));
            common.setBuffer(common.RDPTiles,rdpTileBuffer,sizeof(rdpTile),RenderBufferStructuredView(sizeof(rdpTile)));
            common.setBuffer(common.GPUTiles,gpuTileBuffer,sizeof(gpuTile),RenderBufferStructuredView(sizeof(gpuTile)));
            textures.setTexture(0,skyTexture.get(),RenderTextureLayout::SHADER_READ,skyTextureView.get());
            prepareBeamScene({{6,3,1,0}});
            require(render(1,0)==reflected&&render(0,0)==original,"Native wall fixture failed to restore original rendering");

            // Edge-on native fence card: native light lies in its plane, so
            // the original zero-thickness card alone cannot shadow the sand.
            // Generate the same bounded CPU proxy used by the renderer; its
            // private positions/UV/shade stream is sampled by production rays.
            const auto fenceP0=params[0],fenceP2=params[2],fenceP3=params[3];
            const auto fenceR0=rdp[0],fenceR2=rdp[2],fenceR3=rdp[3];
            const auto fenceI0=renderIndices[0],fenceI2=renderIndices[2],fenceI3=renderIndices[3];
            for(uint32_t v=0;v<4;++v) world[v][1]=-2;
            std::array<Wr64RTFenceVertex,4> fenceQuad{};
            const float fenceCard[4][5]={{-4,0,0,0,32},{4,0,0,32,32},{4,8,0,32,0},{-4,8,0,0,0}};
            for(uint32_t v=0;v<4;++v) {
                fenceQuad[v].position={fenceCard[v][0],fenceCard[v][1],fenceCard[v][2],1};
                fenceQuad[v].uv={fenceCard[v][3],fenceCard[v][4]};fenceQuad[v].shade={1,1,1,1};
                std::memcpy(world[7+v],fenceQuad[v].position.data(),sizeof(world[0]));
                std::memcpy(uv[7+v],fenceQuad[v].uv.data(),sizeof(uv[0]));
                std::memcpy(colors[7+v],fenceQuad[v].shade.data(),sizeof(colors[0]));
                std::memcpy(screen[7+v],savedScreen[v],sizeof(screen[0]));
            }
            const uint32_t fenceFaces[6]={7,8,9,7,9,10};std::memcpy(indices+9,fenceFaces,sizeof(fenceFaces));
            Wr64RTFenceProxy fenceProxy;fenceProxy.drawIndex=2;
            require(wr64RTAppendFenceProxy(fenceQuad,fenceProxy)&&fenceProxy.triangles.size()==96,"Native fence proxy producer returned unexpected slices");
            Pixels fenceTexels(32*256,0);
            for(uint32_t y=0;y<32;++y) for(uint32_t x=0;x<32;++x) {
                const size_t o=y*256+x*4;fenceTexels[o]=fenceTexels[o+1]=fenceTexels[o+2]=255;
                fenceTexels[o+3]=(x>=16&&(y<12||y>=20))?255:0;
            }
            auto fenceTexture=device->createTexture(RenderTextureDesc::Texture2D(32,32,1,RenderFormat::R8G8B8A8_UNORM));
            auto fenceView=fenceTexture->createTextureView(RenderTextureViewDesc::Texture2D(RenderFormat::R8G8B8A8_UNORM));
            auto fenceUpload=upload(fenceTexels.data(),fenceTexels.size(),0);
            worker.commandList->begin();worker.commandList->barriers(RenderBarrierStage::COPY,RenderTextureBarrier(fenceTexture.get(),RenderTextureLayout::COPY_DEST));
            worker.commandList->copyTextureRegion(RenderTextureCopyLocation::Subresource(fenceTexture.get()),RenderTextureCopyLocation::PlacedFootprint(fenceUpload,RenderFormat::R8G8B8A8_UNORM,32,32,1,64));
            worker.commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE,RenderTextureBarrier(fenceTexture.get(),RenderTextureLayout::SHADER_READ));
            worker.commandList->end();worker.execute();worker.wait();
            textures.setTexture(0,fenceTexture.get(),RenderTextureLayout::SHADER_READ,fenceView.get());
            common.setBuffer(common.RDPTiles,upload(&cutoutTile,sizeof(cutoutTile),RenderBufferFlag::STORAGE),sizeof(cutoutTile),RenderBufferStructuredView(sizeof(cutoutTile)));
            common.setBuffer(common.GPUTiles,upload(&cutoutGpuTile,sizeof(cutoutGpuTile),RenderBufferFlag::STORAGE),sizeof(cutoutGpuTile),RenderBufferStructuredView(sizeof(cutoutGpuTile)));
            params[0]=primitiveSkyParams;rdp[0].primColor=hlslpp::float4(.1f,.2f,.7f,1);renderIndices[0].faceIndicesStart=0;
            params[2]=textureSkyParams;params[2].ccL=0xfc127fff;params[2].ccH=0xfffff238;
            params[2].omL=0xc8113078;params[2].omH=0x00182cff;params[2].flags.linearFiltering=0;
            rdp[2].primColor=hlslpp::float4(1,1,1,0);rdp[2].fogColor=hlslpp::float4(.05f,.9f,.1f,1);
            renderIndices[2].faceIndicesStart=9;renderIndices[2].rdpTileIndex=0;renderIndices[2].rdpTileCount=1;
            params[3]=params[2];rdp[3]=rdp[2];renderIndices[3]=renderIndices[2];renderIndices[3].instanceIndex=3;
            fill(renderParamsBuffer,params,sizeof(params));fill(rdpParamsBuffer,rdp,sizeof(rdp));fill(renderIndicesBuffer,renderIndices,sizeof(renderIndices));
            fill(screenBuffer,screen,sizeof(screen));fill(uvBuffer,uv,sizeof(uv));fill(colorBuffer,colors,sizeof(colors));
            reflection=Params{};reflection.shadowOptions[0]=1;reflection.shadowOptions[1]=.5f;reflection.shadowOptions[2]=30000;
            reflection.shadowLight[0]=-1;reflection.shadowLight[1]=1;reflection.shadowLight[3]=.55f;
            auto prepareFence=[&](bool proxies) {
                std::vector<Wr64RTFenceProxy> selected;if(proxies)selected.push_back(fenceProxy);
                require(scene.prepare(device.get(),positions.get(),faces.get(),16,54,{{9,6,2,3}},selected),"Fence proxy AS preparation failed");
                common.setAccelerationStructure(common.SceneBVH,scene.accelerationStructure());
                common.setBuffer(common.wr64FenceProxy,scene.proxyBuffer(),scene.proxyBufferSize());
                common.setBuffer(common.interleavedRasters,scene.geometryBuffer(),scene.geometryBufferSize(),RenderBufferStructuredView(16));
                refreshFixtureIndices();
            };
            prepareFence(false);reflection.shadowOptions[0]=0;
            const auto nativeFenceOff=render(0,0),nativeFenceReflection=render(1,0);
            reflection.shadowOptions[0]=1;pipelineOverride=worldPipelines.get(false,false,false,false,true,true);
            const auto flatFenceMask=render(1,5);
            require(shadowWhite(flatFenceMask),"Original edge-on fence unexpectedly blocks parallel native light");
            prepareFence(true);const auto proxyMask=render(1,5);pipelineOverride=nullptr;reflection.shadowOptions[0]=0;
            require(render(0,0)==nativeFenceOff&&render(1,0)==nativeFenceReflection,"Private fence proxy altered native or reflected geometry");
            // Independent native raster acceptance of the generated surfaces,
            // projected along the light onto the receiving floor. Its union of
            // native discarded fragments is the shadow acceptance reference.
            const size_t proxyCount=fenceProxy.triangles.size();
            std::vector<std::array<float,4>> proxyScreen(proxyCount),proxyWorld(proxyCount),proxyShade(proxyCount);
            std::vector<std::array<float,2>> proxyUV(proxyCount);std::vector<uint32_t> proxyIndex(proxyCount);
            for(size_t v=0;v<proxyCount;++v) {
                const auto& vertex=fenceProxy.triangles[v];proxyWorld[v]=vertex.position;proxyShade[v]=vertex.shade;proxyUV[v]=vertex.uv;proxyIndex[v]=uint32_t(v);
                proxyScreen[v]={(vertex.position[0]+vertex.position[1]+1.5f+5)*6.4f,(5-vertex.position[2])*6.4f,.5f,1};
            }
            auto proxyWorldUpload=upload(proxyWorld.data(),proxyWorld.size()*16,RenderBufferFlag::STORAGE);
            const RenderVertexBufferView proxyViews[]={
                RenderVertexBufferView(upload(proxyScreen.data(),proxyScreen.size()*16,RenderBufferFlag::VERTEX)->at(0),proxyScreen.size()*16),
                RenderVertexBufferView(upload(proxyUV.data(),proxyUV.size()*8,RenderBufferFlag::VERTEX)->at(0),proxyUV.size()*8),
                RenderVertexBufferView(upload(proxyShade.data(),proxyShade.size()*16,RenderBufferFlag::VERTEX)->at(0),proxyShade.size()*16)};
            const RenderIndexBufferView proxyIndexView(upload(proxyIndex.data(),proxyIndex.size()*4,RenderBufferFlag::INDEX)->at(0),proxyIndex.size()*4,RenderFormat::R32_UINT);
            common.setBuffer(common.posBuffer,proxyWorldUpload,proxyWorld.size()*16);
            vertexBufferOverride=proxyViews;indexBufferOverride=&proxyIndexView;pipelineOverride=worldPipelines.get(false,false,false,false,true,true);
            const auto nativeProxyMask=render(0,0,2,0,uint32_t(proxyCount));
            vertexBufferOverride=nullptr;indexBufferOverride=nullptr;pipelineOverride=nullptr;
            common.setBuffer(common.posBuffer,positions.get(),sizeof(world));
            size_t proxyCompared=0,proxyBlocked=0,proxyClear=0;bool proxyCorrect=true;
            for(uint32_t y=2;y<62;++y) for(uint32_t x=2;x<62;++x) {
                const size_t p=(y*Width+x)*4;const bool accepted=nativeProxyMask[p+1]>127;bool uniform=true;
                for(int dy=-1;dy<=1;++dy) for(int dx=-1;dx<=1;++dx)
                    uniform &= (nativeProxyMask[((int(y)+dy)*Width+int(x)+dx)*4+1]>127)==accepted;
                if(!uniform)continue;
                proxyCorrect &= proxyMask[p]==(accepted?0:255);accepted?++proxyBlocked:++proxyClear;++proxyCompared;
            }
            require(proxyCorrect&&proxyBlocked>100&&proxyClear>1000,"Fence proxy alpha holes disagree with native rasterized acceptance");
            clearDestination=RenderColor(1,1,1,1);reflection.shadowOptions[0]=1;pipelineOverride=worldPipelines.get(false,false,false,false,true,true);
            const auto proxyOwnerMask=render(1,5,2,9,6);const auto proxyOtherReceiver=render(1,5,3,9,6);
            require(shadowWhite(proxyOwnerMask),"Approximate fence volume shadows its own native card");
            size_t otherReceiverHits=0;for(size_t q=0;q<proxyOtherReceiver.size();q+=4)otherReceiverHits+=proxyOtherReceiver[q]<128;
            require(otherReceiverHits>100,"Fence owner exclusion incorrectly suppresses another receiver draw");
            pipelineOverride=nullptr;clearDestination=RenderColor(0,0,0,0);prepareFence(false);
            pipelineOverride=worldPipelines.get(false,false,false,false,true,true);
            require(scene.stats().proxyGeometryCount==0&&scene.proxyBufferSize()>=48&&render(1,5)==flatFenceMask,"Removing proxies retained stale shadow geometry");
            pipelineOverride=nullptr;reflection.shadowOptions[0]=0;
            require(render(1,0)==nativeFenceReflection,"Removing proxies changed original reflections");
            std::printf("%ux MSAA fence proxy: slices%zu native comparisons%zu blocked%zu clear%zu other-receiver%zu; native/reflection/empty restoration passed.\n",samples,proxyCount/6,proxyCompared,proxyBlocked,proxyClear,otherReceiverHits);
            params[0]=fenceP0;params[2]=fenceP2;params[3]=fenceP3;rdp[0]=fenceR0;rdp[2]=fenceR2;rdp[3]=fenceR3;
            renderIndices[0]=fenceI0;renderIndices[2]=fenceI2;renderIndices[3]=fenceI3;reflection=layeredStart;
            std::memcpy(world,savedWorld,sizeof(world));std::memcpy(screen,savedScreen,sizeof(screen));std::memcpy(uv,savedUV,sizeof(uv));std::memcpy(colors,savedColors,sizeof(colors));std::memcpy(indices,savedIndices,sizeof(indices));
            fill(renderParamsBuffer,params,sizeof(params));fill(rdpParamsBuffer,rdp,sizeof(rdp));fill(renderIndicesBuffer,renderIndices,sizeof(renderIndices));
            fill(screenBuffer,screen,sizeof(screen));fill(uvBuffer,uv,sizeof(uv));fill(colorBuffer,colors,sizeof(colors));
            common.setBuffer(common.RDPTiles,rdpTileBuffer,sizeof(rdpTile),RenderBufferStructuredView(sizeof(rdpTile)));
            common.setBuffer(common.GPUTiles,gpuTileBuffer,sizeof(gpuTile),RenderBufferStructuredView(sizeof(gpuTile)));
            textures.setTexture(0,skyTexture.get(),RenderTextureLayout::SHADER_READ,skyTextureView.get());
            prepareBeamScene({{6,3,1,0}});require(render(1,0)==reflected&&render(0,0)==original,"Fence proxy fixture did not restore prior baselines");

            // Deterministic actor softness is an opt-in extension of the
            // preceding hard-shadow contracts. The expected coverage here is
            // an independent analytic ray/rectangle test, not shader readback.
            interop::RenderParams softSavedParams[4];interop::RDPParams softSavedRdp[4];
            interop::RenderIndices softSavedIndices[4];
            std::memcpy(softSavedParams,params,sizeof(params));std::memcpy(softSavedRdp,rdp,sizeof(rdp));
            std::memcpy(softSavedIndices,renderIndices,sizeof(renderIndices));const auto softStart=reflection;
            auto softQuad=[&](uint32_t first,float x0,float x1,float y,float z0,float z1) {
                const float p[4][4]={{x0,y,z1,1},{x1,y,z1,1},{x1,y,z0,1},{x0,y,z0,1}};
                std::memcpy(world[first],p,sizeof(p));
                for(uint32_t v=0;v<4;++v) {
                    std::memcpy(screen[first+v],savedScreen[v],sizeof(screen[0]));
                    colors[first+v][0]=colors[first+v][1]=colors[first+v][2]=1;colors[first+v][3]=0;
                    uv[first+v][0]=uv[first+v][1]=0;
                }
            };
            softQuad(0,-20,20,0,-20,20);softQuad(4,-20,20,-4,-20,20);
            softQuad(8,-6,6,5,-6,6);softQuad(12,198,202,5,-20,20);
            for(uint32_t q=0;q<4;++q) {
                const uint32_t f[6]={q*4,q*4+1,q*4+2,q*4,q*4+2,q*4+3};
                std::memcpy(indices+q*6,f,sizeof(f));
                params[q]=primitiveSkyParams;params[q].omL=0;params[q].omH=0x00082cff;
                params[q].flags.sampleCount=samples==1?0:2;
                renderIndices[q].instanceIndex=q;renderIndices[q].faceIndicesStart=q*6;
                renderIndices[q].rdpTileIndex=0;renderIndices[q].rdpTileCount=0;
            }
            rdp[0].primColor=hlslpp::float4(.1f,.2f,.7f,1);
            rdp[1].primColor=hlslpp::float4(.6f,.3f,.12f,1);
            rdp[2].primColor=hlslpp::float4(.95f,.8f,.1f,1);
            rdp[3].primColor=hlslpp::float4(.85f,.05f,.2f,1);
            params[0]=textureSkyParams;params[0].ccL=0xfcffffff;params[0].ccH=0xfffcf279;
            params[0].omL=0x005049d8;params[0].omH=0x00082cff;params[0].flags.sampleCount=samples==1?0:2;
            renderIndices[0].rdpTileIndex=1;renderIndices[0].rdpTileCount=1;
            common.setBuffer(common.RDPTiles,upload(alphaTiles,sizeof(alphaTiles),RenderBufferFlag::STORAGE),sizeof(alphaTiles),RenderBufferStructuredView(sizeof(interop::RDPTile)));
            common.setBuffer(common.GPUTiles,upload(alphaGpuTiles,sizeof(alphaGpuTiles),RenderBufferFlag::STORAGE),sizeof(alphaGpuTiles),RenderBufferStructuredView(sizeof(interop::GPUTile)));
            textures.setTexture(1,waterTexture.get(),RenderTextureLayout::SHADER_READ,waterTextureView.get());
            fill(renderParamsBuffer,params,sizeof(params));fill(rdpParamsBuffer,rdp,sizeof(rdp));fill(renderIndicesBuffer,renderIndices,sizeof(renderIndices));
            fill(screenBuffer,screen,sizeof(screen));fill(uvBuffer,uv,sizeof(uv));fill(colorBuffer,colors,sizeof(colors));
            reflection=Params{};reflection.camera[1]=40;reflection.camera[2]=-40;reflection.strength=0;
            reflection.shadowOptions[0]=1;reflection.shadowOptions[1]=.5f;reflection.shadowOptions[2]=30000;
            reflection.shadowLight[0]=.6f;reflection.shadowLight[1]=.8f;reflection.shadowLight[3]=.55f;
            reflection.sceneOptions[1]=1;reflection.sceneOptions[2]=1;
            auto prepareSoft=[&](uint32_t actorFlags=17u,bool scenery=false) {
                std::vector<Wr64RTSceneGeometry> g={{6,6,1,1},{12,6,2,actorFlags}};
                if(scenery)g.push_back({18,6,3,1});prepareBeamScene(g);
            };
            captureActorReadbacks = true;
            prepareSoft();setNativeWaterAlpha(255);clearDestination=RenderColor(0,0,0,0);
            pipelineOverride=worldPipelines.get(false,false,false,false,true,true);
            const auto softNativeFloor=render(0,0,1,6,6),softFloor=render(1,0,1,6,6),softFloorMask=render(1,5,1,6,6);
            require(render(1,5,1,6,6)==softFloorMask,"Actor shadow samples jitter between identical frames");
            pipelineOverride=nullptr;const auto softSurfaceMask=render(1,5);
            const auto softNativeWater=render(0,0);const auto softWater=render(1,0);
            std::vector<double> softFloorCoverage(Width*Height),softSurfaceCoverage(Width*Height);
            auto actorCoverage=[&](uint32_t x,uint32_t y,double receiverY,double radius,uint32_t sampleCount=16,uint32_t radialPairCount=0) {
                const double px=(x+.5)*40/Width-20,pz=20-(y+.5)*40/Height;
                const double shift=(5-(receiverY+.5))*.75;
                uint32_t hits=0;
                const uint32_t pairCount=sampleCount/2;
                if(!radialPairCount)radialPairCount=pairCount;
                for(uint32_t pair=0;pair<pairCount;++pair) {
                    const double r=std::sqrt((pair+.5)/double(radialPairCount)),angle=pair*3.14159265358979323846*(3-std::sqrt(5.0));
                    for(double sign:{-1.0,1.0}) {
                        const double hx=px+shift+sign*radius*r*std::cos(angle);
                        const double hz=pz-sign*radius*r*std::sin(angle);
                        hits+=hx>=-6&&hx<=6&&hz>=-6&&hz<=6;
                    }
                }
                return hits/double(sampleCount);
            };
            size_t softEdges=0,wideEdges=0,softFull=0,softClear=0;int softMaskError=0,softColorError=0;
            bool softExpected=true,softCoverageChannel=true;
            for(uint32_t y=2;y<62;++y)for(uint32_t x=2;x<62;++x) {
                const size_t i=y*Width+x,p=i*4;const double ground=actorCoverage(x,y,-4,2.5),surface=actorCoverage(x,y,0,7.5);
                softFloorCoverage[i]=ground;softSurfaceCoverage[i]=surface;
                softEdges+=ground>0&&ground<1;wideEdges+=surface>0&&surface<1;softFull+=ground==1;softClear+=ground==0;
                const int maskError=int(std::ceil(std::max(std::abs(softFloorMask[p]-255*(1-ground)),std::abs(softSurfaceMask[p]-255*(1-surface)))));
                softMaskError=std::max(softMaskError,maskError);softExpected &= maskError<=1;
                for(uint32_t c=0;c<3;++c) {
                    const int e=int(std::ceil(std::max(std::abs(softFloor[p+c]-(1-.55*ground)*softNativeFloor[p+c]),
                        std::abs(softWater[p+c]-(1-.18*surface)*softNativeWater[p+c]))));
                    softColorError=std::max(softColorError,e);softExpected &= e<=2;
                }
                softCoverageChannel &= softWater[p+3]==softNativeWater[p+3]&&softFloor[p+3]==softNativeFloor[p+3];
            }
            std::printf("%ux MSAA actor kernel: solid-edge%zu water-edge%zu full%zu clear%zu mask-error%d color-error%d.\n",samples,softEdges,wideEdges,softFull,softClear,softMaskError,softColorError);
            require(softExpected&&softCoverageChannel&&softEdges>100&&wideEdges>softEdges*2&&softFull>50&&softClear>1000,
                "Actor-only soft shadow kernel disagrees with analytic rays or native coverage");
            if (qualityOptions) {
                Pixels qualityMasks[4];size_t qualityComparisons=0;
                for(uint32_t rayCount:{4u,8u,12u,16u}) {
                    reflection.qualityOptions[1]=float(rayCount);
                    pipelineOverride=worldPipelines.get(false,false,false,false,true,true);
                    const auto floorMask=render(1,5,1,6,6),floorColor=render(1,0,1,6,6);
                    require(render(1,5,1,6,6)==floorMask,"Reduced solid shadow quality is nondeterministic");
                    pipelineOverride=nullptr;const auto waterMask=render(1,5),waterColor=render(1,0);
                    require(render(1,5)==waterMask,"Reduced water shadow quality is nondeterministic");
                    qualityMasks[rayCount/4-1]=waterMask;
                    size_t fractional=0,outerSupport=0,clear=0,full=0;int maxMaskError=0;
                    bool correct=true;
                    for(uint32_t y=2;y<62;++y)for(uint32_t x=2;x<62;++x) {
                        const size_t p=(y*Width+x)*4;
                        const double floor=actorCoverage(x,y,-4,2.5,rayCount),water=actorCoverage(x,y,0,7.5,rayCount);
                        const double truncated=actorCoverage(x,y,0,7.5,rayCount,8);
                        fractional+=water>0&&water<1;clear+=water==0;full+=floor==1;
                        outerSupport+=water>0&&truncated==0;
                        const int e=int(std::ceil(std::max(std::abs(floorMask[p]-255*(1-floor)),std::abs(waterMask[p]-255*(1-water)))));
                        maxMaskError=std::max(maxMaskError,e);correct &= e<=1;
                        for(uint32_t c=0;c<3;++c) {
                            correct &= std::abs(floorColor[p+c]-(1-.55*floor)*softNativeFloor[p+c])<=2;
                            correct &= std::abs(waterColor[p+c]-(1-.18*water)*softNativeWater[p+c])<=2;
                        }
                        correct &= floorColor[p+3]==softNativeFloor[p+3]&&waterColor[p+3]==softNativeWater[p+3];
                        ++qualityComparisons;
                    }
                    require(correct&&fractional>100&&clear>1000&&full>50,
                        "RT shadow quality disagrees with independent disc rays, strength or native alpha");
                    if(rayCount<16)require(outerSupport>10,"Reduced shadow quality truncated the old inner kernel and shrank its support");
                    else require(waterMask==softSurfaceMask&&floorMask==softFloorMask&&waterColor==softWater&&floorColor==softFloor,
                        "Explicit 16-ray quality changed legacy-zero shadow output");
                    std::printf("%ux RT quality actor rays%u: fractional%zu beyond-truncated-support%zu mask-error%d.\n",samples,rayCount,fractional,outerSupport,maxMaskError);
                }
                for(float invalid:{0.f,-1.f,std::numeric_limits<float>::quiet_NaN(),std::numeric_limits<float>::infinity(),32.f}) {
                    reflection.qualityOptions[1]=invalid;
                    require(render(1,5)==softSurfaceMask,"Invalid/default shadow sample setting did not preserve 16 rays");
                }
                for(const auto rounded:std::array<std::pair<float,uint32_t>,4>{{{1.f,4u},{6.f,8u},{10.f,12u},{14.f,16u}}}) {
                    reflection.qualityOptions[1]=rounded.first;
                    require(render(1,5)==qualityMasks[rounded.second/4-1],"Shadow sample setting did not clamp/round to a supported mode");
                }
                reflection.qualityOptions[1]=0;
                require(render(1,5)==softSurfaceMask,"Changing shadow quality left a stale sample kernel");
                std::printf("%ux RT quality shadows: %zu analytic pixel comparisons; changing settings restores native-default output.\n",samples,qualityComparisons);
            }
            reflection.shadowLight[3]=0;require(render(1,0)==softNativeWater,"Zero actor strength changed native water");
            pipelineOverride=worldPipelines.get(false,false,false,false,true,true);
            require(render(1,0,1,6,6)==softNativeFloor,"Zero actor strength changed the solid receiver");
            pipelineOverride=nullptr;reflection.shadowLight[3]=.55f;

            // The broad-phase is only an optimization: conservative, missing
            // and invalid bounds must agree with actually tracing the actor.
            reflection.actorBoundsMin[0][0]=-6;reflection.actorBoundsMin[0][1]=5;reflection.actorBoundsMin[0][2]=-6;
            reflection.actorBoundsMax[0][0]=6;reflection.actorBoundsMax[0][1]=5;reflection.actorBoundsMax[0][2]=6;
            reflection.sceneOptions[3]=1;const auto boundedSoft=reflection;
            require(render(1,5)==softSurfaceMask,"Conservative actor AABB suppressed part of the wider surface kernel");
            pipelineOverride=worldPipelines.get(false,false,false,false,true,true);
            require(render(1,5,1,6,6)==softFloorMask,"Conservative actor AABB suppressed part of the solid kernel");
            pipelineOverride=nullptr;
            for(uint32_t invalid=0;invalid<5;++invalid) {
                reflection=boundedSoft;
                if(invalid==0)reflection.sceneOptions[3]=0;
                if(invalid==1)reflection.sceneOptions[2]=3;
                if(invalid==2)reflection.actorBoundsMin[0][0]=std::numeric_limits<float>::quiet_NaN();
                if(invalid==3)reflection.actorBoundsMax[0][1]=std::numeric_limits<float>::infinity();
                if(invalid==4)reflection.actorBoundsMin[0][0]=7;
                require(render(1,5)==softSurfaceMask,"Invalid/incomplete actor bounds suppressed a real soft shadow");
            }
            reflection=boundedSoft;reflection.sceneOptions[3]=0;
            for(auto& v:world){v[0]+=32768;v[1]+=1024;v[2]-=32768;}
            reflection.camera[0]+=32768;reflection.camera[1]+=1024;reflection.camera[2]-=32768;rebuildPositions();
            require(render(1,5)==softSurfaceMask,"Actor kernel changed when camera and world were translated together");
            pipelineOverride=worldPipelines.get(false,false,false,false,true,true);
            const auto translatedSoftFloor=render(1,5,1,6,6);
            size_t translatedDifferences=0,translationBoundaryPixels=0,translationExactPixels=0;int translatedMaximum=0;bool translationCorrect=true;
            float translatedMagnitude=0;
            for(const auto& v:world)for(uint32_t c=0;c<3;++c)translatedMagnitude=std::max(translatedMagnitude,std::abs(v[c]));
            const double translatedUlp=std::nextafter(translatedMagnitude,std::numeric_limits<float>::infinity())-translatedMagnitude;
            for(uint32_t y=0;y<Height;++y)for(uint32_t x=0;x<Width;++x) {
                const size_t p=(y*Width+x)*4;const int error=std::abs(int(translatedSoftFloor[p])-int(softFloorMask[p]));
                const double px=(x+.5)*40/Width-20,pz=20-(y+.5)*40/Height;double nearest=1e10;uint32_t ambiguousTaps=0;
                for(uint32_t pair=0;pair<8;++pair)for(double sign:{-1.0,1.0}) {
                    const double r=std::sqrt((pair+.5)/8.0),angle=pair*3.14159265358979323846*(3-std::sqrt(5.0));
                    const double hx=px+6.375+sign*2.5*r*std::cos(angle),hz=pz-sign*2.5*r*std::sin(angle);
                    const double dx=std::abs(std::abs(hx)-6),dz=std::abs(std::abs(hz)-6);
                    nearest=std::min(nearest,std::min(dx,dz));
                    ambiguousTaps+=(dx<=translatedUlp&&std::abs(hz)<=6+translatedUlp)||(dz<=translatedUlp&&std::abs(hx)<=6+translatedUlp);
                }
                // Pair3 grazes this fixture's edge by .000206 world units,
                // below float spacing at32768. Permit only that independently
                // identified tap to change; all other pixels remain exact.
                if(ambiguousTaps)++translationBoundaryPixels;
                else {++translationExactPixels;translationCorrect &= error==0;}
                translationCorrect &= error<=int(std::ceil(255.0*ambiguousTaps/16));
                translationCorrect &= translatedSoftFloor[p+3]==softFloorMask[p+3];
                for(uint32_t c=1;c<3;++c)translationCorrect &= translatedSoftFloor[p+c]==translatedSoftFloor[p];
                if(!error)continue;translatedMaximum=std::max(translatedMaximum,error);
                if(translatedDifferences<8) {
                    std::printf("%ux translated solid sample%u,%u old%u new%u nearest-edge%.9f bounds-mask%u.\n",samples,x,y,unsigned(softFloorMask[p]),unsigned(translatedSoftFloor[p]),nearest,reflection.sceneOptions[3]);
                }
                ++translatedDifferences;
            }
            std::printf("%ux translated solid differences%zu maximum%d exact-nonboundary%zu boundary%zu ulp%.8f.\n",samples,translatedDifferences,translatedMaximum,translationExactPixels,translationBoundaryPixels,translatedUlp);
            require(translationCorrect&&translationExactPixels>4000,"Translated solid actor kernel changed beyond independently bounded float-edge uncertainty");
            pipelineOverride=nullptr;
            for(auto& v:world){v[0]-=32768;v[1]-=1024;v[2]+=32768;}
            reflection=boundedSoft;rebuildPositions();
            reflection.camera[0]+=13;reflection.camera[2]+=7;
            require(render(1,5)==softSurfaceMask,"Camera movement rotated or randomized the world-anchored actor kernel");
            reflection=boundedSoft;
            prepareSoft(16);require(shadowWhite(render(1,5))&&render(1,0)==softNativeWater,"Actor identity without caster permission produced a water shadow");
            pipelineOverride=worldPipelines.get(false,false,false,false,true,true);
            require(shadowWhite(render(1,5,1,6,6))&&render(1,0,1,6,6)==softNativeFloor,"Actor identity bypassed the physical-caster flag on solid receivers");
            pipelineOverride=nullptr;prepareSoft();
            for(uint32_t v=8;v<12;++v)world[v][0]+=200;
            reflection.actorBoundsMin[0][0]+=200;reflection.actorBoundsMax[0][0]+=200;rebuildPositions();
            require(shadowWhite(render(1,5))&&render(1,0)==softNativeWater,"A valid remote actor bound created a local shadow");
            for(uint32_t v=8;v<12;++v)world[v][0]-=200;reflection=boundedSoft;rebuildPositions();
            captureActorReadbacks = false;
            softQuad(12,-2,2,5,-20,20);prepareSoft(17,true);
            pipelineOverride=worldPipelines.get(false,false,false,false,true,true);
            const auto mixedMask=render(1,5,1,6,6);size_t hardSceneryPixels=0;bool mixedCorrect=true;
            for(uint32_t y=2;y<62;++y)for(uint32_t x=2;x<62;++x) {
                const size_t i=y*Width+x,p=i*4;const double hitX=(x+.5)*40/Width-20+8.5*.75;
                const bool hard=hitX>=-2&&hitX<=2;hardSceneryPixels+=hard;
                mixedCorrect &= std::abs(mixedMask[p]-255*(1-(hard?1:softFloorCoverage[i])))<=1;
            }
            pipelineOverride=nullptr;
            require(mixedCorrect&&hardSceneryPixels>200,"Soft actor selection blurred the accepted solid scenery shadow");
#include "water_object_shadow_fixture.inl"
            prepareSoft();

            captureActorReadbacks = true;
            // Real receiver -> water composition, including native fully
            // transparent water, exposes accidental double-strength shadows.
            prepassPipeline=worldPipelines.get(false,false,false,false,true,true);
            prepassDrawIndex=1;prepassFirstIndex=6;prepassIndexCount=6;
            size_t actorLayerChecks=0,hardOverlayDifferences=0;int actorLayerError=0;bool actorLayersCorrect=true;
            for(uint8_t alpha:{uint8_t(0),uint8_t(179),uint8_t(255)}) {
                setNativeWaterAlpha(alpha);const auto layeredActor=render(1,0);const double a=alpha/255.0;
                for(uint32_t y=2;y<62;++y)for(uint32_t x=2;x<62;++x) {
                    const size_t i=y*Width+x,p=i*4;const double q=1-.18*softSurfaceCoverage[i];
                    for(uint32_t c=0;c<3;++c) {
                        const double baseline=a*softNativeWater[p+c]+(1-a)*softFloor[p+c];
                        const int e=int(std::ceil(std::abs(layeredActor[p+c]-q*baseline)));
                        actorLayerError=std::max(actorLayerError,e);actorLayersCorrect &= e<=2;
                        hardOverlayDifferences+=std::abs(layeredActor[p+c]-(1-.55*softSurfaceCoverage[i])*baseline)>5;
                        // At full strength floor >=.45 and surface >=.82:
                        // their joint transmission cannot fall below .369.
                        const double fullyLit=a*softNativeWater[p+c]+(1-a)*softNativeFloor[p+c];
                        actorLayersCorrect &= layeredActor[p+c]+2>=.369*fullyLit;
                        ++actorLayerChecks;
                    }
                    actorLayersCorrect &= layeredActor[p+3]==softNativeWater[p+3];
                }
            }
            prepassPipeline=nullptr;
            std::printf("%ux MSAA actor layers: comparisons%zu max-error%d rejected-hard-overlay%zu.\n",samples,actorLayerChecks,actorLayerError,hardOverlayDifferences);
            require(actorLayersCorrect&&hardOverlayDifferences>1500,"Actor surface/seabed composition violated alpha or the bounded overlap strength");
            softQuad(8,-14,14,5,-14,14);prepareSoft();reflection.sceneOptions[3]=0;setNativeWaterAlpha(0);
            require(center(render(1,5))[0]==0,"Broad actor fixture did not fully cover the surface kernel");
            pipelineOverride=worldPipelines.get(false,false,false,false,true,true);
            require(center(render(1,5,1,6,6))[0]==0,"Broad actor fixture did not fully cover the solid kernel");
            pipelineOverride=nullptr;prepassPipeline=worldPipelines.get(false,false,false,false,true,true);
            const auto fullyOverlappedActor=center(render(1,0));const auto fullyLitFloor=center(softNativeFloor);
            for(uint32_t c=0;c<3;++c)require(std::abs(fullyOverlappedActor[c]-.369*fullyLitFloor[c])<=2,
                "Fully overlapping actor layers did not retain .369 of the lit floor");
            prepassPipeline=nullptr;softQuad(8,-6,6,5,-6,6);prepareSoft();reflection=boundedSoft;

            // Reflection-color differences isolate A*F*R from the attenuated
            // native water and transmitted destination without assuming that
            // the actor itself is absent from the reflection acceleration AS.
            setNativeWaterAlpha(179);reflection.strength=1;clearDestination=RenderColor(.8f,.4f,.2f,1);
            reflection.shadowOptions[0]=0;const auto actorObjectUnshadowed=render(1,0);
            reflection.shadowOptions[0]=1;const auto actorObjectShadowed=render(1,0);
            reflection.strength=0;const auto actorBaseShadowed=render(1,0);
            reflection.shadowOptions[0]=0;const auto actorBaseUnshadowed=render(1,0);
            reflection.strength=1;setNativeWaterAlpha(255);const auto actorReflectHit=render(1,2);setNativeWaterAlpha(179);
            bool actorReflectionCorrect=true;size_t actorReflectionChecks=0;
            for(uint32_t y=2;y<62;++y)for(uint32_t x=2;x<62;++x) {
                const size_t i=y*Width+x,p=i*4;if(actorReflectHit[p+1]!=255)continue;
                const double px=(x+.5)*40/Width-20,pz=20-(y+.5)*40/Height;
                const double nv=40/std::sqrt(px*px+1600+(pz+40)*(pz+40));
                const double f=.08+.35*std::pow(1-nv,5),q=1-.18*softSurfaceCoverage[i],a=179.0/255;
                for(uint32_t c=0;c<3;++c) {
                    // Changing reflection strength replaces A*F*W by A*F*R.
                    // Only the removed native W term is attenuated by q.
                    const double expected=(actorObjectUnshadowed[p+c]-actorBaseUnshadowed[p+c])+(1-q)*a*f*softNativeWater[p+c];
                    actorReflectionCorrect &= std::abs((actorObjectShadowed[p+c]-actorBaseShadowed[p+c])-expected)<=3;
                    ++actorReflectionChecks;
                }
            }
            require(actorReflectionCorrect&&actorReflectionChecks>300,"Actor water overlay attenuated the independent scenery/actor reflection term");

            // A bright constant native celestial layer provides an independent
            // environment term at grazing incidence. It must be composed after
            // surface attenuation, even with zero native water alpha.
            for(uint32_t v=8;v<12;++v)world[v][2]-=20;rebuildPositions();
            reflection.sceneOptions[3]=0;reflection.camera[1]=1;reflection.camera[2]=0;
            reflection.celestialProjection[0][1]=32;reflection.celestialProjection[1][1]=32;reflection.celestialProjection[2][1]=1;
            reflection.celestialInfo[0]=1;for(size_t i=2048;i<2064;++i)packCelestialAlpha(i,255);
            reflection.celestial[0]=celestialRecord(-100000,-100000,100000,100000,.9f,.8f,.2f,1,2048,4);
            require(pipelines.prepare(device.get(),layout.get(),ms,false,true),"Actor sky composition PSO failed");
            size_t softSkyChecks=0;bool softSkyCorrect=true;
            for(uint8_t alpha:{uint8_t(0),uint8_t(179),uint8_t(255)}) {
                setNativeWaterAlpha(alpha);reflection.shadowOptions[0]=1;reflection.strength=0;
                const auto attenuatedNative=render(1,0);reflection.strength=1;const auto actorSky=render(1,0);
                const auto actorSkyCoverage=render(1,3),directActorSky=render(1,4);
                for(uint32_t y=2;y<62;++y)for(uint32_t x=2;x<62;++x) {
                    const size_t p=(y*Width+x)*4;if(actorSkyCoverage[p+1]!=166||actorSkyCoverage[p+2]!=255)continue;
                    const double px=(x+.5)*40/Width-20,pz=20-(y+.5)*40/Height;
                    const double nv=1/std::sqrt(px*px+1+pz*pz),ior=(1.333-1)/(1.333+1),f=ior*ior+(1-ior*ior)*std::pow(1-nv,5);
                    for(uint32_t c=0;c<3;++c) {
                        softSkyCorrect &= std::abs(actorSky[p+c]-((1-f)*attenuatedNative[p+c]+f*directActorSky[p+c]))<=2;
                        ++softSkyChecks;
                    }
                }
            }
            require(softSkyCorrect&&softSkyChecks>20000,"Actor overlay darkened the reflected native sky or used the wrong alpha composition");
            std::printf("%ux MSAA soft actors: deterministic/bounds/translation/permission guards, scenery%zu, reflection%zu sky%zu; prior hard baselines retained.\n",samples,hardSceneryPixels,actorReflectionChecks,softSkyChecks);
            captureActorReadbacks = false;
            pipelineOverride=nullptr;prepassPipeline=nullptr;clearDestination=RenderColor(0,0,0,0);reflection=softStart;
            std::memcpy(params,softSavedParams,sizeof(params));std::memcpy(rdp,softSavedRdp,sizeof(rdp));std::memcpy(renderIndices,softSavedIndices,sizeof(renderIndices));
            std::memcpy(world,savedWorld,sizeof(world));std::memcpy(screen,savedScreen,sizeof(screen));std::memcpy(uv,savedUV,sizeof(uv));std::memcpy(colors,savedColors,sizeof(colors));std::memcpy(indices,savedIndices,sizeof(indices));
            fill(renderParamsBuffer,params,sizeof(params));fill(rdpParamsBuffer,rdp,sizeof(rdp));fill(renderIndicesBuffer,renderIndices,sizeof(renderIndices));
            fill(screenBuffer,screen,sizeof(screen));fill(uvBuffer,uv,sizeof(uv));fill(colorBuffer,colors,sizeof(colors));
            common.setBuffer(common.RDPTiles,rdpTileBuffer,sizeof(rdpTile),RenderBufferStructuredView(sizeof(rdpTile)));
            common.setBuffer(common.GPUTiles,gpuTileBuffer,sizeof(gpuTile),RenderBufferStructuredView(sizeof(gpuTile)));
            textures.setTexture(1,skyTexture.get(),RenderTextureLayout::SHADER_READ,skyTextureView.get());
            prepareBeamScene({{6,3,1,0}});require(pipelines.prepare(device.get(),layout.get(),ms,false),"Soft actor fixture could not restore stable PSO");
            require(render(1,0)==reflected&&render(0,0)==original,"Soft actor fixture failed to restore stable reflection/native output");

            if (aoExperiment) {
            // Short-range AO is tested against analytic intersections of the
            // independently generated cosine hemisphere with an overhead card.
            // The receiver and blocker share the actual scene producer/AS;
            // native alpha holes are sampled at each candidate, not a mask
            // pasted over the already rendered image.
            const auto aoStart=reflection;
            interop::RenderParams aoSavedParams[4];interop::RDPParams aoSavedRdp[4];
            interop::RenderIndices aoSavedIndices[4];
            std::memcpy(aoSavedParams,params,sizeof(params));std::memcpy(aoSavedRdp,rdp,sizeof(rdp));
            std::memcpy(aoSavedIndices,renderIndices,sizeof(renderIndices));
            softQuad(0,-20,20,0,-20,20);softQuad(8,-6,6,5,-6,6);
            const uint32_t aoFaces[12]={0,1,2,0,2,3,8,9,10,8,10,11};
            std::memcpy(indices,aoFaces,sizeof(aoFaces));
            params[0]=primitiveSkyParams;params[0].omL=0;params[0].omH=0x00082cff;
            params[0].flags.sampleCount=samples==1?0:2;
            renderIndices[0].instanceIndex=0;renderIndices[0].faceIndicesStart=0;
            renderIndices[0].rdpTileIndex=0;renderIndices[0].rdpTileCount=0;
            renderIndices[2].instanceIndex=2;renderIndices[2].faceIndicesStart=6;
            renderIndices[2].rdpTileIndex=0;renderIndices[2].rdpTileCount=1;
            rdp[0].primColor=hlslpp::float4(.7f,.45f,.2f,1);
            configureCutout(0);
            for(uint32_t v=0;v<4;++v) {
                uv[8+v][0]=(v==1||v==2)?31.75f:.25f;
                uv[8+v][1]=v>=2?31.75f:.25f;
                colors[8+v][3]=1;
                colors[v][3]=0;
            }
            common.setBuffer(common.RDPTiles,upload(&cutoutTile,sizeof(cutoutTile),RenderBufferFlag::STORAGE),sizeof(cutoutTile),RenderBufferStructuredView(sizeof(cutoutTile)));
            common.setBuffer(common.GPUTiles,upload(&cutoutGpuTile,sizeof(cutoutGpuTile),RenderBufferFlag::STORAGE),sizeof(cutoutGpuTile),RenderBufferStructuredView(sizeof(cutoutGpuTile)));
            textures.setTexture(0,cutoutTexture.get(),RenderTextureLayout::SHADER_READ,cutoutView.get());
            fill(screenBuffer,screen,sizeof(screen));fill(uvBuffer,uv,sizeof(uv));fill(colorBuffer,colors,sizeof(colors));
            fill(renderParamsBuffer,params,sizeof(params));fill(rdpParamsBuffer,rdp,sizeof(rdp));fill(renderIndicesBuffer,renderIndices,sizeof(renderIndices));
            reflection=Params{};reflection.camera[1]=40;reflection.camera[2]=0;reflection.strength=0;
            reflection.aoOptions[0]=1;reflection.aoOptions[1]=24;reflection.aoOptions[2]=.12f;reflection.aoOptions[3]=.5f;
            reflection.shadowLight[1]=1;reflection.shadowLight[3]=.55f;
            reflection.shadowOptions[1]=.5f;reflection.shadowOptions[2]=100;
            pipelineOverride=worldPipelines.get(false,false,false,false,true,true);
            clearDestination=RenderColor(.11f,.23f,.37f,0);
            auto prepareAO=[&](uint32_t flags,bool sameDraw=false,bool include=true) {
                std::vector<Wr64RTSceneGeometry> geometry={{0,6,0,1}};
                if(include)geometry.push_back({6,6,sameDraw?0u:2u,flags});
                prepareBeamScene(geometry);
            };
            auto analyticAO=[&](uint32_t x,uint32_t y,bool holes) {
                const double px=(x+.5)*40/Width-20,pz=20-(y+.5)*40/Height;
                uint32_t hits=0;
                for(uint32_t k=0;k<8;++k) {
                    const double r=std::sqrt((k+.5)/8.0),angle=k*3.14159265358979323846*(3-std::sqrt(5.0));
                    const double dy=std::sqrt(1-r*r),t=4.5/dy;
                    const double hx=px+t*r*std::cos(angle),hz=pz-t*r*std::sin(angle);
                    if(t<.5||t>24||hx< -6||hx>6||hz< -6||hz>6)continue;
                    if(holes) {
                        const double u=.25+(hx+6)*31.5/12,v=.25+(6-hz)*31.5/12;
                        const int tx=std::clamp(int(std::floor(std::round(u*128)/128)),0,31);
                        const int ty=std::clamp(int(std::floor(std::round(v*128)/128)),0,31);
                        if(((tx/4+ty/4)%2)==0)continue;
                    }
                    ++hits;
                }
                return hits/8.0;
            };
            prepareAO(1);const auto aoNative=render(0,0),aoSolid=render(1,0),aoSolidMask=render(1,6);
            require(render(1,0)==aoSolid&&render(1,6)==aoSolidMask,"AO samples changed between identical frames");
            size_t aoCompared=0,aoFractional=0,aoClear=0,aoCutoutHoles=0;int aoMaskError=0,aoColorError=0;
            bool aoCorrect=true;
            for(bool holes:{false,true}) {
                prepareAO(holes?3u:1u);const auto ambient=render(1,0),mask=render(1,6);
                for(uint32_t y=2;y<62;++y)for(uint32_t x=2;x<62;++x) {
                    const size_t p=(y*Width+x)*4;const double coverage=analyticAO(x,y,holes);
                    const double q=1-.12*coverage;
                    const int maskError=int(std::ceil(std::abs(mask[p]-255*(1-coverage))));
                    aoMaskError=std::max(aoMaskError,maskError);aoCorrect &= maskError<=1;
                    for(uint32_t c=0;c<3;++c) {
                        const int error=int(std::ceil(std::abs(ambient[p+c]-q*aoNative[p+c])));
                        aoColorError=std::max(aoColorError,error);aoCorrect &= error<=2;
                    }
                    aoCorrect &= ambient[p+3]==aoNative[p+3];++aoCompared;
                    if(!holes){aoFractional+=coverage>0&&coverage<1;aoClear+=coverage==0;}
                    else aoCutoutHoles+=coverage<analyticAO(x,y,false);
                }
            }
            std::printf("%ux MSAA AO oracle: pixels%zu fractional%zu clear%zu cutout-holes%zu mask-error%d color-error%d.\n",samples,aoCompared,aoFractional,aoClear,aoCutoutHoles,aoMaskError,aoColorError);
            require(aoCorrect&&aoFractional>500&&aoClear>500&&aoCutoutHoles>400,"AO failed independent hemisphere/native-cutout coverage or modified native alpha");
            prepareAO(1,true);require(render(1,6)==aoSolidMask,"AO excluded another physical face belonging to the receiving draw");
            prepareAO(1,false,false);require(render(1,0)==aoNative,"Isolated native receiver self-occluded");
            for(uint32_t excluded:{0u,2u,5u,9u,16u}) {
                prepareAO(excluded);require(render(1,0)==aoNative,"AO admitted a noncaster, beam or private fence approximation");
            }
            // Exercise the actual private proxy stream too: flag8 passed as
            // ordinary geometry above is rejected by the scene producer.
            Wr64RTFenceProxy aoProxy;aoProxy.drawIndex=2;
            for(uint32_t index:{8u,9u,10u,8u,10u,11u}) {
                Wr64RTFenceVertex vertex;
                std::copy(world[index],world[index]+4,vertex.position.begin());
                vertex.uv={4.5f,.5f};vertex.shade={1,1,1,1};aoProxy.triangles.push_back(vertex);
            }
            require(scene.prepare(device.get(),positions.get(),faces.get(),16,54,{{0,6,0,1}},{aoProxy}),"Could not prepare AO private-proxy control");
            common.setAccelerationStructure(common.SceneBVH,scene.accelerationStructure());
            common.setBuffer(common.wr64FenceProxy,scene.proxyBuffer(),scene.proxyBufferSize());
            common.setBuffer(common.interleavedRasters,scene.geometryBuffer(),scene.geometryBufferSize(),RenderBufferStructuredView(16));
            refreshFixtureIndices();
            require(render(1,0)==aoNative,"AO shader treated private fence approximation as ambient solid geometry");
            reflection.shadowOptions[0]=1;
            require(center(render(1,5))[0]==0,"Private AO-exclusion control did not cast its directional shadow");
            reflection.shadowOptions[0]=0;
            prepareAO(1);const auto validAO=reflection;
            for(uint32_t invalid=0;invalid<8;++invalid) {
                reflection=validAO;
                if(invalid==0)reflection.aoOptions[0]=0;
                if(invalid==1)reflection.aoOptions[0]=2;
                if(invalid==2)reflection.aoOptions[1]=0;
                if(invalid==3)reflection.aoOptions[1]=129;
                if(invalid==4)reflection.aoOptions[2]=0;
                if(invalid==5)reflection.aoOptions[3]=0;
                if(invalid==6)reflection.aoOptions[1]=std::numeric_limits<float>::quiet_NaN();
                if(invalid==7)reflection.aoOptions[3]=std::numeric_limits<float>::infinity();
                require(render(1,0)==aoNative,"Disabled/invalid AO changed native output");
            }
            reflection=validAO;reflection.aoOptions[1]=4;
            require(render(1,0)==aoNative,"AO hit beyond the configured local radius");
            reflection=validAO;reflection.aoOptions[2]=.2f;const auto cappedAO=render(1,0);
            reflection.aoOptions[2]=1;require(render(1,0)==cappedAO,"AO exceeded its bounded attenuation cap");
            softQuad(8,-100,100,5,-100,100);prepareAO(1);
            require(center(render(1,6))[0]==0,"Overhead AO control did not cover all hemisphere rays");
            const auto fullyOccludedAO=center(render(1,0)),fullyLitAO=center(aoNative);
            for(uint32_t c=0;c<3;++c)require(std::abs(fullyOccludedAO[c]-.8*fullyLitAO[c])<=2,"Fully occluded AO exceeded its .2 attenuation limit");
            softQuad(8,-6,6,5,-6,6);prepareAO(1);
            reflection=validAO;reflection.shadowLight[1]=-1;
            require(render(1,6)==aoSolidMask,"AO hemisphere changed with the directional light instead of receiver orientation");
            reflection=validAO;
            size_t aoFogChecks=0;bool aoFogCorrect=true;
            for(uint32_t fogMode=0;fogMode<4;++fogMode) {
                const float amount=fogMode==1?.4f:fogMode==2?1.f:0.f;
                params[0].omL=fogMode==3?0x005049d8:0xc8112078;
                params[0].omH=fogMode==3?0x00082cff:0x00182cff;
                rdp[0].fogColor=hlslpp::float4(.12f,.35f,.8f,1);
                for(uint32_t v=0;v<4;++v)colors[v][3]=amount;
                fill(renderParamsBuffer,params,sizeof(params));fill(rdpParamsBuffer,rdp,sizeof(rdp));fill(colorBuffer,colors,sizeof(colors));
                reflection.shadowOptions[0]=1;
                const auto nativeFog=render(0,0),combined=render(1,0);
                if(fogMode>=2) {require(combined==nativeFog,"AO/shadow modified fully fogged or unsupported native blender");continue;}
                const float fog[3]={.12f,.35f,.8f};
                for(uint32_t y=2;y<62;++y)for(uint32_t x=2;x<62;++x) {
                    const size_t p=(y*Width+x)*4;const double px=(x+.5)*40/Width-20,pz=20-(y+.5)*40/Height;
                    const double q=(std::abs(px)<6&&std::abs(pz)<6?.45:1)*(1-.12*analyticAO(x,y,false));
                    for(uint32_t c=0;c<3;++c)aoFogCorrect &= std::abs(combined[p+c]-(q*nativeFog[p+c]+(1-q)*amount*fog[c]*255))<=2;
                    aoFogCorrect &= combined[p+3]==nativeFog[p+3];++aoFogChecks;
                }
            }
            require(aoFogCorrect&&aoFogChecks==7200,"Combined AO/shadows altered native fog, alpha or bounded transmission");
            // The broader receiver set includes native rider/craft materials,
            // but must not acquire the shore directional-shadow policy. Use
            // exact archived combiner/mode signatures on the existing real AS
            // fixture, with nonzero visible texture/shade and an overhead hit.
            size_t aoOnlyVisible=0,aoOnlyShadowDifference=0;
            for(uint32_t actorMaterial=0;actorMaterial<2;++actorMaterial) {
                params[0]=textureSkyParams;
                params[0].flags.sampleCount=samples==1?0:2;
                params[0].ccL=actorMaterial?0xFC127FFFu:0xFC127E24u;
                params[0].ccH=actorMaterial?0xFFFFF238u:0xFFFFF3F9u;
                params[0].omL=actorMaterial?0xC8112078u:0x00552078u;
                params[0].omH=actorMaterial?0x0018ACFFu:0x0008ACFFu;
                renderIndices[0].rdpTileCount=1;
                rdp[0].primColor=hlslpp::float4(1,1,1,0);
                rdp[0].envColor=hlslpp::float4(.6f,.8f,1,.7f);
                rdp[0].fogColor=hlslpp::float4(.12f,.35f,.8f,1);
                for(uint32_t v=0;v<4;++v) {
                    uv[v][0]=4.5f;uv[v][1]=.5f;
                    colors[v][0]=.7f;colors[v][1]=.45f;colors[v][2]=.2f;colors[v][3]=actorMaterial?.4f:1.f;
                }
                fill(renderParamsBuffer,params,sizeof(params));fill(rdpParamsBuffer,rdp,sizeof(rdp));
                fill(renderIndicesBuffer,renderIndices,sizeof(renderIndices));fill(uvBuffer,uv,sizeof(uv));fill(colorBuffer,colors,sizeof(colors));
                reflection=validAO;reflection.shadowOptions[0]=1;
                push.padding.x=0;const auto nativeActor=render(0,0),shoreActor=render(1,0);
                push.padding.x=WR64_AO_ONLY_RECEIVER;const auto ambientActor=render(1,0);
                reflection.shadowOptions[0]=0;
                require(render(1,0)==ambientActor,"AO-only actor inherited directional shadows");
                reflection.shadowOptions[0]=1;
                require(render(1,5)==nativeActor,"AO-only actor inherited directional-shadow debug rendering");
                reflection.aoOptions[0]=0;
                require(render(1,0)==nativeActor,"Disabled AO altered an AO-only native actor material");
                reflection=validAO;
                require(render(1,6)==aoSolidMask,"AO-only actor did not retain actual ambient ray coverage");
                for(uint32_t y=2;y<62;++y)for(uint32_t x=2;x<62;++x) {
                    const size_t p=(y*Width+x)*4;
                    aoOnlyVisible+=ambientActor[p]<nativeActor[p];
                    aoOnlyShadowDifference+=ambientActor[p]>shoreActor[p]+8;
                    require(ambientActor[p+3]==nativeActor[p+3],"AO-only actor changed native framebuffer alpha/coverage");
                }
            }
            push.padding.x=0;
            require(aoOnlyVisible>500&&aoOnlyShadowDifference>300,"Native actor AO-only fixture has no positive ambient/directional distinction");
            std::printf("%ux MSAA native actor AO-only: ambient pixels%zu, avoided shore-shadow pixels%zu; disabled/native-alpha/debug policy preserved.\n",samples,aoOnlyVisible,aoOnlyShadowDifference);
            std::printf("%ux MSAA AO: fog/product%zu, native self/other-face, ray flags, radius, invalid, repeated-frame and strength guards passed.\n",samples,aoFogChecks);
            pipelineOverride=nullptr;clearDestination=RenderColor(0,0,0,0);reflection=aoStart;
            std::memcpy(params,aoSavedParams,sizeof(params));std::memcpy(rdp,aoSavedRdp,sizeof(rdp));std::memcpy(renderIndices,aoSavedIndices,sizeof(renderIndices));
            std::memcpy(world,savedWorld,sizeof(world));std::memcpy(screen,savedScreen,sizeof(screen));std::memcpy(uv,savedUV,sizeof(uv));std::memcpy(colors,savedColors,sizeof(colors));std::memcpy(indices,savedIndices,sizeof(indices));
            fill(renderParamsBuffer,params,sizeof(params));fill(rdpParamsBuffer,rdp,sizeof(rdp));fill(renderIndicesBuffer,renderIndices,sizeof(renderIndices));
            fill(screenBuffer,screen,sizeof(screen));fill(uvBuffer,uv,sizeof(uv));fill(colorBuffer,colors,sizeof(colors));
            common.setBuffer(common.RDPTiles,rdpTileBuffer,sizeof(rdpTile),RenderBufferStructuredView(sizeof(rdpTile)));
            common.setBuffer(common.GPUTiles,gpuTileBuffer,sizeof(gpuTile),RenderBufferStructuredView(sizeof(gpuTile)));
            textures.setTexture(0,skyTexture.get(),RenderTextureLayout::SHADER_READ,skyTextureView.get());
            textures.setTexture(1,skyTexture.get(),RenderTextureLayout::SHADER_READ,skyTextureView.get());prepareBeamScene({{6,3,1,0}});
            reflection.aoOptions[0]=1;reflection.aoOptions[1]=24;reflection.aoOptions[2]=.12f;reflection.aoOptions[3]=.5f;
            require(render(1,0)==reflected&&render(0,0)==original,"AO leaked into native water or reflected radiance");
            reflection=aoStart;
            }
        }
        }
        if (validateVulkan) require(validation.errors.load() == 0, "Vulkan validation reported an error during GPU resource teardown");
        if (selected("--sky-methods-only")) {
            std::printf("PASS: %zu sky-method checks; cached sky plus RT objects, RT sky-only, independent strength and two capture/view states at 1x/4x MSAA.\n",checks);
            return 0;
        }
        if (selected("--southern-ramp-only")) {
            std::printf("PASS: %zu Southern Island native ramp shadow reproduction checks at 1x/4x MSAA.\n",checks);
            return 0;
        }
        if (selected("--planar-ray-sky-only")) {
            std::printf("PASS: %zu planar reflection/RT sky combination checks at 1x/4x MSAA.\n", checks);
            return 0;
        }
        if (selected("--solid-self-only")) {
            std::printf("PASS: %zu checks; native rider/craft/scenery solid receivers, same-draw self shadows, close gaps, stable geometric normals and native fog/coverage at 1x/4x MSAA.\n",checks);
            return 0;
        }
        if (selected("--two-player-only")) {
            std::printf("PASS: %zu checks; two independent D3D12 RT views, 1x/4x MSAA, horizontal/vertical splits, native per-view fallback and repeated single submissions.\n", checks);
            return 0;
        }
        if (lifecycle) std::puts("PASS: same-device 4x -> 1x -> 4x lifecycle, production prewarm and reset-before-layout-replacement completed.");
        if (rspCompute) std::puts("PASS: production RSPWorldCS compute -> AS -> ray-query raster first activation and moving-input checks completed.");
        if (rspCompute || combinedSky) std::printf("PASS: %zu checks; Vulkan %s fixture. Vulkan validation errors=%u warnings=%u.\n",
            checks, combinedSky ? "combined opening sky" : "RSP compute", validation.errors.load(), validation.warnings.load());
        else std::printf("PASS: %zu checks; %s production reflections, shared normals, native sky/celestial composition and isolated inset previews at 1x/4x MSAA. Vulkan validation errors=%u warnings=%u.\n",
            checks, vulkan ? "Vulkan" : "D3D12", validation.errors.load(), validation.warnings.load());
        return 0;
    }
    catch (const std::exception &error) {
        std::fprintf(stderr, "FAIL after %zu checks: %s\n", checks, error.what());
        return 1;
    }
}
