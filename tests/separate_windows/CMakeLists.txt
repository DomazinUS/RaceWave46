cmake_minimum_required(VERSION 3.20)
project(Wr64SeparateWindowsTests LANGUAGES CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(SCHEMA "${CMAKE_CURRENT_BINARY_DIR}/split_schema.cpp")
add_custom_command(OUTPUT "${SCHEMA}"
    COMMAND "${Python3_EXECUTABLE}" "${WR64_ROOT}/tests/vertical_split/extract_schema.py" "${WR64_ROOT}" "${SCHEMA}"
    DEPENDS "${WR64_ROOT}/tests/vertical_split/extract_schema.py" "${WR64_ROOT}/src/wr64_frontend.cpp" VERBATIM)
set(RUNTIME "${WR64_ROOT}/lib/N64ModernRuntime")
add_executable(wr64_separate_windows_test separate_windows_test.cpp "${SCHEMA}"
    "${WR64_ROOT}/src/wr64_split_screen.cpp"
    "${RUNTIME}/librecomp/src/config.cpp" "${RUNTIME}/librecomp/src/config_option.cpp" "${RUNTIME}/librecomp/src/files.cpp")
target_compile_features(wr64_separate_windows_test PRIVATE cxx_std_20)
target_compile_definitions(wr64_separate_windows_test PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
target_include_directories(wr64_separate_windows_test PRIVATE
    "${WR64_ROOT}/tests/vertical_split/stubs" "${WR64_ROOT}/tests/config_scope/stubs"
    "${WR64_ROOT}/include" "${WR64_ROOT}/lib/rt64/src"
    "${RUNTIME}/librecomp/include" "${RUNTIME}/librecomp/include/librecomp"
    "${RUNTIME}/N64Recomp/include" "${RUNTIME}/thirdparty")
add_test(NAME separate_windows_native_scope_and_persistence COMMAND wr64_separate_windows_test)
add_test(NAME separate_windows_workload_reset_and_handoff
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/verify_workload_scope.py" "${WR64_ROOT}")
