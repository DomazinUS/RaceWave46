cmake_minimum_required(VERSION 3.20)
project(Wr64ReleaseDefaultsTests LANGUAGES CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(DEFAULTS_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/release_producers.cpp")
add_custom_command(OUTPUT "${DEFAULTS_SOURCE}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_defaults.py" "${WR64_ROOT}" "${DEFAULTS_SOURCE}"
    DEPENDS extract_defaults.py "${WR64_ROOT}/src/wr64_editions.cpp"
        "${WR64_ROOT}/src/recomp_shims.cpp" "${WR64_ROOT}/src/rt64_renderer.cpp"
        "${WR64_ROOT}/src/wr64_frontend.cpp" "${WR64_ROOT}/lib/rt64/src/hle/rt64_workload_queue.cpp"
        "${WR64_ROOT}/lib/RecompFrontend/recompui/src/config/ui_config_tab_graphics.cpp"
        "${WR64_ROOT}/lib/RecompFrontend/recompui/src/config/ui_config_tab_general.cpp"
        "${WR64_ROOT}/lib/RecompFrontend/recompui/src/config/ui_config_tab_sound.cpp"
    VERBATIM)
add_executable(wr64_release_defaults_test release_defaults_test.cpp "${DEFAULTS_SOURCE}"
    "${WR64_ROOT}/lib/rt64/src/common/rt64_user_configuration.cpp"
    "${WR64_ROOT}/lib/N64ModernRuntime/librecomp/src/config.cpp"
    "${WR64_ROOT}/lib/N64ModernRuntime/librecomp/src/config_option.cpp"
    "${WR64_ROOT}/lib/N64ModernRuntime/librecomp/src/files.cpp")
target_compile_features(wr64_release_defaults_test PRIVATE cxx_std_20)
target_compile_definitions(wr64_release_defaults_test PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
target_include_directories(wr64_release_defaults_test PRIVATE
    "${WR64_ROOT}/tests/config_scope/stubs"
    "${WR64_ROOT}/lib/N64ModernRuntime/librecomp/include"
    "${WR64_ROOT}/lib/N64ModernRuntime/librecomp/include/librecomp"
    "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include"
    "${WR64_ROOT}/lib/N64ModernRuntime/thirdparty"
    "${WR64_ROOT}/include" "${WR64_ROOT}/lib/rt64/src" "${WR64_ROOT}/lib/rt64/src/contrib"
    "${WR64_ROOT}/lib/N64ModernRuntime/ultramodern/include")
if(WIN32)
    target_link_libraries(wr64_release_defaults_test PRIVATE shell32)
endif()
add_test(NAME release_startup_without_overrides
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/run_without_overrides.py"
        --single "$<TARGET_FILE:wr64_release_defaults_test>")
set(WR64_RELEASE_REUSE_EXISTING_TESTS OFF CACHE BOOL "Run already-built enhancement and persistence executables with no WR64 environment overrides")
if(WR64_RELEASE_REUSE_EXISTING_TESTS)
    add_test(NAME release_enhancements_without_overrides
        COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/run_without_overrides.py"
            --root "${WR64_ROOT}")
endif()
