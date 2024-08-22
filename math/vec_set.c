/**@(#)Vector (1 dimensional array) component setting
 */

#include <stdio.h>
#include <tina/sys.h>
#include <tina/math.h>

void    vector_set(Vector * v, int i, int vi)
{
    if (v == NULL)
	return;
    if (i < 0 || i >= v->n)
	return;
    VECTOR_SET(v, i, vi);
}

/** obsolete **/
void    vector_put(int vi, Vector * v, int i)
{
    vector_set(v, i, vi);
}

void    vector_setp(Vector * v, int i, void *vi)
{
    if (v == NULL || v->vtype != ptr_v)
	return;
    if (i < 0 || i >= v->n)
	return;
    VECTOR_SETP(v, i, vi);
}

/** obsolete **/
void    vector_putp(void *vi, Vector * v, int i)
{
    vector_setp(v, i, vi);
}

void    vector_setf(Vector * v, int i, double vi)
{
    if (v == NULL || v->vtype == ptr_v)
	return;

    if (i < 0 || i >= v->n)
	return;
    VECTOR_SET(v, i, vi);
}

/** obsolete **/
void    vector_putf(double vi, Vector * v, int i)
{
    vector_setf(v, i, vi);
}

void    vector_setz(Vector * v, int i, Complex vi)
{
    if (v == NULL || v->vtype == ptr_v)
	return;
    if (i < 0 || i >= v->n)
	return;
    VECTOR_SETZ(v, i, vi);
}

/** obsolete **/
void    vector_putz(Complex vi, Vector * v, int i)
{
    vector_setz(v, i, vi);
}
