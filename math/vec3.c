/**@(#)Vector handling (allocation, additon etc)
**/

#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
static Vec3 vec3_0 = {Vec3_id};

Vec3   *vec3_alloc(void)
{
    Vec3   *v = ts_ralloc(Vec3);

    v->el[0] = 0.0;
    v->el[1] = 0.0;
    v->el[2] = 0.0;
    return (v);
}

Vec3   *vec3_make(Vec3 u)


/* float x, y, z; */
{
    Vec3   *v = ts_ralloc(Vec3);

    *v = u;
    return (v);
}

void    vec3_free(void *v)
{
    rfree((void *) v);
}

Vec3    vec3(double x, double y, double z)
{
    Vec3    v = {Vec3_id};

    v.el[0] = x;
    v.el[1] = y;
    v.el[2] = z;
    return (v);
}

Vec3    vec3_zero(void)
{
    return (vec3_0);
}

Vec3    vec3_ex(void)
{
    return (vec3(1.0, 0.0, 0.0));
}

Vec3    vec3_ey(void)
{
    return (vec3(0.0, 1.0, 0.0));
}

Vec3    vec3_ez(void)
{
    return (vec3(0.0, 0.0, 1.0));
}

void    vec3_comps(Vec3 v, float *x, float *y, float *z)
{
    *x = v.el[0];
    *y = v.el[1];
    *z = v.el[2];
}

double  vec3_get_x(Vec3 v)	/* function version of vec3_x macro */

{
    return (v.el[0]);
}

double  vec3_get_y(Vec3 v)	/* function version of vec3_y macro */

{
    return (v.el[1]);
}

double  vec3_get_z(Vec3 v)	/* function version of vec3_z macro */

{
    return (v.el[2]);
}

Vec3    vec3_sum(Vec3 v, Vec3 w)
{
    Vec3    sum = {Vec3_id};

    sum.el[0] = v.el[0] + w.el[0];
    sum.el[1] = v.el[1] + w.el[1];
    sum.el[2] = v.el[2] + w.el[2];
    return (sum);
}

Vec3    vec3_sum3(Vec3 u, Vec3 v, Vec3 w)
{
    Vec3    sum = {Vec3_id};

    sum.el[0] = u.el[0] + v.el[0] + w.el[0];
    sum.el[1] = u.el[1] + v.el[1] + w.el[1];
    sum.el[2] = u.el[2] + v.el[2] + w.el[2];
    return (sum);
}

Vec3    vec3_sum4(Vec3 u, Vec3 v, Vec3 w, Vec3 x)
{
    Vec3    sum = {Vec3_id};

    sum.el[0] = u.el[0] + v.el[0] + w.el[0] + x.el[0];
    sum.el[1] = u.el[1] + v.el[1] + w.el[1] + x.el[1];
    sum.el[2] = u.el[2] + v.el[2] + w.el[2] + x.el[2];
    return (sum);
}

Vec3    vec3_minus(Vec3 v)
{
    Vec3    minus = {Vec3_id};

    minus.el[0] = -v.el[0];
    minus.el[1] = -v.el[1];
    minus.el[2] = -v.el[2];
    return (minus);
}

Vec3    vec3_diff(Vec3 v, Vec3 w)
{
    Vec3    diff = {Vec3_id};

    diff.el[0] = v.el[0] - w.el[0];
    diff.el[1] = v.el[1] - w.el[1];
    diff.el[2] = v.el[2] - w.el[2];
    return (diff);
}

Vec3    vec3_times(double k, Vec3 v)
{
    Vec3    prod = {Vec3_id};

    prod.el[0] = k * v.el[0];
    prod.el[1] = k * v.el[1];
    prod.el[2] = k * v.el[2];
    return (prod);
}

Vec3    vec3_interp(double k, Vec3 v1, Vec3 v2)
{
    double  k1 = 1.0 - k;
    Vec3    interp = {Vec3_id};

    interp.el[0] = k1 * v1.el[0] + k * v2.el[0];
    interp.el[1] = k1 * v1.el[1] + k * v2.el[1];
    interp.el[2] = k1 * v1.el[2] + k * v2.el[2];
    return (interp);
}

double  vec3_dot(Vec3 v, Vec3 w)
{
    return (v.el[0] * w.el[0] + v.el[1] * w.el[1] + v.el[2] * w.el[2]);
}

Vec3    vec3_cross(Vec3 v, Vec3 w)
{
    Vec3    cross = {Vec3_id};

    cross.el[0] = v.el[1] * w.el[2] - v.el[2] * w.el[1];
    cross.el[1] = v.el[2] * w.el[0] - v.el[0] * w.el[2];
    cross.el[2] = v.el[0] * w.el[1] - v.el[1] * w.el[0];
    return (cross);
}

Vec3    vec3_unitcross(Vec3 v, Vec3 w)
{
    Vec3    cross = {Vec3_id};
    Vec3    e = {Vec3_id};

    cross.el[0] = v.el[1] * w.el[2] - v.el[2] * w.el[1];
    cross.el[1] = v.el[2] * w.el[0] - v.el[0] * w.el[2];
    cross.el[2] = v.el[0] * w.el[1] - v.el[1] * w.el[0];
    if (vec3_modunit(cross, &e) == 0.0)
	return (vec3_perp(v));
    return (e);
}

double  vec3_mod(Vec3 v)
{
    double  vx = v.el[0], vy = v.el[1], vz = v.el[2];

    return (sqrt(vx * vx + vy * vy + vz * vz));
}

double  vec3_sqrmod(Vec3 v)
{
    double  vx = v.el[0], vy = v.el[1], vz = v.el[2];

    return (vx * vx + vy * vy + vz * vz);
}

double  vec3_modunit(Vec3 v, Vec3 * e)
{
    double  vx = v.el[0], vy = v.el[1], vz = v.el[2];
    double  k, k1;

    k = sqrt(vx * vx + vy * vy + vz * vz);
    if (k == 0.0)
    {
	*e = vec3_ex();
	return (0.0);
    }
    k1 = 1.0 / k;
    *e = vec3(vx * k1, vy * k1, vz * k1);
    return (k);
}

Vec3    vec3_unit(Vec3 v)
{
    double  vx = v.el[0], vy = v.el[1], vz = v.el[2];
    double  k, k1;

    k = sqrt(vx * vx + vy * vy + vz * vz);
    if (k == 0.0)
	return (vec3_ex());
    k1 = 1.0 / k;
    return (vec3(vx * k1, vy * k1, vz * k1));
}

double  vec3_dist(Vec3 v, Vec3 w)
{
    double  dx = v.el[0] - w.el[0];
    double  dy = v.el[1] - w.el[1];
    double  dz = v.el[2] - w.el[2];

    return (sqrt(dx * dx + dy * dy + dz * dz));
}

double  vec3_sqrdist(Vec3 v, Vec3 w)
{
    double  dx = v.el[0] - w.el[0];
    double  dy = v.el[1] - w.el[1];
    double  dz = v.el[2] - w.el[2];

    return (dx * dx + dy * dy + dz * dz);
}

double  vec3_angle(Vec3 v, Vec3 w)
{
    v = vec3_unit(v);
    w = vec3_unit(w);
    return (atan2(vec3_mod(vec3_cross(v, w)), vec3_dot(v, w)));
}

Vec3    vec3_perp(Vec3 v)
{
    Vec3    e = {Vec3_id};

    v = vec3_unit(v);
    if (vec3_modunit(vec3_cross(vec3_ey(), v), &e) != 0.0)
	return (e);
    return (vec3_unitcross(vec3_ex(), v));
}

void    vec3_basis(Vec3 aim, Vec3 down, Vec3 * ex, Vec3 * ey, Vec3 * ez)
{
    Vec3    vec3_projperp();
    Vec3    v = {Vec3_id};
    double  mdown = vec3_mod(down);

    *ez = vec3_unit(aim);
    v = vec3_projperp(down, *ez);
    if (vec3_mod(v) / mdown < 0.01)
    {
	v = vec3_projperp(vec3_ey(), *ez);
	if (vec3_mod(v) < 0.01)
	    v = vec3_projperp(vec3_ex(), *ez);
    }
    *ey = vec3_unit(v);
    *ex = vec3_unitcross(*ey, *ez);
}

Vec3    vec3_read(FILE * fp)
{
    Vec3    v = {Vec3_id};

    if (fscanf(fp, "%f %f %f", &v.el[0], &v.el[1], &v.el[2]) == 3)
	return (v);

    error("vec3_read: error in read", non_fatal);
    return (vec3_zero());
}

void    vec3_print(FILE * fp, Vec3 v)
{
    (void) fprintf(fp, "%f %f %f ", v.el[0], v.el[1], v.el[2]);
}

void    vec3_pprint(FILE * fp, char *msg, Vec3 v)
{
    (void) fprintf(fp, "%s(%15.6f%15.6f%15.6f)\n",
		   msg, v.el[0], v.el[1], v.el[2]);
}

void    vec3_format(Vec3 v)
{
    format("%f %f %f\n", v.el[0], v.el[1], v.el[2]);
}

Vec3    vec3_rand_sphere(Vec3 c, double r)
{
    double  x, y, z, r2;

    do
    {
	x = rand_unif(-1.0, 1.0);
	y = rand_unif(-1.0, 1.0);
	z = rand_unif(-1.0, 1.0);
	r2 = x * x + y * y + z * z;
    } while (r2 > 1.0);
    r /= sqrt(r2);
    return (vec3_sum(c, vec3_times(r, vec3(x, y, z))));
}
