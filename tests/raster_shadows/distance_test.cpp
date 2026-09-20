#include "common/rt64_wr64_raster_shadow_math.h"
#include "common/rt64_wr64_raster_shadow_scope.h"
#include "common/rt64_wr64_rt_actor_shadow.h"
#include "common/rt64_wr64_rt_settings.h"
#include "common/rt64_wr64_rt_startup.h"
#include "fixtures/original_projection.h"

#include <array>
#include <cmath>
#include <cstring>
#include <iostream>
#include <limits>
#include <stdexcept>

using namespace RT64;
namespace {
using Vec3 = std::array<float, 3>;
size_t checks = 0;
void require(bool value, const char *message) {
    ++checks;
    if (!value) throw std::runtime_error(message);
}
void near(double actual, double expected, double tolerance, const char *message) {
    require(std::isfinite(actual) && std::abs(actual - expected) <= tolerance, message);
}
void same(const Wr64RasterShadowProjection &a, const Wr64RasterShadowProjection &b, const char *message) {
    require(a.valid == b.valid && std::memcmp(a.rows, b.rows, sizeof(a.rows)) == 0, message);
}
std::array<double, 4> project(const Wr64RasterShadowProjection &map, const Vec3 &point) {
    std::array<double, 4> clip{};
    for (size_t row = 0; row < 4; ++row) {
        clip[row] = map.rows[row][3];
        for (size_t col = 0; col < 3; ++col) clip[row] += double(map.rows[row][col]) * point[col];
    }
    return clip;
}
struct ActorFixture {
    bool prepared = true;
    std::array<Wr64RTActorShadowBounds, 4> actorBounds{};
    uint32_t racerShadowCasters = 15, rasterShadowRacers = 0;
    struct { float lightRows[4][4]{}; } rasterShadowParams;
};
#include "distance_production.inc"

void original_parity() {
    // Compare against the accepted pre-feature source, not a reformulation of
    // the new helper. Include negative/global snap ties and large world shifts.
    const Vec3 lights[] = {{-80, 80, 0}, {0, 1, 1}, {1, 0, 0}, {0, 1, 0},
        {0, -1, 0}, {1e-7f, 1, -1e-7f}, {1, 2, -3}, {1e-30f, 2e-30f, -3e-30f},
        {1e30f, 2e30f, -3e30f}, {0, 0, 0}};
    for (const Vec3 &light : lights) for (int i = -32; i <= 32; ++i) {
        const Vec3 camera{float(i * 1024 + 2), float(i * 34 - 6), float(i * 37) + .25f};
        const auto old = OriginalRT64::wr64BuildRasterShadowProjection(camera.data(), light.data());
        const auto now = wr64BuildRasterShadowProjection(camera.data(), light.data(), 0);
        require(old.valid == now.valid && std::memcmp(old.rows, now.rows, sizeof(old.rows)) == 0,
            "Original projection differs from the accepted pre-feature helper");
        same(now, wr64BuildRasterShadowProjection(camera.data(), light.data()), "Default argument changed Original");
        for (uint32_t bad : {4u, 5u, 99u, UINT32_MAX}) {
            require(wr64RasterShadowDistanceMode(bad) == 0 && wr64RasterShadowDistanceScale(bad) == 1,
                "Unknown distance mode escaped Original fallback");
            same(now, wr64BuildRasterShadowProjection(camera.data(), light.data(), bad), "Unknown mode changed projection");
        }
    }
}

void range_and_grid() {
    constexpr float factors[] = {1, 1.5f, 2, 3};
    const Vec3 origin{}, light{0, 0, 1};
    const auto original = wr64BuildRasterShadowProjection(origin.data(), light.data());
    require(Wr64RasterShadowMapSize == 1024 && Wr64RasterShadowDepthSpan == 16384,
        "Distance setting changed map allocation or light depth budget");
    for (uint32_t mode = 0; mode < 4; ++mode) {
        require(wr64RasterShadowDistanceMode(mode) == mode && wr64RasterShadowDistanceScale(mode) == factors[mode],
            "Distance multiplier mapping is wrong");
        const float halfWidth = 2048 * factors[mode], texel = 4 * factors[mode];
        const auto map = wr64BuildRasterShadowProjection(origin.data(), light.data(), mode);
        require(map.valid, "Valid scaled map was rejected");
        require(std::memcmp(map.rows[2], original.rows[2], sizeof(map.rows[2]) * 2) == 0,
            "XY expansion changed normalized depth or W");
        for (float sign : {-1.f, 1.f}) {
            const auto edge = project(map, Vec3{sign * halfWidth, sign * halfWidth, sign * 8192});
            near(edge[0], sign, 4e-8, "Expanded horizontal map edge is wrong");
            near(edge[1], sign, 4e-8, "Expanded vertical map edge is wrong");
            near(edge[2], sign < 0 ? 1 : 0, 0, "Distance changed near/far depth");
            require(std::abs(project(map, Vec3{sign * (halfWidth + 1), 0, 0})[0]) > 1,
                "Point outside expanded coverage was accepted");
        }
        if (mode) {
            const Vec3 caster{2049, 0, 100}, receiver{2049, 0, 0};
            require(project(original, caster)[0] > 1 && project(map, caster)[0] < 1,
                "New range did not admit a caster beyond Original");
            const auto a = project(map, caster), b = project(map, receiver);
            near(a[0], b[0], 0, "Expanded caster and receiver leave the same light ray");
            require(b[2] > a[2] + 2. / 16384, "Range expansion broke shadow depth ordering");
        }
        for (int step : {-1000, -3, 0, 7, 1000}) {
            const Vec3 camera{float(step) * texel, -7 * texel, 37};
            const Vec3 drift{camera[0] + texel * .24f, camera[1] - texel * .24f, camera[2]};
            const Vec3 crossed{camera[0] + texel * .51f, camera[1], camera[2]};
            const auto a = wr64BuildRasterShadowProjection(camera.data(), light.data(), mode);
            same(a, wr64BuildRasterShadowProjection(drift.data(), light.data(), mode),
                "Scaled sub-texel movement changed the map");
            const auto b = wr64BuildRasterShadowProjection(crossed.data(), light.data(), mode);
            near((b.rows[0][3] - a.rows[0][3]) * .5, -1. / 1024, 1e-7,
                "Scaled grid crossing did not move one map texel");
            const auto depthReference = wr64BuildRasterShadowProjection(camera.data(), light.data());
            require(std::memcmp(a.rows[2], depthReference.rows[2], sizeof(a.rows[2]) * 2) == 0,
                "Camera-centered depth changed with distance");
        }
        for (float coordinate : {-1.5f, -.5f, .5f, 1.5f}) {
            const Vec3 camera{coordinate * texel, 0, 0}, translated{(coordinate + 1) * texel, 0, 0};
            const auto a = wr64BuildRasterShadowProjection(camera.data(), light.data(), mode);
            const auto b = wr64BuildRasterShadowProjection(translated.data(), light.data(), mode);
            near(b.rows[0][3] - a.rows[0][3], -1. / 512, 1e-9, "Scaled negative grid tie is inconsistent");
        }
        for (float bad : {std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::infinity()}) {
            const Vec3 badPoint{bad, 0, 0};
            for (const auto &mapBad : {wr64BuildRasterShadowProjection(badPoint.data(), light.data(), mode),
                    wr64BuildRasterShadowProjection(origin.data(), badPoint.data(), mode),
                    wr64BuildRasterShadowProjection(nullptr, light.data(), mode)}) {
                require(!mapBad.valid, "Invalid scaled projection was admitted");
                for (const auto &row : mapBad.rows) for (float value : row)
                    require(value == 0, "Invalid scaled projection leaked partial output");
            }
        }
    }
}

void snapshots() {
    const Vec3 camera{47, -101, 200}, light{-80, 80, 0};
    for (uint32_t selected = 0; selected < 4; ++selected) {
        setWr64ShadowMethod(1);
        setWr64RasterShadowDistance(selected);
        const auto settings = getWr64RTSettings();
        for (uint32_t course = 0; course <= 9; ++course) for (uint32_t players : {1u, 2u})
        for (bool enhanced : {false, true}) for (const auto scene : {std::array<uint32_t, 2>{1, 40},
                std::array<uint32_t, 2>{1, 41}, std::array<uint32_t, 2>{1, 42},
                std::array<uint32_t, 2>{1, 43}, std::array<uint32_t, 2>{1, 44},
                std::array<uint32_t, 2>{1, 45}, std::array<uint32_t, 2>{0, 2},
                std::array<uint32_t, 2>{0, 3}, std::array<uint32_t, 2>{0, 4},
                std::array<uint32_t, 2>{8, 30}, std::array<uint32_t, 2>{8, 31},
                std::array<uint32_t, 2>{0, 0}, std::array<uint32_t, 2>{4, 10}}) {
            const bool allowed = (players == 1 && course <= 8 &&
                (scene[0] == 1 || scene[0] == 8 ||
                    (course == 0 && scene[0] == 0 && scene[1] >= 2 && scene[1] <= 4))) ||
                (players == 2 && enhanced && course >= 1 && course <= 8 && scene[0] == 1);
            Snapshot workload;
            require(!workload.wr64RasterShadowScope && workload.wr64RasterShadowDistanceMode == 0,
                "New workload has a stale shadow range");
            capture(workload, settings, course, players, scene[0], scene[1], enhanced);
            require(workload.wr64RasterShadowScope == allowed &&
                workload.wr64RasterShadowDistanceMode == (allowed ? selected : 0),
                "Shadow range snapshot escaped the accepted course/player/menu scope");
            const auto before = rendererProjection(workload, camera.data(), light.data());
            for (uint32_t next = 0; next < 4; ++next) {
                setWr64RasterShadowDistance(next);
                same(before, rendererProjection(workload, camera.data(), light.data()),
                    "Live UI change altered an already-captured workload");
                Snapshot following;
                capture(following, getWr64RTSettings(), course, players, scene[0], scene[1], enhanced);
                same(rendererProjection(following, camera.data(), light.data()),
                    wr64BuildRasterShadowProjection(camera.data(), light.data(), allowed ? next : 0),
                    "Renderer ignored the following workload's selected range");
            }
            workload.reset();
            require(!workload.wr64RasterShadowScope && workload.wr64RasterShadowDistanceMode == 0,
                "Reused workload retained the previous scope or range");
        }
    }
    Snapshot failed;
    wr64RTStartupGate.request();
    wr64RTStartupGate.publish(Wr64RTStartupGate::State::Failed);
    capture(failed, getWr64RTSettings(), 1, 1, 1, 40, true);
    require(!failed.wr64RasterShadowScope && failed.wr64RasterShadowDistanceMode == 0,
        "Failed renderer startup retained expanded range");
    wr64RTStartupGate.reset();
    for (uint32_t method : {0u, 2u}) {
        setWr64ShadowMethod(method);
        capture(failed, getWr64RTSettings(), 1, 1, 1, 40, true);
        require(!failed.wr64RasterShadowScope && failed.wr64RasterShadowDistanceMode == 0,
            "Original or Ray Traced shadows activated raster distance");
    }
}

void actor_fallback() {
    constexpr float factors[] = {1, 1.5f, 2, 3};
    const Vec3 origin{}, light{0, 0, 1};
    const auto fixture = [&](uint32_t mode, float centerX) {
        ActorFixture result;
        const auto map = wr64BuildRasterShadowProjection(origin.data(), light.data(), mode);
        std::memcpy(result.rasterShadowParams.lightRows, map.rows, sizeof(map.rows));
        for (auto &bounds : result.actorBounds) {
            bounds.populated = true;
            bounds.minimum = {centerX - 10, -10, -10};
            bounds.maximum = {centerX + 10, 10, 10};
        }
        return result;
    };
    for (uint32_t mode = 0; mode < 4; ++mode) {
        auto good = fixture(mode, 0);
        coverActors(&good);
        require(good.rasterShadowRacers == 15, "Covered actor lost native-blob replacement");
        for (uint32_t failure = 0; failure < 7; ++failure) {
            auto bad = fixture(mode, 0);
            if (failure == 0) bad.prepared = false;
            else if (failure == 1) bad.racerShadowCasters = 0;
            for (auto &bounds : bad.actorBounds) {
                if (failure == 2) bounds.reliable = false;
                if (failure == 3) bounds.populated = false;
                if (failure == 4) bounds.maximum[0] = .8f * 2048 * factors[mode] + 1;
                if (failure == 5) bounds.maximum[2] = 7600;
                if (failure == 6) bounds.maximum[1] = std::numeric_limits<float>::quiet_NaN();
            }
            coverActors(&bad);
            require(bad.rasterShadowRacers == 0, "Missing/partial/invalid coverage removed native actor blobs");
        }
        if (mode) {
            const float newlyCovered = .8f * 2048 * factors[mode - 1] + 50;
            auto before = fixture(mode - 1, newlyCovered), after = fixture(mode, newlyCovered);
            coverActors(&before); coverActors(&after);
            require(before.rasterShadowRacers == 0 && after.rasterShadowRacers == 15,
                "Expanded map did not replace blobs only after the full actor was covered");
        }
        auto identity = fixture(mode, 0);
        identity.racerShadowCasters = 1u << 2;
        coverActors(&identity);
        require(identity.rasterShadowRacers == (1u << 2), "Expanded coverage changed racer ownership");
        // Each split-screen presentation derives its map from its own camera.
        const Vec3 otherCamera{20000, 0, 0};
        const auto first = wr64BuildRasterShadowProjection(origin.data(), light.data(), mode);
        const auto second = wr64BuildRasterShadowProjection(otherCamera.data(), light.data(), mode);
        near(project(first, origin)[0], 0, 0, "First camera lost its shadow center");
        near(project(second, otherCamera)[0], 0, 1. / 1024, "Second camera lost its own shadow center");
        require(std::abs(project(first, otherCamera)[0]) > 1 && std::abs(project(second, origin)[0]) > 1,
            "Split presentations accidentally shared shadow coverage");
    }
}
}

int main() {
    try {
        original_parity(); range_and_grid(); snapshots(); actor_fallback();
        std::cout << "PASS: " << checks << " shadow-distance checks: Original byte parity, four ranges, fixed depth, "
            "scaled texel grid, all 16 snapshot transitions, course/player guards and native actor-blob fallback.\n";
    } catch (const std::exception &error) {
        std::cerr << "FAIL after " << checks << " checks: " << error.what() << '\n';
        return 1;
    }
}
