#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/* Replaces each pixel of the image with it`s rank in a window of
   size 2*size +1 with a rank accuracy given by noise.
*/
Imrect * imi_rank(Imrect *im, int size, double noise)
{
        int lx,ux,ly,uy,i,j;
        int m,n,icen,jcen;
        int s,t;
        Imrect *fim;
        int *row;
        double cenpix;
        double level;

        if(im==NULL)
           return(NULL);
        lx = im->region->lx;
        ux = im->region->ux;
        ly = im->region->ly;
        uy = im->region->uy;

        fim=im_alloc(im->height, im->width,im->region,int_v);
        for(i=ly; i<uy; i++){
           icen = i;
           if(i<ly+size) icen = ly+size;
           if(i>uy-size-1) icen = uy-size-1;
           for(j=lx; j<ux; j++){
              jcen = j;
              if(j<lx+size) jcen = lx+size;
              if(j>ux-size-1) jcen = ux-size-1;
              IM_PIX_GET(im, i, j, cenpix);
              level = 0.0;
              for(m=icen-size,s=-size; m<icen+size+1; m++,s++)
              {
                 row = IM_ROW(im,m);
                 for(n=jcen-size,t=-size; n<jcen+size+1; n++,t++)
                 {
                     if (row[n]<(cenpix+noise))
                     {
                     /* soft ranking scheme for smoothly varying grey levels */
                        if (fabs((double)(row[n]-cenpix))<noise)
                            level += 0.5*(1.0-(row[n]-cenpix)/noise);
                        else
                            level += 1.0;
                     }
                 }
              }
              IM_PIX_SET(fim, i, j, level);
           }
        }
        return(fim);
}

Imrect * imf_rank(Imrect *im, int size, double noise)
{
        int lx,ux,ly,uy,i,j;
        int m,n,icen,jcen;
        int s,t;
        Imrect *fim;
        float *row;
        double cenpix;
        double level;
        static float **weight=NULL;

        if(im==NULL)
           return(NULL);
/*  try to introduce a sensible radially symetric filter
    radial gaussian weighting with sigma = size/2.0 
    significantly increases computation and required region size
    but does not improve final result. NAT 8/6/95
        if (weight == NULL)
        {
            weight = farray_alloc(-size,-size,size+1,size+1);
            for (i=-size;i<size+1;i++)
            {
                for (j=-size;j<size+1;j++)
                {
                     weight[i][j] = exp(-2.0*(i*i + j*j)/(double)(size*size));
                }
            }
        }
*/

        lx = im->region->lx;
        ux = im->region->ux;
        ly = im->region->ly;
        uy = im->region->uy;

        fim=im_alloc(im->height, im->width,im->region,float_v);
        for(i=ly; i<uy; i++){
           icen = i;
           if(i<ly+size) icen = ly+size; 
           if(i>uy-size-1) icen = uy-size-1;
           for(j=lx; j<ux; j++){
              jcen = j;
              if(j<lx+size) jcen = lx+size; 
              if(j>ux-size-1) jcen = ux-size-1;
              IM_PIX_GET(im, i, j, cenpix);
              level = 0.0;
              for(m=icen-size,s=-size; m<icen+size+1; m++,s++)
              {
                 row = IM_ROW(im,m);    
                 for(n=jcen-size,t=-size; n<jcen+size+1; n++,t++)
                 {
                     if (row[n]<(cenpix+noise))
                     {
                     /* soft ranking scheme for smoothly varying grey levels */
                        if (fabs(row[n]-cenpix)<noise)
                            level += 0.5*(1.0-(row[n]-cenpix)/noise);
                        else
                            level += 1.0;
                     }
                 }
              }
              IM_PIX_SET(fim, i, j, level);
           }
        }
        return(fim);
}

Imrect *im_rank(Imrect *im, int range, double noise)
{
    if(im == NULL)
        return(NULL);
    switch(im->vtype)
    {
        case uchar_v:
        case char_v:
        case int_v:
            return(imi_rank(im, range, noise));
        case double_v:
        case float_v:
            return(imf_rank(im, range, noise));
        case complex_v:
            return(NULL);
        default:
            return(NULL);
    }
}
