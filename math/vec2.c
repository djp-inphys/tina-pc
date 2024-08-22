/**@(#)Vector handling (allocation, additon etc)
**/

#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

static Vec2 vec2_0 = {Vec2_id};


/** for use with list utilities **/
Vec2   *vec2_alloc(void)
{
    Vec2   *v = ts_ralloc(Vec2);

    v->el[0] = 0.0;
    v->el[1] = 0.0;
    return (Vec2 *) ((void *) v);
}

/* Deep copy a vec2 (takes & returns POINTERS) */
Vec2   *vec2_copy(Vec2 * vec2)
{
    Vec2   *vec2_new = ts_ralloc(Vec2);

    *vec2_new = *vec2;
    return vec2_new;
}

Vec2   *vec2_make(Vec2 u)
{
    Vec2   *v = ts_ralloc(Vec2);

    *v = u;
    return (Vec2 *) ((void *) v);
}

void    vec2_free(void *v)
{
    rfree((void *) v);
}

Vec2    vec2(double x, double y)
{
    Vec2    v = {Vec2_id};

    v.el[0] = x;
    v.el[1] = y;
    return (v);
}

Vec2    vec2_zero(void)
{
    return (vec2_0);
}

Vec2    vec2_ex(void)
{
    return (vec2(1.0, 0.0));
}

Vec2    vec2_ey(void)
{
    return (vec2(0.0, 1.0));
}

void    vec2_comps(Vec2 v, float *x, float *y)
{
    *x = v.el[0];
    *y = v.el[1];
}

double  vec2_get_x(Vec2 * v)
{
    return (v->el[0]);
}

double  vec2_get_y(Vec2 * v)
{
    return (v->el[1]);
}

Vec2    vec2_sum(Vec2 v, Vec2 w)
{
    Vec2    sum = {Vec2_id};

    sum.el[0] = v.el[0] + w.el[0];
    sum.el[1] = v.el[1] + w.el[1];
    return (sum);
}

Vec2    vec2_sum3(Vec2 u, Vec2 v, Vec2 w)
{
    Vec2    sum = {Vec2_id};

    sum.el[0] = u.el[0] + v.el[0] + w.el[0];
    sum.el[1] = u.el[1] + v.el[1] + w.el[1];
    return (sum);
}

Vec2    vec2_sum4(Vec2 u, Vec2 v, Vec2 w, Vec2 x)
{
    Vec2    sum = {Vec2_id};

    sum.el[0] = u.el[0] + v.el[0] + w.el[0] + x.el[0];
    sum.el[1] = u.el[1] + v.el[1] + w.el[1] + x.el[1];
    return (sum);
}

Vec2    vec2_minus(Vec2 v)
{
    Vec2    minus = {Vec2_id};

    minus.el[0] = -v.el[0];
    minus.el[1] = -v.el[1];
    return (minus);
}

Vec2    vec2_diff(Vec2 v, Vec2 w)
{
    Vec2    diff = {Vec2_id};

    diff.el[0] = v.el[0] - w.el[0];
    diff.el[1] = v.el[1] - w.el[1];
    return (diff);
}

Vec2    vec2_times(double k, Vec2 v)
{
    Vec2    prod = {Vec2_id};

    prod.el[0] = k * v.el[0];
    prod.el[1] = k * v.el[1];
    return (prod);
}

Vec2    vec2_interp(double k, Vec2 v1, Vec2 v2)
{
    double  k1 = 1.0 - k;
    Vec2    interp = {Vec2_id};

    interp.el[0] = k1 * v1.el[0] + k * v2.el[0];
    interp.el[1] = k1 * v1.el[1] + k * v2.el[1];
    return (interp);
}

double  vec2_dot(Vec2 v, Vec2 w)
{
    return (v.el[0] * w.el[0] + v.el[1] * w.el[1]);
}

double  vec2_cross(Vec2 v, Vec2 w)
{
    return (v.el[0] * w.el[1] - v.el[1] * w.el[0]);
}

double  vec2_mod(Vec2 v)
{
    double  vx = v.el[0], vy = v.el[1];

    return (sqrt(vx * vx + vy * vy));
}

double  vec2_sqrmod(Vec2 v)
{
    double  vx = v.el[0], vy = v.el[1];

    return (vx * vx + vy * vy);
}

double  vec2_modunit(Vec2 v, Vec2 * e)
{
    double  vx = v.el[0], vy = v.el[1];
    double  k, k1;

    k = sqrt(vx * vx + vy * vy);
    if (k == 0.0)
    {
	*e = vec2_ex();
	return (0.0);
    }
    k1 = 1.0 / k;
    *e = vec2(vx * k1, vy * k1);
    return (k);
}

Vec2    vec2_unit(Vec2 v)
{
    double  vx = v.el[0], vy = v.el[1];
    double  k, k1;

    k = sqrt(vx * vx + vy * vy);
    if (k == 0.0)
	return (vec2_ex());
    k1 = 1.0 / k;
    return (vec2(vx * k1, vy * k1));
}

void    vec2_to_polar(Vec2 v, double *r, double *theta)
{
    double  x = vec2_x(v);
    double  y = vec2_y(v);

    *r = sqrt(x * x + y * y);
    *theta = atan2(y, x);
}

Vec2    vec2_of_polar(double r, double theta)
{
    return (vec2(r * cos(theta), r * sin(theta)));
}

Vec2    vec2_rand_circle(Vec2 centre, double radius)
{
    double  x, y, r;

    do
    {
	x = rand_unif(-1.0, 1.0);
	y = rand_unif(-1.0, 1.0);
    } while ((r = x * x + y * y) > 1.0);
    r = radius / sqrt(r);
    return (vec2_sum(centre, vec2(x / r, y / r)));
}

double  vec2_dist(Vec2 v, Vec2 w)
{
    double  dx = v.el[0] - w.el[0];
    double  dy = v.el[1] - w.el[1];

    return (sqrt(dx * dx + dy * dy));
}

double  vec2_sqrdist(Vec2 v, Vec2 w)
{
    double  dx = v.el[0] - w.el[0];
    double  dy = v.el[1] - w.el[1];

    return (dx * dx + dy * dy);
}

double  vec2_angle(Vec2 v, Vec2 w)
{
    return (atan2(vec2_cross(w, v), vec2_dot(w, v)));
}

Vec2    vec2_perp(Vec2 v)
{
    float   vx, vy;

    vec2_comps(v, &vx, &vy);
    return (vec2_unit(vec2(vy, -vx)));
}

double  vec2_perp_dist(Vec2 p, Vec2 v, Vec2 d)	/* length of
						 * perpendicular from d
						 * to (p,v) */

{
    Vec2    diff = {Vec2_id};

    diff = vec2_diff(d, p);
    return (vec2_mod(vec2_diff(diff, vec2_times(vec2_dot(diff, v), v))));
}

void    vec2_basis(Vec2 up, Vec2 * ex, Vec2 * ey)
{
    if (vec2_mod(up) == 0.0)
    {
	*ex = vec2_ex();
	*ey = vec2_ey();
	return;
    }
    *ey = vec2_unit(up);
    *ex = vec2_perp(*ey);
}

int     vec2_parallel(Vec2 v1, Vec2 v2, double dotthres)
{
    return (fabs(vec2_dot(v1, v2)) > dotthres);
}

Vec2    vec2_read(FILE * fp)
{
    Vec2    v = {Vec2_id};

    (void) fscanf(fp, "%f %f", &v.el[0], &v.el[1]);
    return (v);
}

void    vec2_print(FILE * fp, Vec2 v)
{
    (void) fprintf(fp, "%f %f ", v.el[0], v.el[1]);
}

void    vec2_pprint(FILE * fp, char *msg, Vec2 v)
{
    (void) fprintf(fp, "%s(%15.6f%15.6f)\n", msg, v.el[0], v.el[1]);
}

void    vec2_format(Vec2 v)
{
    format("%f %f\n", v.el[0], v.el[1]);
}

/* Functions useful for setting vec2 ranges for use with
 * tv_camera2_rect. SMC */

/* Return (as a Vec2) the LOWER LEFT corner of a box given by 2 vec2's */
Vec2    vec2_less(Vec2 v1, Vec2 v2)
{
    return (vec2(MIN(v1.el[0], v2.el[0]), (MIN(v1.el[1], v2.el[1]))));
}


/* Return (as a Vec2) the UPPER RIGHT corner of a box given by 2 vec2's */
Vec2    vec2_greater(Vec2 v1, Vec2 v2)
{
    return (vec2(MAX(v1.el[0], v2.el[0]), (MAX(v1.el[1], v2.el[1]))));
}

/* Ensure box (defined by v1 & v2)  includes vec (expanding box if
 * required) (v1 is the UPPER LEFT) (v2 is LOWER RIGHT). */
void    vec2_ranges(Vec2 * v1, Vec2 * v2, Vec2 vec)
{
    *v1 = vec2_less(*v1, vec);
    *v2 = vec2_greater(*v2, vec);
}
