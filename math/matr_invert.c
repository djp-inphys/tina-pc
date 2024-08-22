/*
 *
 * mat_invert.c
 *
 * Matrix inversion.
 *
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

static void invert(int n, double **a)
{
    int     i, j, k;
    int    *p = tvector_alloc(0, n, int);
    double  h, q, s, sup, pivot;
    for (k = 0; k < n; k++)
    {
	sup = 0.0;
	p[k] = 0;
	for (i = k; i < n; i++)
	{
	    s = 0.0;
	    for (j = k; j < n; j++)
		s += fabs(a[i][j]);
	    q = fabs(a[i][k]) / s;
	    if (sup < q)
	    {
		sup = q;
		p[k] = i;
	    }
	}
	if (sup == 0.0)
	    return;
	if (p[k] != k)
	    for (j = 0; j < n; j++)
	    {
		h = a[k][j];
		a[k][j] = a[p[k]][j];
		a[p[k]][j] = h;
	    }
	pivot = a[k][k];
	for (j = 0; j < n; j++)
	    if (j != k)
	    {
		a[k][j] = -a[k][j] / pivot;
		for (i = 0; i < n; i++)
		    if (i != k)
			a[i][j] += a[i][k] * a[k][j];
	    }
	for (i = 0; i < n; i++)
	    a[i][k] = a[i][k] / pivot;
	a[k][k] = 1.0 / pivot;
    }
    for (k = n - 1; k >= 0; k--)
	if (p[k] != k)
	    for (i = 0; i < n; i++)
	    {
		h = a[i][k];
		a[i][k] = a[i][p[k]];
		a[i][p[k]] = h;
	    }

    tvector_free(p, 0, int);
}

/*
Invert matrix a in place using pivoting method above.
*/
void mat_invert(Mat *a)
{
    if(a == NULL)
	return;
    invert(a->n, a->el);
}
