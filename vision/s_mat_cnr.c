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

static double disp, lowd, upd, width, correlate, uniqueness;
static double asymetry = 0.85, range = 3.0;
static Imrect *im_left, *im_right;	/* Defined in
					 * corner/t_mat_cnr.c */

void    stereo_corner_match(Imrect *im_left_new, Imrect *im_right_new,
       Imrect *left_er,Imrect *right_er,
       double new_disp, double new_lowd, double new_upd,
       double new_width, double new_corr, double new_unique, double new_asym)
{
    Rindex *fxl;
    Rindex *fxr;
    Imregion left_search_func(Edgel * edgel);
    Imregion right_search_func(Edgel * edgel);
    Rindex *er_set_findex();
    int     type = MLIST;
    Vec2   *rectpos(Edgel * edgel);

    if (left_er == NULL || right_er == NULL)
    {
	error("no edge structure", non_fatal);
	return;
    }
    im_left = im_left_new;
    im_right = im_right_new;

    if (im_left == NULL || im_right == NULL)
    {
	error("no images", non_fatal);
	return;
    }
    if ((fxl = prop_get(left_er->props, ER_FINDEX)) == NULL)
	if ((fxl = er_set_findex(left_er, ER_FINDEX, rectpos)) == NULL)
	    return;
    if ((fxr = prop_get(right_er->props, ER_FINDEX)) == NULL)
	if ((fxr = er_set_findex(right_er, ER_FINDEX, rectpos)) == NULL)
	    return;

    disp = new_disp;
    lowd = new_lowd * left_er->width;
    upd = new_upd * left_er->width;
    width = new_width;
    correlate = new_corr;
    uniqueness = new_unique;
    asymetry = new_asym;

    rm_corner_matches(fxl, &type);
    get_corner_matches(fxl, fxr, RECTPOS, left_search_func, stereo_left_match);
    rm_corner_matches(fxr, &type);
    get_corner_matches(fxr, fxl, RECTPOS, right_search_func, stereo_right_match);
    set_stereo_corner_matches(fxl);
}

Vec2   *rectpos(Edgel * edgel)
{
    return ((Vec2 *) prop_get(edgel->props, RECTPOS));
}

void   *stereo_left_match(Edgel * edgell, Edgel * edgelr)
{
    float   corr;

    corr = good_corner(edgell, edgelr, (float) range, (float) asymetry, im_left, im_right);

    if (corr > correlate - uniqueness)
    {
	Match  *match;
	Match  *match_alloc();

	match = match_alloc(CORNER);
	match->weight = corr;
	match->to1 = (void *) edgell;
	match->to2 = (void *) edgelr;
	add_match_to_props(edgell, (void *) match, MLIST);
    }
}

void   *stereo_right_match(Edgel * edgelr, Edgel * edgell)
{
    float   corr;

    corr = good_corner(edgelr, edgell, (float) range, (float) asymetry, im_right, im_left);

    if (corr > correlate - uniqueness)
    {
	Match  *match;
	Match  *match_alloc();

	match = match_alloc(CORNER);
	match->weight = corr;
	match->to1 = (void *) edgell;
	match->to2 = (void *) edgelr;
	add_match_to_props(edgelr, (void *) match, MLIST);
    }
}

Imregion left_search_func(Edgel * edgel)
{
    Imregion stereor = {Imregion_id};
    Vec2   *rect;

    rect = (Vec2 *) prop_get(edgel->props, RECTPOS);
    if (rect == NULL)
	rect = &edgel->pos;

    stereor.lx = (int)floor(rect->el[0] + lowd + disp);
    stereor.ux = (int)floor(rect->el[0] + upd + disp);
    stereor.ly = (int)floor(rect->el[1] - width);
    stereor.uy = (int)floor(rect->el[1] + width);
    return (stereor);
}

Imregion right_search_func(Edgel * edgel)
{
    Imregion stereor = {Imregion_id};
    Vec2   *rect;

    rect = (Vec2 *) prop_get(edgel->props, RECTPOS);
    if (rect == NULL)
	rect = &edgel->pos;

    stereor.lx = (int)floor(rect->el[0] + lowd - disp);
    stereor.ux = (int)floor(rect->el[0] + upd - disp);
    stereor.ly = (int)floor(rect->el[1] - width);
    stereor.uy = (int)floor(rect->el[1] + width);
    return (stereor);
}

void    set_stereo_corner_matches(Rindex * fxl)
{
    void   *data = NULL;

    apply_func_to_windex(fxl, (void *(*) ()) set_stereo_corner_match, data);
}

void    rm_stereo_corner_matches(Rindex * fx)
{
    apply_func_to_windex(fx, (void *(*) ()) rm_match_from_props, (void *) MLIST);
}

/* ARGSUSED quieten lint */
/* BUGFIX: JB 22/11/93 was void   *set_stereo_corner_match(Edgel *
 * ledge, void *data) */
void    set_stereo_corner_match(Edgel * ledge, void *data /* unused */ )
{
    Edgel  *redge;
    List   *left_matches;
    List   *right_matches;
    Match  *best_left_match;
    Match  *next_best_left;
    Match  *best_right_match;
    Match  *next_best_right;

    if ((left_matches = (List *) prop_get(ledge->props, MLIST)) == NULL)
	return;
    if ((best_left_match = (Match *) left_matches->to) == NULL)
	return;

    if ((redge = (Edgel *) best_left_match->to2) == NULL)
	return;

    if ((right_matches = (List *) prop_get(redge->props, MLIST)) == NULL)
	return;
    if ((best_right_match = (Match *) right_matches->to) == NULL)
	return;

    if (ledge == best_right_match->to1 && best_left_match->weight > correlate)
    {
	left_matches->type = FIXED_MATCH;
	right_matches->type = FIXED_MATCH;
	if (left_matches->next != NULL && (next_best_left = (Match *) left_matches->next->to) != NULL)
	{
	    if ((best_left_match->weight - next_best_left->weight) < uniqueness)
	    {
		left_matches->type = GOOD_MATCH;
		right_matches->type = GOOD_MATCH;
	    }
	}
	if (right_matches->next != NULL && (next_best_right = (Match *) right_matches->next->to) != NULL)
	{
	    if ((best_right_match->weight - next_best_right->weight) < uniqueness)
	    {
		left_matches->type = GOOD_MATCH;
		right_matches->type = GOOD_MATCH;
	    }
	}
    }
}
