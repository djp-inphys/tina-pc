# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Dynamic_Debug
!MESSAGE No configuration specified.  Defaulting to Dynamic_Debug.
!ENDIF 

!IF "$(CFG)" != "Dynamic_Release" && "$(CFG)" != "Dynamic_Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "math.mak" CFG="Dynamic_Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Dynamic_Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Dynamic_Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

################################################################################
# Begin Project
# PROP Target_Last_Scanned "Dynamic_Debug"
MTL=MkTypLib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Dynamic_Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : ".\WinRel\math.dll" ".\WinRel\math.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /G5 /MD /W2 /GX /YX /O1 /I "d:\tina\include" /I "d:\tina\lib-pc\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_COMPLEX_DEFINED" /D "__STRICT_ANSI__" /D "_PCC" /D "_AFXDLL" /D "_MBCS" /FR /c
CPP_PROJ=/nologo /G5 /MD /W2 /GX /YX /O1 /I "d:\tina\include" /I\
 "d:\tina\lib-pc\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_COMPLEX_DEFINED" /D "__STRICT_ANSI__" /D "_PCC" /D "_AFXDLL" /D "_MBCS"\
 /FR$(INTDIR)/ /Fp$(OUTDIR)/"math.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"math.bsc" 
BSC32_SBRS= \
	".\WinRel\mat_io.sbr" \
	".\WinRel\polygon.sbr" \
	".\WinRel\covar.sbr" \
	".\WinRel\mat_sub.sbr" \
	".\WinRel\mat_build.sbr" \
	".\WinRel\proj2.sbr" \
	".\WinRel\geom2.sbr" \
	".\WinRel\rot2.sbr" \
	".\WinRel\math_util.sbr" \
	".\WinRel\bres_line.sbr" \
	".\WinRel\transform3.sbr" \
	".\WinRel\mat_trnsf3.sbr" \
	".\WinRel\mat_put.sbr" \
	".\WinRel\ics.sbr" \
	".\WinRel\vec_geom.sbr" \
	".\WinRel\hyper.sbr" \
	".\WinRel\mat_eigen.sbr" \
	".\WinRel\mat_svd.sbr" \
	".\WinRel\vec3.sbr" \
	".\WinRel\mat_times.sbr" \
	".\WinRel\pentadiag.sbr" \
	".\WinRel\ivec.sbr" \
	".\WinRel\mat_minus.sbr" \
	".\WinRel\mat_mat2.sbr" \
	".\WinRel\proj3.sbr" \
	".\WinRel\geom3.sbr" \
	".\WinRel\mat2.sbr" \
	".\WinRel\vector.sbr" \
	".\WinRel\rot3.sbr" \
	".\WinRel\dprog.sbr" \
	".\WinRel\mat_fmt.sbr" \
	".\WinRel\univmin.sbr" \
	".\WinRel\eigen.sbr" \
	".\WinRel\mat_invsd.sbr" \
	".\WinRel\symm_line.sbr" \
	".\WinRel\newt_raph.sbr" \
	".\WinRel\mat_vprod.sbr" \
	".\WinRel\vec4.sbr" \
	".\WinRel\matrix_svd.sbr" \
	".\WinRel\mat_copy.sbr" \
	".\WinRel\mat_add.sbr" \
	".\WinRel\fmt_vtype.sbr" \
	".\WinRel\vec.sbr" \
	".\WinRel\mat.sbr" \
	".\WinRel\mat_transp.sbr" \
	".\WinRel\mat_get.sbr" \
	".\WinRel\mat_mat3.sbr" \
	".\WinRel\solve.sbr" \
	".\WinRel\mat_itimes.sbr" \
	".\WinRel\mat_free.sbr" \
	".\WinRel\mat_check.sbr" \
	".\WinRel\mat3.sbr" \
	".\WinRel\vec_image.sbr" \
	".\WinRel\vec_combine.sbr" \
	".\WinRel\mat_lu.sbr" \
	".\WinRel\ipos.sbr" \
	".\WinRel\hull2.sbr" \
	".\WinRel\mat_fill.sbr" \
	".\WinRel\cholesky.sbr" \
	".\WinRel\vec_set.sbr" \
	".\WinRel\simplexmin.sbr" \
	".\WinRel\vec_max.sbr" \
	".\WinRel\mat_gs.sbr" \
	".\WinRel\imget.sbr" \
	".\WinRel\vec_format.sbr" \
	".\WinRel\fourier.sbr" \
	".\WinRel\matr_invert.sbr" \
	".\WinRel\mat_prod.sbr" \
	".\WinRel\mat_chol.sbr" \
	".\WinRel\mat4.sbr" \
	".\WinRel\vec_get.sbr" \
	".\WinRel\mat_invert.sbr" \
	".\WinRel\rand.sbr" \
	".\WinRel\mat_unit.sbr" \
	".\WinRel\eqn.sbr" \
	".\WinRel\fmt_shape.sbr" \
	".\WinRel\hull3.sbr" \
	".\WinRel\svd.sbr" \
	".\WinRel\vec_apply.sbr" \
	".\WinRel\quat.sbr" \
	".\WinRel\transform2.sbr" \
	".\WinRel\mat_mult.sbr" \
	".\WinRel\mat_cast.sbr" \
	".\WinRel\mat_alloc.sbr" \
	".\WinRel\mat_trnsf2.sbr" \
	".\WinRel\mat_util.sbr" \
	".\WinRel\mat_tensor.sbr" \
	".\WinRel\vec2.sbr"

".\WinRel\math.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:I386
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:I386
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"math.pdb" /MACHINE:I386 /DEF:".\math.def"\
 /OUT:$(OUTDIR)/"math.dll" /IMPLIB:$(OUTDIR)/"math.lib" 
DEF_FILE=".\math.def"
LINK32_OBJS= \
	".\WinRel\mat_io.obj" \
	".\WinRel\polygon.obj" \
	".\WinRel\covar.obj" \
	".\WinRel\mat_sub.obj" \
	".\WinRel\mat_build.obj" \
	".\WinRel\proj2.obj" \
	".\WinRel\geom2.obj" \
	".\WinRel\rot2.obj" \
	".\WinRel\math_util.obj" \
	".\WinRel\bres_line.obj" \
	".\WinRel\transform3.obj" \
	".\WinRel\mat_trnsf3.obj" \
	".\WinRel\mat_put.obj" \
	".\WinRel\ics.obj" \
	".\WinRel\vec_geom.obj" \
	".\WinRel\hyper.obj" \
	".\WinRel\mat_eigen.obj" \
	".\WinRel\mat_svd.obj" \
	".\WinRel\vec3.obj" \
	".\WinRel\mat_times.obj" \
	".\WinRel\pentadiag.obj" \
	".\WinRel\ivec.obj" \
	".\WinRel\mat_minus.obj" \
	".\WinRel\mat_mat2.obj" \
	".\WinRel\proj3.obj" \
	".\WinRel\geom3.obj" \
	".\WinRel\mat2.obj" \
	".\WinRel\vector.obj" \
	".\WinRel\rot3.obj" \
	".\WinRel\dprog.obj" \
	".\WinRel\mat_fmt.obj" \
	".\WinRel\univmin.obj" \
	".\WinRel\eigen.obj" \
	".\WinRel\mat_invsd.obj" \
	".\WinRel\symm_line.obj" \
	".\WinRel\newt_raph.obj" \
	".\WinRel\mat_vprod.obj" \
	".\WinRel\vec4.obj" \
	".\WinRel\matrix_svd.obj" \
	".\WinRel\mat_copy.obj" \
	".\WinRel\mat_add.obj" \
	".\WinRel\fmt_vtype.obj" \
	".\WinRel\vec.obj" \
	".\WinRel\mat.obj" \
	".\WinRel\mat_transp.obj" \
	".\WinRel\mat_get.obj" \
	".\WinRel\mat_mat3.obj" \
	".\WinRel\solve.obj" \
	".\WinRel\mat_itimes.obj" \
	".\WinRel\mat_free.obj" \
	".\WinRel\mat_check.obj" \
	".\WinRel\mat3.obj" \
	".\WinRel\vec_image.obj" \
	".\WinRel\vec_combine.obj" \
	".\WinRel\mat_lu.obj" \
	".\WinRel\ipos.obj" \
	".\WinRel\hull2.obj" \
	".\WinRel\mat_fill.obj" \
	".\WinRel\cholesky.obj" \
	".\WinRel\vec_set.obj" \
	".\WinRel\simplexmin.obj" \
	".\WinRel\vec_max.obj" \
	".\WinRel\mat_gs.obj" \
	".\WinRel\imget.obj" \
	".\WinRel\vec_format.obj" \
	".\WinRel\fourier.obj" \
	".\WinRel\matr_invert.obj" \
	".\WinRel\mat_prod.obj" \
	".\WinRel\mat_chol.obj" \
	".\WinRel\mat4.obj" \
	".\WinRel\vec_get.obj" \
	".\WinRel\mat_invert.obj" \
	".\WinRel\rand.obj" \
	".\WinRel\mat_unit.obj" \
	".\WinRel\eqn.obj" \
	".\WinRel\fmt_shape.obj" \
	".\WinRel\hull3.obj" \
	".\WinRel\svd.obj" \
	".\WinRel\vec_apply.obj" \
	".\WinRel\quat.obj" \
	".\WinRel\transform2.obj" \
	".\WinRel\mat_mult.obj" \
	".\WinRel\mat_cast.obj" \
	".\WinRel\mat_alloc.obj" \
	".\WinRel\mat_trnsf2.obj" \
	".\WinRel\mat_util.obj" \
	".\WinRel\mat_tensor.obj" \
	".\WinRel\vec2.obj" \
	"\lib-pc\sys\windebug\sys.lib"

".\WinRel\math.dll" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : ".\WinDebug\math.dll" ".\WinDebug\math.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /W2 /GX /Zi /Od /I "d:\tina\include" /I "d:\tina\lib-pc\include" /D "_DEBUG" /D "WIN32" /D "WINDOWS" /D "_MBSC" /D "_AFXEXT" /D "_COMPLEX_DEFINED" /D "__STRICT_ANSI__" /D "_PCC" /D "_DLL" /Fr /c
CPP_PROJ=/nologo /MD /W2 /GX /Zi /Od /I "d:\tina\include" /I\
 "d:\tina\lib-pc\include" /D "_DEBUG" /D "WIN32" /D "WINDOWS" /D "_MBSC" /D\
 "_AFXEXT" /D "_COMPLEX_DEFINED" /D "__STRICT_ANSI__" /D "_PCC" /D "_DLL"\
 /Fr$(INTDIR)/ /Fo$(INTDIR)/ /Fd$(OUTDIR)/"math.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"math.bsc" 
BSC32_SBRS= \
	".\WinDebug\mat_io.sbr" \
	".\WinDebug\polygon.sbr" \
	".\WinDebug\covar.sbr" \
	".\WinDebug\mat_sub.sbr" \
	".\WinDebug\mat_build.sbr" \
	".\WinDebug\proj2.sbr" \
	".\WinDebug\geom2.sbr" \
	".\WinDebug\rot2.sbr" \
	".\WinDebug\math_util.sbr" \
	".\WinDebug\bres_line.sbr" \
	".\WinDebug\transform3.sbr" \
	".\WinDebug\mat_trnsf3.sbr" \
	".\WinDebug\mat_put.sbr" \
	".\WinDebug\ics.sbr" \
	".\WinDebug\vec_geom.sbr" \
	".\WinDebug\hyper.sbr" \
	".\WinDebug\mat_eigen.sbr" \
	".\WinDebug\mat_svd.sbr" \
	".\WinDebug\vec3.sbr" \
	".\WinDebug\mat_times.sbr" \
	".\WinDebug\pentadiag.sbr" \
	".\WinDebug\ivec.sbr" \
	".\WinDebug\mat_minus.sbr" \
	".\WinDebug\mat_mat2.sbr" \
	".\WinDebug\proj3.sbr" \
	".\WinDebug\geom3.sbr" \
	".\WinDebug\mat2.sbr" \
	".\WinDebug\vector.sbr" \
	".\WinDebug\rot3.sbr" \
	".\WinDebug\dprog.sbr" \
	".\WinDebug\mat_fmt.sbr" \
	".\WinDebug\univmin.sbr" \
	".\WinDebug\eigen.sbr" \
	".\WinDebug\mat_invsd.sbr" \
	".\WinDebug\symm_line.sbr" \
	".\WinDebug\newt_raph.sbr" \
	".\WinDebug\mat_vprod.sbr" \
	".\WinDebug\vec4.sbr" \
	".\WinDebug\matrix_svd.sbr" \
	".\WinDebug\mat_copy.sbr" \
	".\WinDebug\mat_add.sbr" \
	".\WinDebug\fmt_vtype.sbr" \
	".\WinDebug\vec.sbr" \
	".\WinDebug\mat.sbr" \
	".\WinDebug\mat_transp.sbr" \
	".\WinDebug\mat_get.sbr" \
	".\WinDebug\mat_mat3.sbr" \
	".\WinDebug\solve.sbr" \
	".\WinDebug\mat_itimes.sbr" \
	".\WinDebug\mat_free.sbr" \
	".\WinDebug\mat_check.sbr" \
	".\WinDebug\mat3.sbr" \
	".\WinDebug\vec_image.sbr" \
	".\WinDebug\vec_combine.sbr" \
	".\WinDebug\mat_lu.sbr" \
	".\WinDebug\ipos.sbr" \
	".\WinDebug\hull2.sbr" \
	".\WinDebug\mat_fill.sbr" \
	".\WinDebug\cholesky.sbr" \
	".\WinDebug\vec_set.sbr" \
	".\WinDebug\simplexmin.sbr" \
	".\WinDebug\vec_max.sbr" \
	".\WinDebug\mat_gs.sbr" \
	".\WinDebug\imget.sbr" \
	".\WinDebug\vec_format.sbr" \
	".\WinDebug\fourier.sbr" \
	".\WinDebug\matr_invert.sbr" \
	".\WinDebug\mat_prod.sbr" \
	".\WinDebug\mat_chol.sbr" \
	".\WinDebug\mat4.sbr" \
	".\WinDebug\vec_get.sbr" \
	".\WinDebug\mat_invert.sbr" \
	".\WinDebug\rand.sbr" \
	".\WinDebug\mat_unit.sbr" \
	".\WinDebug\eqn.sbr" \
	".\WinDebug\fmt_shape.sbr" \
	".\WinDebug\hull3.sbr" \
	".\WinDebug\svd.sbr" \
	".\WinDebug\vec_apply.sbr" \
	".\WinDebug\quat.sbr" \
	".\WinDebug\transform2.sbr" \
	".\WinDebug\mat_mult.sbr" \
	".\WinDebug\mat_cast.sbr" \
	".\WinDebug\mat_alloc.sbr" \
	".\WinDebug\mat_trnsf2.sbr" \
	".\WinDebug\mat_util.sbr" \
	".\WinDebug\mat_tensor.sbr" \
	".\WinDebug\vec2.sbr"

".\WinDebug\math.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:I386
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:I386
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"math.pdb" /DEBUG /MACHINE:I386 /DEF:".\math.def"\
 /OUT:$(OUTDIR)/"math.dll" /IMPLIB:$(OUTDIR)/"math.lib" 
DEF_FILE=".\math.def"
LINK32_OBJS= \
	".\WinDebug\mat_io.obj" \
	".\WinDebug\polygon.obj" \
	".\WinDebug\covar.obj" \
	".\WinDebug\mat_sub.obj" \
	".\WinDebug\mat_build.obj" \
	".\WinDebug\proj2.obj" \
	".\WinDebug\geom2.obj" \
	".\WinDebug\rot2.obj" \
	".\WinDebug\math_util.obj" \
	".\WinDebug\bres_line.obj" \
	".\WinDebug\transform3.obj" \
	".\WinDebug\mat_trnsf3.obj" \
	".\WinDebug\mat_put.obj" \
	".\WinDebug\ics.obj" \
	".\WinDebug\vec_geom.obj" \
	".\WinDebug\hyper.obj" \
	".\WinDebug\mat_eigen.obj" \
	".\WinDebug\mat_svd.obj" \
	".\WinDebug\vec3.obj" \
	".\WinDebug\mat_times.obj" \
	".\WinDebug\pentadiag.obj" \
	".\WinDebug\ivec.obj" \
	".\WinDebug\mat_minus.obj" \
	".\WinDebug\mat_mat2.obj" \
	".\WinDebug\proj3.obj" \
	".\WinDebug\geom3.obj" \
	".\WinDebug\mat2.obj" \
	".\WinDebug\vector.obj" \
	".\WinDebug\rot3.obj" \
	".\WinDebug\dprog.obj" \
	".\WinDebug\mat_fmt.obj" \
	".\WinDebug\univmin.obj" \
	".\WinDebug\eigen.obj" \
	".\WinDebug\mat_invsd.obj" \
	".\WinDebug\symm_line.obj" \
	".\WinDebug\newt_raph.obj" \
	".\WinDebug\mat_vprod.obj" \
	".\WinDebug\vec4.obj" \
	".\WinDebug\matrix_svd.obj" \
	".\WinDebug\mat_copy.obj" \
	".\WinDebug\mat_add.obj" \
	".\WinDebug\fmt_vtype.obj" \
	".\WinDebug\vec.obj" \
	".\WinDebug\mat.obj" \
	".\WinDebug\mat_transp.obj" \
	".\WinDebug\mat_get.obj" \
	".\WinDebug\mat_mat3.obj" \
	".\WinDebug\solve.obj" \
	".\WinDebug\mat_itimes.obj" \
	".\WinDebug\mat_free.obj" \
	".\WinDebug\mat_check.obj" \
	".\WinDebug\mat3.obj" \
	".\WinDebug\vec_image.obj" \
	".\WinDebug\vec_combine.obj" \
	".\WinDebug\mat_lu.obj" \
	".\WinDebug\ipos.obj" \
	".\WinDebug\hull2.obj" \
	".\WinDebug\mat_fill.obj" \
	".\WinDebug\cholesky.obj" \
	".\WinDebug\vec_set.obj" \
	".\WinDebug\simplexmin.obj" \
	".\WinDebug\vec_max.obj" \
	".\WinDebug\mat_gs.obj" \
	".\WinDebug\imget.obj" \
	".\WinDebug\vec_format.obj" \
	".\WinDebug\fourier.obj" \
	".\WinDebug\matr_invert.obj" \
	".\WinDebug\mat_prod.obj" \
	".\WinDebug\mat_chol.obj" \
	".\WinDebug\mat4.obj" \
	".\WinDebug\vec_get.obj" \
	".\WinDebug\mat_invert.obj" \
	".\WinDebug\rand.obj" \
	".\WinDebug\mat_unit.obj" \
	".\WinDebug\eqn.obj" \
	".\WinDebug\fmt_shape.obj" \
	".\WinDebug\hull3.obj" \
	".\WinDebug\svd.obj" \
	".\WinDebug\vec_apply.obj" \
	".\WinDebug\quat.obj" \
	".\WinDebug\transform2.obj" \
	".\WinDebug\mat_mult.obj" \
	".\WinDebug\mat_cast.obj" \
	".\WinDebug\mat_alloc.obj" \
	".\WinDebug\mat_trnsf2.obj" \
	".\WinDebug\mat_util.obj" \
	".\WinDebug\mat_tensor.obj" \
	".\WinDebug\vec2.obj" \
	$(INTDIR)/"sys.lib"

".\WinDebug\math.dll" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Group "math"

################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_io.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_io.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_io.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\draw\polygon.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\polygon.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\polygon.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\covar\covar.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\covar.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\covar.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_sub.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_sub.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_sub.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_build.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_build.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_build.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\geom\proj2.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\proj2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\proj2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\geom\geom2.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\geom2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\geom2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\transform\rot2.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\rot2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\rot2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\util\math_util.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\math_util.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\math_util.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\draw\bres_line.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\bres_line.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\bres_line.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\transform\transform3.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\transform3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\transform3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_trnsf3.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_trnsf3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_trnsf3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_put.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_put.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_put.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\splines\ics.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\ics.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\ics.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\vector\vec_geom.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\vec_geom.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\vec_geom.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\util\hyper.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\hyper.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\hyper.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matvec\mat_eigen.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_eigen.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_eigen.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matvec\mat_svd.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_svd.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_svd.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\geom\vec3.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\vec3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\vec3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_times.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_times.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_times.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\numeric\pentadiag.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\pentadiag.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\pentadiag.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matvec\ivec.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\ivec.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\ivec.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_minus.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_minus.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_minus.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_mat2.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_mat2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_mat2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\geom\proj3.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\proj3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\proj3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\geom\geom3.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\geom3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\geom3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\geom\mat2.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\vector\vector.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\vector.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\vector.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\transform\rot3.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\rot3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\rot3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\numeric\dprog.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\dprog.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\dprog.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_fmt.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_fmt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_fmt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\numeric\univmin.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\univmin.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\univmin.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\numeric\eigen.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\eigen.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\eigen.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_invsd.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_invsd.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_invsd.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\draw\symm_line.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\symm_line.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\symm_line.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\numeric\newt_raph.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\newt_raph.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\newt_raph.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_vprod.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_vprod.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_vprod.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\geom\vec4.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\vec4.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\vec4.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\matrix_svd.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\matrix_svd.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\matrix_svd.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_copy.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_copy.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_copy.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_add.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_add.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_add.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\fmt_vtype.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\fmt_vtype.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\fmt_vtype.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matvec\vec.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\vec.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\vec.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matvec\mat.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_transp.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_transp.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_transp.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_get.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_get.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_get.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_mat3.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_mat3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_mat3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\numeric\solve.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\solve.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\solve.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_itimes.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_itimes.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_itimes.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_free.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_free.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_free.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_check.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_check.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_check.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\geom\mat3.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\vector\vec_image.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\vec_image.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\vec_image.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\vector\vec_combine.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\vec_combine.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\vec_combine.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matvec\mat_lu.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_lu.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_lu.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\geom\ipos.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\ipos.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\ipos.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\geom\hull2.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\hull2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\hull2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_fill.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_fill.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_fill.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\numeric\cholesky.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\cholesky.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\cholesky.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\vector\vec_set.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\vec_set.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\vec_set.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\numeric\simplexmin.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\simplexmin.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\simplexmin.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\vector\vec_max.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\vec_max.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\vec_max.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matvec\mat_gs.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_gs.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_gs.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\image\imget.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\imget.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\imget.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\vector\vec_format.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\vec_format.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\vec_format.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\numeric\fourier.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\fourier.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\fourier.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matvec\matr_invert.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\matr_invert.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\matr_invert.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_prod.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_prod.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_prod.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matvec\mat_chol.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_chol.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_chol.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\geom\mat4.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat4.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat4.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\vector\vec_get.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\vec_get.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\vec_get.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_invert.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_invert.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_invert.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\util\rand.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\rand.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\rand.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_unit.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_unit.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_unit.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\numeric\eqn.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\eqn.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\eqn.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\fmt_shape.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\fmt_shape.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\fmt_shape.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\geom\hull3.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\hull3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\hull3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\numeric\svd.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\svd.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\svd.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\vector\vec_apply.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\vec_apply.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\vec_apply.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\transform\quat.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\quat.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\quat.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\transform\transform2.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\transform2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\transform2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_mult.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_mult.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_mult.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_cast.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_cast.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_cast.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_alloc.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_alloc.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_alloc.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_trnsf2.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_trnsf2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_trnsf2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_util.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_util.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_util.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\matrix\mat_tensor.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_tensor.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_tensor.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\math\geom\vec2.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\vec2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\vec2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE="\lib-pc\sys\windebug\sys.lib"
# End Source File
################################################################################
# Begin Source File

SOURCE=.\math.def
# End Source File
# End Group
# End Project
################################################################################
