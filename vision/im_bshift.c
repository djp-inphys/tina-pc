#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

Imrect *im_bshift(Imrect *im, int y , int x)
{
    Imrect *im2;
    Imregion *roi;
    double pixval;
    int lx,ux,ly,uy;
    int i,j,newx,newy;

    roi = im->region;
    im2 = im_alloc(im->height,im->width,roi,im->vtype);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    for(i = ly; i < uy; i++)
    {
        for (j = lx; j < ux;j++)
        {
            newx = j+x;
            if(newx>=ux) newx-=(ux-lx);
            if(newx<lx) newx+=(ux-lx);
            newy = i+y;
            if(newy>=uy) newy-=(uy-ly);
            if(newy<ly) newy+=(uy-ly);

            IM_PIX_GET(im,i,j,pixval);
            IM_PIX_SET(im2,newy,newx,pixval);
        }
    }
    return(im2);
}
