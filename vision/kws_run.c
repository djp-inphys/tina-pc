/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

void    kwsnake_correct(Kwsnake * kwsnake, double *fx, double *fy, double dt)
{
    int     i;

    for (i = 0; i < kwsnake->n; i++)
    {
	kwsnake->x[i] -= dt * fx[i];
	kwsnake->y[i] -= dt * fy[i];
    }
}

void    kwsnake_correct_maxstep(Kwsnake * kwsnake, double *dx, double *dy, double maxstep)
{
    int     i;
    double  step = 0.0, k;

    for (i = 0; i < kwsnake->n; i++)
    {
	step = MAX(step, fabs(dx[i]));
	step = MAX(step, fabs(dy[i]));
    }
    if (step == 0.0)
	k = 0.0;
    else
	k = maxstep / step;

    kwsnake_correct(kwsnake, dx, dy, k);
}

void    kwsnake_correct_fullstep(Kwsnake * kwsnake, double *dx, double *dy, double fullstep)
{
    int     i;

    for (i = 0; i < kwsnake->n; i++)
    {
	dx[i] = (dx[i] == 0) ? 0 : SGN(dx[i]);
	dy[i] = (dy[i] == 0) ? 0 : SGN(dy[i]);
    }
    kwsnake_correct(kwsnake, dx, dy, fullstep);
}

static Vec2 grad_orth(float *rast_orth, Vec2 p, Vec2 v, Vec2 q, int n1, int n2)
{
    double  d, g;
    int     i;

    d = vec2_dot(v, vec2_diff(q, p));
    i = (int)floor(d);

    if (i < n1 || i > n2)
	return (vec2(0.0, 0.0));

    if (i > n1 && i < n2)
	g = (rast_orth[i + 1] - rast_orth[i - 1]) * 0.5;
    else if (i == n1)
	g = rast_orth[i + 1] - rast_orth[i];
    else
	g = rast_orth[i] - rast_orth[i - 1];
    return (vec2_times(g, v));
}

Vec2    kwsnake_orth(Kwsnake * kwsnake, int i)
{
    int     n = kwsnake->n;
    double *x = kwsnake->x, *y = kwsnake->y;
    Vec2    v = {Vec2_id};

    if (i != 0 && i != n - 1)
        v = vec2_unit(vec2_diff(vec2(x[i + 1], y[i + 1]), vec2(x[i - 1], y[i - 1
])));
    else if (i == 0)
    {
        if (kwsnake->type == LOOP)
            v = vec2_unit(vec2_diff(vec2(x[1], y[1]), vec2(x[n - 1], y[n - 1])))
;
        else
            v = vec2_unit(vec2_diff(vec2(x[1], y[1]), vec2(x[0], y[0])));
    } else
    {
        if (kwsnake->type == LOOP)
            v = vec2_unit(vec2_diff(vec2(x[0], y[0]), vec2(x[n - 2], y[n - 2])))
;
        else
            v = vec2_unit(vec2_diff(vec2(x[n - 1], y[n - 1]), vec2(x[n - 2], y[n
 - 2])));
    }

    return (vec2(-vec2_y(v), vec2_x(v)));
}


void    kwsnake_external_step_orth(Kwsnake * kwsnake, float **im_orth, Vec2 * p, Vec2 * v, int n1, int n2, double step, int type)
{
    static int n = 0;
    double *x = kwsnake->x;
    double *y = kwsnake->y;
    static double *fx = NULL, *fy = NULL;
    int     i;

    if (kwsnake == NULL)
	return;

    if (n != kwsnake->n)
    {
	n = kwsnake->n;
	/* BUG	dvector_free(fx, 0); dvector_free(fy, 0); */
	fx = dvector_alloc(0, n);
	fy = dvector_alloc(0, n);
    }
    for (i = 0; i < n; i++)
    {
	Vec2    grad = {Vec2_id};

	grad = grad_orth(im_orth[i], p[i], v[i], vec2(x[i], y[i]), n1, n2);
	fx[i] = vec2_x(grad);
	fy[i] = vec2_y(grad);
    }

    switch (type)
    {
    case KW_STEP:
	kwsnake_correct(kwsnake, fx, fy, step);
	break;
    case KW_MAXSTEP:
	kwsnake_correct_maxstep(kwsnake, fx, fy, step);
	break;
    case KW_FULLSTEP:
	kwsnake_correct_fullstep(kwsnake, fx, fy, step);
	break;
    }
}

static void im_gradsubpixf(Imrect * im, double y, double x, double *gy, double *gx)
{
    double  g1, g2;

    g1 = im_sub_pixf(im, y - 1, x);
    g2 = im_sub_pixf(im, y + 1, x);
    *gy = 0.5 * (g2 - g1);
    g1 = im_sub_pixf(im, y, x - 1);
    g2 = im_sub_pixf(im, y, x + 1);
    *gx = 0.5 * (g2 - g1);
}

static void im_d2subpixf(Imrect * im, double y, double x, double *ixx, double *ixy, double *iyy)
{
    *ixx = 0.5 * (im_sub_pixf(im, y, x + 1)
		  - 2.0 * im_sub_pixf(im, y, x)
		  + im_sub_pixf(im, y, x - 1));
    *iyy = 0.5 * (im_sub_pixf(im, y + 1, x)
		  - 2.0 * im_sub_pixf(im, y, x)
		  + im_sub_pixf(im, y - 1, x));
    *ixy = 0.25 * (im_sub_pixf(im, y + 1, x + 1)
		   - im_sub_pixf(im, y + 1, x - 1)
		   - im_sub_pixf(im, y - 1, x + 1)
		   + im_sub_pixf(im, y - 1, x - 1));
}

void    kwsnake_external_step_from_pot(Kwsnake * kwsnake, Imrect * pot, double step, int type)
{
    static int n = 0;
    double *x = kwsnake->x;
    double *y = kwsnake->y;
    static double *fx = NULL, *fy = NULL;
    int     i;

    if (kwsnake == NULL)
	return;

    if (n != kwsnake->n)
    {
	n = kwsnake->n;
	dvector_free((void *) fx, 0);
	dvector_free((void *) fy, 0);
	fx = dvector_alloc(0, n);
	fy = dvector_alloc(0, n);
    }
    for (i = 0; i < n; i++)
    {
	double  gx, gy;

	im_gradsubpixf(pot, y[i], x[i], &gy, &gx);
	fx[i] = gx;
	fy[i] = gy;
    }
    switch (type)
    {
    case KW_STEP:
	kwsnake_correct(kwsnake, fx, fy, step);
	break;
    case KW_MAXSTEP:
	kwsnake_correct_maxstep(kwsnake, fx, fy, step);
	break;
    case KW_FULLSTEP:
	kwsnake_correct_fullstep(kwsnake, fx, fy, step);
	break;
    }
}

static void pentadiag0(int n_call, double a0, double b0, double c0, double d0, double e0, double *x, int cyclic)
{
    static double *a, *b, *c, *d, *e;
    static int n = 0;
    int     i;

    if (n != n_call)
    {
	n = n_call;
	dvector_free((void *) a, 0);
	dvector_free((void *) b, 0);
	dvector_free((void *) c, 0);
	dvector_free((void *) d, 0);
	dvector_free((void *) e, 0);
	a = dvector_alloc(0, n);
	b = dvector_alloc(0, n);
	c = dvector_alloc(0, n);
	d = dvector_alloc(0, n);
	e = dvector_alloc(0, n);
    }
    for (i = 0; i < n; i++)
    {
	a[i] = a0;
	b[i] = b0;
	c[i] = c0;
	d[i] = d0;
	e[i] = e0;
    }
    if (!cyclic)
    {
	a[0] = a[1] = e[n - 1] = e[n - 2] = b[0] = d[n - 1] = 0;
	c[0] += a0 + b0;
	c[1] += a0;
	c[n - 1] += e0 + d0;
	c[n - 2] += e0;
    }
    pentadiag(n, a, b, c, d, e, x);
}

void    kwsnake_internal_step_orth(Kwsnake * kwsnake, Vec2 * p, Vec2 * v, double alpha, double beta)
{
    double *x = kwsnake->x;
    double *y = kwsnake->y;
    static double *o;
    double  a, b, c, d, e;
    static int n = 0;
    int     i;

    if (n != kwsnake->n)
    {
	n = kwsnake->n;
	dvector_free((void *) o, 0);
	o = dvector_alloc(0, n);
    }
    for (i = 0; i < n; ++i)
	o[i] = vec2_dot(vec2_diff(vec2(x[i], y[i]), p[i]), v[i]);

    e = a = beta;
    d = b = -alpha - 4.0 * beta;
    c = 1.0 + 2.0 * alpha + 6.0 * beta;

    pentadiag0(n, a, b, c, d, e, o, kwsnake->type == LOOP);

    for (i = 0; i < n; ++i)
    {
	Vec2    pi = {Vec2_id};

	pi = vec2_sum(p[i], vec2_times(o[i], v[i]));
	x[i] = vec2_x(pi);
	y[i] = vec2_y(pi);
    }
}

void    kwsnake_dt_step(Kwsnake * kwsnake, Imrect * pot, double alpha, double beta, double trans_dt, double shape_dt)
{
    static int n = -1;
    static double *fx = NULL, *fy = NULL, fxmean, fymean;
    double *x = kwsnake->x;
    double *y = kwsnake->y;
    double  a, b, c, d, e, fmax;
    int     i;

    if (kwsnake == NULL)
	return;

    if (n != kwsnake->n)
    {
	n = kwsnake->n;
	/* BUG	dvector_alloc(fx, 0); dvector_alloc(fy, 0); */
	fx = dvector_alloc(0, n);
	fy = dvector_alloc(0, n);
    }
    fmax = 0.0;
    for (i = 0; i < n; i++)
    {
	double  gx, gy, k;
	Vec2    n = {Vec2_id};
	Vec2    kwsnake_orth();

	im_gradsubpixf(pot, y[i], x[i], &gy, &gx);

	n = kwsnake_orth(kwsnake, i);
	k = fabs(vec2_dot(n, vec2_unit(vec2(gx, gy))));
	gx *= k;
	gy *= k;

	fx[i] = -gx;
	fxmean += fx[i];
	fmax = MAX(fmax, fabs(gx));
	fy[i] = -gy;
	fymean += fy[i];
	fmax = MAX(fmax, fabs(gy));
    }
    fxmean /= n;
    fymean /= n;

    if (fmax == 0.0)
	fmax = 1.0;
    for (i = 0; i < n; i++)
    {
	fx[i] -= fxmean;
	fx[i] /= fmax;
	fy[i] -= fymean;
	fy[i] /= fmax;
    }

    fmax = MAX(fabs(fxmean), fabs(fymean));
    if (fmax == 0.0)
	fmax = 1.0;
    fxmean /= fmax;
    fymean /= fmax;

    for (i = 0; i < n; i++)
    {
	x[i] += trans_dt * fxmean + shape_dt * fx[i];
	y[i] += trans_dt * fymean + shape_dt * fy[i];
    }

    e = a = shape_dt * beta;
    d = b = -shape_dt * (alpha + 4.0 * beta);
    c = 1.0 + shape_dt * (2.0 * alpha + 6.0 * beta);

    pentadiag0(n, a, b, c, d, e, x, kwsnake->type == LOOP);
    pentadiag0(n, a, b, c, d, e, y, kwsnake->type == LOOP);
}

void    kwsnake_dt_step2(Kwsnake * kwsnake, Imrect * pot, double alpha, double beta, double trans_dt, double shape_dt)
{
    static int n = -1;
    static double *fx = NULL, *fy = NULL, fxmean, fymean;
    double *x = kwsnake->x;
    double *y = kwsnake->y;
    double  a, b, c, d, e, fmax;
    int     i;

    if (kwsnake == NULL)
	return;

    if (n != kwsnake->n)
    {
	n = kwsnake->n;
	/* BUG 	dvector_alloc(fx, 0); dvector_alloc(fy, 0); */
	fx = dvector_alloc(0, n);
	fy = dvector_alloc(0, n);
    }
    fmax = 0.0;
    for (i = 0; i < n; i++)
    {
	double  ixx, ixy, iyy, gx, gy;
	Vec2    normal = {Vec2_id};
	Vec2    kwsnake_orth();

	im_d2subpixf((Imrect *) pot, *y, *x, &ixx, &ixy, &iyy);
	normal = kwsnake_orth(kwsnake, i);
	gx = ixx * vec2_x(normal) + ixy * vec2_y(normal);
	gy = ixy * vec2_x(normal) + iyy * vec2_y(normal);

	fx[i] = -gx;
	fxmean += fx[i];
	fmax = MAX(fmax, fabs(gx));
	fy[i] = -gy;
	fymean += fy[i];
	fmax = MAX(fmax, fabs(gy));
    }
    fxmean /= n;
    fymean /= n;

    if (fmax == 0.0)
	fmax = 1.0;
    for (i = 0; i < n; i++)
    {
	fx[i] -= fxmean;
	fx[i] /= fmax;
	fy[i] -= fymean;
	fy[i] /= fmax;
    }

    fmax = MAX(fabs(fxmean), fabs(fymean));
    if (fmax == 0.0)
	fmax = 1.0;
    fxmean /= fmax;
    fymean /= fmax;

    for (i = 0; i < n; i++)
    {
	x[i] += trans_dt * fxmean + shape_dt * fx[i];
	y[i] += trans_dt * fymean + shape_dt * fy[i];
    }

    e = a = shape_dt * beta;
    d = b = -shape_dt * (alpha + 4.0 * beta);
    c = 1.0 + shape_dt * (2.0 * alpha + 6.0 * beta);

    pentadiag0(n, a, b, c, d, e, x, kwsnake->type == LOOP);
    pentadiag0(n, a, b, c, d, e, y, kwsnake->type == LOOP);
}

double  kwsnake_dist(Kwsnake * kws1, Kwsnake * kws2)
{
    int     n = kws1->n;
    double *x1 = kws1->x, *x2 = kws2->x;
    double *y1 = kws1->y, *y2 = kws2->y;
    double  d, dmax = 0.0;
    int     i;

    for (i = 0; i < n; i++)
    {
	d = fabs(x1[i] - x2[i]) + fabs(y1[i] - y2[i]);
	if (dmax < d)
	    dmax = d;
    }
    return (dmax);
}

double  kwsnake_dt_run(Kwsnake * kwsnake, Imrect * pot, double alpha, double beta, double trans_dt, double shape_dt, int steps)
{
    int     i;
    double  d;
    Kwsnake *copy = kwsnake_copy(kwsnake);

    for (i = 0; i < steps; i++)
	kwsnake_dt_step(kwsnake, pot, alpha, beta, trans_dt, shape_dt);
    d = kwsnake_dist(kwsnake, copy);
    kwsnake_free(copy);
    return (d);
}

double  kwsnake_dt_run2(Kwsnake * kwsnake, Imrect * pot, double alpha, double beta, double trans_dt, double shape_dt, int steps)
{
    int     i;
    double  d;
    Kwsnake *copy = kwsnake_copy(kwsnake);

    for (i = 0; i < steps; i++)
	kwsnake_dt_step2(kwsnake, pot, alpha, beta, trans_dt, shape_dt);
    d = kwsnake_dist(kwsnake, copy);
    kwsnake_free(copy);
    return (d);
}

void    kwsnake_internal_step(Kwsnake * kwsnake, double alpha, double beta)
{
    double *x = kwsnake->x;
    double *y = kwsnake->y;
    double  a, b, c, d, e;
    int     n = kwsnake->n;

    e = a = beta;
    d = b = -alpha - 4.0 * beta;
    c = 1.0 + 2.0 * alpha + 6.0 * beta;
    pentadiag0(n, a, b, c, d, e, x, kwsnake->type == LOOP);
    pentadiag0(n, a, b, c, d, e, y, kwsnake->type == LOOP);
}

void    kwsnake_step_from_pot(Kwsnake * kwsnake, Imrect * pot, double alpha, double beta, double step, int type)
{
    kwsnake_external_step_from_pot(kwsnake, pot, step, type);
    kwsnake_internal_step(kwsnake, alpha, beta);
}

void    kwsnake_reorth(Kwsnake * kwsnake, Vec2 * p, Vec2 * v)
{
    double *x, *y;
    int     i, n;

    if (kwsnake == NULL)
	return;

    x = kwsnake->x;
    y = kwsnake->y;
    n = kwsnake->n;

    for (i = 0; i < n; ++i)
    {
	double  dp = vec2_dot(v[i], vec2_diff(vec2(x[i], y[i]), p[i]));
	Vec2    new = {Vec2_id};

	new = vec2_sum(p[i], vec2_times(dp, v[i]));
	x[i] = vec2_x(new);
	y[i] = vec2_y(new);
    }
}

void    kwsnake_orth_step(Kwsnake * kwsnake, float **im_orth, Vec2 * p, Vec2 * v, int n1, int n2, double alpha, double beta, double step, int type)
{
    kwsnake_external_step_orth(kwsnake, im_orth, p, v, n1, n2, step, type);
    kwsnake_internal_step(kwsnake, alpha, beta);
}

void    kwsnake_step_orth(Kwsnake * kwsnake, float **im_orth, Vec2 * p, Vec2 * v, int n1, int n2, double alpha, double beta, double step, int type)
{
    kwsnake_external_step_orth(kwsnake, im_orth, p, v, n1, n2, step, type);
    kwsnake_internal_step(kwsnake, alpha, beta);
    kwsnake_reorth(kwsnake, p, v);
}

void    kwsnake_inflate(Kwsnake * kwsnake, Vec2 * p, Vec2 * v, double step)
{
    double *x, *y;
    int     i, n;

    if (kwsnake == NULL)
	return;

    x = kwsnake->x;
    y = kwsnake->y;
    n = kwsnake->n;

    for (i = 0; i < n; ++i)
    {
	Vec2    pi = {Vec2_id};

	pi = vec2_sum(p[i], vec2_times(step, v[i]));
	x[i] = vec2_x(pi);
	y[i] = vec2_y(pi);
    }
}

void    kwsnake_grow(Kwsnake * kwsnake, Vec2 * p, Vec2 * v, Imrect * im, double mean, double sd, double step)
{
    double *x, *y;
    double  gl, gl_low, gl_up;
    int     i, n;

    if (kwsnake == NULL)
	return;

    x = kwsnake->x;
    y = kwsnake->y;
    n = kwsnake->n;

    gl_low = mean - 2 * sd;
    gl_up = mean + 2 * sd;

    for (i = 0; i < n; ++i)
    {
	Vec2    pi = {Vec2_id};

	gl = im_sub_pixf(im, y[i], x[i]);
	if (gl < gl_low || gl > gl_up)
	{
	    pi = vec2_sum(p[i], vec2_times(-step, v[i]));
	    x[i] = vec2_x(pi);
	    y[i] = vec2_y(pi);
	    continue;
	}
	pi = vec2_sum(p[i], vec2_times(step, v[i]));
	gl = im_sub_pixf(im, vec2_y(pi), vec2_x(pi));
	if (gl > gl_low && gl < gl_up)
	{
	    x[i] = vec2_x(pi);
	    y[i] = vec2_y(pi);
	}
    }
}

/* ARGSUSED quieten lint */
void    kwsnake_region(Kwsnake * kwsnake, Imrect * im, double mean, double sd, Vec2 * p, Vec2 * v, double alpha, double beta, double step, int type)





/* unused */
{
    kwsnake_grow(kwsnake, p, v, im, mean, sd, step);
    kwsnake_internal_step(kwsnake, alpha, beta);
}
