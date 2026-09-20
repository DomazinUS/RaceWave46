#pragma once

// Diagnostic only: inactive unless WR64_CONTROLLER_SMOKE=1 at process start.
// Optional WR64_CONTROLLER_SMOKE_DELAY_MS shifts actions/detach by0..300000ms.
// An invalid delay disables the diagnostic before it creates a virtual device.
// WR64_CONTROLLER_SMOKE_MODE=launcher runs the selector/child-return input
// sequence only in the launcher; inherited launcher mode is ignored by cores.
// Other modes run only in the USA core (timetrial adds the menu Down action).
// Call on the host event thread before the existing frontend pump.
void wr64_controller_smoke_update();
// Release and detach only the virtual device created by this helper.
void wr64_controller_smoke_shutdown();
