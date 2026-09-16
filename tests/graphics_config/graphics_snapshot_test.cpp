#include "ultramodern/config.hpp"

#include <atomic>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <type_traits>

namespace host = ultramodern::renderer;
static_assert(!std::is_reference_v<decltype(host::get_graphics_config())>,
    "Graphics readers require a snapshot, not an unlocked reference to mutable storage");

namespace ultramodern {
// This regression exercises the real runtime getter/setter. Only device event
// dispatch and unused renderer error reporting are stubbed; no GPU is opened.
void trigger_config_action() {}
namespace error_handling {
void message_box(const char*) { std::abort(); }
[[noreturn]] void quick_exit(const char*, int, const char*, int) { std::abort(); }
}
}

int main() {
    host::GraphicsConfig first{};
    first.res_option = host::Resolution::Original;
    first.ds_option = 4;
    first.rr_manual_value = 120;
    first.api_option = host::GraphicsApi::Vulkan;
    host::GraphicsConfig second = first;
    second.res_option = host::Resolution::Auto;
    second.ds_option = 0;
    second.rr_manual_value = 60;
    second.api_option = host::GraphicsApi::D3D12;
    host::set_graphics_config(first);
    const auto retained = host::get_graphics_config();
    host::set_graphics_config(second);
    if (!(retained == first)) return 1;

    std::atomic<bool> start{false};
    std::atomic<bool> failed{false};
    std::thread writer([&] {
        while (!start.load()) std::this_thread::yield();
        for (int i = 0; i < 50000; ++i) host::set_graphics_config((i & 1) ? first : second);
    });
    std::thread reader([&] {
        start.store(true);
        for (int i = 0; i < 50000; ++i) {
            const auto snapshot = host::get_graphics_config();
            if (!(snapshot == first) && !(snapshot == second)) failed.store(true);
        }
    });
    writer.join();
    reader.join();
    if (failed.load()) { std::cerr << "FAIL: graphics profile snapshot contains mixed fields\n"; return 1; }
    std::cout << "PASS: retained and concurrent graphics snapshots are coherent\n";
}
