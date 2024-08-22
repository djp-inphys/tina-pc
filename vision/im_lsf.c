/**@(#)
**/
/* im_lsf.c
 * 
 * linear sequential filter functions
 * 
 */

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

static void lsf_smooth(int n1, int n2, float *u1, float *u2, double sigma, float *weight)
{
    int     i;
    float  *v1 = fvector_alloc(n1, n2);
    float  *v2 = fvector_alloc(n1, n2);
    double  a, b = exp(-1.0 / sigma), ab;

    a = (1 - b) / (1 + b);	/** makes filter sum to 1 **/
    ab = a * b;

    v1[n1] = (float)(a * u1[n1]);
    for (i = n1 + 1; i < n2; i++)
	v1[i] = (float)(a * u1[i] + b * v1[i - 1]);

    v2[n2 - 1] = (float) 0.0;
    for (i = n2 - 2; i >= n1; i--)
	v2[i] = (float) (ab * u1[i + 1] + b * v2[i + 1]);

    for (i = n1; i < n2; i++)
	u2[i] = v1[i] + v2[i];

    if (weight != NULL)
	for (i = n1; i < n2; i++)
	    u2[i] /= weight[i];

    fvector_free((void *) v1, n1);
    fvector_free((void *) v2, n1);
}

static void lsf_smooth_side(int n1, int n2, float *u1, float *u2, double sigma, float *weight, int side)
{
    int     i;
    double  a, b = exp(-1.0 / sigma);

    a = 1 - b;			/** makes filter sum to 1 **/

    if (side == 1)
    {
	u2[n1] = (float)(a * u1[n1]);
	for (i = n1 + 1; i < n2; i++)
	    u2[i] = (float)(a * u1[i] + b * u2[i - 1]);
    } else
    {
	u2[n2 - 1] = (float)(a * u1[n2 - 1]);
	for (i = n2 - 2; i >= n1; i--)
	    u2[i] = (float)(a * u1[i] + b * u2[i + 1]);
    }

    if (weight != NULL)
	for (i = n1; i < n2; i++)
	    u2[i] /= weight[i];
}

Imrect *imf_lsf_smooth(Imrect * im1, double sigma)
{
    Imrect *im2;
    Imrect *im3;
    Imregion *roi;
    float  *row1, *row2, *col1, *col2, *ones, *weight;
    int     lx, ux, ly, uy;
    int     i;

    if (im1 == NULL)
	return (NULL);

    roi = im1->region;
    if (roi == NULL)
	return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;


    ones = fvector_alloc(lx, ux);
    weight = fvector_alloc(lx, ux);
    for (i = lx; i < ux; ++i)
	ones[i] = (float)1.0;
    lsf_smooth(lx, ux, ones, weight, sigma, (float *) NULL);
    fvector_free((void *) ones, lx);

    im2 = im_alloc(im1->height, im1->width, roi, float_v);
    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);
    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im1, i, lx, ux);
	lsf_smooth(lx, ux, row1, row2, sigma, weight);
	im_put_rowf(row2, im2, i, lx, ux);
    }
    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    fvector_free((void *) weight, lx);

    ones = fvector_alloc(ly, uy);
    weight = fvector_alloc(ly, uy);
    for (i = ly; i < uy; ++i)
	ones[i] = (float)1.0;
    lsf_smooth(ly, uy, ones, weight, sigma, (float *) NULL);
    fvector_free((void *) ones, ly);

    im3 = im_alloc(im1->height, im1->width, roi, float_v);
    col1 = fvector_alloc(ly, uy);
    col2 = fvector_alloc(ly, uy);
    for (i = lx; i < ux; ++i)
    {
	im_get_colf(col1, im2, i, ly, uy);
	lsf_smooth(ly, uy, col1, col2, sigma, weight);
	im_put_colf(col2, im3, i, ly, uy);
    }
    fvector_free((void *) col1, ly);
    fvector_free((void *) col2, ly);
    fvector_free((void *) weight, ly);

    im_free(im2);

    return (im3);
}

Imrect *imf_lsf_smooth_quad(Imrect * im1, double sigma, int sidex, int sidey)
{
    Imrect *im2;
    Imrect *im3;
    Imregion *roi;
    float  *row1, *row2, *col1, *col2, *ones, *weight;
    int     lx, ux, ly, uy;
    int     i;

    if (im1 == NULL)
	return (NULL);

    roi = im1->region;
    if (roi == NULL)
	return (NULL);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;


    ones = fvector_alloc(lx, ux);
    weight = fvector_alloc(lx, ux);
    for (i = lx; i < ux; ++i)
	ones[i] = (float)1.0;
    lsf_smooth_side(lx, ux, ones, weight, sigma, (float *) NULL, sidex);
    fvector_free((void *) ones, lx);

    im2 = im_alloc(im1->height, im1->width, roi, float_v);
    row1 = fvector_alloc(lx, ux);
    row2 = fvector_alloc(lx, ux);
    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im1, i, lx, ux);
	lsf_smooth_side(lx, ux, row1, row2, sigma, weight, sidex);
	im_put_rowf(row2, im2, i, lx, ux);
    }
    fvector_free((void *) row1, lx);
    fvector_free((void *) row2, lx);
    fvector_free((void *) weight, lx);

    ones = fvector_alloc(ly, uy);
    weight = fvector_alloc(ly, uy);
    for (i = ly; i < uy; ++i)
	ones[i] = (float)1.0;
    lsf_smooth_side(ly, uy, ones, weight, sigma, (float *) NULL, sidey);
    fvector_free((void *) ones, ly);

    im3 = im_alloc(im1->height, im1->width, roi, float_v);
    col1 = fvector_alloc(ly, uy);
    col2 = fvector_alloc(ly, uy);
    for (i = lx; i < ux; ++i)
    {
	im_get_colf(col1, im2, i, ly, uy);
	lsf_smooth_side(ly, uy, col1, col2, sigma, weight, sidey);
	im_put_colf(col2, im3, i, ly, uy);
    }
    fvector_free((void *) col1, ly);
    fvector_free((void *) col2, ly);
    fvector_free((void *) weight, ly);

    im_free(im2);

    return (im3);
}
