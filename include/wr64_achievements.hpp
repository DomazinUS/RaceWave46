#pragma once

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

namespace wr64::achievements {
struct Achievement {
    uint32_t id = 0;
    std::string title, description;
    uint32_t points = 0;
    bool unlocked = false;
    std::string progress;
    std::string badge_name;
    int64_t unlock_time = 0;
    float rarity = -1.0f, rarity_hardcore = -1.0f;
};
struct Snapshot {
    uint64_t revision = 0, account_generation = 0;
    bool busy = false, logged_in = false, game_loaded = false;
    std::string username, status;
    uint32_t unlocked = 0, total = 0, points = 0;
    std::vector<Achievement> achievements;
    bool catalog_loaded = false, catalog_busy = false;
    std::string catalog_status;
    uint32_t total_points = 0;
};
struct Notification {
    uint64_t account_generation = 0;
    std::string title, body;
    std::string badge_name;
};
void initialize(const std::filesystem::path& data_directory);
Snapshot snapshot();
void request_login(std::string username, std::string password, bool remember);
void request_logout();
void request_catalog_refresh();
std::vector<Notification> drain_notifications();
void ui_tick();
void native_frame(uint8_t* rdram);
void set_game_identity(std::string hash);
void game_stopped();
void shutdown();
}
