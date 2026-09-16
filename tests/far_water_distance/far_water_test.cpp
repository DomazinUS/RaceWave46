#include "water_fixture.inc"
#include <array>
#include "wr64_camera_fov.hpp"
#include "recomp.h"
#include "water_previous_header.inc"

namespace previous {
using namespace previous_distance;
#include "water_previous.inc"
}
extern "C" {
void func_801E11B4(uint8_t*, recomp_context*);
void SysUtils_MtxToMtxF(uint8_t*, recomp_context*);
}

using namespace RT64;
static unsigned scenarios = 0;
constexpr uint32_t Modes = 6;
constexpr std::array<std::array<double, 4>, Modes> ExpectedScales{{
    {{1.125, 1.75, 2.375, 3.0}}, {{1.125, 2.25, 3.375, 4.5}}, {{1.125, 2.75, 4.375, 6.0}},
    {{1.125, 3.75, 6.375, 9.0}}, {{1.125, 4.75, 8.375, 12.0}}, {{1.125, 5.75, 10.375, 15.0}}
}};

template<class T> static void prefixEqual(const std::vector<T>& a, const std::vector<T>& b, size_t count, const char* why) {
    require(a.size() >= count && b.size() >= count && std::memcmp(a.data(), b.data(), count * sizeof(T)) == 0, why);
}
static void sameNative(const DrawData& a, const DrawData& b) {
    prefixEqual(a.posFloats, b.posFloats, VertexCount * 3, "Native and unrelated positions changed");
    prefixEqual(a.velFloats, b.velFloats, VertexCount * 3, "Native and unrelated velocities changed");
    prefixEqual(a.tcFloats, b.tcFloats, VertexCount * 2, "Native and unrelated UV changed");
    prefixEqual(a.tcVelFloats, b.tcVelFloats, VertexCount * 2, "Native and unrelated UV velocity changed");
    prefixEqual(a.normColBytes, b.normColBytes, VertexCount * 4, "Native and unrelated normals changed");
    prefixEqual(a.vertexSegmentedAddresses, b.vertexSegmentedAddresses, VertexCount, "Native source identities changed");
    prefixEqual(a.wr64WaterProducerKeys, b.wr64WaterProducerKeys, VertexCount, "Native producer identities changed");
    for (size_t i = 0; i < FaceCount; ++i)
        require(a.faceIndices[i] == b.faceIndices[i], "Original index storage changed");
}
static void sameNonGeometry(const DrawData& a, const DrawData& b) {
    auto copy = a;
    copy.posFloats = b.posFloats; copy.velFloats = b.velFloats;
    sameData(copy, b);
}
static double nativeMedian(const DrawData& draw) {
    std::map<uint32_t, float> bySource;
    for (uint32_t i = WaterBase; i < WaterBase + 488; ++i)
        bySource.emplace(draw.vertexSegmentedAddresses[i], draw.posFloats[i * 3 + 1]);
    std::vector<float> y;
    for (auto& entry : bySource) y.push_back(entry.second);
    std::sort(y.begin(), y.end());
    require(y.size() == 469, "Native welded producer count changed");
    return y[y.size() / 2];
}
static void checkShape(const DrawData& d, const Projection& p, uint32_t mode) {
    require(d.vertexCount() == VertexCount + 288 && p.gameCalls[0].callDesc.triangleCount == 1440,
        "Extension increased native topology or allocation size");
    require(d.wr64FarWaterDistanceMode == mode, "Committed draw lost its own extent");
    std::array<double, 2> center{};
    for (uint32_t anchor = 0; anchor < 6; ++anchor) {
        const uint32_t source = d.wr64WaterFieldInfo[(VertexCount + anchor * 12) * 4 + 1];
        center[0] += d.posFloats[source * 3]; center[1] += d.posFloats[source * 3 + 2];
    }
    center[0] /= 6; center[1] /= 6;
    const auto y = nativeMedian(d);
    for (uint32_t slot = 0; slot < 288; ++slot) {
        const uint32_t vertex = VertexCount + slot;
        const uint32_t source = d.wr64WaterFieldInfo[vertex * 4 + 1];
        const uint32_t layer = slot / 72;
        require(d.wr64WaterVertexMask[vertex] == 5 && d.wr64WaterFieldInfo[vertex * 4] == 0,
            "Generated identity or neutral shader mode changed");
        require(d.wr64WaterFieldInfo[vertex * 4 + 2] == layer + 1 && d.wr64WaterFieldInfo[vertex * 4 + 3] == slot % 72,
            "Four-ring logical identities changed");
        for (uint32_t c : {0U, 2U}) {
            const double expected = center[c / 2] + ExpectedScales[mode][layer] * (d.posFloats[source * 3 + c] - center[c / 2]);
            require(std::fabs(d.posFloats[vertex * 3 + c] - expected) < 0.01, "Flat ring extent is incorrect");
        }
        require(std::fabs(d.posFloats[vertex * 3 + 1] - y) < 0.0001, "Flat ring stopped following native tide datum");
        require(d.normColBytes[vertex * 4] == 0 && d.normColBytes[vertex * 4 + 1] == 127 && d.normColBytes[vertex * 4 + 2] == 0,
            "Flat coverage acquired wave lighting");
        for (uint32_t c = 0; c < 2; ++c)
            require(std::fabs(std::remainder(d.tcFloats[vertex * 2 + c] - 16.0, 32.0)) < 0.0001, "Flat coverage acquired animated-wave UV");
    }
}
static void fractionalWinding(const DrawData& d) {
    for (size_t f = 864 * 3; f < d.wr64WaterFaceIndices.size(); f += 3) {
        for (double q : {0.0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 0.875, 1.0}) {
            double x[3]{}, z[3]{};
            for (size_t c = 0; c < 3; ++c) {
                const uint32_t v = d.wr64WaterFaceIndices[f + c];
                require(v < d.vertexCount(), "Fractional face escaped fixed vertex capacity");
                x[c] = d.posFloats[v * 3] - double(d.velFloats[v * 3]) * q;
                z[c] = d.posFloats[v * 3 + 2] - double(d.velFloats[v * 3 + 2]) * q;
            }
            const double area = (x[1] - x[0]) * (z[2] - z[0]) - (z[1] - z[0]) * (x[2] - x[0]);
            require(std::isfinite(area) && area < -0.001, "Extended water folds during an interpolated presentation");
        }
    }
}
static Workload shifted(const Workload& original, float dx, float dy, float dz, bool moving) {
    auto result = original;
    for (uint32_t v = WaterBase; v < WaterBase + 500; ++v) {
        result.drawData.posFloats[v * 3] += dx;
        result.drawData.posFloats[v * 3 + 1] += dy;
        result.drawData.posFloats[v * 3 + 2] += dz;
        result.drawData.velFloats[v * 3] = moving ? 32.0f : 0.0f;
        result.drawData.velFloats[v * 3 + 1] = moving ? 5.0f : 0.0f;
        result.drawData.velFloats[v * 3 + 2] = moving ? -16.0f : 0.0f;
    }
    return result;
}
static void capture(Workload& workload, const std::map<uint32_t, uint32_t>& ram,
    uint32_t wr64Course, uint32_t wr64Players, uint32_t wr64Phase, uint32_t wr64Mode) {
    const auto wr64Word = [&](uint32_t address) { const auto found=ram.find(address); return found==ram.end()?0U:found->second; };
#include "water_capture.inc"
}
static void scopeTests() {
    for (uint32_t i : {0U, 1U, 2U, 3U, 4U, 5U, 6U, UINT32_MAX}) {
        setWr64FarWaterDistanceMode(i);
        require(getWr64FarWaterDistanceMode() == (i < Modes ? i : 0), "Invalid modes must restore Original");
    }
    for (uint32_t mode = 0; mode < Modes; ++mode) for (uint32_t layer = 1; layer <= 4; ++layer)
        require(wr64FarWaterRingScale(mode, layer) == ExpectedScales[mode][layer - 1], "Public scale mapping changed");
    setWr64FarWaterDistanceMode(5);
    // Execute the actual two-camera State snapshot across every world family.
    for (uint32_t course=0;course<=9;++course) for(uint32_t players:{0U,1U,2U,3U})
    for(uint32_t phase:{0U,1U,2U,8U}) for(uint32_t raceMode:{2U,3U,4U,7U,30U,31U,39U,40U,41U,44U,45U,46U})
    for(uint32_t first:{0U,1U,2U}) for(uint32_t second:{0U,1U,2U}) {
        std::map<uint32_t,uint32_t> ram{{0x80223930,first},{0x80223934,second},
            {0x80227C80,4},{0x80227D8C,4},{0x80227D68,0},{0x80227E74,1}};
        Workload workload; capture(workload,ram,course,players,phase,raceMode);
        const bool race=phase==1&&raceMode>=40&&raceMode<=45;
        const bool world=players==1 ? course<=8&&(phase==1||(phase==8&&(raceMode==30||raceMode==31))||
            (course==0&&phase==0&&raceMode>=2&&raceMode<=4)) :
            players==2&&course>=1&&course<=8&&race;
        for(uint32_t view=0;view<2;++view) {
            const bool expected=world&&view<players&&(view?second:first)<2;
            require(workload.wr64FarWaterDistanceViewScope[view]==expected,"Native per-view world/camera scope mismatch");
            require(workload.wr64FarWaterDistanceViewModes[view]==(expected?5U:0U),"Captured view mode mismatch");
        }
        require(workload.wr64FarWaterDistanceMode==workload.wr64FarWaterDistanceViewModes[0],"Dense mode diverged from first source view");
    }
    for(uint32_t index:{0U,1U}) for(uint32_t type:{0U,3U,4U,5U,6U}) for(uint32_t owner:{0U,1U,2U}) {
        uint32_t camera=0x80227C80+index*0x10C;
        std::map<uint32_t,uint32_t> ram{{0x80223930,index},{0x80223934,index},{camera,type},{camera+0xE8,owner}};
        Workload workload;capture(workload,ram,1,2,1,41);
        require(workload.wr64FarWaterDistanceViewModes[0]==((type==3||type==4||type==5)&&owner==index?5U:0U),"Malformed camera admitted");
    }
    ++scenarios;
}
static uint32_t ramWord(const std::vector<uint8_t>& r, uint32_t a) {
    uint32_t value; std::memcpy(&value, r.data() + (a & 0x7FFFFF), 4); return value;
}
static float ramFloat(const std::vector<uint8_t>& r, uint32_t a) {
    const auto value = ramWord(r, a); float result; std::memcpy(&result, &value, 4); return result;
}
static int16_t ramHalf(const std::vector<uint8_t>& r, uint32_t a) {
    int16_t value; std::memcpy(&value, r.data() + ((a ^ 2) & 0x7FFFFF), 2); return value;
}
using Vector4 = std::array<double, 4>;
using Matrix4 = std::array<double, 16>;
static Matrix4 ramMatrix(const std::vector<uint8_t>& r, uint32_t a) {
    Matrix4 m{};
    for (uint32_t i = 0; i < 16; ++i) m[i] = ramHalf(r, a + i * 2) + double(uint16_t(ramHalf(r, a + 32 + i * 2))) / 65536.0;
    return m;
}
static Vector4 transform(const Vector4& v, const Matrix4& m) {
    Vector4 output{};
    for (uint32_t j = 0; j < 4; ++j) for (uint32_t i = 0; i < 4; ++i) output[j] += v[i] * m[i * 4 + j];
    return output;
}
static void horizon(const Workload& fixture, const Projection& fixtureProjection, const char* path) {
    std::ifstream input(path, std::ios::binary);
    std::vector<uint8_t> ram(std::istreambuf_iterator<char>(input), {});
    require(ram.size() == 0x800000 && ramWord(ram, 0x800D8170) == 1 && ramWord(ram, 0x800DAB28) == 1,
        "Horizon proof needs a complete Sunny one-player native capture");
    const uint32_t slot = ramWord(ram, 0x80223930), camera = 0x80227C80 + slot * 0x10C, pool = ramWord(ram, 0x801518B8);
    require(slot <= 1 && ramWord(ram, camera) == 4, "Horizon proof needs a normal chase camera");
    auto native = fixture;
    for (uint32_t i = WaterBase; i < WaterBase + 500; ++i) {
        const uint32_t address = native.drawData.vertexSegmentedAddresses[i];
        require((address >> 24) == 3, "Water source escaped the real segment-three producer");
        const uint32_t at = pool + (address & 0xFFFFFF);
        require(at >= 0x80000000 && at < 0x80800000 - 16, "Archived vertex outside RAM");
        for (uint32_t c = 0; c < 3; ++c) {
            native.drawData.posFloats[i * 3 + c] = ramHalf(ram, at + c * 2);
            native.drawData.velFloats[i * 3 + c] = 0;
        }
    }
    const double ex = ramFloat(ram, camera + 0x4C), ez = ramFloat(ram, camera + 0x54);
    double dx = ramFloat(ram, camera + 0x7C) - ex, dz = ramFloat(ram, camera + 0x84) - ez;
    const double length = std::hypot(dx, dz); dx /= length; dz /= length;
    current::fixtureStrength = 0;
    for (double extra : {0.0, 10.0}) {
        auto projectedRam = ram;
        wr64::camera_fov::set_extra_degrees(extra);
        recomp_context ctx{}; ctx.f_odd = &ctx.f0.u32h; ctx.r4 = S32(pool); ctx.r5 = S32(camera); ctx.r29 = S32(0x807FF000);
        func_801E11B4(projectedRam.data(), &ctx);
        const auto view = ramMatrix(projectedRam, pool + 0xE088 + slot * 64);
        auto projection = ramMatrix(projectedRam, pool + 0xE008 + slot * 64);
        // Expand the horizontal extent to16:9 while preserving the native vertical lens.
        projection[0] = projection[5] / (16.0 / 9.0);
        const auto project = [&](const Vector4& p) { return transform(transform(p, view), projection); };
        const auto optical = project({dx, 0, dz, 0});
        require(optical[3] > 0, "Optical horizontal ray points behind the eye");
        const double opticalY = optical[1] / optical[3];
        double priorDistance = 0, priorGap = std::numeric_limits<double>::infinity();
        std::printf("HORIZON capture=%s extra_fov=%.0f optical_row720=%.6f near=%.3f far=%.3f\n", path, extra,
            (1 - opticalY) * 360, ramFloat(ram, camera + 0x9C), ramFloat(ram, camera + 0xA0));
        for (uint32_t mode = 0; mode < Modes; ++mode) {
            auto water = native; auto p = fixtureProjection; water.wr64FarWaterDistanceMode = mode;
            require(current::tryAugmentWr64WaterDenseAnnulus(water, p, 0) == current::Wr64DenseWaterCallResult::Augmented,
                "Actual Sunny native mesh did not admit annulus");
            double distance = std::numeric_limits<double>::infinity();
            for (uint32_t i = 0; i < 72; ++i) {
                const uint32_t a = VertexCount + 216 + i, b = VertexCount + 216 + (i + 1) % 72;
                const auto& positions = water.drawData.posFloats;
                const double ax = positions[a * 3] - ex, az = positions[a * 3 + 2] - ez;
                const double sx = positions[b * 3] - positions[a * 3], sz = positions[b * 3 + 2] - positions[a * 3 + 2];
                const double denominator = dx * sz - dz * sx;
                if (std::fabs(denominator) < 1e-9) continue;
                const double t = (ax * sz - az * sx) / denominator, u = (ax * dz - az * dx) / denominator;
                if (t > 0 && u >= -1e-6 && u <= 1 + 1e-6) distance = std::min(distance, t);
            }
            require(std::isfinite(distance) && distance > priorDistance, "Larger setting failed to extend actual Sunny forward coverage");
            const auto edge = project({ex + distance * dx, nativeMedian(water.drawData), ez + distance * dz, 1});
            const double gap = (opticalY - edge[1] / edge[3]) * 360;
            require(edge[3] > 0 && gap > 0 && gap < priorGap, "Finite edge did not approach the fixed optical horizon");
            require(edge[2] / edge[3] < 1.0, "Forward water edge exceeded native far clip");
            std::printf("  mode=%u forward_distance=%.6f gap720=%.6f native_ndc_z=%.9f\n", mode, distance, gap, edge[2] / edge[3]);
            priorDistance = distance; priorGap = gap; ++scenarios;
        }
    }
    wr64::camera_fov::set_extra_degrees(0);
}
extern "C" void* wr64_test_address(uint8_t* r, uint64_t address, unsigned bytes, const char*, int) {
    const auto a = uint32_t(address);
    require(a >= 0x80000000 && a <= 0x80800000 - bytes && !(a & (bytes - 1)), "Native camera memory bounds");
    return r + (a & 0x7FFFFF);
}
extern "C" void _nsqrtf(uint8_t*, recomp_context* ctx) { ctx->f0.fl = std::sqrt(ctx->f12.fl); }
int main(int argc, char** argv) {
    try {
        require(argc >= 2, "Provide native_water.txt and optional archived Sunny RAM captures");
        Projection originalProjection;
        const auto original = load(argv[1], originalProjection);
        scopeTests();
        for (float strength : {0.0f, 0.5f, 1.0f}) {
            current::fixtureStrength = baseline::fixtureStrength = strength;
            auto old = original; auto oldProjection = originalProjection;
            require(baseline::tryAugmentWr64WaterDenseAnnulus(old, oldProjection, 0) == baseline::Wr64DenseWaterCallResult::Augmented, "Saved pre-feature baseline rejects archived native water");
            for (uint32_t mode = 0; mode < Modes; ++mode) {
                auto test = original; auto projection = originalProjection;
                test.wr64FarWaterDistanceMode = mode;
                setWr64FarWaterDistanceMode((mode + 1) % Modes);
                require(current::tryAugmentWr64WaterDenseAnnulus(test, projection, 0) == current::Wr64DenseWaterCallResult::Augmented, "Supported extent rejected archived native water");
                checkShape(test.drawData, projection, mode);
                sameNative(test.drawData, old.drawData); sameNonGeometry(test.drawData, old.drawData); sameCall(projection, oldProjection);
                prefixEqual(test.drawData.posFloats, old.drawData.posFloats, (VertexCount + 72) * 3, "First transition ring or primary field changed");
                prefixEqual(test.drawData.velFloats, old.drawData.velFloats, (VertexCount + 72) * 3, "First transition ring velocity changed");
                if (mode < 3) {
                    auto prior = original; auto priorProjection = originalProjection;
                    prior.wr64FarWaterDistanceMode = mode; previous::fixtureStrength = strength;
                    require(previous::tryAugmentWr64WaterDenseAnnulus(prior, priorProjection, 0) == previous::Wr64DenseWaterCallResult::Augmented,
                        "Validated prior distance mode rejected native water");
                    sameData(test.drawData, prior.drawData); sameCall(projection, priorProjection);
                    require(test.drawData.wr64FarWaterDistanceMode == prior.drawData.wr64FarWaterDistanceMode, "Validated committed mode changed");
                }
                if (mode == 0) {
                    sameData(test.drawData, old.drawData);
                    auto finalized = test; auto oldFinalized = old;
                    require(current::finalizeWr64WaterDenseAnnulus(finalized.drawData, test.drawData, 965).passed &&
                        baseline::finalizeWr64WaterDenseAnnulus(oldFinalized.drawData, old.drawData, 965).passed, "Original finalization failed");
                    sameData(finalized.drawData, oldFinalized.drawData);
                }
                else require(!same(test.drawData.posFloats, old.drawData.posFloats), "Non-Original positive control did not extend coverage");
                ++scenarios;
            }
        }
        // Every mode transition includes camera translation and a different native tide.
        for (float strength : {0.0f, 0.5f, 1.0f}) for (uint32_t previousMode = 0; previousMode < Modes; ++previousMode)
        for (uint32_t currentMode = 0; currentMode < Modes; ++currentMode) {
            current::fixtureStrength = strength;
            auto previous = shifted(original, 0, -2, 0, false);
            auto currentFrame = shifted(original, 32, 3, -16, true);
            previous.wr64FarWaterDistanceMode = previousMode; currentFrame.wr64FarWaterDistanceMode = currentMode;
            auto previousProjection = originalProjection, currentProjection = originalProjection;
            require(current::tryAugmentWr64WaterDenseAnnulus(previous, previousProjection, 0) == current::Wr64DenseWaterCallResult::Augmented &&
                current::tryAugmentWr64WaterDenseAnnulus(currentFrame, currentProjection, 0) == current::Wr64DenseWaterCallResult::Augmented, "Transition endpoint augmentation failed");
            const auto before = currentFrame.drawData, previousBefore = previous.drawData;
            setWr64FarWaterDistanceMode((currentMode + 2) % Modes);
            currentFrame.wr64FarWaterDistanceMode = (currentMode + 1) % Modes;
            const auto finalized = current::finalizeWr64WaterDenseAnnulus(currentFrame.drawData, previous.drawData, 966);
            require(finalized.passed && !finalized.initialized, "Captured mode transition failed temporal finalization");
            sameNative(currentFrame.drawData, before); sameData(previous.drawData, previousBefore);
            require(currentFrame.drawData.wr64FarWaterDistanceMode == currentMode, "Finalizer read live UI/workload state instead of committed draw");
            for (uint32_t v = VertexCount; v < VertexCount + 288; ++v) for (uint32_t c = 0; c < 3; ++c)
                require(std::fabs(double(currentFrame.drawData.posFloats[v * 3 + c]) - currentFrame.drawData.velFloats[v * 3 + c] - previous.drawData.posFloats[v * 3 + c]) < 0.02,
                    "Interpolated previous endpoint lost its previous extent or tide");
            fractionalWinding(currentFrame.drawData); ++scenarios;
        }
        // Unsafe native geometry retains the whole original sheet and its stock fan.
        std::map<uint32_t, uint32_t> seen;
        uint32_t duplicate = UINT32_MAX;
        for (uint32_t v = WaterBase; v < WaterBase + 488; ++v)
            if (!seen.emplace(original.drawData.vertexSegmentedAddresses[v], v).second) duplicate = v;
        require(duplicate != UINT32_MAX, "Real duplicated seam missing");
        for (uint32_t mode = 0; mode < Modes; ++mode) {
            auto invalid = original; auto invalidProjection = originalProjection;
            invalid.wr64FarWaterDistanceMode = mode;
            invalid.drawData.posFloats[duplicate * 3] += 1;
            const auto snapshot = invalid.drawData;
            require(current::tryAugmentWr64WaterDenseAnnulus(invalid, invalidProjection, 0) == current::Wr64DenseWaterCallResult::NativeRetained, "Unsafe duplicate source was extended");
            sameData(invalid.drawData, snapshot); sameCall(invalidProjection, originalProjection);
            require(invalid.drawData.wr64FarWaterDistanceMode == 0, "Rejected call committed a distance mode");
            require(!current::finalizeWr64WaterDenseAnnulus(invalid.drawData, original.drawData, 967).attempted, "Native fallback tried to finalize nonexistent rings");
            auto next = original; auto nextProjection = originalProjection; next.wr64FarWaterDistanceMode = mode;
            require(current::tryAugmentWr64WaterDenseAnnulus(next, nextProjection, 0) == current::Wr64DenseWaterCallResult::Augmented, "Valid frame did not recover after native fallback");
            const auto finalized = current::finalizeWr64WaterDenseAnnulus(next.drawData, invalid.drawData, 968);
            require(finalized.passed && finalized.initialized, "First valid rings did not initialize at their current extent");
            fractionalWinding(next.drawData); ++scenarios;
        }
        for (int argument = 2; argument < argc; ++argument) horizon(original, originalProjection, argv[argument]);
        std::printf("PASS: %u flat-water scenarios, %zu assertions; Original/prior-mode byte parity, fixed topology, neutral rings, native/scope preservation, all36 mode transitions, tide/motion, fractional winding and archived horizon coverage.\n", scenarios, checks);
        return 0;
    } catch (const std::exception& error) {
        std::fprintf(stderr, "FAIL after %zu assertions: %s\n", checks, error.what()); return 1;
    }
}
