#include "common/rt64_wr64_raster_shadow_math.h"
#include "common/rt64_wr64_raster_shadow_scope.h"
#include "common/rt64_wr64_rt_shadow.h"

#include <array>
#include <cmath>
#include <cstring>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

using namespace RT64;
namespace {
    using Vec3 = std::array<float, 3>;
    using Clip = std::array<double, 4>;
    size_t checks = 0;
    void require(bool value, const char *message) {
        ++checks;
        if (!value) throw std::runtime_error(message);
    }
    void near(double actual, double expected, double tolerance, const char *message) {
        require(std::isfinite(actual) && std::abs(actual - expected) <= tolerance, message);
    }
    Clip project(const Wr64RasterShadowProjection &projection, const Vec3 &point) {
        Clip result{};
        for (size_t r = 0; r < 4; ++r) {
            result[r] = projection.rows[r][3];
            for (size_t c = 0; c < 3; ++c) result[r] += double(projection.rows[r][c]) * point[c];
        }
        return result;
    }
    Vec3 rowBasis(const Wr64RasterShadowProjection &projection, size_t row) {
        Vec3 result{};
        const float scale = row < 2 ? 2048.f : -16384.f;
        for (size_t c = 0; c < 3; ++c) result[c] = projection.rows[row][c] * scale;
        return result;
    }
    double dot(const Vec3 &a, const Vec3 &b) {
        double result = 0;
        for (size_t c = 0; c < 3; ++c) result += double(a[c]) * b[c];
        return result;
    }
    Vec3 add(const Vec3 &a, const Vec3 &b, float scale = 1.f) {
        Vec3 result{};
        for (size_t c = 0; c < 3; ++c) result[c] = a[c] + b[c] * scale;
        return result;
    }
    bool inside(const Clip &p) {
        return p[0] >= -1 && p[0] <= 1 && p[1] >= -1 && p[1] <= 1 && p[2] >= 0 && p[2] <= 1;
    }
    void invalid(const Wr64RasterShadowProjection &projection) {
        require(!projection.valid, "Invalid input enabled raster shadow projection");
        for (const auto &row : projection.rows) for (float value : row) require(value == 0, "Invalid projection leaked partial rows");
    }
}

int main() {
    try {
        // USA transition identities are documented independently in
        // rt_reflection_setting/reflection_scope_test.cpp. Test the admitted
        // scenes and retained-course menu states, not a second scope predicate.
        struct SceneState { uint32_t phase, mode; bool allowed; const char *label; };
        const SceneState courseStates[] = {
            {1, 40, true, "Course race start rejected"},
            {1, 41, true, "Course active race rejected"},
            {1, 42, true, "Course post-goal race rejected"},
            {1, 7, true, "Course attract race rejected"},
            {8, 30, true, "Course introduction rejected"},
            {8, 31, true, "Course introduction fade rejected"},
            {17, 0, false, "Cold boot with retained course enabled shadows"},
            {0, 0, false, "Pre-opening state enabled shadows"},
            {0, 1, false, "Mode before Dolphin opening enabled shadows"},
            {0, 5, false, "Mode after Dolphin title fade enabled shadows"},
            {0, 8, false, "Attract exit enabled shadows"},
            {4, 10, false, "Watercraft selection enabled shadows"},
            {4, 11, false, "Watercraft selection fade enabled shadows"},
            {5, 20, false, "Course selection enabled shadows"},
            {7, 60, false, "Options menu enabled shadows"},
            {10, 62, false, "Change Names preview enabled shadows"},
            {10, 63, false, "Change Names preview fade enabled shadows"},
            {8, 29, false, "Mode before course introduction enabled shadows"},
            {8, 32, false, "Mode after course introduction enabled shadows"},
            {8, 40, false, "Race mode in introduction phase enabled shadows"},
            {0, 40, false, "Race mode outside gameplay phase enabled shadows"},
            {UINT32_MAX, UINT32_MAX, false, "Invalid native phase enabled shadows"}
        };
        const size_t scopeBegin = checks;
        for (uint32_t course = 0; course <= 8; ++course) for (const auto &state : courseStates) {
            require(wr64RasterShadowScope(true, course, 1, state.phase, state.mode) == state.allowed, state.label);
            require(!wr64RasterShadowScope(false, course, 1, state.phase, state.mode), "Deselected shadows enabled a course scene");
            for (uint32_t players : {0u, 2u, 3u, 4u, UINT32_MAX}) {
                require(!wr64RasterShadowScope(true, course, players, state.phase, state.mode),
                    "Expanded raster shadows accepted multiplayer or invalid player count");
                require(!wr64RasterShadowScope(false, course, players, state.phase, state.mode),
                    "Deselected shadows accepted multiplayer or invalid player count");
            }
        }
        // Only Dolphin Park owns the phase-zero opening/title world. Retained
        // race-course IDs or the separate course-9 menu world cannot opt in.
        for (uint32_t course : {0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u, UINT32_MAX})
            for (uint32_t mode : {2u, 3u, 4u}) for (uint32_t players : {0u, 1u, 2u, 3u, 4u, UINT32_MAX}) {
            require(wr64RasterShadowScope(true, course, players, 0, mode) == (course == 0 && players == 1),
                "Opening/title shadows do not match the one-player Dolphin Park world");
            require(!wr64RasterShadowScope(false, course, players, 0, mode), "Deselected shadows enabled opening/title");
        }
        // A course-9 menu scene must remain excluded even if it retains a race
        // or introduction state. Out-of-range identities also remain rejected.
        for (uint32_t course : {9u, 10u, UINT32_MAX}) for (const auto &state : courseStates)
            for (uint32_t players : {0u, 1u, 2u, UINT32_MAX}) {
                require(!wr64RasterShadowScope(true, course, players, state.phase, state.mode),
                    "Menu-preview or invalid course identity enabled raster shadows");
                require(!wr64RasterShadowScope(false, course, players, state.phase, state.mode),
                    "Deselected shadows accepted a menu-preview or invalid course identity");
            }
        const SceneState twoPlayerStates[] = {
            {1, 39, false, "Two-player mode before race was admitted"},
            {1, 40, true, "Native two-player race start rejected"},
            {1, 41, true, "Native two-player race rejected"},
            {1, 42, true, "Native two-player post-goal rejected"},
            {1, 43, true, "Native two-player mode 43 rejected"},
            {1, 44, true, "Native two-player mode 44 rejected"},
            {1, 45, true, "Native two-player mode 45 rejected"},
            {1, 46, false, "Two-player mode after race was admitted"},
            {1, 7, false, "Two-player attract mode was admitted"},
            {8, 30, false, "Two-player introduction was admitted"},
            {0, 2, false, "Two-player opening was admitted"},
            {4, 10, false, "Two-player menu inset was admitted"},
            {5, 20, false, "Two-player course selection was admitted"},
            {17, 0, false, "Two-player boot was admitted"}
        };
        for (uint32_t course : {0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u, UINT32_MAX})
        for (uint32_t players : {0u, 2u, 3u, UINT32_MAX})
        for (bool selected : {false, true}) for (bool enhanced : {false, true})
        for (const auto &state : twoPlayerStates) {
            const bool expected = selected && enhanced && course >= 1 && course <= 8 && players == 2 && state.allowed;
            require(wr64RasterShadowScope(selected, course, players, state.phase, state.mode, enhanced) == expected,
                "Raster shadow two-player scope escaped validated native races");
            require(wr64RasterTwoPlayerScope(selected, course, players, state.phase, state.mode, enhanced) == expected,
                "Raster two-player owner predicate escaped validated native races");
        }
        const size_t scopeChecks = checks - scopeBegin;

        // A shadow-only profile must still publish both native view owners and
        // read the fixed world-light preset through the two-player reader.
        Wr64RTSettings shadowOnly{false, false};
        shadowOnly.rasterShadows = true;
        std::vector<uint8_t> lightRam(0x800000);
        const float sunsetSine = float(std::sqrt(.5));
        std::memcpy(lightRam.data() + 0x00154350 + 0x800, &sunsetSine, sizeof(sunsetSine));
        std::memcpy(lightRam.data() + 0x00154350 + 0x3800, &sunsetSine, sizeof(sunsetSine));
        for (uint32_t course = 1; course <= 8; ++course) {
            const auto shadowOnlyScopes = wr64WaterEffectScopes(shadowOnly, true, course, 2, 1, 40, 0, true);
            require(shadowOnlyScopes.twoPlayer && !shadowOnlyScopes.rayScene && !shadowOnlyScopes.objects &&
                !shadowOnlyScopes.raySky && !shadowOnlyScopes.rasterSky && !shadowOnlyScopes.rasterScene,
                "Shadow-only profile lost two view owners or activated another effect");
            const uint32_t preset = 0x000D9964 + course * 0x110;
            const float direction[] = {-64, 64, 32};
            for (uint32_t component = 0; component < 3; ++component) {
                const uint32_t diffuse = 100 + component * 10, ambient = 10 + component * 10;
                std::memcpy(lightRam.data() + preset + component * 4, &diffuse, sizeof(diffuse));
                std::memcpy(lightRam.data() + preset + 0x0c + component * 4, &ambient, sizeof(ambient));
                std::memcpy(lightRam.data() + preset + 0xac + component * 4, &direction[component], sizeof(float));
            }
            const auto onePlayerLight = wr64RTShadowReadLight(lightRam.data(), lightRam.size(), course, 1);
            const auto twoPlayerLight = wr64RTTwoPlayerShadowReadLight(lightRam.data(), lightRam.size(), course, 2,
                shadowOnlyScopes.twoPlayer);
            require(onePlayerLight.valid && twoPlayerLight.valid, "Shadow-only two-player native light rejected");
            for (size_t component = 0; component < 3; ++component) {
                near(twoPlayerLight.toLight[component], onePlayerLight.toLight[component], 0, "Two-player changed the world-light direction");
                near(twoPlayerLight.diffuse[component], onePlayerLight.diffuse[component], 0, "Two-player changed native diffuse light");
                near(twoPlayerLight.ambient[component], onePlayerLight.ambient[component], 0, "Two-player changed native ambient light");
            }
            const auto unloaded = wr64WaterEffectScopes(shadowOnly, true, course, 2, 1, 40, 0, false);
            require(!wr64RTTwoPlayerShadowReadLight(lightRam.data(), lightRam.size(), course, 2, unloaded.twoPlayer).valid,
                "Unloaded Enhanced assets enabled shadow-only two-player light");
        }
        require(Wr64RasterShadowMapSize == 1024 && Wr64RasterShadowWidth == 4096.f &&
            Wr64RasterShadowDepthSpan == 16384.f && Wr64RasterShadowTexelSize == 4.f,
            "Fixed coverage, depth span or texel grid changed");
        const Vec3 origin{}, vertical{0, 1, 0}, forward{0, 0, 1};
        invalid(wr64BuildRasterShadowProjection(nullptr, vertical.data()));
        invalid(wr64BuildRasterShadowProjection(origin.data(), nullptr));
        invalid(wr64BuildRasterShadowProjection(origin.data(), origin.data()));
        for (float bad : {std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::infinity(),
            -std::numeric_limits<float>::infinity()}) {
            for (size_t c = 0; c < 3; ++c) {
                Vec3 camera{}, light = vertical;
                camera[c] = bad; invalid(wr64BuildRasterShadowProjection(camera.data(), vertical.data()));
                light[c] = bad; invalid(wr64BuildRasterShadowProjection(origin.data(), light.data()));
            }
        }
        const Vec3 lights[] = {{-80, 80, 0}, {0, 1, 1}, {1, 0, 0}, {0, 1, 0},
            {0, -1, 0}, {1e-7f, 1, -1e-7f}, {1, 2, -3}};
        size_t occlusionRays = 0;
        for (const Vec3 &light : lights) {
            const auto map = wr64BuildRasterShadowProjection(origin.data(), light.data());
            require(map.valid, "Finite light including vertical fallback was rejected");
            const auto right = rowBasis(map, 0), up = rowBasis(map, 1), towardLight = rowBasis(map, 2);
            near(dot(right, right), 1, 2e-7, "Right basis is not unit length");
            near(dot(up, up), 1, 2e-7, "Up basis is not unit length");
            near(dot(towardLight, towardLight), 1, 2e-7, "Light basis is not unit length");
            near(dot(right, up), 0, 2e-7, "Light plane basis is not orthogonal");
            near(dot(right, towardLight), 0, 2e-7, "Right is not perpendicular to light");
            near(dot(up, towardLight), 0, 2e-7, "Up is not perpendicular to light");
            require(dot(towardLight, light) > 0, "Depth basis points toward the wrong light hemisphere");
            for (float scale : {1e-30f, 1e30f}) {
                const auto scaled = add(origin, light, scale);
                const auto equivalent = wr64BuildRasterShadowProjection(origin.data(), scaled.data());
                require(equivalent.valid, "Finite nonzero light magnitude failed robust normalization");
                for (size_t r = 0; r < 4; ++r) for (size_t c = 0; c < 4; ++c)
                    near(equivalent.rows[r][c], map.rows[r][c], 1e-8, "Light magnitude changed projection");
            }
            for (int x = -5; x <= 5; ++x) for (int y = -5; y <= 5; ++y) {
                const auto caster = add(add(origin, right, float(x * 60)), up, float(y * 60));
                const auto bed = add(caster, towardLight, -100);
                const auto beforeCaster = add(caster, towardLight, 20);
                const auto c = project(map, caster), b = project(map, bed), before = project(map, beforeCaster);
                near(b[0], c[0], 1e-7, "Caster and seabed leave the same light ray in X");
                near(b[1], c[1], 1e-7, "Caster and seabed leave the same light ray in Y");
                near(before[0], c[0], 1e-7, "Point before caster leaves the light ray in X");
                near(before[1], c[1], 1e-7, "Point before caster leaves the light ray in Y");
                near(b[2] - c[2], 100. / 16384, 1e-8, "Seabed depth separation is wrong");
                // Independent depth comparison with a 2-world-unit bias: a
                // near caster occludes the bed, never the point ahead of it.
                require(b[2] > c[2] + 2. / 16384 && !(before[2] > c[2] + 2. / 16384),
                    "Depth ordering shadows a point in front or exposes the seabed");
                near(c[3], 1, 0, "Projection unexpectedly became perspective");
                ++occlusionRays;
            }
            // Move both geometry and camera by exact shadow-grid steps plus
            // an arbitrary light-depth shift. Their projected relationship is
            // preserved without fitting bounds to changing scene objects.
            for (int step : {-1000, -3, 0, 7, 1000}) {
                const auto shift = add(add(add(origin, right, float(step * 4)), up, -20), towardLight, 17);
                const auto translated = wr64BuildRasterShadowProjection(shift.data(), light.data());
                const Vec3 point{109, -53, 27};
                const auto a = project(map, point), b = project(translated, add(point, shift));
                for (size_t c = 0; c < 4; ++c) near(a[c], b[c], 2e-6, "Grid-aligned camera/geometry translation changed projection");
            }
            const auto drift = add(add(origin, right, .75f), up, -.75f);
            const auto stable = wr64BuildRasterShadowProjection(drift.data(), light.data());
            for (size_t row = 0; row < 2; ++row) for (size_t c = 0; c < 4; ++c)
                require(stable.rows[row][c] == map.rows[row][c], "Sub-texel camera movement shifted light-plane rows");
        }
        // Axis-aligned reference fixes absolute dimensions, orientation and
        // D3D texture V inversion independently of the constructed basis.
        const auto aligned = wr64BuildRasterShadowProjection(origin.data(), forward.data());
        const Vec3 corners[] = {{-2048, -2048, 8192}, {2048, 2048, -8192}};
        for (size_t i = 0; i < 2; ++i) {
            const auto p = project(aligned, corners[i]);
            near(p[0], i ? 1 : -1, 0, "Horizontal map edge mismatch");
            near(p[1], i ? 1 : -1, 0, "Vertical map edge mismatch");
            near(p[2], double(i), 0, "Light near/far boundary mismatch");
            near(p[0] * .5 + .5, double(i), 0, "Texture U mapping mismatch");
            near(.5 - p[1] * .5, 1. - double(i), 0, "Texture V is not inverted from clip Y");
            require(inside(p), "Inclusive map boundary was rejected");
        }
        for (const Vec3 &point : {Vec3{2049, 0, 0}, Vec3{-2049, 0, 0}, Vec3{0, 2049, 0},
            Vec3{0, -2049, 0}, Vec3{0, 0, 8193}, Vec3{0, 0, -8193}})
            require(!inside(project(aligned, point)), "Point outside fixed map bounds was accepted");
        const Vec3 camera{101, 201, 37}, drifted{101.9f, 201.9f, 37}, crossed{102.1f, 202.1f, 37};
        const auto a = wr64BuildRasterShadowProjection(camera.data(), forward.data());
        const auto b = wr64BuildRasterShadowProjection(drifted.data(), forward.data());
        const auto c = wr64BuildRasterShadowProjection(crossed.data(), forward.data());
        require(std::memcmp(a.rows, b.rows, sizeof(a.rows)) == 0, "Camera drift changed a stable projection");
        const auto pa = project(a, origin), pc = project(c, origin);
        near((pc[0] - pa[0]) * .5, -1. / 1024, 0, "Grid crossing did not move exactly one U texel");
        near((pa[1] - pc[1]) * .5, 1. / 1024, 0, "Grid crossing did not move exactly one V texel");
        for (float coordinate : {-6.f, -2.f, 2.f, 6.f}) {
            const Vec3 atTie{coordinate, 0, 0}, translatedTie{coordinate + 4, 0, 0};
            const auto first = wr64BuildRasterShadowProjection(atTie.data(), forward.data());
            const auto second = wr64BuildRasterShadowProjection(translatedTie.data(), forward.data());
            near(second.rows[0][3] - first.rows[0][3], -4. / 2048, 0, "Negative half-texel tie breaks global grid translation");
        }
        std::cout << "PASS: " << checks << " raster-shadow CPU checks (" << scopeChecks << " scope guards); " << occlusionRays
            << " caster/seabed light rays, seven light directions, fixed edges, grid snapping and translation invariance.\n";
        return 0;
    }
    catch (const std::exception &error) {
        std::cerr << "FAIL after " << checks << " checks: " << error.what() << '\n';
        return 1;
    }
}
