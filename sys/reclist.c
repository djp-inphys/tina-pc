/**@(#)Mutually recursive lists & strings handling
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>

/* apply function to recursive lists */

void    reclist_apply(void *ptr, int ptype, void (*func) ( /* ??? */ ), int type, void *data);

void    reclist_list_apply(List * list, void (*func) ( /* ??? */ ), int type, void *data)
{
    List   *ptr;

    for (ptr = list; ptr != NULL; ptr = ptr->next)
	reclist_apply(ptr->to, ptr->type, func, type, data);
}

void    reclist_string_apply(Tstring * str, void (*func) ( /* ??? */ ), int type, void *data)
{
    Ddlist *ptr;
    Ddlist *end;

    if (str == NULL)
	return;

    end = str->end;

    for (ptr = str->start;; ptr = ptr->next)
    {
	reclist_apply(ptr->to, ptr->type, func, type, data);

	if (ptr == end)
	    break;
    }
}

void    reclist_apply(void *ptr, int ptype, void (*func) ( /* ??? */ ), int type, void *data)

/* ptr type */

/* test type */

{
    switch (ptype)
    {
	case LIST:
	reclist_list_apply((List *) ptr, func, type, data);
	break;
    case STRING:
	reclist_string_apply((Tstring *) ptr, func, type, data);
	break;
    default:
	if ((type == (int) NULL) || (type == ptype))
	    func(ptr, ptype, data);
	break;
    }
}

/* reclist rm all occurences of to */

void   *reclist_rm_entry(void *ptr, int type, void *to, void (*freefunc) ( /* ??? */ ));

List   *reclist_list_rm_entry(List * list, void *to, void (*freefunc) ( /* ??? */ ))
{
    List   *ptr;
    List   *next;
    List   *newlist = NULL;

    for (ptr = list; ptr != NULL; ptr = next)
    {
	void   *temp;

	next = ptr->next;
	temp = (void *) reclist_rm_entry(ptr->to, ptr->type, to, freefunc);
	if (temp != NULL)
	    newlist = ref_addtostart(newlist, temp, ptr->type);
    }
    return (list_reverse(newlist));
}

Tstring *reclist_string_rm_entry(Tstring * str, void *to, void (*freefunc) ( /* ??? */ ))
{
    Ddlist *ptr;
    Ddlist *end;
    Ddlist *next;
    Ddlist *newlist = NULL;

    if (str == NULL)
	return (NULL);

    end = str->end;

    for (ptr = str->start;; ptr = next)
    {
	void   *temp;

	next = ptr->next;
	temp = (void *) reclist_rm_entry(ptr->to, ptr->type, to, freefunc);

	if (temp != NULL)
	    newlist = dd_ref_addtostart(newlist, temp, ptr->type);
	if (ptr == end)
	    break;
    }
    if (newlist == NULL)
	return (NULL);
    newlist = dd_list_reverse(newlist);
    return (str_make(str->type, newlist, dd_get_end(newlist)));
}

void   *reclist_rm_entry(void *ptr, int type, void *to, void (*freefunc) ( /* ??? */ ))
{
    switch (type)
    {
	case LIST:
	return ((void *) reclist_list_rm_entry((List *) ptr, to, freefunc));
    case STRING:
	return ((void *) reclist_string_rm_entry((Tstring *) ptr, to, freefunc));
    default:
	if (to != ptr)
	    return (ptr);
	if (freefunc != NULL)
	    freefunc(ptr, type);
	return (NULL);
	break;
    }
    return (NULL);
}

/* copy recursive lists possibly updating their types */
List   *reclist_list_update(List * list, void *(*func) ( /* ??? */ ), int type,
			            void *data)
{
    List   *ptr;
    List   *newlist = NULL;

    for (ptr = list; ptr != NULL; ptr = ptr->next)
    {
	void   *copy;
	int     ptype = ptr->type;

	copy = reclist_update(ptr->to, &ptype, func, type, data);
	if (copy != NULL)
	    newlist = ref_addtostart(newlist, copy, ptype);
    }
    return (list_reverse(newlist));
}

Tstring *reclist_string_update(Tstring * str, void *(*func) ( /* ??? */ ), int type, void *data)
{
    Ddlist *ptr;
    Ddlist *end;
    Ddlist *newlist = NULL;

    if (str == NULL)
	return (NULL);

    end = str->end;

    for (ptr = str->start;; ptr = ptr->next)
    {
	void   *copy;
	int     ptype = ptr->type;

	copy = reclist_update(ptr->to, &ptype, func, type, data);

	if (copy != NULL)
	    newlist = dd_ref_addtostart(newlist, copy, ptype);
	if (ptr == end)
	    break;
    }
    if (newlist == NULL)
	return (NULL);
    newlist = dd_list_reverse(newlist);
    str = str_make(str->type, newlist, dd_get_end(newlist));
    if (str->type == LOOP)
    {
	str->end->next = str->start;
	str->start->last = str->end;
    }
    return (str);
}

void   *reclist_update(void *ptr, int *ptype, void *(*func) ( /* ??? */ ), int type, void *data)

/* ptr type */

/* test type */

{
    switch (*ptype)
    {
	case LIST:
	return ((void *) reclist_list_update((List *) ptr, func, type, data));
    case STRING:
	return ((void *) reclist_string_update((Tstring *) ptr, func, type, data));
    default:
	if ((type == (int) NULL) || (type == *ptype))
	    return ((func == NULL) ? ptr : func(ptr, ptype, data));
	break;
    }
    return (NULL);
}

/* Update recursive lists to simple flat lists allow type of element to
 * be updated */
List   *reclist_flat(void *ptr, int *ptype, void *(*func) ( /* ??? */ ), int type, void *data);
List   *reclist_list_flat(List * list, void *(*func) ( /* ??? */ ), int type, void *data)
{
    List   *ptr;
    List   *listend = NULL;
    List   *flatlist = NULL;

    for (ptr = list; ptr != NULL; ptr = ptr->next)
    {
	List   *newlist;
	int     ptype = ptr->type;

	newlist = reclist_flat(ptr->to, &ptype, func, type, data);
	if (newlist == NULL)
	    continue;
	if (flatlist == NULL)
	    flatlist = newlist;
	else
	    listend->next = newlist;
	listend = list_get_end(newlist);
    }
    return (flatlist);
}

List   *reclist_string_flat(Tstring * str, void *(*func) ( /* ??? */ ), int type, void *data)
{
    Ddlist *ptr;
    Ddlist *end;
    List   *listend = NULL;
    List   *flatlist = NULL;

    if (str == NULL)
	return (NULL);

    end = str->end;

    for (ptr = str->start;; ptr = ptr->next)
    {
	List   *newlist;
	int     ptype = ptr->type;

	newlist = reclist_flat(ptr->to, &ptype, func, type, data);
	if (newlist != NULL)
	{
	    if (flatlist == NULL)
		flatlist = newlist;
	    else
		listend->next = newlist;
	    listend = list_get_end(newlist);
	}
	if (ptr == end)
	    break;
    }
    return (flatlist);
}

List   *reclist_flat(void *ptr, int *ptype, void *(*func) ( /* ??? */ ), int type, void *data)

/* ptr type */

/* test type */

{
    switch (*ptype)
    {
	case LIST:
	return (reclist_list_flat((List *) ptr, func, type, data));
    case STRING:
	return (reclist_string_flat((Tstring *) ptr, func, type, data));
    default:
	if ((type == (int) NULL) || (type == *ptype))
	{
	    ptr = (func == NULL) ? ptr : func(ptr, ptype, data);
	    if (ptr == NULL)
		return (NULL);
	    return (link_alloc((void *) ptr, *ptype));
	}
	break;
    }
    return (NULL);
}

/* copy recursive lists without updating their types */

void   *reclist_copy(void *ptr, int ptype, void *(*func) ( /* ??? */ ), int type, void *data);

List   *reclist_list_copy(List * list, void *(*func) ( /* ??? */ ), int type, void *data)
{
    List   *ptr;
    List   *newlist = NULL;

    for (ptr = list; ptr != NULL; ptr = ptr->next)
    {
	void   *copy;

	copy = reclist_copy(ptr->to, ptr->type, func, type, data);
	if (copy != NULL)
	    newlist = ref_addtostart(newlist, copy, ptr->type);
    }
    return (list_reverse(newlist));
}

Tstring *reclist_string_copy(Tstring * str, void *(*func) ( /* ??? */ ), int type, void *data)
{
    Ddlist *ptr;
    Ddlist *end;
    Ddlist *newlist = NULL;

    if (str == NULL)
	return (NULL);

    end = str->end;

    for (ptr = str->start;; ptr = ptr->next)
    {
	void   *copy;

	copy = reclist_copy(ptr->to, ptr->type, func, type, data);

	if (copy != NULL)
	    newlist = dd_ref_addtostart(newlist, copy, ptr->type);
	if (ptr == end)
	    break;
    }
    if (newlist == NULL)
	return (NULL);
    newlist = dd_list_reverse(newlist);
    return (str_make(str->type, newlist, dd_get_end(newlist)));
}

void   *reclist_copy(void *ptr, int ptype, void *(*func) ( /* ??? */ ), int type, void *data)

/* ptr type */

/* test type */

{
    switch (ptype)
    {
	case LIST:
	return ((void *) reclist_list_copy((List *) ptr, func, type, data));
    case STRING:
	return ((void *) reclist_string_copy((Tstring *) ptr, func, type, data));
    default:
	if ((type == (int) NULL) || (type == ptype))
	    return ((func == NULL) ? ptr : func(ptr, ptype, data));
	break;
    }
    return (NULL);
}

/* Recursive list free */
List   *reclist_list_free(List * list, void (*freefunc) ( /* ??? */ ), int type,
			          void *data)
{
    List   *ptr;
    List   *next;
    List   *last = NULL;

    for (ptr = list; ptr != NULL; ptr = next)
    {
	next = ptr->next;
	ptr->to = reclist_free(ptr->to, ptr->type, freefunc, type, data);
	if (ptr->to == NULL)
	{
	    if (last == NULL)
		list = link_rm_el(list);
	    else
		(void) link_rm_next_el(last);
	} else
	    last = ptr;
    }
    return (list);
}

Tstring *reclist_string_free(Tstring * str, void (*freefunc) ( /* ??? */ ), int type, void *data)
{
    Ddlist *ptr;
    Ddlist *start;
    Ddlist *end;
    Ddlist *next;
    int     more = 1;

    if (str == NULL)
	return (NULL);

    ptr = start = str->start;
    end = str->end;

    do
    {
	next = ptr->next;
	if (ptr == end)
	    more = 0;
	ptr->to = reclist_free(ptr->to, ptr->type, freefunc, type, data);
	if (ptr->to == NULL)
	{
	    if (ptr == end)
	    {
		if (ptr == start)
		    start = end = NULL;
		else
		    end = end->last;
	    }
	    if (ptr == start)
		start = dd_link_rm_el(start);
	    else
		ptr = dd_link_rm_el(ptr);
	}
	ptr = next;
    } while (more);

    if (start == NULL)
    {
	str_rm_only_str(str);
	return (NULL);
    }
    str->start = start;
    str->end = end;
    str->count = ddstr_count(start, end);
    return (str);
}

void   *reclist_free(void *ptr, int ptype, void (*freefunc) ( /* ??? */ ), int type, void *data)

/* ptr type */

/* test type */

{
    switch (ptype)
    {
	case LIST:
	return ((void *) reclist_list_free((List *) ptr, freefunc, type, data));
    case STRING:
	return ((void *) reclist_string_free((Tstring *) ptr, freefunc, type, data));
    default:
	if ((type != (int) NULL) && (type != ptype))
	    return (ptr);
	if (freefunc != NULL)
	    freefunc(ptr, ptype, data);
	return (NULL);
    }
}
