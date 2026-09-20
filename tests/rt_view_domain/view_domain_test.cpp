#include "common/rt64_wr64_rt_view.h"
#include "common/rt64_wr64_rt_sky.h"

#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using namespace RT64;
namespace {
unsigned checks = 0;
void require(bool value, const char *message) {
    ++checks;
    if (!value) { std::cerr << "FAIL: " << message << '\n'; std::exit(1); }
}

WR64RTViewDomain nativeView(unsigned view) {
    WR64RTViewDomain domain;
    domain.perspective = true;
    domain.scale[0] = 212.0f;
    domain.scale[1] = 120.0f;
    domain.scale[2] = 0.5f;
    domain.translate[0] = 212.0f;
    domain.translate[1] = view == 1 ? 60.0f : 180.0f;
    domain.translate[2] = 0.5f;
    domain.scissor[0] = 0;
    domain.scissor[1] = view == 1 ? 0 : 480;
    domain.scissor[2] = 1696;
    domain.scissor[3] = view == 1 ? 480 : 960;
    return domain;
}

void domains() {
    require(wr64RTNativeRaceView({}) == 0, "uninitialized domain has no owner");
    require(!wr64RTSameRaceView({}, {}), "two invalid domains never match");
    const auto p1 = nativeView(1), p2 = nativeView(2);
    for (unsigned view : {1u, 2u}) {
        const auto water = nativeView(view);
        require(wr64RTNativeRaceView(water) == view, "native water view selected");
        require(wr64RTSameRaceView(water, water), "same view's world and water admitted");
        require(!wr64RTSameRaceView(water, nativeView(3 - view)),
            "even identical camera matrices cannot merge the two native domains");

        // Vertical is a late affine of precisely these source viewports. The
        // same native owner must survive arbitrary output sizes and aspect ratios.
        for (bool vertical : {false, true}) for (const auto size :
            {std::array<float, 2>{1280, 720}, {3840, 1080}, {3441, 1440}}) {
            const auto layout = wr64VerticalLayout(vertical, size[0], size[1], size[1] / 240.0f);
            const auto affine = wr64VerticalWorld(layout, int(view));
            require(wr64RTNativeRaceView(water) == view, "presentation preserves native ownership");
            require(std::isfinite(affine.x(size[0] * 0.5f)) &&
                std::isfinite(affine.y(water.translate[1])), "late presentation is finite");
        }

        auto changed = water;
        changed.scale[1] = -120.0f;
        require(wr64RTNativeRaceView(changed) == view, "Y convention may invert without changing owner");
        changed = water; changed.perspective = false;
        require(wr64RTNativeRaceView(changed) == 0, "rectangle/orthographic HUD never selects a scene");
        changed = water; changed.menuModelPreview = true;
        require(wr64RTNativeRaceView(changed) == 0, "menu model explicitly excluded");
        changed = water; changed.menuWaterPreview = true;
        require(wr64RTNativeRaceView(changed) == 0, "menu water explicitly excluded");

        for (float center : {26.0f, 146.0f, 28.0f, 138.0f, 120.0f, 66.0f, 176.0f}) {
            changed = water; changed.translate[1] = center;
            require(wr64RTNativeRaceView(changed) == 0,
                "signal, indicator, full-frame and legacy inset viewports excluded");
        }
        changed = water; changed.translate[1] = nativeView(3 - view).translate[1];
        require(wr64RTNativeRaceView(changed) == 0, "contradictory viewport/scissor owner rejected");
        for (int component : {0, 1}) for (float delta : {-1.0f, -0.25f, 0.25f, 1.0f}) {
            changed = water; changed.scale[component] += delta;
            require(wr64RTNativeRaceView(changed) == 0, "different viewport scale cannot impersonate view");
            changed = water; changed.translate[component] += delta;
            require(wr64RTNativeRaceView(changed) == 0, "different viewport center cannot impersonate view");
        }
        for (int component = 0; component < 4; ++component) {
            for (int value : {std::numeric_limits<int>::min(), -1, 1,
                std::numeric_limits<int>::max()}) {
                changed = water; changed.scissor[component] = value;
                require(wr64RTNativeRaceView(changed) == 0,
                    "malformed/inset/extended scissor cannot acquire owner");
            }
        }
        changed = water; changed.scissor[1] = 0; changed.scissor[3] = 960;
        require(wr64RTNativeRaceView(changed) == 0, "full-frame scissor not a split view");
        changed = water; changed.scissor[3] = changed.scissor[1];
        require(wr64RTNativeRaceView(changed) == 0, "empty scissor has no owner");

        for (int component = 0; component < 3; ++component) {
            for (float invalid : {std::numeric_limits<float>::infinity(),
                -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::quiet_NaN()}) {
                changed = water; changed.scale[component] = invalid;
                require(wr64RTNativeRaceView(changed) == 0, "nonfinite viewport scale rejected");
                require(!wr64RTSameRaceView(water, changed), "invalid reference domain rejected");
                changed = water; changed.translate[component] = invalid;
                require(wr64RTNativeRaceView(changed) == 0, "nonfinite viewport translation rejected");
            }
        }
    }
    require(!wr64RTSameRaceView(p1, p2) && !wr64RTSameRaceView(p2, p1),
        "cross-player isolation is symmetric");

    // Grouping is independent of projection storage and traversal order. Sky,
    // world and water can each create a different projection index for a view.
    const std::array<WR64RTViewDomain, 7> projections{p2, p1, {}, p2, p1, p2, p1};
    for (unsigned reference : {0u, 1u, 3u, 4u, 5u, 6u}) {
        for (unsigned candidate = 0; candidate < projections.size(); ++candidate) {
            const bool expected = candidate != 2 &&
                ((reference == 0 || reference == 3 || reference == 5) ==
                 (candidate == 0 || candidate == 3 || candidate == 5));
            require(wr64RTSameRaceView(projections[candidate], projections[reference]) == expected,
                "projection ordinal is not a camera identity");
        }
    }
}

void materials() {
    using Signature = bool (*)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
    struct Material { Signature predicate; uint32_t ccL, ccH, omL, omH; };
    const Material families[] = {
        {wr64RTSkySignature, 0xFC11C223, 0xFF87FFFF, 0x00504240, 0x00882C3F},
        {wr64RTBackdropSignature, 0xFC22FFFF, 0x1FFCFA38, 0x0F0A4000, 0x00982C3F},
        {wr64RTBackdropSignature, 0xFCFFFFFF, 0xFFFCF279, 0x0F0A4000, 0x00882C3F}
    };
    for (const auto &family : families) {
        for (uint32_t dither : {0U, 0x40U, 0x80U, 0xC0U}) {
            const uint32_t h = family.omH | dither;
            require(family.predicate(6, family.ccL, family.ccH, family.omL, h),
                "RGB dithering does not change native sky material");
            require(!family.predicate(5, family.ccL, family.ccH, family.omL, h),
                "incomplete fan remains excluded");
            for (unsigned bit = 0; bit < 32; ++bit) {
                const uint32_t mask = 1U << bit;
                require(!family.predicate(6, family.ccL ^ mask, family.ccH, family.omL, h),
                    "combiner L stays exact");
                require(!family.predicate(6, family.ccL, family.ccH ^ mask, family.omL, h),
                    "combiner H stays exact");
                require(!family.predicate(6, family.ccL, family.ccH, family.omL ^ mask, h),
                    "othermode L stays exact");
                require(family.predicate(6, family.ccL, family.ccH, family.omL, h ^ mask) ==
                    ((mask & 0xC0U) != 0), "only two RGB dither bits may differ");
            }
        }
    }

    std::ifstream capture(WR64_CAPTURED_MATERIALS);
    require(bool(capture), "captured native P1/P2 material rows available");
    std::string line;
    std::getline(capture, line);
    unsigned seen = 0;
    while (std::getline(capture, line)) {
        if (line.empty()) continue;
        std::stringstream row(line);
        std::vector<std::string> fields;
        std::string field;
        while (std::getline(row, field, ',')) fields.push_back(field);
        require(fields.size() == 19, "captured material field count");
        const auto value = [&](unsigned i, int base = 16) {
            return uint32_t(std::stoul(fields[i], nullptr, base));
        };
        const uint32_t id = value(7), omH = value(11);
        require(id == 0x57524300 || id == 0x57524301, "actual captured course matrix identity");
        require(wr64RTSkySignature(value(4, 10), value(8), value(9), value(10), omH),
            "both actual captured cloud materials selected");
        const bool previousExactPredicate = omH == 0x00882C3F;
        require(previousExactPredicate == (id == 0x57524300),
            "negative control: previous classifier excludes actual P2 cloud");
        seen |= id == 0x57524300 ? 1 : 2;
    }
    require(seen == 3, "capture includes both actual player materials");
}
}

int main() {
    domains();
    materials();
    std::cout << "PASS: " << checks << " native RT view/domain/material checks\n";
}
