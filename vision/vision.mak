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
!MESSAGE NMAKE /f "vision.mak" CFG="Dynamic_Debug"
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

ALL : ".\WinRel\vision.dll" ".\WinRel\vision.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /G5 /MD /W2 /GX /YX /O1 /I "d:\tina\include" /I "d:\tina\lib-pc\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /D "_COMPLEX_DEFINED" /D "__STRICT_ANSI__" /D "_PCC" /D "_DLL" /FR /c
CPP_PROJ=/nologo /G5 /MD /W2 /GX /YX /O1 /I "d:\tina\include" /I\
 "d:\tina\lib-pc\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D\
 "_AFXEXT" /D "_COMPLEX_DEFINED" /D "__STRICT_ANSI__" /D "_PCC" /D "_DLL"\
 /FR$(INTDIR)/ /Fp$(OUTDIR)/"vision.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"vision.bsc" 
BSC32_SBRS= \
	".\WinRel\im_fourier.sbr" \
	".\WinRel\conic2.sbr" \
	".\WinRel\cone.sbr" \
	".\WinRel\rect.sbr" \
	".\WinRel\state_trns.sbr" \
	".\WinRel\ecal_smplx.sbr" \
	".\WinRel\choose_wta.sbr" \
	".\WinRel\im_aratio.sbr" \
	".\WinRel\match_es.sbr" \
	".\WinRel\bnd_region.sbr" \
	".\WinRel\es_string3.sbr" \
	".\WinRel\im_combine.sbr" \
	".\WinRel\state_tina.sbr" \
	".\WinRel\kalman.sbr" \
	".\WinRel\gstat_sclr.sbr" \
	".\WinRel\supp_fig.sbr" \
	".\WinRel\choose.sbr" \
	".\WinRel\scalar.sbr" \
	".\WinRel\plane.sbr" \
	".\WinRel\im_gauss.sbr" \
	".\WinRel\im_apply.sbr" \
	".\WinRel\knots.sbr" \
	".\WinRel\geom_fmt.sbr" \
	".\WinRel\proj.sbr" \
	".\WinRel\cone_trans.sbr" \
	".\WinRel\camera.sbr" \
	".\WinRel\pnt3_trans.sbr" \
	".\WinRel\geom_trans.sbr" \
	".\WinRel\cam_error.sbr" \
	".\WinRel\disp_range.sbr" \
	".\WinRel\state_orth.sbr" \
	".\WinRel\geom_copy.sbr" \
	".\WinRel\conic.sbr" \
	".\WinRel\con_stat.sbr" \
	".\WinRel\match_epi.sbr" \
	".\WinRel\gstat_ln3.sbr" \
	".\WinRel\cal_util.sbr" \
	".\WinRel\match_supp.sbr" \
	".\WinRel\pnt3_fmt.sbr" \
	".\WinRel\im_conv_1d.sbr" \
	".\WinRel\kws.sbr" \
	".\WinRel\fitline3.sbr" \
	".\WinRel\linearprox.sbr" \
	".\WinRel\curvinvar.sbr" \
	".\WinRel\transplane.sbr" \
	".\WinRel\fitline2.sbr" \
	".\WinRel\tr3_fmt.sbr" \
	".\WinRel\iso_error.sbr" \
	".\WinRel\im_surf.sbr" \
	".\WinRel\gstat_tf3.sbr" \
	".\WinRel\point3.sbr" \
	".\WinRel\mat_cliche.sbr" \
	".\WinRel\splines.sbr" \
	".\WinRel\sclr_fmt.sbr" \
	".\WinRel\state_fmt.sbr" \
	".\WinRel\geom_props.sbr" \
	".\WinRel\geom_free.sbr" \
	".\WinRel\par_cam.sbr" \
	".\WinRel\h_v_lines.sbr" \
	".\WinRel\kws_run.sbr" \
	".\WinRel\string2.sbr" \
	".\WinRel\im_smooth.sbr" \
	".\WinRel\sindex.sbr" \
	".\WinRel\gstat_pln.sbr" \
	".\WinRel\conicprox.sbr" \
	".\WinRel\dp_mlist.sbr" \
	".\WinRel\polyprox.sbr" \
	".\WinRel\im_median.sbr" \
	".\WinRel\st_mat_cnr.sbr" \
	".\WinRel\setindex.sbr" \
	".\WinRel\im_warp.sbr" \
	".\WinRel\string3.sbr" \
	".\WinRel\str3_tris.sbr" \
	".\WinRel\gstat_cam.sbr" \
	".\WinRel\im_morph.sbr" \
	".\WinRel\transf3.sbr" \
	".\WinRel\rindex.sbr" \
	".\WinRel\edge.sbr" \
	".\WinRel\mat_geom.sbr" \
	".\WinRel\geom_alloc.sbr" \
	".\WinRel\con_klmn.sbr" \
	".\WinRel\con_fltr.sbr" \
	".\WinRel\trnslation.sbr" \
	".\WinRel\edgerect.sbr" \
	".\WinRel\geom_error.sbr" \
	".\WinRel\rotation.sbr" \
	".\WinRel\im_lsf.sbr" \
	".\WinRel\geom_negate.sbr" \
	".\WinRel\mat_fast.sbr" \
	".\WinRel\line2_fmt.sbr" \
	".\WinRel\gstat_geom.sbr" \
	".\WinRel\str2.sbr" \
	".\WinRel\line3_trns.sbr" \
	".\WinRel\cal_smplx.sbr" \
	".\WinRel\state_par.sbr" \
	".\WinRel\geom_hull.sbr" \
	".\WinRel\conic_5pt.sbr" \
	".\WinRel\dynamic.sbr" \
	".\WinRel\smooth_1d.sbr" \
	".\WinRel\conic3.sbr" \
	".\WinRel\cam_aim.sbr" \
	".\WinRel\corner.sbr" \
	".\WinRel\s_mat_cnr.sbr" \
	".\WinRel\con_util.sbr" \
	".\WinRel\match_dp.sbr" \
	".\WinRel\im_sample.sbr" \
	".\WinRel\match_cnr.sbr" \
	".\WinRel\cam_dstrt.sbr" \
	".\WinRel\line2_rect.sbr" \
	".\WinRel\line2_coln.sbr" \
	".\WinRel\mat_match.sbr" \
	".\WinRel\state_hull.sbr" \
	".\WinRel\prof1.sbr" \
	".\WinRel\state_extd.sbr" \
	".\WinRel\conv_quat.sbr" \
	".\WinRel\matcher.sbr" \
	".\WinRel\affine_cv.sbr" \
	".\WinRel\im_ptr.sbr" \
	".\WinRel\linkedges.sbr" \
	".\WinRel\con_rect.sbr" \
	".\WinRel\plane_fmt.sbr" \
	".\WinRel\gstat_pnt2.sbr" \
	".\WinRel\pwrte.sbr" \
	".\WinRel\im_grad.sbr" \
	".\WinRel\pnt2_fmt.sbr" \
	".\WinRel\im_deriv.sbr" \
	".\WinRel\nonmax.sbr" \
	".\WinRel\ucbs2.sbr" \
	".\WinRel\mat_con.sbr" \
	".\WinRel\im_filter.sbr" \
	".\WinRel\canny.sbr" \
	".\WinRel\par_proj.sbr" \
	".\WinRel\point2.sbr" \
	".\WinRel\geom3_from2.sbr" \
	".\WinRel\state_eq.sbr" \
	".\WinRel\im_create.sbr" \
	".\WinRel\state_geom.sbr" \
	".\WinRel\state_crct.sbr" \
	".\WinRel\geom_flat.sbr" \
	".\WinRel\line3.sbr" \
	".\WinRel\support.sbr" \
	".\WinRel\plane_lsq.sbr" \
	".\WinRel\circ2.sbr" \
	".\WinRel\select.sbr" \
	".\WinRel\im_max.sbr" \
	".\WinRel\state.sbr" \
	".\WinRel\line2_trns.sbr" \
	".\WinRel\gstat_pnt3.sbr" \
	".\WinRel\edge_strings.sbr" \
	".\WinRel\curvprox.sbr" \
	".\WinRel\geom_label.sbr" \
	".\WinRel\con_test.sbr" \
	".\WinRel\circprox.sbr" \
	".\WinRel\line3_fmt.sbr" \
	".\WinRel\line2.sbr" \
	".\WinRel\windex.sbr" \
	".\WinRel\im_scale.sbr" \
	".\WinRel\match.sbr" \
	".\WinRel\state_on.sbr" \
	".\WinRel\grid_match.sbr" \
	".\WinRel\matchable.sbr" \
	".\WinRel\conv_prof.sbr" \
	".\WinRel\state_add.sbr" \
	".\WinRel\gstat_ln2.sbr" \
	".\WinRel\set_findex.sbr" \
	".\WinRel\cam_conv.sbr" \
	".\WinRel\basis.sbr" \
	".\WinRel\transform.sbr" \
	".\WinRel\im_suptype.sbr" \
	".\WinRel\cal_tsai.sbr" \
	".\WinRel\wx_lists.sbr" \
	".\WinRel\curvature.sbr" \
	".\WinRel\label.sbr" \
	".\WinRel\disp_hist.sbr" \
	".\WinRel\scal_smplx.sbr" \
	".\WinRel\match_str.sbr" \
	".\WinRel\pnt2_rect.sbr" \
	".\WinRel\t_mat_cnr.sbr" \
	".\WinRel\im_gabor.sbr" \
	".\WinRel\im_quad.sbr" \
	".\WinRel\im_shade.sbr" \
	".\WinRel\im_sin.sbr" \
	".\WinRel\im_sqrt.sbr" \
	".\WinRel\im_thresh.sbr" \
	".\WinRel\im_log.sbr" \
	".\WinRel\im_bshift.sbr" \
	".\WinRel\im_add.sbr" \
	".\WinRel\im_complexify.sbr" \
	".\WinRel\im_rank.sbr"

".\WinRel\vision.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:I386
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:I386
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"vision.pdb" /MACHINE:I386 /DEF:".\vision.def"\
 /OUT:$(OUTDIR)/"vision.dll" /IMPLIB:$(OUTDIR)/"vision.lib" 
DEF_FILE=".\vision.def"
LINK32_OBJS= \
	".\WinRel\im_fourier.obj" \
	".\WinRel\conic2.obj" \
	".\WinRel\cone.obj" \
	".\WinRel\rect.obj" \
	".\WinRel\state_trns.obj" \
	".\WinRel\ecal_smplx.obj" \
	".\WinRel\choose_wta.obj" \
	".\WinRel\im_aratio.obj" \
	".\WinRel\match_es.obj" \
	".\WinRel\bnd_region.obj" \
	".\WinRel\es_string3.obj" \
	".\WinRel\im_combine.obj" \
	".\WinRel\state_tina.obj" \
	".\WinRel\kalman.obj" \
	".\WinRel\gstat_sclr.obj" \
	".\WinRel\supp_fig.obj" \
	".\WinRel\choose.obj" \
	".\WinRel\scalar.obj" \
	".\WinRel\plane.obj" \
	".\WinRel\im_gauss.obj" \
	".\WinRel\im_apply.obj" \
	".\WinRel\knots.obj" \
	".\WinRel\geom_fmt.obj" \
	".\WinRel\proj.obj" \
	".\WinRel\cone_trans.obj" \
	".\WinRel\camera.obj" \
	".\WinRel\pnt3_trans.obj" \
	".\WinRel\geom_trans.obj" \
	".\WinRel\cam_error.obj" \
	".\WinRel\disp_range.obj" \
	".\WinRel\state_orth.obj" \
	".\WinRel\geom_copy.obj" \
	".\WinRel\conic.obj" \
	".\WinRel\con_stat.obj" \
	".\WinRel\match_epi.obj" \
	".\WinRel\gstat_ln3.obj" \
	".\WinRel\cal_util.obj" \
	".\WinRel\match_supp.obj" \
	".\WinRel\pnt3_fmt.obj" \
	".\WinRel\im_conv_1d.obj" \
	".\WinRel\kws.obj" \
	".\WinRel\fitline3.obj" \
	".\WinRel\linearprox.obj" \
	".\WinRel\curvinvar.obj" \
	".\WinRel\transplane.obj" \
	".\WinRel\fitline2.obj" \
	".\WinRel\tr3_fmt.obj" \
	".\WinRel\iso_error.obj" \
	".\WinRel\im_surf.obj" \
	".\WinRel\gstat_tf3.obj" \
	".\WinRel\point3.obj" \
	".\WinRel\mat_cliche.obj" \
	".\WinRel\splines.obj" \
	".\WinRel\sclr_fmt.obj" \
	".\WinRel\state_fmt.obj" \
	".\WinRel\geom_props.obj" \
	".\WinRel\geom_free.obj" \
	".\WinRel\par_cam.obj" \
	".\WinRel\h_v_lines.obj" \
	".\WinRel\kws_run.obj" \
	".\WinRel\string2.obj" \
	".\WinRel\im_smooth.obj" \
	".\WinRel\sindex.obj" \
	".\WinRel\gstat_pln.obj" \
	".\WinRel\conicprox.obj" \
	".\WinRel\dp_mlist.obj" \
	".\WinRel\polyprox.obj" \
	".\WinRel\im_median.obj" \
	".\WinRel\st_mat_cnr.obj" \
	".\WinRel\setindex.obj" \
	".\WinRel\im_warp.obj" \
	".\WinRel\string3.obj" \
	".\WinRel\str3_tris.obj" \
	".\WinRel\gstat_cam.obj" \
	".\WinRel\im_morph.obj" \
	".\WinRel\transf3.obj" \
	".\WinRel\rindex.obj" \
	".\WinRel\edge.obj" \
	".\WinRel\mat_geom.obj" \
	".\WinRel\geom_alloc.obj" \
	".\WinRel\con_klmn.obj" \
	".\WinRel\con_fltr.obj" \
	".\WinRel\trnslation.obj" \
	".\WinRel\edgerect.obj" \
	".\WinRel\geom_error.obj" \
	".\WinRel\rotation.obj" \
	".\WinRel\im_lsf.obj" \
	".\WinRel\geom_negate.obj" \
	".\WinRel\mat_fast.obj" \
	".\WinRel\line2_fmt.obj" \
	".\WinRel\gstat_geom.obj" \
	".\WinRel\str2.obj" \
	".\WinRel\line3_trns.obj" \
	".\WinRel\cal_smplx.obj" \
	".\WinRel\state_par.obj" \
	".\WinRel\geom_hull.obj" \
	".\WinRel\conic_5pt.obj" \
	".\WinRel\dynamic.obj" \
	".\WinRel\smooth_1d.obj" \
	".\WinRel\conic3.obj" \
	".\WinRel\cam_aim.obj" \
	".\WinRel\corner.obj" \
	".\WinRel\s_mat_cnr.obj" \
	".\WinRel\con_util.obj" \
	".\WinRel\match_dp.obj" \
	".\WinRel\im_sample.obj" \
	".\WinRel\match_cnr.obj" \
	".\WinRel\cam_dstrt.obj" \
	".\WinRel\line2_rect.obj" \
	".\WinRel\line2_coln.obj" \
	".\WinRel\mat_match.obj" \
	".\WinRel\state_hull.obj" \
	".\WinRel\prof1.obj" \
	".\WinRel\state_extd.obj" \
	".\WinRel\conv_quat.obj" \
	".\WinRel\matcher.obj" \
	".\WinRel\affine_cv.obj" \
	".\WinRel\im_ptr.obj" \
	".\WinRel\linkedges.obj" \
	".\WinRel\con_rect.obj" \
	".\WinRel\plane_fmt.obj" \
	".\WinRel\gstat_pnt2.obj" \
	".\WinRel\pwrte.obj" \
	".\WinRel\im_grad.obj" \
	".\WinRel\pnt2_fmt.obj" \
	".\WinRel\im_deriv.obj" \
	".\WinRel\nonmax.obj" \
	".\WinRel\ucbs2.obj" \
	".\WinRel\mat_con.obj" \
	".\WinRel\im_filter.obj" \
	".\WinRel\canny.obj" \
	".\WinRel\par_proj.obj" \
	".\WinRel\point2.obj" \
	".\WinRel\geom3_from2.obj" \
	".\WinRel\state_eq.obj" \
	".\WinRel\im_create.obj" \
	".\WinRel\state_geom.obj" \
	".\WinRel\state_crct.obj" \
	".\WinRel\geom_flat.obj" \
	".\WinRel\line3.obj" \
	".\WinRel\support.obj" \
	".\WinRel\plane_lsq.obj" \
	".\WinRel\circ2.obj" \
	".\WinRel\select.obj" \
	".\WinRel\im_max.obj" \
	".\WinRel\state.obj" \
	".\WinRel\line2_trns.obj" \
	".\WinRel\gstat_pnt3.obj" \
	".\WinRel\edge_strings.obj" \
	".\WinRel\curvprox.obj" \
	".\WinRel\geom_label.obj" \
	".\WinRel\con_test.obj" \
	".\WinRel\circprox.obj" \
	".\WinRel\line3_fmt.obj" \
	".\WinRel\line2.obj" \
	".\WinRel\windex.obj" \
	".\WinRel\im_scale.obj" \
	".\WinRel\match.obj" \
	".\WinRel\state_on.obj" \
	".\WinRel\grid_match.obj" \
	".\WinRel\matchable.obj" \
	".\WinRel\conv_prof.obj" \
	".\WinRel\state_add.obj" \
	".\WinRel\gstat_ln2.obj" \
	".\WinRel\set_findex.obj" \
	".\WinRel\cam_conv.obj" \
	".\WinRel\basis.obj" \
	".\WinRel\transform.obj" \
	".\WinRel\im_suptype.obj" \
	".\WinRel\cal_tsai.obj" \
	".\WinRel\wx_lists.obj" \
	".\WinRel\curvature.obj" \
	".\WinRel\label.obj" \
	".\WinRel\disp_hist.obj" \
	".\WinRel\scal_smplx.obj" \
	".\WinRel\match_str.obj" \
	".\WinRel\pnt2_rect.obj" \
	".\WinRel\t_mat_cnr.obj" \
	".\WinRel\im_gabor.obj" \
	".\WinRel\im_quad.obj" \
	".\WinRel\im_shade.obj" \
	".\WinRel\im_sin.obj" \
	".\WinRel\im_sqrt.obj" \
	".\WinRel\im_thresh.obj" \
	".\WinRel\im_log.obj" \
	".\WinRel\im_bshift.obj" \
	".\WinRel\im_add.obj" \
	".\WinRel\im_complexify.obj" \
	".\WinRel\im_rank.obj" \
	"\lib-pc\sys\windebug\sys.lib" \
	"\lib-pc\math\windebug\math.lib"

".\WinRel\vision.dll" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

ALL : ".\WinDebug\vision.dll" ".\WinDebug\vision.bsc"

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /I "d:\tina\include" /I "d:\tina\lib-pc\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXEXT" /D "_COMPLEX_DEFINED" /D "__STRICT_ANSI__" /D "_PCC" /D "_DLL" /FR /c
CPP_PROJ=/nologo /MD /W3 /GX /Zi /Od /I "d:\tina\include" /I\
 "d:\tina\lib-pc\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D\
 "_AFXEXT" /D "_COMPLEX_DEFINED" /D "__STRICT_ANSI__" /D "_PCC" /D "_DLL"\
 /FR$(INTDIR)/ /Fo$(INTDIR)/ /Fd$(OUTDIR)/"vision.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"vision.bsc" 
BSC32_SBRS= \
	".\WinDebug\im_fourier.sbr" \
	".\WinDebug\conic2.sbr" \
	".\WinDebug\cone.sbr" \
	".\WinDebug\rect.sbr" \
	".\WinDebug\state_trns.sbr" \
	".\WinDebug\ecal_smplx.sbr" \
	".\WinDebug\choose_wta.sbr" \
	".\WinDebug\im_aratio.sbr" \
	".\WinDebug\match_es.sbr" \
	".\WinDebug\bnd_region.sbr" \
	".\WinDebug\es_string3.sbr" \
	".\WinDebug\im_combine.sbr" \
	".\WinDebug\state_tina.sbr" \
	".\WinDebug\kalman.sbr" \
	".\WinDebug\gstat_sclr.sbr" \
	".\WinDebug\supp_fig.sbr" \
	".\WinDebug\choose.sbr" \
	".\WinDebug\scalar.sbr" \
	".\WinDebug\plane.sbr" \
	".\WinDebug\im_gauss.sbr" \
	".\WinDebug\im_apply.sbr" \
	".\WinDebug\knots.sbr" \
	".\WinDebug\geom_fmt.sbr" \
	".\WinDebug\proj.sbr" \
	".\WinDebug\cone_trans.sbr" \
	".\WinDebug\camera.sbr" \
	".\WinDebug\pnt3_trans.sbr" \
	".\WinDebug\geom_trans.sbr" \
	".\WinDebug\cam_error.sbr" \
	".\WinDebug\disp_range.sbr" \
	".\WinDebug\state_orth.sbr" \
	".\WinDebug\geom_copy.sbr" \
	".\WinDebug\conic.sbr" \
	".\WinDebug\con_stat.sbr" \
	".\WinDebug\match_epi.sbr" \
	".\WinDebug\gstat_ln3.sbr" \
	".\WinDebug\cal_util.sbr" \
	".\WinDebug\match_supp.sbr" \
	".\WinDebug\pnt3_fmt.sbr" \
	".\WinDebug\im_conv_1d.sbr" \
	".\WinDebug\kws.sbr" \
	".\WinDebug\fitline3.sbr" \
	".\WinDebug\linearprox.sbr" \
	".\WinDebug\curvinvar.sbr" \
	".\WinDebug\transplane.sbr" \
	".\WinDebug\fitline2.sbr" \
	".\WinDebug\tr3_fmt.sbr" \
	".\WinDebug\iso_error.sbr" \
	".\WinDebug\im_surf.sbr" \
	".\WinDebug\gstat_tf3.sbr" \
	".\WinDebug\point3.sbr" \
	".\WinDebug\mat_cliche.sbr" \
	".\WinDebug\splines.sbr" \
	".\WinDebug\sclr_fmt.sbr" \
	".\WinDebug\state_fmt.sbr" \
	".\WinDebug\geom_props.sbr" \
	".\WinDebug\geom_free.sbr" \
	".\WinDebug\par_cam.sbr" \
	".\WinDebug\h_v_lines.sbr" \
	".\WinDebug\kws_run.sbr" \
	".\WinDebug\string2.sbr" \
	".\WinDebug\im_smooth.sbr" \
	".\WinDebug\sindex.sbr" \
	".\WinDebug\gstat_pln.sbr" \
	".\WinDebug\conicprox.sbr" \
	".\WinDebug\dp_mlist.sbr" \
	".\WinDebug\polyprox.sbr" \
	".\WinDebug\im_median.sbr" \
	".\WinDebug\st_mat_cnr.sbr" \
	".\WinDebug\setindex.sbr" \
	".\WinDebug\im_warp.sbr" \
	".\WinDebug\string3.sbr" \
	".\WinDebug\str3_tris.sbr" \
	".\WinDebug\gstat_cam.sbr" \
	".\WinDebug\im_morph.sbr" \
	".\WinDebug\transf3.sbr" \
	".\WinDebug\rindex.sbr" \
	".\WinDebug\edge.sbr" \
	".\WinDebug\mat_geom.sbr" \
	".\WinDebug\geom_alloc.sbr" \
	".\WinDebug\con_klmn.sbr" \
	".\WinDebug\con_fltr.sbr" \
	".\WinDebug\trnslation.sbr" \
	".\WinDebug\edgerect.sbr" \
	".\WinDebug\geom_error.sbr" \
	".\WinDebug\rotation.sbr" \
	".\WinDebug\im_lsf.sbr" \
	".\WinDebug\geom_negate.sbr" \
	".\WinDebug\mat_fast.sbr" \
	".\WinDebug\line2_fmt.sbr" \
	".\WinDebug\gstat_geom.sbr" \
	".\WinDebug\str2.sbr" \
	".\WinDebug\line3_trns.sbr" \
	".\WinDebug\cal_smplx.sbr" \
	".\WinDebug\state_par.sbr" \
	".\WinDebug\geom_hull.sbr" \
	".\WinDebug\conic_5pt.sbr" \
	".\WinDebug\dynamic.sbr" \
	".\WinDebug\smooth_1d.sbr" \
	".\WinDebug\conic3.sbr" \
	".\WinDebug\cam_aim.sbr" \
	".\WinDebug\corner.sbr" \
	".\WinDebug\s_mat_cnr.sbr" \
	".\WinDebug\con_util.sbr" \
	".\WinDebug\match_dp.sbr" \
	".\WinDebug\im_sample.sbr" \
	".\WinDebug\match_cnr.sbr" \
	".\WinDebug\cam_dstrt.sbr" \
	".\WinDebug\line2_rect.sbr" \
	".\WinDebug\line2_coln.sbr" \
	".\WinDebug\mat_match.sbr" \
	".\WinDebug\state_hull.sbr" \
	".\WinDebug\prof1.sbr" \
	".\WinDebug\state_extd.sbr" \
	".\WinDebug\conv_quat.sbr" \
	".\WinDebug\matcher.sbr" \
	".\WinDebug\affine_cv.sbr" \
	".\WinDebug\im_ptr.sbr" \
	".\WinDebug\linkedges.sbr" \
	".\WinDebug\con_rect.sbr" \
	".\WinDebug\plane_fmt.sbr" \
	".\WinDebug\gstat_pnt2.sbr" \
	".\WinDebug\pwrte.sbr" \
	".\WinDebug\im_grad.sbr" \
	".\WinDebug\pnt2_fmt.sbr" \
	".\WinDebug\im_deriv.sbr" \
	".\WinDebug\nonmax.sbr" \
	".\WinDebug\ucbs2.sbr" \
	".\WinDebug\mat_con.sbr" \
	".\WinDebug\im_filter.sbr" \
	".\WinDebug\canny.sbr" \
	".\WinDebug\par_proj.sbr" \
	".\WinDebug\point2.sbr" \
	".\WinDebug\geom3_from2.sbr" \
	".\WinDebug\state_eq.sbr" \
	".\WinDebug\im_create.sbr" \
	".\WinDebug\state_geom.sbr" \
	".\WinDebug\state_crct.sbr" \
	".\WinDebug\geom_flat.sbr" \
	".\WinDebug\line3.sbr" \
	".\WinDebug\support.sbr" \
	".\WinDebug\plane_lsq.sbr" \
	".\WinDebug\circ2.sbr" \
	".\WinDebug\select.sbr" \
	".\WinDebug\im_max.sbr" \
	".\WinDebug\state.sbr" \
	".\WinDebug\line2_trns.sbr" \
	".\WinDebug\gstat_pnt3.sbr" \
	".\WinDebug\edge_strings.sbr" \
	".\WinDebug\curvprox.sbr" \
	".\WinDebug\geom_label.sbr" \
	".\WinDebug\con_test.sbr" \
	".\WinDebug\circprox.sbr" \
	".\WinDebug\line3_fmt.sbr" \
	".\WinDebug\line2.sbr" \
	".\WinDebug\windex.sbr" \
	".\WinDebug\im_scale.sbr" \
	".\WinDebug\match.sbr" \
	".\WinDebug\state_on.sbr" \
	".\WinDebug\grid_match.sbr" \
	".\WinDebug\matchable.sbr" \
	".\WinDebug\conv_prof.sbr" \
	".\WinDebug\state_add.sbr" \
	".\WinDebug\gstat_ln2.sbr" \
	".\WinDebug\set_findex.sbr" \
	".\WinDebug\cam_conv.sbr" \
	".\WinDebug\basis.sbr" \
	".\WinDebug\transform.sbr" \
	".\WinDebug\im_suptype.sbr" \
	".\WinDebug\cal_tsai.sbr" \
	".\WinDebug\wx_lists.sbr" \
	".\WinDebug\curvature.sbr" \
	".\WinDebug\label.sbr" \
	".\WinDebug\disp_hist.sbr" \
	".\WinDebug\scal_smplx.sbr" \
	".\WinDebug\match_str.sbr" \
	".\WinDebug\pnt2_rect.sbr" \
	".\WinDebug\t_mat_cnr.sbr" \
	".\WinDebug\im_gabor.sbr" \
	".\WinDebug\im_quad.sbr" \
	".\WinDebug\im_shade.sbr" \
	".\WinDebug\im_sin.sbr" \
	".\WinDebug\im_sqrt.sbr" \
	".\WinDebug\im_thresh.sbr" \
	".\WinDebug\im_log.sbr" \
	".\WinDebug\im_bshift.sbr" \
	".\WinDebug\im_add.sbr" \
	".\WinDebug\im_complexify.sbr" \
	".\WinDebug\im_rank.sbr"

".\WinDebug\vision.bsc" : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:I386
# ADD LINK32 /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:I386
# SUBTRACT LINK32 /PDB:none /MAP
LINK32_FLAGS=/NOLOGO /SUBSYSTEM:windows /DLL /INCREMENTAL:yes\
 /PDB:$(OUTDIR)/"vision.pdb" /DEBUG /MACHINE:I386 /DEF:".\vision.def"\
 /OUT:$(OUTDIR)/"vision.dll" /IMPLIB:$(OUTDIR)/"vision.lib" 
DEF_FILE=".\vision.def"
LINK32_OBJS= \
	".\WinDebug\im_fourier.obj" \
	".\WinDebug\conic2.obj" \
	".\WinDebug\cone.obj" \
	".\WinDebug\rect.obj" \
	".\WinDebug\state_trns.obj" \
	".\WinDebug\ecal_smplx.obj" \
	".\WinDebug\choose_wta.obj" \
	".\WinDebug\im_aratio.obj" \
	".\WinDebug\match_es.obj" \
	".\WinDebug\bnd_region.obj" \
	".\WinDebug\es_string3.obj" \
	".\WinDebug\im_combine.obj" \
	".\WinDebug\state_tina.obj" \
	".\WinDebug\kalman.obj" \
	".\WinDebug\gstat_sclr.obj" \
	".\WinDebug\supp_fig.obj" \
	".\WinDebug\choose.obj" \
	".\WinDebug\scalar.obj" \
	".\WinDebug\plane.obj" \
	".\WinDebug\im_gauss.obj" \
	".\WinDebug\im_apply.obj" \
	".\WinDebug\knots.obj" \
	".\WinDebug\geom_fmt.obj" \
	".\WinDebug\proj.obj" \
	".\WinDebug\cone_trans.obj" \
	".\WinDebug\camera.obj" \
	".\WinDebug\pnt3_trans.obj" \
	".\WinDebug\geom_trans.obj" \
	".\WinDebug\cam_error.obj" \
	".\WinDebug\disp_range.obj" \
	".\WinDebug\state_orth.obj" \
	".\WinDebug\geom_copy.obj" \
	".\WinDebug\conic.obj" \
	".\WinDebug\con_stat.obj" \
	".\WinDebug\match_epi.obj" \
	".\WinDebug\gstat_ln3.obj" \
	".\WinDebug\cal_util.obj" \
	".\WinDebug\match_supp.obj" \
	".\WinDebug\pnt3_fmt.obj" \
	".\WinDebug\im_conv_1d.obj" \
	".\WinDebug\kws.obj" \
	".\WinDebug\fitline3.obj" \
	".\WinDebug\linearprox.obj" \
	".\WinDebug\curvinvar.obj" \
	".\WinDebug\transplane.obj" \
	".\WinDebug\fitline2.obj" \
	".\WinDebug\tr3_fmt.obj" \
	".\WinDebug\iso_error.obj" \
	".\WinDebug\im_surf.obj" \
	".\WinDebug\gstat_tf3.obj" \
	".\WinDebug\point3.obj" \
	".\WinDebug\mat_cliche.obj" \
	".\WinDebug\splines.obj" \
	".\WinDebug\sclr_fmt.obj" \
	".\WinDebug\state_fmt.obj" \
	".\WinDebug\geom_props.obj" \
	".\WinDebug\geom_free.obj" \
	".\WinDebug\par_cam.obj" \
	".\WinDebug\h_v_lines.obj" \
	".\WinDebug\kws_run.obj" \
	".\WinDebug\string2.obj" \
	".\WinDebug\im_smooth.obj" \
	".\WinDebug\sindex.obj" \
	".\WinDebug\gstat_pln.obj" \
	".\WinDebug\conicprox.obj" \
	".\WinDebug\dp_mlist.obj" \
	".\WinDebug\polyprox.obj" \
	".\WinDebug\im_median.obj" \
	".\WinDebug\st_mat_cnr.obj" \
	".\WinDebug\setindex.obj" \
	".\WinDebug\im_warp.obj" \
	".\WinDebug\string3.obj" \
	".\WinDebug\str3_tris.obj" \
	".\WinDebug\gstat_cam.obj" \
	".\WinDebug\im_morph.obj" \
	".\WinDebug\transf3.obj" \
	".\WinDebug\rindex.obj" \
	".\WinDebug\edge.obj" \
	".\WinDebug\mat_geom.obj" \
	".\WinDebug\geom_alloc.obj" \
	".\WinDebug\con_klmn.obj" \
	".\WinDebug\con_fltr.obj" \
	".\WinDebug\trnslation.obj" \
	".\WinDebug\edgerect.obj" \
	".\WinDebug\geom_error.obj" \
	".\WinDebug\rotation.obj" \
	".\WinDebug\im_lsf.obj" \
	".\WinDebug\geom_negate.obj" \
	".\WinDebug\mat_fast.obj" \
	".\WinDebug\line2_fmt.obj" \
	".\WinDebug\gstat_geom.obj" \
	".\WinDebug\str2.obj" \
	".\WinDebug\line3_trns.obj" \
	".\WinDebug\cal_smplx.obj" \
	".\WinDebug\state_par.obj" \
	".\WinDebug\geom_hull.obj" \
	".\WinDebug\conic_5pt.obj" \
	".\WinDebug\dynamic.obj" \
	".\WinDebug\smooth_1d.obj" \
	".\WinDebug\conic3.obj" \
	".\WinDebug\cam_aim.obj" \
	".\WinDebug\corner.obj" \
	".\WinDebug\s_mat_cnr.obj" \
	".\WinDebug\con_util.obj" \
	".\WinDebug\match_dp.obj" \
	".\WinDebug\im_sample.obj" \
	".\WinDebug\match_cnr.obj" \
	".\WinDebug\cam_dstrt.obj" \
	".\WinDebug\line2_rect.obj" \
	".\WinDebug\line2_coln.obj" \
	".\WinDebug\mat_match.obj" \
	".\WinDebug\state_hull.obj" \
	".\WinDebug\prof1.obj" \
	".\WinDebug\state_extd.obj" \
	".\WinDebug\conv_quat.obj" \
	".\WinDebug\matcher.obj" \
	".\WinDebug\affine_cv.obj" \
	".\WinDebug\im_ptr.obj" \
	".\WinDebug\linkedges.obj" \
	".\WinDebug\con_rect.obj" \
	".\WinDebug\plane_fmt.obj" \
	".\WinDebug\gstat_pnt2.obj" \
	".\WinDebug\pwrte.obj" \
	".\WinDebug\im_grad.obj" \
	".\WinDebug\pnt2_fmt.obj" \
	".\WinDebug\im_deriv.obj" \
	".\WinDebug\nonmax.obj" \
	".\WinDebug\ucbs2.obj" \
	".\WinDebug\mat_con.obj" \
	".\WinDebug\im_filter.obj" \
	".\WinDebug\canny.obj" \
	".\WinDebug\par_proj.obj" \
	".\WinDebug\point2.obj" \
	".\WinDebug\geom3_from2.obj" \
	".\WinDebug\state_eq.obj" \
	".\WinDebug\im_create.obj" \
	".\WinDebug\state_geom.obj" \
	".\WinDebug\state_crct.obj" \
	".\WinDebug\geom_flat.obj" \
	".\WinDebug\line3.obj" \
	".\WinDebug\support.obj" \
	".\WinDebug\plane_lsq.obj" \
	".\WinDebug\circ2.obj" \
	".\WinDebug\select.obj" \
	".\WinDebug\im_max.obj" \
	".\WinDebug\state.obj" \
	".\WinDebug\line2_trns.obj" \
	".\WinDebug\gstat_pnt3.obj" \
	".\WinDebug\edge_strings.obj" \
	".\WinDebug\curvprox.obj" \
	".\WinDebug\geom_label.obj" \
	".\WinDebug\con_test.obj" \
	".\WinDebug\circprox.obj" \
	".\WinDebug\line3_fmt.obj" \
	".\WinDebug\line2.obj" \
	".\WinDebug\windex.obj" \
	".\WinDebug\im_scale.obj" \
	".\WinDebug\match.obj" \
	".\WinDebug\state_on.obj" \
	".\WinDebug\grid_match.obj" \
	".\WinDebug\matchable.obj" \
	".\WinDebug\conv_prof.obj" \
	".\WinDebug\state_add.obj" \
	".\WinDebug\gstat_ln2.obj" \
	".\WinDebug\set_findex.obj" \
	".\WinDebug\cam_conv.obj" \
	".\WinDebug\basis.obj" \
	".\WinDebug\transform.obj" \
	".\WinDebug\im_suptype.obj" \
	".\WinDebug\cal_tsai.obj" \
	".\WinDebug\wx_lists.obj" \
	".\WinDebug\curvature.obj" \
	".\WinDebug\label.obj" \
	".\WinDebug\disp_hist.obj" \
	".\WinDebug\scal_smplx.obj" \
	".\WinDebug\match_str.obj" \
	".\WinDebug\pnt2_rect.obj" \
	".\WinDebug\t_mat_cnr.obj" \
	".\WinDebug\im_gabor.obj" \
	".\WinDebug\im_quad.obj" \
	".\WinDebug\im_shade.obj" \
	".\WinDebug\im_sin.obj" \
	".\WinDebug\im_sqrt.obj" \
	".\WinDebug\im_thresh.obj" \
	".\WinDebug\im_log.obj" \
	".\WinDebug\im_bshift.obj" \
	".\WinDebug\im_add.obj" \
	".\WinDebug\im_complexify.obj" \
	".\WinDebug\im_rank.obj" \
	"\lib-pc\sys\windebug\sys.lib" \
	"\lib-pc\math\windebug\math.lib"

".\WinDebug\vision.dll" : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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
# Begin Group "vision"

################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_fourier.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_fourier.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_fourier.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\curve2\conic2.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\conic2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\conic2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\cone\cone.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\cone.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\cone.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\camera\rect.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\rect.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\rect.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geomstat\constraint\state_trns.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\state_trns.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\state_trns.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\calib\ecal_smplx.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\ecal_smplx.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\ecal_smplx.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\stereo\choose_wta.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\choose_wta.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\choose_wta.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_aratio.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_aratio.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_aratio.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\match\match_es.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\match_es.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\match_es.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\edge\bnd_region.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\bnd_region.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\bnd_region.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\curve3\es_string3.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\es_string3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\es_string3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_combine.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_combine.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_combine.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geomstat\state\state_tina.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\state_tina.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\state_tina.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geomstat\kalman\kalman.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\kalman.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\kalman.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geomstat\geom\gstat_sclr.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\gstat_sclr.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\gstat_sclr.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\stereo\supp_fig.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\supp_fig.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\supp_fig.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\stereo\choose.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\choose.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\choose.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\scalar\scalar.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\scalar.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\scalar.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\plane\plane.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\plane.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\plane.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_gauss.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_gauss.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_gauss.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_apply.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_apply.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_apply.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\spline\knots.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\knots.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\knots.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geom\geom_fmt.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\geom_fmt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\geom_fmt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\camera\proj.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\proj.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\proj.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\cone\cone_trans.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\cone_trans.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\cone_trans.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\camera\camera.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\camera.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\camera.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\point3\pnt3_trans.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\pnt3_trans.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\pnt3_trans.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geom\geom_trans.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\geom_trans.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\geom_trans.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\calib\cam_error.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\cam_error.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\cam_error.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\stereo\disp_range.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\disp_range.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\disp_range.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geomstat\constraint\state_orth.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\state_orth.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\state_orth.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geom\geom_copy.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\geom_copy.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\geom_copy.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\conic\conic.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\conic.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\conic.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\conic\con_stat.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\con_stat.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\con_stat.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\stereo\match_epi.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\match_epi.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\match_epi.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geomstat\geom\gstat_ln3.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\gstat_ln3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\gstat_ln3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\calib\cal_util.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\cal_util.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\cal_util.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\stereo\match_supp.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\match_supp.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\match_supp.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\point3\pnt3_fmt.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\pnt3_fmt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\pnt3_fmt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_conv_1d.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_conv_1d.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_conv_1d.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\spline\kws.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\kws.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\kws.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\line3\fitline3.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\fitline3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\fitline3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\line2\linearprox.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\linearprox.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\linearprox.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\curve2\curvinvar.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\curvinvar.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\curvinvar.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\plane\transplane.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\transplane.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\transplane.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\line2\fitline2.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\fitline2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\fitline2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\transf3\tr3_fmt.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\tr3_fmt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\tr3_fmt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\matcher\iso_error.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\iso_error.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\iso_error.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_surf.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_surf.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_surf.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geomstat\geom\gstat_tf3.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\gstat_tf3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\gstat_tf3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\point3\point3.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\point3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\point3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\matcher\mat_cliche.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_cliche.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_cliche.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\curve2\splines.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\splines.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\splines.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\scalar\sclr_fmt.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\sclr_fmt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\sclr_fmt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geomstat\state\state_fmt.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\state_fmt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\state_fmt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geom\geom_props.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\geom_props.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\geom_props.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geom\geom_free.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\geom_free.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\geom_free.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\camera\par_cam.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\par_cam.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\par_cam.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\calib\h_v_lines.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\h_v_lines.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\h_v_lines.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\spline\kws_run.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\kws_run.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\kws_run.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\curve2\string2.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\string2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\string2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_smooth.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_smooth.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_smooth.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\index\sindex.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\sindex.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\sindex.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geomstat\geom\gstat_pln.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\gstat_pln.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\gstat_pln.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\curve2\conicprox.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\conicprox.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\conicprox.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\match\dp_mlist.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\dp_mlist.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\dp_mlist.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\line2\polyprox.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\polyprox.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\polyprox.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_median.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_median.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_median.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\corner\st_mat_cnr.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\st_mat_cnr.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\st_mat_cnr.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\stereo\setindex.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\setindex.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\setindex.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_warp.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_warp.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_warp.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\curve3\string3.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\string3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\string3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\curve3\str3_tris.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\str3_tris.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\str3_tris.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geomstat\camera\gstat_cam.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\gstat_cam.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\gstat_cam.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_morph.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_morph.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_morph.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\transf3\transf3.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\transf3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\transf3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\index\rindex.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\rindex.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\rindex.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\edge\edge.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\edge.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\edge.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\matcher\mat_geom.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_geom.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_geom.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geom\geom_alloc.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\geom_alloc.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\geom_alloc.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\conic\con_klmn.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\con_klmn.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\con_klmn.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\conic\con_fltr.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\con_fltr.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\con_fltr.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\transform\trnslation.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\trnslation.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\trnslation.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\edge\edgerect.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\edgerect.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\edgerect.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geom\geom_error.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\geom_error.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\geom_error.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\transform\rotation.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\rotation.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\rotation.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_lsf.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_lsf.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_lsf.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geom\geom_negate.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\geom_negate.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\geom_negate.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\stereo\mat_fast.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_fast.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_fast.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\line2\line2_fmt.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\line2_fmt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\line2_fmt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geomstat\geom\gstat_geom.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\gstat_geom.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\gstat_geom.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\edge\str2.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\str2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\str2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\line3\line3_trns.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\line3_trns.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\line3_trns.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\calib\cal_smplx.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\cal_smplx.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\cal_smplx.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geomstat\constraint\state_par.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\state_par.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\state_par.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geom\geom_hull.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\geom_hull.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\geom_hull.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\conic\conic_5pt.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\conic_5pt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\conic_5pt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\match\dynamic.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\dynamic.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\dynamic.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\smooth_1d.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\smooth_1d.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\smooth_1d.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\curve3\conic3.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\conic3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\conic3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\camera\cam_aim.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\cam_aim.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\cam_aim.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\corner.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\corner.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\corner.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\corner\s_mat_cnr.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\s_mat_cnr.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\s_mat_cnr.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\conic\con_util.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\con_util.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\con_util.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\stereo\match_dp.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\match_dp.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\match_dp.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_sample.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_sample.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_sample.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\corner\match_cnr.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\match_cnr.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\match_cnr.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\camera\cam_dstrt.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\cam_dstrt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\cam_dstrt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\line2\line2_rect.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\line2_rect.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\line2_rect.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\line2\line2_coln.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\line2_coln.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\line2_coln.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\matcher\mat_match.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_match.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_match.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geomstat\state\state_hull.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\state_hull.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\state_hull.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\prof1.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\prof1.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\prof1.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geomstat\constraint\state_extd.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\state_extd.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\state_extd.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\calib\conv_quat.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\conv_quat.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\conv_quat.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\matcher\matcher.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\matcher.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\matcher.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\curve3\affine_cv.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\affine_cv.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\affine_cv.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_ptr.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_ptr.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_ptr.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\edge\linkedges.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\linkedges.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\linkedges.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\conic\con_rect.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\con_rect.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\con_rect.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\plane\plane_fmt.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\plane_fmt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\plane_fmt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geomstat\geom\gstat_pnt2.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\gstat_pnt2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\gstat_pnt2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\matcher\pwrte.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\pwrte.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\pwrte.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_grad.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_grad.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_grad.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\point2\pnt2_fmt.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\pnt2_fmt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\pnt2_fmt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_deriv.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_deriv.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_deriv.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\nonmax.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\nonmax.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\nonmax.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\spline\ucbs2.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\ucbs2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\ucbs2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\matcher\mat_con.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\mat_con.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\mat_con.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_filter.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_filter.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_filter.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\canny.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\canny.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\canny.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\camera\par_proj.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\par_proj.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\par_proj.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\point2\point2.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\point2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\point2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geom\geom3_from2.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\geom3_from2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\geom3_from2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geomstat\constraint\state_eq.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\state_eq.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\state_eq.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_create.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_create.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_create.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geomstat\state\state_geom.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\state_geom.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\state_geom.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geomstat\state\state_crct.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\state_crct.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\state_crct.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geom\geom_flat.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\geom_flat.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\geom_flat.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\line3\line3.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\line3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\line3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\stereo\support.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\support.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\support.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\plane\plane_lsq.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\plane_lsq.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\plane_lsq.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\curve2\circ2.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\circ2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\circ2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\stereo\select.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\select.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\select.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_max.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_max.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_max.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geomstat\state\state.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\state.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\state.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\line2\line2_trns.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\line2_trns.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\line2_trns.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geomstat\geom\gstat_pnt3.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\gstat_pnt3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\gstat_pnt3.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\edge\edge_strings.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\edge_strings.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\edge_strings.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\curve2\curvprox.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\curvprox.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\curvprox.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geom\geom_label.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\geom_label.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\geom_label.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\curve2\con_test.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\con_test.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\con_test.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\curve2\circprox.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\circprox.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\circprox.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\line3\line3_fmt.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\line3_fmt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\line3_fmt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\line2\line2.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\line2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\line2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\index\windex.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\windex.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\windex.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_scale.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_scale.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_scale.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\match\match.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\match.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\match.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geomstat\constraint\state_on.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\state_on.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\state_on.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\calib\grid_match.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\grid_match.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\grid_match.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\stereo\matchable.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\matchable.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\matchable.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\conv_prof.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\conv_prof.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\conv_prof.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geomstat\constraint\state_add.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\state_add.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\state_add.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geomstat\geom\gstat_ln2.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\gstat_ln2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\gstat_ln2.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\corner\set_findex.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\set_findex.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\set_findex.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\calib\cam_conv.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\cam_conv.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\cam_conv.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\geomstat\basis\basis.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\basis.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\basis.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\transform\transform.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\transform.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\transform.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_suptype.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_suptype.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_suptype.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\calib\cal_tsai.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\cal_tsai.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\cal_tsai.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\index\wx_lists.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\wx_lists.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\wx_lists.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\curve2\curvature.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\curvature.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\curvature.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\util\label.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\label.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\label.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\stereo\disp_hist.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\disp_hist.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\disp_hist.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\calib\scal_smplx.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\scal_smplx.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\scal_smplx.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\stereo\match_str.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\match_str.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\match_str.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\point2\pnt2_rect.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\pnt2_rect.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\pnt2_rect.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\corner\t_mat_cnr.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\t_mat_cnr.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\t_mat_cnr.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_gabor.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_gabor.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_gabor.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_quad.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_quad.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_quad.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_shade.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_shade.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_shade.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_sin.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_sin.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_sin.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_sqrt.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_sqrt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_sqrt.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_thresh.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_thresh.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_thresh.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_log.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_log.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_log.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_bshift.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_bshift.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_bshift.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_add.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_add.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_add.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_complexify.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_complexify.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_complexify.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\src\vision\improc\im_rank.c

!IF  "$(CFG)" == "Dynamic_Release"

".\WinRel\im_rank.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Dynamic_Debug"

".\WinDebug\im_rank.obj" :  $(SOURCE)  $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\vision.def
# End Source File
################################################################################
# Begin Source File

SOURCE="\lib-pc\sys\windebug\sys.lib"
# End Source File
################################################################################
# Begin Source File

SOURCE="\lib-pc\math\windebug\math.lib"
# End Source File
# End Group
# End Project
################################################################################
