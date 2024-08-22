/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sys_types.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/tina_types.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

static double xdisp, ydisp, height, width, correlate, uniqueness;
static double asymetry = 0.85, range = 3.0;
static Imrect *old_er_left = NULL;
static Imrect *old_er_right = NULL;

void    left_corners_store(Imrect * er)
{
    old_er_left = er;
}

void    right_corners_store(Imrect * er)
{
    old_er_right = er;
}

Imrect *stored_left_corners(void)
{
    return (old_er_left);
}

Imrect *stored_right_corners(void)
{
    return (old_er_right);
}

void    temporal_corner_match(Imrect * er, Imrect * old_er, double new_xdisp, double new_ydisp, double new_height, double new_width, double new_corr, double new_unique, double new_asym)
{
    Rindex *fx;
    Rindex *old_fx;
    Rindex *er_set_findex();
    Imregion backward_search_func(Edgel * edgel);
    Imregion forward_search_func(Edgel * edgel);
    int     type = BACKTEMP;

    if (er == NULL || old_er == NULL)
    {
	error("missing edge structure", non_fatal);
	return;
    }
    if ((fx = prop_get(er->props, ER_TINDEX)) == NULL)
	if ((fx = er_set_findex(er, ER_TINDEX, (Vec2 * (*) ()) NULL)) == NULL)
	    return;
    if ((old_fx = prop_get(old_er->props, ER_TINDEX)) == NULL)
	if ((old_fx = er_set_findex(old_er, ER_TINDEX, (Vec2 * (*) ()) NULL)) == NULL)
	    return;

    xdisp = new_xdisp;
    ydisp = new_ydisp;
    height = new_height;
    width = new_width;
    correlate = new_corr;
    uniqueness = new_unique;
    asymetry = new_asym;

    rm_corner_matches(fx, &type);
    get_corner_matches(fx, old_fx, (int) NULL, backward_search_func, (void*(*) ())temp_backward_match);
    type = FORTEMP;
    rm_corner_matches(old_fx, &type);
    get_corner_matches(old_fx, fx, (int) NULL, forward_search_func, (void*(*) ())temp_forward_match);
    set_temporal_corner_matches(fx);
}

/* BUGFIX JB 22/11/93 was: void   *temp_backward_match(Edgel * edge1,
 * Edgel * edge2) */
void    temp_backward_match(Edgel * edge1, Edgel * edge2)
{
    float   corr;

    corr = good_corner(edge1, edge2, (float) range, (float) asymetry,
		       (Imrect *) NULL, (Imrect *) NULL);

    if (corr > correlate - uniqueness)
    {
	Match  *match;
	Match  *match_alloc();

	match = match_alloc(CORNER);
	match->weight = corr;
	match->to1 = (void *) edge1;
	match->to2 = (void *) edge2;
	add_match_to_props(edge1, (void *) match, BACKTEMP);
    }
}

/* BUGFIX JB 22/11/93 was: void   *temp_forward_match(Edgel * edge2,
 * Edgel * edge1) */
void    temp_forward_match(Edgel * edge2, Edgel * edge1)
{
    float   corr;

    corr = good_corner(edge1, edge2, (float) range, (float) asymetry,
		       (Imrect *) NULL, (Imrect *) NULL);

    if (corr > correlate - uniqueness)
    {
	Match  *match;
	Match  *match_alloc();

	match = match_alloc(CORNER);
	match->weight = corr;
	match->to1 = (void *) edge1;
	match->to2 = (void *) edge2;
	add_match_to_props(edge2, (void *) match, FORTEMP);
    }
}

Imregion forward_search_func(Edgel * edgel)
{
    Imregion tempr = {Imregion_id};
    Vec2   *rect;

    rect = &edgel->pos;

    tempr.lx = (int)floor(rect->el[0] - width + xdisp);
    tempr.ux = (int)floor(rect->el[0] + width + xdisp);
    tempr.ly = (int)floor(rect->el[1] - height + ydisp);
    tempr.uy = (int)floor(rect->el[1] + height + ydisp);
    return (tempr);
}

Imregion backward_search_func(Edgel * edgel)
{
    Imregion tempr = {Imregion_id};
    Vec2   *rect;

    rect = &edgel->pos;

    tempr.lx = (int)floor(rect->el[0] - width - xdisp);
    tempr.ux = (int)floor(rect->el[0] + width - xdisp);
    tempr.ly = (int)floor(rect->el[1] - height - ydisp);
    tempr.uy = (int)floor(rect->el[1] + height - ydisp);
    return (tempr);
}

void    set_temporal_corner_matches(Rindex * fx)
/* BUG Rindex  fx; */

{
    void   *data = NULL;
    apply_func_to_windex(fx, (void*(*)())set_temporal_corner_match, data);
}

/* ARGSUSED quieten lint */
/* BUGFIX JB 22/11/93 was void   *set_temporal_corner_match(Edgel *
 * edge1, void *data) */
void    set_temporal_corner_match(Edgel * edge1, void *data)

/* unused */
{
    Edgel  *edge2;
    List   *matches1;
    List   *matches2;
    Match  *best_match1;
    Match  *best_match2;

    if ((matches1 = (List *) prop_get(edge1->props, BACKTEMP)) == NULL)
	return;
    if ((best_match1 = (Match *) matches1->to) == NULL)
	return;

    if ((edge2 = (Edgel *) best_match1->to2) == NULL)
	return;

    if ((matches2 = (List *) prop_get(edge2->props, FORTEMP)) == NULL)
	return;
    if ((best_match2 = (Match *) matches2->to) == NULL)
	return;

    if (edge1 == best_match2->to1 && best_match1->weight > correlate)
    {
	matches1->type = GOOD_MATCH;
	matches2->type = GOOD_MATCH;
    }
}
