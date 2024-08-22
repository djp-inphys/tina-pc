/**@(#)
**/
/**
* conic_5pt.c:
* recover coeffs of conic through 5pts by
* four line method
**/

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/**
coefficients of line  L = l0*x+l0*y+l2 = 0

through  (x0 y0)  and  (x1 y1)
**/
static void line_coeffs(double *line, Vec2 p1, Vec2 p2)
{
    line[0] = vec2_y(p2) - vec2_y(p1);
    line[1] = vec2_x(p1) - vec2_x(p2);
    line[2] = vec2_x(p2) * vec2_y(p1) - vec2_x(p1) * vec2_y(p2);
}

/**

coefficients of degenerate conic (pair of lines)
C = L0*L1
**/
static Conic *conic_from_2_lines(double *l0, double *l1)
{
    Conic  *conic = conic_alloc((int) NULL);

    conic->a = l0[0] * l1[0];
    conic->b = 0.5 * (l0[0] * l1[1] + l0[1] * l1[0]);
    conic->c = l0[1] * l1[1];
    conic->d = 0.5 * (l0[0] * l1[2] + l0[2] * l1[0]);
    conic->e = 0.5 * (l0[1] * l1[2] + l0[2] * l1[1]);
    conic->f = l0[2] * l1[2];
    return (conic);
}

/**
linear combination  C = t*C0+(1-t)*C1  of two conics
**/
static Conic *conic_combine(Conic * conic0, Conic * conic1, double t)
{
    Conic  *conic = conic_alloc((int) NULL);
    double  t1 = 1.0 - t;

    conic->a = t * conic0->a + t1 * conic1->a;
    conic->b = t * conic0->b + t1 * conic1->b;
    conic->c = t * conic0->c + t1 * conic1->c;
    conic->d = t * conic0->d + t1 * conic1->d;
    conic->e = t * conic0->e + t1 * conic1->e;
    conic->f = t * conic0->f + t1 * conic1->f;
    return (conic);
}

/**
returns circular conic through three points
**/
Conic  *conic_circ_3pt(Vec2 p1, Vec2 p2, Vec2 p3)
{
    double  r;
    Vec2    c = {Vec2_id};
    Conic  *conic;

    vec2_circ_3_points(p1, p2, p3, &c, &r);
    conic = conic_make(ELLIPSE, c, 0.0, r, r, 0.0, TWOPI, 0);
    conic_set_ends(conic, p1, p3, p2);
    return (conic);
}

/**
conic passing through  5  given points
calculated by the 4-line method
**/
Conic  *conic_5pt(Vec2 p1, Vec2 p2, Vec2 p3, Vec2 p4, Vec2 p5)
{
    Conic  *conic;
    Conic  *conic0;
    Conic  *conic1;
    double  l0[3], l1[3], l2[3], l3[3];

    line_coeffs(l0, p1, p2);
    line_coeffs(l1, p2, p3);
    line_coeffs(l2, p3, p4);
    line_coeffs(l3, p4, p1);
    conic0 = conic_from_2_lines(l0, l2);
    conic1 = conic_from_2_lines(l1, l3);
    conic = conic_combine(conic0, conic1, conic_lambda(conic0, conic1, p5));
    conic_free(conic0);
    conic_free(conic1);
    conic_setup(conic);
    return (conic);
}

/* Ellipse passing through  5  given points if it exists aspect ratio
 * is too small or 5pt fit is ellipse returns 3pt circle */
Conic  *conic_ellipse_5pt(Vec2 p1, Vec2 p2, Vec2 p3, Vec2 p4, Vec2 p5, double min_aratio)
{
    Conic  *conic = conic_5pt(p1, p2, p3, p4, p5);

    if (conic->type == HYPERBOLA || conic_aratio(conic) < min_aratio)
    {
	conic_free(conic);
	return (conic_circ_3pt(p1, p3, p5));
    } else
	return (conic);
}

/**
conic given 2  tangencies and one other point
**/
Conic  *conic_3pt(Vec2 p1, Vec2 v1, Vec2 p2, Vec2 v2, Vec2 p3)
{
    Conic  *conic;
    Conic  *conic0;
    Conic  *conic1;
    double  l0[3], l1[3], l2[3];

    line_coeffs(l0, p1, vec2_sum(p1, v1));
    line_coeffs(l1, p2, vec2_sum(p2, v2));
    line_coeffs(l2, p1, p2);
    conic0 = conic_from_2_lines(l0, l1);
    conic1 = conic_from_2_lines(l2, l2);
    conic = conic_combine(conic0, conic1, conic_lambda(conic0, conic1, p3));
    conic_free(conic0);
    conic_free(conic1);
    conic_setup(conic);
    return (conic);
}

/**
ellipse given 2  tangencies and one other point if it exists
aspect ratio is too small or 5pt fit is ellipse returns
3pt circle
**/
Conic  *conic_ellipse_3pt(Vec2 p1, Vec2 v1, Vec2 p2, Vec2 v2, Vec2 p3, double min_aratio)
{
    Conic  *conic = conic_3pt(p1, v1, p2, v2, p3);

    /** temporary change **/
    if (conic->type == HYPERBOLA || conic_aratio(conic) < min_aratio)
    {
	conic_free(conic);
	return (conic_circ_3pt(p1, p2, p3));
    } else
	return (conic);
}

/**
5 point  conic fit to dd string -
looks for well separated points
**/
Conic  *ddstr_conic_5pt(Ddlist * start, Ddlist * end)
{
    Ddlist *m1;
    Ddlist *m2;
    Ddlist *m3;
    Vec2    p0 = {Vec2_id};
    Vec2    p1 = {Vec2_id};
    Vec2    p2 = {Vec2_id};
    Vec2    p3 = {Vec2_id};
    Vec2    p4 = {Vec2_id};
    Conic  *conic;

    if (start == end)
	return (NULL);

    m2 = ddstr_mid_point(start, end);
    m1 = ddstr_mid_point(start, m2);
    m3 = ddstr_mid_point(m2, end);

    if (start == m1 || m1 == m2 || m2 == m3 || m3 == end)	/* not distinct points */
	return (NULL);

    DD_GET_POS2(start, p0);
    DD_GET_POS2(m1, p1);
    DD_GET_POS2(m2, p2);
    DD_GET_POS2(m3, p3);
    DD_GET_POS2(end, p4);

    if (vec2_mod(vec2_diff(p0, p4)) < vec2_mod(vec2_diff(p0, p1)))
	conic = ddstr_conic_5pt(m1, end);	/* end points too close */
    else
	conic = conic_5pt(p0, p1, p2, p3, p4);
    conic_set_ends(conic, p0, p4, p2);
    return (conic);
}

/* 5 point ellipse fit to point string - looks for well separated
 * points */
Conic  *ddstr_conic_ellipse_5pt(Ddlist * start, Ddlist * end, double min_aratio)
{
    Ddlist *m1;
    Ddlist *m2;
    Ddlist *m3;
    Vec2    p0 = {Vec2_id};
    Vec2    p1 = {Vec2_id};
    Vec2    p2 = {Vec2_id};
    Vec2    p3 = {Vec2_id};
    Vec2    p4 = {Vec2_id};
    Conic  *conic;

    if (start == end)
	return (NULL);

    m2 = ddstr_mid_point(start, end);
    m1 = ddstr_mid_point(start, m2);
    m3 = ddstr_mid_point(m2, end);

    if (start == m1 || m1 == m2 || m2 == m3 || m3 == end)	/* not distinct points */
	return (NULL);

    DD_GET_POS2(start, p0);
    DD_GET_POS2(m1, p1);
    DD_GET_POS2(m2, p2);
    DD_GET_POS2(m3, p3);
    DD_GET_POS2(end, p4);

    if (vec2_mod(vec2_diff(p0, p4)) < vec2_mod(vec2_diff(p0, p1)))
	conic = ddstr_conic_ellipse_5pt(m1, end, min_aratio);
    else
	conic = conic_ellipse_5pt(p0, p1, p2, p3, p4, min_aratio);
    conic_set_ends(conic, p0, p4, p2);
    return (conic);
}

/**
3 point circle fit to point string -
looks for well separated points
**/
Conic  *ddstr_conic_circ_3pt(Ddlist * start, Ddlist * end)
{
    Ddlist *mid;
    Vec2    p0 = {Vec2_id};
    Vec2    p1 = {Vec2_id};
    Vec2    p2 = {Vec2_id};
    Conic  *conic;

    if (start == end)
	return (NULL);

    mid = ddstr_mid_point(start, end);

    if (start == mid || mid == end)	/* not distinct points */
	return (NULL);

    DD_GET_POS2(start, p0);
    DD_GET_POS2(mid, p1);
    DD_GET_POS2(end, p2);

    if (vec2_mod(vec2_diff(p0, p2)) < vec2_mod(vec2_diff(p0, p1)) / 2)
	conic = ddstr_conic_circ_3pt(start, ddstr_mid_point(mid, end));
    else
	conic = conic_circ_3pt(p0, p1, p2);
    conic_set_ends(conic, p0, p2, p1);
    return (conic);
}

/** chooses same points on string as conic fitting **/

Bool    ddstr_5pts_choose(Ddlist * start, Ddlist * end, Vec2 * p)
{
    Ddlist *m1;
    Ddlist *m2;
    Ddlist *m3;

    if (start == end)
	return (false);

    m2 = ddstr_mid_point(start, end);
    m1 = ddstr_mid_point(start, m2);
    m3 = ddstr_mid_point(m2, end);

    if (start == m1 || m1 == m2 || m2 == m3 || m3 == end)
	/* not distinct points */
	return (false);

    DD_GET_POS2(start, p[0]);
    DD_GET_POS2(m1, p[1]);
    DD_GET_POS2(m2, p[2]);
    DD_GET_POS2(m3, p[3]);
    DD_GET_POS2(end, p[4]);

    if (vec2_mod(vec2_diff(p[0], p[4])) < vec2_mod(vec2_diff(p[0], p[1])))
	/* end points too close */
	return (ddstr_5pts_choose(m1, end, p));
    return (true);
}

double  line_error(Line2 * line, Vec2 p)
{
    return (vec2_cross(line->v, vec2_diff(p, line->p)));
}

void    line_errors_check(Line2 * line, double *sum1, double *sum2)
{
    Tstring *str;
    Ddlist *ptr;

    if (line == NULL)
	return;
    str = prop_get(line->props, STRING);
    if (str == NULL)
	return;

    for (ptr = str->start;; ptr = ptr->next)
    {
	double  e;
	Vec2    p = {Vec2_id};

	DD_GET_POS2(ptr, p);
	e = line_error(line, p);
	*sum1 += e;
	*sum2 += e * e;
	if (ptr == str->end)
	    break;
    }
    *sum1 /= str->count;
    *sum2 /= str->count;
}
