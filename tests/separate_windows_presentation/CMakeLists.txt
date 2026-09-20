cmake_minimum_required(VERSION 3.20)
project(Wr64SeparateWindowsPresentationTests LANGUAGES CXX)
enable_testing()
find_package(Python3 REQUIRED COMPONENTS Interpreter)
get_filename_component(WR64_ROOT "../.." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(EXTRACTED "${CMAKE_CURRENT_BINARY_DIR}/presentation_functions.inc")
add_custom_command(OUTPUT "${EXTRACTED}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_LIST_DIR}/extract.py" "${WR64_ROOT}" "${EXTRACTED}"
    DEPENDS extract.py
      "${WR64_ROOT}/lib/rt64/src/hle/rt64_present_queue.cpp"
      "${WR64_ROOT}/lib/rt64/src/render/rt64_vi_renderer.cpp"
      "${WR64_ROOT}/lib/rt64/src/contrib/plume/plume_d3d12.cpp"
    VERBATIM)
add_executable(separate_windows_presentation_test presentation_test.cpp "${EXTRACTED}")
target_compile_features(separate_windows_presentation_test PRIVATE cxx_std_20)
target_compile_definitions(separate_windows_presentation_test PRIVATE HLSL_CPU)
target_include_directories(separate_windows_presentation_test PRIVATE
    "${CMAKE_CURRENT_BINARY_DIR}" "${WR64_ROOT}/include" "${WR64_ROOT}/lib/rt64/src"
    "${WR64_ROOT}/lib/rt64/src/contrib/hlslpp/include")
if(NOT WIN32)
    target_compile_definitions(separate_windows_presentation_test PRIVATE _WIN32)
endif()
add_test(NAME separate_windows_crop_and_lifecycle COMMAND separate_windows_presentation_test)
