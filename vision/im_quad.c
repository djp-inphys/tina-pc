#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Imrect *im_quad(im)
Imrect *im;
{
    Imrect *im2;
    Imregion roi;
    double pixval;
    int lx,ux,ly,uy,nx,ny;
    int i,j;

    if (im->vtype == complex_v) return(NULL);
    roi = *(Imregion *)im->region;
    lx = roi.lx;
    ux = roi.ux;
    ly = roi.ly;
    uy = roi.uy;
    for(nx = 1; nx <= ux-lx; nx *= 2);
    for(ny = 1; ny <= uy-ly; ny *= 2);
    nx/=2;
    ny/=2;

    ux = roi.ux = lx + nx;
    uy = roi.uy = ly + ny;

    roi.ux+=ux-lx;
    roi.uy+=uy-ly;

    im2 = im_alloc(2*im->height,2*im->width,&roi,im->vtype);

    for(i = ly; i < uy; i++)
    {
        for (j = lx; j < ux;j++)
        {
            IM_PIX_GET(im,i,j,pixval);
            IM_PIX_SET(im2,i,j,pixval);
            IM_PIX_SET(im2,i,roi.ux+roi.lx-j-1,pixval);
            IM_PIX_SET(im2,roi.uy+roi.ly-i-1,j,pixval);
            IM_PIX_SET(im2,roi.uy+roi.ly-i-1,roi.ux+roi.lx-j-1,pixval);
        }
    }
    im_free(im);
    return(im2);
}
