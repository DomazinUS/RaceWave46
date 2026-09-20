if(NOT DEFINED INPUT)
    message(FATAL_ERROR "INPUT is required")
endif()

file(READ "${INPUT}" CONTENT)
string(REGEX MATCHALL
    "static RelocEntry [A-Za-z0-9_]+\\[\\] = \\{[\r\n\t ]*\\};"
    EMPTY_RELOC_TABLES
    "${CONTENT}")

foreach(EMPTY_TABLE IN LISTS EMPTY_RELOC_TABLES)
    string(REGEX MATCH "static RelocEntry ([A-Za-z0-9_]+)" _ "${EMPTY_TABLE}")
    set(TABLE_NAME "${CMAKE_MATCH_1}")
    string(REPLACE
        "${EMPTY_TABLE}"
        "static RelocEntry ${TABLE_NAME}[1] = {};"
        CONTENT
        "${CONTENT}")
    string(REPLACE
        ".num_relocs = ARRLEN(${TABLE_NAME})"
        ".num_relocs = 0"
        CONTENT
        "${CONTENT}")
endforeach()

file(WRITE "${INPUT}" "${CONTENT}")

