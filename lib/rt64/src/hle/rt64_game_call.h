//
// RT64
//

#pragma once

#include <array>
#include <vector>

#include "render/rt64_shader_common.h"

#if SCRIPT_ENABLED
#include "script/rt64_script.h"
#endif

#include "rt64_draw_call.h"

namespace RT64 {
    struct GameCall {
        DrawCall callDesc;
        ShaderDescription shaderDesc;

        // Optional presentation geometry. Native topology, call identity and
        // reflection lookup retain the original six cloud triangles.
        struct {
            uint32_t vertexStart = UINT32_MAX;
            uint32_t faceIndicesStart = UINT32_MAX;
            uint32_t faceCount = 0;
            std::array<uint32_t, 7> sources{};
            std::vector<std::array<float, 7>> weights;
        } wr64CloudCoverage;

        struct {
            // Only applies to raw triangle geometry from LLE triangle commands.
            uint32_t rawVertexStart;

            // Only applies to indexed geometry from the RSP.
            uint32_t faceIndicesStart;
        } meshDesc;

        struct {
            uint32_t highlightColor;
        } debuggerDesc;

        struct {
            bool enabled;
#       if SCRIPT_ENABLED
            CallMatchCallback *matchCallback; // FIXME: This only supports one match callback active at a time per draw call.
#       endif
        } lerpDesc;
    };
};
