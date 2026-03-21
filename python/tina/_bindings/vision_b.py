import ctypes

from .._lib import vision as _lib
from ._types import Imrect_p, Camera_p, Vec2, Vec3

# Image filters
imf_gauss = _lib.imf_gauss
imf_gauss.restype = Imrect_p
imf_gauss.argtypes = [Imrect_p, ctypes.c_double, ctypes.c_double]

canny = _lib.canny
canny.restype = Imrect_p
canny.argtypes = [
    Imrect_p,
    ctypes.c_double,  # sigma
    ctypes.c_double,  # precision
    ctypes.c_double,  # lowthres
    ctypes.c_double,  # upthres
    ctypes.c_int,     # lengththres
]

er_find_edge_strings = _lib.er_find_edge_strings
er_find_edge_strings.restype = None
er_find_edge_strings.argtypes = [Imrect_p]

# Camera model
cam_alloc = _lib.cam_alloc
cam_alloc.restype = Camera_p
cam_alloc.argtypes = [ctypes.c_int]

cam_make = _lib.cam_make
cam_make.restype = Camera_p
cam_make.argtypes = [
    ctypes.c_uint,        # type
    ctypes.c_void_p,      # Transform3*
    ctypes.c_double,      # f
    ctypes.c_double,      # pix
    ctypes.c_double,      # ax
    ctypes.c_double,      # ay
    ctypes.c_double,      # cx
    ctypes.c_double,      # cy
    ctypes.c_int,         # width
    ctypes.c_int,         # height
]

cam_free = _lib.cam_free
cam_free.restype = None
cam_free.argtypes = [Camera_p]

cam_proj = _lib.cam_proj
cam_proj.restype = Vec2
cam_proj.argtypes = [Camera_p, Vec3]
