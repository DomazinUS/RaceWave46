cmake_minimum_required(VERSION 3.20)
project(Wr64SunnyBuoyTests LANGUAGES C CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(NATIVE "${CMAKE_CURRENT_BINARY_DIR}/native_buoys.c")
add_custom_command(OUTPUT "${NATIVE}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_native.py" "${WR64_ROOT}" "${NATIVE}"
    DEPENDS extract_native.py "${WR64_ROOT}/config/us.rev1.toml"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_0.c" "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_3.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_6.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_15.c" VERBATIM)
add_executable(wr64_sunny_buoys_test buoys_test.cpp "${NATIVE}" "${WR64_ROOT}/src/wr64_sunny_buoys.cpp")
target_compile_features(wr64_sunny_buoys_test PRIVATE cxx_std_20)
target_include_directories(wr64_sunny_buoys_test PRIVATE "${WR64_ROOT}/tests/sunny_two_player_detail"
    "${WR64_ROOT}/include" "${WR64_ROOT}/RecompiledFuncsPoint0" "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include")
add_test(NAME sunny_native_buoy_details COMMAND wr64_sunny_buoys_test)
