/**@(#)
**/
/* support.c
 * 
 * generic stereo functions for support match support accumulation and
 * exchange
 * 
 * match support structures are associated with match structures used to
 * identify mathes during generic forms of stereo processing support
 * and match structures have access to each other on their property
 * lists in a mutual fashion using the keys MATCH_SUPPORT and plain old
 * MATCH respectively */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

/* allocate and initialise support data structure */
Support *supp_alloc(void)
{
    Support *sup = ts_ralloc(Support);

    return (sup);
}

/* functions at match level to acess support structure and return
 * various matching strength support values */

double  match_strength(Match * match)
{
    Support *sup;

    sup = (Support *) prop_get(match->props, MATCH_SUPPORT);

    return ((sup == NULL || sup->type <= BAD_MATCH) ? 0.0 : sup->matching_strength);
}

double  match_total_string_strength(Match * match)
{
    Support *sup;

    sup = (Support *) prop_get(match->props, MATCH_SUPPORT);

    return ((sup == NULL || sup->type <= BAD_MATCH) ? 0.0 : sup->total_string);
}

double  match_local_string_strength(Match * match)
{
    Support *sup;

    sup = (Support *) prop_get(match->props, MATCH_SUPPORT);

    return ((sup == NULL || sup->type <= BAD_MATCH) ? 0.0 : sup->local_string);
}

double  match_local_area_strength(Match * match)
{
    Support *sup;

    sup = (Support *) prop_get(match->props, MATCH_SUPPORT);

    return ((sup == NULL || sup->type <= BAD_MATCH) ? 0.0 : sup->local_area);
}

/* set matching strength field of support structure for a list of
 * matches */
void    match_set_strength_from_weight(Match * match)
{
    Support *sup;

    sup = (Support *) prop_get(match->props, MATCH_SUPPORT);
    if (sup == NULL)
	return;
    sup->matching_strength = match->weight;
}

/* set matching strength field of support structure for a list of
 * matches */
/* ARGSUSED quieten lint */
void    match_set_match_strength(Match * match, int type, double *strength)
{
    Support *sup;

    sup = (Support *) prop_get(match->props, MATCH_SUPPORT);
    if (sup == NULL)
	return;
    sup->matching_strength = (float)*strength;
}

/* set total string field of support structure for a list of matches */
/* ARGSUSED quieten lint */
void    match_set_total_string(Match * match, int type, double *strength)
{
    Support *sup;

    sup = (Support *) prop_get(match->props, MATCH_SUPPORT);
    if (sup == NULL)
	return;
    sup->total_string = (float)*strength;
}

/* set the support type field of a list of matches to type */
void    mlist_set_supp_type(List * mlist, int type)
{
    while (mlist != NULL)
    {
	Match  *match = (Match *) mlist->to;
	Support *sup;

	sup = (Support *) prop_get(match->props, MATCH_SUPPORT);
	if (sup != NULL)
	    sup->type = type;
	mlist = mlist->next;
    }
}
