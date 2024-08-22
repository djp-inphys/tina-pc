/**@(#)Matrix multiplication (various types and shapes)
**/

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

Vector *imatrix_vprod();
Vector *fmatrix_vprod();
Vector *dmatrix_vprod();

#ifdef _ICC
#define matrix_tensor mat_tensor
#endif

Matrix *matrix_tensor(Vector * v1, Vector * v2)
{
    Matrix *m;
    Vartype vtype;
    int     i, j;

    if (v1 == NULL || v2 == NULL)
	return (NULL);

    /** choose type of product: e.g. int*float = float, etc. **/

    vtype = matrix_sup_vtype(v1->vtype, v1->vtype);
    m = matrix_alloc(v1->n, v2->n, matrix_full, vtype);
    if (vtype == complex_v)
	for (i = 0; i < v1->n; i++)
	    for (j = 0; j < v2->n; j++)
	    {
		Complex v1i = {Complex_id};
		Complex v2j = {Complex_id};

		VECTOR_GETZ(v1, i, v1i);
		VECTOR_GETZ(v2, j, v2j);
		matrix_putz(cmplx_prod(v1i, v2j), m, i, j);
	    }
    else
	for (i = 0; i < v1->n; i++)
	    for (j = 0; j < v2->n; j++)
	    {
		double  v1i, v2j;

		VECTOR_GET(v1, i, v1i);
		VECTOR_GET(v2, j, v2j);
		matrix_putf(v1i * v2j, m, i, j);
	    }
    return (m);
}
