#ifndef __WR64_UI_FUNCS_H__
#define __WR64_UI_FUNCS_H__

/*
 * The host shim RecompFrontend hard-codes a path to. See patch_helpers.h for
 * why these three files live here rather than in the library.
 *
 * recomp_run_ui_callbacks is DEFINED in
 * recompui/src/api/ui_api_events.cpp; this only declares it, and the
 * DECLARE_FUNC expansion must match that definition exactly:
 *
 *     extern "C" void recomp_run_ui_callbacks(uint8_t* rdram, recomp_context* ctx)
 *
 * NOTE for later: in other projects this is CALLED once per frame from
 * recompiled patch code, which is what drains recompui's queued UI callbacks.
 * Wave Race 64 has no patch code, so nothing calls it yet - the function is
 * defined and never invoked. That is fine while no mod registers a UI
 * callback; revisit it when mod support goes in.
 */

#include "patch_helpers.h"
#include "recompui_event_structs.h"

DECLARE_FUNC(void, recomp_run_ui_callbacks);

#endif
