/**@(#)
**/
#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

void    scalar_format(Scalar * scalar)
{
    format("Scalar:%15d\n", scalar->label);
    format("val   :%15.6f", scalar->val);
    format("\n");
}
