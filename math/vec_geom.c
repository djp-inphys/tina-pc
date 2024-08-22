/**@(#)Vector geometry (simple).
 */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

double  vector_dot(Vector * v1, Vector * v2)
{
    int     i, nmin;
    double  sum = 0.0, v1i, v2i;

    if (v1 == NULL || v2 == NULL)
	return (0.0);
    nmin = MIN(v1->n, v2->n);
    for (i = 0; i < nmin; i++)
    {
	VECTOR_GET(v1, i, v1i);
	VECTOR_GET(v2, i, v2i);
	sum += v1i * v2i;
    }
    return (sum);
}

Complex vector_dotz(Vector * v1, Vector * v2)
{
    int     i, nmin;
    Complex sum = {Complex_id};
    Complex v1i = {Complex_id};
    Complex v2i = {Complex_id};

    if (v1 == NULL || v2 == NULL)
	return (cmplx_zero());
    nmin = MIN(v1->n, v2->n);
    sum = cmplx_zero();
    for (i = 0; i < nmin; i++)
    {
	VECTOR_GETZ(v1, i, v1i);
	VECTOR_GETZ(v2, i, v2i);
	sum = cmplx_sum(sum, cmplx_cprod(v1i, v2i));
    }
    return (sum);
}

double  vector_mod(Vector * v)
{
    if (v == NULL)
	return (0.0);

    if (v->vtype == complex_v)
	return (sqrt(vector_dotz(v, v).x));
    else
	return (sqrt(vector_dot(v, v)));
}

Vector *vector_unit(Vector * v)
{
    double  m = vector_mod(v);

    return (vector_times(1.0 / m, v));
}

double  vector_sqrmod(Vector * v)
{
    if (v == NULL)
	return (0.0);

    if (v->vtype == complex_v)
	return (vector_dotz(v, v).x);
    else
	return (vector_dot(v, v));
}

double  vector_dist(Vector * v1, Vector * v2)
{
    Vector *v12 = vector_diff(v2, v1);
    double  d;

    d = vector_mod(v12);
    vector_free(v12);
    return (d);
}

double  vector_sqrdist(Vector * v1, Vector * v2)
{
    Vector *v12 = vector_diff(v2, v1);
    double  d;

    d = vector_sqrmod(v12);
    vector_free(v12);
    return (d);
}
