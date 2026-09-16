#include "wr64_diagnostic_policy.h"
#include "wr64_achievements.hpp"
#include "wr64_achievements_native.hpp"
#include "wr64_achievements_platform.hpp"
#include "rc_client.h"
#include "rc_api_runtime.h"
#include "rc_api_user.h"

#include <algorithm>
#include <chrono>
#include <condition_variable>
#include <cmath>
#include <cstdio>
#include <deque>
#include <fstream>
#include <memory>
#include <mutex>
#include <string_view>
#include <thread>
#include <unordered_set>
#include <utility>

namespace wr64::achievements {
namespace {
using Clock = std::chrono::steady_clock;
struct Session : std::enable_shared_from_this<Session> {
    rc_client_t* client = nullptr;
    std::size_t pending = 0;
    bool retired = false, flush_clock = false, allow_retired_submission = false;
    ~Session() {
        // The pinned client clears game before dispatching pending mastery on
        // unload. Reset drains those events while game is attached; it resets
        // local triggers without reading/evaluating another emulated frame.
        // This session has already stopped and its event handler is silent.
        if (retired && rc_client_get_game_info(client)) rc_client_reset(client);
        rc_client_destroy(client);
    }
};
void flush_retired(Session& session, bool submit_scheduled);
void begin_catalog();
struct Command {
    bool logout = false, token = false, remember = false;
    std::string username, secret;
};
struct Work {
    enum Kind { Http, Save, Remove, Log } kind = Http;
    std::string url, post, content_type, message;
    platform::Credentials credentials;
    rc_client_server_callback_t callback = nullptr;
    void* callback_data = nullptr;
    std::shared_ptr<Session> owner;
};
struct Completion {
    platform::HttpResponse response;
    rc_client_server_callback_t callback = nullptr;
    void* callback_data = nullptr;
    std::shared_ptr<Session> owner;
};
struct Service {
    // All rc_client calls and callbacks are serialized here. Network and disk
    // work never hold this mutex or execute on the native frame thread.
    std::mutex mutex, io_mutex;
    std::condition_variable wake;
    std::deque<Work> work;
    std::deque<Completion> completed;
    std::deque<Command> commands;
    std::thread worker;
    bool stop_worker = false, stopping = false, io_active = false;
    std::shared_ptr<Session> current;
    std::vector<std::shared_ptr<Session>> sessions;
    rc_client_t* client = nullptr;
    rc_client_async_handle_t* login_handle = nullptr;
    rc_client_async_handle_t* load_handle = nullptr;
    std::filesystem::path directory;
    std::string user_agent, hash;
    uint8_t* memory = nullptr;
    bool live_game = false, load_attempted = false, remember = false, token_login = false, dirty = true;
    uint64_t frames = 0, reads = 0;
    Snapshot view;
    std::vector<Notification> notifications;
    Clock::time_point refreshed{};
    Clock::time_point catalog_requested_at{};
    uint64_t catalog_serial = 0;
    bool catalog_data_ready = false, catalog_unlocks_ready = false;
    std::vector<Achievement> catalog, catalog_pending;
    std::unordered_set<uint32_t> catalog_unlocks;

    void enqueue(Work item) {
        std::lock_guard lock(io_mutex);
        work.push_back(std::move(item));
        wake.notify_one();
    }
    void log(std::string message) {
#if WR64_ENABLE_DIAGNOSTICS
        WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[achievements] %s\n", message.c_str()));
        Work item; item.kind = Work::Log;
        item.message = std::move(message);
        enqueue(std::move(item));
#else
        (void)message;
#endif
    }
    void run_worker() {
#if WR64_ENABLE_DIAGNOSTICS
        // Only low-volume lifecycle/unlock messages are logged, on the I/O
        // worker. Never log credentials, server payloads, or per-frame RAM.
        const auto log_path = directory / "achievements.log";
        std::error_code ignored;
        if (std::filesystem::is_regular_file(log_path, ignored))
            std::filesystem::copy_file(log_path, directory / "achievements.log.previous",
                std::filesystem::copy_options::overwrite_existing, ignored);
        std::ofstream log_file(log_path, std::ios::trunc);
        const auto log_start = Clock::now();
#endif
        for (;;) {
            Work item;
            {
                std::unique_lock lock(io_mutex);
                wake.wait(lock, [&] { return stop_worker || !work.empty(); });
                if (stop_worker) break;
                item = std::move(work.front());
                work.pop_front();
                io_active = true;
            }
            if (item.kind == Work::Http) {
                platform::HttpResponse response;
                try {
                    response = platform::http_request(item.url, item.post, item.content_type, user_agent);
                } catch (...) { response.status = RC_API_SERVER_RESPONSE_RETRYABLE_CLIENT_ERROR; }
                platform::erase_secret(item.post);
                platform::erase_secret(item.url);
                std::lock_guard lock(io_mutex);
                // Move ownership out of the worker before publishing. Client
                // destruction always remains on the serialized service side.
                completed.push_back({std::move(response), item.callback, item.callback_data, std::move(item.owner)});
                io_active = false;
                wake.notify_all();
#if WR64_ENABLE_DIAGNOSTICS
            } else if (item.kind == Work::Log) {
                if (log_file) {
                    log_file << std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - log_start).count()
                        << "ms " << item.message << '\n';
                    log_file.flush();
                }
                std::lock_guard lock(io_mutex);
                io_active = false;
                wake.notify_all();
#endif
            } else {
                try {
                    if (item.kind == Work::Save) {
                        if (!platform::save_credentials(directory, item.credentials))
                            WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[achievements] could not save encrypted sign-in\n"));
                    } else platform::remove_credentials(directory);
                } catch (...) { std::fprintf(stderr, "[achievements] credential storage unavailable\n"); }
                platform::erase_secret(item.credentials.token);
                std::lock_guard lock(io_mutex);
                io_active = false;
                wake.notify_all();
            }
        }
    }
    void status(std::string message) { log(message); view.status = std::move(message); dirty = true; }
    void refresh() {
        const auto now = Clock::now();
        if (!dirty && now - refreshed < std::chrono::seconds(1)) return;
        dirty = false;
        refreshed = now;
        const auto* user = rc_client_get_user_info(client);
        view.logged_in = user != nullptr;
        view.username = user && user->display_name ? user->display_name : "";
        view.achievements.clear();
        view.unlocked = view.total = view.points = view.total_points = 0;
        if (view.game_loaded) {
            rc_client_user_game_summary_t summary{};
            rc_client_get_user_game_summary(client, &summary);
            view.unlocked = summary.num_unlocked_achievements;
            view.total = summary.num_core_achievements;
            view.points = summary.points_unlocked;
            auto* list = rc_client_create_achievement_list(client,
                RC_CLIENT_ACHIEVEMENT_CATEGORY_CORE, RC_CLIENT_ACHIEVEMENT_LIST_GROUPING_LOCK_STATE);
            if (list) {
                for (uint32_t b = 0; b < list->num_buckets; ++b) {
                    const auto& bucket = list->buckets[b];
                    for (uint32_t i = 0; i < bucket.num_achievements; ++i) {
                        const auto& a = *bucket.achievements[i];
                        view.achievements.push_back({a.id, a.title ? a.title : "", a.description ? a.description : "",
                            a.points, a.state == RC_CLIENT_ACHIEVEMENT_STATE_UNLOCKED,
                            a.state == RC_CLIENT_ACHIEVEMENT_STATE_DISABLED ? "Unsupported" : a.measured_progress,
                            a.badge_name, static_cast<int64_t>(a.unlock_time), a.rarity, a.rarity_hardcore});
                        view.total_points += a.points;
                    }
                }
                rc_client_destroy_achievement_list(list);
            }
            std::sort(view.achievements.begin(), view.achievements.end(),
                [](const auto& a, const auto& b) { return a.id < b.id; });
            // Keep real session unlocks/timestamps when returning to browsing.
            catalog = view.achievements;
            view.catalog_loaded = true;
        } else if (view.logged_in && view.catalog_loaded) {
            view.achievements = catalog;
            view.total = static_cast<uint32_t>(catalog.size());
            for (const auto& a : catalog) {
                view.total_points += a.points;
                if (a.unlocked) { ++view.unlocked; view.points += a.points; }
            }
        }
        ++view.revision;
    }
    void finish_responses() {
        std::deque<Completion> batch;
        { std::lock_guard lock(io_mutex); batch.swap(completed); }
        for (auto& item : batch) {
            const rc_api_server_response_t response{item.response.body.data(),
                item.response.body.size(), item.response.status};
            item.callback(&response, item.callback_data);
            if (item.owner->retired) flush_retired(*item.owner, false);
            // A callback can enqueue an immediate retry. Decrement afterward,
            // while its original client, identity and game are still alive.
            --item.owner->pending;
            platform::erase_secret(item.response.body);
        }
    }
    void collect_sessions() {
        std::erase_if(sessions, [&](const auto& session) {
            return session != current && session->retired && session->pending == 0;
        });
    }
};
Service service;

void* generation_data() { return reinterpret_cast<void*>(static_cast<uintptr_t>(service.view.account_generation)); }
bool current_generation(void* data) {
    return static_cast<uint64_t>(reinterpret_cast<uintptr_t>(data)) == service.view.account_generation;
}

uint32_t RC_CCONV read_memory(uint32_t address, uint8_t* buffer, uint32_t count, rc_client_t* client) {
    const auto* owner = static_cast<Session*>(rc_client_get_userdata(client));
    if (!owner || owner->retired || client != service.client) return 0;
    ++service.reads;
    return native::read_memory_bytes(service.memory, native::memory_size, address, buffer, count);
}

void RC_CCONV server_call(const rc_api_request_t* request, rc_client_server_callback_t callback,
    void* data, rc_client_t* client) {
    auto* owner = static_cast<Session*>(rc_client_get_userdata(client));
    const std::string_view post = request->post_data ? request->post_data : "";
    const bool submission = post.starts_with("r=awardachievement&") || post.starts_with("r=submitlbentry&");
    if (owner->retired && (!owner->allow_retired_submission || !submission)) {
        if (submission)
            service.log("closed-session submission remains unconfirmed; no offline outbox");
        // Empty errors still retry in rcheevos. A parsed terminal error frees
        // the callback and its scheduled retry without changing any account.
        static constexpr char canceled[] = "{\"Success\":false,\"Error\":\"The originating game session has closed.\"}";
        const rc_api_server_response_t response{canceled, sizeof(canceled) - 1, RC_API_SERVER_RESPONSE_CLIENT_ERROR};
        callback(&response, data);
        return;
    }
    Work item;
    item.url = request->url ? request->url : "";
    item.post = request->post_data ? request->post_data : "";
    item.content_type = request->content_type ? request->content_type : "";
    item.callback = callback;
    item.callback_data = data;
    item.owner = owner->shared_from_this();
    ++owner->pending;
    service.enqueue(std::move(item));
}

struct CatalogRequest {
    uint64_t generation, serial;
    rc_client_t* client;
    bool unlocks;
};

void catalog_failed(int result) {
    service.view.catalog_busy = false;
    service.catalog_pending.clear();
    service.view.catalog_status = service.view.catalog_loaded
        ? "Could not refresh. Showing the last loaded achievements."
        : "Could not load achievements. Use Refresh achievements to retry.";
    service.dirty = true;
    service.log("catalog request failed result=" + std::to_string(result));
}

void RC_CCONV catalog_response(const rc_api_server_response_t* raw, void* userdata) {
    const std::unique_ptr<CatalogRequest> request(static_cast<CatalogRequest*>(userdata));
    if (service.stopping || request->client != service.client || service.current->retired ||
        request->generation != service.view.account_generation || request->serial != service.catalog_serial ||
        !service.view.catalog_busy) return;
    if (request->unlocks) {
        rc_api_fetch_user_unlocks_response_t response{};
        const int result = rc_api_process_fetch_user_unlocks_server_response(&response, raw);
        const bool valid = result == RC_OK && response.response.succeeded && response.num_achievement_ids <= 10000;
        if (valid) {
            service.catalog_unlocks.clear();
            for (uint32_t i = 0; i < response.num_achievement_ids; ++i)
                service.catalog_unlocks.insert(response.achievement_ids[i]);
            service.catalog_unlocks_ready = true;
        }
        rc_api_destroy_fetch_user_unlocks_response(&response);
        if (!valid) { catalog_failed(result == RC_OK ? RC_INVALID_STATE : result); return; }
    } else {
        rc_api_fetch_game_data_response_t response{};
        const int result = rc_api_process_fetch_game_data_server_response(&response, raw);
        const bool valid = result == RC_OK && response.response.succeeded && response.id == 10617 &&
            response.console_id == 2 && response.num_achievements <= 10000;
        if (valid) {
            service.catalog_pending.clear();
            for (uint32_t i = 0; i < response.num_achievements; ++i) {
                const auto& a = response.achievements[i];
                // The legacy metadata endpoint can add zero-point client
                // notices. Match rc_client's reserved warning-ID boundary;
                // these are not achievements in the game's official set.
                if (a.category != RC_ACHIEVEMENT_CATEGORY_CORE || a.id >= 101000001u) continue;
                const auto rate = [](float value) { return std::isfinite(value) && value >= 0 && value <= 100 ? value : -1.0f; };
                service.catalog_pending.push_back({a.id, a.title ? a.title : "", a.description ? a.description : "",
                    a.points, false, "", a.badge_name ? a.badge_name : "", 0, rate(a.rarity), rate(a.rarity_hardcore)});
            }
            service.catalog_data_ready = true;
        }
        rc_api_destroy_fetch_game_data_response(&response);
        if (!valid) { catalog_failed(result == RC_OK ? RC_INVALID_STATE : result); return; }
    }
    if (!service.catalog_data_ready || !service.catalog_unlocks_ready) return;
    // The catalog is display data only. It never activates definitions, starts
    // a gameplay session or evaluates RAM. Runtime unlocks take precedence over
    // a metadata response that may have started before an achievement was earned.
    if (!service.view.game_loaded) {
        for (auto& a : service.catalog_pending) {
            a.unlocked = service.catalog_unlocks.contains(a.id);
            if (a.unlocked) {
                const auto known = std::find_if(service.catalog.begin(), service.catalog.end(),
                    [&](const auto& previous) { return previous.id == a.id && previous.unlocked; });
                if (known != service.catalog.end()) a.unlock_time = known->unlock_time;
            }
        }
        std::sort(service.catalog_pending.begin(), service.catalog_pending.end(),
            [](const auto& a, const auto& b) { return a.id < b.id; });
        service.catalog = std::move(service.catalog_pending);
    }
    service.catalog_pending.clear();
    service.view.catalog_loaded = true;
    service.view.catalog_busy = false;
    service.view.catalog_status = "Achievements and account progress loaded.";
    service.dirty = true;
    service.log("catalog ready; game=10617; evaluation unchanged");
}

void begin_catalog() {
    if (!service.client || service.stopping || service.current->retired || service.view.catalog_busy) return;
    const auto* user = rc_client_get_user_info(service.client);
    if (!user || !user->username || !user->token) return;
    const auto now = Clock::now();
    if (service.catalog_requested_at != Clock::time_point{} &&
        now - service.catalog_requested_at < std::chrono::seconds(5)) return;
    service.catalog_requested_at = now;
    ++service.catalog_serial;
    service.catalog_data_ready = service.catalog_unlocks_ready = false;
    service.catalog_pending.clear();
    service.catalog_unlocks.clear();
    service.view.catalog_busy = true;
    service.view.catalog_status = service.view.catalog_loaded ? "Refreshing achievements…" : "Loading achievements…";
    service.dirty = true;
    for (bool unlocks : {false, true}) {
        rc_api_request_t api{};
        int result;
        if (unlocks) {
            rc_api_fetch_user_unlocks_request_t params{};
            params.username = user->username; params.api_token = user->token;
            params.game_id = 10617; params.hardcore = 0; // Includes softcore and hardcore awards.
            result = rc_api_init_fetch_user_unlocks_request(&api, &params);
        } else {
            rc_api_fetch_game_data_request_t params{};
            params.username = user->username; params.api_token = user->token; params.game_id = 10617;
            result = rc_api_init_fetch_game_data_request(&api, &params);
        }
        if (result == RC_OK) {
            auto request = std::make_unique<CatalogRequest>(CatalogRequest{
                service.view.account_generation, service.catalog_serial, service.client, unlocks});
            server_call(&api, catalog_response, request.get(), service.client);
            request.release(); // The worker owns the callback and originating client.
        }
        rc_api_destroy_request(&api);
        if (result != RC_OK) { catalog_failed(result); break; }
    }
}

rc_clock_t RC_CCONV session_clock(const rc_client_t* client) {
    auto* owner = static_cast<Session*>(rc_client_get_userdata(client));
    const auto now = static_cast<rc_clock_t>(std::chrono::duration_cast<std::chrono::milliseconds>(
        Clock::now().time_since_epoch()).count());
    if (owner->flush_clock) {
        owner->flush_clock = false;
        return now + 121000;
    }
    return now;
}

void flush_retired(Session& session, bool submit_scheduled) {
    // The pinned client's maximum retry delay is 120s. Only idle's deadline
    // read advances; request timestamps still use the real monotonic clock.
    // Aborted loads cannot validate RAM, and retired memory reads return zero.
    session.allow_retired_submission = submit_scheduled;
    session.flush_clock = true;
    rc_client_idle(session.client);
    session.flush_clock = false;
    session.allow_retired_submission = false;
}

void RC_CCONV loaded(int result, const char*, rc_client_t* client, void* data) {
    if (!current_generation(data) || client != service.client || service.current->retired || service.stopping) return;
    service.load_handle = nullptr;
    service.view.busy = false;
    const auto* game = rc_client_get_game_info(client);
    if (result != RC_OK || !game || game->id != 10617) {
        rc_client_unload_game(client);
        service.view.game_loaded = false;
        service.status("Achievements could not load. Sign out and sign in to retry.");
        service.log("load failed result=" + std::to_string(result));
        return;
    }
    service.view.game_loaded = true;
    service.status("Softcore achievements active.");
    rc_client_user_game_summary_t summary{};
    rc_client_get_user_game_summary(client, &summary);
    service.log("game=10617 softcore=1 achievements=" + std::to_string(summary.num_core_achievements) +
        " unsupported=" + std::to_string(summary.num_unsupported_achievements));
}

void RC_CCONV logged_in(int result, const char*, rc_client_t* client, void* data) {
    if (!current_generation(data) || client != service.client || service.current->retired || service.stopping) return;
    service.login_handle = nullptr;
    service.view.busy = false;
    if (result != RC_OK) {
        const bool invalid_login = result == RC_INVALID_CREDENTIALS || result == RC_EXPIRED_TOKEN;
        if (invalid_login && service.token_login) {
            Work item; item.kind = Work::Remove; service.enqueue(std::move(item));
        }
        service.status(invalid_login
            ? "Sign-in failed. Please sign in again with your username and password."
            : "Could not connect to RetroAchievements. Please try again.");
        service.log("sign-in failed result=" + std::to_string(result));
        return;
    }
    service.status(service.live_game ? "Preparing softcore achievements…" : "Signed in. Softcore achievements unlock during play.");
    service.load_attempted = false;
    if (service.remember) {
        const auto* user = rc_client_get_user_info(client);
        if (user && user->username && user->token) {
            Work item; item.kind = Work::Save;
            item.credentials = {user->username, user->token};
            service.enqueue(std::move(item));
        }
    }
    service.log("signed in; softcore only");
    begin_catalog();
}

void RC_CCONV event_handler(const rc_client_event_t* event, rc_client_t* client) {
    if (service.stopping || client != service.client || service.current->retired) return;
    service.dirty = true;
    switch (event->type) {
    case RC_CLIENT_EVENT_ACHIEVEMENT_TRIGGERED:
        if (event->achievement) {
            const auto& a = *event->achievement;
            service.notifications.push_back({service.view.account_generation,
                std::string("Achievement unlocked · ") + std::to_string(a.points) + " points",
                a.title ? a.title : "", a.badge_name});
            service.log("softcore unlock id=" + std::to_string(a.id));
        }
        break;
    case RC_CLIENT_EVENT_GAME_COMPLETED:
        service.notifications.push_back({service.view.account_generation, "Wave Race 64 completed!", "All softcore achievements unlocked."});
        break;
    case RC_CLIENT_EVENT_DISCONNECTED:
        service.status("Connection lost. Pending unlocks will retry while the game is open.");
        break;
    case RC_CLIENT_EVENT_RECONNECTED:
        service.status("Softcore achievements active. Pending unlocks synced.");
        break;
    case RC_CLIENT_EVENT_SERVER_ERROR:
        service.status("An achievement request failed. Check your connection and account progress.");
        service.log("server request failed result=" +
            std::to_string(event->server_error ? event->server_error->result : RC_NO_RESPONSE));
        break;
    default: break;
    }
}

void retire_current() {
    if (!service.current || service.current->retired) return;
    service.current->retired = true;
    if (service.login_handle) rc_client_abort_async(service.client, service.login_handle);
    if (service.load_handle) {
        rc_client_abort_async(service.client, service.load_handle);
        // A deferred activation uses state.load, not the async aborted bit.
        // No achievements can have been evaluated on this unfinished game.
        rc_client_unload_game(service.client);
    }
    service.login_handle = service.load_handle = nullptr;
    flush_retired(*service.current, true);
}

void create_client() {
    service.current = std::make_shared<Session>();
    service.current->client = rc_client_create(read_memory, server_call);
    service.client = service.current->client;
    if (!service.client) return;
    service.sessions.push_back(service.current);
    rc_client_set_userdata(service.client, service.current.get());
    rc_client_set_get_time_millisecs_function(service.client, session_clock);
    rc_client_set_hardcore_enabled(service.client, 0);
    rc_client_set_unofficial_enabled(service.client, 0);
    rc_client_set_encore_mode_enabled(service.client, 0);
    rc_client_set_allow_background_memory_reads(service.client, 0);
    rc_client_set_event_handler(service.client, event_handler);
}

void clear_account() {
    ++service.view.account_generation;
    retire_current();
    create_client();
    service.collect_sessions();
    service.view.game_loaded = service.view.logged_in = service.view.busy = false;
    service.view.username.clear();
    ++service.catalog_serial;
    service.catalog_requested_at = {};
    service.catalog.clear();
    service.catalog_pending.clear();
    service.catalog_unlocks.clear();
    service.view.catalog_loaded = service.view.catalog_busy = false;
    service.view.catalog_status.clear();
    service.notifications.clear();
    service.load_attempted = false;
    service.dirty = true;
}

void pump() {
    while (!service.commands.empty()) {
        auto command = std::move(service.commands.front());
        service.commands.pop_front();
        clear_account();
        // The worker serializes remove/save operations, so a previous login
        // cannot restore its token after a subsequent sign-out.
        if (!command.token) { Work item; item.kind = Work::Remove; service.enqueue(std::move(item)); }
        if (command.logout) {
            service.status("Sign in to earn softcore achievements.");
            continue;
        }
        service.remember = command.remember;
        service.token_login = command.token;
        if (!service.client) {
            platform::erase_secret(command.secret);
            service.status("RetroAchievements could not start.");
            continue;
        }
        service.view.busy = true;
        service.status("Signing in…");
        service.login_handle = command.token
            ? rc_client_begin_login_with_token(service.client, command.username.c_str(), command.secret.c_str(), logged_in, generation_data())
            : rc_client_begin_login_with_password(service.client, command.username.c_str(), command.secret.c_str(), logged_in, generation_data());
        platform::erase_secret(command.secret);
    }
    service.finish_responses();
    service.collect_sessions();
    // Game identification/loading is initiated on the guest thread. Deferred
    // memory validation must also run there, never on the rendering/UI thread.
    if (service.client && !service.current->retired && service.memory && !service.hash.empty() &&
        !service.load_attempted && rc_client_get_user_info(service.client)) {
        service.load_attempted = true;
        service.view.busy = true;
        service.status("Loading softcore achievements…");
        service.load_handle = rc_client_begin_load_game(service.client, service.hash.c_str(), loaded, generation_data());
    }
}
} // namespace

void initialize(const std::filesystem::path& directory) {
    std::lock_guard lock(service.mutex);
    if (service.client) return;
    service.directory = directory;
    service.view = {};
    service.hash.clear();
    service.memory = nullptr;
    service.live_game = service.load_attempted = service.remember = false;
    service.frames = service.reads = 0;
    service.notifications.clear();
    ++service.catalog_serial;
    service.catalog_requested_at = {};
    service.catalog.clear(); service.catalog_pending.clear(); service.catalog_unlocks.clear();
    service.stopping = service.stop_worker = service.io_active = false;
    create_client();
    if (!service.client) { service.view.status = "RetroAchievements could not start."; return; }
    char clause[128]{};
    rc_client_get_user_agent_clause(service.client, clause, sizeof(clause));
    service.user_agent = std::string("WaveRace64Recompiled/1.0.0 (Windows) ") + clause;
    service.log("client initialized; N64 memory view=raw host words; softcore only");
    service.status("Sign in to earn softcore achievements.");
    try {
        if (auto credentials = platform::load_credentials(directory)) {
            service.commands.push_back({false, true, true, std::move(credentials->username), std::move(credentials->token)});
        }
    } catch (...) { service.status("Saved sign-in is unavailable. Please sign in again."); }
    service.worker = std::thread([] { service.run_worker(); });
    service.refresh();
}

Snapshot snapshot() { std::lock_guard lock(service.mutex); return service.view; }
void request_login(std::string username, std::string password, bool remember) {
    std::lock_guard lock(service.mutex);
    if (!service.client || service.stopping || username.empty() || username.size() > 128 || password.empty() || password.size() > 1024) {
        platform::erase_secret(password);
        return;
    }
    service.commands.push_back({false, false, remember, std::move(username), std::move(password)});
}
void request_logout() {
    std::lock_guard lock(service.mutex);
    if (service.client && !service.stopping) service.commands.push_back({true});
}
void request_catalog_refresh() {
    std::lock_guard lock(service.mutex);
    begin_catalog();
}
std::vector<Notification> drain_notifications() {
    std::lock_guard lock(service.mutex);
    std::vector<Notification> result;
    result.swap(service.notifications);
    return result;
}
void ui_tick() {
    std::unique_lock lock(service.mutex, std::try_to_lock);
    if (!lock || !service.client || service.stopping) return;
    pump();
    // With background reads disabled, idle may finish deferred memory
    // validation. It is safe here only before any game has been initialized.
    if (!service.live_game && !service.current->retired) rc_client_idle(service.client);
    service.refresh();
}
void native_frame(uint8_t* rdram) {
    std::lock_guard lock(service.mutex);
    if (!service.client || service.stopping || !service.live_game || service.current->retired) return;
    service.memory = rdram;
    pump();
    if (service.client && !service.current->retired) rc_client_do_frame(service.client);
    ++service.frames;
    service.memory = nullptr;
    service.refresh();
}
void set_game_identity(std::string hash) {
    std::lock_guard lock(service.mutex);
    if (!service.client || service.stopping) return;
    if (service.current->retired || service.load_handle || rc_client_get_game_info(service.client)) {
        // A different game never inherits pending callbacks from the previous
        // game. Restore only the signed-in identity through the official login.
        Command restore;
        if (const auto* user = rc_client_get_user_info(service.client)) {
            restore.token = true;
            restore.remember = service.remember;
            restore.username = user->username ? user->username : "";
            restore.secret = user->token ? user->token : "";
        }
        clear_account();
        if (!restore.secret.empty()) service.commands.push_back(std::move(restore));
    }
    service.hash = hash == native::original_rom_hash ? std::move(hash) : "";
    service.live_game = true;
    service.view.game_loaded = false;
    service.load_attempted = false;
    service.status(service.hash.empty() ? "This ROM is not supported by the achievement set."
        : "Start with a signed-in account to earn softcore achievements.");
    service.log("native game identity supported=" + std::to_string(!service.hash.empty()));
}
void game_stopped() {
    std::lock_guard lock(service.mutex);
    if (!service.client) return;
    service.dirty = true;
    service.refresh();
    ++service.catalog_serial;
    service.view.catalog_busy = false;
    retire_current();
    service.hash.clear();
    service.live_game = false;
    service.memory = nullptr;
    service.view.game_loaded = false;
    service.status("Game closed.");
    service.log("native_frames=" + std::to_string(service.frames) + " memory_reads=" + std::to_string(service.reads));
}
void shutdown() {
    {
        std::lock_guard lock(service.mutex);
        if (service.stopping || (!service.client && !service.worker.joinable())) return;
        service.stopping = true;
        service.memory = nullptr;
        service.live_game = false;
        retire_current();
        // Honor an explicit sign-out even when the final UI pump has not run.
        // A queued sign-in is not started during shutdown.
        for (auto& command : service.commands) {
            if (command.logout) { Work item; item.kind = Work::Remove; service.enqueue(std::move(item)); }
            platform::erase_secret(command.secret);
        }
        service.commands.clear();
    }
    // Keep the worker alive until every accepted request has been sent and its
    // callback delivered. Retired sessions allow one already-scheduled retry,
    // then terminate further failures locally. This is a bounded drain, not a
    // durable offline outbox; successful server confirmation is still required.
    for (;;) {
        {
            std::lock_guard lock(service.mutex);
            service.finish_responses();
            service.collect_sessions();
            std::lock_guard io_lock(service.io_mutex);
            const bool pending = std::any_of(service.sessions.begin(), service.sessions.end(),
                [](const auto& owner) { return owner->pending != 0; });
            if (!pending && !service.io_active && service.work.empty() && service.completed.empty()) {
                service.stop_worker = true;
                service.wake.notify_all();
                break;
            }
        }
        std::unique_lock lock(service.io_mutex);
        service.wake.wait_for(lock, std::chrono::milliseconds(25));
    }
    if (service.worker.joinable()) service.worker.join();
    std::lock_guard lock(service.mutex);
    service.client = nullptr;
    service.current.reset();
    service.sessions.clear();
}
} // namespace wr64::achievements
