cmake_minimum_required(VERSION 3.20)
project(Wr64RiderViewIdentity LANGUAGES CXX)
enable_testing()
find_package(Python3 REQUIRED COMPONENTS Interpreter)
get_filename_component(WR64_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
set(EXTRACTED "${CMAKE_CURRENT_BINARY_DIR}/identity_functions.inc")
add_custom_command(OUTPUT "${EXTRACTED}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract.py" "${WR64_ROOT}" "${EXTRACTED}"
    DEPENDS extract.py
        "${WR64_ROOT}/lib/rt64/src/hle/rt64_rsp.cpp"
        "${WR64_ROOT}/lib/rt64/src/hle/rt64_game_frame.cpp"
        "${WR64_ROOT}/lib/rt64/src/render/rt64_transform_processor.cpp"
        "${WR64_ROOT}/RecompiledFuncsPoint0/funcs_6.c"
        "${WR64_ROOT}/src/wr64_split_screen.cpp")
add_executable(rider_view_identity identity_test.cpp "${EXTRACTED}"
    "${WR64_ROOT}/lib/rt64/src/common/rt64_common.cpp"
    "${WR64_ROOT}/lib/rt64/src/common/rt64_math.cpp"
    "${WR64_ROOT}/lib/rt64/src/hle/rt64_rigid_body.cpp")
target_compile_features(rider_view_identity PRIVATE cxx_std_17)
target_compile_definitions(rider_view_identity PRIVATE HLSL_CPU)
target_include_directories(rider_view_identity PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
    "${WR64_ROOT}/lib/rt64/src" "${WR64_ROOT}/lib/rt64/src/contrib/hlslpp/include")
add_test(NAME rider_view_identity COMMAND rider_view_identity)
