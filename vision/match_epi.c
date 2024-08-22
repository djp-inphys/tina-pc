/**@(#)
**/
/* match_epi.c
 * 
 * generic stereo functions for identifying matches between epipolar edge
 * sub-strings contained in the stereo index
 * 
 * optimised for general ease of handling and testing of stereo algorithms
 * rather than computational/memory efficiency.
 * 
 * the MLIST property of the epipolar sub-strings is used to store a list
 * of potential matches */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/* test if the string of which s is an epipolar sub-string is already
 * referenced by the ->to2 field of a member of the list of matches
 * mlist
 * 
 * as strings can cross the same set of epipolar/rasters more than one the
 * STRING id label added during the construction of the stereo index is
 * used to identify unique sections */
static Bool string_already_matched(Tstring * s, List * mlist)
{
    List   *mptr;
    int     s_id;

    if (s == NULL || mlist == NULL)
	return (false);

    s_id = (int) prop_get(s->props, STRING);

    for (mptr = mlist; mptr != NULL; mptr = mptr->next)
    {
	Tstring *sptr = (Tstring *) ((Match *) (mptr->to))->to2;

	if (s_id == (int) prop_get(sptr->props, STRING))
	    return (true);
    }

    return (false);
}

/* compute the stereo matching strength weight between a pair of
 * epipolar sub-strings
 * 
 * the matching strenght increases with: the similarity of edge string
 * contrast the actual contrast value the number of edges in the edge
 * string */
double  ss_match_weight(Tstring * s1, Tstring * s2)
{
    float   mean_count;
    double  es_mean_con();
    double  con1, con2;

    if (s1 == NULL || s2 == NULL)
	return (0.0);

    con1 = es_mean_con(s1);
    con2 = es_mean_con(s2);
    mean_count = (float)((s1->count + s2->count) / 2.0);
    return (mean_count * con1 * (1.0 - fabs(con1 - con2) / (con1 + con2)));
}

/* add to the list of matches of an edge sub-string additional matches
 * with the list of sub-strings from a matching epipolar/raster
 * 
 * the matches are stored as a lists on the MLIST property of the epipolar
 * sub-strings from the left image
 * 
 * matches are only sought over the range lx to ux which is determined in
 * turn from the disparity range
 * 
 * matches must satisfy match_func (NULL value for all matches) and are
 * limited to a single match per uniquely labled meta edge string using
 * the string_already_matched function */
void    es_add_new_matches(Tstring * es, List * slist, double lx, double ux, Bool(*match_func) ( /* ??? */ ))
/* string contiguous edges along a raster */
/* list of raster edge strings */
/* matching window */

/* edge string match test (NULL for all matches) */
{
    List   *lptr;
    Tstring *sptr;
    List   *mlist;

    mlist = (List *) prop_get(es->props, MLIST);

    for (lptr = slist; lptr != NULL; lptr = lptr->next)
    {
	sptr = (Tstring *) lptr->to;
	if ((sptr->type == FORWARD && vec2_x(DD_EDGE_POS(sptr->end)) > lx) ||
	    (sptr->type == BACKWARD && vec2_x(DD_EDGE_POS(sptr->start)) > lx))
	    break;
    }
    for (; lptr != NULL; lptr = lptr->next)
    {
	sptr = (Tstring *) lptr->to;
	if ((sptr->type == FORWARD && vec2_x(DD_EDGE_POS(sptr->end)) > ux) ||
	    (sptr->type == BACKWARD && vec2_x(DD_EDGE_POS(sptr->start)) > ux))
	    break;
	if (string_already_matched(sptr, mlist) == true)
	    continue;
	if (match_func == NULL || match_func(es, sptr))	/* they can match */
	{
	    Match  *m = match_make((void *) es, (void *) sptr, STRING);

	    m->weight = (float)ss_match_weight(es, sptr);
	    mlist = ref_addtostart(mlist, (void *) m, MATCH);
	}
    }
    es->props = proplist_addifnp(es->props, (void *) mlist, MLIST, mlist_free, false);
}

/* find all matches between a pair of epipolar lines uses the function
 * es_add_new_matches */
void    es_match_epi_pair(List * left, List * right, Bool(*match_func) ( /* ??? */ ))
/* list of edge strings on left epipolar */
/* list of edge strings on right epipolar */

/* edge string match test (NULL for all matches) */
{
    double  lowd, upd;		/* range of allowed disparity */
    List   *ptr;

    for (ptr = left; ptr != NULL; ptr = ptr->next)
    {
	double  lx, ux;
	Tstring *es = (Tstring *) ptr->to;

	(void) disp_range_at_pos2(str2_centroid(es), &lowd, &upd);

	if (es->type == FORWARD)
	{
	    lx = vec2_x(DD_EDGE_POS(es->start)) + lowd;
	    ux = vec2_x(DD_EDGE_POS(es->end)) + upd;
	} else
	{			/* BACKWARD */
	    lx = vec2_x(DD_EDGE_POS(es->end)) + lowd;
	    ux = vec2_x(DD_EDGE_POS(es->start)) + upd;
	}
	es_add_new_matches(es, right, lx, ux, match_func);
    }
}

/* find all matches between left and right edgerects search over
 * vertical raster range of vslop to allow for calibration error and
 * edge migration
 * 
 * the same edge string will not be matched on different rasters only the
 * first match is maintained, hence matching between corresponding
 * rasters is performed before those within allowed vertical error */
void    er_set_matches(Imrect * er_left, Imrect * er_right, int vslop, Bool(*match_func) ( /* ??? */ ))
/* imrects containing left and right edges */
/* vertical range for allowable matches */

/* edge string match test (NULL for all matches) */
{
    Rindex *sx_left;
    Rindex *sx_right;
    List   *left;
    List   *right;
    int     ll, lu, rl, ru;
    int     i, j;

    if (er_left == NULL || er_right == NULL)
	return;

    sx_left = (Rindex *) prop_get(er_left->props, SINDEX);	/* Stereo INDEX */
    sx_right = (Rindex *) prop_get(er_right->props, SINDEX);

    if (sx_left == NULL || sx_right == NULL)
	return;

    ll = sx_left->region->ly;
    rl = sx_right->region->ly;
    lu = sx_left->region->uy;
    ru = sx_right->region->uy;

    for (i = ll; i < lu; ++i)
    {
	left = (List *) sx_left->index[i];
	for (j = 0; j <= vslop; ++j)
	{
	    if (i + j >= rl && i + j < ru)	/* in right image */
	    {
		right = (List *) sx_right->index[i + j];
		es_match_epi_pair(left, right, match_func);
	    }
	    if (j != 0 && i - j >= rl && i - j < ru)	/* in right image */
	    {
		right = (List *) sx_right->index[i - j];
		es_match_epi_pair(left, right, match_func);
	    }
	}
    }
}

/* add copy of match list (only links are copied) of current edge
 * string to global list */
void    es_add_to_mlist(Tstring * es, int type, List ** mlist)
{
    if (type != STRING)
	return;
    *mlist = list_append(list_copy((List *) prop_get(es->props, MLIST),
				   (void *(*) ()) NULL, NULL), *mlist);
}

/* edge sub-string match format also prints support structure if
 * available */
void    em_format(Match * em, int type)
{
    Support *s;

    if (em == NULL || type != MATCH)
	return;

    format("edge string \n");
    es_format((Tstring *) em->to1);
    format("\nis matched to\n");
    es_format((Tstring *) em->to2);
    s = (Support *) prop_get(em->props, MATCH_SUPPORT);
    if (s != NULL)
    {
	format("match type   %d\n", s->type);
	format("local string %f\n", s->local_string);
	format("total string %f\n", s->total_string);
	format("local area   %f\n", s->local_area);
	format("matching     %f\n", s->matching_strength);
    }
}

/* format whole list of string of edge sub-string matches */
void    em_list_format(List * mlist)
{
    list_apply_func(mlist, em_format, NULL);
}
