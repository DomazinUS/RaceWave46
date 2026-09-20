"""Extract one archived numeric sky packet, without copying textures or a ROM."""
import argparse
import hashlib
import json
from pathlib import Path

p = argparse.ArgumentParser()
p.add_argument('capture', type=Path)
p.add_argument('header', type=Path)
a = p.parse_args()
with a.capture.open('rb') as stream:
    line = stream.readline()
c = json.loads(line)
assert c['workload'] == 5 and len(c['layers']) == 2
layers = {layer['material']['draw']: layer for layer in c['layers']}
assert set(layers) == {2, 3}
vertices = {}
for layer in layers.values():
    for vertex in layer['vertices']:
        if vertex['id'] in vertices:
            assert vertices[vertex['id']] == vertex['gpu_u32']
        vertices[vertex['id']] = vertex['gpu_u32']
record = max(c['records_u32'], key=lambda r: r[30])
assert record[2] == 11 and record[30] > 0
out = ['#pragma once', '// Numeric first-opening archive from the September11 D3D12 diagnostic.',
       '// Not a capture of the failing Vulkan session. Texture pixels and GPUTile',
       '// replacement/mip/descriptor metadata are absent and remain synthetic.',
       '// First JSON line SHA256: ' + hashlib.sha256(line).hexdigest(),
       'namespace OpeningSkyCapture {']
def words(name, values):
    out.append('constexpr uint32_t ' + name + '[] = {' + ','.join(str(x) + 'u' for x in values) + '};')
for name, key in [('Camera','camera_u32'),('CloudParams','cloud_params_u32'),('Sky','sky_u32'),('Backdrop','backdrop_u32')]:
    words(name, c[key])
words('WaterCenter', record[4:8])
words('WaterNormal', record[8:12])
out.append('struct Vertex { uint32_t index; uint32_t data[10]; };')
out.append('constexpr Vertex Vertices[] = {')
for index, data in sorted(vertices.items()):
    out.append('{' + str(index) + 'u,{' + ','.join(str(x) + 'u' for x in data) + '}},')
out.append('};')
for draw, layer in sorted(layers.items()):
    prefix = 'Backdrop' if draw == 2 else 'Cloud'
    material = layer['material']
    words(prefix+'Faces', [v['id'] for v in layer['vertices']])
    words(prefix+'Combiner', material['combiner'])
    words(prefix+'OtherMode', material['other_mode'])
    words(prefix+'RDP', material['rdp_u32'])
    for tile in material['tiles']:
        words('Tile'+str(tile['index']), tile['rdp_u32'])
out.append('}')
a.header.write_text('\n'.join(out)+'\n', encoding='utf-8')
print('Extracted14 native vertices,36 indices, two materials and three tiles; texture pixels remain synthetic.')
