# Pinned upstream source; see UPSTREAM.md. Keep the library independent of UI.
file(GLOB RCHEEVOS_SOURCES CONFIGURE_DEPENDS
    src/*.c src/rcheevos/*.c src/rapi/*.c src/rhash/*.c)
list(FILTER RCHEEVOS_SOURCES EXCLUDE REGEX "/(rc_libretro|rc_client_external)\\.c$")
add_library(wr64_rcheevos STATIC ${RCHEEVOS_SOURCES})
target_include_directories(wr64_rcheevos PUBLIC include PRIVATE src)
target_compile_definitions(wr64_rcheevos PUBLIC RC_DISABLE_LUA RC_CLIENT_SUPPORTS_HASH)
if(MSVC)
    target_compile_definitions(wr64_rcheevos PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
