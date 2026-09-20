#include "recomp.h"
#include "../lib/rt64/src/common/rt64_wr64_wave_distance.h"

extern "C" void wr64_wave_distance_capture(uint8_t *rdram, recomp_context *ctx) {
    if (!rdram || !ctx) return;
    const uint32_t center = uint32_t(ctx->r30);
    if (center != 0x80192420U && center != 0x8019243CU) return;
    const uint32_t view = center == 0x8019243CU ? 1U : 0U;
    const uint32_t pool = uint32_t(MEM_W(0, S32(0x801518B8U)));
    const uint32_t output = uint32_t(MEM_W(0x7C, ctx->r29));
    if (output != pool + (view ? 0x170D8U : 0x13D68U)) return;
    RT64::wr64PublishWaveDistance(rdram, view);
}
