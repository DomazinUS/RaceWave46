"""Exercise the configure-time module on copies only; no GPU or game launch."""
import pathlib
import subprocess
import sys
import tempfile


cmake, module, production = map(pathlib.Path, sys.argv[1:])
fixtures = pathlib.Path(__file__).parent
original = (fixtures / "original.cpp").read_bytes().replace(b"\r\n", b"\n")
fixed = (fixtures / "fixed.cpp").read_bytes().replace(b"\r\n", b"\n")
checks = 0


def require(condition, description):
    global checks
    checks += 1
    if not condition:
        raise AssertionError(description)


def patch(source):
    return subprocess.run(
        [str(cmake), f"-DRT64_PLUME_D3D12_SOURCE={source}", "-P", str(module)],
        capture_output=True, text=True, timeout=15,
    )


with tempfile.TemporaryDirectory(prefix="wr64-plume-patch-") as directory:
    root = pathlib.Path(directory)
    for ending, name in ((b"\n", "lf"), (b"\r\n", "crlf")):
        source = root / f"plume-{name}.cpp"
        source.write_bytes(original.replace(b"\n", ending))
        result = patch(source)
        require(result.returncode == 0, result.stdout + result.stderr)
        require(source.read_bytes() == fixed.replace(b"\n", ending),
                f"First application did not produce exact fixed {name} source")
        before = source.stat().st_mtime_ns
        result = patch(source)
        require(result.returncode == 0, result.stdout + result.stderr)
        require(source.read_bytes() == fixed.replace(b"\n", ending),
                f"Second application changed {name} content")
        require(source.stat().st_mtime_ns == before,
                "Idempotent application must not rewrite the source")

    # One recognized block must not be written when the other is unfamiliar.
    source = root / "unexpected.cpp"
    unexpected = original.replace(b"descriptorIndexRelative =", b"changedUpstreamOffset =")
    source.write_bytes(unexpected)
    result = patch(source)
    require(result.returncode != 0, "Unrecognized source unexpectedly succeeded")
    require("unexpected sampler update source" in result.stderr,
            "Failure did not explain which upstream block needs review")
    require(source.read_bytes() == unexpected, "Failure partially rewrote source")

    source = root / "ambiguous.cpp"
    source.write_bytes(original + original)
    result = patch(source)
    require(result.returncode != 0, "Duplicate source blocks unexpectedly succeeded")
    require(source.read_bytes() == original + original, "Duplicate-source failure changed file")

    # Verify the real vendored file is recognized without modifying it. It may
    # already contain the fix because configure has run in this checkout.
    source = root / "production-copy.cpp"
    production_bytes = production.read_bytes()
    source.write_bytes(production_bytes)
    result = patch(source)
    require(result.returncode == 0, "Production source copy was not recognized: " + result.stderr)
    first = source.read_bytes()
    if b"Immutable samplers cannot be updated." in production_bytes:
        require(first == production_bytes, "Already-fixed production source changed")
    result = patch(source)
    require(result.returncode == 0 and source.read_bytes() == first,
            "Production source copy was not idempotent")

print(f"PASS: {checks} patch checks; exact source, LF/CRLF, idempotence, failure atomicity, production copy.")
