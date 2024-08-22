/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Imrect *im_tsmooth(Imrect * im1)
{
    Imrect *im2;
    int     ix, iy;
    Imregion *roi;

    if (im1 == NULL)
	return (NULL);

    im2 = im_alloc(im1->height, im1->width, im1->region, im1->vtype);
    roi = im1->region;
    for (ix = roi->lx; ix < roi->ux; ix++)
	for (iy = roi->ly; iy < roi->uy; iy++)
	{
	    double  v0, v2, nx, ny, n;
	    double  x = ix + 0.5;
	    double  y = iy + 0.5;

	    nx = im_sub_pixf(im1, y, x + 0.5) - im_sub_pixf(im1, y, x - 0.5);
	    ny = im_sub_pixf(im1, y + 0.5, x) - im_sub_pixf(im1, y - 0.5, x);
	    n = sqrt(nx * nx + ny * ny);
	    if (n == 0.0)
		n = 1.0;
	    else
	    {
		nx /= n;
		ny /= n;
	    }
	    v0 = im_sub_pixf(im1, y + nx, x - ny);
	    v2 = im_sub_pixf(im1, y - nx, x + ny);
	    IM_PIX_SET(im2, iy, ix, 0.5 * (v0 + v2));
	}
    return (im2);
}
