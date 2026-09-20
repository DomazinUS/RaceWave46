cmake_minimum_required(VERSION 3.20)
project(Wr64FreeRideMenu LANGUAGES C CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(NATIVE "${CMAKE_CURRENT_BINARY_DIR}/native_menu.c")
add_custom_command(OUTPUT "${NATIVE}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_native.py" "${ROOT}" "${NATIVE}"
    DEPENDS extract_native.py "${ROOT}/RecompiledFuncsPoint0/funcs_21.c" "${ROOT}/config/us.rev1.toml")
add_executable(free_ride_menu_test menu_test.cpp "${NATIVE}" "${ROOT}/src/wr64_free_ride_menu.cpp")
target_compile_features(free_ride_menu_test PRIVATE cxx_std_20)
target_include_directories(free_ride_menu_test PRIVATE "${ROOT}/include" "${ROOT}/RecompiledFuncsPoint0"
    "${ROOT}/lib/N64ModernRuntime/N64Recomp/include" "${ROOT}/tests/sunny_two_player_detail")
add_test(NAME native_free_ride_course_menu COMMAND free_ride_menu_test)
