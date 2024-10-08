/**@(#)Tina structure info .c file.
   @(#)Automatically generated by 'tstruct_info_gen'
**/
#include <tina/all_tina.h>
#include <tina/X_dummy.h>
#include <tina/brain.h>

/* Array of info used to serialise Tina structures */
Tina_data_info tina_data_info_array[] =
{
    {"", 0, "ts_base", NULL, NULL, NULL, NULL},

    {AIFFHDR_SWAP_STRING, sizeof(Aiffhdr), "aiffhdr", ts_serialise, ts_deserialise, ts_print, ts_free},
    {BASIS2_SWAP_STRING, sizeof(Basis2), "basis2", ts_serialise, ts_deserialise, ts_print, ts_free},
    {BASIS3_SWAP_STRING, sizeof(Basis3), "basis3", ts_serialise, ts_deserialise, ts_print, ts_free},
    {BIN_NODE_SWAP_STRING, sizeof(Bin_node), "bin_node", ts_serialise, ts_deserialise, ts_print, ts_free},
    {BLK_STAT_SWAP_STRING, sizeof(Blk_stat), "blk_stat", ts_serialise, ts_deserialise, ts_print, ts_free},
    {CAMERA_SWAP_STRING, sizeof(Camera), "camera", ts_serialise, ts_deserialise, ts_print, ts_free},
    {CIRC2_SWAP_STRING, sizeof(Circ2), "circ2", ts_serialise, ts_deserialise, ts_print, ts_free},
    {CMAP_DATA_SWAP_STRING, sizeof(Cmap_data), "cmap_data", ts_serialise, ts_deserialise, ts_print, ts_free},
    {CMAP_DATA_VISIBLE_SWAP_STRING, sizeof(Cmap_data_visible), "cmap_data_visible", ts_serialise, ts_deserialise, ts_print, ts_free},
    {COMPLEX_SWAP_STRING, sizeof(Complex), "complex", ts_serialise, ts_deserialise, ts_print, ts_free},
    {CONE_SWAP_STRING, sizeof(Cone), "cone", ts_serialise, ts_deserialise, ts_print, ts_free},
    {CONIC_SWAP_STRING, sizeof(Conic), "conic", ts_serialise, ts_deserialise, ts_print, ts_free},
    {CONIC3_SWAP_STRING, sizeof(Conic3), "conic3", ts_serialise, ts_deserialise, ts_print, ts_free},
    {CONIC_STAT_SWAP_STRING, sizeof(Conic_stat), "conic_stat", ts_serialise, ts_deserialise, ts_print, ts_free},
    {COVAR_SWAP_STRING, sizeof(Covar), "covar", ts_serialise, ts_deserialise, ts_print, ts_free},
    {CURSOR_DATA_SWAP_STRING, sizeof(Cursor_data), "cursor_data", ts_serialise, ts_deserialise, ts_print, ts_free},
    {CVR_SLICE_SWAP_STRING, sizeof(Cvr_slice), "cvr_slice", ts_serialise, ts_deserialise, ts_print, ts_free},
    {CVR_VOI_SWAP_STRING, sizeof(Cvr_voi), "cvr_voi", ts_serialise, ts_deserialise, ts_print, ts_free},
    {CYLINDER_SWAP_STRING, sizeof(Cylinder), "cylinder", ts_serialise, ts_deserialise, ts_print, ts_free},
    {DDLIST_SWAP_STRING, sizeof(Ddlist), "ddlist", ts_serialise, ts_deserialise, ts_print, ts_free},
    {DPNODE_SWAP_STRING, sizeof(Dpnode), "dpnode", ts_serialise, ts_deserialise, ts_print, ts_free},
    {EDGE_CONN_SWAP_STRING, sizeof(Edge_conn), "edge_conn", ts_serialise, ts_deserialise, ts_print, ts_free},
    {EDGE_FP_SWAP_STRING, sizeof(Edge_fp), "edge_fp", ts_serialise, ts_deserialise, ts_print, ts_free},
    {EDGEL_SWAP_STRING, sizeof(Edgel), "edgel", ts_serialise, ts_deserialise, ts_print, ts_free},
    {EPOS_SWAP_STRING, sizeof(Epos), "epos", ts_serialise, ts_deserialise, ts_print, ts_free},
    {FIELD_INFO_SWAP_STRING, sizeof(Field_info), "field_info", ts_serialise, ts_deserialise, ts_print, ts_free},
    {FONT_DATA_SWAP_STRING, sizeof(Font_data), "font_data", ts_serialise, ts_deserialise, ts_print, ts_free},
    {GENERIC_SWAP_STRING, sizeof(Generic), "generic", ts_serialise, ts_deserialise, ts_print, ts_free},
    {GRAPH_NODE_SWAP_STRING, sizeof(Graph_node), "graph_node", ts_serialise, ts_deserialise, ts_print, ts_free},
    {ICARRAY_SWAP_STRING, sizeof(Icarray), "icarray", ts_serialise, ts_deserialise, ts_print, ts_free},
    {ICS2_SWAP_STRING, sizeof(Ics2), "ics2", ts_serialise, ts_deserialise, ts_print, ts_free},
    {IFFHDR_SWAP_STRING, sizeof(Iffhdr), "iffhdr", ts_serialise, ts_deserialise, ts_print, ts_free},
    {IMRECT_SWAP_STRING, sizeof(Imrect), "imrect", ts_serialise, ts_deserialise, ts_print, ts_free},
    {IMREGION_SWAP_STRING, sizeof(Imregion), "imregion", ts_serialise, ts_deserialise, ts_print, ts_free},
    {IMSTACK_SWAP_STRING, sizeof(Imstack), "imstack", ts_serialise, ts_deserialise, ts_print, ts_free},
    {IPOS_SWAP_STRING, sizeof(Ipos), "ipos", ts_serialise, ts_deserialise, ts_print, ts_free},
    {ISO_ERROR_SWAP_STRING, sizeof(Iso_error), "iso_error", ts_serialise, ts_deserialise, ts_print, ts_free},
    {KWSNAKE_SWAP_STRING, sizeof(Kwsnake), "kwsnake", ts_serialise, ts_deserialise, ts_print, ts_free},
    {LINE2_SWAP_STRING, sizeof(Line2), "line2", ts_serialise, ts_deserialise, ts_print, ts_free},
    {LINE3_SWAP_STRING, sizeof(Line3), "line3", ts_serialise, ts_deserialise, ts_print, ts_free},
    {LIST_SWAP_STRING, sizeof(List), "list", ts_serialise, ts_deserialise, ts_print, ts_free},
    {MAT2_SWAP_STRING, sizeof(Mat2), "mat2", ts_serialise, ts_deserialise, ts_print, ts_free},
    {MAT3_SWAP_STRING, sizeof(Mat3), "mat3", ts_serialise, ts_deserialise, ts_print, ts_free},
    {MAT4_SWAP_STRING, sizeof(Mat4), "mat4", ts_serialise, ts_deserialise, ts_print, ts_free},
    {MATCH_SWAP_STRING, sizeof(Match), "match", ts_serialise, ts_deserialise, ts_print, ts_free},
    {MATCH_CLICHE_SWAP_STRING, sizeof(Match_cliche), "match_cliche", ts_serialise, ts_deserialise, ts_print, ts_free},
    {MATCH_CLIQUE_SWAP_STRING, sizeof(Match_clique), "match_clique", ts_serialise, ts_deserialise, ts_print, ts_free},
    {MATRIX_SWAP_STRING, sizeof(Matrix), "matrix", ts_serialise, ts_deserialise, ts_print, ts_free},
    {PAIR_SWAP_STRING, sizeof(Pair), "pair", ts_serialise, ts_deserialise, ts_print, ts_free},
    {PARCAM_SWAP_STRING, sizeof(Parcam), "parcam", ts_serialise, ts_deserialise, ts_print, ts_free},
    {PL_AXES_SWAP_STRING, sizeof(Pl_axes), "pl_axes", ts_serialise, ts_deserialise, ts_print, ts_free},
    {PL_CTR_SWAP_STRING, sizeof(Pl_ctr), "pl_ctr", ts_serialise, ts_deserialise, ts_print, ts_free},
    {PL_GRAPH_SWAP_STRING, sizeof(Pl_graph), "pl_graph", ts_serialise, ts_deserialise, ts_print, ts_free},
    {PLANE_SWAP_STRING, sizeof(Plane), "plane", ts_serialise, ts_deserialise, ts_print, ts_free},
    {POINT2_SWAP_STRING, sizeof(Point2), "point2", ts_serialise, ts_deserialise, ts_print, ts_free},
    {POINT3_SWAP_STRING, sizeof(Point3), "point3", ts_serialise, ts_deserialise, ts_print, ts_free},
    {POS2_SWAP_STRING, sizeof(Pos2), "pos2", ts_serialise, ts_deserialise, ts_print, ts_free},
    {POS3_SWAP_STRING, sizeof(Pos3), "pos3", ts_serialise, ts_deserialise, ts_print, ts_free},
    {PROF1_SWAP_STRING, sizeof(Prof1), "prof1", ts_serialise, ts_deserialise, ts_print, ts_free},
    {PROP_SWAP_STRING, sizeof(Prop), "prop", ts_serialise, ts_deserialise, ts_print, ts_free},
    {PWRTE_GEN_SWAP_STRING, sizeof(Pwrte_gen), "pwrte_gen", ts_serialise, ts_deserialise, ts_print, ts_free},
    {PWRTE_POINT_TO_POINT_SWAP_STRING, sizeof(Pwrte_point_to_point), "pwrte_point_to_point", ts_serialise, ts_deserialise, ts_print, ts_free},
    {PWRTE_POINT_TO_VEC_SWAP_STRING, sizeof(Pwrte_point_to_vec), "pwrte_point_to_vec", ts_serialise, ts_deserialise, ts_print, ts_free},
    {PWRTE_VEC_TO_VEC_SWAP_STRING, sizeof(Pwrte_vec_to_vec), "pwrte_vec_to_vec", ts_serialise, ts_deserialise, ts_print, ts_free},
    {QUAD3_SWAP_STRING, sizeof(Quad3), "quad3", ts_serialise, ts_deserialise, ts_print, ts_free},
    {QUADRIC_SWAP_STRING, sizeof(Quadric), "quadric", ts_serialise, ts_deserialise, ts_print, ts_free},
    {RGB_SWAP_STRING, sizeof(Rgb), "rgb", ts_serialise, ts_deserialise, ts_print, ts_free},
    {RINDEX_SWAP_STRING, sizeof(Rindex), "rindex", ts_serialise, ts_deserialise, ts_print, ts_free},
    {RULED_SWAP_STRING, sizeof(Ruled), "ruled", ts_serialise, ts_deserialise, ts_print, ts_free},
    {SCALAR_SWAP_STRING, sizeof(Scalar), "scalar", ts_serialise, ts_deserialise, ts_print, ts_free},
    {SNAKE_SWAP_STRING, sizeof(Snake), "snake", ts_serialise, ts_deserialise, ts_print, ts_free},
    {STATE_SWAP_STRING, sizeof(State), "state", ts_serialise, ts_deserialise, ts_print, ts_free},
    {STRING_MATCH_SWAP_STRING, sizeof(String_match), "string_match", ts_serialise, ts_deserialise, ts_print, ts_free},
    {SUPPORT_SWAP_STRING, sizeof(Support), "support", ts_serialise, ts_deserialise, ts_print, ts_free},
    {TERRAIN_DATA_SWAP_STRING, sizeof(Terrain_data), "terrain_data", ts_serialise, ts_deserialise, ts_print, ts_free},
    {TINA_COLOR_SWAP_STRING, sizeof(Tina_color), "tina_color", ts_serialise, ts_deserialise, ts_print, ts_free},
    {TOPTOOL_DATA_SWAP_STRING, sizeof(Toptool_data), "toptool_data", ts_serialise, ts_deserialise, ts_print, ts_free},
    {TORUS_SWAP_STRING, sizeof(Torus), "torus", ts_serialise, ts_deserialise, ts_print, ts_free},
    {TRANSF3_SWAP_STRING, sizeof(Transf3), "transf3", ts_serialise, ts_deserialise, ts_print, ts_free},
    {TRANSFORM2_SWAP_STRING, sizeof(Transform2), "transform2", ts_serialise, ts_deserialise, ts_print, ts_free},
    {TRANSFORM3_SWAP_STRING, sizeof(Transform3), "transform3", ts_serialise, ts_deserialise, ts_print, ts_free},
    {TREE_NODE_SWAP_STRING, sizeof(Tree_node), "tree_node", ts_serialise, ts_deserialise, ts_print, ts_free},
    {TSTRING_SWAP_STRING, sizeof(Tstring), "tstring", ts_serialise, ts_deserialise, ts_print, ts_free},
    {TV_SWAP_STRING, sizeof(Tv), "tv", ts_serialise, ts_deserialise, ts_print, ts_free},
    {TV_CLOSEST_SWAP_STRING, sizeof(Tv_closest), "tv_closest", ts_serialise, ts_deserialise, ts_print, ts_free},
    {TV_DRAW_SWAP_STRING, sizeof(Tv_draw), "tv_draw", ts_serialise, ts_deserialise, ts_print, ts_free},
    {TV_MASK_SWAP_STRING, sizeof(Tv_mask), "tv_mask", ts_serialise, ts_deserialise, ts_print, ts_free},
    {TV_MOUSE_SWAP_STRING, sizeof(Tv_mouse), "tv_mouse", ts_serialise, ts_deserialise, ts_print, ts_free},
    {TV_PATCH_SWAP_STRING, sizeof(Tv_patch), "tv_patch", ts_serialise, ts_deserialise, ts_print, ts_free},
    {TV_PICK_SWAP_STRING, sizeof(Tv_pick), "tv_pick", ts_serialise, ts_deserialise, ts_print, ts_free},
    {TV_PICTURE_SWAP_STRING, sizeof(Tv_picture), "tv_picture", ts_serialise, ts_deserialise, ts_print, ts_free},
    {TV_SCREEN_SWAP_STRING, sizeof(Tv_screen), "tv_screen", ts_serialise, ts_deserialise, ts_print, ts_free},
    {TV_ZBUFF_SWAP_STRING, sizeof(Tv_zbuff), "tv_zbuff", ts_serialise, ts_deserialise, ts_print, ts_free},
    {TW_CALLBACK_SWAP_STRING, sizeof(Tw_callback), "tw_callback", ts_serialise, ts_deserialise, ts_print, ts_free},
    {UCBS_SWAP_STRING, sizeof(Ucbs), "ucbs", ts_serialise, ts_deserialise, ts_print, ts_free},
    {UCBS2_SWAP_STRING, sizeof(Ucbs2), "ucbs2", ts_serialise, ts_deserialise, ts_print, ts_free},
    {UCBS3_SWAP_STRING, sizeof(Ucbs3), "ucbs3", ts_serialise, ts_deserialise, ts_print, ts_free},
    {VEC2_SWAP_STRING, sizeof(Vec2), "vec2", ts_serialise, ts_deserialise, ts_print, ts_free},
    {VEC3_SWAP_STRING, sizeof(Vec3), "vec3", ts_serialise, ts_deserialise, ts_print, ts_free},
    {VEC4_SWAP_STRING, sizeof(Vec4), "vec4", ts_serialise, ts_deserialise, ts_print, ts_free},
    {VECTOR_SWAP_STRING, sizeof(Vector), "vector", ts_serialise, ts_deserialise, ts_print, ts_free},
    {VIOLS_NODE_SWAP_STRING, sizeof(Viols_node), "viols_node", ts_serialise, ts_deserialise, ts_print, ts_free},
    {VRAM_SWAP_STRING, sizeof(Vram), "vram", ts_serialise, ts_deserialise, ts_print, ts_free},
    {WINDEX_SWAP_STRING, sizeof(Windex), "windex", ts_serialise, ts_deserialise, ts_print, ts_free},
    {USER_TYPE_0_SWAP_STRING, sizeof(User_type_0), "User_type_0", ts_serialise, ts_deserialise, ts_print, ts_free},
    {USER_TYPE_1_SWAP_STRING, sizeof(User_type_1), "User_type_1", ts_serialise, ts_deserialise, ts_print, ts_free},
    {USER_TYPE_2_SWAP_STRING, sizeof(User_type_2), "User_type_2", ts_serialise, ts_deserialise, ts_print, ts_free},
    {USER_TYPE_3_SWAP_STRING, sizeof(User_type_3), "User_type_3", ts_serialise, ts_deserialise, ts_print, ts_free},
    {USER_TYPE_4_SWAP_STRING, sizeof(User_type_4), "User_type_4", ts_serialise, ts_deserialise, ts_print, ts_free},
    {USER_TYPE_5_SWAP_STRING, sizeof(User_type_5), "User_type_5", ts_serialise, ts_deserialise, ts_print, ts_free},
    {USER_TYPE_6_SWAP_STRING, sizeof(User_type_6), "User_type_6", ts_serialise, ts_deserialise, ts_print, ts_free},
    {USER_TYPE_7_SWAP_STRING, sizeof(User_type_7), "User_type_7", ts_serialise, ts_deserialise, ts_print, ts_free},
    {USER_TYPE_8_SWAP_STRING, sizeof(User_type_8), "User_type_8", ts_serialise, ts_deserialise, ts_print, ts_free},
    {USER_TYPE_9_SWAP_STRING, sizeof(User_type_9), "User_type_9",
     ts_serialise, ts_deserialise, ts_print, ts_free},
    {TS_INT_SWAP_STRING, sizeof(Ts_int),"ts_int",ts_serialise, ts_deserialise, ts_print, ts_free},
    {TS_FLOAT_SWAP_STRING, sizeof(Ts_float),"ts_float",ts_serialise, ts_deserialise, ts_print, ts_free},
    {TS_DOUBLE_SWAP_STRING, sizeof(Ts_double),"ts_double",ts_serialise, ts_deserialise, ts_print, ts_free},
    {TS_STRING_SWAP_STRING, sizeof(Ts_string),"ts_string",ts_serialise, ts_deserialise, ts_print, ts_free},
};


Tina_data_info *get_tina_data_info_array()
{
	return tina_data_info_array;
}
