/**@(#)
**/
/* functions for indexing the edgerect structure at the edgel level.
 * 
 */
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

static Vec2 *(*locate) ();
static Imregion *er_rect_bounding_region(Imrect * er);


/* routine to construct a fast access index for edge structures stored
 * in the Imrect er. The indexing scheme is positional using the
 * location for each edge defined by the function locate_func. The
 * resulting structure is put into the Imrects property list for later
 * retrieval by the given type and then returned. */
Rindex *er_set_findex(Imrect * er, int type, Vec2 * (*locate_func) ( /* ??? */ ))
{
    Rindex *fx;
    Rindex *rx_alloc();
    Imregion *index_region;
    int     lx, ly, ux, uy;
    int     i, j;
    Vec2   *edge_pos(Edgel * edgel);
    void    rx_free_links();

    if (er->vtype != ptr_v)
    {
	error("findex: passed non edge rect ", non_fatal);
	return (NULL);
    }
    if (locate_func == NULL)
	locate = edge_pos;
    else
	locate = locate_func;

    index_region = er_rect_bounding_region(er);
    if (index_region == NULL)
    {
	error("findex: nill region ", non_fatal);
	return (NULL);
    }
    fx = rx_alloc(index_region, type);

    lx = er->region->lx;
    ly = er->region->ly;
    ux = er->region->ux;
    uy = er->region->uy;

    for (i = ly; i < uy; ++i)
    {
	for (j = lx; j < ux; ++j)
	{
	    Edgel  *edge = (Edgel *) IM_PTR(er, i, j);

	    if (edge != NULL)
	    {
		List   *link_addtostart();
		Vec2   *rect;
		int     ry;

		if ((rect = locate(edge)) != NULL)
		{
		    ry = (int)floor(rect->el[1]);
		    fx->index[ry] = link_addtostart((List *) fx->index[ry],
				   link_alloc((void *) edge, STRING));
		}
	    }
	}
    }
    er->props = proplist_addifnp(er->props, (void *) fx, type, rx_free_links, true);
    return (fx);
}

Vec2   *edge_pos(Edgel * edgel)
{
    return (&edgel->pos);
}

/* ARGSUSED quieten lint */
static void inc_region(Edgel * edge, int type, Imregion * roi)

/* not used */

{
    int     x, y;
    Vec2   *rect;

    if ((rect = locate(edge)) == NULL)
	return;
    x = (int)floor(rect->el[0]);
    y = (int)floor(rect->el[1]);

    if (roi->lx == LARGEST_INT)
    {
	roi->lx = roi->ux = x;
	roi->ly = roi->uy = y;
	return;
    }
    if (x < roi->lx)
	roi->lx = x;
    if (y < roi->ly)
	roi->ly = y;
    if (x > roi->ux)
	roi->ux = x;
    if (y > roi->uy)
	roi->uy = y;
}

static Imregion *er_rect_bounding_region(Imrect * er)
{
    Imregion *roi;

    if (er == NULL || er->vtype != ptr_v)
	return (NULL);

    roi = roi_alloc(LARGEST_INT, LARGEST_INT, LARGEST_INT, LARGEST_INT);
    er_apply_to_all_edges(er, (void (*) ()) inc_region, (void *) roi);
    if (roi->lx == LARGEST_INT)
    {
	rfree((void *) roi);
	return (NULL);
    }
    roi->ux += 1;
    roi->uy += 1;
    return (roi);
}
