/**@(#)
**/
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

void   *geom3_from_geom2(void *geom, int *type, double *thres)
{
    switch (*type)
    {
	case LINE2:
	*type = LINE3;
	return ((void *) line3_from_line2((Line2 *) geom));
    case CONIC2:
	*type = CONIC3;
	return ((void *) conic3_from_conic2((Conic *) geom, *thres));
    }
    return (NULL);
}
