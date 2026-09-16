cmake_minimum_required(VERSION 3.20)
project(Wr64ObjectDrawDistanceTests LANGUAGES C CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(NATIVE "${CMAKE_CURRENT_BINARY_DIR}/native_objects.c")
add_custom_command(OUTPUT "${NATIVE}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_native.py" "${WR64_ROOT}" "${NATIVE}"
    DEPENDS extract_native.py "${WR64_ROOT}/config/us.rev1.toml"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_3.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_15.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_19.c"
        "${WR64_ROOT}/src/wr64_object_distance.cpp"
        "${WR64_ROOT}/include/wr64_object_distance.hpp" VERBATIM)
add_executable(wr64_object_draw_distance_test object_test.cpp "${NATIVE}"
    "${WR64_ROOT}/src/wr64_object_distance.cpp")
target_compile_features(wr64_object_draw_distance_test PRIVATE cxx_std_20)
target_include_directories(wr64_object_draw_distance_test PRIVATE
    "${WR64_ROOT}/tests/sunny_two_player_detail" "${WR64_ROOT}/include"
    "${WR64_ROOT}/RecompiledFuncsPoint0" "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include")
add_test(NAME native_object_draw_distance COMMAND wr64_object_draw_distance_test)
set(WR64_DOLPHIN_RAM "" CACHE FILEPATH "Optional original Dolphin capture-20260728-224442/rdram.bin")
if(WR64_DOLPHIN_RAM)
    file(SHA256 "${WR64_DOLPHIN_RAM}" DOLPHIN_SHA256)
    if(NOT DOLPHIN_SHA256 STREQUAL "08ee4482e164740514b61a5d917e115f53aae65f6e48c4597f869f1ac26fd104")
        message(FATAL_ERROR "WR64_DOLPHIN_RAM must be the verified original capture-20260728-224442/rdram.bin")
    endif()
    add_test(NAME archived_dolphin_ramp_distance COMMAND wr64_object_draw_distance_test "${WR64_DOLPHIN_RAM}")
    set_tests_properties(archived_dolphin_ramp_distance PROPERTIES LABELS "cpu;native;draw-distance" TIMEOUT 20)
endif()
set_tests_properties(native_object_draw_distance PROPERTIES LABELS "cpu;native;draw-distance" TIMEOUT 20)
