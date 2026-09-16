#pragma once

#include <cstdint>
#include <vector>

namespace wr64::rom_patch {

// The game this project recompiles is the WIDESCREEN ROM, not the cartridge
// image: the recompiled C in RecompiledFuncsPoint0 was generated from a Wave
// Race 64 (USA, Rev 1) image with the "wr64ws robust" widescreen patch already
// applied, and the renderer's whole 424-pixel-wide geometry follows from it.
//
// Asking a player to patch their own ROM before they can start is a step that
// can only go wrong, so the patch travels inside the executable and is applied
// here, in memory, at the moment a ROM is selected. A player supplies the
// ordinary cartridge image they own; nothing is written back to it.
//
// Returns true when the buffer WAS the unpatched cartridge image and now holds
// the patched one. Returns false and leaves the buffer untouched for anything
// else - including a ROM that is already patched, which needs no help and is
// recognised by the caller's own hash check.
bool apply_if_unpatched(std::vector<uint8_t> &rom);

}  // namespace wr64::rom_patch
