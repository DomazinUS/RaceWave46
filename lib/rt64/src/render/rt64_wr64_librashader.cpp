#include "rt64_wr64_librashader.h"

#include <algorithm>
#include <cstdio>
#include <mutex>
#include <vector>

#include "common/rt64_wr64_librashader_settings.h"

// Volk must precede librashader.h so Vulkan prototypes stay disabled.
#include "plume_vulkan.h"
#define LIBRA_RUNTIME_VULKAN

#ifdef _WIN32
#   ifndef NOMINMAX
#       define NOMINMAX
#   endif
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN
#   endif
#   include <windows.h>
#   include "plume_d3d12.h"
#   define LIBRA_RUNTIME_D3D12
#else
#   include <dlfcn.h>
#endif

#include "librashader.h"

namespace RT64 {
    namespace {
        struct Library {
            Wr64LibrashaderAvailability availability;
            PFN_libra_preset_create preset_create = nullptr;
            PFN_libra_preset_free preset_free = nullptr;
            PFN_libra_error_write error_write = nullptr;
            PFN_libra_error_free_string error_free_string = nullptr;
            PFN_libra_error_free error_free = nullptr;
            PFN_libra_vk_filter_chain_create_deferred vk_filter_chain_create_deferred = nullptr;
            PFN_libra_vk_filter_chain_frame vk_filter_chain_frame = nullptr;
            PFN_libra_vk_filter_chain_free vk_filter_chain_free = nullptr;
#       ifdef _WIN32
            PFN_libra_d3d12_filter_chain_create_deferred d3d12_filter_chain_create_deferred = nullptr;
            PFN_libra_d3d12_filter_chain_frame d3d12_filter_chain_frame = nullptr;
            PFN_libra_d3d12_filter_chain_free d3d12_filter_chain_free = nullptr;
#       endif
        };

#   ifdef _WIN32
        using LibraryHandle = HMODULE;

        LibraryHandle openLibrary(const std::filesystem::path &path) {
            // Resolve the DLL's own dependencies from its directory, not the working directory.
            const DWORD flags = path.has_parent_path() ? LOAD_WITH_ALTERED_SEARCH_PATH : 0;
            return LoadLibraryExW(path.c_str(), nullptr, flags);
        }

        void *findSymbol(LibraryHandle handle, const char *name) {
            return reinterpret_cast<void *>(GetProcAddress(handle, name));
        }

        const std::vector<std::filesystem::path> libraryCandidates(const std::filesystem::path &programDirectory) {
            return { programDirectory / L"librashader.dll" };
        }
#   else
        using LibraryHandle = void *;

        LibraryHandle openLibrary(const std::filesystem::path &path) {
            return dlopen(path.c_str(), RTLD_NOW | RTLD_LOCAL);
        }

        void *findSymbol(LibraryHandle handle, const char *name) {
            return dlsym(handle, name);
        }

        const std::vector<std::filesystem::path> libraryCandidates(const std::filesystem::path &programDirectory) {
            // Bundled copy first, then a distribution package (SONAME is the ABI version).
            return { programDirectory / "librashader.so", "librashader.so.2", "librashader.so" };
        }
#   endif

        template<typename T>
        bool loadSymbol(LibraryHandle handle, const char *name, T &target) {
            target = reinterpret_cast<T>(findSymbol(handle, name));
            return target != nullptr;
        }

        Library loadLibrary() {
            Library library;
            LibraryHandle handle = nullptr;
            std::filesystem::path loadedPath;
            for (const std::filesystem::path &candidate : libraryCandidates(wr64ProgramDirectory())) {
                handle = openLibrary(candidate);
                if (handle != nullptr) {
                    loadedPath = candidate;
                    break;
                }
            }

            if (handle == nullptr) {
                library.availability.message = "librashader is not installed with the game.";
                return library;
            }

            PFN_libra_instance_abi_version abiVersion = nullptr;
            if (!loadSymbol(handle, "libra_instance_abi_version", abiVersion) || abiVersion() != LIBRASHADER_CURRENT_ABI) {
                library.availability.message = "The installed librashader is incompatible with this game.";
                return library;
            }

            bool complete = loadSymbol(handle, "libra_preset_create", library.preset_create);
            complete &= loadSymbol(handle, "libra_preset_free", library.preset_free);
            complete &= loadSymbol(handle, "libra_error_write", library.error_write);
            complete &= loadSymbol(handle, "libra_error_free_string", library.error_free_string);
            complete &= loadSymbol(handle, "libra_error_free", library.error_free);
            complete &= loadSymbol(handle, "libra_vk_filter_chain_create_deferred", library.vk_filter_chain_create_deferred);
            complete &= loadSymbol(handle, "libra_vk_filter_chain_frame", library.vk_filter_chain_frame);
            complete &= loadSymbol(handle, "libra_vk_filter_chain_free", library.vk_filter_chain_free);
#       ifdef _WIN32
            complete &= loadSymbol(handle, "libra_d3d12_filter_chain_create_deferred", library.d3d12_filter_chain_create_deferred);
            complete &= loadSymbol(handle, "libra_d3d12_filter_chain_frame", library.d3d12_filter_chain_frame);
            complete &= loadSymbol(handle, "libra_d3d12_filter_chain_free", library.d3d12_filter_chain_free);
#       endif
            if (!complete) {
                library.availability.message = "The installed librashader lacks a required graphics runtime.";
                return library;
            }

            // The library stays loaded for the life of the process.
            library.availability.loaded = true;
            const auto path = loadedPath.u8string();
            library.availability.message.assign(path.begin(), path.end());
            return library;
        }

        const Library &library() {
            static const Library instance = loadLibrary();
            return instance;
        }

        std::string takeError(libra_error_t error) {
            if (error == nullptr) return {};
            const Library &lib = library();
            std::string message = "unknown librashader error";
            char *text = nullptr;
            if ((lib.error_write(error, &text) == 0) && (text != nullptr)) {
                message = text;
                lib.error_free_string(&text);
            }

            lib.error_free(&error);
            return message;
        }

        bool apiSupported(UserConfiguration::GraphicsAPI api) {
#       ifdef _WIN32
            if (api == UserConfiguration::GraphicsAPI::D3D12) return true;
#       endif
            return api == UserConfiguration::GraphicsAPI::Vulkan;
        }
    }

    std::filesystem::path wr64ProgramDirectory() {
#   ifdef _WIN32
        std::wstring path(32768, L'\0');
        const DWORD length = GetModuleFileNameW(nullptr, path.data(), DWORD(path.size()));
        if ((length == 0) || (length >= path.size())) return {};
        path.resize(length);
        return std::filesystem::path(path).parent_path();
#   else
        std::error_code error;
        const std::filesystem::path executable = std::filesystem::read_symlink("/proc/self/exe", error);
        return error ? std::filesystem::current_path(error) : executable.parent_path();
#   endif
    }

    const Wr64LibrashaderAvailability &wr64LibrashaderAvailability() {
        return library().availability;
    }

    struct Wr64LibrashaderOutput::Impl {
        RenderDevice *device = nullptr;
        RenderCommandQueue *queue = nullptr;
        UserConfiguration::GraphicsAPI api = UserConfiguration::GraphicsAPI::OptionCount;
        // The preset generation that the chain, or its failure, belongs to.
        uint64_t presetGeneration = 0;
        bool presetResolved = false;
        libra_vk_filter_chain_t vkChain = nullptr;
#   ifdef _WIN32
        libra_d3d12_filter_chain_t d3d12Chain = nullptr;
#   endif
        std::unique_ptr<RenderCommandList> setupCommandList;
        std::unique_ptr<RenderCommandFence> setupFence;
        std::unique_ptr<RenderTexture> texture;
        std::unique_ptr<RenderFramebuffer> framebuffer;
        uint32_t width = 0;
        uint32_t height = 0;
        size_t frameCount = 0;
        bool clearHistory = true;
        // A chain whose frame failed; released once the GPU is done with the recorded frame.
        bool chainFailed = false;

        bool hasChain() const {
            if (chainFailed) return false;
#       ifdef _WIN32
            if (d3d12Chain != nullptr) return true;
#       endif
            return vkChain != nullptr;
        }

        void releaseChain() {
            const Library &lib = library();
            if (vkChain != nullptr) {
                takeError(lib.vk_filter_chain_free(&vkChain));
                vkChain = nullptr;
            }
#       ifdef _WIN32
            if (d3d12Chain != nullptr) {
                takeError(lib.d3d12_filter_chain_free(&d3d12Chain));
                d3d12Chain = nullptr;
            }
#       endif
            chainFailed = false;
        }

        void releaseTexture() {
            framebuffer.reset();
            texture.reset();
            width = 0;
            height = 0;
        }

        void releaseDevice() {
            releaseChain();
            releaseTexture();
            setupCommandList.reset();
            setupFence.reset();
            device = nullptr;
            queue = nullptr;
            api = UserConfiguration::GraphicsAPI::OptionCount;
            presetResolved = false;
        }

        std::string createChain(const std::string &presetPath) {
            const Library &lib = library();
            libra_shader_preset_t preset = nullptr;
            std::string error = takeError(lib.preset_create(presetPath.c_str(), &preset));
            if (!error.empty()) return error;

            if (setupCommandList == nullptr) {
                setupCommandList = queue->createCommandList();
                setupFence = device->createCommandFence();
            }

            // Deferred creation records the LUT uploads here, so only plume submits to the queue.
            setupCommandList->begin();
            if (api == UserConfiguration::GraphicsAPI::Vulkan) {
                VulkanDevice *vulkanDevice = static_cast<VulkanDevice *>(device);
                VulkanCommandQueue *vulkanQueue = static_cast<VulkanCommandQueue *>(queue);
                libra_device_vk_t handles = {};
                handles.physical_device = vulkanDevice->physicalDevice;
                handles.instance = vulkanDevice->renderInterface->instance;
                handles.device = vulkanDevice->vk;
                handles.queue = vulkanQueue->queue->vk;
                handles.entry = vkGetInstanceProcAddr;
                filter_chain_vk_opt_t options = {};
                options.version = LIBRASHADER_CURRENT_VERSION;
                VkCommandBuffer commandBuffer = static_cast<VulkanCommandList *>(setupCommandList.get())->vk;
                error = takeError(lib.vk_filter_chain_create_deferred(&preset, handles, commandBuffer, &options, &vkChain));
            }
#       ifdef _WIN32
            else if (api == UserConfiguration::GraphicsAPI::D3D12) {
                D3D12Device *d3d12Device = static_cast<D3D12Device *>(device);
                filter_chain_d3d12_opt_t options = {};
                options.version = LIBRASHADER_CURRENT_VERSION;
                ID3D12GraphicsCommandList *commandList = static_cast<D3D12CommandList *>(setupCommandList.get())->d3d;
                error = takeError(lib.d3d12_filter_chain_create_deferred(&preset, d3d12Device->d3d, commandList, &options, &d3d12Chain));
            }
#       endif
            setupCommandList->end();
            queue->executeCommandLists(setupCommandList.get(), setupFence.get());
            queue->waitForCommandFence(setupFence.get());

            // Creation consumes the preset; free it only if creation did not take it.
            if (preset != nullptr) {
                takeError(lib.preset_free(&preset));
            }

            if (!error.empty()) {
                releaseChain();
            }

            return error;
        }

        void ensureTexture(uint32_t targetWidth, uint32_t targetHeight) {
            if ((texture != nullptr) && (width == targetWidth) && (height == targetHeight)) return;
            releaseTexture();
            // Matches the VI pipelines' render target format.
            texture = device->createTexture(RenderTextureDesc::ColorTarget(targetWidth, targetHeight, RenderFormat::B8G8R8A8_UNORM));
            texture->setName("WR64 librashader input");
            const RenderTexture *colorAttachment = texture.get();
            framebuffer = device->createFramebuffer(RenderFramebufferDesc(&colorAttachment, 1));
            width = targetWidth;
            height = targetHeight;
            clearHistory = true;
        }
    };

    Wr64LibrashaderOutput::Wr64LibrashaderOutput() : impl(std::make_unique<Impl>()) { }

    Wr64LibrashaderOutput::~Wr64LibrashaderOutput() {
        release();
    }

    bool Wr64LibrashaderOutput::prepare(RenderDevice *device, RenderCommandQueue *queue, UserConfiguration::GraphicsAPI api,
        uint32_t outputWidth, uint32_t outputHeight, uint32_t nativeHeight)
    {
        if (impl->chainFailed) {
            impl->releaseChain();
        }

        const Wr64ShaderSelection selection = getWr64ShaderSelection();
        if (selection.presetPath.empty() || (outputWidth == 0) || (outputHeight == 0)) {
            if ((impl->vkChain != nullptr) || (impl->texture != nullptr)
#           ifdef _WIN32
                || (impl->d3d12Chain != nullptr)
#           endif
            ) {
                impl->releaseChain();
                impl->releaseTexture();
            }

            impl->presetGeneration = selection.presetGeneration;
            impl->presetResolved = true;
            return false;
        }

        if (!wr64LibrashaderAvailability().loaded) {
            if (!impl->presetResolved || (impl->presetGeneration != selection.presetGeneration)) {
                reportWr64ShaderStatus(selection.presetGeneration, true, wr64LibrashaderAvailability().message);
                impl->presetGeneration = selection.presetGeneration;
                impl->presetResolved = true;
            }

            return false;
        }

        if ((impl->device != device) || (impl->queue != queue) || (impl->api != api)) {
            impl->releaseDevice();
            impl->device = device;
            impl->queue = queue;
            impl->api = api;
        }

        if (!apiSupported(api)) {
            if (!impl->presetResolved || (impl->presetGeneration != selection.presetGeneration)) {
                reportWr64ShaderStatus(selection.presetGeneration, true, "librashader is not supported with this graphics API.");
                impl->presetGeneration = selection.presetGeneration;
                impl->presetResolved = true;
            }

            return false;
        }

        if (!impl->presetResolved || (impl->presetGeneration != selection.presetGeneration)) {
            impl->releaseChain();
            impl->presetGeneration = selection.presetGeneration;
            impl->presetResolved = true;
            const std::string error = impl->createChain(selection.presetPath);
            if (!error.empty()) {
                std::fprintf(stderr, "[librashader] could not load %s: %s\n", selection.presetPath.c_str(), error.c_str());
            }

            reportWr64ShaderStatus(selection.presetGeneration, !error.empty(), error);
            impl->clearHistory = true;
        }

        if (!impl->hasChain()) {
            return false;
        }

        uint32_t targetWidth = outputWidth;
        uint32_t targetHeight = outputHeight;
        if (selection.input == Wr64ShaderInput::Native) {
            // Keep the window's aspect ratio so the shader output fills it without distortion.
            targetHeight = (std::min)(outputHeight, (std::max)(nativeHeight, 1U));
            targetWidth = (std::max)(uint32_t((uint64_t(outputWidth) * targetHeight + outputHeight / 2) / outputHeight), 1U);
        }

        impl->ensureTexture(targetWidth, targetHeight);
        return true;
    }

    RenderFramebuffer *Wr64LibrashaderOutput::inputFramebuffer() const {
        return impl->framebuffer.get();
    }

    RenderTexture *Wr64LibrashaderOutput::inputTexture() const {
        return impl->texture.get();
    }

    uint32_t Wr64LibrashaderOutput::inputWidth() const {
        return impl->width;
    }

    uint32_t Wr64LibrashaderOutput::inputHeight() const {
        return impl->height;
    }

    bool Wr64LibrashaderOutput::apply(RenderCommandList *commandList, RenderTexture *output, uint32_t outputWidth, uint32_t outputHeight) {
        if (!impl->hasChain() || (impl->texture == nullptr)) {
            return false;
        }

        const Library &lib = library();
        // librashader records its own passes; none of plume's may be open.
        commandList->setFramebuffer(nullptr);
        commandList->barriers(RenderBarrierStage::GRAPHICS, RenderTextureBarrier(impl->texture.get(), RenderTextureLayout::SHADER_READ));

        const libra_viewport_t viewport = { 0.0f, 0.0f, outputWidth, outputHeight };
        std::string error;
        if (impl->api == UserConfiguration::GraphicsAPI::Vulkan) {
            const VulkanTexture *input = static_cast<const VulkanTexture *>(impl->texture.get());
            const VulkanTexture *target = static_cast<const VulkanTexture *>(output);
            const libra_image_vk_t source = { input->vk, input->imageFormat, impl->width, impl->height };
            // Swap chain images carry their format only in the plume description.
            VkFormat targetFormat = target->imageFormat;
            if (targetFormat == VK_FORMAT_UNDEFINED) {
                targetFormat = (target->desc.format == RenderFormat::R8G8B8A8_UNORM) ? VK_FORMAT_R8G8B8A8_UNORM : VK_FORMAT_B8G8R8A8_UNORM;
            }
            const libra_image_vk_t destination = { target->vk, targetFormat, outputWidth, outputHeight };
            frame_vk_opt_t options = {};
            options.version = LIBRASHADER_CURRENT_VERSION;
            options.clear_history = impl->clearHistory;
            options.frame_direction = 1;
            options.total_subframes = 1;
            options.current_subframe = 1;
            options.brightness_nits = 200.0f;
            VkCommandBuffer commandBuffer = static_cast<VulkanCommandList *>(commandList)->vk;
            error = takeError(lib.vk_filter_chain_frame(&impl->vkChain, commandBuffer, impl->frameCount, source, destination,
                &viewport, nullptr, &options));
        }
#   ifdef _WIN32
        else if (impl->api == UserConfiguration::GraphicsAPI::D3D12) {
            D3D12CommandList *d3d12CommandList = static_cast<D3D12CommandList *>(commandList);
            libra_image_d3d12_t source = {};
            source.image_type = LIBRA_D3D12_IMAGE_TYPE_RESOURCE;
            source.handle.resource = static_cast<D3D12Texture *>(impl->texture.get())->d3d;
            libra_image_d3d12_t destination = {};
            destination.image_type = LIBRA_D3D12_IMAGE_TYPE_RESOURCE;
            destination.handle.resource = static_cast<D3D12Texture *>(output)->d3d;
            frame_d3d12_opt_t options = {};
            options.version = LIBRASHADER_CURRENT_VERSION;
            options.clear_history = impl->clearHistory;
            options.frame_direction = 1;
            options.total_subframes = 1;
            options.current_subframe = 1;
            options.brightness_nits = 200.0f;
            error = takeError(lib.d3d12_filter_chain_frame(&impl->d3d12Chain, d3d12CommandList->d3d, impl->frameCount,
                source, destination, &viewport, nullptr, &options));

            // librashader changed the root signature, pipeline, heaps and topology behind plume's caches.
            d3d12CommandList->notifyDescriptorHeapWasChangedExternally();
            d3d12CommandList->activeGraphicsPipelineLayout = nullptr;
            d3d12CommandList->activeComputePipelineLayout = nullptr;
            d3d12CommandList->activeGraphicsPipeline = nullptr;
            d3d12CommandList->activeTopology = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
        }
#   endif

        // Order the chain's color writes before later overlay drawing into the same image.
        commandList->barriers(RenderBarrierStage::GRAPHICS, RenderTextureBarrier(output, RenderTextureLayout::COLOR_WRITE));

        if (!error.empty()) {
            std::fprintf(stderr, "[librashader] frame failed: %s\n", error.c_str());
            reportWr64ShaderStatus(impl->presetGeneration, true, error);
            impl->chainFailed = true;
            return false;
        }

        impl->frameCount++;
        impl->clearHistory = false;
        return true;
    }

    void Wr64LibrashaderOutput::release() {
        if (impl != nullptr) {
            impl->releaseDevice();
        }
    }
}
