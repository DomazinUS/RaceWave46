cmake_minimum_required(VERSION 3.20)
project(Wr64VerticalSplitTests LANGUAGES C CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_SOURCE_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
set(SPLIT_SCHEMA "${CMAKE_CURRENT_BINARY_DIR}/split_schema.cpp")
add_custom_command(OUTPUT "${SPLIT_SCHEMA}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_schema.py" "${WR64_SOURCE_ROOT}" "${SPLIT_SCHEMA}"
    DEPENDS extract_schema.py "${WR64_SOURCE_ROOT}/src/wr64_frontend.cpp"
    VERBATIM)
add_executable(wr64_vertical_split_test vertical_split_test.cpp
    "${SPLIT_SCHEMA}"
    "${WR64_SOURCE_ROOT}/src/wr64_split_screen.cpp"
    "${WR64_SOURCE_ROOT}/lib/rt64/src/common/rt64_common.cpp"
    "${WR64_SOURCE_ROOT}/lib/N64ModernRuntime/librecomp/src/config.cpp"
    "${WR64_SOURCE_ROOT}/lib/N64ModernRuntime/librecomp/src/config_option.cpp"
    "${WR64_SOURCE_ROOT}/lib/N64ModernRuntime/librecomp/src/files.cpp")
target_compile_features(wr64_vertical_split_test PRIVATE cxx_std_20)
target_compile_definitions(wr64_vertical_split_test PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
target_include_directories(wr64_vertical_split_test PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/stubs"
    "${WR64_SOURCE_ROOT}/tests/config_scope/stubs"
    "${WR64_SOURCE_ROOT}/lib/N64ModernRuntime/librecomp/include"
    "${WR64_SOURCE_ROOT}/lib/N64ModernRuntime/librecomp/include/librecomp"
    "${WR64_SOURCE_ROOT}/lib/N64ModernRuntime/N64Recomp/include"
    "${WR64_SOURCE_ROOT}/lib/N64ModernRuntime/thirdparty"
    "${WR64_SOURCE_ROOT}/include"
    "${WR64_SOURCE_ROOT}/lib/rt64/src"
    "${WR64_SOURCE_ROOT}/lib/rt64/src/contrib/hlslpp/include")
add_test(NAME vertical_split_invariants COMMAND wr64_vertical_split_test)
add_test(NAME vertical_split_native_hooks
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/verify_native_hooks.py" "${WR64_SOURCE_ROOT}")
set(LAP_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/native_lap.c")
add_custom_command(OUTPUT "${LAP_SOURCE}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_lap.py" "${WR64_SOURCE_ROOT}" "${LAP_SOURCE}"
    DEPENDS extract_lap.py "${WR64_SOURCE_ROOT}/config/us.rev1.toml"
        "${WR64_SOURCE_ROOT}/RecompiledFuncsPoint0/funcs_18.c"
        "${WR64_SOURCE_ROOT}/RecompiledFuncsPoint0/funcs_20.c"
    VERBATIM)
add_executable(wr64_vertical_lap_test vertical_lap_test.cpp "${LAP_SOURCE}"
    "${WR64_SOURCE_ROOT}/src/wr64_split_screen.cpp")
target_compile_features(wr64_vertical_lap_test PRIVATE cxx_std_20)
target_include_directories(wr64_vertical_lap_test PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/stubs"
    "${WR64_SOURCE_ROOT}/include"
    "${WR64_SOURCE_ROOT}/RecompiledFuncsPoint0"
    "${WR64_SOURCE_ROOT}/lib/N64ModernRuntime/N64Recomp/include"
    "${WR64_SOURCE_ROOT}/lib/rt64/src")
add_test(NAME vertical_split_native_lap COMMAND wr64_vertical_lap_test)
