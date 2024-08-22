/**@(#)3D geometry
**/

#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

/**
Notation:
q - point position
l - point on line,  v - unit direction of line
p - point on plane, n - unit normal to plane
*/

Vec3    vec3_midpoint(Vec3 q1, Vec3 q2)
{
    Vec3    midpoint = {Vec3_id};

    vec3_x(midpoint) = (float)0.5 * (vec3_x(q1) + vec3_x(q2));
    vec3_y(midpoint) = (float)0.5 * (vec3_y(q1) + vec3_y(q2));
    vec3_z(midpoint) = (float)0.5 * (vec3_z(q1) + vec3_z(q2));
    return (midpoint);
}

Vec3    vec3_projperp(Vec3 u, Vec3 v)	/**part of  u  perpendicular to unit  v**/

{
    return (vec3_diff(u, vec3_times(vec3_dot(u, v), v)));
}

Vec3    vec3_projpar(Vec3 u, Vec3 v)	/**part of  u  parallel to unit  v**/

{
    return (vec3_times(vec3_dot(u, v), v));
}

Vec3    vec3_proj_on_line(Vec3 q, Vec3 l, Vec3 v)
{
    Vec3    lq = {Vec3_id};

    lq = vec3_diff(q, l);
    return (vec3_sum(l, vec3_times(vec3_dot(lq, v), v)));
}

Vec3    vec3_proj_on_plane(Vec3 q, Vec3 p, Vec3 n)
{
    Vec3    qp = {Vec3_id};

    qp = vec3_diff(p, q);
    return (vec3_sum(q, vec3_times(vec3_dot(qp, n), n)));
}
/*
Vec3    vec3_proj_line_on_plane(Vec3 l1, Vec3 v1, Vec3 p, Vec3 n, Vec3 * l2, Vec3 * v2)
{
    *l2 = vec3_proj_on_plane(l1, p, n);
    *v2 = vec3_unit(vec3_projperp(v1, n));
}
*/
    /* BUG: function incomplete */

Vec3    vec3_closest_lines(Vec3 l1, Vec3 v1, Vec3 l2, Vec3 v2)
{
    double  d12 = vec3_dot(v1, v2);
    double  t1;

    if (d12 == 1.0)
	return (l1);
    t1 = vec3_dot(vec3_diff(l2, l1),
	      vec3_diff(v1, vec3_times(d12, v2))) / (1.0 - d12 * d12);
    return (vec3_sum(l1, vec3_times(t1, v1)));
}

Vec3    vec3_inter_lines(Vec3 l1, Vec3 v1, Vec3 l2, Vec3 v2)
{
    return (vec3_midpoint(vec3_closest_lines(l1, v1, l2, v2),
			  vec3_closest_lines(l2, v2, l1, v1)));
}

Vec3    vec3_inter_line_plane(Vec3 l, Vec3 v, Vec3 p, Vec3 n)
{
    double  vn = vec3_dot(v, n);
    double  t;

    if (vn == 0.0)
	return (vec3_proj_on_plane(l, p, n));
    t = vec3_dot(vec3_diff(p, l), n) / vn;
    return (vec3_sum(l, vec3_times(t, v)));
}

void    vec3_inter_planes(Vec3 p1, Vec3 n1, Vec3 p2, Vec3 n2, Vec3 * l, Vec3 * v)
{
    Vec3    n12 = {Vec3_id};
    Vec3    n21 = {Vec3_id};
    Vec3    p = {Vec3_id};
    Vec3    c = {Vec3_id};
    double  cc, s1, s2;

    c = vec3_cross(n1, n2);
    cc = vec3_modunit(c, v);
    cc *= cc;
    if (cc == 0.0)
    {
	*l = vec3_times(0.5, vec3_sum(p1, p2));
	*v = vec3_perp(n1);
	return;
    }
    p = vec3_midpoint(p1, p2);
    n12 = vec3_projperp(n1, n2);
    s1 = vec3_dot(vec3_diff(p1, p), n1) / cc;
    n21 = vec3_projperp(n2, n1);
    s2 = vec3_dot(vec3_diff(p2, p), n2) / cc;
    *l = vec3_sum3(p, vec3_times(s1, n12), vec3_times(s2, n21));
    *v = vec3_unit(c);
}

void    vec3_join_2_points(Vec3 q1, Vec3 q2, Vec3 * l, Vec3 * v)
{
    *l = vec3_times(0.5, vec3_sum(q1, q2));
    *v = vec3_unit(vec3_diff(q2, q1));
}

void    vec3_join_3_points(Vec3 q1, Vec3 q2, Vec3 q3, Vec3 * p, Vec3 * n)
{
    *p = vec3_times(1.0 / 3.0, vec3_sum3(q1, q2, q3));
    *n = vec3_unit(vec3_cross(vec3_diff(q3, q2), vec3_diff(q1, q2)));
}

void    vec3_join_point_line(Vec3 q, Vec3 l, Vec3 v, Vec3 * p, Vec3 * n)
{
    *p = vec3_midpoint(q, l);
    *n = vec3_unitcross(vec3_diff(q, l), v);
}

void    vec3_join_lines(Vec3 l1, Vec3 v1, Vec3 l2, Vec3 v2, Vec3 * p, Vec3 * n)
{
    double  a = vec3_dot(v1, v2);

    if (a < 0.7071)
    {
	*p = vec3_sum3(l1, l2, vec3_minus(vec3_inter_lines(l1, v1, l2, v2)));
	*n = vec3_unitcross(v1, v2);
    } else
    {
	*p = vec3_times(0.5, vec3_sum(l1, l2));
	*n = vec3_unitcross(v1, vec3_diff(l2, l1));
    }
}

double  vec3_dist_point_plane(Vec3 q, Vec3 p, Vec3 n)
{
    Vec3    dq = {Vec3_id};

    dq = vec3_projpar(vec3_diff(q, p), n);
    return (vec3_mod(dq));
}

double  vec3_dist_point_line(Vec3 q, Vec3 l, Vec3 v)
{
    Vec3    dq = {Vec3_id};

    dq = vec3_projperp(vec3_diff(q, l), v);
    return (vec3_mod(dq));
}

double  vec3_dist_lines(Vec3 l1, Vec3 v1, Vec3 l2, Vec3 v2)
{
    Vec3    n = {Vec3_id};

    if (vec3_modunit(vec3_cross(v1, v2), &n) == 0.0)
	return (vec3_mod(vec3_projperp(vec3_diff(l2, l1), v1)));
    else
	return (fabs(vec3_dot(n, vec3_diff(l2, l1))));
}

void    vec3_circ_3_points(Vec3 p1, Vec3 p2, Vec3 p3, Vec3 * centre, Vec3 * normal, double *radius)
{
    Vec3    a = {Vec3_id};
    Vec3    b = {Vec3_id};
    double  a2, b2, ab, u, v, w;

    a = vec3_diff(p2, p1);
    b = vec3_diff(p3, p1);
    *normal = vec3_unitcross(a, b);

    a2 = vec3_sqrmod(a);
    b2 = vec3_sqrmod(b);
    ab = vec3_dot(a, b);

    u = b2 * (a2 - ab);
    v = a2 * (b2 - ab);
    w = 2.0 * (a2 * b2 - ab * ab);

    a = vec3_times(u, a);
    b = vec3_times(v, b);

    *centre = vec3_sum(p1, vec3_times(1 / w, vec3_sum(a, b)));
    *normal = vec3_unitcross(a, b);
    *radius = sqrt((a2 * b2 * (a2 + b2 - 2.0 * ab)) / (2.0 * w));
}

/**
some geometry using thresholds
**/

Bool    vec3_collinear(Vec3 p1, Vec3 p2, Vec3 q1, Vec3 q2, double dotth1, double dotth2)
/* defines a line */


{
    float   sqrmod[4];
    float   maxmod;
    Vec3    vec[4] = {{Vec3_id}, {Vec3_id}, {Vec3_id}, {Vec3_id}};
    Vec3    maxv = {Vec3_id};
    Vec3    v1 = {Vec3_id};
    Vec3    v2 = {Vec3_id};
    int     maxi, i;

    v1 = vec3_unit(vec3_diff(p2, p1));
    v2 = vec3_unit(vec3_diff(q2, q1));

    vec[0] = vec3_diff(p1, q1);
    sqrmod[0] = vec3_sqrmod(vec[0]);
    vec[1] = vec3_diff(p1, q2);
    sqrmod[1] = vec3_sqrmod(vec[1]);
    vec[2] = vec3_diff(p2, q1);
    sqrmod[2] = vec3_sqrmod(vec[2]);
    vec[3] = vec3_diff(p2, q2);
    sqrmod[3] = vec3_sqrmod(vec[3]);

    maxmod = sqrmod[0];
    maxi = 0;
    for (i = 1; i < 4; ++i)
	if (sqrmod[i] > maxmod)
	{
	    maxmod = sqrmod[i];
	    maxi = i;
	}
    maxv = vec3_times(1 / sqrt(maxmod), vec[maxi]);
    return (Bool) (fabs(vec3_dot(v1, maxv)) > dotth1 && fabs(vec3_dot(v2, maxv)) > dotth2);
}

double  vec3_closest_app(Vec3 p1, Vec3 v1, Vec3 p2, Vec3 v2, Vec3 * c1, Vec3 * c2)


/* closest points respectively */
{
    Vec3    cross = {Vec3_id};
    Vec3    diff = {Vec3_id};
    float   dp, crossmagsq;
    float   l1, l2;

    if (c1 == NULL || c2 == NULL)
	return (0.0);

    diff = vec3_diff(p1, p2);
    cross = vec3_cross(v1, v2);

    dp = vec3_dot(diff, cross);

    crossmagsq = vec3_sqrmod(cross);
    diff = vec3_diff(diff, vec3_times(dp / crossmagsq, cross));
    l1 = -vec3_dot(cross, vec3_cross(diff, v2)) / crossmagsq;
    l2 = vec3_dot(cross, vec3_cross(v1, diff)) / crossmagsq;

    *c1 = vec3_sum(p1, vec3_times(l1, v1));
    *c2 = vec3_sum(p2, vec3_times(l2, v2));
    return (dp / sqrt(crossmagsq));
}

Bool    vec3_parallel(Vec3 v1, Vec3 v2, double dotthres)
{
    return (Bool) (fabs(vec3_dot(v1, v2)) > dotthres);
}
