// Deliberately compile the unchanged production implementation here: observing
// its read counter verifies UI/network pumps never touch guest memory without
// adding a test API or replacing the official rc_client implementation.
#include "../../src/wr64_achievements.cpp"

#include <atomic>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#include <DbgHelp.h>
#pragma comment(lib, "dbghelp.lib")
// Useful for lifetime regressions: preserve a native stack in the CTest log
// instead of displaying an interactive Windows crash dialog.
LONG WINAPI fixture_exception(EXCEPTION_POINTERS* exception) {
    if (exception->ExceptionRecord->ExceptionCode != EXCEPTION_ACCESS_VIOLATION) return EXCEPTION_CONTINUE_SEARCH;
    static bool reporting = false;
    if (reporting) return EXCEPTION_CONTINUE_SEARCH;
    reporting = true;
    const auto process = GetCurrentProcess(), thread = GetCurrentThread();
    SymSetOptions(SYMOPT_LOAD_LINES | SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS);
    SymInitialize(process, nullptr, TRUE);
    auto context = *exception->ContextRecord;
    STACKFRAME64 frame{};
    frame.AddrPC = {context.Rip, 0, AddrModeFlat};
    frame.AddrFrame = {context.Rbp, 0, AddrModeFlat};
    frame.AddrStack = {context.Rsp, 0, AddrModeFlat};
    std::fprintf(stderr, "[fixture] access violation stack:\n");
    for (unsigned i = 0; i < 24 && frame.AddrPC.Offset; ++i) {
        alignas(SYMBOL_INFO) char storage[sizeof(SYMBOL_INFO) + MAX_SYM_NAME]{};
        auto* symbol = reinterpret_cast<SYMBOL_INFO*>(storage);
        symbol->SizeOfStruct = sizeof(SYMBOL_INFO); symbol->MaxNameLen = MAX_SYM_NAME;
        DWORD64 displacement = 0;
        IMAGEHLP_LINE64 line{}; line.SizeOfStruct = sizeof(line);
        DWORD line_displacement = 0;
        if (SymFromAddr(process, frame.AddrPC.Offset, &displacement, symbol))
            std::fprintf(stderr, "  %s+0x%llx", symbol->Name, static_cast<unsigned long long>(displacement));
        else std::fprintf(stderr, "  0x%llx", static_cast<unsigned long long>(frame.AddrPC.Offset));
        if (SymGetLineFromAddr64(process, frame.AddrPC.Offset, &line_displacement, &line))
            std::fprintf(stderr, " (%s:%lu)", line.FileName, line.LineNumber);
        std::fprintf(stderr, "\n");
        if (!StackWalk64(IMAGE_FILE_MACHINE_AMD64, process, thread, &frame, &context, nullptr,
            SymFunctionTableAccess64, SymGetModuleBase64, nullptr)) break;
    }
    return EXCEPTION_CONTINUE_SEARCH;
}
#endif

namespace ra = wr64::achievements;
using namespace std::chrono_literals;
namespace fixture {
std::mutex mutex;
std::condition_variable wake;
struct Exchange {
    std::string action, user, body;
    int status = 200;
    bool released = true, started = false, finished = false;
    std::string hardcore;
};
struct Request { std::string action, user, hardcore, achievement; bool token_login = false; std::string game; };
std::deque<std::shared_ptr<Exchange>> expected, catalog_expected;
std::vector<std::shared_ptr<Exchange>> all_exchanges;
std::vector<Request> requests, catalog_requests;
std::optional<ra::platform::Credentials> stored;
unsigned checks = 0, saves = 0, removes = 0, active_http = 0;
std::string failure;
const auto main_thread = std::this_thread::get_id();

std::string field(const std::string& post, const std::string& key) {
    const auto prefix = key + '=';
    size_t offset = 0;
    while (offset < post.size()) {
        const auto end = post.find('&', offset);
        if (post.compare(offset, prefix.size(), prefix) == 0)
            return post.substr(offset + prefix.size(), end == std::string::npos ? end : end - offset - prefix.size());
        if (end == std::string::npos) break;
        offset = end + 1;
    }
    return {};
}
void require(bool condition, const char* message) {
    ++checks;
    if (!condition) throw std::runtime_error(message);
}
auto plan(std::string action, std::string user, std::string body, int status = 200, bool hold = false) {
    auto exchange = std::make_shared<Exchange>(Exchange{std::move(action), std::move(user), std::move(body), status, !hold});
    std::lock_guard lock(mutex);
    (exchange->action == "patch" || exchange->action == "unlocks" ? catalog_expected : expected).push_back(exchange);
    all_exchanges.push_back(exchange);
    return exchange;
}
void release(const std::shared_ptr<Exchange>& exchange) {
    std::lock_guard lock(mutex);
    exchange->released = true;
    wake.notify_all();
}
bool started(const std::shared_ptr<Exchange>& exchange) { std::lock_guard lock(mutex); return exchange->started; }
bool finished(const std::shared_ptr<Exchange>& exchange) { std::lock_guard lock(mutex); return exchange->finished; }
void no_http_failure() { std::lock_guard lock(mutex); if (!failure.empty()) throw std::runtime_error(failure); }
template<class Predicate> void until(Predicate predicate, const char* message, uint8_t* memory = nullptr) {
    const auto deadline = std::chrono::steady_clock::now() + 4s;
    while (!predicate()) {
        if (memory) ra::native_frame(memory); else ra::ui_tick();
        no_http_failure();
        if (std::chrono::steady_clock::now() >= deadline) throw std::runtime_error(message);
        std::this_thread::sleep_for(1ms);
    }
    ++checks;
}
void settle() {
    until([] {
        ra::ui_tick();
        std::lock_guard lock(mutex);
        if (active_http != 0) return false;
        std::lock_guard io_lock(ra::service.io_mutex);
        return !ra::service.io_active && ra::service.work.empty() && ra::service.completed.empty();
    }, "service worker did not settle");
}
uint64_t reads() { std::lock_guard lock(ra::service.mutex); return ra::service.reads; }
std::string login_reply(const std::string& user) {
    return "{\"Success\":true,\"User\":\"" + user + "\",\"Token\":\"FakeToken" + user +
        "\",\"Score\":0,\"SoftcoreScore\":0,\"Messages\":0}";
}
// Synthetic data with the official achievementsets format, based on upstream
// test/test_rc_client.c patchdata_2ach_0lbd. No real achievement IDs or triggers.
const char* game_reply = R"({"Success":true,"GameId":10617,"Title":"Fixture Wave Race","ConsoleId":2,
"ImageIconUrl":"https://fixture.invalid/icon.png","RichPresenceGameId":10617,"RichPresencePatch":"",
"Sets":[{"AchievementSetId":99111,"GameId":10617,"Title":null,"Type":"core","ImageIconUrl":"https://fixture.invalid/icon.png",
"Achievements":[
{"ID":990001,"Title":"Synthetic byte trigger","Description":"Fixture only","Flags":3,"Points":5,"MemAddr":"0xH0001=3_0xH0002=7","Author":"Fixture","BadgeName":"00001","Created":1367266583,"Modified":1376929305},
{"ID":990002,"Title":"Synthetic measured trigger","Description":"Fixture only","Flags":3,"Points":2,"MemAddr":"M:0xH0010=10","Author":"Fixture","BadgeName":"00002","Created":1367266583,"Modified":1376929305}
],"Leaderboards":[]}]})";
const char* no_unlocks = R"({"Success":true,"Unlocks":[],"HardcoreUnlocks":[]})";
// Display-only catalog replies use the official legacy patch/unlocks formats.
// Defaults keep existing lifecycle cases focused on their runtime requests;
// explicit plans override these defaults for catalog ownership/error cases.
const char* catalog_reply = R"({"Success":true,"PatchData":{"ID":10617,"Title":"Fixture Wave Race","ConsoleID":2,
"ImageIcon":"/Images/00001.png","RichPresencePatch":"","Achievements":[
{"ID":990001,"Title":"Synthetic byte trigger","Description":"Fixture only","Flags":3,"Points":5,"MemAddr":"0xH0001=3_0xH0002=7","Author":"Fixture","BadgeName":"00001","Created":1367266583,"Modified":1376929305,"Rarity":12.5,"RarityHardcore":4.25},
{"ID":990002,"Title":"Synthetic measured trigger","Description":"Fixture only","Flags":3,"Points":2,"MemAddr":"M:0xH0010=10","Author":"Fixture","BadgeName":"00002","Created":1367266583,"Modified":1376929305,"Rarity":75.0,"RarityHardcore":20.5},
{"ID":101000001,"Title":"Synthetic reserved client warning","Description":"Not a playable achievement","Flags":3,"Points":1,"MemAddr":"0=1","Author":"Fixture","BadgeName":"00003","Created":1367266583,"Modified":1376929305}
],"Leaderboards":[]}})";
const char* catalog_no_unlocks = R"({"Success":true,"UserUnlocks":[]})";
void prepare_load(const std::string& user) {
    plan("achievementsets", user, game_reply);
    plan("startsession", user, no_unlocks);
}
void load_game(std::vector<uint8_t>& memory, const std::string& user) {
    prepare_load(user);
    ra::set_game_identity(ra::native::original_rom_hash);
    until([] { return ra::snapshot().game_loaded; }, "synthetic game did not load", memory.data());
    require(ra::snapshot().total == 2, "synthetic set must expose both achievements");
    require(ra::snapshot().unlocked == 0, "new account should have no unlocks");
    settle();
}
}

namespace wr64::achievements::platform {
HttpResponse http_request(const std::string& url, const std::string& post, const std::string& content_type, const std::string& user_agent) {
    using namespace fixture;
    std::unique_lock lock(mutex);
    const auto action = field(post, "r"), user = field(post, "u");
    const bool catalog = action == "patch" || action == "unlocks";
    (catalog ? catalog_requests : requests).push_back(
        {action, user, field(post, "h"), field(post, "a"), !field(post, "t").empty(), field(post, "g")});
    if (std::this_thread::get_id() == main_thread) failure = "HTTP ran on test's native/UI thread";
    if (url.empty() || content_type.empty() || user_agent.find("WaveRace64Recompiled/1.0.0") == std::string::npos)
        failure = "production HTTP metadata missing";
    if (action == "ping") return {200, "{\"Success\":true}"};
    auto& plans = catalog ? catalog_expected : expected;
    if (catalog && (plans.empty() || plans.front()->action != action || plans.front()->user != user))
        return {200, action == "patch" ? catalog_reply : catalog_no_unlocks};
    if (plans.empty()) { failure = "unexpected mocked request: " + action; return {500, "{}"}; }
    auto exchange = plans.front();
    plans.pop_front();
    if (exchange->action != action || exchange->user != user) failure = "mocked request order/account mismatch: " + action;
    if (!exchange->hardcore.empty() && exchange->hardcore != field(post, "h")) failure = "mocked catalog progress mode mismatch";
    exchange->started = true;
    ++active_http;
    if (!wake.wait_for(lock, 4s, [&] { return exchange->released; })) failure = "mocked HTTP release timed out";
    --active_http;
    exchange->finished = true;
    return {exchange->status, exchange->body};
}
std::optional<Credentials> load_credentials(const std::filesystem::path&) { std::lock_guard lock(fixture::mutex); return fixture::stored; }
bool save_credentials(const std::filesystem::path&, const Credentials& credentials) {
    std::lock_guard lock(fixture::mutex); fixture::stored = credentials; ++fixture::saves; return true;
}
void remove_credentials(const std::filesystem::path&) {
    std::lock_guard lock(fixture::mutex); fixture::stored.reset(); ++fixture::removes;
}
void erase_secret(std::string& value) { std::fill(value.begin(), value.end(), '\0'); value.clear(); }
}

#include "lifecycle.inl"
#include "catalog.inl"

int main(int argc, char** argv) {
#ifdef _WIN32
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
    AddVectoredExceptionHandler(1, fixture_exception);
#endif
    using namespace fixture;
    try {
        if (argc == 3 && std::string(argv[1]) == "--catalog") {
            catalog_fixture::run(argv[2]);
            ra::shutdown();
            no_http_failure();
            { std::lock_guard lock(mutex); require(expected.empty() && catalog_expected.empty(), "unconsumed catalog HTTP expectations"); }
            std::cout << "PASS achievements service catalog " << argv[2] << ": " << checks << " checks; fake HTTP/store only\n";
            return 0;
        }
        if (argc == 3 && std::string(argv[1]) == "--lifecycle") {
            lifecycle::run(argv[2]);
            ra::shutdown();
            no_http_failure();
            { std::lock_guard lock(mutex); require(expected.empty() && catalog_expected.empty(), "unconsumed lifecycle HTTP expectations"); }
            std::cout << "PASS achievements service lifecycle " << argv[2] << ": " << checks << " checks; fake HTTP/store only\n";
            return 0;
        }
        // This path is a label for the fake store; no filesystem or network I/O
        // is linked. All strings and users below are deliberately synthetic.
        ra::initialize("fixture-store-never-created");
        require(!ra::snapshot().logged_in, "initial state must be signed out");
        require(rc_client_get_hardcore_enabled(ra::service.client) == 0, "hardcore must be disabled");
        require(reads() == 0, "initialization must not read memory");

        plan("login2", "Alice", R"({"Success":false,"Error":"Invalid credentials","Status":401,"Code":"invalid_credentials"})", 401);
        ra::request_login("Alice", "FakeIncorrectPassword", false);
        until([] { return ra::snapshot().status.find("Sign-in failed") != std::string::npos; }, "login failure was not surfaced");
        require(!ra::snapshot().logged_in && !ra::snapshot().busy, "failed login retained account/busy state");

        auto canceled = plan("login2", "Alice", login_reply("Alice"), 200, true);
        ra::request_login("Alice", "FakePassword", true);
        until([&] { return started(canceled); }, "delayed login never started");
        const auto canceled_generation = ra::snapshot().account_generation;
        ra::request_logout(); ra::ui_tick();
        require(ra::snapshot().account_generation > canceled_generation, "logout must change account generation");
        release(canceled);
        until([&] { return finished(canceled); }, "canceled login did not finish"); settle();
        require(!ra::snapshot().logged_in && !ra::snapshot().busy, "late login response signed canceled account back in");
        require(ra::drain_notifications().empty(), "late login emitted an account notification");
        { std::lock_guard lock(mutex); require(!stored, "late login stored a canceled token"); }

        plan("login2", "Alice", login_reply("Alice"));
        ra::request_login("Alice", "FakePassword", true);
        until([] { return ra::snapshot().logged_in; }, "valid login failed"); settle();
        require(ra::snapshot().username == "Alice", "wrong signed-in account");
        { std::lock_guard lock(mutex); require(stored && stored->username == "Alice" && saves == 1, "remember sign-in did not save fake token"); }
        require(reads() == 0, "login and UI pumps must not read memory");

        std::vector<uint8_t> memory(ra::native::memory_size);
        ra::set_game_identity("unsupported-synthetic-hash");
        ra::native_frame(memory.data()); settle();
        require(!ra::snapshot().game_loaded, "unsupported identity loaded achievements");
        require(reads() == 0, "unsupported identity read memory");

        auto set_response = plan("achievementsets", "Alice", game_reply);
        auto session_response = plan("startsession", "Alice", no_unlocks);
        ra::set_game_identity(ra::native::original_rom_hash);
        ra::native_frame(memory.data());
        const auto reads_before_network = reads();
        until([&] { return finished(session_response); }, "mock game session response did not complete"); settle();
        require(reads() == reads_before_network, "network/UI completion read native memory");
        require(!ra::snapshot().game_loaded, "deferred game memory validation ran outside native frame");
        until([] { return ra::snapshot().game_loaded; }, "native frame did not finalize game", memory.data());
        require(reads() > reads_before_network, "native frame never performed achievement memory reads");
        require(ra::snapshot().total == 2 && ra::snapshot().achievements.size() == 2, "incorrect synthetic achievement list");
        const auto loaded_snapshot = ra::snapshot();
        const auto byte_achievement = std::find_if(loaded_snapshot.achievements.begin(), loaded_snapshot.achievements.end(),
            [](const auto& achievement) { return achievement.id == 990001; });
        const auto measured_achievement = std::find_if(loaded_snapshot.achievements.begin(), loaded_snapshot.achievements.end(),
            [](const auto& achievement) { return achievement.id == 990002; });
        require(byte_achievement != loaded_snapshot.achievements.end() && byte_achievement->badge_name == "00001",
            "byte achievement lost its official badge name");
        require(measured_achievement != loaded_snapshot.achievements.end() && measured_achievement->badge_name == "00002",
            "measured achievement lost its official badge name");
        auto notifications = ra::drain_notifications();
        require(notifications.empty(), "routine game load emitted a startup banner");

        // RA's N64 memory contract exposes raw host-word RDRAM bytes. Reversing
        // the offsets with ^3 is the negative control, not the client layout.
        ra::native_frame(memory.data());
        memory[1 ^ 3] = 3; memory[2 ^ 3] = 7;
        ra::native_frame(memory.data());
        require(ra::snapshot().unlocked == 0, "guest-byte unswapping incorrectly triggered achievement");
        memory[1] = memory[2] = 0;
        memory[1] = 3; memory[2] = 7;
        auto award = plan("awardachievement", "Alice", R"({"Success":true,"Score":0,"SoftcoreScore":5,"AchievementID":990001,"AchievementsRemaining":1})");
        const auto reads_before_idle = reads();
        for (unsigned i = 0; i < 8; ++i) ra::ui_tick();
        require(reads() == reads_before_idle && ra::snapshot().unlocked == 0, "UI idle evaluated live achievement memory");
        ra::native_frame(memory.data());
        require(ra::snapshot().unlocked == 1 && ra::snapshot().points == 5, "native byte trigger did not unlock with correct points");
        notifications = ra::drain_notifications();
        require(notifications.size() == 1 && notifications[0].body == "Synthetic byte trigger", "unlock toast contents/count incorrect");
        require(notifications[0].badge_name == byte_achievement->badge_name,
            "unlock notification badge differs from its official achievement badge");
        until([&] { return finished(award); }, "softcore mock award not submitted"); settle();
        for (unsigned i = 0; i < 4; ++i) ra::native_frame(memory.data());
        require(ra::drain_notifications().empty(), "unlocked trigger repeated notifications");
        { std::lock_guard lock(mutex);
          const auto& request = *std::find_if(requests.begin(), requests.end(), [](const auto& r) { return r.action == "awardachievement"; });
          require(request.hardcore == "0" && request.achievement == "990001", "award request was not the synthetic softcore achievement"); }

        // Delayed old-account game response must not overwrite the replacement
        // account. The single worker serializes HTTP; callbacks are still late.
        ra::game_stopped();
        ra::request_logout(); ra::ui_tick(); settle();
        require(!ra::snapshot().logged_in && ra::snapshot().achievements.empty(), "logout retained previous achievement list");
        { std::lock_guard lock(mutex); require(!stored, "logout retained remembered account"); }
        plan("login2", "Alice", login_reply("Alice"));
        ra::request_login("Alice", "FakePassword", false);
        until([] { return ra::snapshot().logged_in; }, "second Alice login failed");
        auto old_load = plan("achievementsets", "Alice", game_reply, 200, true);
        ra::set_game_identity(ra::native::original_rom_hash);
        ra::native_frame(memory.data());
        until([&] { return started(old_load); }, "old account load never started");
        const auto old_generation = ra::snapshot().account_generation;
        plan("login2", "Bob", login_reply("Bob"));
        ra::request_login("Bob", "FakePasswordBob", false); ra::ui_tick();
        release(old_load);
        until([] { return ra::snapshot().logged_in && ra::snapshot().username == "Bob"; }, "new account not isolated from late response"); settle();
        require(ra::snapshot().account_generation > old_generation && !ra::snapshot().game_loaded, "late old-account load changed replacement state");
        require(ra::drain_notifications().empty(), "old account notification leaked to Bob");
        std::fill(memory.begin(), memory.end(), 0);
        load_game(memory, "Bob");
        require(ra::snapshot().unlocked == 0, "Alice's local unlock leaked into Bob's progress");
        notifications = ra::drain_notifications();
        require(notifications.empty(), "replacement account game load emitted a startup banner");

        ra::game_stopped(); ra::ui_tick();
        require(!ra::snapshot().game_loaded && ra::snapshot().catalog_loaded && ra::snapshot().achievements.size() == 2,
            "game exit did not retain only the signed-in display catalog");
        const auto reads_after_stop = reads();
        ra::native_frame(memory.data()); ra::ui_tick();
        require(reads() == reads_after_stop, "closed game still evaluated memory");
        ra::shutdown();
        require(ra::service.client == nullptr, "shutdown retained rc_client");

        // Remembered-token startup and service restart are fake-store-only.
        { std::lock_guard lock(mutex); stored = ra::platform::Credentials{"Bob", "FakeTokenBob"}; }
        plan("login2", "Bob", login_reply("Bob"));
        ra::initialize("fixture-store-never-created");
        until([] { return ra::snapshot().logged_in; }, "remembered token startup failed"); settle();
        require(!ra::snapshot().game_loaded && reads() == 0, "restart retained old native game state");
        { std::lock_guard lock(mutex); require(requests.back().token_login, "remembered startup used password instead of token"); }
        ra::request_logout(); ra::ui_tick(); settle();
        ra::shutdown();
        no_http_failure();
        { std::lock_guard lock(mutex); require(expected.empty() && catalog_expected.empty() && !stored, "unconsumed fake requests or sign-out credentials"); }
        std::cout << "PASS achievements service: " << checks << " checks; fake HTTP/store only; softcore; UI/background native reads=0\n";
        return 0;
    } catch (const std::exception& error) {
        { std::lock_guard lock(mutex); for (auto& exchange : all_exchanges) exchange->released = true; wake.notify_all(); }
        ra::shutdown();
        std::cerr << "FAIL achievements service: " << error.what() << '\n';
        return 1;
    }
}
