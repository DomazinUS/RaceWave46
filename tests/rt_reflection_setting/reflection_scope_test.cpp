#include "common/rt64_wr64_rt_scope.h"
#include "common/rt64_wr64_raster_sky_scope.h"

#include <cstdint>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

namespace {
struct Snapshot {
    const char* label;
    uint32_t course;
    uint32_t players;
    uint32_t phase;
    uint32_t mode;
    bool expected;
};

// Native USA Rev1 transition evidence, rather than a copy of the predicate:
// 80094FE8 initializes boot mode0/phase17; 801EB180 initializes Dolphin Park
// mode2/phase0/players1. Overlay i0's 802C6878 and 802C6A1C enter modes3 and4
// while retaining phase0. 801EBD28/801EBFE4 use preview phases4/5. Championship
// introduction801EB91C enters mode30/phase8/players1; i3_802C6E9C enters31/8.
// Its renderer i3_802C5B40 draws the real course through8009328C before the map.
// Common course start8009345C enters mode40/phase1, including course0 warmup
// and subtype11 Stunt Mode. Addresses are in RecompiledFuncsPoint0.
// The native Course Select loop uses indices0..8 (802C6D88,802C6E28,802C6E64),
// while rider selection explicitly assigns course9 (801EBE00/801EBE08).
// Difficulty801CB338 and reverse800DAB68 are independent of course800D8170;
// the expert/reverse map branches retain the same course index (802C6B04..
// 802C6BD8). Common8009347C/80093488 sets phase1 before these variants branch.
// The display names below follow the independent USA course-name table in
// wr64_ghost_ui.cpp, whose IDs also feed native ghost recording and save keys.
struct NativeCourse {
    uint32_t id;
    const char* name;
};
constexpr NativeCourse nativeCourses[] = {
    {0, "Dolphin Park"}, {1, "Sunny Beach"}, {2, "Sunset Bay"},
    {3, "Marine Fortress"}, {4, "Drake Lake"}, {5, "Port Blue"},
    {6, "Twilight City"}, {7, "Southern Island"}, {8, "Glacier Coast"},
};
constexpr Snapshot nativeTransitions[] = {
    {"cold boot logo",                  0, 1, 17,  0, false},
    {"Dolphin opening camera",          0, 1,  0,  2, true},
    {"Dolphin title awaits Start",      0, 1,  0,  2, true},
    {"main menu over Dolphin water",    0, 1,  0,  3, true},
    {"main menu exit fade",             0, 1,  0,  4, true},
    {"watercraft select",               9, 1,  4, 10, false},
    {"Sunny course select",             1, 1,  5, 20, false},
    {"Sunny race starts",               1, 1,  1, 40, true},
    {"Sunny race runs",                 1, 1,  1, 41, true},
    {"Sunny attract race",              1, 1,  1,  7, true},
    {"Sunny attract exit phase0",       1, 1,  0,  8, false},
    {"return to Dolphin opening",       0, 1,  0,  2, true},
    {"return to main menu",             0, 1,  0,  3, true},
    {"Dolphin course select",           0, 1,  5, 20, false},
    {"Dolphin warmup begins",           0, 1,  1, 40, true},
    {"Dolphin Stunt begins",            0, 1,  1, 40, true},
    {"Dolphin gameplay continues",      0, 1,  1, 41, true},
    {"Sunset race starts",              2, 1,  1, 40, true},
    {"Sunset race runs",                2, 1,  1, 41, true},
    {"Sunset post-goal race scene",     2, 1,  1, 42, true},
    {"Sunset attract exit phase0",      2, 1,  0,  8, false},
    {"Sunset boot guard",               2, 1, 17,  0, false},
    {"Marine Fortress starts",          3, 1,  1, 40, true},
    {"Sunny course introduction",       1, 1,  8, 30, true},
    {"Sunny introduction fade",         1, 1,  8, 31, true},
    {"Dolphin course introduction",     0, 1,  8, 30, true},
    {"Dolphin introduction fade",       0, 1,  8, 31, true},
    {"Sunset course introduction",      2, 1,  8, 30, true},
    {"Sunset introduction fade",        2, 1,  8, 31, true},
    {"Change Names preview",            9, 1, 10, 62, false},
    {"Options after Dolphin",           0, 1,  7, 60, false},
    {"two-player Sunny race",           1, 2,  1, 40, false},
    {"two-player Dolphin race",         0, 2,  1, 40, false},
    {"two-player Sunset race",          2, 2,  1, 40, false},
    {"two-player opening guard",        0, 2,  0,  2, false},
    {"boot again after a race",         0, 1, 17,  0, false},
};

unsigned assertions = 0;

void check(bool actual, bool expected, const std::string& label) {
    ++assertions;
    if (actual != expected) {
        throw std::runtime_error(label + (actual ? " unexpectedly enabled RT" : " unexpectedly disabled RT"));
    }
}

bool evaluate(const Snapshot& snapshot, bool selected = true) {
    return RT64::wr64RTReflectionScope(selected, snapshot.course, snapshot.players,
        snapshot.phase, snapshot.mode);
}

bool evaluateAllScenes(const Snapshot& snapshot, bool selected, uint32_t menuLayout) {
    return evaluate(snapshot, selected) || RT64::wr64RTMenuReflectionScope(selected,
        snapshot.course, snapshot.players, snapshot.phase, snapshot.mode, menuLayout);
}

void replay_native_transitions() {
    for (const Snapshot& snapshot : nativeTransitions) {
        check(evaluate(snapshot), snapshot.expected, snapshot.label);
        check(evaluate(snapshot, false), false, std::string(snapshot.label) + ": Original selected");
        check(evaluate(snapshot), snapshot.expected, std::string(snapshot.label) + ": selected again");
    }

    // Returning through the states in reverse must not retain the previous
    // workload's eligibility, especially race -> preview and opening -> boot.
    for (size_t i = sizeof(nativeTransitions) / sizeof(nativeTransitions[0]); i > 0; --i) {
        const Snapshot& snapshot = nativeTransitions[i - 1];
        check(evaluate(snapshot), snapshot.expected, std::string(snapshot.label) + ": reverse traversal");
    }
}

void replay_each_course() {
    struct Stage {
        const char* label;
        uint32_t phase;
        uint32_t mode;
        bool expected;
    };
    // Shared native course lifecycle. Difficulty and reverse direction do not
    // alter these snapshots, so the scope must not need a variant-specific ID.
    constexpr Stage stages[] = {
        {"course chooser",       5, 20, false},
        {"introduction",         8, 30, true},
        {"introduction fade",    8, 31, true},
        {"gameplay begins",      1, 40, true},
        {"gameplay continues",   1, 41, true},
        {"post-goal scene",      1, 42, true},
        {"course chooser again", 5, 20, false},
        {"Options",              7, 60, false},
        {"boot",                17,  0, false},
    };
    for (const NativeCourse& course : nativeCourses) {
        for (const Stage& stage : stages) {
            const std::string label = std::string(course.name) + ": " + stage.label;
            check(RT64::wr64RTReflectionScope(true, course.id, 1, stage.phase, stage.mode),
                stage.expected, label);
            check(RT64::wr64RTReflectionScope(false, course.id, 1, stage.phase, stage.mode),
                false, label + ": Original");
            check(RT64::wr64RTReflectionScope(true, course.id, 1, stage.phase, stage.mode),
                stage.expected, label + ": enabled again");
            const bool courseScope = RT64::wr64RTReflectionScope(true, course.id, 1, stage.phase, stage.mode);
            check(RT64::wr64RTSkyReflectionScope(courseScope, true), stage.expected,
                label + ": native sky experiment");
            check(RT64::wr64RTSkyReflectionScope(courseScope, false), false,
                label + ": native sky experiment disabled");
            for (uint32_t players : {0u, 2u, 3u, 4u, std::numeric_limits<uint32_t>::max()}) {
                check(RT64::wr64RTReflectionScope(true, course.id, players, stage.phase, stage.mode),
                    false, label + ": non-single-player state");
            }
        }
        for (uint32_t mode : {2u, 3u, 4u}) {
            // Explicitly retain Dolphin's already supported opening family;
            // extending gameplay must not admit it for the other eight courses.
            check(RT64::wr64RTReflectionScope(true, course.id, 1, 0, mode),
                course.id == 0, std::string(course.name) + ": opening restriction");
            const bool scene = RT64::wr64RTReflectionScope(true, course.id, 1, 0, mode);
            check(RT64::wr64RTSkyReflectionScope(scene, true), course.id == 0,
                std::string(course.name) + ": opening sky restriction");
        }
        for (const Stage preview : {Stage{"rider chooser", 4, 10, false},
                Stage{"rider chooser fade", 4, 11, false},
                Stage{"Change Names", 10, 62, false},
                Stage{"Change Names fade", 10, 63, false}}) {
            check(RT64::wr64RTReflectionScope(true, course.id, 1, preview.phase, preview.mode),
                false, std::string(course.name) + ": " + preview.label);
        }
    }
}

void reject_nearby_states() {
    // Native phase0 also occurs in the attract exit mode8. Opening support is
    // specifically modes2..4; adjacent mode numbers must not widen its scope.
    for (uint32_t mode : {0u, 1u, 5u, 6u, 7u, 8u, 10u, 30u, 40u, 60u,
            std::numeric_limits<uint32_t>::max()}) {
        check(RT64::wr64RTReflectionScope(true, 0, 1, 0, mode), false,
            "Dolphin phase0 unrelated mode " + std::to_string(mode));
    }

    for (uint32_t mode : {2u, 3u, 4u}) {
        check(RT64::wr64RTReflectionScope(true, 1, 1, 0, mode), false,
            "Opening extension must not change Sunny phase0");
        check(RT64::wr64RTReflectionScope(true, 2, 1, 0, mode), false,
            "Sunset extension must not inherit Dolphin phase0 opening");
        for (uint32_t phase : {2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u, 10u, 17u,
                std::numeric_limits<uint32_t>::max()}) {
            check(RT64::wr64RTReflectionScope(true, 0, 1, phase, mode), false,
                "Dolphin preview/non-world phase " + std::to_string(phase));
        }
    }

    // Phase8 carries a real course only in the audited introduction family.
    // Neighboring mode numbers must not turn this into general preview support.
    for (const NativeCourse& course : nativeCourses) {
        for (uint32_t mode : {0u, 1u, 2u, 3u, 4u, 7u, 8u, 10u, 20u, 29u,
                32u, 40u, 41u, 60u, std::numeric_limits<uint32_t>::max()}) {
            check(RT64::wr64RTReflectionScope(true, course.id, 1, 8, mode), false,
                std::string(course.name) + ": introduction phase8 unrelated mode " + std::to_string(mode));
        }
    }

    for (const Snapshot& accepted : nativeTransitions) {
        if (!accepted.expected) continue;
        for (uint32_t players : {0u, 2u, 3u, 4u, std::numeric_limits<uint32_t>::max()}) {
            check(RT64::wr64RTReflectionScope(true, accepted.course, players,
                accepted.phase, accepted.mode), false, std::string(accepted.label) + ": invalid player count");
        }
        for (uint32_t course : {9u, 10u, 11u, 16u,
                std::numeric_limits<uint32_t>::max()}) {
            check(RT64::wr64RTReflectionScope(true, course, accepted.players,
                accepted.phase, accepted.mode), false, std::string(accepted.label) + ": unrelated course");
        }
    }
}

void replay_native_menu_scenes() {
    // Native initialization:801EBD48/54/EBE08 enters10/4/course9;
    // i2_802C850C/8518 enters11/4 while leaving the course in place.
    // 801EC3CC/3D8/42C enters62/10/course9 and801EC410 sets players1;
    // i8_802C6F6C/6F78 enters63/10. Both builders call8009328C, which
    // branches on actual players800DAB28 at80093290 and emits two world
    // passes at8009334C/3364 when players!=1. The separate layout halfword
    // 801CE60C controls the inset viewport at8008FCAC/FD18.
    constexpr Snapshot menuTransitions[] = {
        {"Watercraft opens",             9, 1,  4, 10, true},
        {"Watercraft selection/custom",   9, 1,  4, 10, true},
        {"Watercraft exit fade",          9, 1,  4, 11, true},
        {"Course map after Watercraft",   2, 1,  5, 20, false},
        {"Course9 stale map state",       9, 1,  5, 20, false},
        {"Options before names",          0, 1,  7, 60, false},
        {"Change Names selection/edit",    9, 1, 10, 62, true},
        {"Change Names exit fade",        9, 1, 10, 63, true},
        {"Options after names",           9, 1,  7, 60, false},
        {"Names neighboring Options",     9, 1, 10, 61, false},
        {"Names neighboring records",     9, 1, 10, 64, false},
        {"Watercraft unrelated mode",     9, 1,  4, 12, false},
        {"Names mode in Watercraft",      9, 1,  4, 62, false},
        {"Watercraft mode in names",      9, 1, 10, 10, false},
        {"Course9 stale gameplay",        9, 1,  1, 40, false},
        {"Course9 stale opening",         9, 1,  0,  2, false},
        {"Course9 cold boot",             9, 1, 17,  0, false},
    };
    for (const Snapshot& snapshot : menuTransitions) {
        for (bool selected : {false, true}) {
            for (uint32_t layout : {0u, 1u, 2u, std::numeric_limits<uint32_t>::max()}) {
                const bool expected = snapshot.expected && selected && layout == 1;
                const bool menu = RT64::wr64RTMenuReflectionScope(selected, snapshot.course,
                    snapshot.players, snapshot.phase, snapshot.mode, layout);
                const std::string label = std::string(snapshot.label) + ": layout " + std::to_string(layout);
                check(menu, expected, label + ": menu scope");
                check(evaluate(snapshot, selected), false, label + ": not a full course camera");
                check(evaluateAllScenes(snapshot, selected, layout), expected, label + ": combined scope");
                check(RT64::wr64RTSkyReflectionScope(menu, true), expected, label + ": sky enabled");
                check(RT64::wr64RTSkyReflectionScope(menu, false), false, label + ": sky disabled");
            }
        }
        if (!snapshot.expected) continue;
        for (uint32_t players : {0u, 2u, 3u, 4u, std::numeric_limits<uint32_t>::max()}) {
            check(RT64::wr64RTMenuReflectionScope(true, snapshot.course, players,
                snapshot.phase, snapshot.mode, 1), false,
                std::string(snapshot.label) + ": actual multiple/invalid cameras despite layout1");
        }
        for (const NativeCourse& course : nativeCourses) {
            check(RT64::wr64RTMenuReflectionScope(true, course.id, 1,
                snapshot.phase, snapshot.mode, 1), false,
                std::string(snapshot.label) + ": no menu exemption for " + course.name);
        }
        for (uint32_t course : {10u, 11u, std::numeric_limits<uint32_t>::max()}) {
            check(RT64::wr64RTMenuReflectionScope(true, course, 1,
                snapshot.phase, snapshot.mode, 1), false,
                std::string(snapshot.label) + ": unrelated course");
        }
    }
    for (size_t i = sizeof(menuTransitions) / sizeof(menuTransitions[0]); i > 0; --i) {
        const auto& snapshot = menuTransitions[i - 1];
        check(evaluateAllScenes(snapshot, true, 1), snapshot.expected,
            std::string(snapshot.label) + ": reverse traversal retains no previous eligibility");
    }
}
void raster_all_course_scope() {
    for (const auto& snapshot : nativeTransitions) {
        for (bool selected : {false, true}) {
            check(RT64::wr64RasterSkyScope(selected, snapshot.course, snapshot.players,
                snapshot.phase, snapshot.mode), selected && snapshot.expected,
                std::string(snapshot.label) + ": raster sky all courses");
            RT64::Wr64RTSettings settings{false, false};
            settings.rasterReflections = selected;
            const auto scopes = RT64::wr64WaterEffectScopes(settings, true, snapshot.course,
                snapshot.players, snapshot.phase, snapshot.mode, 1, true);
            const bool raceTwo = snapshot.course <= 8 && snapshot.players == 2 &&
                snapshot.phase == 1 && snapshot.mode == 40;
            check(scopes.rasterScene, selected && (snapshot.expected || raceTwo),
                std::string(snapshot.label) + ": raster object transition");
            check(scopes.rayScene || scopes.raySky || scopes.objects || scopes.rasterSky ||
                scopes.menu, false,
                std::string(snapshot.label) + ": raster objects retain independent sky and AS scope");
            check(scopes.twoPlayer, selected && raceTwo,
                std::string(snapshot.label) + ": native race raster view owners");
        }
    }
    struct Stage { uint32_t phase, mode; bool expected; };
    constexpr Stage stages[] = {
        {1, 7, true}, {1, 40, true}, {1, 41, true}, {1, 42, true},
        {1, 43, true}, {1, 44, true}, {1, 45, true},
        {8, 30, true}, {8, 31, true}, {8, 29, false}, {8, 32, false},
        {0, 2, false}, {0, 3, false}, {0, 4, false}, {0, 8, false},
        {4, 10, false}, {4, 11, false}, {10, 62, false}, {10, 63, false},
        {5, 20, false}, {7, 60, false}, {17, 0, false}
    };
    for (uint32_t course : {0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u,
            std::numeric_limits<uint32_t>::max()}) {
        for (uint32_t players : {0u, 1u, 2u, std::numeric_limits<uint32_t>::max()}) {
            for (const auto& stage : stages) {
                const std::string label = "Raster sky course " + std::to_string(course) +
                    " players " + std::to_string(players) + " phase " + std::to_string(stage.phase) +
                    " mode " + std::to_string(stage.mode);
                const bool opening = course == 0 && stage.phase == 0 && stage.mode >= 2 && stage.mode <= 4;
                const bool expected = course <= 8u && players == 1u && (stage.expected || opening);
                check(RT64::wr64RasterSkyScope(true, course, players, stage.phase, stage.mode), expected, label);
                check(RT64::wr64RasterSkyScope(false, course, players, stage.phase, stage.mode), false,
                    label + ": disabled selection");
                for (bool selected : {false, true}) for (bool ready : {false, true})
                for (bool enhanced : {false, true}) {
                    RT64::Wr64RTSettings settings{false, false};
                    settings.rasterReflections = selected;
                    const auto scopes = RT64::wr64WaterEffectScopes(settings, ready,
                        course, players, stage.phase, stage.mode, 1, enhanced);
                    const bool raceTwo = enhanced && course <= 8 && players == 2 &&
                        stage.phase == 1 && stage.mode >= 40 && stage.mode <= 45;
                    check(scopes.rasterScene, (expected || raceTwo) && selected && ready,
                        label + ": raster objects preserve one-player, VS courses and two-player Dolphin Park");
                    check(scopes.rayScene || scopes.raySky || scopes.objects || scopes.rasterSky ||
                        scopes.menu, false,
                        label + ": raster objects alone do not admit preview, sky or AS");
                    check(scopes.twoPlayer, raceTwo && selected && ready,
                        label + ": raster objects retain native race split-screen ownership");
                }
            }
        }
    }
}

void independent_sky_methods() {
    struct Scene { uint32_t course, players, phase, mode, layout; bool enhanced, expected, menu, two; };
    const Scene scenes[] = {
        {0,1,0,2,0,false,true,false,false}, {0,1,0,3,0,false,true,false,false},
        {0,1,0,4,0,false,true,false,false}, {0,1,17,0,0,false,false,false,false},
        {0,1,1,40,0,false,true,false,false}, {1,1,1,40,0,false,true,false,false},
        {2,1,1,40,0,false,true,false,false}, {3,1,1,40,0,false,true,false,false},
        {4,1,1,40,0,false,true,false,false}, {5,1,1,40,0,false,true,false,false},
        {6,1,1,40,0,false,true,false,false}, {7,1,1,40,0,false,true,false,false},
        {8,1,1,40,0,false,true,false,false}, {8,1,8,30,0,false,true,false,false},
        {9,1,4,10,1,false,true,true,false}, {9,1,10,62,1,false,true,true,false},
        {9,1,4,10,0,false,false,false,false}, {9,2,4,10,1,true,false,false,false},
        {1,2,1,40,0,true,true,false,true}, {2,2,1,41,0,true,true,false,true},
        {1,2,1,41,0,true,true,false,true}, {1,2,1,42,0,true,true,false,true},
        {1,2,1,43,0,true,true,false,true}, {1,2,1,44,0,true,true,false,true},
        {1,2,1,45,0,true,true,false,true},
        {3,2,1,42,0,true,true,false,true}, {4,2,1,43,0,true,true,false,true},
        {5,2,1,44,0,true,true,false,true}, {6,2,1,45,0,true,true,false,true},
        {7,2,1,40,0,true,true,false,true}, {8,2,1,40,0,true,true,false,true},
        {1,2,1,40,0,false,false,false,false}, {0,2,1,40,0,true,true,false,true},
        {0,2,1,40,0,false,false,false,false},
        {8,2,0,2,0,true,false,false,false}, {1,1,5,20,0,false,false,false,false},
        {1,2,1,39,0,true,false,false,false}, {1,2,1,46,0,true,false,false,false},
        {1,2,8,30,0,true,false,false,false}, {1,2,0,2,0,true,false,false,false},
        {1,2,5,20,0,true,false,false,false}, {1,2,17,0,0,true,false,false,false}
    };
    for (const auto &scene : scenes) for (bool objects : {false,true})
    for (bool sky : {false,true}) for (bool raster : {false,true}) for (bool ready : {false,true})
    for (bool rasterObjects : {false,true}) for (bool rasterShadows : {false,true}) {
        RT64::Wr64RTSettings settings{objects, true};
        settings.skyReflections = sky; settings.rasterSky = raster;
        settings.rasterReflections = rasterObjects;
        settings.rasterShadows = rasterShadows;
        const auto actual = RT64::wr64WaterEffectScopes(settings, ready, scene.course, scene.players,
            scene.phase, scene.mode, scene.layout, scene.enhanced);
        const bool eligible = ready && scene.expected;
        check(actual.objects, eligible && objects, "independent RT object scope");
        check(actual.rasterSky, eligible && sky && raster, "independent raster sky scope");
        check(actual.raySky, eligible && sky && !raster, "independent ray sky scope");
        check(actual.rayScene, eligible && (objects || (sky && !raster)), "AS needed only for ray effects");
        check(actual.rasterScene, eligible && !scene.menu && rasterObjects,
            "independent raster objects admit established one-player and all Enhanced two-player courses");
        check(actual.menu, ready && (objects || sky) && scene.menu, "live preview ownership");
        check(actual.twoPlayer, ready && scene.two &&
            (objects || sky || rasterObjects || rasterShadows), "split-screen ownership");
        check(RT64::wr64RasterSkyScope(sky && raster, scene.course, scene.players,
            scene.phase, scene.mode, scene.layout, scene.enhanced), scene.expected && sky && raster,
            "raster scene domain excludes menus and unloaded assets");
    }
}
} // namespace

int main() {
    try {
        replay_native_transitions();
        replay_each_course();
        reject_nearby_states();
        replay_native_menu_scenes();
        raster_all_course_scope();
        independent_sky_methods();
        std::cout << "PASS: " << assertions << " native transition, toggle, preview and exclusion assertions\n";
        return 0;
    }
    catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
