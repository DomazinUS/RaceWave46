// Included inside the headless fixture namespace. Uses the embedded production
// framebuffer shaders and descriptor definitions; no game, window or swapchain.
extern "C" {
    extern const char FbReadAnyFullCSBlobSPIRV[];
    extern const size_t FbReadAnyFullCSBlobSPIRV_size;
    extern const char FbReadAnyChangesCSBlobSPIRV[];
    extern const size_t FbReadAnyChangesCSBlobSPIRV_size;
    extern const char FbWriteColorCSBlobSPIRV[];
    extern const size_t FbWriteColorCSBlobSPIRV_size;
    extern const char FbWriteDepthCSBlobSPIRV[];
    extern const size_t FbWriteDepthCSBlobSPIRV_size;
    extern const char FbWriteDepthCSMSBlobSPIRV[];
    extern const size_t FbWriteDepthCSMSBlobSPIRV_size;
}

void verifyVulkanNativeDepthMS(RenderDevice *device, FixtureWorker &worker, VulkanValidation &validation) {
    constexpr uint32_t Edge = 8, PixelCount = Edge * Edge, NativeBytes = PixelCount * sizeof(uint16_t);
    require(device->getSampleCountsSupported(RenderFormat::D32_FLOAT) & RenderSampleCount::COUNT_4,
        "4x D32 depth is unsupported on the fixture device");
    FramebufferWriteDescriptorBufferSet writeBuffer(device);
    FramebufferWriteDescriptorTextureSet writeTexture(device);
    const uint32_t constants[9] = {0, 0, Edge, Edge, 5, 2, 3, 0, 0};
    RenderPipelineLayoutBuilder builder;
    builder.begin();
    builder.addPushConstant(0, 0, sizeof(constants), RenderShaderStageFlag::COMPUTE);
    builder.addDescriptorSet(writeBuffer);
    builder.addDescriptorSet(writeTexture);
    builder.end();
    auto layout = builder.create(device);
    auto shader = device->createShader(FbWriteDepthCSMSBlobSPIRV, FbWriteDepthCSMSBlobSPIRV_size, "CSMain", RenderShaderFormat::SPIRV);
    auto pipeline = device->createComputePipeline(RenderComputePipelineDesc(layout.get(), shader.get(), Edge, Edge, 1));
    require(pipeline && static_cast<VulkanComputePipeline *>(pipeline.get())->vk, "Production 4x depth-write pipeline creation failed");
    RenderMultisampling samples;
    samples.sampleCount = RenderSampleCount::COUNT_4;
    auto depth = device->createTexture(RenderTextureDesc::DepthTarget(Edge, Edge, RenderFormat::D32_FLOAT, samples));
    auto framebuffer = device->createFramebuffer(RenderFramebufferDesc(nullptr, 0, depth.get()));
    auto native = device->createBuffer(RenderBufferDesc::DefaultBuffer(NativeBytes,
        RenderBufferFlag::STORAGE | RenderBufferFlag::UNORDERED_ACCESS | RenderBufferFlag::FORMATTED));
    auto view = native->createBufferFormattedView(RenderFormat::R16_UINT);
    auto readback = device->createBuffer(RenderBufferDesc::ReadbackBuffer(NativeBytes));
    writeBuffer.setBuffer(writeBuffer.gOutput, native.get(), NativeBytes, view.get());
    writeTexture.setTexture(writeTexture.gInput, depth.get(), RenderTextureLayout::SHADER_READ);
    const std::array<std::pair<float, uint16_t>, 4> values = {{{0.f, 0x0000}, {.25f, 0x1000}, {.75f, 0x3FFC}, {1.f, 0xFFFC}}};
    for (const auto &value : values) {
        worker.commandList->begin();
        worker.commandList->barriers(RenderBarrierStage::GRAPHICS, RenderTextureBarrier(depth.get(), RenderTextureLayout::DEPTH_WRITE));
        worker.commandList->setFramebuffer(framebuffer.get());
        worker.commandList->clearDepth(true, value.first);
        worker.commandList->barriers(RenderBarrierStage::COMPUTE, RenderTextureBarrier(depth.get(), RenderTextureLayout::SHADER_READ));
        worker.commandList->barriers(RenderBarrierStage::COMPUTE, RenderBufferBarrier(native.get(), RenderBufferAccess::WRITE));
        worker.commandList->setComputePipelineLayout(layout.get());
        worker.commandList->setPipeline(pipeline.get());
        worker.commandList->setComputePushConstants(0, constants);
        worker.commandList->setComputeDescriptorSet(writeBuffer.get(), 0);
        worker.commandList->setComputeDescriptorSet(writeTexture.get(), 1);
        worker.commandList->dispatch(1, 1, 1);
        worker.commandList->barriers(RenderBarrierStage::COPY, RenderBufferBarrier(native.get(), RenderBufferAccess::READ));
        worker.commandList->copyBufferRegion(readback->at(0), native->at(0), NativeBytes);
        worker.commandList->end();
        require(validation.errors == 0 && validation.warnings == 0, "4x native depth commands failed validation before submit");
        worker.execute();
        worker.wait();
        require(validation.errors == 0 && validation.warnings == 0, "4x native depth submission emitted validation messages");
        const RenderRange read(0, NativeBytes), noWrite(0, 0);
        const auto *bytes = static_cast<const uint8_t *>(readback->map(0, &read));
        require(bytes, "4x native depth readback mapping failed");
        for (uint32_t i = 0; i < PixelCount; ++i)
            require(bytes[i * 2] == uint8_t(value.second >> 8) && bytes[i * 2 + 1] == uint8_t(value.second),
                "4x native depth write-back disagrees with expected encoded depth");
        readback->unmap(0, &noWrite);
        std::printf("Native depth 4x: %.2f -> 0x%04X, 64 exact pixel encodings passed\n", value.first, value.second);
    }
}

void verifyVulkanNativeFramebuffer(RenderDevice *device, FixtureWorker &worker, VulkanValidation &validation) {
    constexpr uint32_t Edge = 8, Pixels = Edge * Edge;
    struct Constants {
        uint32_t offset[2] = {}, resolution[2] = {Edge, Edge};
        uint32_t fmt = 0, siz = 0, ditherPattern = 3, ditherRandomSeed = 0, usesHDR = 0;
    };
    static_assert(sizeof(Constants) == 36, "Native framebuffer constant layout changed");
    FramebufferReadChangesDescriptorBufferSet readBuffers(device);
    FramebufferReadChangesDescriptorChangesSet readTextures(device);
    FramebufferWriteDescriptorBufferSet writeBuffer(device);
    FramebufferWriteDescriptorTextureSet writeTexture(device);
    RenderPipelineLayoutBuilder builder;
    builder.begin();
    builder.addPushConstant(0, 0, sizeof(Constants), RenderShaderStageFlag::COMPUTE);
    builder.addDescriptorSet(readBuffers);
    builder.addDescriptorSet(readTextures);
    builder.end();
    auto readLayout = builder.create(device);
    builder.begin();
    builder.addPushConstant(0, 0, sizeof(Constants), RenderShaderStageFlag::COMPUTE);
    builder.addDescriptorSet(writeBuffer);
    builder.addDescriptorSet(writeTexture);
    builder.end();
    auto writeLayout = builder.create(device);
    auto makePipeline = [&](const char *blob, size_t size, RenderPipelineLayout *layout) {
        auto shader = device->createShader(blob, size, "CSMain", RenderShaderFormat::SPIRV);
        auto pipeline = device->createComputePipeline(RenderComputePipelineDesc(layout, shader.get(), Edge, Edge, 1));
        require(pipeline && static_cast<VulkanComputePipeline *>(pipeline.get())->vk, "Native framebuffer pipeline creation failed");
        return pipeline;
    };
    auto full = makePipeline(FbReadAnyFullCSBlobSPIRV, FbReadAnyFullCSBlobSPIRV_size, readLayout.get());
    auto changes = makePipeline(FbReadAnyChangesCSBlobSPIRV, FbReadAnyChangesCSBlobSPIRV_size, readLayout.get());
    auto writeColor = makePipeline(FbWriteColorCSBlobSPIRV, FbWriteColorCSBlobSPIRV_size, writeLayout.get());
    auto writeDepth = makePipeline(FbWriteDepthCSBlobSPIRV, FbWriteDepthCSBlobSPIRV_size, writeLayout.get());
    require(validation.errors == 0 && validation.warnings == 0, "Native framebuffer pipeline emitted validation messages");
    auto imageReadback = [&](RenderTexture *image, RenderBuffer *output) {
        worker.commandList->barriers(RenderBarrierStage::COPY, RenderTextureBarrier(image, RenderTextureLayout::COPY_SOURCE));
        auto *commands = static_cast<VulkanCommandList *>(worker.commandList.get());
        commands->endActiveRenderPass();
        VkBufferImageCopy copy{};
        copy.bufferRowLength = Edge;
        copy.bufferImageHeight = Edge;
        copy.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        copy.imageSubresource.layerCount = 1;
        copy.imageExtent = {Edge, Edge, 1};
        vkCmdCopyImageToBuffer(commands->vk, static_cast<VulkanTexture *>(image)->vk,
            VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, static_cast<VulkanBuffer *>(output)->vk, 1, &copy);
    };
    auto readBytes = [&](RenderBuffer *buffer, size_t size) {
        const RenderRange read(0, size), noWrite(0, 0);
        const auto *mapped = static_cast<const uint8_t *>(buffer->map(0, &read));
        require(mapped, "Native framebuffer readback map failed");
        std::vector<uint8_t> bytes(mapped, mapped + size);
        buffer->unmap(0, &noWrite);
        return bytes;
    };
    const auto started = std::chrono::steady_clock::now();
    uint32_t cases = 0;
    for (uint32_t caseIndex = 0; caseIndex < 7; ++caseIndex) {
        const bool depth = caseIndex == 6, hdr = !depth && caseIndex >= 3;
        const uint32_t siz = depth ? 2 : 1 + caseIndex % 3;
        const uint32_t nativeStride = 1U << (siz - 1), nativeBytes = Pixels * nativeStride;
        const uint32_t outputStride = hdr ? 8 : 4, outputBytes = Pixels * outputStride;
        const RenderFormat bufferFormat = siz == 1 ? RenderFormat::R8_UINT : siz == 2 ? RenderFormat::R16_UINT : RenderFormat::R32_UINT;
        const RenderFormat pixelFormat = depth ? RenderFormat::R32_FLOAT : hdr ? RenderFormat::R16G16B16A16_UNORM : RenderFormat::R8G8B8A8_UNORM;
        auto newUpload = device->createBuffer(RenderBufferDesc::UploadBuffer(nativeBytes));
        auto oldUpload = device->createBuffer(RenderBufferDesc::UploadBuffer(nativeBytes));
        auto countUpload = device->createBuffer(RenderBufferDesc::UploadBuffer(sizeof(uint32_t)));
        const auto nativeFlags = RenderBufferFlag::STORAGE | RenderBufferFlag::UNORDERED_ACCESS | RenderBufferFlag::FORMATTED;
        auto newInput = device->createBuffer(RenderBufferDesc::DefaultBuffer(nativeBytes, nativeFlags));
        auto oldInput = device->createBuffer(RenderBufferDesc::DefaultBuffer(nativeBytes, nativeFlags));
        auto nativeOutput = device->createBuffer(RenderBufferDesc::DefaultBuffer(nativeBytes, nativeFlags));
        auto counter = device->createBuffer(RenderBufferDesc::DefaultBuffer(sizeof(uint32_t), RenderBufferFlag::STORAGE | RenderBufferFlag::UNORDERED_ACCESS));
        auto newView = newInput->createBufferFormattedView(bufferFormat);
        auto oldView = oldInput->createBufferFormattedView(bufferFormat);
        auto outputView = nativeOutput->createBufferFormattedView(bufferFormat);
        auto pixels = device->createTexture(RenderTextureDesc::Texture2D(Edge, Edge, 1, pixelFormat, RenderTextureFlag::STORAGE | RenderTextureFlag::UNORDERED_ACCESS));
        auto mask = device->createTexture(RenderTextureDesc::Texture2D(Edge, Edge, 1, RenderFormat::R8_UINT, RenderTextureFlag::STORAGE | RenderTextureFlag::UNORDERED_ACCESS));
        auto pixelReadback = device->createBuffer(RenderBufferDesc::ReadbackBuffer(outputBytes));
        auto maskReadback = device->createBuffer(RenderBufferDesc::ReadbackBuffer(Pixels));
        auto nativeReadback = device->createBuffer(RenderBufferDesc::ReadbackBuffer(nativeBytes));
        auto countReadback = device->createBuffer(RenderBufferDesc::ReadbackBuffer(sizeof(uint32_t)));
        readBuffers.setBuffer(readBuffers.gNewInput, newInput.get(), nativeBytes, newView.get());
        readBuffers.setBuffer(readBuffers.gCurInput, oldInput.get(), nativeBytes, oldView.get());
        readBuffers.setBuffer(readBuffers.gOutputCount, counter.get(), RenderBufferStructuredView(sizeof(uint32_t)));
        // FramebufferChangePool deliberately binds this same image to both
        // outputs. Preserve that real descriptor contract, including the unused
        // color/depth branch, so dummy-slot format issues are caught here.
        readTextures.setTexture(readTextures.gOutputChangeColor, pixels.get(), RenderTextureLayout::GENERAL);
        readTextures.setTexture(readTextures.gOutputChangeDepth, pixels.get(), RenderTextureLayout::GENERAL);
        readTextures.setTexture(readTextures.gOutputChangeBoolean, mask.get(), RenderTextureLayout::GENERAL);
        writeBuffer.setBuffer(writeBuffer.gOutput, nativeOutput.get(), nativeBytes, outputView.get());
        writeTexture.setTexture(writeTexture.gInput, pixels.get(), RenderTextureLayout::SHADER_READ);
        Constants constants;
        constants.fmt = depth ? 5 : siz == 1 ? 4 : 0;
        constants.siz = siz;
        constants.usesHDR = hdr;
        std::vector<uint8_t> baseline(nativeBytes), current(nativeBytes);
        std::array<std::array<uint8_t, 4>, Pixels> expectedColor{};
        std::array<float, Pixels> expectedDepth{};
        auto generate = [&](bool changed) {
            for (uint32_t i = 0; i < Pixels; ++i) {
                const uint32_t variant = i + (changed && (i & 1) ? 71 : 0);
                uint32_t value;
                if (depth) {
                    const uint32_t exponent = variant % 8, mantissa = (variant * 29 + 13) % 2048;
                    value = (exponent << 13) | (mantissa << 2);
                    expectedDepth[i] = float((mantissa << (6 - std::min(6U, exponent))) + (0x40000U - (0x40000U >> exponent))) / 262143.f;
                }
                else if (siz == 1) {
                    value = 11 + (variant * 17) % 241;
                    expectedColor[i].fill(uint8_t(value));
                }
                else if (siz == 2) {
                    const uint32_t r = (variant * 7 + 1) % 32, g = (variant * 13 + 3) % 32, b = (variant * 19 + 7) % 32;
                    value = (r << 11) | (g << 6) | (b << 1) | 1;
                    expectedColor[i] = {uint8_t((r << 3) | (r >> 2)), uint8_t((g << 3) | (g >> 2)), uint8_t((b << 3) | (b >> 2)), 255};
                }
                else {
                    expectedColor[i] = {uint8_t(3 + variant * 17), uint8_t(11 + variant * 23), uint8_t(29 + variant * 31), 255};
                    const auto &c = expectedColor[i];
                    value = (uint32_t(c[0]) << 24) | (uint32_t(c[1]) << 16) | (uint32_t(c[2]) << 8) | c[3];
                }
                for (uint32_t b = 0; b < nativeStride; ++b) current[i * nativeStride + b] = uint8_t(value >> ((nativeStride - b - 1) * 8));
            }
        };
        generate(false);
        baseline = current;
        fill(oldUpload.get(), baseline.data(), baseline.size());
        const uint32_t zero = 0;
        fill(countUpload.get(), &zero, sizeof(zero));
        for (uint32_t pass = 0; pass < 2; ++pass) {
            generate(pass != 0);
            fill(newUpload.get(), current.data(), current.size());
            worker.commandList->begin();
            const RenderBufferBarrier copyBefore[] = {{newInput.get(), RenderBufferAccess::WRITE}, {oldInput.get(), RenderBufferAccess::WRITE}, {counter.get(), RenderBufferAccess::WRITE}};
            worker.commandList->barriers(RenderBarrierStage::COPY, copyBefore, 3, nullptr, 0);
            worker.commandList->copyBufferRegion(newInput->at(0), newUpload->at(0), nativeBytes);
            worker.commandList->copyBufferRegion(oldInput->at(0), oldUpload->at(0), nativeBytes);
            worker.commandList->copyBufferRegion(counter->at(0), countUpload->at(0), sizeof(uint32_t));
            const RenderBufferBarrier computeBuffers[] = {{newInput.get(), RenderBufferAccess::READ}, {oldInput.get(), RenderBufferAccess::READ}, {counter.get(), RenderBufferAccess::READ | RenderBufferAccess::WRITE}};
            const RenderTextureBarrier computeTextures[] = {{pixels.get(), RenderTextureLayout::GENERAL}, {mask.get(), RenderTextureLayout::GENERAL}};
            worker.commandList->barriers(RenderBarrierStage::COMPUTE, computeBuffers, 3, computeTextures, 2);
            worker.commandList->setPipeline(pass ? changes.get() : full.get());
            worker.commandList->setComputePipelineLayout(readLayout.get());
            worker.commandList->setComputePushConstants(0, &constants);
            worker.commandList->setComputeDescriptorSet(readBuffers.get(), 0);
            worker.commandList->setComputeDescriptorSet(readTextures.get(), 1);
            worker.commandList->dispatch(1, 1, 1);
            // Do not submit commands known to be invalid. This fixture tests
            // corrected shader binaries, never an intentionally broken GPU path.
            require(validation.errors == 0 && validation.warnings == 0, "Native framebuffer read descriptors/shader failed validation before submit");
            worker.commandList->barriers(RenderBarrierStage::COMPUTE, RenderTextureBarrier(pixels.get(), RenderTextureLayout::SHADER_READ));
            worker.commandList->barriers(RenderBarrierStage::COMPUTE, RenderBufferBarrier(nativeOutput.get(), RenderBufferAccess::WRITE));
            worker.commandList->setPipeline(depth ? writeDepth.get() : writeColor.get());
            worker.commandList->setComputePipelineLayout(writeLayout.get());
            worker.commandList->setComputePushConstants(0, &constants);
            worker.commandList->setComputeDescriptorSet(writeBuffer.get(), 0);
            worker.commandList->setComputeDescriptorSet(writeTexture.get(), 1);
            worker.commandList->dispatch(1, 1, 1);
            imageReadback(pixels.get(), pixelReadback.get());
            imageReadback(mask.get(), maskReadback.get());
            const RenderBufferBarrier copyAfter[] = {{nativeOutput.get(), RenderBufferAccess::READ}, {counter.get(), RenderBufferAccess::READ}};
            worker.commandList->barriers(RenderBarrierStage::COPY, copyAfter, 2, nullptr, 0);
            worker.commandList->copyBufferRegion(nativeReadback->at(0), nativeOutput->at(0), nativeBytes);
            worker.commandList->copyBufferRegion(countReadback->at(0), counter->at(0), sizeof(uint32_t));
            worker.commandList->end();
            require(validation.errors == 0 && validation.warnings == 0, "Native framebuffer commands failed validation before submit");
            worker.execute();
            worker.wait();
            require(validation.errors == 0 && validation.warnings == 0, "Native framebuffer submission emitted validation messages");
            const auto actualPixels = readBytes(pixelReadback.get(), outputBytes);
            const auto actualMask = readBytes(maskReadback.get(), Pixels);
            const auto actualNative = readBytes(nativeReadback.get(), nativeBytes);
            const auto actualCount = readBytes(countReadback.get(), sizeof(uint32_t));
            uint32_t changedCount;
            std::memcpy(&changedCount, actualCount.data(), sizeof(changedCount));
            require(changedCount == (pass ? Pixels / 2 : 0), "Native framebuffer change counter is incorrect");
            for (uint32_t i = 0; i < Pixels; ++i) {
                require(actualMask[i] == (pass ? i & 1 : 1), "Native framebuffer change mask is incorrect");
                if (depth) {
                    float actual;
                    std::memcpy(&actual, actualPixels.data() + i * sizeof(float), sizeof(actual));
                    require(std::isfinite(actual) && std::abs(actual - expectedDepth[i]) < 1e-7f, "Native depth decode disagrees with expected depth");
                }
                else for (uint32_t c = 0; c < 4; ++c) {
                    if (hdr) {
                        uint16_t actual;
                        std::memcpy(&actual, actualPixels.data() + i * outputStride + c * sizeof(uint16_t), sizeof(actual));
                        require(actual == uint16_t(expectedColor[i][c]) * 257, "HDR native framebuffer decode is incorrect");
                    }
                    else require(actualPixels[i * outputStride + c] == expectedColor[i][c], "SDR native framebuffer decode is incorrect");
                }
            }
            require(actualNative == current, "Native framebuffer write-back changed initialized pixel bytes");
            std::printf("Native framebuffer %s %u-bit %s: %s, 64 pixels + mask/count + %u exact native bytes passed\n",
                depth ? "depth" : "color", nativeStride * 8, hdr ? "HDR16" : depth ? "R32F" : "SDR8", pass ? "changes/write" : "full/write", nativeBytes);
        }
        ++cases;
    }
    std::printf("PASS: %u native framebuffer cases, full/change decode plus production write-back, elapsed_ms=%.3f\n", cases,
        std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - started).count());
}
