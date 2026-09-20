cmake_minimum_required(VERSION 3.20)
project(Wr64PresentPacingTests LANGUAGES CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(PRESENT_IMPLEMENTATION "${CMAKE_CURRENT_BINARY_DIR}/present_implementation.inc")
set(PACING_IMPLEMENTATION "${CMAKE_CURRENT_BINARY_DIR}/pacing_implementation.inc")
add_custom_command(OUTPUT "${PRESENT_IMPLEMENTATION}" "${PACING_IMPLEMENTATION}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_implementation.py"
        "${WR64_ROOT}" "${CMAKE_CURRENT_BINARY_DIR}"
    DEPENDS extract_implementation.py
        "${WR64_ROOT}/lib/rt64/src/contrib/plume/plume_d3d12.cpp"
        "${WR64_ROOT}/lib/rt64/src/hle/rt64_present_queue.cpp"
    VERBATIM)
add_executable(wr64_present_pacing_test present_pacing_test.cpp
    "${PRESENT_IMPLEMENTATION}" "${PACING_IMPLEMENTATION}")
target_compile_features(wr64_present_pacing_test PRIVATE cxx_std_17)
target_compile_definitions(wr64_present_pacing_test PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
target_include_directories(wr64_present_pacing_test PRIVATE
    "${CMAKE_CURRENT_BINARY_DIR}" "${WR64_ROOT}/lib/rt64/src")
add_test(NAME present_vsync_and_pacing COMMAND wr64_present_pacing_test)
