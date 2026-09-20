"""Compile the production dolphin stamper in a small synthetic-workload test.

Only renderer container types are substituted by the test. The complete
stamper body, native texture classifier and transform-group definitions are
the actual production source, so guard/ordering changes exercise real code.
"""
from pathlib import Path
import sys

source, output = map(Path, sys.argv[1:])
text = source.read_text()
start = text.index('    static void wr64DolphinStampTransformIdentity(Workload &workload) {')
end = text.index('    static void wr64DrakeSchoolStampTransformIdentity(', start)
output.write_text(text[start:end])
