cmake_minimum_required(VERSION 3.20)
project(Wr64RTCelestialTests LANGUAGES C CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(NATIVE_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/native_celestial_projector.c")
add_custom_command(OUTPUT "${NATIVE_SOURCE}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_native.py" "${WR64_ROOT}" "${NATIVE_SOURCE}"
    DEPENDS extract_native.py "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_5.c" VERBATIM)
add_executable(wr64_rt_celestial_test celestial_test.cpp "${NATIVE_SOURCE}")
target_compile_features(wr64_rt_celestial_test PRIVATE cxx_std_20)
target_include_directories(wr64_rt_celestial_test PRIVATE "${WR64_ROOT}/include"
    "${WR64_ROOT}/RecompiledFuncsPoint0" "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include" "${WR64_ROOT}/lib/rt64/src")
if(MSVC)
    target_compile_options(wr64_rt_celestial_test PRIVATE /fp:strict
        $<$<COMPILE_LANGUAGE:CXX>:/W4> $<$<COMPILE_LANGUAGE:C>:/W0>)
    # The unmodified generated MIPS C has intentional register conversions and
    # dead visibility branches. Keep /W4 on the new helper and test harness.
endif()
add_test(NAME rt_native_celestial_projection_and_snapshot COMMAND wr64_rt_celestial_test)

add_executable(wr64_rt_celestial_archive_test archive_snapshot_test.cpp)
target_compile_features(wr64_rt_celestial_archive_test PRIVATE cxx_std_20)
target_include_directories(wr64_rt_celestial_archive_test PRIVATE "${WR64_ROOT}/lib/rt64/src")
if(MSVC)
    target_compile_options(wr64_rt_celestial_archive_test PRIVATE /W4)
endif()
set(WR64_CELESTIAL_ARCHIVE "" CACHE FILEPATH "Optional local archived rdram.bin; never copied into tests")
set(WR64_CELESTIAL_ARCHIVE_SEGMENT1 "0x00228e10" CACHE STRING "Raw segment1 command argument from the matching archive")
set(WR64_CELESTIAL_ARCHIVE_SEGMENT8 "0x80316800" CACHE STRING "Raw segment8 command argument from the matching archive")
if(WR64_CELESTIAL_ARCHIVE)
    add_test(NAME rt_native_celestial_archived_snapshot COMMAND wr64_rt_celestial_archive_test
        "${WR64_CELESTIAL_ARCHIVE}" "${WR64_CELESTIAL_ARCHIVE_SEGMENT1}" "${WR64_CELESTIAL_ARCHIVE_SEGMENT8}")
endif()
