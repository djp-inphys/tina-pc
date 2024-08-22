/**@(#)Find max and min x,y,z extent of a set of vectors sequentially
**/

#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

void    vec3_extend_hull(Vec3 * vmin, Vec3 * vmax, Vec3 v)
{
    double  xmin = vec3_x(*vmin), ymin = vec3_y(*vmin), zmin = vec3_z(*vmin);
    double  xmax = vec3_x(*vmax), ymax = vec3_y(*vmax), zmax = vec3_z(*vmax);
    double  s;

    s = vec3_x(v);
    if (s < xmin)
	xmin = s;
    if (s > xmax)
	xmax = s;
    s = vec3_y(v);
    if (s < ymin)
	ymin = s;
    if (s > ymax)
	ymax = s;
    s = vec3_z(v);
    if (s < zmin)
	zmin = s;
    if (s > zmax)
	zmax = s;
    *vmin = vec3(xmin, ymin, zmin);
    *vmax = vec3(xmax, ymax, zmax);
}
