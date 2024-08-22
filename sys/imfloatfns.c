/**@(#)Image handling (float images).
 */

#include <stdio.h>
#include <tina/sys.h>
#include <tina/sys_types.h>
#include <tina/sysfuncs.h>
#include <tina/image.h>

double  im_get_quadmaxf(Imrect * image, float x, float y, float *px, float *py)
/* image of type float */


/* fits simple quadratic function to image and returns interpolated
 * value and max/min of local area NAT 10/10/90 */
{
    Imregion *region = image->region;
    double   pixval[3][3];
    double   a, b, c, d, e, f;
    double  inter;
    double   temp;
    short   i, j, n, m;
    double   xs, ys;

    i = (int) x - 1;
    j = (int) y - 1;

    if (j < region->ly + 1 || j > region->uy - 1
	|| i < region->lx + 1 || i > region->ux - 1)
	return (0);

    for (n = 0; n < 3; n++)
    {
	for (m = 0; m < 3; m++)
	{
	    pixval[n][m] = im_get_pixf(image, j + n, i + m);
	}
    }

    a = pixval[1][1];
    b = (pixval[0][2] - pixval[0][0]
	 + pixval[1][2] - pixval[1][0]
	 + pixval[2][2] - pixval[2][0]) / 6.0;
    c = (pixval[2][0] - pixval[0][0]
	 + pixval[2][1] - pixval[0][1]
	 + pixval[2][2] - pixval[0][2]) / 6.0;
    d = (pixval[0][0] - 2.0 * pixval[0][1] + pixval[0][2]
	 + 3.0 * pixval[1][0] - 6.0 * pixval[1][1] + 3.0 * pixval[1][2]
	 + pixval[2][0] - 2.0 * pixval[2][1] + pixval[2][2]) / 10.0;
    e = (pixval[0][0] - pixval[2][0]
	 + pixval[2][2] - pixval[0][2]) / 4.0;
    f = (pixval[0][0] + 3.0 * pixval[0][1] + pixval[0][2]
	 - 2.0 * pixval[1][0] - 6.0 * pixval[1][1] - 2.0 * pixval[1][2]
	 + pixval[2][0] + 3.0 * pixval[2][1] + pixval[2][2]) / 10.0;

    temp = 4.0 * d * f - e * e;
    *px = (float) (1.5 + (float) i + (e * c - 2 * f * b) / temp);
    *py = (float) (1.5 + (float) j + (e * b - 2 * d * c) / temp);

    xs = (e * c - 2 * f * b) / temp;
    ys = (e * b - 2 * d * c) / temp;

    inter = a + b * xs + c * ys + d * xs * xs + e * xs * ys + f * ys * ys;

    return (inter);
}

double  im_get_quadinterpf(Imrect * image, float x, float y, float *pdx, float *pdy)
/* image of type float */


/* fits simple quadratic function to image and returns interpolated
 * value NAT 10/10/90 */
{
    Imregion *region = image->region;
    double   pixval[3][3];
    double   a, b, c, d, e, f;
    double  inter;
    short   i, j, n, m;
    double   xs, ys;

    i = (int) x - 1;
    j = (int) y - 1;

    /* assume that pixel contents are exaluated at the centre */
    xs = x - (float) i - 1.5;
    ys = y - (float) j - 1.5;

    if (i < region->ly + 1 || i > region->uy - 1
	|| j < region->lx + 1 || j > region->ux - 1)
	return (0);

    for (n = 0; n < 3; n++)
    {
	for (m = 0; m < 3; m++)
	{
	    pixval[n][m] = im_get_pixf(image, j + n, i + m);
	}
    }

    a = pixval[1][1];
    b = (pixval[0][2] - pixval[0][0]
	 + pixval[1][2] - pixval[1][0]
	 + pixval[2][2] - pixval[2][0]) / 6.0;
    c = (pixval[2][0] - pixval[0][0]
	 + pixval[2][1] - pixval[0][1]
	 + pixval[2][2] - pixval[0][2]) / 6.0;
    d = (pixval[0][0] - 2.0 * pixval[0][1] + pixval[0][2]
	 + 3.0 * pixval[1][0] - 6.0 * pixval[1][1] + 3.0 * pixval[1][2]
	 + pixval[2][0] - 2.0 * pixval[2][1] + pixval[2][2]) / 10.0;
    e = (pixval[0][0] - pixval[2][0]
	 + pixval[2][2] - pixval[0][2]) / 4.0;
    f = (pixval[0][0] + 3.0 * pixval[0][1] + pixval[0][2]
	 - 2.0 * pixval[1][0] - 6.0 * pixval[1][1] - 2.0 * pixval[1][2]
	 + pixval[2][0] + 3.0 * pixval[2][1] + pixval[2][2]) / 10.0;

    *pdx = (float) (b + 2.0 * d * xs + e * ys);
    *pdy = (float) (c + e * xs + 2.0 * f * ys);

    inter = a + b * xs + c * ys + d * xs * xs + e * xs * ys + f * ys * ys;

    return (inter);
}
