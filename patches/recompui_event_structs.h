#ifndef __WR64_RECOMPUI_EVENT_STRUCTS_H__
#define __WR64_RECOMPUI_EVENT_STRUCTS_H__

/*
 * RecompuiEventType / RecompuiDragPhase / RecompuiMenuAction / RecompuiEventData.
 *
 * Other projects keep a hand-maintained COPY of these here, and that copy has
 * drifted: Zelda64Recomp's is missing UI_EVENT_NAVIGATE, UI_EVENT_MOUSE_BUTTON,
 * the whole RecompuiMenuAction enum and the menu_action member - all of which
 * recompui/src/api/ui_api_events.cpp uses today. A stale copy here would be a
 * silent ABI mismatch across the host/patch boundary rather than a compile
 * error, so this forwards to the one recompui itself compiles against:
 *
 *     lib/RecompFrontend/recompui/include/recompui/event_structs.h
 *
 * recompui/include is already on the include path of every target that reaches
 * this header, so it resolves without extra CMake wiring, and it cannot drift.
 *
 * IF THIS PROJECT EVER GAINS RECOMPILED PATCH CODE (a MIPS-side build), that
 * side has no access to recompui's headers and will need a real copy here,
 * kept in sync with the file above by hand. Guard it with #ifdef MIPS.
 */

#include "recompui/event_structs.h"

#endif
