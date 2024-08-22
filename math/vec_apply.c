/**@(#)Vector handling (eg vector_apply: apply a function to every component)
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

/**
apply functions call a function
    f(&input, &output, &data)
on every element of a vector,
input and output can be different types.

A valid inplace call is
    vector_apply_inplace(v, v, f, data)
**/

void    vector_apply_inplace(Vector * w, Vector * v, void (*f) ( /* ??? */ ), void *data)
{
    int     i, n;

    if (w == NULL)
	return;

    if (v == NULL)
	n = 0;
    else
	n = MIN(v->n, w->n);

    for (i = 0; i < n; i++)
    {
	void   *vi, *wi;

	VECTOR_GETP(v, i, vi);
	VECTOR_GETP(w, i, wi);
	f(vi, wi, data);
    }
    for (i = n; i < w->n; i++)
    {
	void   *wi;

	VECTOR_GETP(w, i, wi);
	f(NULL, wi, data);
    }
}

Vector *vector_apply(Vector * v, Vartype vtype, void (*f) ( /* ??? */ ), void *data)
{
    Vector *w;

    if (v == NULL)
	return (NULL);
    w = vector_alloc(v->n, vtype);
    vector_apply_inplace(w, v, f, data);
    return (w);
}

Vector *vector_itimes(int k, Vector * v)
{
    Vector *w;
    Vartype vtype;
    int     i, n;

    if (v == NULL)
	return (NULL);

    n = v->n;
    vtype = vector_sup_vtype(int_v, v->vtype);
    w = vector_alloc(v->n, vtype);
    switch (vtype)
    {
    case char_v:
    case uchar_v:
    case int_v:
    case uint_v:
    case short_v:
    case ushort_v:
	for (i = 0; i < n; i++)
	{
	    double     vi, wi;

	    VECTOR_GET(v, i, vi);
	    wi = k * vi;
	    VECTOR_SET(w, i, wi);
	}
	break;
    case float_v:
    case double_v:
	for (i = 0; i < n; i++)
	{
	    double  vi, wi;

	    VECTOR_GET(v, i, vi);
	    wi = k * vi;
	    VECTOR_SET(w, i, wi);
	}
	break;
    case complex_v:
	for (i = 0; i < n; i++)
	{
	    Complex vi = {Complex_id};
	    Complex wi = {Complex_id};

	    VECTOR_GETZ(v, i, vi);
	    wi = cmplx_times((double) k, vi);
	    VECTOR_SETZ(w, i, wi);
	}
	break;
    }
    return (w);
}

Vector *vector_times(double k, Vector * v)
{
    Vartype vtype;
    Vector *w;
    int     i, n;

    if (v == NULL)
	return (NULL);

    vtype = vector_sup_vtype(float_v, v->vtype);
    n = v->n;
    w = vector_alloc(v->n, vtype);
    switch (vtype)
    {
    case float_v:
    case double_v:
	for (i = 0; i < n; i++)
	{
	    double  vi, wi;

	    VECTOR_GET(v, i, vi);
	    wi = k * vi;
	    VECTOR_SET(w, i, wi);
	}
	break;
    case complex_v:
	for (i = 0; i < n; i++)
	{
	    Complex vi = {Complex_id};
	    Complex wi = {Complex_id};

	    VECTOR_GETZ(v, i, vi);
	    wi = cmplx_times(k, vi);
	    VECTOR_SETZ(w, i, wi);
	}
	break;
    }
    return (w);
}

Vector *vector_ztimes(Complex k, Vector * v)
{
    Vector *w;
    int     i, n;

    if (v == NULL)
	return (NULL);

    n = v->n;
    w = vector_alloc(v->n, complex_v);
    for (i = 0; i < n; i++)
    {
	Complex vi = {Complex_id};
	Complex wi = {Complex_id};

	VECTOR_GETZ(v, i, vi);
	wi = cmplx_prod(k, vi);
	VECTOR_SETZ(w, i, wi);
    }
    return (w);
}

void    vector_minus_inplace(Vector * v)
{
    int     i, n;

    if (v == NULL)
	return;

    n = v->n;
    switch (v->vtype)
    {
    case char_v:
    case uchar_v:
    case int_v:
    case uint_v:
    case short_v:
    case ushort_v:
	for (i = 0; i < n; i++)
	{
	    double    vi;

	    VECTOR_GET(v, i, vi);
	    VECTOR_SET(v, i, -vi);
	}
	break;
    case float_v:
    case double_v:
	for (i = 0; i < n; i++)
	{
	    double  vi;

	    VECTOR_GET(v, i, vi);
	    VECTOR_SET(v, i, -vi);
	}
	break;
    case complex_v:
	for (i = 0; i < n; i++)
	{
	    Complex vi = {Complex_id};

	    VECTOR_GETZ(v, i, vi);
	    VECTOR_SETZ(v, i, cmplx_minus(vi));
	}
	break;
    }
}

Vector *vector_minus(Vector * v)
{
    Vector *w;
    int     i, n;

    if (v == NULL)
	return (NULL);

    n = v->n;
    w = vector_alloc(v->n, v->vtype);
    switch (v->vtype)
    {
    case char_v:
    case uchar_v:
    case int_v:
    case uint_v:
    case short_v:
    case ushort_v:
	for (i = 0; i < n; i++)
	{
	    double     vi, wi;

	    VECTOR_GET(v, i, vi);
	    wi = -vi;
	    VECTOR_SET(w, i, wi);
	}
	break;
    case float_v:
    case double_v:
	for (i = 0; i < n; i++)
	{
	    double  vi, wi;

	    VECTOR_GET(v, i, vi);
	    wi = -vi;
	    VECTOR_SET(w, i, wi);
	}
	break;
    case complex_v:
	for (i = 0; i < n; i++)
	{
	    Complex vi = {Complex_id};
	    Complex wi = {Complex_id};

	    VECTOR_GETZ(v, i, vi);
	    wi = cmplx_minus(vi);
	    VECTOR_SETZ(w, i, wi);
	}
	break;
    }
    return (w);
}

void    fft_complex_inplace();
void    fft_inverse_complex_inplace();

void    vector_fft_inplace(Vector * v)
{
    if (v == NULL || v->vtype != complex_v)
	return;
    fft_cmplx_inplace((Complex *) v->data, v->n);
}

Vector *vector_fft(Vector * v)
{
    Vector *w;
    int     n = 1;

    if (v == NULL)
	return (NULL);
    while (n < v->n)
	n *= 2;
    w = vector_extend(v, n, complex_v);
    vector_fft_inplace(w);
    return (w);
}

void    vector_fft_inverse_inplace(Vector * v)
{
    if (v == NULL || v->vtype != complex_v)
	return;
    fft_inverse_cmplx_inplace((Complex *) v->data, v->n);
}

Vector *vector_fft_inverse(Vector * v)
{
    Vector *w;
    int     n = 1;

    if (v == NULL)
	return (NULL);
    while (n < v->n)
	n *= 2;
    w = vector_extend(v, n, complex_v);
    vector_fft_inverse_inplace(w);
    return (w);
}
