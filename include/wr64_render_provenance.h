#pragma once

#include <cstdint>

extern "C" void wr64_note_cpu_boot_logo(uint8_t* rdram, uint32_t framebuffer);
extern "C" void wr64_wait_for_rt_startup(uint8_t* rdram);

extern "C" void wr64_note_gfx_task(
    uint32_t task_address,
    uint32_t context_ra,
    uint32_t root_display_list,
    uint32_t ucode,
    uint32_t ucode_data);

extern "C" uint64_t wr64_claim_gfx_task(
    uint32_t root_display_list,
    uint32_t ucode,
    uint32_t ucode_data,
    uint32_t* task_address,
    uint32_t* context_ra);

extern "C" void wr64_hud_score_spawn(uint32_t slot_address);
extern "C" void wr64_hud_park_spawn(void);
extern "C" void wr64_hud_score_draw(uint8_t* rdram, uint32_t slot_address, uint32_t begin, uint32_t end);
extern "C" void wr64_hud_park_draw(uint8_t* rdram, uint32_t slot, uint32_t begin, uint32_t end);
extern "C" void wr64_ending_hud_spawn(void);
extern "C" void wr64_ending_hud_draw(uint8_t* rdram, uint32_t row, uint32_t begin, uint32_t end);

// Private Dolphin top-exit trial. The token authenticates the native producer;
// the captured position is never reconstructed from its clipped RDP rectangle.
extern "C" uint32_t wr64_dolphin_sun_begin(uint8_t* rdram, float center_x, float center_y);
extern "C" void wr64_dolphin_sun_packet(uint8_t* rdram, uint32_t token, uint32_t packet);
