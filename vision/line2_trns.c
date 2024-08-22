/**@(#)
**/
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

void    line2_transform(Line2 * line, Transform2 trans)
{
    if (line)
    {
	line->p1 = trans2_pos(trans, line->p1);
	line->p2 = trans2_pos(trans, line->p2);
	line->p = trans2_pos(trans, line->p);
	line->v = trans2_vec(trans, line->v);
    }
}

int     line2_on_and_overlap(Line2 * l1, Line2 * l2, double length_ratio, double posth)
{
    Vec2    p1 = {Vec2_id};
    Vec2    p2 = {Vec2_id};
    float   d1, d2;
    float   min_length;

    /* find end points of l2 w.r.t. l1->p1 */
    p1 = vec2_diff(l2->p1, l1->p1);
    p2 = vec2_diff(l2->p2, l1->p1);

    /* and their distances from l1->p1 along direction l1->v */
    d1 = (float)vec2_dot(l1->v, p1);
    d2 = (float)vec2_dot(l1->v, p2);

    min_length = (float)fmin(l1->length, l2->length);

    if (overlap_length(d1, d2, 0.0, l1->length) < min_length * length_ratio)
	return (0);

    if (d1 > d2)
	SWAP(float, d1, d2);

    /* find distances from overlaping endpoints to other line */
    if (d1 < 0)			/* use l1->p1 */
	p1 = vec2_projperp(vec2_diff(l1->p1, l2->p1), l2->v);
    else			/* use l2->p1 */
	p1 = vec2_diff(p1, vec2_times(d1, l1->v));

    if (d2 > l1->length)	/* use l1->p2 */
	p2 = vec2_projperp(vec2_diff(l1->p2, l2->p1), l2->v);
    else			/* use l2->p1 */
	p2 = vec2_diff(p2, vec2_times(d2, l1->v));

    posth *= posth;
    return (vec2_sqrmod(p1) < posth && vec2_sqrmod(p2) < posth);
}

int     line2_coincident(Line2 * l1, Line2 * l2, double doterror, double poserror)

/* BUG */
{
    if (l1 == NULL || l2 == NULL)
	return (0);

    return (line2_on_and_overlap(l1, l2, 0.5, poserror));
}
