// Exercise the existing USA native projection and disk/glow display-list
// producer. The matrix loader supplies synthetic camera fixtures; no ROM,
// graphics API, window, or game process is required.
#include "recomp.h"
#include "wr64_ultrawide.hpp"
#include "common/rt64_wr64_ultrawide.h"
#include <algorithm>
#include <array>
#include <bit>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

extern "C" {
void func_8008962C(uint8_t*, recomp_context*);
void baseline_func_8008962C(uint8_t*, recomp_context*);
void regenerated_func_8008962C(uint8_t*, recomp_context*);
void projection_control_func_8008962C(uint8_t*, recomp_context*);
void func_8008D94C(uint8_t*, recomp_context*);
}
using Function = void (*)(uint8_t*, recomp_context*);
using Record = std::array<uint32_t, 6>;
static std::array<float, 16> projectionMatrix{}, viewMatrix{};
static unsigned checks = 0, cases = 0, unchangedCases = 0, extendedCases = 0, matrixCalls = 0;
static std::string caseDescription;
static void require(bool value, const char* message) {
    ++checks;
    if (!value) {
        std::cerr << message << ": " << caseDescription << '\n';
        std::exit(1);
    }
}
static float real(uint32_t bits) { return std::bit_cast<float>(bits); }

extern "C" void SysUtils_MtxToMtxF(uint8_t* rdram, recomp_context* ctx) {
    const auto& matrix = uint32_t(ctx->r4) == 0x8040E008 ? projectionMatrix : viewMatrix;
    require(uint32_t(ctx->r4) == 0x8040E008 || uint32_t(ctx->r4) == 0x8040E088,
        "native projection requested unexpected matrix");
    for (int i = 0; i < 16; ++i) MEM_W(i * 4, ctx->r5) = std::bit_cast<uint32_t>(matrix[i]);
    ++matrixCalls;
}

struct Replay {
    std::vector<uint8_t> memory = std::vector<uint8_t>(8 * 1024 * 1024);
    void setFloat(uint32_t address, float value) {
        uint8_t* rdram = memory.data();
        MEM_W(0, S32(address)) = std::bit_cast<uint32_t>(value);
    }
    void setDouble(uint32_t address, double value) {
        uint8_t* rdram = memory.data();
        SD(std::bit_cast<uint64_t>(value), 0, S32(address));
    }
    Replay() {
        uint8_t* rdram = memory.data();
        MEM_W(0, S32(0x801518B8)) = 0x80400000;
        // A unit sun direction at azimuth zero, with a camera direction set
        // independently below. All constants are synthetic fixture values.
        setFloat(0x80154350, 0.0f);
        setFloat(0x80155350, 1.0f);
        setDouble(0x800EAAF0, 2.0); // Helper's optional horizontal constraint.
        setDouble(0x800EAAF8, 1.0);
        setDouble(0x800EAB00, 1.0);
        setDouble(0x800EAB08, 0.001);
        setDouble(0x800EAB10, -0.001);
        setDouble(0x800EAB18, 0.001);
        setDouble(0x800EAB20, 1000000.0);
        setDouble(0x800EAB28, -1000000.0);
        setDouble(0x800EAB30, -1000000.0);
        setDouble(0x800EAB38, 0.0);
        setDouble(0x800EAB40, 0.0);
        setDouble(0x800EAB48, 240.0);
        setDouble(0x800EAB50, 0.001);
        setDouble(0x800EAB58, -0.001);
        setFloat(0x800EAB60, -64.0f);
    }
    Record run(Function function, int course, uint32_t address, float facing,
               float center, float vertical = 110.0f, float halfWidth = 12.0f, float clipW = 1.0f,
               bool coherentCamera = false, float verticalFov = 60.0f) {
        uint8_t* rdram = memory.data();
        recomp_context ctx{};
        ctx.f_odd = &ctx.f0.u32h;
        ctx.r29 = S32(0x80700000);
        ctx.r16 = S32(0x80654320);
        ctx.r7 = S32(address);
        ctx.r6 = std::bit_cast<uint32_t>(24.0f);
        ctx.f12.fl = 1.0f;
        ctx.f14.fl = 0.0f;
        std::memset(rdram + 0x700000 - 0x200, 0, 0x400);
        std::memset(rdram + (address & 0x7FFFFF) - 16, 0xA5, 56);
        MEM_W(0, S32(0x800D8170)) = course;
        MEM_W(course * 4, S32(0x800D9944)) = 24;
        setFloat(0x80227D70, facing);
        setFloat(0x80227D74, std::sqrt(std::max(0.0f, 1.0f - facing * facing)));
        // Controlled projected coordinates isolate the direction predicate
        // from position: both matrices still pass through the complete native
        // multiply, perspective division, width offset, and record windows.
        projectionMatrix.fill(0);
        projectionMatrix[0] = projectionMatrix[5] = projectionMatrix[10] = 1.0f;
        projectionMatrix[15] = clipW;
        viewMatrix.fill(0);
        viewMatrix[4] = halfWidth / 24.0f;
        viewMatrix[5] = 0.5f;
        viewMatrix[12] = (center - halfWidth - wr64_sun_logical_width() * 0.5f) * clipW / 212.0f;
        viewMatrix[13] = (120.0f - vertical - 12.0f) * clipW / 120.0f;
        viewMatrix[15] = 1.0f;
        if (coherentCamera) {
            // A real perspective camera, rather than independently selected
            // direction and screen position. The sun lies on world +X, and
            // the view matrix and angular predicate use the same yaw.
            const float lateral = std::copysign(std::sqrt(std::max(0.0f, 1.0f - facing * facing)), center);
            const float focal = 1.0f / std::tan(verticalFov * 3.14159265358979323846f / 360.0f);
            ctx.f12.fl = 2000.0f;
            ctx.r6 = std::bit_cast<uint32_t>(12.0f);
            setFloat(0x80227D74, -lateral);
            projectionMatrix.fill(0);
            projectionMatrix[0] = focal / (424.0f / 240.0f);
            projectionMatrix[5] = focal;
            projectionMatrix[10] = -1.0f;
            projectionMatrix[11] = -1.0f;
            viewMatrix.fill(0);
            viewMatrix[0] = lateral;
            viewMatrix[2] = -facing;
            viewMatrix[5] = 1.0f;
            viewMatrix[8] = -facing;
            viewMatrix[10] = -lateral;
            viewMatrix[15] = 1.0f;
        }
        function(rdram, &ctx);
        require(uint32_t(ctx.r29) == 0x80700000 && uint32_t(ctx.r16) == 0x80654320,
            "native projection failed to restore stack or saved register");
        for (int i = -16; i < 40; ++i)
            if (i < 0 || i >= 24) require(rdram[(address & 0x7FFFFF) + i] == 0xA5,
                "native projection wrote outside its record");
        Record result{};
        for (int i = 0; i < 6; ++i) result[i] = MEM_W(i * 4, S32(address));
        return result;
    }
    std::vector<std::array<float, 4>> rectangles(const Record& record, int course = 2, int radius = 24) {
        uint8_t* rdram = memory.data();
        recomp_context ctx{};
        ctx.f_odd = &ctx.f0.u32h;
        ctx.r29 = S32(0x80700000);
        ctx.r4 = S32(0x80500000);
        std::memset(rdram + 0x700000 - 0x200, 0, 0x400);
        std::memset(rdram + 0x500000, 0xA5, 0x1000);
        MEM_W(0, S32(0x800D8170)) = course;
        MEM_W(course * 4, S32(0x800D9944)) = radius;
        for (int i = 0; i < 6; ++i) MEM_W(i * 4, S32(0x801C4170)) = record[i];
        func_8008D94C(rdram, &ctx);
        require(uint32_t(ctx.r2) >= 0x80500000 && uint32_t(ctx.r2) < 0x80501000,
            "sun display-list cursor out of bounds");
        std::vector<std::array<float, 4>> result;
        for (uint32_t p = 0x80500000; p < uint32_t(ctx.r2); p += 8) {
            uint32_t high = MEM_W(0, S32(p)), low = MEM_W(4, S32(p));
            if ((high >> 24) == 0xE4)
                result.push_back({float((low >> 12) & 0xFFF) / 4.0f, float((high >> 12) & 0xFFF) / 4.0f,
                    float(low & 0xFFF) / 4.0f, float(high & 0xFFF) / 4.0f});
        }
        return result;
    }
};

static Record compare(Replay& replay, int course, uint32_t address, float facing, float center,
                      float vertical = 110.0f, float halfWidth = 12.0f, float clipW = 1.0f) {
    caseDescription = "width=" + std::to_string(wr64_sun_logical_width()) + " course=" + std::to_string(course) +
        " record=" + std::to_string(address) + " facing=" + std::to_string(facing) +
        " center=" + std::to_string(center) + " y=" + std::to_string(vertical) + " w=" + std::to_string(clipW);
    const auto before = replay.run(baseline_func_8008962C, course, address, facing, center, vertical, halfWidth, clipW);
    const auto after = replay.run(func_8008962C, course, address, facing, center, vertical, halfWidth, clipW);
    const auto regenerated = replay.run(regenerated_func_8008962C, course, address, facing, center, vertical, halfWidth, clipW);
    require(after == regenerated, "checked-in projection differs from durable config hook recipe");
    const bool probe = wr64_sun_logical_width() > 424 && (course == 0 || course == 2) &&
        address == 0x801C4170 && facing > 0 && facing < 0.5f;
    if (!probe) {
        require(after == before, "repair altered baseline aspect, course, record, or angularly accepted state");
        ++unchangedCases;
    } else {
        const auto projected = replay.run(projection_control_func_8008962C, course, address, facing, center, vertical, halfWidth, clipW);
        const float projectedCenter = std::trunc(real(projected[0]) + real(projected[3]));
        const bool keep = projectedCenter > (course == 0 ? -128.0f : wr64_sun_logical_width() * 0.5f) &&
            projectedCenter < wr64_sun_horizontal_cull_limit();
        // The control has already passed the native record windows. Window
        // failures can legitimately park both paths identically.
        if (keep && real(projected[5]) >= 0) {
            require(after == projected, "right-exit record does not match original native projection");
            require(real(before[5]) == -1.0f, "immutable baseline failed to reproduce angular rejection");
            ++extendedCases;
        } else if (vertical == 110.0f && clipW == 1.0f) {
            require(after == before, "left or fully culled state changed");
            ++unchangedCases;
        }
    }
    ++cases;
    return after;
}

static void dolphinCoherentCameras(Replay& replay) {
    unsigned restoredLeft = 0, restoredRight = 0, accepted = 0;
    for (float aspect : {16.0f / 9.0f, 21.0f / 9.0f, 32.0f / 9.0f, 48.0f / 9.0f}) {
        RT64::wr64UltrawidePublishAspect(aspect);
        for (float fov : {40.0f, 50.0f, 60.0f, 75.0f}) {
            for (int degrees = -85; degrees <= 85; ++degrees) {
                const float facing = std::cos(float(degrees) * 3.14159265358979323846f / 180.0f);
                caseDescription = "DP coherent camera width=" + std::to_string(wr64_sun_logical_width()) +
                    " yaw=" + std::to_string(degrees) + " vertical FOV=" + std::to_string(fov);
                const auto before = replay.run(baseline_func_8008962C, 0, 0x801C4170, facing,
                    float(degrees), 110, 12, 1, true, fov);
                const auto projected = replay.run(projection_control_func_8008962C, 0, 0x801C4170, facing,
                    float(degrees), 110, 12, 1, true, fov);
                const auto after = replay.run(func_8008962C, 0, 0x801C4170, facing,
                    float(degrees), 110, 12, 1, true, fov);
                const auto regenerated = replay.run(regenerated_func_8008962C, 0, 0x801C4170, facing,
                    float(degrees), 110, 12, 1, true, fov);
                require(after == regenerated, "DP coherent projection differs from durable config");
                const float center = real(projected[0]) + real(projected[3]);
                if (real(projected[5]) >= 0) {
                    const float focal = 120.0f / std::tan(fov * 3.14159265358979323846f / 360.0f);
                    const float expected = wr64_sun_logical_width() * 0.5f +
                        focal * std::tan(float(degrees) * 3.14159265358979323846f / 180.0f);
                    require(std::abs(center - expected) < 0.01f,
                        "DP native path did not preserve coherent perspective projection");
                }
                if (facing >= 0.5f || wr64_sun_logical_width() <= 424.0f) {
                    require(after == before, "DP angularly accepted or baseline camera changed");
                    ++accepted;
                } else if (real(projected[5]) >= 0 && center > -12.0f && center < wr64_sun_logical_width() + 12.0f) {
                    require(after == projected, "DP angular cutoff removed a disk still inside the wider view");
                    require(real(before[5]) == -1.0f, "DP negative control did not reproduce angular rejection");
                    require(replay.rectangles(after, 0, 12) == replay.rectangles(projected, 0, 12),
                        "DP disk emitter disagreed with original visible native projection");
                    if (degrees < 0) ++restoredLeft;
                    else ++restoredRight;
                }
                ++cases;
            }
        }
    }
    require(restoredLeft > 20 && restoredRight > 20,
        "coherent cameras did not exercise both Dolphin Park horizontal exits");
    std::cout << "DP coherent cameras: " << restoredLeft << " left and " << restoredRight
        << " right previously missing visible positions; " << accepted << " exact accepted/baseline records.\n";

    // Existing top-edge reconstruction depends on the authored shortened
    // rectangle. Preserve every field in those original accepted records and
    // their emitted full/shortened vertical bounds, across all supported widths.
    unsigned topEdgeCases = 0;
    for (float aspect : {16.0f / 9.0f, 21.0f / 9.0f, 32.0f / 9.0f}) {
        RT64::wr64UltrawidePublishAspect(aspect);
        for (float facing : {0.5f, 0.75f, 1.0f})
            for (int y = -32; y <= 260; ++y) {
                caseDescription = "DP preserved top edge width=" + std::to_string(wr64_sun_logical_width()) +
                    " facing=" + std::to_string(facing) + " y=" + std::to_string(y);
                const auto before = replay.run(baseline_func_8008962C, 0, 0x801C4170, facing, 212, float(y));
                const auto after = replay.run(func_8008962C, 0, 0x801C4170, facing, 212, float(y));
                require(after == before, "DP original top-edge record changed");
                require(replay.rectangles(after, 0, 12) == replay.rectangles(before, 0, 12),
                    "DP authored top-edge disk rectangles changed");
                ++topEdgeCases;
                ++cases;
            }
    }
    std::cout << "DP original top-edge records and disk bounds: " << topEdgeCases << " exact comparisons.\n";
}

int main() {
    Replay replay;
    for (float aspect : {4.0f / 3.0f, 16.0f / 9.0f, 21.0f / 9.0f, 32.0f / 9.0f}) {
        RT64::wr64UltrawidePublishAspect(aspect);
        for (int course = 0; course < 9; ++course)
            for (uint32_t record : {0x801C4170U, 0x801C4190U, 0x80600000U})
                for (float facing : {-1.0f, -0.001f, 0.0f, 0.001f, 0.1f, 0.49f, 0.499999f, 0.5f, 0.500001f, 1.0f})
                    for (float center : {-1500.0f, -300.0f, -1.0f, 0.0f, 120.0f, 212.0f, 300.0f,
                            423.0f, 424.0f, 550.0f, 565.0f, 600.0f, 683.0f, 684.0f, 685.0f,
                            847.0f, 848.0f, 975.0f, 976.0f, 1500.0f})
                        compare(replay, course, record, facing, center);
        if (aspect <= 16.0f / 9.0f) continue;
        // Every pixel over each exit, including native integer truncation,
        // centerline eligibility, and the existing width+128 cull boundary.
        for (int course : {0, 2}) {
            for (int center = -300; center <= int(wr64_sun_logical_width()) + 160; ++center)
                for (float fraction : {0.0f, 0.25f, 0.999f})
                    compare(replay, course, 0x801C4170, 0.49f, float(center) + fraction);
            for (float y : {-1500.0f, -100.0f, 0.0f, 239.0f, 240.0f, 1500.0f})
                for (float w : {-1.0f, 0.0001f, 1.0f, 4.0f})
                    compare(replay, course, 0x801C4170, 0.49f, 565.0f, y, 12.0f, w);
        }

        unsigned oldVisibleLosses = 0, lastVisible = 0;
        for (int center = int(wr64_sun_logical_width()) - 30;
             center <= int(wr64_sun_logical_width()) + 130; ++center) {
            const auto after = compare(replay, 2, 0x801C4170, 0.49f, float(center) + 0.25f);
            const auto projected = replay.run(projection_control_func_8008962C, 2, 0x801C4170, 0.49f, float(center) + 0.25f);
            const auto controlRectangles = replay.rectangles(projected);
            const auto afterRectangles = replay.rectangles(after);
            bool visible = false;
            for (const auto& rectangle : controlRectangles)
                visible |= rectangle[0] < wr64_sun_logical_width() && rectangle[1] > 0 && rectangle[1] > rectangle[0];
            if (visible) {
                require(afterRectangles == controlRectangles, "disk/glow disappeared before native rectangles left screen");
                const auto before = replay.run(baseline_func_8008962C, 2, 0x801C4170, 0.49f, float(center) + 0.25f);
                require(replay.rectangles(before).empty(), "baseline unexpectedly retained the right-exit disk/glow");
                ++oldVisibleLosses;
                lastVisible = center;
            }
            if (center >= wr64_sun_horizontal_cull_limit())
                require(afterRectangles.empty(), "existing right cull failed to remove fully offscreen sun");
        }
        require(oldVisibleLosses >= 40, "negative control did not reproduce substantial early visible loss");
        require(lastVisible >= wr64_sun_logical_width() + 20, "native sun did not survive beyond center leaving screen");
        std::cout << "width " << wr64_sun_logical_width() << ": " << oldVisibleLosses
            << " previously missing visible disk/glow positions restored; last visible center " << lastVisible << ".\n";
    }
    dolphinCoherentCameras(replay);
    require(extendedCases > 1000, "insufficient native right-exit coverage");
    require(matrixCalls > 1000, "native projection matrices were not exercised");
    std::cout << cases << " native projector replays; " << unchangedCases << " exact baseline comparisons; "
        << extendedCases << " extended records match original projection; " << checks << " assertions.\n"
        << "Native helpers and disk/glow emitter unchanged; current source matches config-regenerated hooks.\n";
}
