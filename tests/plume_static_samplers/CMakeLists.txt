cmake_minimum_required(VERSION 3.20)
project(Wr64PlumeStaticSamplerPatchTests LANGUAGES NONE)

find_package(Python3 REQUIRED COMPONENTS Interpreter)
get_filename_component(WR64_SOURCE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../.." ABSOLUTE)
enable_testing()
add_test(NAME plume_static_sampler_patch
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/patch_test.py"
        "${CMAKE_COMMAND}"
        "${WR64_SOURCE_ROOT}/lib/rt64/cmake/patch_plume_static_samplers.cmake"
        "${WR64_SOURCE_ROOT}/lib/rt64/src/contrib/plume/plume_d3d12.cpp")
set_tests_properties(plume_static_sampler_patch PROPERTIES TIMEOUT 30)
