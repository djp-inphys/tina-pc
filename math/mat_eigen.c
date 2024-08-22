#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

#define SIGN(a,b) ((b)<0 ? -fabs(a) : fabs(a))

static void tred2(int n, double **a, double *d, double *e)
{
    int l, k, j, i;
    double scale, hh, h, g, f;

    /*
    start arrays at 0 not 1
    */
    for (i = 0; i < n; ++i)
	(a[i])--;
    a--;
    d--;
    e--;

    for (i = n; i >= 2; i--)
    {
	l = i - 1;
	h = scale = 0.0;
	if (l > 1)
	{
	    for (k = 1; k <= l; k++)
		scale += fabs(a[i][k]);
	    if (scale == 0.0)
		e[i] = a[i][l];
	    else
	    {
		for (k = 1; k <= l; k++)
		{
		    a[i][k] /= scale;
		    h += a[i][k] * a[i][k];
		}
		f = a[i][l];
		g = f > 0 ? -sqrt(h) : sqrt(h);
		e[i] = scale * g;
		h -= f * g;
		a[i][l] = f - g;
		f = 0.0;
		for (j = 1; j <= l; j++)
		{
		    a[j][i] = a[i][j] / h;
		    g = 0.0;
		    for (k = 1; k <= j; k++)
			g += a[j][k] * a[i][k];
		    for (k = j + 1; k <= l; k++)
			g += a[k][j] * a[i][k];
		    e[j] = g / h;
		    f += e[j] * a[i][j];
		}
		hh = f / (h + h);
		for (j = 1; j <= l; j++)
		{
		    f = a[i][j];
		    e[j] = g = e[j] - hh * f;
		    for (k = 1; k <= j; k++)
			a[j][k] -= (f * e[k] + g * a[i][k]);
		}
	    }
	}
	else
	    e[i] = a[i][l];
	d[i] = h;
    }
    d[1] = 0.0;
    e[1] = 0.0;
    for (i = 1; i <= n; i++)
    {
	l = i - 1;
	if (d[i])
	{
	    for (j = 1; j <= l; j++)
	    {
		g = 0.0;
		for (k = 1; k <= l; k++)
		    g += a[i][k] * a[k][j];
		for (k = 1; k <= l; k++)
		    a[k][j] -= g * a[k][i];
	    }
	}
	d[i] = a[i][i];
	a[i][i] = 1.0;
	for (j = 1; j <= l; j++)
	    a[j][i] = a[i][j] = 0.0;
    }

    a++;
    d++;
    e++;
    for (i = 0; i < n; ++i)
	(a[i])++;
}

static int tqli(int n, double **z, double *d, double *e)
{
    int m, l, iter, i, k;
    double s, r, p, g, f, dd, c, b;

    /*
    start arrays at 0 not 1
    */
    for (i = 0; i < n; ++i)
	(z[i])--;
    z--;
    d--;
    e--;

    for (i = 2; i <= n; i++)
	e[i - 1] = e[i];
    e[n] = 0.0;
    for (l = 1; l <= n; l++)
    {
	iter = 0;
	do
	{
	    for (m = l; m <= n - 1; m++)
	    {
		dd = fabs(d[m]) + fabs(d[m + 1]);
		if (fabs(e[m]) + dd == dd)
		    break;
	    }
	    if (m != l)
	    {
		if (iter++ == 30)
		    return (0);
		g = (d[l + 1] - d[l]) / (2.0 * e[l]);
		r = sqrt((g * g) + 1.0);
		g = d[m] - d[l] + e[l] / (g + SIGN(r, g));
		s = c = 1.0;
		p = 0.0;
		for (i = m - 1; i >= l; i--)
		{
		    f = s * e[i];
		    b = c * e[i];
		    if (fabs(f) >= fabs(g))
		    {
			c = g / f;
			r = sqrt((c * c) + 1.0);
			e[i + 1] = f * r;
			c *= (s = 1.0 / r);
		    }
		    else
		    {
			s = f / g;
			r = sqrt((s * s) + 1.0);
			e[i + 1] = g * r;
			s *= (c = 1.0 / r);
		    }
		    g = d[i + 1] - p;
		    r = (d[i] - g) * s + 2.0 * c * b;
		    p = s * r;
		    d[i + 1] = g + p;
		    g = c * r - b;
		    for (k = 1; k <= n; k++)
		    {
			f = z[k][i + 1];
			z[k][i + 1] = s * z[k][i] + c * f;
			z[k][i] = c * z[k][i] - s * f;
		    }
		}
		d[l] = d[l] - p;
		e[l] = g;
		e[m] = 0.0;
	    }
	}
	while (m != l);
    }

    z++;
    d++;
    e++;
    for (i = 0; i < n; ++i)
	(z[i])++;

    return (1);
}

/*
Find eigenvalues and eigenvectors of symmetric  n  by n matrix a,
*/
static int eigen(int n, double **a, double **evec, double *eval)
{
    int i, j, k, success;
    double *d = tvector_alloc(0, n, double);
    double *e = tvector_alloc(0, n, double);

    for(i = 0; i < n; i++)
	for(j = 0; j < n; j++)
	    evec[i][j] = a[i][j];

    tred2(n, evec, eval, e);
    success = tqli(n, evec, eval, e);

    if(!success)
    {
	tvector_free(d, 0, double);
	tvector_free(e, 0, double);
	return(success);
    }

    for (j = 0; j < n - 1; j++)
    {
	double emax = eval[j];
	int jmax = j;
	for (k = j + 1; k < n; k++)
	    if (emax < eval[k])
	    {
		emax = eval[k];
		jmax = k;
	    }
	if (jmax != j)
	{
	    SWAP(double, eval[j], eval[jmax]);
	    for(i = 0; i < n; i++)
		SWAP(double, evec[i][j], evec[i][jmax]);
	}
    }
    tvector_free(d, 0, double);
    tvector_free(e, 0, double);
    return (success);
}

/*
eval's in descending order
evecs in columns of matrix evec
*/
int mat_eigen(Mat *a, Mat *evec, Vec *eval)
{
    return(eigen(a->n, a->el, evec->el, eval->el));
}


#undef SIGN
