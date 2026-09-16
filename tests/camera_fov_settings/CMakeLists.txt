cmake_minimum_required(VERSION 3.20)
project(Wr64CameraFovSettingsTests LANGUAGES CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(RUNTIME "${WR64_ROOT}/lib/N64ModernRuntime")
set(SCHEMA "${CMAKE_CURRENT_BINARY_DIR}/fov_schema.cpp")
add_custom_command(OUTPUT "${SCHEMA}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_schema.py" "${WR64_ROOT}" "${SCHEMA}"
    DEPENDS extract_schema.py "${WR64_ROOT}/src/wr64_frontend.cpp" VERBATIM)
add_executable(wr64_camera_fov_settings_test settings_test.cpp "${SCHEMA}"
    "${WR64_ROOT}/src/wr64_camera_fov.cpp"
    "${RUNTIME}/librecomp/src/config.cpp"
    "${RUNTIME}/librecomp/src/config_option.cpp"
    "${RUNTIME}/librecomp/src/files.cpp")
target_compile_features(wr64_camera_fov_settings_test PRIVATE cxx_std_20)
target_include_directories(wr64_camera_fov_settings_test PRIVATE
    "${WR64_ROOT}/tests/config_scope/stubs" "${WR64_ROOT}/include"
    "${RUNTIME}/librecomp/include" "${RUNTIME}/librecomp/include/librecomp"
    "${RUNTIME}/N64Recomp/include" "${RUNTIME}/thirdparty")
add_test(NAME gameplay_fov_frontend_persistence COMMAND wr64_camera_fov_settings_test)
