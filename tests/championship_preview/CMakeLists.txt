cmake_minimum_required(VERSION 3.20)
project(Wr64ChampionshipPreviewTests LANGUAGES C CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(NATIVE_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/native_championship.c")
add_custom_command(OUTPUT "${NATIVE_SOURCE}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_native.py" "${WR64_ROOT}" "${NATIVE_SOURCE}"
    DEPENDS extract_native.py "${WR64_ROOT}/config/us.rev1.toml"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_2.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_6.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_18.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_21.c"
    VERBATIM)
add_executable(wr64_championship_preview_test championship_preview_test.cpp "${NATIVE_SOURCE}"
    "${WR64_ROOT}/src/wr64_championship_preview.cpp")
target_compile_features(wr64_championship_preview_test PRIVATE cxx_std_20)
target_include_directories(wr64_championship_preview_test PRIVATE
    "${WR64_ROOT}/include" "${WR64_ROOT}/RecompiledFuncsPoint0"
    "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include"
    "${WR64_ROOT}/lib/rt64/src" "${WR64_ROOT}/lib/rt64/include")
add_test(NAME native_championship_preview COMMAND wr64_championship_preview_test)
set_tests_properties(native_championship_preview PROPERTIES ENVIRONMENT "WR64_CHAMPIONSHIP_PREVIEW=1;WR64_CHAMPIONSHIP_PREVIEW_TRACE=")
add_test(NAME native_championship_preview_disabled COMMAND wr64_championship_preview_test --disabled)
set_tests_properties(native_championship_preview_disabled PROPERTIES ENVIRONMENT "WR64_CHAMPIONSHIP_PREVIEW=0;WR64_CHAMPIONSHIP_PREVIEW_TRACE=")
