cmake_minimum_required(VERSION 3.20)
project(Wr64EndingRTTests LANGUAGES C CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(NATIVE_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/native_ending.c")
add_custom_command(OUTPUT "${NATIVE_SOURCE}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_native.py" "${WR64_ROOT}" "${NATIVE_SOURCE}"
    DEPENDS extract_native.py "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_5.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_6.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_19.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_23.c" VERBATIM)
add_executable(wr64_ending_rt_test ending_test.cpp "${NATIVE_SOURCE}")
target_compile_features(wr64_ending_rt_test PRIVATE cxx_std_20)
target_include_directories(wr64_ending_rt_test PRIVATE "${WR64_ROOT}/include"
    "${WR64_ROOT}/RecompiledFuncsPoint0" "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include"
    "${WR64_ROOT}/lib/rt64/src")
if(MSVC)
    target_compile_options(wr64_ending_rt_test PRIVATE /fp:strict
        $<$<COMPILE_LANGUAGE:CXX>:/W4> $<$<COMPILE_LANGUAGE:C>:/W0>)
endif()
add_test(NAME ending_native_scope_light_and_viewport COMMAND wr64_ending_rt_test)
