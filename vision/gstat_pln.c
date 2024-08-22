/**@(#)
**/
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Basis3 *plane_basis(Plane * plane)
{
    Basis3 *b;
    Basis3 *basis3_alloc();

    b = basis3_alloc();
    vec3_basis(plane->n, vec3_ey(), &b->ex, &b->ey, &b->ez);
    return (b);
}

void    plane_correct(Plane * plane, Basis3 * basis, Vector * x)
{
    double  x0 = vector_getf(x, 0);
    double  x1 = vector_getf(x, 1);
    double  x2 = vector_getf(x, 2);
    Vec3    aim = {Vec3_id};
    Vec3    up = {Vec3_id};

    plane->p = vec3_sum(plane->p, vec3_times(x0, basis->ez));
    aim = vec3_sum3(basis->ez, vec3_times(x1, basis->ex),
		    vec3_times(x2, basis->ey));
    up = vec3_sum(basis->ey, vec3_times(-x2, basis->ez));
    vec3_basis(aim, up, &basis->ex, &basis->ey, &basis->ez);
    plane->n = basis->ez;
}
