/**@(#)Property list handling.  (Using generic lists & Props).
 * @(#)Prop is { int type; int count; void (*freefunc)(); void *to; }
 */

#include <stdio.h>
#include <tina/sys.h>
#include <tina/sys_types.h>
#include <tina/sysfuncs.h>
#include <tina/lists.h>

/* Alloc and init prop structure */
static Prop *prop_alloc(void *ptr, int type, void (*freefunc) ( /* ??? */ ))
{
    Prop   *prop = ts_ralloc(Prop);

    prop->type = type;
    prop->freefunc = freefunc;
    prop->count = 1;
    prop->to = ptr;
    return (prop);
}

/* Get first ref of given type */
static Prop *prop_get_by_type(List * proplist, int type)
{
    List   *lptr;
    Prop   *prop;

    for (lptr = proplist; lptr != NULL; lptr = lptr->next)
    {
	prop = (Prop *) lptr->to;
	if (prop->type == type)
	    return (prop);
    }

    return (NULL);
}

static Prop *prop_get_by_ref(List * proplist, void *ptr)
{
    List   *lptr;
    Prop   *prop;

    for (lptr = proplist; lptr != NULL; lptr = lptr->next)
    {
	prop = (Prop *) lptr->to;
	if (prop->to == ptr)
	    return (prop);
    }

    return (NULL);
}

/* Add a new prop to front */
List   *proplist_add(List * proplist, void *ptr, int type, void (*freefunc) ( /* ??? */ ))
{
    List   *lptr;

    lptr = link_alloc((void *) prop_alloc(ptr, type, freefunc), PROP_TYPE);
    return (link_addtostart(proplist, lptr));
}

/* Add if not present */
List   *proplist_addifnp(List * proplist, void *ptr, int type, void (*freefunc) ( /* ??? */ ), Bool dofree)
{
    List   *lptr;
    Prop   *prop = prop_get_by_type(proplist, type);

    if (prop != NULL)
    {
	if (dofree == true && prop->freefunc != NULL)
	    prop->freefunc(prop->to, prop->type);
	prop->to = ptr;
	return (proplist);
    }
    lptr = link_alloc((void *) prop_alloc(ptr, type, freefunc), PROP_TYPE);
    return (link_addtostart(proplist, lptr));
}

/* Get first prop of specified type */
void   *prop_get(List * proplist, int type)
{
    Prop   *prop = prop_get_by_type(proplist, type);

    return ((prop == NULL) ? NULL : prop->to);
}

int     prop_present(List * proplist, int type)
{
    Prop   *prop = prop_get_by_type(proplist, type);

    return (prop != NULL);
}

int     prop_ref_present(List * proplist, void *ptr)
{
    List   *lptr;

    for (lptr = proplist; lptr != NULL; lptr = lptr->next)
	if (((Prop *) lptr->to)->to == ptr)
	    return (1);
    return (0);
}

/* Get first element of * proplist */
void   *prop_first(List * proplist, int *type)
{
    if (proplist == NULL)
    {
	*type = 0;
	return (NULL);
    }
    *type = ((Prop *) proplist->to)->type;
    return (((Prop *) proplist->to)->to);
}

/* Set/reset prop of specified type */
int     prop_set(List * proplist, void *ptr, int type, Bool dofree)
{
    /* if true try to free the referenced property value */
    Prop   *prop = prop_get_by_type(proplist, type);

    if (prop == NULL)
	return (0);

    if (dofree == true && prop->freefunc != NULL)
	prop->freefunc(prop->to, prop->type);

    prop->to = ptr;
    return (1);
}

List   *proplist_copy(List * proplist)
{
    List   *list_copy();
    List   *copy;
    List   *lptr;

    copy = list_copy(proplist, (void *(*) ()) NULL, NULL);	/* copy list only (not
								 * prop) */

    for (lptr = copy; lptr != NULL; lptr = lptr->next)
	++((Prop *) (lptr->to))->count;
    return (copy);
}

/* Rm prop ref from list */
List   *proplist_rm(List * proplist, int type)
{
    Prop   *prop = prop_get_by_type(proplist, type);
    List   *list_rm_ref();

    if (prop == NULL)
	return (proplist);

    if (--prop->count)
	return (list_rm_ref(proplist, (void *) prop, (void (*) ()) NULL));
    else
	return (list_rm_ref(proplist, (void *) prop, (void (*) ()) rfree));
}

/* Rm prop ref from list */
List   *proplist_rm_by_ref(List * proplist, void *ptr)
{
    Prop   *prop = prop_get_by_ref(proplist, ptr);
    List   *list_rm_ref();

    if (prop == NULL)
	return (proplist);

    if (--prop->count)
	return (list_rm_ref(proplist, (void *) prop, (void (*) ()) NULL));
    else
	return (list_rm_ref(proplist, (void *) prop, (void (*) ()) rfree));
}

/* Rm prop ref and free prop */
List   *proplist_free(List * proplist, int type)
{
    Prop   *prop = prop_get_by_type(proplist, type);
    List   *list_rm_ref();

    if (prop == NULL)
	return (proplist);

    if (--prop->count)
	return (list_rm_ref(proplist, (void *) prop, (void (*) ()) NULL));
    else
    {				/* last reference */
	if (prop->freefunc != NULL)
	    prop->freefunc(prop->to, prop->type);

	return (list_rm_ref(proplist, (void *) prop, rfree));
    }
}

List   *proplist_free_by_ref(List * proplist, void *ptr)
{
    Prop   *prop = prop_get_by_ref(proplist, ptr);
    List   *list_rm_ref();

    if (prop == NULL)
	return (proplist);

    if (--prop->count)
	return (list_rm_ref(proplist, (void *) prop, (void (*) ()) NULL));
    else
    {				/* last reference */
	if (prop->freefunc != NULL)
	    prop->freefunc(prop->to, prop->type);

	return (list_rm_ref(proplist, (void *) prop, rfree));
    }
}

static void prop_rm(Prop * prop)
{
    if (prop == NULL)
	return;

    if (!(--prop->count))
	rfree((void *) prop);
}

static void prop_free(Prop * prop)
{
    if (prop == NULL)
	return;

    if (!(--prop->count))
    {
	if (prop->freefunc != NULL)
	    prop->freefunc(prop->to, prop->type);
	rfree((void *) prop);
    }
}

/* Rm all references in proplist */
void    proplist_rmlist(List * proplist)
{
    void    list_rm();

    list_rm(proplist, prop_rm);
}

/* Rm the first property in the list */
List   *proplist_rm_first(List * proplist)
{
    List   *link_rm();

    return (link_rm(proplist, prop_rm));
}

/* Free whole list */
void    proplist_freelist(List * proplist)
{
    void    list_rm();

    list_rm(proplist, prop_free);
}
