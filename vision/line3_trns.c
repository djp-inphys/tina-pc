/**@(#)
**/
/* line3_trns.c
 * 
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>

void    line3_transform(Line3 * line, Transform3 trans)
{
    if (line == NULL)
	return;

    line->p1 = trans3_pos(trans, line->p1);
    line->p2 = trans3_pos(trans, line->p2);
    line->p = trans3_pos(trans, line->p);
    line->v = trans3_vec(trans, line->v);
}

double  overlap_length(double a1, double a2, double b1, double b2)
{
    if (a1 > a2)
	SWAP(double, a1, a2);
    if (b1 > b2)
	SWAP(double, b1, b2);
    if (a1 > b2 || a2 < b1)
	return (0.0);
    if (a1 < b1)
	a1 = b1;
    if (a2 > b2)
	a2 = b2;
    return (a2 - a1);
}

int     line3_on_and_overlap(Line3 * l1, Line3 * l2, double length_ratio, double posth)
{
    Vec3    p1 = {Vec3_id};
    Vec3    p2 = {Vec3_id};
    float   d1, d2;
    float   min_length;

    /* find end points of l2 w.r.t. l1->p1 */
    p1 = vec3_diff(l2->p1, l1->p1);
    p2 = vec3_diff(l2->p2, l1->p1);

    /* and their distances from l1->p1 along direction l1->v */
    d1 = (float) vec3_dot(l1->v, p1);
    d2 = (float) vec3_dot(l1->v, p2);

    min_length = (float) fmin(l1->length, l2->length);

    if (overlap_length(d1, d2, 0.0, l1->length) < min_length * length_ratio)
	return (0);

    if (d1 > d2)
	SWAP(float, d1, d2);

    /* find distances from overlaping endpoints to other line */
    if (d1 < 0)			/* use l1->p1 */
	p1 = vec3_projperp(vec3_diff(l1->p1, l2->p1), l2->v);
    else			/* use l2->p1 */
	p1 = vec3_diff(p1, vec3_times(d1, l1->v));

    if (d2 > l1->length)	/* use l1->p2 */
	p2 = vec3_projperp(vec3_diff(l1->p2, l2->p1), l2->v);
    else			/* use l2->p1 */
	p2 = vec3_diff(p2, vec3_times(d2, l1->v));

    posth *= posth;
    return (vec3_sqrmod(p1) < posth && vec3_sqrmod(p2) < posth);
}

int     line3_coincident(Line3 * l1, Line3 * l2, double doterror, double poserror)

/* BUG */
{
    if (l1 == NULL || l2 == NULL)
	return (0);

    if (vec3_dot(l1->v, l2->v) < 0)
	return (0);		/* pointing in opposite directions */

    return (line3_on_and_overlap(l1, l2, 0.5, poserror));
}

Bool    line3_within_error(Line3 * l1, Line3 * l2)
{
    Iso_error *iso1;
    Iso_error *iso2;

    if (l1 == NULL || l2 == NULL)
	return (false);

    iso1 = (Iso_error *) prop_get(l1->props, ISO_ERROR);
    iso2 = (Iso_error *) prop_get(l2->props, ISO_ERROR);

    if (iso1 == NULL || iso2 == NULL)
	return (false);

    if (!line3_coincident(l1, l2, iso1->dot * iso2->dot, iso1->pos + iso2->pos))
	return (false);

    return (true);
}
