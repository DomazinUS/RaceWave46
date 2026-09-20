cmake_minimum_required(VERSION 3.20)
project(Wr64RTSolidReceiverTests LANGUAGES CXX)
enable_testing()
find_package(Python3 REQUIRED COMPONENTS Interpreter)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(WR64_RECEIVER_SOURCE "${WR64_ROOT}/lib/rt64/src/render/rt64_framebuffer_renderer.cpp")
add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/native_receiver_selection.inl"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract.py"
        "${WR64_ROOT}" "${CMAKE_CURRENT_BINARY_DIR}/native_receiver_selection.inl"
    DEPENDS extract.py "${WR64_RECEIVER_SOURCE}" VERBATIM)
add_executable(wr64_solid_receiver_test receiver_test.cpp "${CMAKE_CURRENT_BINARY_DIR}/native_receiver_selection.inl")
target_compile_features(wr64_solid_receiver_test PRIVATE cxx_std_17)
target_include_directories(wr64_solid_receiver_test PRIVATE "${CMAKE_CURRENT_BINARY_DIR}" "${WR64_ROOT}/lib/rt64/src")
add_test(NAME rt_native_solid_receivers COMMAND wr64_solid_receiver_test)
