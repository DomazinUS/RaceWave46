#pragma once

#include "rt64_wr64_ui_filter_scope.h"
#include "shared/rt64_rdp_params.h"
#include "shared/rt64_render_flags.h"

namespace RT64 {
    // Call only after the draw's TMEM uploads have resolved its texture hash.
    // Keeping this operation together prevents the CPU shader description and
    // the two uploaded parameter arrays from disagreeing about the same draw.
    inline bool wr64ApplyResolvedUiFilter(const Wr64UiFilterDraw &draw,
        uint32_t selectedMode, bool nativeUpscale2D,
        interop::RDPParams &callParams, interop::RenderFlags &shaderFlags,
        interop::RDPParams &uploadedParams, interop::RenderFlags &uploadedFlags)
    {
        const uint32_t mode = selectedMode > 0 && selectedMode <= 2 &&
            wr64UiFilterEligible(draw) ? selectedMode : 0;
        const bool upscale2D = nativeUpscale2D || mode != 0;
        const bool changed = callParams.wr64UiFilter != mode ||
            uploadedParams.wr64UiFilter != mode ||
            shaderFlags.upscale2D != upscale2D ||
            uploadedFlags.upscale2D != upscale2D;
        callParams.wr64UiFilter = mode;
        uploadedParams.wr64UiFilter = mode;
        shaderFlags.upscale2D = upscale2D;
        uploadedFlags.upscale2D = upscale2D;
        return changed;
    }
}
