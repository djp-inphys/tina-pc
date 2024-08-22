/**@(#)Interpolation Cubic Spline. Functions converted from Numeric
 * @(#)Recipies to perform 1d cubic spline interpolation
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>

void    spl_ci_gen(float *x, float *y, int n, double *ypf, double *ypl, float *y2)
{
    int     i, k;
    float   p, qn, sig, un, *u;

    u = fvector_alloc(0, n - 1);/* intermediate values */

    if (ypf == NULL)		/* natural splines: 0 second derivative
				 * at ends */
	y2[0] = u[0] = 0.0;
    else
    {
	y2[0] = -0.5;
	u[0] = (3.0 / (x[1] - x[0])) * ((y[1] - y[0]) / (x[1] - x[0]) - *ypf);
    }

    for (i = 1; i <= n - 2; i++)
    {
	sig = (x[i] - x[i - 1]) / (x[i + 1] - x[i - 1]);
	p = sig * y2[i - 1] + 2.0;
	y2[i] = (sig - 1.0) / p;
	u[i] = (y[i + 1] - y[i]) / (x[i + 1] - x[i]) - (y[i] - y[i - 1]) / (x[i] - x[i - 1]);
	u[i] = (6.0 * u[i] / (x[i + 1] - x[i - 1]) - sig * u[i - 1]) / p;
    }

    if (ypl == NULL)
	qn = un = 0.0;
    else
    {
	qn = 0.5;
	un = (3.0 / (x[n - 1] - x[n - 2])) * (*ypl - (y[n - 1] - y[n - 2]) / (x[n - 1] - x[n - 2]));
    }
    y2[n - 1] = (un - qn * u[n - 2]) / (qn * y2[n - 2] + 1.0);

    for (k = n - 2; k >= 0; k--)
	y2[k] = y2[k] * y2[k + 1] + u[k];

    fvector_free((void *) u, 0);
}

/* ARGSUSED Quieten Lint */
void    spl_ci_sbp(float *x, float *y, int n, double *ypf, double *ypl, float *y2)
{
    int     i;
    float  *u, *g;

    u = fvector_alloc(0, n);	/* intermediate values */
    g = fvector_alloc(0, n);	/* intermediate values */

    u[0] = g[0] = 0.0;		/* start condition */

    for (i = 1; i <= n - 2; i++)
    {
	double  a, b, c, d, temp;

	a = x[i] - x[i - 1];
	b = (x[i + 1] - x[i - 1]) / 3;
	c = x[i + 1] - x[i];
	d = (y[i + 1] - y[i]) / c - (y[i] - y[i - 1]) / a;
	a /= 6;
	c /= 6;

	temp = b - a * g[i - 1];
	u[i] = (d - a * u[i - 1]) / temp;
	g[i] = c / temp;
    }

    u[n - 1] = g[n - 1] = 0.0;	/* end condition */

    y2[n - 1] = u[n - 1];
    for (i = n - 2; i >= 0; i--)
	y2[i] = u[i] + y2[i + 1] * g[i];

    fvector_free((void *) u, 0);
    fvector_free((void *) g, 0);
}

double  spl_ci_val(float *xa, float *ya, float *y2a, int n, double x)
{
    int     klo, khi, k;
    float   h, b, a, y;

    klo = 0;
    khi = n - 1;
    while (khi - klo > 1)
    {				/* binary search */
	k = (khi + klo) >> 1;	/* mid point */
	if (xa[k] > x)
	    khi = k;
	else
	    klo = k;
    }
    h = xa[khi] - xa[klo];	/* should be strictly increasing */
    if (h == 0.0)
    {
	error("spl_ci_val: non monotonic absisa", warning);
	return (0.0);
    }
    a = (xa[khi] - x) / h;
    b = (x - xa[klo]) / h;
    y = a * ya[klo] + b * ya[khi] + ((a * a * a - a) * y2a[klo] + (b * b * b - b) * y2a[khi]) * (h * h) / 6.0;
    return (y);
}
