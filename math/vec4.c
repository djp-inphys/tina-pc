/**@(#)Vector handling (allocation, addition etc)
**/

#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

static Vec4 vec4_0 = {Vec4_id};

Vec4   *vec4_alloc(void)
{
    Vec4   *v = ts_ralloc(Vec4);

    v->el[0] = 0.0;
    v->el[1] = 0.0;
    v->el[2] = 0.0;
    v->el[3] = 0.0;
    return (v);
}

Vec4   *vec4_make(Vec4 u)
{
    Vec4   *v = ts_ralloc(Vec4);

    *v = u;
    return (v);
}

void    vec4_free(void *v)
{
    rfree((void *) v);
}

Vec4    vec4(double x, double y, double z, double w)
{
    Vec4    v = {Vec4_id};

    v.el[0] = x;
    v.el[1] = y;
    v.el[2] = z;
    v.el[3] = w;
    return (v);
}

Vec4    vec4_zero(void)
{
    return (vec4_0);
}

Vec4    vec4_ex(void)
{
    return (vec4(1.0, 0.0, 0.0, 0.0));
}

Vec4    vec4_ey(void)
{
    return (vec4(0.0, 1.0, 0.0, 0.0));
}

Vec4    vec4_ez(void)
{
    return (vec4(0.0, 0.0, 1.0, 0.0));
}

Vec4    vec4_ew(void)
{
    return (vec4(0.0, 0.0, 0.0, 1.0));
}

void    vec4_comps(Vec4 v, float *x, float *y, float *z, float *w)
{
    *x = v.el[0];
    *y = v.el[1];
    *z = v.el[2];
    *w = v.el[3];
}

double  vec4_get_x(Vec4 v)	/* function version of vec4_x macro */

{
    return (v.el[0]);
}

double  vec4_get_y(Vec4 v)	/* function version of vec4_y macro */

{
    return (v.el[1]);
}

double  vec4_get_z(Vec4 v)	/* function version of vec4_z macro */

{
    return (v.el[2]);
}

double  vec4_get_w(Vec4 v)	/* function version of vec4_w macro */

{
    return (v.el[3]);
}

Vec4    vec4_sum(Vec4 v, Vec4 w)
{
    Vec4    sum = {Vec4_id};

    sum.el[0] = v.el[0] + w.el[0];
    sum.el[1] = v.el[1] + w.el[1];
    sum.el[2] = v.el[2] + w.el[2];
    sum.el[3] = v.el[3] + w.el[2];
    return (sum);
}

Vec4    vec4_sum3(Vec4 u, Vec4 v, Vec4 w)
{
    Vec4    sum = {Vec4_id};

    sum.el[0] = u.el[0] + v.el[0] + w.el[0];
    sum.el[1] = u.el[1] + v.el[1] + w.el[1];
    sum.el[2] = u.el[2] + v.el[2] + w.el[2];
    sum.el[3] = u.el[3] + v.el[3] + w.el[3];
    return (sum);
}

Vec4    vec4_sum4(Vec4 u, Vec4 v, Vec4 w, Vec4 x)
{
    Vec4    sum = {Vec4_id};

    sum.el[0] = u.el[0] + v.el[0] + w.el[0] + x.el[0];
    sum.el[1] = u.el[1] + v.el[1] + w.el[1] + x.el[1];
    sum.el[2] = u.el[2] + v.el[2] + w.el[2] + x.el[2];
    sum.el[3] = u.el[3] + v.el[3] + w.el[3] + x.el[3];
    return (sum);
}

Vec4    vec4_minus(Vec4 v)
{
    Vec4    minus = {Vec4_id};

    minus.el[0] = -v.el[0];
    minus.el[1] = -v.el[1];
    minus.el[2] = -v.el[2];
    minus.el[3] = -v.el[3];
    return (minus);
}

Vec4    vec4_diff(Vec4 v, Vec4 w)
{
    Vec4    diff = {Vec4_id};

    diff.el[0] = v.el[0] - w.el[0];
    diff.el[1] = v.el[1] - w.el[1];
    diff.el[2] = v.el[2] - w.el[2];
    diff.el[3] = v.el[3] - w.el[3];
    return (diff);
}

Vec4    vec4_times(double k, Vec4 v)
{
    Vec4    prod = {Vec4_id};

    prod.el[0] = k * v.el[0];
    prod.el[1] = k * v.el[1];
    prod.el[2] = k * v.el[2];
    prod.el[3] = k * v.el[3];
    return (prod);
}

Vec4    vec4_interp(double k, Vec4 v1, Vec4 v2)
{
    double  k1 = 1.0 - k;
    Vec4    interp = {Vec4_id};

    interp.el[0] = k1 * v1.el[0] + k * v2.el[0];
    interp.el[1] = k1 * v1.el[1] + k * v2.el[1];
    interp.el[2] = k1 * v1.el[2] + k * v2.el[2];
    interp.el[3] = k1 * v1.el[3] + k * v2.el[3];
    return (interp);
}

double  vec4_dot(Vec4 v, Vec4 w)
{
    return (v.el[0] * w.el[0] + v.el[1] * w.el[1]
	    + v.el[2] * w.el[2] + v.el[3] * w.el[3]);
}

/**
note:
in 4D cross product is an antisymmetric matrix
**/

Mat4    vec4_cross(Vec4 v, Vec4 w)
{
    Mat4    cross = {Mat4_id};
    int     i, j;

    for (i = 0; i < 4; i++)
	for (j = 0; j < 4; j++)
	    cross.el[i][j] = v.el[i] * w.el[j] - v.el[j] * w.el[i];
    return (cross);
}

double  vec4_mod(Vec4 v)
{
    double  vx = v.el[0], vy = v.el[1], vz = v.el[2], vw = v.el[3];

    return (sqrt(vx * vx + vy * vy + vz * vz + vw * vw));
}

double  vec4_sqrmod(Vec4 v)
{
    double  vx = v.el[0], vy = v.el[1], vz = v.el[2], vw = v.el[3];

    return (vx * vx + vy * vy + vz * vz + vw * vw);
}

double  vec4_modunit(Vec4 v, Vec4 * e)
{
    double  vx = v.el[0], vy = v.el[1], vz = v.el[2], vw = v.el[3];
    double  k, k1;

    k = sqrt(vx * vx + vy * vy + vz * vz + vw * vw);
    if (k == 0.0)
    {
	*e = vec4_ex();
	return (0.0);
    }
    k1 = 1.0 / k;
    *e = vec4(vx * k1, vy * k1, vz * k1, vw * k1);
    return (k);
}

Vec4    vec4_unit(Vec4 v)
{
    double  vx = v.el[0], vy = v.el[1], vz = v.el[2], vw = v.el[3];
    double  k, k1;

    k = sqrt(vx * vx + vy * vy + vz * vz + vw * vw);
    if (k == 0.0)
	return (vec4_ex());
    k1 = 1.0 / k;
    return (vec4(vx * k1, vy * k1, vz * k1, vw * k1));
}

double  vec4_dist(Vec4 v, Vec4 w)
{
    double  dx = v.el[0] - w.el[0];
    double  dy = v.el[1] - w.el[1];
    double  dz = v.el[2] - w.el[2];
    double  dw = v.el[3] - w.el[3];

    return (sqrt(dx * dx + dy * dy + dz * dz + dw * dw));
}

double  vec4_sqrdist(Vec4 v, Vec4 w)
{
    double  dx = v.el[0] - w.el[0];
    double  dy = v.el[1] - w.el[1];
    double  dz = v.el[2] - w.el[2];
    double  dw = v.el[3] - w.el[3];

    return (dx * dx + dy * dy + dz * dz + dw * dw);
}

double  vec4_angle(Vec4 v, Vec4 w)
{
    v = vec4_unit(v);
    w = vec4_unit(w);
    return (acos(vec4_dot(v, w)));
}

Vec4    vec4_read(FILE * fp)
{
    Vec4    v = {Vec4_id};

    if (fscanf(fp, "%f %f %f %f", &v.el[0], &v.el[1], &v.el[2], &v.el[3]) == 4)
	return (v);

    error("vec4_read: error in read", non_fatal);
    return (vec4_zero());
}

void    vec4_print(FILE * fp, Vec4 v)
{
    (void) fprintf(fp, "%f %f %f %f ", v.el[0], v.el[1], v.el[2], v.el[3]);
}

void    vec4_pprint(FILE * fp, char *msg, Vec4 v)
{
    (void) fprintf(fp, "%s(%15.6f%15.6f%15.6f%15.6f)\n",
		   msg, v.el[0], v.el[1], v.el[2], v.el[3]);
}

void    vec4_format(Vec4 v)
{
    format("%f %f %f %f\n", v.el[0], v.el[1], v.el[2], v.el[3]);
}
