/**@(#)
**/
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/* find least square fit of plane through list of assorted 3D geometry */

static void plane_fit_add_point(Matrix * A, Vector * b, int i, Vec3 p, double w)
/* Ax = b */
/* row of matrix/vector */
/* data */
/* weight */
{
    A->el.double_v[i][0] = vec3_x(p) * w;
    A->el.double_v[i][1] = vec3_y(p) * w;
    A->el.double_v[i][2] = w;
    VECTOR_DOUBLE(b, i) = vec3_z(p) * w;
}

Plane  *plane_lsq(List * geom3, float *resid)
/* assorted 3D data (Vec3, Point3, Line3) */

{
    int     n, i;
    Matrix *A;
    Vector *x;
    Vector *b;
    Plane  *plane = NULL;
    List   *ptr;

    if (geom3 == NULL)
	return (NULL);

    for (n = 0, ptr = geom3; ptr != NULL; ptr = ptr->next)
    {
	switch (ptr->type)
	{
	case VEC3:
	case POINT3:
	    n++;
	    break;
	case LINE3:
	    n += 2;
	    break;
	default:
	    break;
	}
    }

    A = matrix_alloc(n, 3, matrix_full, double_v);
    b = vector_alloc(n, double_v);

    for (i = 0, ptr = geom3; ptr != NULL; ptr = ptr->next)
    {
	switch (ptr->type)
	{
	case VEC3:
	    plane_fit_add_point(A, b, i++, *(Vec3 *) ptr->to, 1.0);
	    break;
	case POINT3:
	    plane_fit_add_point(A, b, i++, ((Point3 *) ptr->to)->p, 1.0);
	    break;
	case LINE3:
	    plane_fit_add_point(A, b, i++, ((Line3 *) ptr->to)->p1, 1.0);
	    plane_fit_add_point(A, b, i++, ((Line3 *) ptr->to)->p2, 1.0);
	    break;
	default:
	    break;
	}
    }

    x = matrix_cholesky_least_square(A, b);
    if (x != NULL)
    {
	double  a = VECTOR_DOUBLE(x, 0);
	double  b = VECTOR_DOUBLE(x, 1);
	double  c = VECTOR_DOUBLE(x, 2);
	Vec3    n = {Vec3_id};
	Vec3    p = {Vec3_id};

	n = vec3_unit(vec3(a, b, -1.0));
	p = vec3(0.0, 0.0, c);
	plane = plane_make(p, n, THREEDIM);
    }
    matrix_free(A);
    vector_free(b);
    vector_free(x);

    *resid = (float)0.0;

    return (plane);
}

Vec3    geom3_centroid(List * geom3)
/* assorted 3D data (Vec3, Point3, Line3) */
{
    int     i;
    List   *ptr;
    Vec3    c = {Vec3_id};

    c = vec3(0.0, 0.0, 0.0);
    for (i = 0, ptr = geom3; ptr != NULL; ptr = ptr->next)
    {
	switch (ptr->type)
	{
	case VEC3:
	    c = vec3_sum(c, *(Vec3 *) ptr->to);
	    ++i;
	    break;
	case POINT3:
	    c = vec3_sum(c, ((Point3 *) ptr->to)->p);
	    ++i;
	    break;
	case LINE3:
	    c = vec3_sum(c, ((Line3 *) ptr->to)->p1);
	    c = vec3_sum(c, ((Line3 *) ptr->to)->p2);
	    i += 2;
	    break;
	default:
	    break;
	}
    }
    return ((i == 0) ? c : vec3_times(1.0 / i, c));
}
