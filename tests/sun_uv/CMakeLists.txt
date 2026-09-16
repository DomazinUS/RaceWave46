cmake_minimum_required(VERSION 3.20)
project(Wr64SunUvTests LANGUAGES C CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(NATIVE_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/native_sun_functions.c")
add_custom_command(OUTPUT "${NATIVE_SOURCE}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_native.py" "${WR64_ROOT}" "${NATIVE_SOURCE}"
    DEPENDS extract_native.py "${WR64_ROOT}/config/us.rev1.toml" "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_5.c"
    VERBATIM)
add_executable(wr64_sun_uv_test sun_uv_test.cpp "${NATIVE_SOURCE}" "${WR64_ROOT}/src/wr64_ultrawide.cpp")
target_compile_features(wr64_sun_uv_test PRIVATE cxx_std_20)
target_include_directories(wr64_sun_uv_test PRIVATE
    "${WR64_ROOT}/include" "${WR64_ROOT}/RecompiledFuncsPoint0"
    "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include" "${WR64_ROOT}/lib/rt64/src")
add_test(NAME native_sun_uv_scope_and_phase COMMAND wr64_sun_uv_test)
