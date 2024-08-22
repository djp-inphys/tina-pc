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

double  orth_lines(State * state, int i0, int i1, int *pdf)
{
    int     df0, df1;
    Basis3 *basis0;
    Basis3 *basis1;
    Vector *h;
    Vector *h0;
    Vector *h1;
    double  accuracy = state->accuracy;
    double  z, eps, res, dres;

    basis0 = (Basis3 *) vector_getp(state->basis, i0);
    basis1 = (Basis3 *) vector_getp(state->basis, i1);
    df0 = geom_df(LINE3);
    df1 = geom_df(LINE3);

    h = vector_alloc(state->maxindex, ptr_v);
    h0 = vector_alloc(df0, double_v);
    vector_putp((void *) h0, h, i0);
    h1 = vector_alloc(df1, double_v);
    vector_putp((void *) h1, h, i1);

    eps = accuracy;
    z = vec3_dot(basis0->ez, basis1->ez);

    vector_putf(0.0, h0, 0);
    vector_putf(0.0, h0, 1);
    vector_putf(vec3_dot(basis0->ex, basis1->ez), h0, 2);
    vector_putf(vec3_dot(basis0->ey, basis1->ez), h0, 3);

    vector_putf(0.0, h1, 0);
    vector_putf(0.0, h1, 1);
    vector_putf(vec3_dot(basis0->ez, basis1->ex), h1, 2);
    vector_putf(vec3_dot(basis0->ez, basis1->ey), h1, 3);

    dres = kalman(state, z, h, eps, pdf);
    if (dres == 1e10)
	return (1e10);
    res = dres;

    vector_free(h0);
    vector_free(h1);
    vector_free(h);

    return (res);
}

double  orth_line_plane(State * state, int i0, int i1, int *pdf)
{
    int     df0, df1;
    Basis3 *basis0;
    Basis3 *basis1;
    Vector *h;
    Vector *h0;
    Vector *h1;
    double  accuracy = state->accuracy;
    double  z, eps, res, dres;
    double  ezz;

    basis0 = (Basis3 *) vector_getp(state->basis, i0);
    basis1 = (Basis3 *) vector_getp(state->basis, i1);
    df0 = geom_df(LINE3);
    df1 = geom_df(PLANE);

    ezz = vec3_dot(basis0->ez, basis1->ez);

    h = vector_alloc(state->maxindex, ptr_v);
    h0 = vector_alloc(df0, double_v);
    vector_putp((void *) h0, h, i0);
    h1 = vector_alloc(df1, double_v);
    vector_putp((void *) h1, h, i1);

    eps = accuracy;
    z = vec3_dot(basis0->ez, basis1->ex);

    vector_putf(0.0, h0, 0);
    vector_putf(0.0, h0, 1);
    vector_putf(vec3_dot(basis0->ex, basis1->ex), h0, 2);
    vector_putf(vec3_dot(basis0->ey, basis1->ex), h0, 3);

    vector_putf(0.0, h1, 0);
    vector_putf(-ezz, h1, 1);
    vector_putf(0.0, h1, 2);

    dres = kalman(state, z, h, eps, pdf);
    if (dres == 1e10)
	return (1e10);
    res = dres;

    z = vec3_dot(basis0->ez, basis1->ey);

    vector_putf(0.0, h0, 0);
    vector_putf(0.0, h0, 1);
    vector_putf(vec3_dot(basis0->ex, basis1->ey), h0, 2);
    vector_putf(vec3_dot(basis0->ey, basis1->ey), h0, 3);

    vector_putf(0.0, h1, 0);
    vector_putf(0.0, h1, 1);
    vector_putf(-ezz, h1, 2);

    dres = kalman(state, z, h, eps, pdf);
    if (dres == 1e10)
	return (1e10);
    res += dres;

    vector_free(h0);
    vector_free(h1);
    vector_free(h);
    return (res);
}

double  orth_planes(State * state, int i0, int i1, int *pdf)
{
    int     df0, df1;
    Basis3 *basis0;
    Basis3 *basis1;
    Vector *h;
    Vector *h0;
    Vector *h1;
    double  accuracy = state->accuracy;
    double  z, eps, res, dres;

    basis0 = (Basis3 *) vector_getp(state->basis, i0);
    basis1 = (Basis3 *) vector_getp(state->basis, i1);
    df0 = geom_df(PLANE);
    df1 = geom_df(PLANE);

    h = vector_alloc(state->maxindex, ptr_v);
    h0 = vector_alloc(df0, double_v);
    vector_putp((void *) h0, h, i0);
    h1 = vector_alloc(df1, double_v);
    vector_putp((void *) h1, h, i1);

    eps = accuracy;
    z = vec3_dot(basis0->ez, basis1->ez);

    vector_putf(0.0, h0, 0);
    vector_putf(vec3_dot(basis0->ex, basis1->ez), h0, 1);
    vector_putf(vec3_dot(basis0->ey, basis1->ez), h0, 2);

    vector_putf(0.0, h1, 0);
    vector_putf(vec3_dot(basis0->ez, basis1->ex), h1, 1);
    vector_putf(vec3_dot(basis0->ez, basis1->ey), h1, 2);

    dres = kalman(state, z, h, eps, pdf);
    if (dres == 1e10)
	return (1e10);
    res = dres;

    vector_free(h0);
    vector_free(h1);
    vector_free(h);

    return (res);
}

double  state_orth(State * state, int i0, int i1)
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
    case OPAIR(LINE3, LINE3):
	df = 1;
	res = orth_lines(state, i0, i1, &df);
	break;
    case OPAIR(LINE3, PLANE):
	df = 2;
	res = orth_line_plane(state, i0, i1, &df);
	break;
    case OPAIR(PLANE, PLANE):
	df = 2;
	res = orth_planes(state, i0, i1, &df);
	break;
    default:
	return (-1.0);
    }
    return (chisq(res, df));
}
