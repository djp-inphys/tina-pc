/**@(#)Obtain general image raster
 */

#include <stdio.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

void    im_get_interp_rast(float *line, Imrect * image, Vec2 p, Vec2 v, int n1, int n2, double ds)


/* define point and direction of interpolation */
/* relative coodinates (0 is the point p) */
/* step */
{
    int     i;
    Vec2    pi = {Vec2_id};

    if (image == NULL)
	return;

    for (i = n1; i < n2; ++i)
    {
	pi = vec2_sum(p, vec2_times(i * ds, v));
	line[i] = im_sub_pixf(image, vec2_y(pi), vec2_x(pi));
    }
}
