#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Imrect *imz_cmplx(Imrect * im1, Imrect * im2)
{
    Imrect *im3;
    Imregion *roi;
    float *row1;
    float *row2;
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
    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);
    row3 = zvector_alloc(lx, ux);
 
    for (i = ly; i < uy; ++i)
    {
        im_get_rowf(row1, im1, i, lx, ux);
        im_get_rowf(row2, im2, i, lx, ux);
        for (j = lx; j < ux; ++j)
            row3[j] = cmplx((double)row1[j], (double)row2[j]);
        im_put_rowz(row3, im3, i, lx, ux);
    }
 
    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    zvector_free((void *) row3, lx);
    rfree((void *) roi);
    return (im3);
}

