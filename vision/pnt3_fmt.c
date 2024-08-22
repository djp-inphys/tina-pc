/**@(#)
**/
#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

void    point3_format(Point3 * point)
{
    Vec3    p = {Vec3_id};

    p = point->p;
    format("Point3:%15d\n", point->label);
    format("p     :%15.6f%15.6f%15.6f\n", vec3_x(p), vec3_y(p), vec3_z(p));
    format("\n");
}
