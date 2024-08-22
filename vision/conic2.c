/**@(#)
**/
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/**
recover unbroken (in pixel sence) string of Vec2 from conic
**/

static Conic *conic;

static Ddlist *conic2_chop(double t1, double t2, Vec2 v1, Vec2 v2)
{
    int     x1, y1, x2, y2;
    double  t;
    Vec2    v = {Vec2_id};

    x1 = (int)floor(vec2_x(v1));
    y1 = (int)floor(vec2_y(v1));
    x2 = (int)floor(vec2_x(v2));
    y2 = (int)floor(vec2_y(v2));
    if (x1 == x2 && y1 == y2)	/* same pixel */
	return (NULL);
    if (abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1)	/* neighbours */
	return (dd_link_alloc((void *) vec2_make(v2), VEC2));

    t = (t1 + t2) * 0.5;
    v = conic_point(conic, t);
    return (dd_append(conic2_chop(t1, t, v1, v), conic2_chop(t, t2, v, v2)));
}

Tstring *conic2_string(Conic * c)
{
    Ddlist *list;
    Tstring *str;
    double  t1, t2, tm;
    Vec2    v1 = {Vec2_id};
    Vec2    v2 = {Vec2_id};
    Vec2    vm = {Vec2_id};
    int     x1, x2, y1, y2;

    if (c == NULL)
	return (NULL);

    conic = c;
    t1 = c->t1;
    t2 = c->t2;
    tm = (t1 + t2) * 0.5;
    v1 = conic_point(c, t1);
    v2 = conic_point(c, t2);
    vm = conic_point(c, tm);
    list = dd_link_alloc((void *) vec2_make(v1), VEC2);
    list = dd_append(list, conic2_chop(t1, tm, v1, vm));
    list = dd_append(list, conic2_chop(tm, t2, vm, v2));

    str = str_make(STRING, list, dd_get_end(list));
    if (str == NULL || str->count <= 3)
	return (str);

    x1 = (int)floor(vec2_x(v1));
    x2 = (int)floor(vec2_x(v2));
    y1 = (int)floor(vec2_y(v1));
    y2 = (int)floor(vec2_y(v2));
    if (abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1)	/* neighbours */
    {
	if (x1 == x2 && y1 == y2)	/* in same pixel */
	{
	    str->start = str->start->next;
	    (void) dd_link_rm(list, rfree);	/* same as start */
	}
	str->type = LOOP;
	str->start->last = str->end;
	str->end->next = str->start;
    }
    return (str);
}
