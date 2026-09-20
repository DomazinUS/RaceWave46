#include "common/rt64_wr64_rt_material.h"
#include <cstdlib>
#include <iostream>

using RT64::Wr64RTMaterial;
static unsigned checks = 0;
static void require(bool result, const char *message) {
    ++checks;
    if (!result) { std::cerr << "FAIL " << message << '\n'; std::exit(1); }
}

int main() {
    struct Fixture { uint32_t otherModeL; Wr64RTMaterial expected; const char *name; };
    // Native captures: START support/rope and palms are texture-edge surfaces;
    // the matching START bases and letters differ by coverage-times-alpha only.
    const Fixture fixtures[] = {
        { 0xC8113078, Wr64RTMaterial::Cutout, "native START supports, rope and palm cutouts" },
        { 0xC8112078, Wr64RTMaterial::Opaque, "native START bases and lettering" },
        { 0x00552078, Wr64RTMaterial::Opaque, "native rider opaque material" },
        { 0x005049D8, Wr64RTMaterial::Rejected, "native water and rider blob" },
        { 0x0F0A4000, Wr64RTMaterial::Rejected, "native sky backdrop" },
        { 0x00504240, Wr64RTMaterial::Rejected, "native cloud material" },
        { 0xC8113079, Wr64RTMaterial::Cutout, "coverage alpha plus threshold" },
        { 0xC8112079, Wr64RTMaterial::Cutout, "threshold without coverage alpha" },
        { 0xC811207A, Wr64RTMaterial::Rejected, "reserved alpha mode" },
        { 0xC811207B, Wr64RTMaterial::Rejected, "dither alpha mode" },
        { 0xC811307A, Wr64RTMaterial::Rejected, "coverage alpha cannot admit reserved mode" },
        { 0xC811307B, Wr64RTMaterial::Rejected, "coverage alpha cannot admit dither" },
        { 0xC8113058, Wr64RTMaterial::Rejected, "texture edge without depth writes" },
        { 0xC8113878, Wr64RTMaterial::Rejected, "translucent depth mode with coverage alpha" },
        { 0xC8112478, Wr64RTMaterial::Opaque, "interpenetrating opaque depth mode preserved" },
        { 0xC8112C78, Wr64RTMaterial::Opaque, "decal admission preserved for separate shadow policy" },
        { 0xC8113C78, Wr64RTMaterial::Cutout, "decal texture edge still needs alpha testing" },
        { 0, Wr64RTMaterial::Rejected, "empty material has no depth writes" }
    };
    for (const auto &fixture : fixtures) {
        require(RT64::wr64RTClassifyMaterial(fixture.otherModeL) == fixture.expected, fixture.name);
        // AA, blending, coverage destination and other independent state must
        // not accidentally narrow the pre-existing material admission.
        constexpr uint32_t coveragePolicyBits = 0x1C23;
        for (uint32_t bit = 0; bit < 32; ++bit) {
            const uint32_t flag = uint32_t(1) << bit;
            if (!(flag & coveragePolicyBits)) {
                require(RT64::wr64RTClassifyMaterial(fixture.otherModeL ^ flag) == fixture.expected,
                    "unrelated render-state bits do not change material class");
            }
        }
    }
    static_assert(uint32_t(Wr64RTMaterial::Rejected) == 0);
    static_assert(uint32_t(Wr64RTMaterial::Opaque) == 1);
    static_assert(uint32_t(Wr64RTMaterial::Cutout) == 2);
    std::cout << "PASS " << checks << " material coverage checks\n";
}
