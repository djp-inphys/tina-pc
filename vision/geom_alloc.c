/**@(#)
**/
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

void   *geom_alloc(unsigned int type, unsigned int internal_type)
{
    switch (type)
    {
	case SCALAR:
	return ((void *) scalar_alloc(internal_type));
    case POINT2:
	return ((void *) point2_alloc(internal_type));
    case LINE2:
	return ((void *) line2_alloc(internal_type));
    case CONIC2:
	return ((void *) conic_alloc(internal_type));
    case POINT3:
	return ((void *) point3_alloc(internal_type));
    case LINE3:
	return ((void *) line3_alloc(internal_type));
    case CONIC3:
	return ((void *) conic3_alloc(internal_type));
    case PLANE:
	return ((void *) plane_alloc(internal_type));
    case TRANSF3:
	return ((void *) transf3_alloc(internal_type));
    }
    return (NULL);
}
