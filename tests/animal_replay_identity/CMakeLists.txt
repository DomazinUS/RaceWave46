cmake_minimum_required(VERSION 3.20)
project(Wr64AnimalReplayIdentity LANGUAGES CXX)
enable_testing()
find_package(Python3 REQUIRED COMPONENTS Interpreter)
get_filename_component(WR64_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
set(EXTRACTED "${CMAKE_CURRENT_BINARY_DIR}/identity_functions.inc")
add_custom_command(OUTPUT "${EXTRACTED}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract.py" "${WR64_ROOT}" "${EXTRACTED}"
    DEPENDS extract.py "${WR64_ROOT}/lib/rt64/src/hle/rt64_game_frame.cpp")
add_executable(animal_replay_identity_test identity_test.cpp "${EXTRACTED}"
    "${WR64_ROOT}/lib/rt64/src/common/rt64_common.cpp")
target_compile_features(animal_replay_identity_test PRIVATE cxx_std_17)
target_compile_definitions(animal_replay_identity_test PRIVATE HLSL_CPU)
target_include_directories(animal_replay_identity_test PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
    "${WR64_ROOT}/lib/rt64/src" "${WR64_ROOT}/lib/rt64/src/contrib/hlslpp/include")
add_test(NAME exact_animal_replay_identities COMMAND animal_replay_identity_test)
