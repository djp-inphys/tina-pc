/**@(#)Matrix elements setting. (Setting locations outside matrix is not an error).
 */

#include <math.h>
#include <stdio.h>
#include <tina/sys.h>
#include <tina/math.h>

void    matrix_put_full(int val, Matrix * mat, int i, int j);
void    matrix_putf_full(double val, Matrix * mat, int i, int j);
void    matrix_putz_full(Complex val, Matrix * mat, int i, int j);
void    matrix_putp_full(void *val, Matrix * mat, int i, int j);
Complex cmplx();

/** puts integer value into matrix, casting if necessary **/

void    mat_putf(float val, Matrix * mat, int i, int j)
{
    if (i < 0 || i >= mat->m || j < 0 || j >= mat->n)
	return;
    mat->el.float_v[i][j] = val;
}

void    matrix_put(int val, Matrix * mat, int i, int j)
{
    if (mat == NULL)
	return;

    if (i < 0 || i >= mat->m || j < 0 || j >= mat->n)
	return;

    switch (mat->shape)
    {
    case matrix_full:
	matrix_put_full(val, mat, i, j);
	break;
    case matrix_lower:
    case matrix_symmetric:
	if (i < j)
	    SWAP(int, i, j);
	matrix_put_full(val, mat, i, j);
	break;
    case matrix_upper:
	if (j < i)
	    SWAP(int, i, j);
	matrix_put_full(val, mat, i, j);
	break;
    }
}

void    matrix_put_full(int val, Matrix * mat, int i, int j)
{
    switch (mat->vtype)
    {
	case char_v:
	mat->el.char_v[i][j] = (char) val;
	break;
    case uchar_v:
	mat->el.uchar_v[i][j] = (unsigned char) val;
	break;
    case short_v:
	mat->el.short_v[i][j] = (short) val;
	break;
    case ushort_v:
	mat->el.ushort_v[i][j] = (unsigned short) val;
	break;
    case int_v:
	mat->el.int_v[i][j] = (int) val;
	break;
    case uint_v:
	mat->el.uint_v[i][j] = (unsigned int) val;
	break;
    case float_v:
	mat->el.float_v[i][j] = (float) val;
	break;
    case double_v:
	mat->el.double_v[i][j] = (double) val;
	break;
    case complex_v:
	mat->el.complex_v[i][j] = cmplx((double) val, 0.0);
	break;
    case ptr_v:
	mat->el.ptr_v[i][j] = (void *) val;
	break;
    }
}

/** puts double value into matrix, casting if necessary **/

void    matrix_putf(double val, Matrix * mat, int i, int j)
{
    if (mat == NULL)
	return;

    if (i < 0 || i >= mat->m || j < 0 || j >= mat->n)
	return;

    switch (mat->shape)
    {
    case matrix_full:
	matrix_putf_full(val, mat, i, j);
	break;
    case matrix_lower:
    case matrix_symmetric:
	if (i < j)
	    SWAP(int, i, j);
	matrix_putf_full(val, mat, i, j);
	break;
    case matrix_upper:
	if (j < i)
	    SWAP(int, i, j);
	matrix_putf_full(val, mat, i, j);
	break;
    }
}

void    matrix_putf_full(double val, Matrix * mat, int i, int j)
{
    switch (mat->vtype)
    {
	case char_v:
	mat->el.char_v[i][j] = (char) val;
	break;
    case uchar_v:
	mat->el.uchar_v[i][j] = (unsigned char) val;
	break;
    case short_v:
	mat->el.short_v[i][j] = (short) val;
	break;
    case ushort_v:
	mat->el.ushort_v[i][j] = (unsigned short) val;
	break;
    case int_v:
	mat->el.int_v[i][j] = (int) val;
	break;
    case uint_v:
	mat->el.uint_v[i][j] = (unsigned int) val;
	break;
    case float_v:
	mat->el.float_v[i][j] = (float) val;
	break;
    case double_v:
	mat->el.double_v[i][j] = (double) val;
	break;
    case complex_v:
	mat->el.complex_v[i][j] = cmplx((double) val, 0.0);
	break;
    case ptr_v:
	mat->el.ptr_v[i][j] = (void *) (int) val;
	break;
    }
}

/** puts complex value into matrix, casting if necessary **/

void    matrix_putz(Complex val, Matrix * mat, int i, int j)
{
    if (mat == NULL)
	return;

    if (i < 0 || i >= mat->m || j < 0 || j >= mat->n)
	return;

    switch (mat->shape)
    {
    case matrix_full:
	matrix_putz_full(val, mat, i, j);
	break;
    case matrix_lower:
    case matrix_symmetric:
	if (i < j)
	    SWAP(int, i, j);
	matrix_putz_full(val, mat, i, j);
	break;
    case matrix_upper:
	if (j < i)
	    SWAP(int, i, j);
	matrix_putz_full(val, mat, i, j);
	break;
    }
}

void    matrix_putz_full(Complex val, Matrix * mat, int i, int j)
{
    switch (mat->vtype)
    {
	case char_v:
	mat->el.char_v[i][j] = (char) val.x;
	break;
    case uchar_v:
	mat->el.uchar_v[i][j] = (unsigned char) val.x;
	break;
    case short_v:
	mat->el.short_v[i][j] = (short) val.x;
	break;
    case ushort_v:
	mat->el.ushort_v[i][j] = (unsigned short) val.x;
	break;
    case int_v:
	mat->el.int_v[i][j] = (int) val.x;
	break;
    case uint_v:
	mat->el.uint_v[i][j] = (unsigned int) val.x;
	break;
    case float_v:
	mat->el.float_v[i][j] = (float) val.x;
	break;
    case double_v:
	mat->el.double_v[i][j] = (double) val.x;
	break;
    case complex_v:
	mat->el.complex_v[i][j] = val;
	break;
    case ptr_v:
	mat->el.ptr_v[i][j] = (void *) (int) val.x;
	break;
    }
}

/** puts ptr value into matrix, casting if necessary **/

void    matrix_putp(void *val, Matrix * mat, int i, int j)
{
    if (mat == NULL)
	return;

    if (i < 0 || i >= mat->m || j < 0 || j >= mat->n)
	return;

    switch (mat->shape)
    {
    case matrix_full:
	matrix_putp_full(val, mat, i, j);
	break;
    case matrix_lower:
    case matrix_symmetric:
	if (i < j)
	    SWAP(int, i, j);
	matrix_putp_full(val, mat, i, j);
	break;
    case matrix_upper:
	if (j < i)
	    SWAP(int, i, j);
	matrix_putp_full(val, mat, i, j);
	break;
    }
}

void    matrix_putp_full(void *val, Matrix * mat, int i, int j)
{
    switch (mat->vtype)
    {
	/* cast twice to avoid compiler warning: cast from pointer to
	 * integer of different size */
	case char_v:
	mat->el.char_v[i][j] = (char) (int) val;
	break;
    case uchar_v:
	mat->el.uchar_v[i][j] = (unsigned char) (int) val;
	break;
    case short_v:
	mat->el.short_v[i][j] = (short) (int) val;
	break;
    case ushort_v:
	mat->el.ushort_v[i][j] = (unsigned short) (int) val;
	break;
    case int_v:
	mat->el.int_v[i][j] = (int) val;
	break;
    case uint_v:
	mat->el.uint_v[i][j] = (unsigned int) val;
	break;
    case float_v:
	mat->el.float_v[i][j] = (float) (int) val;
	break;
    case double_v:
	mat->el.double_v[i][j] = (double) (int) val;
	break;
    case complex_v:
	mat->el.complex_v[i][j] = cmplx((double) (int) val, 0.0);
	break;
    case ptr_v:
	mat->el.ptr_v[i][j] = val;
	break;
    }
}
