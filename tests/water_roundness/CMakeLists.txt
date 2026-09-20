cmake_minimum_required(VERSION 3.20)
project(Wr64WaterRoundnessTests LANGUAGES C CXX)
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
# Reuse the exact native producer extraction/build dependencies without changing
# or running the existing sky tests.
add_subdirectory("../sunny_two_player_sky" native_support EXCLUDE_FROM_ALL)
get_target_property(NATIVE_SOURCES wr64_native_rt_admission_test SOURCES)
list(FILTER NATIVE_SOURCES EXCLUDE REGEX "rt_admission_test.cpp$")
get_target_property(NATIVE_INCLUDES wr64_native_rt_admission_test INCLUDE_DIRECTORIES)
set(SUPPORT "${CMAKE_CURRENT_BINARY_DIR}/native_roundness_support.inc")
set(MATCHING "${CMAKE_CURRENT_BINARY_DIR}/roundness_matching.inc")
add_custom_command(OUTPUT "${SUPPORT}" "${MATCHING}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_support.py"
        "${WR64_ROOT}/tests/sunny_two_player_sky/rt_admission_test.cpp" "${SUPPORT}"
        "${WR64_ROOT}" "${MATCHING}"
    DEPENDS extract_support.py "${WR64_ROOT}/tests/sunny_two_player_sky/rt_admission_test.cpp"
        "${WR64_ROOT}/lib/rt64/src/hle/rt64_workload_queue.cpp"
        "${WR64_ROOT}/lib/rt64/src/hle/rt64_state.cpp"
        "${WR64_ROOT}/lib/rt64/src/hle/rt64_game_frame.cpp"
        "${WR64_ROOT}/lib/rt64/src/hle/rt64_workload.cpp" VERBATIM)
add_executable(wr64_water_roundness_test roundness.cpp "${SUPPORT}" "${MATCHING}" ${NATIVE_SOURCES})
target_compile_features(wr64_water_roundness_test PRIVATE cxx_std_20)
target_include_directories(wr64_water_roundness_test PRIVATE ${NATIVE_INCLUDES}
    "${CMAKE_CURRENT_BINARY_DIR}" "${WR64_ROOT}/tests/sunny_two_player_sky")
