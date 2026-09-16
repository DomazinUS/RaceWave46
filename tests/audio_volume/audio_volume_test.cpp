#include "wr64_audio_volume.hpp"

#include <array>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

static void require(bool condition, const char* message) {
    if (!condition) { std::cerr << "FAIL: " << message << '\n'; std::exit(1); }
}

int main() {
    std::vector<std::int16_t> source;
    for (int sample = -32768; sample <= 32767; ++sample) source.push_back(static_cast<std::int16_t>(sample));
    auto output = source;
    wr64::audio::apply_main_volume(output.data(), output.size(), 100.0);
    require(output == source, "100% preserves every possible signed 16-bit PCM sample");
    wr64::audio::apply_main_volume(output.data(), output.size(), 50.0);
    for (std::size_t i = 0; i < output.size(); ++i)
        require(output[i] == source[i] / 2, "50% attenuates positive and negative samples once without clipping");
    wr64::audio::apply_main_volume(output.data(), output.size(), 0.0);
    require(std::all_of(output.begin(), output.end(), [](auto sample) { return sample == 0; }),
        "0% silences the entire output");
    output = source;
    wr64::audio::apply_main_volume(output.data(), output.size(), 101.0);
    require(output == source, "out-of-range maximum does not amplify or overflow PCM");
    wr64::audio::apply_main_volume(output.data(), output.size(), std::numeric_limits<double>::quiet_NaN());
    require(output == source, "invalid gain cannot corrupt PCM");
    const std::array<std::int16_t, 6> queued{10000, -20000, 0, 0, 30000, -32768};
    auto first = queued;
    auto next = queued;
    wr64::audio::apply_main_volume(first.data(), first.size(), 25.0);
    wr64::audio::apply_main_volume(next.data(), next.size(), 100.0);
    require(first[0] == 2500 && first[1] == -5000 && first[4] == 7500 && first[5] == -8192,
        "stereo channels receive the same gain");
    require(first[2] == 0 && first[3] == 0, "underrun padding remains silent");
    require(next == queued, "changing gain leaves the queued source untouched for the next callback");
    std::cout << "PASS: output volume across all 65,536 PCM values and live gain changes\n";
}
