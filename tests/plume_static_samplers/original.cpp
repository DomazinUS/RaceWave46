// Fixture: unmodified D3D12DescriptorSet source blocks from bundled Plume.
// Unrelated source before and after must remain byte-identical.
        auto addDescriptor = [&](const RenderDescriptorRange &range, uint32_t descriptorCount) {
            descriptorTypes.emplace_back(range.type);

            bool isDynamicSampler = (range.type == RenderDescriptorRangeType::SAMPLER) && (range.immutableSampler == nullptr);
            if (isDynamicSampler) {
                descriptorHeapIndices.emplace_back(samplerDescriptorCount);
                samplerDescriptorCount += descriptorCount;
            }
            else {
                descriptorHeapIndices.emplace_back(viewDescriptorCount);
                viewDescriptorCount += descriptorCount;
            }
        };
// Unrelated source between blocks remains intact.
    void D3D12DescriptorSet::setSampler(uint32_t descriptorIndex, const RenderSampler *sampler) {
        if (sampler != nullptr) {
            const D3D12Sampler *interfaceSampler = static_cast<const D3D12Sampler *>(sampler);
            uint32_t descriptorIndexClamped = std::min(descriptorIndex, descriptorTypeMaxIndex);
            uint32_t descriptorIndexRelative = (descriptorIndex - descriptorIndexClamped);
            uint32_t descriptorHeapIndex = descriptorHeapIndices[descriptorIndexClamped];
            const D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = device->samplerHeapAllocator->getCPUHandleAt(samplerAllocation.offset + descriptorHeapIndex + descriptorIndexRelative);
            device->d3d->CreateSampler(&interfaceSampler->samplerDesc, cpuHandle);
        }
    }
// Unrelated source after the fixture.
