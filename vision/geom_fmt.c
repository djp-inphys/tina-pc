/**@(#)
**/
#include <stdio.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

void    geom_format(void *geom, unsigned int type)
{
    switch (type)
    {
	case POINT2:
	point2_format((Point2 *) geom);
	break;
    case LINE2:
	line2_format((Line2 *) geom);
	break;
    case CONIC2:
	conic_format((Conic *) geom);
	break;
    case POINT3:
	point3_format((Point3 *) geom);
	break;
    case LINE3:
	line3_format((Line3 *) geom);
	break;
    case CONIC3:
	conic3_format((Conic3 *) geom);
	break;
    case PLANE:
	plane_format((Plane *) geom);
	break;
    case TRANSF3:
	/* BUGFIX: was plane_format */
	transf3_format((Transf3 *) geom);
	break;
    }
}
