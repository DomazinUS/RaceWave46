cmake_minimum_required(VERSION 3.20)
project(Wr64FrontendAssetTests LANGUAGES CXX)
enable_testing()
get_filename_component(WR64_SOURCE_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
set(WR64_UI "${WR64_SOURCE_ROOT}/lib/RecompFrontend/recompui")
set(WR64_RML "${WR64_UI}/lib/RmlUi")
add_executable(wr64_frontend_asset_test
    frontend_asset_test.cpp
    "${WR64_RML}/Source/Core/URL.cpp"
    "${WR64_RML}/Source/Core/SystemInterface.cpp"
    "${WR64_RML}/Source/Core/StringUtilities.cpp")
target_compile_features(wr64_frontend_asset_test PRIVATE cxx_std_20)
target_compile_definitions(wr64_frontend_asset_test PRIVATE RMLUI_STATIC_LIB NOMINMAX)
if(MSVC)
    target_compile_options(wr64_frontend_asset_test PRIVATE /utf-8)
endif()
target_include_directories(wr64_frontend_asset_test PRIVATE
    "${WR64_UI}/src" "${WR64_RML}/Include" "${WR64_RML}/Source/Core")
add_test(NAME frontend_asset_paths_and_file_reads
    COMMAND wr64_frontend_asset_test "${CMAKE_CURRENT_BINARY_DIR}")
