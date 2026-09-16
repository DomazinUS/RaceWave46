cmake_minimum_required(VERSION 3.20)
project(Wr64GhostTests LANGUAGES CXX)
enable_testing()
get_filename_component(WR64_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
add_executable(wr64_ghost_test ghost_test.cpp
    "${WR64_ROOT}/src/wr64_ghost.cpp"
    "${WR64_ROOT}/src/controller_pak.cpp"
    "${WR64_ROOT}/lib/N64ModernRuntime/librecomp/src/files.cpp")
target_compile_features(wr64_ghost_test PRIVATE cxx_std_20)
target_include_directories(wr64_ghost_test PRIVATE stubs
    "${WR64_ROOT}/include"
    "${WR64_ROOT}/lib/N64ModernRuntime/librecomp/include"
    "${WR64_ROOT}/lib/N64ModernRuntime/librecomp/include/librecomp")
add_test(NAME ghost_lifecycle_and_persistence COMMAND wr64_ghost_test "${CMAKE_CURRENT_BINARY_DIR}/isolated-pak")

find_package(Python3 COMPONENTS Interpreter REQUIRED)
add_executable(wr64_ghost_autosave_test ghost_autosave_test.cpp
    "${WR64_ROOT}/src/wr64_ghost.cpp"
    "${WR64_ROOT}/src/controller_pak.cpp"
    "${WR64_ROOT}/lib/N64ModernRuntime/librecomp/src/files.cpp")
target_compile_features(wr64_ghost_autosave_test PRIVATE cxx_std_20)
target_include_directories(wr64_ghost_autosave_test PRIVATE stubs
    "${WR64_ROOT}/include"
    "${WR64_ROOT}/lib/N64ModernRuntime/librecomp/include"
    "${WR64_ROOT}/lib/N64ModernRuntime/librecomp/include/librecomp")
add_test(NAME ghost_automatic_persistence_across_processes
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/run_autosave_test.py"
        "$<TARGET_FILE:wr64_ghost_autosave_test>" "${CMAKE_CURRENT_BINARY_DIR}/isolated-autosave")

set(DOLPHIN_STAMPER_SOURCE "${WR64_ROOT}/lib/rt64/src/hle/rt64_game_frame.cpp")
set(DOLPHIN_STAMPER_TEST "${CMAKE_CURRENT_BINARY_DIR}/dolphin_stamper_test.inc")
add_custom_command(OUTPUT "${DOLPHIN_STAMPER_TEST}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_dolphin_stamper_test.py"
        "${DOLPHIN_STAMPER_SOURCE}" "${DOLPHIN_STAMPER_TEST}"
    DEPENDS "${DOLPHIN_STAMPER_SOURCE}" "${CMAKE_CURRENT_LIST_DIR}/extract_dolphin_stamper_test.py"
    VERBATIM)
add_executable(wr64_ghost_renderer_identity_test ghost_renderer_identity_test.cpp "${DOLPHIN_STAMPER_TEST}")
target_compile_features(wr64_ghost_renderer_identity_test PRIVATE cxx_std_17)
target_include_directories(wr64_ghost_renderer_identity_test PRIVATE
    "${CMAKE_CURRENT_BINARY_DIR}" "${WR64_ROOT}/lib/rt64/src"
    "${WR64_ROOT}/lib/rt64/src/contrib/hlslpp/include")
add_test(NAME ghost_renderer_preserves_explicit_identity COMMAND wr64_ghost_renderer_identity_test)

set(WR64_GHOST_NATIVE_ROM "" CACHE FILEPATH "Optional local, user-owned USA Rev1 ROM for native adapter tests")
if(WR64_GHOST_NATIVE_ROM)
    enable_language(C)
    find_package(Python3 COMPONENTS Interpreter REQUIRED)
    set(NATIVE_TEST_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/usa_native_test_functions.c")
    execute_process(COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_native_test.py"
        "${WR64_ROOT}" "${NATIVE_TEST_SOURCE}" COMMAND_ERROR_IS_FATAL ANY)
    add_executable(wr64_ghost_native_test ghost_native_test.cpp "${NATIVE_TEST_SOURCE}"
        "${WR64_ROOT}/src/wr64_ghost_native.cpp"
        "${WR64_ROOT}/src/wr64_ghost.cpp" "${WR64_ROOT}/src/controller_pak.cpp"
        "${WR64_ROOT}/lib/N64ModernRuntime/librecomp/src/files.cpp")
    target_compile_features(wr64_ghost_native_test PRIVATE cxx_std_20)
    target_include_directories(wr64_ghost_native_test PRIVATE stubs "${WR64_ROOT}/include"
        "${CMAKE_CURRENT_BINARY_DIR}"
        "${WR64_ROOT}/RecompiledFuncsPoint0" "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include"
        "${WR64_ROOT}/lib/N64ModernRuntime/librecomp/include"
        "${WR64_ROOT}/lib/N64ModernRuntime/librecomp/include/librecomp")
    add_test(NAME ghost_native_usa_adapter COMMAND wr64_ghost_native_test "${WR64_GHOST_NATIVE_ROM}")
    add_test(NAME ghost_native_automatic_persistence COMMAND wr64_ghost_native_test
        "${WR64_GHOST_NATIVE_ROM}" --autosave "${CMAKE_CURRENT_BINARY_DIR}/isolated-native-autosave")
    add_test(NAME ghost_native_diagnostic_preview COMMAND wr64_ghost_native_test "${WR64_GHOST_NATIVE_ROM}" --smoke)
    set_tests_properties(ghost_native_diagnostic_preview PROPERTIES
        ENVIRONMENT "WR64_GHOST_TRACE=1;WR64_GHOST_RENDER_SMOKE=1")
endif()
