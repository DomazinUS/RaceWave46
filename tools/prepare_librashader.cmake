# The librashader runtime that is copied beside the game. Its C API header is
# vendored in lib/librashader/include, and the game loads the library at run
# time, so a build without it still works with the librashader option disabled.
set(WR64_LIBRASHADER_VERSION 0.12.0)
option(WR64_BUNDLE_LIBRASHADER "Copy the librashader runtime beside the game executable" ON)
set(WR64_LIBRASHADER_LIBRARY "" CACHE FILEPATH
    "Prebuilt librashader ${WR64_LIBRASHADER_VERSION} (C ABI 2) library to bundle instead of the pinned download")

# x86_64 Windows release asset and the librashader.dll inside it.
set(WR64_LIBRASHADER_WINDOWS_ARCHIVE librashader-x86_64-windows-v0.12.0-optimized.zip)
set(WR64_LIBRASHADER_WINDOWS_ARCHIVE_SHA256 521fe0f364bfa705883f9e99fb1733a3a24f0f403bcc5591b6b78f6cff289183)
set(WR64_LIBRASHADER_WINDOWS_DLL_SHA256 1890f647c7fbe52d4cc591526db24367caca284996855c4565c6003c7e46f8cc)

# Sets output_variable to the library to bundle, or to an empty string.
function(wr64_prepare_librashader output_variable)
    set(${output_variable} "" PARENT_SCOPE)
    if(NOT WR64_BUNDLE_LIBRASHADER)
        return()
    endif()

    if(WR64_LIBRASHADER_LIBRARY)
        if(NOT EXISTS "${WR64_LIBRASHADER_LIBRARY}")
            message(FATAL_ERROR "WR64_LIBRASHADER_LIBRARY does not exist: ${WR64_LIBRASHADER_LIBRARY}")
        endif()
        set(${output_variable} "${WR64_LIBRASHADER_LIBRARY}" PARENT_SCOPE)
        return()
    endif()

    if(NOT WIN32)
        message(STATUS "librashader: not bundled. Build it with tools/build_librashader.sh and pass "
            "-DWR64_LIBRASHADER_LIBRARY, or install a distribution librashader.so.2.")
        return()
    endif()

    if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
        message(STATUS "librashader: no pinned build for this Windows architecture; not bundled.")
        return()
    endif()

    set(directory "${CMAKE_BINARY_DIR}/_deps/wr64-librashader-${WR64_LIBRASHADER_VERSION}")
    set(library "${directory}/librashader.dll")
    if(EXISTS "${library}")
        file(SHA256 "${library}" library_hash)
        if(library_hash STREQUAL WR64_LIBRASHADER_WINDOWS_DLL_SHA256)
            set(${output_variable} "${library}" PARENT_SCOPE)
            return()
        endif()
    endif()

    set(download "${CMAKE_BINARY_DIR}/_deps/${WR64_LIBRASHADER_WINDOWS_ARCHIVE}")
    if(EXISTS "${download}")
        file(SHA256 "${download}" download_hash)
    endif()
    if(NOT download_hash STREQUAL WR64_LIBRASHADER_WINDOWS_ARCHIVE_SHA256)
        file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/_deps")
        message(STATUS "Acquiring pinned librashader ${WR64_LIBRASHADER_VERSION}")
        file(DOWNLOAD
            "https://github.com/SnowflakePowered/librashader/releases/download/librashader-v${WR64_LIBRASHADER_VERSION}/${WR64_LIBRASHADER_WINDOWS_ARCHIVE}"
            "${download}" EXPECTED_HASH "SHA256=${WR64_LIBRASHADER_WINDOWS_ARCHIVE_SHA256}" TLS_VERIFY ON
            TIMEOUT 300 INACTIVITY_TIMEOUT 30 STATUS download_status)
        list(GET download_status 0 download_code)
        if(NOT download_code EQUAL 0)
            message(FATAL_ERROR "librashader download failed: ${download_status}. Set WR64_LIBRASHADER_LIBRARY "
                "for an offline build, or WR64_BUNDLE_LIBRASHADER=OFF to build without it.")
        endif()
    endif()

    file(REMOVE_RECURSE "${directory}")
    file(ARCHIVE_EXTRACT INPUT "${download}" DESTINATION "${directory}" PATTERNS librashader.dll)
    file(SHA256 "${library}" library_hash)
    if(NOT library_hash STREQUAL WR64_LIBRASHADER_WINDOWS_DLL_SHA256)
        message(FATAL_ERROR "The extracted librashader.dll does not match the pinned release.")
    endif()
    set(${output_variable} "${library}" PARENT_SCOPE)
endfunction()
