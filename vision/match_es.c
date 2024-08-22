/**@(#)
**/
/* match_es.c
 * 
 * generic functions that relate edge strings and matches */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

/* initialise match list of an edge string */
void    es_init_mlist(Tstring * es)
{
    if (es == NULL)
	return;
    (void) prop_set(es->props, NULL, MLIST, true);
}

/* get the list of matches at a meta string level from the union
 * implied by matches between epipolar edge subs-trings
 * 
 * 
 * the resulting match list is unique wrt ->to2 field (what they match to)
 * 
 * meta edge strings may be a composite made from copies of smaller edge
 * strings
 * 
 * hence it follows that: 1. edge strings and substrings may not share
 * list elements 2. edge strings and substrings do reference the same
 * edgels 3. edge strings and substrings may not preserve the local
 * order of edges */
List   *es_get_list_of_matches(Tstring * es)
{
    Ddlist *ptr;
    Ddlist *end;
    Tstring *sub, *sub_last = NULL;
    List   *matches = NULL;

    if (es == NULL)
	return (NULL);

    end = es->end;
    for (ptr = es->start;; ptr = ptr->next)
    {
	Edgel  *edge;
	List   *mlist;

	if (ptr->type != EDGE)
	    continue;

	edge = DD_EDGE(ptr);
	sub = (Tstring *) prop_get(edge->props, SINDEX);
	if (sub != NULL && sub != sub_last)
	{
	    mlist = (List *) prop_get(sub->props, MLIST);

	    for (; mlist != NULL; mlist = mlist->next)
	    {
		Match  *m = (Match *) mlist->to;

		if (link_get_by_ref(matches, m->to2) == NULL)
		    matches = ref_addtostart((List *) matches, (void *) m, MATCH);
	    }
	}
	sub_last = sub;
	if (ptr == end)
	    break;
    }
    return (matches);
}
