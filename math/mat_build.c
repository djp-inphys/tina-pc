/**@(#)Build Matrices of various types and shapes around already allocated arrays
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>

Matrix *matrix_build(int m, int n, Matrix_shape shape, Vartype vtype, void *el)
{
    Matrix *mat;

    if (m < 0 || n < 0)
    {
	error("matrix_build: bad size", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("matrix_build: zero size", warning);
	return (NULL);
    }
    if (el == NULL)
    {
	error("matrix_build: null array", non_fatal);
	return (NULL);
    }
    mat = ts_ralloc(Matrix);
    mat->m = m;
    mat->n = n;
    mat->shape = shape;
    mat->vtype = vtype;
    switch (mat->vtype)
    {
    case int_v:
	mat->el.int_v = (int **) el;
	break;
    case float_v:
	mat->el.float_v = (float **) el;
	break;
    case double_v:
	mat->el.double_v = (double **) el;
	break;
    }
    return (mat);
}
