#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
// Only the already-loaded perspective argument changes; native camera storage
// and its animation inputs are never rewritten.
uint32_t wr64_camera_fov_lens(const uint8_t* rdram, uint32_t camera,
    uint32_t pool, uint32_t original_bits);
#ifdef __cplusplus
}
#endif
