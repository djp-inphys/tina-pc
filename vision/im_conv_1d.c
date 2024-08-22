/**@(#)
**/
/**im_conv_1d.c:

 1d and separable 2d convolution functions

 use `Faltung' convolution convention:
 (func*prof)[i] = Sum func[i-j]*prof[j]

 func is set to 0 when undefined (see smooth.c for another
 convention at limits)

 accepts only floating point convolution profiles
**/

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/vision.h>

/**
Convolves array line1 into line2.
Upper and lower array limits are for line2.
Line1 is assumed to be long enough for prof to go off end of line2.
**/

static void conv_line(float *line1, Prof1 * prof, int lower, int upper, float *line2)
{
    int     i, j;
    int     n1, n2;
    double  sum;
    float  *el = prof->el.float_v;

    n1 = prof->n1;
    n2 = prof->n2;
    for (i = lower; i < upper; i++)
    {
	sum = 0.0;
	for (j = n1; j < n2; j++)
	    sum += line1[i - j] * el[j];
	line2[i] = (float) sum;
    }
}

Imrect *im_conv_h(Imrect * im1, Prof1 * prof)
{
    Imrect *im2;
    Imregion *roi;
    float  *row1, *row2;
    int     lx, ux, ly, uy;
    int     lxn, uxn;
    int     n1, n2;
    int     i;

    if (im1 == NULL)
	return (NULL);
    if (prof == NULL)
	return (NULL);

    if ((roi = im1->region) == NULL)
	return (NULL);

    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    n1 = prof->n1;
    n2 = prof->n2;
    lxn = MAX(lx, lx - n2 + 1);
    uxn = MIN(ux, ux - n1);

    im2 = im_alloc(im1->height, im1->width, roi, float_v);

    row1 = fvector_alloc(lx - n2 + 1, ux - n1);
    row2 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im1, i, lxn, uxn);
	conv_line(row1, prof, lx, ux, row2);
	im_put_rowf(row2, im2, i, lx, ux);
    }

    fvector_free((void *) row1, lx - n2 + 1);
    fvector_free((void *) row2, lx);
    return (im2);
}

Imrect *im_conv_v(Imrect * im1, Prof1 * prof)
{
    Imrect *im2;
    Imregion *roi;
    float  *col1, *col2;
    int     lx, ux, ly, uy;
    int     lyn, uyn;
    int     n1, n2;
    int     i;

    if (im1 == NULL)
	return (NULL);
    if (prof == NULL)
	return (NULL);

    if ((roi = im1->region) == NULL)
	return (NULL);

    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    n1 = prof->n1;
    n2 = prof->n2;
    lyn = MAX(ly, ly - n2 + 1);
    uyn = MIN(uy, uy - n1);

    im2 = im_alloc(im1->height, im1->width, roi, float_v);

    col1 = fvector_alloc(ly - n2 + 1, uy - n1);
    col2 = fvector_alloc(ly, uy);
    for (i = lx; i < ux; ++i)
    {
	im_get_colf(col1, im1, i, lyn, uyn);
	conv_line(col1, prof, ly, uy, col2);
	im_put_colf(col2, im2, i, ly, uy);
    }

    fvector_free((void *) col1, ly - n2 + 1);
    fvector_free((void *) col2, ly);
    return (im2);
}

Imrect *im_conv_separable(Imrect * im1, Prof1 * prof_h, Prof1 * prof_v)
{
    Imrect *im2;
    Imrect *im3;

    if (im1 == NULL)
	return (NULL);
    if (prof_h == NULL)
	return (NULL);
    if (prof_v == NULL)
	return (NULL);

    im2 = im_conv_h(im1, prof_h);
    im3 = im_conv_v(im2, prof_v);

    im_free(im2);
    return (im3);
}
