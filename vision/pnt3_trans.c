/**@(#)
**/
/* transpoint.c
 * 
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

void    point3_transform(Point3 * point, Transform3 trans)
{
    if (point == NULL)
	return;

    point->p = trans3_pos(trans, point->p);
}

Bool    point3_coincident(Point3 * p1, Point3 * p2, double poserror)
{
    if (p1 == NULL || p2 == NULL)
	return (false);

    if (vec3_dist(p1->p, p2->p) < poserror)
	return (true);
    else
	return (false);
}

Bool    point3_within_error(Point3 * p1, Point3 * p2)
{
    Iso_error *iso1;
    Iso_error *iso2;

    if (p1 == NULL || p2 == NULL)
	return (false);

    iso1 = (Iso_error *) prop_get(p1->props, ISO_ERROR);
    iso2 = (Iso_error *) prop_get(p2->props, ISO_ERROR);

    if (iso1 == NULL || iso2 == NULL)
	return (false);

    return (point3_coincident(p1, p2, iso1->pos + iso2->pos));
}
