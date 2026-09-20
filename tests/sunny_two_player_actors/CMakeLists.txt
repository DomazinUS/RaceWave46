cmake_minimum_required(VERSION 3.20)
project(Wr64SunnyActorsTests LANGUAGES C CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(NATIVE_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/native_sunny_actors.c")
add_custom_command(OUTPUT "${NATIVE_SOURCE}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_native.py" "${WR64_ROOT}" "${NATIVE_SOURCE}"
    DEPENDS extract_native.py "${WR64_ROOT}/config/us.rev1.toml"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_0.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_1.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_2.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_15.c"
    VERBATIM)
add_executable(wr64_sunny_actors_test actors_test.cpp "${NATIVE_SOURCE}"
    "${WR64_ROOT}/src/wr64_sunny_actors.cpp" "${WR64_ROOT}/src/wr64_sunny_detail.cpp")
target_compile_features(wr64_sunny_actors_test PRIVATE cxx_std_20)
target_include_directories(wr64_sunny_actors_test PRIVATE "${CMAKE_CURRENT_LIST_DIR}"
    "${WR64_ROOT}/include" "${WR64_ROOT}/RecompiledFuncsPoint0"
    "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include")
set(WR64_TEST_ROM "" CACHE FILEPATH "Private USA Rev1 ROM, never copied into artifacts")
if(WR64_TEST_ROM)
    add_test(NAME sunny_native_actor_shadows COMMAND "${Python3_EXECUTABLE}"
        "${CMAKE_CURRENT_LIST_DIR}/../sunny_two_player_detail/run_private_rom_test.py"
        "$<TARGET_FILE:wr64_sunny_actors_test>" "${WR64_TEST_ROM}")
endif()
