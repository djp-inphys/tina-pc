/**@(#)
**/
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Basis2 *point2_basis(Point2 * point)
/* BUG */

{
    Basis2 *basis2_alloc();

    return (basis2_alloc());
}

void    point2_correct(Point2 * point, Basis2 * basis, Vector * x)
{
    float   x0 = (float)vector_getf(x, 0);
    float   x1 = (float)vector_getf(x, 1);

    point->p = vec2_sum3(point->p, vec2_times(x0, basis->ex),
			 vec2_times(x1, basis->ey));
}
