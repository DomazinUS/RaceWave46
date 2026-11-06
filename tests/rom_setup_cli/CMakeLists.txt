cmake_minimum_required(VERSION 3.20)
project(Wr64RomSetupCliTests LANGUAGES CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(WR64_GAME_EXECUTABLE "" CACHE FILEPATH "Optional built WaveRace64Recompiled for the end-to-end import test")
set(WR64_TEST_ROM "" CACHE FILEPATH "Optional unmodified USA Rev 1 ROM for the end-to-end import test")

add_executable(wr64_rom_setup_cli_test rom_setup_cli_test.cpp "${WR64_ROOT}/src/wr64_editions.cpp")
target_compile_features(wr64_rom_setup_cli_test PRIVATE cxx_std_20)
target_compile_definitions(wr64_rom_setup_cli_test PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
target_include_directories(wr64_rom_setup_cli_test PRIVATE "${WR64_ROOT}/include")
if(WIN32)
    target_link_libraries(wr64_rom_setup_cli_test PRIVATE shell32)
endif()
add_test(NAME rom_setup_options COMMAND wr64_rom_setup_cli_test)

if(WR64_GAME_EXECUTABLE AND WR64_TEST_ROM)
    add_test(NAME rom_setup_end_to_end
        COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/end_to_end.py"
            --game "${WR64_GAME_EXECUTABLE}" --rom "${WR64_TEST_ROM}")
endif()
