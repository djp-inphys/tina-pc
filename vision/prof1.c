/**@(#)
**/
/* prof1.c
 * 
 * standard handling functions for generic profiles
 * 
 */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/vision.h>

Prof1  *prof1_alloc(int n1, int n2, Vartype vtype)
{
    Prof1  *prof;

    if (n2 < n1)
    {
	error("prof1_alloc: bad size", non_fatal);
	return (NULL);
    }
    if (n2 == n1)
    {
	error("prof1_alloc: zero size", warning);
	return (NULL);
    }
    prof = ts_ralloc(Prof1);
    prof->n1 = n1;
    prof->n2 = n2;
    prof->vtype = vtype;

    switch (vtype)
    {
    case char_v:
    case uchar_v:
	prof->el.char_v = cvector_alloc(n1, n2);
	break;
    case short_v:
    case ushort_v:
	prof->el.short_v = svector_alloc(n1, n2);
	break;
    case int_v:
    case uint_v:
	prof->el.int_v = ivector_alloc(n1, n2);
	break;
    case float_v:
	prof->el.float_v = fvector_alloc(n1, n2);
	break;
    case double_v:
	prof->el.double_v = dvector_alloc(n1, n2);
	break;
    case complex_v:
	prof->el.complex_v = zvector_alloc(n1, n2);
	break;
    case ptr_v:
	prof->el.ptr_v = pvector_alloc(n1, n2);
	break;
    }
    return (prof);
}

void    prof1_free(Prof1 * prof)
{
    int     n;

    if (prof == NULL)
	return;
    n = prof->n1;

    switch (prof->vtype)
    {
    case char_v:
    case uchar_v:
	cvector_free((void *) prof->el.char_v, n);
	break;
    case short_v:
    case ushort_v:
	svector_free((void *) prof->el.short_v, n);
	break;
    case int_v:
    case uint_v:
	ivector_free((void *) prof->el.int_v, n);
	break;
    case float_v:
	fvector_free((void *) prof->el.float_v, n);
	break;
    case double_v:
	dvector_free((void *) prof->el.double_v, n);
	break;
    case complex_v:
	zvector_free((void *) prof->el.complex_v, n);
	break;
    case ptr_v:
	pvector_free((void *) prof->el.ptr_v, n);
	break;
    }
    rfree((void *) prof);
}

Prof1  *prof1_reverse(Prof1 * prof)
{
    Prof1  *rev;
    Prof1  *prof1_alloc(int n1, int n2, Vartype vtype);
    int     i, n1, n2;

    if (prof == NULL)
	return (NULL);

    n1 = -prof->n2 + 1;
    n2 = -prof->n1 + 1;
    rev = prof1_alloc(n1, n2, prof->vtype);
    switch (prof->vtype)
    {
    case char_v:
    case uchar_v:
	for (i = n1; i < n2; ++i)
	    rev->el.char_v[i] = prof->el.char_v[-i];
	break;
    case short_v:
    case ushort_v:
	for (i = n1; i < n2; ++i)
	    rev->el.short_v[i] = prof->el.short_v[-i];
	break;
    case int_v:
    case uint_v:
	for (i = n1; i < n2; ++i)
	    rev->el.int_v[i] = prof->el.int_v[-i];
	break;
    case float_v:
	for (i = n1; i < n2; ++i)
	    rev->el.float_v[i] = prof->el.float_v[-i];
	break;
    case double_v:
	for (i = n1; i < n2; ++i)
	    rev->el.double_v[i] = prof->el.double_v[-i];
	break;
    case complex_v:
	for (i = n1; i < n2; ++i)
	    rev->el.complex_v[i] = prof->el.complex_v[-i];
	break;
    case ptr_v:
	for (i = n1; i < n2; ++i)
	    rev->el.ptr_v[i] = prof->el.ptr_v[-i];
	break;
    }
    return (rev);
}
