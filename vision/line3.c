/**@(#)
**/
/* line3.c functions for manipulating 3D lines
 * 
 * typedef struct line3 { int type; struct vec3 p1,p2; struct vec3 v;
 * float length; struct list *props; } Line3;
 * 
 */

#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>
#ifdef _PCC
#include <memory.h>
#endif

Line3  *line3_alloc(unsigned int type)
{
    Line3  *line = ts_ralloc(Line3);

    line->type = type;
    line->label = new_label();
    return (line);
}

Line3  *line3_make(Vec3 p1, Vec3 p2, int type)
{
    Line3  *line = ts_ralloc(Line3);

    line->type = type;
    line->label = new_label();
    line->p1 = p1;
    line->p2 = p2;
    line->p = vec3_times(0.5, vec3_sum(p1, p2));
    line->v = vec3_diff(p2, p1);
    line->length = (float)vec3_mod(line->v);
    line->v = vec3_times(1.0 / line->length, line->v);
    line->props = NULL;
    return (line);
}

void    line3_remake(Line3 * line, int type)
{
    if (line == NULL)
	return;

    line->type = type;
    line->p = vec3_times(0.5, vec3_sum(line->p1, line->p2));
    line->v = vec3_diff(line->p2, line->p1);
    line->length = (float)vec3_mod(line->v);
    line->v = vec3_times(1.0 / line->length, line->v);
}

void    line3_free(Line3 * line)
{
    if (line == NULL)
	return;
    proplist_freelist(line->props);
    rfree((void *) line);
}

Line3  *line3_copy(Line3 * line)/* identical copy that shares proplist */

{
    Line3  *copy;
    List   *proplist_copy();

    if (line == NULL)
	return (NULL);

    copy = ts_ralloc(Line3);
    (void) memcpy((char *) copy, (char *) line, sizeof(Line3));
    copy->props = proplist_copy(line->props);
    return (copy);
}

Line3  *line3_clone(Line3 * line)	/* identical copy with null
					 * proplist */

{
    Line3  *copy;

    if (line == NULL)
	return (NULL);

    copy = ts_ralloc(Line3);
    (void) memcpy((char *) copy, (char *) line, sizeof(Line3));
    copy->props = NULL;
    return (copy);
}

Line3  *line3_negative(Line3 * line)
{
    if (line == NULL)
	return (NULL);

    line = line3_copy(line);
    SWAP(Vec3, line->p1, line->p2);
    line->v = vec3_minus(line->v);
    return (line);
}

void    line3_negate(Line3 * line)
{
    if (line == NULL)
	return;

    SWAP(Vec3, line->p1, line->p2);
    line->v = vec3_minus(line->v);
}

/* rough separation between mid points */

double  line3_separation(Line3 * l1, Line3 * l2)
{
    Vec3    c1 = {Vec3_id};
    Vec3    c2 = {Vec3_id};

    if (l1 == NULL || l2 == NULL)
	return (0.0);		/* meaningless */

    c1 = vec3_times(0.5, vec3_sum(l1->p1, l1->p2));
    c2 = vec3_times(0.5, vec3_sum(l2->p1, l2->p2));

    return (vec3_mod(vec3_diff(c1, c2)));
}

/* minimum separation between extended lines */

double  line3_min_separation(Line3 * l1, Line3 * l2)
{
    float   d1, d2, d3, d4;

    d1 = (float)vec3_mod(vec3_diff(l1->p1, l2->p1));
    d2 = (float)vec3_mod(vec3_diff(l1->p1, l2->p2));
    d3 = (float)vec3_mod(vec3_diff(l1->p2, l2->p1));
    d4 = (float)vec3_mod(vec3_diff(l1->p2, l2->p2));

    d1 = MIN(d1, d2);
    d3 = MIN(d3, d4);

    return (MIN(d1, d3));
}

Bool    line3_point_on_line(Line3 * line, Vec3 p, double thres)
{
    Vec3    d = {Vec3_id};
    double  dp;

    d = vec3_diff(p, line->p1);
    dp = vec3_dot(line->v, d);
    d = vec3_diff(d, vec3_times(dp, line->v));
    return ((vec3_sqrmod(d) < SQR(thres)) ? true : false);
}
