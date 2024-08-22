/**@(#)
**/
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/* crude use static variables in reclist_list_apply */
static Vec3 vmin = {Vec3_id};
static Vec3 vmax = {Vec3_id};

/* add a single 3D geometrical primitive to the current hull bounds */
static void geom_add_to_hull(void *geom, int type)
{
    switch (type)
    {
	case POINT3:
	vec3_extend_hull(&vmin, &vmax, ((Point3 *) geom)->p);
	break;
    case LINE3:
	vec3_extend_hull(&vmin, &vmax, ((Line3 *) geom)->p1);
	vec3_extend_hull(&vmin, &vmax, ((Line3 *) geom)->p2);
	break;
    case CONIC3:
	{
	    Conic3 *c3 = (Conic3 *) geom;
	    double  t;

	    vec3_extend_hull(&vmin, &vmax, conic3_point(c3, c3->conic->t1));
	    vec3_extend_hull(&vmin, &vmax, conic3_point(c3, c3->conic->t2));
	    t = (c3->conic->t1 + c3->conic->t2) * 0.5;
	    vec3_extend_hull(&vmin, &vmax, conic3_point(c3, t));
	    break;
	}
    case PLANE:
	vec3_extend_hull(&vmin, &vmax, ((Plane *) geom)->p);
	break;
    }
}

/* takes a list (might be recursive) of geometrical primitives and
 * computes an approximate bounding hull, represented as a centre and
 * radius
 * 
 * does not protect against a list with no 3D geometry in it */

void    geom_hull_get(List * geom, Vec3 * centre, double *radius)
{
    /* initialise hull bounds */
    vmin = vec3(1e10, 1e10, 1e10);
    vmax = vec3(-1e10, -1e10, -1e10);

    reclist_list_apply(geom, geom_add_to_hull, (int) NULL, NULL);

    *centre = vec3_times(0.5, vec3_sum(vmin, vmax));
    *radius = 0.45 * vec3_dist(vmin, vmax);
}
