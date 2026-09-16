// WR64 stereo s16 resampler: Kaiser-windowed sinc with a polyphase table.
// The 32-tap kernel uses 1024 phases plus one interpolation row, Kaiser beta 9
// (approximately 90 dB sidelobes), and per-phase unity-DC normalization.
// Linear phase interpolation and an integer rational position accumulator avoid
// phase drift. Equal input/output rates bypass conversion. Keep the offline
// reference renderer consistent with changes to this kernel and phase policy.

#pragma once

#include <cmath>
#include <cstdint>
#include <cstring>
#include <vector>

namespace wr64::audio_resampler {

static constexpr uint32_t Wr64ResamplerTaps   = 32;
static constexpr uint32_t Wr64ResamplerPhases = 1024;
static constexpr double   Wr64ResamplerBeta   = 9.0;
// MSVC does not define M_PI without _USE_MATH_DEFINES; carry it explicitly.
static constexpr double   Wr64ResamplerPi     = 3.14159265358979323846;

// Modified Bessel function of the first kind, order zero. Power series;
// converges in ~25 terms for beta <= 10 and is only used to build the table.
inline double wr64BesselI0(double x) {
    double sum = 1.0;
    double term = 1.0;
    const double half_x = x * 0.5;
    for (int k = 1; k < 40; k++) {
        term *= (half_x / k) * (half_x / k);
        sum += term;
        if (term < 1e-18 * sum) {
            break;
        }
    }
    return sum;
}

class Resampler {
public:
    void configure(uint32_t in_rate, uint32_t out_rate) {
        in_rate_ = in_rate;
        out_rate_ = out_rate;
        identity_ = (in_rate == out_rate);
        pending_.clear();
        ready_.clear();
        next_out_ = 0;
        dropped_in_ = 0;
        if (!identity_ && table_.empty()) {
            build_table();
        }
    }

    bool configured() const { return (in_rate_ != 0) && (out_rate_ != 0); }
    uint32_t input_rate() const { return in_rate_; }

    // Interleaved stereo s16 in; converted frames accumulate in ready().
    void put(const int16_t *samples, size_t sample_count) {
        if (identity_) {
            ready_.insert(ready_.end(), samples, samples + sample_count);
            return;
        }
        pending_.insert(pending_.end(), samples, samples + sample_count);
        produce();
    }

    // The tail still inside the kernel window, pushed out with zero padding.
    // Called before a rate change so the old rate's last milliseconds play.
    void flush() {
        if (identity_ || pending_.empty()) {
            return;
        }
        const std::vector<int16_t> zeros(Wr64ResamplerTaps * 2, 0);
        pending_.insert(pending_.end(), zeros.begin(), zeros.end());
        produce();
        pending_.clear();
        next_out_ = 0;
        dropped_in_ = 0;
    }

    std::vector<int16_t> &ready() { return ready_; }

private:
    void build_table() {
        const int half = int(Wr64ResamplerTaps) / 2;
        table_.assign(size_t(Wr64ResamplerPhases + 1) * Wr64ResamplerTaps, 0.0f);
        const double i0_beta = wr64BesselI0(Wr64ResamplerBeta);
        for (uint32_t p = 0; p <= Wr64ResamplerPhases; p++) {
            const double frac = double(p) / double(Wr64ResamplerPhases);
            double row[Wr64ResamplerTaps];
            double sum = 0.0;
            for (uint32_t k = 0; k < Wr64ResamplerTaps; k++) {
                const double arg = double(int(k) - (half - 1)) - frac;
                const double s = (arg == 0.0) ? 1.0
                    : std::sin(Wr64ResamplerPi * arg) / (Wr64ResamplerPi * arg);
                const double ratio = arg / double(half);
                const double inside = 1.0 - ratio * ratio;
                const double w = (inside >= 0.0)
                    ? wr64BesselI0(Wr64ResamplerBeta * std::sqrt(inside)) / i0_beta
                    : 0.0;
                row[k] = s * w;
                sum += row[k];
            }
            for (uint32_t k = 0; k < Wr64ResamplerTaps; k++) {
                table_[size_t(p) * Wr64ResamplerTaps + k] = float(row[k] / sum);
            }
        }
    }

    void produce() {
        const int half = int(Wr64ResamplerTaps) / 2;
        const uint64_t frames_pending = pending_.size() / 2;
        for (;;) {
            // Exact rational position of the next output frame, in input
            // frames: t = next_out * in / out. Integer math, no drift, ever.
            const uint64_t t_num = next_out_ * in_rate_;
            const uint64_t t_int = t_num / out_rate_;
            // The kernel needs input frames [t_int - (half-1), t_int + half].
            if (t_int < uint64_t(half - 1) + dropped_in_) {
                // Still inside the priming region at a fresh start; emit from
                // the earliest full window instead of inventing history.
                next_out_++;
                continue;
            }
            const uint64_t base = t_int - (half - 1) - dropped_in_;
            if (base + Wr64ResamplerTaps > frames_pending) {
                break;
            }
            const double frac =
                double(t_num % out_rate_) / double(out_rate_);
            const double pf = frac * double(Wr64ResamplerPhases);
            const uint32_t p0 = uint32_t(pf);
            const float pw = float(pf - double(p0));
            const float *h0 = &table_[size_t(p0) * Wr64ResamplerTaps];
            const float *h1 = h0 + Wr64ResamplerTaps;
            float acc_l = 0.0f;
            float acc_r = 0.0f;
            const int16_t *x = &pending_[size_t(base) * 2];
            for (uint32_t k = 0; k < Wr64ResamplerTaps; k++) {
                const float h = h0[k] + (h1[k] - h0[k]) * pw;
                acc_l += h * float(x[k * 2]);
                acc_r += h * float(x[k * 2 + 1]);
            }
            ready_.push_back(clamp16(acc_l));
            ready_.push_back(clamp16(acc_r));
            next_out_++;
        }
        // Drop input frames the kernel can never need again.
        const uint64_t t_next = (next_out_ * in_rate_) / out_rate_;
        if (t_next >= uint64_t(half - 1) + dropped_in_) {
            const uint64_t droppable = t_next - (half - 1) - dropped_in_;
            const uint64_t keep_from = (droppable < frames_pending) ? droppable : frames_pending;
            if (keep_from > 0) {
                pending_.erase(pending_.begin(),
                    pending_.begin() + ptrdiff_t(keep_from * 2));
                dropped_in_ += keep_from;
            }
        }
    }

    static int16_t clamp16(float v) {
        const float r = std::round(v);
        if (r > 32767.0f) return 32767;
        if (r < -32768.0f) return -32768;
        return int16_t(r);
    }

    uint32_t in_rate_ = 0;
    uint32_t out_rate_ = 0;
    bool identity_ = true;
    std::vector<float> table_;
    std::vector<int16_t> pending_;
    std::vector<int16_t> ready_;
    uint64_t next_out_ = 0;
    uint64_t dropped_in_ = 0;
};

} // namespace wr64::audio_resampler
