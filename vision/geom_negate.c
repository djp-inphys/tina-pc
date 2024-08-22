/**@(#)
**/
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/* inplace negation of geometrical primitive
 * 
 * maintains same physical location only directional properties are
 * updated */

void    geom_negate(void *geom, int type)
{
    switch (type)
    {
	case SCALAR:
	break;
    case POINT2:
	break;
    case LINE2:
	line2_negate((Line2 *) geom);
	break;
    case CONIC2:
	break;
    case POINT3:
	break;
    case LINE3:
	line3_negate((Line3 *) geom);
	break;
    case CONIC3:
	conic3_negate((Conic3 *) geom);
	break;
    case PLANE:
	break;
    case TRANSF3:
	break;
    }
}

void   *geom_negative(void *geom, int type)
{
    switch (type)
    {
	case LINE2:
	return (line2_negative((Line2 *) geom));
    case CONIC2:
	return (NULL);
    case LINE3:
	return (line3_negative((Line3 *) geom));
    case CONIC3:
	return (conic3_negative((Conic3 *) geom));
    case PLANE:
	return (NULL);
    case TRANSF3:
	return (NULL);
    }
    return (NULL);
}
