cmake_minimum_required(VERSION 3.20)
project(Wr64RtReflectionGpuTests LANGUAGES CXX)

option(WR64_RT_GPU_TESTS "Build optional headless D3D12 GPU regression probes" OFF)
if(NOT WR64_RT_GPU_TESTS)
    return()
endif()

if(NOT WIN32)
    message(FATAL_ERROR "The current headless GPU probes require Windows D3D12.")
endif()

get_filename_component(WR64_SOURCE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../.." ABSOLUTE)
set(WR64_RT64_SRC "${WR64_SOURCE_ROOT}/lib/rt64/src")
include("${WR64_SOURCE_ROOT}/tools/prepare_dxc.cmake")
wr64_prepare_dxc("${WR64_RT64_SRC}/contrib/dxc/bin/x64" WR64_DXC_BIN)
set(WR64_DXC "${WR64_DXC_BIN}/dxc.exe")
file(GLOB_RECURSE WR64_SHADER_HEADERS CONFIGURE_DEPENDS
    "${WR64_RT64_SRC}/shaders/*.hlsli" "${WR64_RT64_SRC}/shared/*.h")
set(WR64_WATER_COMPUTE_SHADERS)
foreach(shader RSPProcessCS RSPWorldCS)
    set(output "${CMAKE_CURRENT_BINARY_DIR}/${shader}.dxil")
    add_custom_command(OUTPUT "${output}"
        COMMAND "${WR64_DXC}" "-I${WR64_RT64_SRC}" "-I${WR64_RT64_SRC}/shaders"
            -E CSMain -T cs_6_3 -Wno-ignored-attributes
            "${WR64_RT64_SRC}/shaders/${shader}.hlsl" -Fo "${output}"
        DEPENDS "${WR64_RT64_SRC}/shaders/${shader}.hlsl" ${WR64_SHADER_HEADERS}
        VERBATIM)
    list(APPEND WR64_WATER_COMPUTE_SHADERS "${output}")
endforeach()
add_custom_target(wr64_water_compute_shaders DEPENDS ${WR64_WATER_COMPUTE_SHADERS})
add_executable(wr64_water_gpu water_gpu.cpp)
add_dependencies(wr64_water_gpu wr64_water_compute_shaders)
target_compile_features(wr64_water_gpu PRIVATE cxx_std_17)
target_compile_definitions(wr64_water_gpu PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
target_link_libraries(wr64_water_gpu PRIVATE d3d12 dxgi dxguid)

enable_testing()
add_executable(wr64_startup_gate startup_gate.cpp)
target_include_directories(wr64_startup_gate PRIVATE "${WR64_RT64_SRC}")
target_compile_features(wr64_startup_gate PRIVATE cxx_std_17)
add_test(NAME wr64_startup_gate COMMAND wr64_startup_gate)
set_tests_properties(wr64_startup_gate PROPERTIES LABELS "cpu;raytracing" TIMEOUT 10)
add_executable(wr64_sky_selection sky_selection.cpp)
target_compile_features(wr64_sky_selection PRIVATE cxx_std_17)
add_test(NAME wr64_sky_selection COMMAND wr64_sky_selection)
set_tests_properties(wr64_sky_selection PROPERTIES LABELS "cpu;raytracing" TIMEOUT 10)
add_executable(wr64_water_adjacency water_adjacency.cpp)
add_executable(wr64_motion_timing motion_timing.cpp)
target_compile_features(wr64_motion_timing PRIVATE cxx_std_17)
add_test(NAME wr64_motion_timing COMMAND wr64_motion_timing)
set_tests_properties(wr64_motion_timing PROPERTIES LABELS "cpu;motion" TIMEOUT 10)
target_compile_features(wr64_water_adjacency PRIVATE cxx_std_17)
add_test(NAME wr64_water_adjacency COMMAND wr64_water_adjacency)
set_tests_properties(wr64_water_adjacency PROPERTIES LABELS "cpu;raytracing" TIMEOUT 10)
add_test(NAME wr64_water_gpu COMMAND wr64_water_gpu
    "${CMAKE_CURRENT_BINARY_DIR}/RSPProcessCS.dxil"
    "${CMAKE_CURRENT_BINARY_DIR}/RSPWorldCS.dxil")
set_tests_properties(wr64_water_gpu PROPERTIES LABELS "gpu;d3d12" TIMEOUT 60)

# The scene probe reuses the exact AS helper and Plume backend from the game.
# A prebuilt Release Plume library avoids configuring the entire game here.
set(WR64_PLUME_LIBRARY "${WR64_SOURCE_ROOT}/build/rt64/src/contrib/plume/plume.lib"
    CACHE FILEPATH "Prebuilt Release Plume library for the optional scene GPU probe")
if(EXISTS "${WR64_PLUME_LIBRARY}")
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/scene_gpu.dxil"
        COMMAND "${WR64_DXC}" -E CSMain -T cs_6_5 -WX
            "${CMAKE_CURRENT_SOURCE_DIR}/scene_gpu.hlsl"
            -Fo "${CMAKE_CURRENT_BINARY_DIR}/scene_gpu.dxil"
        DEPENDS scene_gpu.hlsl VERBATIM)
    add_custom_target(wr64_scene_compute_shader
        DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/scene_gpu.dxil")
    add_executable(wr64_scene_gpu scene_gpu.cpp
        "${WR64_RT64_SRC}/render/rt64_wr64_rt_scene.cpp"
        "${WR64_RT64_SRC}/render/rt64_render_worker.cpp")
    add_dependencies(wr64_scene_gpu wr64_scene_compute_shader)
    target_compile_features(wr64_scene_gpu PRIVATE cxx_std_17)
    target_compile_definitions(wr64_scene_gpu PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
    target_include_directories(wr64_scene_gpu PRIVATE "${WR64_RT64_SRC}"
        "${WR64_RT64_SRC}/contrib/plume"
        "${WR64_RT64_SRC}/contrib/plume/contrib/D3D12MemoryAllocator/include")
    target_link_libraries(wr64_scene_gpu PRIVATE "${WR64_PLUME_LIBRARY}"
        d3d12 dxgi dxguid user32)
    add_test(NAME wr64_scene_gpu COMMAND wr64_scene_gpu
        "${CMAKE_CURRENT_BINARY_DIR}/scene_gpu.dxil")
    set_tests_properties(wr64_scene_gpu PROPERTIES
        LABELS "gpu;d3d12;raytracing" TIMEOUT 60 SKIP_RETURN_CODE 77)
else()
    message(STATUS "Scene GPU probe omitted: set WR64_PLUME_LIBRARY to a built Release plume.lib")
endif()

# Exercise the embedded world shader through the production ShaderLibrary and
# VertexProcessor, including the actual push-constant range and descriptor set.
set(WR64_RT64_LIBRARY "${WR64_SOURCE_ROOT}/build/rt64/rt64.lib"
    CACHE FILEPATH "Prebuilt Release RT64 library for the production world GPU probe")
if(EXISTS "${WR64_RT64_LIBRARY}" AND EXISTS "${WR64_PLUME_LIBRARY}")
    get_filename_component(WR64_RT64_BUILD "${WR64_RT64_LIBRARY}" DIRECTORY)
    foreach(probe world_pipeline raster raster_submission)
        add_executable(wr64_${probe}_gpu ${probe}_gpu.cpp)
        target_compile_features(wr64_${probe}_gpu PRIVATE cxx_std_17)
        target_compile_definitions(wr64_${probe}_gpu PRIVATE HLSL_CPU NOMINMAX WIN32_LEAN_AND_MEAN)
        target_include_directories(wr64_${probe}_gpu PRIVATE "${WR64_RT64_SRC}"
            "${WR64_RT64_SRC}/contrib" "${WR64_RT64_SRC}/contrib/plume"
            "${WR64_RT64_SRC}/contrib/hlslpp/include" "${WR64_RT64_SRC}/contrib/imgui"
            "${WR64_RT64_SRC}/contrib/dxc/inc"
            "${WR64_RT64_SRC}/contrib/plume/contrib/volk"
            "${WR64_RT64_SRC}/contrib/plume/contrib/Vulkan-Headers/include"
            "${WR64_RT64_SRC}/contrib/plume/contrib/VulkanMemoryAllocator/include"
            "${WR64_RT64_SRC}/contrib/re-spirv/external/SPIRV-Headers/include"
            "${WR64_RT64_SRC}/contrib/plume/contrib/D3D12MemoryAllocator/include")
        target_link_libraries(wr64_${probe}_gpu PRIVATE "${WR64_RT64_LIBRARY}"
            "${WR64_PLUME_LIBRARY}" "${WR64_RT64_BUILD}/src/contrib/re-spirv/re-spirv.lib"
            "${WR64_RT64_BUILD}/src/contrib/zstd/build/cmake/lib/zstd_static.lib"
            "${WR64_RT64_SRC}/contrib/dxc/lib/x64/dxcompiler.lib" d3d12 dxgi dxguid user32)
        add_test(NAME wr64_${probe}_gpu COMMAND "${CMAKE_COMMAND}" -E env
            "PATH=${WR64_DXC_BIN};$ENV{PATH}"
            "$<TARGET_FILE:wr64_${probe}_gpu>")
        set_tests_properties(wr64_${probe}_gpu PROPERTIES LABELS "gpu;d3d12" TIMEOUT 60)
    endforeach()
    add_test(NAME wr64_southern_ramp_gpu COMMAND "${CMAKE_COMMAND}" -E env
        "PATH=${WR64_DXC_BIN};$ENV{PATH}"
        "$<TARGET_FILE:wr64_raster_gpu>" "southern_ramp" "--southern-ramp-only")
    set_tests_properties(wr64_southern_ramp_gpu PROPERTIES LABELS "gpu;d3d12;raytracing;solid-receivers"
        TIMEOUT 120 SKIP_RETURN_CODE 77)
    add_test(NAME wr64_raster_sky_gpu COMMAND "${CMAKE_COMMAND}" -E env
        "PATH=${WR64_DXC_BIN};$ENV{PATH}"
        "$<TARGET_FILE:wr64_raster_gpu>" "raster_sky" "--raster-sky-only")
    set_tests_properties(wr64_raster_sky_gpu PROPERTIES LABELS "gpu;d3d12;raster-only" TIMEOUT 180)
    add_test(NAME wr64_solid_self_gpu COMMAND "${CMAKE_COMMAND}" -E env
        "PATH=${WR64_DXC_BIN};$ENV{PATH}"
        "$<TARGET_FILE:wr64_raster_gpu>" "solid_self" "--solid-self-only")
    set_tests_properties(wr64_solid_self_gpu PROPERTIES LABELS "gpu;d3d12;raytracing;solid-receivers"
        TIMEOUT 120 SKIP_RETURN_CODE 77)
    # This suite compiles multiple real shader/MSAA variants; its individual
    # async readiness guard already allows 120 seconds on a cold driver cache.
    set_tests_properties(wr64_raster_gpu PROPERTIES LABELS "gpu;d3d12;raytracing" SKIP_RETURN_CODE 77 TIMEOUT 240)
    add_test(NAME wr64_two_player_gpu COMMAND "${CMAKE_COMMAND}" -E env
        "PATH=${WR64_DXC_BIN};$ENV{PATH}"
        "$<TARGET_FILE:wr64_raster_gpu>" "two_player" "--two-player-only")
    set_tests_properties(wr64_two_player_gpu PROPERTIES LABELS "gpu;d3d12;raytracing;two-player"
        TIMEOUT 240 SKIP_RETURN_CODE 77)
endif()
