# PlumeFileToC.cmake
# Builds the file_to_c tool for embedding binary files as C arrays

# Build the file_to_c tool for the host system
function(plume_build_file_to_c)
    if(TARGET plume_file_to_c)
        return()
    endif()

    # Find the source file relative to this module
    set(FILE_TO_C_SOURCE "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../tools/file_to_c.cpp")

    if(NOT EXISTS "${FILE_TO_C_SOURCE}")
        message(FATAL_ERROR "plume file_to_c.cpp not found at ${FILE_TO_C_SOURCE}")
    endif()

    add_executable(plume_file_to_c ${FILE_TO_C_SOURCE})
    set_target_properties(plume_file_to_c PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plume_tools"
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )

    if(APPLE)
        set_target_properties(plume_file_to_c PROPERTIES
            XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "-"
        )
    endif()
endfunction()

# Convert a binary file to a C header
# Usage: plume_file_to_c_header(INPUT_FILE OUTPUT_C OUTPUT_H VARIABLE_NAME)
function(plume_file_to_c_header INPUT_FILE VARIABLE_NAME OUTPUT_C OUTPUT_H)
    plume_build_file_to_c()

    get_filename_component(OUTPUT_DIR "${OUTPUT_C}" DIRECTORY)
    file(MAKE_DIRECTORY "${OUTPUT_DIR}")

    add_custom_command(
        OUTPUT "${OUTPUT_C}" "${OUTPUT_H}"
        COMMAND plume_file_to_c "${INPUT_FILE}" "${VARIABLE_NAME}" "${OUTPUT_C}" "${OUTPUT_H}"
        DEPENDS "${INPUT_FILE}" plume_file_to_c
        COMMENT "Generating C header for ${VARIABLE_NAME}"
        VERBATIM
    )
endfunction()
