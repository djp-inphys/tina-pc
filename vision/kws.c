/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Vec2    kwsnake_eval(Kwsnake * kwsnake, double t)
{
    int     i, i1;
    int     n = kwsnake->n;
    double *x = kwsnake->x;
    double *y = kwsnake->y;
    double  dt, dt1;

    i = (int)floor(t);
    dt = t - i;
    dt1 = 1.0 - dt;
    while (i < 0)
	i += n;
    i %= n;
    i1 = (i + 1) % n;
    return (vec2(dt1 * x[i] + dt * x[i1], dt1 * y[i] + dt * y[i1]));
}

/**
make a spline with given points
**/

Kwsnake *kwsnake_make(int type, int n, double *x, double *y)
{
    Kwsnake *kwsnake = ts_ralloc(Kwsnake);

    kwsnake->type = type;
    kwsnake->n = n;
    kwsnake->x = dvector_dcopy(x, 0, n);
    kwsnake->y = dvector_dcopy(y, 0, n);
    return (kwsnake);
}

Kwsnake *kwsnake_copy(Kwsnake * kwsnake)
{
    if (kwsnake == NULL)
	return (NULL);
    return (kwsnake_make(kwsnake->type, kwsnake->n, kwsnake->x, kwsnake->y));
}

void    kwsnake_free(Kwsnake * kwsnake)
{
    if (kwsnake == NULL)
	return;
    dvector_free((void *) kwsnake->x, 0);
    dvector_free((void *) kwsnake->y, 0);
    rfree((void *) kwsnake);
}

Kwsnake *kwsnake_interpolate_list(int type, List * points)
{
    double *x, *y;
    Kwsnake *kwsnake;
    List   *ptr;
    int     i, n;

    n = list_length(points);
    x = dvector_alloc(0, n);
    y = dvector_alloc(0, n);
    for (i = 0, ptr = points; i < n; i++, ptr = ptr->next)
    {
	Vec2   *v = (Vec2 *) ptr->to;

	x[i] = vec2_x(*v);
	y[i] = vec2_y(*v);
    }
    kwsnake = kwsnake_make(type, n, x, y);
    dvector_free((void *) x, 0);
    dvector_free((void *) y, 0);
    return (kwsnake);
}

Kwsnake *kwsnake_from_ucbs2(Ucbs2 * ucbs, double sample, int *mask)

/* approx sample spacing */
/* if not null set ks indices for control points */
{
    double *x, *y;
    double  s, d;
    int     i, j, k, n, nmax, ntot, steps;
    Vec2    v = {Vec2_id};
    Vec2    v_next = {Vec2_id};

    if (ucbs == NULL)
	return (NULL);

    n = ucbs->n;
    nmax = (ucbs->type == LOOP) ? n : n - 1;

    v = ucbs2_eval(ucbs, 0.0);
    for (ntot = 0, i = 0; i < nmax; ++i, v = v_next)
    {
	v_next = ucbs2_eval(ucbs, i + 1.0);
	d = vec2_mod(vec2_diff(v_next, v));
	steps = (int)(d / sample + 1);

	if (mask != NULL)
	    mask[i] = ntot;
	ntot += steps;
    }

    if (ucbs->type != LOOP)
    {
	if (mask != NULL)
	    mask[i] = ntot;
	ntot++;
    }
    x = dvector_alloc(0, ntot);
    y = dvector_alloc(0, ntot);

    v = ucbs2_eval(ucbs, 0.0);
    for (i = 0, k = 0; i < nmax; ++i, v = v_next)
    {
	v_next = ucbs2_eval(ucbs, i + 1.0);
	d = vec2_mod(vec2_diff(v_next, v));
	steps = (int)(d / sample + 1);
	s = 1.0 / steps;

	for (j = 0; j < steps; ++j, ++k)
	{
	    v = ucbs2_eval(ucbs, i + j * s);
	    x[k] = vec2_x(v);
	    y[k] = vec2_y(v);
	}
    }

    if (ucbs->type != LOOP)	/* add the last point */
    {
	v = ucbs2_eval(ucbs, (double) nmax);
	x[k] = vec2_x(v);
	y[k] = vec2_y(v);
    }
    return (kwsnake_make(ucbs->type, ntot, x, y));
}

Kwsnake *kwsnake_of_es(Tstring * es, int ds)
{
    int     n;
    Kwsnake *kwsnake;
    double *x, *y;

    if (es == NULL)
	return (NULL);

    n = MAX(5, es->count / ds);
    x = dvector_alloc(0, n);
    y = dvector_alloc(0, n);
    str2_get_knots(es, n, x, y);
    kwsnake = kwsnake_make(es->type, n, x, y);
    dvector_free((void *) x, 0);
    dvector_free((void *) y, 0);
    return (kwsnake);
}

/* Convert kwsnake to edge_string */
Tstring *es_of_kwsnake(Kwsnake * kwsnake)
{
    double  t1 = 0.0;
    double t2 = 0.0;

    if (kwsnake == NULL)
	return (NULL);

    switch (kwsnake->type)
    {
    case LOOP:
	t2 = kwsnake->n;
	break;
    case STRING:
	t2 = kwsnake->n - 1;
	break;
    }
    return (str2_of_curve2(kwsnake_eval, (void *) kwsnake, t1, t2, NULL));
}

double  kws_length(Kwsnake * kwsnake)
{
    int     i, n;
    double *x, *y, l = 0.0;
    Vec2    p1 = {Vec2_id};
    Vec2    p2 = {Vec2_id};

    if (kwsnake == NULL)
	return (-1.0);
    n = kwsnake->n;
    x = kwsnake->x;
    y = kwsnake->y;
    p2 = vec2(x[n - 1], y[n - 1]);
    for (i = 0; i < n; i++)
    {
	p1 = p2;
	p2 = vec2(x[i], y[i]);
	l += vec2_dist(p1, p2);
    }
    return (l);
}
