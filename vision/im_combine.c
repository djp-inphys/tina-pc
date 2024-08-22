/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/** combining two images, general case **/

Imrect *im_combine(Imrect * im1, Imrect * im2, void *(*func) (), void *data)
{
    Imrect *im3;
    Imregion *roi;
    int    *row1, *row2, *row3;
    int     lx, ux, ly, uy;
    int     width, height;
    int     i, j;

    if (im1 == NULL || im2 == NULL)
	return (NULL);

    roi = roi_inter(im1->region, im2->region);
    if (roi == NULL)
	return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    width = MIN(im1->width, im2->width);
    height = MIN(im1->height, im2->height);

    im3 = im_alloc(height, width, roi, ptr_v);
    row1 = tvector_alloc(lx, ux, int);
    row2 = tvector_alloc(lx, ux, int);
    row3 = tvector_alloc(lx, ux, int);

    for (i = ly; i < uy; ++i)
    {
	im_get_row(row1, im1, i, lx, ux);
	im_get_row(row2, im2, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row3[j] = (int) (*func) (row1[j], row2[j], data);
	im_put_row(row3, im3, i, lx, ux);
    }

    tvector_free(row1, lx, void *);
    tvector_free(row2, lx, void *);
    tvector_free(row3, lx, void *);
    rfree((void *) roi);
    return (im3);
}

/** combining two floating point images, in place version, and special cases **/

Imrect *imf_combine(Imrect * im1, Imrect * im2, double (*func) ( /* ??? */ ), void *data)
{
    Imrect *im3;
    Imregion *roi;
    float  *row1, *row2, *row3;
    int     lx, ux, ly, uy;
    int     width, height;
    int     i, j;

    if (im1 == NULL || im2 == NULL)
	return (NULL);

    roi = roi_inter(im1->region, im2->region);
    if (roi == NULL)
	return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    width = MIN(im1->width, im2->width);
    height = MIN(im1->height, im2->height);

    im3 = im_alloc(height, width, roi, float_v);
    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);
    row3 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im1, i, lx, ux);
	im_get_rowf(row2, im2, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row3[j] = (float)(*func) (row1[j], row2[j], data);
	im_put_rowf(row3, im3, i, lx, ux);
    }

    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    fvector_free((void *) row3, lx);
    rfree((void *) roi);
    return (im3);
}

void    imf_combine_inplace(Imrect * im1, Imrect * im2, double (*func) ( /* ??? */ ), void *data)
{
    Imregion *roi;
    float  *row1, *row2, *row3;
    int     lx, ux, ly, uy;
    int     i, j;

    if (im1 == NULL || im2 == NULL)
	return;

    roi = roi_inter(im1->region, im2->region);
    rfree((void *) im1->region);
    im1->region = roi;

    if (roi == NULL)
	return;
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);
    row3 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im1, i, lx, ux);
	im_get_rowf(row2, im2, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row3[j] = (float)(*func) (row1[j], row2[j], data);
	im_put_rowf(row3, im1, i, lx, ux);
    }

    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    fvector_free((void *) row3, lx);
    rfree((void *) roi);
}

Imrect *imi_sum(Imrect * im1, Imrect * im2)
{
    Imrect *im3;
    Imregion *roi;
    int    *row1, *row2, *row3;
    int     lx, ux, ly, uy;
    int     width, height;
    int     i, j;

    if (im1 == NULL || im2 == NULL)
	return (NULL);

    roi = roi_inter(im1->region, im2->region);
    if (roi == NULL)
	return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    width = MIN(im1->width, im2->width);
    height = MIN(im1->height, im2->height);

    im3 = im_alloc(height, width, roi, int_v);
    row1 = ivector_alloc(lx, ux);
    row2 = ivector_alloc(lx, ux);
    row3 = ivector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_row(row1, im1, i, lx, ux);
	im_get_row(row2, im2, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row3[j] = row1[j] + row2[j];
	im_put_row(row3, im3, i, lx, ux);
    }

    ivector_free((void *) row1, lx);
    ivector_free((void *) row2, lx);
    ivector_free((void *) row3, lx);
    rfree((void *) roi);
    return (im3);
}

Imrect *imf_sum(Imrect * im1, Imrect * im2)
{
    Imrect *im3;
    Imregion *roi;
    float  *row1, *row2, *row3;
    int     lx, ux, ly, uy;
    int     width, height;
    int     i, j;

    if (im1 == NULL || im2 == NULL)
	return (NULL);

    roi = roi_inter(im1->region, im2->region);
    if (roi == NULL)
	return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    width = MIN(im1->width, im2->width);
    height = MIN(im1->height, im2->height);

    im3 = im_alloc(height, width, roi, float_v);
    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);
    row3 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im1, i, lx, ux);
	im_get_rowf(row2, im2, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row3[j] = row1[j] + row2[j];
	im_put_rowf(row3, im3, i, lx, ux);
    }

    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    fvector_free((void *) row3, lx);
    rfree((void *) roi);
    return (im3);
}

Imrect *imz_sum(Imrect * im1, Imrect * im2)
{
    Imrect *im3;
    Imregion *roi;
    Complex *row1;
    Complex *row2;
    Complex *row3;
    int     lx, ux, ly, uy;
    int     width, height;
    int     i, j;

    if (im1 == NULL || im2 == NULL)
	return (NULL);

    roi = roi_inter(im1->region, im2->region);
    if (roi == NULL)
	return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    width = MIN(im1->width, im2->width);
    height = MIN(im1->height, im2->height);

    im3 = im_alloc(height, width, roi, complex_v);
    row1 = zvector_alloc(lx, ux);
    row2 = zvector_alloc(lx, ux);
    row3 = zvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowz(row1, im1, i, lx, ux);
	im_get_rowz(row2, im2, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row3[j] = cmplx_sum(row1[j], row2[j]);
	im_put_rowz(row3, im3, i, lx, ux);
    }

    zvector_free((void *) row1, lx);
    zvector_free((void *) row2, lx);
    zvector_free((void *) row3, lx);
    rfree((void *) roi);
    return (im3);
}

Imrect *im_sum(Imrect * im1, Imrect * im2)
{
    if (im1 == NULL || im2 == NULL)
	return (NULL);
    switch (im_sup_vtype(im1->vtype, im2->vtype))
    {
    case uchar_v:
    case char_v:
    case int_v:
	return (imi_sum(im1, im2));
    case float_v:
	return (imf_sum(im1, im2));
    case complex_v:
	return (imz_sum(im1, im2));
    default:
	return (NULL);
    }
    return (NULL);
}

Imrect *imi_diff(Imrect * im1, Imrect * im2)
{
    Imrect *im3;
    Imregion *roi;
    int    *row1, *row2, *row3;
    int     lx, ux, ly, uy;
    int     width, height;
    int     i, j;

    if (im1 == NULL || im2 == NULL)
	return (NULL);

    roi = roi_inter(im1->region, im2->region);
    if (roi == NULL)
	return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    width = MIN(im1->width, im2->width);
    height = MIN(im1->height, im2->height);

    im3 = im_alloc(height, width, roi, int_v);
    row1 = ivector_alloc(lx, ux);
    row2 = ivector_alloc(lx, ux);
    row3 = ivector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_row(row1, im1, i, lx, ux);
	im_get_row(row2, im2, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row3[j] = row1[j] - row2[j];
	im_put_row(row3, im3, i, lx, ux);
    }

    ivector_free((void *) row1, lx);
    ivector_free((void *) row2, lx);
    ivector_free((void *) row3, lx);
    rfree((void *) roi);
    return (im3);
}

Imrect *imf_diff(Imrect * im1, Imrect * im2)
{
    Imrect *im3;
    Imregion *roi;
    float  *row1, *row2, *row3;
    int     lx, ux, ly, uy;
    int     width, height;
    int     i, j;

    if (im1 == NULL || im2 == NULL)
	return (NULL);

    roi = roi_inter(im1->region, im2->region);
    if (roi == NULL)
	return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    width = MIN(im1->width, im2->width);
    height = MIN(im1->height, im2->height);

    im3 = im_alloc(height, width, roi, float_v);
    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);
    row3 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im1, i, lx, ux);
	im_get_rowf(row2, im2, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row3[j] = row1[j] - row2[j];
	im_put_rowf(row3, im3, i, lx, ux);
    }

    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    fvector_free((void *) row3, lx);
    rfree((void *) roi);
    return (im3);
}

Imrect *imz_diff(Imrect * im1, Imrect * im2)
{
    Imrect *im3;
    Imregion *roi;
    Complex *row1;
    Complex *row2;
    Complex *row3;
    int     lx, ux, ly, uy;
    int     width, height;
    int     i, j;

    if (im1 == NULL || im2 == NULL)
	return (NULL);

    roi = roi_inter(im1->region, im2->region);
    if (roi == NULL)
	return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    width = MIN(im1->width, im2->width);
    height = MIN(im1->height, im2->height);

    im3 = im_alloc(height, width, roi, complex_v);
    row1 = zvector_alloc(lx, ux);
    row2 = zvector_alloc(lx, ux);
    row3 = zvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowz(row1, im1, i, lx, ux);
	im_get_rowz(row2, im2, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row3[j] = cmplx_diff(row1[j], row2[j]);
	im_put_rowz(row3, im3, i, lx, ux);
    }

    zvector_free((void *) row1, lx);
    zvector_free((void *) row2, lx);
    zvector_free((void *) row3, lx);
    rfree((void *) roi);
    return (im3);
}

Imrect *im_diff(Imrect * im1, Imrect * im2)
{
    if (im1 == NULL || im2 == NULL)
	return (NULL);
    switch (im_sup_vtype(im1->vtype, im2->vtype))
    {
    case uchar_v:
    case char_v:
    case int_v:
	return(imi_diff(im1, im2));
    case float_v:
	return(imf_diff(im1, im2));
    case complex_v:
	return(imz_diff(im1, im2));
    default:
	return (NULL);
    }
    return (NULL);
}

Imrect *imf_wsum(double a, double b, Imrect * im1, Imrect * im2)
{
    Imrect *im3;
    Imregion *roi;
    float  *row1, *row2, *row3;
    int     lx, ux, ly, uy;
    int     width, height;
    int     i, j;

    if (im1 == NULL || im2 == NULL)
	return (NULL);

    roi = roi_inter(im1->region, im2->region);
    if (roi == NULL)
	return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    width = MIN(im1->width, im2->width);
    height = MIN(im1->height, im2->height);

    im3 = im_alloc(height, width, roi, float_v);
    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);
    row3 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im1, i, lx, ux);
	im_get_rowf(row2, im2, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row3[j] = (float) (a * row1[j] + b * row2[j]);
	im_put_rowf(row3, im3, i, lx, ux);
    }

    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    fvector_free((void *) row3, lx);
    rfree((void *) roi);
    return (im3);
}

Imrect *imf_sumsq(Imrect * im1, Imrect * im2)
{
    Imrect *im3;
    Imregion *roi;
    float  *row1, *row2, *row3;
    int     lx, ux, ly, uy;
    int     width, height;
    int     i, j;

    if (im1 == NULL || im2 == NULL)
	return (NULL);

    roi = roi_inter(im1->region, im2->region);
    if (roi == NULL)
	return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    width = MIN(im1->width, im2->width);
    height = MIN(im1->height, im2->height);

    im3 = im_alloc(height, width, roi, float_v);
    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);
    row3 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im1, i, lx, ux);
	im_get_rowf(row2, im2, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row3[j] = row1[j] * row1[j] + row2[j] * row2[j];
	im_put_rowf(row3, im3, i, lx, ux);
    }

    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    fvector_free((void *) row3, lx);
    rfree((void *) roi);
    return (im3);
}

Imrect *imi_prod(Imrect * im1, Imrect * im2)
{
    Imrect *im3;
    Imregion *roi;
    int    *row1, *row2, *row3;
    int     lx, ux, ly, uy;
    int     width, height;
    int     i, j;

    if (im1 == NULL || im2 == NULL)
	return (NULL);

    roi = roi_inter(im1->region, im2->region);
    if (roi == NULL)
	return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    width = MIN(im1->width, im2->width);
    height = MIN(im1->height, im2->height);

    im3 = im_alloc(height, width, roi, int_v);
    row1 = ivector_alloc(lx, ux);
    row2 = ivector_alloc(lx, ux);
    row3 = ivector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_row(row1, im1, i, lx, ux);
	im_get_row(row2, im2, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row3[j] = row1[j] * row2[j];
	im_put_row(row3, im3, i, lx, ux);
    }

    ivector_free((void *) row1, lx);
    ivector_free((void *) row2, lx);
    ivector_free((void *) row3, lx);
    rfree((void *) roi);
    return (im3);
}

Imrect *imf_prod(Imrect * im1, Imrect * im2)
{
    Imrect *im3;
    Imregion *roi;
    float  *row1, *row2, *row3;
    int     lx, ux, ly, uy;
    int     width, height;
    int     i, j;

    if (im1 == NULL || im2 == NULL)
	return (NULL);

    roi = roi_inter(im1->region, im2->region);
    if (roi == NULL)
	return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    width = MIN(im1->width, im2->width);
    height = MIN(im1->height, im2->height);

    im3 = im_alloc(height, width, roi, float_v);
    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);
    row3 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im1, i, lx, ux);
	im_get_rowf(row2, im2, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row3[j] = row1[j] * row2[j];
	im_put_rowf(row3, im3, i, lx, ux);
    }

    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    fvector_free((void *) row3, lx);
    rfree((void *) roi);
    return (im3);
}

Imrect *imz_prod(Imrect * im1, Imrect * im2)
{
    Imrect *im3;
    Imregion *roi;
    Complex *row1;
    Complex *row2;
    Complex *row3;
    int     lx, ux, ly, uy;
    int     width, height;
    int     i, j;

    if (im1 == NULL || im2 == NULL)
	return (NULL);

    roi = roi_inter(im1->region, im2->region);
    if (roi == NULL)
	return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    width = MIN(im1->width, im2->width);
    height = MIN(im1->height, im2->height);

    im3 = im_alloc(height, width, roi, complex_v);
    row1 = zvector_alloc(lx, ux);
    row2 = zvector_alloc(lx, ux);
    row3 = zvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowz(row1, im1, i, lx, ux);
	im_get_rowz(row2, im2, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row3[j] = cmplx_prod(row1[j], row2[j]);
	im_put_rowz(row3, im3, i, lx, ux);
    }

    zvector_free((void *) row1, lx);
    zvector_free((void *) row2, lx);
    zvector_free((void *) row3, lx);
    rfree((void *) roi);
    return (im3);
}

Imrect *im_prod(Imrect * im1, Imrect * im2)
{
    if (im1 == NULL || im2 == NULL)
	return (NULL);
    switch (im_sup_vtype(im1->vtype, im2->vtype))
    {
    case uchar_v:
    case char_v:
    case int_v:
	return(imi_prod(im1, im2));
    case float_v:
	return(imf_prod(im1, im2));
    case complex_v:
	return(imz_prod(im1, im2));
    default:
	return (NULL);
    }
    return (NULL);
}

Imrect *imf_div(Imrect * im1, Imrect * im2, double thresh, double val)
{
    Imrect *im3;
    Imregion *roi;
    float  *row1, *row2, *row3;
    int     lx, ux, ly, uy;
    int     width, height;
    int     i, j;

    if (im1 == NULL || im2 == NULL)
	return (NULL);

    roi = roi_inter(im1->region, im2->region);
    if (roi == NULL)
	return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    width = MIN(im1->width, im2->width);
    height = MIN(im1->height, im2->height);

    im3 = im_alloc(height, width, roi, float_v);
    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);
    row3 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im1, i, lx, ux);
	im_get_rowf(row2, im2, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    if (row2[j] * row2[j] <= thresh*thresh)
		row3[j] = (float) (2.0*row1[j]/(row2[j]+val));
	    else
		row3[j] = row1[j] / row2[j];
	im_put_rowf(row3, im3, i, lx, ux);
    }

    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    fvector_free((void *) row3, lx);
    rfree((void *) roi);
    return (im3);
}

Imrect *imz_div(Imrect * im1, Imrect * im2, double thresh, Complex val)
{
    Imrect *im3;
    Imregion *roi;
    Complex *row1;
    Complex *row2;
    Complex *row3;
    int     lx, ux, ly, uy;
    int     width, height;
    int     i, j;

    if (im1 == NULL || im2 == NULL)
	return (NULL);

    roi = roi_inter(im1->region, im2->region);
    if (roi == NULL)
	return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    width = MIN(im1->width, im2->width);
    height = MIN(im1->height, im2->height);

    im3 = im_alloc(height, width, roi, complex_v);
    row1 = zvector_alloc(lx, ux);
    row2 = zvector_alloc(lx, ux);
    row3 = zvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowz(row1, im1, i, lx, ux);
	im_get_rowz(row2, im2, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    if (cmplx_sqrmod(row2[j]) <= thresh*thresh)
                if (row2[j].x>0.0)
                   row3[j] = cmplx_div(row1[j],
                             cmplx_times(0.5,cmplx_sum(val,row2[j])));
                else
                   row3[j] = cmplx_div(row1[j],
                             cmplx_times(0.5,cmplx_diff(row2[j],val)));
	    else
		row3[j] = cmplx_div(row1[j], row2[j]);
	im_put_rowz(row3, im3, i, lx, ux);
    }

    zvector_free((void *) row1, lx);
    zvector_free((void *) row2, lx);
    zvector_free((void *) row3, lx);
    rfree((void *) roi);
    return (im3);
}

Imrect *im_div(Imrect * im1, Imrect * im2, double thresh, double val)
{
    if (im1 == NULL || im2 == NULL)
	return (NULL);
    switch (im_sup_vtype(im1->vtype, im2->vtype))
    {
    case uchar_v:
    case char_v:
    case int_v:
    case float_v:
	return(imf_div(im1, im2, thresh, val));
    case complex_v:
	return(imz_div(im1, im2, thresh, cmplx(val, 0.0)));
    default:
	return (NULL);
    }
    return (NULL);
}
