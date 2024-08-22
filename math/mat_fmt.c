/**@(#)Matrix input/output (various types and shapes)
 */

#include <math.h>
#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

int     matrix_get();
double  matrix_getf();
Complex matrix_getz();
void   *matrix_getp();

void    cmatrix_format(Matrix * mat);
void    cmatrix_format_full(Matrix * mat);
void    cmatrix_format_lower(Matrix * mat);
void    cmatrix_format_gen(Matrix * mat);
void    smatrix_format(Matrix * mat);
void    smatrix_format_full(Matrix * mat);
void    smatrix_format_lower(Matrix * mat);
void    smatrix_format_gen(Matrix * mat);
void    imatrix_format(Matrix * mat);
void    imatrix_format_full(Matrix * mat);
void    imatrix_format_lower(Matrix * mat);
void    imatrix_format_gen(Matrix * mat);
void    fmatrix_format(Matrix * mat);
void    fmatrix_format_full(Matrix * mat);
void    fmatrix_format_lower(Matrix * mat);
void    fmatrix_format_gen(Matrix * mat);
void    dmatrix_format(Matrix * mat);
void    dmatrix_format_full(Matrix * mat);
void    dmatrix_format_lower(Matrix * mat);
void    dmatrix_format_gen(Matrix * mat);
void    zmatrix_format(Matrix * mat);
void    zmatrix_format_full(Matrix * mat);
void    zmatrix_format_lower(Matrix * mat);
void    zmatrix_format_gen(Matrix * mat);
void    pmatrix_format(Matrix * mat);
void    pmatrix_format_full(Matrix * mat);
void    pmatrix_format_lower(Matrix * mat);
void    pmatrix_format_gen(Matrix * mat);

static void format_header(Matrix * mat)
{
    format("matrix: ");
    format_shape(mat->shape);
    format(" %d by %d  of ", mat->m, mat->n);
    format_vtype(mat->vtype);
    format("\n");
}

void    mat_format(Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    int     n = mat->n;
    float **el = mat->el.float_v;

    format_header(mat);

    for (i = 0; i < m; ++i)
    {
	for (j = 0; j < n; ++j)
	    format("%12.6f ", el[i][j]);
	format("\n");
    }
}

void    matrix_format(Matrix * mat)
{
    if (mat == NULL)
    {
	format("nil ");
	return;
    }
    switch (mat->vtype)
    {
    case char_v:
    case uchar_v:
	cmatrix_format(mat);
	break;
    case short_v:
    case ushort_v:
	smatrix_format(mat);
	break;
    case int_v:
    case uint_v:
	imatrix_format(mat);
	break;
    case float_v:
	fmatrix_format(mat);
	break;
    case double_v:
	dmatrix_format(mat);
	break;
    case complex_v:
	zmatrix_format(mat);
	break;
    case ptr_v:
	pmatrix_format(mat);
	break;
    }
}

void    cmatrix_format(Matrix * mat)
{
    switch (mat->shape)
    {
	case matrix_full:
	cmatrix_format_full(mat);
	break;
    case matrix_lower:
    case matrix_symmetric:
	cmatrix_format_lower(mat);
	break;
    default:
	cmatrix_format_gen(mat);
	break;
    }
}

void    cmatrix_format_full(Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    int     n = mat->n;
    char  **el = mat->el.char_v;

    format_header(mat);

    for (i = 0; i < m; ++i)
    {
	for (j = 0; j < n; ++j)
	    format("%c ", el[i][j]);
	format("\n");
    }
}

void    cmatrix_format_lower(Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    char  **el = mat->el.char_v;

    format_header(mat);

    for (i = 0; i < m; ++i)
    {
	for (j = 0; j <= i; ++j)
	    format("%c ", el[i][j]);
	format("\n");
    }
}

void    cmatrix_format_gen(Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    int     n = mat->n;

    format_header(mat);

    for (i = 0; i < m; ++i)
    {
	for (j = 0; j < n; ++j)
	    format("%c ", matrix_get(mat, i, j));
	format("\n");
    }
}

void    smatrix_format(Matrix * mat)
{
    switch (mat->shape)
    {
	case matrix_full:
	smatrix_format_full(mat);
	break;
    case matrix_lower:
    case matrix_symmetric:
	smatrix_format_lower(mat);
	break;
    default:
	smatrix_format_gen(mat);
	break;
    }
}


void    smatrix_format_full(Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    int     n = mat->n;
    short **el = mat->el.short_v;

    format_header(mat);

    for (i = 0; i < m; ++i)
    {
	for (j = 0; j < n; ++j)
	    format("%10d ", el[i][j]);
	format("\n");
    }
}

void    smatrix_format_lower(Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    short **el = mat->el.short_v;

    format_header(mat);

    for (i = 0; i < m; ++i)
    {
	for (j = 0; j <= i; ++j)
	    format("%10d ", el[i][j]);
	format("\n");
    }
}

void    smatrix_format_gen(Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    int     n = mat->n;

    format_header(mat);

    for (i = 0; i < m; ++i)
    {
	for (j = 0; j < n; ++j)
	    format("%10d ", matrix_get(mat, i, j));
	format("\n");
    }
}

void    imatrix_format(Matrix * mat)
{
    switch (mat->shape)
    {
	case matrix_full:
	imatrix_format_full(mat);
	break;
    case matrix_lower:
    case matrix_symmetric:
	imatrix_format_lower(mat);
	break;
    default:
	imatrix_format_gen(mat);
	break;
    }
}


void    imatrix_format_full(Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    int     n = mat->n;
    int   **el = mat->el.int_v;

    format_header(mat);

    for (i = 0; i < m; ++i)
    {
	for (j = 0; j < n; ++j)
	    format("%10d ", el[i][j]);
	format("\n");
    }
}

void    imatrix_format_lower(Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    int   **el = mat->el.int_v;

    format_header(mat);

    for (i = 0; i < m; ++i)
    {
	for (j = 0; j <= i; ++j)
	    format("%10d ", el[i][j]);
	format("\n");
    }
}

void    imatrix_format_gen(Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    int     n = mat->n;

    format_header(mat);

    for (i = 0; i < m; ++i)
    {
	for (j = 0; j < n; ++j)
	    format("%10d ", matrix_get(mat, i, j));
	format("\n");
    }
}

void    fmatrix_format(Matrix * mat)
{
    switch (mat->shape)
    {
	case matrix_full:
	fmatrix_format_full(mat);
	break;
    case matrix_lower:
    case matrix_symmetric:
	fmatrix_format_lower(mat);
	break;
    default:
	fmatrix_format_gen(mat);
	break;
    }
}

void    fmatrix_format_full(Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    int     n = mat->n;
    float **el = mat->el.float_v;

    format_header(mat);

    for (i = 0; i < m; ++i)
    {
	for (j = 0; j < n; ++j)
	    format("%12.6f ", el[i][j]);
	format("\n");
    }
}

void    fmatrix_format_lower(Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    float **el = mat->el.float_v;

    format_header(mat);

    for (i = 0; i < m; ++i)
    {
	for (j = 0; j <= i; ++j)
	    format("%12.6f ", el[i][j]);
	format("\n");
    }
}

void    fmatrix_format_gen(Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    int     n = mat->n;

    format_header(mat);

    for (i = 0; i < m; ++i)
    {
	for (j = 0; j < n; ++j)
	    format("%12.6f ", matrix_getf(mat, i, j));
	format("\n");
    }
}

void    dmatrix_format(Matrix * mat)
{
    switch (mat->shape)
    {
	case matrix_full:
	dmatrix_format_full(mat);
	break;
    case matrix_lower:
    case matrix_symmetric:
	dmatrix_format_lower(mat);
	break;
    default:
	dmatrix_format_gen(mat);
	break;
    }
}

void    dmatrix_format_full(Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    int     n = mat->n;
    double **el = mat->el.double_v;

    format_header(mat);

    for (i = 0; i < m; ++i)
    {
	for (j = 0; j < n; ++j)
	    format("%12.6f ", el[i][j]);
	format("\n");
    }
}

void    dmatrix_format_lower(Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    double **el = mat->el.double_v;

    format_header(mat);

    for (i = 0; i < m; ++i)
    {
	for (j = 0; j <= i; ++j)
	    format("%12.6f ", el[i][j]);
	format("\n");
    }
}

void    dmatrix_format_gen(Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    int     n = mat->n;

    format_header(mat);

    for (i = 0; i < m; ++i)
    {
	for (j = 0; j < n; ++j)
	    format("%12.6f ", matrix_getf(mat, i, j));
	format("\n");
    }
}

void    zmatrix_format(Matrix * mat)
{
    switch (mat->shape)
    {
	case matrix_full:
	zmatrix_format_full(mat);
	break;
    case matrix_lower:
    case matrix_symmetric:
	zmatrix_format_lower(mat);
	break;
    default:
	zmatrix_format_gen(mat);
	break;
    }
}

void    zmatrix_format_full(Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    int     n = mat->n;
    Complex **el = mat->el.complex_v;

    format_header(mat);

    for (i = 0; i < m; ++i)
    {
	for (j = 0; j < n; ++j)
	    format("(%12.6f,%12.6f) ", el[i][j].x, el[i][j].y);
	format("\n");
    }
}

void    zmatrix_format_lower(Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    Complex **el = mat->el.complex_v;

    format_header(mat);

    for (i = 0; i < m; ++i)
    {
	for (j = 0; j <= i; ++j)
	    format("(%12.6f,%12.6f) ", el[i][j].x, el[i][j].y);
	format("\n");
    }
}

void    zmatrix_format_gen(Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    int     n = mat->n;

    format_header(mat);

    for (i = 0; i < m; ++i)
    {
	for (j = 0; j < n; ++j)
	{
	    Complex val = {Complex_id};

	    val = matrix_getz(mat, i, j);
	    format("(%12.6f,%12.6f) ", val.x, val.y);
	}
	format("\n");
    }
}

void    ptr_default_print(void *ptr)
{
    if (ptr == NULL)
	format(" 0");
    else
	format(" *");
}

static void (*ptr_print) () = ptr_default_print;

void    ptr_set_print(void (*newprint) ( /* ??? */ ))
{
    ptr_print = newprint;
}

void    (*ptr_get_print(void)) ( /* ??? */ )
{
    return (ptr_print);
}

void    pmatrix_format(Matrix * mat)
{
    switch (mat->shape)
    {
	case matrix_full:
	pmatrix_format_full(mat);
	break;
    case matrix_lower:
    case matrix_symmetric:
	pmatrix_format_lower(mat);
	break;
    default:
	pmatrix_format_gen(mat);
	break;
    }
}

void    pmatrix_format_full(Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    int     n = mat->n;
    void ***el = mat->el.ptr_v;

    format_header(mat);

    for (i = 0; i < m; ++i)
    {
	for (j = 0; j < n; ++j)
	    ptr_print(el[i][j]);
	format("\n");
    }
}

void    pmatrix_format_lower(Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    void ***el = mat->el.ptr_v;

    format_header(mat);

    for (i = 0; i < m; ++i)
    {
	for (j = 0; j <= i; ++j)
	    ptr_print(el[i][j]);
	format("\n");
    }
}

void    pmatrix_format_gen(Matrix * mat)
{
    int     i, j;
    int     m = mat->m;
    int     n = mat->n;

    format_header(mat);

    for (i = 0; i < m; ++i)
    {
	for (j = 0; j < n; ++j)
	{
	    void   *val;

	    val = matrix_getp(mat, i, j);
	    ptr_print(val);
	}
	format("\n");
    }
}
