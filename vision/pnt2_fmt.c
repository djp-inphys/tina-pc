/**@(#)
**/
#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

void    point2_format(Point2 * point)
{
    Vec2    p = {Vec2_id};

    p = point->p;
    format("Point2:%15d\n", point->label);
    format("p     :%15.6f%15.6f\n", vec2_x(p), vec2_y(p));
    format("\n");
}
