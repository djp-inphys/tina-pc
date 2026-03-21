import os
from typing import Tuple

import numpy as np

from .._bindings import sys_b, vision_b

# Default vartype for grayscale images (override via env if needed)
DEFAULT_VARTYPE = int(os.environ.get("TINA_DEFAULT_VTYPE", "0"))


def from_numpy(arr: np.ndarray, vtype: int = DEFAULT_VARTYPE) -> Tuple[object, Tuple[int, int]]:
    """Allocate an Imrect and copy pixel data from a numpy array (grayscale)."""
    arr = np.asarray(arr)
    if arr.ndim != 2:
        raise ValueError("Only 2D grayscale arrays are supported")
    h, w = arr.shape
    im = sys_b.im_alloc(int(h), int(w), None, int(vtype))
    if not im:
        raise RuntimeError("im_alloc failed")

    for i in range(h):
        for j in range(w):
            sys_b.im_put_pixf(float(arr[i, j]), im, i, j)

    return im, (h, w)


def to_numpy(im_ptr, shape: Tuple[int, int]) -> np.ndarray:
    """Convert an Imrect pointer back to a numpy array using cached shape."""
    h, w = shape
    out = np.zeros((h, w), dtype=np.float64)
    for i in range(h):
        for j in range(w):
            out[i, j] = sys_b.im_get_pixf(im_ptr, i, j)
    return out


def gaussian_smooth(arr: np.ndarray, sigma: float, precision: float = 0.01) -> np.ndarray:
    im, shape = from_numpy(arr)
    try:
        out_ptr = vision_b.imf_gauss(im, float(sigma), float(precision))
        if not out_ptr:
            raise RuntimeError("imf_gauss returned NULL")
        return to_numpy(out_ptr, shape)
    finally:
        sys_b.im_free(im)


def canny(arr: np.ndarray, sigma: float = 1.0, precision: float = 0.01,
          low: float = 0.5, high: float = 1.5, length_thresh: int = 10) -> np.ndarray:
    im, shape = from_numpy(arr)
    try:
        out_ptr = vision_b.canny(im, float(sigma), float(precision), float(low), float(high), int(length_thresh))
        if not out_ptr:
            raise RuntimeError("canny returned NULL")
        return to_numpy(out_ptr, shape)
    finally:
        sys_b.im_free(im)
