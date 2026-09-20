cmake_minimum_required(VERSION 3.20)
project(Wr64DolphinSunNativeExitTests LANGUAGES CXX)
enable_testing()
find_package(Python3 COMPONENTS Interpreter REQUIRED)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(PRODUCER "${CMAKE_CURRENT_BINARY_DIR}/producer.cpp")
add_custom_command(OUTPUT "${PRODUCER}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_producer.py" "${WR64_ROOT}" "${PRODUCER}"
    DEPENDS extract_producer.py "${WR64_ROOT}/src/wr64_render_provenance.cpp"
    VERBATIM)
add_executable(dolphin_sun_native_exit_test dolphin_sun_native_exit_test.cpp "${PRODUCER}")
target_compile_features(dolphin_sun_native_exit_test PRIVATE cxx_std_20)
target_compile_definitions(dolphin_sun_native_exit_test PRIVATE WR64_ENABLE_RT64)
target_include_directories(dolphin_sun_native_exit_test PRIVATE "${WR64_ROOT}/lib/rt64/src" "${WR64_ROOT}/include")
add_test(NAME dolphin_native_exit_enabled COMMAND dolphin_sun_native_exit_test 1)
add_test(NAME dolphin_native_exit_default_on COMMAND dolphin_sun_native_exit_test "")
add_test(NAME dolphin_native_exit_explicit_off COMMAND dolphin_sun_native_exit_test 0)
add_test(NAME dolphin_native_exit_non_exact_gate COMMAND dolphin_sun_native_exit_test 10)
add_test(NAME dolphin_native_exit_default_matches_enabled
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/compare_gates.py" native "$<TARGET_FILE:dolphin_sun_native_exit_test>")

# Compile against the engine's real draw data and RDP default alignment. This
# catches handoff failures that a structurally similar mock cannot represent.
add_executable(dolphin_sun_renderer_claim_test renderer_claim_test.cpp
    "${WR64_ROOT}/lib/rt64/src/common/rt64_common.cpp")
target_compile_features(dolphin_sun_renderer_claim_test PRIVATE cxx_std_20)
target_compile_definitions(dolphin_sun_renderer_claim_test PRIVATE HLSL_CPU NOMINMAX)
target_include_directories(dolphin_sun_renderer_claim_test PRIVATE
    "${WR64_ROOT}/lib/rt64/src"
    "${WR64_ROOT}/lib/rt64/include"
    "${WR64_ROOT}/lib/rt64/src/contrib"
    "${WR64_ROOT}/lib/rt64/src/contrib/plume"
    "${WR64_ROOT}/lib/rt64/src/contrib/hlslpp/include"
    "${WR64_ROOT}/lib/rt64/src/contrib/imgui"
    "${WR64_ROOT}/lib/rt64/src/contrib/mupen64plus-core/src/api")
add_test(NAME dolphin_native_exit_real_renderer_claim COMMAND dolphin_sun_renderer_claim_test)
