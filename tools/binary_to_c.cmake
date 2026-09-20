if(NOT DEFINED INPUT OR NOT DEFINED OUTPUT_C OR NOT DEFINED OUTPUT_H OR NOT DEFINED SYMBOL)
    message(FATAL_ERROR "INPUT, OUTPUT_C, OUTPUT_H, and SYMBOL are required")
endif()

file(READ "${INPUT}" BINARY_HEX HEX)
string(LENGTH "${BINARY_HEX}" HEX_LENGTH)
math(EXPR BINARY_LENGTH "${HEX_LENGTH} / 2")

set(BYTES "")
if(HEX_LENGTH GREATER 0)
    math(EXPR LAST_OFFSET "${HEX_LENGTH} - 2")
    foreach(OFFSET RANGE 0 ${LAST_OFFSET} 2)
        string(SUBSTRING "${BINARY_HEX}" ${OFFSET} 2 BYTE)
        string(APPEND BYTES "0x${BYTE},")
        math(EXPR BYTE_INDEX "${OFFSET} / 2 + 1")
        math(EXPR LINE_REMAINDER "${BYTE_INDEX} % 16")
        if(LINE_REMAINDER EQUAL 0)
            string(APPEND BYTES "\n    ")
        else()
            string(APPEND BYTES " ")
        endif()
    endforeach()
endif()

get_filename_component(HEADER_NAME "${OUTPUT_H}" NAME)
file(WRITE "${OUTPUT_H}"
    "#pragma once\n\n#include <stddef.h>\n\n#ifdef __cplusplus\nextern \"C\" {\n#endif\n\nextern const char ${SYMBOL}[${BINARY_LENGTH}];\n\n#ifdef __cplusplus\n}\n#endif\n")
file(WRITE "${OUTPUT_C}"
    "#include \"${HEADER_NAME}\"\n\nconst char ${SYMBOL}[${BINARY_LENGTH}] = {\n    ${BYTES}\n};\n")
