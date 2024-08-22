/**@(#)Fill Matrix (gets full copies of a matrix)
 * @(#)(slowest possible implementation (wts)
 */

#include <tina/sys.h>
#include <tina/math.h>

double  matrix_getf();
void    matrix_putf();
Matrix *matrix_alloc();

Matrix *matrix_fill(Matrix * mat)
{
    Matrix *full;
    int     n, m;
    int     i, j;

    if (mat == NULL)
	return (NULL);

    m = mat->m;
    n = mat->n;
    full = matrix_alloc(m, n, matrix_full, mat->vtype);

    if (full == NULL)
	return (NULL);

    for (i = 0; i < m; ++i)
	for (j = 0; j < n; ++j)
	    matrix_putf(matrix_getf(mat, i, j), full, i, j);
    return (full);
}

Matrix *matrix_cast_fill(Matrix * mat, Vartype vtype)
{
    Matrix *full;
    int     n, m;
    int     i, j;

    if (mat == NULL)
	return (NULL);

    m = mat->m;
    n = mat->n;
    full = matrix_alloc(m, n, matrix_full, vtype);

    if (full == NULL)
	return (NULL);

    for (i = 0; i < m; ++i)
	for (j = 0; j < n; ++j)
	    matrix_putf(matrix_getf(mat, i, j), full, i, j);
    return (full);
}
