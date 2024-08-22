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

double  kalman();

double  line3_transf(State * state, int i0, int i1, int i2, int *pdf)
{
    int     df0, df1, df2;
    Line3  *line0;
    Line3  *line1;
    Transf3 *transf;
    Basis3 *basis0;
    Basis3 *basis1;
    Vector *h;
    Vector *h0;
    Vector *h1;
    Vector *h2;
    double  lscale = state->lscale;
    double  accuracy = state->accuracy;
    double  z, eps, res, dres;
    double  exx, exy, eyx, eyy, ezz, dpz;
    Vec3    p = {Vec3_id};
    Vec3    dp = {Vec3_id};
    Vec3    c = {Vec3_id};
    Vec3    ex = {Vec3_id};
    Vec3    ey = {Vec3_id};
    Vec3    ez = {Vec3_id};
    Vec3    rex = {Vec3_id};
    Vec3    rey = {Vec3_id};
    Vec3    rez = {Vec3_id};
    Vec3    t = {Vec3_id};
    Mat3    R = {Mat3_id};

    line0 = (Line3 *) vector_getp(state->geom, i0);
    line1 = (Line3 *) vector_getp(state->geom, i1);
    transf = (Transf3 *) vector_getp(state->geom, i2);
    basis0 = (Basis3 *) vector_getp(state->basis, i0);
    basis1 = (Basis3 *) vector_getp(state->basis, i1);
    df0 = geom_df(LINE3);
    df1 = geom_df(LINE3);
    df2 = geom_df(TRANSF3);

    h = vector_alloc(state->maxindex, ptr_v);
    h0 = vector_alloc(df0, double_v);
    vector_putp((void *) h0, h, i0);
    h1 = vector_alloc(df1, double_v);
    vector_putp((void *) h1, h, i1);
    h2 = vector_alloc(df2, double_v);
    vector_putp((void *) h2, h, i2);

    R = transf->T.R;
    t = transf->T.t;
    p = vec3_sum(t, mat3_vprod(R, line1->p));
    ex = mat3_vprod(R, basis1->ex);
    ey = mat3_vprod(R, basis1->ey);
    ez = mat3_vprod(R, basis1->ez);
    rex = vec3_ex();
    rey = vec3_ey();
    rez = vec3_ez();
    exx = vec3_dot(basis0->ex, ex);
    exy = vec3_dot(basis0->ex, ey);
    eyx = vec3_dot(basis0->ey, ex);
    eyy = vec3_dot(basis0->ey, ey);
    ezz = vec3_dot(basis0->ez, ez);
    dp = vec3_diff(line0->p, p);
    dpz = vec3_dot(dp, basis0->ez);

    eps = accuracy * lscale;

    z = vec3_dot(dp, basis0->ex);
    c = vec3_cross(p, basis0->ex);

    vector_putf(1.0, h0, 0);
    vector_putf(0.0, h0, 1);
    vector_putf(-dpz, h0, 2);
    vector_putf(0.0, h0, 3);

    vector_putf(-exx, h1, 0);
    vector_putf(-exy, h1, 1);
    vector_putf(0.0, h1, 2);
    vector_putf(0.0, h1, 3);

    vector_putf(-vec3_dot(rex, c), h2, 0);
    vector_putf(-vec3_dot(rey, c), h2, 1);
    vector_putf(-vec3_dot(rez, c), h2, 2);
    vector_putf(-vec3_dot(rex, basis0->ex), h2, 3);
    vector_putf(-vec3_dot(rey, basis0->ex), h2, 4);
    vector_putf(-vec3_dot(rez, basis0->ex), h2, 5);

    dres = kalman(state, z, h, eps, pdf);
    if (dres == 1e10)
	return (1e10);
    res = dres;

    z = vec3_dot(dp, basis0->ey);
    c = vec3_cross(p, basis0->ey);

    vector_putf(0.0, h0, 0);
    vector_putf(1.0, h0, 1);
    vector_putf(0.0, h0, 2);
    vector_putf(-dpz, h0, 3);

    vector_putf(-eyx, h1, 0);
    vector_putf(-eyy, h1, 1);
    vector_putf(0.0, h1, 2);
    vector_putf(0.0, h1, 3);

    vector_putf(-vec3_dot(rex, c), h2, 0);
    vector_putf(-vec3_dot(rey, c), h2, 1);
    vector_putf(-vec3_dot(rez, c), h2, 2);
    vector_putf(-vec3_dot(rex, basis0->ey), h2, 3);
    vector_putf(-vec3_dot(rey, basis0->ey), h2, 4);
    vector_putf(-vec3_dot(rez, basis0->ey), h2, 5);

    dres = kalman(state, z, h, eps, pdf);
    if (dres == 1e10)
	return (1e10);
    res += dres;

    eps = accuracy;

    z = -vec3_dot(ez, basis0->ex);
    c = vec3_cross(ez, basis0->ex);

    vector_putf(0.0, h0, 0);
    vector_putf(0.0, h0, 1);
    vector_putf(ezz, h0, 2);
    vector_putf(0.0, h0, 3);

    vector_putf(0.0, h1, 0);
    vector_putf(0.0, h1, 1);
    vector_putf(-exx, h1, 2);
    vector_putf(-exy, h1, 3);

    vector_putf(-vec3_dot(rex, c), h2, 0);
    vector_putf(-vec3_dot(rey, c), h2, 1);
    vector_putf(-vec3_dot(rez, c), h2, 2);
    vector_putf(0.0, h2, 3);
    vector_putf(0.0, h2, 4);
    vector_putf(0.0, h2, 5);

    dres = kalman(state, z, h, eps, pdf);
    if (dres == 1e10)
	return (1e10);
    res += dres;

    z = -vec3_dot(ez, basis0->ey);
    c = vec3_cross(ez, basis0->ey);

    vector_putf(0.0, h0, 0);
    vector_putf(0.0, h0, 1);
    vector_putf(0.0, h0, 2);
    vector_putf(ezz, h0, 3);

    vector_putf(0.0, h1, 0);
    vector_putf(0.0, h1, 1);
    vector_putf(-eyx, h1, 2);
    vector_putf(-eyy, h1, 3);

    vector_putf(-vec3_dot(rex, c), h2, 0);
    vector_putf(-vec3_dot(rey, c), h2, 1);
    vector_putf(-vec3_dot(rez, c), h2, 2);
    vector_putf(0.0, h2, 3);
    vector_putf(0.0, h2, 4);
    vector_putf(0.0, h2, 5);

    dres = kalman(state, z, h, eps, pdf);
    if (dres == 1e10)
	return (1e10);
    res += dres;

    vector_free(h0);
    vector_free(h1);
    vector_free(h2);
    vector_free(h);

    return (res);
}

double  state_transf(State * state, int i0, int i1, int i2)
{
    int     df;
    int     type0, type1, type2;
    double  res;

    if ((i0 < 0 || i0 > state->maxindex) ||
	(i1 < 0 || i1 > state->maxindex) ||
	(i2 < 0 || i2 > state->maxindex))
    {
	error("state_transf: bad index", non_fatal);
	return (-1.0);
    }
    type0 = vector_get(state->type, i0);
    type1 = vector_get(state->type, i1);
    type2 = vector_get(state->type, i2);
    if (type2 != TRANSF3)
	error("state_transf: bad type", non_fatal);

    (void) geom_reorder(&i0, &i1, &type0, &type1);
    switch (OPAIR(type0, type1))
    {
    case OPAIR(LINE3, LINE3):
	df = 4;
	res = line3_transf(state, i0, i1, i2, &df);
	break;
    default:
	error("state_transf: bad type", non_fatal);
	return (-1.0);
    }
    return (chisq(res, df));
}
