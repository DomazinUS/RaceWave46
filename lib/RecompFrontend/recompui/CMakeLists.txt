cmake_minimum_required(VERSION 3.20)

project(recompui LANGUAGES C CXX)

if (WIN32)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/lib/")
endif()

file(GLOB API_CXX_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/api/*.cpp)
file(GLOB BASE_CXX_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/base/*.cpp)
file(GLOB COMPOSITES_CXX_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/composites/*.cpp)
file(GLOB CONFIG_CXX_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/config/*.cpp)
file(GLOB CORE_CXX_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.cpp)
file(GLOB DATA_CXX_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/data/*.cpp)
file(GLOB ELEMENTS_CXX_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/elements/*.cpp)
file(GLOB RENDERER_CXX_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/*.cpp)
file(GLOB RML_ELEMENTS_CXX_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/rml_elements/*.cpp)
file(GLOB RML_HACKS_CXX_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/rml_hacks/*.cpp)
file(GLOB UTIL_CXX_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/util/*.cpp)

if (APPLE)
    set(UTIL_CXX_SOURCES ${UTIL_CXX_SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/src/util/support_apple.mm)
endif()

set(RML_BACKEND_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/lib/RmlUi/Backends/RmlUi_Platform_SDL.cpp)

# Define the library
add_library(recompui STATIC
    ${API_CXX_SOURCES}
    ${BASE_CXX_SOURCES}
    ${COMPOSITES_CXX_SOURCES}
    ${CONFIG_CXX_SOURCES}
    ${CORE_CXX_SOURCES}
    ${DATA_CXX_SOURCES}
    ${ELEMENTS_CXX_SOURCES}
    ${RENDERER_CXX_SOURCES}
    ${RML_ELEMENTS_CXX_SOURCES}
    ${RML_HACKS_CXX_SOURCES}
    ${UTIL_CXX_SOURCES}
    ${RML_BACKEND_SOURCES}
)

# 

SET(LUNASVG_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/lunasvg)

SET(RMLUI_SVG_PLUGIN ON CACHE BOOL "" FORCE)
SET(RMLUI_TESTS_ENABLED OFF CACHE BOOL "" FORCE)
SET(LUNASVG_BUILD_STATIC ON CACHE BOOL "" FORCE)
set(RT64_STATIC TRUE)
set(RT64_SDL_WINDOW_VULKAN TRUE)
add_compile_definitions(HLSL_CPU)

add_subdirectory(lib/RmlUi)
target_compile_definitions(rmlui_core PRIVATE LUNASVG_BUILD_STATIC)

# TODO: Only necessary because frontend is unable to build standalone without the SDL2 Package.
target_compile_definitions(recompui PRIVATE RMLUI_SDL_VERSION_MAJOR=2)

target_include_directories(recompui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../recompinput/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/GamepadMotionHelpers
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/SlotMap
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/api
    ${CMAKE_CURRENT_SOURCE_DIR}/src/base
    ${CMAKE_CURRENT_SOURCE_DIR}/src/composites
    ${CMAKE_CURRENT_SOURCE_DIR}/src/config
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
    ${CMAKE_CURRENT_SOURCE_DIR}/src/data
    ${CMAKE_CURRENT_SOURCE_DIR}/src/elements
    ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rml_elements
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rml_hacks
    ${CMAKE_CURRENT_SOURCE_DIR}/src/util
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/RmlUi/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/RmlUi/Backends
    ${RECOMP_FRONTEND_RT64_PATH}/include
    ${RECOMP_FRONTEND_RT64_PATH}/src/contrib
    ${RECOMP_FRONTEND_RT64_PATH}/src/contrib/hlslpp/include
    ${RECOMP_FRONTEND_RT64_PATH}/src/contrib/dxc/inc
    ${RECOMP_FRONTEND_RT64_PATH}/src
    ${RECOMP_FRONTEND_RT64_PATH}/src/rhi
    ${RECOMP_FRONTEND_RT64_PATH}/src/render
    ${RECOMP_FRONTEND_RT64_PATH}/src/contrib/nativefiledialog-extended/src/include
    ${RECOMP_FRONTEND_RT64_PATH}/src/contrib/plume
    ${RECOMP_FRONTEND_N64MODERNRUNTIME_PATH}/librecomp/include
    ${RECOMP_FRONTEND_N64MODERNRUNTIME_PATH}/N64Recomp/include
    ${RECOMP_FRONTEND_N64MODERNRUNTIME_PATH}/ultramodern/include
    ${RECOMP_FRONTEND_N64MODERNRUNTIME_PATH}/thirdparty
    ${RECOMP_FRONTEND_N64MODERNRUNTIME_PATH}/thirdparty/concurrentqueue
    ${RECOMP_FRONTEND_N64MODERNRUNTIME_PATH}/thirdparty/miniz
    ${RECOMP_FRONTEND_N64MODERNRUNTIME_PATH}/thirdparty/sse2neon
    ${CMAKE_BINARY_DIR}/shaders
)

build_vertex_shader(recompui "shaders/InterfaceVS.hlsl" "shaders/InterfaceVS.hlsl")
build_pixel_shader(recompui "shaders/InterfacePS.hlsl" "shaders/InterfacePS.hlsl")

target_include_directories(recompui PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/recompui")

if (WIN32)
    target_include_directories(recompui PRIVATE ${sdl2_SOURCE_DIR}/include)
elseif (APPLE OR CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_include_directories(recompui PRIVATE ${SDL2_INCLUDE_DIRS})
endif()

target_compile_options(recompui PRIVATE
    -Wno-unused-parameter
)

if (WIN32)
    add_compile_definitions(NOMINMAX)
endif()

target_link_libraries(recompui PUBLIC
    RmlUi::Core
    RmlUi::Debugger
    lunasvg
    miniz
)
