#include "common/rt64_wr64_dolphin_sun_edge.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace RT64;
using Scope = Wr64DolphinSunEdgeScope;
constexpr uint64_t Disk = 0x79185A8F164D1366ULL;
constexpr uint64_t Flare = 0xB82E909F647A31ADULL;
static unsigned checks = 0;

static void require(bool value, const std::string &reason) {
    ++checks;
    if (!value) {
        std::fprintf(stderr, "FAIL: %s\n", reason.c_str());
        std::exit(1);
    }
}

static float opacity(Scope scope, float top) {
    return wr64DolphinSunEdgeOpacity(scope, Disk, true, top);
}

static void testScopeAndContinuity() {
    // A bounded exhaustive matrix includes invalid states and every course,
    // player count, phase and mode adjacent to the admitted opening state.
    // Gameplay fading was rejected and every gameplay mode must stay inactive.
    for (int course = -2; course <= 12; ++course) {
        for (int players = -1; players <= 5; ++players) {
            for (int phase = -2; phase <= 8; ++phase) {
                for (int mode = -2; mode <= 8; ++mode) {
                    Scope expected = Scope::None;
                    if (course == 0 && players == 1 && phase == 0 && mode == 2)
                        expected = Scope::Opening;
                    require(wr64DolphinSunEdgeScope(course, players, phase, mode) == expected,
                        "scope admitted an unrelated game state or rejected Dolphin Park");
                }
            }
        }
    }

    require(static_cast<unsigned>(Scope::None) == 0 && static_cast<unsigned>(Scope::Opening) == 2,
        "opening scope changed its existing value");
    for (uint32_t mode : {uint32_t(0), uint32_t(1), uint32_t(2), uint32_t(3), uint32_t(99), UINT32_MAX}) {
        require(wr64DolphinSunEdgeScope(0, 1, 1, mode) == Scope::None,
            "a gameplay mode still admits the rejected fade");
    }
    for (Scope scope : {Scope::None, static_cast<Scope>(1), Scope::Opening}) {
        for (float top : {std::numeric_limits<float>::quiet_NaN(),
                          std::numeric_limits<float>::infinity(),
                          -std::numeric_limits<float>::infinity()}) {
            require(opacity(scope, top) == 1.0f, "invalid coordinate changed the original draw");
        }
        for (float top : {-4096.0f, -96.0f, 0.0f, 0.125f, 24.0f, 80.0f, 96.0f, 4096.0f}) {
            for (uint64_t hash : {uint64_t(0), Flare, uint64_t(0x8A399FACE63FE583ULL),
                                 uint64_t(0x329E604758F9E8BCULL), Disk ^ 1ULL}) {
                require(wr64DolphinSunEdgeOpacity(scope, hash, true, top) == 1.0f,
                    "unrelated texture changed, including shared flare or Sunset Bay sun");
            }
            require(wr64DolphinSunEdgeOpacity(scope, Disk, false, top) == 1.0f,
                "a nonrectangle draw changed");
            require(opacity(Scope::None, top) == 1.0f, "inactive scope changed opacity");
        }
    }
    // The removed Gameplay value (1), every other unknown scope, and None
    // must preserve opacity even at positions previously inside the fade.
    for (unsigned value = 0; value <= 255; ++value) {
        if (value == static_cast<unsigned>(Scope::Opening)) continue;
        for (float top : {-4096.0f, -96.0f, -0.25f, 0.0f, 0.125f, 12.0f,
                          24.0f, 36.0f, 47.875f, 48.0f, 80.0f, 104.0f, 4096.0f}) {
            require(opacity(static_cast<Scope>(value), top) == 1.0f,
                "inactive or removed gameplay scope changed opacity");
        }
    }

    {
        const Scope scope = Scope::Opening;
        const float margin = 80.0f;
        require(opacity(scope, margin - 0.125f) == 0.0f, "edge side is not transparent");
        require(opacity(scope, margin) == 0.0f, "fade does not end before the cut");
        require(opacity(scope, margin + 24.0f) == 0.5f, "fade midpoint moved");
        require(opacity(scope, margin + 48.0f) == 1.0f, "settled visible sun dimmed");
        require(opacity(scope, margin + 12.0f) == 0.15625f, "first quarter fade changed");
        require(opacity(scope, margin + 36.0f) == 0.84375f, "last quarter fade changed");

        float previous = 0.0f;
        for (int step = -1024; step <= 2048; ++step) {
            const float value = opacity(scope, margin + step * 0.0625f);
            require(std::isfinite(value) && value >= 0.0f && value <= 1.0f,
                "finite coordinate produced invalid opacity");
            require(value >= previous, "fade reverses while the disk moves down");
            // The maximum smoothstep slope is 1.5 / 48 per quarter-pixel.
            require(value - previous < 0.002f, "fractional chosen motion steps in opacity");
            previous = value;
        }
        require(opacity(scope, margin + 0.01f) < 0.000001f,
            "fade has a hard onset at the invisible boundary");
        require(1.0f - opacity(scope, margin + 47.99f) < 0.000001f,
            "fade has a hard onset at the fully visible boundary");

        // A fast opening tick traverses the complete band. Nine output weights
        // must still produce intermediate values without a temporal cache.
        previous = 1.0f;
        unsigned partial = 0;
        for (int output = 0; output <= 9; ++output) {
            const float top = margin + 72.0f - output * (96.0f / 9.0f);
            const float value = opacity(scope, top);
            require(value <= previous, "fast opening interpolation reverses");
            if (value > 0.0f && value < 1.0f) ++partial;
            previous = value;
        }
        require(partial >= 4 && previous == 0.0f,
            "fast opening interpolation did not cross a continuous fade");
    }
}

struct Row {
    std::string scenario;
    Scope scope;
    bool gameplay;
    uint64_t output, submission, hash;
    float weight, rawTop, rawBottom, chosenTop, chosenBottom, viewportTop, viewportHeight;
    float u1, v1, u2, v2;
    float alpha() const { return wr64DolphinSunEdgeOpacity(scope, hash, true, chosenTop); }
    float visibleContribution() const {
        return std::max(0.0f, viewportTop + viewportHeight - std::max(0.0f, viewportTop)) * alpha();
    }
};

static std::vector<Row> readCapture(const char *path) {
    std::ifstream stream(path);
    require(stream.good(), "compact capture cannot be opened");
    std::string line;
    std::getline(stream, line);
    std::vector<Row> rows;
    while (std::getline(stream, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        std::istringstream input(line);
        std::vector<std::string> fields;
        std::string field;
        while (std::getline(input, field, ',')) fields.push_back(field);
        require(fields.size() == 17, "compact capture has an unexpected schema");
        Row row{};
        row.scenario = fields[0];
        require(fields[1] == "Opening" || fields[1] == "Gameplay", "unknown fixture scene annotation");
        row.gameplay = fields[1] == "Gameplay";
        row.scope = wr64DolphinSunEdgeScope(0, 1, row.gameplay ? 1 : 0, 2);
        row.output = std::stoull(fields[2]);
        row.submission = std::stoull(fields[3]);
        row.weight = std::stof(fields[4]);
        row.hash = std::stoull(fields[5], nullptr, 16);
        row.rawTop = std::stof(fields[6]); row.rawBottom = std::stof(fields[7]);
        row.chosenTop = std::stof(fields[8]); row.chosenBottom = std::stof(fields[9]);
        row.viewportTop = std::stof(fields[10]); row.viewportHeight = std::stof(fields[11]);
        row.u1 = std::stof(fields[12]); row.v1 = std::stof(fields[13]);
        row.u2 = std::stof(fields[14]); row.v2 = std::stof(fields[15]);
        require(fields[16] == "1908x1080", "native-size preparation leaked into fixture");
        rows.push_back(row);
    }
    require(!rows.empty(), "capture fixture is empty");
    return rows;
}

static void testCapture(const char *path) {
    const auto rows = readCapture(path);
    std::map<uint64_t, std::vector<Row>> submissions;
    unsigned parks = 0, flares = 0, openingHidden = 0, away = 0, cropped = 0, gameplay = 0;
    for (const Row &row : rows) {
        const float value = row.alpha();
        require(std::isfinite(value) && value >= 0.0f && value <= 1.0f,
            "capture playback produced invalid opacity");
        if (row.gameplay) {
            ++gameplay;
            require(row.scope == Scope::None && value == 1.0f,
                "recorded gameplay draw still receives the rejected fade");
            const float originalContribution = std::max(0.0f,
                row.viewportTop + row.viewportHeight - std::max(0.0f, row.viewportTop));
            require(row.visibleContribution() == originalContribution,
                "recorded gameplay coverage changed");
        }
        if (row.hash == Flare) {
            ++flares;
            require(value == 1.0f, "recorded flare changed");
            continue;
        }
        require(row.hash == Disk, "fixture unexpectedly contains another texture");
        submissions[row.submission].push_back(row);
        if (row.viewportHeight == 0.0f) {
            ++parks;
            require(row.visibleContribution() == 0.0f, "settled R3 park became visible");
        }
        if (row.submission == 194 || row.submission == 195) {
            ++openingHidden;
            require(value == 0.0f, "recorded opening edge disk remains visible");
        }
        if (row.submission == 352 || (row.submission == 700 && row.chosenTop >= 48.0f)) {
            ++away;
            require(value == 1.0f, "recorded sun away from the edge changed");
        }
        if (row.viewportHeight > 0.0f && row.rawTop == 0.0f && row.rawBottom < 96.0f) {
            ++cropped;
            require(row.v2 - row.v1 < 31.0f, "fixture lost its shortened native UV witness");
            require(value == (row.gameplay ? 1.0f : 0.0f),
                "shortened native UV draw changed outside the accepted opening correction");
        }
    }
    require(parks >= 30 && flares >= 20 && openingHidden == 18 && away >= 18 && cropped >= 54 && gameplay >= 200,
        "fixture no longer exercises all measured regressions");

    // Gameplay is restored exactly, including the existing R3 boundary. This
    // test deliberately does not claim that opacity fixes the geometric exit.
    const auto &before = submissions[757];
    const auto &after = submissions[758];
    require(before.size() == 9 && after.size() == 9, "757 to 758 regression boundary is missing");
    require(before.back().viewportTop + before.back().viewportHeight == 63.0f,
        "fixture lost the original 63-pixel abrupt disappearance witness");
    require(before.back().visibleContribution() == 63.0f,
        "gameplay sun is still faded before the original R3 cutoff");
    for (const Row &row : before) require(row.alpha() == 1.0f, "gameplay disk opacity was not restored");
    for (const Row &row : after) require(row.visibleContribution() == 0.0f, "existing R3 suppression changed");

    const auto &entry = submissions[734];
    require(entry.size() == 9, "recorded gameplay entry is missing");
    for (const Row &row : entry) require(row.alpha() == 1.0f, "recorded gameplay entry is still faded");
}

int main(int argc, char **argv) {
    if (argc == 1) testScopeAndContinuity();
    else if (argc == 2) testCapture(argv[1]);
    else { std::fprintf(stderr, "Usage: %s [capture.csv]\n", argv[0]); return 2; }
    std::printf("PASS: %u Dolphin Park sun edge checks\n", checks);
    return 0;
}
