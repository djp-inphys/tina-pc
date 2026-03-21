"""TINA Python bindings and CLI scaffolding."""

from ._lib import math as _lib_math, sys_lib as _lib_sys, vision as _lib_vision, file_lib as _lib_file  # noqa: F401
from ._bindings import sys_b  # noqa: F401
import ctypes

__all__ = ["_lib_math", "_lib_sys", "_lib_vision", "_lib_file"]


# Redirect TINA's internal error/format print hooks into Python exceptions
_ERROR_CB = ctypes.CFUNCTYPE(None, ctypes.c_char_p)


@_ERROR_CB
def _error_handler(msg):
    decoded = msg.decode() if isinstance(msg, (bytes, bytearray)) else str(msg)
    raise RuntimeError(decoded)


sys_b.error_set_print(_error_handler)
sys_b.format_set_print(_error_handler)
