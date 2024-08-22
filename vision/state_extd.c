/**@(#)
**/
#include <math.h>
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/**
GS_END1   : make end1 p
GS_END2   : make end2 p
GS_ENDANY : make nearest end p
GS_ENDOUT : make nearest end p if p is beyond end
GS_ENDNEAR: make nearest end p if p near enough
**/

int     extend_line_to_point(Vec3 * e1, Vec3 * e2, int dirn, Vec3 p)
{
    Vec3    v = {Vec3_id};

    v = vec3_unit(vec3_diff(*e2, *e1));
    switch (dirn)
    {
    case GS_END1:
	*e1 = vec3_proj_on_line(p, *e1, v);
	return (GS_END1);
	break;
    case GS_END2:
	*e2 = vec3_proj_on_line(p, *e2, v);
	return (GS_END1);
	break;
    case GS_ENDANY:
	{
	    double  t, t1, t2;

	    t1 = vec3_dot(v, *e1);
	    t2 = vec3_dot(v, *e2);
	    t = (vec3_dot(v, p) - t1) / (t2 - t1);
	    if (t < 0.5)
	    {
		*e1 = vec3_proj_on_line(p, *e1, v);
		return (GS_END1);
	    } else
	    {
		*e2 = vec3_proj_on_line(p, *e2, v);
		return (GS_END2);
	    }
	    break;
	}
    case GS_ENDOUT:
	{
	    double  t, t1, t2;

	    t1 = vec3_dot(v, *e1);
	    t2 = vec3_dot(v, *e2);
	    t = (vec3_dot(v, p) - t1) / (t2 - t1);
	    if (t < 0.0)
	    {
		*e1 = vec3_proj_on_line(p, *e1, v);
		return (GS_END1);
	    } else if (t > 1.0)
	    {
		*e2 = vec3_proj_on_line(p, *e2, v);
		return (GS_END2);
	    }
	    break;
	}
    case GS_ENDNEAR:
	{
	    double  t, t1, t2;

	    t1 = vec3_dot(v, *e1);
	    t2 = vec3_dot(v, *e2);
	    t = (vec3_dot(v, p) - t1) / (t2 - t1);
	    if (t < 0.2)
	    {
		*e1 = vec3_proj_on_line(p, *e1, v);
		return (GS_END1);
	    } else if (t > 0.8)
	    {
		*e2 = vec3_proj_on_line(p, *e2, v);
		return (GS_END2);
	    }
	    break;
	}
    }
    error("extend_line_to_point: no such extension type", non_fatal);
    return (0);
}

int     extend_line_to_line(Vec3 * e1, Vec3 * e2, int dirn, Vec3 p, Vec3 v)
{
    /* BUGFIX l unused */
    /* Vec3    u; u = vec3_unit(vec3_diff(*e2, *e1)); Vec3    l; l =
     * vec3_closest_lines(*e1, u, p, v); */
    return (extend_line_to_point(e1, e2, dirn, p));
}

int     extend_line_to_plane(Vec3 * e1, Vec3 * e2, int dirn, Vec3 p, Vec3 n)
{
    Vec3    u = {Vec3_id};

    u = vec3_diff(*e2, *e1);
    p = vec3_inter_line_plane(*e1, u, p, n);
    return (extend_line_to_point(e1, e2, dirn, p));
}

void    state_extend(State * state, int i0, int i1, int dirn)
{
    int     type0, type1;

    if (state_badpair(state, i0, i1))
	return;

    type0 = vector_get(state->type, i0);
    type1 = vector_get(state->type, i1);
    (void) geom_reorder(&i0, &i1, &type0, &type1);

    switch (OPAIR(type0, type1))
    {
    case OPAIR(POINT3, LINE3):
	{
	    Point3 *point = (Point3 *) vector_getp(state->geom, i0);
	    Line3  *line = (Line3 *) vector_getp(state->geom, i1);

	    (void) extend_line_to_point(&line->p1, &line->p2, dirn, point->p);
	    break;
	}
    case OPAIR(LINE3, LINE3):
	{
	    /** on pick list in wrong order **/
	    Line3  *line0 = (Line3 *) vector_getp(state->geom, i1);
	    Line3  *line1 = (Line3 *) vector_getp(state->geom, i0);

	    (void) extend_line_to_line(&line0->p1, &line0->p2, dirn,
				       line1->p, line1->v);
	    break;
	}
    case OPAIR(LINE3, PLANE):
	{
	    Line3  *line = (Line3 *) vector_getp(state->geom, i0);
	    Plane  *plane = (Plane *) vector_getp(state->geom, i1);

	    (void) extend_line_to_plane(&line->p1, &line->p2, dirn,
					plane->p, plane->n);
	    break;
	}
    }
}
