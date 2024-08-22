/**@(#)
**/
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

void    scalar_correct(Scalar * scalar, void *basis, Vector * x)

/* BUG */

{
    scalar->val += (float)vector_getf(x, 0);
}
