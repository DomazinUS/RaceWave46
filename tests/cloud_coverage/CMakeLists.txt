cmake_minimum_required(VERSION 3.20)
project(Wr64CloudCoverageTests LANGUAGES CXX)
enable_testing()
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
add_executable(wr64_cloud_coverage_test cloud_coverage_test.cpp)
target_compile_features(wr64_cloud_coverage_test PRIVATE cxx_std_20)
target_include_directories(wr64_cloud_coverage_test PRIVATE "${WR64_ROOT}/lib/rt64/src")
add_test(NAME cloud_annulus_native_fixtures_and_geometry COMMAND wr64_cloud_coverage_test)

find_package(Python3 COMPONENTS Interpreter REQUIRED)
set(WR64_CLOUD_RESET "${CMAKE_CURRENT_BINARY_DIR}/actual_reset.cpp")
add_custom_command(OUTPUT "${WR64_CLOUD_RESET}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_reset.py" "${WR64_ROOT}" "${WR64_CLOUD_RESET}"
    DEPENDS extract_reset.py "${WR64_ROOT}/lib/rt64/src/hle/rt64_workload.cpp"
        "${WR64_ROOT}/lib/rt64/src/render/rt64_framebuffer_renderer.cpp"
        "${WR64_ROOT}/lib/rt64/src/hle/rt64_state.cpp"
    VERBATIM)
add_executable(wr64_cloud_renderer_integration_test renderer_integration_test.cpp "${WR64_CLOUD_RESET}"
    "${WR64_ROOT}/lib/rt64/src/common/rt64_common.cpp"
    "${WR64_ROOT}/lib/rt64/src/common/rt64_math.cpp")
target_compile_features(wr64_cloud_renderer_integration_test PRIVATE cxx_std_20)
target_compile_definitions(wr64_cloud_renderer_integration_test PRIVATE HLSL_CPU NOMINMAX)
target_include_directories(wr64_cloud_renderer_integration_test PRIVATE
    "${WR64_ROOT}/lib/rt64/src"
    "${WR64_ROOT}/lib/rt64/include"
    "${WR64_ROOT}/lib/rt64/src/contrib"
    "${WR64_ROOT}/lib/rt64/src/contrib/plume"
    "${WR64_ROOT}/lib/rt64/src/contrib/hlslpp/include"
    "${WR64_ROOT}/lib/rt64/src/contrib/imgui"
    "${WR64_ROOT}/lib/rt64/src/contrib/mupen64plus-core/src/api")
add_test(NAME cloud_renderer_actual_types COMMAND wr64_cloud_renderer_integration_test 1)
add_test(NAME cloud_renderer_default_unchanged COMMAND wr64_cloud_renderer_integration_test "")
add_test(NAME cloud_renderer_disabled_unchanged COMMAND wr64_cloud_renderer_integration_test 0)
add_test(NAME cloud_renderer_non_exact_gate_unchanged COMMAND wr64_cloud_renderer_integration_test 10)

set(RUNTIME "${WR64_ROOT}/lib/N64ModernRuntime")
set(SCHEMA "${CMAKE_CURRENT_BINARY_DIR}/cloud_schema.cpp")
add_custom_command(OUTPUT "${SCHEMA}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_schema.py" "${WR64_ROOT}" "${SCHEMA}"
    DEPENDS extract_schema.py "${WR64_ROOT}/src/wr64_frontend.cpp" VERBATIM)
add_executable(wr64_cloud_settings_test settings_test.cpp "${SCHEMA}"
    "${RUNTIME}/librecomp/src/config.cpp" "${RUNTIME}/librecomp/src/config_option.cpp" "${RUNTIME}/librecomp/src/files.cpp")
target_compile_features(wr64_cloud_settings_test PRIVATE cxx_std_20)
target_include_directories(wr64_cloud_settings_test PRIVATE "${WR64_ROOT}/tests/config_scope/stubs"
    "${WR64_ROOT}/include" "${WR64_ROOT}/lib/rt64/src" "${RUNTIME}/librecomp/include"
    "${RUNTIME}/librecomp/include/librecomp" "${RUNTIME}/N64Recomp/include" "${RUNTIME}/thirdparty")
add_test(NAME cloud_setting_persistence_and_load COMMAND wr64_cloud_settings_test)
