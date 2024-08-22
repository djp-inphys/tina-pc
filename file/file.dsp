# Microsoft Developer Studio Project File - Name="file" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=file - Win32 Dynamic_Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "file.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "file.mak" CFG="file - Win32 Dynamic_Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "file - Win32 Dynamic_Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "file - Win32 Dynamic_Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/file", QQAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "file - Win32 Dynamic_Debug"

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
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GX /ZI /Od /I "\tina\include" /I "\tina\lib-pc\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /D "_COMPLEX_DEFINED" /D "__STRICT_ANSI__" /D "_PCC" /D "_DLL" /D "_WINDLL" /D "_AFXDLL" /FR /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 \tina\lib-pc\vision\WinDebug\vision.lib /nologo /subsystem:windows /dll /debug /machine:I386

!ELSEIF  "$(CFG)" == "file - Win32 Dynamic_Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "file___W"
# PROP BASE Intermediate_Dir "file___W"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "winrelease"
# PROP Intermediate_Dir "winrelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MDd /W3 /Gm /GX /Zi /Od /I "\tina\include" /I "\tina\lib-pc\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /D "_COMPLEX_DEFINED" /D "__STRICT_ANSI__" /D "_PCC" /D "_DLL" /D "_WINDLL" /D "_AFXDLL" /FR /FD /c
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GX /Zi /O2 /I "\tina\include" /I "\tina\lib-pc\include" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /D "_COMPLEX_DEFINED" /D "__STRICT_ANSI__" /D "_PCC" /D "_DLL" /D "_WINDLL" /D "_AFXDLL" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_AFXDLL"
BSC32=bscmake.exe
# SUBTRACT BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386

!ENDIF 

# Begin Target

# Name "file - Win32 Dynamic_Debug"
# Name "file - Win32 Dynamic_Release"
# Begin Group "file"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\aiff_io.c
# End Source File
# Begin Source File

SOURCE=.\cam_g3_rd.c
# End Source File
# Begin Source File

SOURCE=.\cam_io.c
# End Source File
# Begin Source File

SOURCE=.\covar_r.c
# End Source File
# Begin Source File

SOURCE=.\covar_w.c
# End Source File
# Begin Source File

SOURCE=.\distort_r.c
# End Source File
# Begin Source File

SOURCE=.\distort_w.c
# End Source File
# Begin Source File

SOURCE=.\edges_read.c
# End Source File
# Begin Source File

SOURCE=.\edges_w.c
# End Source File
# Begin Source File

SOURCE=.\ffg_new_read.c
# End Source File
# Begin Source File

SOURCE=.\ffg_new_wrt.c
# End Source File
# Begin Source File

SOURCE=.\ffg_read.c
# End Source File
# Begin Source File

SOURCE=.\ffg_write.c
# End Source File
# Begin Source File

SOURCE=.\file.def
# End Source File
# Begin Source File

SOURCE=.\file_io.c
# End Source File
# Begin Source File

SOURCE=.\file_util.c
# End Source File
# Begin Source File

SOURCE=.\geom2_read.c
# End Source File
# Begin Source File

SOURCE=.\geom2_wrt.c
# End Source File
# Begin Source File

SOURCE=.\geom3_read.c
# End Source File
# Begin Source File

SOURCE=.\geom3_wrt.c
# End Source File
# Begin Source File

SOURCE=.\iff_io.c
# End Source File
# Begin Source File

SOURCE=.\matrix_r.c
# End Source File
# Begin Source File

SOURCE=.\matrix_w.c
# End Source File
# Begin Source File

SOURCE=.\raw_io.c
# End Source File
# Begin Source File

SOURCE=.\raw_read_fd.c
# End Source File
# Begin Source File

SOURCE=.\view_prms.c
# End Source File
# Begin Source File

SOURCE=.\wisp_write.c
# End Source File
# Begin Source File

SOURCE=..\vision\math.lib
# End Source File
# Begin Source File

SOURCE=..\math\sys.lib
# End Source File
# Begin Source File

SOURCE=.\vision.lib
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# End Group
# End Target
# End Project
