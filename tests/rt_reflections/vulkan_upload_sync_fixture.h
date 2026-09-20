// Included inside the headless fixture namespace. No game, window or swapchain.
extern "C" {
    extern const char TextureDecodeCSBlobSPIRV[];
    extern const size_t TextureDecodeCSBlobSPIRV_size;
}

struct VulkanSubmissionContract {
    PFN_vkQueueSubmit original = vkQueueSubmit;
    static inline uint32_t expectedWaits = 0, calls = 0;
    ~VulkanSubmissionContract() { vkQueueSubmit = original; }
    static VKAPI_ATTR VkResult VKAPI_CALL inspect(VkQueue, uint32_t count, const VkSubmitInfo *submits, VkFence) {
        require(count == 1 && submits, "Unexpected mocked submission count");
        const auto &submit = submits[0];
        require(submit.waitSemaphoreCount == expectedWaits, "Wait semaphore count changed");
        require(submit.pWaitDstStageMask, "Missing semaphore destination stages");
        // Check the first entry before reading any others: the old scalar
        // COLOR_ATTACHMENT_OUTPUT contract fails safely here, without reading
        // beyond that old scalar or submitting invalid work to the GPU.
        require(submit.pWaitDstStageMask[0] == VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
            "Semaphore wait permits compute/transfer/vertex consumers before uploaded inputs are ready");
        for (uint32_t i = 0; i < expectedWaits; ++i)
            require(submit.pWaitSemaphores[i] && submit.pWaitDstStageMask[i] == VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
                "Each wait semaphore needs its own complete destination-stage entry");
        ++calls;
        return VK_SUCCESS;
    }
};

void verifyVulkanUploadSynchronization(RenderDevice *device, FixtureWorker &direct) {
    auto *native = static_cast<VulkanDevice *>(device);
    RenderWorker copy(device, "Headless texture copy producer", RenderCommandListType::COPY);
    RenderWorker compute(device, "Headless texture compute consumer", RenderCommandListType::COMPUTE);
    auto *directQueue = static_cast<VulkanCommandQueue *>(direct.commandQueue.get());
    auto *copyQueue = static_cast<VulkanCommandQueue *>(copy.commandQueue.get());
    auto *computeQueue = static_cast<VulkanCommandQueue *>(compute.commandQueue.get());
    require(directQueue->familyIndex == copyQueue->familyIndex && directQueue->familyIndex == computeQueue->familyIndex,
        "EXCLUSIVE resources cross queue families without an ownership-transfer contract");
    if (native->queueFamilies[directQueue->familyIndex].queues.size() >= 3)
        require(directQueue->queueIndex != copyQueue->queueIndex && directQueue->queueIndex != computeQueue->queueIndex &&
            copyQueue->queueIndex != computeQueue->queueIndex, "Workers unnecessarily collapsed onto one native queue");
    std::printf("Upload synchronization: family=%u DIRECT=%u COPY=%u COMPUTE=%u\n",
        directQueue->familyIndex, directQueue->queueIndex, copyQueue->queueIndex, computeQueue->queueIndex);

    std::array<std::unique_ptr<RenderCommandSemaphore>, 4> semaphores;
    RenderCommandSemaphore *waits[4];
    for (uint32_t i = 0; i < 4; ++i) { semaphores[i] = device->createCommandSemaphore(); waits[i] = semaphores[i].get(); }
    {
        VulkanSubmissionContract capture;
        VulkanSubmissionContract::calls = 0;
        // Establish that the original upload wait fails this contract without
        // sending it to Vulkan, even for a single semaphore.
        const VkPipelineStageFlags oldColorOnlyWait = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        const VkSemaphore firstSemaphore = static_cast<VulkanCommandSemaphore *>(waits[0])->vk;
        VkSubmitInfo oldContract{VK_STRUCTURE_TYPE_SUBMIT_INFO};
        oldContract.waitSemaphoreCount = 1;
        oldContract.pWaitSemaphores = &firstSemaphore;
        oldContract.pWaitDstStageMask = &oldColorOnlyWait;
        VulkanSubmissionContract::expectedWaits = 1;
        bool oldRejected = false;
        try { VulkanSubmissionContract::inspect(VK_NULL_HANDLE, 1, &oldContract, VK_NULL_HANDLE); }
        catch (const std::runtime_error &) { oldRejected = true; }
        require(oldRejected, "Submission contract accepted the original color-only upload wait");
        vkQueueSubmit = VulkanSubmissionContract::inspect;
        const RenderCommandList *list = direct.commandList.get();
        for (uint32_t count : {1U, 2U, 4U}) {
            VulkanSubmissionContract::expectedWaits = count;
            direct.commandQueue->executeCommandLists(&list, 1, waits, count, nullptr, 0);
        }
        require(VulkanSubmissionContract::calls == 3, "Submission-mask contract did not inspect every case");
    }

    TextureDecodeDescriptorSet descriptors(device);
    RenderPipelineLayoutBuilder layoutBuilder;
    layoutBuilder.begin();
    layoutBuilder.addPushConstant(0, 0, 8 * sizeof(uint32_t), RenderShaderStageFlag::COMPUTE);
    layoutBuilder.addDescriptorSet(descriptors);
    layoutBuilder.end();
    auto layout = layoutBuilder.create(device);
    auto shader = device->createShader(TextureDecodeCSBlobSPIRV, TextureDecodeCSBlobSPIRV_size, "CSMain", RenderShaderFormat::SPIRV);
    auto pipeline = device->createComputePipeline(RenderComputePipelineDesc(layout.get(), shader.get(), 8, 8, 1));
    require(pipeline && static_cast<VulkanComputePipeline *>(pipeline.get())->vk, "Production texture-decode pipeline creation failed");
    constexpr uint32_t Edge = 8, TmemBytes = 4096, RowBytes = Edge * 4;
    auto upload = device->createBuffer(RenderBufferDesc::UploadBuffer(TmemBytes));
    auto tmem = device->createTexture(RenderTextureDesc::Texture1D(TmemBytes, 1, RenderFormat::R8_UINT));
    auto decoded = device->createTexture(RenderTextureDesc::Texture2D(Edge, Edge, 1, RenderFormat::R8G8B8A8_UNORM,
        RenderTextureFlag::STORAGE | RenderTextureFlag::UNORDERED_ACCESS));
    auto readback = device->createBuffer(RenderBufferDesc::ReadbackBuffer(Edge * RowBytes));
    descriptors.setTexture(descriptors.TMEM, tmem.get(), RenderTextureLayout::SHADER_READ);
    descriptors.setTexture(descriptors.RGBA32, decoded.get(), RenderTextureLayout::GENERAL);
    const uint32_t constants[8] = {Edge, Edge, 4, 1, 0, Edge, 0, 0}; // Native I8 decoding, no TLUT.
    const auto begin = std::chrono::steady_clock::now();
    for (uint32_t iteration = 0; iteration < 16; ++iteration) {
        std::array<uint8_t, TmemBytes> input{};
        std::array<uint8_t, Edge * Edge> expected{};
        for (uint32_t y = 0; y < Edge; ++y) for (uint32_t x = 0; x < Edge; ++x) {
            const uint8_t value = uint8_t(13 + ((iteration * 23 + y * 17 + x * 11) % 229));
            expected[y * Edge + x] = value;
            // Native TMEM swaps 32-bit words on odd rows.
            input[y * Edge + (x ^ ((y & 1) ? 4 : 0))] = value;
        }
        fill(upload.get(), input.data(), input.size());
        copy.commandList->begin();
        copy.commandList->barriers(RenderBarrierStage::COPY, RenderTextureBarrier(tmem.get(), RenderTextureLayout::COPY_DEST));
        copy.commandList->copyTextureRegion(RenderTextureCopyLocation::Subresource(tmem.get()),
            RenderTextureCopyLocation::PlacedFootprint(upload.get(), RenderFormat::R8_UINT, TmemBytes, 1, 1, TmemBytes));
        copy.commandList->end();
        const RenderCommandList *copyList = copy.commandList.get();
        copy.commandQueue->executeCommandLists(&copyList, 1, nullptr, 0, waits, 2);

        RenderWorker &consumer = (iteration & 1) ? compute : static_cast<RenderWorker &>(direct);
        consumer.commandList->begin();
        const RenderTextureBarrier before[] = {{tmem.get(), RenderTextureLayout::SHADER_READ}, {decoded.get(), RenderTextureLayout::GENERAL}};
        consumer.commandList->barriers(RenderBarrierStage::COMPUTE, nullptr, 0, before, 2);
        consumer.commandList->setPipeline(pipeline.get());
        consumer.commandList->setComputePipelineLayout(layout.get());
        consumer.commandList->setComputePushConstants(0, constants);
        consumer.commandList->setComputeDescriptorSet(descriptors.get(), 0);
        consumer.commandList->dispatch(1, 1, 1);
        consumer.commandList->barriers(RenderBarrierStage::COPY, RenderTextureBarrier(decoded.get(), RenderTextureLayout::COPY_SOURCE));
        // Plume has no Vulkan image-to-buffer branch. Match the existing
        // raster fixture's native readback after the production transition.
        auto *commands = static_cast<VulkanCommandList *>(consumer.commandList.get());
        commands->endActiveRenderPass();
        VkBufferImageCopy readCopy{};
        readCopy.bufferRowLength = Edge;
        readCopy.bufferImageHeight = Edge;
        readCopy.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        readCopy.imageSubresource.layerCount = 1;
        readCopy.imageExtent = {Edge, Edge, 1};
        vkCmdCopyImageToBuffer(commands->vk, static_cast<VulkanTexture *>(decoded.get())->vk,
            VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, static_cast<VulkanBuffer *>(readback.get())->vk, 1, &readCopy);
        consumer.commandList->end();
        const RenderCommandList *consumerList = consumer.commandList.get();
        consumer.commandQueue->executeCommandLists(&consumerList, 1, waits, 2, nullptr, 0, consumer.commandFence.get());
        consumer.wait();
        const RenderRange read(0, Edge * RowBytes);
        const auto *pixels = static_cast<const uint8_t *>(readback->map(0, &read));
        require(pixels, "Texture decode readback mapping failed");
        for (uint32_t i = 0; i < Edge * Edge; ++i) for (uint32_t channel = 0; channel < 4; ++channel)
            require(pixels[i * 4 + channel] == expected[i], "Cross-queue texture decode read stale or incorrect TMEM bytes");
        const RenderRange noWrite(0, 0);
        readback->unmap(0, &noWrite);
    }
    std::printf("PASS: 16 COPY-to-DIRECT/COMPUTE production texture decodes, 4096 exact output bytes, 1/2/4-wait submission contracts; elapsed_ms=%.3f\n",
        std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - begin).count());
}
