#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

Imrect *im_shading(Imrect *im,double slant,double tilt,double scale)
/* shade an image */
{
    Imrect *fim,*hgim,*vgim,*im_re();
    Imrect *imf_grad_h(),*imf_grad_v();
    Imregion *roi;
    float *row1,*row2,*row3;
    int i,j;
    int lx,ux,ly,uy;
    double ctss,stss,cs;

    fim = im_re(im);
    if (fim == NULL)
        return (NULL);

    roi = fim->region;
    if (roi == NULL)
        return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    hgim =  imf_grad_h(fim);
    vgim =  imf_grad_v(fim);
    ctss = cos(tilt)*sin(slant);
    stss = sin(tilt)*sin(slant);
    cs = cos(slant);

    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);
    row3 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
        im_get_rowf(row1, hgim, i, lx, ux);
        im_get_rowf(row2, vgim, i, lx, ux);
        for (j = lx; j < ux; ++j)
        {
            row3[j] = (float) (scale*(row1[j]*ctss + row2[j]*stss + cs)
                    / sqrt(row1[j]*row1[j] + row2[j]*row2[j] + 1.0));

        }
        im_put_rowf(row3, fim, i, lx, ux);
    }

    fvector_free(row1, lx);
    fvector_free(row2, lx);
    fvector_free(row3, lx);
    im_free(hgim);
    im_free(vgim);
    return (fim);
}

Imrect *shade_conv(double slant,double tilt,Imregion *roi)
/* compute effective convolution kernal in the fourier domain */
{
    Imrect *im;
    Complex *row;
    Complex cgrad;
    double amplitude,phase;
    int lx, ux, ly, uy;
    double rangex,rangey;
    int i, j;

    if (roi == NULL)
        return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;
    rangex = roi->ux-roi->lx;
    rangey = roi->uy-roi->ly;

    im = im_alloc(uy-ly, ux-lx, roi, complex_v);
    row = zvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
        for (j = lx; j < ux; ++j)
        {
            phase = -PIBY2;
            amplitude = sin(slant)*(sin(TWOPI*(j-lx)/rangex)*cos(tilt) +
                                    sin(TWOPI*(i-ly)/rangey)*sin(tilt));
/*
            cgrad.y = amplitude * sin(phase);
            cgrad.x = amplitude * cos(phase);
*/
            cgrad.y = -amplitude;
            cgrad.x = 0.0;
            row[j] = cgrad;
        }
        im_put_rowz(row, im, i, lx, ux);
    }

    zvector_free(row, lx);
    return (im);
}

Imrect *imz_fshade(Imrect *im1,double slant,double tilt)
/* compute the effective shading convolution for shallow
 surfaces in the fourier domain */
{
    Imrect *im2;
    Imregion *roi;
    Complex *row1;
    Complex cgrad;
    Complex *row2;
    double amplitude,phase;
    int lx, ux, ly, uy;
    double rangex,rangey;
    int i, j;

    if (im1 == NULL||im1->vtype!=complex_v)
        return (NULL);

    roi = im1->region;
    if (roi == NULL)
        return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;
    rangex = roi->ux-roi->lx;
    rangey = roi->uy-roi->ly;

    im2 = im_alloc(im1->height, im1->width, roi, complex_v);
    row1 = zvector_alloc(lx, ux);
    row2 = zvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
        im_get_rowz(row1, im1, i, lx, ux);
        for (j = lx; j < ux; ++j)
        {
            cgrad.x = (row1[j]).x;
            cgrad.y = (row1[j]).y;
            if (cgrad.x*cgrad.x + cgrad.y*cgrad.y==0.0)
                amplitude = 0.0;
            else
                amplitude = sqrt(cgrad.x*cgrad.x + cgrad.y*cgrad.y);

            if (cgrad.x!=0.0)
                phase = atan2(cgrad.y,cgrad.x);
            else if (cgrad.y > 0.0 ) phase = PIBY2; 
            else phase = -PIBY2;
            phase -= PIBY2;
            amplitude *= sin(slant)*(sin(TWOPI*(j-lx)/rangex)*cos(tilt) +
                                     sin(TWOPI*(i-ly)/rangey)*sin(tilt));
            cgrad.y = amplitude * sin(phase);
            cgrad.x = amplitude * cos(phase);
            row2[j] = cgrad;
        }
        im_put_rowz(row2, im2, i, lx, ux);
    }

    zvector_free(row1, lx);
    zvector_free(row2, lx);
    return (im2);
}

Imrect *imz_fshape(Imrect *im1,double slant,double tilt,double limit)
{
    Imrect *im2;
    Imregion *roi;
    Complex *row1;
    Complex cgrad;
    Complex *row2;
    double amplitude,phase,fac;
    int lx, ux, ly, uy;
    double rangex,rangey;
    double ss,ct,st;
    int i, j;

    if (im1 == NULL||im1->vtype!=complex_v)
        return (NULL);

    roi = im1->region;
    if (roi == NULL)
        return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;
    rangex = roi->ux-roi->lx;
    rangey = roi->uy-roi->ly;

    im2 = im_alloc(im1->height, im1->width, roi, complex_v);
    row1 = zvector_alloc(lx, ux);
    row2 = zvector_alloc(lx, ux);
    ss = sin(slant);
    ct = cos(tilt);
    st = sin(tilt);

    for (i = ly; i < uy; ++i)
    {
        im_get_rowz(row1, im1, i, lx, ux);
        for (j = lx; j < ux; ++j)
        {
            cgrad.x = (row1[j]).x;
            cgrad.y = (row1[j]).y;
            if (cgrad.x*cgrad.x + cgrad.y*cgrad.y==0.0)
                amplitude = 0.0;
            else
                amplitude = sqrt(cgrad.x*cgrad.x + cgrad.y*cgrad.y);

            if (cgrad.x!=0.0)
                phase = atan2(cgrad.y,cgrad.x);
            else if (cgrad.y > 0.0 ) phase = PIBY2; 
            else phase = -PIBY2;

            phase += PIBY2;
            fac = ss*(sin(TWOPI*(j-lx)/rangex)*ct +
                      sin(TWOPI*(i-ly)/rangey)*st);
            if (fac>0.0)
            {
               if (fac<limit*ss) fac = limit*ss;
            }
            else 
            {
               if (fac>-limit*ss) fac = -limit*ss;
            }
            if (!(fabs(fac)>0.00001)) 
                 format("bollocks\n");

            amplitude /= fac;
            cgrad.y = amplitude * sin(phase);
            cgrad.x = amplitude * cos(phase);
            row2[j] = cgrad;
        }
        im_put_rowz(row2, im2, i, lx, ux);
    }

    zvector_free(row1, lx);
    zvector_free(row2, lx);
    return (im2);
}

Imrect *imz_fxgrad(Imrect *im1)
/* compute x gradient of image in the fourier domain */
{
    Imrect *im2;
    Imregion *roi;
    Complex *row1;
    Complex cgrad;
    Complex *row2;
    double amplitude,phase;
    int lx, ux, ly, uy;
    double range;
    int i, j;

    if (im1 == NULL||im1->vtype!=complex_v)
        return (NULL);

    roi = im1->region;
    if (roi == NULL)
        return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;
    range = roi->ux-roi->lx;

    im2 = im_alloc(im1->height, im1->width, roi, complex_v);
    row1 = zvector_alloc(lx, ux);
    row2 = zvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
        im_get_rowz(row1, im1, i, lx, ux);
        for (j = lx; j < ux; ++j)
        {
            cgrad.x = (row1[j]).x;
            cgrad.y = (row1[j]).y;
            if (cgrad.x*cgrad.x + cgrad.y*cgrad.y==0.0)
                amplitude = 0.0;
            else
                amplitude = sqrt(cgrad.x*cgrad.x + cgrad.y*cgrad.y);

            phase = atan2(cgrad.y,cgrad.x);
            phase -= PIBY2;
            amplitude *= sin(TWOPI*(j-lx)/range);
            cgrad.y = amplitude * sin(phase);
            cgrad.x = amplitude * cos(phase);
            row2[j] = cgrad;
        }
        im_put_rowz(row2, im2, i, lx, ux);
    }

    zvector_free(row1, lx);
    zvector_free(row2, lx);
    return (im2);
}

Imrect *imz_fygrad(Imrect *im1)
/* compute y gradient of image in the fourier domain */
{
    Imrect *im2;
    Imregion *roi;
    Complex *row1;
    Complex cgrad;
    Complex *row2;
    double amplitude,phase;
    int lx, ux, ly, uy;
    double range;
    int i, j;

    if (im1 == NULL||im1->vtype!=complex_v)
        return (NULL);

    roi = im1->region;
    if (roi == NULL)
        return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;
    range = roi->uy-roi->ly;

    im2 = im_alloc(im1->height, im1->width, roi, complex_v);
    row1 = zvector_alloc(lx, ux);
    row2 = zvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
        im_get_rowz(row1, im1, i, lx, ux);
        for (j = lx; j < ux; ++j)
        {
            cgrad.x = (row1[j]).x;
            cgrad.y = (row1[j]).y;
            if (cgrad.x*cgrad.x + cgrad.y*cgrad.y==0.0)
                amplitude = 0.0;
            else
                amplitude = sqrt(cgrad.x*cgrad.x + cgrad.y*cgrad.y);
 
            phase = atan2(cgrad.y,cgrad.x);
            phase -= PIBY2;
            amplitude *= sin(TWOPI*(i-ly)/range);
            cgrad.y = amplitude * sin(phase);
            cgrad.x = amplitude * cos(phase);
            row2[j] = cgrad;
        }
        im_put_rowz(row2, im2, i, lx, ux);
    }

    zvector_free(row1, lx);
    zvector_free(row2, lx);
    return (im2);
}

