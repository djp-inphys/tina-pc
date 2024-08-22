/**@(#)
**/
#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

#define I 	176.0
#define F        18.0
#define PIX       0.011
#define FUDGE     2.0

/** Mock up of typical camera geometry **/

double  cam_f(void)
{
    return (F);
}

double  cam_pix(void)
{
    return (FUDGE * PIX);
}

Vec3    left_origin(void)
{
    return (vec3_zero());
}

Vec3    right_origin(void)
{
    return (vec3(I, 0.0, 0.0));
}
