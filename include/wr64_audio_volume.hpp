#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>

namespace wr64::audio {

// Apply once at device delivery, after resampling. At 100% the original PCM
// remains bit-identical; changing volume does not alter any queued samples.
inline void apply_main_volume(std::int16_t* output, std::size_t count, double percent) {
    if (!std::isfinite(percent) || percent >= 100.0) return;
    if (percent <= 0.0) {
        std::fill_n(output, count, std::int16_t{0});
        return;
    }
    const double gain = percent / 100.0;
    for (std::size_t i = 0; i < count; ++i)
        output[i] = static_cast<std::int16_t>(output[i] * gain);
}

} // namespace wr64::audio
