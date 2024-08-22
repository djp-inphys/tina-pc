/**@(#)Matrix multiplied by a scalar.
 */

#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

Vartype matrix_sup_vtype();

int     matrix_get();
double  matrix_getf();

Matrix *matrix_alloc();
Matrix *matrix_cast();

Matrix *imatrix_times();
Matrix *fmatrix_times(double k, Matrix * mat);
Matrix *dmatrix_times(double k, Matrix * mat);

Matrix *matrix_times(double k, Matrix * mat)
{
    Matrix *prod;
    Matrix *m;
    Vartype vtype;

    if (mat == NULL)
	return (NULL);

    vtype = matrix_sup_vtype(mat->vtype, float_v);

    if (mat->vtype != vtype)
	m = matrix_cast(mat, vtype);
    else
	m = mat;

    switch (vtype)
    {
    case float_v:
	prod = fmatrix_times(k, m);
    case double_v:
	prod = dmatrix_times(k, m);
    }
    if (mat->vtype != vtype)
	matrix_free(m);

    return (prod);
}

Matrix *fmatrix_times(double k, Matrix * mat)
{
    Matrix *prod;
    int     m = mat->m;
    int     n = mat->n;
    float **el1 = mat->el.float_v;
    float **el2;
    int     i, j;

    switch (mat->shape)
    {
    case matrix_full:
	prod = matrix_alloc(m, n, matrix_full, float_v);
	el2 = prod->el.float_v;
	for (i = 0; i < m; ++i)
	    for (j = 0; j < n; ++j)
		el2[i][j] = k * el1[i][j];
	break;
    case matrix_lower:
	prod = matrix_alloc(m, n, matrix_lower, float_v);
	el2 = prod->el.float_v;
	for (i = 0; i < m; ++i)
	    for (j = 0; j <= i; ++j)
		el2[i][j] = k * el1[i][j];
	break;
    case matrix_upper:
	prod = matrix_alloc(m, n, matrix_upper, float_v);
	el2 = prod->el.float_v;
	for (i = 0; i < m; ++i)
	    for (j = i; j < n; ++j)
		el2[i][j] = k * el1[i][j];
	break;
    case matrix_symmetric:
	prod = matrix_alloc(m, n, matrix_symmetric, float_v);
	el2 = prod->el.float_v;
	for (i = 0; i < m; ++i)
	    for (j = 0; j <= i; ++j)
		el2[i][j] = k * el1[i][j];
	break;
    default:
	prod = matrix_alloc(m, n, matrix_full, float_v);
	for (i = 0; i < m; ++i)
	    for (j = 0; j < n; ++j)
		matrix_putf(k * matrix_getf(mat, i, j), prod, i, j);
	break;
    }

    return (prod);
}

Matrix *dmatrix_times(double k, Matrix * mat)
{
    Matrix *prod;
    int     m = mat->m;
    int     n = mat->n;
    double **el1 = mat->el.double_v;
    double **el2;
    int     i, j;

    switch (mat->shape)
    {
    case matrix_full:
	prod = matrix_alloc(m, n, matrix_full, double_v);
	el2 = prod->el.double_v;
	for (i = 0; i < m; ++i)
	    for (j = 0; j < n; ++j)
		el2[i][j] = k * el1[i][j];
	break;
    case matrix_lower:
	prod = matrix_alloc(m, n, matrix_lower, double_v);
	el2 = prod->el.double_v;
	for (i = 0; i < m; ++i)
	    for (j = 0; j <= i; ++j)
		el2[i][j] = k * el1[i][j];
	break;
    case matrix_upper:
	prod = matrix_alloc(m, n, matrix_upper, double_v);
	el2 = prod->el.double_v;
	for (i = 0; i < m; ++i)
	    for (j = i; j < n; ++j)
		el2[i][j] = k * el1[i][j];
	break;
    case matrix_symmetric:
	prod = matrix_alloc(m, n, matrix_symmetric, double_v);
	el2 = prod->el.double_v;
	for (i = 0; i < m; ++i)
	    for (j = 0; j <= i; ++j)
		el2[i][j] = k * el1[i][j];
	break;
    default:
	prod = matrix_alloc(m, n, matrix_full, double_v);
	for (i = 0; i < m; ++i)
	    for (j = 0; j < n; ++j)
		matrix_putf(k * matrix_getf(mat, i, j), prod, i, j);
	break;
    }

    return (prod);
}
