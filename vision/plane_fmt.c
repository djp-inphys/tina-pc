/**@(#)
**/
#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

void    plane_format(Plane * plane)
{
    Vec3    p = {Vec3_id};
    Vec3    n = {Vec3_id};

    p = plane->p;
    n = plane->n;
    format("Plane :%15d\n", plane->label);
    format("p     :%15.6f%15.6f%15.6f\n", vec3_x(p), vec3_y(p), vec3_z(p));
    format("n     :%15.6f%15.6f%15.6f\n", vec3_x(n), vec3_y(n), vec3_z(n));
    format("\n");
}
