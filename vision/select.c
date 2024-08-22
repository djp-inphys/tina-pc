/**@(#)
**/
/* select.c
 * 
 * generic stereo functions for selecting correct matches
 * 
 * selection involves the removal of alternative matches */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

/* for a matched edge string fix and select unique GOOD_MATCH matches
 * remove reference to all other matches */
void    es_select_fix_matches(Tstring * es)
{
    List   *list;
    List   *ptr;
    Support *selected = NULL;

    if (es == NULL)
	return;

    list = (List *) prop_get(es->props, MLIST);

    for (ptr = list; ptr != NULL; ptr = ptr->next)
    {
	Match  *match = (Match *) ptr->to;
	Support *sup;

	sup = (Support *) prop_get(match->props, MATCH_SUPPORT);

	if (sup->type < GOOD_MATCH)
	    continue;

	if (selected != NULL)
	    break;
	selected = sup;
    }

    if (selected != NULL && ptr == NULL)
    {
	List   *new;

	selected->type = FIXED_MATCH;
	if (list->next == NULL)
	    return;		/* only one element in the list */

	list = list_rm_ref(list, (void *) selected->match, (void (*) ()) NULL);
	(void) prop_set(es->props, (void *) list, MLIST, false);	/* put the list back */
	new = link_alloc((void *) selected->match, MATCH);
	(void) prop_set(es->props, (void *) new, MLIST, true);	/* frees up the list */
    } else
	(void) prop_set(es->props, NULL, MLIST, true);
}

/* set matching strength to zero for matches < GOOD_MATCH reset support
 * type of all matches to to POT_MATCH */
void    es_supp_good_matches_only(Tstring * es)
{
    List   *list;
    List   *ptr;

    if (es == NULL)
	return;

    list = (List *) prop_get(es->props, MLIST);

    for (ptr = list; ptr != NULL; ptr = ptr->next)
    {
	Match  *match = (Match *) ptr->to;
	Support *sup;

	sup = (Support *) prop_get(match->props, MATCH_SUPPORT);

	if (sup->type < GOOD_MATCH)
	    sup->matching_strength = (float)0.0;
	sup->type = POT_MATCH;
    }
}
