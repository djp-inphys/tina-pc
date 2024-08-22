/**@(#)
**/
/* choose_wta.c
 * 
 * Generic stereo functions for performing winner take all choices.
 * 
 * Includes WTA schemes for implementing either uniqueness or ordering. */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/* Test if 2 matches are unique wrt uniquely labeled regular
 * sub-strings. */
/* ARGSUSED quieten lint */
Bool    matches_not_unique(Match * m1, int type, Match * m2)

/* unused */

{
    int     s1_id, s2_id;

    if (m1->to1 == m2->to1 || m1->to2 == m2->to2)
	return (true);

    s1_id = (int) prop_get(((Tstring *) m1->to1)->props, STRING);
    s2_id = (int) prop_get(((Tstring *) m2->to1)->props, STRING);

    if (s1_id == s2_id)
	return (true);

    s1_id = (int) prop_get(((Tstring *) m1->to2)->props, STRING);
    s2_id = (int) prop_get(((Tstring *) m2->to2)->props, STRING);

    if (s1_id == s2_id)
	return (true);

    return (false);
}

/* Test if 2 matches preserve order along the x direction. */
/* ARGSUSED quieten lint */
Bool    matches_not_ordered(Match * m1, int type, Match * m2)

/* unused */

{
    double  x11, x12, x21, x22;
    Vec2    v = {Vec2_id};

    v = str2_centroid((Tstring *) m1->to1);
    x11 = vec2_x(v);
    v = str2_centroid((Tstring *) m1->to2);
    x12 = vec2_x(v);
    v = str2_centroid((Tstring *) m2->to1);
    x21 = vec2_x(v);
    v = str2_centroid((Tstring *) m2->to2);
    x22 = vec2_x(v);

    if ((x11 < x12) != (x21 < x22))
	return (true);

    return (false);
}

/* Apply WTA scheme to matches associated with a single raster.
 * 
 * WTA allows strongest matches to be chosen and competitors to be
 * eliminated.
 * 
 * Scheme implemeted here does not properly allow for the fact that the
 * same sub-string can be indexed on different rows. */
void    choose_wta(List * left, double (*cost_func) ( /* ??? */ ), Bool(*compat_func) ( /* ??? */ ))
/* epipolar edge list */



{
    List   *mlist = NULL;
    List   *ptr;
    List   *next;
    List   *choose = NULL;

    list_apply_func(left, es_add_to_mlist, (void *) &mlist);
    mlist = list_reverse(sort_list(mlist, cost_func, NULL));
    mlist_set_supp_type(mlist, BAD_MATCH);

    for (ptr = mlist; ptr != NULL; ptr = next)
    {
	Match  *m = (Match *) ptr->to;

	next = ptr->next;
	choose = link_addtostart((List *) choose, ptr);
	next = list_rm_links_on_func(next, compat_func, (void *) m);
    }
    mlist_set_supp_type(choose, GOOD_MATCH);
    list_rm_links(mlist);
}

/* Apply wta scheme to all the rasters in the edgerect. */
void    choose_wta_matches(Imrect * er, double (*cost_func) ( /* ??? */ ), Bool(*compat_func) ( /* ??? */ ))
/* left edgerect */



{
    Rindex *sx;
    int     ly, uy, i;

    if (er == NULL || (sx = (Rindex *) prop_get(er->props, SINDEX)) == NULL)
	return;

    ly = sx->region->ly;
    uy = sx->region->uy;

    for (i = ly; i < uy; ++i)
	choose_wta((List *) sx->index[i], cost_func, compat_func);
}
