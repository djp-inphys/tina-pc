# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Win32 Release" && "$(CFG)" != "Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "serialise.mak" CFG="Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

################################################################################
# Begin Project
# PROP Target_Last_Scanned "Win32 Debug"
MTL=MkTypLib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : ".\WinRel\serialise.dll" ".\WinRel\serialise.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MT /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
CPP_PROJ=/nologo /MT /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /FR$(INTDIR)/ /Fp$(OUTDIR)/"serialise.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"serialise.bsc" 
BSC32_SBRS= \
	".\WinRel\imstack.sbr" \
	".\WinRel\windex.sbr" \
	".\WinRel\rindex.sbr" \
	".\WinRel\narray.sbr" \
	".\WinRel\prop.sbr" \
	".\WinRel\ddlist.sbr" \
	".\WinRel\vector.sbr" \
	".\WinRel\imrect.sbr" \
	".\WinRel\edge_conn.sbr" \
	".\WinRel\nvector.sbr" \
	".\WinRel\list.sbr" \
	".\WinRel\ts_set.sbr" \
	".\WinRel\matrix.sbr"

".\WinRel\serialise.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"serialise.pdb" /MACHINE:I386 /DEF:".\serialise.def"\
 /OUT:$(OUTDIR)/"serialise.dll" /IMPLIB:$(OUTDIR)/"serialise.lib" 
DEF_FILE=".\serialise.def"
LINK32_OBJS= \
	".\WinRel\imstack.obj" \
	".\WinRel\windex.obj" \
	".\WinRel\rindex.obj" \
	".\WinRel\narray.obj" \
	".\WinRel\prop.obj" \
	".\WinRel\ddlist.obj" \
	".\WinRel\vector.obj" \
	".\WinRel\imrect.obj" \
	".\WinRel\edge_conn.obj" \
	".\WinRel\nvector.obj" \
	".\WinRel\list.obj" \
	".\WinRel\ts_set.obj" \
	".\WinRel\matrix.obj" \
	"\lib-pc\sys\windebug\sys.lib" \
	"\lib-pc\file\windebug\file.lib" \
	"\lib-pc\math\windebug\math.lib" \
	"\lib-pc\vision\windebug\vision.lib"

".\WinRel\serialise.dll" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : ".\WinDebug\serialise.dll" ".\WinDebug\serialise.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MT /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
CPP_PROJ=/nologo /MT /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /FR$(INTDIR)/ /Fp$(OUTDIR)/"serialise.pch" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"serialise.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"serialise.bsc" 
BSC32_SBRS= \
	".\WinDebug\imstack.sbr" \
	".\WinDebug\windex.sbr" \
	".\WinDebug\rindex.sbr" \
	".\WinDebug\narray.sbr" \
	".\WinDebug\prop.sbr" \
	".\WinDebug\ddlist.sbr" \
	".\WinDebug\vector.sbr" \
	".\WinDebug\imrect.sbr" \
	".\WinDebug\edge_conn.sbr" \
	".\WinDebug\nvector.sbr" \
	".\WinDebug\list.sbr" \
	".\WinDebug\ts_set.sbr" \
	".\WinDebug\matrix.sbr"

".\WinDebug\serialise.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"serialise.pdb" /DEBUG /MACHINE:I386 /DEF:".\serialise.def"\
 /OUT:$(OUTDIR)/"serialise.dll" /IMPLIB:$(OUTDIR)/"serialise.lib" 
DEF_FILE=".\serialise.def"
LINK32_OBJS= \
	".\WinDebug\imstack.obj" \
	".\WinDebug\windex.obj" \
	".\WinDebug\rindex.obj" \
	".\WinDebug\narray.obj" \
	".\WinDebug\prop.obj" \
	".\WinDebug\ddlist.obj" \
	".\WinDebug\vector.obj" \
	".\WinDebug\imrect.obj" \
	".\WinDebug\edge_conn.obj" \
	".\WinDebug\nvector.obj" \
	".\WinDebug\list.obj" \
	".\WinDebug\ts_set.obj" \
	".\WinDebug\matrix.obj" \
	"\lib-pc\sys\windebug\sys.lib" \
	"\lib-pc\file\windebug\file.lib" \
	"\lib-pc\math\windebug\math.lib" \
	"\lib-pc\vision\windebug\vision.lib"

".\WinDebug\serialise.dll" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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
# Begin Group "Source Files"

################################################################################
# Begin Source File

SOURCE=\src\serialise\imstack.c

!IF  "$(CFG)" == "Win32 Release"

".\WinRel\imstack.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

".\WinDebug\imstack.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\serialise\windex.c

!IF  "$(CFG)" == "Win32 Release"

".\WinRel\windex.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

".\WinDebug\windex.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\serialise\rindex.c

!IF  "$(CFG)" == "Win32 Release"

".\WinRel\rindex.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

".\WinDebug\rindex.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\serialise\narray.c

!IF  "$(CFG)" == "Win32 Release"

".\WinRel\narray.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

".\WinDebug\narray.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\serialise\prop.c

!IF  "$(CFG)" == "Win32 Release"

".\WinRel\prop.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

".\WinDebug\prop.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\serialise\ddlist.c

!IF  "$(CFG)" == "Win32 Release"

".\WinRel\ddlist.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

".\WinDebug\ddlist.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\serialise\vector.c

!IF  "$(CFG)" == "Win32 Release"

".\WinRel\vector.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

".\WinDebug\vector.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\serialise\imrect.c

!IF  "$(CFG)" == "Win32 Release"

".\WinRel\imrect.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

".\WinDebug\imrect.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\serialise\edge_conn.c

!IF  "$(CFG)" == "Win32 Release"

".\WinRel\edge_conn.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

".\WinDebug\edge_conn.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\serialise\nvector.c

!IF  "$(CFG)" == "Win32 Release"

".\WinRel\nvector.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

".\WinDebug\nvector.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\serialise\list.c

!IF  "$(CFG)" == "Win32 Release"

".\WinRel\list.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

".\WinDebug\list.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\serialise\ts_set.c
DEP_TS_SE=\
	"\tina\include\TINA\ALL_TINA.H"\
	"\tina\lib-pc\include\values.h"\
	"\tina\include\TINA\SYS.H"\
	"\tina\include\TINA\SYSFUNCS.H"\
	"\tina\include\TINA\MATH.H"\
	"\tina\include\TINA\mathfuncs.h"\
	"\tina\include\TINA\VISION.H"\
	"\tina\include\TINA\visionfuncs.h"\
	"\tina\include\TINA\TV.H"\
	"\tina\include\TINA\TVFUNCS.H"\
	"\tina\include\TINA\toolsfuncs.h"\
	"\tina\include\TINA\FILE.H"\
	"\tina\include\TINA\filefuncs.h"\
	"\tina\include\TINA\DRAW.H"\
	"\tina\include\TINA\drawfuncs.h"\
	"\tina\include\TINA\IMAGE.H"\
	"\tina\include\TINA\SYS_GEN.H"\
	"\tina\include\TINA\tstruct_info.h"\
	"\tina\include\TINA\sys_types.h"\
	"\tina\include\TINA\DYNAMIC.H"\
	"\tina\include\TINA\LISTS.H"\
	"\tina\include\TINA\GRAPH.H"\
	"\tina\include\TINA\PAIR.H"\
	"\tina\include\TINA\GENERIC.H"\
	"\tina\include\TINA\complexfuncs.h"\
	"\tina\include\TINA\covarfuncs.h"\
	"\tina\include\TINA\calibfuncs.h"\
	"\tina\include\TINA\IFF.H"\
	"\tina\include\TINA\AIFF.H"\
	"\tina\include\TINA\FILE_GEN.H"

!IF  "$(CFG)" == "Win32 Release"

".\WinRel\ts_set.obj" :  $(SOURCE)  $(DEP_TS_SE) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

".\WinDebug\ts_set.obj" :  $(SOURCE)  $(DEP_TS_SE) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\serialise\matrix.c

!IF  "$(CFG)" == "Win32 Release"

".\WinRel\matrix.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

".\WinDebug\matrix.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE="\lib-pc\sys\windebug\sys.lib"
# End Source File
################################################################################
# Begin Source File

SOURCE="\lib-pc\file\windebug\file.lib"
# End Source File
################################################################################
# Begin Source File

SOURCE="\lib-pc\math\windebug\math.lib"
# End Source File
################################################################################
# Begin Source File

SOURCE="\lib-pc\vision\windebug\vision.lib"
# End Source File
################################################################################
# Begin Source File

SOURCE=.\serialise.def
# End Source File
# End Group
# End Project
################################################################################
