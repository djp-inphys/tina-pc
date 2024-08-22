/**@(#)
**/
/**
rect.c:
general rectification function
**/

#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

Vec2    rectify_pos(Mat3 rect, Vec2 p)
{
    Vec3    w = {Vec3_id};

    w = proj3_of_vec2(p);
    w = mat3_vprod(rect, w);
    return (proj2_of_vec3(w));
}

double  rectify_orient(Mat3 rect, Vec2 p, double or)

/* position */
/* orientation in radians */
{
    Vec2    md = {Vec2_id};
    Vec2    pd = {Vec2_id};	/* pos minus delta and plus delta */
    float   s = (float)sin(or), c = (float)cos(or);

    pd = rectify_pos(rect, vec2(vec2_x(p) + c, vec2_y(p) + s));
    md = rectify_pos(rect, vec2(vec2_x(p) - c, vec2_y(p) - s));

    p = vec2_diff(pd, md);
    return (atan2(vec2_y(p), vec2_x(p)));
}

void    rectify_pos_and_dir(Mat3 rect, Vec2 * p, Vec2 * v)

/* position and direction */
{
    Vec2    q = {Vec2_id};

    q = vec2_sum(*p, *v);
    *p = rectify_pos(rect, *p);
    q = rectify_pos(rect, q);
    *v = vec2_unit(vec2_diff(q, *p));
}

/* ARGSUSED quieten lint */
void    edge_apply_rect(Edgel * edge, int type, Mat3 * rect)

/* unused */

{
    if (edge == NULL || rect == NULL)
	return;

    edge->type &= EDGE_SET_RECT_MASK;
    edge->type |= EDGE_RECTIFIED;
    edge->pos = rectify_pos(*rect, edge->pos);
    edge->orient = (float)rectify_orient(*rect, edge->pos, edge->orient);
}

/* ARGSUSED quieten lint */
void    edge_apply_derect(Edgel * edge, int type, Mat3 * rect)

/* unused */

{
    if (edge == NULL || rect == NULL)
	return;

    edge->type &= EDGE_SET_RECT_MASK;
    edge->type |= EDGE_NOT_RECTIFIED;
    edge->pos = rectify_pos(*rect, edge->pos);
    edge->orient = (float)rectify_orient(*rect, edge->pos, edge->orient);
}

/* ARGSUSED quieten lint */
void    edge_add_rect_prop(Edgel * edge, int type, Mat3 * rect)

/* unused */

{
    Vec2   *r;

    if (edge == NULL)
	return;

    r = vec2_alloc();
    *r = rectify_pos(*rect, edge->pos);
    edge->props = proplist_addifnp(edge->props, (void *) r, RECTPOS, vec2_free, true);
}

void    er_add_rectpos_prop(Imrect * er, Mat3 rect)
{
    er_apply_to_all_edges(er, edge_add_rect_prop, (void *) &rect);
}

void    er_rectify(Imrect * er, Mat3 rect)
{
    er_apply_to_all_edges(er, edge_apply_rect, (void *) &rect);
}

void    er_derectify(Imrect * er, Mat3 rect)
{
    er_apply_to_all_edges(er, edge_apply_derect, (void *) &rect);
}
