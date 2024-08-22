/**@(#)
**/
/**
proj.c:
Projection functions for general camera
**/

#include <tina/sys.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

Vec2    cam_proj(Camera * cam, Vec3 v)
{
    Vec2    w = {Vec2_id};
    Vec2    rectify_pos();

    /** transform into camera frame **/
    if (cam->transf != NULL)
	v = trans3_pos(*cam->transf, v);

    /** project onto unit focal plane **/
    w = proj2_of_vec3(v);

    /** allow for optical distortion **/
    if (cam->distort_func != NULL)
	w = cam->distort_func(w, cam->distort_params);

    /** change to image coordinates **/
    w = rectify_pos(cam->cam_to_im, w);

    return (w);
}

void    cam_ray(Camera * cam, Vec2 u, Vec3 * p, Vec3 * v)
{
    Vec2    rectify_pos();
    Vec3    w = {Vec3_id};

    /* change from image to unit camera coordinates */
    rectify_pos(cam->im_to_cam, u);

    /** allow for optical distortion **/
    if (cam->correct_func != NULL)
	u = cam->correct_func(u, cam->distort_params);

    w = proj3_of_vec2(u);
    if (cam->transf != NULL)
    {
	*p = trans3_get_origin2in1(*(cam->transf));

	w = trans3_inverse_vec(*(cam->transf), w);
	*v = vec3_unit(w);
    } else
    {
	*p = vec3_zero();
	*v = vec3_unit(w);
    }
}
