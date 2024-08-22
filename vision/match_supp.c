/**@(#)
**/
/* match_supp.c
 * 
 * generic stereo functions for adding match support structures to matches
 * between epipolar edge sub-strings */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/* add support structure to property list of match structure using the
 * key MATCH_SUPPORT */
List   *match_add_supp_prop(Match * m)
{
    Support *sup;

    sup = supp_alloc();
    sup->type = POT_MATCH;
    sup->matching_strength = m->weight;
    sup->match = m;
    m->props = proplist_addifnp(m->props, (void *) sup, MATCH_SUPPORT, rfree, true);
    /* BUG control reaches end of non-void function */
}

/* add support structure to all matches of epipolar edge sub-string
 * using match_add_supp_prop function */
void    es_add_supp_prop(Tstring * es)
/* epipolar edge string */
{
    if (es == NULL)
	return;

    list_apply_func((List *) prop_get(es->props, MLIST),
		    (void (*) ()) match_add_supp_prop, NULL);
}
