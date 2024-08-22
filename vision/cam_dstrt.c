/**@(#)
**/
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Vec2    radial_distort(Vec2 w, double *a)
{
    Vec2    v = {Vec2_id};
    double  radsq;

    radsq = w.el[0] * w.el[0] + w.el[1] * w.el[1];
    v.el[0] = (float)((1.0 - a[1] * radsq) * w.el[0]);
    v.el[1] = (float)((1.0 - a[1] * radsq) * w.el[1]);
    return (v);
}

Vec2    radial_correct(Vec2 w, double *a)
{
    Vec2    v = {Vec2_id};
    double  radsq;

    v.el[0] = w.el[0];
    v.el[1] = w.el[1];

    radsq = v.el[0] * v.el[0] + v.el[1] * v.el[1];
    v.el[0] = (float)((1.0 + a[1] * radsq) * w.el[0]);
    v.el[1] = (float)((1.0 + a[1] * radsq) * w.el[1]);

    radsq = v.el[0] * v.el[0] + v.el[1] * v.el[1];
    v.el[0] = (float)((1.0 + a[1] * radsq) * w.el[0]);
    v.el[1] = (float)((1.0 + a[1] * radsq) * w.el[1]);
    return (v);
}

Vec2    cam_correct(Vec2 u, Camera * cam)



/* this routine cannot be called with a NULL cam pointer */
{
    if ((cam->correct_func != NULL) && (cam->distort_params != NULL))
    {
	/* change from image to unit camera coordinates */
	u = rectify_pos(cam->im_to_cam, u);
	/** allow for optical distortion **/
	u = cam->correct_func(u, cam->distort_params);
	/** change back to image coordinates **/
	u = rectify_pos(cam->cam_to_im, u);
    }
    return (u);
}

void   *cam_distort_copy(double *b)
{
    int     i, n;
    double *a;

    n = (int) (b[0] + 0.5);
    a = (double *) ralloc((unsigned) (sizeof(double) * (n + 1)));
    for (i = 0; i < n + 1; i++)
	a[i] = b[i];
    return(a);
}

/* ARGSUSED quieten lint */
void    edge_apply_corr(Edgel * edge, int type, Camera * cam)

/* unused */

{
    if (edge == NULL || cam == NULL || cam->correct_func == NULL || cam->distort_params == NULL)
	return;
    edge->type &= EDGE_SET_CORR_MASK;
    edge->type |= EDGE_CORRECTED;
    edge->pos = cam_correct(edge->pos, cam);
}

/* ARGSUSED quieten lint */
void    edge_add_corr_prop(Edgel * edge, int type, Camera * cam)
{
    Vec2   *r;

    if (edge == NULL || cam == NULL || cam->correct_func == NULL || cam->distort_params == NULL)
	return;
    r = vec2_alloc();

    *r = cam_correct(edge->pos, cam);
    edge->props = proplist_addifnp(edge->props, (void *) r, CORRPOS, vec2_free, true);
}

void    er_add_corrpos_prop(Imrect * er, Camera * cam)
{
    er_apply_to_all_edges(er, edge_add_corr_prop, (void *) cam);
}

void    er_correct(Imrect * er, Camera * cam)
{
    er_apply_to_all_edges(er, edge_apply_corr, (void *) cam);
}
