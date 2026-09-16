// Offline capture-domain checks. No GPU, ROM, windows, or game process.
#include <cstdint>
#include <cstdio>
#include <limits>
#include <string>

#include "../../lib/rt64/src/common/rt64_wr64_rt_preview.h"

namespace {
RT64::WR64RTPreviewDomain nativePreview(bool widened) {
    // Native 8008FD18 loads viewport 800DA8F0: raw scale (848,480),
    // translation (1320,624). RSP::setViewport divides X/Y by four.
    // The accepted preview patch shifts X by -208 quarter pixels and
    // changes ED424180 to ED284180, leaving the right/bottom word0062835C.
    RT64::WR64RTPreviewDomain domain;
    domain.nativeWaterViewport = RT64::wr64RTMenuWaterViewport(0x800DA8F0);
    domain.scale[0] = 212.0f;
    domain.scale[1] = 120.0f;
    domain.scale[2] = 0.5f;
    domain.translate[0] = widened ? 278.0f : 330.0f;
    domain.translate[1] = 156.0f;
    domain.translate[2] = 0.5f;
    domain.scissor[0] = widened ? 644 : 1060;
    domain.scissor[1] = 384;
    domain.scissor[2] = 1576;
    domain.scissor[3] = 860;
    return domain;
}
}

int main() {
    using namespace RT64;
    unsigned checks = 0, failures = 0;
    const auto expect = [&](bool result, const std::string &label) {
        ++checks;
        if (!result) {
            ++failures;
            std::fprintf(stderr, "FAIL: %s\n", label.c_str());
        }
    };
    expect(wr64RTMenuWaterViewport(0x800DA8F0), "native large live-water viewport");
    for (uint32_t source : {0u, 0x000DA8F0u, 0xA00DA8F0u, 0x800DA8E0u,
            0x800DA900u, 0x800DA8F1u, 0x07001280u, 0x070012F0u,
            std::numeric_limits<uint32_t>::max()}) {
        expect(!wr64RTMenuWaterViewport(source), "unrelated viewport source " + std::to_string(source));
    }

    for (bool widened : {false, true}) {
        const auto water = nativePreview(widened);
        const std::string layout = widened ? "widened" : "original";
        expect(wr64RTSamePreviewDomain(water, water), layout + " native water and native sky share domain");
        expect(!wr64RTSamePreviewDomain(nativePreview(!widened), water), layout + " stale layout rejected");

        auto candidate = water;
        candidate.nativeWaterViewport = false;
        expect(!wr64RTSamePreviewDomain(candidate, water), layout + " same camera and numeric viewport, different source");
        expect(!wr64RTSamePreviewDomain(water, candidate), layout + " water source must also match");
        candidate = water;
        candidate.scale[0] = 31.0f;
        candidate.scale[1] = 19.0f;
        candidate.translate[0] = 60.0f;
        candidate.translate[1] = 68.0f;
        candidate.scissor[0] = 116;
        candidate.scissor[1] = 196;
        candidate.scissor[2] = 364;
        candidate.scissor[3] = 348;
        expect(!wr64RTSamePreviewDomain(candidate, water), layout + " miniature craft pane despite shared camera");

        for (uint32_t axis = 0; axis < 3; ++axis) {
            candidate = water;
            candidate.scale[axis] += 0.001f;
            expect(!wr64RTSamePreviewDomain(candidate, water), layout + " different viewport scale " + std::to_string(axis));
            candidate = water;
            candidate.translate[axis] += 0.001f;
            expect(!wr64RTSamePreviewDomain(candidate, water), layout + " different viewport translation " + std::to_string(axis));
        }
        candidate = water;
        candidate.translate[2] += 0.00005f;
        expect(wr64RTSamePreviewDomain(candidate, water), layout + " finite float comparison allowance");

        for (uint32_t edge = 0; edge < 4; ++edge) {
            for (int32_t delta : {-9, -8, 8, 9}) {
                candidate = water;
                candidate.scissor[edge] += delta;
                const bool same = wr64RTSamePreviewDomain(candidate, water);
                expect(same == (delta >= -8 && delta <= 8), layout + " quarter-pixel scissor tolerance edge " +
                    std::to_string(edge) + " delta " + std::to_string(delta));
            }
        }
        candidate = water;
        candidate.scissor[0] = 0;
        candidate.scissor[1] = 0;
        candidate.scissor[2] = 1696;
        candidate.scissor[3] = 960;
        expect(!wr64RTSamePreviewDomain(candidate, water), layout + " full-frame overlay must not enter inset world");

        for (uint32_t axis = 0; axis < 2; ++axis) {
            candidate = water;
            candidate.scissor[axis + 2] = candidate.scissor[axis];
            expect(!wr64RTSamePreviewDomain(candidate, candidate), layout + " zero rectangle extent " + std::to_string(axis));
            --candidate.scissor[axis + 2];
            expect(!wr64RTSamePreviewDomain(candidate, candidate), layout + " inverted rectangle extent " + std::to_string(axis));
            candidate = water;
            candidate.scale[axis] = 0.0f;
            expect(!wr64RTSamePreviewDomain(candidate, candidate), layout + " zero viewport extent " + std::to_string(axis));
            candidate.scale[axis] = -water.scale[axis];
            expect(!wr64RTSamePreviewDomain(candidate, candidate), layout + " negative viewport extent " + std::to_string(axis));
        }

        for (float invalid : {std::numeric_limits<float>::quiet_NaN(),
                std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity()}) {
            for (uint32_t axis = 0; axis < 3; ++axis) {
                candidate = water;
                candidate.scale[axis] = invalid;
                expect(!wr64RTSamePreviewDomain(candidate, water), layout + " nonfinite candidate scale");
                expect(!wr64RTSamePreviewDomain(water, candidate), layout + " nonfinite water scale");
                candidate = water;
                candidate.translate[axis] = invalid;
                expect(!wr64RTSamePreviewDomain(candidate, water), layout + " nonfinite candidate translation");
                expect(!wr64RTSamePreviewDomain(water, candidate), layout + " nonfinite water translation");
            }
        }
    }

    auto water = nativePreview(true), candidate = water;
    water.scale[0] = 0.00001f;
    candidate = water;
    candidate.scale[0] = 0.0f;
    expect(!wr64RTSamePreviewDomain(candidate, water), "zero candidate width cannot slip through float tolerance");
    water = nativePreview(true);
    water.scale[1] = 0.00001f;
    candidate = water;
    candidate.scale[1] = 0.0f;
    expect(!wr64RTSamePreviewDomain(candidate, water), "zero candidate height cannot slip through float tolerance");

    const int32_t hi = std::numeric_limits<int32_t>::max();
    const int32_t lo = std::numeric_limits<int32_t>::min();
    water = nativePreview(true);
    water.scissor[0] = lo;
    water.scissor[1] = lo;
    water.scissor[2] = hi;
    water.scissor[3] = hi;
    expect(wr64RTSamePreviewDomain(water, water), "identical signed-limit rectangles do not overflow");
    candidate = water;
    candidate.scissor[0] = hi - 4;
    expect(!wr64RTSamePreviewDomain(candidate, water), "huge horizontal inset cannot wrap into tolerance");
    candidate = water;
    candidate.scissor[1] = hi - 4;
    expect(!wr64RTSamePreviewDomain(candidate, water), "huge vertical inset cannot wrap into tolerance");
    candidate = water;
    candidate.scissor[2] = lo + 4;
    expect(!wr64RTSamePreviewDomain(candidate, water), "huge right-edge difference cannot wrap into tolerance");
    candidate = water;
    candidate.scissor[3] = lo + 4;
    expect(!wr64RTSamePreviewDomain(candidate, water), "huge bottom-edge difference cannot wrap into tolerance");

    std::printf("%s: %u native live-preview domain checks.\n", failures ? "FAIL" : "PASS", checks);
    return failures ? 1 : 0;
}
