/**@(#)
**/
/**im_warp.c:

general image warping
**/

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

/**
phase this version out
**/

void    imf_warp(Imrect * im1, Imrect * im2, Vec2(*f) ( /* ??? */ ), void *data)
{
    double  x, y;
    Imregion *roi;

    roi = im2->region;

    for (x = roi->lx + 0.5; x < roi->ux; x++)
	for (y = roi->ly + 0.5; y < roi->uy; y++)
	{
	    double  pixval;
	    Vec2    v1 = {Vec2_id};
	    Vec2    v2 = {Vec2_id};

	    v2 = vec2(x, y);
	    v1 = (*f) (v2, data);
	    pixval = im_sub_pixf(im1, vec2_y(v1), vec2_x(v1));
	    im_put_pixf(pixval, im2, (int) y, (int) x);
	}
}

Imrect *im_warp(Imrect * im1, Vec2(*f) ( /* ??? */ ), void *data)
{
    Imrect *im2;
    double  x, y;
    Imregion *roi;

    if (im1 == NULL)
	return (NULL);

    roi = im1->region;
    im2 = im_copy(im1);

    for (x = roi->lx + 0.5; x < roi->ux; x++)
	for (y = roi->ly + 0.5; y < roi->uy; y++)
	{
	    double  pixval;
	    Vec2    v1 = {Vec2_id};
	    Vec2    v2 = {Vec2_id};

	    v2 = vec2(x, y);
	    v1 = (*f) (v2, data);
	    pixval = im_sub_pixf(im1, vec2_y(v1), vec2_x(v1));
	    im_put_pixf(pixval, im2, (int) y, (int) x);
	}
    return (im2);
}

Imregion *roi_rectify(Imregion * roi, Mat3 rect)
{
    Vec2    v = {Vec2_id};
    Vec2    vmin = {Vec2_id};
    Vec2    vmax = {Vec2_id};
    int     lx, ly, ux, uy;

    if (roi == NULL)
	return (NULL);

    v = vec2_rectify(rect, vec2((double) roi->lx, (double) roi->ly));
    vmin = vmax = v;
    v = vec2_rectify(rect, vec2((double) roi->ux + 1, (double) roi->ly));
    vec2_extend_hull(&vmin, &vmax, v);
    v = vec2_rectify(rect, vec2((double) roi->lx, (double) roi->uy + 1));
    vec2_extend_hull(&vmin, &vmax, v);
    v = vec2_rectify(rect, vec2((double) roi->ux + 1, (double) roi->uy + 1));
    vec2_extend_hull(&vmin, &vmax, v);

    lx = (int)floor(vec2_x(vmin));
    ux = (int)(ceil(vec2_x(vmax)) - 0.5);
    ly = (int)floor(vec2_y(vmin));
    uy = (int)(ceil(vec2_y(vmax)) - 0.5);

    return (roi_alloc(lx, ly, ux, uy));
}

Imrect *im_rectify(Imrect * im1, Mat3 rect)
{
    Mat3    irect = {Mat3_id};
    Imrect *im2;
    Imregion *roi;
    int     x, y, lx, ly, ux, uy;

    if (im1 == NULL)
	return (NULL);

    roi = roi_rectify(im1->region, rect);

    im2 = im_alloc(im1->height, im1->width, roi, im1->vtype);
    lx = roi->lx;
    ux = roi->ux;
    ly = roi->ly;
    uy = roi->uy;
    rfree((void *) roi);

    irect = mat3_inverse(rect);

    for (x = lx; x < ux; x++)
	for (y = ly; y < uy; y++)
	{
	    Vec2    v = {Vec2_id};

	    v = vec2_rectify(irect, vec2(x + 0.5, y + 0.5));
	    if (im2->vtype != complex_v)
	    {
		double  g;

		g = im_sub_pixf(im1, vec2_y(v), vec2_x(v));
		im_put_pixf(g, im2, y, x);
	    } else
	    {
		Complex g = {Complex_id};

		g = im_sub_pixz(im1, vec2_y(v), vec2_x(v));
		im_put_pixz(g, im2, y, x);
	    }
	}

    return (im2);
}
