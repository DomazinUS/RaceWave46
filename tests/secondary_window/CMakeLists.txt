cmake_minimum_required(VERSION 3.20)
project(wr64_secondary_window_test LANGUAGES CXX)
enable_testing()
set(CMAKE_CXX_STANDARD 20)
add_executable(secondary_window_test secondary_window_test.cpp)
target_include_directories(secondary_window_test PRIVATE ../../include)
target_compile_definitions(secondary_window_test PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
add_test(NAME secondary_window_lifecycle COMMAND secondary_window_test)
# Compile the same implementation against the real Windows SDK as well.
# Only the executable with substituted OS functions is ever run.
add_library(secondary_window_native_compile OBJECT ../../src/wr64_secondary_window.cpp)
target_include_directories(secondary_window_native_compile PRIVATE ../../include)

# Compile the actual small UI hint function with an in-memory preference and
# SDL hint stub. Extraction keeps its static mode cache and branches intact.
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/RecompFrontend/recompui/src/base/ui_state.cpp" UI_SOURCE)
string(FIND "${UI_SOURCE}" "void apply_background_input_mode() {" MODE_START)
string(FIND "${UI_SOURCE}" "bool recompui::get_cont_active() {" MODE_END)
if(MODE_START LESS 0 OR MODE_END LESS MODE_START)
    message(FATAL_ERROR "Background input function extraction anchors changed")
endif()
math(EXPR MODE_LENGTH "${MODE_END} - ${MODE_START}")
string(SUBSTRING "${UI_SOURCE}" ${MODE_START} ${MODE_LENGTH} NATIVE_MODE_FUNCTION)
configure_file(background_input_test.cpp.in background_input_test.cpp @ONLY)
add_executable(secondary_background_input_test "${CMAKE_CURRENT_BINARY_DIR}/background_input_test.cpp")
target_include_directories(secondary_background_input_test PRIVATE ../../lib/rt64/src)
add_test(NAME secondary_background_input COMMAND secondary_background_input_test)
