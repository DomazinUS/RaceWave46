// Include the production implementation to exercise private container/cache and
// async cancellation invariants without adding a test API to the game.
#include "../../src/wr64_achievement_badges.cpp"
#include <iostream>
#include <stdexcept>

using namespace wr64::achievement_badges;
namespace {
unsigned checks = 0;
void check(bool condition, const char* message) {
    ++checks;
    if (!condition) throw std::runtime_error(message);
}
void be(std::vector<char>& bytes, std::uint32_t value) {
    for (int shift = 24; shift >= 0; shift -= 8) bytes.push_back(char(value >> shift));
}
void chunk(std::vector<char>& bytes, const char* type, const std::vector<char>& data) {
    be(bytes, static_cast<std::uint32_t>(data.size()));
    const auto start = bytes.size();
    bytes.insert(bytes.end(), type, type + 4);
    bytes.insert(bytes.end(), data.begin(), data.end());
    be(bytes, crc32(bytes.data() + start, data.size() + 4));
}
std::vector<char> png(unsigned width = 1, unsigned height = 1) {
    std::vector<char> result = {char(137), 80, 78, 71, 13, 10, 26, 10};
    std::vector<char> header;
    be(header, width); be(header, height);
    header.insert(header.end(), {8, 6, 0, 0, 0});
    chunk(result, "IHDR", header);
    // A real zlib stream: one uncompressed row containing filter0 and red RGBA.
    chunk(result, "IDAT", {0x78, 1, 1, 5, 0, char(0xFA), char(0xFF), 0, char(0xFF), 0, 0, char(0xFF), 5, 0, 1, char(0xFF)});
    chunk(result, "IEND", {});
    return result;
}
void write(const std::filesystem::path& path, const std::vector<char>& bytes) {
    std::ofstream out(path, std::ios::binary);
    out.write(bytes.data(), std::streamsize(bytes.size()));
    check(bool(out), "fixture write failed");
}
std::vector<Image> wait_images(std::size_t expected) {
    std::vector<Image> images;
    const auto end = std::chrono::steady_clock::now() + std::chrono::seconds(3);
    while (images.size() < expected && std::chrono::steady_clock::now() < end) {
        auto next = drain_images();
        for (auto& image : next) images.push_back(std::move(image));
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    return images;
}
void offline(const std::filesystem::path& directory) {
    for (const auto* bad : {"", "../129251", "129251_lock", "https://example.org/1", "local\\1", "1/2", "1?x", "1\r\n", "12345678901", "-1"}) {
        check(source_name(bad, false).empty(), "unsupported badge produced a source");
        request(bad, true);
    }
    check(source_name("129251", false) == "?/wr64/achievement-badges/129251.png", "color source mismatch");
    check(source_name("129251", true) == "?/wr64/achievement-badges/129251-locked.png", "locked source mismatch");
    for (const bool locked : {false, true})
        check(source_name("129251", locked).starts_with("?/wr64/achievement-badges/"),
            "badge source is not rooted in Rml's virtual image namespace");
    check(source_name("00001", false) != source_name("1", false), "badge name identity lost leading zeros");
    check(cache.pending.empty(), "unsupported requests were queued");
    check(crc32("123456789", 9) == 0xCBF43926u, "PNG CRC known vector mismatch");
    const auto good = png();
    check(valid_png(good), "valid PNG rejected");
    for (std::size_t i = 0; i < good.size(); ++i) {
        check(!valid_png(std::vector<char>(good.begin(), good.begin() + i)), "truncated PNG accepted");
        auto corrupt = good; corrupt[i] ^= 1;
        check(!valid_png(corrupt), "corrupted PNG accepted");
    }
    check(!valid_png(png(513, 1)), "oversized dimensions accepted");
    check(!valid_png(png(1, 0)), "zero height accepted");
    auto trailing = good; trailing.push_back(0);
    check(!valid_png(trailing), "trailing PNG data accepted");
    check(!valid_png(std::vector<char>(image_limit + 1, 0)), "oversized PNG accepted");

    // Hold off the worker entirely to make priority/deduplication deterministic.
    cache.stopping.store(false);
    request("10"); request("20"); request("30"); request("20", true);
    check(cache.pending.size() == 6 && cache.requested.size() == 6, "duplicate request grew queue");
    check(cache.pending[0].filename() == "20.png" && cache.pending[1].filename() == "20_lock.png", "toast did not promote both variants color first");
    request("40", true);
    check(cache.pending[0].filename() == "40.png" && cache.pending[1].filename() == "40_lock.png", "new priority color not first");
    for (unsigned i = 100; i < 1000; ++i) request(std::to_string(i));
    check(cache.pending.size() == image_count_limit && cache.requested.size() == image_count_limit, "queue/dedupe cap not enforced");
    shutdown();
    check(cache.pending.empty() && cache.requested.empty(), "shutdown did not clear pending state");

    std::filesystem::create_directories(directory / "achievement-badges");
    auto cache_dir = directory / "achievement-badges";
    write(cache_dir / "129251.png", good);
    write(cache_dir / "129251_lock.png", good);
    check(load_cached(cache_dir / "129251.png") == good, "disk cache did not validate/read PNG");
    write(cache_dir / "99.png", std::vector<char>{'n', 'o', 't', ' ', 'P', 'N', 'G'});
    check(load_cached(cache_dir / "99.png").empty(), "invalid cache content accepted");
    save_cached(cache_dir / "99.png", good);
    check(load_cached(cache_dir / "99.png") == good, "atomic valid cache replacement failed");
    initialize(directory);
    request("129251"); request("129251", true);
    const auto images = wait_images(2);
    check(images.size() == 2, "both cached image variants were not delivered");
    for (const auto& image : images) {
        check(image.bytes == good, "queued PNG bytes changed");
        check(image.source == source_name("129251", false) || image.source == source_name("129251", true), "delivered synthetic source mismatched public API");
    }
    check(images[0].source != images[1].source, "delivered same variant twice");
    request("129251");
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    check(drain_images().empty(), "ready image downloaded/delivered twice");
    auto stop_start = std::chrono::steady_clock::now();
    shutdown(); shutdown();
    check(std::chrono::steady_clock::now() - stop_start < std::chrono::seconds(1), "idle shutdown did not finish promptly");
    initialize(directory); request("129251");
    check(wait_images(2).size() == 2, "reinitialize did not reset image deduplication");
    shutdown();

    // Prune only the fixed cache namespace; keep unrelated files and directories.
    for (unsigned i = 1000; i < 1520; ++i) write(cache_dir / (std::to_string(i) + ".png"), good);
    write(cache_dir / "keep-user-file.png", {'x'});
    std::filesystem::create_directory(cache_dir / "88.png");
    trim_cache(cache_dir);
    std::size_t files = 0;
    for (const auto& entry : std::filesystem::directory_iterator(cache_dir))
        if (entry.is_regular_file() && cache_filename(entry.path().filename().string())) ++files;
    check(files == image_count_limit, "disk entry cap not enforced");
    check(std::filesystem::exists(cache_dir / "keep-user-file.png") && std::filesystem::is_directory(cache_dir / "88.png"), "pruning changed unrelated content");
    auto huge = cache_dir / "999999.png";
    write(huge, good);
    std::filesystem::resize_file(huge, disk_limit + 1);
    check(load_cached(huge).empty(), "oversized disk entry allocated/read");
    trim_cache(cache_dir);
    std::uintmax_t total = 0;
    for (const auto& entry : std::filesystem::directory_iterator(cache_dir))
        if (entry.is_regular_file() && cache_filename(entry.path().filename().string())) total += entry.file_size();
    check(total <= disk_limit, "disk byte cap not enforced");
}

void live(const std::filesystem::path& directory) {
#ifdef _WIN32
    std::atomic<bool> stopping{false};
    Downloader downloader;
    for (const bool locked : {false, true}) {
        const auto bytes = downloader.fetch(Task{"129251", locked}, stopping);
        check(valid_png(bytes), "official public Sunny Beach badge GET failed");
        write(directory / (locked ? "official-129251-lock.png" : "official-129251.png"), bytes);
        std::cout << "Official public badge " << (locked ? "locked" : "color") << ": " << bytes.size() << " bytes\n";
    }
    // Request cancellation exercises the production async handle/state teardown;
    // neither this transport nor this fixture can send account credentials.
    for (unsigned i = 0; i < 10; ++i) {
        std::atomic<bool> cancel{false};
        const auto start = std::chrono::steady_clock::now();
        std::thread caller([&] { Downloader connection; connection.fetch(Task{"129252", false}, cancel); });
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        cancel.store(true);
        caller.join();
        check(std::chrono::steady_clock::now() - start < std::chrono::seconds(2), "active request cancellation blocked shutdown");
    }
#endif
}
}

int main(int argc, char** argv) {
    try {
        const auto directory = std::filesystem::temp_directory_path() /
            ("wr64-badge-test-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
        std::filesystem::create_directories(directory);
        offline(directory);
        if (argc > 1 && std::string_view(argv[1]) == "--live-public-images") live(directory);
        std::cout << "PASS: " << checks << " checks; fixture files: " << directory.string() << '\n';
        return 0;
    } catch (const std::exception& error) {
        shutdown();
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
