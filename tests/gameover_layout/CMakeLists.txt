cmake_minimum_required(VERSION 3.20)
project(Wr64GameOverLayoutTests LANGUAGES C CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(NATIVE_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/native_gameover.c")
add_custom_command(OUTPUT "${NATIVE_SOURCE}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_native.py" "${WR64_ROOT}" "${NATIVE_SOURCE}"
    DEPENDS extract_native.py "${WR64_ROOT}/config/us.rev1.toml"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_6.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_17.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_18.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_22.c"
    VERBATIM)
add_executable(wr64_gameover_layout_test gameover_layout_test.cpp "${NATIVE_SOURCE}")
target_compile_features(wr64_gameover_layout_test PRIVATE cxx_std_20)
target_include_directories(wr64_gameover_layout_test PRIVATE
    "${WR64_ROOT}/RecompiledFuncsPoint0"
    "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include"
    "${WR64_ROOT}/lib/rt64/src")
add_test(NAME native_gameover_layout COMMAND wr64_gameover_layout_test)
