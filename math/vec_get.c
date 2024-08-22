/**@(#)Vector (1 dimensional array) component reading
 */

#include <stdio.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

static Complex zero = {Complex_id, 0.0, 0.0};

void   *vector_getp(Vector * v, int i)
{
    void   *vi;

    if (v == NULL || v->vtype != ptr_v)
	return (NULL);
    if (i < 0 || i >= v->n)
	return (NULL);
    VECTOR_GETP(v, i, vi);
    return (vi);
}

int     vector_get(Vector * v, int i)
{
    double    vi;

    if (v == NULL || v->vtype == ptr_v)
	return (0);
    if (i < 0 || i >= v->n)
	return (0);
    VECTOR_GET(v, i, vi);
    return ((int)vi);
}

double  vector_getf(Vector * v, int i)
{
    double  vi;

    if (v == NULL || v->vtype == ptr_v)
	return (0.0);
    if (i < 0 || i >= v->n)
	return (0.0);
    VECTOR_GET(v, i, vi);
    return (vi);
}

Complex vector_getz(Vector * v, int i)
{
    Complex vi = {Complex_id};

    if (v == NULL || v->vtype == ptr_v)
	return (zero);
    if (i < 0 || i >= v->n)
	return (zero);
    VECTOR_GETZ(v, i, vi);
    return (vi);
}

double  vector_interpf(Vector * v, double x)
{
    int     xi;
    double  x1, x2;
    double  vi, v1, v2;

    if (v == NULL || v->vtype == ptr_v)
	return (0);
    if (x < 0 || x > v->n)
	return (0.0);

    if (x < v->n)
	xi = (int)x;
    else
	xi = v->n;

    x1 = x - xi;
    x2 = 1.0 - x1;
    VECTOR_GET(v, xi, v1);
    VECTOR_GET(v, xi + 1, v2);
    vi = x2 * v1 + x1 * v2;
    return (vi);
}

Complex vector_interpz(Vector * v, double x)
{
    int     xi;
    double  x1, x2;
    Complex vi = {Complex_id};
    Complex v1 = {Complex_id};
    Complex v2 = {Complex_id};

    if (v == NULL || v->vtype == ptr_v)
	return (zero);
    if (x < 0 || x > v->n)
	return (zero);

    if (x < v->n)
	xi = (int)x;
    else
	xi = v->n;

    x1 = x - xi;
    x2 = 1.0 - x1;
    VECTOR_GETZ(v, xi, v1);
    VECTOR_GETZ(v, xi + 1, v2);
    vi.x = x2 * v1.x + x1 * v2.x;
    vi.y = x2 * v1.y + x1 * v2.y;
    return (vi);
}
