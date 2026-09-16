cmake_minimum_required(VERSION 3.20)
project(Wr64RasterShadowMathTests LANGUAGES CXX)

get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
find_package(Python3 COMPONENTS Interpreter REQUIRED)
set(DISTANCE_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/distance_production.inc")
add_custom_command(OUTPUT "${DISTANCE_SOURCE}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/prepare_distance.py" "${WR64_ROOT}" "${DISTANCE_SOURCE}"
    DEPENDS prepare_distance.py
        "${WR64_ROOT}/lib/rt64/src/hle/rt64_state.cpp"
        "${WR64_ROOT}/lib/rt64/src/hle/rt64_workload.cpp"
        "${WR64_ROOT}/lib/rt64/src/hle/rt64_workload.h"
        "${WR64_ROOT}/lib/rt64/src/render/rt64_framebuffer_renderer.cpp"
    VERBATIM)
add_executable(wr64_raster_shadow_math math_test.cpp)
target_compile_features(wr64_raster_shadow_math PRIVATE cxx_std_17)
target_include_directories(wr64_raster_shadow_math PRIVATE "${WR64_ROOT}/lib/rt64/src")
if(MSVC)
    target_compile_options(wr64_raster_shadow_math PRIVATE /W4 /WX /fp:strict)
else()
    target_compile_options(wr64_raster_shadow_math PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
enable_testing()
add_test(NAME raster_shadow_stable_projection COMMAND wr64_raster_shadow_math)
set_tests_properties(raster_shadow_stable_projection PROPERTIES LABELS "cpu;raster-shadows" TIMEOUT 10)
add_executable(wr64_raster_shadow_distance distance_test.cpp "${DISTANCE_SOURCE}")
target_compile_features(wr64_raster_shadow_distance PRIVATE cxx_std_17)
target_include_directories(wr64_raster_shadow_distance PRIVATE "${WR64_ROOT}/lib/rt64/src" "${CMAKE_CURRENT_BINARY_DIR}")
if(MSVC)
    target_compile_options(wr64_raster_shadow_distance PRIVATE /W4 /WX /fp:strict)
else()
    target_compile_options(wr64_raster_shadow_distance PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
add_test(NAME raster_shadow_distance COMMAND wr64_raster_shadow_distance)
set_tests_properties(raster_shadow_distance PROPERTIES LABELS "cpu;raster-shadows" TIMEOUT 10)
