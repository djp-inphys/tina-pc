/*
 *
 * cholesky.c
 *
 * Utilities for square root decomposition of a symmetric matrix.
 *
 */

#include <math.h>
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

/*
Cholesky decomposition of n by n matrix s (s = L Lt).
Overwrites L into lower triangle of s.
*/
Bool cholesky(int n, double **s)
{
    int i, j, k;

    for (k = 0; k < n; k++)
    {
	if (s[k][k] < 0.0)
	    return (false);
	if (s[k][k] < MINFLOAT)
	    s[k][k] = MINFLOAT;
	s[k][k] = sqrt(s[k][k]);
	for (i = k + 1; i < n; i++)
	{
	    s[i][k] /= s[k][k];
	    for (j = k + 1; j <= i; j++)
		s[i][j] -= s[i][k] * s[j][k];
	}
    }
    for(i = 0; i < n; i++)
	for(j = i+1; j < n; j++)
	    s[i][j] = 0.0;
    return (true);
}

void mat_cholesky(Mat *s)
{
    cholesky(s->n, s->el);
}

/*
Solves ly=x in place. l n by n lower triangular matrix. Solution
y overwrites x.
*/
void lower_solve(int n, double **l, double *x)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
	for (j = 0; j < i; j++)
	    x[i] -= l[i][j] * x[j];
	x[i] /= l[i][i];
    }
}

/*
Square root free Cholesky decomposition s = l d lt.
l lower triangular, d stored on diagonal of l.
*/
Bool cholesky_ldl(int n, double **s, double **l, double *d)
{
    int i, j, k;

    for(i = 0; i < n; i++)
    {
	for(j = 0; j <= i; j++)
	    l[i][j] = s[i][j];
	for(j = i+1; j < n; j++)
	    l[i][j] = 0;
    }
    for (k = 0; k < n; k++)
    {
	d[k] = l[k][k];
	l[k][k] = 1;
	for (i = k + 1; i < n; i++)
	{
	    l[i][k] /= d[k];
	    for (j = k + 1; j <= i; j++)
		l[i][j] -= d[k] * l[i][k] * l[j][k];
	}
    }
    return (true);
}

void mat_cholesky_ldl(Mat *s, Mat *l, Vec *d)
{
    cholesky_ldl(s->n, s->el, l->el, d->el);
}
