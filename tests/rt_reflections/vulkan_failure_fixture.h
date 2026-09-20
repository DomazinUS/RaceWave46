// Mock only the API return values; no command reaches the GPU and no device is
// deliberately lost. Real instance/device handles keep the wrapper paths valid.
struct VulkanFailureCalls {
    PFN_vkQueueSubmit submit = vkQueueSubmit;
    PFN_vkWaitForFences wait = vkWaitForFences;
    PFN_vkResetFences reset = vkResetFences;
    static inline uint32_t resetCalls = 0;
    ~VulkanFailureCalls() { vkQueueSubmit = submit; vkWaitForFences = wait; vkResetFences = reset; }
    static VKAPI_ATTR VkResult VKAPI_CALL failedSubmit(VkQueue, uint32_t, const VkSubmitInfo *, VkFence) { return VK_ERROR_DEVICE_LOST; }
    static VKAPI_ATTR VkResult VKAPI_CALL failedWait(VkDevice, uint32_t, const VkFence *, VkBool32, uint64_t) { return VK_ERROR_DEVICE_LOST; }
    static VKAPI_ATTR VkResult VKAPI_CALL timedOutWait(VkDevice, uint32_t, const VkFence *, VkBool32, uint64_t) { return VK_TIMEOUT; }
    static VKAPI_ATTR VkResult VKAPI_CALL completedWait(VkDevice, uint32_t, const VkFence *, VkBool32, uint64_t) { return VK_SUCCESS; }
    static VKAPI_ATTR VkResult VKAPI_CALL failedReset(VkDevice, uint32_t, const VkFence *) { ++resetCalls; return VK_ERROR_DEVICE_LOST; }
};

struct VulkanFailureDiagnostics {
    VulkanDevice *device;
    PFN_vkGetQueueCheckpointDataNV checkpoints;
    PFN_vkGetDeviceFaultInfoEXT fault;
    bool reported;
    static inline uint32_t checkpointCalls = 0, faultCalls = 0;
    explicit VulkanFailureDiagnostics(VulkanDevice *value) : device(value),
        checkpoints(value->getQueueCheckpointData), fault(value->getDeviceFaultInfo),
        reported(value->checkpointFailureReported.load()) {
        checkpointCalls = faultCalls = 0;
        device->getQueueCheckpointData = mockCheckpoints;
        device->getDeviceFaultInfo = mockFault;
        device->checkpointFailureReported.store(false);
    }
    ~VulkanFailureDiagnostics() {
        device->getQueueCheckpointData = checkpoints;
        device->getDeviceFaultInfo = fault;
        device->checkpointFailureReported.store(reported);
    }
    static VKAPI_ATTR void VKAPI_CALL mockCheckpoints(VkQueue, uint32_t *count, VkCheckpointDataNV *data) {
        ++checkpointCalls;
        require(data && *count >= 1, "Checkpoint report did not provide bounded storage");
        require(data[0].sType == VK_STRUCTURE_TYPE_CHECKPOINT_DATA_NV, "Checkpoint data structure is uninitialized");
        data[0].stage = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
        // Unknown opaque markers must not be treated as readable strings.
        data[0].pCheckpointMarker = reinterpret_cast<void *>(uintptr_t(1));
        *count = 1;
    }
    static VKAPI_ATTR VkResult VKAPI_CALL mockFault(VkDevice, VkDeviceFaultCountsEXT *counts, VkDeviceFaultInfoEXT *info) {
        ++faultCalls;
        require(counts && info && counts->addressInfoCount > 0 && counts->addressInfoCount <= 256 &&
            counts->vendorInfoCount > 0 && counts->vendorInfoCount <= 256,
            "Fault report did not provide bounded storage");
        require(!info->pVendorBinaryData && counts->vendorBinarySize == 0,
            "Fault report unexpectedly requested a vendor binary");
        std::strcpy(info->description, "synthetic fault; healthy GPU never queried");
        info->pAddressInfos[0] = {VK_DEVICE_FAULT_ADDRESS_TYPE_READ_INVALID_EXT, 0x12340000, 4096};
        std::strcpy(info->pVendorInfos[0].description, "synthetic vendor detail");
        info->pVendorInfos[0].vendorFaultCode = 123;
        info->pVendorInfos[0].vendorFaultData = 456;
        // Force the report's defensive count bounds and incomplete-data path.
        counts->addressInfoCount = 300;
        counts->vendorInfoCount = 300;
        return VK_INCOMPLETE;
    }
};

void verifyVulkanFailurePropagation(FixtureWorker &worker) {
    auto expectsFailure = [](auto operation, const char *api, const char *code = "-4") {
        bool caught = false;
        try { operation(); }
        catch (const std::runtime_error &error) {
            caught = std::strstr(error.what(), api) && std::strstr(error.what(), code);
        }
        require(caught, "Vulkan backend swallowed a fatal API result or omitted its origin/code");
    };
    VulkanFailureCalls calls;
    auto *device = static_cast<VulkanCommandQueue *>(worker.commandQueue.get())->device;
    VulkanFailureDiagnostics diagnostics(device);
    VulkanFailureCalls::resetCalls = 0;
    vkWaitForFences = VulkanFailureCalls::timedOutWait;
    expectsFailure([&] { worker.commandQueue->waitForCommandFence(worker.commandFence.get()); }, "vkWaitForFences", "2");
    require(VulkanFailureDiagnostics::checkpointCalls == 0 && VulkanFailureDiagnostics::faultCalls == 0,
        "Non-device-loss error queried device-loss diagnostics");
    vkQueueSubmit = VulkanFailureCalls::failedSubmit;
    expectsFailure([&] { worker.commandQueue->executeCommandLists(worker.commandList.get(), worker.commandFence.get()); }, "vkQueueSubmit");
    uint32_t nativeQueues = 0;
    for (const auto &family : device->queueFamilies)
        for (const auto &queue : family.queues) nativeQueues += queue.vk != VK_NULL_HANDLE;
    require(VulkanFailureDiagnostics::checkpointCalls == nativeQueues && VulkanFailureDiagnostics::faultCalls == 1,
        "Device loss did not query each native queue once and one bounded fault report");
    vkWaitForFences = VulkanFailureCalls::failedWait;
    vkResetFences = VulkanFailureCalls::failedReset;
    expectsFailure([&] { worker.commandQueue->waitForCommandFence(worker.commandFence.get()); }, "vkWaitForFences");
    require(VulkanFailureCalls::resetCalls == 0, "Vulkan backend reset a fence after completion failed");
    vkWaitForFences = VulkanFailureCalls::completedWait;
    expectsFailure([&] { worker.commandQueue->waitForCommandFence(worker.commandFence.get()); }, "vkResetFences");
    require(VulkanFailureCalls::resetCalls == 1, "Vulkan backend did not check fence reset failure");
    require(VulkanFailureDiagnostics::checkpointCalls == nativeQueues && VulkanFailureDiagnostics::faultCalls == 1,
        "Repeated device loss duplicated checkpoint/fault queries");
    std::puts("PASS: mocked Vulkan submit/wait/reset failures propagate; timeout does not query diagnostics; device loss reports bounded fault data and each queue once; no GPU submission or device loss induced.");
}
