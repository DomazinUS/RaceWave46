// CPU-only capture guard regression. No GPU, ROM, windows or game process.
#include <cstdint>
#include <cstdio>
#include <limits>
#include "../../lib/rt64/src/common/rt64_wr64_rt_sky.h"

int main() {
    using namespace RT64;
    unsigned checks = 0, failures = 0;
    const auto expect = [&](bool result, const char *caseName) {
        ++checks;
        if (!result) { ++failures; std::fprintf(stderr, "FAIL: %s\n", caseName); }
    };
    expect(wr64RTSkySignature(6, 0xFC11C223, 0xFF87FFFF, 0x00504240, 0x00882C3F), "captured native sky signature");
    expect(!wr64RTSkySignature(2, 0xFC11C223, 0xFF87FFFF, 0x00504240, 0x00882C3F), "incomplete sky geometry");
    expect(!wr64RTSkySignature(6, 0xFC11C223, 0xFF87FFFE, 0x00504240, 0x00882C3F), "different color combiner");
    expect(!wr64RTSkySignature(6, 0xFC11C223, 0xFF87FFFF, 0x00504241, 0x00882C3F), "different alpha mode");
    expect(!wr64RTSkySignature(6, 0xFC11C223, 0xFF87FFFF, 0x00504240, 0x00802C3F), "different perspective mode");
    // Native DL010103B8 topology, verified from archived RDRAM. The lower
    // plane has the same material and viewport but must not count as a second
    // backdrop candidate before the genuine backdrop is encountered.
    const uint32_t backdropIndices[18] = {0, 1, 6, 1, 2, 6, 2, 3, 6, 3, 4, 6, 4, 5, 6, 5, 0, 6};
    uint32_t backdropSources[18] = {};
    auto fillSources = [&](uint32_t base) {
        for (uint32_t i = 0; i < 18; ++i) backdropSources[i] = base + backdropIndices[i] * 16;
    };
    fillSources(0x06000000);
    expect(!wr64RTBackdropSourceFamily(backdropSources, 18), "earlier same-material lower plane excluded from backdrop family");
    fillSources(0x060000E0);
    expect(wr64RTBackdropSourceFamily(backdropSources, 18), "captured P1 backdrop producer block");
    fillSources(0x06000150);
    expect(wr64RTBackdropSourceFamily(backdropSources, 18), "native P2 backdrop producer block");
    backdropSources[0] = 0x060000E0;
    expect(!wr64RTBackdropSourceFamily(backdropSources, 18), "mixed player source blocks rejected");
    fillSources(0x060000E0);
    ++backdropSources[0];
    expect(!wr64RTBackdropSourceFamily(backdropSources, 18), "misaligned producer vertex rejected");
    fillSources(0x060000E0);
    for (uint32_t &source : backdropSources) if (source == 0x06000140) source = 0x06000130;
    expect(!wr64RTBackdropSourceFamily(backdropSources, 18), "missing apex cannot count as complete family");
    expect(!wr64RTBackdropSourceFamily(nullptr, 18), "missing provenance rejected");
    expect(!wr64RTBackdropSourceFamily(backdropSources, 17), "partial triangle stream rejected");
    // Native 320x240 coordinates, stored as quarter pixels. The preview
    // rectangle has the same material but must never become the environment.
    expect(wr64RTSkyFullCoverage(0, 0, 1280, 960, 0, 0, 1280, 960), "full native frame");
    expect(wr64RTSkyFullCoverage(8, 8, 1272, 952, 0, 0, 1280, 960), "inclusive-edge allowance");
    expect(!wr64RTSkyFullCoverage(512, 384, 1184, 864, 0, 0, 1280, 960), "watercraft preview inset");
    expect(!wr64RTSkyFullCoverage(0, 0, 1280, 480, 0, 0, 1280, 960), "horizontal split viewport");
    expect(!wr64RTSkyFullCoverage(0, 0, 640, 960, 0, 0, 1280, 960), "vertical split viewport");
    expect(wr64RTSkyFullCoverage(-640, 0, 1920, 960, 0, 0, 1280, 960), "expanded aspect coverage");
    expect(!wr64RTSkyFullCoverage(0, 0, 0, 960, 0, 0, 1280, 960), "empty draw rectangle");
    expect(!wr64RTSkyFullCoverage(0, 0, 1280, 960, 0, 0, 0, 960), "empty framebuffer rectangle");
    expect(wr64RTSkyFullCoverage(160, 120, 1440, 1080, 160, 120, 1440, 1080), "offset full framebuffer");
    const int32_t hi = std::numeric_limits<int32_t>::max(), lo = std::numeric_limits<int32_t>::min();
    expect(wr64RTSkyFullCoverage(lo, lo, hi, hi, lo, lo, hi, hi), "signed limits without overflow");
    expect(!wr64RTSkyFullCoverage(hi - 4, lo, hi, hi, lo, lo, hi, hi), "extreme inset cannot wrap into coverage");
    std::printf("%s: %u native-sky capture guard checks.\n", failures ? "FAIL" : "PASS", checks);
    return failures ? 1 : 0;
}
