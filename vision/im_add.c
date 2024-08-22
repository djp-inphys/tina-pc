#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

Imrect *imc_add(int k,Imrect *im)
{
    Imrect *im2;
    Imregion *roi;
    int *row1, *row2;
    int lx, ux, ly, uy;
    int width, height;
    int i, j;

    if (im == NULL)
        return (NULL);

    roi = im->region;
    if (roi == NULL)
        return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    width = im->width;
    height = im->height;

    im2 = im_alloc(height, width, roi, char_v);
    row1 = ivector_alloc(lx, ux);
    row2 = ivector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
        im_get_row(row1, im, i, lx, ux);
        for (j = lx; j < ux; ++j)
            row2[j] = row1[j]+k;
        im_put_row(row2, im2, i, lx, ux);
    }

    ivector_free(row1, lx);
    ivector_free(row2, lx);
    return (im2);
}

Imrect *imi_add(int k,Imrect *im)
{
    Imrect *im2;
    Imregion *roi;
    int *row1, *row2;
    int lx, ux, ly, uy;
    int width, height;
    int i, j;

    if (im == NULL)
        return (NULL);

    roi = im->region;
    if (roi == NULL)
        return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    width = im->width;
    height = im->height;

    im2 = im_alloc(height, width, roi, int_v);
    row1 = ivector_alloc(lx, ux);
    row2 = ivector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
        im_get_row(row1, im, i, lx, ux);
        for (j = lx; j < ux; ++j)
            row2[j] = row1[j]+k;
        im_put_row(row2, im2, i, lx, ux);
    }

    ivector_free(row1, lx);
    ivector_free(row2, lx);
    return (im2);
}

Imrect *imf_add(double k,Imrect *im)
{
    Imrect *im2;
    Imregion *roi;
    float *row1, *row2;
    int lx, ux, ly, uy;
    int width, height;
    int i, j;

    if (im == NULL)
        return (NULL);

    roi = im->region;
    if (roi == NULL)
        return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    width = im->width;
    height = im->height;

    im2 = im_alloc(height, width, roi, float_v);
    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
        im_get_rowf(row1, im, i, lx, ux);
        for (j = lx; j < ux; ++j)
            row2[j] = (float)(row1[j]+k);
        im_put_rowf(row2, im2, i, lx, ux);
    }

    fvector_free(row1, lx);
    fvector_free(row2, lx);
    return (im2);
}

Imrect *imz_add(Complex k,Imrect *im)
{
    Imrect *im2;
    Imregion *roi;
    Complex *row1, *row2;
    int lx, ux, ly, uy;
    int width, height;
    int i, j;

    if (im == NULL)
        return (NULL);

    roi = im->region;
    if (roi == NULL)
        return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    width = im->width;
    height = im->height;

    im2 = im_alloc(height, width, roi, complex_v);
    row1 = zvector_alloc(lx, ux);
    row2 = zvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
        im_get_rowz(row1, im, i, lx, ux);
        for (j = lx; j < ux; ++j)
        {
            row2[j].x = row1[j].x+k.x;
            row2[j].y = row1[j].y+k.y;
        }
        im_put_rowz(row2, im2, i, lx, ux);
    }

    zvector_free(row1, lx);
    zvector_free(row2, lx);
    return (im2);
}

Imrect *im_add(k,im)
Imrect *im;
double k;
{
    if(im == NULL )
        return(NULL);
    switch(im->vtype)
    {
        case char_v:
            return(imc_add((int)k,im));
        case int_v:
            return(imi_add((int)k,im));
        case float_v:
            return(imf_add(k,im));
        case complex_v: /* im sure this should be cmplx(k,k) NAT */
            return(imz_add(cmplx(k,0.0),im));
    }
}
