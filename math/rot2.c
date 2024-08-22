/**@(#)Rotation
**/
#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

Mat2    rot2(double theta)
{
    double  c = cos(theta);
    double  s = sin(theta);

    return (mat2(c, -s,
		 s, c));
}

double  rot2_angle(Mat2 m)
{
    return (atan2(mat2_yx(m), mat2_xx(m)));
}

/* APA 2/2/94 */

Mat2   rot2_with_scale(double theta, double scale_factor)
{
    double          c = cos(theta)*scale_factor;
    double          s = sin(theta)*scale_factor;
    return (mat2(c, -s, s, c));
}
