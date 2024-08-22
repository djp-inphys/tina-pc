/*
 *
 * mat_lu.c
 *
 * Routines using LU decoposition of square matrices.
 *
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

static void lu_decomp(int n, double **a, int *indx, double *d)
{
    int i, imax, j, k;
    double big, dum, sum, temp;
    double *v = tvector_alloc(0, n, double);
    double tiny = 1.0/MAXFLOAT;

    *d = 1.0;
    for (i = 0; i < n; i++)
    {
	big = 0.0;
	for (j = 0; j < n; j++)
	    if ((temp = fabs(a[i][j])) > big)
		big = temp;
	if (big == 0.0)
	    big = tiny;
	v[i] = 1.0 / big;
    }
    for (j = 0; j < n; j++)
    {
	for (i = 0; i < j; i++)
	{
	    sum = a[i][j];
	    for (k = 0; k < i; k++)
		sum -= a[i][k] * a[k][j];
	    a[i][j] = sum;
	}
	big = 0.0;
	for (i = j; i < n; i++)
	{
	    sum = a[i][j];
	    for (k = 0; k < j; k++)
		sum -= a[i][k] * a[k][j];
	    a[i][j] = sum;
	    if ((dum = v[i] * fabs(sum)) >= big)
	    {
		big = dum;
		imax = i;
	    }
	}
	if (j != imax)
	{
	    for (k = 0; k < n; k++)
	    {
		dum = a[imax][k];
		a[imax][k] = a[j][k];
		a[j][k] = dum;
	    }
	    *d = -(*d);
	    v[imax] = v[j];
	}
	indx[j] = imax;
	if (a[j][j] == 0.0)
	    a[j][j] = tiny;
	if (j != n - 1)
	{
	    dum = 1.0 / (a[j][j]);
	    for (i = j + 1; i < n; i++)
		a[i][j] *= dum;
	}
    }
    tvector_free(v, 0, double);
}

static void lu_backsub(int n, double **a, int *indx, double *b)
{
    int i, k = -1, ip, j;
    double sum;

    for (i = 0; i < n; i++)
    {
	ip = indx[i];
	sum = b[ip];
	b[ip] = b[i];
	if (k >= 0)
	    for (j = k; j <= i - 1; j++)
		sum -= a[i][j] * b[j];
	else if (sum)
	    k = i;
	b[i] = sum;
    }
    for (i = n - 1; i >= 0; i--)
    {
	sum = b[i];
	for (j = i + 1; j < n; j++)
	    sum -= a[i][j] * b[j];
	b[i] = sum / a[i][i];
    }
}

void mat_solve(Mat * a, Vec * y)
{
    double d;
    int n = a->n;
    int *index = tvector_alloc(0, n, int);
    if (a == NULL || y == NULL)
	return;
    lu_decomp(n, a->el, index, &d);
    lu_backsub(n, a->el, index, y->el);
    tvector_free(index, 0, int);
}

double mat_det(Mat *a)
{
    double det, d;
    int i, n = a->n;
    int *index = tvector_alloc(0, n, int);
    Mat *a1 = mat_make(a->m, a->n);

    mat_copy(a1, a);
    lu_decomp(n, a1->el, index, &d);
    for (det = 1, i = 0; i < n; i++)
	det *= a1->el[i][i];
    tvector_free(index, 0, int);
    mat_free(a1);
    return (det);
}
