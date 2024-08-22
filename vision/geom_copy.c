/**@(#)
**/
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

void   *geom_copy(void *geom, int type)
{
    switch (type)
    {
	case SCALAR:
	return ((void *) scalar_copy((Scalar *) geom));
    case POINT2:
	return ((void *) point2_copy((Point2 *) geom));
    case LINE2:
	return ((void *) line2_copy((Line2 *) geom));
    case CONIC2:
	return ((void *) conic_copy((Conic *) geom));
    case POINT3:
	return ((void *) point3_copy((Point3 *) geom));
    case LINE3:
	return ((void *) line3_copy((Line3 *) geom));
    case CONIC3:
	return ((void *) conic3_copy((Conic3 *) geom));
    case PLANE:
	return ((void *) plane_copy((Plane *) geom));
    case TRANSF3:
	return ((void *) transf3_copy((Transf3 *) geom));
    }
    return (NULL);
}

void   *geom_update_copy(void *geom, int *type)
{
    switch (*type)
    {
	case SCALAR:
	return ((void *) scalar_copy((Scalar *) geom));
    case POINT2:
	return ((void *) point2_copy((Point2 *) geom));
    case LINE2:
	return ((void *) line2_copy((Line2 *) geom));
    case CONIC2:
	return ((void *) conic_copy((Conic *) geom));
    case POINT3:
	return ((void *) point3_copy((Point3 *) geom));
    case LINE3:
	return ((void *) line3_copy((Line3 *) geom));
    case CONIC3:
	return ((void *) conic3_copy((Conic3 *) geom));
    case PLANE:
	return ((void *) plane_copy((Plane *) geom));
    case TRANSF3:
	return ((void *) transf3_copy((Transf3 *) geom));
    }
    return (NULL);
}
