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


Imrect *im_arg(Imrect * im)
{
    return (imz_arg(im));
}

Imrect *im_im(Imrect * im)
{
    if (im == NULL)
	return (NULL);
    if (im->vtype == complex_v)
	return (imz_im(im));
    else
	return (im_alloc(im->height, im->width, im->region, im->vtype));
}

Imrect *im_minus(Imrect * im)
{
    switch (im->vtype)
    {
	case complex_v:
	return (imz_minus(im));
    case double_v:
    case float_v:
	return (imf_minus(im));
    default:
	return (imi_minus(im));
    }
}

Imrect *im_mod(Imrect * im)
{
    switch (im->vtype)
    {
	case complex_v:
	return (imz_mod(im));
    case double_v:
    case float_v:
	return (imf_mod(im));
    default:
	return (imi_mod(im));
    }
}

Imrect *im_re(Imrect * im)
{
    if (im == NULL)
	return (NULL);
    if (im->vtype == complex_v)
	return (imz_re(im));
    else
	return (im_copy(im));
}

Imrect *imf_apply(Imrect * im1, double (*func) ( /* ??? */ ), void *data)
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

    im2 = im_alloc(im1->height, im1->width, roi, float_v);
    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im1, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row2[j] = (float)(*func) (row1[j], data);
	im_put_rowf(row2, im2, i, lx, ux);
    }

    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    return (im2);
}

void    imf_apply_inplace(Imrect * im, double (*func) ( /* ??? */ ), void *data)
{
    Imregion *roi;
    float  *row1, *row2;
    int     lx, ux, ly, uy;
    int     i, j;

    if (im == NULL)
	return;

    roi = im->region;
    if (roi == NULL)
	return;
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row2[j] = (float) (*func) (row1[j], data);
	im_put_rowf(row2, im, i, lx, ux);
    }

    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
}

Imrect *imf_dfilter(Imrect * im1)
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

    im2 = im_alloc(im1->height, im1->width, roi, float_v);
    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im1, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    if (row1[j] > 0.0)
		row2[j] = (float) log(row1[j]);
	    else if (row1[j] == 0.0)
		row2[j] = (float) -1.0;
	    else
		row2[j] = (float) -log(-row1[j]);
	im_put_rowf(row2, im2, i, lx, ux);
    }

    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    return (im2);
}

Imrect *imf_mod(Imrect * im1)
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

    im2 = im_alloc(im1->height, im1->width, roi, float_v);
    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im1, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row2[j] = (float) fabs(row1[j]);
	im_put_rowf(row2, im2, i, lx, ux);
    }

    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    return (im2);
}

Imrect *imi_minus(Imrect * im1)
{
    Imrect *im2;
    Imregion *roi;
    int    *row1, *row2;
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

    im2 = im_alloc(im1->height, im1->width, roi, int_v);
    row1 = ivector_alloc(lx, ux);
    row2 = ivector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_row(row1, im1, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row2[j] = -row1[j];
	im_put_row(row2, im2, i, lx, ux);
    }

    ivector_free((void *) row1, lx);
    ivector_free((void *) row2, lx);
    return (im2);
}

Imrect *imi_mod(Imrect * im1)
{
    Imrect *im2;
    Imregion *roi;
    int    *row1, *row2;
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

    im2 = im_alloc(im1->height, im1->width, roi, int_v);
    row1 = ivector_alloc(lx, ux);
    row2 = ivector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_row(row1, im1, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row2[j] = abs(row1[j]);
	im_put_row(row2, im2, i, lx, ux);
    }

    ivector_free((void *) row1, lx);
    ivector_free((void *) row2, lx);
    return (im2);
}

Imrect *imz_minus(Imrect * im1)
{
    Imrect *im2;
    Imregion *roi;
    Complex *row1;
    Complex *row2;
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

    im2 = im_alloc(im1->height, im1->width, roi, complex_v);
    row1 = zvector_alloc(lx, ux);
    row2 = zvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowz(row1, im1, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row2[j] = cmplx_minus(row1[j]);
	im_put_rowz(row2, im2, i, lx, ux);
    }

    zvector_free((void *) row1, lx);
    zvector_free((void *) row2, lx);
    return (im2);
}

Imrect *imz_mod(Imrect * im1)
{
    Imrect *im2;
    Imregion *roi;
    Complex *row1;
    float  *row2;
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

    im2 = im_alloc(im1->height, im1->width, roi, float_v);
    row1 = zvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowz(row1, im1, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row2[j] = (float) cmplx_mod(row1[j]);
	im_put_rowf(row2, im2, i, lx, ux);
    }

    zvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    return (im2);
}

Imrect *imz_arg(Imrect * im1)
{
    Imrect *im2;
    Imregion *roi;
    Complex *row1;
    float  *row2;
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

    im2 = im_alloc(im1->height, im1->width, roi, float_v);
    row1 = zvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowz(row1, im1, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row2[j] = (float) cmplx_arg(row1[j]);
	im_put_rowf(row2, im2, i, lx, ux);
    }

    zvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    return (im2);
}

Imrect *imz_re(Imrect * im1)
{
    Imrect *im2;
    Imregion *roi;
    Complex *row1;
    float  *row2;
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

    im2 = im_alloc(im1->height, im1->width, roi, float_v);
    row1 = zvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowz(row1, im1, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row2[j] = (float) cmplx_re(row1[j]);
	im_put_rowf(row2, im2, i, lx, ux);
    }

    zvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    return (im2);
}

Imrect *imz_im(Imrect * im1)
{
    Imrect *im2;
    Imregion *roi;
    Complex *row1;
    float  *row2;
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

    im2 = im_alloc(im1->height, im1->width, roi, float_v);
    row1 = zvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowz(row1, im1, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row2[j] = (float) cmplx_im(row1[j]);
	im_put_rowf(row2, im2, i, lx, ux);
    }

    zvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    return (im2);
}

Imrect *imz_phase(Imrect * im1)
{
    Imrect *im2;
    Imregion *roi;
    Complex *row1;
    Complex *row2;
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

    im2 = im_alloc(im1->height, im1->width, roi, complex_v);
    row1 = zvector_alloc(lx, ux);
    row2 = zvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowz(row1, im1, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row2[j] = cmplx_phase(row1[j]);
	im_put_rowz(row2, im2, i, lx, ux);
    }

    zvector_free((void *) row1, lx);
    zvector_free((void *) row2, lx);
    return (im2);
}

Imrect *im_phase(Imrect * im)
{
    return (imz_arg(im));
}

Imrect *im_cis(Imrect * im1)
{
    Imrect *im2;
    Imregion *roi;
    float  *row1;
    Complex *row2;
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

    im2 = im_alloc(im1->height, im1->width, roi, complex_v);
    row1 = fvector_alloc(lx, ux);
    row2 = zvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im1, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row2[j] = cmplx_cis(row1[j]);
	im_put_rowz(row2, im2, i, lx, ux);
    }

    fvector_free((void *) row1, lx);
    zvector_free((void *) row2, lx);
    return (im2);
}

Imrect *imi_sqr(Imrect * im1)
{
    Imrect *im2;
    Imregion *roi;
    int    *row1, *row2;
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

    im2 = im_alloc(im1->height, im1->width, roi, int_v);
    row1 = ivector_alloc(lx, ux);
    row2 = ivector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_row(row1, im1, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row2[j] = row1[j] * row1[j];
	im_put_row(row2, im2, i, lx, ux);
    }

    ivector_free((void *) row1, lx);
    ivector_free((void *) row2, lx);
    return (im2);
}

Imrect *imz_sqr(Imrect * im1)
{
    Imrect *im2;
    Imregion *roi;
    Complex *row1;
    Complex *row2;
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

    im2 = im_alloc(im1->height, im1->width, roi, complex_v);
    row1 = zvector_alloc(lx, ux);
    row2 = zvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowz(row1, im1, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row2[j] = cmplx_sqr(row1[j]);
	im_put_rowz(row2, im2, i, lx, ux);
    }

    zvector_free((void *) row1, lx);
    zvector_free((void *) row2, lx);
    return (im2);
}

Imrect *im_sqr(Imrect * im)
{
    switch (im->vtype)
    {
	case complex_v:
	return (imz_sqr(im));
    case double_v:
    case float_v:
	return (imf_sqr(im));
    default:
	return (imi_sqr(im));
    }
}

Imrect *imz_times(double k, Imrect * im1)
{
    Imrect *im2;
    Imregion *roi;
    Complex *row1;
    Complex *row2;
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

    im2 = im_alloc(im1->height, im1->width, roi, complex_v);
    row1 = zvector_alloc(lx, ux);
    row2 = zvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowz(row1, im1, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row2[j] = cmplx_times(k, row1[j]);
	im_put_rowz(row2, im2, i, lx, ux);
    }

    zvector_free((void *) row1, lx);
    zvector_free((void *) row2, lx);
    return (im2);
}

Imrect *im_times(double k, Imrect * im)
{
    switch (im->vtype)
    {
	case complex_v:
	return (imz_times(k, im));
    default:
	return (imf_times(k, im));
    }
}

Imrect *im_conj(Imrect * im1)
{
    Imrect *im2;
    Imregion *roi;
    Complex *row;
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

    im2 = im_alloc(im1->height, im1->width, roi, complex_v);
    row = zvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowz(row, im1, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row[j] = cmplx_conj(row[j]);
	im_put_rowz(row, im2, i, lx, ux);
    }
    zvector_free((void *) row, lx);
    return (im2);
}

Imrect *imf_minus(Imrect * im1)
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

    im2 = im_alloc(im1->height, im1->width, roi, float_v);
    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im1, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row2[j] = -row1[j];
	im_put_rowf(row2, im2, i, lx, ux);
    }

    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    return (im2);
}

Imrect *imf_power(double k, Imrect * im1)
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

    im2 = im_alloc(im1->height, im1->width, roi, float_v);
    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im1, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row2[j] = (float) pow(row1[j], k);
	im_put_rowf(row2, im2, i, lx, ux);
    }

    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    return (im2);
}

Imrect *imf_rm_dc(Imrect * im1)
{
    Imrect *im2;
    Imregion *roi;
    float  *row;
    int     lx, ux, ly, uy;
    int     i, j;
    double  sum;

    if (im1 == NULL)
	return (NULL);

    roi = im1->region;
    if (roi == NULL)
	return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    im2 = im_alloc(im1->height, im1->width, roi, float_v);
    row = fvector_alloc(lx, ux);

    sum = 0.0;
    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row, im1, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    sum += row[j];
    }
    sum /= (ux - lx) * (uy - ly);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row, im1, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row[j] -= (float) sum;
	im_put_rowf(row, im2, i, lx, ux);
    }
    fvector_free((void *) row, lx);
    return (im2);
}

Imrect *imf_sqr(Imrect * im1)
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

    im2 = im_alloc(im1->height, im1->width, roi, float_v);
    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im1, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row2[j] = row1[j] * row1[j];
	im_put_rowf(row2, im2, i, lx, ux);
    }

    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    return (im2);
}

Imrect *imf_times(double k, Imrect * im1)
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

    im2 = im_alloc(im1->height, im1->width, roi, float_v);
    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im1, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row2[j] = (float) (k * row1[j]);
	im_put_rowf(row2, im2, i, lx, ux);
    }

    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    return (im2);
}
