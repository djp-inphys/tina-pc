/**@(#)Matrix invertion (various types & shapes)
  @(#)(arithmetic always done in double precision)
 */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

int     matrix_get();
double  matrix_getf();

void    matrix_put();
void    matrix_putf();

double **darray_invert(double **a1, int n);
double **dupper_invert(double **u, int n);
double **dlower_invert(double **l, int n);

Matrix *matrix_alloc();
Matrix *matrix_build();
Matrix *matrix_copy();
Matrix *matrix_cast();
Matrix *matrix_fill();
Matrix *dmatrix_invert(Matrix * mat);

Vartype matrix_sup_vtype();

Matrix *matrix_invert(Matrix * mat)
{
    Matrix *inverse;
    Matrix *inverse1;
    Matrix *m;

    if (mat == NULL)
	return (mat);

    /** make copy of type double if necessary **/

    if (mat->vtype != double_v)
	m = matrix_cast(mat, double_v);
    else
	m = mat;

    inverse1 = dmatrix_invert(m);

    switch (mat->vtype)
    {
    case int_v:
    case float_v:
	inverse = matrix_cast(inverse1, float_v);
	matrix_free((Matrix *) inverse1);
	break;
    case double_v:
	inverse = inverse1;
	break;
    }

    /** free copy if necessary **/

    if (mat->vtype != double_v)
	matrix_free((Matrix *) m);

    return (inverse);
}

Matrix *dmatrix_invert(Matrix * mat)
{
    Matrix *inverse;
    double **el;
    int     m;

    m = MIN(mat->m, mat->n);
    switch (mat->shape)
    {
    case matrix_full:
	el = darray_invert(mat->el.double_v, m);
	inverse = matrix_build(m, m, matrix_full, double_v, (void *) el);
	break;
    case matrix_lower:
	el = dlower_invert(mat->el.double_v, m);
	inverse = matrix_build(m, m, matrix_upper, double_v, (void *) el);
	break;
    case matrix_upper:
	el = dupper_invert(mat->el.double_v, m);
	inverse = matrix_build(m, m, matrix_lower, double_v, (void *) el);
	break;
    default:
	{
	    Matrix *mat1 = matrix_fill(mat);

	    inverse = dmatrix_invert(mat1);
	    matrix_free((Matrix *) mat1);
	    break;
	}
    }
    return (inverse);
}

double **darray_invert(double **a1, int n)
{
    int     i, j, k;
    int    *p = ivector_alloc(0, n);
    double **a = darray_alloc(0, 0, n, n);
    double  h, q, s, sup, pivot;


    for (i = 0; i < n; i++)
	for (j = 0; j < n; j++)
	    a[i][j] = a1[i][j];

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
	    return (NULL);
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

    ivector_free((void *) p, 0);
    return (a);
}

double **dlower_invert(double **l, int n)
{
    int     i, j, k;
    double  sum;
    double **u = dupper_alloc(0, n);

    for (j = n - 1; j >= 0; --j)
    {
	u[j][j] = -1.0 / l[j][j];
	for (i = j + 1; i < n; ++i)
	{
	    sum = 0.0;
	    for (k = j; k < i; ++k)
		sum += l[i][k] * u[k][j];
	    u[i][j] = u[j][j] * sum;
	}
    }

    return (u);
}

double **dupper_invert(double **u, int n)
{
    int     i, j, k;
    double  sum;
    double **l = dlower_alloc(0, n);

    for (j = 0; j < n; ++j)
    {
	l[j][j] = -1.0 / u[j][j];
	for (i = j - 1; i >= 0; --i)
	{
	    sum = 0.0;
	    for (k = i; k < j; ++k)
		sum += u[i][k] * l[k][j];
	    l[i][j] = l[j][j] * sum;
	}
    }
    return (l);
}
