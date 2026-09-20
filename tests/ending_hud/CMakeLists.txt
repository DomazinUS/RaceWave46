cmake_minimum_required(VERSION 3.20)
project(Wr64EndingHudTests LANGUAGES C CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/prepare.py"
    "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_6.c" "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_17.c"
    "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_18.c" "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_23.c" "${WR64_ROOT}/config/us.rev1.toml")
execute_process(COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/prepare.py"
    "${WR64_ROOT}" "${CMAKE_CURRENT_BINARY_DIR}" COMMAND_ERROR_IS_FATAL ANY)
add_executable(wr64_ending_hud_test ending_hud_test.cpp "${CMAKE_CURRENT_BINARY_DIR}/native_ending.c"
    "${CMAKE_CURRENT_BINARY_DIR}/hud_bridge.cpp" "${WR64_ROOT}/src/wr64_menu_layout.cpp")
target_compile_definitions(wr64_ending_hud_test PRIVATE WR64_ENABLE_RT64=1)
target_compile_features(wr64_ending_hud_test PRIVATE cxx_std_20)
target_include_directories(wr64_ending_hud_test PRIVATE "${WR64_ROOT}/include"
    "${WR64_ROOT}/RecompiledFuncsPoint0" "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include"
    "${WR64_ROOT}/lib/rt64/src")
if(MSVC)
    target_compile_options(wr64_ending_hud_test PRIVATE /fp:strict $<$<COMPILE_LANGUAGE:C>:/W0>)
endif()
set(WR64_ENDING_ARCHIVE "" CACHE FILEPATH "Private eight MiB native RDRAM capture")
set(WR64_ENDING_ROM "" CACHE FILEPATH "Private original USA Rev1 ROM")
if(WR64_ENDING_ARCHIVE AND WR64_ENDING_ROM)
    add_test(NAME ending_hud_native_replay COMMAND wr64_ending_hud_test
        "${WR64_ENDING_ARCHIVE}" "${WR64_ENDING_ROM}" "${CMAKE_CURRENT_BINARY_DIR}/ending-packets.csv")
endif()
