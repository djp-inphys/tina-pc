/**@(#)
**/
/* supp_fig.c
 * 
 * generic stereo functions for computing total figural support for each
 * match along an extended edge contour string support flows between
 * close neighbours of similar disparity
 * 
 * computationally more expensive than alternative strategy of computing
 * closely related same string match support */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

#define SUPPORT_WINDOW   5	/* rasters difference for allowable
				 * support */
#define DISPARITY_WINDOW 3	/* disparity difference for allowable
				 * support */
#define GRADIENT_LIMIT 0.25	/* sq of gradient limit for allowable
				 * support */

/* test whether a pair of matches are compatible (figural connectivity
 * of one or other edge string is assumed) the test is thus a diparity
 * and dipsarity gradient test.
 * 
 * first identify closest ends of strings referenced through the pair of
 * matches and find their image coordinates
 * 
 * check the dispairt difference and gradients are within local threshold
 * values */
static int figuraly_compatible(Match * m1, Match * m2)
{
    Ddlist *d11;
    Ddlist *d12;
    Ddlist *d21;
    Ddlist *d22;
    Vec2    v11 = {Vec2_id};
    Vec2    v12 = {Vec2_id};
    Vec2    v21 = {Vec2_id};
    Vec2    v22 = {Vec2_id};
    double  disp, sep;		/* disparity, separation */

    if (es_closest_ends((Tstring *) m1->to1, (Tstring *) m2->to1, &d11, &d21) == false)
	return (0);
    if (es_closest_ends((Tstring *) m1->to2, (Tstring *) m2->to2, &d12, &d22) == false)
	return (0);

    DD_GET_POS2(d11, v11);
    DD_GET_POS2(d12, v12);
    DD_GET_POS2(d21, v21);
    DD_GET_POS2(d22, v22);

    disp = fabs((vec2_x(v12) - vec2_x(v11)) - (vec2_x(v22) - vec2_x(v21)));
    if (disp < 1.0)
	return (1);
    if (disp > DISPARITY_WINDOW)
	return (0);

    sep = vec2_sqrmod(vec2_diff(v11, v21));
    if (((disp * disp) / sep) < GRADIENT_LIMIT)
	return (1);
    return (0);
}

/* look back over the figural support window for the match that gives
 * most (if any) figural support for the current match figural support
 * is stored in the local string field of the support structure
 * associated with a match
 * 
 * support is always taken from the absolute strongest supporting match in
 * the support window, but the strength of that support is
 * 
 * scaled invesely with the gap in the data (no of rasters) */
static double supp_figural_last(Match * m, Ddlist * sptr, Ddlist * start)
{
    int     i;

    if (sptr == start)
	return (0.0);

    for (i = 0, sptr = sptr->last; i < SUPPORT_WINDOW; i++, sptr = sptr->last)
    {
	Tstring *sub;
	List   *mlist;
	List   *mptr;
	Bool    supp_exists = false;
	double  supp, max_supp = 0.0;

	sub = (Tstring *) sptr->to;
	mlist = (List *) prop_get(sub->props, MLIST);

	for (mptr = mlist; mptr != NULL; mptr = mptr->next)
	{
	    Match  *m_new;

	    m_new = (Match *) mptr->to;
	    if (figuraly_compatible(m, m_new))
	    {
		supp_exists = true;
		supp = match_local_string_strength(m_new);
		if (supp > max_supp)
		    max_supp = supp;
	    }
	}

	if (supp_exists == true)
	    return (max_supp / (i + 1));

	if (sptr == start)
	    break;
    }
    return (0.0);
}

/* look forward over the figural support window for the match that
 * gives most (if any) figural support for the current match figural
 * support is stored in the local string field of the support structure
 * associated with a match
 * 
 * support is always taken from the absolute strongest supporting match in
 * the support window, but the strength of that support is
 * 
 * scaled invesely with the gap in the data (no of rasters) */
static double supp_figural_next(Match * m, Ddlist * sptr, Ddlist * end)
{
    int     i;

    if (sptr == end)
	return (0.0);

    for (i = 0, sptr = sptr->next; i < SUPPORT_WINDOW; i++, sptr = sptr->next)
    {
	Tstring *sub;
	List   *mlist;
	List   *mptr;
	Bool    supp_exists = false;
	double  supp, max_supp = 0.0;

	sub = (Tstring *) sptr->to;
	mlist = (List *) prop_get(sub->props, MLIST);

	for (mptr = mlist; mptr != NULL; mptr = mptr->next)
	{
	    Match  *m_new;

	    m_new = (Match *) mptr->to;
	    if (figuraly_compatible(m, m_new))
	    {
		supp_exists = true;
		supp = match_local_string_strength(m_new);
		if (supp > max_supp)
		    max_supp = supp;
	    }
	}

	if (supp_exists == true)
	    return (max_supp / (i + 1));

	if (sptr == end)
	    break;
    }
    return (0.0);
}

/* walk along an string of sub strings accumulating figural support
 * into the local_string field of the support structure using
 * supp_fugural_last and the local cost funtion
 * 
 * now walk back accumulating support in the opposite direction in the
 * same way using supp_fugural_next and the local cost funtion also
 * store the combined sum in the total_string field of the support
 * structure ARGSUSED quieten lint */
static void supp_figural(Tstring * str, int type, double (*cost_func) ( /* ??? */ ))
/* string of stereo index substrings */
/* not used */

{
    Ddlist *start;
    Ddlist *end;
    Ddlist *sptr;

    if (str == NULL || str->type != SINDEX)
	return;

    start = str->start;
    end = str->end;

    for (sptr = start;; sptr = sptr->next)
    {
	Tstring *sub;
	List   *mlist;
	List   *mptr;

	sub = (Tstring *) sptr->to;
	mlist = (List *) prop_get(sub->props, MLIST);

	for (mptr = mlist; mptr != NULL; mptr = mptr->next)
	{
	    Match  *m;
	    Support *s;

	    m = (Match *) mptr->to;
	    s = (Support *) prop_get(m->props, MATCH_SUPPORT);
	    if (s->type <= BAD_MATCH)
		continue;
	    s->local_string = (float)((cost_func == NULL) ? m->weight : cost_func(m));
	    s->local_string += (float)(supp_figural_last(m, sptr, start));
	}

	if (sptr == end)
	    break;
    }

    for (sptr = end;; sptr = sptr->last)
    {
	Tstring *sub;
	List   *mlist;
	List   *mptr;

	sub = (Tstring *) sptr->to;
	mlist = (List *) prop_get(sub->props, MLIST);

	for (mptr = mlist; mptr != NULL; mptr = mptr->next)
	{
	    Match  *m;
	    Support *s;

	    m = (Match *) mptr->to;
	    s = (Support *) prop_get(m->props, MATCH_SUPPORT);
	    if (s->type <= BAD_MATCH)
		continue;
	    s->total_string = s->local_string;
	    s->local_string = (float)supp_figural_next(m, sptr, end);
	    s->total_string += s->local_string;
	    s->local_string += (float)((cost_func == NULL) ? m->weight : cost_func(m));
	}

	if (sptr == start)
	    break;
    }
}

/* applies figural support funtion to an edge string
 * 
 * first the pure edge string is converted to an equivelent string of
 * epipolar sub-strings that were identified at during the construction
 * of the stereo index. Matches are defined at this level.
 * 
 * the funtion cost_func determins the weight that is accumulated
 * figurally */
void    es_figural_supp(Tstring * es, int type, double (*cost_func) ( /* ??? */ ))

/* not used */

{
    es = string_of_sindex_strings(es);
    supp_figural(es, type, cost_func);
    str_rm_links(es);
}
