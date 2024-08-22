/**@(#)
**/
#include <math.h>
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>

#define NMAX 1000
#define ALPHA 1.0
#define BETA 0.5
#define GAMMA 2.0

/* smc 2/2/93 */
#ifdef Print
#undef Print
#endif
/* smc 2/2/93 */

#define Print(x)  { if(out_text!=NULL) out_text(x); }

static void (*out_text) () = NULL;

double  simplexmin(int n, double *x, double lambda, double (*funk) ( /* ??? */ ), double ftol, void (*text) ( /* ??? */ ))
{
    int     i, j, lowest = 0;
    double **p;
    double *y;
    int     nfunk;
    double  f;
    void    amoeba(double **p, double *y, int ndim, double ftol, double (*funk) ( /* ??? */ ), int *nfunk);
    char    temp[64];

    out_text = text;
    y = (double *) ralloc((unsigned) ((n + 1) * sizeof(double)));
    if ((p = darray_alloc(0, 0, n + 1, n)) == NULL)
	return (0.0);

    for (i = 0; i < n + 1; i++)
    {
	for (j = 0; j < n; j++)
	{
	    p[i][j] = x[j];
	}
	if (i > 0)
	    p[i][i - 1] = x[i - 1] * (1.0 + lambda);
	y[i] = (*funk) (n, p[i]);
	if (i > 0)
	{
	    p[i][i - 1] = x[i - 1] * (1.0 - lambda);
	    if ((f = (*funk) (n, p[i])) > y[i])
		p[i][i - 1] = x[i - 1] * (1.0 + lambda);
	    else
		y[i] = f;
	}
    }

    Print(sprintf(temp, " initial value %f \n", y[0]));
    amoeba(p, y, n, ftol, funk, &nfunk);
    for (j = 0; j < n + 1; j++)
	if (y[j] < y[lowest])
	    lowest = j;
    for (i = 0; i < n; i++)
	x[i] = p[lowest][i];
    f = y[lowest];
    darray_free((char **) p, 0, 0, n + 1, n);
    rfree((void *) y);
    Print(sprintf(temp, " number of function evaluations %d \n", nfunk));
    Print(sprintf(temp, " final value %f \n", f));
    return (f);
}

double  simplexmin2(int n, double *x, double *lambda, double (*funk) ( /* ??? */ ), double ftol, void (*text) ( /* ??? */ ))
{
    int     i, j, lowest = 0;
    double **p;
    double *y;
    int     nfunk;
    double  f;
    void    amoeba(double **p, double *y, int ndim, double ftol, double (*funk) ( /* ??? */ ), int *nfunk);
    char    temp[64];

    out_text = text;
    y = (double *) ralloc((unsigned) ((n + 1) * sizeof(double)));
    if ((p = darray_alloc(0, 0, n + 1, n)) == NULL)
	return (0.0);

    for (i = 0; i < n + 1; i++)
    {
	for (j = 0; j < n; j++)
	{
	    p[i][j] = x[j];
	}
	if (i > 0)
	    p[i][i - 1] = x[i - 1] + lambda[i - 1];
	y[i] = (*funk) (n, p[i]);
	if (i > 0)
	{
	    p[i][i - 1] = x[i - 1] - lambda[i - 1];
	    if ((f = (*funk) (n, p[i])) > y[i])
		p[i][i - 1] = x[i - 1] + lambda[i - 1];
	    else
		y[i] = f;
	}
    }

    Print(sprintf(temp, " initial value %f \n", y[0]));
    amoeba(p, y, n, ftol, funk, &nfunk);
    for (j = 0; j < n + 1; j++)
	if (y[j] < y[lowest])
	    lowest = j;
    for (i = 0; i < n; i++)
	x[i] = p[lowest][i];
    f = y[lowest];
    darray_free((char **) p, 0, 0, n + 1, n);
    rfree((void *) y);
    Print(sprintf(temp, " number of function evaluations %d \n", nfunk));
    Print(sprintf(temp, " final value %f \n", f));
    return (f);
}

void    amoeba(double **p, double *y, int ndim, double ftol, double (*funk) ( /* ??? */ ), int *nfunk)
{
    int     i, j, ilo, ihi, inhi, mpts = ndim + 1;
    double  ytry, ysave, sum, rtol, amotry(double **p, double *y, double *psum, int ndim, double (*funk) ( /* ??? */ ), int ihi, int *nfunk, double fac),
           *psum;

    psum = (double *) ralloc((unsigned) ndim * sizeof(double));
    *nfunk = 0;
    for (j = 0; j < ndim; j++)
    {
	for (i = 0, sum = 0.0; i < mpts; i++)
	    sum += p[i][j];
	psum[j] = sum;
    }
    for (;;)
    {
	ilo = 0;
	ihi = y[0] > y[1] ? (inhi = 1, 0) : (inhi = 0, 1);
	for (i = 0; i < mpts; i++)
	{
	    if (y[i] < y[ilo])
		ilo = i;
	    if (y[i] > y[ihi])
	    {
		inhi = ihi;
		ihi = i;
	    } else if (y[i] > y[inhi])
		if (i != ihi)
		    inhi = i;
	}
	rtol = 2.0 * fabs(y[ihi] - y[ilo]) / (fabs(y[ihi]) + fabs(y[ilo]));
	if (rtol > ftol && *nfunk <= NMAX);
	else
	    break;

	ytry = amotry(p, y, psum, ndim, funk, ihi, nfunk, -ALPHA);

	if (ytry <= y[ilo])
	    ytry = amotry(p, y, psum, ndim, funk, ihi, nfunk, GAMMA);
	else if (ytry >= y[inhi])
	{
	    ysave = y[ihi];
	    ytry = amotry(p, y, psum, ndim, funk, ihi, nfunk, BETA);
	    if (ytry >= ysave)
	    {
		for (i = 0; i < mpts; i++)
		{
		    if (i != ilo)
		    {
			for (j = 0; j < ndim; j++)
			{
			    psum[j] = 0.5 * (p[i][j] + p[ilo][j]);
			    p[i][j] = psum[j];
			}
			y[i] = (*funk) (ndim, psum);
		    }
		}
		*nfunk += ndim;
		for (j = 0; j < ndim; j++)
		{
		    for (i = 0, sum = 0.0; i < mpts; i++)
			sum += p[i][j];
		    psum[j] = sum;
		}
	    }
	}
    }
    rfree((void *) psum);
}

double  amotry(double **p, double *y, double *psum, int ndim, double (*funk) ( /* ??? */ ), int ihi, int *nfunk, double fac)
{
    int     j;
    double  fac1, fac2, ytry, *ptry;

    ptry = (double *) ralloc((unsigned) ndim * sizeof(double));;
    fac1 = (1.0 - fac) / ndim;
    fac2 = fac1 - fac;
    for (j = 0; j < ndim; j++)
	ptry[j] = psum[j] * fac1 - p[ihi][j] * fac2;
    ytry = (*funk) (ndim, ptry);
    ++(*nfunk);
    if (ytry < y[ihi])
    {
	y[ihi] = ytry;
	for (j = 0; j < ndim; j++)
	{
	    psum[j] += ptry[j] - p[ihi][j];
	    p[ihi][j] = ptry[j];
	}
    }
    rfree((void *) ptry);
    return ytry;
}

double **maketarray(int l_array, int w_array, float gl)
{
    double **array;
    short   i, j;

    if ((array = (double **) ralloc((unsigned) l_array * sizeof(double *))) == NULL)
	return (NULL);
    if ((array[0] = (double *) ralloc((unsigned) l_array * w_array * sizeof(double))) == NULL)
	return (void *) (NULL);
    for (i = 1; i < l_array; ++i)
	array[i] = array[i - 1] + w_array;
    for (i = 0; i < l_array; ++i)
	for (j = 0; j < w_array; j++)
	    array[i][j] = gl;
    return (array);
}

void    freetarray(double **array)
{
    if (array == NULL)
	return;
    if (array[0] != NULL)
	rfree((void *) array[0]);
    if (array != NULL)
	rfree((void *) array);
}
