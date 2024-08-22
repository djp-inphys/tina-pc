/**@(#)Matrix handling (various types and shapes)
 */

#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

void    matrix_putf();

Matrix_shape matrix_sup_shape(Matrix_shape shape1, Matrix_shape shape2)
{
    if (shape1 != shape2)
	return (matrix_full);
    else
	return (shape1);
}

Vartype matrix_sup_vtype(Vartype vtype1, Vartype vtype2)
{
    if (vtype1 == double_v || vtype2 == double_v)
	return (double_v);
    if (vtype1 == float_v || vtype2 == float_v)
	return (float_v);
    return (int_v);
}

int     matrix_swap_rows(Matrix * mat, int r1, int r2)
{
    int     m, n;
    int     i;

    if (mat == NULL || mat->shape != matrix_full)
	return (0);

    m = mat->m;
    n = mat->n;

    if (r1 < 0 || r1 >= m || r2 < 0 || r2 > m)
	return (0);

    for (i = 0; i < n; ++i)
    {
	double  temp;

	temp = matrix_getf(mat, r1, i);
	matrix_putf(matrix_getf(mat, r2, i), mat, r1, i);
	matrix_putf(temp, mat, r2, i);
    }
    return (1);
}

int     matrix_swap_cols(Matrix * mat, int c1, int c2)
{
    int     m, n;
    int     i;

    if (mat == NULL || mat->shape != matrix_full)
	return (0);

    m = mat->m;
    n = mat->n;

    if (c1 < 0 || c1 >= n || c2 < 0 || c2 > n)
	return (0);

    for (i = 0; i < m; ++i)
    {
	double  temp;

	temp = matrix_getf(mat, i, c1);
	matrix_putf(matrix_getf(mat, i, c2), mat, i, c1);
	matrix_putf(temp, mat, i, c2);
    }
    return (1);
}

Vector *matrix_col_vector(Matrix * mat, int c)
{
    Vector *col;
    Vector *vector_alloc();
    int     m, n;
    int     i;

    if (mat == NULL)
	return (NULL);

    m = mat->m;
    n = mat->n;

    if (c < 0 || c >= n)
	return (NULL);

    col = vector_alloc(m, mat->vtype);

    for (i = 0; i < m; ++i)
    {
	vector_putf(matrix_getf(mat, i, c), col, i);
    }
    return (col);
}
