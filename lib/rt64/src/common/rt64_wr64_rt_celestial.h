#pragma once

#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace RT64 {
    // CPU snapshots of the native sky sprites. No pointers to mutable game RAM
    // survive publication to the presentation thread. Lens flares are excluded:
    // they are a camera effect, not another body in the reflected sky.
    struct Wr64RTCelestialBody {
        float cosAzimuth = 0.0f, sinAzimuth = 0.0f;
        float heightPixels = 0.0f, radius = 2000.0f;
        float halfWidth = 0.0f, halfHeight = 0.0f, texelStep = 0.0f;
        std::array<float, 4> color{};
        uint32_t texture = 0;
    };

    struct Wr64RTCelestialSnapshot {
        // Four native IA16 alpha bytes per word, least-significant byte first.
        // Slots: disk 32x32 at byte0, glow32x32 at1024, stars4x4 at2048.
        std::array<uint32_t, 516> alphaWords{};
        std::array<Wr64RTCelestialBody, 20> bodies{};
        uint32_t count = 0;
        bool constrainForward = false;
    };

    struct Wr64RTCelestialRecord {
        std::array<float, 4> rect{};       // Native424x240 chart, L/T/R/B.
        std::array<float, 4> texcoords{};  // StartS/T, texels per pixel S/T.
        std::array<float, 4> color{};
        uint32_t texture = 0;
    };

    struct Wr64RTCelestialProjection {
        std::array<Wr64RTCelestialRecord, 20> records{};
        uint32_t count = 0;
        // Dot each row with float4(worldDirection,0); native pixel is XY/W.
        std::array<std::array<float, 4>, 3> projectionRows{};
    };

    // RDRAM is in RT64's word-swapped host layout. RSP segment bases preserve
    // the command's raw address, including KSEG aliases. Match the texture path
    // (RSP::fromSegmented then RDP::maskAddress), then check the physical range.
    inline Wr64RTCelestialSnapshot wr64RTCelestialReadSnapshot(const uint8_t *ram, size_t size,
        const std::array<uint32_t, 16> &segments, uint32_t course, uint32_t players,
        bool twoPlayerEnhanced = false) {
        Wr64RTCelestialSnapshot result;
        // The restored 2P sprites share these authored angles, heights, colors
        // and texture bytes. Camera-dependent native screen records are never
        // read here: each RT view projects this immutable snapshot separately.
        // Only the producer's validated Enhanced race scope may opt 2P in.
        const bool eligiblePlayers = players == 1 ||
            (players == 2 && twoPlayerEnhanced && (course == 0 || course == 2 || course == 6));
        if (ram == nullptr || size < 0x800000 || !eligiblePlayers || (course != 0 && course != 2 && course != 6)) {
            return result;
        }
        auto word = [&](uint32_t address) {
            uint32_t value = 0;
            std::memcpy(&value, ram + (address & 0x7fffff), sizeof(value));
            return value;
        };
        auto real = [&](uint32_t address) {
            const uint32_t bits = word(address);
            float value = 0.0f;
            std::memcpy(&value, &bits, sizeof(value));
            return value;
        };
        auto loadAlpha = [&](uint32_t segmented, uint32_t texels, uint32_t byteOffset) {
            const uint32_t base = segments[segmented >> 24];
            const uint32_t resolved = base + (segmented & 0xffffff);
            const uint64_t physical = resolved & 0xffffff;
            if (base == 0 || (physical & 3) != 0 || physical + uint64_t(texels) * 2 > size || physical + uint64_t(texels) * 2 > 0x800000) {
                return false;
            }
            bool anyAlpha = false;
            for (uint32_t i = 0; i < texels; i++) {
                const uint32_t alpha = ram[(size_t(physical) + i * 2 + 1) ^ 3];
                result.alphaWords[(byteOffset + i) / 4] |= alpha << (((byteOffset + i) % 4) * 8);
                anyAlpha |= alpha != 0;
            }
            return anyAlpha;
        };
        auto add = [&](float angle, float height, float halfExtent, float step,
            std::array<float, 4> color, uint32_t texture) {
            if (!std::isfinite(angle) || angle < 0.0f || angle >= 360.0f ||
                !std::isfinite(height) || std::fabs(height) > 4096.0f ||
                halfExtent <= 0.0f || halfExtent > 512.0f || result.count >= result.bodies.size()) {
                return false;
            }
            // Preserve the original 4096-entry sine table and truncation.
            const uint32_t index = uint32_t((angle / 360.0f) * 4096.0f) & 0xfff;
            const float s = real(0x80154350 + index * 4);
            const float c = real(0x80154350 + ((index + 1024) & 0xfff) * 4);
            const float lengthSquared = s * s + c * c;
            if (!std::isfinite(lengthSquared) || lengthSquared < 0.99f || lengthSquared > 1.01f) {
                return false;
            }
            auto &body = result.bodies[result.count++];
            body.cosAzimuth = c; body.sinAzimuth = s;
            body.heightPixels = height;
            body.halfWidth = body.halfHeight = halfExtent;
            body.texelStep = step; body.color = color; body.texture = texture;
            return true;
        };
        result.constrainForward = course != 0;
        if (!loadAlpha(0x08004400, 1024, 0)) {
            return {};
        }
        if (course == 0 || course == 2) {
            const float angle = course == 0 ? 5.0f : real(0x800EAB88);
            const float height = float(int32_t(word(0x800D9924 + course * 4)));
            const float halfExtent = float(word(0x800D9944 + course * 4));
            const uint32_t derivative = course == 0 ? 0x555 : 0x29b;
            // RDP::drawRect quantizes the final coordinate to 1/32 texel.
            const float width = halfExtent * 2.0f;
            if (halfExtent <= 0.0f || halfExtent > 512.0f) { return {}; }
            const float step = float((uint64_t(derivative) * uint32_t(width * 4.0f)) >> 7) / (32.0f * width);
            if (course == 2) {
                if (!loadAlpha(0x08004C00, 1024, 1024)) {
                    return {};
                }
                std::array<float, 4> glow{ 0.0f, 0.0f, 0.0f, 1.0f };
                for (uint32_t i = 0; i < 3; i++) {
                    glow[i] = float(ram[((0x800D9918 + course * 3 + i) & 0x7fffff) ^ 3]) / 255.0f;
                }
                if (!add(angle, height, halfExtent, step, glow, 1)) { return {}; }
            }
            // Native disk combiner uses texture alpha, ignoring primitive alpha.
            if (!add(angle, height, halfExtent, step, { 1.0f, 1.0f, 1.0f, 1.0f }, 0)) { return {}; }
        }
        else {
            if (!loadAlpha(0x010102B0, 16, 2048)) { return {}; }
            // func80089C08 supplies these exact heights. Six angles are ROM
            // constants, including the deliberate native257.5-degree entry.
            std::array<float, 16> angles{ 0, 22.5f, 45, 67.5f, 90, 112.5f, 135,
                real(0x800EAB6C), 180, real(0x800EAB70), 225, real(0x800EAB74),
                270, real(0x800EAB78), real(0x800EAB7C), real(0x800EAB80) };
            constexpr std::array<float, 16> heights{ 80,40,50,30,80,20,80,70,80,60,30,50,80,90,20,30 };
            for (uint32_t i = 0; i < angles.size(); i++) {
                const bool large = word(0x800DA628 + i * 4) != 0;
                std::array<float, 4> color{};
                for (uint32_t c = 0; c < 4; c++) {
                    color[c] = float(word(0x800DA6A8 + i * 16 + c * 4) & 0xff) / 255.0f;
                }
                if (!add(angles[i], heights[i], large ? 2.0f : 1.0f, large ? 1.0f : 2.0f, color, 2)) { return {}; }
            }
            const float moonAngle = real(0x800EAB84);
            // Both native moon passes have identical bounds; preserve order.
            if (!add(moonAngle, 90.0f, 12.0f, 1.5f, { 240/255.0f,240/255.0f,28/255.0f,110/255.0f }, 0) ||
                !add(moonAngle, 90.0f, 12.0f, 1.5f, { 1,1,1,1 }, 0)) { return {}; }
        }
        return result;
    }

    // Reevaluate func8008962C's native chart at the presentation camera. These
    // sprites have fixed pixel elevation/size, not immutable world-space quads.
    // Remove primary-screen and facing<0.5 culls, but reject the rear hemisphere.
    // Keep float centers so presentation updates do not introduce integer steps.
    inline Wr64RTCelestialProjection wr64RTCelestialProject(const Wr64RTCelestialSnapshot &snapshot,
        const std::array<float, 16> &view, const std::array<float, 16> &projection,
        const std::array<float, 3> &eye) {
        Wr64RTCelestialProjection result;
        if (snapshot.count > snapshot.bodies.size()) { return result; }
        for (float v : view) { if (!std::isfinite(v)) { return result; } }
        for (float v : projection) { if (!std::isfinite(v)) { return result; } }
        for (float v : eye) { if (!std::isfinite(v)) { return result; } }
        const double forwardLength = std::sqrt(double(view[2]) * view[2] + double(view[10]) * view[10]);
        if (forwardLength < 1e-6) { return result; }
        const float forwardX = float(-view[2] / forwardLength), forwardZ = float(-view[10] / forwardLength);
        for (size_t row = 0; row < 4; row++) {
            std::array<double, 4> vp{};
            for (size_t col = 0; col < 4; col++) {
                for (size_t k = 0; k < 4; k++) { vp[col] += double(view[row * 4 + k]) * projection[k * 4 + col]; }
            }
            result.projectionRows[0][row] = float(212.0 * (vp[0] + vp[3]));
            result.projectionRows[1][row] = float(120.0 * (vp[3] - vp[1]));
            result.projectionRows[2][row] = float(vp[3]);
            if (!std::isfinite(result.projectionRows[0][row]) || !std::isfinite(result.projectionRows[1][row]) ||
                !std::isfinite(result.projectionRows[2][row])) { return {}; }
        }
        for (uint32_t i = 0; i < snapshot.count; i++) {
            const auto &body = snapshot.bodies[i];
            if (!std::isfinite(body.cosAzimuth) || !std::isfinite(body.sinAzimuth) ||
                !std::isfinite(body.radius) || body.radius <= 0.0f ||
                !std::isfinite(body.heightPixels) || !std::isfinite(body.halfWidth) ||
                !std::isfinite(body.halfHeight) || !std::isfinite(body.texelStep) ||
                body.halfWidth <= 0.0f || body.halfWidth > 512.0f || body.halfHeight <= 0.0f || body.halfHeight > 512.0f ||
                body.texelStep <= 0.0f || body.texelStep > 64.0f || body.texture > 2) { continue; }
            bool validColor = true;
            for (float c : body.color) { validColor &= std::isfinite(c) && c >= 0.0f && c <= 1.0f; }
            if (!validColor) { continue; }
            double x = double(body.cosAzimuth) * body.radius, z = double(body.sinAzimuth) * body.radius;
            const double forward = z * forwardZ + x * forwardX;
            if (forward <= 0.0) { continue; }
            if (snapshot.constrainForward && forward >= 1000.0) {
                x = (x - forwardX * forward) + forwardX * 1000.0;
                z = (z - forwardZ * forward) + forwardZ * 1000.0;
            }
            x += eye[0]; z += eye[2];
            std::array<double, 3> camera{};
            for (size_t c = 0; c < 3; c++) {
                camera[c] = (double(view[c]) * x + double(view[8 + c]) * z) + view[12 + c];
            }
            std::array<double, 4> clip{};
            for (size_t c = 0; c < 4; c++) {
                clip[c] = ((double(projection[c]) * camera[0] + double(projection[4 + c]) * camera[1]) +
                    double(projection[8 + c]) * camera[2]) + projection[12 + c];
            }
            if (!std::isfinite(clip[3]) || clip[3] <= 1e-6) { continue; }
            // Native projector stores each component to float before the
            // emitter adds/subtracts the camera-up height offset.
            const float centerX = float(clip[0] * 212.0 / clip[3] + 212.0) + view[4] * body.heightPixels;
            const float centerY = float(120.0 - clip[1] * 120.0 / clip[3]) - view[5] * body.heightPixels;
            if (!std::isfinite(centerX) || !std::isfinite(centerY) ||
                std::fabs(centerX) > 1e7f || std::fabs(centerY) > 1e7f) { continue; }
            auto &record = result.records[result.count++];
            record.rect = { centerX - body.halfWidth, centerY - body.halfHeight,
                centerX + body.halfWidth, centerY + body.halfHeight };
            record.texcoords = { 0,0,body.texelStep,body.texelStep };
            record.color = body.color;
            record.texture = body.texture;
        }
        return result;
    }
}
