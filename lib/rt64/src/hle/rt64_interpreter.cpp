//
// RT64
//

#include "../../../../include/wr64_diagnostic_policy.h"

#include "rt64_interpreter.h"
#include "wr64_forensic.h"

#include <cassert>

//#define DUMP_DISPLAY_LISTS

namespace RT64 {
    static FILE *displayListFp = nullptr;

    static uint64_t wr64ForensicDisplayListAddress(
        const State *state, const DisplayList *dl)
    {
        if ((state == nullptr) || (state->RDRAM == nullptr) || (dl == nullptr)) {
            return 0;
        }

        const uintptr_t base = reinterpret_cast<uintptr_t>(state->RDRAM);
        const uintptr_t address = reinterpret_cast<uintptr_t>(dl);
        return (address >= base) ? uint64_t(address - base) : UINT64_MAX;
    }

    // Interpreter

    Interpreter::Interpreter() {
        state = nullptr;
        hleGBI = nullptr;
        extendedFunction = gbiManager.getExtendedFunction();
    }

    void Interpreter::setup(State *state) {
        this->state = state;
    }

    void Interpreter::loadUCodeGBI(uint32_t textAddress, uint32_t dataAddress, bool resetFromTask) {
        if (!resetFromTask) {
            state->flush();
        }

        const uint32_t AddressMask = 0xFFFFF8;
        const uint32_t maskedTextAddress = textAddress & AddressMask;
        const uint32_t maskedDataAddress = dataAddress & AddressMask;
        if ((UCode.textAddress != maskedTextAddress) || (UCode.dataAddress != maskedDataAddress)) {
            hleGBI = gbiManager.getGBIForUCode(state->RDRAM, maskedTextAddress, maskedDataAddress);
            if (hleGBI != nullptr) {
                state->rsp->setGBI(hleGBI);
            }

            UCode.textAddress = maskedTextAddress;
            UCode.dataAddress = maskedDataAddress;
        }

        if (hleGBI != nullptr) {
            GBIReset resetFunction = resetFromTask ? hleGBI->resetFromTask : hleGBI->resetFromLoad;
            if (resetFunction != nullptr) {
                resetFunction(state);
            }
        }
    }

    void Interpreter::processRDPLists(uint32_t dlStartAdddress, DisplayList *dlStart, DisplayList *dlEnd) {
        state->dlCpuProfiler.start();

        // Update the state with the current display list address.
        state->displayListAddress = dlStartAdddress;
        state->displayListCounter++;

        // Check RDRAM if required.
        state->checkRDRAM();

        GBI *rdpGBI = state->rdp->gbi;
        constexpr unsigned int opCodeMask = 0x3F;

        // Run the command interpreter.
        assert(rdpGBI != nullptr);
        DisplayList *dl = dlStart;
        uint8_t opCode;
        GBIFunction func;
        uint32_t cmdLength;
        size_t pendingCommandRemainingBytes = state->rdp->pendingCommandRemainingBytes;

        if (dlStart >= dlEnd) {
            state->dlCpuProfiler.end();
            return;
        }

        if (pendingCommandRemainingBytes != 0) {
            // Copy the remaining command bytes from the current displaylist
            uint32_t toCopy = (uint32_t)std::min(pendingCommandRemainingBytes, (uintptr_t)dlEnd - (uintptr_t)dl);
            memcpy(state->rdp->pendingCommandBuffer.data() + state->rdp->pendingCommandCurrentBytes, dl, toCopy);

            // Modify start to skip the copied bytes
            dl = (DisplayList *)(toCopy + (uintptr_t)dl);

            // Check if we've copied all of the bytes of the command into the buffer
            if (pendingCommandRemainingBytes == toCopy) {
                // All bytes have been copied, so run the completed command
                DisplayList *pendingCommand = (DisplayList *)state->rdp->pendingCommandBuffer.data();
                opCode = (pendingCommand->w0 >> 24) & opCodeMask;
                func = rdpGBI->map[opCode];

                if (func != nullptr) {
                    func(state, &pendingCommand);
                }
                else {
                    RT64_LOG_PRINTF("DL Parser ran into an unknown RDP opCode: %u / 0x%X", opCode, opCode);
                }

                state->rdp->pendingCommandCurrentBytes = 0;
                state->rdp->pendingCommandRemainingBytes = 0;
            }
            // Not all of the bytes were copied, so adjust RDP state accordingly and exit.
            else {
                state->rdp->pendingCommandCurrentBytes += toCopy;
                state->rdp->pendingCommandRemainingBytes -= toCopy;
                state->dlCpuProfiler.end();
                return;
            }
        }

        // Create a dummy pointer and pass that, since displaylist pointer incrementing is handled differently in LLE.
        DisplayList *dummy;
        while ((dl != nullptr) && ((dlEnd == nullptr) || (dl < dlEnd))) {
            opCode = (dl->w0 >> 24) & opCodeMask;
            const uint32_t forensicLength =
                ((extendedOpCode != 0) && (opCode == extendedOpCode))
                ? 1U : state->rdp->commandWordLengths[opCode];
            WR64_DIAGNOSTIC_LOG(wr64_forensic_record(WR64_FORENSIC_RDP_COMMAND,
                wr64ForensicDisplayListAddress(state, dl), dl->w0, dl->w1,
                opCode, forensicLength, state->displayListCounter,
                uint64_t(dlEnd != nullptr), 0););

            if ((extendedOpCode != 0) && (opCode == extendedOpCode)) {
                dummy = dl;
                extendedFunction(state, &dl);
                cmdLength = 1;
            }
            else {
                func = rdpGBI->map[opCode];
                cmdLength = state->rdp->commandWordLengths[opCode];

#       ifdef DUMP_DISPLAY_LISTS
                RT64_LOG_PRINTF("0x%08X 0x%08X", dl->w0, dl->w1);
#       endif

                // Check if this command is unfinished and store the partial contents if so.
                if (dl + cmdLength > dlEnd) {
                    uint32_t toCopy = (uint32_t)((uintptr_t)dlEnd - (uintptr_t)dl);
                    memcpy(state->rdp->pendingCommandBuffer.data(), dl, toCopy);
                    state->rdp->pendingCommandCurrentBytes = toCopy;
                    state->rdp->pendingCommandRemainingBytes = cmdLength * sizeof(DisplayList) - toCopy;
                    break;
                }

                if (func != nullptr) {
                    dummy = dl;
                    func(state, &dummy);
                }
                else {
                    RT64_LOG_PRINTF("DL Parser ran into an unknown RDP opCode: %u / 0x%X", opCode, opCode);
                }
            }

            if (dl != nullptr) {
                dl += cmdLength;
            }
        }

        state->dlCpuProfiler.end();
    }

    void Interpreter::processDisplayLists(uint32_t dlStartAdddress, DisplayList *dlStart) {
        assert(hleGBI != nullptr);

        state->dlCpuProfiler.start();

        // Update the state with the current display list address.
        state->displayListAddress = dlStartAdddress;
        state->displayListCounter++;

        // Check RDRAM if required.
        state->checkRDRAM();

        // Run the command interpreter.
        DisplayList *dl = dlStart;
        uint8_t opCode;
        GBIFunction func;
        while (dl != nullptr) {
            opCode = (dl->w0 >> 24);
            state->wr64DolphinSunCurrent = opCode == 0xe4 ? wr64DolphinSunLookup(
                state->wr64CurrentTaskSequence,
                uint32_t(wr64ForensicDisplayListAddress(state, dl)), state->RDRAM) : Wr64DolphinSunSprite{};
            state->wr64HudCurrent = (opCode == 0xe4 || opCode == 0xf6 ||
                dl->w0 == 0x64000002u || dl->w0 == 0x64000003u) ? wr64HudLookup(
                state->wr64CurrentTaskSequence,
                uint32_t(wr64ForensicDisplayListAddress(state, dl)), state->RDRAM) : Wr64HudMotion{};
            WR64_DIAGNOSTIC_LOG(wr64_forensic_record(WR64_FORENSIC_RSP_COMMAND,
                wr64ForensicDisplayListAddress(state, dl), dl->w0, dl->w1,
                opCode, state->displayListCounter, uint32_t(hleGBI->ucode),
                uint64_t((extendedOpCode != 0) && (opCode == extendedOpCode)), 0););

            if ((extendedOpCode != 0) && (opCode == extendedOpCode)) {
                extendedFunction(state, &dl);
            }
            else {
                func = hleGBI->map[opCode];

#       ifdef DUMP_DISPLAY_LISTS
                RT64_LOG_PRINTF("0x%08X 0x%08X", dl->w0, dl->w1);
#       endif

                if (func != nullptr) {
                    func(state, &dl);
                }
                else {
                    RT64_LOG_PRINTF("DL Parser ran into an unknown opCode (GBI %u): %u / 0x%X", uint32_t(hleGBI->ucode), opCode, opCode);
                }
            }

            if (dl != nullptr) {
                dl++;
            }
        }

        state->dlCpuProfiler.end();
    }
};
