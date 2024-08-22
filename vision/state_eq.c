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

double  point3_equal(State * state, int i0, int i1, int *pdf)
{
    int     df0, df1;
    Point3 *point0;
    Point3 *point1;
    Basis3 *basis0;
    Basis3 *basis1;
    Vec3    dp = {Vec3_id};
    Vector *h;
    Vector *h0;
    Vector *h1;
    double  lscale = state->lscale;
    double  accuracy = state->accuracy;
    double  z, eps, res, dres;

    point0 = (Point3 *) vector_getp(state->geom, i0);
    point1 = (Point3 *) vector_getp(state->geom, i1);
    basis0 = (Basis3 *) vector_getp(state->basis, i0);
    basis1 = (Basis3 *) vector_getp(state->basis, i1);
    df0 = geom_df(POINT3);
    df1 = geom_df(POINT3);

    dp = vec3_diff(point0->p, point1->p);
    eps = accuracy * lscale;

    h = vector_alloc(state->maxindex, ptr_v);
    h0 = vector_alloc(df0, double_v);
    vector_putp((void *) h0, h, i0);
    h1 = vector_alloc(df1, double_v);
    vector_putp((void *) h1, h, i1);

    z = vec3_dot(dp, basis1->ex);

    vector_putf(vec3_dot(basis0->ex, basis1->ex), h0, 0);
    vector_putf(vec3_dot(basis0->ey, basis1->ex), h0, 1);
    vector_putf(vec3_dot(basis0->ez, basis1->ex), h0, 2);

    vector_putf(-1.0, h1, 0);
    vector_putf(0.0, h1, 1);
    vector_putf(0.0, h1, 2);

    dres = kalman(state, z, h, eps, pdf);
    if (dres == 1e10)
	return (1e10);
    res = dres;

    z = vec3_dot(dp, basis1->ey);

    vector_putf(vec3_dot(basis0->ex, basis1->ey), h0, 0);
    vector_putf(vec3_dot(basis0->ey, basis1->ey), h0, 1);
    vector_putf(vec3_dot(basis0->ez, basis1->ey), h0, 2);

    vector_putf(0.0, h1, 0);
    vector_putf(-1.0, h1, 1);
    vector_putf(0.0, h1, 2);

    dres = kalman(state, z, h, eps, pdf);
    if (dres == 1e10)
	return (1e10);
    res += dres;

    z = vec3_dot(dp, basis1->ez);

    vector_putf(vec3_dot(basis0->ex, basis1->ez), h0, 0);
    vector_putf(vec3_dot(basis0->ey, basis1->ez), h0, 1);
    vector_putf(vec3_dot(basis0->ez, basis1->ez), h0, 2);

    vector_putf(0.0, h1, 0);
    vector_putf(0.0, h1, 1);
    vector_putf(-1.0, h1, 2);

    dres = kalman(state, z, h, eps, pdf);
    if (dres == 1e10)
	return (1e10);
    res += dres;

    vector_free(h0);
    vector_free(h1);
    vector_free(h);

    return (res);
}

double  line3_equal(State * state, int i0, int i1, int *pdf)
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
    double  z, eps, res, dres;
    double  exx, exy, eyx, eyy, ezz, dpz;

    line0 = (Line3 *) vector_getp(state->geom, i0);
    line1 = (Line3 *) vector_getp(state->geom, i1);
    basis0 = (Basis3 *) vector_getp(state->basis, i0);
    basis1 = (Basis3 *) vector_getp(state->basis, i1);
    df0 = geom_df(LINE3);
    df1 = geom_df(LINE3);

    h = vector_alloc(state->maxindex, ptr_v);
    h0 = vector_alloc(df0, double_v);
    vector_putp((void *) h0, h, i0);
    h1 = vector_alloc(df1, double_v);
    vector_putp((void *) h1, h, i1);


    exx = vec3_dot(basis0->ex, basis1->ex);
    exy = vec3_dot(basis0->ex, basis1->ey);
    eyx = vec3_dot(basis0->ey, basis1->ex);
    eyy = vec3_dot(basis0->ey, basis1->ey);
    ezz = vec3_dot(basis0->ez, basis1->ez);
    dp = vec3_diff(line0->p, line1->p);
    dpz = vec3_dot(dp, basis0->ez);

    eps = accuracy * lscale;
    z = vec3_dot(dp, basis0->ex);

    vector_putf(1.0, h0, 0);
    vector_putf(0.0, h0, 1);
    vector_putf(-dpz, h0, 2);
    vector_putf(0.0, h0, 3);

    vector_putf(-exx, h1, 0);
    vector_putf(-exy, h1, 1);
    vector_putf(0.0, h1, 2);
    vector_putf(0.0, h1, 3);

    dres = kalman(state, z, h, eps, pdf);
    if (dres == 1e10)
	return (1e10);
    res = dres;

    z = vec3_dot(dp, basis0->ey);

    vector_putf(0.0, h0, 0);
    vector_putf(1.0, h0, 1);
    vector_putf(0.0, h0, 2);
    vector_putf(-dpz, h0, 3);

    vector_putf(-eyx, h1, 0);
    vector_putf(-eyy, h1, 1);
    vector_putf(0.0, h1, 2);
    vector_putf(0.0, h1, 3);

    dres = kalman(state, z, h, eps, pdf);
    if (dres == 1e10)
	return (1e10);
    res += dres;

    eps = accuracy;
    z = -vec3_dot(basis0->ex, basis1->ez);

    vector_putf(0.0, h0, 0);
    vector_putf(0.0, h0, 1);
    vector_putf(ezz, h0, 2);
    vector_putf(0.0, h0, 3);

    vector_putf(0.0, h1, 0);
    vector_putf(0.0, h1, 1);
    vector_putf(-exx, h1, 2);
    vector_putf(-exy, h1, 3);

    dres = kalman(state, z, h, eps, pdf);
    if (dres == 1e10)
	return (1e10);
    res += dres;


    z = -vec3_dot(basis0->ey, basis1->ez);

    vector_putf(0.0, h0, 0);
    vector_putf(0.0, h0, 1);
    vector_putf(0.0, h0, 2);
    vector_putf(ezz, h0, 3);

    vector_putf(0.0, h1, 0);
    vector_putf(0.0, h1, 1);
    vector_putf(-eyx, h1, 2);
    vector_putf(eyy, h1, 3);

    dres = kalman(state, z, h, eps, pdf);
    if (dres == 1e10)
	return (1e10);
    res += dres;

    vector_free(h0);
    vector_free(h1);
    vector_free(h);

    return (res);
}

double  plane_equal(State * state, int i0, int i1, int *pdf)
{
    int     df0, df1;
    Plane  *plane0;
    Plane  *plane1;
    Basis3 *basis0;
    Basis3 *basis1;
    Vec3    dp = {Vec3_id};
    Vector *h;
    Vector *h0;
    Vector *h1;
    double  lscale = state->lscale;
    double  accuracy = state->accuracy;
    double  z, eps, res, dres;

    plane0 = (Plane *) vector_getp(state->geom, i0);
    plane1 = (Plane *) vector_getp(state->geom, i1);
    basis0 = (Basis3 *) vector_getp(state->basis, i0);
    basis1 = (Basis3 *) vector_getp(state->basis, i1);
    df0 = geom_df(PLANE);
    df1 = geom_df(PLANE);

    h = vector_alloc(state->maxindex, ptr_v);
    h0 = vector_alloc(df0, double_v);
    vector_putp((void *) h0, h, i0);
    h1 = vector_alloc(df1, double_v);
    vector_putp((void *) h1, h, i1);


    dp = vec3_diff(plane0->p, plane1->p);

    eps = accuracy * lscale;
    z = vec3_dot(dp, basis0->ex);

    vector_putf(1.0, h0, 0);
    vector_putf(vec3_dot(dp, basis0->ex), h0, 1);
    vector_putf(vec3_dot(dp, basis0->ey), h0, 2);

    vector_putf(-vec3_dot(basis0->ez, basis1->ez), h1, 0);
    vector_putf(0.0, h1, 1);
    vector_putf(0.0, h1, 2);

    dres = kalman(state, z, h, eps, pdf);
    if (dres == 1e10)
	return (1e10);
    res = dres;

    eps = accuracy;
    dp = vec3_diff(basis0->ez, basis1->ez);

    z = vec3_dot(dp, basis0->ex);

    vector_putf(0.0, h0, 0);
    vector_putf(1.0, h0, 1);
    vector_putf(0.0, h0, 2);

    vector_putf(0.0, h1, 0);
    vector_putf(-vec3_dot(basis0->ex, basis1->ex), h1, 1);
    vector_putf(-vec3_dot(basis0->ex, basis1->ey), h1, 2);

    dres = kalman(state, z, h, eps, pdf);
    if (dres == 1e10)
	return (1e10);
    res += dres;

    z = vec3_dot(dp, basis0->ey);

    vector_putf(0.0, h0, 0);
    vector_putf(0.0, h0, 1);
    vector_putf(1.0, h0, 2);

    vector_putf(0.0, h1, 0);
    vector_putf(-vec3_dot(basis0->ey, basis1->ex), h1, 1);
    vector_putf(-vec3_dot(basis0->ey, basis1->ey), h1, 2);

    dres = kalman(state, z, h, eps, pdf);
    if (dres == 1e10)
	return (1e10);
    res += dres;

    vector_free(h0);
    vector_free(h1);
    vector_free(h);

    return (res);
}

double  state_equal(State * state, int i0, int i1)
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
    case OPAIR(POINT3, POINT3):
	df = 3;
	res = point3_equal(state, i0, i1, &df);
	break;
    case OPAIR(LINE3, LINE3):
	df = 4;
	res = line3_equal(state, i0, i1, &df);
	break;
    case OPAIR(PLANE, PLANE):
	df = 3;
	res = plane_equal(state, i0, i1, &df);
	break;
    default:
	return (-1.0);
    }
    return (chisq(res, df));
}
