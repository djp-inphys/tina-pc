/**@(#)Matrix element access (Default values are returned for locations
 * @(#)outside matrix, accessing these locations is not an error.
 */

#include <math.h>
#include <stdio.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

int     matrix_get_full(Matrix * mat, int i, int j);
double  matrix_getf_full(Matrix * mat, int i, int j);
Complex matrix_getz_full(Matrix * mat, int i, int j);
void   *matrix_getp_full(Matrix * mat, int i, int j);
Complex cmplx();
Complex cmplx_zero();
Complex cmplx_unit();

/** default values for locations outside matrix **/

static int mat_default_val = 0;
static double mat_default_fval = 0.0;
static Complex mat_default_zval = {Complex_id, 0.0, 0.0};
static void *mat_default_pval = NULL;

/** functions to set default values **/

void    matrix_set_default_val(int ival)
{
    mat_default_val = ival;
}

void    matrix_set_default_fval(double fval)
{
    mat_default_fval = fval;
}

void    matrix_set_default_zval(Complex zval)
{
    mat_default_zval = zval;
}

void    matrix_set_default_pval(void *pval)
{
    mat_default_pval = pval;
}

double  mat_getf(Matrix * mat, int i, int j)
{
    if (i < 0 || i >= mat->m || j < 0 || j >= mat->n)
	return (mat_default_fval);
    return (mat->el.float_v[i][j]);
}

/** gets integer value from matrix, casting if necessary **/

int     matrix_get(Matrix * mat, int i, int j)
{
    if (mat == NULL)
	return (mat_default_val);

    if (i < 0 || i >= mat->m || j < 0 || j >= mat->n)
	return (mat_default_val);

    switch (mat->shape)
    {
    case matrix_full:
	return (matrix_get_full(mat, i, j));
    case matrix_lower:
    case matrix_symmetric:
	if (i < j)
	    SWAP(int, i, j);
	return (matrix_get_full(mat, i, j));
    case matrix_upper:
	if (j < i)
	    SWAP(int, i, j);
	return (matrix_get_full(mat, i, j));
    }
    return (mat_default_val);
}

int     matrix_get_full(Matrix * mat, int i, int j)
{
    int     val;

    switch (mat->vtype)
    {
    case char_v:
	val = (int) mat->el.char_v[i][j];
	break;
    case uchar_v:
	val = (int) mat->el.uchar_v[i][j];
	break;
    case short_v:
	val = (int) mat->el.short_v[i][j];
	break;
    case ushort_v:
	val = (int) mat->el.ushort_v[i][j];
	break;
    case int_v:
	val = mat->el.int_v[i][j];
	break;
    case uint_v:
	val = (int) mat->el.uint_v[i][j];
	break;
    case float_v:
	val = (int) mat->el.float_v[i][j];
	break;
    case double_v:
	val = (int) mat->el.double_v[i][j];
	break;
    case complex_v:
	val = (int) mat->el.complex_v[i][j].x;
	break;
    case ptr_v:
	if (mat->el.ptr_v[i][j] == NULL)
	    val = 0;
	else
	    val = 1;
	break;
    }
    return (val);
}

/** gets float value from matrix, casting if necessary **/

double  matrix_getf(Matrix * mat, int i, int j)
{
    if (mat == NULL)
	return (mat_default_fval);

    if (i < 0 || i >= mat->m || j < 0 || j >= mat->n)
	return (mat_default_fval);

    switch (mat->shape)
    {
    case matrix_full:
	return (matrix_getf_full(mat, i, j));
    case matrix_lower:
    case matrix_symmetric:
	if (i < j)
	    SWAP(int, i, j);
	return (matrix_getf_full(mat, i, j));
    case matrix_upper:
	if (j < i)
	    SWAP(int, i, j);
	return (matrix_getf_full(mat, i, j));
    }
    return (mat_default_fval);
}

double  matrix_getf_full(Matrix * mat, int i, int j)
{
    double  val;

    switch (mat->vtype)
    {
    case char_v:
	val = (double) mat->el.char_v[i][j];
	break;
    case uchar_v:
	val = (double) mat->el.uchar_v[i][j];
	break;
    case short_v:
	val = (double) mat->el.short_v[i][j];
	break;
    case ushort_v:
	val = (double) mat->el.ushort_v[i][j];
	break;
    case int_v:
	val = (double) mat->el.int_v[i][j];
	break;
    case uint_v:
	val = (double) mat->el.uint_v[i][j];
	break;
    case float_v:
	val = (double) mat->el.float_v[i][j];
	break;
    case double_v:
	val = (double) mat->el.double_v[i][j];
	break;
    case complex_v:
	val = (double) mat->el.complex_v[i][j].x;
	break;
    case ptr_v:
	if (mat->el.ptr_v[i][j] == NULL)
	    val = 0;
	else
	    val = 1;
	break;
    }
    return (val);
}

/** gets complex value from matrix, casting if necessary **/

Complex matrix_getz(Matrix * mat, int i, int j)
{
    if (mat == NULL)
	return (mat_default_zval);

    if (i < 0 || i >= mat->m || j < 0 || j >= mat->n)
	return (mat_default_zval);

    switch (mat->shape)
    {
    case matrix_full:
	return (matrix_getz_full(mat, i, j));
    case matrix_lower:
    case matrix_symmetric:
	if (i < j)
	    SWAP(int, i, j);
	return (matrix_getz_full(mat, i, j));
    case matrix_upper:
	if (j < i)
	    SWAP(int, i, j);
	return (matrix_getz_full(mat, i, j));
    }
    return (mat_default_zval);
}

Complex matrix_getz_full(Matrix * mat, int i, int j)
{
    Complex val = {Complex_id};

    switch (mat->vtype)
    {
    case char_v:
	val = cmplx((double) mat->el.char_v[i][j], 0.0);
	break;
    case uchar_v:
	val = cmplx((double) mat->el.uchar_v[i][j], 0.0);
	break;
    case short_v:
	val = cmplx((double) mat->el.short_v[i][j], 0.0);
	break;
    case ushort_v:
	val = cmplx((double) mat->el.ushort_v[i][j], 0.0);
	break;
    case int_v:
	val = cmplx((double) mat->el.int_v[i][j], 0.0);
	break;
    case uint_v:
	val = cmplx((double) mat->el.uint_v[i][j], 0.0);
	break;
    case float_v:
	val = cmplx((double) mat->el.float_v[i][j], 0.0);
	break;
    case double_v:
	val = cmplx((double) mat->el.double_v[i][j], 0.0);
	break;
    case complex_v:
	val = mat->el.complex_v[i][j];
	break;
    case ptr_v:
	if (mat->el.ptr_v[i][j] == NULL)
	    val = cmplx_zero();
	else
	    val = cmplx_unit();
	break;
    }
    return (val);
}

/** gets pointer value from matrix, casting if necessary **/

void   *matrix_getp(Matrix * mat, int i, int j)
{
    if (mat == NULL)
	return (mat_default_pval);

    if (i < 0 || i >= mat->m || j < 0 || j >= mat->n)
	return (mat_default_pval);

    switch (mat->shape)
    {
    case matrix_full:
	return (matrix_getp_full(mat, i, j));
    case matrix_lower:
    case matrix_symmetric:
	if (i < j)
	    SWAP(int, i, j);
	return (matrix_getp_full(mat, i, j));
    case matrix_upper:
	if (j < i)
	    SWAP(int, i, j);
	return (matrix_getp_full(mat, i, j));
    }
    return (mat_default_pval);
}

void   *matrix_getp_full(Matrix * mat, int i, int j)
{
    void   *val;

    switch (mat->vtype)
    {
	/* cast twice to avoid compiler warning: cast to pointer from
	 * integer of different size */
    case char_v:
	val = (void *) (int) mat->el.char_v[i][j];
	break;
    case uchar_v:
	val = (void *) (int) mat->el.uchar_v[i][j];
	break;
    case short_v:
	val = (void *) (int) mat->el.short_v[i][j];
	break;
    case ushort_v:
	val = (void *) (int) mat->el.ushort_v[i][j];
	break;
    case int_v:
	val = (void *) mat->el.int_v[i][j];
	break;
    case uint_v:
	val = (void *) mat->el.uint_v[i][j];
	break;
    case ptr_v:
	val = mat->el.ptr_v[i][j];
	break;
    default:
	val = mat_default_pval;
	break;
    }
    return (val);
}
