cmake_minimum_required(VERSION 3.20)
project(Wr64LibrashaderPresetTests LANGUAGES CXX)
enable_testing()
get_filename_component(WR64_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
add_executable(wr64_librashader_presets_test librashader_presets_test.cpp)
target_compile_features(wr64_librashader_presets_test PRIVATE cxx_std_20)
target_include_directories(wr64_librashader_presets_test PRIVATE
    "${WR64_ROOT}/include"
    "${WR64_ROOT}/lib/rt64/src"
    "${WR64_ROOT}/lib/N64ModernRuntime/thirdparty")
add_test(NAME librashader_presets
    COMMAND wr64_librashader_presets_test "${WR64_ROOT}/assets/shaders")
