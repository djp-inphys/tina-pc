/**@(#)Ddlist (doubly directed lists) handling.
 * @(#)Ddlist is { int type; Ddlist *next; Ddlist *last; void *to; }
 */
#include <tina/sys.h>
#include <tina/sysfuncs.h>

/* Allocate space and set a single list element */
Ddlist *dd_link_alloc(void *ptr, int type)
{
    Ddlist *list;

    list = ts_ralloc(Ddlist);
    list->next = NULL;
    list->type = type;
    list->last = NULL;
    list->to = ptr;
    return (list);
}

void    dd_ref_set(Ddlist * el, void *ptr, int type)
{
    el->to = ptr;
    el->type = type;
}

Ddlist *dd_list_make(int n, int type)	/* make and initialize a list
					 * of length n */


{
    int     i;
    Ddlist *list = NULL;
    Ddlist *dd_ref_addtostart(Ddlist * list, void *ptr, int type);

    for (i = 0; i < n; i++)
	list = dd_ref_addtostart(list, NULL, type);

    return (list);
}

Ddlist *dd_get_end(Ddlist * list)
{
    if (list == NULL)
	return (NULL);

    while (list->next != NULL)
	list = list->next;

    return (list);
}

Ddlist *dd_get_start(Ddlist * list)
{
    if (list == NULL)
	return (NULL);

    while (list->last != NULL)
	list = list->last;

    return (list);
}

Ddlist *dd_append(Ddlist * l1, Ddlist * l2)	/* append l2 to l1 */

{
    Ddlist *lptr;

    if (l1 == NULL)
	return (l2);

    if (l2 == NULL)
	return (l1);

    for (lptr = l1; lptr->next != NULL; lptr = lptr->next);

    lptr->next = l2;
    l2->last = lptr;

    return (l1);
}

/* Add new element to front of list returning front of list */
Ddlist *dd_link_addtostart(Ddlist * list, Ddlist * el)
{
    if (el == NULL)
	return (list);

    el->next = list;
    el->last = NULL;
    if (list != NULL)
	list->last = el;
    return (el);
}

Ddlist *dd_ref_addtostart(Ddlist * list, void *ptr, int type)
{
    return (dd_link_addtostart(list, dd_link_alloc(ptr, type)));
}

Ddlist *dd_link_addtoend(Ddlist * end, Ddlist * el)	/* add new element to
							 * back of list
							 * returning back of
							 * list */


{
    if (el == NULL)
	return (end);

    el->next = NULL;
    el->last = end;
    if (end != NULL)
	end->next = el;
    return (el);
}

Ddlist *dd_ref_addtoend(Ddlist * end, void *ptr, int type)
{
    return (dd_link_addtoend(end, dd_link_alloc(ptr, type)));
}

Ddlist *dd_list_addtoend(Ddlist * list, Ddlist * el)	/* add new element to
							 * back of list
							 * returning front of
							 * list */


{
    Ddlist *end;

    if (el == NULL)
	return (list);

    end = dd_get_end(list);
    el->next = NULL;
    el->last = end;
    if (list == NULL)
	return (el);

    end->next = el;
    return (list);
}

void    dd_link_addafter(Ddlist * at, Ddlist * el)	/* add new element after
							 * at */


{
    if (at == NULL || el == NULL)
	return;

    el->next = at->next;
    at->next = el;
    el->last = at;
    if (el->next != NULL)
	el->next->last = el;
}

void    dd_link_rm_next_el(Ddlist * at)	/* rm next element from list */

{
    Ddlist *temp;

    if (at == NULL || at->next == NULL)
	return;

    temp = at->next;
    at->next = at->next->next;
    if (at->next != NULL)
	at->next->last = at;
    rfree((void *) temp);
}

Ddlist *dd_link_rm_el(Ddlist * at)	/* rm element returning next */

{
    Ddlist *next;

    if (at == NULL)
	return (NULL);

    next = at->next;

    if (at->next != NULL)
	at->next->last = at->last;

    if (at->last != NULL)
	at->last->next = at->next;

    rfree((void *) at);
    return (next);
}

void    dd_ref_free(Ddlist * at, void (*freefunc) ( /* ??? */ ))	/* free element at */


{
    if (at == NULL || freefunc == NULL)
	return;

    freefunc(at->to, at->type);
    at->to = NULL;
}

void    dd_link_rm_next(Ddlist * at, void (*freefunc) ( /* ??? */ ))	/* free and rm next
									 * element */


{
    if (at == NULL)
	return;

    dd_ref_free(at->next, freefunc);
    (void) dd_link_rm_next_el(at);
}

/* Free and rm this element returning next */
Ddlist *dd_link_rm(Ddlist * at, void (*freefunc) ( /* ??? */ ))
{
    if (at == NULL)
	return (NULL);

    dd_ref_free(at, freefunc);
    return (dd_link_rm_el(at));
}

Ddlist *dd_list_rm_el(Ddlist * list, Ddlist * el, void (*freefunc) ( /* ??? */ ))
{
    if (list == NULL)
	return (NULL);

    if (el == list)
	return (dd_link_rm_el(el));

    (void) dd_link_rm(el, freefunc);	/* actually removes element
					 * from list */
    return (list);
}

Ddlist *dd_link_get_by_ref(Ddlist * list, void *ptr)	/* get list element by
							 * reference */


{
    Ddlist *lptr;

    for (lptr = list; lptr != NULL; lptr = lptr->next)
	if (lptr->to == ptr)
	    return (lptr);

    return (NULL);
}

Ddlist *dd_link_get_by_type(Ddlist * list, int type)	/* get first list
							 * element of type */


{
    Ddlist *lptr;

    for (lptr = list; lptr != NULL; lptr = lptr->next)
	if (lptr->type == type)
	    return (lptr);

    return (NULL);
}

Ddlist *dd_list_rm_ref(Ddlist * list, void *ptr, void (*freefunc) ( /* ??? */ ))
{
    Ddlist *el;

    if (list == NULL)
	return (NULL);

    el = dd_link_get_by_ref(list, ptr);
    if (el == NULL)
	return (NULL);
    return (dd_list_rm_el(list, el, freefunc));
}

void    dd_list_rm_links(Ddlist * list)	/* remove a list */

{
    while (list != NULL)
	list = dd_link_rm_el(list);
}

Ddlist *dd_list_rm_links_on_type(Ddlist * list, int type)
{
    Ddlist *lptr;

    while (list != NULL && list->type == type)
	list = dd_link_rm_el(list);

    for (lptr = list->next; lptr != NULL;)
	if (lptr->type == type)
	    (void) dd_link_rm_el(lptr);
	else
	    lptr = lptr->next;

    return (list);
}

Ddlist *dd_list_rm_links_on_func(Ddlist * list, Bool(*func) ( /* ??? */ ))
{
    Ddlist *lptr;

    while (list != NULL && func(list->to, list->type) == true)
	list = dd_link_rm_el(list);

    for (lptr = list->next; lptr != NULL;)
	if (func(lptr->to, lptr->type) == true)
	    lptr = dd_link_rm_el(lptr);
	else
	    lptr = lptr->next;

    return (list);
}

void    dd_list_free_refs(Ddlist * list, void (*freefunc) ( /* ??? */ ))	/* free the elements of
										 * a list */


{
    Ddlist *lptr;

    for (lptr = list; lptr != NULL; lptr = lptr->next)
	dd_ref_free(lptr, freefunc);
}

/* Free and rm the elements of a list */
void    dd_list_rm(Ddlist * list, void (*freefunc) ( /* ??? */ ))
{
    while (list != NULL)
	list = dd_link_rm(list, freefunc);
}

Ddlist *dd_link_copy(Ddlist * el, void *(*cpfunc) ( /* ??? */ ), void *data)
{
    void   *cpy;

    if (cpfunc == NULL)
	return (dd_link_alloc(el->to, el->type));
    cpy = cpfunc(el->to, el->type, data);
    return ((cpy == NULL) ? NULL : dd_link_alloc(cpy, el->type));
}

Ddlist *dd_list_copy(Ddlist * list, void *(*cpfunc) ( /* ??? */ ), void *data)	/* copy a whole list */



{
    Ddlist *copy;
    Ddlist *end;
    Ddlist *lptr;

    if (list == NULL)
	return (NULL);

    for (end = NULL, lptr = list; end == NULL && lptr != NULL; lptr = lptr->next)
	end = copy = dd_link_copy((Ddlist *) list->to, cpfunc, data);

    for (; lptr != NULL; lptr = lptr->next)
	end = dd_link_addtoend(end, dd_link_copy((Ddlist *) lptr->to, cpfunc, data));
    return (copy);
}

Ddlist *dd_list_reverse(Ddlist * list)	/* reverse a list without
					 * copying it */

{
    Ddlist *rev = NULL;

    while (list)
    {
	Ddlist *next;

	next = list->next;
	rev = dd_link_addtostart(rev, list);
	list = next;
    }
    return (rev);
}

Ddlist *dd_list_reversecopy(Ddlist * list, void (*cpfunc) ( /* ??? */ ), void *data)
{
    Ddlist *rev = NULL;
    Ddlist *lptr;

    for (lptr = list; lptr != NULL; lptr = lptr->next)
	rev = dd_link_addtostart(rev, dd_link_copy((Ddlist *) lptr->to,
					(void *(*) ()) cpfunc, data));

    return (rev);
}

void    dd_apply_func(Ddlist * list, void (*func) ( /* ??? */ ), void *data)
{
    Ddlist *lptr;

    for (lptr = list; lptr != NULL; lptr = lptr->next)
	func(lptr->to, lptr->type, data);
}

Ddlist *dd_get_min(Ddlist * list, Bool(*func) ( /* ??? */ ), void *data)
{
    Ddlist *lptr;
    Ddlist *min_ptr = NULL;
    double  min_d = 0.0;
    double  d;

    for (lptr = list; lptr != NULL; lptr = lptr->next)
    {
	if (func(lptr->to, lptr->type, data, &d) == true &&
	    (min_ptr == NULL || d < min_d))
	{
	    min_ptr = lptr;
	    min_d = d;
	}
    }
    return (min_ptr);
}

Ddlist *dd_nth_el(Ddlist * list, int n)
{
    int     i;

    for (i = 0; i < n; ++i, list = list->next)
	if (list == NULL)
	    return (NULL);

    return (list);
}

#ifndef ANSIFYING
#ifdef __STRICT_ANSI__


Ddlist *dd_list_of(void *ptr,...)
{
    va_list ap;
    Ddlist *list = NULL;

    va_start(ap, ptr);

    while (ptr)
    {
	int     type = va_arg(ap, int);

	list = dd_ref_addtostart(list, ptr, type);
	ptr = va_arg(ap, void *);

    }
    va_end(ap);
    return (dd_list_reverse(list));
}

#else

Ddlist *dd_list_of(va_alist) va_dcl
{
    va_list ap;
    Ddlist *list = NULL;
    void   *ptr;

    va_start(ap);
    while ((ptr = va_arg(ap, void *)) != NULL)
    {
	int     type = va_arg(ap, int);

	list = dd_ref_addtostart(list, ptr, type);
    }
    va_end(ap);

    return (dd_list_reverse(list));
}

#endif				/* __STRICT_ANSI__ */
#endif				/* ANSIFYING */
