/**@(#)
**/
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

static void inc_region(void *ptr, int type, Imregion * roi)
{
    int     x, y;
    Vec2    p = {Vec2_id};

    GET_POS2(ptr, type, p);
    x = (int)floor(vec2_x(p));
    y = (int)floor(vec2_y(p));

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

/* ARGSUSED quieten lint */
static void es_region(Tstring * str, int type, Imregion * roi)
{
    str_apply_func(str, inc_region, (void *) roi);
}

Imregion *es_bounding_region(Tstring * es)
{
    Imregion *roi;

    roi = roi_alloc(LARGEST_INT, LARGEST_INT, LARGEST_INT, LARGEST_INT);
    str_apply_func(es, inc_region, (void *) roi);
    if (roi->lx == LARGEST_INT)
    {
	rfree((void *) roi);
	return (NULL);
    }
    roi->ux += 1;
    roi->uy += 1;
    return (roi);
}

Imregion *strings_bounding_region(List * strings)
{
    Imregion *roi;

    roi = roi_alloc(LARGEST_INT, LARGEST_INT, LARGEST_INT, LARGEST_INT);
    list_apply_func(strings, es_region, (void *) roi);
    if (roi->lx == LARGEST_INT)
    {
	rfree((void *) roi);
	return (NULL);
    }
    roi->ux += 1;
    roi->uy += 1;
    return (roi);
}

Imregion *er_bounding_region(Imrect * er)
{
    Imregion *roi;

    if (er == NULL || er->vtype != ptr_v)
	return (NULL);

    roi = roi_alloc(LARGEST_INT, LARGEST_INT, LARGEST_INT, LARGEST_INT);
    er_apply_to_all_strings(er, es_region, (void *) roi);
    if (roi->lx == LARGEST_INT)
    {
	rfree((void *) roi);
	return (NULL);
    }
    roi->ux += 1;
    roi->uy += 1;
    return (roi);
}
