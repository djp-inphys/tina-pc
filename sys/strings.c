/** @(#)Tstring handling (Tstring is generic list).
 * @(#)Tstring is {int type; Ddlist *start; Ddlist *end; int count; Listprops;}
 * @(#)Tstring represents and manipulates connected data (eg derived from
 * @(#)edges) as a whole. Tstring handling functions are prefixed str. */

#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>

List *proplist_copy();
Ddlist *dd_list_make();
Ddlist *dd_get_end();

Tstring *str_alloc(void)
{
    /* allocate string structure and initialise pointers to nil */
    Tstring *str = ts_ralloc(Tstring);
    str->count = str->type = 0;
    str->start = str->end = (Ddlist *) NULL;
    str->props = NULL;
    return (str);
}

Tstring *str_make(int type, Ddlist * start, Ddlist * end)
{
    Tstring *str = ts_ralloc(Tstring);
    str->type = type;
    str->start = start;
    str->end = end;
    if (type == LOOP)
    {
	start->last = end;
	end->next = start;
    }
    str->count = ddstr_count(start, end);
    str->props = NULL;
    return (str);
}

Ddlist *str_mid_point(Tstring * str)
{
    Ddlist *ddstr_nth_point();
    if (str == NULL)
	return (NULL);
    return (ddstr_nth_point(str->start, str->end, str->count / 2));
}

/* copy of n evenly spaced points along a string */

Tstring *str_divide(Tstring * str, int n)
{
    Tstring *new = str_alloc();
    Ddlist *ddnew = (Ddlist *) dd_list_make(n, (int) NULL);
    Ddlist *dd1, *dd2;
    int i, j, l;
    double dl;

    new->type = str->type;
    new->start = ddnew;
    new->end = dd_get_end(ddnew);
    new->count = n;

    l = str->count;
    switch (str->type)
    {
      case STRING:
	dl = (l - 1) / (n - 1);
	break;
      case LOOP:
	dl = (l - 1) / n;
	new->end->next = new->start;
	new->start->last = new->end;
	break;
    }

    for (i = 0, j = 0, dd1 = str->start, dd2 = ddnew;
	 j < n;
	 i++, dd1 = dd1->next, dd2 = dd2->next)
    {
	if (i >= j * dl || (str->type == STRING && dd1 == str->end))
	{
	    dd2->type = dd1->type;
	    dd2->to = dd1->to;
	    j++;
	}
    }

    return (new);
}

void str_free(Tstring * str, void (*freefunc) ( /* ??? */ ))
{
    void ddstr_free();

    if (str == NULL)
	return;

    proplist_freelist(str->props);
    ddstr_free(str->start, str->end, freefunc);
    rfree((void *) str);
}

void str_rm_links(Tstring * str)
{
    void ddstr_rm_links();

    if (str == NULL)
	return;

    proplist_freelist(str->props);
    ddstr_rm_links(str->start, str->end);
    rfree((void *) str);
}

void str_rm(Tstring * str, void (*freefunc) ( /* ??? */ ))
{
    void ddstr_rm();

    if (str == NULL)
	return;

    proplist_freelist(str->props);
    ddstr_rm(str->start, str->end, freefunc);
    rfree((void *) str);
}

void str_rm_only_str(Tstring * str)
{
    if (str == NULL)
	return;

    proplist_freelist(str->props);
    rfree((void *) str);
}

Tstring *str_segment(Tstring * str, Ddlist * at)
{
    Ddlist *start;
    Ddlist *end;

    if (str == NULL)
	return (NULL);

    start = str->start;
    end = str->end;

    if (at == start || at == end)
	return (NULL);

    str->end = at;
    str->count = ddstr_count(start, at);
    return (str_make(str->type, at->next, end));
}

Ddlist *str_link_get_by_ref(Tstring * str, void *ptr)
{
    Ddlist *ddstr_link_get_by_ref();

    if (str == NULL)
	return (NULL);

    return (ddstr_link_get_by_ref(str->start, str->end, ptr));
}

Tstring *str_list_get_by_ref(List * strings, void *ptr)
{
    List *lptr;

    for (lptr = strings; lptr != NULL; lptr = lptr->next)
	if (str_link_get_by_ref((Tstring *) lptr->to, ptr) != NULL)
	    return ((Tstring *) lptr->to);
    return (NULL);
}

void str_reverse(Tstring * str)
{
    void ddstr_reverse();
    if (str == NULL)
	return;
    ddstr_reverse(&(str->start), &(str->end));
    if(str->type == LOOP)
    {
	str->start->last = str->end;
	str->end->next = str->start;
    }
}

Tstring *str_combine(Tstring * s1, Tstring * s2)
{
    if (s1 == NULL || s2 == NULL)
	return (NULL);

    s1->end->next = s2->start;
    s2->start->last = s1->end;
    return (str_make(s1->type, s1->start, s2->end));
}

Tstring *str_copy(Tstring * str, void *(*copyfunc) ( /* ??? */ ), void *data)
{
    Tstring *copy;
    Ddlist *start;
    Ddlist *end;
    void ddstr_copy();

    if (str == NULL)
	return (NULL);

    start = str->start;
    end = str->end;
    ddstr_copy(&start, &end, copyfunc, data);
    copy = str_make(str->type, start, end);
    copy->props = proplist_copy(str->props);
    return (copy);
}

Tstring *str_clone(Tstring * str)	/* new string pointing at old
					 * data */

{
    Tstring *copy;
    Ddlist *start;
    Ddlist *end;

    if (str == NULL)
	return (NULL);

    start = str->start;
    end = str->end;

    ddstr_copy(&start, &end, (void *(*) ()) NULL, NULL);
    if (str->start->last == str->end)
    {
	start->last = end;
	end->next = start;
    }
    copy = str_make(str->type, start, end);
    copy->props = proplist_copy(str->props);
    return (copy);
}

void str_apply_func(Tstring * str, void (*func) ( /* ??? */ ), void *data)
{
    void ddstr_apply_func();

    if (str == NULL)
	return;

    ddstr_apply_func(str->start, str->end, func, data);
}

Ddlist *str_get_min(Tstring * str, Bool(*func) ( /* ??? */ ), void *data)
{
    Ddlist *ddstr_get_min();
    Ddlist *ddlist = NULL;

    if (str)
    {
	ddlist = ddstr_get_min(str->start, str->end, func, data);
    }
    return ddlist;
}

Bool str_get_min_dist(Tstring * str, Bool(*func) ( /* ??? */ ), void *data, double *d)
{
    Ddlist *min_ptr = str_get_min(str, func, data);

    return (func(min_ptr->to, min_ptr->type, data, d));
}

Tstring *str_list_get_min(List * strings, Bool(*func) ( /* ??? */ ), void *data)
{
    List *ptr;
    Tstring *min_str = NULL;
    double d, min_d = 0.0;

    for (ptr = strings; ptr != NULL; ptr = ptr->next)
    {
	if (str_get_min_dist((Tstring *) ptr->to, func, data, &d) == false)
	    continue;

	if (min_str == NULL || d < min_d)
	{
	    min_str = ptr->to;
	    min_d = d;
	}
    }
    return (min_str);
}

void str_rm_list(List * strings)
{
    list_rm(strings, str_rm_links);
}

int str_length(Tstring * str)
{
    int i;
    Ddlist *dd;

    if (str == NULL)
	return (-1);

    for (dd = str->start, i = 1;; dd = dd->next, i++)
	if (dd == str->end)
	    break;

    return (i);
}
