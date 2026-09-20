#include "recomp.h"
#include "common/rt64_wr64_cpu_logo.h"
#define XXH_INLINE_ALL
#include "contrib/xxHash/xxhash.h"
#include <cmath>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <vector>

extern "C" void func_800980D0(uint8_t*, recomp_context*);
static unsigned checks = 0;
static void require(bool value, const char* reason) {
    ++checks;
    if (!value) throw std::runtime_error(reason);
}
static void near(float actual, float expected, const char* reason) {
    require(std::fabs(actual - expected) < 0.002f, reason);
}

int main() {
    using namespace RT64;
    try {
        std::vector<uint8_t> ram(8 * 1024 * 1024);
        auto* rdram = ram.data();
        constexpr uint32_t fb = 0x00200000;
        constexpr uint32_t image = 0x000DCEC8;
        for (uint32_t i = 0; i < 128 * 128 * 2; ++i) ram[image + i] = uint8_t(i * 31 + i / 256);
        const auto untouched = ram;
        MEM_W(0, int32_t(0x801542C0)) = int32_t(0x80200000);
        MEM_W(4, int32_t(0x801542C0)) = int32_t(0x80240000);
        MEM_W(8, int32_t(0x801542C0)) = int32_t(0x80280000);
        require(!wr64IsCpuLogo(fb, 424, 240, 0), "no logo identity before native producer");
        recomp_context ctx{};
        ctx.r4 = int32_t(0x80200000);
        func_800980D0(rdram, &ctx);
        for (unsigned row = 0; row < 128; ++row) {
            require(std::memcmp(rdram + fb + (56 + row) * 848 + 148 * 2,
                rdram + image + row * 256, 256) == 0, "original CPU pixels and placement retained");
        }
        require(std::memcmp(rdram + image, untouched.data() + image, 32768) == 0,
            "runtime identity registration does not modify source image");
        const uint64_t hash = XXH3_64bits(rdram + fb, Wr64CpuLogoBytes);
        require(wr64IsCpuLogo(fb, 424, 240, hash), "native blitter registers exact completed framebuffer");
        require(!wr64IsCpuLogo(fb + 0x40000, 424, 240, hash), "another framebuffer is not the logo");
        require(!wr64IsCpuLogo(fb, 320, 240, hash), "other VI geometry does not match");
        ram[fb + 4096] ^= 0x20;
        require(!wr64IsCpuLogo(fb, 424, 240, XXH3_64bits(rdram + fb, Wr64CpuLogoBytes)),
            "later CPU content at the same address does not inherit logo policy");
        for (const float aspect : {4.0f / 3, 16.0f / 9, 21.0f / 9, 32.0f / 9}) {
            const float height = 540, width = height * aspect;
            const auto old = wr64UsaPresentationExtent(width, height, true);
            const auto logo = wr64CpuAwarePresentationExtent(width, height, true, true, true);
            const auto scratchMenu = wr64CpuAwarePresentationExtent(width, height, true, true, false);
            const auto gpuGame = wr64CpuAwarePresentationExtent(width, height, true, false, true);
            near(scratchMenu.width, old.width, "other CPU menu widths unchanged");
            near(scratchMenu.height, old.height, "other CPU menu heights unchanged");
            near(gpuGame.width, old.width, "stale CPU bytes cannot classify GPU-rendered scenes");
            near(gpuGame.height, old.height, "GPU presentation height unchanged");
            if (aspect <= Wr64BaselineAspect) {
                near(logo.width, old.width, "16:9 and narrower logo width unchanged");
                near(logo.height, old.height, "16:9 and narrower logo height unchanged");
            } else {
                near(logo.width, height * Wr64BaselineAspect, "ultrawide retains established logo proportions");
                near(logo.height, height, "ultrawide logo retains vertical size");
            }
            const auto fixed = wr64CpuAwarePresentationExtent(width, height, false, true, true);
            const auto oldFixed = wr64UsaPresentationExtent(width, height, false);
            near(fixed.width, oldFixed.width, "Original aspect remains unchanged");
            near(fixed.height, oldFixed.height, "Original presentation height remains unchanged");
        }
        std::cout << "PASS: " << checks << " native CPU-logo and presentation checks\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
