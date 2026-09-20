"""Embed the unmodified shipped IPS bytes for the production ROM patcher."""
from pathlib import Path
import sys

source, output_c, output_h = map(Path, sys.argv[1:])
data = source.read_bytes()
output_h.write_text('#pragma once\n#ifdef __cplusplus\nextern "C" {\n#endif\n'
                    f'extern const char wr64_rom_patch_ips[{len(data)}];\n'
                    '#ifdef __cplusplus\n}\n#endif\n')
rows = [','.join(f'0x{byte:02x}' for byte in data[n:n+32]) for n in range(0, len(data), 32)]
output_c.write_text(f'#include "{output_h.name}"\n'
                    f'const char wr64_rom_patch_ips[{len(data)}] = {{\n' + ',\n'.join(rows) + '\n};\n')
