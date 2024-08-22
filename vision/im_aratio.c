/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

Imrect *imf_aratio(double k, Imrect * im)
{
    Imrect *im2;
    int     width, height;
    double  x, y;

    width = im->width;
    height = (int) (k * im->height);

    im2 = im_alloc(height, width, (Imregion *) NULL, float_v);

    for (x = 0.5; x < width; x++)
	for (y = 0.5; y < height; y++)
	{
	    double   pixval;

	    pixval = im_sub_pixf(im, (y +0.5) / k, x+0.5);
	    im_put_pixf(pixval, im2, tina_int(y), tina_int(x));
	}

    return (im2);
}

Imrect *imf_bratio(double k, Imrect * im)
{
    Imrect *im2;
    int     width, height;
    double  x, y;

    width = (int) (k * im->width);
    height = im->height;

    im2 = im_alloc(height, width, (Imregion *) NULL, float_v);

    for (x = 0.5; x < width; x++)
        for (y = 0.5; y < height; y++)
        {
            double   pixval;

            pixval = im_sub_pixf(im, y+0.5 , (x+0.5)/k );
            im_put_pixf(pixval, im2, tina_int(y), tina_int(x));
        }

    return (im2);
}
