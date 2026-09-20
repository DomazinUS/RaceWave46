cmake_minimum_required(VERSION 3.20)
project(Wr64RTTwoPlayerScopeTests LANGUAGES CXX)
enable_testing()
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
add_executable(wr64_rt_two_player_scope_test scope_test.cpp)
target_compile_features(wr64_rt_two_player_scope_test PRIVATE cxx_std_20)
target_include_directories(wr64_rt_two_player_scope_test PRIVATE "${WR64_ROOT}/lib/rt64/src")
add_test(NAME rt_all_course_two_player_scope COMMAND wr64_rt_two_player_scope_test)

# Exercise the original public predicates/light reader unchanged alongside the
# new explicit two-player entry points.
add_executable(wr64_rt_original_scope_test ../rt_reflection_setting/reflection_scope_test.cpp)
add_executable(wr64_rt_original_shadow_test ../rt_shadows/shadow_test.cpp)
foreach(target wr64_rt_original_scope_test wr64_rt_original_shadow_test)
    target_compile_features(${target} PRIVATE cxx_std_20)
    target_include_directories(${target} PRIVATE "${WR64_ROOT}/lib/rt64/src")
endforeach()
add_test(NAME rt_original_scene_scope COMMAND wr64_rt_original_scope_test)
add_test(NAME rt_original_authored_light COMMAND wr64_rt_original_shadow_test)
