/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

#define TINY 1.0e-20;

void    ludcmp(double **a, int n, int *indx, double *d)
{
    int     i, imax, j, k;	/* BUG `imax' may be used uninitialized
				 * in this function */
    double  big, dum, sum, temp;
    double *vv;

    vv = dvector_alloc(0, n);
    *d = 1.0;
    for (i = 0; i < n; i++)
    {
	big = 0.0;
	for (j = 0; j < n; j++)
	    if ((temp = fabs(a[i][j])) > big)
		big = temp;
	if (big == 0.0)
	    big = TINY;
	vv[i] = 1.0 / big;
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
	    if ((dum = vv[i] * fabs(sum)) >= big)
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
	    vv[imax] = vv[j];
	}
	indx[j] = imax;
	if (a[j][j] == 0.0)
	    a[j][j] = TINY;
	if (j != n - 1)
	{
	    dum = 1.0 / (a[j][j]);
	    for (i = j + 1; i < n; i++)
		a[i][j] *= dum;
	}
    }
    dvector_free((void *) vv, 0);
}

#undef TINY


void    lubksb(double **a, int n, int *indx, double *b)
{
    int     i, ii = -1, ip, j;
    double  sum;

    for (i = 0; i < n; i++)
    {
	ip = indx[i];
	sum = b[ip];
	b[ip] = b[i];
	if (ii >= 0)
	    for (j = ii; j <= i - 1; j++)
		sum -= a[i][j] * b[j];
	else if (sum)
	    ii = i;
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

Vector *matrix_solve(Matrix * mat, Vector * y)
{
    Vector *x;
    double **a, *b, d;
    int    *index, n;

    if (mat == NULL || y == NULL)
	return (NULL);
    if (mat->m != y->n || mat->n != y->n)
	return (NULL);

    n = mat->m;
    a = darray_dcopy(mat->el.double_v, 0, 0, n, n);
    x = vector_copy(y);
    b = x->data;
    index = ivector_alloc(0, n);

    ludcmp(a, n, index, &d);
    lubksb(a, n, index, b);

    darray_free((char **) a, 0, 0, n, n);
    ivector_free((void *) index, 0);

    return (x);
}
