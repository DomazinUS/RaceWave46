cmake_minimum_required(VERSION 3.20)
project(Wr64DolphinVisibleEffects LANGUAGES C CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(NATIVE_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/native_effects.c")
add_custom_command(OUTPUT "${NATIVE_SOURCE}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_native.py" "${WR64_ROOT}" "${NATIVE_SOURCE}"
    DEPENDS extract_native.py pre_effects_hooks.json "${WR64_ROOT}/config/us.rev1.toml"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_5.c" "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_1.c" VERBATIM)
add_executable(wr64_dolphin_visible_effects_test effects_test.cpp "${NATIVE_SOURCE}" "${WR64_ROOT}/src/wr64_ultrawide.cpp")
target_compile_features(wr64_dolphin_visible_effects_test PRIVATE cxx_std_20)
target_include_directories(wr64_dolphin_visible_effects_test PRIVATE "${WR64_ROOT}/include" "${WR64_ROOT}/RecompiledFuncsPoint0"
    "${WR64_ROOT}/lib/N64ModernRuntime/N64Recomp/include" "${WR64_ROOT}/lib/rt64/src")
foreach(mode IN ITEMS off no_native no_effects malformed enabled)
    add_test(NAME dolphin_visible_effects_${mode} COMMAND wr64_dolphin_visible_effects_test ${mode})
endforeach()
set_tests_properties(dolphin_visible_effects_off PROPERTIES ENVIRONMENT "WR64_DOLPHIN_SUN_NATIVE_EXIT=0;WR64_DOLPHIN_SUN_VISIBLE_EFFECTS=0")
set_tests_properties(dolphin_visible_effects_no_native PROPERTIES ENVIRONMENT "WR64_DOLPHIN_SUN_NATIVE_EXIT=0;WR64_DOLPHIN_SUN_VISIBLE_EFFECTS=1")
set_tests_properties(dolphin_visible_effects_no_effects PROPERTIES ENVIRONMENT "WR64_DOLPHIN_SUN_NATIVE_EXIT=1;WR64_DOLPHIN_SUN_VISIBLE_EFFECTS=0")
set_tests_properties(dolphin_visible_effects_malformed PROPERTIES ENVIRONMENT "WR64_DOLPHIN_SUN_NATIVE_EXIT=1;WR64_DOLPHIN_SUN_VISIBLE_EFFECTS=10")
set_tests_properties(dolphin_visible_effects_enabled PROPERTIES ENVIRONMENT "WR64_DOLPHIN_SUN_NATIVE_EXIT=1;WR64_DOLPHIN_SUN_VISIBLE_EFFECTS=1")
add_test(NAME dolphin_visible_effects_default_on COMMAND "${CMAKE_COMMAND}" -E env
    --unset=WR64_DOLPHIN_SUN_NATIVE_EXIT --unset=WR64_DOLPHIN_SUN_VISIBLE_EFFECTS
    "$<TARGET_FILE:wr64_dolphin_visible_effects_test>" default)
add_test(NAME dolphin_visible_effects_default_matches_enabled
    COMMAND "${Python3_EXECUTABLE}" "${WR64_ROOT}/tests/dolphin_sun_native_exit/compare_gates.py" effects "$<TARGET_FILE:wr64_dolphin_visible_effects_test>")
