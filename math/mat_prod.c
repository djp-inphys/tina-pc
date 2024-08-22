/**@(#)Matrix multiplication (various types and shapes)
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

int     matrix_get();

void    matrix_put();
void    matrix_putf();

Matrix *matrix_alloc();
Matrix *matrix_copy();
Matrix *matrix_cast_fill();

Vartype matrix_sup_vtype();

Matrix *imatrix_prod(Matrix * mat1, Matrix * mat2);
Matrix *fmatrix_prod(Matrix * mat1, Matrix * mat2);
Matrix *dmatrix_prod(Matrix * mat1, Matrix * mat2);

Matrix *matrix_prod(Matrix * mat1, Matrix * mat2)
{
    Matrix *prod;
    Matrix *m1;
    Matrix *m2;
    Vartype vtype;

    if (mat1 == NULL)
	return (NULL);
    if (mat2 == NULL)
	return (NULL);

    /** choose type of product: e.g. int*float = float, etc. **/

    vtype = matrix_sup_vtype(mat1->vtype, mat2->vtype);

    /** make copy of required type if necessary **/

    m1 = matrix_cast_fill(mat1, vtype);
    m2 = matrix_cast_fill(mat2, vtype);

    switch (vtype)
    {
    case int_v:
	prod = imatrix_prod(m1, m2);
	break;
    case float_v:
	prod = fmatrix_prod(m1, m2);
	break;
    case double_v:
	prod = dmatrix_prod(m1, m2);
	break;
    }

    /** free copies **/

    matrix_free(m1);
    matrix_free(m2);

    return (prod);
}

Matrix *imatrix_prod(Matrix * mat1, Matrix * mat2)
{
    Matrix *prod;
    int   **el1, **el2, **el3;
    int     sum;
    int     m, n1, n;
    int     i, j, k;

    if (mat1 == NULL || mat2 == NULL)
	return (NULL);

    if ((n1 = mat1->n) != mat2->m)
    {
	error("imatrix_prod: sizes not matched", warning);
	return (NULL);
    }
    m = mat1->m;
    n = mat2->n;
    prod = matrix_alloc(m, n, matrix_full, int_v);

    el1 = mat1->el.int_v;
    el2 = mat2->el.int_v;
    el3 = prod->el.int_v;

    for (i = 0; i < m; i++)
	for (j = 0; j < n; j++)
	{
	    sum = 0;
	    for (k = 0; k < n1; k++)
		sum += el1[i][k] * el2[k][j];
	    el3[i][j] = sum;
	}

    return (prod);
}

Matrix *fmatrix_prod(Matrix * mat1, Matrix * mat2)
{
    Matrix *prod;
    float **el1, **el2, **el3;
    double   sum;
    int     m, n1, n;
    int     i, j, k;

    if (mat1 == NULL || mat2 == NULL)
	return (NULL);

    if ((n1 = mat1->n) != mat2->m)
    {
	error("fmatrix_prod: sizes not matched", warning);
	return (NULL);
    }
    m = mat1->m;
    n = mat2->n;
    prod = matrix_alloc(m, n, matrix_full, float_v);

    el1 = mat1->el.float_v;
    el2 = mat2->el.float_v;
    el3 = prod->el.float_v;

    for (i = 0; i < m; i++)
	for (j = 0; j < n; j++)
	{
	    sum = 0.0;
	    for (k = 0; k < n1; k++)
		sum += el1[i][k] * el2[k][j];
	    el3[i][j] = sum;
	}

    return (prod);
}

Matrix *dmatrix_prod(Matrix * mat1, Matrix * mat2)
{
    Matrix *prod;
    double **el1, **el2, **el3;
    double  sum;
    int     m, n1, n;
    int     i, j, k;

    if (mat1 == NULL || mat2 == NULL)
	return (NULL);

    if ((n1 = mat1->n) != mat2->m)
    {
	error("imatrix_prod: sizes not matched", warning);
	return (NULL);
    }
    m = mat1->m;
    n = mat2->n;
    prod = matrix_alloc(m, n, matrix_full, double_v);

    el1 = mat1->el.double_v;
    el2 = mat2->el.double_v;
    el3 = prod->el.double_v;

    for (i = 0; i < m; i++)
	for (j = 0; j < n; j++)
	{
	    sum = 0.0;
	    for (k = 0; k < n1; k++)
		sum += el1[i][k] * el2[k][j];
	    el3[i][j] = sum;
	}

    return (prod);
}
