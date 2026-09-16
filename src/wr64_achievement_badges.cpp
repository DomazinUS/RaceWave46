#include "wr64_achievement_badges.hpp"

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <cstring>
#include <deque>
#include <fstream>
#include <mutex>
#include <string_view>
#include <thread>
#include <unordered_set>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <winhttp.h>
#endif

namespace wr64::achievement_badges {
namespace {
constexpr std::size_t image_limit = 512 * 1024;
constexpr std::size_t image_count_limit = 512;
constexpr std::size_t ready_limit = 16 * 1024 * 1024;
constexpr std::uintmax_t disk_limit = 32 * 1024 * 1024;

bool valid_name(std::string_view name) {
    return !name.empty() && name.size() <= 10 &&
        std::all_of(name.begin(), name.end(), [](char c) { return c >= '0' && c <= '9'; });
}

struct Task {
    std::string name;
    bool locked;
    std::string filename() const { return name + (locked ? "_lock.png" : ".png"); }
};

std::uint32_t big_endian(const char* p) {
    const auto* b = reinterpret_cast<const unsigned char*>(p);
    return (std::uint32_t(b[0]) << 24) | (std::uint32_t(b[1]) << 16) |
        (std::uint32_t(b[2]) << 8) | b[3];
}

std::uint32_t crc32(const char* bytes, std::size_t count) {
    std::uint32_t crc = ~0u;
    for (std::size_t i = 0; i < count; ++i) {
        crc ^= static_cast<unsigned char>(bytes[i]);
        for (unsigned bit = 0; bit < 8; ++bit)
            crc = (crc >> 1) ^ (0xEDB88320u & (0u - (crc & 1)));
    }
    return ~crc;
}

// Validate the entire bounded PNG container before either caching or handing it
// to the UI decoder. Decoding remains the frontend's job; dimensions are bounded
// here so a small compressed file cannot ask it to allocate a huge image.
bool valid_png(const std::vector<char>& bytes) {
    constexpr unsigned char signature[] = {137, 80, 78, 71, 13, 10, 26, 10};
    if (bytes.size() < 57 || bytes.size() > image_limit ||
        std::memcmp(bytes.data(), signature, sizeof(signature)) != 0) return false;
    bool header = false, pixels = false, palette = false;
    unsigned char color_type = 0;
    for (std::size_t offset = 8; offset < bytes.size();) {
        if (bytes.size() - offset < 12) return false;
        const std::size_t count = big_endian(bytes.data() + offset);
        if (count > bytes.size() - offset - 12) return false;
        const char* type = bytes.data() + offset + 4;
        const char* data = type + 4;
        if (crc32(type, count + 4) != big_endian(data + count)) return false;
        if (!header) {
            if (std::memcmp(type, "IHDR", 4) != 0 || count != 13) return false;
            const auto width = big_endian(data), height = big_endian(data + 4);
            if (width == 0 || height == 0 || width > 512 || height > 512) return false;
            const auto depth = static_cast<unsigned char>(data[8]);
            color_type = static_cast<unsigned char>(data[9]);
            const bool valid_depth = (color_type == 0 && (depth == 1 || depth == 2 || depth == 4 || depth == 8 || depth == 16)) ||
                (color_type == 3 && (depth == 1 || depth == 2 || depth == 4 || depth == 8)) ||
                ((color_type == 2 || color_type == 4 || color_type == 6) && (depth == 8 || depth == 16));
            if (!valid_depth || data[10] != 0 || data[11] != 0 || static_cast<unsigned char>(data[12]) > 1) return false;
            header = true;
        }
        else if (std::memcmp(type, "IHDR", 4) == 0) return false;
        else if (std::memcmp(type, "PLTE", 4) == 0) {
            if (pixels || palette || count == 0 || count > 768 || count % 3 != 0) return false;
            palette = true;
        }
        else if (std::memcmp(type, "IDAT", 4) == 0) {
            if (color_type == 3 && !palette) return false;
            pixels = pixels || count != 0;
        }
        else if (std::memcmp(type, "IEND", 4) == 0)
            return count == 0 && pixels && offset + 12 == bytes.size();
        else if ((static_cast<unsigned char>(type[0]) & 32) == 0) return false;
        offset += count + 12;
    }
    return false;
}

bool cache_filename(std::string_view name) {
    if (name.ends_with("_lock.png")) name.remove_suffix(9);
    else if (name.ends_with(".png")) name.remove_suffix(4);
    else return false;
    return valid_name(name);
}

std::vector<char> load_cached(const std::filesystem::path& path) {
    std::error_code ec;
    if (!std::filesystem::is_regular_file(std::filesystem::symlink_status(path, ec)) || ec) return {};
    const auto size = std::filesystem::file_size(path, ec);
    if (ec || size > image_limit) return {};
    std::ifstream input(path, std::ios::binary);
    std::vector<char> bytes(static_cast<std::size_t>(size));
    if (!input.read(bytes.data(), static_cast<std::streamsize>(bytes.size())) || !valid_png(bytes)) return {};
    return bytes;
}

void trim_cache(const std::filesystem::path& directory) {
    struct Entry { std::filesystem::path path; std::uintmax_t size; std::filesystem::file_time_type time; };
    std::vector<Entry> entries;
    std::uintmax_t total = 0;
    std::error_code ec;
    // Only our strictly named PNG files are eligible. Never recurse into a
    // directory or remove unrelated files placed beside this cache.
    for (auto it = std::filesystem::directory_iterator(directory, ec); !ec && it != std::filesystem::directory_iterator(); it.increment(ec)) {
        if (!cache_filename(it->path().filename().string())) continue;
        if (!std::filesystem::is_regular_file(it->symlink_status(ec)) || ec) { ec.clear(); continue; }
        const auto size = it->file_size(ec);
        if (ec) { ec.clear(); continue; }
        const auto time = it->last_write_time(ec);
        if (ec) { ec.clear(); continue; }
        entries.push_back({it->path(), size, time});
        total += size;
    }
    std::sort(entries.begin(), entries.end(), [](const Entry& a, const Entry& b) { return a.time < b.time; });
    std::size_t remaining = entries.size();
    for (const auto& entry : entries) {
        if (remaining <= image_count_limit && total <= disk_limit) break;
        if (std::filesystem::remove(entry.path, ec)) { --remaining; total -= entry.size; }
        ec.clear();
    }
}

void save_cached(const std::filesystem::path& path, const std::vector<char>& bytes) {
    auto temporary = path;
#ifdef _WIN32
    temporary += "." + std::to_string(GetCurrentProcessId()) + ".tmp";
#else
    temporary += ".tmp";
#endif
    {
        std::ofstream output(temporary, std::ios::binary | std::ios::trunc);
        if (!output.write(bytes.data(), static_cast<std::streamsize>(bytes.size()))) {
            output.close();
            std::error_code ec;
            std::filesystem::remove(temporary, ec);
            return;
        }
    }
#ifdef _WIN32
    const bool moved = MoveFileExW(temporary.c_str(), path.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH) != FALSE;
#else
    std::error_code move_error;
    std::filesystem::rename(temporary, path, move_error);
    const bool moved = !move_error;
#endif
    if (!moved) { std::error_code ec; std::filesystem::remove(temporary, ec); }
}

#ifdef _WIN32
struct Handle {
    HINTERNET value = nullptr;
    ~Handle() { if (value) WinHttpCloseHandle(value); }
    Handle() = default;
    Handle(const Handle&) = delete;
};

struct RequestState {
    std::mutex mutex;
    std::condition_variable changed;
    DWORD events = 0, read_count = 0;
    bool error = false, closed = false;
};

void CALLBACK http_status(HINTERNET, DWORD_PTR context, DWORD status, void*, DWORD count) {
    if (!context) return;
    auto& state = *reinterpret_cast<RequestState*>(context);
    {
        std::lock_guard lock(state.mutex);
        if (status == WINHTTP_CALLBACK_STATUS_HANDLE_CLOSING) state.closed = true;
        else if (status == WINHTTP_CALLBACK_STATUS_REQUEST_ERROR) state.error = true;
        else {
            state.events |= status;
            if (status == WINHTTP_CALLBACK_STATUS_READ_COMPLETE) state.read_count = count;
        }
        // HANDLE_CLOSING can release the final owner as soon as it acquires this
        // mutex. Make notification the final state access before unlocking.
        state.changed.notify_all();
    }
}

struct Request {
    HINTERNET handle = nullptr;
    RequestState state;
    std::array<char, 8192> read_buffer{};
    bool callback_attached = false;
    ~Request() {
        if (!handle) return;
        // All asynchronous WinHTTP initiating calls have returned before this
        // worker closes its request. HANDLE_CLOSING is the final callback; keep
        // context and read storage alive until it arrives, including cancellation.
        WinHttpCloseHandle(handle);
        if (callback_attached) {
            std::unique_lock lock(state.mutex);
            state.changed.wait(lock, [&] { return state.closed; });
        }
    }
    bool wait(DWORD event, const std::atomic<bool>& stopping, std::chrono::steady_clock::time_point deadline) {
        std::unique_lock lock(state.mutex);
        while (!(state.events & event) && !state.error && !stopping.load()) {
            const auto now = std::chrono::steady_clock::now();
            if (now >= deadline) return false;
            state.changed.wait_until(lock, std::min(deadline, now + std::chrono::milliseconds(25)));
        }
        state.events &= ~event;
        return !state.error && !stopping.load();
    }
};

bool initiated(BOOL result) { return result || GetLastError() == ERROR_IO_PENDING; }

struct Downloader {
    Handle session, connection;
    Downloader() {
        session.value = WinHttpOpen(L"WaveRace64Recompiled/1.0 RetroAchievementsBadges", WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY,
            WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, WINHTTP_FLAG_ASYNC);
        if (!session.value || !WinHttpSetTimeouts(session.value, 2000, 2000, 2500, 2500)) return;
        connection.value = WinHttpConnect(session.value, L"media.retroachievements.org", INTERNET_DEFAULT_HTTPS_PORT, 0);
    }
    std::vector<char> fetch(const Task& task, const std::atomic<bool>& stopping) {
        if (!connection.value || stopping.load()) return {};
        // Matches the pinned official rc_api_init_fetch_image_request builder.
        // The caller supplies only an already validated numeric image name.
        const std::string ascii_path = "/Badge/" + task.filename();
        const std::wstring path(ascii_path.begin(), ascii_path.end());
        Request request;
        const wchar_t* accept[] = {L"image/png", nullptr};
        request.handle = WinHttpOpenRequest(connection.value, L"GET", path.c_str(), nullptr,
            WINHTTP_NO_REFERER, accept, WINHTTP_FLAG_SECURE);
        if (!request.handle) return {};
        DWORD disabled = WINHTTP_DISABLE_COOKIES | WINHTTP_DISABLE_AUTHENTICATION | WINHTTP_DISABLE_REDIRECTS;
        if (!WinHttpSetOption(request.handle, WINHTTP_OPTION_DISABLE_FEATURE, &disabled, sizeof(disabled))) return {};
        DWORD_PTR context = reinterpret_cast<DWORD_PTR>(&request.state);
        if (!WinHttpSetOption(request.handle, WINHTTP_OPTION_CONTEXT_VALUE, &context, sizeof(context))) return {};
        constexpr DWORD notifications = WINHTTP_CALLBACK_FLAG_SENDREQUEST_COMPLETE | WINHTTP_CALLBACK_FLAG_HEADERS_AVAILABLE |
            WINHTTP_CALLBACK_FLAG_READ_COMPLETE | WINHTTP_CALLBACK_FLAG_REQUEST_ERROR | WINHTTP_CALLBACK_FLAG_HANDLES;
        if (WinHttpSetStatusCallback(request.handle, http_status, notifications, 0) == WINHTTP_INVALID_STATUS_CALLBACK) return {};
        request.callback_attached = true;
        const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(8);
        if (!initiated(WinHttpSendRequest(request.handle, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA,
                0, 0, context)) || !request.wait(WINHTTP_CALLBACK_STATUS_SENDREQUEST_COMPLETE, stopping, deadline)) return {};
        if (!initiated(WinHttpReceiveResponse(request.handle, nullptr)) ||
            !request.wait(WINHTTP_CALLBACK_STATUS_HEADERS_AVAILABLE, stopping, deadline)) return {};
        DWORD status = 0, size = sizeof(status);
        if (!WinHttpQueryHeaders(request.handle, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
            WINHTTP_HEADER_NAME_BY_INDEX, &status, &size, WINHTTP_NO_HEADER_INDEX) || status != 200) return {};
        DWORD content_length = 0;
        size = sizeof(content_length);
        if (WinHttpQueryHeaders(request.handle, WINHTTP_QUERY_CONTENT_LENGTH | WINHTTP_QUERY_FLAG_NUMBER,
            WINHTTP_HEADER_NAME_BY_INDEX, &content_length, &size, WINHTTP_NO_HEADER_INDEX) && content_length > image_limit) return {};
        std::vector<char> result;
        while (!stopping.load()) {
            if (!initiated(WinHttpReadData(request.handle, request.read_buffer.data(), DWORD(request.read_buffer.size()), nullptr)) ||
                !request.wait(WINHTTP_CALLBACK_STATUS_READ_COMPLETE, stopping, deadline)) return {};
            const auto count = request.state.read_count; // callback completed before wait acquired its mutex
            if (!count) return valid_png(result) ? result : std::vector<char>{};
            if (count > image_limit - result.size()) return {};
            result.insert(result.end(), request.read_buffer.data(), request.read_buffer.data() + count);
        }
        return {};
    }
};
#else
struct Downloader {
    std::vector<char> fetch(const Task&, const std::atomic<bool>&) { return {}; }
};
#endif

struct Cache {
    std::mutex mutex;
    std::condition_variable changed;
    std::thread worker;
    std::atomic<bool> stopping{true};
    std::filesystem::path directory;
    std::deque<Task> pending;
    std::unordered_set<std::string> requested;
    std::vector<Image> ready;
    std::size_t ready_bytes = 0;
    ~Cache() { stopping.store(true); changed.notify_all(); if (worker.joinable()) worker.join(); }
};
Cache cache;

void run() {
    Downloader downloader;
    std::error_code ec;
    std::filesystem::create_directories(cache.directory, ec);
    trim_cache(cache.directory);
    while (!cache.stopping.load()) {
        Task task;
        {
            std::unique_lock lock(cache.mutex);
            cache.changed.wait(lock, [] { return cache.stopping.load() || !cache.pending.empty(); });
            if (cache.stopping.load()) break;
            task = std::move(cache.pending.front());
            cache.pending.pop_front();
        }
        auto bytes = load_cached(cache.directory / task.filename());
        if (bytes.empty()) {
            bytes = downloader.fetch(task, cache.stopping);
            if (bytes.empty() || cache.stopping.load()) continue;
            save_cached(cache.directory / task.filename(), bytes);
            trim_cache(cache.directory);
        }
        {
            std::unique_lock lock(cache.mutex);
            cache.changed.wait(lock, [&] { return cache.stopping.load() || cache.ready_bytes + bytes.size() <= ready_limit; });
            if (cache.stopping.load()) break;
            cache.ready_bytes += bytes.size();
            cache.ready.push_back({source_name(task.name, task.locked), std::move(bytes)});
        }
    }
}
}

std::string source_name(const std::string& badge_name, bool locked) {
    // RmlUi resolves ordinary sources relative to the document's assets path.
    // '?' preserves the exact in-memory texture key, like native thumbnails.
    return valid_name(badge_name) ? "?/wr64/achievement-badges/" + badge_name + (locked ? "-locked.png" : ".png") : "";
}

void initialize(const std::filesystem::path& runtime_directory) {
    std::lock_guard lock(cache.mutex);
    if (cache.worker.joinable()) return;
    cache.directory = runtime_directory / "achievement-badges";
    cache.stopping.store(false);
    cache.worker = std::thread([] {
        // Image/network/cache failure must never terminate the game or its award
        // service. The frontend continues to display its existing fallback.
        try { run(); } catch (...) { cache.stopping.store(true); cache.changed.notify_all(); }
    });
}

void request(std::string badge_name, bool priority) {
    if (!valid_name(badge_name)) return;
    std::lock_guard lock(cache.mutex);
    if (cache.stopping.load()) return;
    // Insert locked first when pushing to the front, leaving the color image
    // first for the toast. A queued duplicate is promoted instead of duplicated.
    for (unsigned i = 0; i < 2; ++i) {
        Task task{badge_name, priority ? i == 0 : i != 0};
        const auto filename = task.filename();
        if (cache.requested.contains(filename)) {
            if (priority) {
                const auto it = std::find_if(cache.pending.begin(), cache.pending.end(), [&](const Task& pending) { return pending.filename() == filename; });
                if (it != cache.pending.end()) { cache.pending.erase(it); cache.pending.push_front(std::move(task)); }
            }
        }
        else if (cache.requested.size() < image_count_limit) {
            cache.requested.insert(filename);
            if (priority) cache.pending.push_front(std::move(task));
            else cache.pending.push_back(std::move(task));
        }
    }
    cache.changed.notify_one();
}

std::vector<Image> drain_images() {
    std::lock_guard lock(cache.mutex);
    auto result = std::move(cache.ready);
    cache.ready.clear();
    cache.ready_bytes = 0;
    cache.changed.notify_one();
    return result;
}

void shutdown() {
    cache.stopping.store(true);
    cache.changed.notify_all();
    if (cache.worker.joinable()) cache.worker.join();
    std::lock_guard lock(cache.mutex);
    cache.pending.clear();
    cache.requested.clear();
    cache.ready.clear();
    cache.ready_bytes = 0;
}
}
