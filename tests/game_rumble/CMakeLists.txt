cmake_minimum_required(VERSION 3.20)
project(Wr64GameRumbleTests LANGUAGES CXX)
enable_testing()
get_filename_component(WR64_SOURCE_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
add_executable(wr64_game_rumble_test
    game_rumble_test.cpp
    "${WR64_SOURCE_ROOT}/src/wr64_game_rumble.cpp")
target_compile_features(wr64_game_rumble_test PRIVATE cxx_std_20)
target_include_directories(wr64_game_rumble_test PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/stubs" "${WR64_SOURCE_ROOT}/include")
add_test(NAME game_rumble_semantics COMMAND wr64_game_rumble_test)
add_library(wr64_controller_smoke_compile OBJECT "${WR64_SOURCE_ROOT}/src/wr64_controller_smoke.cpp")
target_compile_features(wr64_controller_smoke_compile PRIVATE cxx_std_20)
target_include_directories(wr64_controller_smoke_compile PRIVATE
    "${WR64_SOURCE_ROOT}/include"
    "${WR64_SOURCE_ROOT}/lib/rt64/src/contrib/mupen64plus-win32-deps/SDL2-2.26.3/include")
add_executable(wr64_ultrawide_test ultrawide_test.cpp
    "${WR64_SOURCE_ROOT}/src/wr64_ultrawide.cpp"
    "${WR64_SOURCE_ROOT}/lib/rt64/src/common/rt64_common.cpp")
target_compile_features(wr64_ultrawide_test PRIVATE cxx_std_17)
target_include_directories(wr64_ultrawide_test PRIVATE
    "${WR64_SOURCE_ROOT}/include"
    "${WR64_SOURCE_ROOT}/lib/rt64/src"
    "${WR64_SOURCE_ROOT}/lib/rt64/src/contrib/hlslpp/include")
add_test(NAME ultrawide_layout_invariants COMMAND wr64_ultrawide_test)
find_package(Python3 REQUIRED COMPONENTS Interpreter)
set(FINISH_HUD_RENDERER "${CMAKE_CURRENT_BINARY_DIR}/finish_hud_renderer.cpp")
add_custom_command(OUTPUT "${FINISH_HUD_RENDERER}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_finish_hud.py"
        "${WR64_SOURCE_ROOT}" "${FINISH_HUD_RENDERER}"
    DEPENDS "${CMAKE_CURRENT_LIST_DIR}/extract_finish_hud.py"
        "${WR64_SOURCE_ROOT}/lib/rt64/src/render/rt64_framebuffer_renderer.cpp"
    VERBATIM)
add_executable(wr64_finish_hud_test finish_hud_test.cpp "${FINISH_HUD_RENDERER}"
    "${WR64_SOURCE_ROOT}/lib/rt64/src/common/rt64_common.cpp")
target_compile_features(wr64_finish_hud_test PRIVATE cxx_std_17)
target_include_directories(wr64_finish_hud_test PRIVATE "${CMAKE_CURRENT_LIST_DIR}"
    "${WR64_SOURCE_ROOT}/include" "${WR64_SOURCE_ROOT}/lib/rt64/src"
    "${WR64_SOURCE_ROOT}/lib/rt64/src/contrib/hlslpp/include")
add_test(NAME finish_hud_actual_renderer_baseline_and_wide COMMAND wr64_finish_hud_test)
