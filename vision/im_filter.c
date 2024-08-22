/**@(#)
**/
/* filter_1d.c
 * 
 * one dimensional generic filtering functions
 * 
 * functions convert to floating point images
 * 
 */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/vision.h>

Imrect *im_filter_rows(Imrect * image, void (*func) ( /* ??? */ ), void *data)
/* image to be filtered */


{
    Imrect *filtered_im;
    float  *line;
    int     lx, ux, ly, uy;
    int     i;

    if (image == NULL)
	return (NULL);

    lx = image->region->lx;
    ux = image->region->ux;
    ly = image->region->ly;
    uy = image->region->uy;

    filtered_im = im_alloc(image->height, image->width, image->region, float_v);
    line = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(line, image, i, lx, ux);
	func(line, lx, ux, data);
	im_put_rowf(line, filtered_im, i, lx, ux);
    }

    fvector_free((void *) line, lx);
    return (filtered_im);
}

Imrect *im_filter_cols(Imrect * image, void (*func) ( /* ??? */ ), void *data)
/* image to be filtered */


{
    Imrect *filtered_im;
    float  *line;
    int     lx, ux, ly, uy;
    int     i;

    if (image == NULL)
	return (NULL);

    lx = image->region->lx;
    ux = image->region->ux;
    ly = image->region->ly;
    uy = image->region->uy;

    filtered_im = im_alloc(image->height, image->width, image->region, float_v);
    line = fvector_alloc(ly, uy);

    for (i = lx; i < ux; ++i)
    {
	im_get_colf(line, image, i, ly, uy);
	func(line, ly, uy, data);
	im_put_colf(line, filtered_im, i, ly, uy);
    }

    fvector_free((void *) line, ly);
    return (filtered_im);
}
