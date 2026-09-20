cmake_minimum_required(VERSION 3.20)
project(Wr64ConfigScopeTests LANGUAGES CXX)

enable_testing()
get_filename_component(WR64_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
set(RUNTIME "${WR64_ROOT}/lib/N64ModernRuntime")
add_executable(wr64_config_scope_test config_scope_test.cpp
    "${RUNTIME}/librecomp/src/config.cpp"
    "${RUNTIME}/librecomp/src/config_option.cpp"
    "${RUNTIME}/librecomp/src/files.cpp")
target_compile_features(wr64_config_scope_test PRIVATE cxx_std_20)
target_include_directories(wr64_config_scope_test PRIVATE stubs
    "${RUNTIME}/librecomp/include"
    "${RUNTIME}/librecomp/include/librecomp"
    "${RUNTIME}/N64Recomp/include"
    "${RUNTIME}/thirdparty")
add_test(NAME config_profile_storage_and_reload
    COMMAND wr64_config_scope_test "${CMAKE_CURRENT_BINARY_DIR}/isolated-profiles")

add_executable(wr64_gameplay_settings_test gameplay_settings_test.cpp
    "${RUNTIME}/librecomp/src/config.cpp"
    "${RUNTIME}/librecomp/src/config_option.cpp"
    "${RUNTIME}/librecomp/src/files.cpp")
target_compile_features(wr64_gameplay_settings_test PRIVATE cxx_std_20)
target_include_directories(wr64_gameplay_settings_test PRIVATE stubs
    "${WR64_ROOT}/include"
    "${RUNTIME}/librecomp/include"
    "${RUNTIME}/librecomp/include/librecomp"
    "${RUNTIME}/N64Recomp/include"
    "${RUNTIME}/thirdparty")
add_test(NAME gameplay_settings_migration
    COMMAND wr64_gameplay_settings_test "${CMAKE_CURRENT_BINARY_DIR}/isolated-gameplay-profiles")
