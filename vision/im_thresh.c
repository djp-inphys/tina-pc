#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Imrect *imi_thresh(double k, Imrect *im1)
{
    Imrect *im2;
    Imregion *roi;
    int *row1, *row2;
    int lx, ux, ly, uy;
    int i, j;

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
            if(row1[j] < k)
                row2[j] = (int)0.0;
            else
                row2[j] = row1[j];
        im_put_row(row2, im2, i, lx, ux);
    }

    ivector_free(row1, lx);
    ivector_free(row2, lx);
    return (im2);
}

Imrect *imi_bthresh(double k, Imrect *im1)
{
    Imrect *im2;
    Imregion *roi;
    int *row1, *row2;
    int lx, ux, ly, uy;
    int i, j;
 
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
            if(row1[j] < k)
                row2[j] = (int)0.0;
            else
                row2[j] = (int)1.0;
        im_put_row(row2, im2, i, lx, ux);
    }
 
    ivector_free(row1, lx);
    ivector_free(row2, lx);
    return (im2);
}

Imrect *imf_thresh(double k, Imrect *im1)
{
    Imrect *im2;
    Imregion *roi;
    float *row1, *row2;
    int lx, ux, ly, uy;
    int i, j;

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
            if(row1[j] < k)
                row2[j] = (float)0.0;
            else
                row2[j] = row1[j];
        im_put_rowf(row2, im2, i, lx, ux);
    }

    fvector_free(row1, lx);
    fvector_free(row2, lx);
    return (im2);
}

Imrect *imf_bthresh(double k, Imrect *im1)
{
    Imrect *im2;
    Imregion *roi;
    float *row1, *row2;
    int lx, ux, ly, uy;
    int i, j;
 
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
            if(row1[j] < k)
                row2[j] = (float)0.0;
            else
                row2[j] = (float)1.0;
        im_put_rowf(row2, im2, i, lx, ux);
    }
 
    fvector_free(row1, lx);
    fvector_free(row2, lx);
    return (im2);
}

Imrect *imz_thresh(double k, Imrect *im1)
{
    Imrect *im2;
    Imregion *roi;
    Complex *row1, *row2;
    int lx, ux, ly, uy;
    int i, j;
 
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
    row2 = zvector_alloc(lx, ux);
 
    for (i = ly; i < uy; ++i)
    {
        im_get_rowz(row1, im1, i, lx, ux);
        for (j = lx; j < ux; ++j)
            if(row1[j].x < k)
            {
                row2[j].x = 0.0;
                row2[j].y = 0.0;
            }
            else
            {
                row2[j].x = row1[j].x;
                row2[j].y = row1[j].y;
            }
        im_put_rowz(row2, im2, i, lx, ux);
    }
 
    zvector_free(row1, lx);
    zvector_free(row2, lx);
    return (im2);
}

Imrect *imz_bthresh(double k, Imrect *im1)
{
    Imrect *im2;
    Imregion *roi;
    Complex *row1, *row2;
    int lx, ux, ly, uy;
    int i, j;

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
    row2 = zvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
        im_get_rowz(row1, im1, i, lx, ux);
        for (j = lx; j < ux; ++j)
            if(row1[j].x < k)
            {
                row2[j].x = 0.0;
                row2[j].y = 0.0;
            }
            else
            {
                row2[j].x = 1.0;
                row2[j].y = 0.0;
            }
        im_put_rowz(row2, im2, i, lx, ux);
    }

    zvector_free(row1, lx);
    zvector_free(row2, lx);
    return (im2);
}

Imrect *im_thresh(double k,Imrect *im)
{
    if(im == NULL )
        return(NULL);
    switch(im->vtype)
    {
        case uchar_v:
        case char_v:
        case int_v:
            return(imi_thresh(k,im));
        case float_v:
            return(imf_thresh(k,im));
        case complex_v:
            return(imz_thresh(k,im));
        default:
            return(NULL);
    }
}

Imrect *im_bthresh(double k,Imrect *im)
{
    if(im == NULL )
        return(NULL);
    switch(im->vtype)
    {
        case uchar_v:
        case char_v:
        case int_v:
            return(imi_bthresh(k,im));
        case float_v:
            return(imf_bthresh(k,im));
        case complex_v:
            return(imz_bthresh(k,im));
        default:
            return(NULL);
    }
}
