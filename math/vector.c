/**@(#)Vector (1 dimensional array) allocation
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

Vector *vector_alloc(int n, Vartype vtype)
{
    Vector *v;
    unsigned int vsize;

    if (n <= 0)
	return (NULL);
    if ((vsize = var_size(vtype)) == -1)
	return (NULL);

    v = ts_ralloc(Vector);
    v->n = n;
    v->vtype = vtype;
    if (vtype == complex_v)
    {
	v->data = zvector_alloc(0, n);
    } else
    {
	v->data = nvector_alloc(0, n, vsize);
    }
    return (v);
}

void    vector_free(Vector * v)
{
    if (v == NULL)
	return;
    rfree((void *) v->data);
    rfree((void *) v);
}

/**
wrap a vector structure round already allocated memory
**/

Vector *vector_build(int n, Vartype vtype, void *el)
{
    Vector *v;

    if (n <= 0)
	return (NULL);
    v = ts_ralloc(Vector);
    v->n = n;
    v->vtype = vtype;
    v->data = el;
    return (v);
}

void    vector_copy_inplace(Vector * w, Vector * v)
{
    int     i, n;

    if (w == NULL || v == NULL)
	return;

    if (v->n <= w->n && v->vtype == w->vtype)
    {				/** can use memcpy **/
	nvector_copy_inplace((char *) w->data, (char *) v->data, 0, v->n,
			     var_size(w->vtype));
	if (w->vtype == complex_v)
	{
	    ts_nvector_zero_inplace((char *) w->data, v->n, w->n, Complex);
	} else
	{
	    nvector_zero_inplace((char *) w->data, v->n, w->n, var_size(w->vtype));
	}
	return;
    }
    n = MIN(v->n, w->n);
    switch (v->vtype)
    {
    case char_v:
    case uchar_v:
    case short_v:
    case ushort_v:
    case int_v:
    case uint_v:
    case ptr_v:
	for (i = 0; i < n; i++)
	{
	    double     vi;

	    VECTOR_GET(v, i, vi);
	    VECTOR_SET(w, i, vi);
	}
	break;
    case float_v:
    case double_v:
	for (i = 0; i < n; i++)
	{
	    double  vi;

	    VECTOR_GET(v, i, vi);
	    VECTOR_SET(w, i, vi);
	}
	break;
    case complex_v:
	for (i = 0; i < n; i++)
	{
	    Complex vi = {Complex_id};

	    VECTOR_GETZ(v, i, vi);
	    VECTOR_SETZ(w, i, vi);
	}
	break;
    }
    if (w->vtype == complex_v)
    {
	ts_nvector_zero_inplace((char *) w->data, n, w->n, Complex);
    } else
    {
	nvector_zero_inplace((char *) w->data, n, w->n, var_size(w->vtype));
    }
}

Vector *vector_copy(Vector * v)
{
    Vector *copy;

    copy = vector_alloc((int) v->n, (Vartype) v->vtype);	/* ICCBUG argument and
								 * old-style */
    /* parameter mismatch: 'vector_alloc'  */
    vector_copy_inplace(copy, v);
    return (copy);
}

Vector *vector_cast(Vector * v, Vartype vtype)
{
    Vector *copy;

    copy = vector_alloc(v->n, vtype);
    vector_copy_inplace(copy, v);
    return (copy);
}

Vector *vector_extend(Vector * v, int n, Vartype vtype)
{
    Vector *copy;

    copy = vector_alloc(n, vtype);	/* ICCBUG argument and
					 * old-style parameter */
    /* mismatch: 'vector_alloc' */
    vector_copy_inplace(copy, v);
    return (copy);
}

Vartype vector_sup_vtype(Vartype vtype1, Vartype vtype2)
{
    if (vtype1 == complex_v || vtype2 == complex_v)
	return (complex_v);
    if (vtype1 == double_v || vtype2 == double_v)
	return (double_v);
    if (vtype1 == float_v || vtype2 == float_v)
	return (float_v);
    return (int_v);
}

#ifndef ANSIFYING
#ifdef __STRICT_ANSI__

Vector *vector(int n, Vartype vtype,...)
{
    va_list ap;
    int     i;
    Vector *v;

    if (n < 1)
	return (NULL);
    v = vector_alloc(n, vtype);	/* ICCBUG argument and old-style
				 * parameter */
    /* mismatch: 'vector_alloc' */
    va_start(ap, vtype);

    switch (vtype)
    {
    case ptr_v:
	for (i = 0; i < n; i++)
	{
	    void   *vi = (void *) va_arg(ap, void *);

	    VECTOR_SET(v, i, (int) vi);
	}
	break;
    case uchar_v:
    case char_v:
    case short_v:
    case int_v:
	for (i = 0; i < n; i++)
	{
	    int     vi = (int) va_arg(ap, int);

	    VECTOR_SET(v, i, vi);
	}
	break;
    case float_v:
    case double_v:
	for (i = 0; i < n; i++)
	{
	    double  vi = (double) va_arg(ap, double);

	    VECTOR_SET(v, i, vi);
	}
	break;
    }
    va_end(ap);

    return (v);
}

#else

Vector *vector(n, vtype, va_alist)
int     n;
Vartype vtype;

va_dcl
{
    va_list ap;
    int     i;
    Vector *v;

    if (n < 1)
	return (NULL);
    v = vector_alloc(n, vtype);	/* ICCBUG argument and old-style
				 * parameter */
    /* mismatch: 'vector_alloc' */
    va_start(ap);
    switch (vtype)
    {
    case ptr_v:
	for (i = 0; i < n; i++)
	{
	    void   *vi = (void *) va_arg(ap, void *);

	    VECTOR_SET(v, i, (int) vi);
	}
	break;
    case uchar_v:
    case char_v:
    case short_v:
    case int_v:
	for (i = 0; i < n; i++)
	{
	    int     vi = (int) va_arg(ap, int);

	    VECTOR_SET(v, i, vi);
	}
	break;
    case float_v:
    case double_v:
	for (i = 0; i < n; i++)
	{
	    double  vi = (double) va_arg(ap, double);

	    VECTOR_SET(v, i, vi);
	}
	break;
    }
    va_end(ap);

    return (v);
}

#endif				/* __STRICT_ANSI__ */
#endif				/* ANSIFYING */
