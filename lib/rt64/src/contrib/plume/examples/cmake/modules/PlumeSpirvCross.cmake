# PlumeSpirvCross.cmake
# Fetches and builds SPIRV-Cross from source, then builds our spirv_cross_msl tool

include(FetchContent)

# Build the spirv_cross_msl tool, fetching and compiling SPIRV-Cross if not provided
function(plume_fetch_spirv_cross)
    if(TARGET plume_spirv_cross_msl)
        return()
    endif()

    # Use provided paths or fetch and build from source
    if(DEFINED PLUME_SPIRV_CROSS_LIB_DIR AND DEFINED PLUME_SPIRV_CROSS_INCLUDE_DIR)
        # User provided prebuilt libraries
        set(SPIRV_CROSS_LIB_DIR "${PLUME_SPIRV_CROSS_LIB_DIR}")
        set(SPIRV_CROSS_INCLUDE_DIR "${PLUME_SPIRV_CROSS_INCLUDE_DIR}")
        set(SPIRV_CROSS_USE_PREBUILT TRUE)
    else()
        # Fetch and build from source
        set(SPIRV_CROSS_STATIC ON CACHE BOOL "" FORCE)
        set(SPIRV_CROSS_SHARED OFF CACHE BOOL "" FORCE)
        set(SPIRV_CROSS_CLI OFF CACHE BOOL "" FORCE)
        set(SPIRV_CROSS_ENABLE_TESTS OFF CACHE BOOL "" FORCE)
        set(SPIRV_CROSS_ENABLE_GLSL ON CACHE BOOL "" FORCE)
        set(SPIRV_CROSS_ENABLE_MSL ON CACHE BOOL "" FORCE)
        set(SPIRV_CROSS_ENABLE_HLSL OFF CACHE BOOL "" FORCE)
        set(SPIRV_CROSS_ENABLE_CPP OFF CACHE BOOL "" FORCE)
        set(SPIRV_CROSS_ENABLE_REFLECT OFF CACHE BOOL "" FORCE)
        set(SPIRV_CROSS_ENABLE_UTIL OFF CACHE BOOL "" FORCE)
        set(SPIRV_CROSS_ENABLE_C_API OFF CACHE BOOL "" FORCE)
        set(SPIRV_CROSS_SKIP_INSTALL ON CACHE BOOL "" FORCE)

        FetchContent_Declare(
            spirv_cross
            GIT_REPOSITORY https://github.com/KhronosGroup/SPIRV-Cross.git
            GIT_TAG vulkan-sdk-1.4.335.0
            GIT_SHALLOW TRUE
        )
        FetchContent_MakeAvailable(spirv_cross)

        set(SPIRV_CROSS_INCLUDE_DIR "${spirv_cross_SOURCE_DIR}")
        set(SPIRV_CROSS_USE_PREBUILT FALSE)
    endif()

    # Build our custom spirv_cross_msl tool
    set(SPIRV_CROSS_MSL_SOURCE "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../tools/spirv_cross_msl.cpp")

    if(NOT EXISTS "${SPIRV_CROSS_MSL_SOURCE}")
        message(FATAL_ERROR "plume spirv_cross_msl.cpp not found at ${SPIRV_CROSS_MSL_SOURCE}")
    endif()

    add_executable(plume_spirv_cross_msl ${SPIRV_CROSS_MSL_SOURCE})
    target_include_directories(plume_spirv_cross_msl PRIVATE ${SPIRV_CROSS_INCLUDE_DIR})
    set_target_properties(plume_spirv_cross_msl PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

    if(SPIRV_CROSS_USE_PREBUILT)
        # Link against pre-built static libraries
        # Order matters: msl depends on glsl depends on core
        if(WIN32)
            target_link_libraries(plume_spirv_cross_msl PRIVATE
                "${SPIRV_CROSS_LIB_DIR}/spirv-cross-msl.lib"
                "${SPIRV_CROSS_LIB_DIR}/spirv-cross-glsl.lib"
                "${SPIRV_CROSS_LIB_DIR}/spirv-cross-core.lib"
            )
        else()
            target_link_libraries(plume_spirv_cross_msl PRIVATE
                "${SPIRV_CROSS_LIB_DIR}/libspirv-cross-msl.a"
                "${SPIRV_CROSS_LIB_DIR}/libspirv-cross-glsl.a"
                "${SPIRV_CROSS_LIB_DIR}/libspirv-cross-core.a"
            )
        endif()
    else()
        # Link against freshly built targets
        target_link_libraries(plume_spirv_cross_msl PRIVATE
            spirv-cross-msl
            spirv-cross-glsl
            spirv-cross-core
        )
    endif()

    set_target_properties(plume_spirv_cross_msl PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plume_tools"
    )

    if(APPLE)
        set_target_properties(plume_spirv_cross_msl PROPERTIES
            XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "-"
        )
    endif()
endfunction()
