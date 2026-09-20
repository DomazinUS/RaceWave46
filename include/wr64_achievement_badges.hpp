#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace wr64::achievement_badges {
struct Image {
    std::string source;
    std::vector<char> bytes;
};

// One independent, credentialless image worker. Call shutdown before reinitializing.
void initialize(const std::filesystem::path& runtime_directory);
// Queues both official variants; priority requests move pending images to the front.
// Only numeric official BadgeName values are supported. Other names use the UI fallback.
void request(std::string badge_name, bool priority = false);
// The UI thread uploads these PNG files. A source becomes usable only after upload.
std::vector<Image> drain_images();
std::string source_name(const std::string& badge_name, bool locked);
void shutdown();
}
