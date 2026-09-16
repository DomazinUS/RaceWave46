//
// RT64
//

#include "rt64_vi_renderer.h"
#include "../../../../include/wr64_diagnostic_policy.h"

#include <cstdio>
#include <cstdlib>

#include "shared/rt64_hlsl.h"
#include "shared/rt64_video_interface.h"

namespace RT64 {
    // VIRenderer

    VIRenderer::VIRenderer() { }

    VIRenderer::~VIRenderer() { }

    inline hlslpp::float2 computeHDSize(hlslpp::float2 sdSize, hlslpp::float2 resolutionScale, uint32_t downsamplingScale) {
        return (sdSize * resolutionScale) / float(downsamplingScale);
    }

    inline hlslpp::float2 fromSDtoHD(hlslpp::float2 coordinate, hlslpp::float2 sdSize, hlslpp::float2 hdSize) {
        const hlslpp::float2 relativeScale = hdSize / sdSize;
        return coordinate * relativeScale;
    }

    inline hlslpp::float2 fromHDtoWindow(hlslpp::float2 coordinate, hlslpp::float2 hdSize, hlslpp::float2 windowSize) {
        const hlslpp::float2 hdCenter = hdSize / 2;
        const hlslpp::float2 windowCenter = windowSize / 2;
        const hlslpp::float2 relativeCoordinate = { coordinate.x - hdCenter.x, coordinate.y - hdCenter.y };

        // Window is wider than virtual HD TV, we do pillarboxing.
        float relativeScale;
        if ((windowSize.x / windowSize.y) > (hdSize.x / hdSize.y)) {
            relativeScale = windowSize.y / hdSize.y;
        }
        // Window is taller than virtual HD TV, we do letterboxing.
        else {
            relativeScale = windowSize.x / hdSize.x;
        }

        return windowCenter + relativeCoordinate * relativeScale;
    }

    void VIRenderer::render(const RenderParams &p) {
        // Invalid explicit regions must never expose the other player's view.
        if (p.outputRegion.enabled && !wr64PresentRegionValid(p.outputRegion)) return;
        const ShaderRecord *shader = nullptr;
        const RenderSampler *sampler = nullptr;
        switch (p.filtering) {
        case UserConfiguration::Filtering::Nearest:
            shader = &p.shaderLibrary->videoInterfaceNearest;
            sampler = p.shaderLibrary->samplerLibrary.nearest.borderBorder.get();
            break;
        case UserConfiguration::Filtering::AntiAliasedPixelScaling:
            shader = &p.shaderLibrary->videoInterfacePixel;
            sampler = p.shaderLibrary->samplerLibrary.linear.borderBorder.get();
            break;
        case UserConfiguration::Filtering::Linear:
        default:
            shader = &p.shaderLibrary->videoInterfaceLinear;
            sampler = p.shaderLibrary->samplerLibrary.linear.borderBorder.get();
            break;
        }

        if ((descriptorSet == nullptr) || (descriptorSetSampler != sampler)) {
            descriptorSet = std::make_unique<VideoInterfaceDescriptorSet>(sampler, p.device);
            descriptorSetSampler = sampler;
        }

        descriptorSet->setTexture(descriptorSet->gInput, p.texture, RenderTextureLayout::SHADER_READ);

        static const char *presentationCropValue = std::getenv("WR64_PRESENTATION_CROP");
        static bool presentationCropParsed = false;
        static bool presentationCropValid = false;
        static float presentationCropLeft = 0.0f;
        static float presentationCropTop = 0.0f;
        static float presentationCropRight = 1.0f;
        static float presentationCropBottom = 1.0f;
        if (!p.outputRegion.enabled && !presentationCropParsed) {
            presentationCropParsed = true;
            if (presentationCropValue != nullptr) {
                const int parsedCount = std::sscanf(
                    presentationCropValue,
                    "%f,%f,%f,%f",
                    &presentationCropLeft,
                    &presentationCropTop,
                    &presentationCropRight,
                    &presentationCropBottom);
                presentationCropValid =
                    (parsedCount == 4) &&
                    (presentationCropLeft >= 0.0f) &&
                    (presentationCropTop >= 0.0f) &&
                    (presentationCropRight <= 1.0f) &&
                    (presentationCropBottom <= 1.0f) &&
                    (presentationCropRight > presentationCropLeft) &&
                    (presentationCropBottom > presentationCropTop);
                WR64_DIAGNOSTIC_LOG(std::fprintf(
                    stdout,
                    "[rt64] presentation crop: value=%s valid=%d rect=(%.6f,%.6f)-(%.6f,%.6f)\n",
                    presentationCropValue,
                    presentationCropValid ? 1 : 0,
                    presentationCropLeft,
                    presentationCropTop,
                    presentationCropRight,
                    presentationCropBottom););
                WR64_DIAGNOSTIC_LOG(std::fflush(stdout););
            }
        }

        RenderViewport viewport;
        RenderRect scissor;
        if (p.outputRegion.enabled) {
            const auto fit = wr64PresentRegionViewport(p.outputRegion, p.swapChain->getWidth(), p.swapChain->getHeight());
            viewport = RenderViewport(fit.x, fit.y, fit.width, fit.height);
            scissor = RenderRect(int32_t(std::floor(fit.x)), int32_t(std::floor(fit.y)),
                int32_t(std::ceil(fit.x + fit.width)), int32_t(std::ceil(fit.y + fit.height)));
        }
        else {
            getViewportAndScissor(p.swapChain, *p.vi, p.presentationResolutionScale, p.downsamplingScale, p.removeBlackBorders, viewport, scissor);
        }
        if (!p.outputRegion.enabled && presentationCropValid) {
            const uint32_t swapWidth = p.swapChain->getWidth();
            const uint32_t swapHeight = p.swapChain->getHeight();
            viewport = RenderViewport(0.0f, 0.0f, float(swapWidth), float(swapHeight));
            scissor = RenderRect(0, 0, swapWidth, swapHeight);
        }

        static const bool presentTraceEnabled = WR64_DIAGNOSTIC_ENABLED && std::getenv("WR64_PRESENT_TRACE") != nullptr;
        if (presentTraceEnabled) {
            static uint32_t previousSwapWidth = 0;
            static uint32_t previousSwapHeight = 0;
            static RenderViewport previousViewport{};
            static RenderRect previousScissor{};
            static bool firstTrace = true;
            const uint32_t swapWidth = p.swapChain->getWidth();
            const uint32_t swapHeight = p.swapChain->getHeight();
            if (firstTrace || (swapWidth != previousSwapWidth) || (swapHeight != previousSwapHeight) ||
                (viewport != previousViewport) || (scissor != previousScissor)) {
                const hlslpp::float2 fbSize = p.vi->fbSize();
                std::fprintf(
                    stdout,
                    "[rt64] final present: swap=%ux%u fb=%.3fx%.3f textureScale=%.6fx%.6f "
                    "presentScale=%.6fx%.6f downsample=%u "
                    "removeBorders=%d viewport=(%.3f,%.3f %.3fx%.3f) scissor=(%d,%d)-(%d,%d)\n",
                    swapWidth,
                    swapHeight,
                    static_cast<float>(fbSize.x),
                    static_cast<float>(fbSize.y),
                    static_cast<float>(p.resolutionScale.x),
                    static_cast<float>(p.resolutionScale.y),
                    static_cast<float>(p.presentationResolutionScale.x),
                    static_cast<float>(p.presentationResolutionScale.y),
                    p.downsamplingScale,
                    p.removeBlackBorders ? 1 : 0,
                    viewport.x,
                    viewport.y,
                    viewport.width,
                    viewport.height,
                    scissor.left,
                    scissor.top,
                    scissor.right,
                    scissor.bottom);
                std::fflush(stdout);
                firstTrace = false;
                previousSwapWidth = swapWidth;
                previousSwapHeight = swapHeight;
                previousViewport = viewport;
                previousScissor = scissor;
            }
        }
        p.commandList->setViewports(viewport);
        p.commandList->setScissors(scissor);

        interop::VideoInterfaceCB pushConstants;
        pushConstants.videoResolution = computeHDSize(hlslpp::float2(p.vi->fbSize()), p.resolutionScale, p.downsamplingScale);
        pushConstants.textureResolution = { float(p.textureWidth), float(p.textureHeight) };
        pushConstants.sourceUVOffset = { 0.0f, 0.0f };
        pushConstants.sourceUVScale = { 1.0f, 1.0f };

        if (p.outputRegion.enabled) {
            pushConstants.sourceUVOffset = { p.outputRegion.left, p.outputRegion.top };
            pushConstants.sourceUVScale = { p.outputRegion.right - p.outputRegion.left,
                p.outputRegion.bottom - p.outputRegion.top };
        }
        else if (presentationCropValid) {
            pushConstants.sourceUVOffset = { presentationCropLeft, presentationCropTop };
            pushConstants.sourceUVScale = {
                presentationCropRight - presentationCropLeft,
                presentationCropBottom - presentationCropTop
            };
        }
        pushConstants.gamma = p.vi->gamma();

        p.commandList->setPipeline(shader->pipeline.get());
        p.commandList->setGraphicsPipelineLayout(shader->pipelineLayout.get());
        p.commandList->setGraphicsDescriptorSet(descriptorSet->get(), 0);
        p.commandList->setGraphicsPushConstants(0, &pushConstants);
        p.commandList->setVertexBuffers(0, nullptr, 0, nullptr);
        p.commandList->drawInstanced(3, 1, 0, 0);
    }

    void VIRenderer::getViewportAndScissor(const RenderSwapChain *swapChain, const VI &vi, hlslpp::float2 resolutionScale, uint32_t downsamplingScale, bool removeBlackBorders, RenderViewport &viewport, RenderRect &scissor) {
        // We define three different coordinate spaces to work with to translate the VI parameters into the Window.
        //
        // VideoSD: This corresponds to the SD TV Scanline space, which is what the VI natively works on.
        // 
        // VideoHD: This corresponds to what the imaginary "HD" TV would be if it supported the amount of scanlines
        // desired by the resolution scale (divided by the downsampling scale) and a wider aspect ratio.
        // 
        // Window: The native coordinate space of the device's render target.
        //
        // The provided buffer doesn't necessarily have the same dimensions that the VI will sample to display it 
        // on the screen. To work around that, the viewport the buffer will be drawn in will be expanded so only
        // the region of interest is rendered. A scissor will cut it off correctly according to the coordinates
        // specified by the VI.
        const hlslpp::float2 sdSize = removeBlackBorders ? hlslpp::float2(vi.fbSize()) : hlslpp::float2(320.0f, 240.0f);
        const hlslpp::float2 hdSize = computeHDSize(sdSize, resolutionScale, downsamplingScale);
        const hlslpp::float2 windowSize = { float(swapChain->getWidth()), float(swapChain->getHeight()) };

        // Query the VI for the current rendering area.
        hlslpp::float4 viViewRect = vi.viewRectangle() * sdSize.xyxy;
        hlslpp::float4 viCropRect = vi.cropRectangle() * sdSize.xyxy;

        // Scale all the rectangles to the space of the Window.
        hlslpp::float2 topLeftViewport = fromSDtoHD({ float(viViewRect.x), float(viViewRect.y) }, sdSize, hdSize);
        hlslpp::float2 bottomRightViewport = fromSDtoHD({ float(viViewRect.x + viViewRect.z), float(viViewRect.y + viViewRect.w) }, sdSize, hdSize);
        topLeftViewport = fromHDtoWindow(topLeftViewport, hdSize, windowSize);
        bottomRightViewport = fromHDtoWindow(bottomRightViewport, hdSize, windowSize);

        hlslpp::float2 topLeftScissor = fromSDtoHD({ float(viCropRect.x), float(viCropRect.y) }, sdSize, hdSize);
        hlslpp::float2 bottomRightScissor = fromSDtoHD({ float(viCropRect.x + viCropRect.z), float(viCropRect.y + viCropRect.w) }, sdSize, hdSize);
        topLeftScissor = fromHDtoWindow(topLeftScissor, hdSize, windowSize);
        bottomRightScissor = fromHDtoWindow(bottomRightScissor, hdSize, windowSize);

        viewport = RenderViewport(topLeftViewport.x, topLeftViewport.y, bottomRightViewport.x - topLeftViewport.x, bottomRightViewport.y - topLeftViewport.y);
        scissor = RenderRect(lround(topLeftScissor.x), lround(topLeftScissor.y), lround(bottomRightScissor.x), lround(bottomRightScissor.y));
    }
};
