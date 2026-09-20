#ifndef WR64_FREE_RIDE_H
#define WR64_FREE_RIDE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Native VS identity is retained so input, pause and two-view rendering keep
 * their ordinary paths. This predicate does not change any emulated state. */
int wr64_free_ride_active(const uint8_t* rdram);

/* Only a selected human rider's native checkpoint/rules record is admitted. */
int wr64_free_ride_skip_retirement(const uint8_t* rdram, uint32_t record_address);

/* Sequence-player speech commands only; engine/music/SFX commands pass. */
int wr64_free_ride_skip_audio(const uint8_t* rdram, uint32_t command);

/* Called once from the native race-audio initializer, after track preload.
 * Uses the existing music countdown/start path and respects music disabled. */
void wr64_free_ride_schedule_music(uint8_t* rdram);

/* Explicit presentation sites, including the two-player timer block. */
int wr64_free_ride_skip_hud(const uint8_t* rdram, uint32_t native_site);

#ifdef __cplusplus
}
#endif

#endif
