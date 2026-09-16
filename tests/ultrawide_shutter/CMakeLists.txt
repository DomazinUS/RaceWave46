cmake_minimum_required(VERSION 3.20)
project(Wr64ShutterTests LANGUAGES CXX)
enable_testing()
get_filename_component(WR64_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
add_executable(wr64_shutter_test shutter_test.cpp)
target_compile_features(wr64_shutter_test PRIVATE cxx_std_17)
target_include_directories(wr64_shutter_test PRIVATE "${WR64_ROOT}/lib/rt64/src")
add_test(NAME shutter_scope_and_coverage COMMAND wr64_shutter_test)
set(WR64_SHUTTER_NATIVE_ROM "" CACHE FILEPATH "Optional user-owned original USA Rev1 ROM for native shutter replay")
if(WR64_SHUTTER_NATIVE_ROM)
    enable_language(C)
    find_package(Python3 COMPONENTS Interpreter REQUIRED)
    set(NATIVE "${CMAKE_CURRENT_BINARY_DIR}/native_shutter.c")
    add_custom_command(OUTPUT "${NATIVE}"
        COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_native.py" "${WR64_ROOT}" "${NATIVE}"
        DEPENDS "${CMAKE_CURRENT_LIST_DIR}/extract_native.py"
            "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_0.c"
            "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_15.c"
            "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_18.c"
        VERBATIM)
    add_executable(wr64_shutter_native_test shutter_native_test.cpp "${NATIVE}")
    target_compile_features(wr64_shutter_native_test PRIVATE cxx_std_17)
    target_include_directories(wr64_shutter_native_test PRIVATE
        "${WR64_ROOT}/RecompiledFuncsPoint0"
        "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include"
        "${WR64_ROOT}/lib/rt64/src")
    add_test(NAME shutter_native_usa_trajectory COMMAND wr64_shutter_native_test
        "${WR64_SHUTTER_NATIVE_ROM}" "${WR64_ROOT}/data/waverace64-widescreen.ips")
endif()
