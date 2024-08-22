/**@(#)
**/
#ifdef TRANSPUTER
#include <valuesdual.h>
#else
#include <values.h>
#endif
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/* standard access funtion to get left image pixel position from the 3D
 * to image match structure */

Vec2   *leftpix_get(List * l)
{
    Match  *image_3d;
    Match  *left_right;

    if ((image_3d = (Match *) l->to)
	&& (left_right = image_3d->to2))
	return (left_right->to1);
    else
	return (NULL);
}

/* standard access funtion to get right image pixel position from the
 * 3D to image match structure */

Vec2   *rightpix_get(List * l)
{
    Match  *image_3d;
    Match  *left_right;

    if ((image_3d = (Match *) l->to)
	&& (left_right = image_3d->to2))
	return (left_right->to2);
    else
	return (NULL);
}

Vec3   *world_get(List * l)
{
    Match  *image_3d;

    if ((image_3d = l->to))
	return (image_3d->to1);
    else
	return (NULL);
}

void    calib_update(Covar * tot_inv, Camera * leftc, Camera * rightc, int mask)
{
    int     i, n_par = 0;
    double *a;

    if (tot_inv == NULL)
	return;

    for (i = 0; i < 16; i++)
	if (mask & (1 << i))
	    n_par++;
    a = (double *) ralloc((unsigned) (2 * (n_par + 6) * sizeof(double)));

    (void) conv_camera_int(mask, leftc, &a[6]);
    (void) conv_camera_int(mask, rightc, &a[n_par + 6]);
    (void) conv_camera_ext(leftc, a);
    (void) conv_camera_rel(leftc, rightc, &a[n_par]);
    for (i = 0; i < 2 * n_par + 6; i++)
	VECTOR_GET(tot_inv->vec, i, a[i + 6]);
    (void) store_camera_int(mask, &a[6], leftc);
    (void) store_camera_int(mask, &a[n_par + 2 * 6], rightc);
    (void) store_camera_ext(a, leftc);
    (void) store_camera_rel(&a[n_par + 6], leftc, rightc);
    rfree((void *) a);
}
