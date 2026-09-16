cmake_minimum_required(VERSION 3.20)
project(Wr64ControllerIntegrationTests LANGUAGES CXX)
enable_testing()
get_filename_component(WR64_SOURCE_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
set(FRONTEND "${WR64_SOURCE_ROOT}/lib/RecompFrontend")
set(SDL_ROOT "${WR64_SOURCE_ROOT}/lib/rt64/src/contrib/mupen64plus-win32-deps/SDL2-2.26.3")
set(INPUT_SOURCES input_binding input_events input_mapping input_state input_types players profiles)
list(TRANSFORM INPUT_SOURCES PREPEND "${FRONTEND}/recompinput/src/")
list(TRANSFORM INPUT_SOURCES APPEND ".cpp")
add_executable(wr64_controller_integration_test
    controller_integration_test.cpp ${INPUT_SOURCES}
    "${WR64_SOURCE_ROOT}/src/wr64_input.cpp"
    "${WR64_SOURCE_ROOT}/lib/N64ModernRuntime/ultramodern/src/input.cpp"
    "${FRONTEND}/recompui/src/config/ui_config_tab_general.cpp"
    "${WR64_SOURCE_ROOT}/lib/N64ModernRuntime/librecomp/src/config.cpp"
    "${WR64_SOURCE_ROOT}/lib/N64ModernRuntime/librecomp/src/config_option.cpp"
    "${WR64_SOURCE_ROOT}/lib/N64ModernRuntime/librecomp/src/files.cpp")
target_compile_features(wr64_controller_integration_test PRIVATE cxx_std_20)
target_compile_definitions(wr64_controller_integration_test PRIVATE
    WR64_ENABLE_FRONTEND SDL_MAIN_HANDLED NOMINMAX
    WR64_TEST_GENERAL_CONFIG_DIR="${CMAKE_CURRENT_BINARY_DIR}/isolated-general")
target_compile_options(wr64_controller_integration_test PRIVATE
    "$<$<CXX_COMPILER_ID:MSVC>:/FI${CMAKE_CURRENT_LIST_DIR}/providers.h>")
target_include_directories(wr64_controller_integration_test PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/stubs"
    "${CMAKE_CURRENT_LIST_DIR}"
    "${WR64_SOURCE_ROOT}/include"
    "${FRONTEND}/recompinput/include"
    "${FRONTEND}/recompinput/include/recompinput"
    "${FRONTEND}/recompinput/src"
    "${FRONTEND}/lib/GamepadMotionHelpers"
    "${WR64_SOURCE_ROOT}/lib/N64ModernRuntime/thirdparty"
    "${WR64_SOURCE_ROOT}/lib/N64ModernRuntime/ultramodern/include"
    "${WR64_SOURCE_ROOT}/lib/N64ModernRuntime/librecomp/include"
    "${WR64_SOURCE_ROOT}/lib/N64ModernRuntime/librecomp/include/librecomp"
    "${WR64_SOURCE_ROOT}/lib/N64ModernRuntime/N64Recomp/include"
    "${SDL_ROOT}/include")
target_link_libraries(wr64_controller_integration_test PRIVATE "${SDL_ROOT}/lib/x64/SDL2.lib")
add_custom_command(TARGET wr64_controller_integration_test POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${SDL_ROOT}/lib/x64/SDL2.dll"
        "$<TARGET_FILE_DIR:wr64_controller_integration_test>")
add_test(NAME controller_virtual_sdl_integration COMMAND wr64_controller_integration_test)
add_test(NAME controller_virtual_sdl_ps5_optout COMMAND wr64_controller_integration_test --ps5-rumble-disabled)
set_tests_properties(controller_virtual_sdl_integration controller_virtual_sdl_ps5_optout
    PROPERTIES RESOURCE_LOCK wr64_controller_general_settings)
