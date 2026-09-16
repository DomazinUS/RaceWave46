#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <mutex>
#include <vector>
#include "../../include/rt64_extended_gbi.h"

namespace RT64 {
    inline bool wr64DolphinSunNativeExitEnabled() {
        static const bool enabled = [] {
            const char *value = std::getenv("WR64_DOLPHIN_SUN_NATIVE_EXIT");
            // Enabled by default; exact 0 opts out.
            return !value || !value[0] || (value[0] == '1' && value[1] == '\0');
        }();
        return enabled;
    }

    // Native producer snapshot, captured before clipping and bound to exactly
    // one emitted packet. Admission/generation belong to the native producer;
    // neither a texture match nor a renderer history can manufacture them.
    struct Wr64DolphinSunSprite {
        uint64_t generation = 0;
        uint32_t context = 0, recordId = 0, view = 0;
        bool admitted = false;
        float centerX = 0, centerY = 0, radiusX = 0, radiusY = 0;
        int16_t preclipS = 0, preclipT = 0, dsdx = 0, dtdy = 0;
        bool flip = false;
    };
    using Wr64DolphinSunRect = std::array<float, 4>; // Signed native pixels.
    struct Wr64DolphinSunRectPair {
        uint64_t key = 0;
        Wr64DolphinSunRect previous{}, current{};
    };
    constexpr uint64_t Wr64DolphinSunSpriteTexture = 0x79185A8F164D1366ULL;
    constexpr uint32_t Wr64DolphinSunNoVertices = UINT32_MAX;

    inline bool wr64DolphinSunSpriteValid(const Wr64DolphinSunSprite &sprite) {
        if (!wr64DolphinSunNativeExitEnabled() || !sprite.admitted || !sprite.generation ||
            sprite.recordId != 0x801C4170u || (sprite.context & 0xFFFFFFu) != 0x010100u ||
            sprite.view != 0 || sprite.flip || sprite.radiusX != 12.0f || sprite.radiusY != 12.0f ||
            sprite.preclipS != 0 || sprite.preclipT != 0 || sprite.dsdx != 0x555 || sprite.dtdy != 0x555) return false;
        for (float value : {sprite.centerX, sprite.centerY, sprite.radiusX, sprite.radiusY})
            if (!std::isfinite(value)) return false;
        const float width = sprite.radiusX * 2.0f, height = sprite.radiusY * 2.0f;
        return std::abs(sprite.centerX) <= 16384.0f && std::abs(sprite.centerY) <= 16384.0f &&
            width >= 1.0f && width <= 512.0f && height >= 1.0f && height <= 512.0f &&
            width == std::floor(width) && height == std::floor(height);
    }

    inline Wr64DolphinSunRect wr64DolphinSunFullRect(const Wr64DolphinSunSprite &sprite) {
        return {sprite.centerX - sprite.radiusX, sprite.centerY - sprite.radiusY,
            sprite.centerX + sprite.radiusX, sprite.centerY + sprite.radiusY};
    }

    inline std::array<float, 4> wr64DolphinSunFullUV(const Wr64DolphinSunSprite &sprite) {
        // Preserve the native RDP endpoint quantization. For a 24-pixel DP
        // disk and derivative 1365 this is 0..31.96875, not 0..32.
        const int64_t width = int64_t(sprite.radiusX * 2.0f);
        const int64_t height = int64_t(sprite.radiusY * 2.0f);
        const int64_t lrs = (int64_t(sprite.preclipS) * 128 + int64_t(sprite.dsdx) * width * 4) >> 7;
        const int64_t lrt = (int64_t(sprite.preclipT) * 128 + int64_t(sprite.dtdy) * height * 4) >> 7;
        return {sprite.preclipS / 32.0f, sprite.preclipT / 32.0f, float(lrs) / 32.0f, float(lrt) / 32.0f};
    }

    inline bool wr64DolphinSunSameSprite(const Wr64DolphinSunSprite &previous,
        const Wr64DolphinSunSprite &current) {
        return wr64DolphinSunSpriteValid(previous) && wr64DolphinSunSpriteValid(current) &&
            previous.generation == current.generation && previous.context == current.context &&
            previous.recordId == current.recordId && previous.view == current.view &&
            previous.radiusX == current.radiusX && previous.radiusY == current.radiusY &&
            previous.preclipS == current.preclipS && previous.preclipT == current.preclipT &&
            previous.dsdx == current.dsdx && previous.dtdy == current.dtdy && previous.flip == current.flip;
    }

    inline bool wr64DolphinSunMotionContinuous(const Wr64DolphinSunSprite &previous,
        const Wr64DolphinSunSprite &current, float maximumStepPixels) {
        if (!wr64DolphinSunSameSprite(previous, current) || !std::isfinite(maximumStepPixels) ||
            maximumStepPixels <= 0.0f) return false;
        const double dx = double(current.centerX) - previous.centerX;
        const double dy = double(current.centerY) - previous.centerY;
        return dx * dx + dy * dy <= double(maximumStepPixels) * maximumStepPixels;
    }

    inline Wr64DolphinSunRect wr64DolphinSunInterpolate(const Wr64DolphinSunRectPair &pair, float weight) {
        const float t = std::isfinite(weight) ? std::clamp(weight, 0.0f, 1.0f) : 1.0f;
        if (t == 0.0f) return pair.previous;
        if (t == 1.0f) return pair.current;
        Wr64DolphinSunRect result;
        const float left = pair.previous[0] + (pair.current[0] - pair.previous[0]) * t;
        const float top = pair.previous[1] + (pair.current[1] - pair.previous[1]) * t;
        // A matched producer retains its size and texture layout exactly.
        result = {left, top, left + (pair.current[2] - pair.current[0]),
            top + (pair.current[3] - pair.current[1])};
        return result;
    }

    // Called after all original raw vertex starts have been assigned, before
    // upload. Original vertices remain untouched for native RAM rendering and
    // fallback. Only a presentation consumer selects this additional quad.
    template <typename DrawData>
    uint32_t wr64DolphinSunAppendVertices(DrawData &data, uint32_t originalStart,
        const Wr64DolphinSunSprite &sprite) {
        if (!wr64DolphinSunSpriteValid(sprite)) return Wr64DolphinSunNoVertices;
        const size_t count = data.triPosFloats.size() / 4;
        if (data.triPosFloats.size() % 4 || data.triTcFloats.size() != count * 2 ||
            data.triColorFloats.size() != count * 4 || count > UINT32_MAX - 6 ||
            size_t(originalStart) + 6 > count) return Wr64DolphinSunNoVertices;
        const auto uv = wr64DolphinSunFullUV(sprite);
        // This path only owns the complete 32x32 DP disk texture.
        if (uv[0] < 0 || uv[1] < 0 || uv[2] <= uv[0] || uv[3] <= uv[1] ||
            uv[2] > 32 || uv[3] > 32) return Wr64DolphinSunNoVertices;
        std::array<float, 24> positions, colors;
        std::copy_n(data.triPosFloats.begin() + size_t(originalStart) * 4, 24, positions.begin());
        std::copy_n(data.triColorFloats.begin() + size_t(originalStart) * 4, 24, colors.begin());
        const std::array<float, 12> texcoords = {
            uv[0], uv[1], uv[2], uv[1], uv[0], uv[3],
            uv[2], uv[3], uv[2], uv[1], uv[0], uv[3]};
        data.triPosFloats.insert(data.triPosFloats.end(), positions.begin(), positions.end());
        data.triTcFloats.insert(data.triTcFloats.end(), texcoords.begin(), texcoords.end());
        data.triColorFloats.insert(data.triColorFloats.end(), colors.begin(), colors.end());
        return uint32_t(count);
    }

    template <typename DrawCall, typename DrawData>
    bool wr64DolphinSunClaimValid(const DrawCall &call, const DrawData &data, bool rectangle) {
        if (!rectangle || !wr64DolphinSunSpriteValid(call.wr64DolphinSunSprite) ||
            call.wr64DolphinSunVertexStart == Wr64DolphinSunNoVertices || call.triangleCount != 2 ||
            call.rectLeftOrigin != G_EX_ORIGIN_NONE || call.rectRightOrigin != G_EX_ORIGIN_NONE ||
            call.rectDsdx != call.wr64DolphinSunSprite.dsdx || call.rectDtdy != call.wr64DolphinSunSprite.dtdy ||
            !call.tileCount || call.tileIndex >= data.callTiles.size()) return false;
        const auto &tile = data.callTiles[call.tileIndex];
        return tile.valid && !tile.tileCopyUsed && !tile.rawTMEM &&
            tile.tmemHashOrID == Wr64DolphinSunSpriteTexture && tile.sampleWidth == 32 && tile.sampleHeight == 32 &&
            size_t(call.wr64DolphinSunVertexStart) + 6 <= data.triPosFloats.size() / 4;
    }

    struct Wr64DolphinSunCommand {
        uint32_t address = 0;
        std::array<uint32_t, 6> words{};
        Wr64DolphinSunSprite sprite{};
    };
    struct Wr64DolphinSunBatch {
        uint64_t sequence = 0;
        std::vector<Wr64DolphinSunCommand> commands;
    };
    inline std::mutex wr64DolphinSunMutex;
    inline std::vector<Wr64DolphinSunCommand> wr64DolphinSunPending;
    inline bool wr64DolphinSunOverflow = false;
    inline thread_local Wr64DolphinSunBatch wr64DolphinSunClaimed;
    constexpr size_t Wr64DolphinSunMaxCommands = 64;

    inline uint32_t wr64DolphinSunReadWord(const uint8_t *ram, uint32_t address) {
        uint32_t word;
        std::memcpy(&word, ram + address, sizeof(word));
        return word;
    }

    inline bool wr64DolphinSunRecord(const uint8_t *ram, uint32_t packetAddress,
        const Wr64DolphinSunSprite &sprite) {
        const uint32_t address = packetAddress & 0x1FFFFFFFu;
        if (!ram || !wr64DolphinSunSpriteValid(sprite) || !address || (address & 7) ||
            address > 0x800000u - 24) return false;
        Wr64DolphinSunCommand command;
        command.address = address;
        command.sprite = sprite;
        for (uint32_t i = 0; i < 6; ++i) command.words[i] = wr64DolphinSunReadWord(ram, address + i * 4);
        if ((command.words[0] >> 24) != 0xE4 || command.words[2] != 0xB3000000u ||
            command.words[4] != 0xB2000000u || int16_t(command.words[5] >> 16) != sprite.dsdx ||
            int16_t(command.words[5]) != sprite.dtdy) return false;
        std::lock_guard<std::mutex> lock(wr64DolphinSunMutex);
        if (wr64DolphinSunOverflow) return false;
        if (wr64DolphinSunPending.size() >= Wr64DolphinSunMaxCommands) {
            wr64DolphinSunPending.clear();
            wr64DolphinSunOverflow = true;
            return false;
        }
        wr64DolphinSunPending.push_back(command);
        return true;
    }

    inline Wr64DolphinSunBatch wr64DolphinSunSeal(uint64_t sequence) {
        std::lock_guard<std::mutex> lock(wr64DolphinSunMutex);
        Wr64DolphinSunBatch batch;
        batch.sequence = sequence;
        batch.commands.swap(wr64DolphinSunPending);
        wr64DolphinSunOverflow = false;
        return batch;
    }

    inline Wr64DolphinSunSprite wr64DolphinSunLookup(uint64_t sequence, uint32_t packetAddress,
        const uint8_t *ram) {
        if (!wr64DolphinSunNativeExitEnabled() || !sequence ||
            sequence != wr64DolphinSunClaimed.sequence || !ram) return {};
        const uint32_t address = packetAddress & 0x1FFFFFFFu;
        if (!address || (address & 7) || address > 0x800000u - 24) return {};
        const Wr64DolphinSunCommand *match = nullptr;
        for (const auto &command : wr64DolphinSunClaimed.commands) {
            if (command.address != address) continue;
            if (match) return {}; // Duplicate producer ownership is ambiguous.
            for (uint32_t i = 0; i < 6; ++i)
                if (command.words[i] != wr64DolphinSunReadWord(ram, address + i * 4)) return {};
            match = &command;
        }
        return match ? match->sprite : Wr64DolphinSunSprite{};
    }
}
