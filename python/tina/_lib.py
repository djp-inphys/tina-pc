import ctypes
import os
import pathlib
from typing import Optional


def _candidate_paths(name: str):
    """Yield candidate shared library paths for the given module name."""
    lib_dir = pathlib.Path(os.environ.get("TINA_LIB_DIR", "build"))
    platform_names = [
        f"libtina_{name}.so",
        f"libtina_{name}.dylib",
        f"tina_{name}.dll",
    ]
    for filename in platform_names:
        candidate = lib_dir / filename
        if candidate.exists():
            yield candidate


def load_library(name: str, handle_errors: bool = True) -> Optional[ctypes.CDLL]:
    """Load a TINA shared library by module name (math, sys, vision, file, serialise)."""
    for candidate in _candidate_paths(name):
        try:
            return ctypes.CDLL(str(candidate))
        except OSError:
            continue
    if handle_errors:
        raise OSError(f"Cannot find or load shared library for tina_{name}")
    return None


math = load_library("math")
sys_lib = load_library("sys")
vision = load_library("vision")
file_lib = load_library("file")
serialise = load_library("serialise", handle_errors=False)
