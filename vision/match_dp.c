/**@(#)
**/
/* dp_match.c
 * 
 * generic stereo routines for dynamic programming
 * 
 * includes support and choice functionality
 * 
 * uses dynamic programming at its most abstract through the match list
 * interface */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/* static variable for max DP table size plus get and set functions
 * 
 * using a fixed DP array improves efficiency as the table is not
 * allocated at each iteration */

static int max_dp_table_size = 100;

void    stereo_dp_max_size_set(int size)
{
    max_dp_table_size = size;
}

int     stereo_dp_max_size_get(void)
{
    return (max_dp_table_size);
}

/* add DP index to elements in the epipolar edge sub-string list that
 * represent ordered matching features along a raster */
static void es_list_add_dpindex_prop(List * es)
{
    List   *lptr;
    Tstring *str;
    int     i;

    for (lptr = es, i = 0; lptr != NULL; lptr = lptr->next, ++i)
    {
	str = (Tstring *) lptr->to;
	str->props = proplist_addifnp(str->props, (void *) i, DP_INDEX,
				      (void (*) ()) NULL, false);
    }
}

/* recover DP index from an epipolar sub-string */
static int es_index_get(Tstring * es)
{
    return ((int) prop_get(es->props, DP_INDEX));
}

/* get mean x position of edge string */
static double es_mean_x(Tstring * es)
{
    Vec2    v = {Vec2_id};

    v = str2_centroid(es);

    return (vec2_x(v));
}

/* take an ordered list and remove repeated references */
static void thin_ordered_list(List * list)
{
    List   *p1;
    List   *p2;
    List   *p3;

    for (p1 = list; p1 != NULL; p1 = p2)
    {
	for (p2 = p1->next; p2 != NULL; p2 = p2->next)
	    if (p2->to != p1->to)
		break;

	if (p1->next == p2)
	    continue;

	if (p2 == NULL)
	    break;

	p3 = p1->next;
	p1->next = p2;
	while (p3 != p2)
	{
	    p1 = p3->next;
	    rfree((void *) p3);
	    p3 = p1;
	}
    }
}

/* perform dynamic programming to identify optimal ordered selection of
 * matches referenced through the list of epipolar edge sub-strings
 * from the left image
 * 
 * the matching strength upon which DP is based is returned by calling the
 * match_weight_func on the match
 * 
 * because of the way in which the stereo index is constructed and because
 * it is possible to allow vertical miss-match at the match formation
 * stage the right and side of the matches can not be guaranteed to
 * come from a single raster of the stereo index. they are though
 * guaranteed to be unigue with respect to uniquely labled subsections
 * of global edge contours.
 * 
 * the list of all matches associated with the raster left is processed to
 * recover a list of right hand edges strings these are subsequently
 * ordered and thined to produce a unique list of edge sub-strings that
 * constitues a virtual raster of the right image. */
List   *match_epi_dprog(List * left, double (*match_weight_func) ( /* ??? */ ))
/* epipolar edge list */

{
    List   *mlist = NULL;
    List   *right;
    List   *dplist;

    list_apply_func(left, es_add_to_mlist, (void *) &mlist);
    right = mlist_to2_list(mlist);
    right = sort_list(right, es_mean_x, NULL);
    thin_ordered_list(right);

    if (right == NULL)
	return (NULL);

    es_list_add_dpindex_prop(left);
    es_list_add_dpindex_prop(right);

    mlist_set_dp_indices(mlist, es_index_get, NULL);

    dplist = dp_mlist(mlist, match_weight_func);

    list_rm_links(right);
    list_rm_links(mlist);

    return (dplist);
}

/* use raster based DP to choose optimal match order for the matching
 * strength implied by the match_weight_func */
void    choose_ordered_matches(Imrect * er, double (*match_weight_func) ( /* ??? */ ))
/* left edgerect */

{
    Rindex *sx;
    int     ly, uy, i;

    if (er == NULL || (sx = (Rindex *) prop_get(er->props, SINDEX)) == NULL)
	return;

    ly = sx->region->ly;
    uy = sx->region->uy;

    dp_mlist_build(max_dp_table_size);

    for (i = ly; i < uy; ++i)
    {
	List   *mlist = NULL;
	List   *best;

	list_apply_func((List *) sx->index[i], es_add_to_mlist, (void *) &mlist);
	best = match_epi_dprog((List *) sx->index[i], match_weight_func);
	mlist_set_supp_type(mlist, BAD_MATCH);
	mlist_set_supp_type(best, GOOD_MATCH);
	list_rm_links(mlist);
	list_rm_links(best);
    }
}

/* set matching strength according to DP selection the
 * matching_strength of the support structure is
 * 
 * set to the weight of the match (not the DP sum) for matches on the
 * optimal path and zero otherwise */
void    support_ordered_matches(Imrect * er, double (*match_weight_func) ( /* ??? */ ))
/* left edgerect */

{
    Rindex *sx;
    int     ly, uy, i;
    double  zero = 0;

    if (er == NULL || (sx = (Rindex *) prop_get(er->props, SINDEX)) == NULL)
	return;

    ly = sx->region->ly;
    uy = sx->region->uy;

    dp_mlist_build(max_dp_table_size);

    for (i = ly; i < uy; ++i)
    {
	List   *mlist = NULL;
	List   *best;

	list_apply_func((List *) sx->index[i], es_add_to_mlist, (void *) &mlist);
	best = match_epi_dprog((List *) sx->index[i], match_weight_func);
	list_apply_func(mlist, match_set_match_strength, (void *) &zero);
	list_apply_func(best, (void (*) ()) match_set_strength_from_weight,
			NULL);
	list_rm_links(mlist);
	list_rm_links(best);
    }
}
