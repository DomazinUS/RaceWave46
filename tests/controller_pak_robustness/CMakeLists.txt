cmake_minimum_required(VERSION 3.20)
project(Wr64ControllerPakRobustness LANGUAGES CXX)
enable_testing()
get_filename_component(WR64_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
add_executable(wr64_controller_pak_robustness controller_pak_robustness.cpp
    "${WR64_ROOT}/src/controller_pak.cpp"
    "${WR64_ROOT}/lib/N64ModernRuntime/librecomp/src/files.cpp")
target_compile_features(wr64_controller_pak_robustness PRIVATE cxx_std_20)
target_include_directories(wr64_controller_pak_robustness PRIVATE stubs
    "${WR64_ROOT}/include"
    "${WR64_ROOT}/lib/N64ModernRuntime/librecomp/include"
    "${WR64_ROOT}/lib/N64ModernRuntime/librecomp/include/librecomp")
add_test(NAME controller_pak_corruption_and_failed_writes
    COMMAND wr64_controller_pak_robustness "${CMAKE_CURRENT_BINARY_DIR}/isolated-pak")
