cmake_minimum_required(VERSION 3.20)
project(Wr64SeabedDistanceTests LANGUAGES C CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(NATIVE_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/native_seabed.c")
add_custom_command(OUTPUT "${NATIVE_SOURCE}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_native.py" "${WR64_ROOT}" "${NATIVE_SOURCE}"
    DEPENDS extract_native.py "${WR64_ROOT}/config/us.rev1.toml"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_0.c" "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_1.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_6.c" VERBATIM)
add_executable(wr64_seabed_distance_test seabed_distance_test.cpp "${NATIVE_SOURCE}"
    "${WR64_ROOT}/src/wr64_seabed_distance.cpp" "${WR64_ROOT}/src/wr64_sunny_sky.cpp")
target_compile_features(wr64_seabed_distance_test PRIVATE cxx_std_20)
target_include_directories(wr64_seabed_distance_test PRIVATE "${CMAKE_CURRENT_LIST_DIR}/../sunny_two_player_detail"
    "${WR64_ROOT}/include" "${WR64_ROOT}/RecompiledFuncsPoint0"
    "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include")
set(WR64_TEST_ROM "" CACHE FILEPATH "Private USA Rev1 ROM, read in memory only")
if(WR64_TEST_ROM)
    add_test(NAME native_seabed_distance COMMAND "${Python3_EXECUTABLE}"
        "${CMAKE_CURRENT_LIST_DIR}/../sunny_two_player_detail/run_private_rom_test.py"
        "$<TARGET_FILE:wr64_seabed_distance_test>" "${WR64_TEST_ROM}")
endif()

# Local, previously recorded gameplay RAM is read in memory; never copied into
# source, fixtures or a release package. Synthetic cases remain self-contained.
foreach(WR64_CAPTURE_DATE "20260729-000900" "20260728-202327" "20260728-205118" "20260728-224442")
    set(WR64_CAPTURE "${WR64_ROOT}/../../forensic-observatory-r1-20260728/.forensics/capture-${WR64_CAPTURE_DATE}/rdram.bin")
    if(WR64_TEST_ROM AND EXISTS "${WR64_CAPTURE}")
        add_test(NAME "native_seabed_archive_${WR64_CAPTURE_DATE}" COMMAND
            "$<TARGET_FILE:wr64_seabed_distance_test>" "${WR64_TEST_ROM}" "${WR64_CAPTURE}")
    endif()
endforeach()
