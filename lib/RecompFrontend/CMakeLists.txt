cmake_minimum_required(VERSION 3.20)

project(RecompFrontend)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_SIMULATE_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-everything /W4")
endif()

# Opt out of constexpr mutex constructor on windows to prevent vcredist issues
if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_DISABLE_CONSTEXPR_MUTEX_CONSTRUCTOR")
endif()

option(RECOMP_FRONTEND_N64MODERNRUNTIME_PATH "Set the path where N64ModernRuntime is.")
option(RECOMP_FRONTEND_RT64_PATH "Set the path where RT64 is.")

if (NOT RECOMP_FRONTEND_N64MODERNRUNTIME_PATH)
    message(FATAL_ERROR "N64ModernRuntime's path was not provided." )
endif()

if (NOT RECOMP_FRONTEND_RT64_PATH)
    message(FATAL_ERROR "RT64's path was not provided." )
endif()

add_subdirectory(recompui)
add_subdirectory(recompinput)
