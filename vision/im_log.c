#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Imrect *imf_log(Imrect * im1)
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
            if (row1[j] >= 1.0)
                row2[j] = (float)log(row1[j]);
            else if (fabs(row1[j]) < 1.0)
                row2[j] = (float)0.0;
            else
                row2[j] = (float)-log(-row1[j]);
        im_put_rowf(row2, im2, i, lx, ux);
    }

    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    return (im2);
}

Imrect *imz_log(Imrect * im1)
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
            row2[j] = cmplx_log(row1[j]);
        im_put_rowz(row2, im2, i, lx, ux);
    }

    zvector_free((void *) row1, lx);
    zvector_free((void *) row2, lx);
    return (im2);
}

Imrect *im_log(Imrect * im)
{
    switch (im->vtype)
    {
        case complex_v:
        return (imz_log(im));
    default:
        return (imf_log(im));
    }
}

Imrect *imf_exp(Imrect * im1)
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
                row2[j] = (float)exp(row1[j]);
            else
                row2[j] = (float)-exp(-row1[j]);
        im_put_rowf(row2, im2, i, lx, ux);
    }

    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    return (im2);
}

Imrect *imz_exp(Imrect * im1)
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
            row2[j] = cmplx_exp(row1[j]);
        im_put_rowz(row2, im2, i, lx, ux);
    }

    zvector_free((void *) row1, lx);
    zvector_free((void *) row2, lx);
    return (im2);
}

Imrect *im_exp(Imrect * im)
{
    switch (im->vtype)
    {
        case complex_v:
        return (imz_exp(im));
    default:
        return (imf_exp(im));
    }
}
