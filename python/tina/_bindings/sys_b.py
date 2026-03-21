import ctypes

from .._lib import sys_lib as _lib
from ._types import Imrect_p, Imregion_p

# ralloc / rfree
ralloc = _lib.ralloc
ralloc.restype = ctypes.c_void_p
ralloc.argtypes = [ctypes.c_uint]

rfree = _lib.rfree
rfree.restype = None
rfree.argtypes = [ctypes.c_void_p]

# Image allocation / copy / free
im_alloc = _lib.im_alloc
im_alloc.restype = Imrect_p
im_alloc.argtypes = [ctypes.c_int, ctypes.c_int, Imregion_p, ctypes.c_int]

im_copy = _lib.im_copy
im_copy.restype = Imrect_p
im_copy.argtypes = [Imrect_p]

im_free = _lib.im_free
im_free.restype = None
im_free.argtypes = [Imrect_p]

# Pixel get/set (integer & float)
im_put_pix = _lib.im_put_pix
im_put_pix.restype = None
im_put_pix.argtypes = [ctypes.c_int, Imrect_p, ctypes.c_int, ctypes.c_int]

im_put_pixf = _lib.im_put_pixf
im_put_pixf.restype = None
im_put_pixf.argtypes = [ctypes.c_double, Imrect_p, ctypes.c_int, ctypes.c_int]

im_get_pix = _lib.im_get_pix
im_get_pix.restype = ctypes.c_int
im_get_pix.argtypes = [Imrect_p, ctypes.c_int, ctypes.c_int]

im_get_pixf = _lib.im_get_pixf
im_get_pixf.restype = ctypes.c_double
im_get_pixf.argtypes = [Imrect_p, ctypes.c_int, ctypes.c_int]

# Error / format redirection
ERROR_CB = ctypes.CFUNCTYPE(None, ctypes.c_char_p)

error_set_print = _lib.error_set_print
error_set_print.restype = None
error_set_print.argtypes = [ERROR_CB]

format_set_print = _lib.format_set_print
format_set_print.restype = None
format_set_print.argtypes = [ERROR_CB]
