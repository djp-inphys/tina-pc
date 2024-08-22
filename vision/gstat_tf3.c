/**@(#)
**/
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

void   *transf3_basis(Transf3 * transf)
/* BUG */
{
    return (NULL);
}

void    transf3_correct(Transf3 * transf, Basis3 * basis, Vector * x)

/* BUG */

{
    double  x0 = vector_getf(x, 0);
    double  x1 = vector_getf(x, 1);
    double  x2 = vector_getf(x, 2);
    double  x3 = vector_getf(x, 3);
    double  x4 = vector_getf(x, 4);
    double  x5 = vector_getf(x, 5);
    Vec3    axis = {Vec3_id};
    Transform3 T = {Transform3_id};

    axis = vec3(x0, x1, x2);
    T.R = rot3_1(axis);
    T.t = vec3(x3, x4, x5);
    transf->T = trans3_prod(T, transf->T);
}
