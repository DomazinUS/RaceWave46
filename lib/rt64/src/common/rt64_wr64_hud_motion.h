#pragma once

#include <array>
#include <cstdint>
#include <cstring>
#include <mutex>
#include <vector>

namespace RT64 {
// Native draw-producer identity, copied at emission time. Texture hashes are
// deliberately absent: scrolling message strips are rebaked as they are cut.
struct Wr64HudMotion {
    uint64_t generation = 0;
    uint32_t kind = 0; // 1: park instruction unit, 2: Stunt award, 3: ending panel.
    uint32_t slot = 0, part = 0, content = 0, age = 0, context = 0;
    int32_t x = 0, y = 0;
};
struct Wr64HudCommand {
    uint32_t address = 0;
    uint32_t wordCount = 6;
    std::array<uint32_t, 6> words{};
    Wr64HudMotion motion{};
};
struct Wr64HudBatch {
    uint64_t sequence = 0;
    std::vector<Wr64HudCommand> commands;
};
inline std::mutex wr64HudMutex;
inline std::vector<Wr64HudCommand> wr64HudPending;
inline std::array<uint64_t, 6> wr64HudGenerations{};
inline uint64_t wr64HudNextGeneration = 0;
inline thread_local Wr64HudBatch wr64HudClaimed;
constexpr size_t Wr64HudMaxCommands = 256;

inline uint32_t wr64HudReadWord(const uint8_t *ram, uint32_t address) {
    uint32_t value;
    std::memcpy(&value, ram + (address & 0x1fffffffu), sizeof(value));
    return value;
}
inline void wr64HudSpawn(uint32_t slot) {
    if (slot >= wr64HudGenerations.size()) return;
    std::lock_guard<std::mutex> lock(wr64HudMutex);
    wr64HudGenerations[slot] = ++wr64HudNextGeneration;
}
// Read only the exact contiguous packet emitted by a known native producer.
// The bounded scan accepts complete F3DEX texrect/B3/B2 triples, with their
// full words retained to reject overwritten display-list storage at decode.
inline void wr64HudRecord(const uint8_t *ram, uint32_t begin, uint32_t end,
    Wr64HudMotion motion, uint32_t generationSlot)
{
    begin &= 0x1fffffffu; end &= 0x1fffffffu;
    if (!ram || generationSlot >= wr64HudGenerations.size() || (begin & 7) || (end & 7) ||
        end <= begin || end > 0x800000u || end - begin > 0x4000u) return;
    std::lock_guard<std::mutex> lock(wr64HudMutex);
    motion.generation = wr64HudGenerations[generationSlot];
    if (!motion.generation) return;
    uint32_t part = 0;
    for (uint32_t p = begin; p + 8 <= end; p += 8) {
        const bool native = p + 24 <= end && (wr64HudReadWord(ram, p) >> 24) == 0xe4 &&
            wr64HudReadWord(ram, p + 8) == 0xb3000000u &&
            wr64HudReadWord(ram, p + 16) == 0xb2000000u;
        // Existing ultrawide menu promotion replaces the same 24-byte packet
        // with signed coordinates and explicit no-origin alignment.
        const bool promoted = p + 24 <= end && wr64HudReadWord(ram, p) == 0x64000002u &&
            wr64HudReadWord(ram, p + 4) == 0x04004000u;
        // The ending ranking panel also contains native solid icon backdrops.
        // They travel with its frame and labels, including signed wide packets.
        const bool fill = motion.kind == 3 && (wr64HudReadWord(ram, p) >> 24) == 0xf6;
        const bool promotedFill = motion.kind == 3 && p + 16 <= end &&
            wr64HudReadWord(ram, p) == 0x64000003u && wr64HudReadWord(ram, p + 4) == 0x00800800u;
        if (!native && !promoted && !fill && !promotedFill) continue;
        if (wr64HudPending.size() >= Wr64HudMaxCommands) {
            // Refuse this packet rather than publishing a partly identified
            // animation. An overflow never changes native rendering.
            wr64HudPending.clear();
            return;
        }
        Wr64HudCommand command;
        command.address = p;
        command.wordCount = fill ? 2 : promotedFill ? 4 : 6;
        for (uint32_t i = 0; i < command.wordCount; ++i) command.words[i] = wr64HudReadWord(ram, p + i * 4);
        command.motion = motion;
        command.motion.part = part++;
        wr64HudPending.push_back(command);
        p += command.wordCount * 4 - 8;
    }
}
inline Wr64HudBatch wr64HudSeal(uint64_t sequence) {
    std::lock_guard<std::mutex> lock(wr64HudMutex);
    Wr64HudBatch batch;
    batch.sequence = sequence;
    batch.commands.swap(wr64HudPending);
    return batch;
}
inline Wr64HudMotion wr64HudLookup(uint64_t sequence, uint32_t address,
    const uint8_t *ram)
{
    if (!sequence || sequence != wr64HudClaimed.sequence || !ram ||
        !address || address > 0x800000u - 8) return {};
    for (const auto &command : wr64HudClaimed.commands) {
        if (command.address != address) continue;
        if (command.wordCount < 2 || command.wordCount > 6 ||
            address > 0x800000u - command.wordCount * 4) return {};
        for (uint32_t i = 0; i < command.wordCount; ++i)
            if (command.words[i] != wr64HudReadWord(ram, address + i * 4)) return {};
        return command.motion;
    }
    return {};
}
inline bool wr64HudContinuous(const Wr64HudMotion &previous, const Wr64HudMotion &current) {
    if (!current.generation || previous.generation != current.generation ||
        previous.kind != current.kind || previous.slot != current.slot ||
        (current.kind != 3 && previous.part != current.part) || previous.content != current.content ||
        previous.context != current.context) return false;
    const int64_t dx = int64_t(current.x) - previous.x;
    const int64_t dy = int64_t(current.y) - previous.y;
    if (current.kind == 1) return (dx == 0 || dx == -2) && dy == 0;
    if (current.kind == 2) return current.age == previous.age + 1 &&
        current.age < 23 && dx >= -10 && dx <= 0 && dy >= -10 && dy <= 8;
    // Clipping changes emitted ordinals. The ending matcher uses the native
    // row's shared translation so newly entering pieces move with the panel.
    if (current.kind == 3) return dx == 0 && (dy == -2 || dy == 0);
    return false;
}
} // namespace RT64
