/**@(#)Multiply an integer matrix by an integer
 */

#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

int     matrix_get();
Matrix *matrix_alloc();

Matrix *matrix_itimes(int k, Matrix * mat)
{
    Matrix *prod;
    int     m, n, i, j;
    int   **el1, **el2;

    if (mat == NULL)
	return (NULL);

    m = mat->m;
    n = mat->n;
    el1 = mat->el.int_v;

    switch (mat->shape)
    {
    case matrix_full:
	prod = matrix_alloc(m, n, matrix_full, int_v);
	el2 = prod->el.int_v;
	for (i = 0; i < m; ++i)
	    for (j = 0; j < n; ++j)
		el2[i][j] = k * el1[i][j];
	break;
    case matrix_lower:
	prod = matrix_alloc(m, n, matrix_lower, int_v);
	el2 = prod->el.int_v;
	for (i = 0; i < m; ++i)
	    for (j = 0; j <= i; ++j)
		el2[i][j] = k * el1[i][j];
	break;
    case matrix_upper:
	prod = matrix_alloc(m, n, matrix_upper, int_v);
	el2 = prod->el.int_v;
	for (i = 0; i < m; ++i)
	    for (j = i; j < n; ++j)
		el2[i][j] = k * el1[i][j];
	break;
    case matrix_symmetric:
	prod = matrix_alloc(m, n, matrix_symmetric, int_v);
	el2 = prod->el.int_v;
	for (i = 0; i < m; ++i)
	    for (j = 0; j <= i; ++j)
		el2[i][j] = k * el1[i][j];
	break;
    default:
	prod = matrix_alloc(m, n, matrix_full, int_v);
	for (i = 0; i < m; ++i)
	    for (j = 0; j < n; ++j)
		matrix_put(k * matrix_get(mat, i, j), prod, i, j);
	break;
    }

    return (prod);
}
