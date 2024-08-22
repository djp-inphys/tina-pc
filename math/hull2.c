/**@(#)Find max and min x,y extent of a set of vectors sequentially
**/
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>


void    vec2_extend_hull(Vec2 * vmin, Vec2 * vmax, Vec2 v)
{
    double  xmin = vec2_x(*vmin), ymin = vec2_y(*vmin);
    double  xmax = vec2_x(*vmax), ymax = vec2_y(*vmax);
    double  s;

    s = vec2_x(v);
    if (s < xmin)
	xmin = s;
    if (s > xmax)
	xmax = s;
    s = vec2_y(v);
    if (s < ymin)
	ymin = s;
    if (s > ymax)
	ymax = s;
    *vmin = vec2(xmin, ymin);
    *vmax = vec2(xmax, ymax);
}
