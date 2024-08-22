/**@(#)
**/
/**
camera.c:
general camera functions
**/

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/* ARGSUSED quieten lint */
Camera *cam_alloc(int type)
/* unused */
{
    Camera *cam = ts_ralloc(Camera);

    cam->label = new_label();

    return (cam);
}

void    cam_comp_default_rects(Camera * cam)
{
    double  kx, ky;
    double  cx, cy;

    if (cam == NULL)
	return;

    kx = cam->ax * cam->f / cam->pixel;
    ky = cam->ay * cam->f / cam->pixel;
    cx = cam->cx;
    cy = cam->cy;

    cam->cam_to_im = mat3(kx, 0.0, cx,
			  0.0, ky, cy,
			  0.0, 0.0, 1.0);

    cam->im_to_cam = mat3(1.0 / kx, 0.0, -cx / kx,
			  0.0, 1.0 / ky, -cy / ky,
			  0.0, 0.0, 1.0);
}

Camera *cam_make(unsigned int type, Transform3 * transf, double f, double pix, double ax, double ay, double cx, double cy, int width, int height)
{
    Camera *cam = ts_ralloc(Camera);

    cam->type = type;
    cam->label = new_label();

    cam->f = (float)f;
    cam->ax = (float)ax;
    cam->ay = (float)ay;
    cam->cx = (float)cx;
    cam->cy = (float)cy;
    cam->pixel = (float)pix;
    cam->width = width;
    cam->height = height;

    cam->distort_params = NULL;
    cam->distort_func = cam->correct_func = NULL;
    cam->correct_func = NULL;
    cam->copy_dist_func = NULL;
    cam->transf = trans3_copy(transf);

    cam_comp_default_rects(cam);

    return (cam);
}

Camera *cam_copy(Camera * cam)
{
    Camera *new_cam;

    if (cam == NULL)
	return (NULL);
    new_cam = cam_make(cam->type, cam->transf, cam->f, cam->pixel,
		       cam->ax, cam->ay, cam->cx, cam->cy,
		       cam->width, cam->height);
    new_cam->correct_func = cam->correct_func;
    new_cam->distort_func = cam->distort_func;
    if (cam->distort_params != NULL)
    {
	if (cam->copy_dist_func != NULL)
	{
	    new_cam->distort_params = cam->copy_dist_func(cam->distort_params);
	    new_cam->copy_dist_func = cam->copy_dist_func;
	} else
	{
	    format("warning: distortion parameters not copied\n");
	    new_cam->correct_func = new_cam->distort_func = NULL;
	}
    } else			/* no distortion now */
	new_cam->correct_func = new_cam->distort_func = NULL;
    return (new_cam);
}

Bool    cam_scale_to_image(Camera * cam, Imrect * im)
{
    int     hscale, wscale;
    Bool    larger;

    if (cam == NULL || im == NULL)
	return (false);

    if (cam->width == im->width && cam->height == im->height)
	return (true);

    if (cam->width > im->width)
    {
	larger = true;
	wscale = cam->width / im->width;
	if (cam->width != wscale * im->width)
	    return (false);	/* can't scale camera */
    } else
    {
	larger = false;
	wscale = im->width / cam->width;
	if (im->width != wscale * cam->width)
	    return (false);	/* can't scale camera */
    }

    if (cam->height > im->height)
    {
	if (larger == false)
	    return (false);
	hscale = cam->height / im->height;
	if (hscale != wscale || cam->height != hscale * im->height)
	    return (false);	/* cant scale camera */
    } else
    {
	if (larger == true)
	    return (false);
	hscale = im->height / cam->height;
	if (hscale != wscale || im->height != hscale * cam->height)
	    return (false);	/* cant scale camera */
    }

    if (larger)
    {
	cam->width /= wscale;
	cam->height /= wscale;
	cam->pixel *= wscale;	/* the pixel size increases */
	cam->cx /= wscale;
	cam->cy /= wscale;
    } else
    {
	cam->width *= wscale;
	cam->height *= wscale;
	cam->pixel /= wscale;	/* the pixel size decreases */
	cam->cx *= wscale;
	cam->cy *= wscale;
    }
    cam_comp_default_rects(cam);
    return (true);
}

void    cam_free(Camera * cam)
{
    if (cam == NULL)
	return;

    if (cam->transf)
	rfree((void *) cam->transf);
    if (cam->distort_params)
	rfree((void *) cam->distort_params);

    rfree((void *) cam);
}
