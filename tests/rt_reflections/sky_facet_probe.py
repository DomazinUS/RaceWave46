"""Offline analytical water/sky discontinuity probe; no graphics or game launch.

This is not a captured Wave Race mesh or production GPU execution. It proves
that the experimental sky shader's derivative-normal formula permits seams
on this synthetic patch, even if sky lookup/UV interpolation is correct. It
does not establish the actual course's normal, sky-coverage or draw-selection
values, or identify which mechanism produced any particular screenshot.
Native water is triangulated; this patch gives adjacent triangles different
slopes. The original, validated no-sky shader is outside this probe's scope.

Run: python tests/rt_reflections/sky_facet_probe.py
"""

import json
import math
from pathlib import Path


def add(a, b):
    return tuple(x + y for x, y in zip(a, b))


def sub(a, b):
    return tuple(x - y for x, y in zip(a, b))


def mul(a, t):
    return tuple(x * t for x in a)


def dot(a, b):
    return sum(x * y for x, y in zip(a, b))


def cross(a, b):
    return (a[1] * b[2] - a[2] * b[1],
            a[2] * b[0] - a[0] * b[2],
            a[0] * b[1] - a[1] * b[0])


def unit(a):
    return mul(a, 1 / math.sqrt(dot(a, a)))


def average(a, b):
    return mul(add(a, b), 0.5)


def angle(a, b):
    return math.degrees(math.acos(max(-1, min(1, dot(unit(a), unit(b))))))


def reflection(view, normal):
    # HLSL reflect(-v, n) = -v + 2 * dot(n, v) * n.
    return sub(mul(normal, 2 * dot(normal, view)), view)


def normal(a, b, c):
    n = cross(sub(b, a), sub(c, a))
    return n if n[1] >= 0 else mul(n, -1)


def sky_color(direction):
    # A continuous sky gradient, deliberately no texture/filter/coverage seam.
    elevation = max(0, min(1, direction[1]))
    return (0.95 - 0.65 * elevation, 0.42 + 0.12 * elevation,
            0.16 + 0.56 * elevation)


def water_color(view, n, sky, enabled=True):
    native = (0.8, 0.32, 0.06)
    fresnel = 0.08 + 0.35 * (1 - max(0, min(1, dot(n, view)))) ** 5
    return add(mul(native, 1 - fresnel), mul(sky, fresnel)) if enabled else native


def channel_jump(a, b):
    return 255 * max(abs(x - y) for x, y in zip(a, b))


def evaluate(height, epsilon):
    a, b = (-30.0, 0.0, 0.0), (30.0, height, 0.0)
    c, d = (30.0, 0.0, 60.0), (-30.0, height, 60.0)
    raw = [normal(a, b, c), normal(a, c, d)]
    faces = list(map(unit, raw))
    shared = unit(add(*raw))  # Area-weighted normals at shared A/C vertices.
    midpoint = average(a, c)
    positions = [add(mul(midpoint, 1 - epsilon), mul(tip, epsilon))
                 for tip in (b, d)]
    camera = (0.0, 45.0, -150.0)
    views = [unit(sub(camera, p)) for p in positions]
    smooth = [unit(add(mul(shared, 1 - epsilon), mul(n, epsilon))) for n in faces]
    rays = [reflection(v, n) for v, n in zip(views, faces)]
    smooth_rays = [reflection(v, n) for v, n in zip(views, smooth)]
    assert all(r[1] > 0 for r in rays + smooth_rays)
    colors = [sky_color(r) for r in rays]
    smooth_colors = [sky_color(r) for r in smooth_rays]
    outputs = [water_color(v, n, col) for v, n, col in zip(views, faces, colors)]
    smooth_outputs = [water_color(v, n, col) for v, n, col in zip(views, smooth, smooth_colors)]
    # Sampling a smooth direction alone still leaves flat-normal Fresnel.
    sky_only_outputs = [water_color(v, n, col) for v, n, col in zip(views, faces, smooth_colors)]
    # Isolate an outer finite-fan boundary using a constant sky color. The
    # threshold is synthetic and chosen between the two reflected elevations;
    # it does not claim to identify the actual game's native sky-fan limits.
    cutoff = (rays[0][1] + rays[1][1]) * 0.5
    covered = [r[1] >= cutoff for r in rays]
    solid = (0.2, 0.6, 1.0)
    coverage_outputs = [water_color(v, n, solid, ok)
                        for v, n, ok in zip(views, faces, covered)]
    return {
        "height": height, "edge_distance_barycentric": epsilon,
        "face_normal_angle_degrees": angle(*faces),
        "flat_reflection_direction_jump_degrees": angle(*rays),
        "smooth_reflection_direction_jump_degrees": angle(*smooth_rays),
        "flat_reflected_elevation_degrees": [math.degrees(math.asin(r[1])) for r in rays],
        "continuous_full_coverage_sky_rgb_jump_8bit": channel_jump(*colors),
        "continuous_full_coverage_water_rgb_jump_8bit": channel_jump(*outputs),
        "smooth_full_coverage_sky_rgb_jump_8bit": channel_jump(*smooth_colors),
        "smooth_full_coverage_water_rgb_jump_8bit": channel_jump(*smooth_outputs),
        "smooth_sky_direction_but_flat_fresnel_water_rgb_jump_8bit": channel_jump(*sky_only_outputs),
        "constant_sky_with_finite_coverage": covered,
        "constant_sky_finite_coverage_water_rgb_jump_8bit": channel_jump(*coverage_outputs),
    }


def main():
    shader = (Path(__file__).resolve().parents[2] /
              "lib/rt64/src/shaders/Wr64WaterSkyReflectionPS.hlsl").read_text()
    assert "cross(dx, dy)" in shader and "reflect(-v, n)" in shader, (
        "Experimental sky normal/direction strategy changed; review analytical mapping")
    rows = [evaluate(height, epsilon) for height in (0.0, 3.0, 6.0)
            for epsilon in (1e-2, 1e-4, 1e-6)]
    flat = rows[2]
    creased = rows[-1]
    assert flat["continuous_full_coverage_water_rgb_jump_8bit"] < 1e-3
    assert creased["flat_reflection_direction_jump_degrees"] > 10
    assert creased["continuous_full_coverage_sky_rgb_jump_8bit"] > 20
    assert creased["continuous_full_coverage_water_rgb_jump_8bit"] > 1
    assert creased["smooth_full_coverage_water_rgb_jump_8bit"] < 1e-3
    assert len(set(creased["constant_sky_with_finite_coverage"])) == 2
    print(json.dumps({
        "kind": "Synthetic analytic reproduction, not captured course validation",
        "edge": "Adjacent A/B/C and A/C/D triangles, 60-unit grid spacing",
        "checks": "PASS: planar control, slope seam, continuous-sky colors, smooth edge limit, finite coverage",
        "cases": rows,
    }, indent=2))


if __name__ == "__main__":
    main()
