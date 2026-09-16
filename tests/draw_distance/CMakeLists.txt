cmake_minimum_required(VERSION 3.20)
project(Wr64DrawDistanceTests LANGUAGES C CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(NATIVE "${CMAKE_CURRENT_BINARY_DIR}/native_draw_distance.c")
add_custom_command(OUTPUT "${NATIVE}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_native.py" "${WR64_ROOT}" "${NATIVE}"
    DEPENDS extract_native.py "${WR64_ROOT}/config/us.rev1.toml"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_0.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_3.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_19.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_15.c" VERBATIM)
add_executable(wr64_draw_distance_test draw_distance_test.cpp "${NATIVE}"
    "${WR64_ROOT}/src/wr64_draw_distance.cpp"
    "${WR64_ROOT}/src/wr64_object_distance.cpp"
    "${WR64_ROOT}/src/wr64_sunny_buoys.cpp"
    "${WR64_ROOT}/src/wr64_twilight_buoy_lights.cpp")
target_compile_features(wr64_draw_distance_test PRIVATE cxx_std_20)
target_include_directories(wr64_draw_distance_test PRIVATE
    "${WR64_ROOT}/tests/sunny_two_player_detail" "${WR64_ROOT}/include"
    "${WR64_ROOT}/RecompiledFuncsPoint0" "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include")
add_test(NAME native_buoy_draw_distance COMMAND wr64_draw_distance_test)
set(OPENING_CAPTURE "${WR64_ROOT}/../../forensic-observatory-r1-20260728/.forensics/capture-20260728-224442/rdram.bin")
if(EXISTS "${OPENING_CAPTURE}")
    add_test(NAME archived_dolphin_opening_buoy_distance
        COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/run_archived_opening.py"
        "$<TARGET_FILE:wr64_draw_distance_test>" "${OPENING_CAPTURE}")
endif()

set(RUNTIME "${WR64_ROOT}/lib/N64ModernRuntime")
set(SCHEMA "${CMAKE_CURRENT_BINARY_DIR}/draw_distance_schema.cpp")
add_custom_command(OUTPUT "${SCHEMA}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_schema.py" "${WR64_ROOT}" "${SCHEMA}"
    DEPENDS extract_schema.py "${WR64_ROOT}/src/wr64_frontend.cpp" VERBATIM)
add_executable(wr64_draw_distance_settings_test settings_test.cpp "${SCHEMA}"
    "${WR64_ROOT}/src/wr64_draw_distance.cpp"
    "${WR64_ROOT}/src/wr64_object_distance.cpp"
    "${RUNTIME}/librecomp/src/config.cpp"
    "${RUNTIME}/librecomp/src/config_option.cpp"
    "${RUNTIME}/librecomp/src/files.cpp")
target_compile_features(wr64_draw_distance_settings_test PRIVATE cxx_std_20)
target_include_directories(wr64_draw_distance_settings_test PRIVATE
    "${WR64_ROOT}/tests/config_scope/stubs" "${WR64_ROOT}/include"
    "${RUNTIME}/librecomp/include" "${RUNTIME}/librecomp/include/librecomp"
    "${RUNTIME}/N64Recomp/include" "${RUNTIME}/thirdparty")
add_test(NAME buoy_and_object_draw_distance_persistence COMMAND wr64_draw_distance_settings_test)
