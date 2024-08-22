/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

Imrect *corner2(Imrect * im, double sigma, double precision, double lowthres)
{
    Imrect *gim;
    Imrect *corn_im;
    Imrect *cornim(Imrect * im, double sigma, double precision, double edge_sup);
    Imrect *maxim;
    Imrect *imf_nmax();
    Imrect *imf_gauss();
    void    corner_locate(Imrect * im, Imrect * corner_im);

    gim = imf_gauss(im, sigma, precision);
    im_free(gim);
    corn_im = cornim(gim, sigma, precision, 0.0);
    maxim = imf_nmax(corn_im, 1024 * lowthres, 0);
    corner_locate(maxim, corn_im);
    im_free(corn_im);

    return (maxim);
}

Imrect *corner(Imrect * im, double sigma, double precision, double lowthres)
{
    Imrect *gim;
    Imrect *corn_im;
    Imrect *cornim(Imrect * im, double sigma, double precision, double edge_sup);
    Imrect *maxim;
    Imrect *imf_nmax();
    Imrect *imf_gauss();
    void    corner_locate(Imrect * im, Imrect * corner_im);

    corn_im = cornim(im, sigma, precision, 0.05);
    gim = imf_gauss(corn_im, sigma, precision);
    im_free(corn_im);
    maxim = imf_nmax(gim, 1024 * lowthres, 0);
    corner_locate(maxim, gim);
    im_free(gim);

    return (maxim);
}

Imrect *cornim(Imrect * im, double sigma, double precision, double edge_sup)
{
    Imrect *imf_gauss();
    Imrect *gimx;
    Imrect *gimy;
    Imrect *gimxy;
    Imrect *gimedge;
    Imrect *gradx;
    Imrect *imf_grad_h();
    Imrect *grady;
    Imrect *imf_grad_v();
    Imrect *gradsqx;
    Imrect *gradsqy;
    Imrect *gradsqxy;
    Imrect *gradsqxsqy;
    Imrect *imf_prod();
    Imrect *imf_sum();
    Imrect *corn_im;
    Imrect *cornim2(Imrect * im1, Imrect * im2, Imrect * im3, Imrect * im4, double edge_sup);

    if (im == NULL)
	return (NULL);

    gradx = imf_grad_h(im);
    grady = imf_grad_v(im);
    gradsqx = imf_prod(gradx, gradx);
    gradsqy = imf_prod(grady, grady);
    gradsqxy = imf_prod(gradx, grady);
    im_free(gradx);
    im_free(grady);
    gradsqxsqy = imf_sum(gradsqx, gradsqy);

    gimx = imf_gauss(gradsqx, sigma, precision);
    im_free(gradsqx);
    gimy = imf_gauss(gradsqy, sigma, precision);
    im_free(gradsqy);
    gimxy = imf_gauss(gradsqxy, sigma, precision);
    im_free(gradsqxy);
    gimedge = imf_gauss(gradsqxsqy, 1.1 * sigma, precision);
    im_free(gradsqxsqy);

    corn_im = cornim2(gimx, gimy, gimxy, gimedge, edge_sup);
    im_free(gimx);
    im_free(gimy);
    im_free(gimxy);
    im_free(gimedge);

    return (corn_im);
}

Imrect *cornim2(Imrect * im1, Imrect * im2, Imrect * im3, Imrect * im4, double edge_sup)
{
    Imrect *cornim;
    Imregion *roi;
    float  *line1, *line2, *line3, *line4;
    int     lx, ux, ly, uy;
    int     i, j;

    if (im1 == NULL || im2 == NULL || im3 == NULL)
	return (NULL);

    roi = im1->region;

    if (roi == NULL)
	return (NULL);

    cornim = im_alloc(im1->height, im1->width, roi, float_v);

    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    line1 = fvector_alloc(lx, ux);
    line2 = fvector_alloc(lx, ux);
    line3 = fvector_alloc(lx, ux);
    line4 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(line1, im1, i, lx, ux);
	im_get_rowf(line2, im2, i, lx, ux);
	im_get_rowf(line3, im3, i, lx, ux);
	im_get_rowf(line4, im4, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    IM_FLOAT(cornim, i, j) = (float)(line1[j] * line2[j] - line3[j] * line3[j]
		- edge_sup * line4[j] * line4[j]);
    }

    fvector_free((void *) line1, lx);
    fvector_free((void *) line2, lx);
    fvector_free((void *) line3, lx);
    fvector_free((void *) line4, lx);
    return (cornim);
}

void    corner_locate(Imrect * im, Imrect * corner_im)
{
    Imregion *region;
    float   x, y;
    int     i, j;
    int     lx, ux, ly, uy;

    if (im == NULL || corner_im == NULL)
	return;

    region = im->region;

    lx = region->lx + 1;
    ux = region->ux - 1;
    ly = region->ly + 1;
    uy = region->uy - 1;

    for (i = ly; i < uy; ++i)
    {
	for (j = lx; j < ux; ++j)
	{
	    Edgel  *eptr;

	    if ((eptr = IM_PTR(im, i, j)) == NULL)
		continue;

	    eptr->contrast = (float)im_get_quadmaxf(corner_im, (float) j, (float) i, &x, &y);
	    eptr->pos = vec2(x, y);
	    eptr->type &= EDGE_GET_CONN_MASK;
	    eptr->type |= EDGE_ISOLATED;
	}
    }
}
