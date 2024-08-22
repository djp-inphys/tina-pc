/**@(#)Matrix copy (various types and shapes)
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

int     matrix_get();

void    matrix_put();
void    matrix_putf();

Matrix *matrix_alloc();
Matrix *matrix_build();

Matrix *imatrix_copy(Matrix * mat);
Matrix *fmatrix_copy(Matrix * mat);
Matrix *dmatrix_copy(Matrix * mat);

Matrix *matrix_copy(Matrix * mat)
{
    if (mat == NULL)
	return (NULL);

    switch (mat->vtype)
    {
    case int_v:
	return (imatrix_copy(mat));
    case float_v:
	return (fmatrix_copy(mat));
    case double_v:
	return (dmatrix_copy(mat));
    }

    error("matrix_copy: no such type", non_fatal);
    return (NULL);
}

Matrix *imatrix_copy(Matrix * mat)
{
    void   *el;
    int     m = mat->m;
    int     n = mat->n;
    Matrix_shape shape = mat->shape;

    int     dummy1 = 0;
    int     dummy2 = 0;

    switch (shape)
    {
    case matrix_full:
	el = (void *) iarray_icopy(mat->el.int_v, 0, 0, m, n);
	break;
    case matrix_lower:
    case matrix_symmetric:

	/* BUG ilower_icopy(int **a, int m1, n1, m2, n2 */
	el = (void *) ilower_icopy(mat->el.int_v, 0, n, dummy1, dummy2);
	break;
    case matrix_upper:
	el = (void *) iupper_icopy(mat->el.int_v, 0, n);
	break;
    default:
	{
	    int     i, j;
	    Matrix *copy = matrix_alloc(m, n, shape, int_v);

	    for (i = 0; i < m; ++i)
		for (j = 0; j < n; ++j)
		    matrix_put(matrix_get(mat, i, j), copy, i, j);
	    return (copy);
	}
    }
    return (matrix_build(m, n, shape, int_v, el));
}

Matrix *fmatrix_copy(Matrix * mat)
{
    void   *el;
    int     m = mat->m;
    int     n = mat->n;
    Matrix_shape shape = mat->shape;

    int     dummy1 = 0;
    int     dummy2 = 0;

    switch (shape)
    {
    case matrix_full:
	el = (void *) farray_fcopy(mat->el.float_v, 0, 0, m, n);
	break;
    case matrix_lower:
    case matrix_symmetric:

	/* BUG flower_dcopy(double **a, int m1, n1, m2, n2) */
	el = (void *) flower_fcopy(mat->el.float_v, 0, n, dummy1, dummy2);
	break;
    case matrix_upper:
	el = (void *) fupper_fcopy(mat->el.float_v, 0, n);
	break;
    default:
	{
	    int     i, j;
	    Matrix *copy = matrix_alloc(m, n, shape, float_v);

	    for (i = 0; i < m; ++i)
		for (j = 0; j < n; ++j)
		    matrix_putf(matrix_getf(mat, i, j), copy, i, j);
	    return (copy);
	}
    }
    return (matrix_build(m, n, shape, float_v, el));
}

Matrix *dmatrix_copy(Matrix * mat)
{
    void   *el;
    int     m = mat->m;
    int     n = mat->n;
    Matrix_shape shape = mat->shape;

    int     dummy1 = 0;
    int     dummy2 = 0;

    switch (shape)
    {
    case matrix_full:
	el = (void *) darray_dcopy(mat->el.double_v, 0, 0, m, n);
	break;
    case matrix_lower:
    case matrix_symmetric:

	/* BUG double **dlower_dcopy(a, m1, n1, m2, n2) */
	el = (void *) dlower_dcopy(mat->el.double_v, 0, n, dummy1, dummy2);
	break;
    case matrix_upper:
	el = (void *) dupper_dcopy(mat->el.double_v, 0, n);
	break;
    default:
	{
	    int     i, j;
	    Matrix *copy = matrix_alloc(m, n, shape, double_v);

	    for (i = 0; i < m; ++i)
		for (j = 0; j < n; ++j)
		    matrix_putf(matrix_getf(mat, i, j), copy, i, j);
	    return (copy);
	}
    }
    return (matrix_build(m, n, shape, double_v, el));
}

Matrix *matrix_copy_inplace(Matrix * mat1, Matrix * mat2)
{
    int     n, m;
    int     i, j;

    if (mat1 == NULL || mat2 == NULL)
	return (mat2);

    m = mat1->m;
    n = mat1->n;

    if (mat2->m != m || mat2->n != n)
	return (mat2);

    for (i = 0; i < m; ++i)
	for (j = 0; j < n; ++j)
	    matrix_putf(matrix_getf(mat1, i, j), mat2, i, j);
    return (mat2);
}
