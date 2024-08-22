/**@(#)
**/
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/* apply given transform to a 3D geometrical primitive
 * 
 * transformation performed inplace */

void    geom_transform(void *geom, int type, Transform3 * trans)
{
    switch (type)
    {
	case POINT3:
	point3_transform((Point3 *) geom, *trans);
	break;
    case LINE3:
	line3_transform((Line3 *) geom, *trans);
	break;
    case CONIC3:
	conic3_transform((Conic3 *) geom, *trans);
	break;
    case PLANE:
	plane_transform((Plane *) geom, *trans);
	break;
    }
}
