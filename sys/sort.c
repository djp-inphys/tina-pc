/**@(#)List sorting (generic)
 */

#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>

/* key sorting algorithm */

void    sort_keys_simple(int *key, float *val, int n)
{
    int     i, j;
    int     nm1 = n - 1;

    for (i = 0; i < n; ++i)	/* initialise keys */
	key[i] = i;

    for (i = 0; i < nm1; ++i)
    {
	float   minval = val[key[i]];
	int     minkey = i;

	for (j = i + 1; j < n; ++j)
	    if (val[key[j]] < minval)
	    {
		minkey = j;
		minval = val[key[j]];
	    }
	if (minkey != i)
	{
	    int     temp = key[i];

	    key[i] = key[minkey];
	    key[minkey] = temp;
	}
    }
}

List   *sort_list(List * list, double (*valfunc) ( /* ??? */ ), void *data)
{
    int     i, n;
    float  *val;
    int    *key;
    List  **listel;
    List   *lptr;
    List   *sorted;
    List   *link_addtostart();

    if (list == NULL)
	return (NULL);

    for (lptr = list, n = 0; lptr != NULL; lptr = lptr->next)
	++n;

    val = (float *) ralloc((unsigned) n * sizeof(float));
    key = (int *) ralloc((unsigned) n * sizeof(int));
    listel = (List **) ralloc((unsigned) n * sizeof(List *));

    for (i = 0, lptr = list; i < n; ++i, lptr = lptr->next)
    {
	val[i] = (float) valfunc(lptr->to, lptr->type, data);
	listel[i] = lptr;
    }

    sort_keys_simple(key, val, n);

    sorted = NULL;
    for (i = n - 1; i >= 0; --i)
	sorted = link_addtostart(sorted, listel[key[i]]);

    rfree((void *) val);
    rfree((void *) key);
    rfree((void *) listel);
    return (sorted);
}

Ddlist *sort_ddlist(Ddlist * list, double (*valfunc) ( /* ??? */ ), void *data)
{
    int     i, n;
    float  *val;
    int    *key;
    Ddlist **listel;
    Ddlist *lptr;
    Ddlist *sorted;
    Ddlist *dd_link_addtostart();

    if (list == NULL)
	return (NULL);

    for (lptr = list, n = 0; lptr != NULL; lptr = lptr->next)
	++n;

    val = (float *) ralloc((unsigned) n * sizeof(float));
    key = (int *) ralloc((unsigned) n * sizeof(int));
    listel = (Ddlist **) ralloc((unsigned) n * sizeof(Ddlist *));

    for (i = 0, lptr = list; i < n; ++i, lptr = lptr->next)
    {
	val[i] = (float) valfunc(lptr->to, lptr->type, data);
	listel[i] = lptr;
    }

    sort_keys_simple(key, val, n);

    sorted = NULL;
    for (i = n - 1; i >= 0; --i)
	sorted = dd_link_addtostart(sorted, listel[key[i]]);

    rfree((void *) val);
    rfree((void *) key);
    rfree((void *) listel);
    return (sorted);
}
