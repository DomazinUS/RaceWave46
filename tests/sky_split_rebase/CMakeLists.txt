cmake_minimum_required(VERSION 3.20)
project(Wr64SkySplitRebase LANGUAGES CXX)
enable_testing()
find_package(Python3 REQUIRED COMPONENTS Interpreter)
get_filename_component(WR64_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
set(EXTRACTED "${CMAKE_CURRENT_BINARY_DIR}/sky_functions.inc")
set(TYPES "${CMAKE_CURRENT_BINARY_DIR}/sky_types.inc")
add_custom_command(OUTPUT "${EXTRACTED}" "${TYPES}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract.py" "${WR64_ROOT}" "${CMAKE_CURRENT_BINARY_DIR}"
    DEPENDS extract.py captured-cloud-materials.csv "${WR64_ROOT}/lib/rt64/src/common/rt64_wr64_sky_bracket.h"
    "${WR64_ROOT}/lib/rt64/src/hle/rt64_game_frame.cpp"
    "${WR64_ROOT}/lib/rt64/src/hle/rt64_game_frame.h"
    "${WR64_ROOT}/lib/rt64/src/hle/rt64_draw_call.h")
add_executable(sky_split_rebase_test sky_test.cpp "${EXTRACTED}" "${TYPES}"
    "${WR64_ROOT}/lib/rt64/src/common/rt64_common.cpp")
target_compile_features(sky_split_rebase_test PRIVATE cxx_std_17)
target_compile_definitions(sky_split_rebase_test PRIVATE HLSL_CPU)
target_include_directories(sky_split_rebase_test PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
    "${WR64_ROOT}/lib/rt64/src" "${WR64_ROOT}/lib/rt64/src/contrib/hlslpp/include")
add_test(NAME split_sky_rebase COMMAND sky_split_rebase_test normal)
add_test(NAME split_sky_smart_disabled COMMAND sky_split_rebase_test disabled)
add_test(NAME split_sky_diagnostics COMMAND sky_split_rebase_test diagnostic)
set_tests_properties(split_sky_rebase PROPERTIES ENVIRONMENT "WR64_SKY_TC_SMART=1;WR64_SKY_BRACKET=0;WR64_SKY_TC_JUMP=20;WR64_SKY_REANCHOR=1000")
set_tests_properties(split_sky_smart_disabled PROPERTIES ENVIRONMENT "WR64_SKY_TC_SMART=0;WR64_SKY_BRACKET=0")
set_tests_properties(split_sky_diagnostics PROPERTIES ENVIRONMENT "WR64_SKY_TC_SMART=1;WR64_SKY_BRACKET=1")
