/**@(#)Vector (1 dimensional array) handling (biggest component etc)
 */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>

double  vector_max(Vector * v, int *imax)
{
    int     i;
    double  vi, vmax;

    if (imax != NULL)
	*imax = 0;
    if (v == NULL)
	return (0.0);

    VECTOR_GET(v, 0, vmax);
    for (i = 1; i < v->n; i++)
    {
	VECTOR_GET(v, i, vi);
	if (vmax < vi)
	{
	    vmax = vi;
	    if (imax != NULL)
		*imax = i;
	}
    }
    return (vmax);
}

double  vector_min(Vector * v, int *imin)
{
    int     i;
    double  vi, vmin;

    if (imin != NULL)
	*imin = 0;
    if (v == NULL)
	return (0.0);

    VECTOR_GET(v, 0, vmin);
    for (i = 1; i < v->n; i++)
    {
	VECTOR_GET(v, i, vi);
	if (vmin > vi)
	{
	    vmin = vi;
	    if (imin != NULL)
		*imin = i;
	}
    }
    return (vmin);
}

double  vector_maxmod(Vector * v, int *imax)
{
    int     i;
    double  vmod, vmax;

    if (imax != NULL)
	*imax = 0;
    if (v == NULL)
	return (0.0);

    if (v->vtype == complex_v)
    {
	Complex vi = {Complex_id};

	VECTOR_GETZ(v, 0, vi);
	vmax = cmplx_sqrmod(vi);
	for (i = 1; i < v->n; i++)
	{
	    VECTOR_GETZ(v, i, vi);
	    vmod = cmplx_sqrmod(vi);
	    if (vmax < vmod)
	    {
		vmax = vmod;
		if (imax != NULL)
		    *imax = i;
	    }
	}
    } else
    {
	double  vi;

	VECTOR_GET(v, 0, vi);
	vmax = fabs(vi);
	for (i = 1; i < v->n; i++)
	{
	    VECTOR_GET(v, i, vi);
	    vmod = fabs(vi);
	    if (vmax < vmod)
	    {
		vmax = vmod;
		if (imax != NULL)
		    *imax = i;
	    }
	}
    }
    return (vmax);
}

double  vector_minmod(Vector * v, int *imin)
{
    int     i;
    double  vmod, vmin;

    if (imin != NULL)
	*imin = 0;
    if (v == NULL)
	return (0.0);

    if (v->vtype == complex_v)
    {
	Complex vi = {Complex_id};

	VECTOR_GETZ(v, 0, vi);
	vmin = cmplx_sqrmod(vi);
	for (i = 1; i < v->n; i++)
	{
	    VECTOR_GETZ(v, i, vi);
	    vmod = cmplx_sqrmod(vi);
	    if (vmin > vmod)
	    {
		vmin = vmod;
		if (imin != NULL)
		    *imin = i;
	    }
	}
    } else
    {
	double  vi;

	VECTOR_GET(v, 0, vi);
	vmin = fabs(vi);
	for (i = 1; i < v->n; i++)
	{
	    VECTOR_GET(v, i, vi);
	    vmod = fabs(vi);
	    if (vmin > vmod)
	    {
		vmin = vmod;
		if (imin != NULL)
		    *imin = i;
	    }
	}
    }
    return (vmin);
}
