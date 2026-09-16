// Vulkan-only backend contract regression. Included inside raster_gpu's fixture
// namespace so it shares the checked upload helper and assertion accounting.
// Effect/material/geometry-index readbacks are exercised by the common suite.
void verifyVulkanOffsetAS(RenderDevice *device, FixtureWorker &worker) {
    const float vertices[][4] = {{-2,0,0,1},{0,2,0,1},{2,0,0,1},{0,-2,0,1}};
    const uint32_t indices[] = {0,1,2, 0,2,3, 0,1,3};
    auto vertexBuffer = device->createBuffer(RenderBufferDesc::UploadBuffer(sizeof(vertices), RenderBufferFlag::ACCELERATION_STRUCTURE_INPUT));
    auto indexBuffer = device->createBuffer(RenderBufferDesc::UploadBuffer(sizeof(indices), RenderBufferFlag::ACCELERATION_STRUCTURE_INPUT));
    require(vertexBuffer && indexBuffer, "Could not allocate Vulkan AS contract inputs");
    fill(vertexBuffer.get(), vertices, sizeof(vertices));
    fill(indexBuffer.get(), indices, sizeof(indices));
    const RenderBottomLevelASMesh meshes[] = {
        {indexBuffer->at(0), vertexBuffer->at(0), RenderFormat::R32_UINT, RenderFormat::R32G32B32_FLOAT, 3, 4, 16, true},
        {indexBuffer->at(12), vertexBuffer->at(0), RenderFormat::R32_UINT, RenderFormat::R32G32B32_FLOAT, 6, 4, 16, false}
    };
    RenderBottomLevelASBuildInfo bottomInfo;
    device->setBottomLevelASBuildInfo(bottomInfo, meshes, 2, true, false);
    require(bottomInfo.meshCount == 2 && bottomInfo.primitiveCount == 3 && bottomInfo.scratchSize && bottomInfo.accelerationStructureSize,
        "Vulkan multi-geometry AS sizes/counts are invalid");
    const size_t geometriesBytes = sizeof(VkAccelerationStructureGeometryKHR) * 2;
    require(bottomInfo.buildData.size() == geometriesBytes + sizeof(VkAccelerationStructureBuildRangeInfoKHR) * 2,
        "Vulkan BLAS needs one build range per geometry");
    VkAccelerationStructureBuildRangeInfoKHR ranges[2];
    std::memcpy(ranges, bottomInfo.buildData.data() + geometriesBytes, sizeof(ranges));
    require(ranges[0].primitiveCount == 1 && ranges[1].primitiveCount == 2,
        "Vulkan BLAS lost individual geometry primitive counts");
    auto bottomBuffer = device->createBuffer(RenderBufferDesc::AccelerationStructureBuffer(bottomInfo.accelerationStructureSize));
    require(bottomBuffer != nullptr, "Could not allocate contract BLAS buffer");
    auto bottom = device->createAccelerationStructure({RenderAccelerationStructureType::BOTTOM_LEVEL, bottomBuffer->at(0), bottomInfo.accelerationStructureSize});
    require(bottom && bottom->getDeviceAddress(), "Vulkan BLAS has no actual AS device address");
    RenderTopLevelASInstance instance(bottomBuffer->at(0), 7, 0xFF, 0, true, RenderAffineTransform());
    instance.bottomLevelASDeviceAddress = bottom->getDeviceAddress();
    RenderTopLevelASBuildInfo topInfo;
    device->setTopLevelASBuildInfo(topInfo, &instance, 1, true, false);
    require(topInfo.instanceCount == 1 && topInfo.scratchSize && topInfo.accelerationStructureSize &&
        topInfo.instancesBufferData.size() == sizeof(VkAccelerationStructureInstanceKHR), "Vulkan TLAS contract data is invalid");
    VkAccelerationStructureInstanceKHR nativeInstance{};
    std::memcpy(&nativeInstance, topInfo.instancesBufferData.data(), sizeof(nativeInstance));
    require(nativeInstance.accelerationStructureReference == instance.bottomLevelASDeviceAddress && nativeInstance.instanceCustomIndex == 7,
        "Vulkan TLAS did not preserve the queried BLAS address or instance ID");
    auto topBuffer = device->createBuffer(RenderBufferDesc::AccelerationStructureBuffer(topInfo.accelerationStructureSize));
    require(topBuffer != nullptr, "Could not allocate contract TLAS buffer");
    auto top = device->createAccelerationStructure({RenderAccelerationStructureType::TOP_LEVEL, topBuffer->at(0), topInfo.accelerationStructureSize});
    constexpr uint64_t scratchOffset = 13; // Deliberately not device-aligned.
    auto scratch = device->createBuffer(RenderBufferDesc::DefaultBuffer(scratchOffset + std::max(bottomInfo.scratchSize, topInfo.scratchSize),
        RenderBufferFlag::ACCELERATION_STRUCTURE_SCRATCH | RenderBufferFlag::UNORDERED_ACCESS));
    auto instances = device->createBuffer(RenderBufferDesc::UploadBuffer(topInfo.instancesBufferData.size(), RenderBufferFlag::ACCELERATION_STRUCTURE_INPUT));
    require(top && top->getDeviceAddress() && scratch && instances, "Could not allocate Vulkan offset-scratch contract resources");
    fill(instances.get(), topInfo.instancesBufferData.data(), topInfo.instancesBufferData.size());
    worker.commandList->begin();
    const RenderBufferBarrier before[] = {
        {vertexBuffer.get(), RenderBufferAccess::READ}, {indexBuffer.get(), RenderBufferAccess::READ},
        {instances.get(), RenderBufferAccess::READ}, {bottomBuffer.get(), RenderBufferAccess::WRITE},
        {topBuffer.get(), RenderBufferAccess::WRITE}, {scratch.get(), RenderBufferAccess::WRITE}
    };
    worker.commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE, before, uint32_t(std::size(before)), nullptr, 0);
    worker.commandList->buildBottomLevelAS(bottom.get(), scratch->at(scratchOffset), bottomInfo);
    const RenderBufferBarrier between[] = {
        {bottomBuffer.get(), RenderBufferAccess::READ}, {scratch.get(), RenderBufferAccess::WRITE}
    };
    worker.commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE, between, uint32_t(std::size(between)), nullptr, 0);
    worker.commandList->buildTopLevelAS(top.get(), scratch->at(scratchOffset), instances->at(0), topInfo);
    worker.commandList->barriers(RenderBarrierStage::GRAPHICS_AND_COMPUTE, RenderBufferBarrier(topBuffer.get(), RenderBufferAccess::READ));
    worker.commandList->end();
    worker.execute();
    worker.wait();
    std::puts("Vulkan AS contracts: distinct 1/2-triangle ranges, queried BLAS address, scratch offset 13 built successfully.");
}
