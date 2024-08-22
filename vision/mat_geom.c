/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

static float lthres = (float) 10.0;

void    matcher_set_lthres(double lengththres)
{
    lthres = (float) lengththres;
}

double  matcher_get_lthres(void)
{
    return (lthres);
}

void   *smm_filter(void *geom, int type)
{
    switch (type)
    {
	case POINT3:
	return ((void *) point3_copy((Point3 *) geom));
    case LINE3:
	{
	    Line3  *l = (Line3 *) geom;

	    if (l->length > lthres)
		return ((void *) line3_copy(l));
	    return (NULL);
	}
    case CONIC3:
	{
	    Conic3 *c = (Conic3 *) geom;

	    if (c->type == ELLIPSE)
		return ((void *) conic3_copy(c));
	    return (NULL);
	}
    case PLANE:
	return ((void *) plane_copy((Plane *) geom));
    case TRANSF3:
	return ((void *) transf3_copy((Transf3 *) geom));
    }
    return (NULL);
}

Bool    smm_pwr_allowed_type(int type)
{
    switch (type)
    {
	case POINT3:
	case LINE3:
	case CONIC3:
	return (true);
    default:
	return (false);
    }
}

Vec3    smm_geom_position(void *geom, int type)
{
    switch (type)
    {
	case POINT3:
	return (((Point3 *) geom)->p);
    case LINE3:
	{
	    Line3  *l = (Line3 *) geom;

	    return (vec3_times(0.5, vec3_sum(l->p1, l->p2)));
	}
    case CONIC3:
	return (((Conic3 *) geom)->origin);
    }
    return (vec3(0.0, 0.0, 0.0));
}

double  smm_geom_separation(void *g1, int type1, void *g2, int type2)
{
    Vec3    diff = {Vec3_id};

    diff = vec3_diff(smm_geom_position(g1, type1), smm_geom_position(g2, type2));
    return (vec3_mod(diff));
}

double  smm_geom_sepsq(void *g1, int type1, void *g2, int type2)
{
    Vec3    diff = {Vec3_id};

    diff = vec3_diff(smm_geom_position(g1, type1), smm_geom_position(g2, type2));
    return (vec3_sqrmod(diff));
}

#define PARALLEL_DOTPROD 0.985	/* cos of 10 degrees */

Bool    smm_geom_parallel(void *g1, int type1, void *g2, int type2)
{
    switch (OPAIR(type1, type2))
    {
	case OPAIR(LINE3, LINE3):
	{
	    Line3  *l1 = (Line3 *) g1;
	    Line3  *l2 = (Line3 *) g2;

	    if (fabs(vec3_dot(l1->v, l2->v)) > PARALLEL_DOTPROD)
		return (true);
	    else
		return (false);
	}
    case OPAIR(LINE3, CONIC3):
	{
	    Line3  *l = (Line3 *) g1;
	    Conic3 *c = (Conic3 *) g2;

	    if (fabs(vec3_dot(l->v, c->ez)) > PARALLEL_DOTPROD)
		return (true);
	    else
		return (false);
	}
    case OPAIR(CONIC3, LINE3):
	{
	    Conic3 *c = (Conic3 *) g1;
	    Line3  *l = (Line3 *) g2;

	    if (fabs(vec3_dot(l->v, c->ez)) > PARALLEL_DOTPROD)
		return (true);
	    else
		return (false);
	}
    }
    return (false);
}
