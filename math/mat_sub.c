/**@(#)Matrix subtraction
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

int     matrix_get();
double  matrix_getf();

void    matrix_put();
void    matrix_putf();

Matrix *matrix_alloc();
Matrix *matrix_copy();
Matrix *matrix_cast_fill();
Matrix *matrix_minus();

Vartype matrix_sup_vtype();

Matrix *imatrix_sub(Matrix * mat1, Matrix * mat2);
Matrix *fmatrix_sub(Matrix * mat1, Matrix * mat2);
Matrix *dmatrix_sub(Matrix * mat1, Matrix * mat2);

Matrix *matrix_diff(Matrix * mat1, Matrix * mat2)
{
    return (matrix_sub(mat1, mat2));
}

Matrix *matrix_sub(Matrix * mat1, Matrix * mat2)
{
    Matrix *diff;
    Matrix *m1;
    Matrix *m2;
    Vartype vtype;

    if (mat1 == NULL)
	return (matrix_minus(mat2));
    if (mat2 == NULL)
	return (matrix_copy(mat1));

    /** choose type of diff: e.g. int-float = float, etc. **/

    vtype = matrix_sup_vtype(mat1->vtype, mat2->vtype);

    m1 = matrix_cast_fill(mat1, vtype);
    m2 = matrix_cast_fill(mat2, vtype);

    switch (vtype)
    {
    case int_v:
	diff = imatrix_sub(m1, m2);
	break;
    case float_v:
	diff = fmatrix_sub(m1, m2);
	break;
    case double_v:
	diff = dmatrix_sub(m1, m2);
	break;
    }

    /** free copies  **/

    matrix_free((Matrix *) m1);
    matrix_free((Matrix *) m2);

    return (diff);
}

Matrix *imatrix_sub(Matrix * mat1, Matrix * mat2)
{
    Matrix *diff;
    int   **el1, **el2, **el3;
    int     m, n;
    int     i, j;

    if (mat1 == NULL)
	return (matrix_minus(mat2));
    if (mat2 == NULL)
	return (matrix_copy(mat1));

    if (mat1->m != mat2->m || mat1->n != mat2->n)
    {
	error("imatrix_add: sizes not matched", warning);
	return (NULL);
    }
    m = mat1->m;
    n = mat1->n;
    diff = matrix_alloc(m, n, matrix_full, int_v);

    el1 = mat1->el.int_v;
    el2 = mat2->el.int_v;
    el3 = diff->el.int_v;

    for (i = 0; i < m; i++)
	for (j = 0; j < n; j++)
	    el3[i][j] = el1[i][j] - el2[i][j];

    return (diff);
}

Matrix *fmatrix_sub(Matrix * mat1, Matrix * mat2)
{
    Matrix *diff;
    float **el1, **el2, **el3;
    int     m, n;
    int     i, j;

    if (mat1 == NULL)
	return (matrix_minus(mat2));
    if (mat2 == NULL)
	return (matrix_copy(mat1));

    if (mat1->m != mat2->m || mat1->n != mat2->n)
    {
	error("imatrix_add: sizes not matched", warning);
	return (NULL);
    }
    m = mat1->m;
    n = mat1->n;
    diff = matrix_alloc(m, n, matrix_full, float_v);

    el1 = mat1->el.float_v;
    el2 = mat2->el.float_v;
    el3 = diff->el.float_v;

    for (i = 0; i < m; i++)
	for (j = 0; j < n; j++)
	    el3[i][j] = el1[i][j] - el2[i][j];

    return (diff);
}

Matrix *dmatrix_sub(Matrix * mat1, Matrix * mat2)
{
    Matrix *diff;
    double **el1, **el2, **el3;
    int     m, n;
    int     i, j;

    if (mat1 == NULL)
	return (matrix_minus(mat2));
    if (mat2 == NULL)
	return (matrix_copy(mat1));

    if (mat1->m != mat2->m || mat1->n != mat2->n)
    {
	error("imatrix_add: sizes not matched", warning);
	return (NULL);
    }
    m = mat1->m;
    n = mat1->n;
    diff = matrix_alloc(m, n, matrix_full, double_v);

    el1 = mat1->el.double_v;
    el2 = mat2->el.double_v;
    el3 = diff->el.double_v;

    for (i = 0; i < m; i++)
	for (j = 0; j < n; j++)
	    el3[i][j] = el1[i][j] - el2[i][j];

    return (diff);
}

Matrix *imatrix_sub_inplace(Matrix * mat1, Matrix * mat2)
{
    int   **el1, **el2;
    int     m, n;
    int     i, j;

    if (mat1 == NULL || mat2 == NULL)
	return (mat1);

    if (mat1->m != mat2->m || mat1->n != mat2->n)
    {
	error("imatrix_add: sizes not matched", warning);
	return (mat1);
    }
    m = mat1->m;
    n = mat1->n;

    el1 = mat1->el.int_v;
    el2 = mat2->el.int_v;

    for (i = 0; i < m; i++)
	for (j = 0; j < n; j++)
	    el1[i][j] = el1[i][j] - el2[i][j];

    return (mat1);
}

Matrix *fmatrix_sub_inplace(Matrix * mat1, Matrix * mat2)
{
    float **el1, **el2;
    int     m, n;
    int     i, j;

    if (mat1 == NULL || mat2 == NULL)
	return (mat1);

    if (mat1->m != mat2->m || mat1->n != mat2->n)
    {
	error("imatrix_add: sizes not matched", warning);
	return (mat1);
    }
    m = mat1->m;
    n = mat1->n;

    el1 = mat1->el.float_v;
    el2 = mat2->el.float_v;

    for (i = 0; i < m; i++)
	for (j = 0; j < n; j++)
	    el1[i][j] = el1[i][j] - el2[i][j];

    return (mat1);
}

Matrix *dmatrix_sub_inplace(Matrix * mat1, Matrix * mat2)
{
    double **el1, **el2;
    int     m, n;
    int     i, j;

    if (mat1 == NULL || mat2 == NULL)
	return (mat1);

    if (mat1->m != mat2->m || mat1->n != mat2->n)
    {
	error("imatrix_add: sizes not matched", warning);
	return (mat1);
    }
    m = mat1->m;
    n = mat1->n;

    el1 = mat1->el.double_v;
    el2 = mat2->el.double_v;

    for (i = 0; i < m; i++)
	for (j = 0; j < n; j++)
	    el1[i][j] = el1[i][j] - el2[i][j];

    return (mat1);
}
