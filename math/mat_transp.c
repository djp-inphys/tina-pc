/**@(#)Matrix transpose
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>

int     matrix_get();
double  matrix_getf();

Matrix *matrix_alloc();
Matrix *matrix_copy();

Matrix *imatrix_transp(Matrix * mat);
Matrix *fmatrix_transp(Matrix * mat);
Matrix *dmatrix_transp(Matrix * mat);

Matrix *matrix_transp(Matrix * mat)
{
    if (mat == NULL)
	return (NULL);

    switch (mat->vtype)
    {
    case int_v:
	return (imatrix_transp(mat));
    case float_v:
	return (fmatrix_transp(mat));
    case double_v:
	return (dmatrix_transp(mat));
    }
    error("matrix_transp: no such type", non_fatal);
    return (NULL);
}

Matrix *imatrix_transp(Matrix * mat)
{
    Matrix *transp;
    int   **el1, **el2;
    int     m, n;
    int     i, j;

    if (mat == NULL)
	return (NULL);

    m = mat->m;
    n = mat->n;
    el1 = mat->el.int_v;

    switch (mat->shape)
    {
    case matrix_full:
	transp = matrix_alloc(n, m, matrix_full, int_v);
	el2 = transp->el.int_v;
	for (i = 0; i < m; ++i)
	    for (j = 0; j < n; ++j)
		el2[j][i] = el1[i][j];
	break;
    case matrix_lower:
	transp = matrix_alloc(n, m, matrix_lower, int_v);
	el2 = transp->el.int_v;
	for (i = 0; i < m; ++i)
	    for (j = i; j < m; ++j)
		el2[j][i] = el1[i][j];
	break;
    case matrix_upper:
	transp = matrix_alloc(n, m, matrix_upper, int_v);
	el2 = transp->el.int_v;
	for (i = 0; i < m; ++i)
	    for (j = 0; j <= i; ++j)
		el2[j][i] = el1[i][j];
	break;
    case matrix_symmetric:
	return (matrix_copy(mat));
    default:
	transp = matrix_alloc(n, m, matrix_full, int_v);
	el2 = transp->el.int_v;
	for (i = 0; i < m; ++i)
	    for (j = 0; j < n; ++j)
		el2[j][i] = matrix_get(mat, i, j);
	break;
    }
    return (transp);
}

Matrix *fmatrix_transp(Matrix * mat)
{
    Matrix *transp;
    float **el1, **el2;
    int     m, n;
    int     i, j;

    if (mat == NULL)
	return (NULL);

    m = mat->m;
    n = mat->n;
    el1 = mat->el.float_v;

    switch (mat->shape)
    {
    case matrix_full:
	transp = matrix_alloc(n, m, matrix_full, float_v);
	el2 = transp->el.float_v;
	for (i = 0; i < m; ++i)
	    for (j = 0; j < n; ++j)
		el2[j][i] = el1[i][j];
	break;
    case matrix_lower:
	transp = matrix_alloc(n, m, matrix_lower, float_v);
	el2 = transp->el.float_v;
	for (i = 0; i < m; ++i)
	    for (j = i; j < m; ++j)
		el2[j][i] = el1[i][j];
	break;
    case matrix_upper:
	transp = matrix_alloc(n, m, matrix_upper, float_v);
	el2 = transp->el.float_v;
	for (i = 0; i < m; ++i)
	    for (j = 0; j <= i; ++j)
		el2[j][i] = el1[i][j];
	break;
    case matrix_symmetric:
	return (matrix_copy(mat));
    default:
	transp = matrix_alloc(n, m, matrix_full, float_v);
	el2 = transp->el.float_v;
	for (i = 0; i < m; ++i)
	    for (j = 0; j < n; ++j)
		el2[j][i] = matrix_getf(mat, i, j);
	break;
    }
    return (transp);
}

Matrix *dmatrix_transp(Matrix * mat)
{
    Matrix *transp;
    double **el1, **el2;
    int     m, n;
    int     i, j;

    if (mat == NULL)
	return (NULL);

    m = mat->m;
    n = mat->n;
    el1 = mat->el.double_v;

    switch (mat->shape)
    {
    case matrix_full:
	transp = matrix_alloc(n, m, matrix_full, double_v);
	el2 = transp->el.double_v;
	for (i = 0; i < m; ++i)
	    for (j = 0; j < n; ++j)
		el2[j][i] = el1[i][j];
	break;
    case matrix_lower:
	transp = matrix_alloc(n, m, matrix_lower, double_v);
	el2 = transp->el.double_v;
	for (i = 0; i < m; ++i)
	    for (j = i; j < m; ++j)
		el2[j][i] = el1[i][j];
	break;
    case matrix_upper:
	transp = matrix_alloc(n, m, matrix_upper, double_v);
	el2 = transp->el.double_v;
	for (i = 0; i < m; ++i)
	    for (j = 0; j <= i; ++j)
		el2[j][i] = el1[i][j];
	break;
    case matrix_symmetric:
	return (matrix_copy(mat));
    default:
	transp = matrix_alloc(n, m, matrix_full, double_v);
	el2 = transp->el.double_v;
	for (i = 0; i < m; ++i)
	    for (j = 0; j < n; ++j)
		el2[j][i] = matrix_getf(mat, i, j);
	break;
    }
    return (transp);
}
