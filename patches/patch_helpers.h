#ifndef __PATCH_HELPERS_H__
#define __PATCH_HELPERS_H__

/*
 * Host-side shim expected by RecompFrontend.
 *
 * recompui/src/api/ui_api_events.cpp includes
 *     ../../../../../patches/ui_funcs.h
 * which resolves to <project root>/patches/ui_funcs.h. That header and its two
 * siblings are supplied by the CONSUMING project, not by RecompFrontend - see
 * Zelda64Recomp/patches and snowboardkids2-recomp/patches for the originals.
 * This file is Zelda64Recomp's verbatim; it is the same in every consumer.
 *
 * MIPS is defined when building recompiled patch code for the N64 side. This
 * project has no patch code today, so only the host branch is ever taken.
 */

#ifdef MIPS
#include "ultra64.h"
#else
#include "recomp.h"
#endif

#ifdef __cplusplus
#   define EXTERNC extern "C"
#else
#   define EXTERNC
#endif

#ifdef MIPS
#    define DECLARE_FUNC(type, name, ...) \
        EXTERNC type name(__VA_ARGS__)
#else // MIPS
#    define DECLARE_FUNC(type, name, ...) \
        EXTERNC void name(uint8_t* rdram, recomp_context* ctx)
#endif

#endif
