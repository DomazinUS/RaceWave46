"""Compile actual presentation entry points against bounded GPU/window fakes."""
from pathlib import Path
import sys

root, output = map(Path, sys.argv[1:])
queue = (root / 'lib/rt64/src/hle/rt64_present_queue.cpp').read_text(encoding='utf-8')
vi = (root / 'lib/rt64/src/render/rt64_vi_renderer.cpp').read_text(encoding='utf-8')
plume = (root / 'lib/rt64/src/contrib/plume/plume_d3d12.cpp').read_text(encoding='utf-8')

def function(source, marker):
    start = source.index(marker)
    opening = source.index('{', start)
    depth = 1
    for cursor in range(opening + 1, len(source)):
        if source[cursor] == '{': depth += 1
        elif source[cursor] == '}': depth -= 1
        if depth == 0: return source[start:cursor + 1]
    raise AssertionError(marker)

functions = [function(queue, '    void PresentQueue::releaseSecondaryOutput()'),
             function(queue, '    bool PresentQueue::prepareSecondaryOutput('),
             function(vi, '    void VIRenderer::render(')]
# Execute the actual final output recording and semaphore selection. The
# surrounding native VI lookup/interpolation wait is left outside this CPU fake.
secondary = queue.index('                if (secondaryPresentFrame) {')
primary_end = queue.index('\n            if (lockedWorkloadMutex)', secondary)
recording = queue[secondary:primary_end]
assert recording.endswith('            }\n')
recording = recording[:-len('            }\n')]
functions.append('void recordBothOutputs(PresentQueue &q, RenderCommandList *commandList, '
    'VIRenderer::RenderParams renderParams, bool secondaryPresentFrame, bool displayedSeparateRace, '
    'uint32_t secondarySwapChainIndex, uint32_t swapChainIndex, RenderTexture *swapChainTexture, '
    'RenderFramebuffer *swapChainFramebuffer) {\n'
    'auto &ext=q.ext; auto &secondarySwapChain=q.secondarySwapChain; '
    'auto &secondaryFramebuffers=q.secondaryFramebuffers; auto &secondaryViRenderer=q.secondaryViRenderer; '
    'auto &viRenderer=q.viRenderer; auto &inspectorMutex=q.inspectorMutex; auto &inspector=q.inspector; '
    'auto &acquiredSemaphore=q.acquiredSemaphore; auto &secondaryAcquiredSemaphore=q.secondaryAcquiredSemaphore; '
    'auto &drawSemaphores=q.drawSemaphores; auto &secondaryDrawSemaphores=q.secondaryDrawSemaphores;\n'
    + recording + '\n}')

# Source contracts protect the transaction boundaries that extraction omits.
assert 'scratchColorTarget, colorTarget && colorTarget->wr64SeparateWindows' in queue
assert queue.count('secondarySwapChain->wait(') == 0
assert queue.count('secondarySwapChain->present(') == 1
assert 'secondarySwapChain->setVsyncEnabled(false)' in queue
assert queue.index('secondarySwapChain->present(') > queue.index('swapChainValid = ext.swapChain->present(')
wait = queue.index('ext.presentGraphicsWorker->wait();', secondary)
retire = queue.index('frameCounters.presented = frameCountersNextPresented;', secondary)
assert secondary < wait < retire
assert recording.count('drawHook(commandList, swapChainFramebuffer)') == 1
assert queue.index('wr64SecondaryRaceActive.store(false') < queue.rindex('releaseSecondaryOutput();')
destructor = function(plume, '    D3D12SwapChain::~D3D12SwapChain()')
assert 'i < textures.size()' in destructor and 'i < desc.textureCount' not in destructor
functions.append(destructor)
output.write_text('\n'.join(functions) + '\n', encoding='utf-8')
print('PASS production source contracts: immutable target, two draws before retirement, primary UI/timing, safe destructor')
