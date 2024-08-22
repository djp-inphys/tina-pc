/**@(#)
**/
/* edgerect.c
 * 
 * functions for manipulating Imrects that represent edgerects
 * 
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

void    er_apply_to_all_edges(Imrect * edgerect, void (*edgefunc) ( /* ??? */ ), void *data)
{
    Rindex *row_index;
    int     lx, ly, ux, uy;
    int     i, j;

    if (edgerect == NULL)
	return;

    row_index = prop_get(edgerect->props, ER_ROWS);

    if (row_index != NULL)
    {
	List   *ptr;
	List  **index = (List **) row_index->index;
	Imregion *roi = row_index->region;

	ly = roi->ly;
	uy = roi->uy;

	for (i = ly; i < uy; ++i)
	    for (ptr = index[i]; ptr != NULL; ptr = ptr->next)
		edgefunc(ptr->to, EDGE, data, i, ptr->type);
	return;
    }
    lx = edgerect->region->lx;
    ly = edgerect->region->ly;
    ux = edgerect->region->ux;
    uy = edgerect->region->uy;

    for (i = ly; i < uy; ++i)
	for (j = lx; j < ux; ++j)
	{
	    Edgel  *edge = (Edgel *) IM_PTR(edgerect, i, j);

	    if (edge != NULL)
		edgefunc(edge, EDGE, data, i, j);
	}
}

void    er_apply_to_all_strings(Imrect * er, void (*func) ( /* ??? */ ), void *data)
{
    if (er == NULL)
	return;
    list_apply_func((List *) prop_get(er->props, STRING), func, data);
}

void    es_apply_to_all_edges(Imrect * er, void (*func) ( /* ??? */ ), void *data)
{
    List   *strings;
    List   *lptr;

    if (er == NULL)
	return;

    strings = (List *) prop_get(er->props, STRING);

    for (lptr = strings; lptr != NULL; lptr = lptr->next)
	str_apply_func((Tstring *) lptr->to, func, data);
}

void    er_rm_edges(Imrect * edgerect, unsigned int mask, unsigned int type)	/* rm all edges of
										 * specified type */


{
    int     lx, ly, ux, uy;
    int     i, j;

    if (edgerect == NULL)
	return;

    lx = edgerect->region->lx;
    ly = edgerect->region->ly;
    ux = edgerect->region->ux;
    uy = edgerect->region->uy;

    for (i = ly; i < uy; ++i)
	for (j = lx; j < ux; ++j)
	{
	    Edgel  *edge = (Edgel *) IM_PTR(edgerect, i, j);

	    if ((edge != NULL) && (mask == (int) NULL || type == (edge->type & mask)))
	    {
		edge_free(edge);
		IM_PTR(edgerect, i, j) = NULL;
	    }
	}
}

void    er_free(Imrect * edgerect)
{
    er_apply_to_all_edges(edgerect, edge_free, NULL);
    im_free(edgerect);
}

Edgel  *er_get_edge(Imrect * edgerect, int i, int j)
{
    if (edgerect == NULL || edgerect->vtype != ptr_v ||
	!roi_inregion(edgerect->region, j, i))
	return (NULL);

    return ((Edgel *) IM_PTR(edgerect, i, j));
}

void    er_put_edge(Edgel * edge, Imrect * edgerect, int i, int j)
{
    if (edgerect == NULL || edgerect->vtype != ptr_v ||
	!roi_inregion(edgerect->region, j, i))
	return;

    IM_PTR(edgerect, i, j) = edge;
}

void   *er_closest(Imrect * edgerect, int r, int c, int maxsep, void *(*index_func) ( /* ??? */ ), void *data)
{
    int     i, j, k;
    void   *ptr;
    void   *res;

    if (edgerect == NULL || edgerect->vtype != ptr_v)
	return (NULL);

    if ((ptr = im_get_ptr(edgerect, r, c)) != NULL)
    {
	if (index_func == NULL)
	    return (ptr);
	if ((res = index_func(ptr, data)))
	    return (res);
    }
    for (i = 1; i < maxsep; ++i)
    {
	for (j = -i; j <= i; ++j)
	{
	    void   *ptr[4];

	    ptr[0] = im_get_ptr(edgerect, r + j, c - i);
	    ptr[1] = im_get_ptr(edgerect, r + j, c + i);
	    ptr[2] = im_get_ptr(edgerect, r - i, c + j);
	    ptr[3] = im_get_ptr(edgerect, r + i, c + j);

	    for (k = 0; k < 4; ++k)
	    {
		if (ptr[k] != NULL)
		{
		    if (index_func == NULL)
			return (ptr[k]);
		    if ((res = index_func(ptr[k], data)))
			return (res);
		}
	    }
	}
    }
    return (NULL);
}

int     er_add_edge(Imrect * edgerect, Edgel * edge)
{
    int     i, j;

    if (edgerect == NULL || edge == NULL || edgerect->vtype != ptr_v)
	return (0);

    j = (int)floor(vec2_x(edge->pos));
    i = (int)floor(vec2_y(edge->pos));
    if (!roi_inregion(edgerect->region, j, i))
	return (0);
    if (IM_PTR(edgerect, i, j) == NULL)
    {
	IM_PTR(edgerect, i, j) = (void *) edge;
	return (1);
    } else
	return (0);
}

/* row index allows rapid access to edges
 * 
 * column subscript stored in list type
 * 
 */

void    er_set_row_index(Imrect * er)
/* edge rect */
{
    Rindex *rx;
    Rindex *rx_alloc();
    List  **index;
    int     lx, ly, ux, uy;
    int     i, j;
    void    rx_free_links();

    if (er == NULL)
	return;

    lx = er->region->lx;
    ly = er->region->ly;
    ux = er->region->ux;
    uy = er->region->uy;
    rx = rx_alloc(er->region, EDGE);
    index = (List **) rx->index;

    for (i = ly; i < uy; ++i)
    {
	for (j = lx; j < ux; ++j)
	    if (IM_PTR(er, i, j) != NULL)
		index[i] = ref_addtostart((List *) index[i], (void *) IM_PTR(er, i, j), j);
	index[i] = list_reverse(index[i]);
    }
    er->props = proplist_addifnp(er->props, (void *) rx, ER_ROWS, rx_free_links, true);
}
