/**@(#)
**/
/* transplane.c
 * 
 */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

void    plane_transform(Plane * plane, Transform3 trans)
{
    if (plane == NULL)
	return;

    plane->p = trans3_pos(trans, plane->p);
    plane->n = trans3_vec(trans, plane->n);
}

Bool    plane_coincident(Plane * p1, Plane * p2, double dotthres, double poserror)
{
    double  dn;

    if (p1 == NULL || p2 == NULL)
	return (false);

    if (vec3_dot(p1->n, p2->n) < dotthres)
	return (false);

    dn = vec3_dot(p1->n, vec3_diff(p1->p, p2->p));
    if (fabs(dn) > poserror)
	return (false);

    return (true);
}
