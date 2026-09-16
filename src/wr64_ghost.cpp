#include "wr64_diagnostic_policy.h"
#include "wr64_ghost.hpp"
#include "wr64_controller_pak.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <mutex>
#include <span>
#include <vector>
#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#endif

namespace wr64::ghost {
namespace {
using controller_pak::Store;
constexpr std::size_t kMetadataBytes = 256;
constexpr std::size_t kSlotBytes = 15360;
constexpr std::size_t kSlotHeaderBytes = 16;
constexpr std::array<std::uint8_t, 8> kMagic{'W','R','6','4','G','H','0','1'};
static_assert(kMetadataBytes + 2 * kSlotBytes == kFileBytes);
static_assert(kSlotHeaderBytes + kMaxSamples * 6 <= kSlotBytes);
static_assert(kFileBytes + 512 == controller_pak::kCapacityBytes);

struct Point { std::int16_t x, y, z; };
struct Run {
    Course course{};
    std::uint32_t finish_ms = 0;
    std::uint32_t goal_samples = 0;
    std::vector<Point> points;
    bool complete() const {
        return finish_ms > 0 && finish_ms <= 599999 && goal_samples > 0 &&
            goal_samples < kMaxSamples && goal_samples <= points.size() &&
            points.size() <= kMaxSamples;
    }
};
struct State {
    bool visible = true, resident = false, active = false;
    bool capturing = false, full = false, invalid = false, finished = false;
    bool candidate = false;
    Run recording{}, best{}, playback{}, selected{};
    std::uint32_t cursor = 0;
    RenderPose pose{};
    std::array<SlotInfo, 2> slots{};
    Result last = Result::Ok;
};
std::mutex mutex;
State state;
struct AutomaticEntry {
    Run best{};
    bool loaded = false, dirty = false;
    Result load_result = Result::Ok;
    Result save_result = Result::Ok;
};
struct AutomaticStorage {
    std::filesystem::path directory;
    std::array<AutomaticEntry, 9 * 3 * 2> entries{};
    Result last = Result::Ok;
} automatic;

AutomaticEntry& automatic_entry(Course course);
void flush_automatic();
void save_automatic(AutomaticEntry& entry);

bool valid_course(Course course) {
    return course.index >= 0 && course.index <= 8 &&
        course.difficulty >= 0 && course.difficulty <= 2;
}
SlotInfo info(const Run& run) {
    return {run.complete(), run.course, run.finish_ms,
            static_cast<std::uint32_t>(run.points.size())};
}
void start(Course course) {
    flush_automatic();
    state.active = valid_course(course);
    state.capturing = state.active;
    state.full = state.invalid = state.finished = state.candidate = false;
    state.recording = {};
    state.recording.course = course;
    state.recording.points.reserve(kMaxSamples);
    if (state.active && !automatic.directory.empty()) {
        // Disk best is independent of a deliberately selected manual Pak ghost.
        state.best = automatic_entry(course).best;
    }
    state.playback = state.best.complete() && state.best.course == course ? state.best : Run{};
    if (state.selected.complete() && state.selected.course == course) state.playback = state.selected;
    state.cursor = 0;
    state.pose = {};
}
Vec3 subtract(Vec3 a, Vec3 b) { return {a.x-b.x,a.y-b.y,a.z-b.z}; }
Vec3 cross(Vec3 a, Vec3 b) {
    return {a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x};
}
Vec3 normalized(Vec3 v, Vec3 fallback) {
    const float square = v.x*v.x + v.y*v.y + v.z*v.z;
    if (!std::isfinite(square) || square <= 0.000001f) return fallback;
    const float scale = 1.0f/std::sqrt(square);
    return {v.x*scale,v.y*scale,v.z*scale};
}
Vec3 unpack(Point p) { return {float(p.x),float(p.y),float(p.z)}; }
bool quantize(float value, std::int16_t& output) {
    if (!std::isfinite(value)) return false;
    const float rounded = std::round(value); // nearest, ties away from zero
    if (rounded < -32768.0f || rounded > 32767.0f) return false;
    output = static_cast<std::int16_t>(rounded);
    return true;
}
void advance_playback(const Frame& frame) {
    if (!state.playback.complete()) {
        state.pose.valid = false;
        return;
    }
    if (state.cursor >= state.playback.points.size()) {
        // Native playback holds its last transform when the trajectory ends;
        // its swimming animation still advances unless the race is paused.
        state.pose.animation_frame=(state.pose.animation_frame+2)%16;
        return;
    }
    const auto i = state.cursor;
    const Vec3 position = unpack(state.playback.points[i]);
    Vec3 direction = state.pose.valid ? state.pose.forward : normalized(frame.forward,{0,0,1});
    Vec3 displacement{};
    if (i > 0) displacement = subtract(position,unpack(state.playback.points[i-1]));
    else if (state.playback.points.size() > 1)
        displacement = subtract(unpack(state.playback.points[1]),position);
    const float distance_squared = displacement.x*displacement.x +
        displacement.y*displacement.y + displacement.z*displacement.z;
    if (distance_squared > 0.01f) {
        displacement = normalized(displacement,direction);
        displacement.y *= 0.2f;
        direction = displacement;
    }
    // Retain the source game's side-slide/start-heading behavior without
    // importing its original animation or native instructions.
    // The 100-unit lateral separation shrinks by one each sample. Heading
    // follows the player until the last ten units, then blends to the path.
    const float blend = std::clamp((99.0f-float(i))*0.1f,0.0f,1.0f);
    const Vec3 initial = normalized(frame.forward,{0,0,1});
    const Vec3 previous = state.pose.valid ? state.pose.forward : initial;
    direction = normalized({previous.x+initial.x*blend+direction.x*(1-blend),
                            previous.y+initial.y*blend+direction.y*(1-blend),
                            previous.z+initial.z*blend+direction.z*(1-blend)},previous);
    const Vec3 old_up = state.pose.valid ? state.pose.up : frame.up;
    const Vec3 left = normalized(cross({old_up.x,old_up.y+1,old_up.z},direction),{1,0,0});
    const Vec3 up = normalized(cross(direction,left),{0,1,0});
    state.pose = {true,position,direction,up,((i+1)*2)%16,i};
    ++state.cursor;
}

controller_pak::Key storage_key() {
    controller_pak::Key key;
    key.company_code = 1;
    key.game_code = 0x4E575245; // NWRE; this host namespace is distinct from native NWRJ.
    key.game_name = {'W','R','6','4','H','O','S','T','G','H','O','S','T'};
    key.extension_name = {'G','H','0','1'};
    return key;
}
std::uint32_t checksum(std::span<const std::uint8_t> bytes) {
    std::uint32_t value = 2166136261u;
    for (auto byte : bytes) value = (value ^ byte)*16777619u;
    return value;
}
std::uint32_t read32(std::span<const std::uint8_t> bytes, std::size_t at) {
    return (std::uint32_t(bytes[at])<<24)|(std::uint32_t(bytes[at+1])<<16)|
        (std::uint32_t(bytes[at+2])<<8)|bytes[at+3];
}
std::uint16_t read16(std::span<const std::uint8_t> bytes, std::size_t at) {
    return std::uint16_t((std::uint16_t(bytes[at])<<8)|bytes[at+1]);
}
void write32(std::span<std::uint8_t> bytes, std::size_t at, std::uint32_t value) {
    for (int i=3;i>=0;--i) { bytes[at+i]=std::uint8_t(value); value>>=8; }
}
void write16(std::span<std::uint8_t> bytes, std::size_t at, std::uint16_t value) {
    bytes[at]=std::uint8_t(value>>8); bytes[at+1]=std::uint8_t(value);
}
std::vector<std::uint8_t> encode(const std::array<Run,2>& runs) {
    std::vector<std::uint8_t> output(kFileBytes);
    std::copy(kMagic.begin(),kMagic.end(),output.begin());
    write32(output,8,1);
    write32(output,16,kSampleMilliseconds);
    write32(output,20,kSlotBytes);
    write32(output,24,kMaxSamples);
    for (std::size_t i=0;i<2;++i) {
        const Run& run=runs[i];
        if (!run.complete()) continue;
        auto slot=std::span(output).subspan(kMetadataBytes+i*kSlotBytes,kSlotBytes);
        slot[0]=std::uint8_t(run.course.index);
        slot[1]=std::uint8_t(run.course.difficulty);
        slot[2]=run.course.reverse ? 1 : 0;
        slot[3]=1;
        write16(slot,4,std::uint16_t(run.goal_samples));
        write16(slot,6,std::uint16_t(run.points.size()));
        write32(slot,8,run.finish_ms);
        for (std::size_t n=0;n<run.points.size();++n) {
            const Point p=run.points[n];
            write16(slot,kSlotHeaderBytes+6*n,std::uint16_t(p.x));
            write16(slot,kSlotHeaderBytes+6*n+2,std::uint16_t(p.y));
            write16(slot,kSlotHeaderBytes+6*n+4,std::uint16_t(p.z));
        }
        write32(slot,12,checksum(slot.subspan(kSlotHeaderBytes)));
    }
    write32(output,12,checksum(std::span(output).subspan(16)));
    return output;
}
bool decode(std::span<const std::uint8_t> bytes, std::array<Run,2>& output) {
    if (bytes.size()!=kFileBytes || !std::equal(kMagic.begin(),kMagic.end(),bytes.begin()) ||
        read32(bytes,8)!=1 || read32(bytes,12)!=checksum(bytes.subspan(16)) ||
        read32(bytes,16)!=kSampleMilliseconds || read32(bytes,20)!=kSlotBytes ||
        read32(bytes,24)!=kMaxSamples) return false;
    std::array<Run,2> decoded;
    for (std::size_t i=0;i<2;++i) {
        auto slot=bytes.subspan(kMetadataBytes+i*kSlotBytes,kSlotBytes);
        if (slot[3]==0) continue;
        if (slot[3]!=1 || slot[2]>1) return false;
        Run& run=decoded[i];
        run.course={slot[0],slot[1],slot[2]!=0};
        run.goal_samples=read16(slot,4);
        const auto count=read16(slot,6);
        run.finish_ms=read32(slot,8);
        if (!valid_course(run.course) || count>kMaxSamples ||
            read32(slot,12)!=checksum(slot.subspan(kSlotHeaderBytes))) return false;
        run.points.reserve(count);
        for (std::size_t n=0;n<count;++n) {
            // Explicit sign extension avoids implementation-defined unsigned casts.
            auto coordinate=[&](std::size_t at) {
                const auto value=read16(slot,at);
                return std::int16_t(value < 32768 ? int(value) : int(value)-65536);
            };
            run.points.push_back({coordinate(kSlotHeaderBytes+6*n),
                coordinate(kSlotHeaderBytes+6*n+2),coordinate(kSlotHeaderBytes+6*n+4)});
        }
        if (!run.complete()) return false;
    }
    output=std::move(decoded);
    return true;
}

std::filesystem::path automatic_path(Course course) {
    return automatic.directory / ("course-" + std::to_string(course.index) +
        "-difficulty-" + std::to_string(course.difficulty) + "-reverse-" +
        (course.reverse ? "1" : "0") + ".bin");
}
Result read_automatic_file(const std::filesystem::path& path, Course course, Run& run) {
    std::error_code ec;
    if (!std::filesystem::exists(path, ec)) return ec ? Result::StorageFailure : Result::NoGhost;
    if (std::filesystem::file_size(path, ec) != kFileBytes)
        return ec ? Result::StorageFailure : Result::CorruptData;
    std::ifstream input(path, std::ios::binary);
    std::vector<std::uint8_t> bytes(kFileBytes);
    if (!input.read(reinterpret_cast<char*>(bytes.data()), bytes.size())) return Result::StorageFailure;
    std::array<Run, 2> runs;
    if (!decode(bytes, runs) || !runs[0].complete() || runs[0].course != course || runs[1].complete())
        return Result::CorruptData;
    run = std::move(runs[0]);
    return Result::Ok;
}
AutomaticEntry& automatic_entry(Course course) {
    auto& entry = automatic.entries[(course.index * 3 + course.difficulty) * 2 + int(course.reverse)];
    if (!entry.loaded) {
        entry.loaded = true;
        Run saved;
        const auto path = automatic_path(course);
        const auto primary = read_automatic_file(path, course, saved);
        auto result = primary;
        if (primary != Result::Ok) {
            auto backup = path; backup += ".bak";
            const auto fallback = read_automatic_file(backup, course, saved);
            if (fallback == Result::Ok) {
                result = Result::Ok;
                WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[ghost:autosave] recovered backup for course=%d difficulty=%d reverse=%d\n",
                    course.index, course.difficulty, course.reverse));
            } else if (primary == Result::NoGhost) result = fallback;
        }
        entry.load_result = result == Result::NoGhost ? Result::Ok : result;
        if (saved.complete() && (!entry.best.complete() || saved.finish_ms <= entry.best.finish_ms)) {
            entry.best = std::move(saved);
            entry.dirty = false;
        }
        automatic.last = entry.load_result;
        if (automatic.last != Result::Ok)
            std::fprintf(stderr, "[ghost:autosave] unable to load course=%d difficulty=%d reverse=%d result=%d; existing files preserved\n",
                course.index, course.difficulty, course.reverse, int(automatic.last));
    }
    return entry;
}
void save_automatic(AutomaticEntry& entry) {
    if (!entry.dirty || !entry.best.complete() || automatic.directory.empty()) return;
    if (entry.load_result == Result::StorageFailure) {
        // Retry transient path/I/O failures only at a finish or lifecycle
        // boundary. Never retry (or write) from every post-goal sample.
        entry.loaded = false;
        automatic_entry(entry.best.course);
        if (!entry.dirty) {
            // Recovery may reveal an equal/faster disk ghost after this race
            // already qualified as a candidate. Its later tail must not replace
            // that recovered record either.
            if (state.recording.course == entry.best.course) {
                state.best = entry.best;
                state.candidate = false;
            }
            return;
        }
    }
    // Never replace an unreadable/corrupt archive with a new, possibly slower
    // run. A failed write keeps the completed in-memory best available on retry.
    if (entry.load_result != Result::Ok) {
        automatic.last = entry.load_result;
        return;
    }
    const auto course = entry.best.course;
    const auto path = automatic_path(course);
    auto temporary = path; temporary += ".temp";
    auto backup = path; backup += ".bak";
    const auto write = [&]() {
        std::error_code ec;
        std::filesystem::create_directories(automatic.directory, ec);
        if (ec) return false;
        const auto bytes = encode({entry.best, Run{}});
        std::ofstream output(temporary, std::ios::binary | std::ios::trunc);
        output.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
        output.flush();
        if (!output.good()) return false;
        output.close();
        if (!output.good()) return false;
        Run primary;
        const auto existing = read_automatic_file(path, course, primary);
        if (existing == Result::StorageFailure) return false;
        if (existing == Result::Ok) {
            // Do not copy a damaged primary over a successfully recovered backup.
            std::filesystem::copy_file(path, backup, std::filesystem::copy_options::overwrite_existing, ec);
            if (ec) return false;
        }
#ifdef _WIN32
        return MoveFileExW(temporary.c_str(), path.c_str(),
            MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH) != 0;
#else
        std::filesystem::rename(temporary, path, ec);
        return !ec;
#endif
    };
    if (write()) {
        entry.dirty = false;
        entry.save_result = Result::Ok;
        automatic.last = Result::Ok;
        WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[ghost:autosave] saved course=%d difficulty=%d reverse=%d time_ms=%u samples=%zu\n",
            course.index, course.difficulty, course.reverse, entry.best.finish_ms, entry.best.points.size()));
    } else {
        entry.save_result = Result::StorageFailure;
        automatic.last = Result::StorageFailure;
        std::fprintf(stderr, "[ghost:autosave] write failed for course=%d difficulty=%d reverse=%d; best retained in memory\n",
            course.index, course.difficulty, course.reverse);
    }
}
void flush_automatic() {
    for (auto& entry : automatic.entries) save_automatic(entry);
}
Result read_slots(std::array<Run,2>& runs, int& file) {
    auto& store=Store::instance();
    auto result=store.find_file(0,storage_key(),file);
    if (result==controller_pak::Result::Invalid) return Result::NoGhost;
    if (result!=controller_pak::Result::Ok) return Result::StorageFailure;
    controller_pak::FileState file_state;
    if (store.file_state(0,file,file_state)!=controller_pak::Result::Ok)
        return Result::StorageFailure;
    if (file_state.file_size!=kFileBytes) return Result::CorruptData;
    std::vector<std::uint8_t> bytes(kFileBytes);
    if (store.read_file(0,file,0,bytes)!=controller_pak::Result::Ok)
        return Result::StorageFailure;
    return decode(bytes,runs) ? Result::Ok : Result::CorruptData;
}
Result write_slots(const std::array<Run,2>& runs, int file) {
    auto& store=Store::instance();
    const bool created=file<0;
    if (file<0 && store.allocate_file(0,storage_key(),kFileBytes,file)!=controller_pak::Result::Ok)
        return Result::StorageFailure;
    const auto bytes=encode(runs);
    // One Store transaction includes metadata and both slots. The reused host
    // Store writes via its existing backup/finalize path.
    if (store.write_file(0,file,0,bytes)!=controller_pak::Result::Ok) {
        // Store preserves each individual operation. Undo only a new empty
        // allocation made by this call; never delete an existing ghost file.
        if(created)store.delete_file(0,storage_key());
        return Result::StorageFailure;
    }
    for (std::size_t i=0;i<2;++i) state.slots[i]=info(runs[i]);
    return Result::Ok;
}
} // namespace

void begin_run(Course course) { std::lock_guard lock(mutex); start(course); }
Result initialize_storage(const std::filesystem::path& save_base) {
    std::lock_guard lock(mutex);
    // An empty/relative pre-initialization path must never create a CWD save.
    if (save_base.empty() || !save_base.is_absolute() || save_base.filename().empty())
        return automatic.last = Result::StorageFailure;
    auto directory = save_base.lexically_normal();
    directory.replace_extension(); directory += ".ghosts";
    if (directory == automatic.directory) return automatic.last;
    flush_automatic();
    automatic = {};
    automatic.directory = std::move(directory);
    // A genuine profile switch must not carry another profile's ghost into it.
    state.best = state.playback = state.selected = {};
    state.active = state.capturing = false;
    state.pose = {};
    return Result::Ok;
}
void observe(const Frame& frame) {
    std::lock_guard lock(mutex);
    if (!frame.eligible || !valid_course(frame.course)) {
        if (state.active) flush_automatic();
        state.active=state.capturing=false;
        state.pose.valid=false;
        return;
    }
    if (!state.active || state.recording.course!=frame.course) start(frame.course);
    if (frame.toggle_visibility && state.playback.complete()) state.visible=!state.visible;
    if (frame.paused) return;
    advance_playback(frame); // Hiding the ghost does not stop its timeline.
    if (frame.retired && !state.finished) state.capturing=false;
    if (!state.capturing) return;
    const bool just_finished = frame.finished && !state.finished;
    if (just_finished) {
        state.finished=true;
        state.recording.goal_samples=static_cast<std::uint32_t>(state.recording.points.size());
        state.recording.finish_ms=frame.elapsed_ms;
        const Run& best = automatic.directory.empty() ? state.best : automatic_entry(frame.course).best;
        state.candidate=!state.invalid && !state.full &&
            state.recording.goal_samples>0 && state.recording.goal_samples<kMaxSamples &&
            (!best.complete() || best.course!=frame.course || frame.elapsed_ms<best.finish_ms);
    }
    if (state.recording.points.size()<kMaxSamples) {
        const float slide=std::max(0.0f,100.0f-float(state.recording.points.size()));
        Point point{};
        if (!quantize(frame.position.x+frame.left.x*slide,point.x) ||
            !quantize(frame.position.y,point.y) ||
            !quantize(frame.position.z+frame.left.z*slide,point.z)) {
            state.invalid=true;
            state.capturing=state.candidate=false;
            return;
        }
        state.recording.points.push_back(point);
        if (state.recording.points.size()==kMaxSamples) state.full=true;
    }
    else state.full=true;
    if (state.candidate && state.recording.complete()) {
        state.best=state.recording;
        if (just_finished && state.selected.course == frame.course) state.selected = {};
        if (!automatic.directory.empty()) {
            auto& entry = automatic_entry(frame.course);
            if (entry.best.points.size() != state.recording.points.size() ||
                entry.best.finish_ms != state.recording.finish_ms) {
                entry.best = state.recording;
                entry.dirty = true;
            }
            // Save the finish immediately, even if the process closes before
            // Retry. Post-goal animation tail is flushed at lifecycle boundaries.
            if (just_finished) save_automatic(entry);
        }
    }
}
void end_run() {
    std::lock_guard lock(mutex);
    flush_automatic();
    state.active=state.capturing=false;
    state.pose.valid=false;
}
void set_visible(bool value) { std::lock_guard lock(mutex); state.visible=value; }
void set_dolphin_resident(bool value) { std::lock_guard lock(mutex); state.resident=value; }
Status status() {
    std::lock_guard lock(mutex);
    Status result;
    result.visible=state.visible;
    result.recording=state.capturing && !state.full;
    result.recording_full=state.full;
    result.recording_invalid=state.invalid;
    result.can_save=state.best.complete();
    result.playback_active=state.pose.valid;
    result.dolphin_resident=state.resident;
    result.recorded_samples=static_cast<std::uint32_t>(state.recording.points.size());
    result.best=info(state.best);
    result.slots=state.slots;
    result.last_result=state.last;
    result.autosave_ready = !automatic.directory.empty();
    result.autosave_result = automatic.last;
    result.autosave_pending = std::any_of(automatic.entries.begin(), automatic.entries.end(),
        [](const AutomaticEntry& entry) { return entry.dirty; });
    for (const auto& entry : automatic.entries) {
        if (entry.load_result != Result::Ok) result.autosave_result = entry.load_result;
        else if (entry.save_result != Result::Ok) result.autosave_result = entry.save_result;
    }
    return result;
}
RenderPose render_pose() {
    std::lock_guard lock(mutex);
    RenderPose result=state.pose;
    result.valid=result.valid && state.visible;
    return result;
}
Result refresh_slots() {
    std::lock_guard lock(mutex);
    std::array<Run,2> runs;
    int file=-1;
    auto result=read_slots(runs,file);
    state.slots={};
    if (result==Result::Ok) for (std::size_t i=0;i<2;++i) state.slots[i]=info(runs[i]);
    return state.last=result==Result::NoGhost ? Result::Ok : result;
}
Result save_slot(int slot, bool overwrite_better) {
    std::lock_guard lock(mutex);
    if (slot<0 || slot>=2) return state.last=Result::InvalidSlot;
    if (!state.best.complete()) return state.last=Result::NoGhost;
    std::array<Run,2> runs;
    int file=-1;
    const auto result=read_slots(runs,file);
    if (result!=Result::Ok && result!=Result::NoGhost) return state.last=result;
    if (!overwrite_better && runs[slot].complete() && runs[slot].course==state.best.course &&
        runs[slot].finish_ms<=state.best.finish_ms) return state.last=Result::WouldOverwriteBetter;
    runs[slot]=state.best;
    return state.last=write_slots(runs,file);
}
Result load_slot(int slot) {
    std::lock_guard lock(mutex);
    if (slot<0 || slot>=2) return state.last=Result::InvalidSlot;
    std::array<Run,2> runs;
    int file=-1;
    const auto result=read_slots(runs,file);
    if (result!=Result::Ok) return state.last=result;
    if (!runs[slot].complete()) return state.last=Result::NoGhost;
    state.best=runs[slot];
    state.selected=runs[slot];
    for (std::size_t i=0;i<2;++i) state.slots[i]=info(runs[i]);
    return state.last=Result::Ok;
}
Result clear_slot(int slot) {
    std::lock_guard lock(mutex);
    if (slot<0 || slot>=2) return state.last=Result::InvalidSlot;
    std::array<Run,2> runs;
    int file=-1;
    const auto result=read_slots(runs,file);
    if (result!=Result::Ok) return state.last=result;
    runs[slot]={};
    return state.last=write_slots(runs,file);
}
const char* result_message(Result result) {
    switch(result) {
    case Result::Ok: return "Ready";
    case Result::NoGhost: return "No completed ghost is available";
    case Result::InvalidSlot: return "Choose ghost slot 1 or 2";
    case Result::CorruptData: return "Ghost data is invalid or from an incompatible version";
    case Result::StorageFailure: return "Controller Pak storage could not complete the operation";
    case Result::WouldOverwriteBetter: return "This slot already contains an equal or faster ghost";
    }
    return "Unknown ghost result";
}
void reset_session() {
    std::lock_guard lock(mutex);
    flush_automatic();
    automatic = {};
    const bool visible=state.visible;
    state={};
    state.visible=visible;
}
} // namespace wr64::ghost
