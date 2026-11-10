#!/usr/bin/env python3
"""One-knob host build and test runner for the deterministic CO lifecycle core."""
from __future__ import annotations

import argparse
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent


def run(label: str, command: list[str]) -> None:
    print(f"\n==> {label}", flush=True)
    subprocess.run(command, cwd=ROOT, check=True)


def check() -> None:
    make = shutil.which("make") or shutil.which("gmake")
    if make:
        run("Build and run CO tests", [make, "clean", "test"])
        return
    compiler = next((shutil.which(name) for name in ("gcc", "clang", "cc") if shutil.which(name)), None)
    if not compiler:
        raise RuntimeError("Install GNU Make or a C11 compiler (GCC/Clang) to run host tests.")
    out = ROOT / ".build"
    out.mkdir(exist_ok=True)
    binary = out / ("test_runtime.exe" if sys.platform == "win32" else "test_runtime")
    run("Compile CO runtime test", [compiler, "-std=c11", "-O2", "-Wall", "-Wextra", "-Werror", "-pedantic", "-Iinclude", "src/runtime.c", "tests/test_runtime.c", "-o", str(binary)])
    run("Run CO runtime test", [str(binary)])


def main() -> int:
    parser = argparse.ArgumentParser(description="CO one-knob host verification.")
    parser.add_argument("command", nargs="?", choices=("check", "build", "run"), default="run")
    args = parser.parse_args()
    try:
        check()
        print("\nCO host verification passed. The application owns callback serialization and target timing.")
    except (subprocess.CalledProcessError, RuntimeError) as exc:
        print(f"CO one-knob failed: {exc}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
