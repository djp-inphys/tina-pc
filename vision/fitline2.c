/**@(#)
**/
#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

#define FIT_GAP_THRESHOLD 10

Bool    fit2_point_on_line(Vec2 p, Vec2 v, Vec2 c, double thres)
{
    Vec2    d = {Vec2_id};
    double  dp;

    d = vec2_diff(p, c);
    dp = vec2_dot(v, d);
    d = vec2_diff(d, vec2_times(dp, v));
    return ((vec2_sqrmod(d) < SQR(thres)) ? true : false);
}

Bool    fit2_all_points_on_line(Ddlist * start, Ddlist * end, Vec2 v, Vec2 c, double thres)
{
    Ddlist *dptr;
    Vec2    p = {Vec2_id};

    for (dptr = start;; dptr = dptr->next)
    {
	DD_GET_POS2(dptr, p);
	if (fit2_point_on_line(p, v, c, thres) == false)
	    return (false);
	if (dptr == end)
	    break;
    }

    return (true);
}

int     fit2_points_off_line(Ddlist * start, Ddlist * end, Vec2 v, Vec2 c, double thres)
{
    Ddlist *dptr;
    int     n = 0;
    Vec2    p = {Vec2_id};

    for (dptr = start;; dptr = dptr->next)
    {
	DD_GET_POS2(dptr, p);
	if (fit2_point_on_line(p, v, c, thres) == false)
	    ++n;
	if (dptr == end)
	    break;
    }

    return (n);
}

Ddlist *fit2_findstart(Ddlist * pos, Ddlist * start, Vec2 v, Vec2 c, double thres)
{
    Ddlist *last;
    Ddlist *dptr;
    int     gap = 0;

    if (start == NULL || pos == NULL)
	return (pos);

    for (last = dptr = pos;; dptr = dptr->last)
    {
	Vec2    p = {Vec2_id};

	DD_GET_POS2(dptr, p);
	if (!fit2_point_on_line(p, v, c, thres * 2))
	    break;
	if (fit2_point_on_line(p, v, c, thres))
	{
	    gap = 0;
	    last = dptr;
	} else
	    ++gap;

	if (dptr == start || gap > FIT_GAP_THRESHOLD)
	    break;
    }
    return (last);
}

Ddlist *fit2_findend(Ddlist * pos, Ddlist * end, Vec2 v, Vec2 c, double thres)
{
    Ddlist *last;
    Ddlist *dptr;
    int     gap = 0;

    if (end == NULL || pos == NULL)
	return (pos);

    for (last = dptr = pos;; dptr = dptr->next)
    {
	Vec2    p = {Vec2_id};

	DD_GET_POS2(dptr, p);
	if (!fit2_point_on_line(p, v, c, thres * 2))
	    break;
	if (fit2_point_on_line(p, v, c, thres))
	{
	    gap = 0;
	    last = dptr;
	} else
	    ++gap;

	if (dptr == end || gap > FIT_GAP_THRESHOLD)
	    break;
    }
    return (last);
}

Bool    fit2_regres(Ddlist * start, Ddlist * end, Vec2 * v, Vec2 * c, double *residual)
{
    Ddlist *dptr;
    int     n;
    double  cx, cy, x2, y2, xy;

    cx = 0;
    cy = 0;
    x2 = 0;
    y2 = 0;
    xy = 0;
    for (n = 0, dptr = start;; dptr = dptr->next)
    {
	Vec2    p = {Vec2_id};
	float   x, y;

	DD_GET_POS2(dptr, p);
	x = vec2_x(p);
	y = vec2_y(p);

	cx += x;
	cy += y;
	x2 += x * x;
	y2 += y * y;
	xy += x * y;
	++n;
	if (dptr == end)
	    break;
    }

    if (n < 3)
	return (false);

    cx /= n;
    cy /= n;
    x2 /= n;
    x2 -= cx * cx;
    y2 /= n;
    y2 -= cy * cy;
    xy /= n;
    xy -= cx * cy;

    if (fabs(xy) < 0.0001)
	*v = (x2 > y2) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);
    else
    {
	double  lam1, lam2;
	double  flam1, flam2;
	double  b, root;

	b = x2 + y2;
	root = sqrt(b * b - 4 * (x2 * y2 - xy * xy));
	flam1 = fabs(lam1 = (b + root) / 2);
	flam2 = fabs(lam2 = (b - root) / 2);
	if (flam1 < flam2)
	{
	    *residual = flam1;
	    *v = vec2_unit(vec2(1.0, -(x2 - lam2) / xy));
	} else
	{
	    *residual = flam2;
	    *v = vec2_unit(vec2(1.0, -(x2 - lam1) / xy));
	}
    }
    *c = vec2(cx, cy);

    return (true);
}

Bool    fit2_regres_it(Ddlist * start, Ddlist * end, Vec2 * v, Vec2 * c, double *residual, double thres)
{
    Ddlist *dptr;
    int     n, nthres;
    Bool    outliers;
    double  cx, cy, x2, y2, xy;
    double  CX, CY, X2, Y2, XY;

    thres *= thres;		/* save computation: check against perp
				 * squared */
    CX = 0;
    CY = 0;
    X2 = 0;
    Y2 = 0;
    XY = 0;
    for (n = 0, dptr = start;; dptr = dptr->next)
    {
	Vec2    p = {Vec2_id};
	float   x, y;

	DD_GET_POS2(dptr, p);
	x = vec2_x(p);
	y = vec2_y(p);

	CX += x;
	CY += y;
	X2 += x * x;
	Y2 += y * y;
	XY += x * y;
	++n;
	if (dptr == end)
	    break;
    }

    if (n < 5)
	return (false);
    nthres = MAX(n / 2, 5);

    do
    {
	Ddlist *maxptr = NULL;
	double  maxperpsqr = 0;

	outliers = false;
	cx = CX / n;
	cy = CY / n;
	x2 = X2 / n;
	x2 -= cx * cx;
	y2 = Y2 / n;
	y2 -= cy * cy;
	xy = XY / n;
	xy -= cx * cy;
	if (fabs(xy) < 0.0001)
	    *v = (x2 > y2) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);
	else
	{
	    double  lam1, lam2;
	    double  flam1, flam2;
	    double  b, root;

	    b = x2 + y2;
	    root = sqrt(b * b - 4 * (x2 * y2 - xy * xy));
	    flam1 = fabs(lam1 = (b + root) / 2);
	    flam2 = fabs(lam2 = (b - root) / 2);
	    if (flam1 < flam2)
	    {
		*residual = flam1;
		*v = vec2_unit(vec2(1.0, -(x2 - lam2) / xy));
	    } else
	    {
		*residual = flam2;
		*v = vec2_unit(vec2(1.0, -(x2 - lam1) / xy));
	    }
	}
	*c = vec2(cx, cy);

	for (dptr = start;; dptr = dptr->next)
	{
	    Vec2    p = {Vec2_id};
	    Vec2    d = {Vec2_id};
	    float   dp, perpsqr;

	    if (dptr->type < IGNORE_ME)
	    {
		DD_GET_POS2(dptr, p);
		d = vec2_diff(p, *c);
		dp = (float) vec2_dot(*v, d);
		d = vec2_diff(d, vec2_times(dp, *v));
		perpsqr = (float) vec2_sqrmod(d);
		if (maxptr == NULL || perpsqr > maxperpsqr)
		{
		    maxptr = dptr;
		    maxperpsqr = perpsqr;
		}
	    }
	    if (dptr == end)
		break;
	}

	if (maxperpsqr > thres)
	{
	    Vec2    p = {Vec2_id};
	    float   x, y;

	    outliers = true;
	    DD_GET_POS2(maxptr, p);
	    x = vec2_x(p);
	    y = vec2_y(p);
	    CX -= x;
	    CY -= y;
	    X2 -= x * x;
	    Y2 -= y * y;
	    XY -= x * y;
	    --n;
	    maxptr->type += IGNORE_ME;
	}
    }
    while (outliers == true && n >= nthres);

    for (dptr = start;; dptr = dptr->next)
    {
	if (dptr->type >= IGNORE_ME)
	    dptr->type -= IGNORE_ME;
	if (dptr == end)
	    break;
    }

    return ((n < nthres) ? false : true);
}

Line2  *line2_fit(Ddlist * start, Ddlist * end)	/* permits POS2 strings */

{
    Vec2    p1 = {Vec2_id};
    Vec2    p2 = {Vec2_id};
    Vec2    v = {Vec2_id};
    Vec2    c = {Vec2_id};
    Line2  *line;
    Line2  *line2_make();
    Tstring *string;
    double  residual;

    if (start == NULL || end == NULL || start == end)
	return (NULL);

    DD_GET_POS2(start, p1);
    DD_GET_POS2(end, p2);

    if (fit2_regres(start, end, &v, &c, &residual) == false)
	return (NULL);

    p1 = vec2_sum(c, vec2_times(vec2_dot(vec2_diff(p1, c), v), v));
    p2 = vec2_sum(c, vec2_times(vec2_dot(vec2_diff(p2, c), v), v));

    line = line2_make(p1, p2, LINE_REG_FIT);
    string = str_make(STRING, start, end);
    line->props = proplist_add(line->props, (void *) string, STRING, str_rm_only_str);
    return (line);
}

Line2  *line2_best_fit(Ddlist * start, Ddlist * end, double thres)	/* permits Edgel and
									 * Vec2 strings */

/* orthogonal fit threshold */
{
    Vec2    p1 = {Vec2_id};
    Vec2    p2 = {Vec2_id};
    Vec2    v = {Vec2_id};
    Vec2    c = {Vec2_id};
    Line2  *line;
    Line2  *line2_make();
    Ddlist *dptr;
    Tstring *string;
    double  residual;

    if (start == NULL || end == NULL || start == end)
	return (NULL);

    if (fit2_regres(start, end, &v, &c, &residual) == false)
	return (NULL);

    if (fit2_points_off_line(start, end, v, c, thres))
	if (fit2_regres_it(start, end, &v, &c, &residual, thres) == false)
	    return (NULL);

    for (dptr = start; dptr != end; dptr = dptr->next)
    {
	DD_GET_POS2(dptr, p1);
	if (fit2_point_on_line(p1, v, c, thres) == true)
	{
	    p1 = vec2_sum(c, vec2_times(vec2_dot(vec2_diff(p1, c), v), v));
	    break;
	}
    }
    start = dptr;		/* new start position */

    for (dptr = end; dptr != start; dptr = dptr->last)
    {
	DD_GET_POS2(dptr, p2);
	if (fit2_point_on_line(p2, v, c, thres) == true)
	{
	    p2 = vec2_sum(c, vec2_times(vec2_dot(vec2_diff(p2, c), v), v));
	    break;
	}
    }
    end = dptr;

    if (start == end || vec2_mod(vec2_diff(p2, p1)) == 0.0)
	return (NULL);

    line = line2_make(p1, p2, LINE_REG_FIT);
    string = str_make(STRING, start, end);
    line->props = proplist_add(line->props, (void *) string, STRING, str_rm_only_str);
    return (line);
}

Line2  *line2_fit_and_grow(Ddlist ** pos1ptr, Ddlist ** pos2ptr, Ddlist * start, Ddlist * end, double thres)
/* initial region for fitting */


{
    Ddlist *pos1_last;
    Ddlist *pos2_last;
    Ddlist *pos1;
    Ddlist *pos2;
    Line2  *line;
    Line2  *line2_make();
    Tstring *string;
    double  residual;
    Vec2    p1 = {Vec2_id};
    Vec2    p2 = {Vec2_id};
    Vec2    v = {Vec2_id};
    Vec2    c = {Vec2_id};

    if (start == NULL || end == NULL || start == end)
	return (NULL);

    if (pos1ptr == NULL || pos2ptr == NULL || *pos1ptr == NULL || *pos2ptr == NULL)
	return (NULL);

    pos1 = *pos1ptr;
    pos2 = *pos2ptr;

    do
    {
	pos1_last = pos1;
	pos2_last = pos2;

	if (fit2_regres(pos1, pos2, &v, &c, &residual) == false)
	    return (NULL);

	pos1 = fit2_findstart(pos1, start, v, c, thres);
	pos2 = fit2_findend(pos2, end, v, c, thres);
    }
    while (pos1 != pos1_last || pos2 != pos2_last);

    *pos1ptr = pos1;
    *pos2ptr = pos2;
    DD_GET_POS2(pos1, p1);
    DD_GET_POS2(pos2, p2);
    p1 = vec2_sum(c, vec2_times(vec2_dot(vec2_diff(p1, c), v), v));
    p2 = vec2_sum(c, vec2_times(vec2_dot(vec2_diff(p2, c), v), v));
    line = line2_make(p1, p2, LINE_REG_FIT);
    string = str_make(STRING, pos1, pos2);
    line->props = proplist_add(line->props, (void *) string, STRING, str_rm_only_str);
    return (line);
}

Line2  *line2_between(Ddlist * start, Ddlist * end)
{
    Vec2    p1 = {Vec2_id};
    Vec2    p2 = {Vec2_id};
    Line2  *line;
    Line2  *line2_make();
    Tstring *string;

    if (start == NULL || end == NULL || start == end)
	return (NULL);

    DD_GET_POS2(start, p1);
    DD_GET_POS2(end, p2);
    line = line2_make(p1, p2, LINE_NO_FIT);
    string = str_make(STRING, start, end);
    line->props = proplist_add(line->props, (void *) string, STRING, str_rm_only_str);
    return (line);
}
