"""Compile production presentation decisions against inert DXGI/queue objects.

No window, graphics device, ROM, or game process is created by this fixture.
"""
from pathlib import Path
import re
import sys


def matched(text, start, opening, closing):
    assert text[start] == opening
    depth = 0
    for i in range(start, len(text)):
        if text[i] == opening:
            depth += 1
        elif text[i] == closing:
            depth -= 1
            if depth == 0:
                return text[start:i + 1]
    raise AssertionError("Unbalanced production expression")


root, output = map(Path, sys.argv[1:3])
native = (root / "lib/rt64/src/contrib/plume/plume_d3d12.cpp").read_text()
start = native.index("bool D3D12SwapChain::present(")
body_start = native.index("{", start)
implementation = native[start:body_start] + matched(native, body_start, "{", "}")
(output / "present_implementation.inc").write_text(implementation + "\n")

queue = (root / "lib/rt64/src/hle/rt64_present_queue.cpp").read_text()
start = queue.index("const bool displayPaced = wr64PresentUsesDisplayPacing(")
end = queue.index(";", start) + 1
decision = queue[start:end]
condition_start = queue.index("if (", end) + 3
condition = matched(queue, condition_start, "(", ")")

# A stale or unsynchronized refresh-rate read invalidates the decision after a
# fullscreen/monitor transition. Require the actual target and display rates to
# be copied together while the existing configuration mutex is held.
lock_start = queue.index("std::scoped_lock<std::mutex> configurationLock(",
                         queue.index("void PresentQueue::threadPresent("))
lock_end = queue.index("\n        }", lock_start)
lock = queue[lock_start:lock_end]
for field in ("targetRate", "swapChainRate"):
    assert re.search(rf"{field}\s*=\s*ext\.sharedResources->{field}\s*;", lock), field

(output / "pacing_implementation.inc").write_text(
    decision + "\nreturn " + condition + ";\n")
print("Extracted production D3D12 Present and present-queue pacing decisions")
