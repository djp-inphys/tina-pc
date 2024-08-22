/**@(#)Matrix input/output (various types and shapes)
 */

#include <stdio.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

void    imatrix_print(FILE * fp, Matrix * mat);
void    fmatrix_print(FILE * fp, Matrix * mat);
void    dmatrix_print(FILE * fp, Matrix * mat);
void    imatrix_pprint(FILE * fp, Matrix * mat);
void    fmatrix_pprint(FILE * fp, Matrix * mat);
void    dmatrix_pprint(FILE * fp, Matrix * mat);

void    matrix_print(FILE * fp, Matrix * mat)
{
    (void) fprintf(fp, "matrix ");

    if (mat == NULL)
    {
	(void) fprintf(fp, "nil ");
	return;
    }
    switch (mat->vtype)
    {
    case int_v:
	imatrix_print(fp, mat);
	break;
    case float_v:
	fmatrix_print(fp, mat);
	break;
    case double_v:
	dmatrix_print(fp, mat);
	break;
    }
}

void    imatrix_print(FILE * fp, Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    int     n = mat->n;
    int   **el = mat->el.int_v;

    (void) fprintf(fp, "int ");
    switch (mat->shape)
    {
    case matrix_full:
	(void) fprintf(fp, "full ");
	(void) fprintf(fp, "%d %d ", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	    for (j = 0; j < n; ++j)
		(void) fprintf(fp, "%d ", el[i][j]);
	break;
    case matrix_lower:
	(void) fprintf(fp, "lower ");
	(void) fprintf(fp, "%d %d ", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	    for (j = 0; j <= i; ++j)
		(void) fprintf(fp, "%d ", el[i][j]);
	break;
    case matrix_upper:
	(void) fprintf(fp, "upper ");
	(void) fprintf(fp, "%d %d ", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	    for (j = i; j < m; ++j)
		(void) fprintf(fp, "%d ", el[i][j]);
	break;
    case matrix_symmetric:
	(void) fprintf(fp, "symmetric ");
	(void) fprintf(fp, "%d %d ", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	    for (j = 0; j <= i; ++j)
		(void) fprintf(fp, "%d ", el[i][j]);
	break;
    default:
	{
	    (void) fprintf(fp, "full ");
	    (void) fprintf(fp, "%d %d ", mat->m, mat->n);
	    for (i = 0; i < m; ++i)
		for (j = 0; j < n; ++j)
		    (void) fprintf(fp, "%d ", matrix_get(mat, i, j));
	}
    }
}

void    fmatrix_print(FILE * fp, Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    int     n = mat->n;
    float **el = mat->el.float_v;

    (void) fprintf(fp, "float ");
    switch (mat->shape)
    {
    case matrix_full:
	(void) fprintf(fp, "full ");
	(void) fprintf(fp, "%d %d ", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	    for (j = 0; j < n; ++j)
		(void) fprintf(fp, "%f ", el[i][j]);
	break;
    case matrix_lower:
	(void) fprintf(fp, "lower ");
	(void) fprintf(fp, "%d %d ", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	    for (j = 0; j <= i; ++j)
		(void) fprintf(fp, "%f ", el[i][j]);
	break;
    case matrix_upper:
	(void) fprintf(fp, "upper ");
	(void) fprintf(fp, "%d %d ", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	    for (j = i; j < m; ++j)
		(void) fprintf(fp, "%f ", el[i][j]);
	break;
    case matrix_symmetric:
	(void) fprintf(fp, "symmetric ");
	(void) fprintf(fp, "%d %d ", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	    for (j = 0; j <= i; ++j)
		(void) fprintf(fp, "%f ", el[i][j]);
	break;
    default:
	{
	    (void) fprintf(fp, "full ");
	    (void) fprintf(fp, "%d %d ", mat->m, mat->n);
	    for (i = 0; i < m; ++i)
		for (j = 0; j < n; ++j)
		    (void) fprintf(fp, "%f ", matrix_getf(mat, i, j));
	}
    }
}

void    dmatrix_print(FILE * fp, Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    int     n = mat->n;
    double **el = mat->el.double_v;

    (void) fprintf(fp, "double ");
    switch (mat->shape)
    {
    case matrix_full:
	(void) fprintf(fp, "full ");
	(void) fprintf(fp, "%d %d ", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	    for (j = 0; j < n; ++j)
		(void) fprintf(fp, "%f ", el[i][j]);
	break;
    case matrix_lower:
	(void) fprintf(fp, "lower ");
	(void) fprintf(fp, "%d %d ", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	    for (j = 0; j <= i; ++j)
		(void) fprintf(fp, "%f ", el[i][j]);
	break;
    case matrix_upper:
	(void) fprintf(fp, "upper ");
	(void) fprintf(fp, "%d %d ", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	    for (j = i; j < m; ++j)
		(void) fprintf(fp, "%f ", el[i][j]);
	break;
    case matrix_symmetric:
	(void) fprintf(fp, "symmetric ");
	(void) fprintf(fp, "%d %d ", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	    for (j = 0; j <= i; ++j)
		(void) fprintf(fp, "%f ", el[i][j]);
	break;
    default:
	{
	    (void) fprintf(fp, "full ");
	    (void) fprintf(fp, "%d %d ", mat->m, mat->n);
	    for (i = 0; i < m; ++i)
		for (j = 0; j < n; ++j)
		    (void) fprintf(fp, "%f ", matrix_getf(mat, i, j));
	}
    }
}

void    matrix_pprint(FILE * fp, Matrix * mat)
{
    (void) fprintf(fp, "matrix ");

    if (mat == NULL)
    {
	(void) fprintf(fp, "nil\n");
	return;
    }
    switch (mat->vtype)
    {
    case int_v:
	imatrix_pprint(fp, mat);
	break;
    case float_v:
	fmatrix_pprint(fp, mat);
	break;
    case double_v:
	dmatrix_pprint(fp, mat);
	break;
    }
}

void    imatrix_pprint(FILE * fp, Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    int     n = mat->n;
    int   **el = mat->el.int_v;

    (void) fprintf(fp, "int ");
    switch (mat->shape)
    {
    case matrix_full:
	(void) fprintf(fp, "full ");
	(void) fprintf(fp, "%d %d\n", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	{
	    for (j = 0; j < n; ++j)
		(void) fprintf(fp, "%10d", el[i][j]);
	    (void) fprintf(fp, "\n");
	}
	break;
    case matrix_lower:
	(void) fprintf(fp, "lower ");
	(void) fprintf(fp, "%d %d\n", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	{
	    for (j = 0; j <= i; ++j)
		(void) fprintf(fp, "%10d", el[i][j]);
	    (void) fprintf(fp, "\n");
	}
	break;
    case matrix_upper:
	(void) fprintf(fp, "upper ");
	(void) fprintf(fp, "%d %d\n", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	{
	    for (j = 0; j < i; ++j)
		(void) fprintf(fp, "          ");
	    for (j = i; j < m; ++j)
		(void) fprintf(fp, "%10d", el[i][j]);
	    (void) fprintf(fp, "\n");
	}
	break;
    case matrix_symmetric:
	(void) fprintf(fp, "symmetric ");
	(void) fprintf(fp, "%d %d\n", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	{
	    for (j = 0; j <= i; ++j)
		(void) fprintf(fp, "%10d", el[i][j]);
	    (void) fprintf(fp, "\n");
	}
	break;
    default:
	(void) fprintf(fp, "full ");
	(void) fprintf(fp, "%d %d\n", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	{
	    for (j = 0; j < n; ++j)
		(void) fprintf(fp, "%10d", matrix_get(mat, i, j));
	    (void) fprintf(fp, "\n");
	}
    }
    (void) fprintf(fp, "\n");
}

void    fmatrix_pprint(FILE * fp, Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    int     n = mat->n;
    float **el = mat->el.float_v;

    (void) fprintf(fp, "float ");
    switch (mat->shape)
    {
    case matrix_full:
	(void) fprintf(fp, "full ");
	(void) fprintf(fp, "%d %d\n", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	{
	    for (j = 0; j < n; ++j)
		(void) fprintf(fp, "%15.6f", el[i][j]);
	    (void) fprintf(fp, "\n");
	}
	break;
    case matrix_lower:
	(void) fprintf(fp, "lower ");
	(void) fprintf(fp, "%d %d\n", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	{
	    for (j = 0; j <= i; ++j)
		(void) fprintf(fp, "%15.6f", el[i][j]);
	    (void) fprintf(fp, "\n");
	}
	break;
    case matrix_upper:
	(void) fprintf(fp, "upper ");
	(void) fprintf(fp, "%d %d\n", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	{
	    for (j = 0; j < i; ++j)
		(void) fprintf(fp, "               ");
	    for (j = i; j < m; ++j)
		(void) fprintf(fp, "%15.6f", el[i][j]);
	    (void) fprintf(fp, "\n");
	}
	break;
    case matrix_symmetric:
	(void) fprintf(fp, "symmetric ");
	(void) fprintf(fp, "%d %d\n", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	{
	    for (j = 0; j <= i; ++j)
		(void) fprintf(fp, "%15.6f", el[i][j]);
	    (void) fprintf(fp, "\n");
	}
	break;
    default:
	(void) fprintf(fp, "full ");
	(void) fprintf(fp, "%d %d\n", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	{
	    for (j = 0; j < n; ++j)
		(void) fprintf(fp, "%15.6f", matrix_getf(mat, i, j));
	    (void) fprintf(fp, "\n");
	}
    }
    (void) fprintf(fp, "\n");
}

void    dmatrix_pprint(FILE * fp, Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    int     n = mat->n;
    double **el = mat->el.double_v;

    (void) fprintf(fp, "double ");
    switch (mat->shape)
    {
    case matrix_full:
	(void) fprintf(fp, "full ");
	(void) fprintf(fp, "%d %d\n", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	{
	    for (j = 0; j < n; ++j)
		(void) fprintf(fp, "%15.6f", el[i][j]);
	    (void) fprintf(fp, "\n");
	}
	break;
    case matrix_lower:
	(void) fprintf(fp, "lower ");
	(void) fprintf(fp, "%d %d\n", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	{
	    for (j = 0; j <= i; ++j)
		(void) fprintf(fp, "%15.6f", el[i][j]);
	    (void) fprintf(fp, "\n");
	}
	break;
    case matrix_upper:
	(void) fprintf(fp, "upper ");
	(void) fprintf(fp, "%d %d\n", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	{
	    for (j = 0; j < i; ++j)
		(void) fprintf(fp, "               ");
	    for (j = i; j < m; ++j)
		(void) fprintf(fp, "%15.6f", el[i][j]);
	    (void) fprintf(fp, "\n");
	}
	break;
    case matrix_symmetric:
	(void) fprintf(fp, "symmetric ");
	(void) fprintf(fp, "%d %d\n", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	{
	    for (j = 0; j <= i; ++j)
		(void) fprintf(fp, "%15.6f", el[i][j]);
	    (void) fprintf(fp, "\n");
	}
	break;
    default:
	(void) fprintf(fp, "full ");
	(void) fprintf(fp, "%d %d\n", mat->m, mat->n);
	for (i = 0; i < m; ++i)
	{
	    for (j = 0; j < n; ++j)
		(void) fprintf(fp, "%15.6f", matrix_getf(mat, i, j));
	    (void) fprintf(fp, "\n");
	}
    }
    (void) fprintf(fp, "\n");
}
