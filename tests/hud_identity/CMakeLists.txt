cmake_minimum_required(VERSION 3.20)
project(Wr64HudIdentityTests LANGUAGES CXX)
enable_testing()
get_filename_component(WR64_SOURCE_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
add_executable(wr64_hud_identity_test hud_identity_test.cpp
    "${WR64_SOURCE_ROOT}/lib/rt64/src/common/rt64_common.cpp")
target_compile_features(wr64_hud_identity_test PRIVATE cxx_std_17)
target_include_directories(wr64_hud_identity_test PRIVATE
    "${WR64_SOURCE_ROOT}/lib/rt64/src"
    "${WR64_SOURCE_ROOT}/lib/rt64/src/contrib/hlslpp/include")
add_test(NAME hud_identity_invariants COMMAND wr64_hud_identity_test)
