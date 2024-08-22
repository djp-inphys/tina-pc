#include <math.h>
#include <values.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>

#define s2(a, b) {register int t; if ((t=b-a)< 0) {a += t; b -= t;}}
#define mn3(a, b, c) s2(a, b); s2(a, c);
#define mx3(a, b, c) s2(b, c); s2(a, c);
#define mnmx3(a, b, c) mx3(a, b, c); s2(a, b);
#define mnmx4(a, b, c, d) s2(a, b); s2(c, d); s2(a, c); s2(b, d);
#define mnmx5(a, b, c, d, e) s2(a, b); s2(c, d); mn3(a, c, e); mx3(b, d, e);
#define mnmx6(a, b, c, d, e, f) s2(a, d); s2(b, e); s2(c, f); \
mn3(a, b, c); mx3(d, e, f);

int med3by3(int *b1, int *b2, int *b3)
{
    register int r1, r2, r3, r4, r5, r6;
    r1 = *b1--; r2 = *b1++; r3 = *b1++;
    r4 = *b2--; r5 = *b2++; r6 = *b2++;
    mnmx6(r1, r2, r3, r4, r5, r6);
    r1 = *b3--;
    mnmx5(r1, r2, r3, r4, r5);
    r1 = *b3++;
    mnmx4(r1, r2, r3, r4);
    r1 = *b3++;
    mnmx3(r1, r2, r3);
    return(r2);
}

float med3by3f(float *b1, float *b2, float *b3)
{
    float r[9];
    int label[9];
    int i,j;
    float max=-MAXFLOAT,min=MAXFLOAT;
    int max_label,min_label;

    r[0] = b1[-1]; r[1] = b1[0]; r[2] = b1[1];
    r[3] = b2[-1]; r[4] = b2[0]; r[5] = b2[1];
    r[6] = b3[-1]; r[7] = b3[0]; r[8] = b3[1];
    for (i=0;i<9;i++) label[i] = 1;
    for(j=0;j<4;j++)
    {
        for(i=0;i<9;i++)
        {
           if (label[i] && (r[i]<=min))
           {
               min_label = i; 
               min = r[i];
           }
           if (label[i] && (r[i]>=max))
           {
               max_label = i;
               max = r[i];
           }
        }
        label[max_label] = 0;
        label[min_label] = 0;
        max = -MAXFLOAT;
        min = MAXFLOAT;
    }
    return(r[min_label]);
}
/**
3x3 median filter
At edges adds e.g. new first row equal to old before filtering
**/

Imrect *imc_median(Imrect *im1)
{
    Imrect *im2;
    Imregion *roi;
    int *row, *row1, *row2, *row3;
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

    im2 = im_alloc(im1->height, im1->width, roi, uchar_v);
    row  = ivector_alloc(lx, ux);
    row1 = ivector_alloc(lx-1, ux+1);
    row2 = ivector_alloc(lx-1, ux+1);
    row3 = ivector_alloc(lx-1, ux+1);
    im_get_row(row2, im1, ly, lx, ux);
    row2[lx-1] = row2[lx]; row2[ux] = row2[ux-1];
    im_get_row(row3, im1, ly, lx, ux);
    row3[lx-1] = row3[lx]; row3[ux] = row3[ux-1];
    for (i = ly; i < uy; ++i)
    {
	int *temp = row1;
	row1 = row2;
	row2 = row3;
	row3 = temp;

	if(i != uy-1)
	    im_get_row(row3, im1, i+1, lx, ux);
	else
	    im_get_row(row3, im1, i, lx, ux);
	row3[lx-1] = row3[lx]; row3[ux] = row3[ux-1];

	for (j = lx; j < ux; ++j)
	    row[j] = med3by3(&row1[j], &row2[j], &row3[j]);

	im_put_row(row, im2, i, lx, ux);
    }

    ivector_free(row,  lx);
    ivector_free(row1, lx-1);
    ivector_free(row2, lx-1);
    ivector_free(row3, lx-1);
    return (im2);
}

Imrect *imi_median(Imrect *im)
{
    return(NULL);
}

Imrect *imf_median(Imrect *im1)
{
    Imrect *im2;
    Imregion *roi;
    float *row, *row1, *row2, *row3;
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
    row  = fvector_alloc(lx, ux);
    row1 = fvector_alloc(lx-1, ux+1);
    row2 = fvector_alloc(lx-1, ux+1);
    row3 = fvector_alloc(lx-1, ux+1);
    im_get_rowf(row2, im1, ly, lx, ux);
    row2[lx-1] = row2[lx]; row2[ux] = row2[ux-1];
    im_get_rowf(row3, im1, ly, lx, ux);
    row3[lx-1] = row3[lx]; row3[ux] = row3[ux-1];
    for (i = ly; i < uy; ++i)
    {
        float *temp = row1;
        row1 = row2;
        row2 = row3;
        row3 = temp;

        if(i != uy-1)
            im_get_rowf(row3, im1, i+1, lx, ux);
        else
            im_get_rowf(row3, im1, i, lx, ux);
        row3[lx-1] = row3[lx]; row3[ux] = row3[ux-1];

        for (j = lx; j < ux; ++j)
            row[j] = med3by3f(&row1[j], &row2[j], &row3[j]);

        im_put_rowf(row, im2, i, lx, ux);
    }

    fvector_free(row,  lx);
    fvector_free(row1, lx-1);
    fvector_free(row2, lx-1);
    fvector_free(row3, lx-1);
    return (im2);
}

Imrect *imz_median(Imrect *im)
{
    return(NULL);
}

Imrect *im_median(Imrect *im)
{
    if(im == NULL)
        return(NULL);
    switch(im->vtype)
    {
        case uchar_v:
            return(imc_median(im));
        case int_v:
            return(imi_median(im));
        case float_v:
            return(imf_median(im));
        case complex_v:
            return(imz_median(im));
        default:
            return(NULL); 
    }
}

