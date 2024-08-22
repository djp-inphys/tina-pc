/**@(#)
**/
#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

void    line3_format(Line3 * line)
{
    Vec3    p1 = {Vec3_id};
    Vec3    p2 = {Vec3_id};
    Vec3    p = {Vec3_id};
    Vec3    v = {Vec3_id};

    p1 = line->p1;
    p2 = line->p2;
    p = line->p;
    v = line->v;
    format("Line3 :%15d\n", line->label);
    format("length:%15.6f\n", line->length);
    format("p1    :%15.6f%15.6f%15.6f\n", vec3_x(p1), vec3_y(p1), vec3_z(p1));
    format("p2    :%15.6f%15.6f%15.6f\n", vec3_x(p2), vec3_y(p2), vec3_z(p2));
    format("p     :%15.6f%15.6f%15.6f\n", vec3_x(p), vec3_y(p), vec3_z(p));
    format("v     :%15.6f%15.6f%15.6f\n", vec3_x(v), vec3_y(v), vec3_z(v));
    format("\n");
}
