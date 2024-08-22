/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>

Imrect *imf_grad_h(Imrect * image)
{
    Imrect *grad_im;
    float  *line;
    int     lx, ux, ly, uy;
    int     uxm1;
    int     i, j;

    if (image == NULL)
	return (NULL);

    lx = image->region->lx;
    ux = image->region->ux;
    ly = image->region->ly;
    uy = image->region->uy;
    uxm1 = ux - 1;

    grad_im = im_alloc(image->height, image->width, image->region, float_v);
    line = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(line, image, i, lx, ux);
	IM_FLOAT(grad_im, i, lx) = line[lx + 1] - line[lx];
	for (j = lx + 1; j < uxm1; ++j)
	    IM_FLOAT(grad_im, i, j) = (float)((line[j + 1] - line[j - 1]) * 0.5);
	IM_FLOAT(grad_im, i, uxm1) = line[uxm1] - line[uxm1 - 1];
    }

    fvector_free((void *) line, lx);
    return (grad_im);
}

Imrect *imf_grad_v(Imrect * image)
{
    Imrect *grad_im;
    float  *line;
    int     lx, ux, ly, uy;
    int     uym1;
    int     i, j;

    if (image == NULL)
	return (NULL);

    lx = image->region->lx;
    ux = image->region->ux;
    ly = image->region->ly;
    uy = image->region->uy;
    uym1 = uy - 1;

    grad_im = im_alloc(image->height, image->width, image->region, float_v);
    line = fvector_alloc(ly, uy);

    for (i = lx; i < ux; ++i)
    {
	im_get_colf(line, image, i, ly, uy);
	IM_FLOAT(grad_im, ly, i) = line[ly + 1] - line[ly];
	for (j = ly + 1; j < uym1; ++j)
	    IM_FLOAT(grad_im, j, i) = (float)((line[j + 1] - line[j - 1]) * 0.5);
	IM_FLOAT(grad_im, uym1, i) = line[uym1] - line[uym1 - 1];
    }

    fvector_free((void *) line, ly);
    return (grad_im);
}
