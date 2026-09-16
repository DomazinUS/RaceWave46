cmake_minimum_required(VERSION 3.20)
project(Wr64DolphinFreeRideSettingsTests LANGUAGES CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(RUNTIME "${WR64_ROOT}/lib/N64ModernRuntime")
set(SCHEMA "${CMAKE_CURRENT_BINARY_DIR}/free_ride_schema.cpp")
add_custom_command(OUTPUT "${SCHEMA}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_schema.py" "${WR64_ROOT}" "${SCHEMA}"
    DEPENDS extract_schema.py "${WR64_ROOT}/src/wr64_frontend.cpp" VERBATIM)
add_executable(wr64_dolphin_free_ride_settings_test settings_test.cpp "${SCHEMA}"
    "${WR64_ROOT}/src/wr64_free_ride_menu.cpp"
    "${RUNTIME}/librecomp/src/config.cpp" "${RUNTIME}/librecomp/src/config_option.cpp"
    "${RUNTIME}/librecomp/src/files.cpp")
target_compile_features(wr64_dolphin_free_ride_settings_test PRIVATE cxx_std_20)
target_compile_definitions(wr64_dolphin_free_ride_settings_test PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
target_include_directories(wr64_dolphin_free_ride_settings_test PRIVATE
    "${WR64_ROOT}/tests/config_scope/stubs" "${WR64_ROOT}/include"
    "${RUNTIME}/librecomp/include" "${RUNTIME}/librecomp/include/librecomp"
    "${RUNTIME}/N64Recomp/include" "${RUNTIME}/thirdparty")
add_test(NAME dolphin_free_ride_saved_setting_and_menu
    COMMAND wr64_dolphin_free_ride_settings_test "${CMAKE_CURRENT_BINARY_DIR}/synthetic-profiles")
