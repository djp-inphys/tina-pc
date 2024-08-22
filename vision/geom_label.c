/**@(#)
**/
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

int     geom_label_get(void *p, int type)
{
    switch (type)
    {
	case SCALAR:
	return (((Scalar *) p)->label);
    case POINT2:
	return (((Point2 *) p)->label);
    case LINE2:
	return (((Line2 *) p)->label);
    case CONIC2:
	return (((Conic *) p)->label);
    case POINT3:
	return (((Point3 *) p)->label);
    case LINE3:
	return (((Line3 *) p)->label);
    case CONIC3:
	{
	    Conic3 *con3 = p;

	    if (con3->conic == NULL)
		return (0);
	    return (con3->conic->label);
	}
    case PLANE:
	return (((Plane *) p)->label);
    case TRANSF3:
	return (((Transf3 *) p)->label);
    }
    return (0);
}

static void geom_set_by_label(void *geom, int type, Pair * label_store)
{
    if (label_store->to2 != NULL)
	return;

    if ((int) (label_store->to1) == geom_label_get(geom, type))
    {
	label_store->to2 = geom;
	label_store->type2 = type;
    }
}

void   *geom_getbylabel(List * geom, int label, int *type)
{
    Pair    label_store = {Pair_id};

    label_store.to1 = (void *) label;
    label_store.type1 = _INT;
    label_store.to2 = NULL;
    label_store.type2 = 0;

    reclist_list_apply(geom, geom_set_by_label, (int) NULL, (void *) &label_store);
    *type = label_store.type2;
    return (label_store.to2);
}
