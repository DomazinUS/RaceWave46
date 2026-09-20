cmake_minimum_required(VERSION 3.20)
project(Wr64SunnyAnimalTests LANGUAGES C CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(NATIVE "${CMAKE_CURRENT_BINARY_DIR}/native_animals.c")
add_custom_command(OUTPUT "${NATIVE}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_native.py" "${WR64_ROOT}" "${NATIVE}"
    DEPENDS extract_native.py "${WR64_ROOT}/config/us.rev1.toml"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_0.c" "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_6.c"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_9.c" "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_10.c" VERBATIM)
add_executable(wr64_sunny_animals_test animals_test.cpp "${NATIVE}" "${WR64_ROOT}/src/wr64_sunny_animals.cpp")
target_compile_features(wr64_sunny_animals_test PRIVATE cxx_std_20)
target_include_directories(wr64_sunny_animals_test PRIVATE "${WR64_ROOT}/tests/sunny_two_player_detail"
    "${WR64_ROOT}/include" "${WR64_ROOT}/RecompiledFuncsPoint0" "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include")
add_test(NAME sunny_native_animal_replay COMMAND wr64_sunny_animals_test)
set(WR64_TEST_ROM "" CACHE FILEPATH "Private USA Rev1 ROM, read in memory only")
if(WR64_TEST_ROM)
    set(INTEGRATION_NATIVE "${CMAKE_CURRENT_BINARY_DIR}/native_animals_integration.c")
    add_custom_command(OUTPUT "${INTEGRATION_NATIVE}"
        COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_native.py" "${WR64_ROOT}" "${INTEGRATION_NATIVE}" integration
        DEPENDS extract_native.py "${WR64_ROOT}/config/us.rev1.toml"
            "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_0.c" "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_6.c"
            "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_9.c" "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_10.c"
            "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_17.c" "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_19.c" VERBATIM)
    add_executable(wr64_sunny_animals_integration_test animals_integration_test.cpp "${INTEGRATION_NATIVE}"
        "${WR64_ROOT}/src/wr64_sunny_animals.cpp" "${WR64_ROOT}/src/wr64_sunny_animals_load.cpp")
    target_compile_features(wr64_sunny_animals_integration_test PRIVATE cxx_std_20)
    target_include_directories(wr64_sunny_animals_integration_test PRIVATE "${WR64_ROOT}/tests/sunny_two_player_detail"
        "${WR64_ROOT}/include" "${WR64_ROOT}/RecompiledFuncsPoint0" "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include")
    add_test(NAME sunny_native_animal_asset_draw COMMAND "${Python3_EXECUTABLE}"
        "${WR64_ROOT}/tests/sunny_two_player_detail/run_private_rom_test.py"
        "$<TARGET_FILE:wr64_sunny_animals_integration_test>" "${WR64_TEST_ROM}")
    set(ALL_COURSES_NATIVE "${CMAKE_CURRENT_BINARY_DIR}/native_animals_all_courses.c")
    add_custom_command(OUTPUT "${ALL_COURSES_NATIVE}"
        COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_native.py" "${WR64_ROOT}" "${ALL_COURSES_NATIVE}" allcourses
        DEPENDS extract_native.py "${WR64_ROOT}/config/us.rev1.toml"
            "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_0.c" "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_6.c"
            "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_9.c" "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_10.c"
            "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_17.c" "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_19.c" VERBATIM)
    add_executable(wr64_all_course_animals_test animals_all_courses_test.cpp "${ALL_COURSES_NATIVE}"
        "${WR64_ROOT}/src/wr64_sunny_animals.cpp" "${WR64_ROOT}/src/wr64_sunny_animals_load.cpp")
    target_compile_features(wr64_all_course_animals_test PRIVATE cxx_std_20)
    target_include_directories(wr64_all_course_animals_test PRIVATE "${WR64_ROOT}/tests/sunny_two_player_detail"
        "${WR64_ROOT}/include" "${WR64_ROOT}/RecompiledFuncsPoint0" "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include")
    add_test(NAME all_course_native_animal_asset_draw COMMAND "${Python3_EXECUTABLE}"
        "${WR64_ROOT}/tests/sunny_two_player_detail/run_private_rom_test.py"
        "$<TARGET_FILE:wr64_all_course_animals_test>" "${WR64_TEST_ROM}")
endif()
