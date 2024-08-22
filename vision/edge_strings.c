/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/* ARGSUSED quieten lint */
static void edge_add_prop_def(Edgel * e, int type, Prop_def * pdef)
{
    if (pdef == NULL)
	return;
    e->props = proplist_addifnp(e->props, (void *) pdef->prop, pdef->type, pdef->free_func, pdef->dofree);
}

void    edge_add_prop(Edgel * e, void *ptr, int type, void (*free_func) ( /* ??? */ ), Bool dofree)
{
    if (e == NULL)
	return;
    e->props = proplist_addifnp(e->props, (void *) ptr, type, free_func, dofree);
}

void    es_add_to_prop_list(Tstring * s, void *ptr, int type, void (*free_func) ( /* ??? */ ), Bool dofree)
{
    Prop_def pdef;

    if (s == NULL)
	return;

    pdef.prop = ptr;
    pdef.type = type;
    pdef.free_func = free_func;
    pdef.dofree = dofree;

    str_apply_func(s, edge_add_prop_def, (void *) &pdef);
}

/* code to pick general pos2 strings */

Bool    dist_to_pos2(void *ptr, int type, Vec2 * pp, double *dist)
{
    if (ptr == NULL)
	return (false);

    switch (type)
    {
    case VEC2:
	*dist = vec2_mod(vec2_diff(*pp, *(Vec2 *) ptr));
	return (true);
    case EDGE:
	*dist = vec2_mod(vec2_diff(*pp, ((Edgel *) ptr)->pos));
	return (true);
    default:
	return (false);
    }
}

Tstring *es_closest2(List * strings, Vec2 pos)
{
    Tstring *str_list_get_min();

    return (str_list_get_min(strings, dist_to_pos2, (void *) &pos));
}

void   *es_closest_pos2(List * strings, Vec2 pos, int *type)
{
    Tstring *str = es_closest2(strings, pos);
    Ddlist *dptr;

    if (str == NULL)
	return (NULL);

    dptr = str_get_min(str, dist_to_pos2, (void *) &pos);
    if (dptr == NULL)
	return (NULL);

    *type = dptr->type;
    return (dptr->to);
}

/* hysteresis thresholding for edge strings only */

static Bool hyster(Tstring * string, double thres)
{
    Ddlist *dptr;
    Ddlist *start;
    Ddlist *end;

    if (string == NULL)
	return (false);

    start = string->start;
    end = string->end;

    for (dptr = start; dptr != NULL; dptr = dptr->next)
    {
	if (((Edgel *) (dptr->to))->contrast > thres)
	    return (true);
	if (dptr == end)
	    break;
    }
    return (false);
}

List   *es_list_thres(List * strings, int length_thres, double contrast_thres)
{
    List   *lptr;
    void    edge_set_type_remove_me();

    while (strings != NULL)
    {
	Tstring *sptr = (Tstring *) strings->to;

	if (sptr->count >= length_thres && hyster(sptr, contrast_thres) == true)
	    break;
	str_apply_func((Tstring *) strings->to, edge_set_type_remove_me,
		       NULL);
	strings = link_rm(strings, str_rm_links);
    }

    if (strings == NULL)
	return (NULL);

    lptr = strings;
    while (lptr->next != NULL)
    {
	Tstring *sptr = (Tstring *) lptr->next->to;

	if (sptr->count < length_thres || hyster(sptr, contrast_thres) == false)
	{
	    str_apply_func(sptr, edge_set_type_remove_me, NULL);
	    link_rm_next(lptr, str_rm_links);
	} else
	    lptr = lptr->next;
    }

    return (strings);
}

void    er_edge_strings_thres(Imrect * er, int length_thres, double contrast_thres)
{
    List   *strings;
    void    edge_rm_on_remove_me();

    if (er == NULL)
	return;

    strings = (List *) prop_get(er->props, STRING);
    strings = es_list_thres(strings, length_thres, contrast_thres);
    (void) prop_set(er->props, (void *) strings, STRING, false);
    er_apply_to_all_edges(er, edge_rm_on_remove_me, (void *) er);
}

Bool    es_closest_ends(Tstring * str1, Tstring * str2, Ddlist ** dptr1, Ddlist ** dptr2)
{
    Vec2    s1 = {Vec2_id};
    Vec2    s2 = {Vec2_id};
    Vec2    e1 = {Vec2_id};
    Vec2    e2 = {Vec2_id};
    float   s1s2, s1e2, e1s2, e1e2;

    if (str1 == NULL || str2 == NULL)
	return (false);

    DD_GET_POS2(str1->start, s1);
    DD_GET_POS2(str1->end, e1);
    DD_GET_POS2(str2->start, s2);
    DD_GET_POS2(str2->end, e2);

    s1s2 = (float)vec2_mod(vec2_diff(s1, s2));
    s1e2 = (float)vec2_mod(vec2_diff(s1, e2));
    e1s2 = (float)vec2_mod(vec2_diff(e1, s2));
    e1e2 = (float)vec2_mod(vec2_diff(e1, e2));

    if (MIN(s1s2, s1e2) < MIN(e1s2, e1e2))	/* closest to start s1 */
    {
	*dptr1 = str1->start;
	if (s1s2 < s1e2)	/* starts closest */
	    *dptr2 = str2->start;
	else
	    *dptr2 = str2->end;
    } else
    {
	*dptr1 = str1->end;
	if (e1e2 < e1s2)	/* ends are closest */
	    *dptr2 = str2->end;
	else
	    *dptr2 = str2->start;
    }
    return (true);
}

/* combine pair of strings to produce new string first it finds the
 * closest ends one or other sub-string may be reversed in the new
 * sting the original strings are not affected */
Tstring *es_combine(Tstring * str1, Tstring * str2)
{
    Tstring *str;
    Vec2    s1 = {Vec2_id};
    Vec2    s2 = {Vec2_id};
    Vec2    e1 = {Vec2_id};
    Vec2    e2 = {Vec2_id};
    float   s1s2, s1e2, e1s2, e1e2;

    str1 = str_clone(str1);	/* first copy string structure */
    str2 = str_clone(str2);

    if (str1 == NULL)
	return (str2);
    if (str2 == NULL)
	return (str1);

    DD_GET_POS2(str1->start, s1);
    DD_GET_POS2(str1->end, e1);
    DD_GET_POS2(str2->start, s2);
    DD_GET_POS2(str2->end, e2);

    s1s2 = (float)vec2_mod(vec2_diff(s1, s2));
    s1e2 = (float)vec2_mod(vec2_diff(s1, e2));
    e1s2 = (float)vec2_mod(vec2_diff(e1, s2));
    e1e2 = (float)vec2_mod(vec2_diff(e1, e2));

    if (MIN(s1s2, s1e2) < MIN(e1s2, e1e2))	/* closest to start s1 */
    {
	if (s1s2 < s1e2)	/* starts closest */
	    str_reverse(str2);
	str = str_combine(str2, str1);
    } else
    {
	if (e1e2 < e1s2)	/* ends are closest */
	    str_reverse(str2);
	str = str_combine(str1, str2);
    }
    str_rm_only_str(str1);
    str_rm_only_str(str2);
    return (str);
}

/* concatenate list of stings into new string */
Tstring *es_list_cat(List * strings)
{
    Tstring *str = NULL;
    List   *ptr;

    for (ptr = strings; ptr != NULL; ptr = ptr->next)
	str = es_combine((Tstring *) str, (Tstring *) ptr->to);
    return (str);
}

/* order the list of strings along a virtual meta string only well
 * defined if strings are not very overlapped */
List   *es_list_order(List * strings)
{
    Tstring *str;
    List   *new_start;
    List   *new_end;
    Vec2    s1 = {Vec2_id};
    Vec2    s2 = {Vec2_id};
    Vec2    e1 = {Vec2_id};
    Vec2    e2 = {Vec2_id};
    List   *ptr;

    new_start = new_end = strings;
    strings = strings->next;
    new_start->next = NULL;
    str = (Tstring *) new_start->to;
    DD_GET_POS2(str->start, s1);
    DD_GET_POS2(str->end, e1);

    while (strings != NULL)
    {
	int     start = 0;
	double  mind = 0.0;
	double  d1, d2, d;
	Vec2    minv = {Vec2_id};
	List   *minp = NULL;

	for (ptr = strings; ptr != NULL; ptr = ptr->next)
	{
	    str = (Tstring *) ptr->to;
	    DD_GET_POS2(str->start, s2);
	    DD_GET_POS2(str->end, e2);

	    d1 = vec2_sqrmod(vec2_diff(s2, s1));
	    d2 = vec2_sqrmod(vec2_diff(e2, s1));
	    d = MIN(d1, d2);
	    if (minp == NULL || d < mind)
	    {
		mind = d;
		start = 1;
		minp = ptr;
		minv = (d == d1) ? s2 : e2;
	    }
	    d1 = vec2_sqrmod(vec2_diff(s2, e1));
	    d2 = vec2_sqrmod(vec2_diff(e2, e1));
	    d = MIN(d1, d2);
	    if (d < mind)
	    {
		mind = d;
		start = 0;
		minp = ptr;
		minv = (d == d1) ? s2 : e2;
	    }
	}
	if (start)
	{
	    new_start = link_addtostart(new_start, link_copy(minp,
					  (void *(*) ()) NULL, NULL));
	    s1 = minv;
	} else
	{
	    new_end = link_addtoend(new_end, link_copy(minp,
					  (void *(*) ()) NULL, NULL));
	    new_end->next = NULL;
	    e1 = minv;
	}
	strings = list_rm_el(strings, minp, (void (*) ()) NULL);
    }
    return (new_start);
}

static void es_add_string_to_edge_prop(Tstring * s)
{
    es_add_to_prop_list(s, (void *) s, STRING, (void (*) ()) NULL, false);
}

void    er_reference_strings(Imrect * er)
{
    List   *strings;

    if (er == NULL)
	return;

    strings = (List *) prop_get(er->props, STRING);
    list_apply_func(strings, (void (*) ()) es_add_string_to_edge_prop, NULL);
}

Windex *es_list_build_wx(List * es)
{
    Windex *index;
    Imregion *region;

    region = strings_bounding_region(es);
    if (region == NULL)
	return (NULL);

    index = wx_alloc(region, 16, 16, STRING);
    list_apply_func(es, wx_add_str2, (void *) index);
    return (index);
}

void    es_format(Tstring * es)	/* HP warns Inconsistent type
				 * declaration: "es_format". */
/* BUT its ok */

{
    Ddlist *start;
    Ddlist *end;
    Ddlist *dptr;

    if (es == NULL)
	return;

    start = es->start;
    end = es->end;

    edge_format((Edgel *) start->to);
    for (dptr = start; dptr != end;)
    {
	dptr = dptr->next;
	edge_format((Edgel *) dptr->to);
    }
}
