// Each lifecycle case is a separate CTest process. A stale callback crash is
// therefore reported as a failed case without hiding the remaining results.
namespace lifecycle {
using namespace fixture;
std::vector<uint8_t> sign_in_and_load(bool one_remaining) {
    ra::initialize("fixture-store-never-created");
    plan("login2", "Alice", login_reply("Alice"));
    ra::request_login("Alice", "SyntheticPasswordOnly", false);
    until([] { return ra::snapshot().logged_in; }, "lifecycle Alice login failed");
    std::vector<uint8_t> memory(ra::native::memory_size);
    plan("achievementsets", "Alice", game_reply);
    plan("startsession", "Alice", one_remaining
        ? R"({"Success":true,"Unlocks":[{"ID":990002,"When":1234567899}],"HardcoreUnlocks":[]})"
        : no_unlocks);
    ra::set_game_identity(ra::native::original_rom_hash);
    until([] { return ra::snapshot().game_loaded; }, "lifecycle game load failed", memory.data());
    require(ra::snapshot().total == 2 && ra::snapshot().unlocked == (one_remaining ? 1u : 0u),
        "lifecycle starting progress mismatch");
    ra::drain_notifications();
    ra::native_frame(memory.data()); // arm the false-to-true trigger
    settle();
    return memory;
}
std::string award_reply(uint32_t id, uint32_t remaining) {
    return "{\"Success\":true,\"Score\":0,\"SoftcoreScore\":7,\"AchievementID\":" + std::to_string(id) +
        ",\"AchievementsRemaining\":" + std::to_string(remaining) + "}";
}
void trigger_first(std::vector<uint8_t>& memory) {
    memory[1] = 3; memory[2] = 7;
    ra::native_frame(memory.data());
}
size_t award_count(const std::string& user) {
    std::lock_guard lock(mutex);
    return std::count_if(requests.begin(), requests.end(), [&](const Request& request) {
        return request.action == "awardachievement" && request.user == user;
    });
}
void all_awards_are_softcore() {
    std::lock_guard lock(mutex);
    for (const auto& request : requests) if (request.action == "awardachievement")
        require(request.hardcore == "0", "lifecycle request unexpectedly enabled hardcore");
}

void last_award_after_close(bool logout) {
    auto memory = sign_in_and_load(true);
    auto last_award = plan("awardachievement", "Alice", award_reply(990001, 0), 200, true);
    trigger_first(memory);
    until([&] { return started(last_award); }, "last award request never started");
    require(ra::snapshot().unlocked == 2, "last synthetic achievement did not trigger");
    ra::drain_notifications();
    const auto reads_before_close = reads();
    const auto old_generation = ra::snapshot().account_generation;
    const std::weak_ptr<ra::Session> old_session = ra::service.current;
    if (logout) { ra::request_logout(); ra::ui_tick(); }
    else { ra::game_stopped(); ra::ui_tick(); }
    require(!ra::snapshot().game_loaded, "closed game still exposed loaded achievement list");
    if (logout) require(!ra::snapshot().logged_in && ra::snapshot().account_generation > old_generation,
        "logout failed to retire old account");
    {
        // Observe without retaining ownership through callback completion: the
        // service itself must keep the originating client and game alive.
        const auto retained = old_session.lock();
        require(retained && retained->pending > 0, "retired award lost its pending ownership");
        require(rc_client_get_game_info(retained->client) != nullptr, "retired award lost its original game");
    }
    release(last_award);
    until([&] { return finished(last_award); }, "late last-award response never finished");
    // This completes the real rcheevos callback with AchievementsRemaining=0.
    // The old implementation dereferenced client->game after it was unloaded.
    settle();
    require(!ra::snapshot().game_loaded && (logout ? ra::snapshot().achievements.empty()
        : (ra::snapshot().catalog_loaded && ra::snapshot().achievements.size() == 2 && ra::snapshot().unlocked == 2)),
        "late award reactivated gameplay or changed the signed-in display catalog");
    require(ra::drain_notifications().empty(), "closed game leaked a completion notification");
    require(reads() == reads_before_close, "late award touched retired native memory");
    require(award_count("Alice") == 1, "last award was dropped or duplicated");
    if (logout) require(old_session.expired(), "completed retired account was not destroyed");
    all_awards_are_softcore();
}

void old_account_retry(bool fail_retired_retry) {
    auto memory = sign_in_and_load(false);
    // The official client retries once immediately, then schedules a one-second
    // retry. Switch accounts before that scheduled retry becomes due.
    constexpr const char* temporary_outage = R"({"Success":false,"Error":"Synthetic temporary outage"})";
    plan("awardachievement", "Alice", temporary_outage, 503);
    auto second_failure = plan("awardachievement", "Alice", temporary_outage, 503);
    trigger_first(memory);
    until([&] { return finished(second_failure); }, "immediate award retry did not finish");
    settle();
    require(award_count("Alice") == 2, "expected initial attempt plus immediate retry");
    {
        std::lock_guard lock(ra::service.io_mutex);
        require(ra::service.work.empty() && ra::service.completed.empty(),
            "retry test must reach the scheduled-only state with no pending HTTP");
    }
    ra::drain_notifications();
    const auto alice_generation = ra::snapshot().account_generation;
    // Retirement flushes already-scheduled retries under their original client
    // before starting the new account; it must not abandon scheduled-only work.
    auto old_retry = plan("awardachievement", "Alice", fail_retired_retry ? temporary_outage : award_reply(990001, 1),
        fail_retired_retry ? 503 : 200);
    plan("login2", "Bob", login_reply("Bob"));
    ra::request_login("Bob", "SyntheticBobPasswordOnly", false);
    until([] { return ra::snapshot().logged_in && ra::snapshot().username == "Bob"; }, "Bob login failed during old retry");
    require(ra::snapshot().account_generation > alice_generation, "replacement account reused old generation");
    const auto reads_before_retry = reads();
    until([&] { return finished(old_retry); }, "retired account's scheduled award was lost");
    settle();
    require(award_count("Alice") == 3 && award_count("Bob") == 0, "old unlock was submitted with replacement account credentials");
    require(ra::snapshot().username == "Bob" && !ra::snapshot().game_loaded && ra::snapshot().unlocked == 0,
        "old award response changed Bob's progress");
    require(ra::drain_notifications().empty(), "old retry notification leaked to replacement account");
    require(reads() == reads_before_retry, "retired retry read native memory");
    require(ra::service.sessions.size() == 1 && ra::service.current->pending == 0,
        "completed retired retry retained a session or callback ownership");
    all_awards_are_softcore();
}

void shutdown_drains_accepted_awards() {
    auto memory = sign_in_and_load(false);
    auto first = plan("awardachievement", "Alice", award_reply(990001, 1), 200, true);
    auto second = plan("awardachievement", "Alice", award_reply(990002, 0));
    trigger_first(memory);
    until([&] { return started(first); }, "first queued award never started");
    memory[0x10] = 10;
    ra::native_frame(memory.data());
    require(ra::snapshot().unlocked == 2, "second queued achievement did not trigger");
    require(!started(second), "second HTTP bypassed the blocked single worker");
    {
        std::lock_guard lock(ra::service.io_mutex);
        require(std::any_of(ra::service.work.begin(), ra::service.work.end(), [](const auto& item) {
            return item.kind == ra::Work::Http;
        }), "second award was not accepted into the HTTP queue");
    }
    ra::drain_notifications();
    std::thread release_during_shutdown([&] {
        std::this_thread::sleep_for(30ms);
        release(first);
    });
    // Both requests must go through the fake HTTP platform, and their official
    // callbacks must complete while their original client/game are still alive.
    ra::shutdown();
    release_during_shutdown.join();
    require(finished(first) && finished(second), "shutdown discarded an already accepted award instead of submitting it");
    require(award_count("Alice") == 2, "shutdown did not dispatch exactly two accepted awards");
    require(ra::service.client == nullptr && !ra::service.worker.joinable(), "shutdown left active service resources");
    require(ra::drain_notifications().empty(), "shutdown published a stale completion notification");
    all_awards_are_softcore();
}

void invalid_saved_token_is_removed(bool expired) {
    { std::lock_guard lock(mutex); stored = ra::platform::Credentials{"Alice", "ExpiredSyntheticToken"}; }
    plan("login2", "Alice", expired
        ? R"({"Success":false,"Error":"Expired token","Status":401,"Code":"expired_token"})"
        : R"({"Success":false,"Error":"Invalid token","Status":401,"Code":"invalid_credentials"})", 401);
    ra::initialize("fixture-store-never-created");
    until([] { return ra::snapshot().status.find("Sign-in failed") != std::string::npos; }, "expired token was not rejected");
    settle();
    require(!ra::snapshot().logged_in && !ra::snapshot().busy, "expired token retained login state");
    { std::lock_guard lock(mutex);
      require(!stored && removes > 0, "invalid remembered token was not deleted");
      require(requests.size() == 1 && requests[0].token_login, "expired token was treated as a password"); }
    require(reads() == 0, "expired token handling read game memory");
    ra::shutdown();
    ra::initialize("fixture-store-never-created");
    ra::ui_tick(); settle();
    { std::lock_guard lock(mutex); require(requests.size() == 1, "restart retried the invalid saved token"); }
}

void transient_failure_preserves_token() {
    { std::lock_guard lock(mutex); stored = ra::platform::Credentials{"Alice", "SyntheticSavedToken"}; }
    auto temporary_failure = plan("login2", "Alice", R"({"Success":false,"Error":"Synthetic temporary outage"})", 503);
    ra::initialize("fixture-store-never-created");
    until([&] { return finished(temporary_failure) && !ra::snapshot().busy; }, "temporary token failure was not completed");
    settle();
    require(!ra::snapshot().logged_in, "temporary failure somehow logged in");
    { std::lock_guard lock(mutex);
      require(stored && stored->token == "SyntheticSavedToken" && removes == 0, "temporary outage erased valid remembered credentials"); }
    require(reads() == 0, "temporary token failure touched memory");
    ra::shutdown();
    plan("login2", "Alice", login_reply("Alice"));
    ra::initialize("fixture-store-never-created");
    until([] { return ra::snapshot().logged_in; }, "preserved token could not sign in on next startup");
    settle();
    { std::lock_guard lock(mutex); require(requests.size() == 2 && requests[1].token_login, "preserved token startup did not retry correctly"); }
    ra::request_logout(); ra::ui_tick(); settle();
}

void queued_logout_before_shutdown() {
    { std::lock_guard lock(mutex); stored = ra::platform::Credentials{"Alice", "SyntheticSavedToken"}; }
    plan("login2", "Alice", login_reply("Alice"));
    ra::initialize("fixture-store-never-created");
    until([] { return ra::snapshot().logged_in; }, "queued-logout token login failed");
    settle();
    { std::lock_guard lock(mutex); require(stored.has_value(), "queued-logout control must begin remembered"); }
    ra::request_logout();
    // No UI/native pump is allowed between the explicit intent and shutdown.
    ra::shutdown();
    { std::lock_guard lock(mutex); require(!stored, "shutdown discarded explicit queued sign-out intent"); }
    require(ra::service.client == nullptr, "queued-logout shutdown retained client");
}

void run(const std::string& name) {
    if (name == "last-award-stop") last_award_after_close(false);
    else if (name == "last-award-logout") last_award_after_close(true);
    else if (name == "old-account-retry") old_account_retry(false);
    else if (name == "retired-retry-failure") old_account_retry(true);
    else if (name == "shutdown-drain") shutdown_drains_accepted_awards();
    else if (name == "invalid-token") invalid_saved_token_is_removed(false);
    else if (name == "expired-token") invalid_saved_token_is_removed(true);
    else if (name == "transient-token") transient_failure_preserves_token();
    else if (name == "queued-logout-shutdown") queued_logout_before_shutdown();
    else throw std::runtime_error("unknown lifecycle case");
}
}
