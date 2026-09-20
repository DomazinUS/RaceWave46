#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4201)
#endif
#include "recomp.h"
#ifdef _MSC_VER
#pragma warning(pop)
#include <crtdbg.h>
#endif
#include "common/rt64_wr64_rt_shadow.h"
#include <bit>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

extern "C" void func_80089E24(uint8_t*, recomp_context*);
static unsigned checks = 0, entries = 0, points = 0, matrixCalls = 0;
static std::array<float, 16> view{}, projection{};
static std::array<double, 2> nativePoint{};
static void require(bool value, const char* message) {
    ++checks;
    if (!value) { std::cerr << "FAIL " << message << '\n'; std::exit(1); }
}
// Keep ordinary native camera selection and angular/screen culls. The
// production shadow reader itself has no dependency on these adapter stubs.
extern "C" uint32_t wr64_two_player_celestial_camera_address(uint8_t*, uint32_t address) { return address; }
extern "C" int32_t wr64_sun_right_exit_probe(uint32_t, int32_t, float) { return 0; }
extern "C" int32_t wr64_sun_right_exit_keep(uint32_t, uint32_t) { return 0; }
extern "C" int32_t wr64_sun_dolphin_exit_keep(uint32_t, uint32_t) { return 0; }
extern "C" float wr64_sun_half_extension() { return 0; }
extern "C" float wr64_sun_record_window_limit() { return 1000000; }
extern "C" void wr64_test_native_enter(uint8_t*, recomp_context* ctx) {
    ++entries;
    require(ctx->f12.fl == 2000 && ctx->f14.fl == 5, "actual Dolphin caller supplies distance 2000 and angle 5");
    require(std::bit_cast<float>(uint32_t(ctx->r6)) == 120, "actual Dolphin caller supplies authored pixel height 120");
    require(uint32_t(ctx->r7) == 0x801C4170, "actual Dolphin caller selects its main disk record");
}
extern "C" void wr64_test_native_point(uint8_t* rdram, recomp_context* ctx) {
    ++points;
    nativePoint = {std::bit_cast<double>(LD(ctx->r29, 0x80)), std::bit_cast<double>(LD(ctx->r29, 0x70))};
    require(ctx->f14.d == 0, "native world point uses Y zero before its later screen-space height offset");
}
extern "C" void SysUtils_MtxToMtxF(uint8_t* rdram, recomp_context* ctx) {
    const uint32_t address = uint32_t(ctx->r4);
    const bool isProjection = address == 0x8040E008 || address == 0x8040E048;
    require(isProjection || address == 0x8040E088 || address == 0x8040E0C8, "native camera matrix address");
    const auto& matrix = isProjection ? projection : view;
    for (uint32_t i = 0; i < 16; ++i) MEM_W(i * 4, ctx->r5) = std::bit_cast<uint32_t>(matrix[i]);
    ++matrixCalls;
}
struct Fixture {
    std::vector<uint8_t> ram = std::vector<uint8_t>(0x800000);
    void word(uint32_t a, uint32_t value) { std::memcpy(ram.data() + (a & 0x7fffff), &value, 4); }
    void real(uint32_t a, float value) { word(a, std::bit_cast<uint32_t>(value)); }
    float get(uint32_t a) const { float value = 0; std::memcpy(&value, ram.data() + (a & 0x7fffff), 4); return value; }
    explicit Fixture(const std::vector<uint8_t>& archive) {
        // Use only the real native sine table, immutable projector constants,
        // and Dolphin authored light/size/height tables. Cameras are synthetic.
        for (auto range : {std::array<uint32_t, 2>{0x154350, 4096 * 4}, {0xEAAF0, 0xAC}, {0xD9924, 0x150}})
            std::memcpy(ram.data() + range[0], archive.data() + range[0], range[1]);
        word(0x801518B8, 0x80400000);
    }
};
static void camera(float yaw, float pitch, float roll, float fov, const std::array<float, 3>& eye) {
    const float cy = std::cos(yaw), sy = std::sin(yaw), cp = std::cos(pitch), sp = std::sin(pitch);
    const float cr = std::cos(roll), sr = std::sin(roll);
    const std::array<float, 3> forward{cy * cp, sp, sy * cp}, right{sy, 0, -cy}, up{-cy * sp, cp, -sy * sp};
    view.fill(0);
    for (uint32_t i = 0; i < 3; ++i) {
        view[i * 4] = right[i] * cr + up[i] * sr;
        view[i * 4 + 1] = up[i] * cr - right[i] * sr;
        view[i * 4 + 2] = -forward[i];
        view[12] -= eye[i] * view[i * 4]; view[13] -= eye[i] * view[i * 4 + 1]; view[14] -= eye[i] * view[i * 4 + 2];
    }
    view[15] = 1;
    const float focal = 1.0f / std::tan(fov * 3.14159265358979323846f / 360);
    projection.fill(0); projection[0] = focal / (424.0f / 240); projection[5] = focal;
    projection[10] = -1; projection[11] = -1; projection[14] = -2;
}
int main(int argc, char** argv) {
#ifdef _MSC_VER
    _set_error_mode(_OUT_TO_STDERR);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE); _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
#endif
    require(argc == 2, "usage: wr64_dolphin_sun_shadow_test <private rdram.bin>");
    std::ifstream file(argv[1], std::ios::binary);
    const std::vector<uint8_t> archive{std::istreambuf_iterator<char>(file), {}};
    require(archive.size() == 0x800000, "private archive is exactly eight MiB");
    Fixture f(archive);
    require(f.get(0x800D9A10) == -80 && f.get(0x800D9A14) == 80 && f.get(0x800D9A18) == 0,
        "real native Dolphin preset has horizontal magnitude 80, Y 80: retained elevation 45 degrees");
    const auto fixed = RT64::wr64RTShadowReadLight(f.ram.data(), f.ram.size(), 0, 1);
    require(fixed.valid, "real Dolphin lighting snapshot is valid");
    const double lightHorizontal = std::hypot(fixed.toLight[0], fixed.toLight[2]);
    require(std::fabs(lightHorizontal - fixed.toLight[1]) < 1e-7, "retained authored elevation is 45 degrees");
    unsigned calls = 0, observed = 0, culled = 0, screenRecords = 0, oldPresetFailures = 0;
    double maximumBearingError = 0;
    for (uint32_t cameraIndex : {0U, 1U}) for (float yawOffset : {-2.5f, -0.7f, -0.2f, 0.0f, 0.3f, 0.7f, 2.5f})
        for (float pitch : {-0.25f, 0.0f, 0.25f}) for (float roll : {-0.2f, 0.0f, 0.2f})
        for (float translation : {0.0f, 4250.0f}) for (float fov : {45.0f, 60.0f, 75.0f}) {
            const float yaw = 5 * 3.14159265358979323846f / 180 + yawOffset;
            const std::array<float, 3> eye{translation, 41.75f, translation * 0.7f};
            camera(yaw, pitch, roll, fov, eye);
            f.word(0x80223930, cameraIndex);
            const uint32_t cameraBase = 0x80227C80 + cameraIndex * 0x10C;
            f.real(cameraBase + 0xF0, std::cos(yaw)); f.real(cameraBase + 0xF4, std::sin(yaw));
            for (uint32_t i = 0; i < 3; ++i) f.real(cameraBase + 0x4C + i * 4, eye[i]);
            // Ordinary record history, zeroed culls, and corrupt/stale screen
            // coordinates cannot feed back into the world-space light reader.
            for (uint32_t i = 0; i < 6; ++i) f.word(0x801C4170 + i * 4, calls % 2 ? 0x7FC00000 : 0);
            uint8_t* rdram = f.ram.data();
            recomp_context ctx{}; ctx.f_odd = &ctx.f0.u32h; ctx.r29 = static_cast<gpr>(S32(0x80700000));
            const unsigned priorPoints = points;
            func_80089E24(rdram, &ctx);
            require(uint32_t(ctx.r29) == 0x80700000, "native caller and projector restore stack");
            ++calls;
            if (points > priorPoints) {
                ++observed;
                const double x = nativePoint[0] - eye[0], z = nativePoint[1] - eye[2];
                const double nativeHorizontal = std::hypot(x, z);
                require(nativeHorizontal > 1999 && nativeHorizontal < 2001, "native world point retains its authored 2000 radius");
                const double error = std::max(std::fabs(x / nativeHorizontal - fixed.toLight[0] / lightHorizontal),
                    std::fabs(z / nativeHorizontal - fixed.toLight[2] / lightHorizontal));
                maximumBearingError = std::max(maximumBearingError, error);
                require(error < 1e-7, "RT bearing matches actual native caller/projector world point");
                // A point directly below an elevated caster moves opposite
                // toLight in X/Z when the directional ray meets ground Y0.
                const double shadowX = -10.0 * fixed.toLight[0] / fixed.toLight[1];
                const double shadowZ = -10.0 * fixed.toLight[2] / fixed.toLight[1];
                require(shadowX * x + shadowZ * z < 0, "ground shadow extends away from actual native sun");
                require(-x / nativeHorizontal < -0.99, "negative control: old -X preset opposes actual sun");
                ++oldPresetFailures;
            } else {
                ++culled;
                require(f.get(0x801C4184) == -1, "behind-sun cases execute the original native rejection");
            }
            screenRecords += f.get(0x801C4184) >= 0;
            for (uint32_t recordBits : {0U, std::bit_cast<uint32_t>(5.0f), 0x7FC00000U}) {
                f.word(0x801C4174, recordBits); // zero, alleged parked center, NaN
                const auto one = RT64::wr64RTShadowReadLight(rdram, f.ram.size(), 0, 1);
                const auto two = RT64::wr64RTTwoPlayerShadowReadLight(rdram, f.ram.size(), 0, 2, true);
                require(one.valid && two.valid && one.toLight == fixed.toLight && two.toLight == fixed.toLight,
                    "both player readers remain identical across camera, cull, and projected record changes");
                require(one.diffuse == fixed.diffuse && one.ambient == fixed.ambient && two.diffuse == fixed.diffuse && two.ambient == fixed.ambient,
                    "both player readers retain original lighting colors");
            }
        }
    require(entries == calls && points == observed && matrixCalls == observed * 2, "every replay follows the actual native caller and observed matrix path");
    require(observed > 100 && culled > 100 && screenRecords > 100 && oldPresetFailures == observed, "native front/cull cases and previous-direction negative control exercised");
    std::cout << "PASS " << checks << " checks; " << calls << " native caller replays; " << observed
        << " observed native world points; " << culled << " angular culls; " << screenRecords
        << " retained screen records; maximum bearing error " << maximumBearingError
        << "; actual LUT cos=" << f.get(0x80155430) << " sin=" << f.get(0x80154430) << '\n';
}
