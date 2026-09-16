#pragma once

#include <cstdint>

namespace RT64 {
    // Championship award scene: func_801ECB98 installs course7, one player,
    // phase21 and mode102. The results/fade handler retains it in mode103.
    // The ordinary Southern Island race uses the same course but another phase.
    inline constexpr bool wr64RTEndingScope(uint32_t course, uint32_t players,
        uint32_t phase, uint32_t mode) {
        return course == 7 && players == 1 && phase == 21 && (mode == 102 || mode == 103);
    }

    // Native VS tracks use the full scenery/water assets selected at their
    // course load. Keep this separate from the established one-player and
    // preview predicates. Dolphin Free Ride requires the authenticated full
    // course-0 load; a course ID alone never enables its rendering.
    inline constexpr bool wr64RTTwoPlayerReflectionScope(bool selected, uint32_t course,
        uint32_t players, uint32_t phase, uint32_t mode, bool loadedEnhanced) {
        return selected && loadedEnhanced && course <= 8 && players == 2 &&
            phase == 1 && mode >= 40 && mode <= 45;
    }

    // USA Rev 1 game state, captured by the workload producer. Phase 1 is the
    // normal course scene. Phase 8 modes 30/31 draw the same world underneath
    // the course-introduction overlays. Dolphin Park also supplies the opening/
    // title world in phase 0: modes 2 (opening), 3 (menu), and 4 (menu fade).
    // Boot and course-map previews remain excluded. The separate rider world
    // is handled below so its inset camera cannot be mistaken for a race view.
    inline constexpr bool wr64RTReflectionScope(bool selected, uint32_t course,
        uint32_t players, uint32_t phase, uint32_t mode) {
        // USA race courses occupy 0..8. Difficulty/reverse variants retain the
        // same course ID; course 9 is the separate rider-selection scene.
        if (!selected || players != 1 || course > 8) {
            return false;
        }

        if (phase == 1 || (phase == 8 && (mode == 30 || mode == 31)) ||
            wr64RTEndingScope(course, players, phase, mode)) {
            return true;
        }

        return course == 0 && phase == 0 && mode >= 2 && mode <= 4;
    }

    // Both menus use course 9 and the same live water/rider renderer. Layout 1
    // (native halfword 801CE60C) selects the single large preview. Actual players
    // must also be 1: 8009328C otherwise emits two complete camera passes, even
    // if the retained menu layout still says 1. Renderer-side viewport/scissor
    // checks additionally isolate this scene from the four miniature craft.
    inline constexpr bool wr64RTMenuReflectionScope(bool selected, uint32_t course,
        uint32_t players, uint32_t phase, uint32_t mode, uint32_t menuLayout) {
        return selected && course == 9 && players == 1 && menuLayout == 1 &&
            ((phase == 4 && (mode == 10 || mode == 11)) ||
             (phase == 10 && (mode == 62 || mode == 63)));
    }

    // Sky reconstruction follows the saved reflection selection in every
    // eligible water scene. Individual native layers still pass the renderer's
    // material and camera validation.
    inline constexpr bool wr64RTSkyReflectionScope(bool reflectionScope, bool skySelected) {
        return reflectionScope && skySelected;
    }
}
