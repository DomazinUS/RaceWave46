# Selected WR64 and native framebuffer SPIR-V shaders require newer code
# generation. Keep that compiler and its DLLs separate from the pinned
# Direct3D/default-SPIR-V toolchain, and verify downloaded archive hashes.
set(RT64_WR64_VULKAN_DXC "" CACHE FILEPATH "Override DXC for WR64 Vulkan RT and native framebuffer shaders")

function(wr64_find_vulkan_dxc)
    if (RT64_WR64_VULKAN_DXC)
        if (NOT EXISTS "${RT64_WR64_VULKAN_DXC}")
            message(FATAL_ERROR "RT64_WR64_VULKAN_DXC does not exist: ${RT64_WR64_VULKAN_DXC}")
        endif()
        set(WR64_VULKAN_DXC "${RT64_WR64_VULKAN_DXC}" PARENT_SCOPE)
        return()
    endif()

    set(version "1.9.2607")
    set(root "${CMAKE_BINARY_DIR}/_deps/wr64-dxc-${version}")
    if (CMAKE_HOST_WIN32)
        set(archive "dxc_2026_07_29.zip")
        set(sha256 "a1dfb116ba3eeae6a1582291b53a8e7bf65ad760676bd3194685c8f7367cd241")
        set(compiler "${root}/bin/x64/dxc.exe")
    elseif (CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux" AND CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "^(x86_64|AMD64)$")
        set(archive "linux_dxc_2026_07_29.x86_x64.tar.gz")
        set(sha256 "55665c87824051ed4774ff3280a79ccbbb7d39243b9736ca5e98222134112d54")
        # This official archive contains a named top-level directory; the
        # Windows ZIP instead places bin/ directly at its root.
        set(compiler "${root}/linux_dxc_2026_07_29.x86_x64/bin/dxc")
    else()
        message(FATAL_ERROR "Set RT64_WR64_VULKAN_DXC to a recent SPIR-V-enabled DXC for this build host")
    endif()

    if (NOT EXISTS "${compiler}")
        set(download "${CMAKE_BINARY_DIR}/_deps/${archive}")
        file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/_deps")
        if (EXISTS "${download}")
            file(SHA256 "${download}" actual_hash)
        endif()
        if (NOT actual_hash STREQUAL sha256)
            message(STATUS "Downloading pinned DXC ${version} for WR64 Vulkan shaders only")
            file(DOWNLOAD
                "https://github.com/microsoft/DirectXShaderCompiler/releases/download/v${version}/${archive}"
                "${download}" EXPECTED_HASH "SHA256=${sha256}" TLS_VERIFY ON
                TIMEOUT 300 INACTIVITY_TIMEOUT 30 STATUS download_status)
            list(GET download_status 0 download_code)
            if (NOT download_code EQUAL 0)
                message(FATAL_ERROR "WR64 Vulkan DXC download failed: ${download_status}")
            endif()
        endif()
        file(MAKE_DIRECTORY "${root}")
        file(ARCHIVE_EXTRACT INPUT "${download}" DESTINATION "${root}")
        if (NOT EXISTS "${compiler}")
            message(FATAL_ERROR "Pinned DXC archive did not contain ${compiler}; set RT64_WR64_VULKAN_DXC explicitly")
        endif()
    endif()
    set(WR64_VULKAN_DXC "${compiler}" PARENT_SCOPE)
endfunction()

function(build_wr64_shader_spirv TARGETOBJ SHADERNAME ENTRYPOINT PROFILE VARIANT)
    set(input "${PROJECT_SOURCE_DIR}/src/shaders/${SHADERNAME}.hlsl")
    set(output "${CMAKE_BINARY_DIR}/src/shaders/${VARIANT}.hlsl")
    set(options -spirv -fspv-target-env=vulkan1.2
        -fspv-extension=SPV_KHR_ray_query -fspv-extension=SPV_EXT_descriptor_indexing
        -fvk-use-dx-layout "-I${PROJECT_SOURCE_DIR}/src" -E ${ENTRYPOINT} -T ${PROFILE})
    if (ENTRYPOINT STREQUAL "VSMain")
        list(APPEND options -fvk-invert-y)
    endif()
    # These large shaders must not compile together: even independent compiler
    # invocations can exhaust host commit. The dependency also serializes Make
    # generators, while the named pool documents/enforces the Ninja constraint.
    get_property(previous GLOBAL PROPERTY WR64_PREVIOUS_SPIRV_OUTPUT)
    add_custom_command(OUTPUT "${output}.spv"
        COMMAND "${WR64_VULKAN_DXC}" ${options} ${ARGN} "${input}" -Fo "${output}.spv"
        DEPENDS "${input}" "${WR64_VULKAN_DXC}" ${RT64_SHADER_INCLUDE_DEPENDENCIES} ${previous}
        JOB_POOL wr64_spirv VERBATIM)
    set_property(GLOBAL PROPERTY WR64_PREVIOUS_SPIRV_OUTPUT "${output}.spv")
    add_custom_command(OUTPUT "${output}.spirv.c"
        COMMAND file_to_c "${output}.spv" ${VARIANT}BlobSPIRV "${output}.spirv.c" "${output}.spirv.h"
        DEPENDS "${output}.spv" file_to_c
        BYPRODUCTS "${output}.spirv.h" VERBATIM)
    target_sources(${TARGETOBJ} PRIVATE "${output}.spirv.c")
endfunction()
