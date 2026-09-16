cmake_minimum_required(VERSION 3.20)
project(Wr64SunnyTwoPlayerSkyTests LANGUAGES C CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(NATIVE_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/native_sunny_sky.c")
add_custom_command(OUTPUT "${NATIVE_SOURCE}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_native.py" "${WR64_ROOT}" "${NATIVE_SOURCE}"
    DEPENDS extract_native.py "${WR64_ROOT}/config/us.rev1.toml"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_0.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_1.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_6.c"
    VERBATIM)
add_executable(wr64_sunny_sky_test sunny_sky_test.cpp "${NATIVE_SOURCE}" "${WR64_ROOT}/src/wr64_sunny_sky.cpp")
target_compile_features(wr64_sunny_sky_test PRIVATE cxx_std_20)
target_include_directories(wr64_sunny_sky_test PRIVATE "${CMAKE_CURRENT_LIST_DIR}/../sunny_two_player_detail"
    "${WR64_ROOT}/include" "${WR64_ROOT}/RecompiledFuncsPoint0"
    "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include")
set(WR64_TEST_ROM "" CACHE FILEPATH "Private USA Rev1 ROM, read in memory only")
if(WR64_TEST_ROM)
    add_test(NAME sunny_native_sky_and_clouds COMMAND "${Python3_EXECUTABLE}"
        "${CMAKE_CURRENT_LIST_DIR}/../sunny_two_player_detail/run_private_rom_test.py"
        "$<TARGET_FILE:wr64_sunny_sky_test>" "${WR64_TEST_ROM}")
endif()

# Bridge the actual native producers and shipped ROM patch to the RT admission
# predicates, without a game process or graphics device.
set(RT_WATER_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/native_rt_water.c")
add_custom_command(OUTPUT "${RT_WATER_SOURCE}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/../sunny_water_detail/extract_native.py"
        "${WR64_ROOT}" "${RT_WATER_SOURCE}"
    DEPENDS "${CMAKE_CURRENT_LIST_DIR}/../sunny_water_detail/extract_native.py"
        "${WR64_ROOT}/config/us.rev1.toml" "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_6.c" VERBATIM)
set(RT_PATCH_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/wr64_rom_patch_data.c")
set(RT_PATCH_HEADER "${CMAKE_CURRENT_BINARY_DIR}/wr64_rom_patch_data.h")
add_custom_command(OUTPUT "${RT_PATCH_SOURCE}" "${RT_PATCH_HEADER}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/embed_patch.py"
        "${WR64_ROOT}/data/waverace64-widescreen.ips" "${RT_PATCH_SOURCE}" "${RT_PATCH_HEADER}"
    DEPENDS "${WR64_ROOT}/data/waverace64-widescreen.ips" embed_patch.py VERBATIM)
add_executable(wr64_native_rt_admission_test rt_admission_test.cpp "${NATIVE_SOURCE}"
    "${RT_WATER_SOURCE}" "${RT_PATCH_SOURCE}" "${RT_PATCH_HEADER}"
    "${WR64_ROOT}/src/wr64_sunny_sky.cpp" "${WR64_ROOT}/src/wr64_sunny_water.cpp"
    "${WR64_ROOT}/src/wr64_rom_patch.cpp")
target_compile_features(wr64_native_rt_admission_test PRIVATE cxx_std_20)
target_include_directories(wr64_native_rt_admission_test PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
    "${CMAKE_CURRENT_LIST_DIR}/../sunny_two_player_detail" "${WR64_ROOT}/lib/rt64/src"
    "${WR64_ROOT}/include" "${WR64_ROOT}/RecompiledFuncsPoint0"
    "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include")
if(WR64_TEST_ROM)
    add_test(NAME sunny_native_rt_view_admission COMMAND "${Python3_EXECUTABLE}"
        "${CMAKE_CURRENT_LIST_DIR}/../sunny_two_player_detail/run_private_rom_test.py"
        "$<TARGET_FILE:wr64_native_rt_admission_test>" "${WR64_TEST_ROM}")
endif()
