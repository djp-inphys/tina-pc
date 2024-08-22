/**@(#)Matrix addition
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

Matrix *matrix_alloc();
Matrix *matrix_copy();
Matrix *matrix_cast_fill();

Vartype matrix_sup_vtype();

Matrix *imatrix_add(Matrix * mat1, Matrix * mat2);
Matrix *fmatrix_add(Matrix * mat1, Matrix * mat2);
Matrix *dmatrix_add(Matrix * mat1, Matrix * mat2);

Matrix *matrix_sum(Matrix * mat1, Matrix * mat2)
{
    Matrix *sum;
    Matrix *m1;
    Matrix *m2;
    Vartype vtype;

    if (mat1 == NULL)
	return (matrix_copy(mat2));
    if (mat2 == NULL)
	return (matrix_copy(mat1));

    /** choose type of sum: e.g. int+float = float, etc. **/

    vtype = matrix_sup_vtype(mat1->vtype, mat2->vtype);

    m1 = matrix_cast_fill(mat1, vtype);
    m2 = matrix_cast_fill(mat2, vtype);

    switch (vtype)
    {
    case int_v:
	sum = imatrix_add(m1, m2);
	break;
    case float_v:
	sum = fmatrix_add(m1, m2);
	break;
    case double_v:
	sum = dmatrix_add(m1, m2);
	break;
    }

    /** free copies **/

    matrix_free(m1);
    matrix_free(m2);

    return (sum);
}

Matrix *matrix_add(Matrix * m1, Matrix * m2)
{
    return (matrix_sum(m1, m2));
}

Matrix *imatrix_add(Matrix * mat1, Matrix * mat2)
{
    Matrix *sum;
    int   **el1, **el2, **el3;
    int     m, n;
    int     i, j;

    if (mat1 == NULL)
	return (matrix_copy(mat2));
    if (mat2 == NULL)
	return (matrix_copy(mat1));

    if (mat1->m != mat2->m || mat1->n != mat2->n)
    {
	error("imatrix_add: sizes not matched", warning);
	return (NULL);
    }
    m = mat1->m;
    n = mat1->n;
    sum = matrix_alloc(m, n, matrix_full, int_v);

    el1 = mat1->el.int_v;
    el2 = mat2->el.int_v;
    el3 = sum->el.int_v;

    for (i = 0; i < m; i++)
	for (j = 0; j < n; j++)
	    el3[i][j] = el1[i][j] + el2[i][j];

    return (sum);
}

Matrix *fmatrix_add(Matrix * mat1, Matrix * mat2)
{
    Matrix *sum;
    float **el1, **el2, **el3;
    int     m, n;
    int     i, j;

    if (mat1 == NULL)
	return (matrix_copy(mat2));
    if (mat2 == NULL)
	return (matrix_copy(mat1));

    if (mat1->m != mat2->m || mat1->n != mat2->n)
    {
	error("fmatrix_add: sizes not matched", warning);
	return (NULL);
    }
    m = mat1->m;
    n = mat1->n;
    sum = matrix_alloc(m, n, matrix_full, float_v);

    el1 = mat1->el.float_v;
    el2 = mat2->el.float_v;
    el3 = sum->el.float_v;

    for (i = 0; i < m; i++)
	for (j = 0; j < n; j++)
	    el3[i][j] = el1[i][j] + el2[i][j];

    return (sum);
}

Matrix *dmatrix_add(Matrix * mat1, Matrix * mat2)
{
    Matrix *sum;
    double **el1, **el2, **el3;
    int     m, n;
    int     i, j;

    if (mat1 == NULL)
	return (matrix_copy(mat2));
    if (mat2 == NULL)
	return (matrix_copy(mat1));

    if (mat1->m != mat2->m || mat1->n != mat2->n)
    {
	error("imatrix_add: sizes not matched", warning);
	return (NULL);
    }
    m = mat1->m;
    n = mat1->n;
    sum = matrix_alloc(m, n, matrix_full, double_v);

    el1 = mat1->el.double_v;
    el2 = mat2->el.double_v;
    el3 = sum->el.double_v;

    for (i = 0; i < m; i++)
	for (j = 0; j < n; j++)
	    el3[i][j] = el1[i][j] + el2[i][j];

    return (sum);
}

Matrix *imatrix_add_inplace(Matrix * mat1, Matrix * mat2)
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
	    el1[i][j] = el1[i][j] + el2[i][j];

    return (mat1);
}

Matrix *fmatrix_add_inplace(Matrix * mat1, Matrix * mat2)
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
	    el1[i][j] = el1[i][j] + el2[i][j];

    return (mat1);
}

Matrix *dmatrix_add_inplace(Matrix * mat1, Matrix * mat2)
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
	    el1[i][j] = el1[i][j] + el2[i][j];

    return (mat1);
}
