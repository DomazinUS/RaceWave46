#pragma once

#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>

#include "common/rt64_plume.h"
#include "common/rt64_user_configuration.h"

namespace RT64 {
    struct Wr64LibrashaderAvailability {
        bool loaded = false;
        // Why the runtime is unavailable, or the loaded library's path.
        std::string message;
    };

    // Directory holding the game executable, with its assets and librashader beside it.
    std::filesystem::path wr64ProgramDirectory();

    // Loads librashader once, from the executable's directory first. Safe from any thread.
    const Wr64LibrashaderAvailability &wr64LibrashaderAvailability();

    // A filter chain and its intermediate input image for one presented output.
    // Use only on the present thread. Commands recorded by apply must complete
    // before release, prepare or destruction; the present queue waits for every
    // frame it submits.
    class Wr64LibrashaderOutput {
    public:
        Wr64LibrashaderOutput();
        ~Wr64LibrashaderOutput();

        // Follows the current selection. Compiles a changed preset through its own
        // command list on queue and waits for it. Returns false when this frame
        // should use the normal presentation path.
        bool prepare(RenderDevice *device, RenderCommandQueue *queue, UserConfiguration::GraphicsAPI api,
            uint32_t outputWidth, uint32_t outputHeight, uint32_t nativeHeight);

        RenderFramebuffer *inputFramebuffer() const;
        RenderTexture *inputTexture() const;
        uint32_t inputWidth() const;
        uint32_t inputHeight() const;

        // Runs the chain from the input image into output, which must be in the
        // COLOR_WRITE layout and stays in it. Leaves no framebuffer bound.
        bool apply(RenderCommandList *commandList, RenderTexture *output, uint32_t outputWidth, uint32_t outputHeight);

        void release();

    private:
        struct Impl;
        std::unique_ptr<Impl> impl;
    };
}
