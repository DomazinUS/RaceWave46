cmake_minimum_required(VERSION 3.20)
project(Wr64ForensicDisabled LANGUAGES C CXX)
enable_testing()
get_filename_component(WR64_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
add_executable(forensic_disabled_test disabled_test.cpp legacy_calls.c "${WR64_ROOT}/src/wr64_forensic.cpp")
target_compile_features(forensic_disabled_test PRIVATE cxx_std_17)
target_include_directories(forensic_disabled_test PRIVATE "${WR64_ROOT}/include")
target_compile_definitions(forensic_disabled_test PRIVATE _CRT_SECURE_NO_WARNINGS)
add_test(NAME forensic_disabled COMMAND forensic_disabled_test)
set_tests_properties(forensic_disabled PROPERTIES ENVIRONMENT "WR64_FORENSIC_RING_MB=2048;WR64_FORENSIC_OUTPUT=unexpected-capture")

# Compile the retained implementation too, without linking or initializing its
# recorder. This catches accidental damage to the explicitly enabled path.
add_library(forensic_enabled_compile OBJECT "${WR64_ROOT}/src/wr64_forensic.cpp")
target_compile_features(forensic_enabled_compile PRIVATE cxx_std_17)
target_include_directories(forensic_enabled_compile PRIVATE "${WR64_ROOT}/include")
target_compile_definitions(forensic_enabled_compile PRIVATE WR64_ENABLE_DIAGNOSTICS=1 _CRT_SECURE_NO_WARNINGS NOMINMAX)
