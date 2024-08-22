/**@(#)
**/
/* choose.c
 * 
 * Generic stereo functions for choosing best matches.
 * 
 * They only change the type field in the support structure assiociated
 * with each match.
 * 
 * Functions that also delete alternative matches and select the chosen
 * one can be found in select.c */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/* Chose the best match of an epipolar edge string. Based upon the
 * matching strength field of the support structure. Sets the support
 * type of the best match to GOOD_MATCH. Sets the support type for
 * contradictory matches to BAD_MATCH. */
static void choose_best_match(Tstring * es)
{
    List   *list;
    List   *ptr;
    Support *bestsup = NULL;
    float   max_strength = (float) 0.0;

    if (es == NULL)
	return;

    list = (List *) prop_get(es->props, MLIST);

    for (ptr = list; ptr != NULL; ptr = ptr->next)
    {
	Match  *match = (Match *) ptr->to;
	Support *sup;

	sup = (Support *) prop_get(match->props, MATCH_SUPPORT);

	if (sup->type <= BAD_MATCH)
	    continue;

	sup->type = BAD_MATCH;
	if (bestsup == NULL || sup->matching_strength > max_strength)
	{
	    bestsup = sup;
	    max_strength = sup->matching_strength;
	}
    }
    if (bestsup != NULL)
	bestsup->type = GOOD_MATCH;
}

/* Choose the best match for all the epipolar edge strings that
 * constitute the global edge string. */
void    es_choose_best_matches(Tstring * es)
{
    es_apply_to_sindex_strings(es, choose_best_match, NULL);
}

/* Choose all matches in the match list. Set the support type of each
 * to GOOD_MATCH. Set the support type of contradictory matches to
 * BAD_MATCH. */
void    choose_these_matches(List * mlist)
{
    List   *clist;
    List   *mptr;
    List   *cptr;

    if (mlist == NULL)
	return;

    for (mptr = mlist; mptr != NULL; mptr = mptr->next)
    {
	Match  *match;
	Support *bestsup;
	Tstring *es;

	match = (Match *) mptr->to;
	es = (Tstring *) match->to1;
	bestsup = (Support *) prop_get(match->props, MATCH_SUPPORT);
	if (bestsup->type <= BAD_MATCH)	/* already rejected */
	    continue;

	clist = (List *) prop_get(es->props, MLIST);

	for (cptr = clist; cptr != NULL; cptr = cptr->next)
	{
	    Match  *match = (Match *) cptr->to;
	    Support *sup;

	    sup = (Support *) prop_get(match->props, MATCH_SUPPORT);
	    sup->type = BAD_MATCH;
	}
	bestsup->type = GOOD_MATCH;
    }
}
