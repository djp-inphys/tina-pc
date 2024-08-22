/**@(#)
**/
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

void   *scalar_basis();
Basis2 *point2_basis();
Basis2 *line2_basis();
Basis3 *point3_basis();
Basis3 *line3_basis();
Basis3 *plane_basis();

int     geom_df(int type)
{
    switch (type)
    {
	case SCALAR:
	return (1);
    case POINT2:
	return (2);
    case LINE2:
	return (2);
    case POINT3:
	return (3);
    case LINE3:
	return (4);
    case PLANE:
	return (3);
    case TRANSF3:
	return (4);
    }
    return (0);
}

void   *geom_basis(void *geom, int type)
{
    switch (type)
    {
	case SCALAR:
	return (NULL);
    case POINT2:
	return ((void *) point2_basis((Point2 *) geom));
    case LINE2:
	return ((void *) line2_basis((Line2 *) geom));
    case POINT3:
	return ((void *) point3_basis((Point3 *) geom));
    case LINE3:
	return ((void *) line3_basis((Line3 *) geom));
    case PLANE:
	return ((void *) plane_basis((Plane *) geom));
    case TRANSF3:
	return (NULL);
    }
    return (NULL);
}

void    geom_set_infcov(int type, Matrix * s, double lscale)
{
    double  big = 1, lbig;

    lbig = big * lscale;

    switch (type)
    {
    case SCALAR:
	matrix_putf(big, s, 0, 0);
	break;
    case POINT2:
	matrix_putf(lbig, s, 0, 0);
	matrix_putf(lbig, s, 1, 1);
	break;
    case LINE2:
	matrix_putf(lbig, s, 0, 0);
	matrix_putf(big, s, 1, 1);
	break;
    case POINT3:
	matrix_putf(lbig, s, 0, 0);
	matrix_putf(lbig, s, 1, 1);
	matrix_putf(lbig, s, 2, 2);
	break;
    case LINE3:
	matrix_putf(lbig, s, 0, 0);
	matrix_putf(lbig, s, 1, 1);
	matrix_putf(big, s, 2, 2);
	matrix_putf(big, s, 3, 3);
	break;
    case PLANE:
	matrix_putf(lbig, s, 0, 0);
	matrix_putf(big, s, 1, 1);
	matrix_putf(big, s, 2, 2);
	break;
    case TRANSF3:
	matrix_putf(big, s, 0, 0);
	matrix_putf(big, s, 1, 1);
	matrix_putf(big, s, 2, 2);
	matrix_putf(lbig, s, 0, 3);
	matrix_putf(lbig, s, 1, 4);
	matrix_putf(lbig, s, 2, 5);
	break;
    }
}

void    geom_correct(void *geom, int type, void *basis, Vector * x)
{
    if (x == NULL)
	return;
    switch (type)
    {
    case SCALAR:
	scalar_correct((Scalar *) geom, NULL, x);
	return;
    case POINT2:
	point2_correct((Point2 *) geom, (Basis2 *) basis, x);
	return;
    case LINE2:
	line2_correct((Line2 *) geom, (Basis2 *) basis, x);
	return;
    case POINT3:
	point3_correct((Point3 *) geom, (Basis3 *) basis, x);
	return;
    case LINE3:
	line3_correct((Line3 *) geom, (Basis3 *) basis, x);
	return;
    case PLANE:
	plane_correct((Plane *) geom, (Basis3 *) basis, x);
	return;
    case TRANSF3:
	transf3_correct((Transf3 *) geom, (Basis3 *) NULL, x);
	return;
    }
}

int     geom_rank(int type)
{
    switch (type)
    {
	case SCALAR:
	return (1);
    case POINT2:
	return (2);
    case POINT3:
	return (3);
    case LINE2:
	return (4);
    case LINE3:
	return (5);
    case PLANE:
	return (6);
    case TRANSF3:
	return (7);
    default:
	return (0);
    }
}

Bool    geom_reorder(int *index1, int *index2, int *type1, int *type2)
{
    if (geom_rank(*type1) > geom_rank(*type2))
    {
	int     s;

	s = *index1;
	*index1 = *index2;
	*index2 = s;
	s = *type1;
	*type1 = *type2;
	*type2 = s;
	return (true);
    }
    return (false);
}

double  geom_angle(void *geom1, int type1, void *geom2, int type2)
{
    if (geom_rank(type1) > geom_rank(type2))
    {
	SWAP(void *, geom1, geom2);
	SWAP(int, type1, type2);
    }
    switch (OPAIR(type1, type2))
    {
    case OPAIR(LINE3, LINE3):
	{
	    Line3  *line1 = (Line3 *) geom1;
	    Line3  *line2 = (Line3 *) geom2;

	    return (vec3_angle(line1->v, line2->v));
	}
    case OPAIR(LINE3, PLANE):
	{
	    Line3  *line = (Line3 *) geom1;
	    Plane  *plane = (Plane *) geom2;

	    return (vec3_angle(line->v, plane->n));
	}
    case OPAIR(PLANE, PLANE):
	{
	    Plane  *plane1 = (Plane *) geom1;
	    Plane  *plane2 = (Plane *) geom2;

	    return (vec3_angle(plane1->n, plane2->n));
	}
    default:
	error("geom_angle: bad type", non_fatal);
	return (1e10);
    }
}

double  geom_dist(void *geom1, int type1, void *geom2, int type2)
{
    if (geom_rank(type1) > geom_rank(type2))
    {
	SWAP(void *, geom1, geom2);
	SWAP(int, type1, type2);
    }
    switch (OPAIR(type1, type2))
    {
    case OPAIR(POINT3, POINT3):
	{
	    Point3 *point1 = (Point3 *) geom1;
	    Point3 *point2 = (Point3 *) geom2;

	    return (vec3_dist(point1->p, point2->p));
	}
    case OPAIR(POINT3, LINE3):
	{
	    Point3 *point = (Point3 *) geom1;
	    Line3  *line = (Line3 *) geom2;

	    return (vec3_dist_point_line(point->p, line->p, line->v));
	}
    case OPAIR(POINT3, PLANE):
	{
	    Point3 *point = (Point3 *) geom1;
	    Plane  *plane = (Plane *) geom2;

	    return (vec3_dist_point_plane(point->p, plane->p, plane->n));
	}
    case OPAIR(LINE3, LINE3):
	{
	    Line3  *line1 = (Line3 *) geom1;
	    Line3  *line2 = (Line3 *) geom2;

	    return (vec3_dist_lines(line1->p, line1->v, line2->p, line2->v));
	}
    default:
	error("geom_angle: bad type", non_fatal);
	return (1e10);
    }
}
