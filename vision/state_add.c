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

int     state_add_intersect(State * state, int i0, int i1)
{
    int     inew;
    int     type0, type1;

    if (state_badpair(state, i0, i1))
	return (-1);

    type0 = vector_get(state->type, i0);
    type1 = vector_get(state->type, i1);
    (void) geom_reorder(&i0, &i1, &type0, &type1);

    switch (OPAIR(type0, type1))
    {
    case OPAIR(LINE3, LINE3):
	{
	    Line3  *line0 = (Line3 *) vector_getp(state->geom, i0);
	    Line3  *line1 = (Line3 *) vector_getp(state->geom, i1);
	    Point3 *point;
	    Vec3    p = {Vec3_id};

	    p = vec3_inter_lines(line0->p, line0->v, line1->p, line1->v);
	    point = point3_make(p, (int) NULL);
	    inew = state_add(state, (void *) point, POINT3);
	    state_set_infcov(state, inew);
	    break;
	}
    case OPAIR(LINE3, PLANE):
	{
	    Line3  *line = (Line3 *) vector_getp(state->geom, i0);
	    Plane  *plane = (Plane *) vector_getp(state->geom, i1);
	    Point3 *point;
	    Vec3    p = {Vec3_id};

	    p = vec3_inter_line_plane(line->p, line->v, plane->p, plane->n);
	    point = point3_make(p, (int) NULL);
	    inew = state_add(state, (void *) point, POINT3);
	    state_set_infcov(state, inew);
	    break;
	}
    case OPAIR(PLANE, PLANE):
	{
	    Plane  *plane0 = (Plane *) vector_getp(state->geom, i0);
	    Plane  *plane1 = (Plane *) vector_getp(state->geom, i1);
	    Line3  *line;
	    Vec3    l = {Vec3_id};
	    Vec3    v = {Vec3_id};
	    Vec3    p1 = {Vec3_id};
	    Vec3    p2 = {Vec3_id};

	    vec3_inter_planes(plane0->p, plane0->n, plane1->p, plane1->n, &l, &v);
	    p1 = vec3_diff(l, vec3_times(state->lscale / 16.0, v));
	    p2 = vec3_sum(l, vec3_times(state->lscale / 16.0, v));
	    line = line3_make(p1, p2, (int) NULL);
	    inew = state_add(state, (void *) line, LINE3);
	    state_set_infcov(state, inew);
	    break;
	}
    default:
	inew = -1;
    }
    return (inew);
}

int     state_add_join(State * state, int i0, int i1)
{
    int     inew;
    int     type0, type1;

    if (state_badpair(state, i0, i1))
	return (-1);

    type0 = vector_get(state->type, i0);
    type1 = vector_get(state->type, i1);
    (void) geom_reorder(&i0, &i1, &type0, &type1);

    switch (OPAIR(type0, type1))
    {
    case OPAIR(POINT3, POINT3):
	{
	    Point3 *point0 = (Point3 *) vector_getp(state->geom, i0);
	    Point3 *point1 = (Point3 *) vector_getp(state->geom, i1);
	    Line3  *line;

	    line = line3_make(point0->p, point1->p, (int) NULL);
	    inew = state_add(state, (void *) line, LINE3);
	    state_set_infcov(state, inew);
	    break;
	}
    case OPAIR(POINT3, LINE3):
	{
	    Point3 *point = (Point3 *) vector_getp(state->geom, i0);
	    Line3  *line = (Line3 *) vector_getp(state->geom, i1);
	    Plane  *plane;
	    Vec3    p = {Vec3_id};
	    Vec3    n = {Vec3_id};

	    vec3_join_point_line(point->p, line->p, line->v, &p, &n);
	    plane = plane_make(p, n, (int) NULL);
	    inew = state_add(state, (void *) plane, PLANE);
	    state_set_infcov(state, inew);
	    break;
	}
    case OPAIR(LINE3, LINE3):
	{
	    Line3  *line0 = (Line3 *) vector_getp(state->geom, i0);
	    Line3  *line1 = (Line3 *) vector_getp(state->geom, i1);
	    Plane  *plane;
	    Vec3    p = {Vec3_id};
	    Vec3    n = {Vec3_id};

	    vec3_join_lines(line0->p, line0->v, line1->p, line1->v, &p, &n);
	    plane = plane_make(p, n, (int) NULL);
	    inew = state_add(state, (void *) plane, PLANE);
	    state_set_infcov(state, inew);
	    break;
	}
    default:
	inew = -1;
    }
    return (inew);
}

int     state_add_join3(State * state, int i0, int i1, int i2)
{
    int     inew;
    int     type0, type1, type2;


    type0 = vector_get(state->type, i0);
    type1 = vector_get(state->type, i1);
    type2 = vector_get(state->type, i2);
    if ((i0 < 0 || i0 >= state->maxindex) ||
	(i1 < 1 || i1 >= state->maxindex) ||
	(i0 < 2 || i2 >= state->maxindex))
    {
	error("state_add_join3: bad index", non_fatal);
	return (-1);
    }
    if (type0 != POINT3 || type1 != POINT3 || type2 != POINT3)
    {
	error("state_add_join3: bad types", non_fatal);
	return (-1);
    }
    {
	Point3 *point0 = (Point3 *) vector_getp(state->geom, i0);
	Point3 *point1 = (Point3 *) vector_getp(state->geom, i1);
	Point3 *point2 = (Point3 *) vector_getp(state->geom, i2);
	Plane  *plane;
	Vec3    p = {Vec3_id};
	Vec3    n = {Vec3_id};

	vec3_join_3_points(point0->p, point1->p, point2->p, &p, &n);
	plane = plane_make(p, n, (int) NULL);
	inew = state_add(state, (void *) plane, PLANE);
	state_set_infcov(state, inew);
    }

    return (inew);
}
