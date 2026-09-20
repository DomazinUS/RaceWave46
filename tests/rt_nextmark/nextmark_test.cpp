#include "common/rt64_wr64_rt_nextmark.h"
#include <algorithm>
#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

static unsigned checks = 0;
static void require(bool value, const char *message) {
    ++checks;
    if (!value) { std::cerr << "FAIL " << message << '\n'; std::exit(1); }
}

int main(int argc, char **argv) {
    constexpr uint32_t base = 0x0102CE38;
    const std::array<uint32_t, 6> quad{base, base + 16, base + 32, base, base + 32, base + 48};
    require(RT64::wr64RTIsNextMark(quad), "actual native nextmark quad is an authored marker");
    // RSP's quad expansion can rotate the diagonal or reverse either winding.
    // Exhaust every ordering of two nondegenerate triangles spanning the quad.
    for (unsigned a = 0; a < 4; ++a) for (unsigned b = 0; b < 4; ++b)
    for (unsigned c = 0; c < 4; ++c) for (unsigned d = 0; d < 4; ++d)
    for (unsigned e = 0; e < 4; ++e) for (unsigned f = 0; f < 4; ++f) {
        std::array<unsigned, 6> indices{a, b, c, d, e, f};
        std::array<bool, 4> present{};
        for (auto i : indices) present[i] = true;
        const bool expected = a != b && a != c && b != c && d != e && d != f && e != f &&
            std::all_of(present.begin(), present.end(), [](bool v) { return v; });
        require(RT64::wr64RTIsNextMark({base + a * 16, base + b * 16, base + c * 16,
            base + d * 16, base + e * 16, base + f * 16}) == expected,
            "all quad topologies preserve membership and reject degenerate/incomplete quads");
        for (const uint32_t letter : {0x01029C98u, 0x0102AE48u}) {
            require(RT64::wr64RTIsBuoyLetter({letter+a*16,letter+b*16,letter+c*16,
                letter+d*16,letter+e*16,letter+f*16}) == expected,
                "each complete native L/R quad is identified regardless of winding or diagonal");
        }
    }
    const uint32_t unrelated[] = {0x01029C98, 0x01029CD8, 0x0102AE48, 0x0102AE88,
        0x0102CD18, 0x0102CD48, 0x0102CBF8, 0x0102CC28, 0x0D0121F0, 0, 0xFFFFFFFF,
        base - 16, base + 64, base + 1, base + 0x01000000};
    for (auto source : unrelated) for (size_t corner = 0; corner < quad.size(); ++corner) {
        auto mixed = quad; mixed[corner] = source;
        require(!RT64::wr64RTIsNextMark(mixed), "body, boundary, shore and malformed sources are not nextmark");
    }
    require(!RT64::wr64RTIsBuoyLetter(quad), "floating arrow remains a distinct identity from lettering");
    for (const uint32_t letter : {0x01029C98u, 0x0102AE48u}) {
        const std::array<uint32_t, 6> lettering{letter,letter+16,letter+32,letter,letter+32,letter+48};
        for (const uint32_t wrong : {0x01029CD8u,0x0102AE88u,0x0102CE38u,0x0102CD18u,
            0x0102CD48u,0x0102CBF8u,0x0102CC28u,0x0D0121F0u,0u,0xffffffffu,
            letter-16,letter+64,letter+1,letter+0x01000000u,
            letter==0x01029C98u ? 0x0102AE48u : 0x01029C98u}) {
            for (size_t corner=0;corner<lettering.size();++corner) {
                auto mixed=lettering; mixed[corner]=wrong;
                require(!RT64::wr64RTIsBuoyLetter(mixed),
                    "solid body, boundary buoy, arrow, mixed L/R and invalid sources retain independent shadow policy");
            }
        }
    }
    if (argc > 1) {
        std::ifstream stream(argv[1], std::ios::binary);
        const std::vector<uint8_t> ram((std::istreambuf_iterator<char>(stream)), {});
        require(ram.size() == 0x800000, "archive has original eight MiB RAM layout");
        auto native32 = [&](uint32_t address) {
            require(address <= ram.size() - 4, "native word stays within captured RAM");
            uint32_t result = 0;
            for (unsigned i = 0; i < 4; ++i) result = (result << 8) | ram[(address + i) ^ 3];
            return result;
        };
        const uint32_t segment = native32(0x1CE6B4) & 0xFFFFFF;
        require(native32(segment + 0x2CE78) == 0x0400083F, "native nextmark G_VTX command loads exactly four vertices");
        require(native32(segment + 0x2CE7C) == base, "actual native static source is the claimed segmented block");
        require(native32(segment + 0x2CE80) == 0xB5000000, "actual native primitive is one quad");
        require(native32(segment + 0x2CE84) == 0x0F00050A, "native quad uses all four loaded vertices");
        require(native32(segment + 0x2CE88) == 0xB8000000, "native nextmark list ends immediately after the quad");
        const std::array<std::array<int16_t, 3>, 4> xyz{{{-64,-64,0},{64,-64,0},{64,64,0},{-64,64,0}}};
        for (uint32_t i = 0; i < 4; ++i) for (uint32_t axis = 0; axis < 3; ++axis) {
            const uint32_t a = segment + 0x2CE38 + i * 16 + axis * 2;
            require(a + 1 < ram.size(), "native vertex stays within captured RAM");
            const auto value = int16_t((uint16_t(ram[a ^ 3]) << 8) | ram[(a + 1) ^ 3]);
            require(value == xyz[i][axis], "native marker shape is the documented independent floating quad");
        }
        const std::array<std::array<std::array<int16_t, 3>, 4>, 2> letters{{
            {{{-33,-20,-30},{-44,-20,9},{-44,20,9},{-33,20,-30}}},
            {{{33,20,-30},{44,20,9},{44,-20,9},{33,-20,-30}}}
        }};
        for (unsigned side=0;side<2;++side) {
            const uint32_t source=side ? 0x0102AE48u : 0x01029C98u;
            const uint32_t dl=segment+(side ? 0x2AD68u : 0x29BB8u);
            require(native32(dl)==0x0400083F && native32(dl+4)==source,
                "native letter list loads its own four-vertex source block");
            require(native32(dl+8)==0xB5000000 && native32(dl+12)==0x0F00050A &&
                native32(dl+16)==0xB8000000, "letter list emits exactly one quad, independently of solid body");
            for (uint32_t i=0;i<4;++i) for (uint32_t axis=0;axis<3;++axis) {
                const uint32_t a=segment+(source&0xffffff)+i*16+axis*2;
                require(a+1<ram.size(), "letter vertex stays inside captured RAM");
                const auto value=int16_t((uint16_t(ram[a^3])<<8)|ram[(a+1)^3]);
                require(value==letters[side][i][axis], "native lettering matches separate authored body-face plane");
            }
        }
        std::cout << "Native archived marker verified without embedding game asset bytes.\n";
    }
    std::cout << "PASS " << checks << " checks\n";
}
