/**@(#)Matrix multiply (various)
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

Vector *imatrix_vprod(Matrix * mat, Vector * vec);
Vector *fmatrix_vprod(Matrix * mat, Vector * vec);
Vector *dmatrix_vprod(Matrix * mat, Vector * vec);

Vector *matrix_vprod(Matrix * mat, Vector * vec)
{
    Matrix *m;
    Vector *u;
    Vector *v;
    Vartype vtype;

    if (mat == NULL || vec == NULL)
	return (NULL);

    /** choose type of product: e.g. int*float = float, etc. **/

    vtype = matrix_sup_vtype(mat->vtype, vec->vtype);

    /** make copy of required type **/

    m = matrix_cast_fill(mat, vtype);
    v = vector_cast(vec, vtype);

    switch (vtype)
    {
    case int_v:
	u = imatrix_vprod(m, v);
	break;
    case float_v:
	u = fmatrix_vprod(m, v);
	break;
    case double_v:
	u = dmatrix_vprod(m, v);
	break;
    default:
	u = NULL;
	break;
    }

    /** free copies **/

    matrix_free(m);
    vector_free(v);

    return (u);
}

Vector *imatrix_vprod(Matrix * mat, Vector * vec)
{
    Vector *prod;
    int   **el1, *el2, *el3;
    int     sum;
    int     m, n;
    int     i, j;

    if (mat == NULL || vec == NULL)
	return (NULL);

    m = mat->m;
    n = MIN(mat->n, vec->n);
    prod = vector_alloc(m, int_v);

    el1 = mat->el.int_v;
    el2 = vec->data;
    el3 = prod->data;

    for (i = 0; i < m; i++)
    {
	sum = 0;
	for (j = 0; j < n; j++)
	    sum += el1[i][j] * el2[j];
	el3[i] = sum;
    }

    return (prod);
}

Vector *fmatrix_vprod(Matrix * mat, Vector * vec)
{
    Vector *prod;
    float **el1, *el2, *el3;
    double   sum;
    int     m, n;
    int     i, j;

    if (mat == NULL || vec == NULL)
	return (NULL);

    m = mat->m;
    n = MIN(mat->n, vec->n);
    prod = vector_alloc(m, float_v);

    el1 = mat->el.float_v;
    el2 = vec->data;
    el3 = prod->data;

    for (i = 0; i < m; i++)
    {
	sum = 0.0;
	for (j = 0; j < n; j++)
	    sum += el1[i][j] * el2[j];
	el3[i] = sum;
    }

    return (prod);
}

Vector *dmatrix_vprod(Matrix * mat, Vector * vec)
{
    Vector *prod;
    double **el1, *el2, *el3;
    double  sum;
    int     m, n;
    int     i, j;

    if (mat == NULL || vec == NULL)
	return (NULL);

    m = mat->m;
    n = MIN(mat->n, vec->n);
    prod = vector_alloc(m, double_v);

    el1 = mat->el.double_v;
    el2 = vec->data;
    el3 = prod->data;

    for (i = 0; i < m; i++)
    {
	sum = 0.0;
	for (j = 0; j < n; j++)
	    sum += el1[i][j] * el2[j];
	el3[i] = sum;
    }

    return (prod);
}
