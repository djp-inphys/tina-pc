/**@(#)Build matrices with same elements but different type
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>

int     matrix_get();
double  matrix_getf();

void    matrix_put();
void    matrix_putf();

Matrix *matrix_alloc();
Matrix *matrix_build();

Matrix *imatrix_cast(Matrix * mat);
Matrix *fmatrix_cast(Matrix * mat);
Matrix *dmatrix_cast(Matrix * mat);

Matrix *matrix_cast(Matrix * mat, Vartype vtype)
{
    if (mat == NULL)
	return (NULL);

    switch (vtype)
    {
    case int_v:
	return (imatrix_cast(mat));
    case float_v:
	return (fmatrix_cast(mat));
    case double_v:
	return (dmatrix_cast(mat));
    }
    error("matrix_cast: no such type", non_fatal);
    return (NULL);
}

Matrix *imatrix_cast(Matrix * mat)
{
    int   **el;
    Vartype vtype = mat->vtype;
    Matrix_shape shape = mat->shape;
    int     m = mat->m;
    int     n = mat->n;

    int     dummy1 = 0;
    int     dummy2 = 0;

    switch (OPAIR(vtype, shape))
    {
    case OPAIR(int_v, matrix_full):
	el = iarray_icopy(mat->el.int_v, 0, 0, m, n);
	break;
    case OPAIR(float_v, matrix_full):
	el = iarray_fcopy(mat->el.float_v, 0, 0, m, n);
	break;
    case OPAIR(double_v, matrix_full):
	el = iarray_dcopy(mat->el.double_v, 0, 0, m, n);
	break;
    case OPAIR(int_v, matrix_lower):
    case OPAIR(int_v, matrix_symmetric):

	/* BUG ilower_dcopy(double **, int     m1, n1, m2, n2). dummy1
	 * & */
	/* dummy2 added */
	el = ilower_icopy(mat->el.int_v, 0, n, dummy1, dummy2);
	break;
    case OPAIR(float_v, matrix_lower):
    case OPAIR(float_v, matrix_symmetric):

	/* BUG ilower_dcopy(double **, int     m1, n1, m2, n2) */
	el = ilower_fcopy(mat->el.float_v, 0, n, dummy1, dummy2);
	break;
    case OPAIR(double_v, matrix_lower):
    case OPAIR(double_v, matrix_symmetric):

	/* BUG ilower_dcopy(double **, int     m1, n1, m2, n2) */
	el = ilower_dcopy(mat->el.double_v, 0, n, dummy1, dummy2);
	break;
    case OPAIR(int_v, matrix_upper):
	el = iupper_icopy(mat->el.int_v, 0, n);
	break;
    case OPAIR(float_v, matrix_upper):
	el = iupper_fcopy(mat->el.float_v, 0, n);
	break;
    case OPAIR(double_v, matrix_upper):
	el = iupper_dcopy(mat->el.double_v, 0, n);
	break;
    default:
	{
	    int     i, j;
	    Matrix *copy = matrix_alloc(m, n, mat->shape, int_v);

	    for (i = 0; i < mat->m; ++i)
		for (j = 0; j < mat->n; ++j)
		    matrix_put(matrix_get(mat, i, j), copy, i, j);
	    return (copy);
	}
    }
    return (matrix_build(m, n, mat->shape, int_v, (void *) el));
}

Matrix *fmatrix_cast(Matrix * mat)
{
    float **el;
    Vartype vtype = mat->vtype;
    Matrix_shape shape = mat->shape;
    int     m = mat->m;
    int     n = mat->n;

    int     dummy1 = 0;
    int     dummy2 = 0;

    switch (OPAIR(vtype, shape))
    {
    case OPAIR(int_v, matrix_full):
	el = farray_icopy(mat->el.int_v, 0, 0, m, n);
	break;
    case OPAIR(float_v, matrix_full):
	el = farray_fcopy(mat->el.float_v, 0, 0, m, n);
	break;
    case OPAIR(double_v, matrix_full):
	el = farray_dcopy(mat->el.double_v, 0, 0, m, n);
	break;
    case OPAIR(int_v, matrix_lower):
    case OPAIR(int_v, matrix_symmetric):

	/* BUG flower_dcopy(double **a, int m1, n1, m2, n2) */
	el = flower_icopy(mat->el.int_v, 0, n, dummy1, dummy2);
	break;
    case OPAIR(float_v, matrix_lower):
    case OPAIR(float_v, matrix_symmetric):

	/* BUG flower_dcopy(double **a, int m1, n1, m2, n2) */
	el = flower_fcopy(mat->el.float_v, 0, n, dummy1, dummy2);
	break;
    case OPAIR(double_v, matrix_lower):
    case OPAIR(double_v, matrix_symmetric):

	/* BUG flower_dcopy(double **a, int m1, n1, m2, n2) */
	el = flower_dcopy(mat->el.double_v, 0, n, dummy1, dummy2);
	break;
    case OPAIR(int_v, matrix_upper):
	el = fupper_icopy(mat->el.int_v, 0, n);
	break;
    case OPAIR(float_v, matrix_upper):
	el = fupper_fcopy(mat->el.float_v, 0, n);
	break;
    case OPAIR(double_v, matrix_upper):
	el = fupper_dcopy(mat->el.double_v, 0, n);
	break;
    default:
	{
	    int     i, j;
	    Matrix *copy = matrix_alloc(m, n, mat->shape, float_v);

	    for (i = 0; i < mat->m; ++i)
		for (j = 0; j < mat->n; ++j)
		    matrix_putf(matrix_getf(mat, i, j), copy, i, j);
	    return (copy);
	}
    }
    return (matrix_build(m, n, mat->shape, float_v, (void *) el));
}

Matrix *dmatrix_cast(Matrix * mat)
{
    double **el;
    Vartype vtype = mat->vtype;
    Matrix_shape shape = mat->shape;
    int     m = mat->m;
    int     n = mat->n;

    int     dummy1 = 0;
    int     dummy2 = 0;

    switch (OPAIR(vtype, shape))
    {
    case OPAIR(int_v, matrix_full):
	el = darray_icopy(mat->el.int_v, 0, 0, m, n);
	break;
    case OPAIR(float_v, matrix_full):
	el = darray_fcopy(mat->el.float_v, 0, 0, m, n);
	break;
    case OPAIR(double_v, matrix_full):
	el = darray_dcopy(mat->el.double_v, 0, 0, m, n);
	break;
    case OPAIR(int_v, matrix_lower):
    case OPAIR(int_v, matrix_symmetric):

	/* BUG double **dlower_dcopy(a, m1, n1, m2, n2) */
	el = dlower_icopy(mat->el.int_v, 0, n, dummy1, dummy2);
	break;
    case OPAIR(float_v, matrix_lower):
    case OPAIR(float_v, matrix_symmetric):

	/* BUG double **dlower_dcopy(a, m1, n1, m2, n2) */
	el = dlower_fcopy(mat->el.float_v, 0, n, dummy1, dummy2);
	break;
    case OPAIR(double_v, matrix_lower):
    case OPAIR(double_v, matrix_symmetric):

	/* BUG double **dlower_dcopy(a, m1, n1, m2, n2) */
	el = dlower_dcopy(mat->el.double_v, 0, n, dummy1, dummy2);
	break;
    case OPAIR(int_v, matrix_upper):
	el = dupper_icopy(mat->el.int_v, 0, n);
	break;
    case OPAIR(float_v, matrix_upper):
	el = dupper_fcopy(mat->el.float_v, 0, n);
	break;
    case OPAIR(double_v, matrix_upper):
	el = dupper_dcopy(mat->el.double_v, 0, n);
	break;
    default:
	{
	    int     i, j;
	    Matrix *copy = matrix_alloc(m, n, mat->shape, double_v);

	    for (i = 0; i < mat->m; ++i)
		for (j = 0; j < mat->n; ++j)
		    matrix_putf(matrix_getf(mat, i, j), copy, i, j);
	    return (copy);
	}
    }
    return (matrix_build(m, n, mat->shape, double_v, (void *) el));
}
