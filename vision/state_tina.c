/**@(#)
**/
/**
state_tina.c:
adding Tina primitives to a state
**/

#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/sysfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

double  cam_pix(), cam_f();
Vec3    left_origin();
Vec3    right_origin();

void    state_set_cov_scalar(State * state, int i, double err)
{
    Matrix *sii;
    double  var = err * err;
    int     df = geom_df(SCALAR);

    sii = matrix_alloc(df, df, matrix_lower, double_v);
    matrix_putf(var, sii, 0, 0);
    matrix_putp((void *) sii, state->s, i, i);
}

void    state_set_cov_point2(State * state, int i, double poserr)
{
    Matrix *sii;
    double  pvar = poserr * poserr;
    int     df = geom_df(POINT2);

    sii = matrix_alloc(df, df, matrix_lower, double_v);
    matrix_putf(pvar, sii, 0, 0);
    matrix_putf(pvar, sii, 1, 1);
    matrix_putp((void *) sii, state->s, i, i);
}

void    state_set_cov_line2(State * state, int i, double poserr, double angerr)
{
    Matrix *sii;
    double  pvar = poserr * poserr;
    double  avar = angerr * angerr;
    int     df = geom_df(LINE2);

    sii = matrix_alloc(df, df, matrix_lower, double_v);
    matrix_putf(pvar, sii, 0, 0);
    matrix_putf(avar, sii, 1, 1);
    matrix_putp((void *) sii, state->s, i, i);
}

void    state_set_cov_point3(State * state, int i, double poserr)
{
    Matrix *sii;
    double  pvar = poserr * poserr;
    int     df = geom_df(POINT3);

    sii = matrix_alloc(df, df, matrix_lower, double_v);
    matrix_putf(pvar, sii, 0, 0);
    matrix_putf(pvar, sii, 1, 1);
    matrix_putf(pvar, sii, 2, 2);
    matrix_putp((void *) sii, state->s, i, i);
}

void    state_set_cov_line3(State * state, int i, double poserr, double angerr)
{
    Matrix *sii;
    double  pvar = poserr * poserr;
    double  avar = angerr * angerr;
    int     df = geom_df(LINE3);

    sii = matrix_alloc(df, df, matrix_lower, double_v);
    matrix_putf(pvar, sii, 0, 0);
    matrix_putf(pvar, sii, 1, 1);
    matrix_putf(avar, sii, 2, 2);
    matrix_putf(avar, sii, 3, 3);
    matrix_putp((void *) sii, state->s, i, i);
}

void    state_set_cov_plane(State * state, int i, double poserr, double angerr)
{
    Matrix *sii;
    double  pvar = poserr * poserr;
    double  avar = angerr * angerr;
    int     df = geom_df(PLANE);

    sii = matrix_alloc(df, df, matrix_lower, double_v);
    matrix_putf(pvar, sii, 0, 0);
    matrix_putf(avar, sii, 1, 1);
    matrix_putf(avar, sii, 2, 2);
    matrix_putp((void *) sii, state->s, i, i);
}

void    state_set_cov_transf3(State * state, int i, double poserr, double angerr)
{
    Matrix *sii;
    double  pvar = poserr * poserr;
    double  avar = angerr * angerr;
    int     df = geom_df(TRANSF3);

    sii = matrix_alloc(df, df, matrix_lower, double_v);
    matrix_putf(avar, sii, 0, 0);
    matrix_putf(avar, sii, 1, 1);
    matrix_putf(avar, sii, 2, 2);
    matrix_putf(pvar, sii, 3, 3);
    matrix_putf(pvar, sii, 4, 4);
    matrix_putf(pvar, sii, 5, 5);
    matrix_putp((void *) sii, state->s, i, i);
}

void    state_set_infcov(State * state, int i)
{
    double  big = 1.0;
    double  lscale = state->lscale;

    switch (vector_get(state->type, i))
    {
    case POINT2:
	{
	    double  poserr = lscale * big;

	    state_set_cov_point2(state, i, poserr);
	    break;
	}
    case LINE2:
	{
	    double  poserr = lscale * big;
	    double  angerr = big;

	    state_set_cov_line2(state, i, poserr, angerr);
	    break;
	}
    case POINT3:
	{
	    double  poserr = lscale * big;

	    state_set_cov_point3(state, i, poserr);
	    break;
	}
    case LINE3:
	{
	    double  poserr = lscale * big;
	    double  angerr = big;

	    state_set_cov_line3(state, i, poserr, angerr);
	    break;
	}
    case PLANE:
	{
	    double  poserr = lscale * big;
	    double  angerr = big;

	    state_set_cov_plane(state, i, poserr, angerr);
	    break;
	}
    case TRANSF3:
	{
	    double  poserr = lscale * big;
	    double  angerr = big;

	    state_set_cov_transf3(state, i, poserr, angerr);
	    break;
	}
    }
}

void    state_tinacov_line3(State * state, int i, Line3 * line)
{
    int     iray, ipoint;
    Line3  *ray;
    Point3 *point;
    Vec3    origin = {Vec3_id};
    Vec3    v = {Vec3_id};
    double  err = cam_pix() / cam_f();
    double  state_on();

    state_set_infcov(state, i);

    point = point3_make(line->p1, (int) NULL);
    ipoint = state_add(state, (void *) point, POINT3);
    state_set_infcov(state, ipoint);

    origin = left_origin();
    v = vec3_diff(line->p1, origin);
    ray = line3_make(vec3_diff(origin, v), line->p1, (int) NULL);
    iray = state_add(state, (void *) ray, LINE3);
    state_set_cov_line3(state, iray, 0.0, err);

    /* BUGFIX chi2 unused */
    /* double  chi2; chi2 = state_on(state, ipoint, iray); */
    (void) state_on(state, ipoint, iray);
    state_delete(state, iray);
    geom_free((void *) ray, LINE3);

    origin = right_origin();
    v = vec3_diff(line->p1, origin);
    ray = line3_make(vec3_diff(origin, v), line->p1, (int) NULL);
    iray = state_add(state, (void *) ray, LINE3);
    state_set_cov_line3(state, iray, 0.0, err);

    /* BUGFIX */
    /* WAS: chi2 = state_on(state, ipoint, iray); */
    (void) state_on(state, ipoint, iray);
    state_delete(state, iray);
    geom_free((void *) ray, LINE3);

    /* BUGFIX */
    /* WAS: chi2 = state_on(state, ipoint, iray); */
    (void) state_on(state, ipoint, i);
    state_delete(state, ipoint);
    geom_free((void *) point, POINT3);

    point = point3_make(line->p2, (int) NULL);
    ipoint = state_add(state, (void *) point, POINT3);
    state_set_infcov(state, ipoint);

    origin = left_origin();
    v = vec3_diff(line->p2, origin);
    ray = line3_make(vec3_diff(origin, v), line->p2, (int) NULL);
    iray = state_add(state, (void *) ray, LINE3);
    state_set_cov_line3(state, iray, 0.0, err);

    /* BUGFIX */
    /* WAS: chi2 = state_on(state, ipoint, iray); */
    (void) state_on(state, ipoint, iray);
    state_delete(state, iray);
    geom_free((void *) ray, LINE3);

    origin = right_origin();
    v = vec3_diff(line->p2, origin);
    ray = line3_make(vec3_diff(origin, v), line->p2, (int) NULL);
    iray = state_add(state, (void *) ray, LINE3);
    state_set_cov_line3(state, iray, 0.0, err);

    /* BUGFIX */
    /* WAS: chi2 = state_on(state, ipoint, iray); */
    (void) state_on(state, ipoint, iray);
    state_delete(state, iray);
    geom_free((void *) ray, LINE3);

    /* BUGFIX chi2 unused */
    /* WAS: chi2 = state_on(state, ipoint, i); */
    (void) state_on(state, ipoint, i);
    state_delete(state, ipoint);
    geom_free((void *) point, POINT3);

    state_correct(state);
}

int     state_add_tina(State * state, void *geom, int type)
{
    int     i;

    i = state_add(state, geom, type);
    switch (type)
    {
    case LINE3:
	{
	    Line3  *line = (Line3 *) geom;

	    state_tinacov_line3(state, i, line);
	    break;
	}
    }
    return (i);
}
