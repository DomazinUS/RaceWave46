#include "wr64_graphics_restart.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

using Api = ultramodern::renderer::GraphicsApi;
using Result = wr64::frontend::GraphicsReconfigurationResult;
static int checks = 0;
static void require(bool value, const char* message) {
    ++checks;
    if (!value) throw std::runtime_error(message);
}

struct RendererFixture {
    Api active = Api::D3D12;
    bool device_alive = true;
    bool partial_resources = false;
    int creates = 0;
    int destroys = 0;
    std::vector<Api> attempts;
    std::vector<Api> fail;
    void stop() {
        require(device_alive || partial_resources || creates > 0, "initial old device must exist");
        device_alive = partial_resources = false;
        ++destroys;
    }
    bool initialize(Api api) {
        require(!device_alive && !partial_resources, "old/partial resources destroyed before new API");
        ++creates;
        attempts.push_back(api);
        partial_resources = true;
        for (Api failed : fail) if (failed == api) return false;
        active = api;
        device_alive = true;
        partial_resources = false;
        return true;
    }
    Result apply(Api requested) {
        const auto previous = active;
        return wr64::frontend::reconfigure_graphics(requested, previous,
            [this] { stop(); }, [this](Api api) { return initialize(api); });
    }
};

int main() {
    try {
        using wr64::frontend::graphics_api_reconfiguration_needed;
        require(!graphics_api_reconfiguration_needed(Api::Vulkan, Api::Auto, Api::Vulkan), "explicit active API needs no recreation");
        require(graphics_api_reconfiguration_needed(Api::Vulkan, Api::Auto, Api::D3D12), "different API needs recreation");
        require(!graphics_api_reconfiguration_needed(Api::Vulkan, Api::Auto, Api::Auto), "automatic fallback remains active");
        require(graphics_api_reconfiguration_needed(Api::Vulkan, Api::Vulkan, Api::Auto), "explicit to auto reruns selection");
        RendererFixture repeated;
        for (Api api : {Api::Vulkan, Api::D3D12, Api::Vulkan, Api::D3D12}) {
            require(repeated.apply(api) == Result::Applied, "same-process repeated switch succeeds");
            require(repeated.active == api && repeated.device_alive, "requested device remains alive");
        }
        require(repeated.creates == 4 && repeated.destroys == 4, "one disposal per successful Apply");
        RendererFixture recovery;
        recovery.fail = {Api::Vulkan};
        require(recovery.apply(Api::Vulkan) == Result::Restored, "failed API restores previous");
        require(recovery.active == Api::D3D12 && recovery.device_alive, "fallback leaves valid device");
        require(recovery.attempts == std::vector<Api>{Api::Vulkan, Api::D3D12}, "fallback uses previous API once");
        require(recovery.destroys == 2, "failed partial resources disposed before recovery");
        RendererFixture fatal;
        fatal.fail = {Api::Vulkan, Api::D3D12};
        require(fatal.apply(Api::Vulkan) == Result::Failed, "double failure is terminal");
        require(!fatal.device_alive && !fatal.partial_resources, "double failure leaves no partial renderer");
        require(fatal.creates == 2 && fatal.destroys == 3, "bounded recovery and final cleanup");
        std::cout << "PASS: " << checks << " same-process API/recovery checks\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
