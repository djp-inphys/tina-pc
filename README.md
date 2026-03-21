# TINA PC Library

> **TINA Is Not Abstract** — Windows PC port of the TINA machine vision library

The TINA library is a comprehensive, foundational **ANSI C toolkit** for computer vision and machine vision, originally developed at the **University of Sheffield, UK**. This repository (`tina-pc`) is the **Windows PC port**, providing the full TINA algorithm suite as a set of Windows DLLs (and Unix static archives). It covers everything from linear algebra and numerical methods to edge detection, stereo reconstruction, camera calibration, and Kalman-filter-based geometric constraint solving.

---

## Table of Contents

- [Overview](#overview)
- [Repository Structure](#repository-structure)
- [Tech Stack](#tech-stack)
- [Modules](#modules)
  - [math — Mathematics Library](#math--mathematics-library)
  - [sys — System Utilities Library](#sys--system-utilities-library)
  - [vision — Computer Vision Library](#vision--computer-vision-library)
  - [file — File I/O Library](#file--file-io-library)
  - [serialise — Serialization Library](#serialise--serialization-library)
- [Key Data Structures](#key-data-structures)
- [API Reference](#api-reference)
  - [Camera Operations](#camera-operations)
  - [Image Processing](#image-processing)
  - [Edge Detection](#edge-detection)
  - [Stereo Vision & Matching](#stereo-vision--matching)
  - [Geometric Statistics & Constraint Solving](#geometric-statistics--constraint-solving)
  - [Numerical Methods](#numerical-methods)
  - [Matrix Algebra](#matrix-algebra)
  - [File I/O](#file-io)
- [Build Instructions](#build-instructions)
  - [Windows (NMAKE)](#windows-nmake)
  - [Windows (Visual Studio)](#windows-visual-studio)
  - [Unix / Linux (GCC)](#unix--linux-gcc)
- [Build Outputs](#build-outputs)
- [Module Dependencies](#module-dependencies)
- [Include Paths & Environment](#include-paths--environment)
- [Compiler Flags](#compiler-flags)
- [DLL Export Definitions](#dll-export-definitions)
- [Notable Design Aspects](#notable-design-aspects)

---

## Overview

TINA is a **linkable C library**, not a standalone application. It is designed to be linked into larger vision applications — typically MFC-based Windows GUI workbenches or Unix command-line programs. The library exposes approximately **1,000+ exported functions** across five modules and encompasses ~400 C source files.

**Core capabilities:**

| Domain | Highlights |
|---|---|
| Linear algebra | SVD, Cholesky, LU, eigenvalue, Gram-Schmidt, matrix inversion |
| Numerical methods | Simplex minimization, Newton-Raphson, dynamic programming, Fourier |
| Geometry | 2D/3D points, lines, planes, conics, splines, quaternions |
| Image processing | Gaussian blur, Canny edge, Gabor, morphology, warping, rectification |
| Camera model | Pinhole + radial distortion; Tsai and simplex calibration |
| Stereo vision | Epipolar matching, DP stereo, string/corner matching |
| Constraint solving | Kalman filter, EKF, NLSQ, geometric state vectors |
| File formats | FFG, IFF, AIFF, WISP, raw binary, TINA edge/geometry files |
| Serialization | Typed-struct serialisation/deserialisation |

---

## Repository Structure

```
tina-pc/
├── math/                   # Mathematics library
│   ├── *.c                 # ~90 source files
│   ├── math.mak            # NMAKE build file (Debug/Release)
│   ├── math.dsp            # MS Developer Studio 6 project
│   ├── math.vcproj         # MS Visual C++ 2005+ project
│   ├── math.def            # DLL export definitions
│   └── mssccprj.scc        # Visual SourceSafe metadata
│
├── sys/                    # System utilities library
│   ├── *.c                 # ~50 source files
│   ├── sys.mak             # NMAKE build file
│   ├── sys.dsp             # MS Developer Studio 6 project
│   ├── sys.def             # DLL export definitions
│   └── mssccprj.scc
│
├── vision/                 # Computer vision library
│   ├── *.c                 # ~180+ source files
│   ├── vision.mak          # NMAKE build file
│   ├── vision.dsp          # MS Developer Studio 6 project
│   ├── vision.def          # DLL export definitions
│   └── mssccprj.scc
│
├── file/                   # File I/O library
│   ├── *.c                 # ~25 source files
│   ├── file.sln            # MS Visual Studio solution
│   ├── file.vcproj         # MS Visual C++ 2005+ project
│   ├── file.dsp            # MS Developer Studio 6 project
│   ├── file.def            # DLL export definitions
│   └── mssccprj.scc
│
├── serialise/              # Serialization library
│   ├── *.c / *.C           # ~15 source files
│   ├── serialise.mak       # NMAKE build file
│   ├── serialise.dsp       # MS Developer Studio 6 project
│   └── Makefile            # GNU Makefile (Unix/GCC)
│
└── include/                # Shared header files
    ├── sys/
    │   └── param.h         # System parameter definitions
    └── values.h            # Global constant definitions
```

---

## Tech Stack

| Category | Details |
|---|---|
| **Language** | ANSI C (`__STRICT_ANSI__`) |
| **Platform** | Windows Win32 x86 (primary); Unix/Linux (via GNU Make) |
| **Windows compiler** | Microsoft Visual C++ (`cl.exe`) |
| **Unix compiler** | GCC (`gcc`) |
| **Windows build system** | NMAKE (`.mak`) + MS Developer Studio 6 (`.dsp`) + MS Visual C++ (`.vcproj`/`.sln`) |
| **Unix build system** | GNU Make (`Makefile`) |
| **Windows output** | DLLs (`.dll`) + import libraries (`.lib`) |
| **Unix output** | Static archives (`.a`) |
| **MFC** | Microsoft Foundation Classes (`_AFXDLL`) — Windows DLL builds |
| **Source control (historical)** | Visual SourceSafe (`.scc` files present) |

**Preprocessor defines used in Windows builds:**

| Define | Purpose |
|---|---|
| `WIN32` | Target platform |
| `_WINDOWS` | Windows subsystem |
| `_WINDLL` | Building a DLL |
| `_AFXDLL` / `_AFXEXT` | MFC DLL linkage |
| `_COMPLEX_DEFINED` | Suppress conflicting `complex` type |
| `__STRICT_ANSI__` | Enforce ANSI C compliance |
| `_PCC` | TINA PC-specific code path |
| `_MBCS` | Multi-byte character set |
| `NDEBUG` | Release builds (no assertions) |

---

## Modules

### `math/` — Mathematics Library

The foundational linear algebra and numerical methods module. Compiles to `math.dll` (Windows) or `libtinamath.a` (Unix).

#### Fixed-size matrix/vector algebra
| File(s) | Description |
|---|---|
| `mat2.c`, `mat3.c`, `mat4.c` | 2×2, 3×3, 4×4 fixed-size double matrices: alloc, copy, multiply, transpose, invert, determinant |
| `vec2.c`, `vec3.c`, `vec4.c` | 2D, 3D, 4D double vectors: arithmetic, dot product, cross product, normalise |
| `ivec.c` | Integer vectors |
| `mat.c` | General fixed-matrix utilities |

#### Dynamic matrices and vectors
| File(s) | Description |
|---|---|
| `matrix_alloc.c`, `matrix_copy.c` | Heap-allocated general matrices |
| `matrix_arith.c` | Add, subtract, multiply, scale |
| `matrix_svd.c`, `svd.c`, `mat_svd.c` | Singular value decomposition (multiple implementations) |
| `mat_chol.c`, `cholesky.c` | Cholesky decomposition |
| `mat_lu.c` | LU decomposition |
| `mat_eigen.c`, `eigen.c` | Eigenvalue/eigenvector decomposition |
| `mat_gs.c` | Gram-Schmidt orthogonalisation |
| `mat_fmt.c` | Matrix pretty-print / formatting |
| `vec.c` | Dynamic vectors |

#### Transformations and rotations
| File(s) | Description |
|---|---|
| `rot2.c`, `rot3.c` | 2D and 3D rotation matrices |
| `transform2.c`, `transform3.c` | 2D and 3D rigid-body transforms (rotation + translation) |
| `quat.c` | Quaternion representation and conversion |

#### Geometry
| File(s) | Description |
|---|---|
| `geom2.c`, `geom3.c` | Generic 2D/3D geometric primitives |
| `proj2.c`, `proj3.c` | 2D/3D projective geometry |
| `ipos.c` | Integer positions |
| `hull2.c`, `hull3.c` | 2D/3D convex hull computation |
| `polygon.c` | Polygon utilities |
| `bres_line.c`, `symm_line.c` | Bresenham line drawing |

#### Numerical methods
| File(s) | Description |
|---|---|
| `solve.c` | Linear system solver |
| `eqn.c` | Polynomial equation solving |
| `univmin.c` | 1D minimisation (golden section / Brent) |
| `simplexmin.c` | Nelder-Mead simplex minimisation |
| `newt_raph.c` | Newton-Raphson root-finding |
| `dprog.c` | Dynamic programming |
| `fourier.c` | Fourier transform utilities |
| `pentadiag.c` | Pentadiagonal system solver |
| `covar.c` | Covariance matrix utilities |

#### Splines
| File(s) | Description |
|---|---|
| `ics.c` | Interpolating cubic splines |

#### Utilities
| File(s) | Description |
|---|---|
| `rand.c` | Random number generation |
| `math_util.c` | Miscellaneous math helpers |
| `fmt_shape.c`, `fmt_vtype.c` | Shape/type formatting for display |

---

### `sys/` — System Utilities Library

Low-level memory management, data structures, I/O, and image representation. Compiles to `sys.dll` (Windows) or `libtinautils.a` (Unix). Exports 400+ functions.

#### Memory management
| File(s) | Description |
|---|---|
| `ralloc.c`, `rfree.c` | Reference-counted allocation/deallocation |
| `dynamic.c`, `ndynamic.c`, `vdynamic.c` | Dynamic arrays (typed, vector-style) |
| `ts_save_load.c`, `ts_ndynamic.c`, `tsfree.c` | Typed-struct (TINA type-safe) memory |

#### Image representation
| File(s) | Description |
|---|---|
| `image.c` | `imrect` struct: width, height, pixel type, row-pointer buffer. Allocation, free, copy |
| `region.c` | Image region (ROI) utilities |

#### Data structures
| File(s) | Description |
|---|---|
| `lists.c`, `ddlists.c` | Singly and doubly linked lists |
| `strings.c`, `ddstr.c` | String lists and double-ended string lists |
| `reclist.c` | Record lists |
| `proplist.c` | Property lists (key-value association) |
| `graph.c`, `cliques.c` | Graph data structure and clique finding |
| `sort.c` | Sorting utilities |
| `pair.c` | Pair (2-element tuple) utility |

#### I/O and formatting
| File(s) | Description |
|---|---|
| `io.c` | Generic I/O abstraction |
| `imput.c`, `imget.c` | Image put/get utilities |
| `imfloatfns.c` | Float image I/O helpers |
| `pipe_read.c` | Pipe-based data input |
| `format.c`, `tsprint.c`, `mprintf.c` | Formatted output, typed-struct printing |

#### Serialisation
| File(s) | Description |
|---|---|
| `serialise.c`, `deserialise.c` | TINA typed-struct serialise/deserialise to file |

#### Type system
| File(s) | Description |
|---|---|
| `tstruct_info.c` | Run-time type information for TINA structs |
| `var.c` | Typed variable utilities |
| `tina_int.c` | TINA integer type definitions |

#### Utility
| File(s) | Description |
|---|---|
| `error.c`, `message.c`, `help.c` | Error reporting, message output, help text |
| `null.c` | Null-safe pointer utilities |
| `swap.c` | Byte-swap (endianness) |
| `label.c` | Label/tag utilities |
| `icopy.c`, `fcopy.c`, `ccopy.c`, `dcopy.c` | Typed array copy (int, float, char, double) |
| `string.c` | String manipulation |
| `util.c` | General-purpose utilities |

---

### `vision/` — Computer Vision Library

The main computer vision module — the largest module with 180+ source files. Compiles to `vision.dll` (Windows) or `libtinavision.a` (Unix). Exports 600+ functions. Depends on `math` and `sys`.

#### Image processing
| File(s) | Description |
|---|---|
| `im_create.c` | Create synthetic images: checkerboard, ellipses, noise |
| `im_gauss.c`, `im_smooth.c` | Gaussian and general smoothing |
| `im_conv_1d.c` | 1D separable convolution |
| `im_grad.c`, `im_deriv.c` | Gradient and derivative computation |
| `im_lsf.c` | Least-squares-fit smooth |
| `im_scale.c` | Image scaling / zoom |
| `im_thresh.c` | Thresholding |
| `im_rank.c` | Rank (order-statistic) filter |
| `im_morph.c` | Morphological operations: dilation, erosion |
| `im_warp.c` | Image warping and rectification |
| `im_gabor.c` | Gabor filter (real & complex) |
| `im_median.c` | Median filter |
| `im_shade.c`, `im_surf.c` | Shading/surface image processing |
| `im_apply.c`, `im_combine.c` | Apply functions to images; combine image pairs |
| `im_sample.c`, `im_ptr.c` | Pixel sampling and pointer arithmetic |
| `canny.c` | Canny edge detector (full pipeline) |
| `nonmax.c` | Non-maximum suppression |

#### Edge detection and representation
| File(s) | Description |
|---|---|
| `edge.c` | `Edge` struct: position, orientation, strength, property list |
| `edge_strings.c` | Edge string (linked edge chain) construction |
| `edgerect.c` | Edge raster — 2D array of edge lists |
| `linkedges.c` | Edge linking algorithm |
| `bnd_region.c` | Boundary region computation from edges |

#### 2D geometry
| File(s) | Description |
|---|---|
| `line2.c`, `line2_fmt.c`, `line2_trns.c`, `line2_rect.c`, `line2_coln.c` | 2D line: representation, format, transform, rectify, collinearity |
| `point2.c`, `pnt2_fmt.c`, `pnt2_rect.c` | 2D point: representation, format, rectify |
| `fitline2.c` | Fit line to 2D point set |
| `conic.c`, `conic2.c`, `conic3.c` | General conic section (ellipse, hyperbola, parabola) |
| `con_stat.c`, `con_util.c`, `con_klmn.c`, `conic_5pt.c` | Conic statistics, utilities, Kalman update, 5-point fit |
| `circprox.c`, `conicprox.c` | Circle and conic proximity |
| `curvprox.c`, `curvature.c`, `curvinvar.c` | Curve proximity, curvature, invariants |
| `str2.c`, `string2.c` | 2D string (edge/point chains) |
| `ucbs2.c`, `knots.c`, `splines.c` | Uniform cubic B-splines and knot vectors |
| `polyprox.c`, `linearprox.c` | Polygonal and linear approximation |

#### 3D geometry
| File(s) | Description |
|---|---|
| `line3.c`, `line3_fmt.c`, `line3_trns.c`, `fitline3.c` | 3D line: representation, format, transform, fit |
| `point3.c`, `pnt3_fmt.c`, `pnt3_trans.c` | 3D point: representation, format, transform |
| `plane.c`, `plane_fmt.c`, `transplane.c` | 3D plane: representation, format, transform |
| `cone.c`, `cone_trans.c` | 3D cone: representation and transform |
| `transf3.c`, `tr3_fmt.c` | 3D rigid-body transform: representation, format |
| `conic3.c` | 3D conic section |
| `es_string3.c`, `str3_tris.c`, `string3.c` | 3D edge strings and triangulation |
| `affine_cv.c` | Affine curve fitting |

#### Camera model and calibration
| File(s) | Description |
|---|---|
| `camera.c` | `Camera` struct: focal length `f`, aspect `ax`/`ay`, principal point `cx`/`cy`, pixel size, projection matrices `cam_to_im` / `im_to_cam`, 3D transform |
| `cam_aim.c` | Camera aiming / look-at |
| `cam_conv.c` | Camera parameter conversion |
| `cam_dstrt.c` | Radial distortion model and correction |
| `cam_error.c` | Camera calibration error metrics |
| `proj.c`, `par_proj.c`, `par_cam.c` | Perspective and parallel projection |
| `rect.c` | Image rectification |
| `cal_util.c` | Calibration utilities |
| `cal_smplx.c`, `ecal_smplx.c`, `scal_smplx.c` | Simplex-based camera calibration (mono, stereo, essential matrix) |
| `cal_tsai.c` | Tsai camera calibration algorithm |
| `h_v_lines.c` | Horizontal/vertical calibration lines |
| `grid_match.c` | Calibration grid matching |
| `conv_quat.c` | Quaternion-based camera orientation conversion |

#### Stereo vision and feature matching
| File(s) | Description |
|---|---|
| `match_epi.c` | Epipolar-guided edge string matching |
| `match_dp.c` | Dynamic programming stereo matching |
| `match_str.c` | String-to-string matching |
| `match_es.c` | Edge string matching |
| `matcher.c`, `matchable.c` | Abstract matcher framework |
| `match.c`, `match_supp.c` | Match struct and support computation |
| `match_cnr.c` | Corner matching |
| `disp_hist.c`, `disp_range.c` | Disparity histogram and range |
| `select.c`, `choose.c` | Match selection and voting |
| `support.c`, `supp_fig.c` | Match support figures |
| `setindex.c` | Set-indexed data access |
| `mat_fast.c` | Fast matrix operations for matching |
| `dp_mlist.c`, `dynamic.c` | DP match list and dynamic programming for matching |
| `corner.c`, `s_mat_cnr.c`, `t_mat_cnr.c`, `st_mat_cnr.c` | Corner detection and matrix-based corner handling |

#### Geometric statistics and constraint solving
| File(s) | Description |
|---|---|
| `state.c`, `state_fmt.c` | Geometric state vector: representation and formatting |
| `state_geom.c`, `state_tina.c` | State geometry conversion |
| `state_add.c`, `state_crct.c` | State accumulation and correction |
| `state_hull.c` | Convex hull in state space |
| `state_on.c`, `state_par.c`, `state_orth.c`, `state_extd.c` | State constraints: on-surface, parallel, orthogonal, extended |
| `gstat_pnt2.c`, `gstat_pnt3.c` | Geometric statistics for 2D/3D points |
| `gstat_ln3.c`, `gstat_pln.c` | Geometric statistics for 3D lines and planes |
| `gstat_cam.c`, `gstat_geom.c` | Camera and geometry statistics |
| `gstat_sclr.c`, `gstat_tf3.c` | Scalar and transform statistics |
| `kalman.c` | Kalman filter implementation |
| `basis.c` | Basis vector computation |

#### Splines and active contours
| File(s) | Description |
|---|---|
| `kws.c`, `kws_run.c` | KwSnake: energy-minimising active contour (snake) |

#### Indexing
| File(s) | Description |
|---|---|
| `sindex.c` | Spatial index (2D grid hash) |
| `windex.c` | Weighted index |
| `rindex.c` | Range index |
| `wx_lists.c` | Weighted indexed lists |
| `set_findex.c` | Set feature index |

#### Miscellaneous vision
| File(s) | Description |
|---|---|
| `scalar.c` | Labeled scalar data structure |
| `label.c` | Labeling / region labeling |
| `prof1.c` | 1D intensity profile extraction |
| `pwrte.c` | Pairwise table entries for match scoring |
| `mat_match.c`, `mat_geom.c`, `mat_con.c`, `mat_cliche.c` | Matrix-based matching, geometry, constraints, and clichés |
| `iso_error.c` | Isotropic error model |
| `geom_alloc.c`, `geom_copy.c`, `geom_error.c` | Generic geometry allocation/copy/error |
| `geom_fmt.c`, `geom_free.c`, `geom_hull.c` | Generic geometry format/free/hull |
| `geom_label.c`, `geom_negate.c`, `geom_props.c`, `geom_trans.c` | Generic geometry operations |

---

### `file/` — File I/O Library

File I/O module for TINA-specific and standard image/data formats. Compiles to `file.dll` (Windows). Depends on `vision`, `math`, and `sys`.

| File(s) | Description |
|---|---|
| `raw_io.c`, `raw_read_fd.c` | Raw binary image I/O |
| `ffg_read.c`, `ffg_write.c` | TINA FFG (Feature File Group) format read/write |
| `ffg_new_read.c`, `ffg_new_wrt.c` | Extended FFG format read/write |
| `iff_io.c` | IFF image format |
| `aiff_io.c` | AIFF image format |
| `wisp_write.c` | WISP format output |
| `edges_read.c`, `edges_w.c` | Edge data file read/write |
| `geom2_read.c`, `geom2_wrt.c` | 2D geometry file read/write |
| `geom3_read.c`, `geom3_wrt.c` | 3D geometry file read/write |
| `cam_io.c`, `cam_g3_rd.c` | Camera parameter file I/O |
| `covar_r.c`, `covar_w.c` | Covariance matrix file read/write |
| `distort_r.c`, `distort_w.c` | Distortion parameter file read/write |
| `matrix_r.c`, `matrix_w.c` | General matrix file read/write |
| `view_prms.c` | View parameter file I/O |
| `file_io.c`, `file_util.c` | General file utilities and helpers |

---

### `serialise/` — Serialization Library

Typed serialisation of TINA data structures to/from files. Primarily targeted at Unix (GNU Makefile), though a `.dsp`/`.mak` is also present. Compiles to `libtinaserialise.a` (Unix) or `serialise.dll` (Windows).

| File(s) | Description |
|---|---|
| `ddlist.c`, `list.c` | Double and single linked list serialisation |
| `matrix.c` | Matrix serialisation |
| `narray.c`, `nvector.c`, `vector.c` | N-dimensional array and vector serialisation |
| `prop.c` | Property list serialisation |
| `rindex.c`, `windex.c` | Index serialisation |
| `imrect.c`, `imstack.c` | Image rect and image stack serialisation |
| `ts_set.c` | Typed struct set serialisation |
| `edge_conn.c` / `EDGE_CON.C` | Edge connectivity serialisation |

---

## Key Data Structures

| Type | Source File | Description |
|---|---|---|
| `Camera` | `vision/camera.c` | Pinhole camera model: focal length `f`, aspect ratio `ax`/`ay`, principal point `cx`/`cy`, pixel size, 3×3 projection matrices `cam_to_im`/`im_to_cam`, 3D rigid-body transform `transf` |
| `Transform3` | `math/transform3.c` | 3D rigid-body transform: 3×3 rotation matrix + 3-vector translation |
| `Mat3` | `math/mat3.c` | 3×3 double matrix (fixed-size, stack-allocated) |
| `Vec2` / `Vec3` / `Vec4` | `math/vec2.c` etc. | 2D/3D/4D double column vectors |
| `imrect` (Image) | `sys/image.c` | Raster image: width, height, pixel type enum, row-pointer buffer for arbitrary pixel types |
| `Edge` | `vision/edge.c` | Image edge element: 2D position, orientation angle, gradient strength, property list |
| `Line2` / `Line3` | `vision/line2.c`, `line3.c` | Geometric line (2D: normal+offset form; 3D: point+direction form) |
| `Conic` | `vision/conic.c` | General conic section: 6-coefficient matrix form; supports ellipse, hyperbola, parabola |
| `Plane` | `vision/plane.c` | 3D plane: unit normal + signed distance from origin |
| `Point2` / `Point3` | `vision/point2.c`, `point3.c` | Labeled geometric points with covariance and property list |
| `Scalar` | `vision/scalar.c` | Labeled scalar value with uncertainty |
| `State` | `vision/state.c` | Geometric state vector for Kalman/EKF constraint solving |
| `Match` | `vision/match.c` | Feature-to-feature correspondence with support score and weight |

---

## API Reference

### Camera Operations

```c
/* Camera lifecycle */
Camera *cam_make(void);
Camera *cam_alloc(void);
Camera *cam_copy(Camera *cam);
void    cam_free(Camera *cam);

/* Projection */
Vec2    cam_proj(Camera *cam, Vec3 p);       /* 3D point -> 2D image coords */
Vec3    cam_ray(Camera *cam, Vec2 p);        /* 2D image coords -> 3D ray */

/* Distortion */
void    radial_distort(Camera *cam, double *x, double *y);
void    radial_correct(Camera *cam, double *x, double *y);
void    cam_correct(Camera *cam, imrect *im);

/* Rectification */
void    cam_comp_default_rects(Camera *left, Camera *right, ...);

/* Calibration */
void    cam_cal_tsai(Camera *cam, List *pts2d, List *pts3d);
void    cam_cal_simplex(Camera *cam, List *pts2d, List *pts3d);
void    cam_cal_stereo_simplex(Camera *left, Camera *right, ...);
```

### Image Processing

```c
/* Smoothing */
imrect *imf_gauss(imrect *im, double sigma);
imrect *imf_smooth(imrect *im, double *kernel, int ksize);
imrect *imf_conv_1d(imrect *im, double *kernel, int ksize, int dir);

/* Gradients and derivatives */
imrect *imf_grad_h(imrect *im);              /* horizontal gradient */
imrect *imf_grad_v(imrect *im);              /* vertical gradient */
imrect *imf_deriv(imrect *im, int order);    /* nth derivative */
imrect *imf_laplacian(imrect *im);
imrect *imf_sqrgrad(imrect *im);

/* Filtering */
imrect *imf_median(imrect *im, int radius);
imrect *imf_rank(imrect *im, int rank, int radius);
imrect *im_gabor(imrect *im, double freq, double orient, double sigma);

/* Morphology */
imrect *imf_dilate(imrect *im, int radius);
imrect *imf_erode(imrect *im, int radius);

/* Warping */
imrect *imf_warp(imrect *im, Transform2 *t);
imrect *im_rectify(imrect *im, Camera *cam);

/* Thresholding and scaling */
imrect *imf_thresh(imrect *im, double low, double high);
imrect *imf_scale(imrect *im, double sx, double sy);
```

### Edge Detection

```c
/* Canny pipeline */
List   *canny(imrect *im, double sigma, double low, double high);

/* Non-maximum suppression */
imrect *nonmaxsup(imrect *grad_mag, imrect *grad_dir);

/* Edge string construction */
List   *edge_strings(edgerect *er, double min_length);
edgerect *make_edgerect(imrect *im);
```

### Stereo Vision & Matching

```c
/* Epipolar matching */
List *es_match_epi_pair(List *left_strings, List *right_strings,
                        Camera *left_cam, Camera *right_cam, ...);

/* Dynamic programming stereo */
List *match_epi_dprog(List *left, List *right, Camera *lcam, Camera *rcam,
                      double disp_range, double occ_cost);

/* String matching */
List *es_match_string(Tstring *s1, Tstring *s2, Camera *c1, Camera *c2);
List *es_choose_string_matches(List *candidates, double threshold);

/* Corner matching */
List *stereo_corner_match(List *left_corners, List *right_corners,
                          Camera *lcam, Camera *rcam);
List *get_corner_matches(List *corners, imrect *left, imrect *right);

/* Kalman filter correction */
void kalman(State *state, double *obs, double *obs_cov, ...);
```

### Geometric Statistics & Constraint Solving

```c
/* State vector operations */
State *state_make(int dim);
State *state_geom_make(Geom *g, Camera *cam);
void   state_add(State *s, double *measurement, double *cov);
void   state_correct(State *s);

/* Geometric statistics */
void gstat_pnt2(Point2 *p, State *s);          /* add 2D point to state */
void gstat_pnt3(Point3 *p, State *s);          /* add 3D point to state */
void gstat_ln3(Line3 *l, State *s);            /* add 3D line to state */
void gstat_pln(Plane *pl, State *s);           /* add plane to state */
void gstat_cam(Camera *cam, State *s);         /* add camera to state */

/* Constraints */
void state_on(State *s, Geom *surface);        /* on-surface constraint */
void state_par(State *s, Vec3 dir);            /* parallel constraint */
void state_orth(State *s, Vec3 dir);           /* orthogonality constraint */
```

### Numerical Methods

```c
/* Minimisation */
double simplexmin(double (*func)(double *), double *x0, int n,
                  double tol, int maxiter);
double univmin(double (*f)(double), double a, double b, double tol);

/* Root finding */
void newton_raphson(double (*f)(double), double (*df)(double),
                    double x0, double tol, double *root);

/* Dynamic programming */
double dprog(double **cost, int m, int n, int *path);

/* Fourier */
void fourier(double *data, int n, int sign);
```

### Matrix Algebra

```c
/* SVD */
void mat_svd(Matrix *A, Matrix *U, double *s, Matrix *V);
void svd(double **a, int m, int n, double *w, double **v);

/* Eigenvalue decomposition */
void mat_eigen(Matrix *A, double *vals, Matrix *vecs);

/* Cholesky decomposition */
int  mat_cholesky(Matrix *A, Matrix *L);

/* LU decomposition */
int  mat_lu(Matrix *A, int *pivot);
void mat_lu_solve(Matrix *LU, int *pivot, double *b, double *x);

/* Gram-Schmidt */
Matrix *mat_gram_schmidt(Matrix *A);
```

### File I/O

```c
/* Raw image I/O */
imrect *raw_read(char *filename, int width, int height, int type);
void    raw_write(char *filename, imrect *im);

/* FFG format (TINA Feature File Group) */
void    ffg_read(char *filename, List **geom2, List **geom3, Camera **cam);
void    ffg_write(char *filename, List *geom2, List *geom3, Camera *cam);

/* Camera parameters */
Camera *cam_read(char *filename);
void    cam_write(char *filename, Camera *cam);

/* Geometry files */
List   *geom2_read(char *filename);
void    geom2_write(char *filename, List *geom);
List   *geom3_read(char *filename);
void    geom3_write(char *filename, List *geom);

/* Matrix files */
Matrix *matrix_read(char *filename);
void    matrix_write(char *filename, Matrix *m);
```

---

## Build Instructions

### Windows (NMAKE)

Build each module from its directory using the provided `.mak` file. The NMAKE build supports both **Debug** (`WinDebug/`) and **Release** (`WinRel/`) configurations.

```cmd
:: Release build
cd math
nmake /f math.mak CFG="math - Win32 Release"

cd ..\sys
nmake /f sys.mak CFG="sys - Win32 Release"

cd ..\vision
nmake /f vision.mak CFG="vision - Win32 Release"

cd ..\file
nmake /f file.mak CFG="file - Win32 Release"

:: Debug build
cd ..\math
nmake /f math.mak CFG="math - Win32 Debug"
```

### Windows (Visual Studio)

Open the relevant `.sln` or `.dsp` project files in Visual Studio (legacy Developer Studio 6 or VS 2005+):

- `file/file.sln` — Visual Studio solution for the `file` module
- `math/math.vcproj` — Visual C++ 2005+ project for `math`
- `vision/vision.dsp` — Developer Studio 6 project for `vision`

Each project also supports **Debug** and **Release** build configurations.

> **Note:** The `.dsp` / `.mak` files contain absolute paths referencing `J:\SRC\...` (the original development machine) and `d:\tina\include` for headers. These paths must be updated to match your local TINA installation.

### Unix / Linux (GCC)

The `serialise` module has a GNU Makefile. Other modules can be adapted for GCC by updating include/lib paths.

```bash
# Set environment variables pointing to your TINA installation
export TINA_INCLUDEDIR=/usr/local/tina/include
export TINA_LIBDIR=/usr/local/tina/lib
export TINA_COMPILE_FLAGS="-O2 -D__STRICT_ANSI__ -D_PCC"

# Build the serialise library
cd serialise
make

# Output: $TINA_LIBDIR/libtinaserialise.a
```

---

## Build Outputs

### Windows

| Module | Debug output | Release output |
|---|---|---|
| `math` | `math/WinDebug/math.dll`, `math.lib` | `math/WinRel/math.dll`, `math.lib` |
| `sys` | `sys/WinDebug/sys.dll`, `sys.lib` | `sys/WinRel/sys.dll`, `sys.lib` |
| `vision` | `vision/WinDebug/vision.dll`, `vision.lib` | `vision/WinRel/vision.dll`, `vision.lib` |
| `file` | `file/WinDebug/file.dll`, `file.lib` | `file/WinRel/file.dll`, `file.lib` |
| `serialise` | `serialise/WinDebug/serialise.dll` | `serialise/WinRel/serialise.dll` |

### Unix

| Module | Output |
|---|---|
| `math` | `$(TINA_LIBDIR)/libtinamath.a` |
| `sys` | `$(TINA_LIBDIR)/libtinautils.a` |
| `vision` | `$(TINA_LIBDIR)/libtinavision.a` |
| `file` | `$(TINA_LIBDIR)/libtinafile.a` |
| `serialise` | `$(TINA_LIBDIR)/libtinaserialise.a` |

---

## Module Dependencies

```
math       ─── (no TINA dependencies)
sys        ─── (no TINA dependencies)
vision     ─── math + sys
file       ─── vision + math + sys
serialise  ─── (minimal; standalone)
```

Link order for a full application:

```
-ltinafile -libtinavision -libtinamath -libtinautils
```

On Windows, ensure `file.dll`, `vision.dll`, `math.dll`, and `sys.dll` are all in the DLL search path.

---

## Include Paths & Environment

The build files expect headers to be found at:

| Path | Contents |
|---|---|
| `d:\tina\include` (Windows) or `$(TINA_INCLUDEDIR)` (Unix) | Main TINA public headers |
| `d:\tina\lib-pc\include` | PC-specific platform headers |
| `tina-pc/include/` | Repository-local headers (`sys/param.h`, `values.h`) |

**Required environment variables (Unix builds):**

| Variable | Purpose |
|---|---|
| `TINA_INCLUDEDIR` | Path to TINA public header directory |
| `TINA_LIBDIR` | Path where built libraries are installed |
| `TINA_COMPILE_FLAGS` | Additional compiler flags |

---

## Compiler Flags

### Windows Release (`cl.exe`)

```
/nologo /G5 /MD /W2 /GX /O1
/D "NDEBUG"
/D "WIN32"
/D "_WINDOWS"
/D "_COMPLEX_DEFINED"
/D "__STRICT_ANSI__"
/D "_PCC"
/D "_AFXDLL"
/D "_MBCS"
/D "_WINDLL"
```

### Windows Debug (`cl.exe`)

```
/nologo /G5 /MDd /W2 /GX /Z7 /Od
/D "_DEBUG"
/D "WIN32"
/D "_WINDOWS"
/D "_COMPLEX_DEFINED"
/D "__STRICT_ANSI__"
/D "_PCC"
/D "_AFXDLL"
/D "_MBCS"
/D "_WINDLL"
```

### Unix (GCC example)

```
-O2 -D__STRICT_ANSI__ -D_PCC -I$(TINA_INCLUDEDIR)
```

---

## DLL Export Definitions

Each Windows DLL has a corresponding `.def` file listing all exported symbols. These are required for building the import library (`.lib`) used by client applications.

| File | Approx. exported symbols |
|---|---|
| `sys/sys.def` | 400+ |
| `vision/vision.def` | 600+ |
| `math/math.def` | 200+ |
| `file/file.def` | 100+ |
| `serialise/serialise.def` | ~50 |

Client applications on Windows must link against the `.lib` import libraries and ensure the corresponding `.dll` files are available at runtime.

---

## Notable Design Aspects

- **ANSI C throughout** — The entire library is written in strict ANSI C (`__STRICT_ANSI__`), making it highly portable across compilers. No C99/C11 features are used.

- **Dual build system** — Each module supports both the legacy MSVC toolchain (Developer Studio 6 `.dsp` + NMAKE `.mak`) and newer Visual Studio (`.vcproj`/`.sln`), as well as GCC via GNU Make. This reflects the library's long development history.

- **MFC integration (Windows)** — The Windows DLL builds are linked against MFC (`_AFXDLL`, `_AFXEXT`), indicating TINA was originally deployed inside MFC-based Windows GUI applications (e.g., the TINA workbench).

- **Typed memory system** — The `sys` module implements a run-time type system (`tstruct_info`, `ts_save_load`) that allows generic serialisation, copy, and free of TINA data structures by type tag.

- **Property lists** — Most TINA data structures (edges, points, lines, etc.) carry an open-ended property list, allowing application code to attach arbitrary annotations without modifying the core structs.

- **No tests** — The repository contains no automated test suite. Validation was historically performed through the TINA workbench GUI application.

- **Historical path artefacts** — The `.dsp` and `.mak` files contain absolute paths referencing `J:\SRC\...` (the original developer's machine). These must be adjusted when setting up a new build environment.

- **Visual SourceSafe metadata** — `mssccprj.scc` files are present in `math/`, `sys/`, `vision/`, and `file/`, indicating the codebase was originally managed under Visual SourceSafe (VSS) before migration to Git.

- **Scale** — Approximately 400 C source files, ~1,100+ exported functions, spanning five independently buildable modules with a clear layered dependency hierarchy.
