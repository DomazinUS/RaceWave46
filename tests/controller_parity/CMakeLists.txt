cmake_minimum_required(VERSION 3.20)
project(Wr64ControllerParityTests LANGUAGES CXX)

enable_testing()
get_filename_component(WR64_SOURCE_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
add_executable(wr64_controller_parity_test
    controller_parity_test.cpp
    "${WR64_SOURCE_ROOT}/src/wr64_input.cpp")
target_compile_features(wr64_controller_parity_test PRIVATE cxx_std_20)
target_compile_definitions(wr64_controller_parity_test PRIVATE
    WR64_ENABLE_FRONTEND
    WR64_TEST_CONFIG_DIR="${CMAKE_CURRENT_LIST_DIR}/fixtures")
target_include_directories(wr64_controller_parity_test PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/stubs"
    "${WR64_SOURCE_ROOT}/include"
    "${WR64_SOURCE_ROOT}/lib/N64ModernRuntime/ultramodern/include")
add_test(NAME controller_parity_callbacks COMMAND wr64_controller_parity_test)
add_test(NAME controller_parity_sdl_failure COMMAND wr64_controller_parity_test --sdl-failure)

option(WR64_TEST_SDL_INTEGRATION "Test actual RecompFrontend with isolated SDL virtual pads (Windows/MSVC)" OFF)
if(WR64_TEST_SDL_INTEGRATION)
    if(NOT MSVC)
        message(FATAL_ERROR "SDL virtual integration uses the vendored Windows x64 SDL2 import library and requires MSVC.")
    endif()
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../controller_integration" controller_integration)
endif()
