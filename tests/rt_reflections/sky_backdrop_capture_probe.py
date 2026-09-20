#!/usr/bin/env python3
"""Reconstruct native backdrop hits from an existing numeric sky capture.

Read-only input; no game invocation, texture extraction, or screenshot capture.
Uses double-precision triangle intersections independently of the production
shader. Output contains paired numeric evidence and bounded aggregate counts.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct

import numpy as np


def floats(words):
    return np.array([struct.unpack("<f", struct.pack("<I", w))[0] for w in words], dtype=np.float64)


def intersections(frame, packets):
    """Return distance, texture V, determinant and oriented eye-plane distance."""
    vertices = frame["layers"][1]["vertices"]
    if len(vertices) != 18:
        raise ValueError("Expected the captured six-triangle backdrop")
    values = np.array([floats(v["gpu_u32"]) for v in vertices]).reshape(6, 3, 10)
    a = values[:, 0, :3]
    e1, e2 = values[:, 1, :3] - a, values[:, 2, :3] - a
    eye = floats(frame["backdrop_camera_u32"][:3])
    directions = np.array([floats(r[12:15]) for r in packets])
    p = np.cross(directions[:, None, :], e2[None, :, :])
    determinant = np.einsum("fi,rfi->rf", e1, p)
    delta = eye - a
    q = np.cross(delta, e1)
    scale = np.linalg.norm(e1, axis=1) * np.linalg.norm(e2, axis=1)
    with np.errstate(divide="ignore", invalid="ignore"):
        u = np.einsum("fi,rfi->rf", delta, p) / determinant
        v = np.einsum("ri,fi->rf", directions, q) / determinant
        distance = np.einsum("fi,fi->f", e2, q)[None, :] / determinant
    valid = (np.isfinite(distance) & np.isfinite(u) & np.isfinite(v)
             & (distance > 1e-4) & (u >= -1e-5) & (v >= -1e-5)
             & (u + v <= 1.00001) & (np.abs(determinant) > scale[None, :] * 1e-7))
    # Match the existing interpolation guard after independent intersection.
    u, v = np.maximum(u, 0), np.maximum(v, 0)
    denominator = np.maximum(1, u + v)
    u, v = u / denominator, v / denominator
    texture_v = ((1 - u - v) * values[None, :, 0, 5]
                 + u * values[None, :, 1, 5] + v * values[None, :, 2, 5])
    normals = np.cross(e1, e2)
    plane_distance = np.einsum("fi,fi->f", delta, normals) / np.linalg.norm(normals, axis=1)
    return np.where(valid, distance, np.inf), texture_v, determinant, plane_distance


def analyze(capture, end_ms):
    raw = capture.read_bytes()
    frames = [json.loads(line) for line in raw.splitlines() if line.strip()]
    counts = dict(captured_presentations=0, sky_query_packets=0, old_positive_nearest=0,
                  old_negative_nearest=0, negative_nearest_with_positive_exit=0,
                  negative_nearest_without_positive_exit=0, no_exit_downward=0, no_exit_upward=0,
                  old_no_intersection=0,
                  positive_nearest_unchanged=0, changed_inside_cone=0,
                  inside_cone_packets=0, old_backdrop_flag_mismatches=0)
    paired = []
    changes = []
    for frame in frames:
        if not 0 <= frame["elapsed_ms"] <= end_ms:
            continue
        counts["captured_presentations"] += 1
        packets = [r for r in frame["records_u32"] if r[1] in (5, 6)]
        counts["sky_query_packets"] += len(packets)
        if not packets:
            continue
        material = frame["layers"][1]["material"]
        if material is None or material["geometry_mode"] != 0x2204:
            raise ValueError("This bounded replay expects the captured F3DEX back-culled native backdrop")
        distance, texture_v, determinant, plane_distance = intersections(frame, packets)
        old_face = np.argmin(distance, axis=1)
        old_t = distance[np.arange(len(packets)), old_face]
        positive_distance = np.where(determinant > 0, distance, np.inf)
        new_face = np.argmin(positive_distance, axis=1)
        new_t = positive_distance[np.arange(len(packets)), new_face]
        old_hit = np.isfinite(old_t)
        old_positive = old_hit & (determinant[np.arange(len(packets)), old_face] > 0)
        old_negative = old_hit & ~old_positive
        exit_hit = np.isfinite(new_t)
        unchanged = old_positive & (old_face == new_face) & (old_t == new_t)
        counts["old_positive_nearest"] += int(old_positive.sum())
        counts["old_negative_nearest"] += int(old_negative.sum())
        counts["negative_nearest_with_positive_exit"] += int((old_negative & exit_hit).sum())
        counts["negative_nearest_without_positive_exit"] += int((old_negative & ~exit_hit).sum())
        downward = np.array([floats(r[12:15])[1] <= 0 for r in packets])
        counts["no_exit_downward"] += int((old_negative & ~exit_hit & downward).sum())
        counts["no_exit_upward"] += int((old_negative & ~exit_hit & ~downward).sum())
        counts["old_no_intersection"] += int((~old_hit).sum())
        counts["positive_nearest_unchanged"] += int(unchanged.sum())
        flag = np.array([bool(r[3] & 1) for r in packets])
        counts["old_backdrop_flag_mismatches"] += int((flag != old_hit).sum())
        inside = bool(np.all(plane_distance >= 0))
        if inside:
            counts["inside_cone_packets"] += len(packets)
            counts["changed_inside_cone"] += int((old_negative & exit_hit).sum() + (old_negative & ~exit_hit).sum())
        if old_negative.any():
            changes.append(dict(elapsed_ms=frame["elapsed_ms"], workload=frame["workload"],
                                negative_nearest=int(old_negative.sum()), positive_exit=int((old_negative & exit_hit).sum()),
                                no_exit=int((old_negative & ~exit_hit).sum())))
        if frame["elapsed_ms"] in (5321, 5357):
            for index, packet in enumerate(packets):
                if (packet[0] & 65535, packet[0] >> 16) != (672, 608):
                    continue
                hits = [dict(face=int(face), distance=float(distance[index, face]),
                             texture_v=float(texture_v[index, face]), determinant=float(determinant[index, face]))
                        for face in np.flatnonzero(np.isfinite(distance[index]))]
                paired.append(dict(elapsed_ms=frame["elapsed_ms"], workload=frame["workload"],
                                   presentation=frame["presentation"], pixel=[672, 608],
                                   camera=floats(frame["backdrop_camera_u32"][:3]).tolist(),
                                   ray=floats(packet[12:15]).tolist(), actual_sky_rgba=floats(packet[16:20]).tolist(),
                                   eye_plane_distances=plane_distance.tolist(), intersections=hits,
                                   old_selected_face=int(old_face[index]), corrected_selected_face=int(new_face[index]) if exit_hit[index] else None))
    return dict(schema=1, capture=str(capture.resolve()), sha256=hashlib.sha256(raw).hexdigest(),
                interval_ms=[0, end_ms], counts=counts, paired=paired, changed_presentations=changes)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--capture", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--end-ms", type=int, default=7312, help="End of first opening camera, before later shot")
    args = parser.parse_args()
    if args.capture.resolve() == args.output.resolve():
        parser.error("Output must not replace the input capture")
    result = analyze(args.capture, args.end_ms)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2, allow_nan=False) + "\n", encoding="utf-8")
    print(json.dumps(result["counts"], indent=2))
    print("Paired rays:", len(result["paired"]))
    print("Input SHA256:", result["sha256"])


if __name__ == "__main__":
    main()
