from pathlib import Path
import sys
source=Path(sys.argv[1]).read_text(encoding='utf-8')
end=source.index('\nint main(int argc, char **argv)')
Path(sys.argv[2]).write_text(source[:end], encoding='utf-8')

# Compile the real renderer dispatch gate in the focused harness: helper-only
# tests would miss the native-framerate/Original-effects admission regression.
root=Path(sys.argv[3])
queue=(root/'lib/rt64/src/hle/rt64_workload_queue.cpp').read_text(encoding='utf-8')
start=queue.index('                const bool wr64RTFrameMatching =')
end=queue.index('                bool generateInterpolatedFrames',start)
Path(sys.argv[4]).write_text(queue[start:end], encoding='utf-8')
state=(root/'lib/rt64/src/hle/rt64_state.cpp').read_text(encoding='utf-8')
frame=(root/'lib/rt64/src/hle/rt64_game_frame.cpp').read_text(encoding='utf-8')
reset=(root/'lib/rt64/src/hle/rt64_workload.cpp').read_text(encoding='utf-8')
assert 'workload.wr64SplitWaterRoundnessScope = wr64NativeSplitWaterScope(\n            wr64Course, wr64Players, wr64Phase, wr64Mode, wr64LoadedEnhanced);' in state
assert 'workload.wr64FarWaterDistanceViewScope[view] = wr64FarWaterDistanceScope(' in state
assert 'waterWorkload.wr64SplitWaterRoundnessScope, splitRoundnessStrength)' in frame
assert 'wr64SplitWaterRoundnessScope = false;' in reset
