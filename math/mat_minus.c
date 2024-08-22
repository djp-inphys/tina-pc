/**@(#)Matrix negation. (Negate elements of matrix)
 */

#include <math.h>
#include <stdio.h>
#include <tina/sys.h>
#include <tina/math.h>

int     matrix_get();
double  matrix_getf();
void    matrix_put();
void    matrix_putf();

Matrix *matrix_copy();

Matrix *matrix_minus(Matrix * mat)
{
    int     m, n, i, j;
    Matrix *minus;

    if (mat == NULL)
	return (NULL);

    minus = matrix_copy(mat);
    m = mat->m;
    n = mat->n;

    /** explicit for standard shapes **/

    switch (OPAIR(mat->vtype, mat->shape))
    {
    case OPAIR(int_v, matrix_full):
	{
	    int   **el = minus->el.int_v;

	    for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
		    el[i][j] = -el[i][j];
	    return (minus);
	}
    case OPAIR(float_v, matrix_full):
	{
	    float **el = minus->el.float_v;

	    for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
		    el[i][j] = -el[i][j];
	    return (minus);
	}
    case OPAIR(double_v, matrix_full):
	{
	    double **el = minus->el.double_v;

	    for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
		    el[i][j] = -el[i][j];
	    return (minus);
	}
    case OPAIR(int_v, matrix_lower):
    case OPAIR(int_v, matrix_symmetric):
	{
	    int   **el = minus->el.int_v;

	    for (i = 0; i < m; i++)
		for (j = 0; j <= i; j++)
		    el[i][j] = -el[i][j];
	    return (minus);
	}
    case OPAIR(float_v, matrix_lower):
    case OPAIR(float_v, matrix_symmetric):
	{
	    float **el = minus->el.float_v;

	    for (i = 0; i < m; i++)
		for (j = 0; j <= i; j++)
		    el[i][j] = -el[i][j];
	    return (minus);
	}
    case OPAIR(double_v, matrix_lower):
    case OPAIR(double_v, matrix_symmetric):
	{
	    double **el = minus->el.double_v;

	    for (i = 0; i < m; i++)
		for (j = 0; j <= i; j++)
		    el[i][j] = -el[i][j];
	    return (minus);
	}
    case OPAIR(int_v, matrix_upper):
	{
	    int   **el = minus->el.int_v;

	    for (i = 0; i < m; i++)
		for (j = i; j < n; j++)
		    el[i][j] = -el[i][j];
	    return (minus);
	}
    case OPAIR(float_v, matrix_upper):
	{
	    float **el = minus->el.float_v;

	    for (i = 0; i < m; i++)
		for (j = i; j < n; j++)
		    el[i][j] = -el[i][j];
	    return (minus);
	}
    case OPAIR(double_v, matrix_upper):
	{
	    double **el = minus->el.double_v;

	    for (i = 0; i < m; i++)
		for (j = i; j < n; j++)
		    el[i][j] = -el[i][j];
	    return (minus);
	}
    }

    /** generic for other shapes **/

    switch (mat->vtype)
    {
    case int_v:
	for (i = 0; i < m; i++)
	    for (j = 0; j < n; j++)
		matrix_put(-matrix_get(mat, i, j), minus, i, j);
	break;
    case float_v:
    case double_v:
	for (i = 0; i < m; i++)
	    for (j = 0; j < n; j++)
		matrix_putf(-matrix_getf(mat, i, j), minus, i, j);
	break;
    }
    return (minus);
}

Matrix *fmatrix_minus(Matrix * mat)	/* assume full float matrix */

{
    int     m, n, i, j;
    Matrix *minus;
    float **el;

    if (mat == NULL)
	return (NULL);

    minus = matrix_copy(mat);
    m = mat->m;
    n = mat->n;

    el = minus->el.float_v;
    for (i = 0; i < m; i++)
	for (j = 0; j < n; j++)
	    el[i][j] = -el[i][j];
    return (minus);
}

Matrix *fmatrix_minus_inplace(Matrix * mat)	/* assume full float
						 * matrix */

{
    int     m, n, i, j;
    float **el;

    if (mat == NULL)
	return (NULL);

    m = mat->m;
    n = mat->n;

    el = mat->el.float_v;
    for (i = 0; i < m; i++)
	for (j = 0; j < n; j++)
	    el[i][j] = -el[i][j];
    return (mat);
}
