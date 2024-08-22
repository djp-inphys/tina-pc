# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Win32 Debug" && "$(CFG)" != "Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "sys.mak" CFG="Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

################################################################################
# Begin Project
# PROP Target_Last_Scanned "Win32 Debug"
MTL=MkTypLib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : ".\WinDebug\sys.dll" ".\WinDebug\sys.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /I "d:\tina\include" /I "d:\tina\lib-pc\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXEXT" /D "_COMPLEX_DEFINED" /D "__STRICT_ANSI__" /D "_PCC" /D "_DLL" /D "_AFXDLL" /D "_MBCS" /D "__MEM_TRACE__" /FR /c
CPP_PROJ=/nologo /MD /W3 /GX /Zi /Od /I "d:\tina\include" /I\
 "d:\tina\lib-pc\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXEXT" /D\
 "_COMPLEX_DEFINED" /D "__STRICT_ANSI__" /D "_PCC" /D "_DLL" /D "_AFXDLL" /D\
 "_MBCS" /D "__MEM_TRACE__" /FR$(INTDIR)/ /Fo$(INTDIR)/ /Fd$(OUTDIR)/"sys.pdb"\
 /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x0 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"sys.bsc" 
BSC32_SBRS= \
	".\WinDebug\complex.sbr" \
	".\WinDebug\string.sbr" \
	".\WinDebug\cliques.sbr" \
	".\WinDebug\ts_save_load.sbr" \
	".\WinDebug\message.sbr" \
	".\WinDebug\lists.sbr" \
	".\WinDebug\serialise.sbr" \
	".\WinDebug\swap.sbr" \
	".\WinDebug\ralloc.sbr" \
	".\WinDebug\var.sbr" \
	".\WinDebug\region.sbr" \
	".\WinDebug\deserialise.sbr" \
	".\WinDebug\image.sbr" \
	".\WinDebug\tina_int.sbr" \
	".\WinDebug\tsprint.sbr" \
	".\WinDebug\null.sbr" \
	".\WinDebug\dcopy.sbr" \
	".\WinDebug\imput.sbr" \
	".\WinDebug\error.sbr" \
	".\WinDebug\tsfree.sbr" \
	".\WinDebug\sort.sbr" \
	".\WinDebug\help.sbr" \
	".\WinDebug\mprintf.sbr" \
	".\WinDebug\icopy.sbr" \
	".\WinDebug\util.sbr" \
	".\WinDebug\reclist.sbr" \
	".\WinDebug\ddstr.sbr" \
	".\WinDebug\label.sbr" \
	".\WinDebug\fcopy.sbr" \
	".\WinDebug\ccopy.sbr" \
	".\WinDebug\strings.sbr" \
	".\WinDebug\ts_ndynamic.sbr" \
	".\WinDebug\imget.sbr" \
	".\WinDebug\imfloatfns.sbr" \
	".\WinDebug\generic.sbr" \
	".\WinDebug\tstruct_info.sbr" \
	".\WinDebug\pipe_read.sbr" \
	".\WinDebug\pair.sbr" \
	".\WinDebug\ddlists.sbr" \
	".\WinDebug\ndynamic.sbr" \
	".\WinDebug\io.sbr" \
	".\WinDebug\proplist.sbr" \
	".\WinDebug\graph.sbr" \
	".\WinDebug\vdynamic.sbr" \
	".\WinDebug\format.sbr"

".\WinDebug\sys.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:I386 /DEF:"sys.def" /IMPLIB:"sys.lib"
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:I386 /DEF:"sys.def"
# SUBTRACT LINK32 /NOLOGO /VERBOSE /PDB:none /MAP
LINK32_FLAGS=/SUBSYSTEM:windows /DLL /INCREMENTAL:yes /PDB:$(OUTDIR)/"sys.pdb"\
 /DEBUG /MACHINE:I386 /DEF:"sys.def" /OUT:$(OUTDIR)/"sys.dll"\
 /IMPLIB:$(OUTDIR)/"sys.lib" 
DEF_FILE=".\sys.def"
LINK32_OBJS= \
	".\WinDebug\complex.obj" \
	".\WinDebug\string.obj" \
	".\WinDebug\cliques.obj" \
	".\WinDebug\ts_save_load.obj" \
	".\WinDebug\message.obj" \
	".\WinDebug\lists.obj" \
	".\WinDebug\serialise.obj" \
	".\WinDebug\swap.obj" \
	".\WinDebug\ralloc.obj" \
	".\WinDebug\var.obj" \
	".\WinDebug\region.obj" \
	".\WinDebug\deserialise.obj" \
	".\WinDebug\image.obj" \
	".\WinDebug\tina_int.obj" \
	".\WinDebug\tsprint.obj" \
	".\WinDebug\null.obj" \
	".\WinDebug\dcopy.obj" \
	".\WinDebug\imput.obj" \
	".\WinDebug\error.obj" \
	".\WinDebug\tsfree.obj" \
	".\WinDebug\sort.obj" \
	".\WinDebug\help.obj" \
	".\WinDebug\mprintf.obj" \
	".\WinDebug\icopy.obj" \
	".\WinDebug\util.obj" \
	".\WinDebug\reclist.obj" \
	".\WinDebug\ddstr.obj" \
	".\WinDebug\label.obj" \
	".\WinDebug\fcopy.obj" \
	".\WinDebug\ccopy.obj" \
	".\WinDebug\strings.obj" \
	".\WinDebug\ts_ndynamic.obj" \
	".\WinDebug\imget.obj" \
	".\WinDebug\imfloatfns.obj" \
	".\WinDebug\generic.obj" \
	".\WinDebug\tstruct_info.obj" \
	".\WinDebug\pipe_read.obj" \
	".\WinDebug\pair.obj" \
	".\WinDebug\ddlists.obj" \
	".\WinDebug\ndynamic.obj" \
	".\WinDebug\io.obj" \
	".\WinDebug\proplist.obj" \
	".\WinDebug\graph.obj" \
	".\WinDebug\vdynamic.obj" \
	".\WinDebug\format.obj"

".\WinDebug\sys.dll" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : ".\WinRel\sys.dll" ".\WinRel\sys.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O1 /I "d:\tina\include" /I "d:\tina\lib-pc\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXEXT" /D "_COMPLEX_DEFINED" /D "__STRICT_ANSI__" /D "_PCC" /D "_DLL" /D "_AFXDLL" /D "_MBCS" /D "__MEM_TRACE__" /FR /c
# SUBTRACT CPP /Yu
CPP_PROJ=/nologo /MD /W3 /GX /O1 /I "d:\tina\include" /I\
 "d:\tina\lib-pc\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXEXT" /D\
 "_COMPLEX_DEFINED" /D "__STRICT_ANSI__" /D "_PCC" /D "_DLL" /D "_AFXDLL" /D\
 "_MBCS" /D "__MEM_TRACE__" /FR$(INTDIR)/ /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x0 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"sys.bsc" 
BSC32_SBRS= \
	".\WinRel\complex.sbr" \
	".\WinRel\string.sbr" \
	".\WinRel\cliques.sbr" \
	".\WinRel\ts_save_load.sbr" \
	".\WinRel\message.sbr" \
	".\WinRel\lists.sbr" \
	".\WinRel\serialise.sbr" \
	".\WinRel\swap.sbr" \
	".\WinRel\ralloc.sbr" \
	".\WinRel\var.sbr" \
	".\WinRel\region.sbr" \
	".\WinRel\deserialise.sbr" \
	".\WinRel\image.sbr" \
	".\WinRel\tina_int.sbr" \
	".\WinRel\tsprint.sbr" \
	".\WinRel\null.sbr" \
	".\WinRel\dcopy.sbr" \
	".\WinRel\imput.sbr" \
	".\WinRel\error.sbr" \
	".\WinRel\tsfree.sbr" \
	".\WinRel\sort.sbr" \
	".\WinRel\help.sbr" \
	".\WinRel\mprintf.sbr" \
	".\WinRel\icopy.sbr" \
	".\WinRel\util.sbr" \
	".\WinRel\reclist.sbr" \
	".\WinRel\ddstr.sbr" \
	".\WinRel\label.sbr" \
	".\WinRel\fcopy.sbr" \
	".\WinRel\ccopy.sbr" \
	".\WinRel\strings.sbr" \
	".\WinRel\ts_ndynamic.sbr" \
	".\WinRel\imget.sbr" \
	".\WinRel\imfloatfns.sbr" \
	".\WinRel\generic.sbr" \
	".\WinRel\tstruct_info.sbr" \
	".\WinRel\pipe_read.sbr" \
	".\WinRel\pair.sbr" \
	".\WinRel\ddlists.sbr" \
	".\WinRel\ndynamic.sbr" \
	".\WinRel\io.sbr" \
	".\WinRel\proplist.sbr" \
	".\WinRel\graph.sbr" \
	".\WinRel\vdynamic.sbr" \
	".\WinRel\format.sbr"

".\WinRel\sys.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:I386 /DEF:"sys.def" /IMPLIB:"sys.lib"
# SUBTRACT BASE LINK32 /PDB:none
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:I386 /DEF:"sys.def"
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"sys.pdb" /MACHINE:I386 /DEF:"sys.def" /OUT:$(OUTDIR)/"sys.dll"\
 /IMPLIB:$(OUTDIR)/"sys.lib" 
DEF_FILE=".\sys.def"
LINK32_OBJS= \
	".\WinRel\complex.obj" \
	".\WinRel\string.obj" \
	".\WinRel\cliques.obj" \
	".\WinRel\ts_save_load.obj" \
	".\WinRel\message.obj" \
	".\WinRel\lists.obj" \
	".\WinRel\serialise.obj" \
	".\WinRel\swap.obj" \
	".\WinRel\ralloc.obj" \
	".\WinRel\var.obj" \
	".\WinRel\region.obj" \
	".\WinRel\deserialise.obj" \
	".\WinRel\image.obj" \
	".\WinRel\tina_int.obj" \
	".\WinRel\tsprint.obj" \
	".\WinRel\null.obj" \
	".\WinRel\dcopy.obj" \
	".\WinRel\imput.obj" \
	".\WinRel\error.obj" \
	".\WinRel\tsfree.obj" \
	".\WinRel\sort.obj" \
	".\WinRel\help.obj" \
	".\WinRel\mprintf.obj" \
	".\WinRel\icopy.obj" \
	".\WinRel\util.obj" \
	".\WinRel\reclist.obj" \
	".\WinRel\ddstr.obj" \
	".\WinRel\label.obj" \
	".\WinRel\fcopy.obj" \
	".\WinRel\ccopy.obj" \
	".\WinRel\strings.obj" \
	".\WinRel\ts_ndynamic.obj" \
	".\WinRel\imget.obj" \
	".\WinRel\imfloatfns.obj" \
	".\WinRel\generic.obj" \
	".\WinRel\tstruct_info.obj" \
	".\WinRel\pipe_read.obj" \
	".\WinRel\pair.obj" \
	".\WinRel\ddlists.obj" \
	".\WinRel\ndynamic.obj" \
	".\WinRel\io.obj" \
	".\WinRel\proplist.obj" \
	".\WinRel\graph.obj" \
	".\WinRel\vdynamic.obj" \
	".\WinRel\format.obj"

".\WinRel\sys.dll" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

MTL_PROJ=

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Group "Source Files"

################################################################################
# Begin Source File

SOURCE=\src\sys\complex\complex.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\complex.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\complex.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\gen\string.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\string.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\string.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\graph\cliques.c
DEP_CLIQU=\
	"\tina\include\TINA\SYS.H"\
	"\tina\include\TINA\GRAPH.H"\
	"\tina\include\TINA\SYSFUNCS.H"\
	"\tina\lib-pc\include\values.h"\
	"\tina\include\TINA\SYS_GEN.H"\
	"\tina\include\TINA\tstruct_info.h"\
	"\tina\include\TINA\sys_types.h"\
	"\tina\include\TINA\DYNAMIC.H"\
	"\tina\include\TINA\LISTS.H"\
	"\tina\include\TINA\IMAGE.H"\
	"\tina\include\TINA\PAIR.H"\
	"\tina\include\TINA\GENERIC.H"\
	"\tina\include\TINA\complexfuncs.h"

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\cliques.obj" :  $(SOURCE)  $(DEP_CLIQU) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\cliques.obj" :  $(SOURCE)  $(DEP_CLIQU) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\gen\ts_save_load.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\ts_save_load.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\ts_save_load.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\gen\message.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\message.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\message.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\lists\lists.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\lists.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\lists.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\gen\serialise.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\serialise.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\serialise.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\gen\swap.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\swap.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\swap.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\gen\ralloc.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\ralloc.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\ralloc.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\gen\var.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\var.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\var.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\image\region.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\region.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\region.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\gen\deserialise.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\deserialise.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\deserialise.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\image\image.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\image.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\image.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\gen\tina_int.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\tina_int.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\tina_int.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\gen\tsprint.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\tsprint.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\tsprint.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\gen\null.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\null.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\null.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\dynamic\dcopy.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\dcopy.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\dcopy.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\image\imput.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\imput.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\imput.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\gen\error.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\error.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\error.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\gen\tsfree.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\tsfree.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\tsfree.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\lists\sort.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\sort.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\sort.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\gen\help.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\help.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\help.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\gen\mprintf.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\mprintf.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\mprintf.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\dynamic\icopy.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\icopy.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\icopy.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\lists\util.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\util.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\util.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\lists\reclist.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\reclist.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\reclist.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\lists\ddstr.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\ddstr.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\ddstr.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\generic\label.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\label.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\label.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\dynamic\fcopy.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\fcopy.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\fcopy.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\dynamic\ccopy.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\ccopy.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\ccopy.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\lists\strings.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\strings.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\strings.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\dynamic\ts_ndynamic.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\ts_ndynamic.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\ts_ndynamic.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\image\imget.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\imget.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\imget.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\image\imfloatfns.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\imfloatfns.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\imfloatfns.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\generic\generic.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\generic.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\generic.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\gen\tstruct_info.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\tstruct_info.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\tstruct_info.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\gen\pipe_read.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\pipe_read.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\pipe_read.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\pair\pair.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\pair.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\pair.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\lists\ddlists.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\ddlists.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\ddlists.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\dynamic\ndynamic.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\ndynamic.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\ndynamic.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\gen\io.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\io.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\io.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\lists\proplist.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\proplist.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\proplist.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\graph\graph.c
DEP_GRAPH=\
	"\tina\include\TINA\SYS.H"\
	"\tina\include\TINA\GRAPH.H"\
	"\tina\include\TINA\SYSFUNCS.H"\
	"\tina\lib-pc\include\values.h"\
	"\tina\include\TINA\SYS_GEN.H"\
	"\tina\include\TINA\tstruct_info.h"\
	"\tina\include\TINA\sys_types.h"\
	"\tina\include\TINA\DYNAMIC.H"\
	"\tina\include\TINA\LISTS.H"\
	"\tina\include\TINA\IMAGE.H"\
	"\tina\include\TINA\PAIR.H"\
	"\tina\include\TINA\GENERIC.H"\
	"\tina\include\TINA\complexfuncs.h"

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\graph.obj" :  $(SOURCE)  $(DEP_GRAPH) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\graph.obj" :  $(SOURCE)  $(DEP_GRAPH) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\dynamic\vdynamic.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\vdynamic.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\vdynamic.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\sys\gen\format.c

!IF  "$(CFG)" == "Win32 Debug"

".\WinDebug\format.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Release"

".\WinRel\format.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\sys.def
# End Source File
# End Group
# End Project
################################################################################
