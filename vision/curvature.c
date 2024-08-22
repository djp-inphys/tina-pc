/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

static double qspline_curvature(Vec2 p0, Vec2 p1, Vec2 p2)
{
    double  x0 = vec2_x(p0), x1 = vec2_x(p1), x2 = vec2_x(p2);
    double  y0 = vec2_y(p0), y1 = vec2_y(p1), y2 = vec2_y(p2);
    double  dx, dy, ddx, ddy, ds;

    dx = 0.5 * (x2 - x0);
    ddx = x2 - 2.0 * x1 + x0;
    dy = 0.5 * (y2 - y0);
    ddy = y2 - 2.0 * y1 + y0;

    ds = sqrt(dx * dx + dy * dy);
    return ((dx * ddy - dy * ddx) / (ds * ds * ds));
}

double  dds_curvature(Ddlist * s, int n)
{
    int     i;
    Ddlist *ptr0;
    Ddlist *ptr2;
    Vec2    p0 = {Vec2_id};
    Vec2    p1 = {Vec2_id};
    Vec2    p2 = {Vec2_id};

    /** try to go n points forward && back **/

    for (ptr0 = s, i = 0; ptr0->last != NULL && i < n; ptr0 = ptr0->last, i++)
	;
    for (ptr2 = s, i = 0; ptr2->next != NULL && i < n; ptr2 = ptr2->next, i++)
	;

    DD_GET_POS2(ptr0, p0);
    DD_GET_POS2(s, p1);
    DD_GET_POS2(ptr2, p2);

    return (qspline_curvature(p0, p1, p2));
}

double  es_curvature(Tstring * es, Ddlist * p, double arcratio, double arcmin, double arcmax)
/* edge type string */
/* point on the string at which to measure curvature */
/* try to achieve this ratio of arc length to radius */
/* min and max arc length to use */
{
    Ddlist *start = es->start;
    Ddlist *end = es->end;
    Ddlist *ptr1;
    Ddlist *ptr2;
    Ddlist *ptrm;
    Vec2    p1 = {Vec2_id};
    Vec2    p2 = {Vec2_id};
    Vec2    pm = {Vec2_id};
    double  arc, curvature;
    int     extend1, extend2;

    arc = arcmin;
    ptr1 = ptr2 = p;
    DD_GET_POS2(ptr1, p1);
    DD_GET_POS2(ptr2, p2);
    extend1 = (ptr1 == start) ? 0 : 1;
    extend2 = (ptr2 == end) ? 0 : 1;
    while (extend1 || extend2)
    {
	if (extend1)
	{
	    DD_GET_POS2(ptr1->last, p1);
	    if (vec2_dist(p1, p2) > arc)
		extend1 = 0;
	    else
		ptr1 = ptr1->last;
	    if (ptr1 == start)
		extend1 = 0;
	}
	if (extend2)
	{
	    DD_GET_POS2(ptr2->next, p2);
	    if (vec2_dist(p1, p2) > arc)
		extend2 = 0;
	    else
		ptr2 = ptr2->next;
	    if (ptr2 == end)
		extend2 = 0;
	}
	if (!extend1 && !extend2)
	{
	    double  arcnew;

	    ptrm = ddstr_mid_point(ptr1, ptr2);
	    if (ptr1 == ptrm || ptr2 == ptrm)
		return (0.0);
	    DD_GET_POS2(ptrm, pm);
	    curvature = qspline_curvature(p1, pm, p2);
	    arcnew = ((arcnew = arcratio / curvature) > arcmax) ? arcmax : arcnew;
	    if (arcnew > arc)
	    {
		arc = arcnew;
		if (ptr1 != start)
		    extend1 = 1;
		if (ptr2 != end)
		    extend2 = 1;
	    }
	}
    }
    return (curvature);
}

static double qspline_diffgeom(Vec2 p0, Vec2 p1, Vec2 p2, Vec2 * p, Vec2 * t, double *k)
{
    double  x0 = vec2_x(p0), x1 = vec2_x(p1), x2 = vec2_x(p2);
    double  y0 = vec2_y(p0), y1 = vec2_y(p1), y2 = vec2_y(p2);
    double  dx, dy, ddx, ddy, ds;

    dx = 0.5 * (x2 - x0);
    ddx = x2 - 2.0 * x1 + x0;
    dy = 0.5 * (y2 - y0);
    ddy = y2 - 2.0 * y1 + y0;

    ds = sqrt(dx * dx + dy * dy);
    *p = p1;
    *t = vec2(dx / ds, dy / ds);
    *k = (dx * ddy - dy * ddx) / (ds * ds * ds);
    return(ds);
}

double  dds_diffgeom(Ddlist * s, Vec2 * p, Vec2 * t, double *k, int n)
{
    int     i;
    Ddlist *ptr0;
    Ddlist *ptr2;
    Vec2    p0 = {Vec2_id};
    Vec2    p1 = {Vec2_id};
    Vec2    p2 = {Vec2_id};

    /** try to go n points forward && back **/

    for (ptr0 = s, i = 0; ptr0->last != NULL && i < n; ptr0 = ptr0->last, i++)
	;
    for (ptr2 = s, i = 0; ptr2->next != NULL && i < n; ptr2 = ptr2->next, i++)
	;
    DD_GET_POS2(ptr0, p0);
    DD_GET_POS2(s, p1);
    DD_GET_POS2(ptr2, p2);
    qspline_diffgeom(p0, p1, p2, p, t, k);
    /* BUG control reaches end of non-void function */
}

double  es_diffgeom(Tstring * es, Ddlist * p, double arcratio, double arcmin, double arcmax, Vec2 * pos, Vec2 * t, double *k)
/* edge type string */
/* point on the string at which to measure curvature */
/* try to achieve this ratio of arc length to radius */
/* min and max arc length to use */


{
    Ddlist *start = es->start;
    Ddlist *end = es->end;
    Ddlist *ptr1;
    Ddlist *ptr2;
    Ddlist *ptrm;
    Vec2    p1 = {Vec2_id};
    Vec2    p2 = {Vec2_id};
    Vec2    pm = {Vec2_id};
    double  arc, curvature;
    int     extend1, extend2;

    arc = arcmin;
    ptr1 = ptr2 = p;
    DD_GET_POS2(ptr1, p1);
    DD_GET_POS2(ptr2, p2);
    extend1 = (ptr1 == start) ? 0 : 1;
    extend2 = (ptr2 == end) ? 0 : 1;
    while (extend1 || extend2)
    {
	if (extend1)
	{
	    DD_GET_POS2(ptr1->last, p1);
	    if (vec2_dist(p1, p2) > arc)
		extend1 = 0;
	    else
		ptr1 = ptr1->last;
	    if (ptr1 == start)
		extend1 = 0;
	}
	if (extend2)
	{
	    DD_GET_POS2(ptr2->next, p2);
	    if (vec2_dist(p1, p2) > arc)
		extend2 = 0;
	    else
		ptr2 = ptr2->next;
	    if (ptr2 == end)
		extend2 = 0;
	}
	if (!extend1 && !extend2)
	{
	    double  arcnew;

	    ptrm = ddstr_mid_point(ptr1, ptr2);
	    DD_GET_POS2(ptrm, pm);
	    qspline_diffgeom(p1, pm, p2, pos, t, k);
	    curvature = *k;
	    arcnew = ((arcnew = arcratio / curvature) > arcmax) ? arcmax : arcnew;
	    if (arcnew > arc)
	    {
		arc = arcnew;
		if (ptr1 != start)
		    extend1 = 1;
		if (ptr2 != end)
		    extend2 = 1;
	    }
	}
    }
    /* BUG control reaches end of non-void function */
}

static Vec2 *str_pos2_to_array(Tstring * s, int *n)
{
    int     i, m;
    Vec2   *va;
    Ddlist *dd;

    if (s == NULL)
    {
	/* BUGFIX JB 22/11/93 was *n == -1; */
	*n = -1;
	return (NULL);
    }
    m = str_length(s);

    va = ts_nralloc(m, Vec2);
    for (dd = s->start, i = 0; i < m; dd = dd->next, i++)
	DD_GET_POS2(dd, va[i]);

    *n = m;
    return (va);
}

static void str_pos2_from_array(Tstring * s, Vec2 * va)
{
    Ddlist *dd;
    int     i;

    if (s == NULL || va == NULL)
	return;

    for (dd = s->start, i = 0;; dd = dd->next, i++)
    {
	DD_SET_POS2(dd, va[i]);
	if (dd == s->end)
	    break;
    }
}

Vec2    vec2_smooth(Vec2 v0, Vec2 v1, Vec2 v2)
{
    double  x0 = vec2_x(v0), y0 = vec2_y(v0);
    double  x1 = vec2_x(v1), y1 = vec2_y(v1);
    double  x2 = vec2_x(v2), y2 = vec2_y(v2);

    x1 = 0.25 * (x0 + 2.0 * x1 + x2);
    y1 = 0.25 * (y0 + 2.0 * y1 + y2);

    return (vec2(x1, y1));
}

void    loop_smooth(int l, Vec2 * array, Vec2 * store)
{
    int     i;

    store[0] = vec2_smooth(array[l - 1], array[0], array[1]);
    for (i = 1; i < l - 1; i++)
	store[i] = vec2_smooth(array[i - 1], array[i], array[i + 1]);
    store[l - 1] = vec2_smooth(array[l - 2], array[l - 1], array[0]);

    for (i = 0; i < l; i++)
	array[i] = store[i];
}

void    endfix_smooth(int l, Vec2 * array, Vec2 * store)
{
    int     i;

    for (i = 1; i < l - 1; i++)
	store[i] = vec2_smooth(array[i - 1], array[i], array[i + 1]);

    for (i = 1; i < l - 1; i++)
	array[i] = store[i];
}

void    str_smooth(Tstring * s, int n)
{
    Vec2   *array;
    Vec2   *store;
    int     i, l;

    array = str_pos2_to_array(s, &l);
    store = ts_nralloc(l, Vec2);

    for (i = 0; i < n; i++)
    {
	if (s->type == LOOP)
	    loop_smooth(l, array, store);
	else
	    endfix_smooth(l, array, store);
    }
    str_pos2_from_array(s, array);

    rfree((void *) array);
    rfree((void *) store);
}
