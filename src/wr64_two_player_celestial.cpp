#include "wr64_two_player_celestial.hpp"
#include "wr64_sunny_detail.hpp"
#include "recomp.h"

#include <array>
#include <cstring>

extern "C" {
void func_80089E24(uint8_t*, recomp_context*);
void func_80089F28(uint8_t*, recomp_context*);
void func_80089C08(uint8_t*, recomp_context*);
void func_80089DEC(uint8_t*, recomp_context*);
}

namespace {
constexpr uint32_t Records = 0x801C4170;
constexpr uint32_t RecordBytes = 0x288;
struct ProjectionScope {
    uint8_t* rdram = nullptr;
    uint32_t view = 2;
    std::array<uint8_t, RecordBytes> saved{};
};
thread_local ProjectionScope scope;
}

extern "C" uint32_t wr64_two_player_celestial_begin(uint8_t* rdram, recomp_context* ctx) {
    if (!rdram || !ctx || scope.rdram || !wr64_sunny_detail_active(rdram)) return 0;
    const uint32_t course = uint32_t(MEM_W(0, S32(0x800D8170)));
    const uint32_t view = uint32_t(MEM_W(0, S32(0x800DAB2C)));
    if ((course != 0 && course != 2 && course != 6) || view > 1 || MEM_W(0, S32(0x800DAB28)) != 2) return 0;
    // The native graphics pool reserves two projection/view matrix pairs. Keep
    // the same checked pair selection as the existing two-player world draw.
    if (uint32_t(MEM_W(0, S32(0x80223930 + view * 4))) > 1) return 0;
    const uint32_t stack = uint32_t(ctx->r29);
    const uint32_t pool = uint32_t(MEM_W(0, S32(0x801518B8)));
    if (stack < 0x80000400 || stack > 0x80800000 ||
        pool < 0x80000000 || pool > 0x80800000 - 0xE108) return 0;

    std::memcpy(scope.saved.data(), rdram + (Records & 0x7FFFFF), RecordBytes);
    scope.rdram = rdram;
    scope.view = view;

    // Native projectors write only these screen-space records and stack
    // scratch. They do not advance the game clock, fog or celestial animation.
    // Keep their original addresses so the validated native visibility and
    // texture-coordinate paths continue to operate on the same records.
    recomp_context projection = *ctx;
    projection.f_odd = &projection.f0.u32h;
    if (course == 0 || course == 2) {
        func_80089E24(rdram, &projection);
        func_80089F28(rdram, &projection);
    }
    else {
        func_80089C08(rdram, &projection);
        func_80089DEC(rdram, &projection);
    }
    return 1;
}

extern "C" void wr64_two_player_celestial_end(uint8_t* rdram) {
    if (!rdram || scope.rdram != rdram) return;
    std::memcpy(rdram + (Records & 0x7FFFFF), scope.saved.data(), RecordBytes);
    scope.rdram = nullptr;
    scope.view = 2;
}

extern "C" uint32_t wr64_two_player_celestial_view() {
    return scope.view;
}

extern "C" uint32_t wr64_two_player_celestial_camera_address(uint8_t* rdram, uint32_t original) {
    if (!rdram || scope.rdram != rdram || scope.view > 1 ||
        (original != 0x80223930 && original != 0x80220000)) return original;
    // Redirect the four local load addresses, never the native camera globals.
    return original + scope.view * 4;
}
