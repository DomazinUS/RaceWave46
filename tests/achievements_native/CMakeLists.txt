cmake_minimum_required(VERSION 3.20)
project(Wr64AchievementsNativeTests LANGUAGES C CXX)
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(RCHEEVOS_SOURCE "${WR64_ROOT}/lib/rcheevos" CACHE PATH "Pinned rcheevos source")
add_subdirectory("${RCHEEVOS_SOURCE}" "${CMAKE_CURRENT_BINARY_DIR}/rcheevos")
set(NATIVE_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/native_main_thread.c")
add_custom_command(OUTPUT "${NATIVE_SOURCE}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_native.py" "${WR64_ROOT}" "${NATIVE_SOURCE}"
    DEPENDS extract_native.py "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_0.c" "${WR64_ROOT}/config/us.rev1.toml" VERBATIM)
set(PATCH_C "${CMAKE_CURRENT_BINARY_DIR}/wr64_rom_patch_data.c")
set(PATCH_H "${CMAKE_CURRENT_BINARY_DIR}/wr64_rom_patch_data.h")
add_custom_command(OUTPUT "${PATCH_C}" "${PATCH_H}"
    COMMAND "${CMAKE_COMMAND}" "-DINPUT=${WR64_ROOT}/data/waverace64-widescreen.ips"
        "-DOUTPUT_C=${PATCH_C}" "-DOUTPUT_H=${PATCH_H}" -DSYMBOL=wr64_rom_patch_ips
        -P "${WR64_ROOT}/tools/binary_to_c.cmake"
    DEPENDS "${WR64_ROOT}/data/waverace64-widescreen.ips" VERBATIM)
add_executable(wr64_achievements_native_test native.cpp "${NATIVE_SOURCE}" "${PATCH_C}"
    "${WR64_ROOT}/src/wr64_achievements_hooks.cpp" "${WR64_ROOT}/src/wr64_rom_patch.cpp")
target_compile_features(wr64_achievements_native_test PRIVATE cxx_std_20)
target_link_libraries(wr64_achievements_native_test PRIVATE wr64_rcheevos)
target_include_directories(wr64_achievements_native_test PRIVATE "${WR64_ROOT}/include"
    "${WR64_ROOT}/RecompiledFuncsPoint0" "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include"
    "${CMAKE_CURRENT_BINARY_DIR}" "${RCHEEVOS_SOURCE}/include")
