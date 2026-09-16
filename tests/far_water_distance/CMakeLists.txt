cmake_minimum_required(VERSION 3.20)
project(Wr64FarWaterDistanceTests LANGUAGES C CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(WR64_WATER_ARCHIVE "" CACHE PATH "Private native 500-vertex/876-triangle archive")
set(WR64_WATER_BASELINE "" CACHE FILEPATH "Explicit pre-feature rt64_game_frame.cpp baseline")
set(WR64_WATER_PREVIOUS "" CACHE FILEPATH "Validated three-mode rt64_game_frame.cpp baseline")
set(WR64_SUNNY_CAPTURES "" CACHE STRING "Optional semicolon-separated native Sunny RAM archives")
if(NOT WR64_WATER_ARCHIVE OR NOT WR64_WATER_BASELINE OR NOT WR64_WATER_PREVIOUS)
    message(FATAL_ERROR "Provide WR64_WATER_ARCHIVE, WR64_WATER_BASELINE and WR64_WATER_PREVIOUS")
endif()
set(FIXTURE "${CMAKE_CURRENT_BINARY_DIR}/fixture")
set(FIXTURE_OUTPUTS "${FIXTURE}/water_fixture.inc" "${FIXTURE}/water_production.inc"
    "${FIXTURE}/water_baseline.inc" "${FIXTURE}/water_previous.inc" "${FIXTURE}/water_previous_header.inc" "${FIXTURE}/water_capture.inc" "${FIXTURE}/native_water.txt")
add_custom_command(OUTPUT ${FIXTURE_OUTPUTS}
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/prepare.py" --archive "${WR64_WATER_ARCHIVE}"
        --baseline "${WR64_WATER_BASELINE}" --previous "${WR64_WATER_PREVIOUS}" --output "${FIXTURE}"
    DEPENDS prepare.py "${WR64_ROOT}/tests/water_dense_recovery/prepare.py" "${WR64_ROOT}/tests/water_dense_recovery/recovery.cpp"
        "${WR64_ROOT}/lib/rt64/src/hle/rt64_game_frame.cpp" "${WR64_ROOT}/lib/rt64/src/hle/rt64_state.cpp"
        "${WR64_ROOT}/lib/rt64/src/hle/rt64_workload.cpp" "${WR64_WATER_BASELINE}" "${WR64_WATER_PREVIOUS}" VERBATIM)
set(NATIVE_CAMERA "${CMAKE_CURRENT_BINARY_DIR}/native_camera.c")
add_custom_command(OUTPUT "${NATIVE_CAMERA}"
    COMMAND "${Python3_EXECUTABLE}" "${WR64_ROOT}/tests/camera_fov/extract_native.py" "${WR64_ROOT}" "${NATIVE_CAMERA}"
    DEPENDS "${WR64_ROOT}/tests/camera_fov/extract_native.py" "${WR64_ROOT}/config/us.rev1.toml"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_0.c" "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_16.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_17.c" VERBATIM)
add_executable(wr64_far_water_distance_test far_water_test.cpp ${FIXTURE_OUTPUTS} "${NATIVE_CAMERA}" "${WR64_ROOT}/src/wr64_camera_fov.cpp")
target_compile_features(wr64_far_water_distance_test PRIVATE cxx_std_20)
target_compile_definitions(wr64_far_water_distance_test PRIVATE WR64_WITH_BASELINE NOMINMAX)
target_include_directories(wr64_far_water_distance_test PRIVATE "${FIXTURE}" "${WR64_ROOT}/lib/rt64/src"
    "${WR64_ROOT}/include" "${WR64_ROOT}/RecompiledFuncsPoint0" "${WR64_ROOT}/tests/sunny_two_player_detail"
    "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include")
add_test(NAME flat_water_distance_geometry COMMAND wr64_far_water_distance_test "${FIXTURE}/native_water.txt" ${WR64_SUNNY_CAPTURES})

set(RUNTIME "${WR64_ROOT}/lib/N64ModernRuntime")
set(SCHEMA "${CMAKE_CURRENT_BINARY_DIR}/water_distance_schema.cpp")
add_custom_command(OUTPUT "${SCHEMA}" COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_schema.py" "${WR64_ROOT}" "${SCHEMA}"
    DEPENDS extract_schema.py "${WR64_ROOT}/src/wr64_frontend.cpp" VERBATIM)
add_executable(wr64_water_distance_settings_test settings_test.cpp "${SCHEMA}" "${WR64_ROOT}/src/wr64_seabed_distance.cpp"
    "${RUNTIME}/librecomp/src/config.cpp" "${RUNTIME}/librecomp/src/config_option.cpp" "${RUNTIME}/librecomp/src/files.cpp")
target_compile_features(wr64_water_distance_settings_test PRIVATE cxx_std_20)
target_include_directories(wr64_water_distance_settings_test PRIVATE "${WR64_ROOT}/tests/config_scope/stubs"
    "${WR64_ROOT}/include" "${WR64_ROOT}/lib/rt64/src" "${RUNTIME}/librecomp/include"
    "${RUNTIME}/librecomp/include/librecomp" "${RUNTIME}/N64Recomp/include" "${RUNTIME}/thirdparty")
add_test(NAME water_and_seabed_distance_persistence COMMAND wr64_water_distance_settings_test)

# Decode the shipped native water lists for both split views and sea variants.
add_subdirectory("../sunny_two_player_sky" native_support EXCLUDE_FROM_ALL)
get_target_property(NATIVE_SOURCES wr64_native_rt_admission_test SOURCES)
list(FILTER NATIVE_SOURCES EXCLUDE REGEX "rt_admission_test.cpp$")
get_target_property(NATIVE_INCLUDES wr64_native_rt_admission_test INCLUDE_DIRECTORIES)
set(SUPPORT "${CMAKE_CURRENT_BINARY_DIR}/native_roundness_support.inc")
set(MATCHING "${CMAKE_CURRENT_BINARY_DIR}/roundness_matching.inc")
add_custom_command(OUTPUT "${SUPPORT}" "${MATCHING}"
    COMMAND "${Python3_EXECUTABLE}" "${WR64_ROOT}/tests/water_roundness/extract_support.py"
        "${WR64_ROOT}/tests/sunny_two_player_sky/rt_admission_test.cpp" "${SUPPORT}" "${WR64_ROOT}" "${MATCHING}"
    DEPENDS "${WR64_ROOT}/tests/water_roundness/extract_support.py"
        "${WR64_ROOT}/tests/sunny_two_player_sky/rt_admission_test.cpp"
        "${WR64_ROOT}/lib/rt64/src/hle/rt64_workload_queue.cpp"
        "${WR64_ROOT}/lib/rt64/src/hle/rt64_state.cpp"
        "${WR64_ROOT}/lib/rt64/src/hle/rt64_game_frame.cpp"
        "${WR64_ROOT}/lib/rt64/src/hle/rt64_workload.cpp" VERBATIM)
add_executable(wr64_native_far_water_test native_fan_test.cpp "${SUPPORT}" "${MATCHING}" ${NATIVE_SOURCES})
target_compile_features(wr64_native_far_water_test PRIVATE cxx_std_20)
target_include_directories(wr64_native_far_water_test PRIVATE ${NATIVE_INCLUDES}
    "${CMAKE_CURRENT_BINARY_DIR}" "${WR64_ROOT}/tests/sunny_two_player_sky")
if(WR64_TEST_ROM)
    add_test(NAME native_far_water_per_view COMMAND wr64_native_far_water_test "${WR64_TEST_ROM}")
endif()

set(PRODUCER "${CMAKE_CURRENT_BINARY_DIR}/native_water_producer.c")
add_custom_command(OUTPUT "${PRODUCER}" "${CMAKE_CURRENT_BINARY_DIR}/native_water_producer.viewport.inc"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_producer.py" "${WR64_ROOT}" "${PRODUCER}"
    DEPENDS extract_producer.py "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_0.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_1.c" "${WR64_ROOT}/src/recomp_shims.cpp" VERBATIM)
add_executable(wr64_far_water_producer_test producer_test.cpp "${SUPPORT}" "${MATCHING}" "${PRODUCER}" ${NATIVE_SOURCES})
target_compile_features(wr64_far_water_producer_test PRIVATE cxx_std_20)
target_include_directories(wr64_far_water_producer_test PRIVATE ${NATIVE_INCLUDES}
    "${CMAKE_CURRENT_BINARY_DIR}" "${WR64_ROOT}/tests/sunny_two_player_sky")
if(WR64_TEST_ROM AND WR64_SUNNY_CAPTURES)
    list(GET WR64_SUNNY_CAPTURES 0 PRODUCER_CAPTURE)
    add_test(NAME native_far_water_actual_vertices COMMAND "${Python3_EXECUTABLE}"
        "${CMAKE_CURRENT_LIST_DIR}/run_producer.py" "$<TARGET_FILE:wr64_far_water_producer_test>"
        "${WR64_TEST_ROM}" "${PRODUCER_CAPTURE}")
endif()
