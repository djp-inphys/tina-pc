/** @(#)Functions for manipulating 2D lines
 *
 * typedef struct line2
 * {
 * int     type;
 * struct vec2 p1, p2;
 * struct vec2 v;
 * float   length;
 * struct list *props;
 * }       Line2;
 */

#include <stdio.h>
#include <math.h>
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>
#ifdef _PCC
#include <memory.h>
#endif

Line2  *line2_alloc(unsigned int type)
{
    Line2  *line = ts_ralloc(Line2);

    line->type = type;
    line->label = new_label();
    return (line);
}

Line2  *line2_make(Vec2 p1, Vec2 p2, unsigned int type)
{
    Line2  *line = ts_ralloc(Line2);

    line->type = type;
    line->label = new_label();
    line->p1 = p1;
    line->p2 = p2;
    line->p = vec2_times(0.5, vec2_sum(p1, p2));
    line->v = vec2_diff(p2, p1);
    line->length = (float)vec2_mod(line->v);
    line->v = vec2_times(1.0 / line->length, line->v);
    line->props = NULL;
    return (line);
}

void    line2_free(Line2 * line)
{
    if (line == NULL)
	return;
    proplist_freelist(line->props);
    rfree((void *) line);
}

Line2  *line2_copy(Line2 * line)
{
    Line2  *copy;
    List   *proplist_copy();

    if (line == NULL)
	return (NULL);

    copy = ts_ralloc(Line2);
    (void) memcpy((char *) copy, (char *) line, sizeof(Line2));
    copy->props = proplist_copy(line->props);
    return (copy);
}

Line2  *line2_negative(Line2 * line)
{
    if (line == NULL)
	return (NULL);

    line = line2_copy(line);
    SWAP(Vec2, line->p1, line->p2);
    line->v = vec2_minus(line->v);
    return (line);
}

void    line2_negate(Line2 * line)
{
    if (line == NULL)
	return;

    SWAP(Vec2, line->p1, line->p2);
    line->v = vec2_minus(line->v);
}

Bool    line2_point_on_line(Line2 * line, Vec2 p, double thres)
{
    Vec2    d = {Vec2_id};
    double  dp;

    d = vec2_diff(p, line->p1);
    dp = vec2_dot(line->v, d);
    d = vec2_diff(d, vec2_times(dp, line->v));
    return ((vec2_sqrmod(d) < SQR(thres)) ? true : false);
}
