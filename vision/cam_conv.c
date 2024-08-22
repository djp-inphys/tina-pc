/**@(#)
**/
#include <math.h>
#include <stdio.h>
#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

#define Bit(mask,num)     (mask&(1<<num))

int     conv_camera_int(int mask, Camera * cam, double *a)
{
    int     i = 0;
    double *b;

    if (cam == NULL || a == NULL)
	return (0);

    if (Bit(mask, 0))
	a[i++] = (double) cam->f;
    if (Bit(mask, 1))
	a[i++] = (double) cam->cx;
    if (Bit(mask, 2))
	a[i++] = (double) cam->cy;
    if (Bit(mask, 3))
	a[i++] = 1.0 / (double) cam->ax;
    if (Bit(mask, 4))
	a[i++] = 1.0 / (double) cam->ay;
    if (Bit(mask, 5) && cam->distort_params != NULL)
    {
	b = cam->distort_params;
	a[i++] = b[1];
    }
    return (i);
}

int     conv_camera_ext(Camera * cam, double *a)
{
    double  x[4];
    int     i;

    if (cam == NULL || a == NULL)
	return (0);

    conv_rot_to_quat(&(cam->transf->R), x);
    for (i = 0; i < 3; i++)
	a[i] = x[i + 1];
    a[3] = cam->transf->t.el[0];
    a[4] = cam->transf->t.el[1];
    a[5] = cam->transf->t.el[2];

    return (1);
}

int     conv_camera_rel(Camera * cam1, Camera * cam2, double *a)
{
    double  x[4];
    Transform3 inv2 = {Transform3_id};
    Transform3 rel2to1 = {Transform3_id};
    Transform3 trans3_inverse();
    Transform3 trans3_prod();
    int     i;

    if (cam1 == NULL || cam2 == NULL || a == NULL)
	return (0);
    inv2 = trans3_inverse(*(cam2->transf));
    rel2to1 = trans3_prod(*(cam1->transf), inv2);
    conv_rot_to_quat(&(rel2to1.R), x);
    for (i = 0; i < 3; i++)
	a[i + 2] = x[i + 1];
    a[5] = sqrt(rel2to1.t.el[0] * rel2to1.t.el[0]
		+ rel2to1.t.el[1] * rel2to1.t.el[1]
		+ rel2to1.t.el[2] * rel2to1.t.el[2]);
    if (rel2to1.t.el[0] < 0.0)
	a[5] *= -1.0;
    a[0] = rel2to1.t.el[1] / a[5];
    a[1] = rel2to1.t.el[2] / a[5];
    return (1);
}

int     store_camera_int(int mask, double *a, Camera * cam)
{
    double *b;
    int     i = 0;

    if (cam == NULL || a == NULL)
	return (0);

    if (Bit(mask, 0))
	cam->f = (float)a[i++];
    if (Bit(mask, 1))
	cam->cx = (float)a[i++];
    if (Bit(mask, 2))
	cam->cy = (float)a[i++];
    if (Bit(mask, 3))
	cam->ax = (float)(1.0 / a[i++]);
    if (Bit(mask, 4))
	cam->ay = (float)(1.0 / a[i++]);
    if (Bit(mask, 5) && cam->distort_params != NULL)
    {
	b = cam->distort_params;
	b[1] = a[i++];
    }
    return (i);
}

int     store_camera_ext(double *a, Camera * cam)
{
    void    conv_quat_to_rot();
    double  x[4];
    double  kx, ky;
    int     i;

    if (cam == NULL || a == NULL)
	return (0);

    for (i = 0; i < 3; i++)
	x[i + 1] = a[i];
    if ((x[0] = 1.0 - x[1] * x[1] - x[2] * x[2] - x[3] * x[3]) > 0.0)
	x[0] = sqrt(x[0]);
    else
	return (0);

    conv_quat_to_rot(x, &(cam->transf->R));
    cam->transf->t.el[0] = (float)a[3];
    cam->transf->t.el[1] = (float)a[4];
    cam->transf->t.el[2] = (float)a[5];

    kx = cam->ax * cam->f / cam->pixel;
    ky = cam->ay * cam->f / cam->pixel;
    cam->cam_to_im = mat3(kx, 0.0, cam->cx,
			  0.0, ky, cam->cy,
			  0.0, 0.0, 1.0);
    cam->im_to_cam = mat3(1.0 / kx, 0.0, -cam->cx / kx,
			  0.0, 1.0 / ky, -cam->cy / ky,
			  0.0, 0.0, 1.0);
    return (1);
}

int     store_camera_rel(double *a, Camera * cam1, Camera * cam2)
{
    void    conv_quat_to_rot();
    double  x[4];
    double  kx, ky;
    Transform3 invrel = {Transform3_id};
    Transform3 rel2to1 = {Transform3_id};
    Transform3 trans3_prod();
    Transform3 trans3_inverse();
    int     i;

    if (cam1 == NULL || cam2 == NULL || a == NULL)
	return (0);

    if ((1.0 - a[0] * a[0] - a[1] * a[1]) < 0.0)
	return (0);
    for (i = 0; i < 3; i++)
	x[i + 1] = a[i + 2];
    if ((x[0] = 1.0 - x[1] * x[1] - x[2] * x[2] - x[3] * x[3]) > 0.0)
	x[0] = sqrt(x[0]);
    else
	return (0);
    conv_quat_to_rot(x, &(rel2to1.R));
    rel2to1.t.el[0] = (float)(sqrt(1.0 - a[0] * a[0] - a[1] * a[1]) * a[5]);
    rel2to1.t.el[1] = (float)(a[0] * a[5]);
    rel2to1.t.el[2] = (float)(a[1] * a[5]);

    invrel = trans3_inverse(rel2to1);
    *(cam2->transf) = trans3_prod(invrel, *(cam1->transf));

    kx = cam2->ax * cam2->f / cam2->pixel;
    ky = cam2->ay * cam2->f / cam2->pixel;
    cam2->cam_to_im = mat3(kx, 0.0, cam2->cx,
			   0.0, ky, cam2->cy,
			   0.0, 0.0, 1.0);
    cam2->im_to_cam = mat3(1.0 / kx, 0.0, -cam2->cx / kx,
			   0.0, 1.0 / ky, -cam2->cy / ky,
			   0.0, 0.0, 1.0);
    return (1);
}
