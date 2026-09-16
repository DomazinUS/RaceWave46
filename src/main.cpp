#include "wr64_diagnostic_policy.h"
#include <algorithm>
#include <chrono>
#include <cinttypes>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <memory>
#include <exception>
#include <mutex>
#include <semaphore>
#include <string>
#include <string_view>
#include <thread>
#include <condition_variable>
#include <mutex>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include "wr64_runtime.hpp"
#include "wr64_composer_window.hpp"
#include "wr64_io.hpp"
#include "wr64_renderer.hpp"
#include "wr64_rom_patch.hpp"
#include "wr64_window.hpp"
#include "wr64_forensic.h"
#include "wr64_frontend.hpp"
#include "wr64_input.hpp"
#include "wr64_editions.hpp"
#include "wr64_game_rumble.hpp"
#include "wr64_controller_smoke.hpp"
#include "wr64_ghost.hpp"
#include "wr64_ghost_native.h"
#include "wr64_achievements.hpp"
#include "wr64_achievement_badges.hpp"
#include "wr64_achievements_native.hpp"

#include "librecomp/game.hpp"
#include "librecomp/rsp.hpp"
#include "ultramodern/error_handling.hpp"
#include "ultramodern/input.hpp"
#include "ultramodern/renderer_context.hpp"
#include "ultramodern/ultramodern.hpp"

extern "C" void recomp_entrypoint(uint8_t* rdram, recomp_context* ctx);
extern RspUcodeFunc aspMain;
gpr get_entrypoint_address();

namespace {

// EXP-005: IPS-native ROM with the static safe-area clear DL at 0xF60F0
// widened to full frame (scissor (0,0)-(424,240), fillrect (0,0)-(423,239)).
// EXP-012: additionally widens the IPS-missed transition-fade fill at ROM
// 0xF6270 from (8,20)-(310,218) to full frame (0,0)-(423,239), mirroring the
// sibling full-frame DL at 0xF6188.
// EXP-013: two resident inset scissor builds widened to full frame
// (func_80093DBC ROM 0x4E69C.., func_801FC4D4-A ROM 0xCAB9C..) - hook-redundant.
// EXP-014: THE TRANSITION FADE/DIM QUAD. Layer trace identified the fade as an
// orthographic 2-triangle quad at exactly (8,20)-(415,219) (pass role
// orthographic-overlay). func_801E4440 passes that geometry as immediates to
// the shaded-quad helper func_801E7C58. Both call sites widened to
// (0,0)-(423,239): ROM 0xB304C/0xB3060/0xB3064/0xB3068 (site 1, was
// (8,20)-(415,219)) and 0xB3084/0xB3094/0xB3098/0xB309C (site 2, was
// (8,12)-(415,229)).
// EXP-015: func_801E7908 is the actual TRANSITION fade drawer (four calls to
// the shaded-quad helper func_801E7C58 with animated RGBA from globals; the
// IPS widened x1 310->414 in three calls, kept the 8/20 insets, and missed
// the fourth call entirely). All four call sites widened to (0,0)-(423,239):
// ROM 0xB5FCC 0xB5FF0 0xB5FFC 0xB6000 0xB6004 / 0xB6044 0xB604C 0xB6050 /
// 0xB6084 0xB60A8 0xB60B4 0xB60B8 0xB60BC / 0xB60FC 0xB6104 0xB6108.
// EXP-024: content-edge + separator widen on top of the EXP-015 ROM.
// (a) All six static callers of the shaded-quad helper func_801E7C58
//     (func_801E4440 pause/dim sites 0xB304C/68/84/9C; func_801E7908 fade
//     sites 0xB5FF0/0xB6004/44/50/A8/BC/FC/0x6108) widened from the inclusive
//     (0,0)-(423,239) to exclusive-full (0,0)-(424,240): li 423->424,
//     li 239->240, 12 instruction words. The dynamic caller at 0x1BD698 is
//     untouched.
// (b) Four separator fillrects the IPS missed (static DLs 0x165230/38/80/88)
//     widened from 320-space (8,y)-(311,y+1) to the IPS idiom (8,y)-(415,y+1)
//     (lrx 0x4DC->0x67C).
// EXP-028: the shaded-quad helper func_801E7C58 (ROM ~0xB6338) internally
// CLAMPS x to <=423 and lets y pass at 239 - the inclusive idiom inside the
// shared builder itself, which silently undid the EXP-024 caller widen and
// bounds every quad (including the steady menu backdrops via the dynamic
// caller) to 423x239. Three words convert the clamps into promotions:
//   0xB632C sltiu imm 0x1A8->0x1A7 (X >= 423 enters the clamp branch)
//   0xB6338 addiu imm 0x1A7->0x1A8 (clamp value 423 -> 424)
//   0xB634C sltiu imm 0x0F0->0x0EF (Y >= 239 enters the clamp branch; value
//           already 240). Interior quads (<=422/238) are untouched.
// WIPE-FULLFRAME-R1 (2026-07-29): the screen-change wipe left the top ~2.6 and
// bottom ~6.3 native rows uncovered. Measured cause: the wipe's own transform
// (perspective proj @seg7+0x1300, modelview @seg7+0x1340, uniform scale
// 0.04998779, z -224) maps the cover geometry to screen rows 2.621..233.711 -
// an overscan margin present in the original 320-wide game, not a widescreen
// regression. The cover is 8 quad strips, x 0..3200, y 0..-2560, with a
// textured leading edge at x 3200..3840; four copies of the asset live in the
// segment-1 block (a flat copy of ROM 0xF6090):
//   cover 0x150838 0x151468 0x152098 0x152CC8   edge = cover + 0x120
// The outermost strip edges are extended so the same transform reaches past
// both frame edges (the scissor clips the surplus):
//   y     0 ->    64  (screen row  2.621 -> -3.156)
//   y -2560 -> -2688  (screen row 233.711 -> 245.265)
// Edge-block s/t are extrapolated along each block's own linear fit, so the
// step pattern continues rather than stretching. 56 fields, 80 bytes.
// 2P-FRAME-R1 (2026-07-30): the split-screen play area does not fill the window.
// Each player's viewport is a static Vp struct whose vscale.y is already 120 -
// the full 240 lines - so the letterbox was always the scissor, never the
// viewport. With the two-player scissors opened to a clean 120 lines each
// (corrected in RT64, see lib/rt64/src/common/rt64_wr64_2p_frame.h), the
// viewport centres move so each player's camera axis sits at the centre of its
// own half and both see +/-0.5 of the vertical field of view. Four big-endian
// s16 halfwords at struct offset +10, in pixels * 4; each struct is unique in
// the image, and the one-player structs at 0x0950C0 / 0x10A4E0 are different
// structs in the same tables and are NOT touched:
//   0x0950DA  P1 main       264 -> 240   ( 66 -> 60)
//   0x0950EA  P2 main       704 -> 720   (176 -> 180)
//   0x10A53A  P1 secondary  128 -> 104   ( 32 -> 26)
//   0x10A54A  P2 secondary  568 -> 584   (142 -> 146)
// The secondaries keep their -34 line relationship to their own main.
constexpr uint64_t kRomXxh3 = 0x50D5B6046F0C8115ULL;
constexpr std::u8string_view kGameId = u8"waverace64.n64.us.rev1";
std::binary_semaphore first_vi_ready{0};
std::once_flag first_vi_once;

void on_vi() {
#if WR64_DIAGNOSTIC_ENABLED
    static std::atomic<uint64_t> forensic_native_frame{0};
    const uint64_t native_frame = forensic_native_frame.fetch_add(1) + 1;
    wr64_forensic_set_native_frame(native_frame);
    wr64_forensic_record(WR64_FORENSIC_VI, native_frame, 0, 0, 0, 0, 0, 0, 0);
#endif
    std::call_once(first_vi_once, [] { first_vi_ready.release(); });
#if WR64_DIAGNOSTIC_ENABLED
    wr64::composer::wait_if_frozen();
#endif
}

void show_error(const char* message) {
    std::fprintf(stderr, "[runtime] %s\n", message);
}

RspUcodeFunc* get_rsp_microcode(const OSTask* task) {
    if (task->t.type == M_AUDTASK) {
        return aspMain;
    }
    std::fprintf(stderr, "[runtime] unsupported RSP task type: %" PRIu32 "\n", task->t.type);
    return nullptr;
}

const char* validation_error_name(recomp::RomValidationError error) {
    switch (error) {
        case recomp::RomValidationError::Good: return "good";
        case recomp::RomValidationError::FailedToOpen: return "failed to open";
        case recomp::RomValidationError::NotARom: return "not an N64 ROM";
        case recomp::RomValidationError::IncorrectRom: return "incorrect game";
        case recomp::RomValidationError::NotYet: return "unsupported game";
        case recomp::RomValidationError::IncorrectVersion: return "incorrect revision";
        case recomp::RomValidationError::OtherError: return "runtime error";
    }
    return "unknown error";
}

}  // namespace

int main(int argc, char** argv) {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    std::setvbuf(stderr, nullptr, _IONBF, 0);
    std::atexit([] { WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[runtime] std::exit handler reached\n")); });
    std::at_quick_exit([] { WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[runtime] std::quick_exit handler reached\n")); });
    std::set_terminate([] {
        std::fprintf(stderr, "[runtime] std::terminate handler reached\n");
        std::abort();
    });
#ifdef _WIN32
    SetUnhandledExceptionFilter([](EXCEPTION_POINTERS* exception) -> LONG {
        const auto image_base = reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr));
        const auto exception_address = reinterpret_cast<uintptr_t>(
            exception->ExceptionRecord->ExceptionAddress);
        std::fprintf(
            stderr,
            "[runtime] unhandled Windows exception 0x%08lX at %p (image RVA 0x%llX)\n",
            exception->ExceptionRecord->ExceptionCode,
            exception->ExceptionRecord->ExceptionAddress,
            static_cast<unsigned long long>(exception_address - image_base));
        return EXCEPTION_CONTINUE_SEARCH;
    });
#endif
    wr64::editions::Options options;
    try { options = wr64::editions::parse_process_options(argc, argv); }
    catch (const std::exception& error) {
        std::fprintf(stderr, "[launch] %s\n", error.what());
        return EXIT_FAILURE;
    }
    const std::filesystem::path rom_path = options.rom.empty()
        ? options.runtime / (std::u8string{kGameId} + u8".z64") : options.rom;
#ifdef WR64_ENABLE_RT64
    const int run_seconds = options.seconds;
#else
    const int run_seconds = options.seconds > 0 ? options.seconds : 10;
#endif
#ifdef WR64_ENABLE_RT64
    const bool windowed = true;
#else
    const bool windowed = options.windowed;
#endif
    const std::filesystem::path runtime_path = options.runtime;

    wr64_forensic_initialize();
    wr64::window::set_enabled(windowed);

    std::filesystem::create_directories(runtime_path);
    recomp::register_config_path(runtime_path);
    struct AchievementsShutdown {
        ~AchievementsShutdown() {
            wr64::achievements::shutdown();
            wr64::achievement_badges::shutdown();
        }
    } achievements_shutdown;
    wr64::achievements::initialize(recomp::get_config_path());
    wr64::achievement_badges::initialize(recomp::get_config_path());

    recomp::GameEntry game{
        .rom_hash = kRomXxh3,
        .internal_name = "WAVE RACE 64",
        // REQUIRED. recomp::register_game hard-exits on an empty
        // display_name - librecomp/src/recomp.cpp:77. This is the
        // human-facing game name the frontend will show later; the
        // project's own identity belongs in the window title and the UI,
        // not here.
        .display_name = "Wave Race 64",
        .game_id = std::u8string{kGameId},
        .mod_game_id = "waverace64",
        .save_type = recomp::SaveType::Eep4k,
        .is_enabled = true,
        .has_compressed_code = false,
        .entrypoint_address = get_entrypoint_address(),
        .entrypoint = recomp_entrypoint,
        .on_init_callback = [](uint8_t*, recomp_context*) {
            wr64::achievements::native::game_initialized(recomp::get_rom());
        },
    };

    recomp::register_game(game);
    // A player owns the cartridge image, not the widescreen ROM this port was
    // recompiled from. Both are accepted: the cartridge image is patched in
    // memory here, the already-patched ROM passes the hash check untouched.
    recomp::register_rom_patcher(wr64::rom_patch::apply_if_unpatched);
    // recompui's launcher reads this, and indexes element zero without
    // checking. A no-op when the frontend is not compiled in.
    wr64::frontend::register_game(game);
    wr64::register_overlays();

    std::u8string game_id{kGameId};

    // TWO WAYS TO RUN, and they want opposite things.
    //
    //   Diagnostic: a run script hands over a ROM and a duration, the game
    //   boots itself, captures, and quits. Every trace and census script in
    //   this tree works this way and none of them can sit at a menu.
    //
    //   Interactive: the launcher is the front door, exactly as it is in every
    //   other recomp project. It picks the ROM, validates it once through
    //   recomp::select_rom, remembers it, and starts the game when told to.
    //   Nothing here should validate a ROM or start anything.
#ifdef WR64_ENABLE_FRONTEND
    const bool diagnostic_run = options.launch;
#else
    const bool diagnostic_run = true;
#endif

    if (diagnostic_run) {
        std::error_code rom_error;
        const auto rom_size = std::filesystem::file_size(rom_path, rom_error);
        if (rom_error || rom_size < 64 || rom_size > 64 * 1024 * 1024) {
            std::fprintf(stderr, "ROM validation failed: select a complete USA Rev 1 ROM in the launcher\n");
            return EXIT_FAILURE;
        }
        const auto validation = recomp::select_rom(rom_path, game_id);
        if (validation != recomp::RomValidationError::Good) {
            std::fprintf(stderr, "ROM validation failed: %s\n", validation_error_name(validation));
            return EXIT_FAILURE;
        }
    }

    recomp::rsp::callbacks_t rsp_callbacks{.get_rsp_microcode = get_rsp_microcode};
    ultramodern::renderer::callbacks_t renderer_callbacks{
        .create_render_context = wr64::renderer::create_render_context,
    };
    ultramodern::audio_callbacks_t audio_callbacks{
        .queue_samples = wr64::audio::queue_samples,
        .get_frames_remaining = wr64::audio::get_frames_remaining,
        .set_frequency = wr64::audio::set_frequency,
    };
    ultramodern::input::callbacks_t input_callbacks{
        .poll_input = wr64::input::poll,
        .get_input = wr64::input::get,
        .set_rumble = wr64::input::set_rumble,
        .get_connected_device_info = wr64::input::get_connected_device_info,
    };
    ultramodern::gfx_callbacks_t gfx_callbacks{
        .create_gfx = wr64::window::create_gfx,
        .create_window = wr64::window::create_window,
        .update_gfx = wr64::window::update_gfx,
    };
    ultramodern::error_handling::callbacks_t error_callbacks{
        .message_box = show_error,
    };

    recomp::Configuration config{
        // recomp::Version has user-declared constructors in this runtime, so
        // it is not an aggregate and cannot take designated initialisers.
        .project_version = recomp::Version{1, 0, 0},
        .window_handle = {},
        .rsp_callbacks = rsp_callbacks,
        .renderer_callbacks = renderer_callbacks,
        .audio_callbacks = audio_callbacks,
        .input_callbacks = input_callbacks,
        .gfx_callbacks = gfx_callbacks,
        .events_callbacks = {
            .vi_callback = on_vi,
            .gfx_init_callback = nullptr,
        },
        .error_handling_callbacks = error_callbacks,
        .threads_callbacks = {},
        .message_queue_control = {},
    };

    if (run_seconds > 0) {
        WR64_DIAGNOSTIC_LOG(std::fprintf(
            stderr,
            "Starting %s Wave Race runtime for %d seconds\n",
            windowed ? "windowed" : "headless",
            run_seconds));
    }
    else {
        WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "Starting Wave Race; the launcher opens first\n"));
    }
    std::mutex lifecycle_mutex;
    std::condition_variable lifecycle_wake;
    bool runtime_stopped = false;
    std::thread lifecycle{[game_id, run_seconds, diagnostic_run, &lifecycle_mutex, &lifecycle_wake, &runtime_stopped] {
        if (!diagnostic_run) {
            // The launcher's Start Game calls recomp::start_game itself
            // (ui_launcher.cpp:464). Booting the ROM from here as well is what
            // put the game on screen with the menu stranded on top of it.
            return;
        }
        // Wait until the VI thread completes its first dummy scanout. RT64
        // setup can take longer than the old fixed delay, and marking the game
        // started before this point leaves the runtime without a VI mode.
        first_vi_ready.acquire();
        WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[runtime] starting game thread\n"));
        // The second argument is the game-mode id. Empty is the base game
        // with no game mode, which is what this project has always run.
        recomp::start_game(game_id, "");
        WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[runtime] game thread started\n"));
        if (run_seconds > 0) {
            std::unique_lock lock(lifecycle_mutex);
            if (lifecycle_wake.wait_for(lock, std::chrono::seconds{run_seconds}, [&] { return runtime_stopped; })) return;
            lock.unlock();
            WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[runtime] diagnostic interval complete\n"));
            ultramodern::quit();
        }
    }};

    // Input FIRST: it registers the N64 game inputs that the Controls tab is
    // built from, and configure() is what creates that tab.
    wr64::input::initialize();

    // Program name/id, the primary font and the config tabs. This has to run
    // before recomp::start: start reaches RT64 setup, setup fires recompui's
    // init hook, and that hook throws if any of it is missing.
    wr64::frontend::configure();

    recomp::start(config);
    // start() returns after the native/event workers have joined.
    wr64::achievements::game_stopped();
    wr64::achievements::shutdown();
    wr64::achievement_badges::shutdown();
    WR64_DIAGNOSTIC_LOG(std::fprintf(stderr, "[runtime] host event loop stopped\n"));
    {
        std::lock_guard lock(lifecycle_mutex);
        runtime_stopped = true;
    }
    lifecycle_wake.notify_all();

    // The window's event loop used to do this, because it was the only place
    // that saw the close. recompinput owns those events now, so it happens here.
    // quit() already releases diagnostic waits before the runtime joins its
    // workers. Repeat it here before the remaining application cleanup.
    wr64_forensic_force_resume();
    wr64::composer::shutdown();
    wr64_controller_smoke_shutdown();
    wr64::ghost::reset_session();
    wr64_ghost_native_forget();
    wr64_game_rumble_reset();
    wr64_game_rumble_update();
    wr64::input::shutdown();

    lifecycle.join();
    wr64_forensic_shutdown();
    return EXIT_SUCCESS;
}
