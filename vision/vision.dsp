# Microsoft Developer Studio Project File - Name="vision" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=vision - Win32 Dynamic_Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "vision.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vision.mak" CFG="vision - Win32 Dynamic_Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vision - Win32 Dynamic_Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vision - Win32 Dynamic_Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/vision", FIAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "vision - Win32 Dynamic_Debug"

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
# ADD MTL /mktyplib203
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# SUBTRACT LINK32 /pdb:none /map

!ELSEIF  "$(CFG)" == "vision - Win32 Dynamic_Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "vision__"
# PROP BASE Intermediate_Dir "vision__"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "winrelease"
# PROP Intermediate_Dir "winrelease"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MDd /W3 /Gm /GX /Zi /Od /I "\tina\include" /I "\tina\lib-pc\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /D "_COMPLEX_DEFINED" /D "__STRICT_ANSI__" /D "_PCC" /D "_DLL" /D "_WINDLL" /D "_AFXDLL" /FR /FD /c
# ADD CPP /nologo /G5 /MDd /W3 /Gm /GX /Zi /O2 /I "\tina\include" /I "\tina\lib-pc\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /D "_COMPLEX_DEFINED" /D "__STRICT_ANSI__" /D "_PCC" /D "_DLL" /D "_WINDLL" /D "_AFXDLL" /FD /c
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
# SUBTRACT BASE LINK32 /pdb:none /map
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# SUBTRACT LINK32 /pdb:none /map

!ENDIF 

# Begin Target

# Name "vision - Win32 Dynamic_Debug"
# Name "vision - Win32 Dynamic_Release"
# Begin Group "vision"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\affine_cv.c
# End Source File
# Begin Source File

SOURCE=.\basis.c
# End Source File
# Begin Source File

SOURCE=.\bnd_region.c
# End Source File
# Begin Source File

SOURCE=.\cal_smplx.c
# End Source File
# Begin Source File

SOURCE=.\cal_tsai.c
# End Source File
# Begin Source File

SOURCE=.\cal_util.c
# End Source File
# Begin Source File

SOURCE=.\cam_aim.c
# End Source File
# Begin Source File

SOURCE=.\cam_conv.c
# End Source File
# Begin Source File

SOURCE=.\cam_dstrt.c
# End Source File
# Begin Source File

SOURCE=.\cam_error.c
# End Source File
# Begin Source File

SOURCE=.\camera.c
# End Source File
# Begin Source File

SOURCE=.\canny.c
# End Source File
# Begin Source File

SOURCE=.\choose.c
# End Source File
# Begin Source File

SOURCE=.\choose_wta.c
# End Source File
# Begin Source File

SOURCE=.\circ2.c
# End Source File
# Begin Source File

SOURCE=.\circprox.c
# End Source File
# Begin Source File

SOURCE=.\con_fltr.c
# End Source File
# Begin Source File

SOURCE=.\con_klmn.c
# End Source File
# Begin Source File

SOURCE=.\con_rect.c
# End Source File
# Begin Source File

SOURCE=.\con_stat.c
# End Source File
# Begin Source File

SOURCE=.\con_test.c
# End Source File
# Begin Source File

SOURCE=.\con_util.c
# End Source File
# Begin Source File

SOURCE=.\cone.c
# End Source File
# Begin Source File

SOURCE=.\cone_trans.c
# End Source File
# Begin Source File

SOURCE=.\conic.c
# End Source File
# Begin Source File

SOURCE=.\conic2.c
# End Source File
# Begin Source File

SOURCE=.\conic3.c
# End Source File
# Begin Source File

SOURCE=.\conic_5pt.c
# End Source File
# Begin Source File

SOURCE=.\conicprox.c
# End Source File
# Begin Source File

SOURCE=.\conv_prof.c
# End Source File
# Begin Source File

SOURCE=.\conv_quat.c
# End Source File
# Begin Source File

SOURCE=.\corner.c
# End Source File
# Begin Source File

SOURCE=.\curvature.c
# End Source File
# Begin Source File

SOURCE=.\curvinvar.c
# End Source File
# Begin Source File

SOURCE=.\curvprox.c
# End Source File
# Begin Source File

SOURCE=.\disp_hist.c
# End Source File
# Begin Source File

SOURCE=.\disp_range.c
# End Source File
# Begin Source File

SOURCE=.\dp_mlist.c
# End Source File
# Begin Source File

SOURCE=.\dynamic.c
# End Source File
# Begin Source File

SOURCE=.\ecal_smplx.c
# End Source File
# Begin Source File

SOURCE=.\edge.c
# End Source File
# Begin Source File

SOURCE=.\edge_strings.c
# End Source File
# Begin Source File

SOURCE=.\edgerect.c
# End Source File
# Begin Source File

SOURCE=.\es_string3.c
# End Source File
# Begin Source File

SOURCE=.\fitline2.c
# End Source File
# Begin Source File

SOURCE=.\fitline3.c
# End Source File
# Begin Source File

SOURCE=.\geom3_from2.c
# End Source File
# Begin Source File

SOURCE=.\geom_alloc.c
# End Source File
# Begin Source File

SOURCE=.\geom_copy.c
# End Source File
# Begin Source File

SOURCE=.\geom_error.c
# End Source File
# Begin Source File

SOURCE=.\geom_flat.c
# End Source File
# Begin Source File

SOURCE=.\geom_fmt.c
# End Source File
# Begin Source File

SOURCE=.\geom_free.c
# End Source File
# Begin Source File

SOURCE=.\geom_hull.c
# End Source File
# Begin Source File

SOURCE=.\geom_label.c
# End Source File
# Begin Source File

SOURCE=.\geom_negate.c
# End Source File
# Begin Source File

SOURCE=.\geom_props.c
# End Source File
# Begin Source File

SOURCE=.\geom_trans.c
# End Source File
# Begin Source File

SOURCE=.\grid_match.c
# End Source File
# Begin Source File

SOURCE=.\gstat_cam.c
# End Source File
# Begin Source File

SOURCE=.\gstat_geom.c
# End Source File
# Begin Source File

SOURCE=.\gstat_ln2.c
# End Source File
# Begin Source File

SOURCE=.\gstat_ln3.c
# End Source File
# Begin Source File

SOURCE=.\gstat_pln.c
# End Source File
# Begin Source File

SOURCE=.\gstat_pnt2.c
# End Source File
# Begin Source File

SOURCE=.\gstat_pnt3.c
# End Source File
# Begin Source File

SOURCE=.\gstat_sclr.c
# End Source File
# Begin Source File

SOURCE=.\gstat_tf3.c
# End Source File
# Begin Source File

SOURCE=.\h_v_lines.c
# End Source File
# Begin Source File

SOURCE=.\im_add.c
# End Source File
# Begin Source File

SOURCE=.\im_apply.c
# End Source File
# Begin Source File

SOURCE=.\im_aratio.c
# End Source File
# Begin Source File

SOURCE=.\im_bshift.c
# End Source File
# Begin Source File

SOURCE=.\im_combine.c
# End Source File
# Begin Source File

SOURCE=.\im_complexify.c
# End Source File
# Begin Source File

SOURCE=.\im_conv_1d.c
# End Source File
# Begin Source File

SOURCE=.\im_create.c
# End Source File
# Begin Source File

SOURCE=.\im_deriv.c
# End Source File
# Begin Source File

SOURCE=.\im_filter.c
# End Source File
# Begin Source File

SOURCE=.\im_fourier.c
# End Source File
# Begin Source File

SOURCE=.\im_gabor.c
# End Source File
# Begin Source File

SOURCE=.\im_gauss.c
# End Source File
# Begin Source File

SOURCE=.\im_grad.c
# End Source File
# Begin Source File

SOURCE=.\im_log.c
# End Source File
# Begin Source File

SOURCE=.\im_lsf.c
# End Source File
# Begin Source File

SOURCE=.\im_max.c
# End Source File
# Begin Source File

SOURCE=.\im_median.c
# End Source File
# Begin Source File

SOURCE=.\im_morph.c
# End Source File
# Begin Source File

SOURCE=.\im_ptr.c
# End Source File
# Begin Source File

SOURCE=.\im_quad.c
# End Source File
# Begin Source File

SOURCE=.\im_rank.c
# End Source File
# Begin Source File

SOURCE=.\im_sample.c
# End Source File
# Begin Source File

SOURCE=.\im_scale.c
# End Source File
# Begin Source File

SOURCE=.\im_shade.c
# End Source File
# Begin Source File

SOURCE=.\im_sin.c
# End Source File
# Begin Source File

SOURCE=.\im_smooth.c
# End Source File
# Begin Source File

SOURCE=.\im_sqrt.c
# End Source File
# Begin Source File

SOURCE=.\im_suptype.c
# End Source File
# Begin Source File

SOURCE=.\im_surf.c
# End Source File
# Begin Source File

SOURCE=.\im_thresh.c
# End Source File
# Begin Source File

SOURCE=.\im_warp.c
# End Source File
# Begin Source File

SOURCE=.\iso_error.c
# End Source File
# Begin Source File

SOURCE=.\kalman.c
# End Source File
# Begin Source File

SOURCE=.\knots.c
# End Source File
# Begin Source File

SOURCE=.\kws.c
# End Source File
# Begin Source File

SOURCE=.\kws_run.c
# End Source File
# Begin Source File

SOURCE=.\label.c
# End Source File
# Begin Source File

SOURCE=.\line2.c
# End Source File
# Begin Source File

SOURCE=.\line2_coln.c
# End Source File
# Begin Source File

SOURCE=.\line2_fmt.c
# End Source File
# Begin Source File

SOURCE=.\line2_rect.c
# End Source File
# Begin Source File

SOURCE=.\line2_trns.c
# End Source File
# Begin Source File

SOURCE=.\line3.c
# End Source File
# Begin Source File

SOURCE=.\line3_fmt.c
# End Source File
# Begin Source File

SOURCE=.\line3_trns.c
# End Source File
# Begin Source File

SOURCE=.\linearprox.c
# End Source File
# Begin Source File

SOURCE=.\linkedges.c
# End Source File
# Begin Source File

SOURCE=.\mat_cliche.c
# End Source File
# Begin Source File

SOURCE=.\mat_con.c
# End Source File
# Begin Source File

SOURCE=.\mat_fast.c
# End Source File
# Begin Source File

SOURCE=.\mat_geom.c
# End Source File
# Begin Source File

SOURCE=.\mat_match.c
# End Source File
# Begin Source File

SOURCE=.\match.c
# End Source File
# Begin Source File

SOURCE=.\match_cnr.c
# End Source File
# Begin Source File

SOURCE=.\match_dp.c
# End Source File
# Begin Source File

SOURCE=.\match_epi.c
# End Source File
# Begin Source File

SOURCE=.\match_es.c
# End Source File
# Begin Source File

SOURCE=.\match_str.c
# End Source File
# Begin Source File

SOURCE=.\match_supp.c
# End Source File
# Begin Source File

SOURCE=.\matchable.c
# End Source File
# Begin Source File

SOURCE=.\matcher.c
# End Source File
# Begin Source File

SOURCE=.\nonmax.c
# End Source File
# Begin Source File

SOURCE=.\par_cam.c
# End Source File
# Begin Source File

SOURCE=.\par_proj.c
# End Source File
# Begin Source File

SOURCE=.\plane.c
# End Source File
# Begin Source File

SOURCE=.\plane_fmt.c
# End Source File
# Begin Source File

SOURCE=.\plane_lsq.c
# End Source File
# Begin Source File

SOURCE=.\pnt2_fmt.c
# End Source File
# Begin Source File

SOURCE=.\pnt2_rect.c
# End Source File
# Begin Source File

SOURCE=.\pnt3_fmt.c
# End Source File
# Begin Source File

SOURCE=.\pnt3_trans.c
# End Source File
# Begin Source File

SOURCE=.\point2.c
# End Source File
# Begin Source File

SOURCE=.\point3.c
# End Source File
# Begin Source File

SOURCE=.\polyprox.c
# End Source File
# Begin Source File

SOURCE=.\prof1.c
# End Source File
# Begin Source File

SOURCE=.\proj.c
# End Source File
# Begin Source File

SOURCE=.\pwrte.c
# End Source File
# Begin Source File

SOURCE=.\rect.c
# End Source File
# Begin Source File

SOURCE=.\rindex.c
# End Source File
# Begin Source File

SOURCE=.\rotation.c
# End Source File
# Begin Source File

SOURCE=.\s_mat_cnr.c
# End Source File
# Begin Source File

SOURCE=.\scal_smplx.c
# End Source File
# Begin Source File

SOURCE=.\scalar.c
# End Source File
# Begin Source File

SOURCE=.\sclr_fmt.c
# End Source File
# Begin Source File

SOURCE=.\select.c
# End Source File
# Begin Source File

SOURCE=.\set_findex.c
# End Source File
# Begin Source File

SOURCE=.\setindex.c
# End Source File
# Begin Source File

SOURCE=.\sindex.c
# End Source File
# Begin Source File

SOURCE=.\smooth_1d.c
# End Source File
# Begin Source File

SOURCE=.\splines.c
# End Source File
# Begin Source File

SOURCE=.\st_mat_cnr.c
# End Source File
# Begin Source File

SOURCE=.\state.c
# End Source File
# Begin Source File

SOURCE=.\state_add.c
# End Source File
# Begin Source File

SOURCE=.\state_crct.c
# End Source File
# Begin Source File

SOURCE=.\state_eq.c
# End Source File
# Begin Source File

SOURCE=.\state_extd.c
# End Source File
# Begin Source File

SOURCE=.\state_fmt.c
# End Source File
# Begin Source File

SOURCE=.\state_geom.c
# End Source File
# Begin Source File

SOURCE=.\state_hull.c
# End Source File
# Begin Source File

SOURCE=.\state_on.c
# End Source File
# Begin Source File

SOURCE=.\state_orth.c
# End Source File
# Begin Source File

SOURCE=.\state_par.c
# End Source File
# Begin Source File

SOURCE=.\state_tina.c
# End Source File
# Begin Source File

SOURCE=.\state_trns.c
# End Source File
# Begin Source File

SOURCE=.\str2.c
# End Source File
# Begin Source File

SOURCE=.\str3_tris.c
# End Source File
# Begin Source File

SOURCE=.\string2.c
# End Source File
# Begin Source File

SOURCE=.\string3.c
# End Source File
# Begin Source File

SOURCE=.\supp_fig.c
# End Source File
# Begin Source File

SOURCE=.\support.c
# End Source File
# Begin Source File

SOURCE=.\t_mat_cnr.c
# End Source File
# Begin Source File

SOURCE=.\tr3_fmt.c
# End Source File
# Begin Source File

SOURCE=.\transf3.c
# End Source File
# Begin Source File

SOURCE=.\transform.c
# End Source File
# Begin Source File

SOURCE=.\transplane.c
# End Source File
# Begin Source File

SOURCE=.\trnslation.c
# End Source File
# Begin Source File

SOURCE=.\ucbs2.c
# End Source File
# Begin Source File

SOURCE=.\vision.def
# End Source File
# Begin Source File

SOURCE=.\windex.c
# End Source File
# Begin Source File

SOURCE=.\wx_lists.c
# End Source File
# Begin Source File

SOURCE=.\math.lib
# End Source File
# Begin Source File

SOURCE=..\math\sys.lib
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
