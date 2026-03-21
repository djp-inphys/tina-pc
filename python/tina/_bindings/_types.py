import ctypes


class Vec2(ctypes.Structure):
    _fields_ = [("el", ctypes.c_double * 2)]


class Vec3(ctypes.Structure):
    _fields_ = [("el", ctypes.c_double * 3)]


class Vec4(ctypes.Structure):
    _fields_ = [("el", ctypes.c_double * 4)]


class Mat3(ctypes.Structure):
    _fields_ = [("el", ctypes.c_double * 9)]


class Mat4(ctypes.Structure):
    _fields_ = [("el", ctypes.c_double * 16)]


# Opaque pointer aliases for handle-like TINA structs
Imrect_p = ctypes.c_void_p
Imregion_p = ctypes.c_void_p
Camera_p = ctypes.c_void_p
List_p = ctypes.c_void_p
Matrix_p = ctypes.c_void_p
