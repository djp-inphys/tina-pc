/**@(#)Ddlist handling (doubly directed).
 * @(#)Ddlist is {int type; Ddlist *next; Ddlist *last; void *to;}
 * @(#)They are always referenced by both start and end pointers neither of
 * @(#)which should be nil. The important points being (a) that start and
 * @(#)end are included in the list, and (b) that the list may be part of a
 * @(#)larger list.
 */

#include <stdio.h>
#include <tina/sys.h>

void    rfree();

#define LOOPOVER while (1)

int     ddstr_count(Ddlist * start, Ddlist * end)
{
    Ddlist *dptr;
    int     count;

    if (start == NULL || end == NULL)
	return (0);

    count = 1;
    for (dptr = start; dptr != end; dptr = dptr->next)
	++count;
    return (count);
}

void    ddstr_free(Ddlist * start, Ddlist * end, void (*freefunc) ( /* ??? */ ))
{
    Ddlist *dptr;
    void    dd_ref_free();

    if (start == NULL || end == NULL)
	return;

    dptr = start;

    LOOPOVER
    {
	dd_ref_free(dptr, freefunc);
	if (dptr == end)
	    break;
	dptr = dptr->next;
    }
}

void    ddstr_rm_links(Ddlist * start, Ddlist * end)
{
    Ddlist *dptr;
    Ddlist *next;
    Ddlist *dd_link_rm_el();

    if (start == NULL || end == NULL)
	return;

    dptr = start;

    LOOPOVER
    {
	next = dd_link_rm_el(dptr);
	if (dptr == end)
	    break;
	dptr = next;
    }
}

void    ddstr_rm(Ddlist * start, Ddlist * end, void (*freefunc) ( /* ??? */ ))
{
    Ddlist *dptr;
    Ddlist *next;
    Ddlist *dd_link_rm();

    if (start == NULL || end == NULL)
	return;

    dptr = start;
    LOOPOVER
    {
	next = dd_link_rm(dptr, freefunc);
	if (dptr == end)
	    break;
	dptr = next;
    }
}

Ddlist *ddstr_link_get_by_ref(Ddlist * start, Ddlist * end, void *ptr)
{
    Ddlist *dptr;

    if (start == NULL || end == NULL)
	return (NULL);

    dptr = start;
    LOOPOVER
    {
	if (dptr->to == ptr)
	    return (dptr);
	if (dptr == end)
	    break;
	dptr = dptr->next;
    }
    return (NULL);
}

void    ddstr_reverse(Ddlist ** startp, Ddlist ** endp)
{
    Ddlist *dptr;
    Ddlist *start;
    Ddlist *end;
    Ddlist *dd_link_addtostart();

    if (*startp == NULL || *endp == NULL)
	return;

    end = dptr = *startp;
    start = NULL;

    LOOPOVER
    {
	Ddlist *next = dptr->next;

	start = dd_link_addtostart(start, dptr);
	if (dptr == *endp)
	    break;
	dptr = next;
    }
    *startp = start;
    *endp = end;
}

void    ddstr_copy(Ddlist ** startp, Ddlist ** endp, void *(*copyfunc) ( /* ??? */ ), void *data)
{
    Ddlist *dptr;
    Ddlist *start = NULL;
    Ddlist *end = NULL;
    Ddlist *dd_link_copy();
    Ddlist *dd_link_addtoend();

    if (*startp == NULL || *endp == NULL)
	return;


    dptr = *startp;
    LOOPOVER
    {
	end = dd_link_addtoend(end, dd_link_copy(dptr, copyfunc, data));
	if (start == NULL)
	    start = end;
	if (dptr == *endp)
	    break;
	dptr = dptr->next;
    }
    *startp = start;
    *endp = end;
}

void    ddstr_set_type(Ddlist * start, Ddlist * end, int type, int n)
{
    Ddlist *dptr;
    int     i;

    if (start == NULL || end == NULL)
	return;

    for (i = 0, dptr = start; dptr != end; dptr = dptr->next, ++i)
	if (i % n == 0)
	    dptr->type = type;
    end->type = type;
}

Ddlist *ddstr_nth_point(Ddlist * start, Ddlist * end, int n)
{
    Ddlist *dptr;
    int     i;

    if (start == NULL || end == NULL)
	return (NULL);

    for (i = 0, dptr = start;; dptr = dptr->next, ++i)
    {
	if (i == n)
	    return (dptr);
	if (dptr == end)
	    break;
    }
    return (NULL);
}

Ddlist *ddstr_mid_point(Ddlist * start, Ddlist * end)
{
    int     n;

    if (start == NULL || end == NULL)
	return (NULL);

    n = ddstr_count(start, end) / 2;
    return (ddstr_nth_point(start, end, n));
}

void    ddstr_apply_func(Ddlist * start, Ddlist * end, void (*func) ( /* ??? */ ), void *data)
{
    Ddlist *dptr;

    if (start == NULL || end == NULL)
	return;

    dptr = start;

    LOOPOVER
    {
	func(dptr->to, dptr->type, data);
	if (dptr == end)
	    break;
	dptr = dptr->next;
    }
}

Ddlist *ddstr_get_min(Ddlist * start, Ddlist * end, Bool(*func) ( /* ??? */ ), void *data)
{
    Ddlist *dptr;
    Ddlist *min_ptr = NULL;
    double  d, min_d = 0.0;

    if (start == NULL || end == NULL)
	return (NULL);

    dptr = start;

    LOOPOVER
    {
	if (func(dptr->to, dptr->type, data, &d) == true &&
	    (min_ptr == NULL || d < min_d))
	{
	    min_ptr = dptr;
	    min_d = d;
	}
	if (dptr == end)
	    break;
	dptr = dptr->next;
    }
    return (min_ptr);
}
