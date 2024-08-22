/**@(#) handling images of vec2's and mat2's
Some image apply and combine functions are also defined here
**/

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/**
applying function to image
ptr -> void
**/

void    im_ptr_apply(Imrect * im, void (*func) (), void *data)
{
    int    *row;
    int     lx, ux, ly, uy;
    int     i, j;

    if (im == NULL)
	return;

    lx = im->region->lx;
    ux = im->region->ux;
    ly = im->region->ly;
    uy = im->region->uy;
    row = tvector_alloc(lx, ux, int);

    for (i = ly; i < uy; ++i)
    {
	im_get_row(row, im, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    (*func) ((void *) row[j], data);
    }

    tvector_free(row, lx, int);
}

/**
applying function to image
ptr -> ptr
**/

Imrect *im_pp_apply(Imrect * im1, void *(*func) (), void *data)
{
    Imrect *im2;
    int    *row1, *row2;
    int     lx, ux, ly, uy;
    int     i, j;

    if (im1 == NULL)
	return (NULL);

    lx = im1->region->lx;
    ux = im1->region->ux;
    ly = im1->region->ly;
    uy = im1->region->uy;
    im2 = im_alloc(im1->height, im1->width, im1->region, ptr_v);
    row1 = tvector_alloc(lx, ux, int);
    row2 = tvector_alloc(lx, ux, int);

    for (i = ly; i < uy; ++i)
    {
	im_get_row(row1, im1, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row2[j] = (int) (*func) ((void *) row1[j], data);
	im_put_row(row2, im2, i, lx, ux);
    }

    tvector_free(row1, lx, int);
    tvector_free(row2, lx, int);

    return (im2);
}

/**
applying function to image
ptr -> float
**/

Imrect *im_pf_apply(Imrect * im1, double (*func) (), void *data)
{
    Imrect *im2;
    int    *row1;
    float  *row2;
    int     lx, ux, ly, uy;
    int     i, j;

    if (im1 == NULL)
	return (NULL);

    lx = im1->region->lx;
    ux = im1->region->ux;
    ly = im1->region->ly;
    uy = im1->region->uy;
    im2 = im_alloc(im1->height, im1->width, im1->region, float_v);
    row1 = tvector_alloc(lx, ux, int);
    row2 = tvector_alloc(lx, ux, float);

    for (i = ly; i < uy; ++i)
    {
	im_get_row(row1, im1, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row2[j] = (float)((*func) ((void *) row1[j], data));
	im_put_rowf(row2, im2, i, lx, ux);
    }

    tvector_free(row1, lx, int);
    tvector_free(row2, lx, float);

    return (im2);
}

/**
combining two images
ptr ptr -> ptr
**/

Imrect *im_ppp_combine(Imrect * im1, Imrect * im2, void *(*func) (), void *data)
{
    Imrect *im3;
    Imregion *roi;
    int    *row1, *row2, *row3;
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

    im3 = im_alloc(height, width, roi, ptr_v);
    row1 = tvector_alloc(lx, ux, int);
    row2 = tvector_alloc(lx, ux, int);
    row3 = tvector_alloc(lx, ux, int);

    for (i = ly; i < uy; ++i)
    {
	im_get_row(row1, im1, i, lx, ux);
	im_get_row(row2, im2, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row3[j] = (int) (*func) ((void *) row1[j], (void *) row2[j], data);
	im_put_row(row3, im3, i, lx, ux);
    }

    tvector_free(row1, lx, int);
    tvector_free(row2, lx, int);
    tvector_free(row3, lx, int);
    rfree((void *) roi);
    return (im3);
}

/**
combining two images
float float -> ptr
**/

Imrect *im_ffp_combine(Imrect * im1, Imrect * im2, void *(*func) (), void *data)
{
    Imrect *im3;
    Imregion *roi;
    float  *row1, *row2;
    int    *row3;
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

    im3 = im_alloc(height, width, roi, ptr_v);
    row1 = tvector_alloc(lx, ux, float);
    row2 = tvector_alloc(lx, ux, float);
    row3 = tvector_alloc(lx, ux, int);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im1, i, lx, ux);
	im_get_rowf(row2, im2, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row3[j] = (int) (*func) (row1[j], row2[j], data);
	im_put_row(row3, im3, i, lx, ux);
    }

    tvector_free(row1, lx, float);
    tvector_free(row2, lx, float);
    tvector_free(row3, lx, int);
    rfree((void *) roi);
    return (im3);
}

/**
combining two images
float ptr -> ptr
**/

Imrect *im_fpp_combine(Imrect * im1, Imrect * im2, void *(*func) (), void *data)
{
    Imrect *im3;
    Imregion *roi;
    float  *row1;
    int    *row2, *row3;
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

    im3 = im_alloc(height, width, roi, ptr_v);
    row1 = tvector_alloc(lx, ux, float);
    row2 = tvector_alloc(lx, ux, int);
    row3 = tvector_alloc(lx, ux, int);

    for (i = ly; i < uy; ++i)
    {
	im_get_rowf(row1, im1, i, lx, ux);
	im_get_row(row2, im2, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row3[j] = (int) (*func) (row1[j], (void *) row2[j], data);
	im_put_row(row3, im3, i, lx, ux);
    }

    tvector_free(row1, lx, float);
    tvector_free(row2, lx, int);
    tvector_free(row3, lx, int);
    rfree((void *) roi);
    return (im3);
}

/**
combining two images
ptr ptr -> float
**/

Imrect *im_ppf_combine(Imrect * im1, Imrect * im2, double (*func) (), void *data)
{
    Imrect *im3;
    Imregion *roi;
    int    *row1, *row2;
    float  *row3;
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

    im3 = im_alloc(height, width, roi, ptr_v);
    row1 = tvector_alloc(lx, ux, int);
    row2 = tvector_alloc(lx, ux, int);
    row3 = tvector_alloc(lx, ux, float);

    for (i = ly; i < uy; ++i)
    {
	im_get_row(row1, im1, i, lx, ux);
	im_get_row(row2, im2, i, lx, ux);
	for (j = lx; j < ux; ++j)
	    row3[j] = (float)((*func) ((void *) row1[j], (void *) row2[j], data));
	im_put_rowf(row3, im3, i, lx, ux);
    }

    tvector_free(row1, lx, int);
    tvector_free(row2, lx, int);
    tvector_free(row3, lx, float);
    rfree((void *) roi);
    return (im3);
}

/* free image of vec2's or mat2's */

void    im_vec2_free(Imrect * im)
{
    im_ptr_apply(im, rfree, NULL);
    im_free(im);
}

void    im_mat2_free(Imrect * im)
{
    im_ptr_apply(im, rfree, NULL);
    im_free(im);
}

/* make image of ptr's to vec2's x-coord from im1 y-coord from im2 */

static void *pvec2_make(double x, double y)
{
    return (vec2_make(vec2(x, y)));
}

Imrect *im_vec2(Imrect * im1, Imrect * im2)
{
    return (im_ffp_combine(im1, im2, pvec2_make, NULL));
}

/* add two vec2 images */

static void *pvec2_sum(Vec2 * u, Vec2 * v)
{
    return (vec2_make(vec2_sum(*u, *v)));
}

Imrect *im_vec2_sum(Imrect * u, Imrect * v)
{
    return (im_ppp_combine(u, v, pvec2_sum, NULL));
}

/* subtract  two vec2 images */

static void *pvec2_diff(Vec2 * u, Vec2 * v)
{
    return (vec2_make(vec2_diff(*u, *v)));
}

Imrect *im_vec2_diff(Imrect * u, Imrect * v)
{
    return (im_ppp_combine(u, v, pvec2_diff, NULL));
}

/* dot product of two vec2 images */

static double pvec2_dot(Vec2 * u, Vec2 * v)
{
    return (vec2_dot(*u, *v));
}

Imrect *im_vec2_dot(Imrect * u, Imrect * v)
{
    return (im_ppf_combine(u, v, pvec2_dot, NULL));
}

/* cross product of two vec2 images */

static double pvec2_cross(Vec2 * u, Vec2 * v)
{
    return (vec2_cross(*u, *v));
}

Imrect *im_vec2_cross(Imrect * u, Imrect * v)
{
    return (im_ppf_combine(u, v, pvec2_cross, NULL));
}

/* product of mat2 image and vec2 image */

static void *pmat2_vprod(Mat2 * m, Vec2 * v)
{
    return (vec2_make(mat2_vprod(*m, *v)));
}

Imrect *im_mat2_vprod(Imrect * m, Imrect * v)
{
    return (im_ppp_combine(m, v, pmat2_vprod, NULL));
}

/* scalar product of vec2 image, mat2 image and vec2 image */

Imrect *im_mat2_sprod(Imrect * u, Imrect * m, Imrect * v)
{
    Imrect *mv = im_mat2_vprod(m, v);
    Imrect *umv;

    umv = im_vec2_dot(u, mv);
    im_ptr_apply(mv, rfree, NULL);
    return (umv);
}

/* invert mat2 image */

static void *pmat2_inverse(Mat2 * m)
{
    return (mat2_make(mat2_inverse(*m)));
}

Imrect *im_mat2_inverse(Imrect * m)
{
    return (im_pp_apply(m, pmat2_inverse, NULL));
}

/* make image of mat2's from images of column vectors */

static void *pmat2_of_cols(Vec2 * cx, Vec2 * cy)
{
    return (mat2_make(mat2_of_cols(*cx, *cy)));
}

Imrect *im_mat2_of_cols(Imrect * cx, Imrect * cy)
{
    return (im_ppp_combine(cx, cy, pmat2_of_cols, NULL));
}

/* make image of mat2's from images of row vectors */

static void *pmat2_of_rows(Vec2 * rx, Vec2 * ry)
{
    return (mat2_make(mat2_of_rows(*rx, *ry)));
}

Imrect *im_mat2_of_rows(Imrect * rx, Imrect * ry)
{
    return (im_ppp_combine(rx, ry, pmat2_of_rows, NULL));
}

/* image of gradients */

Imrect *im_vec2_grad(Imrect * im)
{
    Imrect *imx = imf_diffx(im);
    Imrect *imy = imf_diffy(im);
    Imrect *g;

    g = im_vec2(imx, imy);
    im_free(imx);
    im_free(imy);
    return (g);
}

/* setup images of gradients and hessians */

void    im_mat2_grad_hessian(Imrect * im, Imrect ** g, Imrect ** h)
{
    Imrect *imx = imf_diffx(im);
    Imrect *imy = imf_diffy(im);
    Imrect *gx;
    Imrect *gy;

    gx = im_vec2_grad(imx);
    gy = im_vec2_grad(imy);
    *g = im_vec2(imx, imy);
    im_free(imx);
    im_free(imy);
    *h = im_mat2_of_cols(gx, gy);
    im_vec2_free(gx);
    im_vec2_free(gy);
}

/* return image of hessians */

Imrect *im_mat2_hessian(Imrect * im)
{
    Imrect *g;
    Imrect *h;

    im_mat2_grad_hessian(im, &g, &h);
    im_vec2_free(g);
    return (h);
}

/* image of determinants */

static double pmat2_det(Mat2 * m)
{
    return (mat2_det(*m));
}

Imrect *im_mat2_det(Imrect * m)
{
    return (im_pf_apply(m, pmat2_det, NULL));
}

/* components of vec2 and mat2 images */

static double pvec2_x(Vec2 * v)
{
    return (vec2_x(*v));
}

Imrect *im_vec2_x(Imrect * v)
{
    return (im_pf_apply(v, pvec2_x, NULL));
}

static double pvec2_y(Vec2 * v)
{
    return (vec2_y(*v));
}

Imrect *im_vec2_y(Imrect * v)
{
    return (im_pf_apply(v, pvec2_y, NULL));
}

static double pmat2_xx(Mat2 * m)
{
    return (mat2_xx(*m));
}

Imrect *im_mat2_xx(Imrect * m)
{
    return (im_pf_apply(m, pmat2_xx, NULL));
}

static double pmat2_xy(Mat2 * m)
{
    return (mat2_xy(*m));
}

Imrect *im_mat2_xy(Imrect * m)
{
    return (im_pf_apply(m, pmat2_xy, NULL));
}

static double pmat2_yx(Mat2 * m)
{
    return (mat2_yx(*m));
}

Imrect *im_mat2_yx(Imrect * m)
{
    return (im_pf_apply(m, pmat2_yx, NULL));
}

static double pmat2_yy(Mat2 * m)
{
    return (mat2_yy(*m));
}

Imrect *im_mat2_yy(Imrect * m)
{
    return (im_pf_apply(m, pmat2_yy, NULL));
}
