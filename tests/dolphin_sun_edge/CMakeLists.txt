cmake_minimum_required(VERSION 3.20)
project(Wr64DolphinSunEdgeTests LANGUAGES CXX)
enable_testing()
find_package(Python3 REQUIRED COMPONENTS Interpreter)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
add_executable(wr64_dolphin_sun_edge_test dolphin_sun_edge_test.cpp)
target_compile_features(wr64_dolphin_sun_edge_test PRIVATE cxx_std_17)
target_include_directories(wr64_dolphin_sun_edge_test PRIVATE "${WR64_ROOT}/lib/rt64/src")
add_test(NAME dolphin_sun_edge_scope_and_continuity COMMAND wr64_dolphin_sun_edge_test)
add_test(NAME dolphin_sun_edge_recorded_outputs COMMAND wr64_dolphin_sun_edge_test
    "${CMAKE_CURRENT_LIST_DIR}/capture.csv")
add_test(NAME dolphin_sun_edge_existing_code_preserved COMMAND "${Python3_EXECUTABLE}"
    "${CMAKE_CURRENT_LIST_DIR}/verify_preservation.py" "${WR64_ROOT}")
set(CONTRACT "${CMAKE_CURRENT_BINARY_DIR}/raster_contract.inc")
add_custom_command(OUTPUT "${CONTRACT}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract_contract.py"
        "${WR64_ROOT}" "${CONTRACT}"
    DEPENDS extract_contract.py
        "${WR64_ROOT}/lib/rt64/src/render/rt64_framebuffer_renderer.cpp"
        "${WR64_ROOT}/lib/rt64/src/shaders/RasterPS.hlsl"
    VERBATIM)
add_executable(wr64_dolphin_sun_raster_contract_test raster_contract_test.cpp "${CONTRACT}")
target_compile_features(wr64_dolphin_sun_raster_contract_test PRIVATE cxx_std_17)
target_include_directories(wr64_dolphin_sun_raster_contract_test PRIVATE
    "${CMAKE_CURRENT_BINARY_DIR}" "${WR64_ROOT}/lib/rt64/src"
    "${WR64_ROOT}/lib/rt64/src/contrib/hlslpp/include")
add_test(NAME dolphin_sun_edge_raster_tag_and_reset COMMAND wr64_dolphin_sun_raster_contract_test)
