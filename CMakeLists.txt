cmake_minimum_required(VERSION 3.20)

project(WaveRace64Recompiled LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WIN32)
    enable_language(RC)
    add_compile_definitions(NOMINMAX)
endif()

set(WR64_RT64_DEFAULT OFF)
if(MSVC)
    set(WR64_RT64_DEFAULT ON)
endif()
option(WR64_ENABLE_RT64 "Build the native host with RT64 game rendering" ${WR64_RT64_DEFAULT})
option(WR64_ENABLE_DIAGNOSTICS "Compile the developer tracing and recording tools" OFF)
if(WR64_ENABLE_DIAGNOSTICS)
    add_compile_definitions(WR64_ENABLE_DIAGNOSTICS=1)
endif()

if(WR64_ENABLE_RT64)
    if(NOT WIN32)
        message(FATAL_ERROR "The initial Wave Race RT64 host currently supports Windows only.")
    endif()
    set(RT64_STATIC TRUE)
    set(ZSTD_MULTITHREAD_SUPPORT OFF CACHE BOOL "" FORCE)
    add_compile_definitions(HLSL_CPU WR64_ENABLE_RT64)
    include("${CMAKE_SOURCE_DIR}/tools/prepare_dxc.cmake")
    wr64_prepare_dxc(WR64_DXC_BIN)
    add_subdirectory(lib/rt64 rt64)
    target_include_directories(rt64 PRIVATE "${CMAKE_BINARY_DIR}/rt64/src")
endif()

file(READ "${CMAKE_SOURCE_DIR}/lib/N64ModernRuntime/librecomp/src/pi.cpp" RUNTIME_PI_SOURCE)
if(NOT RUNTIME_PI_SOURCE MATCHES "load_overlays\\(physical_addr - recomp::rom_base")
    message(FATAL_ERROR
        "The bundled N64ModernRuntime overlay changes are missing. Restore the dependency from this source release."
    )
endif()

file(READ "${CMAKE_SOURCE_DIR}/lib/N64ModernRuntime/ultramodern/src/events.cpp" RUNTIME_EVENTS_SOURCE)
foreach(wr64_forensic_marker
    "wr64_forensic_wait_if_paused"
    "wr64_forensic_set_rdram"
)
    string(FIND "${RUNTIME_EVENTS_SOURCE}" "${wr64_forensic_marker}" wr64_forensic_pos)
    if(wr64_forensic_pos EQUAL -1)
        message(FATAL_ERROR
            "lib/N64ModernRuntime/ultramodern/src/events.cpp no longer calls "
            "${wr64_forensic_marker}.\n"
            "Required runtime hooks are missing. Restore "
            "lib/N64ModernRuntime from this source release."
        )
    endif()
endforeach()

add_subdirectory(lib/N64ModernRuntime)

if(MSVC)
    foreach(runtime_target ultramodern librecomp)
        get_target_property(runtime_compile_options ${runtime_target} COMPILE_OPTIONS)
        if(runtime_compile_options)
            list(REMOVE_ITEM runtime_compile_options "-Wno-unused-parameter")
            set_property(TARGET ${runtime_target} PROPERTY
                COMPILE_OPTIONS "${runtime_compile_options}")
        endif()
    endforeach()
endif()

option(WR64_ENABLE_FRONTEND "Build RecompFrontend (recompui + recompinput)" OFF)

if(WR64_ENABLE_FRONTEND)
    if(NOT WR64_ENABLE_RT64)
        message(FATAL_ERROR "WR64_ENABLE_FRONTEND requires WR64_ENABLE_RT64.")
    endif()

    if(NOT EXISTS "${CMAKE_SOURCE_DIR}/lib/RecompFrontend/CMakeLists.txt")
        message(FATAL_ERROR
            "The bundled lib/RecompFrontend is missing. Restore it from this source release.\n"
            ""
        )
    endif()
    if(NOT EXISTS "${CMAKE_SOURCE_DIR}/lib/RecompFrontend/recompui/lib/RmlUi/CMakeLists.txt")
        message(FATAL_ERROR
            "The bundled lib/RecompFrontend dependencies are missing. Restore them from this source release.\n"
            ""
        )
    endif()

    file(READ "${CMAKE_SOURCE_DIR}/lib/N64ModernRuntime/librecomp/include/librecomp/game.hpp"
        RUNTIME_GAME_HEADER)
    if(NOT RUNTIME_GAME_HEADER MATCHES "get_config_path")
        message(FATAL_ERROR
            "The librecomp config system is missing from lib/N64ModernRuntime.\n"
            "Restore lib/N64ModernRuntime from this source release."
        )
    endif()

    set(RECOMP_FRONTEND_N64MODERNRUNTIME_PATH "${CMAKE_SOURCE_DIR}/lib/N64ModernRuntime")
    set(RECOMP_FRONTEND_RT64_PATH "${CMAKE_SOURCE_DIR}/lib/rt64")

    set(sdl2_SOURCE_DIR
        "${CMAKE_SOURCE_DIR}/lib/rt64/src/contrib/mupen64plus-win32-deps/SDL2-2.26.3")

    set(WR64_RT64_DIR "${CMAKE_SOURCE_DIR}/lib/rt64")

    file(READ "${WR64_RT64_DIR}/CMakeLists.txt" WR64_RT64_CMAKE)
    foreach(wr64_dxc_marker
        "set (DXC \"\${WR64_DXC_BIN}/dxc.exe\")"
        "set (DXC_DXIL_OPTS \"-Wno-ignored-attributes\")"
        "set (DXC_SPV_OPTS \"-spirv\" \"-fspv-target-env=vulkan1.0\" \"-fvk-use-dx-layout\")"
        "\"-E\" \"PSMain\" \"-T ps_6_3\""
        "\"-E\" \"VSMain\" \"-T vs_6_3\" \"-fvk-invert-y\""
    )
        string(FIND "${WR64_RT64_CMAKE}" "${wr64_dxc_marker}" wr64_dxc_pos)
        if(wr64_dxc_pos EQUAL -1)
            message(FATAL_ERROR
                "lib/rt64/CMakeLists.txt no longer contains:\n"
                "  ${wr64_dxc_marker}\n"
                "The DXC settings mirrored below are stale. Re-read RT64's "
                "\"# For DXC\" block and update them."
            )
        endif()
    endforeach()

    set(DXC             "${WR64_DXC_BIN}/dxc.exe")
    set(DXC_TOOL_DEPENDENCIES "${DXC}" "${WR64_DXC_BIN}/dxcompiler.dll" "${WR64_DXC_BIN}/dxil.dll")
    set(DXC_COMMON_OPTS "-I${WR64_RT64_DIR}/src")
    set(DXC_DXIL_OPTS   "-Wno-ignored-attributes")
    set(DXC_SPV_OPTS    "-spirv" "-fspv-target-env=vulkan1.0" "-fvk-use-dx-layout")
    set(DXC_PS_OPTS     "${DXC_COMMON_OPTS}" "-E" "PSMain" "-T ps_6_3")
    set(DXC_VS_OPTS     "${DXC_COMMON_OPTS}" "-E" "VSMain" "-T vs_6_3" "-fvk-invert-y")

    if(NOT EXISTS "${DXC}")
        message(FATAL_ERROR "dxc.exe not found at ${DXC}")
    endif()

    add_subdirectory(lib/RecompFrontend)

    if(MSVC)
        foreach(frontend_target recompui recompinput)
            if(TARGET ${frontend_target})
                get_target_property(frontend_compile_options ${frontend_target} COMPILE_OPTIONS)
                if(frontend_compile_options)
                    list(REMOVE_ITEM frontend_compile_options "-Wno-unused-parameter")
                    set_property(TARGET ${frontend_target} PROPERTY
                        COMPILE_OPTIONS "${frontend_compile_options}")
                endif()
            endif()
        endforeach()
    endif()
endif()

file(GLOB RECOMPILED_C_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/RecompiledFuncsPoint0/funcs_*.c"
)

if(NOT RECOMPILED_C_SOURCES)
    message(FATAL_ERROR
        "RecompiledFuncsPoint0 is missing. Run N64Recomp with config/us.rev1.toml before configuring CMake."
    )
endif()

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/rsp/aspMain.cpp")
    message(FATAL_ERROR
        "rsp/aspMain.cpp is missing. Run RSPRecomp with config/aspMain.us.rev1.toml before configuring CMake."
    )
endif()

set(PATCHED_RSP_SOURCE "${CMAKE_BINARY_DIR}/generated/aspMain.cpp")
add_custom_command(
    OUTPUT "${PATCHED_RSP_SOURCE}"
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_BINARY_DIR}/generated"
    COMMAND "${CMAKE_COMMAND}"
        "-DINPUT=${CMAKE_SOURCE_DIR}/rsp/aspMain.cpp"
        "-DOUTPUT=${PATCHED_RSP_SOURCE}"
        -P "${CMAKE_SOURCE_DIR}/tools/patch_rsp_dispatch.cmake"
    DEPENDS
        "${CMAKE_SOURCE_DIR}/rsp/aspMain.cpp"
        "${CMAKE_SOURCE_DIR}/tools/patch_rsp_dispatch.cmake"
    VERBATIM
)

add_library(WaveRace64RecompiledCode STATIC
    ${RECOMPILED_C_SOURCES}
    RecompiledFuncsPoint0/lookup.cpp
)

target_compile_options(WaveRace64RecompiledCode PRIVATE
    $<$<COMPILE_LANG_AND_ID:C,GNU,Clang>:-fno-strict-aliasing>
    $<$<COMPILE_LANG_AND_ID:C,GNU,Clang>:-Wno-unused-variable>
    $<$<COMPILE_LANG_AND_ID:C,GNU,Clang>:-Wno-implicit-function-declaration>
)

target_include_directories(WaveRace64RecompiledCode PRIVATE
    RecompiledFuncsPoint0
    lib/N64ModernRuntime/N64Recomp/include
    lib/N64ModernRuntime/ultramodern/include
    lib/N64ModernRuntime/librecomp/include
)

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/data/waverace64-widescreen.ips")
    message(FATAL_ERROR "data/waverace64-widescreen.ips is missing.")
endif()

set(ROM_PATCH_SOURCE "${CMAKE_BINARY_DIR}/generated/wr64_rom_patch_data.c")
set(ROM_PATCH_HEADER "${CMAKE_BINARY_DIR}/generated/wr64_rom_patch_data.h")
add_custom_command(
    OUTPUT "${ROM_PATCH_SOURCE}" "${ROM_PATCH_HEADER}"
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_BINARY_DIR}/generated"
    COMMAND "${CMAKE_COMMAND}"
        "-DINPUT=${CMAKE_SOURCE_DIR}/data/waverace64-widescreen.ips"
        "-DOUTPUT_C=${ROM_PATCH_SOURCE}"
        "-DOUTPUT_H=${ROM_PATCH_HEADER}"
        "-DSYMBOL=wr64_rom_patch_ips"
        -P "${CMAKE_SOURCE_DIR}/tools/binary_to_c.cmake"
    DEPENDS
        "${CMAKE_SOURCE_DIR}/data/waverace64-widescreen.ips"
        "${CMAKE_SOURCE_DIR}/tools/binary_to_c.cmake"
    VERBATIM
)
set_source_files_properties("${ROM_PATCH_SOURCE}" PROPERTIES GENERATED TRUE)

add_subdirectory(lib/rcheevos)

add_executable(WaveRace64Recompiled
    src/main.cpp
    src/wr64_achievements.cpp
    src/wr64_achievements_platform.cpp
    src/wr64_achievement_badges.cpp
    src/wr64_achievements_hooks.cpp
    src/wr64_rom_patch.cpp
    "${ROM_PATCH_SOURCE}"
    src/headless_io.cpp
    src/headless_renderer.cpp
    src/recomp_shims.cpp
    src/register_overlays.cpp
    src/wr64_forensic.cpp
    src/wr64_render_provenance.cpp
    src/wr64_frontend.cpp
    src/wr64_manual_frontend.cpp
    src/wr64_manual_settings_theme.cpp
    src/wr64_input.cpp
    src/wr64_editions.cpp
    src/wr64_game_rumble.cpp
    src/wr64_controller_smoke.cpp
    src/controller_pak.cpp
    src/wr64_ghost.cpp
    src/wr64_ghost_native.cpp
    src/wr64_ultrawide.cpp
    src/wr64_menu_layout.cpp
    src/wr64_watercraft_preview.cpp
    src/wr64_course_preview.cpp
    src/wr64_championship_preview.cpp
    src/wr64_split_screen.cpp
    src/wr64_camera_fov.cpp
    src/wr64_draw_distance.cpp
    src/wr64_object_distance.cpp
    src/wr64_seabed_distance.cpp
    src/wr64_free_ride_menu.cpp
    src/wr64_free_ride.cpp
    src/wr64_sunny_detail.cpp
    src/wr64_sunny_sky.cpp
    src/wr64_two_player_celestial.cpp
    src/wr64_two_player_celestial_draw.cpp
    src/wr64_twilight_buoy_lights.cpp
    src/wr64_sunny_water.cpp
    src/wr64_wave_distance.cpp
    src/wr64_sunny_actors.cpp
    src/wr64_sunny_buoys.cpp
    src/wr64_sunny_animals.cpp
    src/wr64_sunny_animals_load.cpp
    src/wr64_ghost_ui.cpp
    src/win32_window.cpp
    src/wr64_secondary_window.cpp
    "${PATCHED_RSP_SOURCE}"
)

set_source_files_properties("${PATCHED_RSP_SOURCE}" PROPERTIES
    GENERATED TRUE
    COMPILE_OPTIONS "$<$<CXX_COMPILER_ID:GNU,Clang>:-msse4.1>"
)

if(WIN32)
    target_sources(WaveRace64Recompiled PRIVATE resources/waverace.rc)
    set_source_files_properties(resources/waverace.rc PROPERTIES
        INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/resources"
        OBJECT_DEPENDS "${CMAKE_SOURCE_DIR}/resources/WaveRace.ico"
    )
endif()

target_include_directories(WaveRace64Recompiled PRIVATE
    include
    "${CMAKE_BINARY_DIR}/generated"
    RecompiledFuncsPoint0
    lib/N64ModernRuntime/N64Recomp/include
    lib/N64ModernRuntime/ultramodern/include
    lib/N64ModernRuntime/librecomp/include
)

target_link_libraries(WaveRace64Recompiled PRIVATE
    wr64_rcheevos
    WaveRace64RecompiledCode
    librecomp
    ultramodern
)

if(WR64_ENABLE_RT64)
    target_sources(WaveRace64Recompiled PRIVATE
        src/rt64_renderer.cpp
        src/win32_io.cpp
        src/wr64_composer_window.cpp
    )
    target_include_directories(WaveRace64Recompiled PRIVATE
        lib/rt64/src
        lib/rt64/src/contrib
        lib/rt64/src/contrib/plume
        lib/rt64/src/contrib/hlslpp/include
        lib/rt64/src/contrib/imgui
        lib/rt64/src/contrib/mupen64plus-core/src/api
        lib/rt64/src/contrib/mupen64plus-win32-deps/SDL2-2.26.3/include
        lib/rt64/src/contrib/dxc/inc
    )
    target_include_directories(rt64 PRIVATE
        "${CMAKE_SOURCE_DIR}/include"
    )
    target_link_directories(WaveRace64Recompiled PRIVATE
        lib/rt64/src/contrib/mupen64plus-win32-deps/SDL2-2.26.3/lib/x64
    )
    target_link_libraries(WaveRace64Recompiled PRIVATE rt64 Xinput9_1_0)
    set_property(TARGET WaveRace64Recompiled APPEND PROPERTY LINK_DEPENDS
        "${WR64_DXC_BIN}/dxcompiler.dll" "${WR64_DXC_BIN}/dxil.dll")
    add_custom_command(TARGET WaveRace64Recompiled POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "${CMAKE_SOURCE_DIR}/lib/rt64/src/contrib/mupen64plus-win32-deps/SDL2-2.26.3/lib/x64/SDL2.dll"
            "${WR64_DXC_BIN}/dxcompiler.dll"
            "${WR64_DXC_BIN}/dxil.dll"
            "$<TARGET_FILE_DIR:WaveRace64Recompiled>"
        VERBATIM
    )
endif()

if(WR64_ENABLE_FRONTEND)
    target_compile_definitions(WaveRace64Recompiled PRIVATE WR64_ENABLE_FRONTEND)
    target_link_libraries(WaveRace64Recompiled PRIVATE recompui recompinput)
    target_sources(WaveRace64Recompiled PRIVATE src/wr64_texture_packs.cpp src/wr64_achievements_ui.cpp)

    set(WR64_RMLUI_ASSETS
        "${CMAKE_SOURCE_DIR}/assets")
    foreach(wr64_font "LatoLatin-Regular.ttf" "LatoLatin-Bold.ttf" "NotoEmoji-Regular.ttf")
        if(NOT EXISTS "${WR64_RMLUI_ASSETS}/${wr64_font}")
            message(FATAL_ERROR
                "${wr64_font} is not in RmlUi's samples at ${WR64_RMLUI_ASSETS}.\n"
                "recompui's UIState constructor throws without a primary font."
            )
        endif()
    endforeach()
    if(NOT EXISTS "${CMAKE_SOURCE_DIR}/assets/recomp.rcss")
        message(FATAL_ERROR "assets/recomp.rcss is missing.")
    endif()

    set(WR64_UI_ICONS
        Caret Cont Keyboard PlusKeyboard Question Quit
        RecordBorder RecordSpinner Reset Trash X)
    set(WR64_UI_ICON_FILES "")
    foreach(wr64_icon IN LISTS WR64_UI_ICONS)
        set(wr64_icon_path "${CMAKE_SOURCE_DIR}/assets/icons/${wr64_icon}.svg")
        if(NOT EXISTS "${wr64_icon_path}")
            message(FATAL_ERROR
                "assets/icons/${wr64_icon}.svg is missing. recompui loads it by "
                "name and draws nothing when it is absent."
            )
        endif()
        list(APPEND WR64_UI_ICON_FILES "${wr64_icon_path}")
    endforeach()

    foreach(wr64_prompt_file promptfont.ttf LICENSE.txt README.md)
        if(NOT EXISTS "${CMAKE_SOURCE_DIR}/assets/promptfont/${wr64_prompt_file}")
            message(FATAL_ERROR "assets/promptfont/${wr64_prompt_file} is missing.")
        endif()
    endforeach()

    foreach(wr64_manual_image RaceWave46_logo_noBackground.png WaveRace_Recompiled.png WaveRace64_30th_Anniversary.png)
        if(NOT EXISTS "${CMAKE_SOURCE_DIR}/assets/manual/${wr64_manual_image}")
            message(FATAL_ERROR "assets/manual/${wr64_manual_image} is missing.")
        endif()
    endforeach()

    add_custom_target(wr64_frontend_assets ALL
        COMMAND "${CMAKE_COMMAND}" -E make_directory
            "$<TARGET_FILE_DIR:WaveRace64Recompiled>/assets"
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "${WR64_RMLUI_ASSETS}/LatoLatin-Regular.ttf"
            "${WR64_RMLUI_ASSETS}/LatoLatin-Bold.ttf"
            "${WR64_RMLUI_ASSETS}/NotoEmoji-Regular.ttf"
            "${CMAKE_SOURCE_DIR}/assets/recomp.rcss"
            "${CMAKE_SOURCE_DIR}/assets/ASSET-SOURCES.md"
            "${CMAKE_SOURCE_DIR}/assets/LICENSE-fonts.txt"
            "$<TARGET_FILE_DIR:WaveRace64Recompiled>/assets"
        COMMAND "${CMAKE_COMMAND}" -E make_directory
            "$<TARGET_FILE_DIR:WaveRace64Recompiled>/assets/icons"
            "$<TARGET_FILE_DIR:WaveRace64Recompiled>/assets/promptfont"
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            ${WR64_UI_ICON_FILES}
            "$<TARGET_FILE_DIR:WaveRace64Recompiled>/assets/icons"
        COMMAND "${CMAKE_COMMAND}" -E copy_directory
            "${CMAKE_SOURCE_DIR}/assets/icons/VizMap"
            "$<TARGET_FILE_DIR:WaveRace64Recompiled>/assets/icons/VizMap"
        COMMAND "${CMAKE_COMMAND}" -E copy_directory
            "${CMAKE_SOURCE_DIR}/assets/manual"
            "$<TARGET_FILE_DIR:WaveRace64Recompiled>/assets/manual"
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "${CMAKE_SOURCE_DIR}/assets/promptfont/promptfont.ttf"
            "${CMAKE_SOURCE_DIR}/assets/promptfont/LICENSE.txt"
            "${CMAKE_SOURCE_DIR}/assets/promptfont/README.md"
            "$<TARGET_FILE_DIR:WaveRace64Recompiled>/assets/promptfont"
        VERBATIM
    )
    add_dependencies(WaveRace64Recompiled wr64_frontend_assets)
endif()

if(WIN32 OR CYGWIN)
    target_link_libraries(WaveRace64Recompiled PRIVATE user32 gdi32 shell32 winhttp crypt32)
endif()

set_target_properties(WaveRace64Recompiled PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

if(MSVC)
    target_link_options(WaveRace64Recompiled PRIVATE
        "/MAP:${CMAKE_BINARY_DIR}/WaveRace64Recompiled.map")
endif()
