/**@(#)
**/
#include <math.h>
#include <stdio.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

double  kalman();

double  point_on_line(State * state, int i0, int i1, int *pdf)
{
    int     df0, df1;
    Point3 *point;
    Line3  *line;
    Basis3 *basis0;
    Basis3 *basis1;
    Vec3    dp = {Vec3_id};
    Vector *h;
    Vector *h0;
    Vector *h1;
    double  lscale = state->lscale;
    double  accuracy = state->accuracy;
    double  z, eps, res, dres;

    point = (Point3 *) vector_getp(state->geom, i0);
    line = (Line3 *) vector_getp(state->geom, i1);
    basis0 = (Basis3 *) vector_getp(state->basis, i0);
    basis1 = (Basis3 *) vector_getp(state->basis, i1);
    df0 = geom_df(POINT3);
    df1 = geom_df(LINE3);

    dp = vec3_diff(point->p, line->p);

    h = vector_alloc(state->maxindex, ptr_v);
    h0 = vector_alloc(df0, double_v);
    vector_putp((void *) h0, h, i0);
    h1 = vector_alloc(df1, double_v);
    vector_putp((void *) h1, h, i1);

    eps = accuracy * lscale;
    z = vec3_dot(basis1->ex, dp);

    vector_putf(vec3_dot(basis0->ex, basis1->ex), h0, 0);
    vector_putf(vec3_dot(basis0->ey, basis1->ex), h0, 1);
    vector_putf(vec3_dot(basis0->ez, basis1->ex), h0, 2);

    vector_putf(-1.0, h1, 0);
    vector_putf(0.0, h1, 1);
    vector_putf(-vec3_dot(dp, basis1->ez), h1, 2);
    vector_putf(0.0, h1, 3);

    dres = kalman(state, z, h, eps, pdf);
    if (dres == 1e10)
	return (1e10);
    res = dres;

    z = vec3_dot(basis1->ey, dp);
    vector_putf(vec3_dot(basis0->ex, basis1->ey), h0, 0);
    vector_putf(vec3_dot(basis0->ey, basis1->ey), h0, 1);
    vector_putf(vec3_dot(basis0->ez, basis1->ey), h0, 2);

    vector_putf(0.0, h1, 0);
    vector_putf(-1.0, h1, 1);
    vector_putf(0.0, h1, 2);
    vector_putf(-vec3_dot(dp, basis1->ez), h1, 3);

    dres = kalman(state, z, h, eps, pdf);
    if (dres == 1e10)
	return (1e10);
    res += dres;

    vector_free(h0);
    vector_free(h1);
    vector_free(h);

    return (res);
}

double  point_on_plane(State * state, int i0, int i1, int *pdf)
{
    int     df0, df1;
    Point3 *point;
    Plane  *plane;
    Basis3 *basis0;
    Basis3 *basis1;
    Vec3    dp = {Vec3_id};
    Vector *h;
    Vector *h0;
    Vector *h1;
    double  lscale = state->lscale;
    double  accuracy = state->accuracy;
    double  z, eps, res, dres;

    point = (Point3 *) vector_getp(state->geom, i0);
    plane = (Plane *) vector_getp(state->geom, i1);
    basis0 = (Basis3 *) vector_getp(state->basis, i0);
    basis1 = (Basis3 *) vector_getp(state->basis, i1);
    df0 = geom_df(POINT3);
    df1 = geom_df(PLANE);

    dp = vec3_diff(point->p, plane->p);

    h = vector_alloc(state->maxindex, ptr_v);
    h0 = vector_alloc(df0, double_v);
    vector_putp((void *) h0, h, i0);
    h1 = vector_alloc(df1, double_v);
    vector_putp((void *) h1, h, i1);

    eps = accuracy * lscale;
    z = vec3_dot(dp, basis1->ez);

    vector_putf(vec3_dot(basis0->ex, basis1->ez), h0, 0);
    vector_putf(vec3_dot(basis0->ey, basis1->ez), h0, 1);
    vector_putf(vec3_dot(basis0->ez, basis1->ez), h0, 2);

    vector_putf(-1.0, h1, 0);
    vector_putf(vec3_dot(dp, basis1->ex), h1, 1);
    vector_putf(vec3_dot(dp, basis1->ey), h1, 2);

    dres = kalman(state, z, h, eps, pdf);
    if (dres == 1e10)
	return (1e10);
    res = dres;

    vector_free(h0);
    vector_free(h1);
    vector_free(h);

    return (res);
}

double  coplanar_2_lines(State * state, int i0, int i1, int *pdf)
{
    int     df0, df1;
    Line3  *line0;
    Line3  *line1;
    Basis3 *basis0;
    Basis3 *basis1;
    Vec3    dp = {Vec3_id};
    Vector *h;
    Vector *h0;
    Vector *h1;
    double  lscale = state->lscale;
    double  accuracy = state->accuracy;
    double  z, eps, res;

    line0 = (Line3 *) vector_getp(state->geom, i0);
    line1 = (Line3 *) vector_getp(state->geom, i1);
    basis0 = (Basis3 *) vector_getp(state->basis, i0);
    basis1 = (Basis3 *) vector_getp(state->basis, i1);
    df0 = geom_df(LINE3);
    df1 = geom_df(LINE3);

    dp = vec3_diff(line0->p, line1->p);

    h = vector_alloc(state->maxindex, ptr_v);
    h0 = vector_alloc(df0, double_v);
    vector_putp((void *) h0, h, i0);
    h1 = vector_alloc(df1, double_v);
    vector_putp((void *) h1, h, i1);

    eps = accuracy * lscale;
    z = vec3_dot(dp, vec3_cross(basis0->ez, basis1->ez));

    vector_putf(-vec3_dot(basis0->ey, basis1->ez), h0, 0);
    vector_putf(vec3_dot(basis0->ex, basis1->ez), h0, 1);
    vector_putf(vec3_dot(dp, vec3_cross(basis0->ex, basis1->ez)), h0, 2);
    vector_putf(vec3_dot(dp, vec3_cross(basis0->ey, basis1->ez)), h0, 3);

    vector_putf(-vec3_dot(basis0->ez, basis1->ey), h1, 0);
    vector_putf(vec3_dot(basis0->ez, basis1->ex), h1, 1);
    vector_putf(vec3_dot(dp, vec3_cross(basis0->ez, basis1->ex)), h1, 2);
    vector_putf(vec3_dot(dp, vec3_cross(basis0->ez, basis1->ey)), h1, 3);

    res = kalman(state, z, h, eps, pdf);
    vector_free(h0);
    vector_free(h1);
    vector_free(h);
    return (res);
}

double  line_on_plane(State * state, int i0, int i1, int *pdf)
{
    int     df0, df1;
    Line3  *line;
    Plane  *plane;
    Basis3 *basis0;
    Basis3 *basis1;
    Vec3    dp = {Vec3_id};
    Vector *h;
    Vector *h0;
    Vector *h1;
    double  lscale = state->lscale;
    double  accuracy = state->accuracy;
    double  z, eps, res, dres;

    line = (Line3 *) vector_getp(state->geom, i0);
    plane = (Plane *) vector_getp(state->geom, i1);
    basis0 = (Basis3 *) vector_getp(state->basis, i0);
    basis1 = (Basis3 *) vector_getp(state->basis, i1);
    df0 = geom_df(LINE3);
    df1 = geom_df(PLANE);

    dp = vec3_diff(line->p, plane->p);

    h = vector_alloc(state->maxindex, ptr_v);
    h0 = vector_alloc(df0, double_v);
    vector_putp((void *) h0, h, i0);
    h1 = vector_alloc(df1, double_v);
    vector_putp((void *) h1, h, i1);

    eps = accuracy * lscale;
    z = vec3_dot(dp, basis1->ez);

    vector_putf(vec3_dot(basis0->ex, basis1->ez), h0, 0);
    vector_putf(vec3_dot(basis0->ey, basis1->ez), h0, 1);
    vector_putf(0.0, h0, 2);
    vector_putf(0.0, h0, 3);

    vector_putf(-1.0, h1, 0);
    vector_putf(vec3_dot(dp, basis1->ex), h1, 1);
    vector_putf(vec3_dot(dp, basis1->ey), h1, 2);

    dres = kalman(state, z, h, eps, pdf);
    if (dres == 1e10)
	return (1e10);
    res = dres;

    eps = accuracy;
    z = vec3_dot(basis0->ez, basis1->ez);

    vector_putf(0.0, h0, 0);
    vector_putf(0.0, h0, 1);
    vector_putf(vec3_dot(basis0->ex, basis1->ez), h0, 2);
    vector_putf(vec3_dot(basis0->ey, basis1->ez), h0, 3);

    vector_putf(0.0, h1, 0);
    vector_putf(vec3_dot(basis0->ez, basis1->ex), h1, 1);
    vector_putf(vec3_dot(basis0->ez, basis1->ey), h1, 2);

    dres = kalman(state, z, h, eps, pdf);
    if (dres == 1e10)
	return (1e10);
    res += dres;

    vector_free(h0);
    vector_free(h1);
    vector_free(h);

    return (res);
}

double  state_on(State * state, int i0, int i1)
{
    int     df;
    int     type0, type1;
    double  res;

    if (state_badpair(state, i0, i1))
	return (-1.0);

    type0 = vector_get(state->type, i0);
    type1 = vector_get(state->type, i1);
    (void) geom_reorder(&i0, &i1, &type0, &type1);

    switch (OPAIR(type0, type1))
    {
    case OPAIR(POINT3, LINE3):
	df = 2;
	res = point_on_line(state, i0, i1, &df);
	break;
    case OPAIR(POINT3, PLANE):
	df = 1;
	res = point_on_plane(state, i0, i1, &df);
	break;
    case OPAIR(LINE3, LINE3):
	df = 1;
	res = coplanar_2_lines(state, i0, i1, &df);
	break;
    case OPAIR(LINE3, PLANE):
	df = 2;
	res = line_on_plane(state, i0, i1, &df);
	break;
    default:
	return (-1.0);
    }
    return (chisq(res, df));
}
