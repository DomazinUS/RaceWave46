cmake_minimum_required(VERSION 3.20)
project(Wr64CpuLogoTests LANGUAGES C CXX)
enable_testing()
get_filename_component(WR64_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
find_package(Python3 COMPONENTS Interpreter REQUIRED)
set(NATIVE "${CMAKE_CURRENT_BINARY_DIR}/native_logo.c")
add_custom_command(OUTPUT "${NATIVE}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_logo.py" "${WR64_ROOT}" "${NATIVE}"
    DEPENDS "${CMAKE_CURRENT_LIST_DIR}/extract_logo.py" "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_6.c"
    VERBATIM)
add_executable(wr64_cpu_logo_test cpu_logo_test.cpp "${NATIVE}"
    "${WR64_ROOT}/src/wr64_render_provenance.cpp")
target_compile_features(wr64_cpu_logo_test PRIVATE cxx_std_20)
target_compile_definitions(wr64_cpu_logo_test PRIVATE WR64_ENABLE_RT64 NOMINMAX)
target_include_directories(wr64_cpu_logo_test PRIVATE
    "${WR64_ROOT}/include" "${WR64_ROOT}/RecompiledFuncsPoint0"
    "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include"
    "${WR64_ROOT}/lib/rt64/src")
add_test(NAME cpu_logo_identity_and_aspect COMMAND wr64_cpu_logo_test)
