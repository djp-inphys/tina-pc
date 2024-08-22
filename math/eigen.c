/**@(#)Matrix format function to determine all eigen values and vectors of a
  @(#)given symmetric matrix A (generic format) the resulting eigen values and
  @(#)coulumn eigen vectors are sorted in ascending eigen value
 */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

static void tred2(double **a, int n, double *d, double *e);
static int tqli(double *d, double *e, int n, double **z);

int     matrix_eigen_sym(Matrix * A, Vector * Eval, Matrix * Evec)
{
    int     n;
    int     success;
    Vector *e;
    Vector *d;
    Vector *eval;
    Matrix *evec;
    Matrix *matrix_cast_fill();
    Matrix *matrix_copy_inplace();
    Vector *vector_alloc();

    int     i;

    if (A == NULL || A->n != A->m)
	return (0);

    n = A->n;
    if (Evec == NULL || Eval == NULL || Evec->n != n || Evec->m != n || Eval->n != n)
	return (0);

    evec = matrix_cast_fill(A, double_v);
    eval = vector_alloc(n, double_v);
    d = vector_alloc(n, double_v);
    e = vector_alloc(n, double_v);

    tred2(evec->el.double_v, n, (double *) eval->data, (double *) e->data);
    success = tqli((double *) eval->data, (double *) e->data, n, evec->el.double_v);

    if (success) // bubble sort the result
	{
	  unsigned char swap;
      double        temp;

	  do 
	  {	
	  	swap = 0;
	    for (i = 0; i < n - 1; ++i)
	    {
 		  if (VECTOR_DOUBLE(eval, i) < VECTOR_DOUBLE(eval, i+1))
		  {
		  	  swap = 1;

			  temp = VECTOR_DOUBLE(eval, i);
		      VECTOR_DOUBLE(eval, i) = VECTOR_DOUBLE(eval, i+1);
		      VECTOR_DOUBLE(eval, i+1) = temp;
		      (void) matrix_swap_cols(evec, i, i+1 );
	      }
	    }
	  } while( swap == 1 );
	}

    (void) matrix_copy_inplace(evec, Evec);

    vector_copy_inplace(Eval, eval);	/** copy goes <--- **/

    matrix_free((Matrix *) evec);
    vector_free(e);
    vector_free(d);
    vector_free(eval);
    return (success);
}

/**
eigenvalues and eigenvectors of symmetric  n  by n matrix A:
Eval = already allocated vector of n doubles
Evec = already allocated vector of n pointers to vectors of n doubles
VECTOR_DOUBLE(Eval,0)          = biggest eigenvalue
(Vector *) VECTOR_PTR(Evec, 0) = associated eigenvector
**/
int     matrix_eigen(Matrix * A, Vector * Eval, Vector * Evec)
{
    int     n;
    int     success;
    Vector *e;
    Vector *d;
    Vector *eval;
    Matrix *evec;
    Matrix *matrix_cast_fill();
    Vector *vector_alloc();

    int     i, j;

    if (A == NULL || A->n != A->m)
	return (0);

    n = A->n;
    if (Evec == NULL || Eval == NULL)
	return (0);

    evec = matrix_cast_fill(A, double_v);
    eval = vector_alloc(n, double_v);
    d = vector_alloc(n, double_v);
    e = vector_alloc(n, double_v);

    tred2(evec->el.double_v, n, (double *) eval->data, (double *) e->data);
    success = tqli((double *) eval->data, (double *) e->data, n, evec->el.double_v);

    if (success)
	for (i = 0; i < n - 1; ++i)
	{
	    double  min_eval = VECTOR_DOUBLE(eval, i);
	    int     minc = i;

	    for (j = i + 1; j < n; ++j)
		if (VECTOR_DOUBLE(eval, j) < min_eval)
		{
		    min_eval = VECTOR_DOUBLE(eval, j);
		    minc = j;
		}
	    if (minc != i)
	    {
		double  temp = VECTOR_DOUBLE(eval, i);

		VECTOR_DOUBLE(eval, i) = VECTOR_DOUBLE(eval, minc);
		VECTOR_DOUBLE(eval, minc) = temp;
		(void) matrix_swap_cols(evec, i, minc);
	    }
	}

    /** largest first **/
    for (j = 0; j < n; j++)
    {
	Vector *ej = VECTOR_PTR(Evec, j);

	VECTOR_DOUBLE(Eval, j) = VECTOR_DOUBLE(eval, n - 1 - j);
	for (i = 0; i < n; i++)
	    VECTOR_DOUBLE(ej, i) = evec->el.double_v[i][n - 1 - j];
    }


    matrix_free((Matrix *) evec);
    vector_free(e);
    vector_free(d);
    vector_free(eval);
    return (success);
}

static void tred2(double **a, int n, double *d, double *e)
{
    int     l, k, j, i;
    double  scale, hh, h, g, f;

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
	} else
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

#undef SIGN

#define SIGN(a,b) ((b)<0 ? -fabs(a) : fabs(a))

static int tqli(double *d, double *e, int n, double **z)
{
    int     m, l, iter, i, k;
    double  s, r, p, g, f, dd, c, b;

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
		    } else
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
	} while (m != l);
    }

    z++;
    d++;
    e++;
    for (i = 0; i < n; ++i)
	(z[i])++;

    return (1);
}
