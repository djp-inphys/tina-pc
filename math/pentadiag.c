/**@(#)Solve cyclic pentadiagonal system [abcde]x = s;
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>

/**
solves cyclic pentadiagonal system [abcde]x = s;
 - puts answer in s
Originally written in Pascal, so index shift of 1.
**/

void    pentadiag(int n, double *a0, double *b0, double *c0, double *d0, double *e0, double *s0)
{
    int     i, i1, i2;
    int     n1 = n - 1, n2 = n - 2, n3 = n - 3, n4 = n - 4;
    double  v, g, h;
    double *a = a0 - 1, *b = b0 - 1, *c = c0 - 1, *d = d0 - 1;
    double *e = e0 - 1, *s = s0 - 1;

    g = a[2];
    a[2] = 0.0;
    h = 0.0;
    c[1] = 1.0 / c[1];

    for (i = 2; i <= n - 4; i++)
    {
	i1 = i - 1;
	i2 = i + 1;
	v = b[i] * c[i1];
	c[i] -= v * d[i1];
	d[i] -= v * e[i1];
	b[i] = g - v * b[i1];
	a[i] -= v * a[i1];
	s[i] -= v * s[i1];
	v = a[i2] * c[i1];
	b[i2] -= v * d[i1];
	c[i2] -= v * e[i1];
	a[i2] = -v * a[i1];
	g = -v * b[i1];
	s[i2] -= v * s[i1];
	v = e[n1] * c[i1];
	c[n1] -= v * a[i1];
	d[n1] -= v * b[i1];
	e[n1] = h - v * d[i1];
	h = -v * e[i1];
	s[n1] -= v * s[i1];
	v = d[n] * c[i1];
	d[n] = e[n] - v * d[i1];
	e[n] = -v * e[i1];
	b[n] -= v * a[i1];
	c[n] -= v * b[i1];
	s[n] -= v * s[i1];
	c[i] = 1.0 / c[i];
    }

    e[n3] += a[n3];
    a[n3] = g;
    a[n1] = a[n1] + h;
    i = n - 3;
    v = b[n3] * c[n4];
    c[n3] -= v * d[n4];
    s[n3] -= v * s[n4];
    d[n3] -= v * e[n4];
    e[n3] -= v * a[n4];
    a[n3] -= v * b[n4];
    v = a[n2] * c[n4];
    b[n2] -= v * d[n4];
    c[n2] -= v * e[n4];
    s[n2] -= v * s[n4];
    d[n2] -= v * a[n4];
    e[n2] -= v * b[n4];
    v = e[n1] * c[n4];
    a[n1] -= v * d[n4];
    b[n1] -= v * e[n4];
    s[n1] -= v * s[n4];
    c[n1] -= v * a[n4];
    d[n1] -= v * b[n4];
    v = d[n] * c[n4];
    e[n] -= v * d[n4];
    a[n] -= v * e[n4];
    b[n] -= v * a[n4];
    c[n] -= v * b[n4];
    s[n] -= v * s[n4];
    c[n3] = 1.0 / c[n3];
    i = n - 2;
    v = b[n2] * c[n3];
    c[n2] -= v * d[n3];
    s[n2] -= v * s[n3];
    d[n2] -= v * e[n3];
    e[n2] -= v * a[n3];
    v = a[n1] * c[n3];
    b[n1] -= v * d[n3];
    c[n1] -= v * e[n3];
    s[n1] -= v * s[n3];
    d[n1] -= v * a[n3];
    v = e[n] * c[n3];
    a[n] -= v * d[n3];
    b[n] -= v * e[n3];
    s[n] -= v * s[n3];
    c[n] -= v * a[n3];
    c[n2] = 1.0 / c[n2];
    i = n - 1;
    v = b[n1] * c[n2];
    c[n1] -= v * d[n2];
    s[n1] -= v * s[n2];
    d[n1] -= v * e[n2];
    v = a[n] * c[n2];
    b[n] -= v * d[n2];
    c[n] -= v * e[n2];
    s[n] -= v * s[n2];
    c[n1] = 1.0 / c[n1];
    i = n;
    v = b[n] * c[n1];
    c[n] -= v * d[n1];
    s[n] -= v * s[n1];
    c[n] = 1.0 / c[n];
    s[n] *= c[n];
    s[n1] = (s[n1] - d[n1] * s[n]) * c[n1];
    s[n2] = (s[n2] - d[n2] * s[n1] - e[n2] * s[n]) * c[n2];
    s[n3] = (s[n3] - d[n3] * s[n2] - e[n3] * s[n1] - a[n3] * s[n]) * c[n3];

    for (i = n - 4; i >= 1; i--)
	s[i] = (s[i] - d[i] * s[i + 1] - e[i] * s[i + 2] - a[i] * s[n1] - b[i] * s[n]) * c[i];
}

/**
Forms product of cyclic pentadiagonal matrix and vector:
[abcde]x = y
**/

void    pentaprod(int n, double *a, double *b, double *c, double *d, double *e, double *x, double *y)
{
    int     i, n1 = n - 1, n2 = n - 2, n3 = n - 3, n4 = n - 4;

    y[0] = c[0] * x[0] + d[0] * x[1] + e[0] * x[2] + a[0] * x[n2] + b[0] * x[n1];
    y[1] = b[1] * x[0] + c[1] * x[1] + d[1] * x[2] + e[1] * x[3] + a[1] * x[n1];
    for (i = 2; i < n2; i++)
	y[i] = a[i] * x[i - 2] + b[i] * x[i - 1] + c[i] * x[i] + d[i] * x[i + 1] + e[i] * x[i + 2];
    y[n2] = e[n2] * x[0] + a[n2] * x[n4] + b[n2] * x[n3] + c[n2] * x[n2] + d[n2] * x[n1];
    y[n1] = d[n1] * x[0] + e[n1] * x[1] + a[n1] * x[n3] + b[n1] * x[n2] + c[n1] * x[n1];
}

/** temporary solution of cyclic tridiagonal **/

void    triadiag(int n, double *b0, double *c0, double *d0, double *s0)
{
    double *a0 = dvector_alloc(0, n);
    double *e0 = dvector_alloc(0, n);

    pentadiag(n, a0, b0, c0, d0, e0, s0);
    dvector_free((void *) a0, 0);
    dvector_free((void *) e0, 0);
}
