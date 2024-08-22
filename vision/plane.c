/**@(#)
**/
/* plane.c functions for manipulating 3D planes
 * 
 * typedef struct plane { int type; struct vec3 p; struct vec3 n; struct
 * list *props; } Plane;
 * 
 */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>
#ifdef _PCC
#include <memory.h>
#endif

Plane  *plane_alloc(unsigned int type)
{
    Plane  *plane = ts_ralloc(Plane);

    plane->type = type;
    plane->label = new_label();
    plane->p = vec3_zero();
    plane->n = vec3_ez();
    plane->props = NULL;
    return (plane);
}

Plane  *plane_make(Vec3 p, Vec3 n, int type)
{
    Plane  *plane = ts_ralloc(Plane);

    plane->type = type;
    plane->label = new_label();
    plane->p = p;
    plane->n = vec3_unit(n);
    plane->props = NULL;
    return (plane);
}

void    plane_free(Plane * plane)
{
    if (plane == NULL)
	return;
    proplist_freelist(plane->props);
    rfree((void *) plane);
}

Plane  *plane_copy(Plane * plane)
{
    Plane  *copy;
    List   *proplist_copy();

    if (plane == NULL)
	return (NULL);

    copy = ts_ralloc(Plane);
    (void) memcpy((char *) copy, (char *) plane, sizeof(Plane));
    copy->props = proplist_copy(plane->props);
    return (copy);
}

int     plane_number(List * planes)
{
    List   *lptr;
    int     n = 0;

    for (lptr = planes; lptr != NULL; lptr = lptr->next)
	((Plane *) (lptr->to))->label = n++;
    return(n);
}

Bool    plane_point_on_plane(Plane * plane, Vec3 p, double thres)
{
    Vec3    dp = {Vec3_id};
    double  dn;

    dp = vec3_diff(p, plane->p);
    dn = vec3_dot(dp, plane->n);
    return ((fabs(dn) < thres) ? true : false);
}
