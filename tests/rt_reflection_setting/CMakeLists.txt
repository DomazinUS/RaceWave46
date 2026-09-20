cmake_minimum_required(VERSION 3.20)
project(Wr64ReflectionSettingTests LANGUAGES CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(REFLECTION_SCHEMA "${CMAKE_CURRENT_BINARY_DIR}/reflection_schema.cpp")
add_custom_command(OUTPUT "${REFLECTION_SCHEMA}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_schema.py" "${WR64_ROOT}" "${REFLECTION_SCHEMA}"
    DEPENDS extract_schema.py "${WR64_ROOT}/src/wr64_frontend.cpp"
    VERBATIM)
add_executable(wr64_reflection_setting_test reflection_setting_test.cpp "${REFLECTION_SCHEMA}"
    "${WR64_ROOT}/lib/N64ModernRuntime/librecomp/src/config.cpp"
    "${WR64_ROOT}/lib/N64ModernRuntime/librecomp/src/config_option.cpp"
    "${WR64_ROOT}/lib/N64ModernRuntime/librecomp/src/files.cpp")
target_compile_features(wr64_reflection_setting_test PRIVATE cxx_std_20)
# The isolated fixture exercises the bounded diagnostic sink; shipping builds
# keep this opt-in disabled. Its log lives only in the fixture's private profile.
target_compile_definitions(wr64_reflection_setting_test PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN WR64_ENABLE_DIAGNOSTICS=1)
target_include_directories(wr64_reflection_setting_test PRIVATE
    "${WR64_ROOT}/include"
    "${WR64_ROOT}/lib/N64ModernRuntime/ultramodern/include"
    "${WR64_ROOT}/lib/rt64/src"
    "${WR64_ROOT}/tests/config_scope/stubs"
    "${WR64_ROOT}/lib/N64ModernRuntime/librecomp/include"
    "${WR64_ROOT}/lib/N64ModernRuntime/librecomp/include/librecomp"
    "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include"
    "${WR64_ROOT}/lib/N64ModernRuntime/thirdparty")
if(WIN32)
    target_link_libraries(wr64_reflection_setting_test PRIVATE shell32)
    if(EXISTS "${WR64_ROOT}/RUN-RT-REFLECTIONS.ps1")
        add_test(NAME reflection_helper_launch
            COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/verify_launcher.py" "${WR64_ROOT}")
    endif()
endif()
add_test(NAME reflection_frontend_persistence COMMAND wr64_reflection_setting_test)

add_executable(wr64_reflection_scope_test reflection_scope_test.cpp)
target_compile_features(wr64_reflection_scope_test PRIVATE cxx_std_20)
target_include_directories(wr64_reflection_scope_test PRIVATE "${WR64_ROOT}/lib/rt64/src")
add_test(NAME reflection_native_scope COMMAND wr64_reflection_scope_test)

add_executable(wr64_reflection_preview_test ../rt_reflections/preview_selection.cpp)
target_compile_features(wr64_reflection_preview_test PRIVATE cxx_std_17)
add_test(NAME reflection_preview_domain COMMAND wr64_reflection_preview_test)

add_executable(wr64_reflection_sky_selection_test ../rt_reflections/sky_selection.cpp)
target_compile_features(wr64_reflection_sky_selection_test PRIVATE cxx_std_17)
add_test(NAME reflection_sky_capture_guards COMMAND wr64_reflection_sky_selection_test)
