#include "wr64_badge_rounding.hpp"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {
unsigned checks = 0;
void check(bool condition, const char* message) {
    ++checks;
    if (!condition) throw std::runtime_error(message);
}
unsigned byte(char value) { return static_cast<unsigned char>(value); }
std::size_t offset(unsigned x, unsigned y, unsigned width) { return (std::size_t(y) * width + x) * 4; }
std::vector<char> solid(unsigned width, unsigned height, unsigned alpha = 255) {
    std::vector<char> result(std::size_t(width) * height * 4);
    for (std::size_t i = 0; i < result.size(); i += 4) {
        result[i] = char(230); result[i + 1] = 70; result[i + 2] = 11; result[i + 3] = char(alpha);
    }
    return result;
}
void verify_image(const std::vector<char>& original, unsigned width, unsigned height) {
    auto rounded = original;
    check(wr64::achievement_badges::round_badge_pixels(rounded, width, height), "valid RGBA rejected");
    bool same_rgb = true, alpha_not_increased = true, interior_unchanged = true;
    unsigned fractional_edges = 0;
    const unsigned margin = (std::min(width, height) + 9) / 10;
    for (unsigned y = 0; y < height; ++y) for (unsigned x = 0; x < width; ++x) {
        const auto i = offset(x, y, width);
        for (unsigned c = 0; c < 3; ++c) same_rgb &= rounded[i + c] == original[i + c];
        alpha_not_increased &= byte(rounded[i + 3]) <= byte(original[i + 3]);
        fractional_edges += byte(rounded[i + 3]) > 0 && byte(rounded[i + 3]) < byte(original[i + 3]);
        if (x >= margin && x < width - margin && y >= margin && y < height - margin)
            for (unsigned c = 0; c < 4; ++c) interior_unchanged &= rounded[i + c] == original[i + c];
    }
    check(same_rgb, "rounding changed straight RGB at interior, antialias edge, or transparent corner");
    check(alpha_not_increased, "mask increased original alpha");
    check(interior_unchanged, "rounding changed an interior pixel");
    check(fractional_edges > 0, "rounded boundary has no antialiased coverage");
    for (const auto& corner : {std::array<unsigned, 2>{0, 0}, {width - 1, 0}, {0, height - 1}, {width - 1, height - 1}})
        check(byte(rounded[offset(corner[0], corner[1], width) + 3]) == 0, "outer corner is not transparent");
    const auto center = offset(width / 2, height / 2, width);
    check(std::equal(rounded.begin() + center, rounded.begin() + center + 4, original.begin() + center),
        "center RGBA changed");
}
void synthetic() {
    const auto original = solid(64, 64);
    verify_image(original, 64, 64);
    auto rounded = original;
    wr64::achievement_badges::round_badge_pixels(rounded, 64, 64);
    bool symmetric = true;
    for (unsigned y = 0; y < 64; ++y) for (unsigned x = 0; x < 64; ++x) {
        const auto alpha = rounded[offset(x, y, 64) + 3];
        symmetric &= alpha == rounded[offset(63 - x, y, 64) + 3] && alpha == rounded[offset(x, 63 - y, 64) + 3];
    }
    check(symmetric, "opposite rounded corners have different coverage");
    const unsigned edge_alpha = byte(rounded[offset(3, 0, 64) + 3]);
    check(edge_alpha > 0 && edge_alpha < 255, "64px round radius lacks a one-texel fractional boundary");
    check(rounded[offset(6, 0, 64) + 3] == char(255), "10% corner radius changed the straight top edge");

    auto translucent = solid(64, 64, 128);
    verify_image(translucent, 64, 64);
    wr64::achievement_badges::round_badge_pixels(translucent, 64, 64);
    check(byte(translucent[offset(32, 32, 64) + 3]) == 128, "original interior alpha was not preserved");
    const unsigned expected = (edge_alpha * 128u + 127u) / 255u;
    const unsigned actual = byte(translucent[offset(3, 0, 64) + 3]);
    check(actual + 1 >= expected && actual <= expected + 1, "edge alpha did not combine mask and original alpha once");
    auto transparent = solid(64, 64, 0);
    const auto hidden_original = transparent;
    check(wr64::achievement_badges::round_badge_pixels(transparent, 64, 64) && transparent == hidden_original,
        "transparent straight RGBA content was changed");
    verify_image(solid(80, 40), 80, 40);

    for (const auto size : {std::array<unsigned, 2>{0, 64}, {64, 0}, {513, 64}, {64, 513}}) {
        auto invalid = original;
        check(!wr64::achievement_badges::round_badge_pixels(invalid, size[0], size[1]) && invalid == original,
            "invalid dimensions were accepted or changed input");
    }
    for (int delta : {-1, 1}) {
        auto invalid = original; invalid.resize(invalid.size() + delta);
        const auto before = invalid;
        check(!wr64::achievement_badges::round_badge_pixels(invalid, 64, 64) && invalid == before,
            "inexact RGBA payload was accepted or changed input");
    }
    auto maximum = solid(512, 512);
    check(wr64::achievement_badges::round_badge_pixels(maximum, 512, 512), "valid maximum dimensions rejected");
    auto minimum = solid(1, 1);
    check(wr64::achievement_badges::round_badge_pixels(minimum, 1, 1), "valid minimum dimensions rejected");
}
std::vector<char> read(const std::filesystem::path& path) {
    std::ifstream file(path, std::ios::binary);
    return {(std::istreambuf_iterator<char>(file)), {}};
}
void cached_png(const std::filesystem::path& path) {
    const auto bytes = read(path);
    check(!bytes.empty() && bytes.size() <= 512 * 1024, "cached PNG missing or too large");
    int width = 0, height = 0, channels = 0;
    auto* decoded = stbi_load_from_memory(reinterpret_cast<const unsigned char*>(bytes.data()), int(bytes.size()),
        &width, &height, &channels, 4);
    check(decoded != nullptr && width == 64 && height == 64, "cached badge did not decode as 64x64 RGBA");
    std::vector<char> rgba(reinterpret_cast<char*>(decoded), reinterpret_cast<char*>(decoded) + width * height * 4);
    stbi_image_free(decoded);
    verify_image(rgba, unsigned(width), unsigned(height));
    check(read(path) == bytes, "cached original PNG changed");
    std::cout << "Verified cached PNG " << path.filename().string() << ": " << bytes.size() << " bytes, RGB preserved\n";
}
}

int main(int argc, char** argv) {
    try {
        synthetic();
        for (int i = 1; i < argc; ++i) cached_png(argv[i]);
        std::cout << "PASS badge rounding: " << checks << " checks; straight RGBA, alpha-only mask; no GUI/network\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL badge rounding: " << error.what() << '\n';
        return 1;
    }
}
