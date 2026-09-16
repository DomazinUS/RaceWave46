cmake_minimum_required(VERSION 3.20)
project(Wr64TwilightLightsTests LANGUAGES C CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(NATIVE "${CMAKE_CURRENT_BINARY_DIR}/native_lights.c")
add_custom_command(OUTPUT "${NATIVE}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_native.py" "${WR64_ROOT}" "${NATIVE}"
    DEPENDS extract_native.py "${WR64_ROOT}/config/us.rev1.toml"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_3.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_19.c" VERBATIM)
add_executable(wr64_twilight_lights_test lights_test.cpp "${NATIVE}"
    "${WR64_ROOT}/src/wr64_twilight_buoy_lights.cpp")
target_compile_features(wr64_twilight_lights_test PRIVATE cxx_std_20)
target_include_directories(wr64_twilight_lights_test PRIVATE "${WR64_ROOT}/tests/sunny_two_player_detail"
    "${WR64_ROOT}/include" "${WR64_ROOT}/RecompiledFuncsPoint0" "${WR64_ROOT}/lib/rt64/src"
    "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include")
set(WR64_TEST_ROM "" CACHE FILEPATH "Private USA Rev1 ROM; never copied into artifacts")
if(WR64_TEST_ROM)
    add_test(NAME twilight_native_buoy_lights COMMAND "${Python3_EXECUTABLE}"
        "${CMAKE_CURRENT_LIST_DIR}/run_private_rom_test.py"
        "$<TARGET_FILE:wr64_twilight_lights_test>" "${WR64_TEST_ROM}")
endif()
