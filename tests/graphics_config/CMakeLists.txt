cmake_minimum_required(VERSION 3.20)
project(Wr64GraphicsConfigTests LANGUAGES CXX)
enable_testing()
get_filename_component(WR64_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
add_executable(wr64_graphics_config_test graphics_config_test.cpp
    "${WR64_ROOT}/lib/rt64/src/common/rt64_user_configuration.cpp")
target_compile_features(wr64_graphics_config_test PRIVATE cxx_std_20)
target_compile_definitions(wr64_graphics_config_test PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
target_include_directories(wr64_graphics_config_test PRIVATE
    "${WR64_ROOT}/include" "${WR64_ROOT}/lib/rt64/src"
    "${WR64_ROOT}/lib/rt64/src/contrib"
    "${WR64_ROOT}/lib/N64ModernRuntime/ultramodern/include")
add_test(NAME graphics_saved_and_live_settings COMMAND wr64_graphics_config_test)

add_executable(wr64_graphics_snapshot_test graphics_snapshot_test.cpp
    "${WR64_ROOT}/lib/N64ModernRuntime/ultramodern/src/renderer_context.cpp")
target_compile_features(wr64_graphics_snapshot_test PRIVATE cxx_std_20)
target_compile_definitions(wr64_graphics_snapshot_test PRIVATE NOMINMAX)
target_include_directories(wr64_graphics_snapshot_test PRIVATE
    "${WR64_ROOT}/lib/N64ModernRuntime/ultramodern/include"
    "${WR64_ROOT}/lib/N64ModernRuntime/thirdparty/concurrentqueue"
    "${WR64_ROOT}/lib/rt64/src/contrib")
add_test(NAME graphics_configuration_snapshot COMMAND wr64_graphics_snapshot_test)
