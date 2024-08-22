/**@(#)
**/
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

void   *geom_prop_get(void *p, int type, int prop)
{
    switch (type)
    {
	case SCALAR:
	return (prop_get(((Scalar *) p)->props, prop));
    case POINT2:
	return (prop_get(((Point2 *) p)->props, prop));
    case LINE2:
	return (prop_get(((Line2 *) p)->props, prop));
    case CONIC2:
	return (prop_get(((Conic *) p)->props, prop));
    case POINT3:
	return (prop_get(((Point3 *) p)->props, prop));
    case LINE3:
	return (prop_get(((Line3 *) p)->props, prop));
    case CONIC3:
	{
	    Conic3 *con3 = p;

	    if (con3->conic == NULL)
		return (NULL);
	    return (prop_get(con3->conic->props, prop));
	}
    case PLANE:
	return (prop_get(((Plane *) p)->props, prop));
    case TRANSF3:
	return (prop_get(((Transf3 *) p)->props, prop));
    }
    return (NULL);
}

void   *geom_prop_update_get(void *p, int *type, int prop)
{
    int     stype = *type;

    /* BUGFIX JB 22/11/93 was    *type - prop; */
    *type = prop;
    switch (stype)
    {
    case SCALAR:
	return (prop_get(((Scalar *) p)->props, prop));
    case POINT2:
	return (prop_get(((Point2 *) p)->props, prop));
    case LINE2:
	return (prop_get(((Line2 *) p)->props, prop));
    case CONIC2:
	return (prop_get(((Conic *) p)->props, prop));
    case POINT3:
	return (prop_get(((Point3 *) p)->props, prop));
    case LINE3:
	return (prop_get(((Line3 *) p)->props, prop));
    case CONIC3:
	{
	    Conic3 *con3 = p;

	    if (con3->conic == NULL)
		return (NULL);
	    return (prop_get(con3->conic->props, prop));
	}
    case PLANE:
	return (prop_get(((Plane *) p)->props, prop));
    case TRANSF3:
	return (prop_get(((Transf3 *) p)->props, prop));
    }
    return (NULL);
}

void    geom_prop_add(void *geom, int type, void *prop, int prop_type, void (*freefunc) ( /* ??? */ ))
{
    switch (type)
    {
	case SCALAR:
	{
	    Scalar *s = (Scalar *) geom;

	    s->props = proplist_add(s->props, (void *) prop, prop_type, freefunc);
	    break;
	}
    case POINT2:
	{
	    Point2 *p = (Point2 *) geom;

	    p->props = proplist_add(p->props, (void *) prop, prop_type, freefunc);
	    break;
	}
    case LINE2:
	{
	    Line2  *l = (Line2 *) geom;

	    l->props = proplist_add(l->props, (void *) prop, prop_type, freefunc);
	    break;
	}
    case CONIC2:
	{
	    Conic  *c = (Conic *) geom;

	    c->props = proplist_add(c->props, (void *) prop, prop_type, freefunc);
	    break;
	}
    case POINT3:
	{
	    Point3 *p = (Point3 *) geom;

	    p->props = proplist_add(p->props, (void *) prop, prop_type, freefunc);
	    break;
	}
    case LINE3:
	{
	    Line3  *l = (Line3 *) geom;

	    l->props = proplist_add(l->props, (void *) prop, prop_type, freefunc);
	    break;
	}
    case CONIC3:
	{
	    Conic  *c;

	    if (((Conic3 *) geom)->conic == NULL)
		break;
	    c = ((Conic3 *) geom)->conic;
	    c->props = proplist_add(c->props, (void *) prop, prop_type, freefunc);
	    break;
	}
    case PLANE:
	{
	    Plane  *p = (Plane *) geom;

	    p->props = proplist_add(p->props, (void *) prop, prop_type, freefunc);
	    break;
	}
    case TRANSF3:
	{
	    Transf3 *t = (Transf3 *) geom;

	    t->props = proplist_add(t->props, (void *) prop, prop_type, freefunc);
	    break;
	}
    }
}

void    geom_prop_addifnp(void *geom, int type, void *prop, int prop_type, void (*freefunc) ( /* ??? */ ), Bool dofree)
{
    switch (type)
    {
	case SCALAR:
	{
	    Scalar *s = (Scalar *) geom;

	    s->props = proplist_addifnp(s->props, (void *) prop, prop_type, freefunc, dofree);
	    break;
	}
    case POINT2:
	{
	    Point2 *p = (Point2 *) geom;

	    p->props = proplist_addifnp(p->props, (void *) prop, prop_type, freefunc, dofree);
	    break;
	}
    case LINE2:
	{
	    Line2  *l = (Line2 *) geom;

	    l->props = proplist_addifnp(l->props, (void *) prop, prop_type, freefunc, dofree);
	    break;
	}
    case CONIC2:
	{
	    Conic  *c = (Conic *) geom;

	    c->props = proplist_addifnp(c->props, (void *) prop, prop_type, freefunc, dofree);
	    break;
	}
    case POINT3:
	{
	    Point3 *p = (Point3 *) geom;

	    p->props = proplist_addifnp(p->props, (void *) prop, prop_type, freefunc, dofree);
	    break;
	}
    case LINE3:
	{
	    Line3  *l = (Line3 *) geom;

	    l->props = proplist_addifnp(l->props, (void *) prop, prop_type, freefunc, dofree);
	    break;
	}
    case CONIC3:
	{
	    Conic  *c;

	    if (((Conic3 *) geom)->conic == NULL)
		break;
	    c = ((Conic3 *) geom)->conic;
	    c->props = proplist_addifnp(c->props, (void *) prop, prop_type, freefunc, dofree);
	    break;
	}
    case PLANE:
	{
	    Plane  *p = (Plane *) geom;

	    p->props = proplist_addifnp(p->props, (void *) prop, prop_type, freefunc, dofree);
	    break;
	}
    case TRANSF3:
	{
	    Transf3 *t = (Transf3 *) geom;

	    t->props = proplist_addifnp(t->props, (void *) prop, prop_type, freefunc, dofree);
	    break;
	}
    }
}

void    geom_add_image_pos_prop(void *geom, int type, Mat3 * rect)
{
    switch (type)
    {
	case LINE2:
	{
	    Line2  *line;
	    Line2  *imline;

	    line = (Line2 *) geom;
	    imline = line2_rectify(line, *rect);
	    line->props = proplist_addifnp(line->props, (void *) imline,
			       IMPOS, (void (*) ()) line2_free, true);
	    break;
	}
    case CONIC2:
	{
	    Conic  *conic;
	    Conic  *imcon;

	    conic = (Conic *) geom;
	    imcon = conic_rectify(conic, *rect);
	    conic->props = proplist_addifnp(conic->props, (void *) imcon,
			       IMPOS, (void (*) ()) conic_free, true);
	    break;
	}
    }
}
