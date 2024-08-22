/**@(#)
**/
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>

/** finding min and max and scaling images **/

void imf_minmax(Imrect * im, float *pmin, float *pmax)
{
    Imregion *roi;
    float *row, min, max;
    int lx, ux, ly, uy;
    int i, j;

    if (im == NULL)
    {
	*pmin = (float)0.0;
	*pmax = (float)0.0;
	return;
    }
    roi = im->region;
    if (roi == NULL)
    {
	*pmin = (float)0.0;
	*pmax = (float)0.0;
	return;
    }
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    row = fvector_alloc(lx, ux);
    min = max = (float)im_get_pixf(im, ly, lx);
    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row, im, i, lx, ux);
	for (j = lx; j < ux; ++j)
	{
	    if (min > row[j])
		min = row[j];
	    if (max < row[j])
		max = row[j];
	}
    }

    *pmin = min;
    *pmax = max;
    fvector_free((void *) row, lx);
}

double imf_min(Imrect * im, int *y, int *x)
{
    Imregion *roi;
    float *row, min;
    int lx, ux, ly, uy;
    int i, j;

    if (im == NULL)
	return (0.0);

    roi = im->region;
    if (roi == NULL)
	return (0.0);

    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    row = fvector_alloc(lx, ux);
    min = (float)im_get_pixf(im, ly, lx);
    if (y != NULL)
	*y = 0;
    if (x != NULL)
	*x = 0;
    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row, im, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    if (min > row[j])
	    {
		min = row[j];
		if (y != NULL)
		    *y = i;
		if (x != NULL)
		    *x = j;
	    }
    }

    fvector_free((void *) row, lx);
    return (min);
}

double imf_max(Imrect * im, int *y, int *x)
{
    Imregion *roi;
    float *row, max;
    int lx, ux, ly, uy;
    int i, j;

    if (im == NULL)
	return (0.0);

    roi = im->region;
    if (roi == NULL)
	return (0.0);

    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    row = fvector_alloc(lx, ux);
    max = (float)im_get_pixf(im, ly, lx);
    if (y != NULL)
	*y = 0;
    if (x != NULL)
	*x = 0;
    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row, im, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    if (max < row[j])
	    {
		max = row[j];
		if (y != NULL)
		    *y = i;
		if (x != NULL)
		    *x = j;
	    }
    }

    fvector_free((void *) row, lx);
    return (max);
}

Imrect *imf_scale(Imrect * im1, double low, double high)
{
    Imrect *im2;
    Imregion *roi;
    float *row1, *row2;
    int lx, ux, ly, uy;
    int i, j;
    float min, max, scale;

    if (im1 == NULL)
	return (NULL);

    roi = im1->region;
    if (roi == NULL)
	return (NULL);

    imf_minmax(im1, &min, &max);
    if (max == min)
	max = (float)(min + 1.0);

    scale = (float)((high - low) / (max - min));
    low -= scale * min;

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
	    row2[j] = (float)(low + scale * row1[j]);
	im_put_rowf(row2, im2, i, lx, ux);
    }

    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    return (im2);
}

/* gamma scale the range oldlow, oldhigh in image im using newlow,
 * newhigh, thresholding at threslow, threshigh */
void im_gamma_scale_range_inplace(Imrect * im,
				  double gamma,
				  double oldlow, double oldhigh,
				  double newlow, double newhigh,
				  double threslow, double threshigh)
{
    Imregion *roi;
    float *row1, *row2;
    int lx, ux, ly, uy;
    double scale, base, range;
    int i, j;

    if (im == NULL)
	return;

    roi = im->region;
    if (roi == NULL)
	return;
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    if (oldlow == oldhigh)
	scale = 1.0;
    else
	scale = 1.0 / (oldhigh - oldlow);
    base = newlow;
    range = newhigh - oldlow;

    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);
    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im, i, lx, ux);
	for (j = lx; j < ux; ++j)
	{
	    double val;

	    val = base + range * pow(scale * (row1[j] - oldlow), gamma);
	    val = MAX(val, threslow);
	    row2[j] = (float)MIN(val, threshigh);
	}
	im_put_rowf(row2, im, i, lx, ux);
    }

    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
}

/* scales the range oldlow, oldhigh in image im newlow, newhigh,
 * thresholding at threslow, threshigh */
void im_scale_range_inplace(Imrect * im,
			    double oldlow, double oldhigh,
			    double newlow, double newhigh,
			    double threslow, double threshigh)
{
    Imregion *roi;
    float *row1, *row2;
    int lx, ux, ly, uy;
    float scale, base;
    int i, j;

    if (im == NULL)
	return;

    roi = im->region;
    if (roi == NULL)
	return;
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    if (oldlow == oldhigh)
	scale = (float)1.0;
    else
	scale = (float)((newhigh - newlow) / (oldhigh - oldlow));
    base = (float)(newlow - scale * oldlow);

    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);
    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im, i, lx, ux);
	for (j = lx; j < ux; ++j)
	{
	    double val;

	    val = base + scale * row1[j];
	    val = MAX(val, threslow);
	    row2[j] = (float)MIN(val, threshigh);
	}
	im_put_rowf(row2, im, i, lx, ux);
    }

    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
}

void imf_times_inplace(double k, Imrect * im)
{
    Imregion *roi;
    float *row;
    int lx, ux, ly, uy;
    int i, j;

    if (im == NULL)
	return;
    roi = im->region;
    if (roi == NULL)
	return;
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;
    row = fvector_alloc(lx, ux);
    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row, im, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row[j] *= (float)k;
	im_put_rowf(row, im, i, lx, ux);
    }
    fvector_free((void *) row, lx);
}

void imf_add_inplace(double k, Imrect * im)
{
    Imregion *roi;
    float *row;
    int lx, ux, ly, uy;
    int i, j;

    if (im == NULL)
	return;
    roi = im->region;
    if (roi == NULL)
	return;
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;
    row = fvector_alloc(lx, ux);
    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row, im, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row[j] += (float)k;
	im_put_rowf(row, im, i, lx, ux);
    }
    fvector_free((void *) row, lx);
}

void imf_accum_inplace(Imrect * im1, double k, Imrect * im2)
{
    Imregion *roi1, *roi2;
    float *row1, *row2;
    int lx, ux, ly, uy;
    int i, j;

    if (im1 == NULL || im2 == NULL)
	return;

    roi1 = im1->region;
    roi2 = im2->region;
    if (roi1 == NULL || roi2 == NULL)
	return;
    lx = MAX(roi1->lx, roi2->lx);
    ly = MAX(roi1->ly, roi2->ly);
    ux = MIN(roi1->ux, roi2->ux);
    uy = MIN(roi1->uy, roi2->uy);
    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);
    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im1, i, lx, ux);
	im_get_rowf(row2, im2, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row1[j] += (float)(k * row2[j]);
	im_put_rowf(row1, im1, i, lx, ux);
    }
    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
}

double imf_mean(Imrect * im)
{
    Imregion *roi;
    float *row;
    double sum = 0;
    int lx, ux, ly, uy;
    int i, j;

    if (im == NULL)
	return(0);
    roi = im->region;
    if (roi == NULL)
	return(0);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;
    row = fvector_alloc(lx, ux);
    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row, im, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    sum += row[j];
    }
    fvector_free((void *) row, lx);
    return(sum/((uy-ly)*(ux-lx)));
}

void imf_scale_inplace(Imrect * im, double low, double high)
{
    Imregion *roi;
    float *row1, *row2;
    int lx, ux, ly, uy;
    float min, max, scale;
    int i, j;

    if (im == NULL)
	return;

    roi = im->region;
    if (roi == NULL)
	return;
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    imf_minmax(im, &min, &max);
    if (max == min)
	max = (float)(min + 1.0);

    scale = (float)((high - low) / (max - min));
    low -= scale * min;

    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row2[j] = (float)(low + scale * row1[j]);
	im_put_rowf(row2, im, i, lx, ux);
    }

    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
}

void im_locate_max(Imrect * im, int *y, int *x)
{
    Imregion *roi;
    float *row, max;
    int lx, ux, ly, uy, xmax, ymax;
    int i, j;

    if (im == NULL)
    {
	*y = *x = 0;
	return;
    }
    roi = im->region;
    if (roi == NULL)
    {
	*y = *x = 0;
	return;
    }
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    row = fvector_alloc(lx, ux);
    max = (float)im_get_pixf(im, ly, lx);
    xmax = lx;
    ymax = ly;
    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row, im, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    if (max < row[j])
	    {
		max = row[j];
		xmax = j;
		ymax = i;
	    }
    }

    *x = xmax;
    *y = ymax;
    fvector_free((void *) row, lx);
}

/* WARNING: `miny' may be used uninitialized in this function */
void im_locate_interest(Imrect * im, int *y, int *x)
{
    Imregion *roi;
    float *row1, *row2;
    double max;
    int lx, ux, ly, uy, minx, miny = 0;
    int i, j;

    if (im == NULL)
    {
	*y = *x = 0;
	return;
    }
    roi = im->region;
    if (roi == NULL)
    {
	*y = *x = 0;
	return;
    }
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;

    max = 0.0;
    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);
    im_get_rowf(row2, im, ly, lx, ux);
    for (i = ly + 1; i < uy - 1; ++i)
    {
	SWAP(float *, row1, row2);

	im_get_rowf(row2, im, i + 1, lx, ux);
	for (j = lx + 1; j < ux - 1; ++j)
	{
	    double dxy;

	    dxy = fabs(row1[j - 1] - row2[j + 1]) + fabs(row1[j + 1] - row2[j - 1]);
	    if (max < dxy)
	    {
		max = dxy;
		minx = j;
		miny = i;
	    }
	}
    }

    *x = minx;
    *y = miny;
    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
}
