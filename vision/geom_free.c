/**@(#)
**/
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

void    geom_free(void *geom, int type)
{
    switch (type)
    {
	case SCALAR:
	scalar_free((Scalar *) geom);
	break;
    case POINT2:
	point2_free((Point2 *) geom);
	break;
    case LINE2:
	line2_free((Line2 *) geom);
	break;
    case CONIC2:
	conic_free((Conic *) geom);
	break;
    case POINT3:
	point3_free((Point3 *) geom);
	break;
    case LINE3:
	line3_free((Line3 *) geom);
	break;
    case CONIC3:
	conic3_free((Conic3 *) geom);
	break;
    case PLANE:
	plane_free((Plane *) geom);
	break;
    case TRANSF3:
	transf3_free((Transf3 *) geom);
	break;
    }
}
