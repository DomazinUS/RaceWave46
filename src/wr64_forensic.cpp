#define WR64_FORENSIC_IMPLEMENTATION
#include "wr64_forensic.h"

#if WR64_ENABLE_DIAGNOSTICS

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <filesystem>
#include <functional>
#include <fstream>
#include <iomanip>
#include <memory>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

namespace {
constexpr uint32_t RecordMagic = 0x46523657U;
constexpr uint32_t RecordVersion = 1;
constexpr size_t BlobBytes = 128;
constexpr size_t DefaultMegabytes = 512;
constexpr size_t MinimumMegabytes = 16;
constexpr size_t MaximumMegabytes = 2048;
constexpr size_t RdramDefaultBytes = 8 * 1024 * 1024;

struct Timeline {
    uint64_t nativeFrame;
    uint64_t taskSequence;
    uint64_t submissionFrame;
    uint64_t workloadId;
    uint64_t presentId;
    uint64_t outputId;
};

struct RecordData {
    uint32_t magic = RecordMagic;
    uint32_t version = RecordVersion;
    uint64_t sequence = 0;
    uint64_t timestampNs = 0;
    uint32_t threadId = 0;
    uint32_t type = 0;
    Timeline timeline{};
    std::array<uint64_t, 8> args{};
    uint64_t blobTag = 0;
    uint32_t blobSize = 0;
    uint32_t reserved = 0;
    std::array<uint8_t, BlobBytes> blob{};
};

struct Slot {
    std::atomic<uint64_t> committed{UINT64_MAX};
    RecordData data{};
};

struct Recorder {
    std::unique_ptr<Slot[]> slots;
    size_t capacity = 0;
    std::atomic<uint64_t> cursor{0};
    std::atomic<uint32_t> activeWriters{0};
    std::atomic<bool> initialized{false};
    std::atomic<bool> frozen{false};
    std::atomic<bool> paused{false};
    std::atomic<bool> exporting{false};
    std::atomic<uint64_t> nativeFrame{0};
    std::atomic<uint64_t> taskSequence{0};
    std::atomic<uint64_t> submissionFrame{0};
    std::atomic<uint64_t> workloadId{0};
    std::atomic<uint64_t> presentId{0};
    std::atomic<uint64_t> outputId{0};
    std::atomic<uint8_t *> rdram{nullptr};
    std::atomic<size_t> rdramSize{0};
    std::mutex pauseMutex;
    std::condition_variable pauseCondition;
    std::mutex exportMutex;
    std::thread exportThread;
};

Recorder gRecorder;

uint64_t nowNs() {
    return uint64_t(std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count());
}

uint32_t currentThreadId() {
#if defined(_WIN32)
    return uint32_t(GetCurrentThreadId());
#else
    return uint32_t(std::hash<std::thread::id>{}(std::this_thread::get_id()));
#endif
}

size_t configuredMegabytes() {
    const char *value = std::getenv("WR64_FORENSIC_RING_MB");
    if ((value == nullptr) || (value[0] == '\0')) {
        return DefaultMegabytes;
    }

    char *end = nullptr;
    const unsigned long long parsed = std::strtoull(value, &end, 10);
    if ((end == value) || (*end != '\0')) {
        return DefaultMegabytes;
    }

    return std::clamp<size_t>(
        size_t(parsed), MinimumMegabytes, MaximumMegabytes);
}

Timeline loadTimeline() {
    return Timeline{
        gRecorder.nativeFrame.load(std::memory_order_relaxed),
        gRecorder.taskSequence.load(std::memory_order_relaxed),
        gRecorder.submissionFrame.load(std::memory_order_relaxed),
        gRecorder.workloadId.load(std::memory_order_relaxed),
        gRecorder.presentId.load(std::memory_order_relaxed),
        gRecorder.outputId.load(std::memory_order_relaxed)
    };
}

void writeRecord(RecordData record) {
    if (!gRecorder.initialized.load(std::memory_order_acquire) ||
        gRecorder.frozen.load(std::memory_order_acquire))
    {
        return;
    }

    gRecorder.activeWriters.fetch_add(1, std::memory_order_acq_rel);
    if (gRecorder.frozen.load(std::memory_order_acquire)) {
        gRecorder.activeWriters.fetch_sub(1, std::memory_order_acq_rel);
        return;
    }

    const uint64_t sequence =
        gRecorder.cursor.fetch_add(1, std::memory_order_acq_rel);
    Slot &slot = gRecorder.slots[sequence % gRecorder.capacity];
    slot.committed.store(UINT64_MAX, std::memory_order_release);
    record.sequence = sequence;
    record.timestampNs = nowNs();
    record.threadId = currentThreadId();
    record.timeline = loadTimeline();
    slot.data = record;
    slot.committed.store(sequence, std::memory_order_release);
    gRecorder.activeWriters.fetch_sub(1, std::memory_order_acq_rel);
}

std::string timestampName() {
    const auto systemNow = std::chrono::system_clock::now();
    const std::time_t raw = std::chrono::system_clock::to_time_t(systemNow);
    std::tm local{};
#if defined(_WIN32)
    localtime_s(&local, &raw);
#else
    localtime_r(&raw, &local);
#endif
    std::ostringstream stream;
    stream << std::put_time(&local, "%Y%m%d-%H%M%S");
    return stream.str();
}

std::filesystem::path captureRoot() {
    const char *configured = std::getenv("WR64_FORENSIC_OUTPUT");
    if ((configured != nullptr) && (configured[0] != '\0')) {
        return std::filesystem::path(configured);
    }

    return std::filesystem::current_path() / ".forensics";
}

const char *eventName(uint32_t type) {
    switch (type) {
    case WR64_FORENSIC_BOOT: return "boot";
    case WR64_FORENSIC_CONTROL: return "control";
    case WR64_FORENSIC_VI: return "vi";
    case WR64_FORENSIC_GFX_TASK: return "gfx_task";
    case WR64_FORENSIC_RSP_COMMAND: return "rsp_command";
    case WR64_FORENSIC_RDP_COMMAND: return "rdp_command";
    case WR64_FORENSIC_DRAW_CALL: return "draw_call";
    case WR64_FORENSIC_SKY_PRODUCER_BEGIN: return "sky_producer_begin";
    case WR64_FORENSIC_SKY_PRODUCER_END: return "sky_producer_end";
    case WR64_FORENSIC_SKY_MEMORY: return "sky_memory";
    case WR64_FORENSIC_RT64_SKY: return "rt64_sky";
    case WR64_FORENSIC_EXACT_SKY_CUT: return "exact_sky_cut";
    case WR64_FORENSIC_WORKLOAD: return "workload";
    case WR64_FORENSIC_PRESENT: return "present";
    case WR64_FORENSIC_NOTE: return "note";
    default: return "unknown";
    }
}

std::vector<RecordData> snapshotRecords() {
    while (gRecorder.activeWriters.load(std::memory_order_acquire) != 0) {
        std::this_thread::yield();
    }

    const uint64_t end = gRecorder.cursor.load(std::memory_order_acquire);
    const uint64_t begin =
        (end > gRecorder.capacity) ? (end - gRecorder.capacity) : 0;
    std::vector<RecordData> records;
    records.reserve(size_t(end - begin));
    for (uint64_t sequence = begin; sequence < end; sequence++) {
        const Slot &slot = gRecorder.slots[sequence % gRecorder.capacity];
        if (slot.committed.load(std::memory_order_acquire) == sequence) {
            records.push_back(slot.data);
        }
    }

    return records;
}

void exportCapture() {
    std::lock_guard exportLock(gRecorder.exportMutex);
    const std::vector<RecordData> records = snapshotRecords();
    const std::filesystem::path directory =
        captureRoot() / ("capture-" + timestampName());
    std::filesystem::create_directories(directory);

    {
        std::ofstream binary(directory / "events.bin",
            std::ios::binary | std::ios::trunc);
        const uint64_t count = records.size();
        binary.write(reinterpret_cast<const char *>(&count), sizeof(count));
        binary.write(reinterpret_cast<const char *>(records.data()),
            std::streamsize(records.size() * sizeof(RecordData)));
    }

    {
        std::ofstream csv(directory / "events.csv", std::ios::trunc);
        csv << "sequence,timestamp_ns,thread,type,event,native_frame,"
               "task_sequence,submission_frame,workload_id,present_id,"
               "output_id,a0,a1,a2,a3,a4,a5,a6,a7,blob_tag,blob_size\n";
        for (const RecordData &record : records) {
            csv << record.sequence << ',' << record.timestampNs << ','
                << record.threadId << ',' << record.type << ','
                << eventName(record.type) << ','
                << record.timeline.nativeFrame << ','
                << record.timeline.taskSequence << ','
                << record.timeline.submissionFrame << ','
                << record.timeline.workloadId << ','
                << record.timeline.presentId << ','
                << record.timeline.outputId;
            for (const uint64_t value : record.args) {
                csv << ',' << value;
            }
            csv << ',' << record.blobTag << ',' << record.blobSize << '\n';
        }
    }

    {
        std::ofstream blobs(directory / "blobs.bin",
            std::ios::binary | std::ios::trunc);
        for (const RecordData &record : records) {
            if (record.blobSize == 0) {
                continue;
            }
            blobs.write(reinterpret_cast<const char *>(&record.sequence),
                sizeof(record.sequence));
            blobs.write(reinterpret_cast<const char *>(&record.blobTag),
                sizeof(record.blobTag));
            blobs.write(reinterpret_cast<const char *>(&record.blobSize),
                sizeof(record.blobSize));
            blobs.write(reinterpret_cast<const char *>(record.blob.data()),
                record.blobSize);
        }
    }

    uint8_t *rdram = gRecorder.rdram.load(std::memory_order_acquire);
    size_t rdramSize = gRecorder.rdramSize.load(std::memory_order_acquire);
    if (rdram != nullptr) {
        rdramSize = std::min(rdramSize, RdramDefaultBytes);
        std::ofstream memory(directory / "rdram.bin",
            std::ios::binary | std::ios::trunc);
        memory.write(reinterpret_cast<const char *>(rdram),
            std::streamsize(rdramSize));
    }

    {
        std::ofstream manifest(directory / "manifest.txt", std::ios::trunc);
        manifest << "format=WR64 forensic observatory v1\n";
        manifest << "records=" << records.size() << '\n';
        manifest << "record_size=" << sizeof(RecordData) << '\n';
        manifest << "ring_capacity=" << gRecorder.capacity << '\n';
        manifest << "ring_bytes="
            << (gRecorder.capacity * sizeof(Slot)) << '\n';
        manifest << "paused="
            << gRecorder.paused.load(std::memory_order_acquire) << '\n';
        manifest << "native_frame="
            << gRecorder.nativeFrame.load(std::memory_order_acquire) << '\n';
        manifest << "task_sequence="
            << gRecorder.taskSequence.load(std::memory_order_acquire) << '\n';
        manifest << "submission_frame="
            << gRecorder.submissionFrame.load(std::memory_order_acquire) << '\n';
        manifest << "workload_id="
            << gRecorder.workloadId.load(std::memory_order_acquire) << '\n';
        manifest << "present_id="
            << gRecorder.presentId.load(std::memory_order_acquire) << '\n';
        manifest << "output_id="
            << gRecorder.outputId.load(std::memory_order_acquire) << '\n';
    }

    std::fprintf(stderr,
        "[forensic] capture exported: %s (%zu records)\n",
        directory.string().c_str(), records.size());
    gRecorder.exporting.store(false, std::memory_order_release);
}

void captureMemoryChunks(
    uint32_t eventType,
    uint64_t tagBase,
    const uint8_t *data,
    size_t size)
{
    if (data == nullptr) {
        return;
    }

    for (size_t offset = 0; offset < size; offset += BlobBytes) {
        RecordData record;
        record.type = eventType;
        record.blobTag = tagBase + offset;
        record.blobSize = uint32_t(std::min(BlobBytes, size - offset));
        std::memcpy(record.blob.data(), data + offset, record.blobSize);
        writeRecord(record);
    }
}

const uint8_t *rdramAddress(
    const uint8_t *rdram,
    size_t rdramSize,
    uint32_t address,
    size_t bytes)
{
    const size_t offset = size_t(address & 0x00FFFFFFU);
    if ((rdram == nullptr) || (offset > rdramSize) ||
        (bytes > (rdramSize - offset)))
    {
        return nullptr;
    }

    return rdram + offset;
}
}

extern "C" void wr64_forensic_initialize(void) {
    bool expected = false;
    if (!gRecorder.initialized.compare_exchange_strong(
            expected, true, std::memory_order_acq_rel))
    {
        return;
    }

    const size_t bytes = configuredMegabytes() * 1024ULL * 1024ULL;
    gRecorder.capacity = std::max<size_t>(1, bytes / sizeof(Slot));
    gRecorder.slots = std::make_unique<Slot[]>(gRecorder.capacity);
    std::fprintf(stderr,
        "[forensic] rolling recorder allocated: %zu MiB, %zu records\n",
        (gRecorder.capacity * sizeof(Slot)) / (1024 * 1024),
        gRecorder.capacity);
    wr64_forensic_record(WR64_FORENSIC_BOOT,
        gRecorder.capacity, sizeof(Slot), BlobBytes, 0, 0, 0, 0, 0);
}

extern "C" void wr64_forensic_shutdown(void) {
    if (gRecorder.exportThread.joinable()) {
        gRecorder.exportThread.join();
    }
    gRecorder.initialized.store(false, std::memory_order_release);
}

extern "C" int wr64_forensic_enabled(void) {
    return gRecorder.initialized.load(std::memory_order_acquire) ? 1 : 0;
}

extern "C" int wr64_forensic_is_paused(void) {
    return gRecorder.paused.load(std::memory_order_acquire) ? 1 : 0;
}

extern "C" int wr64_forensic_is_frozen(void) {
    return gRecorder.frozen.load(std::memory_order_acquire) ? 1 : 0;
}

extern "C" int wr64_forensic_export_in_progress(void) {
    return gRecorder.exporting.load(std::memory_order_acquire) ? 1 : 0;
}

extern "C" void wr64_forensic_set_rdram(uint8_t *rdram, size_t size) {
    gRecorder.rdram.store(rdram, std::memory_order_release);
    gRecorder.rdramSize.store(size, std::memory_order_release);
}

extern "C" void wr64_forensic_set_native_frame(uint64_t value) {
    gRecorder.nativeFrame.store(value, std::memory_order_release);
}

extern "C" void wr64_forensic_set_task(uint64_t value) {
    gRecorder.taskSequence.store(value, std::memory_order_release);
}

extern "C" void wr64_forensic_set_submission(uint64_t value) {
    gRecorder.submissionFrame.store(value, std::memory_order_release);
}

extern "C" void wr64_forensic_set_workload(uint64_t value) {
    gRecorder.workloadId.store(value, std::memory_order_release);
}

extern "C" void wr64_forensic_set_present(uint64_t value) {
    gRecorder.presentId.store(value, std::memory_order_release);
}

extern "C" void wr64_forensic_set_output(uint64_t value) {
    gRecorder.outputId.store(value, std::memory_order_release);
}

extern "C" void wr64_forensic_record(
    uint32_t type,
    uint64_t a0,
    uint64_t a1,
    uint64_t a2,
    uint64_t a3,
    uint64_t a4,
    uint64_t a5,
    uint64_t a6,
    uint64_t a7)
{
    RecordData record;
    record.type = type;
    record.args = { a0, a1, a2, a3, a4, a5, a6, a7 };
    writeRecord(record);
}

extern "C" void wr64_forensic_record_blob(
    uint32_t type,
    uint64_t tag,
    const void *data,
    size_t size)
{
    captureMemoryChunks(type, tag,
        reinterpret_cast<const uint8_t *>(data), size);
}

extern "C" void wr64_forensic_capture_sky(
    uint8_t *rdram,
    uint32_t phase,
    uint32_t a0,
    uint32_t outputAddress)
{
    const size_t rdramSize = gRecorder.rdramSize.load(std::memory_order_acquire);
    const uint8_t *selector =
        rdramAddress(rdram, rdramSize, 0x80223930U, 4);
    uint32_t selectorRaw = 0;
    if (selector != nullptr) {
        std::memcpy(&selectorRaw, selector, sizeof(selectorRaw));
    }

    wr64_forensic_record(
        phase == 0 ? WR64_FORENSIC_SKY_PRODUCER_BEGIN
                   : WR64_FORENSIC_SKY_PRODUCER_END,
        a0, outputAddress, selectorRaw, 0, 0, 0, 0, 0);

    const uint8_t *fan =
        rdramAddress(rdram, rdramSize, outputAddress, 7 * 16);
    captureMemoryChunks(WR64_FORENSIC_SKY_MEMORY,
        (uint64_t(phase) << 56) | uint64_t(outputAddress), fan, 7 * 16);

    const uint8_t *selectorRegion =
        rdramAddress(rdram, rdramSize, 0x80223920U, 0x30);
    captureMemoryChunks(WR64_FORENSIC_SKY_MEMORY,
        (uint64_t(phase) << 56) | 0x80223920ULL,
        selectorRegion, 0x30);

    const uint8_t *cameraRegion =
        rdramAddress(rdram, rdramSize, 0x80227C80U, 0x10C * 4);
    captureMemoryChunks(WR64_FORENSIC_SKY_MEMORY,
        (uint64_t(phase) << 56) | 0x80227C80ULL,
        cameraRegion, 0x10C * 4);

    const uint8_t *skyGlobals =
        rdramAddress(rdram, rdramSize, 0x800D4760U, 0x28);
    captureMemoryChunks(WR64_FORENSIC_SKY_MEMORY,
        (uint64_t(phase) << 56) | 0x800D4760ULL,
        skyGlobals, 0x28);
}

extern "C" void wr64_forensic_capture_rt64_sky(
    uint32_t stage,
    uint64_t submissionFrame,
    uint32_t transformIndex,
    uint32_t previousTransformIndex,
    const float *positions,
    const float *positionVelocities,
    const float *texcoords,
    const float *texcoordVelocities,
    uint32_t vertexCount,
    const float *viewMatrix,
    const float *projectionMatrix)
{
    wr64_forensic_set_submission(submissionFrame);
    wr64_forensic_record(WR64_FORENSIC_RT64_SKY,
        stage, transformIndex, previousTransformIndex, vertexCount,
        positions != nullptr, positionVelocities != nullptr,
        texcoords != nullptr, texcoordVelocities != nullptr);
    const uint64_t base =
        (uint64_t(stage) << 56) | (uint64_t(transformIndex) << 24);
    const size_t count = std::min<uint32_t>(vertexCount, 7);
    captureMemoryChunks(WR64_FORENSIC_RT64_SKY,
        base | 1, reinterpret_cast<const uint8_t *>(positions),
        positions != nullptr ? count * 3 * sizeof(float) : 0);
    captureMemoryChunks(WR64_FORENSIC_RT64_SKY,
        base | 2, reinterpret_cast<const uint8_t *>(positionVelocities),
        positionVelocities != nullptr ? count * 3 * sizeof(float) : 0);
    captureMemoryChunks(WR64_FORENSIC_RT64_SKY,
        base | 3, reinterpret_cast<const uint8_t *>(texcoords),
        texcoords != nullptr ? count * 2 * sizeof(float) : 0);
    captureMemoryChunks(WR64_FORENSIC_RT64_SKY,
        base | 4, reinterpret_cast<const uint8_t *>(texcoordVelocities),
        texcoordVelocities != nullptr ? count * 2 * sizeof(float) : 0);
    captureMemoryChunks(WR64_FORENSIC_RT64_SKY,
        base | 5, reinterpret_cast<const uint8_t *>(viewMatrix),
        viewMatrix != nullptr ? 16 * sizeof(float) : 0);
    captureMemoryChunks(WR64_FORENSIC_RT64_SKY,
        base | 6, reinterpret_cast<const uint8_t *>(projectionMatrix),
        projectionMatrix != nullptr ? 16 * sizeof(float) : 0);
}

extern "C" void wr64_forensic_freeze_pause_export(void) {
    if (!gRecorder.initialized.load(std::memory_order_acquire) ||
        gRecorder.frozen.exchange(true, std::memory_order_acq_rel))
    {
        return;
    }

    gRecorder.paused.store(true, std::memory_order_release);
    gRecorder.exporting.store(true, std::memory_order_release);
    std::fprintf(stderr,
        "[forensic] F8: recorder frozen; emulation pause requested\n");

    if (gRecorder.exportThread.joinable()) {
        gRecorder.exportThread.join();
    }
    gRecorder.exportThread = std::thread(exportCapture);
}

extern "C" void wr64_forensic_resume_reset(void) {
    if (gRecorder.exporting.load(std::memory_order_acquire)) {
        std::fprintf(stderr,
            "[forensic] F9 ignored: capture export still in progress\n");
        return;
    }

    if (gRecorder.exportThread.joinable()) {
        gRecorder.exportThread.join();
    }
gRecorder.cursor.store(0, std::memory_order_release);
    gRecorder.frozen.store(false, std::memory_order_release);
    gRecorder.paused.store(false, std::memory_order_release);
    wr64_forensic_record(WR64_FORENSIC_CONTROL,
        9, 0, 0, 0, 0, 0, 0, 0);
    gRecorder.pauseCondition.notify_all();
    std::fprintf(stderr,
        "[forensic] F9: recorder reset; emulation resumed\n");
}

extern "C" void wr64_forensic_force_resume(void) {
    {
        std::lock_guard lock(gRecorder.pauseMutex);
        gRecorder.paused.store(false, std::memory_order_release);
    }
    gRecorder.pauseCondition.notify_all();
}

extern "C" void wr64_forensic_wait_if_paused(void) {
    if (!gRecorder.paused.load(std::memory_order_acquire)) {
        return;
    }

    std::unique_lock lock(gRecorder.pauseMutex);
    gRecorder.pauseCondition.wait(lock, []() {
        return !gRecorder.paused.load(std::memory_order_acquire);
    });
}

#else

// A few runtime/generated units declare these C entry points directly instead
// of including the public header. Preserve that ABI without a recorder object,
// allocation, synchronization, RDRAM access, or diagnostic filesystem work.
extern "C" void wr64_forensic_initialize(void) {}
extern "C" void wr64_forensic_shutdown(void) {}
extern "C" int wr64_forensic_enabled(void) { return 0; }
extern "C" int wr64_forensic_is_paused(void) { return 0; }
extern "C" int wr64_forensic_is_frozen(void) { return 0; }
extern "C" int wr64_forensic_export_in_progress(void) { return 0; }
extern "C" void wr64_forensic_set_rdram(uint8_t *, size_t) {}
extern "C" void wr64_forensic_set_native_frame(uint64_t) {}
extern "C" void wr64_forensic_set_task(uint64_t) {}
extern "C" void wr64_forensic_set_submission(uint64_t) {}
extern "C" void wr64_forensic_set_workload(uint64_t) {}
extern "C" void wr64_forensic_set_present(uint64_t) {}
extern "C" void wr64_forensic_set_output(uint64_t) {}
extern "C" void wr64_forensic_record(uint32_t, uint64_t, uint64_t, uint64_t,
    uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) {}
extern "C" void wr64_forensic_record_blob(uint32_t, uint64_t, const void *, size_t) {}
extern "C" void wr64_forensic_capture_sky(uint8_t *, uint32_t, uint32_t, uint32_t) {}
extern "C" void wr64_forensic_capture_rt64_sky(uint32_t, uint64_t, uint32_t,
    uint32_t, const float *, const float *, const float *, const float *,
    uint32_t, const float *, const float *) {}
extern "C" void wr64_forensic_freeze_pause_export(void) {}
extern "C" void wr64_forensic_resume_reset(void) {}
extern "C" void wr64_forensic_force_resume(void) {}
extern "C" void wr64_forensic_wait_if_paused(void) {}

#endif
