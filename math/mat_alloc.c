/**@(#)Matrix allocation: function (various types and shapes)
 */

#include <math.h>
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>

Matrix *cmatrix_alloc(int m, int n, Matrix_shape shape, Vartype vtype);
Matrix *smatrix_alloc(int m, int n, Matrix_shape shape, Vartype vtype);
Matrix *imatrix_alloc(int m, int n, Matrix_shape shape, Vartype vtype);
Matrix *fmatrix_alloc(int m, int n, Matrix_shape shape, Vartype vtype);
Matrix *dmatrix_alloc(int m, int n, Matrix_shape shape, Vartype vtype);
Matrix *zmatrix_alloc(int m, int n, Matrix_shape shape, Vartype vtype);
Matrix *pmatrix_alloc(int m, int n, Matrix_shape shape, Vartype vtype);

Matrix *mat_alloc(int m, int n)
{
    Matrix *mat;

    mat = ts_ralloc(Matrix);
    mat->m = m;
    mat->n = n;
    mat->shape = matrix_full;
    mat->vtype = float_v;
    mat->el.float_v = farray_alloc(0, 0, m, n);
    return (mat);
}

Matrix *matrix_alloc(int m, int n, Matrix_shape shape, Vartype vtype)
{
    if (m < 0 || n < 0)
    {
	error("matrix_alloc: bad size", non_fatal);
	return (NULL);
    }
    if (m == 0 || n == 0)
    {
	error("matrix_alloc: zero size", warning);
	return (NULL);
    }
    switch (vtype)
    {
    case char_v:
    case uchar_v:
	return (cmatrix_alloc(m, n, shape, vtype));
    case short_v:
    case ushort_v:
	return (smatrix_alloc(m, n, shape, vtype));
    case int_v:
    case uint_v:
	return (imatrix_alloc(m, n, shape, vtype));
    case float_v:
	return (fmatrix_alloc(m, n, shape, vtype));
    case double_v:
	return (dmatrix_alloc(m, n, shape, vtype));
    case complex_v:
	return (zmatrix_alloc(m, n, shape, vtype));
    case ptr_v:
	return (pmatrix_alloc(m, n, shape, vtype));
    }
    error("matrix_alloc: no such vtype", non_fatal);
    return (NULL);
}

Matrix *cmatrix_alloc(int m, int n, Matrix_shape shape, Vartype vtype)
{
    Matrix *mat;

    mat = ts_ralloc(Matrix);
    mat->m = m;
    mat->n = n;
    mat->shape = shape;
    mat->vtype = vtype;
    switch (shape)
    {
    case matrix_full:
	mat->el.char_v = carray_alloc(0, 0, m, n);
	break;
    case matrix_lower:
    case matrix_symmetric:
	mat->el.char_v = clower_alloc(0, m);
	break;
    case matrix_upper:
	mat->el.char_v = cupper_alloc(0, m);
	break;
    default:			/** full **/
	mat->el.char_v = carray_alloc(0, 0, m, n);
	break;
    }
    return (mat);
}

Matrix *smatrix_alloc(int m, int n, Matrix_shape shape, Vartype vtype)
{
    Matrix *mat;

    mat = ts_ralloc(Matrix);
    mat->m = m;
    mat->n = n;
    mat->shape = shape;
    mat->vtype = vtype;
    switch (shape)
    {
    case matrix_full:
	mat->el.short_v = sarray_alloc(0, 0, m, n);
	break;
    case matrix_lower:
    case matrix_symmetric:
	mat->el.short_v = slower_alloc(0, m);
	break;
    case matrix_upper:
	mat->el.short_v = supper_alloc(0, m);
	break;
    default:			/** full **/
	mat->el.short_v = sarray_alloc(0, 0, m, n);
	break;
    }
    return (mat);
}

Matrix *imatrix_alloc(int m, int n, Matrix_shape shape, Vartype vtype)
{
    Matrix *mat;

    mat = ts_ralloc(Matrix);
    mat->m = m;
    mat->n = n;
    mat->shape = shape;
    mat->vtype = vtype;
    switch (shape)
    {
    case matrix_full:
	mat->el.int_v = iarray_alloc(0, 0, m, n);
	break;
    case matrix_lower:
    case matrix_symmetric:
	mat->el.int_v = ilower_alloc(0, m);
	break;
    case matrix_upper:
	mat->el.int_v = iupper_alloc(0, m);
	break;
    default:			/** full **/
	mat->el.int_v = iarray_alloc(0, 0, m, n);
	break;
    }
    return (mat);
}

Matrix *fmatrix_alloc(int m, int n, Matrix_shape shape, Vartype vtype)
{
    Matrix *mat;

    mat = ts_ralloc(Matrix);
    mat->m = m;
    mat->n = n;
    mat->shape = shape;
    mat->vtype = vtype;
    switch (shape)
    {
    case matrix_full:
	mat->el.float_v = farray_alloc(0, 0, m, n);
	break;
    case matrix_lower:
    case matrix_symmetric:
	mat->el.float_v = flower_alloc(0, m);
	break;
    case matrix_upper:
	mat->el.float_v = fupper_alloc(0, m);
	break;
    default:			/** full **/
	mat->el.float_v = farray_alloc(0, 0, m, n);
	break;
    }
    return (mat);
}

Matrix *dmatrix_alloc(int m, int n, Matrix_shape shape, Vartype vtype)
{
    Matrix *mat;

    mat = ts_ralloc(Matrix);
    mat->m = m;
    mat->n = n;
    mat->shape = shape;
    mat->vtype = vtype;
    switch (shape)
    {
    case matrix_full:
	mat->el.double_v = darray_alloc(0, 0, m, n);
	break;
    case matrix_lower:
    case matrix_symmetric:
	mat->el.double_v = dlower_alloc(0, m);
	break;
    case matrix_upper:
	mat->el.double_v = dupper_alloc(0, m);
	break;
    default:			/** full **/
	mat->el.double_v = darray_alloc(0, 0, m, n);
	break;
    }
    return (mat);
}

Matrix *zmatrix_alloc(int m, int n, Matrix_shape shape, Vartype vtype)
{
    Matrix *mat;

    mat = ts_ralloc(Matrix);
    mat->m = m;
    mat->n = n;
    mat->shape = shape;
    mat->vtype = vtype;
    switch (shape)
    {
    case matrix_full:
	mat->el.complex_v = zarray_alloc(0, 0, m, n);
	break;
    case matrix_lower:
    case matrix_symmetric:
	mat->el.complex_v = zlower_alloc(0, m);
	break;
    case matrix_upper:
	mat->el.complex_v = zupper_alloc(0, m);
	break;
    default:			/** full **/
	mat->el.complex_v = zarray_alloc(0, 0, m, n);
	break;
    }
    return (mat);
}

Matrix *pmatrix_alloc(int m, int n, Matrix_shape shape, Vartype vtype)
{
    Matrix *mat;

    mat = ts_ralloc(Matrix);
    mat->m = m;
    mat->n = n;
    mat->shape = shape;
    mat->vtype = vtype;
    switch (shape)
    {
    case matrix_full:
	mat->el.ptr_v = parray_alloc(0, 0, m, n);
	break;
    case matrix_lower:
    case matrix_symmetric:
	mat->el.ptr_v = plower_alloc(0, m);
	break;
    case matrix_upper:
	mat->el.ptr_v = pupper_alloc(0, m);
	break;
    default:			/** full **/
	mat->el.ptr_v = parray_alloc(0, 0, m, n);
	break;
    }
    return (mat);
}
