# Keep Plume's physical descriptor offsets consistent with its D3D12 root
# signature. Immutable samplers retain public descriptor indices, but are
# represented only by static samplers and occupy neither descriptor heap.
# The vendored Plume directory can be a submodule or a flattened source copy.

function(_rt64_plume_replace_exact content_var original replacement description)
    set(content "${${content_var}}")
    string(FIND "${content}" "${original}" original_at)
    string(FIND "${content}" "${replacement}" replacement_at)
    if(NOT original_at EQUAL -1 AND replacement_at EQUAL -1)
        set(expected "${original}")
        set(needs_patch TRUE)
    elseif(original_at EQUAL -1 AND NOT replacement_at EQUAL -1)
        set(expected "${replacement}")
        set(needs_patch FALSE)
    else()
        message(FATAL_ERROR "Plume static-sampler patch: unexpected ${description} source. Review upstream plume_d3d12.cpp before updating this exact-source patch.")
    endif()

    # Never silently rewrite several similar methods after an upstream change.
    string(REPLACE "${expected}" "" without_expected "${content}")
    string(LENGTH "${content}" source_size)
    string(LENGTH "${without_expected}" remaining_size)
    string(LENGTH "${expected}" expected_size)
    math(EXPR matched_size "${source_size} - ${remaining_size}")
    if(NOT matched_size EQUAL expected_size)
        message(FATAL_ERROR "Plume static-sampler patch: expected exactly one ${description} block.")
    endif()
    if(needs_patch)
        string(REPLACE "${original}" "${replacement}" content "${content}")
    endif()
    set("${content_var}" "${content}" PARENT_SCOPE)
endfunction()

function(rt64_patch_plume_static_samplers source_file)
    if(NOT EXISTS "${source_file}")
        message(FATAL_ERROR "Plume static-sampler patch: source is missing: ${source_file}")
    endif()
    file(READ "${source_file}" original_source)
    # CMake normalizes CRLF while reading text; inspect bytes for the original
    # convention so a patched Windows checkout retains its existing newlines.
    file(READ "${source_file}" source_bytes HEX)
    string(FIND "${source_bytes}" "0d0a" crlf_at)
    set(source "${original_source}")
    string(REPLACE "\r\n" "\n" source "${source}")

    set(original_offsets [=[        auto addDescriptor = [&](const RenderDescriptorRange &range, uint32_t descriptorCount) {
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
        };]=])
    set(fixed_offsets [=[        auto addDescriptor = [&](const RenderDescriptorRange &range, uint32_t descriptorCount) {
            descriptorTypes.emplace_back(range.type);

            // Preserve public descriptor indices, but static samplers consume
            // no descriptor-heap space. The root signature filters them out of
            // both tables, so subsequent view offsets must do the same.
            if (range.immutableSampler != nullptr) {
                descriptorHeapIndices.emplace_back(UINT32_MAX);
            }
            else if (range.type == RenderDescriptorRangeType::SAMPLER) {
                descriptorHeapIndices.emplace_back(samplerDescriptorCount);
                samplerDescriptorCount += descriptorCount;
            }
            else {
                descriptorHeapIndices.emplace_back(viewDescriptorCount);
                viewDescriptorCount += descriptorCount;
            }
        };]=])
    set(original_sampler [=[    void D3D12DescriptorSet::setSampler(uint32_t descriptorIndex, const RenderSampler *sampler) {
        if (sampler != nullptr) {
            const D3D12Sampler *interfaceSampler = static_cast<const D3D12Sampler *>(sampler);
            uint32_t descriptorIndexClamped = std::min(descriptorIndex, descriptorTypeMaxIndex);
            uint32_t descriptorIndexRelative = (descriptorIndex - descriptorIndexClamped);
            uint32_t descriptorHeapIndex = descriptorHeapIndices[descriptorIndexClamped];
            const D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = device->samplerHeapAllocator->getCPUHandleAt(samplerAllocation.offset + descriptorHeapIndex + descriptorIndexRelative);
            device->d3d->CreateSampler(&interfaceSampler->samplerDesc, cpuHandle);
        }
    }]=])
    set(fixed_sampler [=[    void D3D12DescriptorSet::setSampler(uint32_t descriptorIndex, const RenderSampler *sampler) {
        if (sampler != nullptr) {
            const D3D12Sampler *interfaceSampler = static_cast<const D3D12Sampler *>(sampler);
            uint32_t descriptorIndexClamped = std::min(descriptorIndex, descriptorTypeMaxIndex);
            uint32_t descriptorIndexRelative = (descriptorIndex - descriptorIndexClamped);
            uint32_t descriptorHeapIndex = descriptorHeapIndices[descriptorIndexClamped];
            if (descriptorHeapIndex == UINT32_MAX) {
                assert(false && "Immutable samplers cannot be updated.");
                return;
            }
            const D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = device->samplerHeapAllocator->getCPUHandleAt(samplerAllocation.offset + descriptorHeapIndex + descriptorIndexRelative);
            device->d3d->CreateSampler(&interfaceSampler->samplerDesc, cpuHandle);
        }
    }]=])

    # Validate both blocks before writing, including when only one is patched.
    _rt64_plume_replace_exact(source "${original_offsets}" "${fixed_offsets}" "descriptor offset")
    _rt64_plume_replace_exact(source "${original_sampler}" "${fixed_sampler}" "sampler update")
    if(NOT source STREQUAL original_source)
        # file(WRITE) uses native newlines on Windows. Explicit configuration
        # output preserves LF checkouts as well as CRLF checkouts; a single
        # substitution prevents interpreting any @tokens@ inside C++ source.
        if(crlf_at EQUAL -1)
            set(newline_style LF)
        else()
            set(newline_style CRLF)
        endif()
        file(CONFIGURE OUTPUT "${source_file}" CONTENT "@source@"
            @ONLY NEWLINE_STYLE "${newline_style}")
        message(STATUS "Applied Plume D3D12 static-sampler descriptor fix")
    endif()
endfunction()

# Standalone entry point used by the regression fixture; normal builds include
# this module and pass their own vendored source path explicitly.
if(CMAKE_SCRIPT_MODE_FILE STREQUAL CMAKE_CURRENT_LIST_FILE)
    if(NOT DEFINED RT64_PLUME_D3D12_SOURCE)
        message(FATAL_ERROR "Set RT64_PLUME_D3D12_SOURCE to the source file to patch.")
    endif()
    rt64_patch_plume_static_samplers("${RT64_PLUME_D3D12_SOURCE}")
endif()
