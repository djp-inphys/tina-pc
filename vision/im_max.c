#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

float       array_max(float **in, int i, int j, int num, float thresh)
{
        int        nmax=0;
        float     *row, *above, *below, pix;

        if (in==NULL) return(0.0);

        row   = in[i];
        above = in[i-1];
        below = in[i+1];

        if ((pix = fabs(row[j])) > thresh)
        {
                if      (pix < fabs(above[j-1]) && ++nmax > num) ;
                else if (pix < fabs(above[j])   && ++nmax > num) ;
                else if (pix < fabs(above[j+1]) && ++nmax > num) ;
                else if (pix < fabs(row  [j-1]) && ++nmax > num) ;
                else if (pix < fabs(row  [j+1]) && ++nmax > num) ;
                else if (pix < fabs(below[j-1]) && ++nmax > num) ;
                else if (pix < fabs(below[j])   && ++nmax > num) ;
                else if (pix < fabs(below[j+1]) && ++nmax > num) ;
        }
        else
        {
                return(0.0);
        }

        if (nmax > num) return(0.0);
        else            return(pix);
}

float       imf_pixmax(Imrect *im, int i, int j, int num, float thresh)
{
        float     **array;
        Imregion   *roi;

        if (im==NULL)
                return(0);
        if ((roi = im->region) == NULL)
                return(0);
        if (i<roi->ly+1 || i>roi->uy-2 || j<roi->lx+1 || j>roi->ux-2)
                return(0);

        array = (float **)im->data;
        return(array_max(array, i, j, num, thresh));
}

Imrect *imf_nmax(Imrect *im,float thres,int num)
{
     Imrect *maxim;
     Imregion *region;
     float *max,*max_m1,*max_p1;
     float pix;
     int i,j,nmax;
     int lx,ux,ly,uy;
     int uxm1,uym1;

     if (im==NULL) return(NULL);

     maxim = im_alloc(im->height,im->width,im->region,ptr_v);
     region = maxim->region;
     lx = region->lx;
     ux = region->ux;
     ly = region->ly;
     uy = region->uy;

     max = fvector_alloc(lx, ux);
     max_m1 = fvector_alloc(lx, ux);
     max_p1 = fvector_alloc(lx, ux);
     
     uxm1 = ux-1;
     uym1 = uy-1;

     for (i=ly+1;i<uym1;++i)
     {
         im_get_rowf(max,im,i,lx,ux);
         im_get_rowf(max_m1,im,i-1,lx,ux);
         im_get_rowf(max_p1,im,i+1,lx,ux);
         
         for (j=lx+1;j<uxm1;++j)
         {
              Edgel *eptr, *edge_alloc();
              
              if ((pix = fabs(max[j]))<thres) continue;

              nmax = 0;
              
              if (pix<fabs(max_m1[j-1]) && ++nmax > num) continue;
              if (pix<fabs(max_m1[j])   && ++nmax > num) continue;
              if (pix<fabs(max_m1[j+1]) && ++nmax > num) continue;
              if (pix<fabs(max[j-1])    && ++nmax > num) continue;
              if (pix<fabs(max[j+1])    && ++nmax > num) continue;
              if (pix<fabs(max_p1[j-1]) && ++nmax > num) continue;
              if (pix<fabs(max_p1[j])   && ++nmax > num) continue;
              if (pix<fabs(max_p1[j+1]) && ++nmax > num) continue;

              eptr=edge_alloc(EDGE_RAW);
              IM_PTR(maxim, i, j) = (void *)eptr;
         }
     }
     fvector_free(max, lx);
     fvector_free(max_m1, lx);
     fvector_free(max_p1, lx);
     return(maxim);
}
