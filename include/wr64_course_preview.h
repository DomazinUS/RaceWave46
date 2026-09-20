#pragma once
#include "recomp.h"

#ifdef __cplusplus
extern "C" {
#endif
void wr64_course_preview_prepare(uint8_t* rdram, uint32_t cursor);
void wr64_course_preview_map_begin(uint8_t* rdram, uint32_t cursor);
uint32_t wr64_course_preview_map_end(uint8_t* rdram, uint32_t cursor);
int32_t wr64_course_preview_x(int32_t original);
uint32_t wr64_course_preview_rect_x(uint32_t original);
void wr64_course_preview_mask(uint8_t* rdram, uint32_t cursor);
void wr64_course_preview_finish(uint8_t* rdram, uint32_t cursor);
#ifdef __cplusplus
}
#endif
