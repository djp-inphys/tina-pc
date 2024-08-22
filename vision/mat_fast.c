/**@(#)
**/
/* mat_fast.c
 * 
 * Specialised functions for stereo matching based upon strict string
 * match identity and dynamic programming.
 * 
 * Faster and less memory overhead than generic version.
 * 
 * Weeker figural continuity criteria could be used.
 * 
 * Works by matching edge strings as a whole rather than at the stereo
 * index epipolar edge strings level.
 * 
 * Individual matches are considered between regular edge strings
 * associated with a global string. These only cross each epipolar once
 * are distinguished using the unique label added during the
 * construction of the stereo index (it is stored on the property list
 * of the stereo index sub-strings using the key STRING). */

#include <math.h>
#include <string.h>
#ifdef TRANSPUTER
#include <valuesdual.h>
#else
#include <values.h>
#endif
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/* Add match information at the match string level for the epipolar
 * edge sub-string from one image with respect to the list of epipolar
 * edge strings from the other.
 * 
 * This includes the accumulation of strict figural contour support.
 * 
 * First identify the edge contour string and substring identifier of
 * which this epipolar sub-string forms a part. */
static void match_strings(Tstring * es, List * slist, int r, double lx, double ux, Bool(*match_func) ( /* ??? */ ))
/* string contiguous edges along a raster */
/* list of raster edge strings */
/* row/raster value */
/* matching window */

/* edge string match test (NULL for all matches) */
{
    List   *lptr;
    Tstring *s1, *s2;
    Edgel  *edge;
    List   *mlist;
    int     s1_id, s2_id;
    int     mlist_updated = 0;

    edge = (Edgel *) es->start->to;
    s1 = (Tstring *) prop_get(edge->props, STRING);
    mlist = (List *) prop_get(s1->props, MLIST);
    s1_id = (int) prop_get(es->props, STRING);

    for (lptr = slist; lptr != NULL; lptr = lptr->next)
    {
	s2 = (Tstring *) lptr->to;
	if ((s2->type == FORWARD && vec2_x(DD_EDGE_POS(s2->end)) > lx) ||
	(s2->type == BACKWARD && vec2_x(DD_EDGE_POS(s2->start)) > lx))
	    break;
    }

    for (; lptr != NULL; lptr = lptr->next)
    {
	s2 = (Tstring *) lptr->to;
	if ((s2->type == FORWARD && vec2_x(DD_EDGE_POS(s2->end)) > ux) ||
	(s2->type == BACKWARD && vec2_x(DD_EDGE_POS(s2->start)) > ux))
	    break;
	if (match_func == NULL || match_func(es, s2))	/* they can match */
	{
	    String_match *sm;

	    s2_id = (int) prop_get(s2->props, STRING);
	    if ((sm = str_mat_from_list(mlist, s1_id, s2_id)) == NULL)
	    {
		edge = (Edgel *) s2->start->to;
		sm = sm_make(s1, (Tstring *) prop_get(edge->props, STRING), s1_id, s2_id);
		sm->r_low = sm->r_up = r;
		mlist = ref_addtostart(mlist, (void *) sm, s1_id);
		mlist_updated = 1;
	    }
	    sm->support += ss_match_weight(es, s2);
	    if (r < sm->r_low)
		sm->r_low = r;
	    if (r > sm->r_up)
		sm->r_up = r;
	}
    }
    if (mlist_updated)
	s1->props = proplist_addifnp(s1->props, (void *) mlist, MLIST, sm_list_rm, false);
}

/* consider epipolar edge sub-strings from the stereo index at the
 * raster level
 * 
 * use the match_strings function to accumulate match string data between
 * implicit edge strings */
static void match_strings_epi(List * left, List * right, int r, Bool(*match_func) ( /* ??? */ ))
/* list of edge strings on left epipolar */
/* list of edge strings on right epipolar */
/* row/raster number */

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
	match_strings(es, right, r, lx, ux, match_func);
    }
}

/*********************************************************************
*								     *
*		END OF MATCH STRING SUPPORT FUNCTIONS		     *
*								     *
* 		START OF DYNAMIC PROGRAMMING FUNCTIONS               *
*								     *
**********************************************************************/

/* build dynamic programming index list for the current complete edge
 * countour it containes separate index list elements for each labled
 * sub-string that is unique in raster coverage
 * 
 * actual index values are filled in later depending upon the raster that
 * is being initialised for dynamic programming
 * 
 * walk along edge string using epipolar sub-strings and notice changes in
 * sub-string labels */
static void es_build_dpindex_prop(Tstring * es)
{
    Ddlist *dptr;
    Ddlist *end;
    int     old_str_id = 0, str_id;
    List   *index = NULL;

    if (es == NULL)
	return;

    end = es->end;
    for (dptr = es->start;; dptr = dptr->next)
    {
	Edgel  *e = (Edgel *) dptr->to;
	Tstring *sub;

	sub = (Tstring *) prop_get(e->props, SINDEX);
	if (sub == NULL)
	{
	    if (dptr == end)
		break;
	    continue;
	}
	str_id = (int) prop_get(sub->props, STRING);

	if (str_id != old_str_id)
	{
	    index = ref_addtostart((List *) index, (void *) 0, str_id);
	    old_str_id = str_id;
	}
	dptr = sub->end;
	if (dptr == end)
	    break;
    }
    es->props = proplist_addifnp(es->props, (void *) index, DP_INDEX, list_rm_links, true);
}

/* set dynamic programming indices on the basis of the list of edges
 * that constitute a current raster of the stereo index
 * 
 * the dynamic programming index is associated whole edge contour as well
 * as the epipolar sub-string as that is where match information is
 * made explicit. */
static int es_list_set_dpindices(List * es)
{
    List   *lptr;
    List   *index;
    Tstring *str;
    int     str_id, i;

    for (lptr = es, i = 0; lptr != NULL; lptr = lptr->next, ++i)
    {
	str = (Tstring *) lptr->to;
	str_id = (int) prop_get(str->props, STRING);
	str->props = proplist_addifnp(str->props, (void *) i, DP_INDEX,
				      (void (*) ()) NULL, false);
	str = (Tstring *) prop_get(((Edgel *) str->start->to)->props, STRING);
	index = (List *) prop_get(str->props, DP_INDEX);
	for (; index; index = index->next)
	{
	    if (index->type == str_id)
	    {
		index->to = (void *) i;
		break;
	    }
	}
    }
    return (i);
}

/* Static data structures to simplify dynamic programming code and
 * minimise data structure allocation and freeing. */

static int dp_size;		/* size of square DP array */
static Dpnode **dp_array;	/* the DP array */
static int *low, *up;		/* lower and upper indices into DP
				 * array */

/* Build dynamic programming array of size s by s if s is less than or
 * equal to the size of the existing array then just return
 * 
 * free up the existing array allocate space for low and up index arrays
 * they delimit the active parts of the DP array that is those elements
 * containing valid data */
static void dp_build(int s)
{
    unsigned int label;

    if (s <= dp_size)
	return;

    label = ralloc_end_blocked();	/* allow for blocked allocation */

    narray_free((char **) dp_array, 0, dp_size, 0, dp_size, sizeof(Dpnode));
    rfree((void *) low);
    rfree((void *) up);
    dp_size = s;
    dp_array = ts_narray_alloc(0, 0, dp_size, dp_size, Dpnode);
    low = (int *) ralloc((unsigned) (sizeof(int *) * dp_size));
    up = (int *) ralloc((unsigned) (sizeof(int *) * dp_size));
    if (label)			/* allocation was blocked */
	(void) ralloc_start_blocked(label);	/* re-start blocking */
}

/* apply dynamic programming to the rasters implicit in the lists left
 * and right and return a list of DP matches
 * 
 * the form of the match list returned by the dynamic programming routines
 * is determined by the data field of the Dpnode for efficiency (memory
 * allocation is avoided) it is an integer value that uniquely
 * identifies the DP indices of the left and right edge
 * strings/sub-strings: l_index*r_no + r_index + 1 where r_no is the
 * number of edge strings crossing the right raster. The final 1 is
 * added as if the data field has value is 0 it is not returned (the
 * null match).
 * 
 * The DP array is first filled with entries implied by relavent edge
 * string matches and appropriate low and up indices adusted.
 * 
 * The low and up array idives are then validated to allow the
 * computationally optimal form of dynamic programming to be performed. */
static List *dp_string_matches(List * left, List * right, int r, int l_no, int r_no)

/* raster/row number */
/* max number of left and right indices */
{
    List   *ptr;
    List   *mlist;
    Tstring *str;
    int     firsti, lasti, minj = MAXINT;
    int     s1_id, s2_id;
    int     i, j;

    if (left == NULL || right == NULL)
	return (NULL);

    if (l_no > dp_size || r_no > dp_size)
    {
	error("dp_mlist: dynamic programming table limit exeeded", warning);
	return (NULL);
    }
    /* initialise dp array */
    for (i = 0; i < l_no; ++i)
    {
	low[i] = up[i] = -1;
	(void) memset((char *) dp_array[i], 0, r_no * sizeof(Dpnode));
    }

    for (ptr = left; ptr != NULL; ptr = ptr->next)
    {
	str = (Tstring *) ptr->to;
	i = (int) prop_get(str->props, DP_INDEX);
	s1_id = (int) prop_get(str->props, STRING);
	str = (Tstring *) prop_get(((Edgel *) str->start->to)->props, STRING);
	mlist = (List *) prop_get(str->props, MLIST);
	for (; mlist != NULL; mlist = mlist->next)
	{
	    List   *index_list;
	    String_match *sm;

	    if (s1_id != mlist->type)
		continue;

	    sm = (String_match *) mlist->to;
	    if (r > sm->r_up || r < sm->r_low)
		continue;

	    s2_id = sm->s2_id;
	    str = (Tstring *) ((String_match *) mlist->to)->s2;
	    index_list = (List *) prop_get(str->props, DP_INDEX);
	    for (; index_list != NULL; index_list = index_list->next)
		if (s2_id == index_list->type)
		    break;
	    if (index_list == NULL)
		continue;
	    j = (int) index_list->to;
	    if (low[i] == -1 || j < low[i])
		low[i] = j;
	    if (up[i] == -1 || j > up[i])
		up[i] = j;
	    if (j < minj)
		minj = j;
	    dp_array[i][j].data = (void *) (i * r_no + j + 1);
	    dp_array[i][j].cost = (float) ((String_match *) mlist->to)->support;
	}
    }

    /* find range of left index values with possible matches */
    for (i = 0; i < l_no; ++i)
	if (low[i] != -1)
	    break;
    firsti = i;
    for (i = l_no - 1; i >= 0; --i)
	if (low[i] != -1)
	    break;
    lasti = i;

    if (firsti > lasti)
	return (NULL);

    form_valid_dp_array(low, up, firsti, lasti, minj);
    dp_accum(dp_array, low, up, firsti, lasti);
    return (dp_solution(dp_array, low, up, firsti, lasti));
}

/* run dynamic programming on the left and right raster r and interpret
 * the result
 * 
 * the function dp_string_matches actually performs the dynamic
 * programming
 * 
 * matches are formed between matching left and right epipolar edge
 * strings and added to the property list of the left member using the
 * key MLIST */
static void choose_matches_epi(List * left, List * right, int r)
/* list of edge strings on left epipolar */
/* list of edge strings on right epipolar */
/* raster number */
{
    int     l_no, r_no;
    List   *mlist;
    List   *ptr;

    l_no = es_list_set_dpindices(left);
    r_no = es_list_set_dpindices(right);
    mlist = dp_string_matches(left, right, r, l_no, r_no);

    for (ptr = mlist; ptr != NULL; ptr = ptr->next)
    {
	int     i, j;
	Tstring *l_es, *r_es;
	Match  *match;

	i = ((int) ptr->to) - 1;
	j = (i % r_no);
	i = (i / r_no);
	l_es = (Tstring *) (list_nth(left, i))->to;
	r_es = (Tstring *) (list_nth(right, j))->to;
	match = match_make((void *) l_es, (void *) r_es, STRING);
	l_es->props = proplist_addifnp(l_es->props, (void *) link_alloc((void *) match, MATCH),
				       MLIST, mlist_free, true);
    }

    list_rm_links(mlist);
}

/*********************************************************************
*								     *
* 		END OF DYNAMIC PROGRAMMING FUNCTIONS                 *
*								     *
**********************************************************************/

/* external function call for rapid stereo matching uses all above
 * static funtions and variables
 * 
 * uses left and right edgrect and a matching funtion updates the MLIST
 * property associated with the stereo index sub-strings of the left
 * image */
void    er_string_matcher(Imrect * er_left, Imrect * er_right, Bool(*match_func) ( /* ??? */ ))
/* imrects containing left and right edges */

/* edge string match test (NULL for all matches) */
{
    Rindex *sx_left;
    Rindex *sx_right;
    List   *left;
    List   *right;
    int     ll, lu, rl, ru;
    int     i;

    if (er_left == NULL || er_right == NULL)
	return;

    er_apply_to_all_strings(er_left, es_init_mlist, NULL);
    er_apply_to_all_strings(er_left, es_build_dpindex_prop, NULL);
    er_apply_to_all_strings(er_right, es_build_dpindex_prop, NULL);

    sx_left = (Rindex *) prop_get(er_left->props, SINDEX);	/* Stereo INDEX */
    sx_right = (Rindex *) prop_get(er_right->props, SINDEX);

    if (sx_left == NULL || sx_right == NULL)
	return;

    ll = sx_left->region->ly;
    rl = sx_right->region->ly;
    lu = sx_left->region->uy;
    ru = sx_right->region->uy;

    /* match whole sub strings and compute support */

    for (i = ll; i < lu; ++i)
    {
	if (i < rl || i >= ru)
	    continue;
	left = (List *) sx_left->index[i];
	right = (List *) sx_right->index[i];
	match_strings_epi(left, right, i, match_func);
    }

    /* select correct matches using dynamic programming to force order */

    dp_build(stereo_dp_max_size_get());

    for (i = ll; i < lu; ++i)
    {
	if (i < rl || i >= ru)
	    continue;
	left = (List *) sx_left->index[i];
	right = (List *) sx_right->index[i];
	choose_matches_epi(left, right, i);
    }
}
