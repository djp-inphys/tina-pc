/**@(#)
**/
#include <tina/sys.h>
#include <tina/sysfuncs.h>
#include <tina/math.h>
#include <tina/mathfuncs.h>
#include <tina/vision.h>
#include <tina/visionfuncs.h>

/**
recover unbroken (in pixel sence) string of Vec2 from curve function
**/

static  Vec2(*curve_func) ();
static void *curve_data;
static void *extra_data;

static Ddlist *curve2_chop(double t1, double t2, Vec2 v1, Vec2 v2)
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
    v = curve_func(curve_data, t, extra_data);
    return (dd_append(curve2_chop(t1, t, v1, v), curve2_chop(t, t2, v, v2)));
}

Tstring *str2_of_curve2(Vec2(*c_func) ( /* ??? */ ), void *c_data, double t1, double t2, void *e_data)
{
    Ddlist *list;
    Tstring *str;
    double  tm;
    Vec2    v1 = {Vec2_id};
    Vec2    v2 = {Vec2_id};
    Vec2    vm = {Vec2_id};
    int     x1, x2, y1, y2;

    if (c_func == NULL)
	return (NULL);

    curve_func = c_func;
    curve_data = c_data;
    extra_data = e_data;

    tm = (t1 + t2) * 0.5;
    v1 = curve_func(curve_data, t1, extra_data);
    v2 = curve_func(curve_data, t2, extra_data);
    vm = curve_func(curve_data, tm, extra_data);
    list = dd_link_alloc((void *) vec2_make(v1), VEC2);
    list = dd_append(list, curve2_chop(t1, tm, v1, vm));
    list = dd_append(list, curve2_chop(tm, t2, vm, v2));

    str = str_make(STRING, list, dd_get_end(list));
    if (str == NULL || str->start == str->end)
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
