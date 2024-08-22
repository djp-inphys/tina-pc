/**@(#)
**/
/* match.c
 * 
 * a genericly defined matching structure
 * 
 * typedef struct match { int type; int label; float weight; void *to1;
 * void *to2; struct list *props; } Match; */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/vision.h>
#ifdef _PCC
#include <memory.h>
#endif

/* static variable for unique match label generation */
static int label = 0;

/* allocate match structure body of specified type */
Match  *match_alloc(int type)
{
    Match  *match = ts_ralloc(Match);

    match->type = type;
    match->label = label++;
    match->weight = (float)1.0;
    match->to1 = match->to2 = NULL;
    match->props = NULL;
    return (match);
}

/* allocate match structure and make it reference generic pointers of
 * specified type
 * 
 * note that the match structure is for matches between things of the same
 * tyoe */
Match  *match_make(void *ptr1, void *ptr2, int type)
{
    Match  *match = ts_ralloc(Match);

    match->type = type;
    match->label = label++;
    match->weight = (float)1.0;
    match->to1 = ptr1;
    match->to2 = ptr2;
    match->props = NULL;
    return (match);
}

/* copy the match data structure and make a copy of its property list
 * 
 * changes to the properties will be shared */
Match  *match_copy(Match * match)
{
    Match  *copy;

    if (match == NULL)
	return (NULL);

    copy = ts_ralloc(Match);
    (void) memcpy((char *) copy, (char *) match, sizeof(Match));
    copy->props = proplist_copy(match->props);
    return (copy);
}

/* find the mostr strongly weighted match in a list */
double  mlist_strongest(List * mlist, double (*cost_func) ( /* ??? */ ))
{
    double  maxs = 0;

    while (mlist != NULL)
    {
	Match  *m = (Match *) mlist->to;
	double  s;

	s = (cost_func == NULL) ? m->weight : cost_func(m);

	if (s > maxs)
	    maxs = s;
	mlist = mlist->next;
    }
    return (maxs);
}

/* check if to2 is referenced as a ->to2 of any element of the match
 * list */
Bool    mlist_to2_exists(List * mlist, void *to2)
{
    List   *ptr;

    for (ptr = mlist; ptr != NULL; ptr = ptr->next)
	if (((Match *) ptr->to)->to2 == to2)
	    return (true);
    return (false);
}

/* generate a list of the second reference (->to2) of a match list */
List   *mlist_to2_list(List * mlist)
{
    List   *mptr;
    List   *list = NULL;

    for (mptr = mlist; mptr != NULL; mptr = mptr->next)
    {
	Match  *m = (Match *) mptr->to;

	list = ref_addtostart(list, (void *) m->to2, m->type);
    }
    return (list_reverse(list));
}

void    match_free(Match * match)
{
    if (match == NULL)
	return;
    proplist_freelist(match->props);
    rfree((void *) match);
}

void    mlist_free(List * mlist)
/* list of matches */
{
    list_rm(mlist, match_free);
}
