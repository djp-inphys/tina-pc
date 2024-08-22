# Microsoft Developer Studio Project File - Name="math" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=math - Win32 Dynamic_Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "math.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "math.mak" CFG="math - Win32 Dynamic_Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "math - Win32 Dynamic_Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "math - Win32 Dynamic_Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/math", WAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "math - Win32 Dynamic_Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /G5 /MDd /W2 /Gm /GX /ZI /Od /I "\tina\include" /I "\tina\lib-pc\include" /D "_DEBUG" /D "WIN32" /D "WINDOWS" /D "_MBSC" /D "_AFXEXT" /D "_COMPLEX_DEFINED" /D "__STRICT_ANSI__" /D "_PCC" /D "_DLL" /D "_WINDLL" /D "_AFXDLL" /FR /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /mktyplib203
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "math - Win32 Dynamic_Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "math___W"
# PROP BASE Intermediate_Dir "math___W"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "winrelease"
# PROP Intermediate_Dir "winrelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MDd /W2 /Gm /GX /Zi /Od /I "\tina\include" /I "\tina\lib-pc\include" /D "_DEBUG" /D "WIN32" /D "WINDOWS" /D "_MBSC" /D "_AFXEXT" /D "_COMPLEX_DEFINED" /D "__STRICT_ANSI__" /D "_PCC" /D "_DLL" /D "_WINDLL" /D "_AFXDLL" /FR /FD /c
# ADD CPP /nologo /G5 /MDd /W2 /Gm /GX /Zi /O2 /I "\tina\include" /I "\tina\lib-pc\include" /D "_DEBUG" /D "WIN32" /D "WINDOWS" /D "_MBSC" /D "_AFXEXT" /D "_COMPLEX_DEFINED" /D "__STRICT_ANSI__" /D "_PCC" /D "_DLL" /D "_WINDLL" /D "_AFXDLL" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /mktyplib203
# ADD MTL /mktyplib203
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# SUBTRACT BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "math - Win32 Dynamic_Debug"
# Name "math - Win32 Dynamic_Release"
# Begin Group "math"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\bres_line.c
# End Source File
# Begin Source File

SOURCE=.\cholesky.c
# End Source File
# Begin Source File

SOURCE=.\covar.c
# End Source File
# Begin Source File

SOURCE=.\dprog.c
# End Source File
# Begin Source File

SOURCE=.\eigen.c
# End Source File
# Begin Source File

SOURCE=.\eqn.c
# End Source File
# Begin Source File

SOURCE=.\fmt_shape.c
# End Source File
# Begin Source File

SOURCE=.\fmt_vtype.c
# End Source File
# Begin Source File

SOURCE=.\fourier.c
# End Source File
# Begin Source File

SOURCE=.\geom2.c
# End Source File
# Begin Source File

SOURCE=.\geom3.c
# End Source File
# Begin Source File

SOURCE=.\hull2.c
# End Source File
# Begin Source File

SOURCE=.\hull3.c
# End Source File
# Begin Source File

SOURCE=.\hyper.c
# End Source File
# Begin Source File

SOURCE=.\ics.c
# End Source File
# Begin Source File

SOURCE=.\imget.c
# End Source File
# Begin Source File

SOURCE=.\ipos.c
# End Source File
# Begin Source File

SOURCE=.\ivec.c
# End Source File
# Begin Source File

SOURCE=.\mat.c
# End Source File
# Begin Source File

SOURCE=.\mat2.c
# End Source File
# Begin Source File

SOURCE=.\mat3.c
# End Source File
# Begin Source File

SOURCE=.\mat4.c
# End Source File
# Begin Source File

SOURCE=.\mat_add.c
# End Source File
# Begin Source File

SOURCE=.\mat_alloc.c
# End Source File
# Begin Source File

SOURCE=.\mat_build.c
# End Source File
# Begin Source File

SOURCE=.\mat_cast.c
# End Source File
# Begin Source File

SOURCE=.\mat_check.c
# End Source File
# Begin Source File

SOURCE=.\mat_chol.c
# End Source File
# Begin Source File

SOURCE=.\mat_copy.c
# End Source File
# Begin Source File

SOURCE=.\mat_eigen.c
# End Source File
# Begin Source File

SOURCE=.\mat_fill.c
# End Source File
# Begin Source File

SOURCE=.\mat_fmt.c
# End Source File
# Begin Source File

SOURCE=.\mat_free.c
# End Source File
# Begin Source File

SOURCE=.\mat_get.c
# End Source File
# Begin Source File

SOURCE=.\mat_gs.c
# End Source File
# Begin Source File

SOURCE=.\mat_invert.c
# End Source File
# Begin Source File

SOURCE=.\mat_invsd.c
# End Source File
# Begin Source File

SOURCE=.\mat_io.c
# End Source File
# Begin Source File

SOURCE=.\mat_itimes.c
# End Source File
# Begin Source File

SOURCE=.\mat_lu.c
# End Source File
# Begin Source File

SOURCE=.\mat_mat2.c
# End Source File
# Begin Source File

SOURCE=.\mat_mat3.c
# End Source File
# Begin Source File

SOURCE=.\mat_minus.c
# End Source File
# Begin Source File

SOURCE=.\mat_mult.c
# End Source File
# Begin Source File

SOURCE=.\mat_prod.c
# End Source File
# Begin Source File

SOURCE=.\mat_put.c
# End Source File
# Begin Source File

SOURCE=.\mat_sub.c
# End Source File
# Begin Source File

SOURCE=.\mat_svd.c
# End Source File
# Begin Source File

SOURCE=.\mat_tensor.c
# End Source File
# Begin Source File

SOURCE=.\mat_times.c
# End Source File
# Begin Source File

SOURCE=.\mat_transp.c
# End Source File
# Begin Source File

SOURCE=.\mat_trnsf2.c
# End Source File
# Begin Source File

SOURCE=.\mat_trnsf3.c
# End Source File
# Begin Source File

SOURCE=.\mat_unit.c
# End Source File
# Begin Source File

SOURCE=.\mat_util.c
# End Source File
# Begin Source File

SOURCE=.\mat_vprod.c
# End Source File
# Begin Source File

SOURCE=.\math.def
# End Source File
# Begin Source File

SOURCE=.\math_util.c
# End Source File
# Begin Source File

SOURCE=.\matr_invert.c
# End Source File
# Begin Source File

SOURCE=.\matrix_svd.c
# End Source File
# Begin Source File

SOURCE=.\newt_raph.c
# End Source File
# Begin Source File

SOURCE=.\pentadiag.c
# End Source File
# Begin Source File

SOURCE=.\polygon.c
# End Source File
# Begin Source File

SOURCE=.\proj2.c
# End Source File
# Begin Source File

SOURCE=.\proj3.c
# End Source File
# Begin Source File

SOURCE=.\quat.c
# End Source File
# Begin Source File

SOURCE=.\rand.c
# End Source File
# Begin Source File

SOURCE=.\rot2.c
# End Source File
# Begin Source File

SOURCE=.\rot3.c
# End Source File
# Begin Source File

SOURCE=.\simplexmin.c
# End Source File
# Begin Source File

SOURCE=.\solve.c
# End Source File
# Begin Source File

SOURCE=.\svd.c
# End Source File
# Begin Source File

SOURCE=.\symm_line.c
# End Source File
# Begin Source File

SOURCE=.\transform2.c
# End Source File
# Begin Source File

SOURCE=.\transform3.c
# End Source File
# Begin Source File

SOURCE=.\univmin.c
# End Source File
# Begin Source File

SOURCE=.\vec.c
# End Source File
# Begin Source File

SOURCE=.\vec2.c
# End Source File
# Begin Source File

SOURCE=.\vec3.c
# End Source File
# Begin Source File

SOURCE=.\vec4.c
# End Source File
# Begin Source File

SOURCE=.\vec_apply.c
# End Source File
# Begin Source File

SOURCE=.\vec_combine.c
# End Source File
# Begin Source File

SOURCE=.\vec_format.c
# End Source File
# Begin Source File

SOURCE=.\vec_geom.c
# End Source File
# Begin Source File

SOURCE=.\vec_get.c
# End Source File
# Begin Source File

SOURCE=.\vec_image.c
# End Source File
# Begin Source File

SOURCE=.\vec_max.c
# End Source File
# Begin Source File

SOURCE=.\vec_set.c
# End Source File
# Begin Source File

SOURCE=.\vector.c
# End Source File
# Begin Source File

SOURCE=.\sys.lib
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# End Group
# End Target
# End Project
