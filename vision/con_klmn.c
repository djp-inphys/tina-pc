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
Bierman u-d form of scalar measurement filter
**/

#define N 5

/* Renamed from kalman by Julian to avoid compiler warning: 'kalman
 * static & extern' */
static double klmn(double *x, double (*u)[5], double *d, double z, double *h, double var)
{
    int     i, j;
    double  a[N], s[N], r[N], p[N], k[N], denom, sum, uij;

    for (i = 0; i < N; i++)
    {
	sum = 0.0;
	for (j = 0; j < i; j++)
	    sum += u[j][i] * h[j];
	r[i] = sum + h[i];
    }

    for (i = 0; i < N; i++)
    {
	z += h[i] * x[i];
	s[i] = d[i] * r[i];
    }

    a[0] = s[0] * r[0] + var;
    a[0] = s[0] * r[0] + var;
    d[0] *= var / a[0];
    k[0] = s[0];

    for (j = 1; j < N; j++)
    {
	a[j] = a[j - 1] + s[j] * r[j];
	d[j] *= a[j - 1] / a[j];
	k[j] = s[j];
	p[j] = -r[j] / a[j - 1];
	for (i = 0; i < j; i++)
	{
	    uij = u[i][j];
	    u[i][j] += k[i] * p[j];
	    k[i] += uij * s[j];
	}
    }

    denom = a[4];
    denom = 1.0 / denom;

    for (i = 0; i < N; i++)
	x[i] -= z * k[i] * denom;

    return (z * z * denom);
}

/**

naive least squares (var unused)
**/

double  conic_nlsq(Conic * conic, Conic_stat * stats, Vec2 p, double var)
{
    double  z, h[5];
    double  a, b, c, d, e, f;
    double  px = vec2_x(p), py = vec2_y(p);

    a = conic->a;
    b = conic->b;
    c = conic->c;
    d = conic->d;
    e = conic->e;
    f = conic->f;

    z = a * px * px + 2.0 * b * px * py + c * py * py +
	2.0 * d * px + 2.0 * e * py + f;
    h[0] = px * px - py * py;
    h[1] = 2.0 * px * py;
    h[2] = 2.0 * px;
    h[3] = 2.0 * py;
    h[4] = 1.0;
    var = 1.0;			/* var reset to unity */

    return (klmn(stats->x, stats->u, stats->d, z, h, var));
}

/**
extended kalman filter
**/

double  conic_ekf(Conic * conic, Conic_stat * stats, Vec2 p, double var)
{
    double  z, h[5];
    double  a, b, c, d, e, f;
    double  px = vec2_x(p), py = vec2_y(p);
    double  fx, fy;

    a = conic->a;
    b = conic->b;
    c = conic->c;
    d = conic->d;
    e = conic->e;
    f = conic->f;

    z = a * px * px + 2.0 * b * px * py + c * py * py +
	2.0 * d * px + 2.0 * e * py + f;
    h[0] = px * px - py * py;
    h[1] = 2.0 * px * py;
    h[2] = 2.0 * px;
    h[3] = 2.0 * py;
    h[4] = 1.0;
    fx = 2.0 * (a * px + b * py + d);
    fy = 2.0 * (b * px + c * py + e);
    var *= (fx * fx + fy * fy);

    return (klmn(stats->x, stats->u, stats->d, z, h, var));
}

/**
bias corrected kalman filter
**/

double  conic_bckf(Conic * conic, Conic_stat * stats, Vec2 p, double var)
{
    double  z, h[5];
    double  a, b, c, d, e, f;
    double  px = vec2_x(p), py = vec2_y(p);
    double  fx, fy, t;

    a = conic->a;
    b = conic->b;
    c = conic->c;
    d = conic->d;
    e = conic->e;
    f = conic->f;

    z = a * px * px + 2.0 * b * px * py + c * py * py +
	2.0 * d * px + 2.0 * e * py + f;
    fx = 2.0 * (a * px + b * py + d);
    fy = 2.0 * (b * px + c * py + e);
    var *= (fx * fx + fy * fy);
    t = 2.0 * z / (fx * fx + fy * fy);

    h[0] = px * px - py * py;
    h[1] = 2.0 * px * py;
    h[2] = 2.0 * px;
    h[3] = 2.0 * py;
    h[4] = 1.0;

    h[0] -= t * (px * fx - py * fy);
    h[1] -= t * (py * fx + px * fy);
    h[2] -= t * fx;
    h[3] -= t * fy;

    return (klmn(stats->x, stats->u, stats->d, z, h, var));
}
