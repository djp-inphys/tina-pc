/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

Imrect *imf_sample(double k, Imrect * im)
{
    Imrect *im2;
    int     width, height;
    Imregion *region;
    int     lx, ux, ly, uy;
    int     x, y;

    if (im == NULL)
	return (NULL);

    region = roi_copy(im->region);
    lx = region->lx = (int)(region->lx*k);
    ly = region->ly = (int)(region->ly*k);
    ux = region->ux = (int)(region->ux*k);
    uy = region->uy = (int)(region->uy*k);
    width = (int)(k * im->width);
    height = (int)(k * im->height);

    im2 = im_alloc(height, width, region, float_v);

    for (x = lx; x < ux; x++)
	for (y = ly; y < uy; y++)
	{
	    float   pixval;

	    pixval = (float) im_sub_pixqf(im, (y + 0.5) / k, (x + 0.5) / k);
	    im_put_pixf(pixval, im2, y, x);
	}

    return (im2);
}

Imrect *imf_halve(Imrect * im)
{
    Imrect *im2;
    int     width, height;
    Imregion *roi;
    int     x, y;
    double  g1, g2, g3, g4, g;

    if (im == NULL)
	return (NULL);

    roi = roi_copy(im->region);
    roi->lx = (int)ceil(roi->lx / 2.0);
    roi->ly = (int)ceil(roi->ly / 2.0);
    roi->ux = (int)floor(roi->ux / 2.0);
    roi->uy = (int)floor(roi->uy / 2.0);
    width = (int)floor(im->width / 2.0);
    height = (int)floor(im->height / 2.0);

    im2 = im_alloc(height, width, roi, float_v);

    for (x = roi->lx; x < roi->ux; x++)
	for (y = roi->ly; y < roi->uy; y++)
	{
	    int     x2 = 2 * x, y2 = 2 * y;

	    IM_PIX_GET(im, y2, x2, g1);
	    IM_PIX_GET(im, y2 + 1, x2, g2);
	    IM_PIX_GET(im, y2, x2 + 1, g3);
	    IM_PIX_GET(im, y2 + 1, x2 + 1, g4);
	    g = 0.25 * (g1 + g2 + g3 + g4);
	    IM_PIX_SET(im2, y, x, g);
	}

    return (im2);
}
