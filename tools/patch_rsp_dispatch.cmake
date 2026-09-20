if(NOT DEFINED INPUT OR NOT DEFINED OUTPUT)
    message(FATAL_ERROR "INPUT and OUTPUT are required")
endif()

file(READ "${INPUT}" source)

set(needle [=[    // add         $2, $zero, $1
    r2 = RSP_ADD32(0, r1);
    // lh          $2, 0x10($2)
    r2 = RSP_MEM_H_LOAD(0X10, r2);
]=])

set(replacement [=[    // The ABI command table at DMEM 0x10 is immutable, but later audio
    // operations can alias that region in this recompilation. Dispatch directly
    // from the command index to prevent corrupted, unaligned jump targets.
    static constexpr uint16_t dispatch_targets[16] = {
        0x1118, 0x1470, 0x11DC, 0x1B38,
        0x1214, 0x187C, 0x1254, 0x12D0,
        0x12EC, 0x1328, 0x140C, 0x1294,
        0x1E24, 0x138C, 0x170C, 0x144C,
    };
    r2 = dispatch_targets[(r1 >> 1) & 0xF];
]=])

string(REPLACE "${needle}" "${replacement}" patched "${source}")
if(patched STREQUAL source)
    message(FATAL_ERROR "aspMain dispatch block was not found")
endif()

file(WRITE "${OUTPUT}" "${patched}")
