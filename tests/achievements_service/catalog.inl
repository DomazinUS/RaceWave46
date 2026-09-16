// Catalog requests use the real pinned API parsers, but never real credentials,
// HTTP, or native RAM. Held replies exercise account and gameplay ownership.
namespace catalog_fixture {
using namespace fixture;

const ra::Achievement& achievement(const ra::Snapshot& snapshot, uint32_t id) {
    const auto it = std::find_if(snapshot.achievements.begin(), snapshot.achievements.end(),
        [&](const auto& item) { return item.id == id; });
    if (it == snapshot.achievements.end()) throw std::runtime_error("catalog achievement missing");
    return *it;
}
auto plan_unlocks(const std::string& user, const char* body, bool hold = false) {
    auto response = plan("unlocks", user, body, 200, hold);
    response->hardcore = "0";
    return response;
}
size_t catalog_count() { std::lock_guard lock(mutex); return catalog_requests.size(); }
void allow_refresh() {
    // Move only the display refresh deadline; do not alter rc_client's clock,
    // gameplay frame cadence, HTTP ordering, or pending callback ownership.
    std::lock_guard lock(ra::service.mutex);
    ra::service.catalog_requested_at = ra::Clock::now() - 6s;
}
void sign_in(const std::string& user) {
    ra::initialize("fixture-store-never-created");
    plan("login2", user, login_reply(user));
    ra::request_login(user, "SyntheticCatalogPassword", false);
    until([] { const auto view = ra::snapshot(); return view.logged_in && view.catalog_loaded && !view.catalog_busy; },
        "prelaunch catalog did not load");
    settle();
}
void require_no_gameplay() {
    require(reads() == 0 && ra::service.frames == 0, "display catalog evaluated native gameplay memory");
    require(!ra::snapshot().game_loaded && rc_client_get_game_info(ra::service.client) == nullptr,
        "display catalog activated an rc_client game");
    std::lock_guard lock(mutex);
    require(std::none_of(requests.begin(), requests.end(), [](const auto& request) {
        return request.action == "achievementsets" || request.action == "startsession" ||
            request.action == "awardachievement" || request.action == "submitlbentry" || request.action == "ping";
    }), "prelaunch catalog sent a gameplay/session/submission request");
}

void prelaunch_metadata() {
    plan_unlocks("Alice", R"({"Success":true,"UserUnlocks":[990001,123456,101000001]})");
    sign_in("Alice");
    const auto view = ra::snapshot();
    require(view.catalog_loaded && !view.catalog_busy && !view.catalog_status.empty(), "catalog readiness was not exposed");
    require(view.username == "Alice" && view.total == 2 && view.total_points == 7, "catalog account/count/point totals incorrect");
    require(view.unlocked == 1 && view.points == 5, "catalog progress counted an unknown ID or wrong achievement");
    require(view.achievements.size() == 2 && std::none_of(view.achievements.begin(), view.achievements.end(),
        [](const auto& item) { return item.id == 101000001; }),
        "reserved client warning appeared as a playable catalog achievement");
    const auto& first = achievement(view, 990001);
    const auto& second = achievement(view, 990002);
    require(first.title == "Synthetic byte trigger" && first.description == "Fixture only" && first.points == 5 &&
        first.badge_name == "00001" && first.unlocked, "first catalog metadata or progress incorrect");
    require(second.badge_name == "00002" && second.points == 2 && !second.unlocked, "second catalog metadata or progress incorrect");
    require(first.rarity == 12.5f && first.rarity_hardcore == 4.25f &&
        second.rarity == 75.0f && second.rarity_hardcore == 20.5f, "official rarity fields lost or changed");
    require(first.unlock_time == 0 && second.unlock_time == 0,
        "ID-only prelaunch unlock response fabricated an unlock timestamp");
    require(ra::drain_notifications().empty(), "display-only catalog emitted a game-load or unlock notification");
    {
        std::lock_guard lock(mutex);
        require(catalog_requests.size() == 2, "sign-in did not issue exactly one patch and one progress request");
        require(std::all_of(catalog_requests.begin(), catalog_requests.end(), [](const auto& request) {
            return request.user == "Alice" && request.token_login && request.game == "10617" &&
                (request.action == "patch" || (request.action == "unlocks" && request.hardcore == "0"));
        }), "catalog request lost its authenticated account, game, or softcore-inclusive progress mode");
    }
    require_no_gameplay();
}

void refresh_failure_and_retry() {
    plan_unlocks("Alice", R"({"Success":true,"UserUnlocks":[990001]})");
    sign_in("Alice");
    const auto original = ra::snapshot();
    const auto initial_count = catalog_count();
    for (unsigned i = 0; i < 4; ++i) { ra::request_catalog_refresh(); ra::ui_tick(); }
    settle();
    require(catalog_count() == initial_count, "catalog refresh ignored the five-second rate limit");

    for (const auto& reply : {std::string(R"({"Success":false,"Error":"Synthetic catalog outage"})"), std::string("{malformed")}) {
        allow_refresh();
        auto failed = plan("patch", "Alice", reply, reply.starts_with("{malformed") ? 200 : 503);
        ra::request_catalog_refresh();
        until([&] { return finished(failed) && !ra::snapshot().catalog_busy; }, "catalog failure did not settle");
        settle();
        const auto cached = ra::snapshot();
        require(cached.catalog_loaded && cached.total == original.total && cached.total_points == original.total_points &&
            cached.unlocked == original.unlocked && cached.points == original.points,
            "failed or malformed refresh discarded the previous catalog/progress");
        require(achievement(cached, 990001).badge_name == "00001" && achievement(cached, 990001).unlocked,
            "failed refresh changed the cached achievement");
        require(!cached.catalog_status.empty(), "catalog failure exposed no retry status");
    }
    allow_refresh();
    auto retried = plan_unlocks("Alice", R"({"Success":true,"UserUnlocks":[990002]})");
    ra::request_catalog_refresh();
    until([&] { return finished(retried) && !ra::snapshot().catalog_busy; }, "catalog refresh could not retry after failure");
    settle();
    const auto updated = ra::snapshot();
    require(updated.catalog_loaded && updated.unlocked == 1 && updated.points == 2 &&
        !achievement(updated, 990001).unlocked && achievement(updated, 990002).unlocked,
        "successful retry did not replace cached account progress");
    require_no_gameplay();
}

void logout_with_pending_catalog() {
    auto held = plan_unlocks("Alice", R"({"Success":true,"UserUnlocks":[990001]})", true);
    ra::initialize("fixture-store-never-created");
    plan("login2", "Alice", login_reply("Alice"));
    ra::request_login("Alice", "SyntheticCatalogPassword", false);
    until([&] { return started(held); }, "held catalog progress never started");
    require(ra::snapshot().logged_in && ra::snapshot().catalog_busy, "pending catalog ownership not exposed");
    const auto generation = ra::snapshot().account_generation;
    ra::request_logout(); ra::ui_tick();
    require(!ra::snapshot().logged_in && !ra::snapshot().catalog_loaded && !ra::snapshot().catalog_busy &&
        ra::snapshot().achievements.empty(), "logout retained pending account catalog");
    release(held);
    until([&] { return finished(held); }, "retired catalog reply did not complete");
    settle();
    require(ra::snapshot().account_generation > generation && !ra::snapshot().catalog_loaded &&
        ra::snapshot().achievements.empty(), "late catalog completion restored a logged-out account");
    require(ra::drain_notifications().empty(), "late catalog completion emitted a stale notification");
    require_no_gameplay();
}

void account_swap_with_pending_catalog() {
    auto alice_patch = plan("patch", "Alice", catalog_reply, 200, true);
    ra::initialize("fixture-store-never-created");
    plan("login2", "Alice", login_reply("Alice"));
    ra::request_login("Alice", "SyntheticCatalogPassword", false);
    until([&] { return started(alice_patch); }, "old-account catalog request never started");
    const auto alice_generation = ra::snapshot().account_generation;
    auto bob_login = plan("login2", "Bob", login_reply("Bob"), 200, true);
    plan_unlocks("Bob", R"({"Success":true,"UserUnlocks":[990002]})");
    ra::request_login("Bob", "SyntheticBobCatalogPassword", false); ra::ui_tick();
    release(alice_patch);
    until([&] { return started(bob_login); }, "replacement login did not follow old catalog request");
    require(!ra::snapshot().catalog_loaded && ra::snapshot().achievements.empty(),
        "old-account catalog appeared while replacement login was pending");
    release(bob_login);
    until([] { const auto view = ra::snapshot(); return view.username == "Bob" && view.catalog_loaded && !view.catalog_busy; },
        "replacement account catalog did not load");
    settle();
    const auto bob = ra::snapshot();
    require(bob.account_generation > alice_generation && bob.unlocked == 1 && bob.points == 2 &&
        !achievement(bob, 990001).unlocked && achievement(bob, 990002).unlocked,
        "old catalog response leaked progress into replacement account");
    require(ra::drain_notifications().empty(), "old catalog response leaked a notification to replacement account");
    require_no_gameplay();
}

void live_unlock_over_stale_catalog() {
    sign_in("Alice");
    std::vector<uint8_t> memory(ra::native::memory_size);
    load_game(memory, "Alice");
    ra::drain_notifications();
    ra::native_frame(memory.data()); // arm the native false-to-true trigger
    allow_refresh();
    auto old_progress = plan_unlocks("Alice", catalog_no_unlocks, true);
    ra::request_catalog_refresh();
    until([&] { return started(old_progress); }, "held live catalog refresh never started");
    auto award = plan("awardachievement", "Alice", lifecycle::award_reply(990001, 1));
    lifecycle::trigger_first(memory);
    const auto unlocked = ra::snapshot();
    require(unlocked.game_loaded && unlocked.unlocked == 1 && unlocked.points == 5,
        "native unlock did not occur while catalog response was held");
    const auto unlock_time = achievement(unlocked, 990001).unlock_time;
    require(unlock_time > 0, "live unlock did not retain the official runtime timestamp");
    auto notices = ra::drain_notifications();
    require(notices.size() == 1 && notices[0].badge_name == "00001", "live unlock notification metadata incorrect");
    release(old_progress);
    until([&] { return finished(award) && !ra::snapshot().catalog_busy; }, "stale catalog and queued award did not complete");
    settle();
    const auto after = ra::snapshot();
    require(after.game_loaded && after.unlocked == 1 && after.points == 5 && achievement(after, 990001).unlocked &&
        achievement(after, 990001).unlock_time == unlock_time, "stale catalog response reverted live unlock progress");
    require(ra::drain_notifications().empty(), "stale catalog duplicated a native unlock notification");
    const auto stopped_reads = reads();
    ra::game_stopped(); ra::ui_tick();
    const auto stopped = ra::snapshot();
    require(!stopped.game_loaded && stopped.logged_in && stopped.catalog_loaded && stopped.unlocked == 1 &&
        stopped.points == 5 && achievement(stopped, 990001).unlock_time == unlock_time,
        "game stop discarded signed-in catalog or earned progress");
    ra::native_frame(memory.data()); ra::ui_tick();
    require(reads() == stopped_reads, "retained display catalog evaluated closed-game memory");
    require(lifecycle::award_count("Alice") == 1, "catalog refresh duplicated or discarded the live softcore award");
    lifecycle::all_awards_are_softcore();
}

void run(const std::string& name) {
    if (name == "prelaunch") prelaunch_metadata();
    else if (name == "refresh") refresh_failure_and_retry();
    else if (name == "logout") logout_with_pending_catalog();
    else if (name == "account-swap") account_swap_with_pending_catalog();
    else if (name == "live-unlock") live_unlock_over_stale_catalog();
    else throw std::runtime_error("unknown catalog case");
}
}
