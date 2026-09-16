#include "wr64_ghost.hpp"
#include "wr64_controller_pak.hpp"

#include <array>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

namespace ultramodern {
std::filesystem::path get_save_file_path() { return {}; }
}
namespace {
using namespace wr64::ghost;
namespace fs = std::filesystem;
using Bytes = std::vector<std::uint8_t>;
int checks = 0;
constexpr Course sunny{1, 0, false};
constexpr std::array<Course, 5> courses{{sunny, {2, 0, false}, {8, 2, true}, {1, 1, false}, {1, 0, true}}};
void require(bool condition, const char* message) {
    ++checks;
    if (!condition) throw std::runtime_error(message);
}
fs::path archive(const fs::path& base) {
    auto result = base;
    result.replace_extension();
    result += ".ghosts";
    return result;
}
fs::path saved(const fs::path& base, Course course) {
    return archive(base) / ("course-" + std::to_string(course.index) + "-difficulty-" +
        std::to_string(course.difficulty) + "-reverse-" + (course.reverse ? "1" : "0") + ".bin");
}
Bytes read(const fs::path& path) {
    std::ifstream file(path, std::ios::binary);
    require(file.good(), "expected automatic ghost file is readable");
    return Bytes(std::istreambuf_iterator<char>(file), {});
}
void write(const fs::path& path, const Bytes& bytes) {
    std::ofstream file(path, std::ios::binary | std::ios::trunc);
    file.write(reinterpret_cast<const char*>(bytes.data()), std::streamsize(bytes.size()));
    file.close();
    require(bool(file), "write isolated failure fixture");
}
std::uint32_t read32(const Bytes& bytes, std::size_t offset) {
    return (std::uint32_t(bytes.at(offset)) << 24) | (std::uint32_t(bytes.at(offset + 1)) << 16) |
        (std::uint32_t(bytes.at(offset + 2)) << 8) | bytes.at(offset + 3);
}
std::uint32_t samples(const Bytes& bytes) { return (std::uint32_t(bytes.at(262)) << 8) | bytes.at(263); }
Frame sample(Course course = sunny, float marker = 10.0f) {
    Frame frame;
    frame.course = course;
    frame.eligible = true;
    frame.position = {marker, 2, 4};
    return frame;
}
Frame finish(Course course, std::uint32_t time, float marker = 10.0f) {
    begin_run(course);
    auto frame = sample(course, marker);
    for (int i = 0; i < 4; ++i) observe(frame);
    frame.finished = true;
    frame.elapsed_ms = time;
    observe(frame);
    return frame;
}
void initialize(const fs::path& base) {
    wr64::controller_pak::Store::instance().set_base_save_path_for_tests(base);
    require(initialize_storage(base) == Result::Ok, "bind explicit automatic save profile");
}
void restart(const fs::path& base) {
    reset_session();
    wr64::controller_pak::Store::instance().reset_for_tests();
    initialize(base);
}
void expect_playback(Course course, std::uint32_t time, float marker = 10.0f) {
    begin_run(course);
    require(status().best.available && status().best.course == course && status().best.finish_ms == time,
        "race initialization automatically selects this course's persistent best");
    observe(sample(course));
    require(render_pose().valid && render_pose().position.x == marker + 100,
        "automatically loaded trajectory starts playback without a manual Load action");
}
void write_process(const fs::path& base) {
    initialize(base);
    for (std::size_t i = 0; i < courses.size(); ++i) {
        finish(courses[i], 60001 + std::uint32_t(i), 10.0f + float(i));
        const auto bytes = read(saved(base, courses[i]));
        require(bytes.size() == kFileBytes && read32(bytes, 264) == 60001 + i && samples(bytes) == 5,
            "first finish synchronously creates complete automatic data before end_run or shutdown");
    }
    // Deliberately omit end_run, reset_session and every manual slot API. The
    // orchestrator starts a fresh OS process to read this writer's files.
}
void read_process(const fs::path& base) {
    initialize(base);
    for (std::size_t i = 0; i < courses.size(); ++i)
        expect_playback(courses[i], 60001 + std::uint32_t(i), 10.0f + float(i));
}
void invariants(const fs::path& root) {
    fs::create_directories(root);
    const auto old_cwd = fs::current_path();
    fs::current_path(root);
    reset_session();
    require(initialize_storage({}) == Result::StorageFailure, "empty save base refuses CWD fallback");
    require(initialize_storage("relative.eep") == Result::StorageFailure, "relative save base refuses CWD fallback");
    finish(sunny, 60000);
    reset_session();
    require(fs::is_empty(root), "uninitialized storage creates no files in the working directory");
    fs::current_path(old_cwd);

    const auto base = root / "primary" / "profile.eep";
    initialize(base);
    auto frame = finish(sunny, 60000);
    auto initial = read(saved(base, sunny));
    require(initial.size() == kFileBytes && samples(initial) == 5, "finished trajectory is immediately durable");
    require(initialize_storage(base) == Result::Ok && status().recorded_samples == 5 && status().recording,
        "repeated initialization of the same profile preserves active recording");
    observe(frame);
    observe(frame);
    require(read(saved(base, sunny)) == initial, "post-finish samples do not write storage every frame");
    require(status().autosave_pending, "finished animation tail is queued for a lifecycle flush");
    end_run();
    require(samples(read(saved(base, sunny))) == 7 && !status().autosave_pending,
        "end_run flushes pending finished animation tail");
    restart(base);
    expect_playback(sunny, 60000);
    const auto best = read(saved(base, sunny));
    finish(sunny, 61000, 20);
    end_run();
    require(read(saved(base, sunny)) == best, "slower finish cannot replace automatic fastest trajectory");
    finish(sunny, 60000, 30);
    end_run();
    require(read(saved(base, sunny)) == best, "equal finish cannot replace automatic fastest trajectory");

    begin_run(sunny);
    frame = sample();
    observe(frame);
    frame.retired = true;
    observe(frame);
    frame.retired = false;
    frame.finished = true;
    frame.elapsed_ms = 1000;
    observe(frame);
    end_run();
    require(read(saved(base, sunny)) == best, "retired attempt cannot overwrite disk best");
    begin_run(sunny);
    observe(sample());
    end_run();
    require(read(saved(base, sunny)) == best, "incomplete attempt cannot overwrite disk best");
    begin_run(sunny);
    frame = sample();
    frame.position.x = std::numeric_limits<float>::infinity();
    observe(frame);
    frame = sample();
    frame.finished = true;
    frame.elapsed_ms = 1000;
    observe(frame);
    end_run();
    require(read(saved(base, sunny)) == best, "invalid capture cannot overwrite disk best");
    begin_run(sunny);
    frame = sample();
    for (unsigned i = 0; i < kMaxSamples; ++i) observe(frame);
    frame.finished = true;
    frame.elapsed_ms = 1000;
    observe(frame);
    end_run();
    require(read(saved(base, sunny)) == best, "capture full before the finish cannot overwrite disk best");

    frame = finish(sunny, 59000, 40);
    require(read32(read(saved(base, sunny)), 264) == 59000, "faster finish immediately replaces disk best");
    observe(frame);
    begin_run(courses[1]);
    require(samples(read(saved(base, sunny))) == 6, "next race flushes the previous course's finished tail");
    for (std::size_t i = 1; i < courses.size(); ++i) finish(courses[i], 70000 + std::uint32_t(i));
    restart(base);
    expect_playback(sunny, 59000, 40);
    for (std::size_t i = 1; i < courses.size(); ++i) expect_playback(courses[i], 70000 + std::uint32_t(i));
    frame = finish(sunny, 58000, 50);
    observe(frame);
    observe(frame);
    reset_session();
    require(samples(read(saved(base, sunny))) == 7, "session reset flushes finished tail before clearing RAM");
    initialize(base);
    expect_playback(sunny, 58000, 50);

    const auto other = root / "other-profile" / "profile.eep";
    initialize(other);
    begin_run(sunny);
    observe(sample());
    require(!render_pose().valid && !status().best.available, "another profile does not inherit the first profile's ghost");
    finish(sunny, 80000, 60);
    restart(base);
    expect_playback(sunny, 58000, 50);
    require(read32(read(saved(other, sunny)), 264) == 80000, "per-profile archives retain independent best times");

    const auto manual = root / "manual-slots" / "profile.eep";
    restart(manual);
    finish(sunny, 70000, 80);
    end_run();
    require(save_slot(0) == Result::Ok, "manual slot can retain an earlier slower completed run");
    finish(sunny, 60000, 90);
    end_run();
    auto automatic_best = read(saved(manual, sunny));
    expect_playback(sunny, 60000, 90);
    require(load_slot(0) == Result::Ok, "explicit manual Load remains available alongside autosave");
    require(render_pose().valid && render_pose().position.x == 190,
        "loading a manual slot does not teleport active automatic playback");
    begin_run(sunny);
    observe(sample());
    require(status().best.finish_ms == 60000 && render_pose().valid && render_pose().position.x == 180,
        "manual ghost controls next-race playback while canonical best remains automatic fastest");
    require(read(saved(manual, sunny)) == automatic_best,
        "manual selection changes next-race playback without replacing automatic fastest");
    frame = finish(sunny, 59000, 95);
    require(load_slot(0) == Result::Ok, "manual slot can be selected after a new best finish");
    observe(frame);
    begin_run(sunny);
    observe(sample());
    require(status().best.finish_ms == 59000 && render_pose().valid && render_pose().position.x == 180,
        "finished animation tail does not clear an explicit manual selection before Retry");
    automatic_best = read(saved(manual, sunny));
    finish(sunny, 65000, 100);
    end_run();
    require(read(saved(manual, sunny)) == automatic_best,
        "beating a slower manually selected ghost cannot overwrite faster automatic record");
    restart(manual);
    expect_playback(sunny, 59000, 95);

    const auto wrong_course = root / "wrong-course" / "profile.eep";
    reset_session();
    fs::create_directories(archive(wrong_course));
    const auto other_course_bytes = read(saved(base, courses[1]));
    write(saved(wrong_course, sunny), other_course_bytes);
    initialize(wrong_course);
    begin_run(sunny);
    require(!status().best.available && status().autosave_result == Result::CorruptData,
        "valid container with mismatched course metadata cannot play under another course filename");
    finish(sunny, 1000);
    end_run();
    require(read(saved(wrong_course, sunny)) == other_course_bytes,
        "a new finish preserves a mismatched course archive for explicit recovery");

    const auto blocked = root / "blocked" / "profile.eep";
    reset_session();
    fs::create_directories(blocked.parent_path());
    write(archive(blocked), Bytes{'o', 'c', 'c', 'u', 'p', 'i', 'e', 'd'});
    initialize(blocked);
    finish(sunny, 45000, 70);
    require(status().autosave_result == Result::StorageFailure && status().best.available,
        "write failure is reported while completed ghost remains usable in RAM");
    require(read(archive(blocked)) == Bytes({'o', 'c', 'c', 'u', 'p', 'i', 'e', 'd'}),
        "storage failure leaves the conflicting regular file intact");
    fs::remove(archive(blocked)); // Only this test's explicitly created regular file.
    end_run();
    require(status().autosave_result == Result::Ok && fs::exists(saved(blocked, sunny)),
        "lifecycle flush retries a previously failed save after storage recovers");
    restart(blocked);
    expect_playback(sunny, 45000, 70);

    const auto recovered = root / "recovered-faster" / "profile.eep";
    restart(recovered);
    finish(sunny, 50000, 75);
    end_run();
    const auto faster_bytes = read(saved(recovered, sunny));
    reset_session();
    for (const auto attempt_time : {55000u, 50000u}) {
        reset_session();
#ifdef _WIN32
        // An exclusive handle causes a real Windows read-sharing failure;
        // the known-valid file itself stays byte-for-byte unchanged.
        const auto locked = CreateFileW(saved(recovered, sunny).c_str(), GENERIC_READ,
            0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        require(locked != INVALID_HANDLE_VALUE, "exclusively lock isolated archive for transient read failure");
#else
        // POSIX file_size on a directory reports EISDIR. All paths belong to
        // this test's fresh profile, and only the empty blocker is removed.
        auto parked_primary = saved(recovered, sunny);
        parked_primary += ".held";
        fs::rename(saved(recovered, sunny), parked_primary);
        require(fs::create_directory(saved(recovered, sunny)), "create isolated transient read-error fixture");
#endif
        initialize(recovered);
        begin_run(sunny);
        const auto before_finish = status();
        frame = sample(sunny, 100);
        for (int i = 0; i < 4; ++i) observe(frame);
#ifdef _WIN32
        require(CloseHandle(locked) != 0, "restore read access to isolated archive before finish");
#else
        fs::remove(saved(recovered, sunny));
        fs::rename(parked_primary, saved(recovered, sunny));
#endif
        require(!before_finish.best.available && before_finish.autosave_result == Result::StorageFailure,
            "transient storage failure leaves the upcoming race unaware of existing faster or equal ghost");
        frame.finished = true;
        frame.elapsed_ms = attempt_time;
        observe(frame);
        for (int i = 0; i < 3; ++i) observe(frame);
        end_run();
        require(read(saved(recovered, sunny)) == faster_bytes,
            "post-finish animation tail cannot overwrite a faster or equal ghost recovered during finish save");
        require(status().best.finish_ms == 50000 && status().autosave_result == Result::Ok,
            "recovered faster or equal ghost remains the canonical RAM best after finish");
        restart(recovered);
        expect_playback(sunny, 50000, 75);
    }

    const auto damaged = root / "corrupt" / "profile.eep";
    restart(damaged);
    finish(sunny, 65000, 80);
    end_run();
    finish(sunny, 64000, 90);
    end_run();
    const auto primary = saved(damaged, sunny);
    auto backup = primary;
    backup += ".bak";
    const auto good_backup = read(backup);
    require(read32(good_backup, 264) == 65000, "replacement retains a validated previous best backup");
    reset_session();
    auto corrupt = read(primary);
    corrupt.at(280) ^= 0x80;
    write(primary, corrupt);
    initialize(damaged);
    expect_playback(sunny, 65000, 80);
    finish(sunny, 63000, 100);
    end_run();
    require(read(backup) == good_backup, "repairing corrupt primary does not replace good backup with corrupt bytes");
    reset_session();
    corrupt = read(primary);
    corrupt.at(281) ^= 0x40;
    auto corrupt_backup = good_backup;
    corrupt_backup.at(282) ^= 0x20;
    write(primary, corrupt);
    write(backup, corrupt_backup);
    initialize(damaged);
    begin_run(sunny);
    require(!status().best.available && status().autosave_result == Result::CorruptData,
        "two corrupt copies are rejected without providing a damaged ghost");
    finish(sunny, 62000);
    end_run();
    require(status().autosave_result == Result::CorruptData && read(primary) == corrupt && read(backup) == corrupt_backup,
        "a new finish cannot silently overwrite two corrupt archive copies");
    reset_session();
}
}
int main(int argc, char** argv) {
    try {
        if (argc != 3) throw std::runtime_error("requires --invariants/--write/--read and an isolated absolute path");
        const auto path = fs::path(argv[2]);
        if (!path.is_absolute()) throw std::runtime_error("test path must be absolute");
        const std::string_view mode = argv[1];
        if (mode == "--write") write_process(path);
        else if (mode == "--read") read_process(path);
        else if (mode == "--invariants") invariants(path);
        else throw std::runtime_error("unknown test mode");
        std::cout << checks << " automatic ghost persistence checks passed (" << mode << ")\n";
        return 0;
    }
    catch (const std::exception& error) { std::cerr << "FAIL: " << error.what() << '\n'; return 1; }
}
