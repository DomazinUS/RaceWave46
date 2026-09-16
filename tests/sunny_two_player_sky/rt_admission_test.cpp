// Reuse actual native setup/producer extraction and ROM loading from the
// established fixture. The additional checks interpret its emitted commands;
// they do not invent the viewport, clipping or material at each fan.
#define main original_sky_fixture_main
#include "sunny_sky_test.cpp"
#undef main
#include "wr64_rom_patch.hpp"
#include "common/rt64_wr64_rt_view.h"
#include "common/rt64_wr64_rt_sky.h"
#include "common/rt64_wr64_2p_frame.h"
#include <iomanip>

extern "C" void Draw_WaterEffects(uint8_t*, recomp_context*);
extern "C" uint32_t wr64_sunny_detail_water_active(uint8_t*) { return active; }

namespace {
struct NativeCall {
    RT64::WR64RTViewDomain domain;
    uint32_t viewport = 0, projection = 0, ccL = 0, ccH = 0, omL = 0, omH = 0;
    std::vector<uint32_t> sources;
};

// Narrow F3DWAVE command-state decoder. Vertex/triangle fields match
// gbi_f3dwave.cpp; viewport words match RSP::setViewport; OtherMode writes
// match RSP::setOtherModeH/L. The scissor correction and RT predicates are
// the actual production functions. No clipping/projection reconstruction or
// GPU image is claimed by this command-admission fixture.
struct Decoder {
    Ram &ram;
    NativeCall state;
    std::array<uint32_t, 128> vertices{};
    std::vector<NativeCall> calls;
    unsigned commands = 0;
    explicit Decoder(Ram &ram_, uint32_t initialDither) : ram(ram_) {
        // RSP::reset initializes 080CFF; earlier native draws can select the
        // other RGB-dither value. Exercise both inherited settings explicitly.
        state.omH = (0x080CFFU & ~0xC0U) | initialDither;
    }
    void flush() {
        if (state.sources.empty()) return;
        calls.push_back(state);
        state.sources.clear();
    }
    void command(uint32_t a, uint32_t b, unsigned depth = 0) {
        require(++commands < 12000 && depth < 12, "bounded native display-list traversal");
        const unsigned op = a >> 24;
        if (op != 0xBF && op != 0xB1 && op != 0xB5) flush();
        if (op == 0x03 && ((a >> 16) & 255) == 0x80) {
            require(b >= 0x80000000 && b < 0x80800000 - 16, "native viewport pointer bounds");
            state.viewport = b;
            auto *rdram = ram.data();
            for (unsigned i = 0; i < 3; ++i) {
                state.domain.scale[i] = float(MEM_H(i * 2, gpr(S32(b)))) / (i == 2 ? 1023.0f : 4.0f);
                state.domain.translate[i] = float(MEM_H(8 + i * 2, gpr(S32(b)))) / (i == 2 ? 1023.0f : 4.0f);
            }
        }
        else if (op == 0xED) {
            auto &s = state.domain.scissor;
            s[0] = (a >> 12) & 4095; s[1] = a & 4095;
            s[2] = (b >> 12) & 4095; s[3] = b & 4095;
            RT64::wr64TwoPFrameCorrectScissor(s[0], s[1], s[2], s[3]);
        }
        else if (op == 0x01 && ((a >> 16) & 1)) {
            state.projection = b;
            state.domain.perspective = true;
        }
        else if (op == 0xBA || op == 0xB9) {
            const unsigned size = a & 255, shift = (a >> 8) & 255;
            require(size <= 32 && shift < 32 && size + shift <= 32, "othermode field bounds");
            const uint32_t mask = uint32_t(((uint64_t(1) << size) - 1) << shift);
            auto &word = op == 0xBA ? state.omH : state.omL;
            word = (word & ~mask) | b;
        }
        else if (op == 0xFC) { state.ccL = a; state.ccH = b; }
        else if (op == 0x04) {
            const unsigned count = (a >> 9) & 127, first = ((a >> 16) & 255) / 5;
            require(count && first + count <= vertices.size(), "native F3DWAVE vertex slots");
            for (unsigned i = 0; i < count; ++i) vertices[first + i] = b + i * 16;
        }
        else if (op == 0xBF || op == 0xB1) {
            auto tri = [&](uint32_t w) {
                for (unsigned shift : {16u, 8u, 0u}) {
                    const unsigned v = ((w >> shift) & 255) / 5;
                    require(v < vertices.size() && vertices[v] != 0, "triangle consumes loaded native vertex");
                    state.sources.push_back(vertices[v]);
                }
            };
            if (op == 0xB1) tri(a);
            tri(b);
        }
        else if (op == 0xB5) {
            const unsigned quad[4] = {(b >> 24) / 5, ((b >> 16) & 255) / 5,
                ((b >> 8) & 255) / 5, (b & 255) / 5};
            for (unsigned corner : {0u,1u,2u,0u,2u,3u}) {
                const unsigned v = quad[corner];
                require(v < vertices.size() && vertices[v] != 0, "quad consumes loaded native vertex");
                state.sources.push_back(vertices[v]);
            }
        }
        else if (op == 0x06) {
            require((b >> 24) == 1, "fixture only follows resident native segment-one lists");
            unsigned offset = 0xF6090 + (b & 0xFFFFFF);
            while (true) {
                const uint32_t x = be(offset), y = be(offset + 4);
                command(x, y, depth + 1);
                offset += 8;
                if ((x >> 24) == 0xB8) break;
            }
        }
    }
    void decode(const std::vector<Command> &input) {
        for (auto [a,b] : input) command(a,b);
        flush();
    }
};

std::vector<Command> nativeWater(Ram &ram) {
    recomp_context ctx{}; ctx.f_odd = &ctx.f0.u32h; ctx.r29 = S32(Stack); ctx.r4 = S32(Gp);
    Draw_WaterEffects(ram.data(), &ctx);
    require(uint32_t(ctx.r2) > Gp && uint32_t(ctx.r2) <= Gp + 4096, "native water list bounds");
    std::vector<Command> commands;
    for (uint32_t at = Gp; at < uint32_t(ctx.r2); at += 8)
        commands.emplace_back(get(ram.data(), at), get(ram.data(), at + 4));
    return commands;
}

void checkAdmission(unsigned course, unsigned view, unsigned buffer, uint32_t inheritedDither, unsigned sea = 0) {
    currentCourse = int(course);
    active = true;
    auto ram = initial(2, int(view), int(buffer), int(sea), int(course));
    auto emitted = run(ram, true);
    Decoder decoder(ram, inheritedDither);
    decoder.decode(emitted);
    unsigned clouds = 0, backdrops = 0;
    RT64::WR64RTViewDomain nativeDomain;
    for (const auto &call : decoder.calls) {
        const unsigned triangles = unsigned(call.sources.size() / 3);
        const bool cloud = RT64::wr64RTSkySignature(triangles,call.ccL,call.ccH,call.omL,call.omH);
        const bool backdrop = RT64::wr64RTBackdropSignature(triangles,call.ccL,call.ccH,call.omL,call.omH) &&
            RT64::wr64RTBackdropSourceFamily(call.sources.data(),unsigned(call.sources.size()));
        if (!cloud && !backdrop) continue;
        require(RT64::wr64RTNativeRaceView(call.domain) == view + 1, "actual native sky call accepted by correct RT view");
        require(call.viewport == 0x800DA8D0 + view * 16, "actual sky viewport pointer belongs to current player");
        require(call.projection != 0, "actual sky has native projection load");
        const uint32_t base = (cloud ? 0x060001C0 : 0x060000E0) + view * 0x70;
        for (uint32_t source : call.sources)
            require(source >= base && source < base + 112, "actual fan uses correct player source block");
        auto other = call.domain;
        other.translate[1] = view ? 60.0f : 180.0f;
        require(RT64::wr64RTNativeRaceView(other) == 0, "other player camera cannot use this actual scissor");
        std::cout << "native course=" << course << " P" << view + 1 << ' ' << (cloud ? "cloud" : "backdrop")
            << " vp=" << std::hex << call.viewport << " projection=" << call.projection
            << " othermode=" << call.omL << '/' << call.omH << std::dec
            << " viewport=" << call.domain.scale[0] << ',' << call.domain.scale[1]
            << '/' << call.domain.translate[0] << ',' << call.domain.translate[1]
            << " scissor=" << call.domain.scissor[0] << ',' << call.domain.scissor[1]
            << ',' << call.domain.scissor[2] << ',' << call.domain.scissor[3] << '\n';
        nativeDomain = call.domain;
        if (cloud) ++clouds; else ++backdrops;
    }
    require(clouds == (sea == 0 ? 1 : 0) && backdrops == 1, "native sky sea-mode exclusions retain one backdrop per view");

    decoder.calls.clear();
    decoder.decode(nativeWater(ram));
    unsigned waterTriangles = 0;
    const uint32_t base = (view && sea != 1) ? 0x030170D8 : 0x03013D68;
    for (const auto &call : decoder.calls) {
        require(!call.sources.empty() && std::all_of(call.sources.begin(), call.sources.end(),
            [&](uint32_t source) { return source >= base && source < (sea == 1 ? 0x030170D8 : base + 337 * 16) && (source-base)%16 == 0; }),
            "every actual water triangle comes from the selected native source block");
        require(RT64::wr64RTNativeRaceView(call.domain) == view + 1,
            "actual native water list retains own viewport/scissor");
        require(RT64::wr64RTSameRaceView(call.domain, nativeDomain), "native sky/water share RT ownership");
        waterTriangles += unsigned(call.sources.size() / 3);
        if (waterTriangles == unsigned(call.sources.size()/3)) std::cout << "water material sea=" << sea << " cc=" << std::hex << call.ccL << '/' << call.ccH << " om=" << call.omL << '/' << call.omH << std::dec << '\n';
        require(call.ccL == 0xFCFFFFFF && call.ccH == (course == 4 && sea != 1 ? 0xFFFCF238 : 0xFFFCF279), "native enhanced water combiner retained");
        require(call.omL == (course == 4 && sea != 1 ? 0xC81049D8 : 0x005049D8),
            "native course-specific fogged/translucent water mode retained");
        require((call.omH & ~0xC0u) == (course == 4 && sea != 1 ? 0x00182C3F : 0x00082C3F), "native water texture semantics retained");
    }
    require(waterTriangles == (sea == 1 ? 1548 : 612), "complete actual per-player native wave list classified");
    std::cout << "native course=" << course << " P" << view + 1 << " sea=" << sea << " water triangles=" << waterTriangles << '\n';
}
}

int main(int argc, char **argv) {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    require(argc == 2, "private ROM path required");
    std::ifstream input(argv[1], std::ios::binary);
    rom.assign(std::istreambuf_iterator<char>(input), {});
    require(wr64::rom_patch::apply_if_unpatched(rom), "actual shipped in-memory ROM patch applied");
    for (unsigned course = 0; course <= 8; ++course)
        for (unsigned view : {0u,1u}) for (unsigned buffer : {0u,1u})
            for (uint32_t dither : {0u,0xC0u}) checkAdmission(course,view,buffer,dither);
    for (unsigned course = 0; course <= 8; ++course)
        for (unsigned view : {0u,1u}) for (unsigned sea : {1u,2u})
            checkAdmission(course,view,view,view ? 0xC0u : 0u,sea);
    std::cout << "PASS native RT admission: 108 actual producer cases, " << checks
        << " assertions, " << accesses << " native memory accesses.\n";
}
