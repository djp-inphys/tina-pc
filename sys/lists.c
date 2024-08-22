/**@(#)List handling. (singly directed)
 * @(#)List is { int type; List *next; void *to; }
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>

/* Allocate space for a single list element and set reference to ptr */
List   *link_alloc(void *ptr, int type)
{
    List   *list = ts_ralloc(List);

    list->next = NULL;
    list->type = type;
    list->to = ptr;
    return (list);
}

/* Set list element reference to ptr */
void    ref_set(List * el, void *ptr, int type)
{
    el->to = ptr;
    el->type = type;
}

/* Make a list of n elements */
List   *list_make(int n, int type)
{
    List   *list = NULL;
    int     i;

    for (i = 0; i < n; i++)
    {
	List   *lptr = ts_ralloc(List);

	lptr->next = list;
	list = lptr;
	list->type = type;
	list->to = NULL;
    }
    return (list);
}

/* Get last element of list */
List   *list_get_end(List * list)
{
    if (list == NULL)
	return (NULL);

    while (list->next != NULL)
	list = list->next;

    return (list);
}

/* Append list l2 to l1 */
List   *list_append(List * l1, List * l2)

{
    List   *lptr;

    if (l1 == NULL)
	return (l2);

    if (l2 == NULL)
	return (l1);

    for (lptr = l1; lptr->next != NULL; lptr = lptr->next);

    lptr->next = l2;

    return (l1);
}

/* Add new element to front of list. Return new front of list */
List   *link_addtostart(List * list, List * el)
{
    if (el == NULL)
	return (list);

    el->next = list;
    return (el);
}

List   *ref_addtostart(List * list, void *ptr, int type)
{
    return (link_addtostart(list, link_alloc(ptr, type)));
}

List   *list_addtostart(List * list, List * el)
/* add new element to front of list */
/* return new front of list */
/* - same as link_addtostart */
{
    if (el == NULL)
	return (list);

    el->next = list;
    return (el);
}

List   *link_addtoend(List * end, List * el)	/* add link to back of
						 * list */
/* return new back of list */

{
    if (el == NULL)
	return (end);

    el->next = NULL;
    if (end != NULL)
	end->next = el;

    return (el);
}

List   *ref_addtoend(List * end, void *ptr, int type)
{
    return (link_addtoend(end, link_alloc((void *) ptr, type)));
}

List   *list_addtoend(List * list, List * el)	/* add new element to
						 * back of list */
/* return new front of list */
/* only if list is NULL will front change */
{
    List   *end;

    if (el == NULL)
	return (list);

    el->next = NULL;
    if (list == NULL)
	return (el);

    end = list_get_end(list);
    end->next = el;
    return (list);
}

void    link_addafter(List * at, List * el)	/* add new element to
						 * list after at */


{
    if (at == NULL || el == NULL)
	return;

    el->next = at->next;
    at->next = el;
}

void    link_rm_next_el(List * at)	/* rm next element from list */

{
    List   *temp;

    if (at == NULL || at->next == NULL)
	return;

    temp = at->next;
    at->next = at->next->next;
    rfree((void *) temp);
}

/* rm element from list, return next element in list, the list will now
 * be broken */
List   *link_rm_el(List * at)
{
    List   *list;

    if (at == NULL)
	return (NULL);

    list = at->next;
    rfree((void *) at);
    return (list);
}

/* Free the reference of this element */
void    ref_free(List * at, void (*freefunc) ( /* ??? */ ))
{
    if (at == NULL || freefunc == NULL)
	return;

    freefunc(at->to, at->type);
    at->to = NULL;
}

void    link_rm_next(List * at, void (*freefunc) ( /* ??? */ ))	/* free and rm next
								 * element of list */


{
    if (at == NULL)
	return;
    ref_free(at->next, freefunc);
    link_rm_next_el(at);
}

/* Free and rm this * element from list */
List   *link_rm(List * at, void (*freefunc) ( /* ??? */ ))
/* return next element in list */
/* the list will now be broken */
{
    if (at == NULL)
	return (NULL);

    ref_free(at, freefunc);
    return (link_rm_el(at));
}

List   *list_rm_el(List * list, List * el, void (*freefunc) ( /* ??? */ ))	/* rm this element from
										 * list */
/* return new list */
/* the list will not be broken */

{
    List   *lptr;

    if (list == NULL)
	return (NULL);

    if (el == list)
	return (link_rm(list, freefunc));

    for (lptr = list; lptr->next != NULL; lptr = lptr->next)
	if (lptr->next == el)
	{
	    link_rm_next(lptr, freefunc);
	    break;
	}
    return (list);
}

/* Rm element from list by reference. Return new list. The list will
 * not be broken */
List   *list_rm_ref(List * list, void *ptr, void (*freefunc) ( /* ??? */ ))
{
    List   *lptr;

    if (list == NULL)
	return (NULL);

    if (ptr == list->to)
	return (link_rm(list, freefunc));

    for (lptr = list; lptr->next != NULL; lptr = lptr->next)
	if (lptr->next->to == ptr)
	{
	    link_rm_next(lptr, freefunc);
	    break;
	}
    return (list);
}

void    list_rm_links(List * list)	/* rm all elements of list */

{
    while (list != NULL)
	list = link_rm_el(list);
}

List   *list_rm_links_on_type(List * list, int type)
{
    List   *lptr;

    while (list != NULL && list->type == type)
	list = link_rm_el(list);

    for (lptr = list; lptr != NULL && lptr->next != NULL;)
	if (lptr->next->type == type)
	    link_rm_next_el(lptr);
	else
	    lptr = lptr->next;

    return (list);
}

List   *list_rm_links_on_func(List * list, Bool(*func) ( /* ??? */ ), void *data)
{
    List   *lptr;

    while (list != NULL && func(list->to, list->type, data) == true)
	list = link_rm_el(list);

    for (lptr = list; lptr != NULL && lptr->next != NULL;)
	if (func(lptr->next->to, lptr->next->type, data) == true)
	    link_rm_next_el(lptr);
	else
	    lptr = lptr->next;

    return (list);
}

/* Free all references of list */
void    list_free_refs(List * list, void (*freefunc) ( /* ??? */ ))
{
    List   *lptr;

    for (lptr = list; lptr != NULL; lptr = lptr->next)
	ref_free(lptr, freefunc);
}

/* Free and rm all elements of list */
void    list_rm(List * list, void (*freefunc) ())
{
    while (list != NULL)
	list = link_rm(list, freefunc);
}

void    list_list_rm(List * list)
{
    list_rm(list, list_rm_links);
}

List   *link_copy(List * el, void *(*cpfunc) ( /* ??? */ ), void *data)	/* copy list element */



{
    void   *cpy;

    if (cpfunc == NULL)
	return (link_alloc((void *) el->to, el->type));
    cpy = cpfunc(el->to, el->type, data);
    return ((cpy == NULL) ? NULL : link_alloc((void *) cpy, el->type));
}

List   *list_copy(List * list, void *(*cpfunc) ( /* ??? */ ), void *data)	/* copy whole list */



{
    List   *copy;
    List   *end;
    List   *lptr;

    if (list == NULL)
	return (NULL);

    for (end = NULL, lptr = list; end == NULL && lptr != NULL; lptr = lptr->next)
	end = copy = link_copy(lptr, cpfunc, data);

    for (; lptr != NULL; lptr = lptr->next)
	end = link_addtoend(end, link_copy(lptr, cpfunc, data));
    return (copy);
}

List   *list_reverse(List * list)	/* reverse list */

{
    List   *rev = NULL;

    while (list)
    {
	List   *next;

	next = list->next;
	rev = link_addtostart(rev, list);
	list = next;
    }
    return (rev);
}

/* Copy list reversed */
List   *list_reversecopy(List * list, void *(*cpfunc) ( /* ??? */ ), void *data)
{
    List   *rev = NULL;
    List   *lptr;

    for (lptr = list; lptr != NULL; lptr = lptr->next)
	rev = link_addtostart(rev, link_copy(lptr, cpfunc, data));

    return (rev);
}

/* Apply function to list */
void    list_apply_func(List * list, void (*func) ( /* ??? */ ), void *data)
{
    List   *lptr;

    for (lptr = list; lptr != NULL; lptr = lptr->next)
	func(lptr->to, lptr->type, data);
}

/* Find min function value */
List   *list_get_min(List * list, Bool(*func) ( /* ??? */ ), void *data)
{
    List   *lptr;
    List   *min_ptr = NULL;
    double  d, min_d = 0.0;

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

/* Get list element by reference */
List   *link_get_by_ref(List * list, void *ptr)
{
    List   *lptr;

    for (lptr = list; lptr != NULL; lptr = lptr->next)
	if (lptr->to == ptr)
	    return (lptr);

    return (NULL);
}

/* Get first list element of type */
List   *link_get_by_type(List * list, int type)
{
    List   *lptr;

    for (lptr = list; lptr != NULL; lptr = lptr->next)
	if (lptr->type == type)
	    return (lptr);

    return (NULL);
}

List   *list_add_sorted(List * list, List * el, double (*sortfunc) ( /* ??? */ ))
{
    double   val;
    List   *lptr;

    if (el == NULL)
	return (list);
    if (list == NULL)
    {
	el->next = NULL;
	return (el);
    }
    val = sortfunc(el->to, el->type);

    if (val < sortfunc(list->to, list->type))
	return (list_addtostart(list, el));

    for (lptr = list; lptr->next != NULL; lptr = lptr->next)
	if (val < sortfunc(lptr->next->to, lptr->next->type))
	    break;

    link_addafter(lptr, el);
    return (list);
}

#ifndef ANSIFYING
#ifdef __STRICT_ANSI__


List   *list_of(int type,...)
{
    va_list ap;
    List   *list = NULL;

    va_start(ap, type);

    while (type)
    {
	void   *ptr = va_arg(ap, void *);

	list = ref_addtostart(list, ptr, type);
	type = va_arg(ap, int);
    }
    va_end(ap);
    return (list_reverse(list));
}

#else

List   *list_of(va_alist) va_dcl
{
    va_list ap;
    List   *list = NULL;
    int     type;

    va_start(ap);
    while ((type = va_arg(ap, int)) != 0)
    {
	void   *ptr = va_arg(ap, void *);

	list = ref_addtostart(list, ptr, type);
    }
    va_end(ap);
    return (list_reverse(list));
}

#endif				/* __STRICT_ANSI__ */
#endif				/* ANSIFYING */

void   *list_query(List * list, void *(*match_func) ( /* ??? */ ), void *key)
{
    void   *data;

    for (data = NULL;
	 list && !(data = match_func(key, list->to));
	 list = list->next);

    return data;
}
