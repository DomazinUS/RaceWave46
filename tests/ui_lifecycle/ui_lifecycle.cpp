// Headless production UI renderer lifecycle. No SDL window, swapchain, ROM,
// game thread, input injection, or configuration writes are involved.
#define SDL_MAIN_HANDLED
#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <stdexcept>
#include <unordered_set>
#include <vector>
#include "plume_d3d12.h"
#include "plume_vulkan.h"
#ifdef interface
#undef interface
#endif
#include "ui_renderer.h"
#include "RmlUi/Core.h"

using namespace plume;
static size_t checks = 0;
static void require(bool value, const char* message) {
    ++checks;
    if (!value) {
        // A failed check must not unwind retained renderer state after its
        // device owner: keep the first failure visible, then exit this probe.
        std::fprintf(stderr, "FAIL: %s\n", message);
        std::_Exit(1);
    }
}

struct HeadlessSystem final : Rml::SystemInterface {
    double GetElapsedTime() override { return 1.0; }
    bool LogMessage(Rml::Log::Type type, const Rml::String& message) override {
        std::fprintf(stderr, "RML %d: %s\n", int(type), message.c_str());
        return true;
    }
};

// Count actual Rml calls while forwarding all work to the unchanged production
// compatibility adapter. The retained context uses this stable observer.
struct ObservedRenderer final : Rml::RenderInterface {
    Rml::RenderInterface* target = nullptr;
    size_t compiled = 0, releasedGeometry = 0, loaded = 0, generated = 0, releasedTextures = 0;
    std::unordered_set<Rml::CompiledGeometryHandle> geometry;
    std::unordered_set<Rml::TextureHandle> textures;
    Rml::CompiledGeometryHandle CompileGeometry(Rml::Span<const Rml::Vertex> v, Rml::Span<const int> i) override {
        auto handle = target->CompileGeometry(v, i);
        require(handle != 0 && geometry.insert(handle).second, "Geometry handle must be new and valid");
        ++compiled;
        return handle;
    }
    void RenderGeometry(Rml::CompiledGeometryHandle handle, Rml::Vector2f translation, Rml::TextureHandle texture) override {
        require(geometry.contains(handle), "Rendered released geometry after rebind");
        require(texture == 0 || textures.contains(texture), "Rendered released texture after rebind");
        target->RenderGeometry(handle, translation, texture);
    }
    void ReleaseGeometry(Rml::CompiledGeometryHandle handle) override {
        require(geometry.erase(handle) == 1, "Geometry released twice");
        target->ReleaseGeometry(handle);
        ++releasedGeometry;
    }
    Rml::TextureHandle LoadTexture(Rml::Vector2i& dimensions, const Rml::String& source) override {
        auto handle = target->LoadTexture(dimensions, source);
        require(handle > 1 && textures.insert(handle).second, "File/virtual texture must load as a real GPU texture");
        ++loaded;
        return handle;
    }
    Rml::TextureHandle GenerateTexture(Rml::Span<const Rml::byte> pixels, Rml::Vector2i dimensions) override {
        auto handle = target->GenerateTexture(pixels, dimensions);
        require(handle > 1 && textures.insert(handle).second, "Generated font texture must be valid");
        ++generated;
        return handle;
    }
    void ReleaseTexture(Rml::TextureHandle texture) override {
        require(textures.erase(texture) == 1, "Texture released twice");
        target->ReleaseTexture(texture);
        ++releasedTextures;
    }
    void EnableScissorRegion(bool enable) override { target->EnableScissorRegion(enable); }
    void SetScissorRegion(Rml::Rectanglei region) override { target->SetScissorRegion(region); }
    void SetTransform(const Rml::Matrix4f* transform) override { target->SetTransform(transform); }
};

struct Validation {
    VkInstance instance = VK_NULL_HANDLE;
    VkDebugUtilsMessengerEXT messenger = VK_NULL_HANDLE;
    std::atomic_uint errors{0}, warnings{0};
    static VKAPI_ATTR VkBool32 VKAPI_CALL callback(VkDebugUtilsMessageSeverityFlagBitsEXT severity,
        VkDebugUtilsMessageTypeFlagsEXT, const VkDebugUtilsMessengerCallbackDataEXT* message, void* data) {
        auto& self = *static_cast<Validation*>(data);
        if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) ++self.errors;
        else if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) ++self.warnings;
        std::fprintf(stderr, "VULKAN VALIDATION: %s\n", message->pMessage);
        return VK_FALSE;
    }
    void install(VkInstance selected) {
        require(vkCreateDebugUtilsMessengerEXT && vkDestroyDebugUtilsMessengerEXT, "Validation messenger unavailable");
        instance = selected;
        VkDebugUtilsMessengerCreateInfoEXT info{VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT};
        info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        info.pfnUserCallback = callback;
        info.pUserData = this;
        require(vkCreateDebugUtilsMessengerEXT(instance, &info, nullptr, &messenger) == VK_SUCCESS, "Validation messenger creation failed");
    }
    ~Validation() { if (messenger) vkDestroyDebugUtilsMessengerEXT(instance, messenger, nullptr); }
};

static std::vector<unsigned char> draw(recompui::RmlRenderInterface_RT64& renderer, Rml::Context* context,
    RenderDevice* device, bool vulkan) {
    constexpr unsigned width = 128, height = 128;
    auto queue = device->createCommandQueue(RenderCommandListType::DIRECT);
    auto commands = queue->createCommandList();
    auto fence = device->createCommandFence();
    auto target = device->createTexture(RenderTextureDesc::ColorTarget(width, height, RenderFormat::B8G8R8A8_UNORM));
    const RenderTexture* attachment = target.get();
    auto framebuffer = device->createFramebuffer(RenderFramebufferDesc(&attachment, 1));
    auto readback = device->createBuffer(RenderBufferDesc::ReadbackBuffer(width * height * 4));
    commands->begin();
    commands->barriers(RenderBarrierStage::GRAPHICS, RenderTextureBarrier(target.get(), RenderTextureLayout::COLOR_WRITE));
    commands->setFramebuffer(framebuffer.get());
    commands->clearColor(0, RenderColor(0, 0, 0, 1));
    renderer.start(commands.get(), width, height);
    context->Update();
    context->Render();
    renderer.end(commands.get(), framebuffer.get());
    commands->barriers(RenderBarrierStage::COPY, RenderTextureBarrier(target.get(), RenderTextureLayout::COPY_SOURCE));
    // The abstraction has no Vulkan image-to-buffer branch. Native readback
    // follows its normal production resource transition on either backend.
    if (vulkan) {
        auto* native = static_cast<VulkanCommandList*>(commands.get());
        native->endActiveRenderPass();
        VkBufferImageCopy copy{};
        copy.bufferRowLength = width;
        copy.bufferImageHeight = height;
        copy.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        copy.imageSubresource.layerCount = 1;
        copy.imageExtent = {width, height, 1};
        vkCmdCopyImageToBuffer(native->vk, static_cast<VulkanTexture*>(target.get())->vk,
            VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, static_cast<VulkanBuffer*>(readback.get())->vk, 1, &copy);
    } else {
        D3D12_TEXTURE_COPY_LOCATION dst{}, src{};
        dst.pResource = static_cast<D3D12Buffer*>(readback.get())->d3d;
        dst.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
        dst.PlacedFootprint.Footprint = {DXGI_FORMAT_B8G8R8A8_UNORM, width, height, 1, width * 4};
        src.pResource = static_cast<D3D12Texture*>(target.get())->d3d;
        src.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
        static_cast<D3D12CommandList*>(commands.get())->d3d->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);
    }
    commands->end();
    queue->executeCommandLists(commands.get(), fence.get());
    queue->waitForCommandFence(fence.get());
    std::vector<unsigned char> pixels(width * height * 4);
    const RenderRange read(0, pixels.size());
    const void* mapped = readback->map(0, &read);
    require(mapped != nullptr, "UI readback mapping failed");
    std::memcpy(pixels.data(), mapped, pixels.size());
    const RenderRange noWrite(0, 0);
    readback->unmap(0, &noWrite);
    return pixels;
}

int main(int argc, char** argv) {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    try {
        require(argc >= 2, "Pass the repository font path");
        const bool validationEnabled = argc >= 3 && std::strcmp(argv[2], "--validation") == 0;
        HeadlessSystem system;
        recompui::RmlRenderInterface_RT64 renderer;
        ObservedRenderer observer;
        Rml::Context* context = nullptr;
        Rml::ElementDocument* document = nullptr;
        Rml::Element* retained = nullptr;
        std::vector<unsigned char> original;
        for (unsigned phase = 0; phase < 3; ++phase) {
            const bool vulkan = phase == 1;
            std::unique_ptr<RenderInterface> interface;
            if (vulkan) {
                auto instance = std::make_unique<VulkanInterface>();
                require(instance->isValid(), "Vulkan interface failed");
                interface = std::move(instance);
            } else {
                auto instance = std::make_unique<D3D12Interface>();
                require(instance->isValid(), "D3D12 interface failed");
                interface = std::move(instance);
            }
            Validation validation;
            if (vulkan && validationEnabled) validation.install(static_cast<VulkanInterface*>(interface.get())->instance);
            auto device = interface->createDevice("");
            require(device != nullptr, "UI lifecycle device creation failed");
            std::printf("UI lifecycle phase %u backend=%s device=%s\n", phase, vulkan ? "Vulkan" : "D3D12", device->getDescription().name.c_str());
            const auto compiledBefore = observer.compiled, loadedBefore = observer.loaded, generatedBefore = observer.generated;
            if (phase == 0) {
                renderer.init(interface.get(), device.get());
                observer.target = renderer.get_rml_interface();
                Rml::SetSystemInterface(&system);
                Rml::SetRenderInterface(&observer);
                require(Rml::Initialise(), "Rml initialization failed");
                require(Rml::LoadFontFace(argv[1]), "Fixture font failed to load");
                std::vector<char> rgba(4 * 4 * 4);
                for (unsigned p = 0; p < 16; ++p) {
                    rgba[p * 4] = char(240); rgba[p * 4 + 1] = char(80); rgba[p * 4 + 2] = char(32); rgba[p * 4 + 3] = char(255);
                }
                renderer.queue_image_from_bytes_rgba32("?/lifecycle.rgba", rgba, 4, 4);
                context = Rml::CreateContext("retained-ui", {128, 128});
                require(context != nullptr, "Retained context creation failed");
                document = context->LoadDocumentFromMemory(R"(<rml><head><style>
                    body { margin: 0; width: 128px; height: 128px; background: #164080; font-family: LatoLatin; font-size: 18px; color: white; }
                    #logo { position: absolute; left: 8px; top: 8px; width: 40px; height: 40px; }
                    #state { position: absolute; left: 8px; top: 62px; }
                    </style></head><body><img id="logo" src="?/lifecycle.rgba"/><div id="state">RC TEST</div></body></rml>)");
                require(document != nullptr, "Retained document failed to load");
                retained = document->GetElementById("state");
                require(retained != nullptr, "Retained element missing");
                retained->SetAttribute("selection", "keep-this");
                document->Show();
            } else {
                renderer.rebind_device(interface.get(), device.get());
                require(renderer.get_rml_interface() == observer.target, "Production Rml adapter identity changed during rebind");
                require(Rml::GetContext("retained-ui") == context, "Rml context was recreated");
                require(document->GetElementById("state") == retained, "Document element was recreated");
                require(retained->GetAttribute<Rml::String>("selection", "") == "keep-this", "Retained UI selection lost");
            }
            auto pixels = draw(renderer, context, device.get(), vulkan);
            require(observer.compiled > compiledBefore, "Geometry was not recompiled after device replacement");
            require(observer.loaded > loadedBefore, "Retained virtual image was not reloaded");
            require(observer.generated > generatedBefore, "Retained font texture was not regenerated");
            auto pixel = [&](unsigned x, unsigned y) { return pixels.data() + (y * 128 + x) * 4; };
            auto* logo = pixel(24, 24);
            require(logo[0] == 32 && logo[1] == 80 && logo[2] == 240, "Retained logo pixels changed or disappeared");
            auto* background = pixel(112, 112);
            require(background[0] == 128 && background[1] == 64 && background[2] == 22, "UI solid geometry did not render correctly");
            if (phase == 0) original = pixels;
            if (phase == 2) require(pixels == original, "D3D12 round trip must restore identical retained UI pixels");
            const auto cachedCompiled = observer.compiled, cachedLoaded = observer.loaded, cachedGenerated = observer.generated;
            auto cached = draw(renderer, context, device.get(), vulkan);
            require(cached == pixels, "Second frame changed with no UI update");
            require(observer.compiled == cachedCompiled && observer.loaded == cachedLoaded && observer.generated == cachedGenerated,
                "Unchanged second frame unexpectedly rebuilt UI resources");
            Rml::ReleaseCompiledGeometry(&observer);
            Rml::ReleaseTextures(&observer);
            require(observer.geometry.empty(), "Rml retained compiled geometry across device destruction");
            require(observer.textures.empty(), "Rml retained texture handles across device destruction");
            renderer.release_device_resources();
            device.reset();
            require(validation.errors == 0, "Vulkan lifecycle validation reported errors");
            std::printf("UI lifecycle phase %u passed: compiled=%zu released=%zu loaded=%zu generated=%zu releasedTextures=%zu validationWarnings=%u\n",
                phase, observer.compiled, observer.releasedGeometry, observer.loaded, observer.generated, observer.releasedTextures, validation.warnings.load());
        }
        Rml::RemoveContext("retained-ui");
        Rml::Shutdown();
        renderer.reset();
        require(observer.compiled == observer.releasedGeometry, "Compiled geometry leaked at final shutdown");
        require(observer.loaded + observer.generated == observer.releasedTextures, "Textures leaked at final shutdown");
        std::printf("PASS: %zu checks; retained UI D3D12 -> Vulkan -> D3D12, textures/fonts/geometry released and reloaded.\n", checks);
        return 0;
    } catch (const std::exception& error) {
        std::fprintf(stderr, "FAIL: %s\n", error.what());
        return 1;
    }
}
