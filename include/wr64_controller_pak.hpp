#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <span>

namespace wr64::controller_pak {

constexpr int kPortCount = 2;
constexpr int kDirectoryEntryCount = 16;
constexpr std::size_t kPageSize = 256;
constexpr std::size_t kDataPageCount = 123;
constexpr std::size_t kCapacityBytes = kPageSize * kDataPageCount;

enum class Result : std::int32_t {
    Ok = 0,
    NoPack = 1,
    NewPack = 2,
    Inconsistent = 3,
    ControllerFailure = 4,
    Invalid = 5,
    BadData = 6,
    DataFull = 7,
    DirectoryFull = 8,
    Exists = 9,
};

struct Key {
    std::uint16_t company_code = 0;
    std::uint32_t game_code = 0;
    std::array<std::uint8_t, 16> game_name{};
    std::array<std::uint8_t, 4> extension_name{};

    bool operator==(const Key&) const = default;
};

struct FileState {
    std::uint32_t file_size = 0;
    Key key{};
};

// Host-side Controller Pak filesystem used by the libultra replacement
// wrappers. Each port has an independent persistent 16-entry, 123-page Pak.
// The implementation deliberately does not participate in accessory
// selection, allowing the runtime's Rumble Pak motor path to remain active at
// the same time.
class Store {
public:
    static Store& instance();

    void set_base_save_path_for_tests(std::filesystem::path path);
    void reset_for_tests();

    Result initialize(int port);
    Result find_file(int port, const Key& key, int& file_number);
    Result free_blocks(int port, std::int32_t& bytes_free);
    Result num_files(int port, std::int32_t& max_files, std::int32_t& files_used);
    Result file_state(int port, int file_number, FileState& state);
    Result allocate_file(int port, const Key& key, std::uint32_t file_size,
                         int& file_number);
    Result delete_file(int port, const Key& key);
    Result read_file(int port, int file_number, std::uint32_t offset,
                     std::span<std::uint8_t> output);
    Result write_file(int port, int file_number, std::uint32_t offset,
                      std::span<const std::uint8_t> input);

private:
    Store();
    ~Store();
    Store(const Store&) = delete;
    Store& operator=(const Store&) = delete;

    struct Impl;
    Impl* impl_;
};

} // namespace wr64::controller_pak
