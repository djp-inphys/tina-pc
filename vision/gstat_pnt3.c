/**@(#)
**/
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Basis3 *point3_basis(Point3 * point)
/* BUG */
{
    Basis3 *basis3_alloc();

    return (basis3_alloc());
}

void    point3_correct(Point3 * point, Basis3 * basis, Vector * x)
{
    double  x0 = vector_getf(x, 0);
    double  x1 = vector_getf(x, 1);
    double  x2 = vector_getf(x, 2);

    point->p = vec3_sum(point->p, vec3_times(x0, basis->ex));
    point->p = vec3_sum(point->p, vec3_times(x1, basis->ey));
    point->p = vec3_sum(point->p, vec3_times(x2, basis->ez));
}
