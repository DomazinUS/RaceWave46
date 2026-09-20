cmake_minimum_required(VERSION 3.20)
project(Wr64WakeInterpolationTests LANGUAGES CXX)
enable_testing()
get_filename_component(WR64_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
find_package(Python3 COMPONENTS Interpreter REQUIRED)
set(WAKE_SOURCE "${WR64_ROOT}/lib/rt64/src/hle/rt64_game_frame.cpp")
set(WAKE_TEST_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/spray_test.inc")
add_custom_command(OUTPUT "${WAKE_TEST_SOURCE}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_spray_test.py"
        "${WAKE_SOURCE}" "${WAKE_TEST_SOURCE}"
    DEPENDS "${WAKE_SOURCE}" "${CMAKE_CURRENT_LIST_DIR}/extract_spray_test.py"
    VERBATIM)
add_executable(wr64_wake_interpolation_test wake_interpolation_test.cpp "${WAKE_TEST_SOURCE}")
target_compile_features(wr64_wake_interpolation_test PRIVATE cxx_std_17)
target_compile_definitions(wr64_wake_interpolation_test PRIVATE HLSL_CPU)
target_include_directories(wr64_wake_interpolation_test PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
    "${WR64_ROOT}/lib/rt64/src"
    "${WR64_ROOT}/lib/rt64/src/contrib/hlslpp/include")
add_test(NAME native_wake_producer_ownership COMMAND wr64_wake_interpolation_test)
