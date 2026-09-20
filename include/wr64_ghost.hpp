#pragma once

#include <array>
#include <cstdint>
#include <filesystem>

namespace wr64::ghost {

// Independently authored USA adapter. Uses Shindou's existing host Pak Store;
// the trajectory container is versioned host data, not a Shindou ROM format.
constexpr std::uint32_t kMaxSamples = 2557;
constexpr std::uint32_t kFileBytes = 30976;
constexpr std::uint32_t kSampleMilliseconds = 50;

struct Course {
    std::int32_t index = -1;
    std::int32_t difficulty = 0;
    bool reverse = false;
    bool operator==(const Course&) const = default;
};

struct Vec3 { float x = 0, y = 0, z = 0; };

// One call per native display-list production pass, never a synthetic RT64 frame.
// begin_run must be called on race initialization, including a same-course retry.
struct Frame {
    Course course{};
    bool eligible = false;
    bool paused = false;
    bool retired = false;
    bool finished = false;
    bool toggle_visibility = false;
    std::uint32_t elapsed_ms = 0; // Exact native Chkcrs.ctime_total, not sample*50.
    Vec3 position{};
    Vec3 forward{0, 0, 1};
    Vec3 up{0, 1, 0};
    Vec3 left{1, 0, 0};
};

struct RenderPose {
    bool valid = false;
    Vec3 position{};
    Vec3 forward{0, 0, 1};
    Vec3 up{0, 1, 0};
    std::uint32_t animation_frame = 0;
    std::uint32_t sample_index = 0;
};

enum class Result {
    Ok, NoGhost, InvalidSlot, CorruptData, StorageFailure, WouldOverwriteBetter
};

struct SlotInfo {
    bool available = false;
    Course course{};
    std::uint32_t finish_ms = 0;
    std::uint32_t samples = 0;
};

struct Status {
    bool visible = true;
    bool recording = false;
    bool recording_full = false;
    bool recording_invalid = false;
    bool can_save = false;
    bool playback_active = false;
    bool dolphin_resident = false;
    std::uint32_t recorded_samples = 0;
    SlotInfo best{};
    std::array<SlotInfo, 2> slots{};
    Result last_result = Result::Ok;
    bool autosave_ready = false;
    bool autosave_pending = false;
    Result autosave_result = Result::Ok;
};

// All public operations are thread-safe. Loading changes the ghost selected for
// the next race/retry; it does not teleport an already playing ghost mid-race.
void begin_run(Course course);
// Bind only after runtime save initialization. Automatic bests are independent
// of the two optional Pak slots and keyed by course, difficulty and direction.
Result initialize_storage(const std::filesystem::path& save_base);
void observe(const Frame& frame);
void end_run();
void set_visible(bool visible);
void set_dolphin_resident(bool resident);
Status status();
RenderPose render_pose();
Result refresh_slots();
Result save_slot(int slot, bool overwrite_better = false); // zero-based slots
Result load_slot(int slot);
Result clear_slot(int slot);
const char* result_message(Result result);

// Flushes completed autosaves, then clears host RAM; used at shutdown and in tests.
// It does not erase the Pak or alter persistent visibility/settings.
void reset_session();

} // namespace wr64::ghost
