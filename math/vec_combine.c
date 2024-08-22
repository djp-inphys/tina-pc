/**@(#)Vector maths (add, subtract, etc.)
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

void    vector_sum_inplace(Vector * v1, Vector * v2)
{
    int     i, n;

    if (v1 == NULL || v2 == NULL)
	return;

    n = MIN(v1->n, v2->n);
    switch (v1->vtype)
    {
    case char_v:
    case uchar_v:
    case short_v:
    case ushort_v:
    case int_v:
    case uint_v:
	for (i = 0; i < n; i++)
	{
	    double     v1i, v2i;

	    VECTOR_GET(v1, i, v1i);
	    VECTOR_GET(v2, i, v2i);
	    v1i += v2i;
	    VECTOR_SET(v1, i, v1i);
	}
	break;
    case float_v:
    case double_v:
	for (i = 0; i < n; i++)
	{
	    double  v1i, v2i;

	    VECTOR_GET(v1, i, v1i);
	    VECTOR_GET(v2, i, v2i);
	    v1i += v2i;
	    VECTOR_SET(v1, i, v1i);
	}
	break;
    case complex_v:
	for (i = 0; i < n; i++)
	{
	    Complex v1i = {Complex_id};
	    Complex v2i = {Complex_id};

	    VECTOR_GETZ(v1, i, v1i);
	    VECTOR_GETZ(v2, i, v2i);
	    v1i = cmplx_sum(v1i, v2i);
	    VECTOR_SETZ(v1, i, v1i);
	}
	break;
    default:
	break;
    }
}

Vector *vector_sum(Vector * v1, Vector * v2)
{
    Vector *w;
    Vartype vtype;
    int     n;

    if (v1 == NULL && v2 == NULL)
	return (NULL);
    if (v1 == NULL)
	return (vector_copy(v2));
    if (v2 == NULL)
	return (vector_copy(v1));

    vtype = vector_sup_vtype(v1->vtype, v2->vtype);
    n = MAX(v1->n, v2->n);
    w = vector_extend(v1, n, vtype);
    vector_sum_inplace(w, v2);

    return (w);
}

void    vector_diff_inplace(Vector * v1, Vector * v2)
{
    int     i, n;

    if (v1 == NULL || v2 == NULL)
	return;

    n = MIN(v1->n, v2->n);
    switch (v1->vtype)
    {
    case char_v:
    case uchar_v:
    case short_v:
    case ushort_v:
    case int_v:
    case uint_v:
	for (i = 0; i < n; i++)
	{
	    double     v1i, v2i;

	    VECTOR_GET(v1, i, v1i);
	    VECTOR_GET(v2, i, v2i);
	    v1i -= v2i;
	    VECTOR_SET(v1, i, v1i);
	}
	break;
    case float_v:
    case double_v:
	for (i = 0; i < n; i++)
	{
	    double  v1i, v2i;

	    VECTOR_GET(v1, i, v1i);
	    VECTOR_GET(v2, i, v2i);
	    v1i -= v2i;
	    VECTOR_SET(v1, i, v1i);
	}
	break;
    case complex_v:
	for (i = 0; i < n; i++)
	{
	    Complex v1i = {Complex_id};
	    Complex v2i = {Complex_id};

	    VECTOR_GETZ(v1, i, v1i);
	    VECTOR_GETZ(v2, i, v2i);
	    v1i = cmplx_diff(v1i, v2i);
	    VECTOR_SETZ(v1, i, v1i);
	}
	break;
    default:
	break;
    }
}

Vector *vector_diff(Vector * v1, Vector * v2)
{
    Vector *w;
    Vartype vtype;
    int     n;

    if (v1 == NULL && v2 == NULL)
	return (NULL);
    if (v1 == NULL)
	return (vector_copy(v2));
    if (v2 == NULL)
	return (vector_minus(v1));

    vtype = vector_sup_vtype(v1->vtype, v2->vtype);
    n = MAX(v1->n, v2->n);
    w = vector_extend(v1, n, vtype);
    vector_diff_inplace(w, v2);

    return (w);
}

void    vector_prod_inplace(Vector * v1, Vector * v2)
{
    int     i, n;

    if (v1 == NULL || v2 == NULL)
	return;

    n = MIN(v1->n, v2->n);
    switch (v1->vtype)
    {
    case char_v:
    case uchar_v:
    case short_v:
    case ushort_v:
    case int_v:
    case uint_v:
	for (i = 0; i < n; i++)
	{
	    double  v1i, v2i;

	    VECTOR_GET(v1, i, v1i);
	    VECTOR_GET(v2, i, v2i);
	    v1i *= v2i;
	    VECTOR_SET(v1, i, v1i);
	}
	break;
    case float_v:
    case double_v:
	for (i = 0; i < n; i++)
	{
	    double  v1i, v2i;

	    VECTOR_GET(v1, i, v1i);
	    VECTOR_GET(v2, i, v2i);
	    v1i *= v2i;
	    VECTOR_SET(v1, i, v1i);
	}
	break;
    case complex_v:
	for (i = 0; i < n; i++)
	{
	    Complex v1i = {Complex_id};
	    Complex v2i = {Complex_id};

	    VECTOR_GETZ(v1, i, v1i);
	    VECTOR_GETZ(v2, i, v2i);
	    v1i = cmplx_prod(v1i, v2i);
	    VECTOR_SETZ(v1, i, v1i);
	}
	break;
    default:
	break;
    }
}

Vector *vector_prod(Vector * v1, Vector * v2)
{
    Vector *w;
    Vartype vtype;
    int     n;

    if (v1 == NULL || v2 == NULL)
	return (NULL);

    vtype = vector_sup_vtype(v1->vtype, v2->vtype);
    n = MAX(v1->n, v2->n);
    w = vector_extend(v1, n, vtype);
    vector_prod_inplace(w, v2);
    return (w);
}

/* Product of v1 and complex conjugate of v2 */
void    vector_cprod_inplace(Vector * v1, Vector * v2)
{
    int     i, n;

    if (v1 == NULL || v2 == NULL)
	return;

    n = MIN(v1->n, v2->n);
    switch (v1->vtype)
    {
    case char_v:
    case uchar_v:
    case short_v:
    case ushort_v:
    case int_v:
    case uint_v:
	for (i = 0; i < n; i++)
	{
	    double     v1i, v2i;

	    VECTOR_GET(v1, i, v1i);
	    VECTOR_GET(v2, i, v2i);
	    v1i *= v2i;
	    VECTOR_SET(v1, i, v1i);
	}
	break;
    case float_v:
    case double_v:
	for (i = 0; i < n; i++)
	{
	    double  v1i, v2i;

	    VECTOR_GET(v1, i, v1i);
	    VECTOR_GET(v2, i, v2i);
	    v1i *= v2i;
	    VECTOR_SET(v1, i, v1i);
	}
	break;
    case complex_v:
	for (i = 0; i < n; i++)
	{
	    Complex v1i = {Complex_id};
	    Complex v2i = {Complex_id};

	    VECTOR_GETZ(v1, i, v1i);
	    VECTOR_GETZ(v2, i, v2i);
	    v1i = cmplx_cprod(v1i, v2i);
	    VECTOR_SETZ(v1, i, v1i);
	}
	break;
    default:
	break;
    }
}

Vector *vector_cprod(Vector * v1, Vector * v2)
{
    Vector *w;
    Vartype vtype;
    int     n;

    if (v1 == NULL || v2 == NULL)
	return (NULL);

    vtype = vector_sup_vtype(v1->vtype, v2->vtype);
    n = MAX(v1->n, v2->n);
    w = vector_extend(v1, n, vtype);
    vector_cprod_inplace(w, v2);
    return (w);
}

void    vector_div_inplace(Vector * v1, Vector * v2)
{
    int     i, n;

    if (v1 == NULL || v2 == NULL)
	return;

    n = MIN(v1->n, v2->n);
    switch (v1->vtype)
    {
    case char_v:
    case uchar_v:
    case short_v:
    case ushort_v:
    case int_v:
    case uint_v:
	for (i = 0; i < n; i++)
	{
	    double     v1i, v2i;

	    VECTOR_GET(v1, i, v1i);
	    VECTOR_GET(v2, i, v2i);
	    v1i /= v2i;
	    VECTOR_SET(v1, i, v1i);
	}
	break;
    case float_v:
    case double_v:
	for (i = 0; i < n; i++)
	{
	    double  v1i, v2i;

	    VECTOR_GET(v1, i, v1i);
	    VECTOR_GET(v2, i, v2i);
	    v1i /= v2i;
	    VECTOR_SET(v1, i, v1i);
	}
	break;
    case complex_v:
	for (i = 0; i < n; i++)
	{
	    Complex v1i = {Complex_id};
	    Complex v2i = {Complex_id};

	    VECTOR_GETZ(v1, i, v1i);
	    VECTOR_GETZ(v2, i, v2i);
	    v1i = cmplx_div(v1i, v2i);
	    VECTOR_SETZ(v1, i, v1i);
	}
	break;
    default:
	break;
    }
}

Vector *vector_div(Vector * v1, Vector * v2)
{
    Vector *w;
    Vartype vtype;
    int     n;

    if (v1 == NULL || v2 == NULL)
	return (NULL);

    vtype = vector_sup_vtype(v1->vtype, v2->vtype);
    n = MAX(v1->n, v2->n);
    w = vector_extend(v1, n, vtype);
    vector_div_inplace(w, v2);
    return (w);
}

Vector *vector_conv(Vector * v1, Vector * v2)
{
    Vector *f1;
    Vector *f2;
    Vector *fc;
    Vector *c;

    if (v1 == NULL || v2 == NULL)
	return (NULL);

    f1 = vector_fft(v1);
    f2 = vector_fft(v2);
    fc = vector_prod(v1, v2);
    vector_free(f1);
    vector_free(f2);
    c = vector_fft_inverse(fc);
    vector_free(fc);
    return (c);
}

/* un-normalised correlation of two vectors calculated by fft */
Vector *vector_corr(Vector * v1, Vector * v2)
{
    Vector *f1;
    Vector *f2;
    Vector *fc;
    Vector *c;
    Vector *cr;
    Vector *e1 = NULL;
    Vector *e2 = NULL;
    int     n = 1;

    if (v1 == NULL || v2 == NULL)
	return (NULL);
    while (n < v1->n || n < v2->n)
	n *= 2;;

    if (n != v1->n)
	v1 = e1 = vector_extend(v1, n, v1->vtype);
    if (n != v2->n)
	v2 = e2 = vector_extend(v2, n, v2->vtype);

    f1 = vector_fft(v1);
    f2 = vector_fft(v2);
    fc = vector_cprod(f1, f2);
    vector_free(f1);
    vector_free(f2);
    c = vector_fft_inverse(fc);
    vector_free(fc);
    cr = vector_cast(c, double_v);
    vector_free(c);
    vector_free(e1);
    vector_free(e2);
    return (cr);
}

/* un-normalised correlation of two vectors calculated by fft, with cut
 * lowest frequencies cut off */
Vector *vector_corr_cutoff(Vector * v1, Vector * v2, int cut)
{
    Vector *f1;
    Vector *f2;
    Vector *fc;
    Vector *c;
    Vector *cr;
    Vector *e1 = NULL;
    Vector *e2 = NULL;
    int     n = 1, i;

    if (v1 == NULL || v2 == NULL)
	return (NULL);
    while (n < v1->n || n < v2->n)
	n *= 2;;

    if (n != v1->n)
	v1 = e1 = vector_extend(v1, v1->vtype, n);
    if (n != v2->n)
	v2 = e2 = vector_extend(v2, v2->vtype, n);

    f1 = vector_fft(v1);
    f2 = vector_fft(v2);
    for (i = 0; i < cut; i++)
    {
	VECTOR_SETZ(f1, i, cmplx_zero());
	if (i != 0)
	    VECTOR_SETZ(f1, n - i, cmplx_zero());

	VECTOR_SETZ(f2, i, cmplx_zero());
	if (i != 0)
	    VECTOR_SETZ(f2, n - i, cmplx_zero());
    }
    fc = vector_cprod(f1, f2);
    vector_free(f1);
    vector_free(f2);
    c = vector_fft_inverse(fc);
    vector_free(fc);
    cr = vector_cast(c, double_v);
    vector_free(c);
    vector_free(e1);
    vector_free(e2);
    return (cr);
}
