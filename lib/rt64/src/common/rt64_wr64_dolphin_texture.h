#pragma once

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "hle/rt64_draw_call.h"
#include "xxHash/xxh3.h"

namespace RT64 {

// Exact compatibility with Dolphin's tex1 names. This runs only when the
// texture cache first encounters a native hash, never on the draw path. DDS
// pixels are neither compared nor guessed; indexed textures require both the
// GX texture hash and palette hash. Unsupported layouts retain native art.
class Wr64DolphinTextureIndex {
    struct Key {
        uint64_t texture = 0, palette = 0;
        uint32_t width = 0, height = 0, format = 0;
        bool hasPalette = false;
        bool operator==(const Key &other) const {
            return texture == other.texture && palette == other.palette && width == other.width &&
                height == other.height && format == other.format && hasPalette == other.hasPalette;
        }
    };
    struct KeyHash {
        size_t operator()(const Key &key) const {
            return size_t(key.texture ^ (key.palette + (uint64_t(key.width) << 32) +
                (uint64_t(key.height) << 8) + key.format + uint64_t(key.hasPalette)));
        }
    };
    std::unordered_map<Key, std::string, KeyHash> paths;
    std::unordered_set<uint64_t> shapes;

    static uint64_t shape(uint32_t width, uint32_t height, uint32_t format) {
        return (uint64_t(width) << 32) | (uint64_t(height) << 8) | format;
    }
    static uint16_t rgb5a3(uint16_t value, unsigned variant) {
        if (variant == 2 && !(value & 1)) return 0;
        if ((value & 1) && variant != 1) return uint16_t(0x8000 | (value >> 1));
        return uint16_t(((value & 1) ? 0x7000 : 0) | ((value >> 12) << 8) |
            (((value >> 7) & 15) << 4) | ((value >> 2) & 15));
    }
    static void big16(std::vector<uint8_t> &bytes, uint16_t value) {
        bytes.push_back(uint8_t(value >> 8));
        bytes.push_back(uint8_t(value));
    }

public:
    void addPath(const std::string &path) {
        const auto slash = path.find_last_of("/\\");
        const auto name = path.substr(slash == std::string::npos ? 0 : slash + 1);
        static const std::regex pattern("^tex1_([0-9]+)x([0-9]+)_([0-9a-f]{16})(?:_([0-9a-f]{16}))?_([0-9]+)\\.dds$",
            std::regex::ECMAScript | std::regex::icase);
        std::smatch match;
        if (!std::regex_match(name, match, pattern)) return;
        try {
            const auto width = std::stoul(match[1].str()), height = std::stoul(match[2].str());
            const auto format = std::stoul(match[5].str());
            if (!width || !height || width > 4096 || height > 4096 || format > 255) return;
            Key key{std::stoull(match[3].str(), nullptr, 16),
                match[4].matched ? std::stoull(match[4].str(), nullptr, 16) : 0,
                uint32_t(width), uint32_t(height), uint32_t(format), match[4].matched};
            const auto inserted = paths.emplace(key, path);
            // Duplicate identities from distinct files are ambiguous.
            if (!inserted.second && inserted.first->second != path) inserted.first->second.clear();
            shapes.insert(shape(key.width, key.height, key.format));
        }
        catch (const std::exception &) { /* Malformed filenames are ignored. */ }
    }

    size_t size() const { return paths.size(); }

    std::string match(const uint8_t *tmem, size_t byteCount, uint32_t width, uint32_t height,
        uint32_t tlut, const LoadTile &tile) const {
        if (!tmem || byteCount != 4096 || !width || !height || uint64_t(width) * height > 16384 || !tile.line) return {};
        uint32_t gx = 255;
        if (tile.fmt == 0 && tile.siz == 2) gx = 5;
        else if (tile.fmt == 0 && tile.siz == 3) gx = 6;
        else if (tile.fmt == 2 && tile.siz == 1) gx = 9;
        else if (tile.fmt == 3 && tile.siz == 1) gx = 2;
        else if (tile.fmt == 3 && tile.siz == 2) gx = 3;
        if (gx == 255 || !shapes.count(shape(width, height, gx))) return {};
        const uint32_t blockWidth = (gx == 2 || gx == 9) ? 8 : 4;
        if (width % blockWidth || height % 4) return {};
        const uint32_t paletteType = tlut > 3 ? (tlut >> 14) & 3 : tlut;
        if (gx == 9 && paletteType != 2 && paletteType != 3) return {};
        const uint32_t stride = uint32_t(tile.line) * 8, start = uint32_t(tile.tmem) * 8;
        const uint32_t mask = gx == 6 || paletteType ? 0x7ff : 0xfff;
        const auto get = [&](uint32_t offset, uint32_t y, uint32_t bank = 0) {
            uint32_t address = start + offset;
            if (y & 1) address = start + (offset / stride) * stride + ((offset % stride) ^ 4);
            return tmem[((address & mask) | bank) & 0xfff];
        };
        std::vector<uint32_t> pixels;
        pixels.reserve(width * height);
        uint32_t minIndex = 255, maxIndex = 0;
        for (uint32_t y = 0; y < height; ++y) {
            for (uint32_t x = 0; x < width; ++x) {
                const uint32_t offset = y * stride + ((x << (gx == 6 ? 2 : tile.siz)) >> 1);
                uint32_t pixel = get(offset, y);
                if (gx == 6) pixel = (pixel << 24) | (uint32_t(get(offset + 1, y)) << 16) |
                    (uint32_t(get(offset, y, 0x800)) << 8) | get(offset + 1, y, 0x800);
                else if (tile.siz == 2) pixel = (pixel << 8) | get(offset + 1, y);
                pixels.push_back(pixel);
                if (gx == 9) { minIndex = std::min(minIndex, pixel); maxIndex = std::max(maxIndex, pixel); }
            }
        }
        std::string result;
        bool ambiguous = false;
        const auto accept = [&](const Key &key) {
            const auto found = paths.find(key);
            if (found == paths.end()) return;
            if (found->second.empty() || (!result.empty() && result != found->second)) ambiguous = true;
            else result = found->second;
        };
        std::vector<uint8_t> encoded;
        encoded.reserve(width * height * 4);
        for (unsigned variant = 0; variant < (gx == 5 ? 3u : 1u); ++variant) {
            encoded.clear();
            for (uint32_t by = 0; by < height; by += 4) {
                for (uint32_t bx = 0; bx < width; bx += blockWidth) {
                    for (uint32_t y = by; y < by + 4; ++y) {
                        for (uint32_t x = bx; x < bx + blockWidth; ++x) {
                            const uint32_t pixel = pixels[y * width + x];
                            if (gx == 9) encoded.push_back(uint8_t(pixel));
                            else if (gx == 2) encoded.push_back(uint8_t(((pixel & 15) << 4) | (pixel >> 4)));
                            else if (gx == 3) { encoded.push_back(uint8_t(pixel)); encoded.push_back(uint8_t(pixel >> 8)); }
                            else if (gx == 5) big16(encoded, rgb5a3(uint16_t(pixel), variant));
                            else if (gx == 6) { encoded.push_back(uint8_t(pixel)); encoded.push_back(uint8_t(pixel >> 24)); }
                        }
                    }
                    if (gx == 6) {
                        for (uint32_t y = by; y < by + 4; ++y) {
                            for (uint32_t x = bx; x < bx + 4; ++x) {
                                const auto pixel = pixels[y * width + x];
                                encoded.push_back(uint8_t(pixel >> 16)); encoded.push_back(uint8_t(pixel >> 8));
                            }
                        }
                    }
                }
            }
            Key key{XXH64(encoded.data(), encoded.size(), 0), 0, width, height, gx, gx == 9};
            if (gx != 9) accept(key);
            else {
                std::vector<uint8_t> palette;
                palette.reserve((maxIndex - minIndex + 1) * 2);
                for (unsigned pv = 0; pv < (paletteType == 2 ? 3u : 1u); ++pv) {
                    palette.clear();
                    for (uint32_t i = minIndex; i <= maxIndex; ++i) {
                        const uint16_t value = uint16_t((uint32_t(tmem[0x800 + i * 8]) << 8) | tmem[0x801 + i * 8]);
                        if (paletteType == 2) big16(palette, rgb5a3(value, pv));
                        else { palette.push_back(uint8_t(value)); palette.push_back(uint8_t(value >> 8)); }
                    }
                    key.palette = XXH64(palette.data(), palette.size(), 0);
                    accept(key);
                }
            }
        }
        return ambiguous ? std::string{} : result;
    }
};
}
