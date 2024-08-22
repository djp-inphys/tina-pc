/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/**
values of basis cubics at  u
**/

void    ucbs2_basis_val(double u, double *b0, double *b1, double *b2, double *b3)
{
    double  u1 = 1 - u;

    *b0 = u * u * u / 6.0;
    *b1 = (1.0 + u * (3.0 + u * (3.0 - u * 3.0))) / 6.0;
    *b2 = (4.0 + u * u * (-6.0 + u * 3.0)) / 6.0;
    *b3 = u1 * u1 * u1 / 6.0;
}

/**

evaluate uniform cubic spline at t in [0, n)
**/

Vec2    ucbs2_eval(Ucbs2 * ucbs, double t)
{
    int     i;
    double  u = 0.0;
    double x, y;
    double  b0, b1, b2, b3;
    double  cx0, cx1, cx2, cx3;
    double  cy0, cy1, cy2, cy3;
    double *cx = ucbs->cx;
    double *cy = ucbs->cy;

    i = (int)floor(t);
    switch (ucbs->type)		/** if i out of range **/
    {
    case LOOP:			/** make periodic **/
	u = t - i;
	while (i < 0)
	    i += ucbs->n;
	i %= ucbs->n;
	break;
    case STRING:		/** extrapolate last cubic **/
	if (i < 0)
	    i = 0;
	else if (i > ucbs->n - 2)
	    i = ucbs->n - 2;
	u = t - i;
	break;
    }

    cx0 = cx[i];
    cy0 = cy[i];
    cx1 = cx[i + 1];
    cy1 = cy[i + 1];
    cx2 = cx[i + 2];
    cy2 = cy[i + 2];
    if (i == ucbs->n - 1)
    {
	cx3 = cx[2];
	cy3 = cy[2];
    } else
    {
	cx3 = cx[i + 3];
	cy3 = cy[i + 3];
    }

    ucbs2_basis_val(u, &b0, &b1, &b2, &b3);
    x = b3 * cx0 + b2 * cx1 + b1 * cx2 + b0 * cx3;
    y = b3 * cy0 + b2 * cy1 + b1 * cy2 + b0 * cy3;
    return (vec2(x, y));
}

/* find the spline parameter value approximately closest to point p */

static double resolution = 0.25;
static Vec2 v_close = {Vec2_id};
static Ucbs2 *ucbs_close;

void    ucbs_set_resolution(double res)
{
    resolution = res * res;
}

static int tol(double t1, double t2)
{
    Vec2    v1 = {Vec2_id};
    Vec2    v2 = {Vec2_id};

    v1 = ucbs2_eval(ucbs_close, t1);
    v2 = ucbs2_eval(ucbs_close, t2);
    return (vec2_sqrmod(vec2_diff(v2, v1)) > resolution);
}

static double dist_to_v(double t)
{
    Vec2    v = {Vec2_id};

    v = ucbs2_eval(ucbs_close, t);
    return (vec2_sqrmod(vec2_diff(v, v_close)));
}

/* find closest between params using golden section method */
double  ucbs2_closest_param_to(Ucbs2 * ucbs, Vec2 v, int i)
{
    double  t1, t2;

    /* BUGFIX v1 & v2 unused */
    /* Vec2    v1, v2; */

    if (ucbs == NULL)
	return (0.0);

    v_close = v;
    ucbs_close = ucbs;

    t1 = i - 1.0;
    t2 = i + 1.0;

    /** commented to allow extrapolation
    if (ucbs->type!=LOOP)
    {
        if (i==0)
	   t1 = i;
	if (i==ucbs->n-1)
	   t2 = ucbs->n-1;
    }
    **/
    /* BUGFIX v1 unused */
    /* v1 = ucbs2_eval(ucbs, t1); */
    /* BUGFIX v2 unused */
    /* v2 = ucbs2_eval(ucbs, t2); */
    return (golden_section(dist_to_v, t1, t2, tol, NULL,
			   NULL));
}

double  ucbs2_param(Ucbs2 * ucbs, Vec2 v)
{
    int     n;
    int     i, mini = 0;
    double  t, d, mind;

    if (ucbs == NULL)
	return (0.0);

    n = ucbs->n;
    mind = vec2_sqrmod(vec2_diff(v, ucbs2_eval(ucbs, 0.0)));
    for (i = 0; i < n; ++i)
    {
	d = vec2_sqrmod(vec2_diff(v, ucbs2_eval(ucbs, (double) i)));

	if (d < mind)
	{
	    mind = d;
	    mini = i;
	}
    }

    t = ucbs2_closest_param_to(ucbs, v, mini);

    if (ucbs->type == LOOP)
    {
	if (t < 0)
	    t += n;
	else if (t > n)
	    t -= n;
	return (t);
    } else
	return (t);
}

/**
make a spline with given number of knots
**/

Ucbs2  *ucbs2_make(int type, int n)
{
    Ucbs2  *ucbs = ts_ralloc(Ucbs2);

    ucbs->type = type;
    ucbs->n = n;
    ucbs->cx = dvector_alloc(0, n + 2);
    ucbs->cy = dvector_alloc(0, n + 2);
    ucbs->props = NULL;

    return (ucbs);
}

Ucbs2  *ucbs2_copy(Ucbs2 * old)
{
    Ucbs2  *new;

    if (old == NULL)
	return (NULL);

    new = ts_ralloc(Ucbs2);
    new->type = old->type;
    new->n = old->n;
    new->cx = dvector_dcopy(old->cx, 0, old->n + 2);
    new->cy = dvector_dcopy(old->cy, 0, old->n + 2);
    new->props = proplist_copy(old->props);

    return (new);
}

void    ucbs2_free(Ucbs2 * ucbs)
{
    if (ucbs == NULL)
	return;
    dvector_free((void *) ucbs->cx, 0);
    dvector_free((void *) ucbs->cy, 0);
    rfree((void *) ucbs);
}

static void interpolate(int type, int n, double *x, double *cx)
{
    int     i;
    double *a = dvector_alloc(0, n);
    double *b = dvector_alloc(0, n);
    double *c = dvector_alloc(0, n);

    for (i = 0; i < n; i++)
	cx[i + 1] = x[i];

    /** end conditions **/
    switch (type)
    {
    case LOOP:
	/** periodic **/
	a[0] = c[0] = 1.0 / 6.0;
	b[0] = 2.0 / 3.0;
	a[n - 1] = c[n - 1] = 1.0 / 6.0;
	b[n - 1] = 2.0 / 3.0;
	break;
    case STRING:
	/** natural **/
	a[0] = c[0] = 0.0;
	b[0] = 1.0;
	a[n - 1] = c[n - 1] = 0.0;
	b[n - 1] = 1.0;
	break;
    }

    for (i = 1; i < n - 1; i++)
    {
	a[i] = c[i] = 1.0 / 6.0;
	b[i] = 2.0 / 3.0;
    }

    triadiag(n, a, b, c, cx + 1);
    dvector_free((void *) a, 0);
    dvector_free((void *) b, 0);
    dvector_free((void *) c, 0);
}

void    ucbs2_end_conditions(Ucbs2 * ucbs)
{
    double *cx = ucbs->cx;
    double *cy = ucbs->cy;
    int     n = ucbs->n;

    /** end conditions **/
    switch (ucbs->type)
    {
    case LOOP:
	/** periodic **/
	cx[0] = cx[n];
	cx[n + 1] = cx[1];
	cy[0] = cy[n];
	cy[n + 1] = cy[1];
	break;
    case STRING:
	/** natural **/
	cx[0] = 2.0 * cx[1] - cx[2];
	cx[n + 1] = 2.0 * cx[n] - cx[n - 1];
	cy[0] = 2.0 * cy[1] - cy[2];
	cy[n + 1] = 2.0 * cy[n] - cy[n - 1];
	break;
    }
}

void    ucbs2_interpolate(Ucbs2 * ucbs, double *x, double *y)
{
    interpolate(ucbs->type, ucbs->n, x, ucbs->cx);
    interpolate(ucbs->type, ucbs->n, y, ucbs->cy);
    ucbs2_end_conditions(ucbs);
}

/* delete a control point from a ucbs */
void    ucbs2_delete_control(Ucbs2 * ucbs, int t)

/* the control point in range 1 to n */
{
    double *x, *y;
    int     i, n;
    Vec2    v = {Vec2_id};

    t--;			/* parameter value of control point */
    if (ucbs == NULL || t < 0 || t > ucbs->n)
	return;
    n = ucbs->n - 1;

    if (n == 0)
    {
	ucbs->n = 0;
	return;
    }
    x = dvector_alloc(0, n);
    y = dvector_alloc(0, n);

    for (i = 0; i < t; i++)
    {
	v = ucbs2_eval(ucbs, (double) i);
	x[i] = vec2_x(v);
	y[i] = vec2_y(v);
    }
    for (; i < n; ++i)
    {
	v = ucbs2_eval(ucbs, i + 1.0);
	x[i] = vec2_x(v);
	y[i] = vec2_y(v);
    }

    ucbs->n = n;
    ucbs2_interpolate(ucbs, x, y);
    dvector_free((void *) x, 0);
    dvector_free((void *) y, 0);
}

/* add a new control point to ucbs */
void    ucbs2_add_control(Ucbs2 * ucbs, int t, Vec2 vt)

/* new control point added after t in range 1 to n */
/* new interpolation point must pass through vt */
{
    double *x, *y;
    int     i, n;
    Vec2    v = {Vec2_id};

    t--;			/* parameter value of control point */
    if (ucbs == NULL || t < 0 || t >= ucbs->n)
	return;
    n = ucbs->n + 1;

    x = dvector_alloc(0, n);
    y = dvector_alloc(0, n);

    for (i = 0; i <= t; i++)
    {
	v = ucbs2_eval(ucbs, (double) i);
	x[i] = vec2_x(v);
	y[i] = vec2_y(v);
    }

    x[i] = vec2_x(vt);
    y[i] = vec2_y(vt);
    i++;

    for (; i < n; i++)
    {
	v = ucbs2_eval(ucbs, i - 1.0);
	x[i] = vec2_x(v);
	y[i] = vec2_y(v);
    }

    dvector_free((void *) ucbs->cx, 0);
    dvector_free((void *) ucbs->cy, 0);
    ucbs->cx = dvector_alloc(0, n + 2);
    ucbs->cy = dvector_alloc(0, n + 2);
    ucbs->n = n;
    ucbs2_interpolate(ucbs, x, y);
    dvector_free((void *) x, 0);
    dvector_free((void *) y, 0);
}

/* add a new control point to ucbs: version above is strange */
void    ucbs2_add_point(Ucbs2 * ucbs, int t, Vec2 vt)

/* control point added after t */
/* new interpolation point must pass through vt */
{
    double *x, *y;
    int     i, n;
    Vec2    v = {Vec2_id};

    if (ucbs == NULL || t < 0 || t >= ucbs->n)
	return;
    n = ucbs->n + 1;

    x = dvector_alloc(0, n);
    y = dvector_alloc(0, n);

    for (i = 0; i <= t; i++)
    {
	v = ucbs2_eval(ucbs, (double) i);
	x[i] = vec2_x(v);
	y[i] = vec2_y(v);
    }
    x[i] = vec2_x(vt);
    y[i] = vec2_y(vt);
    i++;
    for (; i < n; i++)
    {
	v = ucbs2_eval(ucbs, i - 1.0);
	x[i] = vec2_x(v);
	y[i] = vec2_y(v);
    }

    dvector_free((void *) ucbs->cx, 0);
    dvector_free((void *) ucbs->cy, 0);
    ucbs->cx = dvector_alloc(0, n + 2);
    ucbs->cy = dvector_alloc(0, n + 2);
    ucbs->n = n;
    ucbs2_interpolate(ucbs, x, y);
    dvector_free((void *) x, 0);
    dvector_free((void *) y, 0);
}

/* delete a control point from a ucbs: version above is strange */
void    ucbs2_delete_point(Ucbs2 * ucbs, int t)

/* the control point */
{
    double *x, *y;
    int     i, n;
    Vec2    v = {Vec2_id};

    if (ucbs == NULL || t < 0 || t > ucbs->n || ucbs->n < 6)
	return;
    n = ucbs->n - 1;

    if (n == 0)
    {
	ucbs->n = 0;
	return;
    }
    x = dvector_alloc(0, n);
    y = dvector_alloc(0, n);

    for (i = 0; i < t; i++)
    {
	v = ucbs2_eval(ucbs, (double) i);
	x[i] = vec2_x(v);
	y[i] = vec2_y(v);
    }
    for (; i < n; ++i)
    {
	v = ucbs2_eval(ucbs, i + 1.0);
	x[i] = vec2_x(v);
	y[i] = vec2_y(v);
    }

    ucbs->n = n;
    ucbs2_interpolate(ucbs, x, y);
    dvector_free((void *) x, 0);
    dvector_free((void *) y, 0);
}

void    ucbs2_replace_point(Ucbs2 * ucbs, int ip, Vec2 p)


/* new i'th interpolation point must pass through p */
{
    double *x, *y;
    int     i, n;

    if (ucbs == NULL || ip < 0 || ip > ucbs->n)
	return;

    n = ucbs->n;
    x = dvector_alloc(0, n);
    y = dvector_alloc(0, n);

    /* old interpolation points */
    for (i = 0; i < n; i++)
    {
	Vec2    v = {Vec2_id};

	v = ucbs2_eval(ucbs, (double) i);
	x[i] = vec2_x(v);
	y[i] = vec2_y(v);
    }

    /* replace point i = ip */
    x[ip] = vec2_x(p);
    y[ip] = vec2_y(p);

    ucbs2_interpolate(ucbs, x, y);
    dvector_free((void *) x, 0);
    dvector_free((void *) y, 0);
}

Ucbs2  *ucbs2_interpolate_list(int type, List * points)
{
    double *x, *y;
    Ucbs2  *ucbs;
    List   *ptr;
    int     i, n;

    n = list_length(points);
    ucbs = ucbs2_make(type, n);
    x = dvector_alloc(0, n);
    y = dvector_alloc(0, n);
    for (i = 0, ptr = points; i < n; i++, ptr = ptr->next)
    {
	Vec2   *v = (Vec2 *) ptr->to;

	x[i] = vec2_x(*v);
	y[i] = vec2_y(*v);
    }
    interpolate(ucbs->type, ucbs->n, x, ucbs->cx);
    interpolate(ucbs->type, ucbs->n, y, ucbs->cy);
    dvector_free((void *) x, 0);
    dvector_free((void *) y, 0);
    ucbs2_end_conditions(ucbs);

    return (ucbs);
}

void    ucbs2_interpolate_kwsnake(Ucbs2 * ucbs, Kwsnake * kwsnake, int *mask)
{
    double *x, *y;
    int     i, n;

    if (ucbs == NULL || kwsnake == NULL || ucbs->n > kwsnake->n)
	return;

    n = ucbs->n;

    if (mask == NULL)
    {
	ucbs2_interpolate(ucbs, kwsnake->x, kwsnake->y);
	return;
    }
    x = dvector_alloc(0, n);
    y = dvector_alloc(0, n);

    for (i = 0; i < n; ++i)
    {
	x[i] = kwsnake->x[mask[i]];
	y[i] = kwsnake->y[mask[i]];
    }

    ucbs2_interpolate(ucbs, x, y);
    dvector_free((void *) x, 0);
    dvector_free((void *) y, 0);
}

Ucbs2  *ucbs2_of_str2(Tstring * es, int ds)
{
    int     n;
    Ucbs2  *ucbs;
    double *x, *y;

    if (es == NULL)
	return (NULL);

    n = MAX(5, es->count / ds);
    ucbs = ucbs2_make(es->type, n);
    x = dvector_alloc(0, n);
    y = dvector_alloc(0, n);
    str2_get_knots(es, n, x, y);
    ucbs2_interpolate(ucbs, x, y);
    dvector_free((void *) x, 0);
    dvector_free((void *) y, 0);
    return (ucbs);
}

Tstring *str2_of_ucbs2(Ucbs2 * ucbs)
{
    double  t1 = 0.0, t2 = 0.0;

    if (ucbs == NULL)
	return (NULL);

    switch (ucbs->type)
    {
    case LOOP:
	t2 = ucbs->n;
	break;
    case STRING:
	t2 = ucbs->n - 1;
	break;
    }
    return (str2_of_curve2(ucbs2_eval, (void *) ucbs, t1, t2, NULL));
}
