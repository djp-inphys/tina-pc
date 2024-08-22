/**@(#)
**/
#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/sysfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

void    state_hull(State * state, Vec3 * centre, float *radius)
{
    Vec3    vmin = {Vec3_id};
    Vec3    vmax = {Vec3_id};
    int     i;
    int    *type = state->type->data;
    void  **geom = state->geom->data;

    vmin = vec3(1e10, 1e10, 1e10);
    vmax = vec3(-1e10, -1e10, -1e10);

    for (i = 0; i < state->maxindex; i++)
    {
	switch (type[i])
	{
	case POINT3:
	    {
		Point3 *point = (Point3 *) geom[i];

		vec3_extend_hull(&vmin, &vmax, point->p);
	    }
	    break;
	case LINE3:
	    {
		Line3  *line = (Line3 *) geom[i];

		vec3_extend_hull(&vmin, &vmax, line->p1);
		vec3_extend_hull(&vmin, &vmax, line->p2);
	    }
	    break;
	case PLANE:
	    {
		Plane  *plane = (Plane *) geom[i];

		vec3_extend_hull(&vmin, &vmax, plane->p);
	    }
	    break;
	}
    }
    *centre = vec3_times(0.5, vec3_sum(vmin, vmax));
    *radius = (float)(0.45 * vec3_dist(vmin, vmax));
}
