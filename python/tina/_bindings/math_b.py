import ctypes

from .._lib import math as _lib
from ._types import Mat3, Vec3, Mat4

# Vec3 construction
vec3 = _lib.vec3
vec3.restype = Vec3
vec3.argtypes = [ctypes.c_double, ctypes.c_double, ctypes.c_double]

# Mat3 construction and operations
mat3 = _lib.mat3
mat3.restype = Mat3
mat3.argtypes = [
    ctypes.c_double, ctypes.c_double, ctypes.c_double,
    ctypes.c_double, ctypes.c_double, ctypes.c_double,
    ctypes.c_double, ctypes.c_double, ctypes.c_double,
]

mat3_prod = _lib.mat3_prod
mat3_prod.restype = Mat3
mat3_prod.argtypes = [Mat3, Mat3]

mat3_inverse = _lib.mat3_inverse
mat3_inverse.restype = Mat3
mat3_inverse.argtypes = [Mat3]

# Eigen decomposition (returns Bool)
mat3_eigen = _lib.mat3_eigen
mat3_eigen.restype = ctypes.c_int
mat3_eigen.argtypes = [
    Mat3,
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(Vec3),
    ctypes.POINTER(Vec3),
    ctypes.POINTER(Vec3),
]

# Matrix SVD (dynamic Matrix* signatures)
matrix_svd = _lib.matrix_svd
matrix_svd.restype = None
matrix_svd.argtypes = [
    ctypes.c_void_p,  # Matrix *A
    ctypes.c_void_p,  # Matrix *U
    ctypes.POINTER(ctypes.c_double),  # double *s
    ctypes.c_void_p,  # Matrix *V
]

# Simplex minimisation
simplexmin = _lib.simplexmin
simplexmin.restype = ctypes.c_double
simplexmin.argtypes = [
    ctypes.c_void_p,  # double (*func)(double *)
    ctypes.POINTER(ctypes.c_double),  # x0
    ctypes.c_int,  # n
    ctypes.c_double,  # tol
    ctypes.c_int,  # maxiter
]
