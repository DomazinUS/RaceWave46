#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
int32_t wr64_menu_half_extension(void);
int32_t wr64_title_menu_origin(uint8_t* rdram, uint32_t table, int32_t original);
int32_t wr64_ending_panel_retire(uint8_t* rdram, uint32_t row, int32_t original);
uint32_t wr64_menu_enable(uint8_t* rdram, uint32_t cursor);
void wr64_menu_promote_waku_rect(uint8_t* rdram, uint32_t cursor, int32_t x, int32_t width);
uint32_t wr64_menu_fill_rect(uint8_t* rdram, uint32_t cursor,
    int32_t left, int32_t top, int32_t right, int32_t bottom, int32_t half_extension);
#ifdef __cplusplus
}
#endif
