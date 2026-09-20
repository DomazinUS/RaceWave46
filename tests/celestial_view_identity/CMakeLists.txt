cmake_minimum_required(VERSION 3.20)
project(Wr64CelestialViewIdentity LANGUAGES CXX)
enable_testing()
find_package(Python3 REQUIRED COMPONENTS Interpreter)
get_filename_component(WR64_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
set(EXTRACTED "${CMAKE_CURRENT_BINARY_DIR}/pairing.inc")
set(ANCHOR "${CMAKE_CURRENT_BINARY_DIR}/renderer_anchor.inc")
add_custom_command(OUTPUT "${EXTRACTED}" "${ANCHOR}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract.py" "${WR64_ROOT}" "${EXTRACTED}"
    DEPENDS extract.py "${WR64_ROOT}/lib/rt64/src/hle/rt64_game_frame.cpp"
        "${WR64_ROOT}/lib/rt64/src/render/rt64_framebuffer_renderer.cpp")
add_executable(celestial_view_identity_test identity_test.cpp "${EXTRACTED}"
    "${WR64_ROOT}/lib/rt64/src/common/rt64_common.cpp")
target_compile_features(celestial_view_identity_test PRIVATE cxx_std_17)
target_include_directories(celestial_view_identity_test PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
    "${WR64_ROOT}/lib/rt64/src" "${WR64_ROOT}/lib/rt64/src/contrib/hlslpp/include")
add_test(NAME celestial_rect_view_histories COMMAND celestial_view_identity_test)
add_executable(celestial_hud_anchor_test hud_anchor_test.cpp "${ANCHOR}"
    "${WR64_ROOT}/lib/rt64/src/common/rt64_common.cpp")
target_compile_features(celestial_hud_anchor_test PRIVATE cxx_std_17)
target_include_directories(celestial_hud_anchor_test PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
    "${WR64_ROOT}/lib/rt64/src" "${WR64_ROOT}/lib/rt64/src/contrib/hlslpp/include")
add_test(NAME celestial_scene_not_hud COMMAND celestial_hud_anchor_test)
