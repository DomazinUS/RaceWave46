// Headless checks for the two native framebuffer compute paths. Uses the
// production embedded SPIR-V and descriptor/push-constant definitions.
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <vector>
#include "plume_vulkan.h"
#include "render/rt64_descriptor_sets.h"
#include "shared/rt64_fb_reinterpret.h"
#include "shared/rt64_f3d_defines.h"
#include "BoxFilterCS.hlsl.spirv.h"
#include "FbReinterpretCS.hlsl.spirv.h"

using namespace plume;
using namespace RT64;
static unsigned checks = 0;
static void require(bool value, const char* message) {
    ++checks;
    if (!value) throw std::runtime_error(message);
}
struct Validation {
    VkInstance instance = VK_NULL_HANDLE;
    VkDebugUtilsMessengerEXT messenger = VK_NULL_HANDLE;
    std::atomic_uint errors{0}, warnings{0};
    static VKAPI_ATTR VkBool32 VKAPI_CALL callback(VkDebugUtilsMessageSeverityFlagBitsEXT severity,
        VkDebugUtilsMessageTypeFlagsEXT, const VkDebugUtilsMessengerCallbackDataEXT* message, void* data) {
        auto& self = *static_cast<Validation*>(data);
        if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) ++self.errors;
        else if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) ++self.warnings;
        std::fprintf(stderr, "VALIDATION: %s\n", message->pMessage);
        return VK_FALSE;
    }
    void install(VkInstance selected) {
        require(vkCreateDebugUtilsMessengerEXT && vkDestroyDebugUtilsMessengerEXT, "Validation unavailable");
        instance = selected;
        VkDebugUtilsMessengerCreateInfoEXT info{VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT};
        info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        info.pfnUserCallback = callback; info.pUserData = this;
        require(vkCreateDebugUtilsMessengerEXT(instance, &info, nullptr, &messenger) == VK_SUCCESS, "Messenger failed");
    }
    ~Validation() { if (messenger) vkDestroyDebugUtilsMessengerEXT(instance, messenger, nullptr); }
};

static void run(RenderDevice* device, bool hdr, bool reinterpretation) {
    const RenderFormat format = hdr ? RenderFormat::R16G16B16A16_UNORM : RenderFormat::R8G8B8A8_UNORM;
    const unsigned componentBytes = hdr ? 2 : 1, scale = hdr ? 257 : 1;
    constexpr unsigned inputWidth = 16, outputWidth = 8, outputHeight = 8;
    // Upload rows follow the production 256-byte alignment convention.
    std::vector<unsigned char> inputBytes(16 * 256, 0);
    auto value = [](unsigned x, unsigned y, unsigned c) { return 16 + ((x * 7 + y * 11 + c * 29) % 220); };
    for (unsigned y = 0; y < 16; ++y) for (unsigned x = 0; x < 16; ++x) for (unsigned c = 0; c < 4; ++c) {
        const uint16_t encoded = uint16_t(value(x, y, c) * scale);
        std::memcpy(inputBytes.data() + y * 256 + (x * 4 + c) * componentBytes, &encoded, componentBytes);
    }
    auto queue = device->createCommandQueue(RenderCommandListType::DIRECT);
    auto commands = queue->createCommandList();
    auto fence = device->createCommandFence();
    auto input = device->createTexture(RenderTextureDesc::Texture2D(16, 16, 1, format));
    auto output = device->createTexture(RenderTextureDesc::Texture2D(8, 8, 1, format,
        RenderTextureFlag::STORAGE | RenderTextureFlag::UNORDERED_ACCESS));
    auto tlut = device->createTexture(RenderTextureDesc::Texture1D(4, 1, RenderFormat::R8_UINT));
    auto upload = device->createBuffer(RenderBufferDesc::UploadBuffer(inputBytes.size()));
    const unsigned outputBytes = outputWidth * outputHeight * 4 * componentBytes;
    auto readback = device->createBuffer(RenderBufferDesc::ReadbackBuffer(outputBytes));
    void* mapped = upload->map(); require(mapped != nullptr, "Upload mapping failed");
    std::memcpy(mapped, inputBytes.data(), inputBytes.size()); upload->unmap();

    BoxFilterDescriptorSet boxSet(device);
    ReinterpretDescriptorSet reinterpretSet(device);
    RenderPipelineLayoutBuilder builder;
    builder.begin();
    builder.addPushConstant(0, 0, reinterpretation ? sizeof(interop::FbReinterpretCB) : sizeof(uint32_t) * 6, RenderShaderStageFlag::COMPUTE);
    if (reinterpretation) builder.addDescriptorSet(reinterpretSet); else builder.addDescriptorSet(boxSet);
    builder.end();
    auto layout = builder.create(device);
    auto shader = device->createShader(reinterpretation ? FbReinterpretCSBlobSPIRV : BoxFilterCSBlobSPIRV,
        reinterpretation ? FbReinterpretCSBlobSPIRV_size : BoxFilterCSBlobSPIRV_size, "CSMain", RenderShaderFormat::SPIRV);
    auto pipeline = device->createComputePipeline(RenderComputePipelineDesc(layout.get(), shader.get(), 8, 8, 1));
    require(pipeline != nullptr, "Production compute pipeline failed");
    commands->begin();
    commands->barriers(RenderBarrierStage::COPY, RenderTextureBarrier(input.get(), RenderTextureLayout::COPY_DEST));
    commands->copyTextureRegion(RenderTextureCopyLocation::Subresource(input.get()),
        RenderTextureCopyLocation::PlacedFootprint(upload.get(), format, 16, 16, 1, 256 / (4 * componentBytes)));
    const RenderTextureBarrier before[] = {
        {input.get(), RenderTextureLayout::SHADER_READ}, {output.get(), RenderTextureLayout::GENERAL},
        {tlut.get(), RenderTextureLayout::SHADER_READ}
    };
    commands->barriers(RenderBarrierStage::COMPUTE, before, 3);
    commands->setComputePipelineLayout(layout.get());
    commands->setPipeline(pipeline.get());
    if (reinterpretation) {
        reinterpretSet.setTexture(reinterpretSet.gInputColor, input.get(), RenderTextureLayout::SHADER_READ);
        reinterpretSet.setTexture(reinterpretSet.gInputTLUT, tlut.get(), RenderTextureLayout::SHADER_READ);
        reinterpretSet.setTexture(reinterpretSet.gOutput, output.get(), RenderTextureLayout::GENERAL);
        interop::FbReinterpretCB params{};
        params.resolution = {8, 8}; params.sampleScale = 1; params.srcSiz = G_IM_SIZ_8b;
        params.dstSiz = G_IM_SIZ_8b; params.dstFmt = G_IM_FMT_I; params.usesHDR = hdr;
        commands->setComputePushConstants(0, &params);
        commands->setComputeDescriptorSet(reinterpretSet.get(), 0);
    } else {
        boxSet.setTexture(boxSet.gInput, input.get(), RenderTextureLayout::SHADER_READ);
        boxSet.setTexture(boxSet.gOutput, output.get(), RenderTextureLayout::GENERAL);
        const int params[] = {16, 16, 2, 2, 1, 0};
        commands->setComputePushConstants(0, params);
        commands->setComputeDescriptorSet(boxSet.get(), 0);
    }
    commands->dispatch(1, 1, 1);
    commands->barriers(RenderBarrierStage::COPY, RenderTextureBarrier(output.get(), RenderTextureLayout::COPY_SOURCE));
    auto* native = static_cast<VulkanCommandList*>(commands.get());
    VkBufferImageCopy copy{};
    copy.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT; copy.imageSubresource.layerCount = 1;
    copy.imageExtent = {8, 8, 1};
    vkCmdCopyImageToBuffer(native->vk, static_cast<VulkanTexture*>(output.get())->vk,
        VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, static_cast<VulkanBuffer*>(readback.get())->vk, 1, &copy);
    commands->end(); queue->executeCommandLists(commands.get(), fence.get()); queue->waitForCommandFence(fence.get());
    const RenderRange read(0, outputBytes);
    const auto* result = static_cast<const unsigned char*>(readback->map(0, &read));
    require(result != nullptr, "Readback mapping failed");
    unsigned maximumError = 0;
    for (unsigned y = 0; y < 8; ++y) for (unsigned x = 0; x < 8; ++x) for (unsigned c = 0; c < 4; ++c) {
        uint16_t actual = 0;
        std::memcpy(&actual, result + ((y * 8 + x) * 4 + c) * componentBytes, componentBytes);
        double expected;
        if (reinterpretation) expected = value(x, y, x & 1) * scale;
        else {
            expected = 0;
            for (int dy = 0; dy < 2; ++dy) for (int dx = 0; dx < 2; ++dx)
                expected += value(unsigned(std::min(15, int(x * 2) + dx + 1)), y * 2 + dy, c) * scale / 4.0;
        }
        const unsigned error = unsigned(std::abs(int(actual) - int(std::lround(expected))));
        maximumError = std::max(maximumError, error);
        if (error > 1) std::fprintf(stderr, "Mismatch shader=%s hdr=%u x=%u y=%u c=%u actual=%u expected=%.3f\n",
            reinterpretation ? "reinterpret" : "box", unsigned(hdr), x, y, c, unsigned(actual), expected);
        require(error <= 1, "Production framebuffer compute pixel differs from CPU expected value");
    }
    const RenderRange noWrite(0, 0); readback->unmap(0, &noWrite);
    std::printf("PASS %s %s: 256 components, max encoding error=%u\n",
        reinterpretation ? "FbReinterpret" : "BoxFilter", hdr ? "RGBA16_UNORM" : "RGBA8_UNORM", maximumError);
}

int main() {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    try {
        VulkanInterface rhi; require(rhi.isValid(), "Vulkan unavailable");
        Validation validation; validation.install(rhi.instance);
        {
            auto device = rhi.createDevice(""); require(device != nullptr, "Vulkan device failed");
            for (bool hdr : {false, true}) for (bool reinterpretation : {false, true}) run(device.get(), hdr, reinterpretation);
        }
        require(validation.errors == 0 && validation.warnings == 0, "Core/sync validation reported a problem");
        std::printf("PASS: %u checks; production framebuffer compute SDR/HDR; zero core/sync warnings/errors.\n", checks);
        return 0;
    } catch (const std::exception& error) {
        std::fprintf(stderr, "FAIL: %s\n", error.what()); return 1;
    }
}
