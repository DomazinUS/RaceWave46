#include "wr64_diagnostic_policy.h"
#include "librecomp/helpers.hpp"

#include <charconv>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string_view>

#include "wr64_split_screen.hpp"

namespace {

constexpr s32 kPfsErrNoPack = 1;
constexpr float kNativePerspectiveAspect = 4.0f / 3.0f;
constexpr float kOriginalViewportWidth = 320.0f;
constexpr float kOriginalViewportHeight = 240.0f;

uint64_t g_sun_trace_frame = 0;
uint32_t g_sun_trace_course = 0;
uint32_t g_sun_trace_output = 0;
bool g_sun_trace_active = false;

bool sun_complete_trace_enabled() {
    static const bool enabled = []() {
        const char* value = WR64_DIAGNOSTIC_ENV(std::getenv("WR64_SUN_COMPLETE_TRACE"));
        return (value != nullptr) && (value[0] == '1') && (value[1] == '\0');
    }();
    return enabled;
}

float guest_float(uint8_t* rdram, uint32_t address) {
    const gpr guest_address = static_cast<gpr>(static_cast<int64_t>(static_cast<int32_t>(address)));
    const uint32_t bits = MEM_W(0, guest_address);
    float value;
    std::memcpy(&value, &bits, sizeof(value));
    return value;
}

double guest_double(uint8_t* rdram, uint32_t address) {
    const gpr guest_address = static_cast<gpr>(static_cast<int64_t>(static_cast<int32_t>(address)));
    const uint64_t bits = LD(guest_address, 0);
    double value;
    std::memcpy(&value, &bits, sizeof(value));
    return value;
}

void print_guest_matrix(uint8_t* rdram, uint32_t address, const char* name) {
    std::cout << " " << name << "=[";
    for (uint32_t row = 0; row < 4; row++) {
        if (row != 0) {
            std::cout << ";";
        }
        for (uint32_t col = 0; col < 4; col++) {
            if (col != 0) {
                std::cout << ",";
            }
            std::cout << guest_float(rdram, address + ((row * 4 + col) * 4));
        }
    }
    std::cout << "]";
}

float parse_experimental_3d_aspect() {
    const char* raw_value = std::getenv("WR64_EXPERIMENTAL_3D_ASPECT");
    if ((raw_value == nullptr) || (*raw_value == '\0')) {
        return 0.0f;
    }

    const std::string_view value{raw_value};
    if (value == "16:9") {
        return 16.0f / 9.0f;
    }
    if (value == "21:9") {
        return 21.0f / 9.0f;
    }
    if (value == "32:9") {
        return 32.0f / 9.0f;
    }

    float parsed = 0.0f;
    const char* begin = value.data();
    const char* end = begin + value.size();
    const auto result = std::from_chars(begin, end, parsed);
    if ((result.ec != std::errc{}) || (result.ptr != end) ||
        !std::isfinite(parsed) || (parsed <= kNativePerspectiveAspect)) {
        std::cerr << "[widescreen] ignoring invalid WR64_EXPERIMENTAL_3D_ASPECT='"
                  << value << "'\n";
        return 0.0f;
    }

    return parsed;
}

float experimental_3d_aspect_value() {
    static const float aspect = parse_experimental_3d_aspect();
    return aspect;
}

void return_no_pack(recomp_context* ctx) {
    _return<s32>(ctx, kPfsErrNoPack);
}

} // namespace

extern "C" float wr64_experimental_3d_aspect() {
    return experimental_3d_aspect_value();
}

// Reproduce the existing Glacier Coast giant actor without changing records,
// course selection, reverse mode, or animal data. Only the two championship
// qualification branches consult this opt-in diagnostic.
extern "C" uint32_t wr64_diagnostic_giant_penguin_enabled() {
    static const bool enabled = [] {
        const char* value = WR64_DIAGNOSTIC_ENV(std::getenv("WR64_DIAGNOSTIC_GIANT_PENGUIN"));
        const bool active = value && std::string_view(value) == "1";
        if (active) std::cerr << "[penguin] Glacier Coast qualification diagnostic enabled\n";
        return active;
    }();
    return enabled ? 1U : 0U;
}

extern "C" uint32_t wr64_experimental_viewport_borders() {
    // ★ VALIDATED FIX, COMPILED IN. No environment variable.
    return 1U;
}

extern "C" uint32_t wr64_sun_complete_trace_enabled() {
    return sun_complete_trace_enabled() ? 1U : 0U;
}

extern "C" uint64_t wr64_sun_trace_frame_number() {
    return g_sun_trace_frame;
}

extern "C" uint32_t wr64_sun_trace_course_id() {
    return g_sun_trace_course;
}

extern "C" void wr64_sun_trace_frame(uint32_t course_id) {
    if (!sun_complete_trace_enabled()) {
        return;
    }
    g_sun_trace_frame++;
    g_sun_trace_course = course_id;
}

extern "C" void wr64_sun_trace_begin(float radius, float angle, uint32_t source_bits, uint32_t output_address) {
    if (!sun_complete_trace_enabled() || (output_address != 0x801C4170U)) {
        g_sun_trace_active = false;
        return;
    }
    float source_value;
    std::memcpy(&source_value, &source_bits, sizeof(source_value));
    g_sun_trace_active = true;
    g_sun_trace_output = output_address;
    std::cout << "[sun-complete] frame=" << g_sun_trace_frame
              << " course=" << g_sun_trace_course
              << " stage=begin projection_source=func_8008962C"
              << " matrix_source=view:D_801518B8[camera]+0xE008,projection:D_801518B8[camera]+0xE088"
              << " spherical_world_input={radius:" << radius << ",angle:" << angle
              << ",course_source:" << source_value << "} output=0x" << std::hex
              << output_address << std::dec << std::endl;
}

extern "C" void wr64_sun_trace_view(uint8_t* rdram, uint32_t stack_address,
                                      double view_x, double view_y, double view_z) {
    if (!g_sun_trace_active) {
        return;
    }
    const double world_x = guest_double(rdram, stack_address + 0x80);
    const double world_z = guest_double(rdram, stack_address + 0x70);
    std::cout << "[sun-complete] frame=" << g_sun_trace_frame
              << " course=" << g_sun_trace_course
              << " stage=view world={" << world_x << ",0," << world_z << ",1}"
              << " view={" << view_x << "," << view_y << "," << view_z << ",1}";
    print_guest_matrix(rdram, stack_address + 0x90, "view_matrix");
    print_guest_matrix(rdram, stack_address + 0xD0, "projection_matrix");
    std::cout << std::endl;
}

extern "C" void wr64_sun_trace_clip(uint8_t* rdram, uint32_t stack_address, double clip_w) {
    if (!g_sun_trace_active) {
        return;
    }
    const double clip_x = guest_double(rdram, stack_address + 0x80);
    const double clip_y = guest_double(rdram, stack_address + 0x78);
    const double clip_z = guest_double(rdram, stack_address + 0x70);
    const double ndc_x = clip_x / clip_w;
    const double ndc_y = clip_y / clip_w;
    const double ndc_z = clip_z / clip_w;
    const float aspect = experimental_3d_aspect_value();
    const double expanded_width = (aspect > 0.0f) ? (kOriginalViewportHeight * aspect) : kOriginalViewportWidth;
    const double expanded_x = (expanded_width * 0.5) + ndc_x * (expanded_width * 0.5);
    const double expanded_y = (kOriginalViewportHeight * 0.5) - ndc_y * (kOriginalViewportHeight * 0.5);
    std::cout << "[sun-complete] frame=" << g_sun_trace_frame
              << " course=" << g_sun_trace_course
              << " stage=clip clip={" << clip_x << "," << clip_y << "," << clip_z << "," << clip_w << "}"
              << " ndc={" << ndc_x << "," << ndc_y << "," << ndc_z << "}"
              << " original_viewport={0,0,320,240} expanded_viewport={0,0," << expanded_width << ",240}"
              << " expanded_screen_from_ndc={" << expanded_x << "," << expanded_y << "}"
              << std::endl;
}

extern "C" void wr64_sun_trace_result(uint8_t* rdram, uint32_t output_address) {
    if (!g_sun_trace_active || (output_address != g_sun_trace_output)) {
        return;
    }
    const float x = guest_float(rdram, output_address + 0x0);
    const float y = guest_float(rdram, output_address + 0x4);
    const float depth = guest_float(rdram, output_address + 0x8);
    const float half_width = guest_float(rdram, output_address + 0xC);
    const float half_height = guest_float(rdram, output_address + 0x10);
    const float visibility_depth = guest_float(rdram, output_address + 0x14);
    std::cout << "[sun-complete] frame=" << g_sun_trace_frame
              << " course=" << g_sun_trace_course
              << " stage=result original_screen={" << x << "," << y << "}"
              << " sprite_half_size={" << half_width << "," << half_height << "}"
              << " projected_depth=" << depth
              << " visibility_depth=" << visibility_depth
              << " visibility_result=" << ((visibility_depth >= 0.0f) ? "visible" : "rejected")
              << std::endl;
    g_sun_trace_active = false;
}

// N64ModernRuntime implements the high-level Controller Pak API as an absent
// accessory. Wave Race's libultra version additionally references these entry
// points, so keep the same no-pack behavior for the missing variants.
extern "C" void osPfsIsPlug_recomp(uint8_t* rdram, recomp_context* ctx) {
    PTR(u8) pattern = _arg<1, PTR(u8)>(rdram, ctx);
    MEM_B(0, pattern) = 0;
    _return<s32>(ctx, 0);
}

extern "C" void osPfsInit_recomp(uint8_t*, recomp_context* ctx) {
    return_no_pack(ctx);
}

extern "C" void __osPfsSelectBank_recomp(uint8_t*, recomp_context* ctx) {
    return_no_pack(ctx);
}

extern "C" void __osContRamRead_recomp(uint8_t*, recomp_context* ctx) {
    return_no_pack(ctx);
}

extern "C" void __osContRamWrite_recomp(uint8_t*, recomp_context* ctx) {
    return_no_pack(ctx);
}

// These debug-server routines are not expected during normal execution. A
// zero cause value accurately reports that no emulated debug interrupt exists.
extern "C" void __osGetCause_recomp(uint8_t*, recomp_context* ctx) {
    _return<u32>(ctx, 0);
}

namespace {

constexpr uint32_t kWr64CourseTransformIdBase = 0x57524300U;

void write_guest_gfx_command(uint8_t* rdram, uint32_t gfx_address,
                             uint32_t word0, uint32_t word1) {
    const gpr guest_address = static_cast<gpr>(
        static_cast<int64_t>(static_cast<int32_t>(gfx_address)));
    MEM_W(0, guest_address) = word0;
    MEM_W(4, guest_address) = word1;
}

} // namespace

// Bracket only Wave Race's course/backdrop pass. These are the current-source
// equivalent of the validated gEXMatrixGroupDecomposedVerts wrapper: no base
// game function is replaced and no water, rider, HUD, or menu pass is grouped.
extern "C" uint32_t wr64_course_group_begin(uint8_t* rdram,
                                             uint32_t gfx_address,
                                             uint32_t viewport_index) {
    // Capture split layout and native race state in this list before either
    // camera renders. Horizontal/default submissions retain their exact bytes.
    gfx_address = wr64_split_screen_frame(rdram, gfx_address);
    // Enable RT64 extended commands for this display list. Wave Race uses the
    // F3D/F3DEX G_SPNOOP opcode (0x00) for the RT64 hook command.
    write_guest_gfx_command(rdram, gfx_address + 0,
                            0x00525464U, 0x10000064U);

    // gEXMatrixGroupDecomposedVerts expands to two commands. Interpolate the
    // complete decomposed matrix plus generated vertices, tiles, texture
    // coordinates, and atmospheric look-at state in original linear order.
    constexpr uint32_t componentInterpolate = 1U;
    constexpr uint32_t lookAtAuto = 2U;
    constexpr uint32_t flags =
        (1U << 0) |                         // push
        (1U << 2) |                         // decomposed interpolation
        (componentInterpolate << 3) |       // position
        (componentInterpolate << 5) |       // rotation
        (componentInterpolate << 7) |       // scale
        (componentInterpolate << 9) |       // skew
        (componentInterpolate << 11) |      // perspective
        (componentInterpolate << 13) |      // generated vertices
        (componentInterpolate << 15) |      // tiles
        (componentInterpolate << 22) |      // texture coordinates
        (lookAtAuto << 24);                 // atmospheric look-at state

    write_guest_gfx_command(rdram, gfx_address + 8,
                            0x6400000CU,
                            kWr64CourseTransformIdBase + (viewport_index & 0xFFU));
    write_guest_gfx_command(rdram, gfx_address + 16, flags, 0U);
    return gfx_address + 24;
}

extern "C" uint32_t wr64_course_group_end(uint8_t* rdram,
                                           uint32_t gfx_address) {
    // gEXPopMatrixGroup(..., G_MTX_MODELVIEW), count 1.
    write_guest_gfx_command(rdram, gfx_address,
                            0x6400000DU, 0x00000001U);
    return gfx_address + 8;
}
