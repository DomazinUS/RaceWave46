cmake_minimum_required(VERSION 3.20)
project(Wr64DolphinSunShadowTests LANGUAGES C CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(NATIVE_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/native_sun.c")
add_custom_command(OUTPUT "${NATIVE_SOURCE}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_native.py" "${WR64_ROOT}" "${NATIVE_SOURCE}"
    DEPENDS extract_native.py "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_5.c" VERBATIM)
add_executable(wr64_dolphin_sun_shadow_test native_shadow_test.cpp "${NATIVE_SOURCE}")
target_compile_features(wr64_dolphin_sun_shadow_test PRIVATE cxx_std_20)
target_include_directories(wr64_dolphin_sun_shadow_test PRIVATE "${WR64_ROOT}/include"
    "${WR64_ROOT}/RecompiledFuncsPoint0" "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include" "${WR64_ROOT}/lib/rt64/src")
if(MSVC)
    target_compile_options(wr64_dolphin_sun_shadow_test PRIVATE /fp:strict
        $<$<COMPILE_LANGUAGE:CXX>:/W4> $<$<COMPILE_LANGUAGE:C>:/W0>)
endif()
set(WR64_DOLPHIN_ARCHIVE "" CACHE FILEPATH "Optional private eight MiB word-swapped RDRAM capture")
if(WR64_DOLPHIN_ARCHIVE)
    add_test(NAME dolphin_shadow_actual_native_bearing COMMAND wr64_dolphin_sun_shadow_test "${WR64_DOLPHIN_ARCHIVE}")
endif()
