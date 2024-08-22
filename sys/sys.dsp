# Microsoft Developer Studio Project File - Name="sys" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=sys - Win32 Dynamic_Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sys.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sys.mak" CFG="sys - Win32 Dynamic_Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sys - Win32 Dynamic_Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "sys - Win32 Dynamic_Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/sys", JGAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sys - Win32 Dynamic_Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "sys___Wi"
# PROP BASE Intermediate_Dir "sys___Wi"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "\tina\include" /I "\tina\lib-pc\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXEXT" /D "_COMPLEX_DEFINED" /D "__STRICT_ANSI__" /D "_PCC" /D "_DLL" /D "_MBCS" /D "__MEM_TRACE__" /D "_WINDLL" /D "_AFXDLL" /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GX /ZI /Od /I "\tina\include" /I "\tina\lib-pc\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXEXT" /D "_COMPLEX_DEFINED" /D "__STRICT_ANSI__" /D "_PCC" /D "_DLL" /D "_MBCS" /D "__MEM_TRACE__" /D "_WINDLL" /D "_AFXDLL" /FR /FD /c
# ADD BASE MTL /mktyplib203
# ADD MTL /mktyplib203
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /subsystem:windows /dll /debug /machine:I386 /def:"sys.def"
# SUBTRACT BASE LINK32 /nologo /verbose /pdb:none /map
# ADD LINK32 /subsystem:windows /dll /debug /machine:I386 /def:"sys.def"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "sys - Win32 Dynamic_Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "sys___Wi"
# PROP BASE Intermediate_Dir "sys___Wi"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "winrelease"
# PROP Intermediate_Dir "winrelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MDd /W3 /Gm /GX /Zi /Od /I "\tina\include" /I "\tina\lib-pc\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXEXT" /D "_COMPLEX_DEFINED" /D "__STRICT_ANSI__" /D "_PCC" /D "_DLL" /D "_MBCS" /D "__MEM_TRACE__" /D "_WINDLL" /D "_AFXDLL" /FR /FD /c
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GX /Zi /O2 /I "\tina\include" /I "\tina\lib-pc\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXEXT" /D "_COMPLEX_DEFINED" /D "__STRICT_ANSI__" /D "_PCC" /D "_DLL" /D "_MBCS" /D "__MEM_TRACE__" /D "_WINDLL" /D "_AFXDLL" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /mktyplib203
# ADD MTL /mktyplib203
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# SUBTRACT BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /subsystem:windows /dll /debug /machine:I386 /def:"sys.def"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /subsystem:windows /dll /debug /machine:I386 /def:"sys.def"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "sys - Win32 Dynamic_Debug"
# Name "sys - Win32 Dynamic_Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\ccopy.c
# End Source File
# Begin Source File

SOURCE=.\cliques.c
# End Source File
# Begin Source File

SOURCE=.\complex.c
# End Source File
# Begin Source File

SOURCE=.\dcopy.c
# End Source File
# Begin Source File

SOURCE=.\ddlists.c
# End Source File
# Begin Source File

SOURCE=.\ddstr.c
# End Source File
# Begin Source File

SOURCE=.\deserialise.c
# End Source File
# Begin Source File

SOURCE=.\error.c
# End Source File
# Begin Source File

SOURCE=.\fcopy.c
# End Source File
# Begin Source File

SOURCE=.\format.c
# End Source File
# Begin Source File

SOURCE=.\generic.c
# End Source File
# Begin Source File

SOURCE=.\graph.c
# End Source File
# Begin Source File

SOURCE=.\help.c
# End Source File
# Begin Source File

SOURCE=.\icopy.c
# End Source File
# Begin Source File

SOURCE=.\image.c
# End Source File
# Begin Source File

SOURCE=.\imfloatfns.c
# End Source File
# Begin Source File

SOURCE=.\imget.c
# End Source File
# Begin Source File

SOURCE=.\imput.c
# End Source File
# Begin Source File

SOURCE=.\io.c
# End Source File
# Begin Source File

SOURCE=.\label.c
# End Source File
# Begin Source File

SOURCE=.\lists.c
# End Source File
# Begin Source File

SOURCE=.\message.c
# End Source File
# Begin Source File

SOURCE=.\mprintf.c
# End Source File
# Begin Source File

SOURCE=.\ndynamic.c
# End Source File
# Begin Source File

SOURCE=.\null.c
# End Source File
# Begin Source File

SOURCE=.\pair.c
# End Source File
# Begin Source File

SOURCE=.\pipe_read.c
# End Source File
# Begin Source File

SOURCE=.\proplist.c
# End Source File
# Begin Source File

SOURCE=.\ralloc.c
# End Source File
# Begin Source File

SOURCE=.\reclist.c
# End Source File
# Begin Source File

SOURCE=.\region.c
# End Source File
# Begin Source File

SOURCE=.\serialise.c
# End Source File
# Begin Source File

SOURCE=.\sort.c
# End Source File
# Begin Source File

SOURCE=.\string.c
# End Source File
# Begin Source File

SOURCE=.\strings.c
# End Source File
# Begin Source File

SOURCE=.\swap.c
# End Source File
# Begin Source File

SOURCE=.\sys.def
# End Source File
# Begin Source File

SOURCE=.\tina_int.c
# End Source File
# Begin Source File

SOURCE=.\ts_ndynamic.c
# End Source File
# Begin Source File

SOURCE=.\ts_save_load.c
# End Source File
# Begin Source File

SOURCE=.\tsfree.c
# End Source File
# Begin Source File

SOURCE=.\tsprint.c
# End Source File
# Begin Source File

SOURCE=.\tstruct_info.c
# End Source File
# Begin Source File

SOURCE=.\util.c
# End Source File
# Begin Source File

SOURCE=.\var.c
# End Source File
# Begin Source File

SOURCE=.\vdynamic.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# End Group
# End Target
# End Project
