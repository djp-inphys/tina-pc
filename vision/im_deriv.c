/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/** applying functions to images, inplace version, and special cases **/

Imrect *imf_diffx(Imrect * im1)
{
    Imrect *im2;
    Imregion *roi;
    float  *row1, *row2;
    int     lx, ux, ly, uy;
    int     i, j;

    if (im1 == NULL)
	return (NULL);

    roi = im1->region;

    if (roi == NULL)
	return (NULL);

    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    if (lx == ux)
	return (NULL);

    im2 = im_alloc(im1->height, im1->width, roi, float_v);
    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im1, i, lx, ux);
	row2[lx] = row1[lx + 1] - row1[lx];
	for (j = lx + 1; j < ux - 1; ++j)
	    row2[j] = (float)(0.5 * (row1[j + 1] - row1[j - 1]));
	row2[ux - 1] = row1[ux - 1] - row1[ux - 2];
	im_put_rowf(row2, im2, i, lx, ux);
    }

    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    return (im2);
}

Imrect *imf_diffy(Imrect * im1)
{
    Imrect *im2;
    Imregion *roi;
    float  *col1, *col2;
    int     lx, ux, ly, uy;
    int     i, j;

    roi = im1->region;

    if (roi == NULL)
	return (NULL);

    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    if (ly == uy)
	return (NULL);

    im2 = im_alloc(im1->height, im1->width, roi, float_v);
    col1 = fvector_alloc(ly, uy);
    col2 = fvector_alloc(ly, uy);

    for (i = lx; i < ux; ++i)
    {
	im_get_colf(col1, im1, i, ly, uy);
	col2[ly] = col1[ly + 1] - col1[ly];
	for (j = ly + 1; j < uy - 1; ++j)
	    col2[j] = (float)(0.5 * (col1[j + 1] - col1[j - 1]));
	col2[uy - 1] = col1[uy - 1] - col1[uy - 2];
	im_put_colf(col2, im2, i, ly, uy);
    }

    fvector_free((void *) col1, ly);
    fvector_free((void *) col2, ly);
    return (im2);
}

/* set both x and y derivatives */
void    im_grad(Imrect * im, Imrect ** imx, Imrect ** imy)
{
    *imx = imf_diffx(im);
    *imy = imf_diffx(im);
}

/* set both x and y derivatives, and second derivatives (if first
 * derivs un-needed, pass null pointer) */

void    im_hessian(Imrect * im, Imrect ** imx, Imrect ** imy, Imrect ** imxx, Imrect ** imxy, Imrect ** imyy)
{
    Imrect *imx1;
    Imrect *imy1;

    imx1 = imf_diffx(im);
    imy1 = imf_diffy(im);
    *imxx = imf_diffx(imx1);

    if (imx == NULL)
	im_free(imx1);
    else
	*imx = imx1;

    *imxy = imf_diffx(imy1);
    *imyy = imf_diffy(imy1);

    if (imy == NULL)
	im_free(imy1);
    else
	*imy = imy1;
}

/** image differential invariants **/

/* Laplacian */

Imrect *imf_laplacian(Imrect * im)
{
    Imrect *imx;
    Imrect *imxx;
    Imrect *imy;
    Imrect *imyy;

    imx = imf_diffx(im);
    imxx = imf_diffx(imx);
    im_free(imx);
    imy = imf_diffy(im);
    imyy = imf_diffy(imy);
    im_free(imy);
    im = imf_sum(imxx, imyy);
    im_free(imxx);
    im_free(imyy);
    return (im);
}

/* Squared gradient */

Imrect *imf_sqrgrad(Imrect * im)
{
    Imrect *imx;
    Imrect *imxx;
    Imrect *imy;
    Imrect *imyy;

    imx = imf_diffx(im);
    imxx = imf_sqr(imx);
    im_free(imx);
    imy = imf_diffy(im);
    imyy = imf_sqr(imy);
    im_free(imy);
    im = imf_sum(imxx, imyy);
    im_free(imxx);
    im_free(imyy);
    return (im);
}

/* Matrix op */

Imrect *imf_matop(Imrect * ax, Imrect * ay, Imrect * mxx, Imrect * mxy, Imrect * myx, Imrect * myy, Imrect * bx, Imrect * by)
{
    Imrect *im1;
    Imrect *im2;
    Imrect *mx;
    Imrect *my;
    Imrect *m;

    im1 = imf_prod(mxx, bx);
    im2 = imf_prod(mxy, by);
    mx = imf_sum(im1, im2);
    im_free(im1);
    im_free(im2);

    im1 = imf_prod(myx, bx);
    im2 = imf_prod(myy, by);
    my = imf_sum(im1, im2);
    im_free(im1);
    im_free(im2);

    im1 = imf_prod(ax, mx);
    im2 = imf_prod(ay, my);
    m = imf_sum(im1, im2);
    im_free(im1);
    im_free(im2);

    im_free(mx);
    im_free(my);

    return (m);
}

/* Second order image invariants */

Imrect *imf_ddn(Imrect * im)
{
    Imrect *imx;
    Imrect *imy;
    Imrect *imxx;
    Imrect *imxy;
    Imrect *imyy;

    im_hessian(im, &imx, &imy, &imxx, &imxy, &imyy);
    im = imf_matop(imx, imy, imxx, imxy, imxy, imyy, imx, imy);

    im_free(imx);
    im_free(imy);
    im_free(imxx);
    im_free(imxy);
    im_free(imyy);

    return (im);
}

Imrect *imf_ddt(Imrect * im)
{
    Imrect *tx;
    Imrect *ty;
    Imrect *imx;
    Imrect *imy;
    Imrect *imxx;
    Imrect *imxy;
    Imrect *imyy;

    im_hessian(im, &imx, &imy, &imxx, &imxy, &imyy);

    tx = imf_minus(imy);
    im_free(imy);
    ty = imx;

    im = imf_matop(tx, ty, imxx, imxy, imxy, imyy, tx, ty);

    im_free(tx);
    im_free(ty);
    im_free(imxx);
    im_free(imxy);
    im_free(imyy);

    return (im);
}

/**
curvature of contour lines
**/

Imrect *imf_curv(Imrect * im, double thresh, double val)
{
    Imrect *num;
    Imrect *den;

    num = imf_ddt(im);
    im = imf_sqrgrad(im);
    den = imf_power(1.5, im);
    im_free(im);
    im = imf_div(num, den, thresh, val);
    im_free(num);
    im_free(den);
    return (im);
}
