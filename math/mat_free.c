/**@(#)Matrix freeing (various types and shapes)
 */

#include <math.h>
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>

void    cmatrix_free(Matrix * mat);
void    smatrix_free(Matrix * mat);
void    imatrix_free(Matrix * mat);
void    fmatrix_free(Matrix * mat);
void    dmatrix_free(Matrix * mat);
void    zmatrix_free(Matrix * mat);
void    pmatrix_free(Matrix * mat);

void    matrix_free(Matrix * mat)
{
    if (mat == NULL)
	return;
    switch (mat->vtype)
    {
    case char_v:
    case uchar_v:
	cmatrix_free((Matrix *) mat);
	break;
    case short_v:
    case ushort_v:
	smatrix_free((Matrix *) mat);
	break;
    case int_v:
    case uint_v:
	imatrix_free((Matrix *) mat);
	break;
    case float_v:
	fmatrix_free(mat);
	break;
    case double_v:
	dmatrix_free(mat);
	break;
    case complex_v:
	zmatrix_free(mat);
	break;
    case ptr_v:
	pmatrix_free(mat);
	break;
    }
}

void    cmatrix_free(Matrix * mat)
{
    switch (mat->shape)
    {
	case matrix_full:
	carray_free((char **) mat->el.char_v, 0, 0, mat->m, mat->n);
	break;
    case matrix_lower:
    case matrix_symmetric:
	clower_free((char **) mat->el.char_v, 0, mat->m);
	break;
    case matrix_upper:
	cupper_free((char **) mat->el.char_v, 0, mat->m);
	break;
    }
    rfree((void *) mat);
}

void    smatrix_free(Matrix * mat)
{
    switch (mat->shape)
    {
	case matrix_full:
	sarray_free((char **) mat->el.short_v, 0, 0, mat->m, mat->n);
	break;
    case matrix_lower:
    case matrix_symmetric:
	slower_free((char **) mat->el.short_v, 0, mat->m);
	break;
    case matrix_upper:
	supper_free((char **) mat->el.short_v, 0, mat->m);
	break;
    }
    rfree((void *) mat);
}

void    imatrix_free(Matrix * mat)
{
    switch (mat->shape)
    {
	case matrix_full:
	iarray_free((char **) mat->el.int_v, 0, 0, mat->m, mat->n);
	break;
    case matrix_lower:
    case matrix_symmetric:
	ilower_free((char **) mat->el.int_v, 0, mat->m);
	break;
    case matrix_upper:
	iupper_free((char **) mat->el.int_v, 0, mat->m);
	break;
    }
    rfree((void *) mat);
}

void    fmatrix_free(Matrix * mat)
{
    switch (mat->shape)
    {
	case matrix_full:
	farray_free((char **) mat->el.float_v, 0, 0, mat->m, mat->n);
	break;
    case matrix_lower:
    case matrix_symmetric:
	flower_free((char **) mat->el.float_v, 0, mat->m);
	break;
    case matrix_upper:
	fupper_free((char **) mat->el.float_v, 0, mat->m);
	break;
    }
    rfree((void *) mat);
}

void    dmatrix_free(Matrix * mat)
{
    switch (mat->shape)
    {
	case matrix_full:
	darray_free((char **) mat->el.double_v, 0, 0, mat->m, mat->n);
	break;
    case matrix_lower:
    case matrix_symmetric:
	dlower_free((char **) mat->el.double_v, 0, mat->m);
	break;
    case matrix_upper:
	dupper_free((char **) mat->el.double_v, 0, mat->m);
	break;
    }
    rfree((void *) mat);
}

void    pmatrix_free(Matrix * mat)
{
    switch (mat->shape)
    {
	case matrix_full:
	parray_free((char **) mat->el.ptr_v, 0, 0, mat->m, mat->n);
	break;
    case matrix_lower:
    case matrix_symmetric:
	plower_free((char **) mat->el.ptr_v, 0, mat->m);
	break;
    case matrix_upper:
	pupper_free((char **) mat->el.ptr_v, 0, mat->m);
	break;
    }
    rfree((void *) mat);
}

void    zmatrix_free(Matrix * mat)
{
    switch (mat->shape)
    {
	case matrix_full:
	zarray_free((char **) mat->el.complex_v, 0, 0, mat->m, mat->n);
	break;
    case matrix_lower:
    case matrix_symmetric:
	zlower_free((char **) mat->el.complex_v, 0, mat->m);
	break;
    case matrix_upper:
	zupper_free((char **) mat->el.complex_v, 0, mat->m);
	break;
    }
    rfree((void *) mat);
}
