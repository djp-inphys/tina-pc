/**@(#)
**/
#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

void    line2_format(Line2 * line)
{
    Vec2    p1 = {Vec2_id};
    Vec2    p2 = {Vec2_id};
    Vec2    v = {Vec2_id};

    p1 = line->p1;
    p2 = line->p2;
    v = line->v;
    format("Line2 :%15d\n", line->label);
    format("length:%15.6f\n", line->length);
    format("p1    :%15.6f%15.6f\n", vec2_x(p1), vec2_y(p1));
    format("p2    :%15.6f%15.6f\n", vec2_x(p2), vec2_y(p2));
    format("v     :%15.6f%15.6f\n", vec2_x(v), vec2_y(v));
    format("\n");
}
