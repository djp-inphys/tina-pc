/**@(#)2D geometry
**/

#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

/***
Notation:
q - point position
l - point on line,  v - unit direction of line
p - point on plane, n - unit normal to plane
***/

Vec2    vec2_midpoint(Vec2 q1, Vec2 q2)
{
    Vec2    midpoint = {Vec2_id};

    vec2_x(midpoint) = (float)0.5 * (vec2_x(q1) + vec2_x(q2));
    vec2_y(midpoint) = (float)0.5 * (vec2_y(q1) + vec2_y(q2));
    return (midpoint);
}

Vec2    vec2_projperp(Vec2 u, Vec2 v)	/**part of  u  perpendicular to unit  v**/

{
    return (vec2_diff(u, vec2_times(vec2_dot(u, v), v)));
}

Vec2    vec2_projpar(Vec2 u, Vec2 v)	/**part of  u  parallel to unit  v**/

{
    return (vec2_times(vec2_dot(u, v), v));
}

Vec2    vec2_proj_on_line(Vec2 q, Vec2 l, Vec2 v)
{
    Vec2    lq = {Vec2_id};

    lq = vec2_diff(q, l);
    return (vec2_sum(l, vec2_times(vec2_dot(lq, v), v)));
}

Vec2    vec2_inter_lines(Vec2 l1, Vec2 v1, Vec2 l2, Vec2 v2)
{
    double  c = vec2_cross(v1, v2), t1;

    if (c == 0.0)
	return (vec2_midpoint(l1, l2));
    t1 = vec2_cross(vec2_diff(l2, l1), v2) / c;
    return (vec2_sum(l1, vec2_times(t1, v1)));
}

void    vec2_join_2_points(Vec2 q1, Vec2 q2, Vec2 * l, Vec2 * v)
{
    *l = vec2_times(0.5, vec2_sum(q1, q2));
    *v = vec2_unit(vec2_diff(q2, q1));
}

double  vec2_dist_point_line(Vec2 q, Vec2 l, Vec2 v)
{
    Vec2    dq = {Vec2_id};

    dq = vec2_projperp(vec2_diff(q, l), v);
    return (vec2_mod(dq));
}

void    vec2_circ_3_points(Vec2 p1, Vec2 p2, Vec2 p3, Vec2 * centre, double *radius)
{
    Vec2    a = {Vec2_id};
    Vec2    b = {Vec2_id};
    double  a2, b2, ab, u, v, w;

    a = vec2_diff(p2, p1);
    b = vec2_diff(p3, p1);

    a2 = vec2_sqrmod(a);
    b2 = vec2_sqrmod(b);
    ab = vec2_dot(a, b);

    u = b2 * (a2 - ab);
    v = a2 * (b2 - ab);
    w = 2.0 * (a2 * b2 - ab * ab);

    a = vec2_times(u, a);
    b = vec2_times(v, b);

    *centre = vec2_sum(p1, vec2_times(1 / w, vec2_sum(a, b)));
    *radius = sqrt((a2 * b2 * (a2 + b2 - 2.0 * ab)) / (2.0 * w));
}

Vec2   *vec2_inter_par_test(Vec2 p, Vec2 v1, Vec2 q, Vec2 v2, double parallel)
{
    Vec2    cp = {Vec2_id};
    Vec2    b = {Vec2_id};
    Vec2   *isct;
    double  a;

    cp = vec2_inter_lines(p, v1, q, v2);
    if (!vec2_parallel(v1, v2, parallel))
    {
	cp.el[0] = -v2.el[1];
	cp.el[1] = v2.el[0];

	a = vec2_dot(cp, vec2_diff(p, q)) / vec2_dot(cp, v1);
	b = vec2_times(a, v1);

	isct = vec2_alloc();
	isct->el[0] = p.el[0] - b.el[0];
	isct->el[1] = p.el[1] - b.el[1];
	return (isct);
    } else
	return (NULL);
}
